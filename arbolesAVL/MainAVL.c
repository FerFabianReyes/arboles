#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "prototipos.h"

int main (int argc, char *argv[])
{
    enum MenuOptions { 
    ADD = 1, REMOVE, PRINT, PREORDER, INORDER, POSTORDER, SEARCH, HEIGHT, EXIT
    };

    int opt, valor;
    NodoAVL *arbol = NULL, *tempNodo;
    bool is_int(char *str);

    if (argc > 1) {
        NodoAVL *tmp_nodo = nodoNuevo(0);
        int32_t number, i;
        for (i = 1; i < argc; i += 1) {
            if (is_int(argv[i]) != true) {
                printf("El argumento %s no es un número.\n", argv[i]);
                continue;
            }

            number = atoi(argv[i]);
            tmp_nodo->valor = number;
            insertarNodo(&arbol, tmp_nodo);
        }
       // nodeDelete(&tmp_node);
    }

    do {
        opt =menu();

        switch (opt) {
        case ADD:
            printf("Ingrese el valor del nodo a insertar: ");
            scanf("%d", &valor);
            insertarNodo(&arbol, nodoNuevo(valor));
            break;

        case REMOVE:
            printf("¿Qué nodo desea eliminar?: ");
            scanf("%d", &valor);
            tempNodo = extraerNodo(&arbol, valor);
            
            if (tempNodo == NULL) {
                printf("El nodo con valor %d no existe.\n", valor);
            }
            else {
                borrarNodo(&tempNodo);
                printf("Nodo con valor %d eliminado.\n", valor);
            }
            break;

        case PRINT:
           imprimirArbol(arbol);
            break;

        case PREORDER:
            printf("Recorrido en preorden: ");
            preorden(arbol);
            break;

        case INORDER:
            printf("Recorrido en enorden: ");
            enorden(arbol);
            break;              

        case POSTORDER:
            printf("Recorrido en postorden: ");
            postorden(arbol);
            break;

        case SEARCH:
            printf("¿Qué valor desea buscar?: ");
            scanf("%d", &valor);
            tempNodo = buscarNodo(arbol, valor);
            printf("El nodo con valor %d: %s.\n",valor,
                    (tempNodo != NULL)? "existe": "no existe");
            break; 

        case HEIGHT:
            printf("La altura del árbol es %d", alturaDeNodo(arbol));
            break;

        case EXIT:
            exit(0);
            break;    
        }

        printf("Presione Enter para continuar...");
        while (getchar() != '\n');
        while (getchar() != '\n');

    } while (opt != EXIT);

    return 0;
}