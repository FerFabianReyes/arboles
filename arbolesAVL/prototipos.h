#ifndef prototipos
#define prototipos

#include <stdbool.h>
#include <stdint.h>

typedef struct NodoAVL NodoAVL;
struct NodoAVL {
	int valor;
    int factorEquilibrio;
	NodoAVL *derecha;
    NodoAVL *izquierda;
};

NodoAVL *nodoCrear(int valor);
void    borrarNodo(NodoAVL **nodo);

void    insertarNodo(NodoAVL **arbol, NodoAVL *nodo);
NodoAVL *extraerNodoArbol(NodoAVL **nodo, int valor);
NodoAVL *buscarNodo(NodoAVL *arbol, int valor);
int     alturaArbol(NodoAVL *arbol); 

void 	imprimirArbol(NodoAVL *arbol);
void    imprimirNotacion(NodoAVL *arbol);
void    vaciarArbol(NodoAVL **raiz);

void    enorden(NodoAVL *arbol);
void    postorden(NodoAVL *arbol);
void    preorden(NodoAVL *arbol);

int     menu();
NodoAVL* rotacionIzquierda(NodoAVL **nodo);
NodoAVL* rotationDerecha(NodoAVL **nodo);

#endif




