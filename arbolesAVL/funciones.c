#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "prototipos.h"

NodoAVL *mayorDeLosMenores(NodoAVL *nodo);

void borrarNodo(NodoAVL **nodo)
{
	free(*nodo);
    *nodo = NULL;
}


NodoAVL *nodoNuevo(int valor)
{
    NodoAVL *nuevo_nodoAVL = malloc(sizeof(*nuevo_nodoAVL));
    if (nuevo_nodoAVL != NULL) {
        nuevo_nodoAVL->valor = valor;
        nuevo_nodoAVL->fe = 0;
        nuevo_nodoAVL->derecha = NULL;
        nuevo_nodoAVL->izquierda  = NULL;
    }

	return nuevo_nodoAVL;
}

NodoAVL *insertarNodo(NodoAVL **arbol, NodoAVL *nodo)
{
    NodoAVL *hijo = nodo;

    if (*arbol == NULL) { //--------------------------
        *arbol = nodo;
    }
    else if (nodo->valor < (*arbol)->valor) {

        (*arbol)->izquierda = insertarNodo(&(*arbol)->izquierda, hijo);

        if (fe((*arbol)) == -2)
        {
            if (hijo->valor  < (*arbol)->izquierda->valor){
                (*arbol) = rotacionIzquierda(&(*arbol));
            } else{
            (*arbol) -> izquierda = rotationDerecha(&(*arbol) -> izquierda);
            (*arbol) = rotacionIzquierda(&(*arbol));
            }
        }
    }    
    else{
       (*arbol)->derecha = insertarNodo(&(*arbol)->derecha, hijo);
        if (fe((*arbol)) >= 2)
        {
            if (hijo->valor  >= (*arbol)->derecha->valor)
            {
                (*arbol) = rotationDerecha(&(*arbol));
            } else{
                (*arbol)->derecha = rotacionIzquierda(&(*arbol)->derecha);
                (*arbol) = rotationDerecha(&(*arbol));
            }
            
        } 
    }

    (*arbol) -> altura = alturaDeNodo((*arbol));
    (*arbol) -> fe = fe((*arbol));
    return (*arbol);
}

