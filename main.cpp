#include <iostream>
#include <string>

using namespace std;

/*========================
    ESTRUCTURA LISTA
=========================*/

struct Producto
{
    string codigo;
    string nombre;
    float precio;
    int stock;

    Producto *siguiente;
};

