#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "prototipos.h"


int main (int argc, char *argv[])
{
    enum MenuOptions { 
    ADD = 1, REMOVE, PRINT, PREORDER, INORDER, POSTORDER, SEARCH, HEIGHT, EXIT
    };

    int opt, value;
    NodoBB *tree = NULL, *tempNode;
    bool is_int(char *str);

    if (argc > 1) {
        NodoBB *tmp_node = nuevoNodo(0);
        int32_t number, i;
        for (i = 1; i < argc; i += 1) {
            if (is_int(argv[i]) != true) {
                printf("El argumento %s no es un número.\n", argv[i]);
                continue;
            }

            number = atoi(argv[i]);
            tmp_node -> valor = number;
            insertarNodo(&tree, tmp_node);
        }
        borrarNodo(&tmp_node);
    }

    do {
        opt = menu();

        switch (opt) {
        case ADD:
            printf("Ingrese el valor del nodo a insertar: ");
            scanf("%d", &value);
            insertarNodo(&tree, nuevoNodo(value));
            break;

        case REMOVE:
            printf("¿Qué nodo desea eliminar?: ");
            scanf("%d", &value);
            tempNode = extraerNodoArbol(&tree, value);
            if (tempNode == NULL) {
                printf("El nodo con valor %d no existe.\n", value);
            }
            else {
                printf("Nodo con valor %d eliminado.\n", value);
                borrarNodo(&tempNode);
                
            }
            break;

        case PRINT:
            imprimirArbol(tree);
            break;

        case PREORDER:
            printf("Recorrido en preorden: ");
            preorden(tree);
            break;

        case INORDER:
            printf("Recorrido en enorden: ");
            enorden(tree);
            break;              

        case POSTORDER:
            printf("Recorrido en postorden: ");
            postorden(tree);
            break;

        case SEARCH:
            printf("¿Qué valor desea buscar?: ");
            scanf("%d", &value);
            


            printf("El nodo con valor %d: %s.\n",value,
                    (tempNode != NULL)? "existe": "no existe");
            break; 

        case HEIGHT:
            printf("La altura del árbol es %d", alturaNodo(tree));
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