void imprimirArbol(NodoAVL *arbol)
{
    if (arbol) {
        printf ("Notación de conjuntos: ");
        setNotation(arbol);
        printf ("\n");

        printf("%d\n", arbol->valor);
        if (arbol->izquierda && arbol->derecha) {
            imprimirArbolRecursivo(arbol->derecha, 1, false);
            
            (arbol->izquierda, 1, true);
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
imprimirArvolRecursivo(NodoAVL *arbol, uint8_t nivel, bool closesLevel)
{
    static uint32_t activeLevelsBits = 0; /* Solo usar manipulaciones de bit a bit */
    if (arbol) {
        if (closesLevel) {
            /* Operador implicación negada o "a and ~b". */
            activeLevelsBits = activeLevelsBits & ~(1 << (nivel - 1));
        } else {
            activeLevelsBits = activeLevelsBits | (1 << (nivel - 1));
        }

        indentation(nivel, activeLevelsBits);
        printf("%s %d\n", (closesLevel)? "└──": "├──", arbol->valor);

        if (arbol->izquierda && arbol->derecha) {
            imprimirArvolRecursivo(arbol->derecha, nivel + 1, false);
            imprimirArvolRecursivo(arbol->izquierda, nivel + 1, true);
        }
        else if (arbol->izquierda) {
            imprimirArvolRecursivo(arbol->izquierda, nivel + 1, true);
        }
        else if (arbol->derecha) {
            imprimirArvolRecursivo(arbol->derecha, nivel + 1, true);
        }
    }
}

void indentation(uint8_t nivel, uint32_t activeLevelsBits)
{
    bool levelIsActive;
    for (uint8_t currentLevel = 0; currentLevel < nivel - 1; currentLevel += 1) {
        levelIsActive = activeLevelsBits & (1 << currentLevel);
        printf((levelIsActive)? "│   ": "    ");
    }
}


void setNotation (NodoAVL *raiz){
    printf ("%d", raiz -> valor);
    if (((raiz -> derecha) != NULL ) && ((raiz -> izquierda) != NULL)){
        printf ("(");
        setNotation (raiz -> izquierda);
        printf (",");
        setNotation (raiz -> derecha);
        printf (")");
    } else if (((raiz -> derecha) == NULL ) && ((raiz -> izquierda) == NULL)){
        return;
    } else if ((raiz -> derecha) == NULL){
        printf ("(");
        setNotation (raiz -> izquierda);
        printf (")");
    } else if ((raiz -> izquerda) == NULL){
        printf ("(");
        setNotation (raiz -> derecha);
        printf (")");
    }
}

void visitarNodo(NodoAVL *nodo){
    printf("%d ", nodo->valor);
}

void postorden(NodoAVL *raiz)
{
    if (raiz == NULL)
        return;

    postorden(raiz->izquierda);
    postorden(raiz->derecha);
    visitarNodo(raiz);
}

void preorden (NodoAVL *raiz){
    if (raiz){
        visitarNodo (raiz);
        preorden (raiz -> izquierda);
        preorden (raiz -> derecha);
    }
}

void inorden (NodoAVL *arbol)
{
    if (arbol != NULL)
    {
        inorden(arbol->izquierda);
        visitarNodo(arbol);
        inorden(arbol->derecha);
    } 
}

int alturaDeNodo(NodoAVL* nodo)
{
    if(nodo != NULL){
        int izquerda, derecha;
        izquerda = alturaDeNodo(nodo -> izquierda);
        derecha = alturaDeNodo(nodo -> derecha);
        if (izquerda > derecha){
            return izquerda + 1;
        }
        return derecha + 1;    
    } else{
        return 0;
    }
}


NodoAVL* rotationDerecha(NodoAVL **nodo)
{
    NodoAVL* temp = (*nodo)-> derecha;

    (*nodo) -> derecha = temp -> izquierda;
    temp -> izquierda = (*nodo);

    (*nodo) -> altura = alturaDeNodo((*nodo));
    temp -> izquierda = alturaDeNodo(temp);

    (*nodo) -> fe = fe((*nodo));
    temp -> fe = fe(temp);
    return temp;
}

/* Rotación  derecha. */
NodoAVL* rotacionIzquierda(NodoAVL **nodo) 
{
    NodoAVL* temp = (*nodo) -> izquierda;
    
    (*nodo) -> izquierda = temp -> derecha;
    temp -> derecha = (*nodo);

    (*nodo) -> altura = alturaDeNodo((*nodo));
    temp -> altura = alturaDeNodo(temp);

    (*nodo) -> fe = fe((*nodo));
    temp -> fe = fe(temp);
    return temp;
    
}

int fe(NodeAVL *node)
{
    int izquierda = alturaDeNodo(nodo -> izquierda);
    int derecha = alturaDeNodo(nodo -> derecha);
    return derecha - izquierda;
}

NodeAVL  *buscarNodo(NodoAVL *arbol, int valor)
{
    NodoAVL *nodoEncontrado = NULL;
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

NodoAVL *extraerNodo(NodoAVL **arbol, int valor)
{
    NodoAVL *nodoEncontrado = NULL;
    if (*arbol) {
        if (valor > (*arbol)->valor)
        {
            nodoEncontrado = extraerNodo(&(*arbol)->derecha, valor);
            //-2
            if (fe((*arbol)) == -2)
        {
            if (nodoEncontrado->valor  > (*arbol)->izquierda->valor){
                (*arbol) = rotacionIzquierda(&(*arbol));
            } else{
            (*arbol) -> izquierda = rotationDerecha(&(*arbol) -> izquierda);
            (*arbol) = rotacionIzquierda(&(*arbol));
            }
        }


        } else if (valor < (*arbol)->valor)
        {
            nodoEncontrado = extraerNodo(&(*arbol)->izquierda, valor);
            //2
             if (fe((*arbol)) >= 2)
        {
            if (nodoEncontrado->valor  < (*arbol)->derecha->valor)
            {
                (*arbol) = rotationDerecha(&(*arbol));
            } else{
                (*arbol)->derecha = rotacionIzquierda(&(*arbol)->derecha);
                (*arbol) = rotationDerecha(&(*arbol));
            }
            
        } 


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
                NodoAVL *mayorDeLosMenores, *remplazoNodo;
                mayorDeLosMenores = mayorDeLosMenores(nodoEncontrado->izquierda);
                remplazoNodo = nodoNuevo(mayorDeLosMenores->valor);

                remplazoNodo->derecha = (*arbol)->derecha;
                bool golIsLeftChild = (*arbol)->izquierda == mayorDeLosMenores;
                if (golIsLeftChild) {
                    remplazoNodo->izquierda = mayorDeLosMenores->izquierda;
                } else {
                    remplazoNodo->izquierda = (*arbol)->izquierda;
                }
                treeExtractNode(&(nodoEncontrado->izquierda), mayorDeLosMenores->valor);
                nodeDelete(&(mayorDeLosMenores));

                (*arbol) = remplazoNodo;
            }
        } 
    }
    return nodoEncontrado;
}


NodoAVL *mayorDeLosMenores(NodoAVL *nodo)
{
    NodoAVL *mayor = nodo;
    if (nodo->derecha)
    {
        mayor = mayorDeLosMenores(nodo->derecha);
    }
    return mayor;
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

