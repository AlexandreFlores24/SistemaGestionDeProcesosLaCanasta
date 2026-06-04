#include <iostream>
#include <fstream>
#include <string>
//#include <limits>
using namespace std;

/*=================================
ESTRUCTURA PRODUCTO*/

struct Producto
{
    string codigo;
    string nombre;
    float precio;
    int stock;
   Producto *siguiente;
};

/*============================
ESTRUCTURA PEDIDO*/
struct Pedido
{
    string cliente;
    string codigoProducto;
    int cantidad;

    Pedido *siguiente;
};

/*======ESTRUCTURA PILA*++++++*/
struct Accion
{
    string descripcion;

    Accion *siguiente;
};

/*====VARIABLES GLOBALES=+++++++=*/

Producto *inicio = NULL;

/* Cola principal */
Pedido *frente = NULL;
Pedido *final = NULL;

/* Cola pendientes */
Pedido *frentePendiente = NULL;
Pedido *finalPendiente = NULL;

/* Pila */
Accion *tope = NULL;

/*=================
	VALIDACIONES****=====*/

void limpiarBuffer()
{
    cin.clear();
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

float leerPrecio()
{
    float precio;

    do
    {
        cout << "Precio: ";
        cin >> precio;

        if(cin.fail() || precio <= 0)
        {
            cout << "\nERROR. Ingrese un precio valido.\n";
            limpiarBuffer();
        }

    }while(cin.fail() || precio <= 0);

    return precio;
}

int leerStock()
{
    int stock;

    do
    {
        cout << "Stock: ";
        cin >> stock;

        if(cin.fail() || stock < 0)
        {
            cout << "\nERROR. Ingrese un stock valido.\n";
            limpiarBuffer();
        }

    }while(cin.fail() || stock < 0);

    return stock;
}

int leerCantidad()
{
    int cantidad;

    do
    {
        cout << "Cantidad: ";
        cin >> cantidad;

        if(cin.fail() || cantidad <= 0)
        {
            cout << "\nERROR. Cantidad invalida.\n";
            limpiarBuffer();
        }

    }while(cin.fail() || cantidad <= 0);

    return cantidad;
}

/*=================================
    VERIFICAR CODIGO REPETIDO====*/

bool codigoExiste(string codigo)
{
    Producto *aux = inicio;

    while(aux != NULL)
    {
        if(aux->codigo == codigo)
        {
            return true;
        }

        aux = aux->siguiente;
    }

    return false;
}

/*=================================
        PERSISTENCIA
=================================*/

void guardarProductos()
{
    ofstream archivo("productos.txt");

    Producto *aux = inicio;

    while(aux != NULL)
    {
        archivo << aux->codigo << endl;
        archivo << aux->nombre << endl;
        archivo << aux->precio << endl;
        archivo << aux->stock << endl;

        aux = aux->siguiente;
    }

    archivo.close();
}

void cargarProductos()
{
    ifstream archivo("productos.txt");

    if(!archivo)
        return;

    while(true)
    {
        Producto *nuevo = new Producto();

        if(!(archivo >> nuevo->codigo))
        {
            delete nuevo;
            break;
        }

        archivo.ignore();

        getline(archivo, nuevo->nombre);

        archivo >> nuevo->precio;
        archivo >> nuevo->stock;
        archivo.ignore();

        nuevo->siguiente = NULL;

        if(inicio == NULL)
        {
            inicio = nuevo;
        }
        else
        {
            Producto *aux = inicio;

            while(aux->siguiente != NULL)
            {
                aux = aux->siguiente;
            }

            aux->siguiente = nuevo;
        }
    }

    archivo.close();
}

/*=================================
            PILA
=================================*/

bool pilaVacia()
{
    return (tope == NULL);
}

void pushAccion(string accion)
{
    Accion *nuevo = new Accion();

    nuevo->descripcion = accion;
    nuevo->siguiente = tope;

    tope = nuevo;
}

void consultarUltimaAccion()
{
    if(pilaVacia())
    {
        cout << "\nNo existen acciones registradas.\n";
        return;
    }

    cout << "\nUltima accion: "
         << tope->descripcion << endl;
}

void popAccion()
{
    if(pilaVacia())
    {
        cout << "\nNo hay acciones para deshacer.\n";
        return;
    }

    Accion *aux = tope;

    cout << "\nAccion eliminada: "
         << aux->descripcion << endl;

    tope = tope->siguiente;

    delete aux;
} 
/*=================================
      LISTA ENLAZADA
=================================*/

void insertarProducto()
{
    Producto *nuevo = new Producto();

    cout << "\n===== REGISTRAR PRODUCTO =====\n";

    do
    {
        cout << "Codigo: ";
        cin >> nuevo->codigo;

        if(nuevo->codigo.empty())
        {
            cout << "\nCodigo no valido.\n";
        }
        else if(codigoExiste(nuevo->codigo))
        {
            cout << "\nEse codigo ya existe.\n";
            nuevo->codigo = "";
        }

    }while(nuevo->codigo.empty());

    cin.ignore();

    do
    {
        cout << "Nombre: ";
        getline(cin, nuevo->nombre);

        if(nuevo->nombre.empty())
        {
            cout << "\nEl nombre no puede estar vacio.\n";
        }

    }while(nuevo->nombre.empty());

    nuevo->precio = leerPrecio();
    nuevo->stock = leerStock();

    nuevo->siguiente = NULL;

    if(inicio == NULL)
    {
        inicio = nuevo;
    }
    else
    {
        Producto *aux = inicio;

        while(aux->siguiente != NULL)
        {
            aux = aux->siguiente;
        }

        aux->siguiente = nuevo;
    }

    pushAccion("Se agrego producto: " + nuevo->codigo);

    guardarProductos();

    cout << "\nProducto registrado correctamente.\n";
}

/*=================================
      BUSCAR PRODUCTO
=================================*/

void buscarProducto()
{
    if(inicio == NULL)
    {
        cout << "\nInventario vacio.\n";
        return;
    }

    string codigo;

    cout << "\nIngrese codigo a buscar: ";
    cin >> codigo;

    Producto *aux = inicio;

    while(aux != NULL)
    {
        if(aux->codigo == codigo)
        {
            cout << "\n===== PRODUCTO ENCONTRADO =====\n";

            cout << "Codigo : "
                 << aux->codigo << endl;

            cout << "Nombre : "
                 << aux->nombre << endl;

            cout << "Precio : "
                 << aux->precio << endl;

            cout << "Stock  : "
                 << aux->stock << endl;

            return;
        }

        aux = aux->siguiente;
    }

    cout << "\nProducto no encontrado.\n";
}

/*=================================
      MOSTRAR INVENTARIO
=================================*/

void mostrarInventario()
{
    if(inicio == NULL)
    {
        cout << "\nNo existen productos registrados.\n";
        return;
    }

    Producto *aux = inicio;

    cout << "\n===== INVENTARIO =====\n";

    while(aux != NULL)
    {
        cout << "\nCodigo : "
             << aux->codigo << endl;

        cout << "Nombre : "
             << aux->nombre << endl;

        cout << "Precio : "
             << aux->precio << endl;

        cout << "Stock  : "
             << aux->stock << endl;

        cout << "--------------------------\n";

        aux = aux->siguiente;
    }
}

/*=================================
      MODIFICAR STOCK
=================================*/

void modificarStock()
{
    if(inicio == NULL)
    {
        cout << "\nInventario vacio.\n";
        return;
    }

    string codigo;

    cout << "\nCodigo del producto: ";
    cin >> codigo;

    Producto *aux = inicio;

    while(aux != NULL)
    {
        if(aux->codigo == codigo)
        {
            cout << "\nStock actual: "
                 << aux->stock << endl;

            aux->stock = leerStock();

            guardarProductos();

            pushAccion("Modifico stock de: " + codigo);

            cout << "\nStock actualizado correctamente.\n";

            return;
        }

        aux = aux->siguiente;
    }

    cout << "\nProducto no encontrado.\n";
}

/*=================================
      ELIMINAR PRODUCTO
=================================*/

void eliminarProducto()
{
    if(inicio == NULL)
    {
        cout << "\nInventario vacio.\n";
        return;
    }

    string codigo;

    cout << "\nCodigo a eliminar: ";
    cin >> codigo;

    Producto *actual = inicio;
    Producto *anterior = NULL;

    while(actual != NULL)
    {
        if(actual->codigo == codigo)
        {
            if(anterior == NULL)
            {
                inicio = actual->siguiente;
            }
            else
            {
                anterior->siguiente =
                actual->siguiente;
            }

            pushAccion("Elimino producto: " + codigo);

            delete actual;

            guardarProductos();

            cout << "\nProducto eliminado correctamente.\n";

            return;
        }

        anterior = actual;
        actual = actual->siguiente;
    }

    cout << "\nProducto no encontrado.\n";
}
/*=================================
      COLA DE PEDIDOS
=================================*/

bool colaVacia()
{
    return (frente == NULL);
}

void encolarPedido()
{
    if(inicio == NULL)
    {
        cout << "\nNo existen productos registrados.\n";
        return;
    }

    Pedido *nuevo = new Pedido();

    cout << "\n===== REGISTRAR PEDIDO =====\n";

    cin.ignore();

    do
    {
        cout << "Cliente: ";
        getline(cin, nuevo->cliente);

        if(nuevo->cliente.empty())
        {
            cout << "\nEl nombre del cliente no puede estar vacio.\n";
        }

    }while(nuevo->cliente.empty());

    cout << "Codigo producto: ";
    cin >> nuevo->codigoProducto;

    bool encontrado = false;

    Producto *aux = inicio;

    while(aux != NULL)
    {
        if(aux->codigo == nuevo->codigoProducto)
        {
            encontrado = true;
            break;
        }

        aux = aux->siguiente;
    }

    if(!encontrado)
    {
        cout << "\nProducto no existe.\n";
        delete nuevo;
        return;
    }

    nuevo->cantidad = leerCantidad();

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

    pushAccion("Registro pedido de " + nuevo->cliente);

    cout << "\nPedido registrado correctamente.\n";
}
/*=================================
   REGISTRAR PEDIDO PENDIENTE
=================================*/

void registrarPedidoPendiente(
        string cliente,
        string codigo,
        int cantidad)
{
    Pedido *nuevo = new Pedido();

    nuevo->cliente = cliente;
    nuevo->codigoProducto = codigo;
    nuevo->cantidad = cantidad;

    nuevo->siguiente = NULL;

    if(frentePendiente == NULL)
    {
        frentePendiente = nuevo;
        finalPendiente = nuevo;
    }
    else
    {
        finalPendiente->siguiente = nuevo;
        finalPendiente = nuevo;
    }

    pushAccion("Pedido enviado a pendientes");

    cout << "\nPedido enviado a cola de pendientes.\n";
}
/*=================================
      DESENCOLAR PEDIDO
=================================*/

void desencolarPedido()
{
    if(colaVacia())
    {
        cout << "\nNo existen pedidos.\n";
        return;
    }

    Pedido *pedidoActual = frente;

    Producto *producto = inicio;

    while(producto != NULL)
    {
        if(producto->codigo ==
           pedidoActual->codigoProducto)
        {
            break;
        }

        producto = producto->siguiente;
    }

    if(producto == NULL)
    {
        cout << "\nProducto no encontrado.\n";
    }
    else
    {
        if(producto->stock >= pedidoActual->cantidad)
        {
            producto->stock -= pedidoActual->cantidad;

            guardarProductos();

            cout << "\nPedido atendido correctamente.\n";

            cout << "Cliente : "
                 << pedidoActual->cliente << endl;

            cout << "Producto: "
                 << producto->nombre << endl;

            cout << "Cantidad: "
                 << pedidoActual->cantidad << endl;

            pushAccion("Pedido atendido");
        }
        else
        {
            registrarPedidoPendiente(
                pedidoActual->cliente,
                pedidoActual->codigoProducto,
                pedidoActual->cantidad
            );
        }
    }

    frente = frente->siguiente;

    if(frente == NULL)
    {
        final = NULL;
    }

    delete pedidoActual;
}
/*=================================
      MOSTRAR PEDIDOS
=================================*/

void mostrarPedidos()
{
    if(colaVacia())
    {
        cout << "\nNo existen pedidos.\n";
        return;
    }

    Pedido *aux = frente;

    cout << "\n===== PEDIDOS =====\n";

    while(aux != NULL)
    {
        cout << "\nCliente : "
             << aux->cliente << endl;

        cout << "Producto: "
             << aux->codigoProducto << endl;

        cout << "Cantidad: "
             << aux->cantidad << endl;

        cout << "---------------------\n";

        aux = aux->siguiente;
    }
}
/*=================================
 MOSTRAR PEDIDOS PENDIENTES
=================================*/

void mostrarPedidosPendientes()
{
    if(frentePendiente == NULL)
    {
        cout << "\nNo existen pedidos pendientes.\n";
        return;
    }

    Pedido *aux = frentePendiente;

    cout << "\n===== PEDIDOS PENDIENTES =====\n";

    while(aux != NULL)
    {
        cout << "\nCliente : "
             << aux->cliente << endl;

        cout << "Producto: "
             << aux->codigoProducto << endl;

        cout << "Cantidad: "
             << aux->cantidad << endl;

        cout << "---------------------\n";

        aux = aux->siguiente;
    }
}
/*=================================
   REINTENTAR PEDIDOS PENDIENTES
=================================*/

void reintentarPedido()
{
    if(frentePendiente == NULL)
    {
        cout << "\nNo existen pedidos pendientes.\n";
        return;
    }

    Pedido *pedido = frentePendiente;

    Producto *producto = inicio;

    while(producto != NULL)
    {
        if(producto->codigo ==
           pedido->codigoProducto)
        {
            break;
        }

        producto = producto->siguiente;
    }

    if(producto != NULL)
    {
        if(producto->stock >= pedido->cantidad)
        {
            producto->stock -= pedido->cantidad;

            guardarProductos();

            cout << "\nPedido pendiente completado.\n";

            pushAccion(
                "Pedido pendiente atendido"
            );

            frentePendiente =
            frentePendiente->siguiente;

            if(frentePendiente == NULL)
            {
                finalPendiente = NULL;
            }

            delete pedido;

            return;
        }
    }

    cout << "\nAun no existe stock suficiente.\n";

}
/*=================================
   MENUS FUNCIONES
=================================*/
int leerOpcion()
{
    int opcion;

    while(true)
    {
        cin >> opcion;

        if(cin.fail())
        {
            cout << "\nERROR. Ingrese un numero valido: ";

            cin.clear();
            cin.ignore(1000, '\n');
        }
        else
        {
            return opcion;
        }
    }
}
void menuInventario()
{
    int op;

    do
    {
        cout<<"\n===== GESTION DE INVENTARIO =====";
        cout<<"\n1. Registrar producto";
        cout<<"\n2. Eliminar producto";
        cout<<"\n3. Buscar producto";
        cout<<"\n4. Modificar stock";
        cout<<"\n5. Mostrar inventario";
        cout<<"\n6. Volver";

        cout<<"\nOpcion: ";
        op = leerOpcion();

        switch(op)
        {
            case 1: insertarProducto(); break;
            case 2: eliminarProducto(); break;
            case 3: buscarProducto(); break;
            case 4: modificarStock(); break;
            case 5: mostrarInventario(); break;
            case 6: break;
            default:
                cout<<"\nOpcion invalida";
        }

    }while(op != 6);
}
void menuPedidos()
{
    int op;

    do
    {
        cout<<"\n===== GESTION DE PEDIDOS =====";
        cout<<"\n1. Registrar pedido";
        cout<<"\n2. Atender pedido";
        cout<<"\n3. Mostrar pedidos";
        cout<<"\n4. Mostrar pedidos pendientes";
        cout<<"\n5. Reintentar pedido pendiente";
        cout<<"\n6. Volver";

        cout<<"\nOpcion: ";
        op = leerOpcion();

        switch(op)
        {
            case 1: encolarPedido(); break;
            case 2: desencolarPedido(); break;
            case 3: mostrarPedidos(); break;
            case 4: mostrarPedidosPendientes(); break;
            case 5: reintentarPedido(); break;
            case 6: break;
            default:
                cout<<"\nOpcion invalida";
        }

    }while(op != 6);
}

void menuHistorial()
{
    int op;

    do
    {
        cout<<"\n===== HISTORIAL =====";
        cout<<"\n1. Ver ultima accion";
        cout<<"\n2. Deshacer accion";
        cout<<"\n3. Volver";

        cout<<"\nOpcion: ";
        op = leerOpcion();

        switch(op)
        {
            case 1:
                consultarUltimaAccion();
                break;

            case 2:
                popAccion();
                break;

            case 3:
                break;

            default:
                cout<<"\nOpcion invalida";
        }

    }while(op != 3);
}
/*=================================
   MENU PRINCIPAL
=================================*/

int main()
{
    int op;

    do
    {
        cout<<"\n================================";
        cout<<"\n SISTEMA LA CANASTA";
        cout<<"\n================================";

        cout<<"\n1. Gestionar Inventario";
        cout<<"\n2. Gestionar Pedidos";
        cout<<"\n3. Historial de Acciones";
        cout<<"\n4. Salir";

        cout<<"\nOpcion: ";
        op = leerOpcion();

        switch(op)
        {
            case 1:
                menuInventario();
                break;

            case 2:
                menuPedidos();
                break;

            case 3:
                menuHistorial();
                break;

            case 4:
                guardarProductos();
                cout<<"\nDatos guardados.";
                break;

            default:
                cout<<"\nOpcion invalida";
        }

    }while(op != 4);
}

