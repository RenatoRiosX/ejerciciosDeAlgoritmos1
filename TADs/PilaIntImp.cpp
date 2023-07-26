#include "PilaInt.h"

#ifdef PILA_INT_IMP

struct nodoPila {
	nodoPila* ant;
	int dato;
};

struct _cabezalPilaInt {
	nodoPila* cima;
	int cantNodos;
};

PilaInt crearPilaInt(){
	PilaInt pila = new _cabezalPilaInt;
	pila->cima = NULL;
	pila->cantNodos = 0;
	return pila;
}

void push(PilaInt& p, int e) {
	nodoPila* nodo = new nodoPila;
	nodo->dato = e;
	nodo->ant = p->cima;
	p->cima = nodo;
	p->cantNodos++;
	
}

int top(PilaInt p) {
	return p->cima->dato;
}

void pop(PilaInt& p) {
	nodoPila* aBorrar = p->cima;
	p->cima = p->cima->ant;
	delete aBorrar;
	p->cantNodos--;
}

unsigned int cantidadElementos(PilaInt p) {
	return p->cantNodos;
}

bool esVacia(PilaInt p) {
	bool vacia = true;
	if (p->cima != NULL) vacia = false;
	return vacia;
}

//Pre:
//Pos: rellena una pila con con los elementos que tiene la otra pila pasada por parametro
nodoPila* copiarPila(nodoPila* p) {
	if (p == NULL) return NULL;
	nodoPila* nodo = new nodoPila;
	nodo->dato = p->dato;
	nodo->ant = copiarPila(p->ant);
	return nodo;
}


PilaInt clon(PilaInt p) {
	PilaInt pclon = new _cabezalPilaInt();
	pclon->cantNodos = p->cantNodos;
	pclon->cima = copiarPila(p->cima);
	return pclon;
}

void destruir(PilaInt& p) {
	while (p->cima != NULL) {
		pop(p);
	}
	delete p;
}


#endif