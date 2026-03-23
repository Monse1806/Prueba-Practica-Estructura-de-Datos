#include <iostream>

#include "Estructuras.h"
#include "listas.h"
#include "pruebaR.cpp"
#include "interfaz.h"   

using namespace std;

int main() {

    ListaJuego miLista; 

    mostrarBienvenida(); 

    iniciarPartida(miLista); 

    return 0;
}
