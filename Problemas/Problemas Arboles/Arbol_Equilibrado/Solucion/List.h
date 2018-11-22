/**
  @file Lista.h

  Implementaci�n del TAD lista, utilizando una 
  lista doblemente enlazada.

  Estructura de Datos y Algoritmos
  Facultad de Inform�tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G�mez Mart�n, 2012
*/
#ifndef __LIST_H
#define __LIST_H

#include "Exceptions.h"
#include <cassert>

/**
 Implementaci�n del TAD Lista utilizando una lista doblemente enlazada.

 Las operaciones son:

 - EmptyList: -> List. Generadora implementada en el
   constructor sin par�metros.
 - Push_front: List, Elem -> List. Generadora.
 - push_back: List, Elem -> List. Modificadora.
 - front: List - -> Elem. Observadora parcial
 - pop_front: List - -> List. Modificadora parcial
 - back: List - -> Elem. Observadora parcial
 - pop_back: List - -> List. Modificadora parcial
 - empty: List -> Bool. Observadora
 - size: List -> Entero. Obervadora.
 - at: List, Entero - -> Elem. Observador parcial.

 @author Marco Antonio G�mez Mart�n
 */
template <class T>
class List {
private:
	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y dos punteros, uno al nodo anterior y otro al nodo siguiente.
	 Ambos punteros podr�an ser NULL si el nodo es el primero
	 y/o �ltimo de la lista enlazada.
	 */
	class Nodo {
	public:
		Nodo() : _sig(NULL), _ant(NULL) {}
		Nodo(const T &elem) : _elem(elem), _sig(NULL), _ant(NULL) {}
		Nodo(Nodo *ant, const T &elem, Nodo *sig) : 
		    _elem(elem), _sig(sig), _ant(ant) {}

		T _elem;
		Nodo *_sig;
		Nodo *_ant;
	};

public:

	/** Constructor; operaci�n EmptyList. */
	List() : _prim(NULL), _ult(NULL), _numElems(0) {}

	/** Destructor; elimina la lista doblemente enlazada. */
	~List() {
		libera();
	}

	/**
	 A�ade un nuevo elemento en la cabeza de la lista.
	 Operaci�n generadora.

	 @param elem Elemento que se a�ade en la cabecera de
	 la lista.
	*/
	void push_front(const T &elem) {
		_prim = insertaElem(elem, NULL, _prim);
		if (_ult == NULL)
			_ult = _prim;
	}

	/**
	 A�ade un nuevo elemento al final de la lista (a la 
	 "derecha"). Operaci�n modificadora.

	 push_back(e, EmptyList) = Cons(e, EmptyList)
	 push_back(e, Push_front(x, xs)) = Push_front(x, push_back(e, xs))
	*/
	void push_back(const T &elem) {
		_ult = insertaElem(elem, _ult, NULL);
		if (_prim == NULL)
			_prim = _ult;
	}

	/**
	 Devuelve el valor almacenado en la cabecera de la
	 lista. Es un error preguntar por el primero de
	 una lista vac�a.

	 front(Push_front(x, xs)) = x
	 error front(EmptyList)

	 @return Elemento en la cabecera de la lista.
	 */
	const T &front() const {
		if (empty())
			throw EmptyListException("Cannot get front. The list is empty.");
		return _prim->_elem;
	}

	/**
	 Devuelve el valor almacenado en la �ltima posici�n
	 de la lista (a la derecha).
	 Es un error preguntar por el primero de una lista vac�a.

	 back(Push_front(x, xs)) = x           SI empty(xs)
	 back(Push_front(x, xs)) = back(xs)  SI !empty(xs)
	 error back(EmptyList)

	 @return Elemento en la cola de la lista.
	 */
	const T &back() const {
		if (empty())
			throw EmptyListException("Cannot get back. The list is empty.");

		return _ult->_elem;
	}

	/**
	 Elimina el primer elemento de la lista.
	 Es un error intentar obtener el resto de una lista vac�a.

	 pop_front(Push_front(x, xs)) = xs
	 error pop_front(EmptyList)
	*/
	void pop_front() {
		if (empty())
			throw EmptyListException("Cannot pop. The list is empty.");

		Nodo *aBorrar = _prim;
		_prim = _prim->_sig;
		borraElem(aBorrar);
		if (_prim == NULL)
			_ult = NULL;
	}

	/**
	 Elimina el �ltimo elemento de la lista.
	 Es un error intentar obtener el inicio de una lista vac�a.

	 inicio(Push_front(x, EmptyList)) = EmptyList
	 inicio(Push_front(x, xs)) = Push_front(x, inicio(xs)) SI !empty(xs)
	 error inicio(EmptyList)
	*/
	void pop_back() {
		if (empty())
			throw EmptyListException("Cannot pop. The list is empty.");

		Nodo *aBorrar = _ult;
		_ult = _ult->_ant;
		borraElem(aBorrar);
		if (_ult == NULL)
			_prim = NULL;
	}

