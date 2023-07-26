#include "MultisetInt.h"

#ifdef MULTISET_INT_IMP

struct nodoMultiset {
	int dato;
	int cantOcurrencias;
	nodoMultiset* sig;
};

struct _cabezalMultisetInt {
	int cantElementos;
	nodoMultiset* l;
};

MultisetInt crearMultisetInt() {
	MultisetInt m = new _cabezalMultisetInt;
	m->cantElementos = 0;
	m->l = NULL;
	return m;
}

//Pre:
//Pos: agrega el elemento e en multiset, si ya estaba entonces le suma la cant de ocurrencias
void agregarElemento(nodoMultiset* &lista, int e, unsigned int ocurrencias) {

	if (lista == NULL) {
		nodoMultiset* nodo = new nodoMultiset;
		nodo->dato = e;
		nodo->cantOcurrencias = ocurrencias;
		nodo->sig = NULL;
		lista = nodo;
	}else {

		if (lista->dato != e) {
			agregarElemento(lista->sig, e, ocurrencias);
		} else {
			//El elemento e ya estaba en el multiset, entonces sumo la cantidad de ocurrencias
			lista->cantOcurrencias += ocurrencias; //C += A equivale a C = C + A
		}
	}
}

void agregar(MultisetInt& s, int e, unsigned int ocurrencias){
	agregarElemento(s->l, e, ocurrencias);
	s->cantElementos = s->cantElementos + ocurrencias;
}

//Pre:
//Pos: borra una ocurrencia del elemento e del multiset. Si e no pertenece, no tiene efecto
void borrarElemento(nodoMultiset*& lista, int e, int & cantElementos) {

	if (lista == NULL) return;

	if (lista->dato != e) {
		borrarElemento(lista->sig, e, cantElementos);
	} else {
		if (lista->cantOcurrencias > 1) {
			lista->cantOcurrencias--;
			
		} else {
			nodoMultiset* aBorrar = lista;
			lista = lista->sig;
			delete aBorrar;	
		}
		//Si llego aca, quiere decir que elimino una ocurrencia del elemento e
		cantElementos--;
	}
}

void borrar(MultisetInt& s, int e) {
	borrarElemento(s->l, e, s->cantElementos) ;
}

bool pertenece(MultisetInt s, int e) {
	nodoMultiset* lista = s->l;
	while (lista != NULL && lista->dato != e) {
		lista = lista->sig;	
	}
	//Si lista es diferente de NULL quiere decir que e esta en el multiset
	return lista != NULL;
}

MultisetInt unionConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt u = crearMultisetInt();
	nodoMultiset* s1Lista = s1->l;
	nodoMultiset* s2Lista = s2->l;
	while (s1Lista != NULL) {
		agregar(u, s1Lista->dato, s1Lista->cantOcurrencias);
		s1Lista = s1Lista->sig;
	}

	while (s2Lista != NULL) {
		int elemento = s2Lista->dato;
		unsigned int ocurrencias = s2Lista->cantOcurrencias;
		if (!pertenece(u, elemento)) {
			agregar(u, elemento, ocurrencias);
		}else {
			nodoMultiset* nodo = u->l;
			bool salir = false;
			while (nodo != NULL && !salir) {
				if (nodo->dato == elemento) {
					if (nodo->cantOcurrencias < ocurrencias) {
						//Actualizo cantidad de elementos y ocurrencias de elemento
						u->cantElementos += (ocurrencias - nodo->cantOcurrencias);
						nodo->cantOcurrencias = ocurrencias;
					}
					salir = true;
				}
				nodo = nodo->sig;
			}
		}
		s2Lista = s2Lista->sig;
	}

	return u;
}

//Pre: 
//Pos: retorna la cantidad de ocurrencias en el multiset de un elemento e 
int cantidadOcurrencias(nodoMultiset* m, int e) {
	int cantOcurrencias = 0;
	while (m != NULL) {
		if (m->dato == e) cantOcurrencias = m->cantOcurrencias;
		m = m->sig;
	}
	return cantOcurrencias;
}

MultisetInt interseccionConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt res = crearMultisetInt();
	nodoMultiset* s1Lista = s1->l;
	while (s1Lista != NULL ) {
		if (pertenece(s2, s1Lista->dato)) {
			int minOcurrencias = s1Lista->cantOcurrencias;
			int ocurrenciasS2 = cantidadOcurrencias(s2->l, s1Lista->dato);
			if (ocurrenciasS2 < minOcurrencias) {
				minOcurrencias = ocurrenciasS2;
			}
			agregar(res, s1Lista->dato, minOcurrencias);
		}
		s1Lista = s1Lista->sig;
	}
	return res;
}


//Pre:
//Pos: borra n  ocurrencias del elemento e del multiset. Si e no pertenece, no tiene efecto
void borrarOcurrenciasDeElemento(nodoMultiset*& lista, int e, int n, int& cantElementos) {

	if (lista == NULL) return;

	if (lista->dato != e) {
		borrarOcurrenciasDeElemento(lista->sig, e, n, cantElementos);
	} else {
		if (lista->cantOcurrencias > n) {
			cantElementos = cantElementos - n;
			lista->cantOcurrencias = lista->cantOcurrencias - n;
		}else {
			cantElementos = cantElementos - lista->cantOcurrencias;
			nodoMultiset* aBorrar = lista;
			lista = lista->sig;
			delete aBorrar;	
		}
	}
}

MultisetInt diferenciaConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt s1Clon = clon(s1);
	nodoMultiset* s2Aux = s2->l;
	while (s2Aux != NULL){
		borrarOcurrenciasDeElemento(s1Clon->l, s2Aux->dato, s2Aux->cantOcurrencias, s1Clon->cantElementos);
		s2Aux = s2Aux->sig;
	}
	return s1Clon;
}

bool contenidoEn(MultisetInt s1, MultisetInt s2) {
	nodoMultiset* l1Aux = s1->l;
	while (l1Aux != NULL) {
		if (!pertenece(s2, l1Aux->dato) || cantidadOcurrencias(l1Aux, l1Aux->dato) > cantidadOcurrencias(s2->l, l1Aux->dato)) return false;
		l1Aux = l1Aux->sig;
	}
	//Si se llego hasta el final de la lista m1, quiere decir que esta contenida
	return true;
}

int elemento(MultisetInt s) {
	//Retorna el primer elemento de la lista
	return s->l->dato;
}

bool esVacio(MultisetInt s) {
	return s->l == 0;
}

unsigned int cantidadElementos(MultisetInt s) {
	return s->cantElementos;
}

//Pre:
//Pos: libera la memoria de la lista
void destruirLista(nodoMultiset*& l) {
	if (l != NULL) {
		destruirLista(l->sig);
		delete l;
		l = NULL;
	}
}

void destruir(MultisetInt& s) {
	destruirLista(s->l);
	delete s;
	s = NULL;
}

MultisetInt clon(MultisetInt s) {
	MultisetInt m = crearMultisetInt();
	nodoMultiset* aux = s->l;
	while (aux != NULL) {
		int dato = aux->dato;
		int cantOcurrencias = aux->cantOcurrencias;
		agregar(m, dato, cantOcurrencias);
		aux = aux->sig;
	}
	return m;
}

#endif