#include "ListaOrdInt.h"

#ifdef LISTA_ORD_INT_IMP_2

typedef struct _cabezalListaOrdInt* ListaOrdInt;

struct nodoArbol {
	nodoArbol* izq;
	nodoArbol* der;
	int dato;
	int cantRepetidos;
};

struct _cabezalListaOrdInt {
	nodoArbol* nodo;
	int cantElementos;
};


ListaOrdInt crearListaOrdInt() {
	ListaOrdInt l = new _cabezalListaOrdInt;
	l->cantElementos = 0;
	l->nodo = NULL;

	return l;
}
//Pre:
//Pos: inserta un nodo en el arbol, en caso de que 'e' ya este en el arbol se aumenta en 1 la cant de repetidos (nodo->cantRepetidos++)
void insertarEnABB(nodoArbol*& nodo, int e) {
	if (nodo == NULL) {
		nodoArbol* n = new nodoArbol;
		n->dato = e;
		n->cantRepetidos++;
		n->izq = NULL;
		n->der = NULL;

	}else {
		if (nodo->dato < e) {
			insertarEnABB(nodo->der, e);
		}else {
			if (nodo->dato > e) {
				insertarEnABB(nodo->izq, e);
			}else {//Si nodo->dato == e, solo hace falta aumentar la cantidad de repetidos
				nodo->cantRepetidos++;
			}
		}
	}
}

void agregar(ListaOrdInt& l, int e) {
	insertarEnABB(l->nodo, e);
	l->cantElementos++;
}

bool borrarElemento(nodoArbol*& nodo, int e) {
	if (nodo != NULL) {
		if (nodo->dato == e) {
			if (nodo->cantRepetidos > 1) {
				nodo->cantRepetidos--;
			}else {
				nodoArbol* aBorrar = nodo;
				nodo = nodo->der;
				delete aBorrar;
				aBorrar = NULL;
			}
			return true; // Quiere decir que borro el elemento
		}else {
			if (nodo->dato > e) {
				borrarElemento(nodo->izq, e);
			}else {
				borrarElemento(nodo->der, e);
			}

		}
	}else {
		return false; // Quiere decir que no se borro el elemento porque no estaba en arbol
	}
}

void borrarMinimo(ListaOrdInt& l) {

	int min = minimo(l);
	if (borrarElemento(l->nodo, min)) {
		l->cantElementos--;
	}

}

void borrarMaximo(ListaOrdInt& l) {
	int max = maximo(l);
	if (borrarElemento(l->nodo, max)) {
		l->cantElementos--;
	}
}



void borrar(ListaOrdInt& l, int e) {
	if (borrarElemento(l->nodo, e)) {//Si borrarElemento devuelve true quiere decir que elimino el elemento
		l->cantElementos--;
	}
}

int minimo(ListaOrdInt l) {
	if (l->nodo != NULL) {
		int min = l->nodo->dato;
		while (l->nodo->izq != NULL) {
			min = l->nodo->dato;
			l->nodo = l->nodo->izq;
		}
		return min;
	}
}

int maximo(ListaOrdInt l) {
	if (l->nodo != NULL) {
		int max = l->nodo->dato;
		while (l->nodo->der != NULL) {
			max = l->nodo->dato;
			l->nodo = l->nodo->der;
		}
		return max;
	}
}

//Pre:
//Pos: retorna true si e se encuentra en el arbol, en otro caso devuelve false
bool existeElemento(nodoArbol* nodo, int e) {

	if (nodo == NULL) return false;
	if (nodo->dato == e) return true;

	if (nodo->dato < e) {
		return existeElemento(nodo->der, e);
	}
	else {
		return existeElemento(nodo->izq, e);
	}

}

bool existe(ListaOrdInt l, int e) {

	return existeElemento(l->nodo, e);
}

bool esVacia(ListaOrdInt l) {
	return l->cantElementos == 0;
}

unsigned int cantidadElementos(ListaOrdInt l) {
	return l->cantElementos;
}
//Pre:recibe un arbol
//Pos: carga todos los datos del arbol recibido en uno nuevo, sin compartir memoria
void cargarArbol(nodoArbol* n, nodoArbol*& m) {
	if (n != NULL) {

		nodoArbol* nodo = new nodoArbol;
		nodo->dato = n->dato;
		nodo->cantRepetidos = n->cantRepetidos;

		cargarArbol(n->der, m->der);
		cargarArbol(n->izq, m->izq);
	}
	else {
		m = NULL;
	}

}

ListaOrdInt clon(ListaOrdInt l) {
	ListaOrdInt lclon = new _cabezalListaOrdInt;
	lclon->cantElementos = l->cantElementos;
	cargarArbol(l->nodo, lclon->nodo);
	return lclon;
}

//Pre:
//Pos: Elimina cada nodo del arbol recibido por parametro
void destruirArbol(nodoArbol*& t) {
	if (t != NULL) {
		destruirArbol(t->izq);
		destruirArbol(t->der);
		delete t;
		t = NULL;
	}

}

void destruir(ListaOrdInt& l) {
	destruirArbol(l->nodo);
	delete l;
	l = NULL;
}



#endif