	/**
	 Operaci�n observadora para saber si una lista
	 tiene o no elementos.

	 empty(EmptyList) = true
	 empty(Push_front(x, xs)) = false

	 @return true si la lista no tiene elementos.
	 */
	bool empty() const {
		return _prim == NULL;
	}

	/**
	 Devuelve el n�mero de elementos que hay en la
	 lista.
	 size(EmptyList) = 0
	 size(Push_front(x, xs)) = 1 + size(xs)

	 @return N�mero de elementos.
	 */
	unsigned int size() const {
		return _numElems;
	}

	/**
	 Devuelve el elemento i-�simo de la lista, teniendo
	 en cuenta que el primer elemento (first())
	 es el elemento 0 y el �ltimo es size()-1,
	 es decir idx est� en [0..size()-1].
	 Operaci�n observadora parcial que puede fallar
	 si se da un �ndice incorrecto. El �ndice es
	 entero sin signo, para evitar que se puedan
	 pedir elementos negativos.

	 elem(0, Push_front(x, xs)) = x
	 elem(n, Push_front(x, xs)) = elem(n-1, xs) si n > 0
	 error elem(n, xs) si !( 0 <= n < size(xs) )
	*/
	const T &at(unsigned int idx) const {
		if (idx >= _numElems)
			throw InvalidAccessException("Cannot get specified element. Invalid index");

		Nodo *aux = _prim;
		for (int i = 0; i < idx; ++i)
			aux = aux->_sig;

		return aux->_elem;
	}

	/**
	 Clase interna que implementa un iterador sobre
	 la lista que permite recorrer la lista pero no
	 permite cambiarlos.
	 */
	class ConstIterator {
	public:
		ConstIterator() : _act(NULL) {}

		void next() {
			if (_act == NULL) throw InvalidAccessException();
			_act = _act->_sig;
		}

		const T &elem() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_elem;
		}

		bool operator==(const ConstIterator &other) const {
			return _act == other._act;
		}

		bool operator!=(const ConstIterator &other) const {
			return !(this->operator==(other));
		}

		const T& operator*() const {
			return elem();
		}

		ConstIterator &operator++() {
			next();
			return *this;
		}

		ConstIterator operator++(int) {
			ConstIterator ret(*this);
			operator++();
			return ret;
		}

	protected:
		// Para que pueda construir objetos del
		// tipo iterador
		friend class List;

		ConstIterator(Nodo *act) : _act(act) {}

