#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Nodo
{
    int dato;
    struct Nodo *izq;
    struct Nodo *der;
} Nodo;

Nodo *crearNodo(int dato);
Nodo *insertarNodo(Nodo *arbol, int dato);
Nodo *buscarNodo(Nodo *arbol, int dato);
Nodo *eliminarNodo(Nodo *arbol, int dato);
void mostrarInorden(Nodo *arbol);
void mostrarPostorden(Nodo *arbol);
void mostrarPreOrden(Nodo *arbol);
int contarNodos(Nodo *raiz);
int obtenerAltura(Nodo *raiz);
bool esCompleto(Nodo *raiz, int indice, int numeroNodos);
bool esBalanceado(Nodo *raiz);
void modificarNodo(Nodo *raiz, int valorViejo, int valorNuevo);
void mostrarMenu();

int main()
{
    Nodo *arbol = NULL;
    int opcion, dato, nuevoDato, indice = 0, numeroNodos;
    Nodo *resultado;

    do
    {
        mostrarMenu();
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Ingrese el valor del nodo a insertar: ");
            scanf("%d", &dato);
            arbol = insertarNodo(arbol, dato);
            break;
        case 2:
            printf("Ingrese el valor del nodo a buscar: ");
            scanf("%d", &dato);
            resultado = buscarNodo(arbol, dato);
            if (resultado != NULL)
                printf("Nodo con valor %d encontrado.\n", resultado->dato);
            else
                printf("Nodo no encontrado.\n");
            break;
        case 3:
            printf("Ingrese el valor del nodo a eliminar: ");
            scanf("%d", &dato);
            arbol = eliminarNodo(arbol, dato);
            break;
        case 4:
            printf("Recorrido en orden: ");
            mostrarInorden(arbol);
            printf("\n");
            break;
        case 5:
            printf("Recorrido en preorden: ");
            mostrarPreOrden(arbol);
            printf("\n");
            break;
        case 6:
            printf("Recorrido en postorden: ");
            mostrarPostorden(arbol);
            printf("\n");
            break;
        case 7:
            printf("Numero de nodos: %d\n", contarNodos(arbol));
            break;
        case 8:
            printf("Altura del arbol: %d\n", obtenerAltura(arbol));
            break;
        case 9:
            numeroNodos = contarNodos(arbol);
            if (esCompleto(arbol, indice, numeroNodos))
                printf("El arbol es completo.\n");
            else
                printf("El arbol no es completo.\n");
            break;
        case 10:
            if (esBalanceado(arbol))
                printf("El arbol esta balanceado.\n");
            else
                printf("El arbol no esta balanceado.\n");
            break;
        case 11:
            printf("Ingrese el valor del nodo a modificar: ");
            scanf("%d", &dato);
            printf("Ingrese el nuevo valor para el nodo: ");
            scanf("%d", &nuevoDato);
            modificarNodo(arbol, dato, nuevoDato);
            break;
        case 12:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion invalida. Intente de nuevo.\n");
        }
        system("PAUSE");
    } while (opcion != 12);

    return 0;
}

Nodo *crearNodo(int dato)
{
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->izq = NULL;
    nuevoNodo->der = NULL;
    return nuevoNodo;
}

Nodo *insertarNodo(Nodo *arbol, int dato)
{
    if (arbol == NULL)
    {
        Nodo *nuevoNodo = crearNodo(dato);
        arbol = nuevoNodo;
    }
    else
    {
        int valorRaiz = arbol->dato;
        if (dato < valorRaiz)
        {
            arbol->izq = insertarNodo(arbol->izq, dato);
        }
        else
        {
            arbol->der = insertarNodo(arbol->der, dato);
        }
        return arbol;
    }
}

Nodo *buscarNodo(Nodo *arbol, int dato)
{
    if (arbol == NULL || arbol->dato == dato)
        return arbol;
    if (dato < arbol->dato)
        return buscarNodo(arbol->izq, dato);
    else
        return buscarNodo(arbol->der, dato);
}

