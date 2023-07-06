#ifndef prototipos
#define prototipos

#include <stdbool.h>
#include <stdint.h>

typedef struct NodoBB NodoBB;
struct NodoBB {
	int valor;
	NodoBB *derecha;
    NodoBB *izquierda;
};

NodoBB  *nuevoNodo(int valor);
void    borrarNodo(NodoBB **nodo);

void    insertarNodo(NodoBB **tree, NodoBB *nodo);
NodoBB  *extraerNodoArbol(NodoBB **nodo, int valor);
NodoBB  *buscarNodo(NodoBB *arbol, int valor);
int     alturaArbol(NodoBB *arbol); 

void 	imprimirArbol(NodoBB *arbol);
void    imprimirNotacion(NodoBB *arbol);
void    vaciarArbol(NodoBB **raiz);

void    enorden(NodoBB *arbol);
void    postorden(NodoBB *arbol);
void    preorden(NodoBB *arbol);

int     menu();

#endif
