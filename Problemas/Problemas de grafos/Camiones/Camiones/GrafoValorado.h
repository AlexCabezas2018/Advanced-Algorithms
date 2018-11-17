//
//  GrafoValorado.h
//
//  Implementación de grafos no dirigidos valorados
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2015-2018  Alberto Verdejo
//

#ifndef GRAFOVALORADO_H_
#define GRAFOVALORADO_H_

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

template <typename Valor>
class Arista_impl;

template <typename Valor>
class Arista {
public:
   Arista();
   Arista(int v, int w, Valor valor);
   int uno() const;
   int otro(int vert) const;
   Valor valor() const;
   void print(std::ostream & o = std::cout) const;
private:
   std::shared_ptr<Arista_impl<Valor>> pimpl;
};

template <typename Valor>
inline std::ostream & operator<<(std::ostream & o, Arista<Valor> const& ar){
   ar.print(o);
   return o;
}

template <typename Valor>
inline bool operator<(Arista<Valor> const& a, Arista<Valor> const& b)
{
   return a.valor() < b.valor();
}

template <typename Valor>
inline bool operator>(Arista<Valor> const& a, Arista<Valor> const& b)
{
   return a.valor() > b.valor();
}


template <typename Valor>
using AdysVal = std::vector<Arista<Valor>>;  // lista de adyacentes a un vértice

template <typename Valor>
class GrafoValorado {
public:
   
   /**
    * Crea un grafo valorado con V vértices, sin aristas.
    */
   GrafoValorado(int v) : _V(v), _E(0), _ady(_V) {}
   
   /**
    * Devuelve el número de vértices del grafo.
    */
   int V() const { return _V; }
   
   /**
    * Devuelve el número de aristas del grafo.
    */
   int E() const { return _E; }
   
   /**
    * Añade la arista v-w al grafo.
    * @throws invalid_argument si algún vértice no existe
    */
   void ponArista(Arista<Valor> const& arista);
   
   /**
    * Devuelve la lista de adyacentes de v.
    * @throws invalid_argument si v no existe
    */
   AdysVal<Valor> const& ady(int v) const;
   
   /**
    * Muestra el grafo en el stream de salida o
    */
   void print(std::ostream & o = std::cout) const;
   
private:
   int _V;   // número de vértices
   int _E;   // número de aristas
   std::vector<AdysVal<Valor>> _ady;   // vector de listas de adyacentes
   
};

/**
 * Para mostrar grafos por la salida estándar.
 */
template <typename Valor>
std::ostream & operator<<(std::ostream & o, GrafoValorado<Valor> const& g);



// IMPLEMENTACIÓN

template <typename Valor>
Arista<Valor>::Arista()
: pimpl(nullptr) {}

template <typename Valor>
Arista<Valor>::Arista(int v, int w, Valor valor)
: pimpl(std::make_shared<Arista_impl<Valor>>(v, w, valor)) {}

template <typename Valor>
int Arista<Valor>::uno() const { return pimpl->uno(); }

template <typename Valor>
int Arista<Valor>::otro(int vert) const { return pimpl->otro(vert); }

template <typename Valor>
Valor Arista<Valor>::valor() const { return pimpl->valor(); }

template <typename Valor>
void Arista<Valor>::print(std::ostream & o) const { pimpl->print(o); }


template <typename Valor>
class Arista_impl {
public:
   Arista_impl(int v, int w, Valor valor) : v(v), w(w), _valor(valor) {}
   int uno() const { return v; }
   int otro(int vert) const { return (vert == v) ? w : v; }
   Valor valor() const { return _valor; }
   void print(std::ostream& o = std::cout) const {
      o << "(" << v << ", " << w << ", " << _valor << ")";
   }
private:
   int v, w;
   Valor _valor;
};


template <typename Valor>
void GrafoValorado<Valor>::ponArista(Arista<Valor> const& arista) {
   int v = arista.uno();
   int w = arista.otro(v);
   if (v >= _V || w >= _V) throw std::invalid_argument("Vertice inexistente");
   ++_E;
   _ady[v].push_back(arista);
   _ady[w].push_back(arista);
}

template <typename Valor>
AdysVal<Valor> const& GrafoValorado<Valor>::ady(int v) const {
   if (v >= _V) throw std::invalid_argument("Vertice inexistente");
   return _ady[v];
}

template <typename Valor>
void GrafoValorado<Valor>::print(std::ostream & o) const {
   o << _V << " vértices, " << _E << " aristas\n";
   for (auto v = 0; v < _V; ++v) {
      o << v << ": ";
      for (auto const& w : _ady[v]) {
         o << w << " ";
      }
      o << "\n";
   }
}

template <typename Valor>
inline std::ostream & operator<<(std::ostream & o, GrafoValorado<Valor> const& g) {
   g.print(o);
   return o;
}


#endif /* GRAFOVALORADO_H_ */
