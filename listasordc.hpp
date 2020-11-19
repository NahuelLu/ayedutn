#ifndef LISTASORDC_HPP_INCLUDED
#define LISTASORDC_HPP_INCLUDED

//Completa

template <typename T>
Nodo<T>* buscar(T clave, Nodo<T>* lista, int (*criterio)(T, T))
{
	while (lista != nullptr && criterio(clave, lista->dato) > 0)
		lista = lista->sig;

	return lista != nullptr && criterio(clave, lista->dato) == 0 ? lista : nullptr;
}
template <typename T>
void insertar(T valor, Nodo<T>*& lista, int (*criterio)(T, T))
{
	Nodo<T>* nuevo = new Nodo<T>;
	nuevo->dato = valor;
	if (lista == nullptr || criterio(nuevo->dato, lista->dato) < 0) {
		nuevo->sig = lista;
		lista = nuevo;
	} else {
		Nodo<T>* p = lista;
		while (p->sig != nullptr && criterio(nuevo->dato, p->sig->dato) >= 0)
			p = p->sig;
		nuevo->sig = p->sig;
		p->sig = nuevo;
	}
}

template <typename T>
Nodo<T>* extraer(T clave, Nodo<T>*& lista, int (*criterio)(T, T))
{
	Nodo<T> *aux, *p;
	if (lista == nullptr) //caso lista vacía
		return nullptr;//Para borrado directo return false;
	if (criterio(clave, lista->dato) == 0) { //caso extraer primer elemento
		aux = lista;
		lista = lista->sig;
		return aux;//Para borrado directo delete aux; return true;
	}
	p = lista;
	while (p->sig != nullptr && criterio(clave, p->sig->dato) > 0)
		p = p->sig;
	if (p->sig != nullptr && criterio(clave, p->sig->dato) == 0) {
		aux = p->sig;
		p->sig = p->sig->sig;
		return aux;//Para borrado directo delete aux; return true;
	} else {
		return nullptr;//Para borrado directo return false;
	}
}

template <typename T>
bool borrar(T clave, Nodo<T>*& lista, int (*criterio)(T, T))
{
	Nodo<T>* extraido = extraer(clave, lista, criterio);
	if (extraido) {
		delete extraido;
		return true;
	} else {
		return false;
	}
}

template <typename T>
Nodo<T>* insertar_unico(T valor, Nodo<T>*& lista, int (*criterio)(T, T))
{
    //Caso de lista vacia o el primero es menor al primer elemento(Varia segun el criterio)
	if (lista == nullptr || criterio(valor, lista->dato) < 0) {
		Nodo<T>* nuevo = new Nodo<T>; //Genero nodo
		nuevo->dato = valor; // y guardo el valor //Este sera valor verificar si esta en la lista o no.
		nuevo->sig = lista;
		lista = nuevo;
		return nuevo;       //Retorna la nuevo
	} else {
		if (criterio(valor, lista->dato) == 0) //Si justo es igual al primero
			return lista;
		Nodo<T>* p = lista;
		while (p->sig != nullptr && criterio(valor, p->sig->dato) > 0)//Mientras que el numero ingresado sea que el que esta en la lista
			p = p->sig;
		if (p->sig != nullptr && criterio(valor, p->sig->dato) == 0) {  //Verifico si se salio del while por ser iguales o porque el elemento a insertar es MENOR al elemento de la lista
			return p->sig; //devuelvo el que ya estaba en la lista (osea estaba el elemento a insertar ya estaba en la lista)
		} else {
		    //Accede al else cuando el elemento a insertar NO ESTA en la lista y lo inserto y la posición correspondiente segun el criterio
			Nodo<T>* nuevo = new Nodo<T>; //Genero nodo
			nuevo->dato = valor; // y guardo el valor
			nuevo->sig = p->sig;
			p->sig = nuevo;
			return nuevo;
		}
	}
}

#endif // LISTASORDC_HPP_INCLUDED
