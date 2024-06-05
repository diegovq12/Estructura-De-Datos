#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo {
    char caracter;
    struct Nodo *siguiente;
} Nodo;

void push(Nodo **pila, char caracter);
void pop(Nodo **pila, char *caracter);

int main() {
    Nodo *pila = NULL;
    char palabra[100];
    
    printf("Ingrese una palabra: ");
    gets(palabra);
    palabra[strcspn(palabra,"\n")] = '\0';


    for (int i = 0; palabra[i] != '\0'; i++) {
        push(&pila, palabra[i]);
    }
    
    char letra;
    printf("Palabra invertida: ");
    while (pila != NULL) {
        pop(&pila, &letra);
        printf("%c", letra);
    }
    printf("\n");

    return 0;
}

void push(Nodo **pila, char caracter) {
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) {
        printf("Error al asignar memoria\n");
        return;
    }

    nuevoNodo->caracter = caracter;
    nuevoNodo->siguiente = *pila;
    *pila = nuevoNodo;
}

void pop(Nodo **pila, char *caracter) {
    if (*pila == NULL) {
        printf("Pila vacía\n");
        return;
    }
    Nodo *aux = *pila;
    *caracter = aux->caracter;
    *pila = aux->siguiente;
    free(aux);
}
