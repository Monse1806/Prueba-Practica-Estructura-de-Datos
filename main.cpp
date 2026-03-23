#include <iostream>
#include "Estructuras.h"
#include "listas.h"
#include "interfaz.h"
#include "logica.cpp"

using namespace std;

// Declaraciones de funciones que están en logica.cpp
void registrarTorre(ListaTorres& torres, Juego& j);
void mostrarTorres(ListaTorres& torres);
void eliminarTorre(ListaTorres& torres);
void registrarOleada(ListaOleadas& oleadas);
void mostrarOleadas(ListaOleadas& oleadas);
void iniciarSiguienteOleada(ListaOleadas& oleadas, ListaEnemigos& enemigos, Juego& j);
void avanzarTurno(ListaTorres& torres, ListaEnemigos& enemigos, Juego& j);
void mostrarEnemigosActivos(ListaEnemigos& enemigos);
void mostrarEstadoGeneral(ListaTorres& torres, ListaEnemigos& enemigos, ListaOleadas& oleadas, const Juego& j);

int main() {
    // Inicializar el juego
    Juego juego;
    juego.vidasJugador = 10;
    juego.turno = 0;
    juego.oro = 500;
    juego.enemigosEliminados = 0;
    juego.enemigosLlegaron = 0;
    juego.partidaActiva = true;
    juego.longitudRuta = 20;

    // Inicializar listas
    ListaTorres torres;
    ListaEnemigos enemigos;
    ListaOleadas oleadas;

    int opcion;
    
    do {
        mostrarPantallaPrincipal(torres, enemigos, juego);
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                registrarTorre(torres, juego);
                break;
            case 2:
                mostrarTorres(torres);
                break;
            case 3:
                eliminarTorre(torres);
                break;
            case 4:
                registrarOleada(oleadas);
                break;
            case 5:
                mostrarOleadas(oleadas);
                break;
            case 6:
                if (juego.partidaActiva) {
                    iniciarSiguienteOleada(oleadas, enemigos, juego);
                } else {
                    cout << "  Juego terminado. No se pueden iniciar nuevas oleadas." << endl;
                    pausar();
                }
                break;
            case 7:
                if (juego.partidaActiva) {
                    avanzarTurno(torres, enemigos, juego);
                } else {
                    cout << "  Juego terminado. No se puede avanzar turnos." << endl;
                    pausar();
                }
                break;
            case 8:
                mostrarEnemigosActivos(enemigos);
                break;
            case 9:
                mostrarEstadoGeneral(torres, enemigos, oleadas, juego);
                break;
            case 0:
                limpiarPantalla();
                cout << "\n  ============================================" << endl;
                cout << "        Gracias por jugar Tower Defense!" << endl;
                cout << "  ============================================" << endl;
                cout << "  Estadísticas finales:" << endl;
                cout << "  - Enemigos eliminados: " << juego.enemigosEliminados << endl;
                cout << "  - Turnos jugados: " << juego.turno << endl;
                cout << "  - Oro restante: " << juego.oro << endl;
                cout << endl;
                break;
            default:
                cout << "  Opción no válida. Intente de nuevo." << endl;
                pausar();
                break;
        }
        
    } while(opcion != 0);
    
    return 0;
}
