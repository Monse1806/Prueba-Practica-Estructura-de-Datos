#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <string>
using namespace std;
// Estructuras 
struct Torre {
    int id;
    string nombre;
    string tipo;
    int posicion;
    int danio;
    int rango;
    int costo;
};
struct NodoTorre { Torre dato; };

struct Enemigo {
    int id;
    string tipo;
    int vida;
    int velocidad;
    int posicion;
    int recompensa;
};
struct NodoEnemigo {
    Enemigo dato;
    NodoEnemigo* prev;
    NodoEnemigo* next;
    NodoEnemigo(Enemigo e) : dato(e), prev(NULL), next(NULL) {}
};

struct Oleada {
    int idOleada;
    int cantidadEnemigos;
    string tipoEnemigo;
    int vidaBase;
    int velocidadBase;
};
struct NodoOleada {
    Oleada dato;
    NodoOleada* next;
    NodoOleada(Oleada o) : dato(o), next(NULL) {}
};

struct Juego {
    int vidasJugador;
    int turno;
    int oro;
    int enemigosEliminados;
    int enemigosLlegaron;
    bool partidaActiva;
    int longitudRuta;
};

#endif
