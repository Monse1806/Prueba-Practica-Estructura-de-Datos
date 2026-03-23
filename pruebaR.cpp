#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "Estructuras.h"
#include "listas.h"
#include "interfaz.h"
using namespace std;
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    cout << endl << "  Presiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}
//  OPCION 1: REGISTRAR TORRE
void registrarTorre(ListaTorres& torres, Juego& j) {
    limpiarPantalla();
    cout << endl << "  === REGISTRAR TORRE ===" << endl << endl;

    Torre t;
    t.id = 0;

    cout << "  Nombre: ";
    cin.ignore();
    getline(cin, t.nombre);

    cout << "  Tipo:" << endl;
    cout << "    1 - Arquero  (danio ligero, rango medio)" << endl;
    cout << "    2 - Canon    (danio alto,  rango amplio)" << endl;
    cout << "    3 - Mago     (danio magico, rango corto)" << endl;
    cout << "    4 - Otro" << endl;
    cout << "  Opcion: ";
    int op; cin >> op;
    if      (op == 1) { t.tipo = "Arquero"; t.danio = 20; t.rango = 2; t.costo = 100; }
    else if (op == 2) { t.tipo = "Canon";   t.danio = 35; t.rango = 3; t.costo = 200; }
    else if (op == 3) { t.tipo = "Mago";    t.danio = 25; t.rango = 1; t.costo = 150; }
    else              { t.tipo = "Otro";    t.danio = 15; t.rango = 2; t.costo = 80;  }

    cout << endl << "  Valores por defecto para " << t.tipo << ":" << endl;
    cout << "    Danio=" << t.danio << "  Rango=" << t.rango << "  Costo=" << t.costo << endl;
    cout << "  Desea personalizarlos? (1=Si / 0=No): ";
    int custom; cin >> custom;
    if (custom == 1) {
        cout << "  Danio: "; cin >> t.danio;
        cout << "  Rango: "; cin >> t.rango;
        cout << "  Costo: "; cin >> t.costo;
    }

    cout << endl << "  Posicion en el camino (0-20): ";
    cin >> t.posicion;
    if (t.posicion < 0 || t.posicion > j.longitudRuta) {
        cout << "  [!] Posicion invalida." << endl;
        pausar(); return;
    }
    if (t.costo > j.oro) {
        cout << "  [!] Oro insuficiente! Tienes " << j.oro
             << " | Necesitas " << t.costo << endl;
        pausar(); return;
    }
    if (torres.insertar(t)) {
        j.oro -= t.costo;
        cout << endl << "  [OK] Torre '" << t.nombre << "' colocada en posicion "
             << t.posicion << "! Oro restante: " << j.oro << endl;
    }
    pausar();
}
//  OPCION 3: ELIMINAR TORRE
void eliminarTorre(ListaTorres& torres) {
    limpiarPantalla();
    cout << endl << "  === ELIMINAR TORRE ===" << endl << endl;
    torres.mostrar();
    if (torres.contar() == 0) { pausar(); return; }
    cout << endl << "  ID a eliminar: ";
    int id; cin >> id;
    if (torres.eliminar(id))
        cout << "  [OK] Torre eliminada." << endl;
    else
        cout << "  [!] No encontrada." << endl;
    pausar();
}

//  OPCION 4: REGISTRAR OLEADA
void registrarOleada(ListaOleadas& oleadas) {
    limpiarPantalla();
    cout << endl << "  === REGISTRAR OLEADA ===" << endl << endl;
    Oleada o;
    o.idOleada = 0;
    cout << "  Tipo de enemigo (Basico / Rapido / Fuerte): ";
    cin.ignore();
    getline(cin, o.tipoEnemigo);
    cout << "  Cantidad de enemigos: "; cin >> o.cantidadEnemigos;
    cout << "  Vida base:            "; cin >> o.vidaBase;
    cout << "  Velocidad base (1-3): "; cin >> o.velocidadBase;
    oleadas.registrar(o);
    cout << endl << "  [OK] Oleada registrada!" << endl;
    pausar();
}

