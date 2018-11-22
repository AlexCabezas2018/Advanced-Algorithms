/*
  Definición de algunas excepciones de las distintas
  implementaciones de los TADs.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Marco Antonio Gómez Martín, 2012
*/
#ifndef __EXCEPCIONES_H
#define __EXCEPCIONES_H

#include <string>
#include <iosfwd>
/**
 Clase de la que heredan todas las excepciones, y
 que proporciona el atributo que almacena el
 mensaje de error.
 */
class ExcepcionTAD {
public:
	ExcepcionTAD() {}
	ExcepcionTAD(const std::string &msg) : _msg(msg) {}

	const std::string msg() const { return _msg; }

	friend std::ostream &operator<<(std::ostream &out, const ExcepcionTAD &e);

protected:
	std::string _msg;
};

inline std::ostream &operator<<(std::ostream &out, const ExcepcionTAD &e) {
	out << e._msg;
	return out;
}


// Macro para declarar las clases de tipo excepción
// que heredan de ExcepcionConMensaje, para ahorrar
// escribir muchas veces lo mismo...
#define DECLARA_EXCEPCION(Excepcion) \
class Excepcion : public ExcepcionTAD { \
public: \
Excepcion() {}; \
Excepcion(const std::string &msg) : ExcepcionTAD(msg) {} \
};

/**
 Excepción generada por algunas operaciones de las pilas.
 */
DECLARA_EXCEPCION(EmptyStackException);

/**
 Excepción generada por algunas operaciones de las pilas.
 */
DECLARA_EXCEPCION(FullStackException);

/**
 Excepción generada por algunas de las operaciones de las colas.
 */
DECLARA_EXCEPCION(EmptyQueueException);

/**
 Excepción generada por algunas operaciones de las colas dobles.
 */
DECLARA_EXCEPCION(EmptyDequeException);

/**
 Excepción generada por algunas operaciones de las listas.
 */
DECLARA_EXCEPCION(EmptyListException);

/**
 Excepción generada por accesos incorrectos a las listas
 (tanto a un número de elemento incorrecto como por
 mal manejo de los iteradores).
 */
DECLARA_EXCEPCION(InvalidAccessException);

/**
 Excepción generada por algunas operaciones de los
 árboles binarios.
 */
DECLARA_EXCEPCION(EArbolVacio);

/**
 Excepción generada por algunas operaciones de los
 diccionarios y árboles de búsqueda.
 */
DECLARA_EXCEPCION(EClaveErronea);

#endif // __EXCEPCIONES_H
