//
//  GrafoDirigidoValorado.h
//
//  Implementación de grafos dirigidos valorados
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2015-2018  Alberto Verdejo
//

#ifndef GRAFODIRIGIDOVALORADO_H_
#define GRAFODIRIGIDOVALORADO_H_

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

template <typename Valor>
class AristaDirigida_impl;

template <typename Valor>
class AristaDirigida {
public:
   AristaDirigida();
   AristaDirigida(int v, int w, Valor valor);
   int from() const;
   int to() const;
   Valor valor() const;
   void print(std::ostream & o = std::cout) const;
private:
   std::shared_ptr<AristaDirigida_impl<Valor>> pimpl;
};

template <typename Valor>
inline std::ostream & operator<<(std::ostream & o, AristaDirigida<Valor> const& ar){
   ar.print(o);
   return o;
}

template <typename Valor>
inline bool operator<(AristaDirigida<Valor> const& a, AristaDirigida<Valor> const& b)
{
   return a.valor() < b.valor();
}

template <typename Valor>
inline bool operator>(AristaDirigida<Valor> const& a, AristaDirigida<Valor> const& b)
{
   return a.valor() > b.valor();
}


template <typename Valor>
using AdysDirVal = std::vector<AristaDirigida<Valor>>;  // lista de adyacentes a un vértice

template <typename Valor>
class GrafoDirigidoValorado {
public:
   
   /**
    * Crea un grafo con V vértices.
    */
   GrafoDirigidoValorado(int v) : _V(v), _E(0), _ady(_V) {}
   
   /**
    * Devuelve el número de vértices del grafo.
    */
   int V() const { return _V; }
   
   /**
    * Devuelve el número de aristas del grafo.
    */
   int E() const { return _E; }
   
   /**
    * Añade la arista dirigida v-w al grafo.
    * @throws invalid_argument si algún vértice no existe
    */
   void ponArista(AristaDirigida<Valor> arista);
   
   /**
    * Comprueba si hay arista de v a w.
    */
   bool hayArista(int v, int w) const;
   
   /**
    * Devuelve la lista de adyacencia de v.
    * @throws invalid_argument si v no existe
    */
   AdysDirVal<Valor> const& ady(int v) const;
   
   /**
    * Devuelve el grafo dirigido inverso.
    */
   GrafoDirigidoValorado<Valor> inverso() const;
   
   /**
    * Muestra el grafo en el stream de salida o
    */
   void print(std::ostream & o = std::cout) const;
   
private:
   int _V;   // número de vértices
   int _E;   // número de aristas
   std::vector<AdysDirVal<Valor>> _ady;   // vector de listas de adyacentes
   
};

/**
 * Para mostrar grafos por la salida estándar.
 */
template <typename Valor>
inline std::ostream & operator<<(std::ostream & o, GrafoDirigidoValorado<Valor> const& g) {
   g.print(o);
   return o;
}


// IMPLEMENTACIÓN

template <typename Valor>
AristaDirigida<Valor>::AristaDirigida()
: pimpl(nullptr) {}

template <typename Valor>
AristaDirigida<Valor>::AristaDirigida(int v, int w, Valor valor)
: pimpl(std::make_shared<AristaDirigida_impl<Valor>>(v, w, valor)) {}

template <typename Valor>
int AristaDirigida<Valor>::from() const { return pimpl->from(); }

template <typename Valor>
int AristaDirigida<Valor>::to() const { return pimpl->to(); }

template <typename Valor>
Valor AristaDirigida<Valor>::valor() const { return pimpl->valor(); }

template <typename Valor>
void AristaDirigida<Valor>::print(std::ostream & o) const { pimpl->print(o); }


template <typename Valor>
class AristaDirigida_impl {
public:
   AristaDirigida_impl(int v, int w, Valor valor) : v(v), w(w), _valor(valor) {};
   int from() const { return v; }
   int to() const { return w; }
   Valor valor() const { return _valor; }
   void print(std::ostream& o) const {
      o << "(" << v << ", " << w << ", " << _valor << ")";
   }
private:
   int v, w;
   Valor _valor;
};


template <typename Valor>
void GrafoDirigidoValorado<Valor>::ponArista(AristaDirigida<Valor> arista) {
   int v = arista.from();
   int w = arista.to();
   if (v >= _V || w >= _V) throw std::invalid_argument("Vertice inexistente");
   ++_E;
   _ady[v].push_back(arista);
}

template <typename Valor>
bool GrafoDirigidoValorado<Valor>::hayArista(int v, int w) const {
   for (auto a : _ady[v])
      if (a.to() == w) return true;
   return false;
}

template <typename Valor>
AdysDirVal<Valor> const& GrafoDirigidoValorado<Valor>::ady(int v) const {
   if (v >= _V) throw std::invalid_argument("Vertice inexistente");
   return _ady[v];
}

template <typename Valor>
GrafoDirigidoValorado<Valor> GrafoDirigidoValorado<Valor>::inverso() const {
   GrafoDirigidoValorado R(_V);
   for (auto v = 0; v < _V; ++v) {
      for (auto a : _ady[v]) {
         R.ponArista(AristaDirigida<Valor>(a.to(), a.from(), a.valor()));
      }
   }
   return R;
}

template <typename Valor>
void GrafoDirigidoValorado<Valor>::print(std::ostream & o) const {
   o << _V << " vértices, " << _E << " aristas\n";
   for (auto v = 0; v < _V; ++v) {
      o << v << ": ";
      for (auto a : _ady[v]) {
         o << a << " ";
      }
      o << "\n";
   }
}


#endif /* GRAFODIRIGIDOVALORADO_H_ */
