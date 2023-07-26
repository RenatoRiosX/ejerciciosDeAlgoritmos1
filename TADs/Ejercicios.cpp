#include "Ejercicios.h"

//Pre:
//Pos: aplana un arbol. Convierte un arbol en una lista
void aplanarArbol(NodoABInt* a, ListaOrdInt & res) {
	if (a==NULL) return;
	else{
		agregar(res, a->dato);
		aplanarArbol(a->izq, res);
		aplanarArbol(a->der, res);
	}
}

//Pre:
//Pos: retorna una lista con los mismos elementos que tiene el arbol 'a' recibido por parametro
ListaOrdInt Enlistar(NodoABInt* a)
{
	if (a == NULL) return NULL;
	ListaOrdInt res = crearListaOrdInt();
	aplanarArbol(a, res);
	return res;
}

//Pre:
//Pos: carga una lista resultado de forma ordenada (ver agregar()) con los elementos que tiene la lista l.
void cargarLista(ListaOrdInt & listaRes, ListaOrdInt &lista) {
	bool estaVacia = esVacia(lista);
	if (estaVacia)return;

	while (!estaVacia)
	{
		int min = minimo(lista);
		agregar(listaRes,min);
		borrar(lista, min);
		estaVacia = esVacia(lista);
	}
}

//Pre:
//Pos: hace un merge de la lista l1 y l2, la lista resultado es ordenada.
ListaOrdInt UnionListaOrd(ListaOrdInt l1, ListaOrdInt l2)
{	
	ListaOrdInt listaUnion = crearListaOrdInt();
	if (esVacia(l1) && esVacia(l2)) return listaUnion;
	ListaOrdInt listal1 = clon(l1);
	ListaOrdInt listal2 = clon(l2);
	if (!esVacia(l1) && esVacia(l2)) {
		cargarLista(listaUnion, listal1);
	}else {
		if (esVacia(l1) && !esVacia(l2)) {
			cargarLista(listaUnion, listal2);
		}else{
			cargarLista(listaUnion, l1);
			cargarLista(listaUnion, l2);
		}
	}
	return listaUnion;
}

bool EstaContenida(PilaInt p1, PilaInt p2)
{
	bool res = false;
	PilaInt p1Clon = clon(p1);
	PilaInt p2Clon = clon(p2);
	PilaInt p3 = crearPilaInt();

	while (!esVacia(p1Clon) && !esVacia(p2Clon)){
		if (top(p1Clon) == top(p2Clon)) { //Si el elemento de la cima de p1 y p2 clon son iguales
			pop(p1Clon);
			pop(p2Clon);
			//Vuelvo a poner en p2clon los elementos que eran diferentes a cima p1clon
			while (!esVacia(p3)){
				push(p2Clon, top(p3));
				pop(p3);
			}
		} else {
			push(p3, top(p2Clon));
			pop(p2Clon);
		}
	}

	if (esVacia(p1Clon)) { //Si p1Clon esta vacia, entonces quiere decir que esta contenida en p2
		res = true;
	}

	destruir(p1Clon);
	destruir(p2Clon);
	destruir(p3);

	return res;
}

//Recordad que un multiset es un conjunto con repeticiones
ListaOrdInt ObtenerRepetidos(MultisetInt m) 
{	
	ListaOrdInt res = crearListaOrdInt();

	MultisetInt mclon = clon(m);

	while (cantidadElementos(mclon) > 0) {
		int x = elemento(mclon);
		//Borro una ocurrencia de x en mclon
		borrar(mclon, x);
		//Si x pertenece a mclon significa que habia mas de una ocurrencia de x en mclon. Si x no esta en lista res, entonces lo agrego
		if (pertenece(mclon, x) && !existe(res, x)) {
			agregar(res, x);
		}
	}
	
	return res;
}

MultisetInt Xor(MultisetInt m1, MultisetInt m2)
{
	MultisetInt unionM = unionConjuntos(m1, m2);
	MultisetInt interseccionM = interseccionConjuntos(m1, m2);
	MultisetInt resultado = diferenciaConjuntos(unionM, interseccionM);
	destruir(unionM);
	destruir(interseccionM);

	return resultado;
}

ColaPrioridadInt MenorPrioridad(ColaPrioridadInt c) {

	ColaPrioridadInt clonC = clon(c);
	ColaPrioridadInt clon2C = clon(c);
	ColaPrioridadInt clon3C = clon(c);

	if (esVacia(clonC))
		return clonC;
	
	int menorPrioridad = principioPrioridad(clon2C);

	//Hallo la menor prioridad de la cola
	while (!esVacia(clon2C)) {
		if (principioPrioridad(clon2C) < menorPrioridad) {
			menorPrioridad = principioPrioridad(clon2C);
		}
		desencolar(clon2C);
	}

	int cantElementosMenorP = 0;
	//Hallo cuantos elementos tienen la menor prioridad
	while (!esVacia(clon3C)) {
		if (principioPrioridad(clon3C) == menorPrioridad) {
			cantElementosMenorP++;
		}
		desencolar(clon3C);
	}
	//Creo una nueva cola de prioridad con la cantidad de elementos que tienen la menor prioridad
	ColaPrioridadInt nuevaCola = crearColaPrioridadInt(cantElementosMenorP);

	while (!esVacia(clonC)) {
		int elemento = principio(clonC);

		if (principioPrioridad(clonC) == menorPrioridad) {
			encolar(nuevaCola, elemento, menorPrioridad);
		}
		desencolar(clonC);
	}

	//Libero memoria
	destruir(clonC);
	destruir(clon2C);
	destruir(clon3C);

	return nuevaCola;

}