//  OPCION 6: INICIAR SIGUIENTE OLEADA
void iniciarSiguienteOleada(ListaOleadas& oleadas, ListaEnemigos& enemigos) {
    limpiarPantalla();
    cout << endl << "  === INICIAR OLEADA ===" << endl << endl;
    if (oleadas.estaVacia()) {
        cout << "  No hay oleadas registradas." << endl;
        pausar(); return;
    }
    Oleada* ola = oleadas.getActual();
    if (!ola) { pausar(); return; }

    cout << "  Lanzando oleada #" << ola->idOleada
         << "  [" << ola->tipoEnemigo << "]"
         << "  x" << ola->cantidadEnemigos << " enemigos" << endl << endl;

    for (int i = 0; i < ola->cantidadEnemigos; i++) {
        Enemigo e;
        e.id         = 0;
        e.tipo       = ola->tipoEnemigo;
        e.vida       = ola->vidaBase;
        e.velocidad  = ola->velocidadBase;
        e.posicion   = 0;
        e.recompensa = ola->vidaBase / 10;
        enemigos.insertarAlFinal(e);
        cout << "  >> Enemigo " << (i+1) << " [" << e.tipo
             << "] desplegado en pos 0" << endl;
    }
    cout << endl << "  [OK] " << ola->cantidadEnemigos << " enemigos en campo!" << endl;
    oleadas.avanzar();
    pausar();
}

//  OPCION 7: AVANZAR TURNO
void avanzarTurno(ListaTorres& torres, ListaEnemigos& enemigos, Juego& j) {
    limpiarPantalla();
    j.turno++;
    cout << endl;
    cout << "  +========================================+" << endl;
    cout << "  |         TURNO #" << setw(3) << j.turno
         << " EN PROGRESO           |" << endl;
    cout << "  +========================================+" << endl;

    if (enemigos.estaVacia()) {
        cout << endl << "  No hay enemigos en el campo." << endl;
        pausar(); return;
    }

    // PASO 1: Mover enemigos
    cout << endl << "  [ MOVIMIENTO ]" << endl;
    NodoEnemigo* a = enemigos.getFirst();
    while (a) {
        a->dato.posicion += a->dato.velocidad;
        cout << "  E#" << a->dato.id
             << " [" << a->dato.tipo << "] -> pos " << a->dato.posicion << endl;
        a = a->next;
    }

    // PASO 2: Torres atacan
    cout << endl << "  [ ATAQUE DE TORRES ]" << endl;
    bool hayAtaque = false;
    for (int ti = 0; ti < torres.getTam(); ti++) {
        Torre& tor = torres.get(ti);
        NodoEnemigo* ene = enemigos.getFirst();
        while (ene) {
            int dist = ene->dato.posicion - tor.posicion;
            if (dist < 0) dist = -dist;
            if (dist <= tor.rango) {
                ene->dato.vida -= tor.danio;
                hayAtaque = true;
                cout << "  [" << tor.nombre << "] ataca E#"
                     << ene->dato.id << "  -" << tor.danio
                     << " vida  => vida: " << ene->dato.vida << endl;
            }
            ene = ene->next;
        }
    }
    if (!hayAtaque) cout << "  (Ninguna torre en rango)" << endl;

    // PASO 3: Eliminar muertos / llegaron a base
    cout << endl << "  [ RESULTADOS ]" << endl;
    NodoEnemigo* cur = enemigos.getFirst();
    while (cur) {
        NodoEnemigo* sig = cur->next;
        if (cur->dato.vida <= 0) {
            cout << "  [+] E#" << cur->dato.id
                 << " destruido! +" << cur->dato.recompensa << " oro" << endl;
            j.oro += cur->dato.recompensa;
            j.enemigosEliminados++;
            enemigos.eliminar(cur->dato.id);
        } else if (cur->dato.posicion >= j.longitudRuta) {
            cout << "  [!!] E#" << cur->dato.id
                 << " llego a la BASE! -1 vida" << endl;
            j.vidasJugador--;
            j.enemigosLlegaron++;
            enemigos.eliminar(cur->dato.id);
        }
        cur = sig;
    }

    // PASO 4: Game Over
    if (j.vidasJugador <= 0) {
        j.partidaActiva = false;
        cout << endl;
        cout << "  +==============================+" << endl;
        cout << "  |   *** GAME  OVER ***         |" << endl;
        cout << "  |  Los enemigos tomaron la base|" << endl;
        cout << "  +==============================+" << endl;
    }

    cout << endl << "  >> Turno #" << j.turno
         << " | Vidas=" << j.vidasJugador
         << " | Oro=" << j.oro
         << " | Elim=" << j.enemigosEliminados << endl;

    pausar();
}

#endif
