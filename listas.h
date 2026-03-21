#ifndef LISTAS_H
#define LISTAS_H

#include <iostream>
#include <iomanip>
#include <string>
#include "estructuras.h"
using namespace std;

//  LISTA SECUENCIAL - TORRES
class ListaTorres {
private:
    static const int MAX = 100;
    NodoTorre arreglo[MAX];
    int tam;
    int contadorId;
public:
    ListaTorres() : tam(0), contadorId(1) {}

    bool insertar(Torre t) {
        if (tam >= MAX) return false;
        t.id = contadorId++;
        arreglo[tam].dato = t;
        tam++;
        return true;
    }
    bool eliminar(int id) {
        for (int i = 0; i < tam; i++) {
            if (arreglo[i].dato.id == id) {
                for (int j = i; j < tam-1; j++) arreglo[j] = arreglo[j+1];
                tam--;
                return true;
            }
        }
        return false;
    }
    Torre* buscar(int id) {
        for (int i = 0; i < tam; i++)
            if (arreglo[i].dato.id == id) return &arreglo[i].dato;
        return NULL;
    }
    void mostrar() const {
        if (tam == 0) { cout << "  (Sin torres)" << endl; return; }
        cout << "  | ID | Nombre         | Tipo     | Pos | Danio | Rango | Costo|" << endl;
        for (int i = 0; i < tam; i++) {
            const Torre& t = arreglo[i].dato;
            string icono = (t.tipo=="Arquero")?"[A]":(t.tipo=="Canon")?"[C]":(t.tipo=="Mago")?"[M]":"[T]";
            cout << "  | " << left << setw(3) << t.id
                 << "| " << setw(15) << t.nombre
                 << "| " << setw(9)  << t.tipo
                 << "| " << setw(4)  << t.posicion
                 << "| " << setw(6)  << t.danio
                 << "| " << setw(6)  << t.rango
                 << "| " << setw(5)  << t.costo << "| " << icono << endl;
        }
        cout << "  Torres activas: " << tam << endl;
    }
    int contar() const { return tam; }
    int getTam()  const { return tam; }
    Torre& get(int i) { return arreglo[i].dato; }
};
//  LISTA DOBLEMENTE ENLAZADA - ENEMIGOS
class ListaEnemigos {
private:
    NodoEnemigo* first;
    NodoEnemigo* last;
    int tam;
    int contadorId;
public:
    ListaEnemigos() : first(NULL), last(NULL), tam(0), contadorId(1) {}
    ~ListaEnemigos() {
        NodoEnemigo* a = first;
        while (a) { NodoEnemigo* s = a->next; delete a; a = s; }
    }
    void insertarAlFinal(Enemigo e) {
        e.id = contadorId++;
        NodoEnemigo* n = new NodoEnemigo(e);
        if (!last) { first = last = n; }
        else { n->prev = last; last->next = n; last = n; }
        tam++;
    }
    bool eliminar(int id) {
        NodoEnemigo* a = first;
        while (a) {
            if (a->dato.id == id) {
                if (a->prev) a->prev->next = a->next; else first = a->next;
                if (a->next) a->next->prev = a->prev; else last  = a->prev;
                delete a; tam--; return true;
            }
            a = a->next;
        }
        return false;
    }
    Enemigo* buscar(int id) {
        NodoEnemigo* a = first;
        while (a) { if (a->dato.id == id) return &a->dato; a = a->next; }
        return NULL;
    }
    void recorrerAdelante() const {
        if (!first) { cout << "  (Sin enemigos activos)" << endl; return; }
        cout << "  | ID | Tipo     | Vida | Vel | Pos | Recomp |" << endl;
        NodoEnemigo* a = first;
        while (a) {
            const Enemigo& e = a->dato;
            int bar = (e.vida > 0) ? (e.vida / 10) : 0;
            if (bar > 10) bar = 10;
            string barra = string(bar,'#') + string(10-bar,'.');
            cout << "  | " << left << setw(3) << e.id
                 << "| " << setw(9) << e.tipo
                 << "| " << setw(5) << e.vida
                 << "| " << setw(4) << e.velocidad
                 << "| " << setw(4) << e.posicion
                 << "| " << setw(7) << e.recompensa
                 << "| [" << barra << "]" << endl;
            a = a->next;
        }
    }
    void recorrerAtras() const {
        if (!last) return;
        cout << "  [Recorrido INVERSO] ";
        NodoEnemigo* a = last;
        while (a) {
            cout << "E#" << a->dato.id << "(pos:" << a->dato.posicion << ") ";
            if (a->prev) cout << "<- ";
            a = a->prev;
        }
        cout << endl;
    }
    NodoEnemigo* getFirst() const { return first; }
    int  getTam()    const { return tam; }
    bool estaVacia() const { return first == NULL; }
};
//  LISTA CIRCULAR - OLEADAS
class ListaOleadas {
private:
    NodoOleada* ultimo;
    NodoOleada* oleadaActual;
    int tam;
    int contadorId;
public:
    ListaOleadas() : ultimo(NULL), oleadaActual(NULL), tam(0), contadorId(1) {}
    ~ListaOleadas() {
        if (!ultimo) return;
        NodoOleada* a = ultimo->next;
        while (a != ultimo) { NodoOleada* s = a->next; delete a; a = s; }
        delete ultimo;
    }
    void registrar(Oleada o) {
        o.idOleada = contadorId++;
        NodoOleada* n = new NodoOleada(o);
        if (!ultimo) { n->next = n; ultimo = n; oleadaActual = n; }
        else { n->next = ultimo->next; ultimo->next = n; ultimo = n; }
        tam++;
    }
    void mostrar() const {
        if (!ultimo) { cout << "  (Sin oleadas)" << endl; return; }
        cout << "  | ID | Cant  | Tipo     | Vida | Vel  |" << endl;
        NodoOleada* a = ultimo->next;
        for (int i = 0; i < tam; i++) {
            string marca = (a == oleadaActual) ? " <<" : "   ";
            cout << "  | " << left << setw(3) << a->dato.idOleada
                 << "| " << setw(6) << a->dato.cantidadEnemigos
                 << "| " << setw(9) << a->dato.tipoEnemigo
                 << "| " << setw(5) << a->dato.vidaBase
                 << "| " << setw(5) << a->dato.velocidadBase
                 << "|" << marca << endl;
            a = a->next;
        }
    }
    Oleada* getActual() { return oleadaActual ? &oleadaActual->dato : NULL; }
    void avanzar() {
        if (oleadaActual) {
            oleadaActual = oleadaActual->next;
            cout << "  Oleada avanzada -> ID: " << oleadaActual->dato.idOleada << endl;
        }
    }
    void reiniciar() {
        if (ultimo) { oleadaActual = ultimo->next; cout << "  Ciclo reiniciado." << endl; }
    }
    int  getTam()    const { return tam; }
    bool estaVacia() const { return ultimo == NULL; }
};

#endif
