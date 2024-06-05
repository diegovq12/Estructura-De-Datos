#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Nodo
{
    int clave;
    char valor[100];
    struct Nodo *siguiente;
} Nodo;

typedef struct
{
    int tamano;
    Nodo **tabla;
} TablaHash;

Nodo *crearNodo(int clave, char *valor);
TablaHash *crearTablaHash(int tamano);
int funcionHash(int clave, int tamano);
void insertar(TablaHash *ht, int clave, char *valor);
char *buscar(TablaHash *ht, int clave);
void eliminar(TablaHash *ht, int clave);
Nodo *crearNodo(int clave, char *valor);
TablaHash *crearTablaHash(int tamano);
int funcionHash(int clave, int tamano);
void insertar(TablaHash *ht, int clave, char *valor);
char *buscar(TablaHash *ht, int clave);
void eliminar(TablaHash *ht, int clave);
void actualizar(TablaHash *ht, int clave, char *nuevo_valor);
void mostrar(TablaHash *ht);

void mostrar_menu();

int main()
{
    TablaHash *TablaHash = crearTablaHash(10);
    int opcion, clave;
    char valor[100];

    do
    {
        mostrar_menu();
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Ingrese la clave del nuevo elemento: ");
            scanf("%d", &clave);
            printf("Ingrese el valor del nuevo elemento: ");
            scanf("%s", valor);
            insertar(TablaHash, clave, valor);
            break;
        case 2:
            printf("Ingrese la clave del elemento a buscar: ");
            scanf("%d", &clave);
            char *resultado = buscar(TablaHash, clave);
            if (resultado == NULL)
            {
                printf("Elemento no encontrado.\n");
            }
            else
            {
                printf("Valor encontrado: %s\n", resultado);
            }
            break;
        case 3:
            printf("Ingrese la clave del elemento a eliminar: ");
            scanf("%d", &clave);
            eliminar(TablaHash, clave);
            break;
        case 4:
            printf("Ingrese la clave del elemento a actualizar: ");
            scanf("%d", &clave);
            printf("Ingrese el nuevo valor: ");
            scanf("%s", valor);
            actualizar(TablaHash, clave, valor);
            break;
        case 5:
            mostrar(TablaHash);
            break;
        case 6:
            printf("Saliendo del programa...\n");
            return 0;
        default:
            printf("Opcion no valida. Por favor, seleccione una opcion valida.\n");
            break;
        }
    } while (opcion != 6);
}

Nodo *crearNodo(int clave, char *valor)
{
    Nodo *nuevo_nodo = (Nodo *)malloc(sizeof(Nodo));
    nuevo_nodo->clave = clave;
    strcpy(nuevo_nodo->valor, valor);
    nuevo_nodo->siguiente = NULL;
    return nuevo_nodo;
}

TablaHash *crearTablaHash(int tamano)
{
    TablaHash *ht = (TablaHash *)malloc(sizeof(TablaHash));

    ht->tamano = tamano;
    ht->tabla = (Nodo **)malloc(tamano * sizeof(Nodo *));
    for (int i = 0; i < tamano; i++)
    {
        ht->tabla[i] = NULL;
    }

    return ht;
}

int funcionHash(int clave, int tamano)
{
    return clave % tamano;
}

void insertar(TablaHash *ht, int clave, char *valor)
{
    int indice = funcionHash(clave, ht->tamano);
    Nodo *nuevo_nodo = crearNodo(clave, valor);
    nuevo_nodo->siguiente = ht->tabla[indice];
    ht->tabla[indice] = nuevo_nodo;
}

char *buscar(TablaHash *ht, int clave)
{
    int indice = funcionHash(clave, ht->tamano);
    Nodo *actual = ht->tabla[indice];
    while (actual != NULL)
    {
        if (actual->clave == clave)
        {
            return actual->valor;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

void eliminar(TablaHash *ht, int clave)
{
    int indice = funcionHash(clave, ht->tamano);
    Nodo *actual = ht->tabla[indice];
    Nodo *anterior = NULL;
    while (actual != NULL && actual->clave != clave)
    {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == NULL)
    {
        printf("El elemento con clave %d no existe en la tabla hash.\n", clave);
        return;
    }
    if (anterior == NULL)
    {
        ht->tabla[indice] = actual->siguiente;
    }
    else
    {
        anterior->siguiente = actual->siguiente;
    }
    free(actual);
    printf("Elemento con clave %d eliminado de la tabla hash.\n", clave);
}

void actualizar(TablaHash *ht, int clave, char *nuevo_valor)
{
    int indice = funcionHash(clave, ht->tamano);
    Nodo *actual = ht->tabla[indice];
    while (actual != NULL)
    {
        if (actual->clave == clave)
        {
            strcpy(actual->valor, nuevo_valor);
            printf("Elemento con clave %d actualizado.\n", clave);
            return;
        }
        actual = actual->siguiente;
    }
    printf("El elemento con clave %d no existe en la tabla hash.\n", clave);
}

void mostrar(TablaHash *ht)
{
    printf("Tabla Hash:\n");
    for (int i = 0; i < ht->tamano; i++)
    {
        Nodo *actual = ht->tabla[i];
        printf("[%d]: ", i);
        while (actual != NULL)
        {
            printf("(%d, %s) -> ", actual->clave, actual->valor);
            actual = actual->siguiente;
        }
        printf("NULL\n");
    }
}

void mostrar_menu()
{
    printf("Menu:\n");
    printf("1. Insertar elemento\n");
    printf("2. Buscar elemento\n");
    printf("3. Eliminar elemento\n");
    printf("4. Actualizar elemento\n");
    printf("5. Mostrar tabla hash\n");
    printf("6. Salir\n");
    printf("Ingrese la opcion deseada: ");
}