		// Puntero al nodo actual del recorrido
		Nodo *_act;
	};

	/**
	 Clase interna que implementa un iterador sobre
	 la lista que permite recorrer la lista e incluso
	 alterar el valor de sus elementos.
	 */
	class Iterator {
	public:
		Iterator() : _act(NULL) {}

		void next() {
			if (_act == NULL) throw InvalidAccessException();
			_act = _act->_sig;
		}

		const T &elem() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_elem;
		}

		void set(const T &elem) const {
			if (_act == NULL) throw InvalidAccessException();
			_act->_elem = elem;
		}

		bool operator==(const Iterator &other) const {
			return _act == other._act;
		}

		bool operator!=(const Iterator &other) const {
			return !(this->operator==(other));
		}

		const T& operator*() const {
			return elem();
		}

		T& operator*() {
			// C�digo id�ntico al de elem() porque �ste es const,
			// por lo que no se puede usar desde aqu�.
			if (_act == NULL) throw InvalidAccessException();
			return _act->_elem;
		}

		Iterator &operator++() {
			next();
			return *this;
		}

		Iterator operator++(int) {
			Iterator ret(*this);
			operator++();
			return ret;
		}

	protected:
		// Para que pueda construir objetos del
		// tipo iterador
		friend class List;

		Iterator(Nodo *act) : _act(act) {}

		// Puntero al nodo actual del recorrido
		Nodo *_act;
	};

	/**
	 Devuelve el iterador constante al principio de la lista.
	 @return iterador al principio de la lista;
	 coincidir� con cend() si la lista est� vac�a.
	 */
	ConstIterator cbegin() const {
		return ConstIterator(_prim);
	}

	/**
	 @return Devuelve un iterador constante al final del recorrido
	 (fuera de �ste).
	 */
	ConstIterator cend() const {
		return ConstIterator(NULL);
	}

	/**
	 Devuelve el iterador no constante al principio de la lista.
	 @return iterador al principio de la lista;
	 coincidir� con end() si la lista est� vac�a.
	 */
	Iterator begin() {
		return Iterator(_prim);
	}

	/**
	 @return Devuelve un iterador no constante al final del recorrido
	 (fuera de �ste).
	 */
	Iterator end() const {
		return Iterator(NULL);
	}


	/**
	 Permite eliminar de la lista el elemento
	 apuntado por el iterador que se pasa como par�metro.
	 El iterador recibido DEJA DE SER V�LIDO. En su
	 lugar, deber� utilizarse el iterador devuelto, que
	 apuntar� al siguiente elemento al borrado.
	 @param it Iterador colocado en el elemento que se
	 quiere borrar.
	 @return Nuevo iterador colocado en el elemento siguiente
	 al borrado (podr�a coincidir con final() si el
	 elemento que se borr� era el �ltimo de la lista).
	 */
	Iterator erase(const Iterator &it) {
		if (it._act == NULL)
			throw InvalidAccessException("Cannot erase specified element. Iterator pointing to NULL");

		// Cubrimos los casos especiales donde
		// borramos alguno de los extremos
		if (it._act == _prim) {
			pop_front();
			return Iterator(_prim);
		} else if (it._act == _ult) {
			pop_back();
			return Iterator(NULL);
		} else {
			// El elemento a borrar es interno a la lista.
			Nodo *sig = it._act->_sig;
			borraElem(it._act);
			return Iterator(sig);
		}
	}

	/**
	 M�todo para insertar un elemento en la lista
	 en el punto marcado por el iterador. En concreto,
	 se a�ade _justo antes_ que el elemento actual. Es
	 decir, si it==l.primero(), el elemento insertado se
	 convierte en el primer elemento (y el iterador
	 apuntar� al segundo). Si it==l.final(), el elemento
	 insertado ser� el �ltimo (e it seguir� apuntando
	 fuera del recorrido).
	 @param elem Valor del elemento a insertar.
	 @param it Punto en el que insertar el elemento.
	 */
	void insert(const T &elem, const Iterator &it) {

		// Caso especial: �a�adir al principio?
		if (_prim == it._act) {
			push_front(elem);
		} else
		// Caso especial: �a�adir al final?
		if (it._act == NULL) {
			push_back(elem);
		}
		// Caso normal
		else {
			insertaElem(elem, it._act->_ant, it._act);
		}
	}

	// //
	// M�TODOS DE "FONTANER�A" DE C++ QUE HACEN VERS�TIL
	// A LA CLASE
	// //

	/** Constructor copia */
	List(const List<T> &other) : _prim(NULL), _ult(NULL) {
		copia(other);
	}

	/** Operador de asignaci�n */
	List<T> &operator=(const List<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci�n. */
	bool operator==(const List<T> &rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		bool iguales = true;
		Nodo *p1 = _prim;
		Nodo *p2 = rhs._prim;
		while ((p1 != NULL) && (p2 != NULL) && iguales) {
			if (p1->_elem != p2->_elem)
				iguales = false;
			else {
				p1 = p1->_sig;
				p2 = p2->_sig;
			}
		}
		return iguales;
	}

	bool operator!=(const List<T> &rhs) const {
		return !(*this == rhs);
	}


protected:

	void libera() {
		libera(_prim);
		_prim = NULL;
		_ult = NULL;
	}

	void copia(const List<T> &other) {
		// En vez de trabajar con punteros en la inserci�n,
		// usamos ponDr
		_prim = 0;
		_numElems = 0;

		Nodo *act = other._prim;
		while (act != NULL) {
			push_back(act->_elem);
			act = act->_sig;
		}
	}

private:


	/**
	 Inserta un elemento entre el nodo1 y el nodo2.
	 Devuelve el puntero al nodo creado.
	 Caso general: los dos nodos existen.
	    nodo1->_sig == nodo2
	    nodo2->_ant == nodo1
	 Casos especiales: alguno de los nodos no existe
	    nodo1 == NULL y/o nodo2 == NULL
	*/
	Nodo *insertaElem(const T &e, Nodo *nodo1, Nodo *nodo2) {
		Nodo *nuevo = new Nodo(nodo1, e, nodo2);
		if (nodo1 != NULL)
			nodo1->_sig = nuevo;
		if (nodo2 != NULL)
			nodo2->_ant = nuevo;
		_numElems ++;
		return nuevo;
	}

	/**
	 Elimina el nodo n. Si el nodo tiene nodos antes
	 o despu�s, actualiza sus punteros anterior y siguiente.
	 Caso general: hay nodos anterior y siguiente.
	 Casos especiales: algunos de los nodos (anterior o siguiente
	 a n) no existen.
	*/
	void borraElem(Nodo *n) {
		assert(n != NULL);
		Nodo *ant = n->_ant;
		Nodo *sig = n->_sig;
		if (ant != NULL)
			ant->_sig = sig;
		if (sig != NULL)
			sig->_ant = ant;
		_numElems --;
		delete n;
	}

	/**
	 Elimina todos los nodos de la lista enlazada cuyo
	 primer nodo se pasa como par�metro.
	 Se admite que el nodo sea NULL (no habr� nada que
	 liberar). En caso de pasarse un nodo v�lido,
	 su puntero al nodo anterior debe ser NULL (si no,
	 no ser�a el primero de la lista!).
	 */
	static void libera(Nodo *prim) {
		assert(!prim || !prim->_ant);

		while (prim != NULL) {
			Nodo *aux = prim;
			prim = prim->_sig;
			delete aux;
		}
	}

	// Puntero al primer y �ltimo elemento
	Nodo *_prim, *_ult;

	// N�mero de elementos (n�mero de nodos entre _prim y _ult)
	unsigned int _numElems;
};

#endif // __LIST_H
