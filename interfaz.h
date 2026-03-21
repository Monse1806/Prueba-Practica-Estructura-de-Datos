#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <iostream>
#include <iomanip>
#include <string>
#include "estructuras.h"
#include "listas.h"
#include "logica.h"
using namespace std;

// ============================================================
//  PERSONA 4 - INTERFAZ, MAPA Y PANTALLAS
//  Archivo: interfaz.h
// ============================================================

#define MAP_ROWS 8
#define MAP_COLS 21
#define PATH_ROW 5
#define CELL_BLANK   0
#define CELL_SCENERY 1
#define CELL_PATH    2
#define CELL_TOWER   3
#define CELL_ENEMY   4
#define CELL_BASE    5
#define CELL_START   6

int mapaBase[MAP_ROWS][MAP_COLS] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

// ------------------------------------------------------------
//  DIBUJAR MAPA 2D
// ------------------------------------------------------------
void dibujarMapa(ListaTorres& torres, ListaEnemigos& enemigos, const Juego& j) {
    int mapa[MAP_ROWS][MAP_COLS];
    for (int r = 0; r < MAP_ROWS; r++)
        for (int c = 0; c < MAP_COLS; c++)
            mapa[r][c] = mapaBase[r][c];

    for (int i = 0; i < torres.getTam(); i++) {
        int pos = torres.get(i).posicion;
        if (pos >= 0 && pos < MAP_COLS) mapa[PATH_ROW][pos] = CELL_TOWER;
    }
    NodoEnemigo* ne = enemigos.getFirst();
    while (ne) {
        int pos = ne->dato.posicion;
        if (pos >= 0 && pos < MAP_COLS) mapa[PATH_ROW][pos] = CELL_ENEMY;
        ne = ne->next;
    }
    if (mapa[PATH_ROW][0]  == CELL_PATH) mapa[PATH_ROW][0]  = CELL_START;
    if (mapa[PATH_ROW][20] == CELL_PATH) mapa[PATH_ROW][20] = CELL_BASE;

    cout << "     ";
    for (int c = 0; c < MAP_COLS; c++) cout << setw(3) << c;
    cout << "  (x)" << endl;

    for (int r = 0; r < MAP_ROWS; r++) {
        cout << setw(3) << r << "  ";
        for (int c = 0; c < MAP_COLS; c++) {
            switch (mapa[r][c]) {
                case CELL_BLANK:   cout << " . "; break;
                case CELL_SCENERY: cout << " # "; break;
                case CELL_PATH:    cout << " - "; break;
                case CELL_TOWER:   cout << "[T]"; break;
                case CELL_ENEMY:   cout << "[E]"; break;
                case CELL_BASE:    cout << "[B]"; break;
                case CELL_START:   cout << "[S]"; break;
                default:           cout << " . "; break;
            }
        }
        cout << endl;
    }
    cout << "  (y)" << endl << endl;
    cout << "  Leyenda: [T]=Torre  [E]=Enemigo  [S]=Inicio  [B]=Base  [-]=Camino  [.]=Libre" << endl;
}

// ------------------------------------------------------------
//  HUD (barra de estado)
// ------------------------------------------------------------
void mostrarHUD(const Juego& j) {
    string vidas = "";
    for (int i = 0; i < j.vidasJugador; i++) vidas += "<3 ";
    if (j.vidasJugador <= 0) vidas = "GAME OVER";

    cout << "  +------------------+------------------+------------------+------------------+" << endl;
    cout << "  | TURNO: " << left << setw(10) << j.turno
         << "| VIDAS: "  << left << setw(10) << vidas
         << "| ORO: "    << left << setw(12) << j.oro
         << "| ELIM: "   << left << setw(10) << j.enemigosEliminados
         << "|" << endl;
    cout << "  +------------------+------------------+------------------+------------------+" << endl;
}

// ------------------------------------------------------------
//  MENU PRINCIPAL
// ------------------------------------------------------------
void mostrarMenu() {
    cout << endl;
    cout << "  +------------------------------------------+" << endl;
    cout << "  |        TOWER DEFENSE  - MENU             |" << endl;
    cout << "  +------------------------------------------+" << endl;
    cout << "  |  1 - Registrar torre defensiva           |" << endl;
    cout << "  |  2 - Mostrar torres registradas          |" << endl;
    cout << "  |  3 - Eliminar torre                      |" << endl;
    cout << "  |  4 - Registrar oleada                    |" << endl;
    cout << "  |  5 - Mostrar oleadas                     |" << endl;
    cout << "  |  6 - Iniciar siguiente oleada            |" << endl;
    cout << "  |  7 - Avanzar turno                       |" << endl;
    cout << "  |  8 - Mostrar enemigos activos            |" << endl;
    cout << "  |  9 - Estado general del juego            |" << endl;
    cout << "  |  0 - Salir                               |" << endl;
    cout << "  +------------------------------------------+" << endl;
    cout << endl << "  Input: ";
}

// ------------------------------------------------------------
//  PANTALLA PRINCIPAL
// ------------------------------------------------------------
void mostrarPantallaPrincipal(ListaTorres& torres, ListaEnemigos& enemigos, const Juego& j) {
    limpiarPantalla();
    cout << endl;
    cout << "  =============================================" << endl;
    cout << "   TOWER DEFENSE | Estructura de Datos C++    " << endl;
    cout << "  =============================================" << endl;
    cout << endl;
    mostrarHUD(j);
    cout << endl;
    dibujarMapa(torres, enemigos, j);
    mostrarMenu();
}

// ------------------------------------------------------------
//  OPCION 9: ESTADO GENERAL
// ------------------------------------------------------------
void mostrarEstadoGeneral(ListaTorres& torres, ListaEnemigos& enemigos,
                           ListaOleadas& oleadas, const Juego& j) {
    limpiarPantalla();
    cout << endl;
    cout << "  +=============================================+" << endl;
    cout << "  |         ESTADO GENERAL DEL JUEGO           |" << endl;
    cout << "  +=============================================+" << endl;
    cout << "  | Turno          : " << left << setw(27) << j.turno              << "|" << endl;
    cout << "  | Vidas          : " << left << setw(27) << j.vidasJugador       << "|" << endl;
    cout << "  | Oro            : " << left << setw(27) << j.oro                << "|" << endl;
    cout << "  | Torres activas : " << left << setw(27) << torres.contar()      << "|" << endl;
    cout << "  | Enemigos campo : " << left << setw(27) << enemigos.getTam()    << "|" << endl;
    cout << "  | Oleadas regist.: " << left << setw(27) << oleadas.getTam()     << "|" << endl;
    cout << "  | Elim.          : " << left << setw(27) << j.enemigosEliminados << "|" << endl;
    cout << "  | Llegaron base  : " << left << setw(27) << j.enemigosLlegaron   << "|" << endl;
    if (j.partidaActiva)
        cout << "  | Estado         : " << left << setw(27) << "ACTIVA"    << "|" << endl;
    else
        cout << "  | Estado         : " << left << setw(27) << "TERMINADA" << "|" << endl;
    cout << "  +=============================================+" << endl;

    cout << endl << "  --- MAPA ACTUAL ---" << endl;
    dibujarMapa(torres, enemigos, j);

    cout << endl << "  --- TORRES ---" << endl;
    torres.mostrar();

    cout << endl << "  --- ENEMIGOS ACTIVOS ---" << endl;
    enemigos.recorrerAdelante();
    cout << endl;
    enemigos.recorrerAtras();

    cout << endl << "  --- OLEADAS ---" << endl;
    oleadas.mostrar();

    pausar();
}

#endif
