#ifndef prototipos
#define prototipos

typedef struct NodoAVL NodoAVL;
struct NodoAVL {
	int valor;
    int fe;
    int altura;
	NodoAVL *derecha;
    NodoAVL *izquierda;
};

NodoAVL *insertarNodo(NodoAVL **arbol, NodoAVL *nodo);
NodoAVL *nodoNuevo(int valor);

void    borrarNodo(NodoAVL **nodo);
NodoAVL *extraerNodo(NodoAVL **nodo, int valor);

void    imprimirArbol(NodoAVL *arbol);
void 	indentation(uint8_t nivel, uint32_t activeLevelsBits);
void 	imprimirArbolRecursivo(NodoAVL *arbol, uint8_t nivel, bool closesLevel);

void    setNotation(NodoAVL *arbol);

void    visitarNodo(NodoAVL *nodo);
void    enorden (NodoAVL *arbol);
void    postorden(NodoAVL *arbol);
void    preorden(NodoAVL *arbol);

NodoAVL  *buscarNodo(NodoAVL *arbol, int valor);
int     alturaDeNodo(NodoAVL *arbol); 

NodoAVL* rotacionIzquierda(NodoAVL **nodo);
NodoAVL* rotationDerecha(NodoAVL **nodo);
int fe(NodoAVL *nodo);
int     menu();
bool is_int(char *str);
#endif




