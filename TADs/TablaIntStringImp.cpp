#include "TablaIntString.h"

#ifdef TABLA_INT_STRING_IMP

struct nodoHash{
	nodoHash* sig;
	int dom;
	const char* img;
};

struct _cabezalTablaIntString {
	nodoHash** vec;
	int cantEsperada;
	int cantElementos;
};

int funcionHash(int d,int largoVec) {
	int indice = d % largoVec;
	if (indice < 0) indice = indice * -1;

	return indice;
}

TablaIntString crearTablaIntString(unsigned int esperados) {
	TablaIntString tb = new _cabezalTablaIntString;
	tb->cantEsperada = esperados;
	tb->cantElementos = 0;
	tb->vec = new nodoHash*[esperados];
	for (int i = 0; i < esperados; i++) tb->vec[i] = NULL;
	return tb;
}

//Pre:
//Pos: agrega un par ordenado si no pertenecia a la tabla, si ya estaba, entonces se actualiza la imagen de d
bool agregarElemento(nodoHash* &lista, int d, const char* r) {
	if (lista == NULL) { // agrego el elemento
		nodoHash* nodo = new nodoHash;
		nodo->dom = d;
		nodo->img = r;
		nodo->sig = NULL;
		lista = nodo;
		return true;
	}else {
		//Si d ya estaba en la lista, se actualiza la imagen
		if (lista->dom == d) {
			lista->img = r;
			return false;
		}else {
			return agregarElemento(lista->sig, d, r);
		}
	}
}
void agregar(TablaIntString& t, int d, const char* r) {
	int indice = funcionHash(d, t->cantEsperada);
	//Si se agrego un elemento se aumenta cantidad
	if (agregarElemento(t->vec[indice], d, r)) t->cantElementos++;
}

bool estaDefinida(TablaIntString t, int d) {
	nodoHash* lista = t->vec[funcionHash(d,t->cantEsperada)];
	while (lista != NULL) {
		if (lista->dom == d) return true;
		lista = lista->sig;
	}
	//Si llego hasta aca quiere decir que no se encontro d en la tabla
	return false;
}

const char* recuperar(TablaIntString t, int d) {
	int pos = funcionHash(d, t->cantEsperada);
	nodoHash* l = t->vec[pos];
	while (l->dom != NULL && l->dom != d) {
		l = l->sig;
	}
	return l->img;
}

//Pre:
//Pos: borrar el par ordenado d->r, si es que se encuentra en la tabla, de no estar el par ordenado, no hace nada
void borrarElemento(nodoHash*& l, int d, int& cantElementos) {

	if (l == NULL) return;
	if (l->dom == d) {
		nodoHash* aBorrar = l;
		l = l->sig;
		delete aBorrar;
		cantElementos--;

	}else {
		borrarElemento(l->sig, d, cantElementos);
	}
}

void borrar(TablaIntString& t, int d) {
	borrarElemento(t->vec[funcionHash(d, t->cantEsperada)], d, t->cantElementos);
}

int elemento(TablaIntString t) {
	int i = 0;
	while (t->vec[i] == NULL) {
		i++;
	}
	//Retorna el primer elemento que encuentre, iniciando por la posicion 0 de array
	return t->vec[i]->dom;
}

bool esVacia(TablaIntString t) {
	return t->cantElementos == 0;
}

unsigned int cantidadElementos(TablaIntString t) {
	return t->cantElementos;
}

//Pre:
//Pos: borrar la lista que recibe por parametro
void borrarHash(nodoHash*& l) {
	if (l != NULL) {
		borrarHash(l->sig);
		delete l;
		l = NULL;
	}
	
}

void destruir(TablaIntString& t) {

	for (int i = 0; i < t->cantEsperada; i++) {
		borrarHash(t->vec[i]);
	}
	delete[] t->vec;
	delete t;
	t = NULL;
}

TablaIntString clon(TablaIntString t) {
	TablaIntString clon = crearTablaIntString(t->cantEsperada); //Creo un nuevo cabezal y clono los datos de t
	for (int i = 0; i < t->cantEsperada; i++) { //Lleno la tabla (clon) con los datos que tiene t
		nodoHash* lista = t->vec[i];
		while (lista != NULL) {
			agregar(clon, lista->dom,lista->img);
			lista = lista->sig;
		}
	}
	
	return clon;
}

#endif