Nodo *eliminarNodo(Nodo *arbol, int dato)
{
    if (arbol == NULL)
    {
        return arbol;
    }
    if (dato < arbol->dato)
    {
        arbol->izq = eliminarNodo(arbol->izq, dato);
    }
    else if (dato > arbol->dato)
    {
        arbol->der = eliminarNodo(arbol->der, dato);
    }
    else
    {
        if (arbol->izq == NULL)
        {
            Nodo *temp = arbol->der;
            free(arbol);
            return temp;
        }
        else if (arbol->der == NULL)
        {
            Nodo *temp = arbol->izq;
            free(arbol);
            return temp;
        }
        Nodo *temp = arbol->der;
        while (temp && temp->izq != NULL)
            temp = temp->izq;
        arbol->dato = temp->dato;
        arbol->der = eliminarNodo(arbol->der, temp->dato);
    }
    return arbol;
}

void mostrarInorden(Nodo *arbol)
{
    if (arbol == NULL)
    {
        return;
    }
    else
    {
        mostrarInorden(arbol->izq);
        printf("%d, ", arbol->dato);
        mostrarInorden(arbol->der);
    }
}

void mostrarPostorden(Nodo *arbol)
{
    if (arbol == NULL)
    {
        return;
    }
    else
    {
        mostrarPostorden(arbol->izq);
        mostrarPostorden(arbol->der);
        printf("%d, ", arbol->dato);
    }
}

void mostrarPreOrden(Nodo *arbol)
{
    if (arbol == NULL)
    {
        return;
    }
    else
    {
        printf("%d, ", arbol->dato);
        mostrarPreOrden(arbol->izq);
        mostrarPreOrden(arbol->der);
    }
}

int contarNodos(Nodo *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + contarNodos(raiz->izq) + contarNodos(raiz->der);
    }
}

int obtenerAltura(Nodo *raiz)
{
    if (raiz == NULL)
        return 0;
    else
    {
        int alturaIzquierda = obtenerAltura(raiz->izq);
        int alturaDerecha = obtenerAltura(raiz->der);
        return (alturaIzquierda > alturaDerecha ? alturaIzquierda : alturaDerecha) + 1;
    }
}

bool esCompleto(Nodo *raiz, int indice, int numeroNodos)
{
    if (raiz == NULL)
        return true;
    if (indice >= numeroNodos)
        return false;
    return esCompleto(raiz->izq, 2 * indice + 1, numeroNodos) &&
           esCompleto(raiz->der, 2 * indice + 2, numeroNodos);
}

bool esBalanceado(Nodo *raiz)
{
    if (raiz == NULL)
        return true;
    int alturaIzquierda = obtenerAltura(raiz->izq);
    int alturaDerecha = obtenerAltura(raiz->der);
    if (abs(alturaIzquierda - alturaDerecha) <= 1 && esBalanceado(raiz->izq) && esBalanceado(raiz->der))
        return true;
    return false;
}

void modificarNodo(Nodo *raiz, int valorViejo, int valorNuevo)
{
    Nodo *nodo = buscarNodo(raiz, valorViejo);
    if (nodo != NULL)
    {
        nodo->dato = valorNuevo;
        printf("Nodo con valor %d modificado a %d.\n", valorViejo, valorNuevo);
    }
    else
    {
        printf("Nodo con valor %d no encontrado.\n", valorViejo);
    }
}

void mostrarMenu()
{
    printf("\n--- Menu de Opciones ---\n");
    printf("1. Insertar nodo\n");
    printf("2. Buscar nodo\n");
    printf("3. Eliminar nodo\n");
    printf("4. Recorrido en orden\n");
    printf("5. Recorrido en preorden\n");
    printf("6. Recorrido en postorden\n");
    printf("7. Contar nodos\n");
    printf("8. Obtener altura\n");
    printf("9. Verificar si el arbol es completo\n");
    printf("10. Verificar si el arbol esta balanceado\n");
    printf("11. Modificar Nodo\n");
    printf("12. Salir\n");
    printf("------------------------\n");
}
