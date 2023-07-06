#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "prototipos.h"

NodoBB  *mayorDeLosMenores(NodoBB *nodo);
void    reemplazar(NodoBB **nodo);
void 	sangria(uint8_t nivel, uint32_t bitsNivelesActivos);
void    visitarNodo(NodoBB *nodo);
void 	imprimirArbolRecursivo(NodoBB *arbol, uint8_t nivel, bool cierraNivel);

NodoBB *
nuevoNodo(int valor)
{
    NodoBB *nuevo_nodo = calloc(1, sizeof(*nuevo_nodo));
    if (nuevo_nodo) {
        nuevo_nodo->valor = valor;
    }
    return nuevo_nodo;
}

void
borrarNodo(NodoBB **nodo)
{
    if (nodo && *nodo) {
        free(*nodo);
        *nodo = NULL;
    }
}

void
insertarNodo(NodoBB **arbol, NodoBB *nodo)
{
    if (arbol) {
        if (*arbol) {
            if (nodo->valor < (*arbol)->valor) {
                insertarNodo(&(*arbol)->izquierda, nodo);
            } else {
                insertarNodo(&(*arbol)->derecha, nodo);
            }
        } else {
            *arbol = nodo;
        }
    }
}

void
imprimirArbol(NodoBB *arbol)
{
    if (arbol) {
        printf("Notación de conjuntos: ");
        imprimirNotacion(arbol);
        printf("\n");

        printf("%d\n", arbol->valor);
        if (arbol->izquierda && arbol->derecha) {
            imprimirArbolRecursivo(arbol->derecha, 1, false);
            imprimirArbolRecursivo(arbol->izquierda, 1, true);
        }
        else if (arbol->izquierda) {
            imprimirArbolRecursivo(arbol->izquierda, 1, true);
        }
        else if (arbol->derecha) {
            imprimirArbolRecursivo(arbol->derecha, 1, true);
        }
    }
}

/* 
 * Imprime cada hijo de un nodo raíz dado, la impresión es realizada
 * recursivamente.
 * Los niveles activos de cada árbol son guardados en una variable estática
 * al interior de la función.
 */
void
imprimirArbolRecursivo(NodoBB *arbol, uint8_t nivel, bool cierraNivel)
{
    static uint32_t bitsNivelesActivos = 0; /* Solo usar manipulaciones de bit a bit */
    if (arbol) {
        if (cierraNivel) {
            /* Operador implicación negada o "a and ~b". */
            bitsNivelesActivos = bitsNivelesActivos & ~(1 << (nivel - 1));
        } else {
            bitsNivelesActivos = bitsNivelesActivos | (1 << (nivel - 1));
        }

        sangria(nivel, bitsNivelesActivos);
        printf("%s %d\n", (cierraNivel)? "└──": "├──", arbol->valor);

        if (arbol->izquierda && arbol->derecha) {
            imprimirArbolRecursivo(arbol->derecha, nivel + 1, false);
            imprimirArbolRecursivo(arbol->izquierda, nivel + 1, true);
        }
        else if (arbol->izquierda) {
            imprimirArbolRecursivo(arbol->izquierda, nivel + 1, true);
        }
        else if (arbol->derecha) {
            imprimirArbolRecursivo(arbol->derecha, nivel + 1, true);
        }
    }
}
/*
 * Imprime la sangría necesaria para cada nivel del árbol al momento de
 * imprimirse, imprime una linea en caso de que se sepa que se está dentro del
 * nivel que se está imprimiendo.
 */
void
sangria(uint8_t nivel, uint32_t bitsNivelesActivos)
{
    bool nivelActivo;
    for (uint8_t nivelActual = 0; nivelActual < nivel - 1; nivelActual += 1) {
        nivelActivo = bitsNivelesActivos & (1 << nivelActual);
        printf((nivelActivo)? "│   ": "    ");
    }
}

/*
 * Imprime la notación de conjuntos.
 */
void 
imprimirNotacion(NodoBB *arbol)
{
    if (arbol) {
        printf("%d", arbol->valor);
        if (arbol->derecha && arbol->izquierda){
            printf ("(");
            imprimirNotacion(arbol->izquierda);
            printf (",");
            imprimirNotacion(arbol->derecha);
            printf (")");
        }
        else if (arbol->derecha){
            printf ("(");
            imprimirNotacion(arbol->derecha);
            printf (")");
        }
        else if (arbol->izquierda) {
            printf ("(");
            imprimirNotacion(arbol->izquierda);
            printf (")");
        }
    }
}

void
visitarNodo(NodoBB *nodo){
    printf("%d ", nodo->valor);
}

