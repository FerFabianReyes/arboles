#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "prototipos.h"

NodoBB *mayorDeLosMenores(NodoBB *nodo);
void reemplazar(NodoBB **nodo);

NodoBB *nuevoNodo(int valor)
{
    NodoBB *nuevo_nodo = malloc(sizeof(*nuevo_nodo));
    if (nuevo_nodo != NULL) {
        nuevo_nodo->valor = valor;
        nuevo_nodo->derecha = NULL;
        nuevo_nodo->izquierda = NULL;
    }

    return nuevo_nodo;
}

void insertarNodo(NodoBB **arbol, NodoBB *nodo)
{
    if (*arbol == NULL) {
        *arbol = nodo;
    }
    else if (nodo->valor < (*arbol)->valor) {
        insertarNodo(&(*arbol)->izquierda, nodo);
    }
    else {
        insertarNodo(&(*arbol)->derecha, nodo);
    }
}

void borrarNodo(NodoBB **nodo)
{
    free(*nodo);
    *nodo = NULL;
}

void imprimirArbol(NodoBB *arbol)
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
void imprimirArbolRecursivo(NodoBB *arbol, uint8_t nivel, bool cierraNivel)
{
    static uint32_t bitsNivelesActivos = 0; /* Solo usar manipulaciones de bit a bit */
    if (arbol) {
        if (cierraNivel) {
            /* Operador implicación negada o "a and ~b". */
            bitsNivelesActivos = bitsNivelesActivos & ~(1 << (nivel - 1));
        } else {
            bitsNivelesActivos = bitsNivelesActivos | (1 << (nivel - 1));
        }

        indentacion(nivel, bitsNivelesActivos);
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

void indentacion(uint8_t nivel, uint32_t bitsNivelesActivos)
{
    bool nivelActivo;
    for (uint8_t nivelActual = 0; nivelActual < nivel - 1; nivelActual += 1) {
        nivelActivo = bitsNivelesActivos & (1 << nivelActual);
        printf((nivelActivo)? "│   ": "    ");
    }
}

void imprimirNotacion(NodoBB *raiz)
{
    printf ("%d", raiz->valor);
    if (((raiz->derecha) != NULL ) && ((raiz->izquierda) != NULL)){
        printf ("(");
        imprimirNotacion(raiz->izquierda);
        printf (",");
        imprimirNotacion(raiz->derecha);
        printf (")");
    } else if (((raiz->derecha) == NULL ) && ((raiz->izquierda) == NULL)){
        return;
    } else if ((raiz->derecha) == NULL){
        printf ("(");
        imprimirNotacion(raiz->izquierda);
        printf (")");
    } else if ((raiz->izquierda) == NULL){
        printf ("(");
        imprimirNotacion(raiz->derecha);
        printf (")");
    }
}

void visitarNodo(NodoBB *nodo){
    printf("%d ", nodo->valor);
}

void postorden(NodoBB *raiz)
{
    if (raiz == NULL)
        return;

    postorden(raiz->izquierda);
    postorden(raiz->derecha);
    visitarNodo(raiz);
}


void preorden(NodoBB *raiz)
{
    if (raiz) {
        visitarNodo(raiz);
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

void enorden(NodoBB *arbol)
{
    if (arbol != NULL) {
        enorden(arbol->izquierda);
        visitarNodo(arbol);
        enorden(arbol->derecha);
    } 
}

int alturaNodo(NodoBB *nodo)
{
    if (nodo != NULL) {
        int izquierda, derecha;
        izquierda = alturaNodo(nodo->izquierda);
        derecha = alturaNodo(nodo->derecha);
        if (izquierda > derecha) {
            return izquierda + 1;
        }
        return derecha + 1;    
    } else {
        return 0;
    }
}


NodoBB *extraerNodoArbol(NodoBB **arbol, int valor)
{
    NodoBB *nodoEncontrado = NULL;
    if (*arbol) {
        if (valor > (*arbol)->valor)
        {
            nodoEncontrado = extraerNodoArbol(&(*arbol)->derecha, valor);
        } else if (valor < (*arbol)->valor)
        {
            nodoEncontrado = extraerNodoArbol(&(*arbol)->izquierda, valor);
        } else
        {
            nodoEncontrado = *arbol;
            if (nodoEncontrado->izquierda == NULL)
            {
                (*arbol) = nodoEncontrado->derecha;
            } else if (nodoEncontrado->derecha == NULL)
            {
                (*arbol) = nodoEncontrado->izquierda;
            } else
            {
                reemplazar(&nodoEncontrado);
            }
        } 
    }
    return nodoEncontrado;
}

void reemplazar(NodoBB **actual) //Mayor de los menores
{
    NodoBB *nuevoActual, *actualTemporal;
    actualTemporal = *actual;
    nuevoActual = (*actual)->izquierda;

    while (nuevoActual->derecha)
    {
        actualTemporal = nuevoActual;
        nuevoActual = nuevoActual->derecha;
    }

    (*actual)->valor = nuevoActual->valor;
    if (actualTemporal == (*actual))
    {
        actualTemporal->izquierda = nuevoActual->izquierda;
    } else
    {
        actualTemporal->derecha = nuevoActual->izquierda;

    }
    
    (*actual) = nuevoActual;
    
}


NodoBB *mayorDeLosMenores(NodoBB *nodo)
{
    NodoBB *mayor = nodo;
    if (nodo->derecha)
    {
        mayor = mayorDeLosMenores(nodo->derecha);
    }
    return mayor;
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

bool is_int(char *str)
{
    for (uint32_t i = 0; str[i] != '\0'; i += 1) {
        if (isdigit(str[i]) == false && str[i] != '-') {
            return false;
        }
    }
    return true;
}

