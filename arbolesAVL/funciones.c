#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#include "prototipos.h"

NodoAVL *mayorDeLosMenores(NodoAVL *nodo);
void    reemplazar(NodoAVL **nodo);
int     factorEquilibrio(NodoAVL *nodo);
void    imprimirNotacion (NodoAVL *raiz);
void    sangria(uint8_t nivel, uint32_t activeLevelsBits);
void    imprimirArbolRecursivo(NodoAVL *arbol, uint8_t nivel, bool closesLevel);

NodoAVL *
nodoCrear(int valor)
{
    NodoAVL *nuevoNodo = calloc(1, sizeof(*nuevoNodo));
    if (nuevoNodo) {
        nuevoNodo->valor = valor;
    }
	return nuevoNodo;
}

void
borrarNodo(NodoAVL **nodo)
{
    if (nodo && *nodo) {
        free(*nodo);
        *nodo = NULL;
    }
}

void
insertarNodo(NodoAVL **arbol, NodoAVL *nodo)
{
    if (arbol) {
        if (*arbol) {
            if (nodo->valor < (*arbol)->valor) {
                insertarNodo(&(*arbol)->izquierda, nodo);
            } else {
                insertarNodo(&(*arbol)->derecha, nodo);
            }
            (*arbol)->factorEquilibrio = factorEquilibrio((*arbol));
            if ((*arbol)->factorEquilibrio == -2) {
                if (nodo->valor < (*arbol)->izquierda->valor) {
                    (*arbol) = rotacionIzquierda(&(*arbol));
                } else {
                    (*arbol)->izquierda = rotationDerecha(&(*arbol)->izquierda);
                    (*arbol) = rotacionIzquierda(&(*arbol));
                }
            }
            else if ((*arbol)->factorEquilibrio == 2) {
                if (nodo->valor >= (*arbol)->derecha->valor) {
                    (*arbol) = rotationDerecha(&(*arbol));
                } else {
                    (*arbol)->derecha = rotacionIzquierda(&(*arbol)->derecha);
                    (*arbol) = rotationDerecha(&(*arbol));
                }

            }
        } else {
            *arbol = nodo;
        }
    }
}

NodoAVL *extraerNodoArbol(NodoAVL **arbol, int valor)
{
    NodoAVL *nodoEncontrado = NULL;
    if (arbol && *arbol) {
        if (valor > (*arbol)->valor) {
            nodoEncontrado = extraerNodoArbol(&(*arbol)->derecha, valor);
            if (factorEquilibrio((*arbol)) == -2) {
                if (nodoEncontrado->valor  > (*arbol)->izquierda->valor){
                    (*arbol) = rotacionIzquierda(&(*arbol));
                } else {
                    (*arbol) -> izquierda = rotationDerecha(&(*arbol) -> izquierda);
                    (*arbol) = rotacionIzquierda(&(*arbol));
                }
            }
        } else if (valor < (*arbol)->valor) {
            nodoEncontrado = extraerNodoArbol(&(*arbol)->izquierda, valor);
            if (factorEquilibrio((*arbol)) == 2) {
                if (nodoEncontrado->valor < (*arbol)->derecha->valor) {
                    (*arbol) = rotationDerecha(&(*arbol));
                } else {
                    (*arbol)->derecha = rotacionIzquierda(&(*arbol)->derecha);
                    (*arbol) = rotationDerecha(&(*arbol));
                }
            } 
        } else {
            nodoEncontrado = *arbol;
            if (nodoEncontrado->izquierda == NULL) {
                (*arbol) = nodoEncontrado->derecha;
            } else if (nodoEncontrado->derecha == NULL) {
                (*arbol) = nodoEncontrado->izquierda;
            } else {
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
    }
    return nodoEncontrado;
}

/*
 * Limpia recursivamente los nodos del árbol/sub-árbol que se recibe como
 * como argumento.
 * No toma en cuenta ninguna rotación ya que se va a vaciar por completo.
 */
void
vaciarArbol(NodoAVL **raiz) 
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

void imprimirArbol(NodoAVL *arbol)
{
    if (arbol) {
        printf ("Notación de conjuntos: ");
        imprimirNotacion(arbol);
        printf ("\n");

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
imprimirArbolRecursivo(NodoAVL *arbol, uint8_t nivel, bool closesLevel)
{
    static uint32_t activeLevelsBits = 0; /* Solo usar manipulaciones de bit a bit */
    if (arbol) {
        if (closesLevel) {
            /* Operador implicación negada o "a and ~b". */
            activeLevelsBits = activeLevelsBits & ~(1 << (nivel - 1));
        } else {
            activeLevelsBits = activeLevelsBits | (1 << (nivel - 1));
        }

        sangria(nivel, activeLevelsBits);
        printf("%s %d\n", (closesLevel)? "└──": "├──", arbol->valor);

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
imprimirNotacion(NodoAVL *arbol)
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
visitarNodo(NodoAVL *nodo){
    if (nodo) {
        printf("%d ", nodo->valor);
    }
}

void
postorden(NodoAVL *raiz)
{
    if (raiz) {
        postorden(raiz->izquierda);
        postorden(raiz->derecha);
        visitarNodo(raiz);
    }
}

void
preorden(NodoAVL *raiz)
{
    if (raiz) {
        visitarNodo(raiz);
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

void
enorden(NodoAVL *raiz)
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
alturaArbol(NodoAVL *raiz)
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


NodoAVL *
rotationDerecha(NodoAVL **nodo)
{
    NodoAVL *temp = NULL;
    if (nodo && *nodo) {
        temp = (*nodo)->derecha;
        (*nodo)->derecha = temp->izquierda;
        temp->izquierda = (*nodo);
        (*nodo)->factorEquilibrio = factorEquilibrio((*nodo));
        temp->factorEquilibrio = factorEquilibrio(temp);
    }
    return temp;
}

/* Rotación  derecha. */
NodoAVL* rotacionIzquierda(NodoAVL **nodo) 
{
    NodoAVL* temp = NULL;
    if (nodo && *nodo) {
        temp = (*nodo) -> izquierda;
        (*nodo) -> izquierda = temp -> derecha;
        temp -> derecha = (*nodo);
        (*nodo) -> factorEquilibrio = factorEquilibrio((*nodo));
        temp -> factorEquilibrio = factorEquilibrio(temp);
    }
    return temp;
}

int
factorEquilibrio(NodoAVL *nodo)
{
    int factor = 0;
    if (nodo) {
        factor = alturaArbol(nodo->derecha) - alturaArbol(nodo->izquierda);
    }
    return factor;
}

NodoAVL *buscarNodo(NodoAVL *arbol, int valor)
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

void reemplazar(NodoAVL **actual) //Mayor de los menores
{
    NodoAVL *nuevoActual, *actualTemporal;
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
