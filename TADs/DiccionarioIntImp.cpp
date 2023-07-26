#include "DiccionarioInt.h"

#ifdef DICCIONARIO_INT_IMP

struct nodoHash {
	nodoHash* sig;
	int dato;
};

struct _cabezalDiccionarioInt {
	nodoHash** vec;
	int cota;
	int cantElementos;
};

//Pre:
//Pos: retorna el resto de la division entera entre x y cota
int fHash(int x, int cota) { 
	int res = x % cota;
	//Si res es negativo, le aplico el valor absoluto, esto lo logro multiplicando por -1
	if (res < 0) res = res * -1; 
	return res;
}

DiccionarioInt crearDiccionarioInt(unsigned int esperados) {

	DiccionarioInt dic = new _cabezalDiccionarioInt;
	dic->cantElementos = 0;
	dic->cota = esperados;
	dic->vec = new nodoHash*[esperados];
	for (int i = 0; i < esperados; i++) dic->vec[i] = NULL;
	return dic;
}

void agregar(DiccionarioInt& d, int e) {

	if (!pertenece(d, e)) {
		int i = fHash(e, d->cota);
		nodoHash* nodo = new nodoHash;
		nodo->dato = e;
		nodo->sig = d->vec[i];
		d->vec[i] = nodo;
		d->cantElementos++;
	}
	
}
//Pre:
//Pos: retorna true si elimino el elemento e, caso contrario false
bool borrarElemento(nodoHash* &l, int e) {

	if (l == NULL) return false;
	if (l->dato == e) {
		nodoHash* aBorrar = l;
		l = l->sig;
		delete aBorrar;
		aBorrar = NULL;

		return true;
	}else {
		return borrarElemento(l->sig, e);
	}
}

void borrar(DiccionarioInt& d, int e) {

	int i= fHash(e, d->cota);

	if (borrarElemento(d->vec[i],e)) {
		d->cantElementos--;
	}
}

bool pertenece(DiccionarioInt d, int e) {

	int i = fHash(e, d->cota);
	nodoHash* lista = d->vec[i];
	while (lista != NULL && lista->dato != e) {
		lista = lista->sig;
	}
	return lista != NULL; //Si lista es NULL quiere decir que e no esta en la tabla, caso contrario lo esta
}

int elemento(DiccionarioInt d) {

	int i = 0;
	nodoHash* lista = d->vec[i];
	while (lista == NULL) {
		i++;
		lista = d->vec[i];
	}
	return lista->dato;
}

bool esVacio(DiccionarioInt d) {

	return d->cantElementos == 0;
}

unsigned int cantidadElementos(DiccionarioInt d) {

	return d->cantElementos;
}

DiccionarioInt clon(DiccionarioInt d) {
	DiccionarioInt clon = crearDiccionarioInt(d->cota); //Creo un nuevo cabezal y clono los datos de d
	for (int i = 0; i < d->cota; i++) { //Lleno la tabla (vec) de clon con los datos que tiene d
		nodoHash* lista = d->vec[i];
		while (lista != NULL) {
			agregar(clon,lista->dato);
			lista = lista->sig;
		}
	}
	return clon;
}
//Pre:
//Pos: borrar la lista que recibe por parametro
void borrarLista(nodoHash* &l) {

	if (l != NULL) {
		nodoHash* aBorrar = l;
		l = l->sig;
		delete aBorrar;
		aBorrar = NULL;
		borrarLista(l->sig);
	}
}

void destruir(DiccionarioInt& d) {

	for (int i = 0; i < d->cota; i++){
		borrarLista(d->vec[i]);
	}
	delete[] d->vec;
	delete d;
	d = NULL;
	
}


#endif