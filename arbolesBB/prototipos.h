#ifndef prototipos
#define prototipos

typedef struct NodoBB NodoBB;
struct NodoBB {
	int valor;
	NodoBB *derecha;
    NodoBB *izquierda;
};

NodoBB  *nuevoNodo(int valor);
void   insertarNodo(NodoBB **tree, NodoBB *nodo);

void    borrarNodo(NodoBB **nodo);
NodoBB *extraerNodoArbol(NodoBB **nodo, int valor);


void 	imprimirArbol(NodoBB *arbol);
void 	indentacion(uint8_t nivel, uint32_t bitsNivelesActivos);
void 	imprimirArbolRecursivo(NodoBB *arbol, uint8_t nivel, bool cierraNivel);
void    imprimirNotacion(NodoBB *arbol);

void    visitarNodo(NodoBB *nodo);
void    enorden(NodoBB *arbol);
void    postorden(NodoBB *arbol);
void    preorden(NodoBB *arbol);

NodoBB  *buscarNodo(NodoBB *arbol, int valor);
int     alturaNodo(NodoBB *arbol); 
int     menu();

bool es_entero(char *str);

#endif
