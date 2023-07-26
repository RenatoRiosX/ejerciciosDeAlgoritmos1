#include "ListaPosInt.h"

#ifdef LISTA_POS_INT_IMP

struct _cabezalListaPosInt {
	int largoVec;
	int* vec;
	int cantElementos;
};

ListaPosInt crearListaPosInt()
{
	ListaPosInt l = new _cabezalListaPosInt;
	l->vec = new int [10];
	l->largoVec = 10;
	l->cantElementos = 0;
	return l;
}

void agregar(ListaPosInt& l, int e, unsigned int pos)
{
	if (l->cantElementos < l->largoVec ) {//Agrego
		if (pos < l->largoVec && l->cantElementos > 0){
			//Muevo los elementos desde pos en adelante una posicion
			for (int i = l->cantElementos-1 ; i >= pos ; i--){
				l->vec[i + 1] = l->vec[i];
			}
			l->vec[pos] = e;
		}else { //Si pos es mayor al largo del vector, entonces inserto en el lugar siguiente al ultimo ocupado
			l->vec[l->cantElementos] = e;
		}
		l->cantElementos++;
	}else { // Creo un nuevo vector, paso los elementos y luego agrego
		int* ptrAux = new int [l->largoVec + 10];
		for (int i = 0; i < l->largoVec; i++){
			ptrAux[i] = l->vec[i];
		}
		delete [] l->vec;
		l->vec = ptrAux;
		l->largoVec = l->largoVec + 10;
		agregar(l,e,pos); //Para agregar hago llamada recursiva, la cual entrara en el primer caso y ahi se agregara el elemento

	}
}

void borrar(ListaPosInt& l, unsigned int pos)
{
	if (l->cantElementos > pos ) {
		for (int i = pos; i < l->cantElementos; i++){
			l->vec[i] = l->vec[i + 1];
		}
		l->cantElementos--;
	}
}

int elemento(ListaPosInt l, unsigned int pos)
{
	assert(pos<l->largoVec); //Si pos es una posicion no valida del vector, entonces se corta el programa
	return l->vec[pos];
}

bool esVacia(ListaPosInt l)
{
	return l->cantElementos == 0;
}

unsigned int cantidadElementos(ListaPosInt l)
{
	return l->cantElementos;
}

ListaPosInt clon(ListaPosInt l)
{
	ListaPosInt lClon = new _cabezalListaPosInt;
	lClon->cantElementos = 0;
	lClon->largoVec = l->largoVec;
	lClon->vec = new int[l->largoVec];

	for (int i = 0; i < l->cantElementos && i < l->largoVec; i++) {
		lClon->vec[i] = l->vec[i];
		lClon->cantElementos++;
	}

	return lClon;
}

void destruir(ListaPosInt& l)
{
	if(l != NULL) delete[] l->vec;
	delete l;
	l = NULL;
}


#endif