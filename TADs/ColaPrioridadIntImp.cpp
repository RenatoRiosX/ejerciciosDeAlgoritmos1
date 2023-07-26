#include "ColaPrioridadInt.h"

#ifdef COLAPRIORIDAD_INT_IMP

struct nodoColaPrioridad{
	nodoColaPrioridad* sig;
	int valor;
	int prioridad;

};

struct _cabezalColaPrioridadInt {
	nodoColaPrioridad* primero;
	nodoColaPrioridad* ult;
	int cantElementos;
	int cota;
};

//Agregar elemento con mayor prioridad e indice
ColaPrioridadInt crearColaPrioridadInt(unsigned int cota) {
	ColaPrioridadInt cola = new _cabezalColaPrioridadInt;
	cola->primero = cola->ult = NULL;
	cola->cantElementos = 0;
	cola->cota = cota;
	return cola;
}

//Pre:!esLlena
//Pos: inserta un elemento e con prioridad p a la cola de prioridad. Los elementos con
//      igual prioridad se agregan en orden FIFO. Numeros mas grandes de p tienen mas prioridad.
void agregarElemento(nodoColaPrioridad* &cola, nodoColaPrioridad*& ultimo, int e, int p) {
	if (cola == NULL) {
		nodoColaPrioridad* nuevo = new nodoColaPrioridad;
		nuevo->valor = e;
		nuevo->prioridad = p;
		nuevo->sig = NULL;
		cola = nuevo;
		ultimo = nuevo;

	} else {
		if (cola->prioridad < p) {
			nodoColaPrioridad* nuevo = new nodoColaPrioridad;
			nuevo->valor = e;
			nuevo->prioridad = p;
			nuevo->sig = cola;
			cola = nuevo;
		} else {
			agregarElemento(cola->sig,ultimo, e, p);
		}
	}
}

void encolar(ColaPrioridadInt& c, int e, int p) {
	//Si la cola de prioridad esta llena se corta la ejecucion
	assert(!esLlena(c));
	agregarElemento(c->primero, c->ult, e, p);
	c->cantElementos++;
}

//retorna el elemento del principio de la cola de prioridad (con mayor prioridad)
int principio(ColaPrioridadInt c) {
	return c->primero->valor;
}

int principioPrioridad(ColaPrioridadInt c) {
	return c->primero->prioridad;
}

void desencolar(ColaPrioridadInt& c) {
	nodoColaPrioridad* aBorrar = c->primero;
	c->primero = c->primero->sig;
	if (c->primero == NULL) c->ult = NULL;
	delete aBorrar;
	c->cantElementos--;

}

bool esVacia(ColaPrioridadInt c) {
	//return c->cantElementos == 0;
	return c->primero == NULL;
}

bool esLlena(ColaPrioridadInt c) {
	return c->cantElementos == c->cota;
}

unsigned int cantidadElementos(ColaPrioridadInt c) {
	return c->cantElementos;
}

ColaPrioridadInt clon(ColaPrioridadInt c) {
	ColaPrioridadInt clon = crearColaPrioridadInt(c->cota);
	nodoColaPrioridad* cAux = c->primero;
	while (cAux != NULL){
		encolar(clon, cAux->valor, cAux->prioridad);
		cAux = cAux->sig;
	}
	return clon;
}

void destruir(ColaPrioridadInt& c) {
	while (!esVacia(c)){
		desencolar(c);
	}
	delete c;
	c = NULL;
}

#endif