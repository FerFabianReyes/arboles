#include <stdio.h>
#include <stdlib.h>

#include "prototipos.h"

enum Opciones { 
    ANADIR = 1, REMOVER, IMPRIMIR, PREORDEN, ENORDEN, POSTORDEN, BUSQUEDA,
    ALTURA, SALIR
};

int
main(int argc, char *argv[])
{
    int opcion, value;
    NodoBB *arbol = NULL, *nodoTemporal;
    if (argc) {
        int32_t numero, i;
        for (i = 1; i < argc; i += 1) {
            if ((sscanf(argv[i], "%d", &numero))) {
                insertarNodo(&arbol, nuevoNodo(numero));
            } else {
                printf("El argumento %s no es un número.\n", argv[i]);
            }
        }
    }

    do {
        system("clear");
        opcion = menu();
        switch (opcion) {
        case ANADIR:
            printf("Ingrese el valor del nodo a insertar: ");
            scanf("%d", &value);
            insertarNodo(&arbol, nuevoNodo(value));
            break;

        case REMOVER:
            printf("¿Qué nodo desea eliminar?: ");
            scanf("%d", &value);
            if ((nodoTemporal = extraerNodoArbol(&arbol, value))) {
                printf("Nodo con valor %d eliminado.\n", value);
                borrarNodo(&nodoTemporal);
            } else {
                printf("El nodo con valor %d no existe.\n", value);
            }
            break;

        case IMPRIMIR:
            imprimirArbol(arbol);
            break;

        case PREORDEN:
            printf("Recorrido en preorden: ");
            preorden(arbol);
            printf("\n");
            break;

        case ENORDEN:
            printf("Recorrido en enorden: ");
            enorden(arbol);
            printf("\n");
            break;              

        case POSTORDEN:
            printf("Recorrido en postorden: ");
            postorden(arbol);
            printf("\n");
            break;

        case BUSQUEDA:
            printf("¿Qué valor desea buscar?: ");
            scanf("%d", &value);
            printf("El nodo con valor %d: %s.\n", value,
                    (nodoTemporal)? "existe": "no existe");
            break; 

        case ALTURA:
            printf("La altura del árbol es %d.\n", alturaArbol(arbol));
            break;

        case SALIR:
            vaciarArbol(&arbol);
            exit(0);
            break;
        }

        printf("Presione Enter para continuar...");
        while (getchar() != '\n');
        while (getchar() != '\n');

    } while (opcion != SALIR);
    return 0;
}