void
postorden(NodoBB *raiz)
{
    if (raiz) {
        postorden(raiz->izquierda);
        postorden(raiz->derecha);
        visitarNodo(raiz);
    }
}

void
preorden(NodoBB *raiz)
{
    if (raiz) {
        visitarNodo(raiz);
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

void
enorden(NodoBB *raiz)
{
    if (raiz) {
        enorden(raiz->izquierda);
        visitarNodo(raiz);
        enorden(raiz->derecha);
    } 
}

/*
 * Regresa la altura del árbol/sub-árbol.
 */
int
alturaArbol(NodoBB *raiz)
{
    int altura = 0;
    if (raiz) {
        int izquierda, derecha;
        izquierda   = alturaArbol(raiz->izquierda);
        derecha     = alturaArbol(raiz->derecha);
        altura      = ((izquierda > derecha)? izquierda: derecha) + 1;
    }
    return altura;
}

/*
 * Limpia recursivamente los nodos del árbol/sub-árbol que se recibe como
 * como argumento.
 */
void
vaciarArbol(NodoBB **raiz) 
{
    if (raiz && *raiz) {
        if ((*raiz)->izquierda) {
            vaciarArbol(&(*raiz)->izquierda);
        }
        if ((*raiz)->derecha) {
            vaciarArbol(&(*raiz)->derecha);
        }
        /* Se borra desde los nodos hoja. */
        if (!(*raiz)->izquierda && !(*raiz)->derecha) {
            borrarNodo(raiz);
        }
    }
}

NodoBB *extraerNodoArbol(NodoBB **arbol, int valor)
{
    NodoBB *nodoEncontrado = NULL;
    if (arbol && *arbol) {
        if (valor > (*arbol)->valor) {
            nodoEncontrado = extraerNodoArbol(&(*arbol)->derecha, valor);
        }
        else if (valor < (*arbol)->valor) {
            nodoEncontrado = extraerNodoArbol(&(*arbol)->izquierda, valor);
        }
        else {
            nodoEncontrado = *arbol;
            if (nodoEncontrado->izquierda == NULL) {
                (*arbol) = nodoEncontrado->derecha;
            }
            else if (nodoEncontrado->derecha == NULL) {
                (*arbol) = nodoEncontrado->izquierda;
            }
            else {
                reemplazar(&nodoEncontrado);
            }
        } 
    }
    return nodoEncontrado;
}

/* 
 * Reemplaza iterativamente el nodo raiz recibido por el mayor de los menores
 * asociados con dicho árbol/sub-árbol.
 */
void
reemplazar(NodoBB **raiz)
{
    NodoBB *nodoActual, *nodoAnterior;
    nodoAnterior = *raiz;
    nodoActual = (*raiz)->izquierda;
    while (nodoActual->derecha) {
        nodoAnterior = nodoActual;
        nodoActual = nodoActual->derecha;
    }
    (*raiz)->valor = nodoActual->valor;
    if (nodoAnterior == (*raiz)) {
        nodoAnterior->izquierda = nodoActual->izquierda;
    } else {
        nodoAnterior->derecha = nodoActual->izquierda;
    }
    (*raiz) = nodoActual;
}


NodoBB *
mayorDeLosMenores(NodoBB *nodo)
{
    if (nodo) {
        return (nodo->derecha)? mayorDeLosMenores(nodo->derecha): nodo;
    }
    return NULL; /* Nunca se debería de recibir un nodo nulo. */
}

NodoBB *buscarNodo(NodoBB *arbol, int valor)
{
    NodoBB *nodoEncontrado = NULL;
    if (arbol) {
        if (arbol->valor > valor) {
            nodoEncontrado = buscarNodo(arbol->izquierda, valor);
        }
        else if (arbol->valor < valor) {
            nodoEncontrado = buscarNodo(arbol->derecha, valor);
        }
        else {
            nodoEncontrado = arbol;
        }
    }
    return nodoEncontrado;
}

int menu()
{
    int opt;
    printf("═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬\n"
            "x x ⁞ Menú. x x\n"
            "═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬\n"
            "▒┊1.- Agregar. (Crear + Insertar)\n"
            "▒┊2.- Quitar. (Extraer + Eliminar)\n"
            "▒┊3.- Imprimir.\n"
            "▒┊4.- Preorden.\n"
            "▒┊5.- Enorden\n"
            "▒┊6.- Postorden.\n"
            "▒┊7.- Buscar.\n"
            "▒┊8.- Altura.\n"
            "▒┊9.- Salir.\n"
            "═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬═▬\n"
            "➫ ");
    scanf("%d", &opt);
    return opt;
}
