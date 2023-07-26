#include "ColaInt.h"

#ifdef COLA_INT_IMP
struct nodoCola {
	nodoCola* sig;
	int dato;
};

struct _cabezalColaInt {
	nodoCola* lista;
	nodoCola* ult;
	int cantElementos;
};

ColaInt crearColaInt() {
	ColaInt cabezal = new _cabezalColaInt;
	cabezal->lista = NULL;
	cabezal->ult = NULL;
	cabezal->cantElementos = 0;
	return cabezal;
}

void encolar(ColaInt& c, int e) {
	nodoCola* nodo = new nodoCola;
	nodo->dato = e;
	nodo->sig = NULL;

	if (c->lista == NULL) c->lista = nodo;
	else c->ult->sig = nodo;
	c->ult = nodo;

	c->cantElementos++;

}

int principio(ColaInt c) {
	return c->lista->dato;
}

void desencolar(ColaInt& c) {
	nodoCola* aBorrar = c->lista;
	c->lista = c->lista->sig;
	if (c->lista == NULL) c->ult = NULL;
	delete aBorrar;
	c->cantElementos--;
}

bool esVacia(ColaInt c) {
	return c->lista == NULL;
}

unsigned int cantidadElementos(ColaInt c) {
	return c->cantElementos;
}

ColaInt clon(ColaInt c) {
	ColaInt clon = crearColaInt();
	nodoCola* aux = c->lista;
	while (aux != NULL)
	{
		encolar(clon, aux->dato);
		aux = aux->sig;
	}
	
	return clon;
}

void destruir(ColaInt& c) {
	while (c->lista != NULL) {
		desencolar(c);
	}
	delete c;
	c = NULL;
}

#endif