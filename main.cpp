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

Producto *inicio = NULL;
/*========================
    ESTRUCTURA COLA
=========================*/

struct Pedido
{
    string cliente;
    string producto;
    int cantidad;

    Pedido *siguiente;
};

Pedido *frente = NULL;
Pedido *final = NULL;


/*========================
    ESTRUCTURA PILA
=========================*/

struct Accion
{
    string descripcion;

    Accion *siguiente;
};

Accion *tope = NULL;


/*========================
    FUNCIONES PILA
=========================*/

void pushAccion(string accion)
{
    Accion *nuevo = new Accion();

    nuevo->descripcion = accion;
    nuevo->siguiente = tope;

    tope = nuevo;

    cout << "\nAccion guardada correctamente\n";
}

void popAccion()
{
    if(tope == NULL)
    {
        cout << "\nPila vacia\n";
    }
    else
    {
        Accion *auxiliar = tope;

        cout << "\nUltima accion eliminada: "
             << auxiliar->descripcion << endl;

        tope = tope->siguiente;

        delete auxiliar;
    }
}


/*========================
    FUNCIONES LISTA
=========================*/

void insertarProducto()
{
    Producto *nuevo = new Producto();

    cout << "\n--- REGISTRO PRODUCTO ---\n";

    cout << "Codigo: ";
    cin >> nuevo->codigo;

    cin.ignore();

    cout << "Nombre: ";
    getline(cin, nuevo->nombre);

    cout << "Precio: ";
    cin >> nuevo->precio;

    cout << "Stock: ";
    cin >> nuevo->stock;

    nuevo->siguiente = NULL;

    if(inicio == NULL)
    {
        inicio = nuevo;
    }
    else
    {
        Producto *auxiliar = inicio;

        while(auxiliar->siguiente != NULL)
        {
            auxiliar = auxiliar->siguiente;
        }

        auxiliar->siguiente = nuevo;
    }

    pushAccion("Se agrego producto");

    cout << "\nProducto registrado correctamente\n";
}

void buscarProducto()
{
    string codigoBuscar;

    cout << "\nIngrese codigo a buscar: ";
    cin >> codigoBuscar;

    Producto *auxiliar = inicio;

    while(auxiliar != NULL)
    {
        if(auxiliar->codigo == codigoBuscar)
        {
            cout << "\nProducto encontrado\n";

            cout << "Codigo: "
                 << auxiliar->codigo << endl;

            cout << "Nombre: "
                 << auxiliar->nombre << endl;

            cout << "Precio: "
                 << auxiliar->precio << endl;

            cout << "Stock: "
                 << auxiliar->stock << endl;

            return;
        }

        auxiliar = auxiliar->siguiente;
    }

    cout << "\nProducto no encontrado\n";
}


/*========================
    FUNCIONES COLA
=========================*/

void encolarPedido()
{
    Pedido *nuevo = new Pedido();

    cout << "\n--- REGISTRAR PEDIDO ---\n";

    cin.ignore();

    cout << "Cliente: ";
    getline(cin, nuevo->cliente);

    cout << "Producto: ";
    getline(cin, nuevo->producto);

    cout << "Cantidad: ";
    cin >> nuevo->cantidad;

    nuevo->siguiente = NULL;

    if(frente == NULL)
    {
        frente = nuevo;
        final = nuevo;
    }
    else
    {
        final->siguiente = nuevo;
        final = nuevo;
    }

    pushAccion("Se registro pedido");

    cout << "\nPedido registrado correctamente\n";
}

void desencolarPedido()
{
    if(frente == NULL)
    {
        cout << "\nNo existen pedidos\n";
    }
    else
    {
        Pedido *auxiliar = frente;

        cout << "\nAtendiendo pedido de: "
             << auxiliar->cliente << endl;

        frente = frente->siguiente;

        delete auxiliar;

        pushAccion("Se atendio pedido");

        cout << "\nPedido atendido correctamente\n";
    }
}


/*========================
    MENU PRINCIPAL
=========================*/

void menu()
{
    int opcion;

    do
    {
        cout << "\n========= MENU =========\n";

        cout << "1. Registrar producto\n";
        cout << "2. Buscar producto\n";
        cout << "3. Registrar pedido\n";
        cout << "4. Atender pedido\n";
        cout << "5. Deshacer accion\n";
        cout << "6. Salir\n";

        cout << "\nSeleccione opcion: ";
        cin >> opcion;

        switch(opcion)
        {
            case 1:
                insertarProducto();
                break;

            case 2:
                buscarProducto();
                break;

            case 3:
                encolarPedido();
                break;

            case 4:
                desencolarPedido();
                break;

            case 5:
                popAccion();
                break;

            case 6:
                cout << "\nSaliendo del sistema...\n";
                break;

            default:
                cout << "\nOpcion incorrecta\n";
        }

    }while(opcion != 6);
}

int main()
{
    menu();

    return 0;
}