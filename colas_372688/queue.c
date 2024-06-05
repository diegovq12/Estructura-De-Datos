#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estructura de un nodo de la cola
typedef struct Nodo
{
    int dato;
    struct Nodo *siguiente;
} Nodo;

// Estructura de la cola
typedef struct Cola
{
    Nodo *frente;
    Nodo *final;
} Cola;

void inicializarCola(Cola *cola);
int getSize(Cola *cola);
bool isEmpty(Cola *cola);
void clear(Cola *cola);
void enqueue(Cola *cola, int dato);
void dequeue(Cola *cola);
int front(Cola *cola);

void mostrarMenu();

int main()
{
    Cola cola;
    inicializarCola(&cola);
    int opcion, dato;

    do
    {
        mostrarMenu();
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Ingrese el elemento a insertar: ");
            scanf("%d", &dato);
            enqueue(&cola, dato);
            break;
        case 2:
            dequeue(&cola);
            break;
        case 3:
            if (!isEmpty(&cola))
            {
                printf("Elemento al frente de la cola: %d\n", front(&cola));
            }
            else
            {
                printf("La cola esta vacia.\n");
            }
            break;
        case 4:
            if (isEmpty(&cola))
                printf("La cola esta vacia.\n");
            else
                printf("La cola no esta vacia.\n");
            break;
        case 5:
            printf("Tamano de la cola: %d\n",getSize(&cola));
            break;
        case 6:
            clear(&cola);
            printf("La cola ha sido vaciada.\n");
        case 7:
            printf("Cerrando programa...\n");
            break;
        default:
            printf("Opcion invalida...");
            break;
        }
        system("PAUSE");
    } while (opcion != 7);
}

// Insertar elementos al final de la cola (enqueue).
void enqueue(Cola *cola, int dato)
{
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL)
    {
        printf("Error al crear el nuevo nodo\n");
        return;
    }
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;
    if (isEmpty(cola))
    {
        cola->frente = nuevoNodo;
    }
else
    {
        cola->final->siguiente = nuevoNodo;
    }
    cola->final = nuevoNodo;
    printf("Elemento %d insertado en la cola\n", dato);
}

// Eliminar elementos del frente de la cola (dequeue).
void dequeue(Cola *cola)
{
    if (isEmpty(cola))
    {
        printf("La cola está vacía. No se puede eliminar.\n");
        return;
    }
    Nodo *aux = cola->frente;
    cola->frente = cola->frente->siguiente;
    printf("Elemento %d eliminado de la cola.\n", aux->dato);
    free(aux);
    if (cola->frente == NULL)
    {
        cola->final = NULL;
    }
}
// Obtener el elemento en el frente de la cola sin eliminarlo (front).
int front(Cola *cola)
{
    if (isEmpty(cola))
    {
        printf("La cola esta vacia");
        return -1;
    }
    return cola->frente->dato;
}

void inicializarCola(Cola *cola)
{
    cola->frente = NULL;
    cola->final = NULL;
}
int getSize(Cola *cola)
{
    int contador = 0;
    Nodo *actual = cola->frente;
    while (actual != NULL)
    {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

bool isEmpty(Cola *cola)
{
    return (cola->frente == NULL);
}

void clear(Cola *cola)
{
    while (!isEmpty(cola))
    {
        dequeue(cola);
    }
}

void mostrarMenu()
{
    printf("\n--- Menu de Opciones ---\n");
    printf("1. Insertar elemento al final de la cola (enqueue)\n");
    printf("2. Eliminar elemento del frente de la cola (dequeue)\n");
    printf("3. Obtener el elemento en el frente de la cola sin eliminarlo (front)\n");
    printf("4. Verificar si la cola esta vacia (isEmpty)\n");
    printf("5. Obtener el tamano de la cola (size)\n");
    printf("6. Vaciar la cola (clear)\n");
    printf("7. Salir\n");
    printf("------------------------\n");
}