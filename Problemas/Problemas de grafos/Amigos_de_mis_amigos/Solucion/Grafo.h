//
//  Grafo.h
//
//  Implementación de grafos no dirigidos
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2015-2018  Alberto Verdejo
//

#ifndef GRAFO_H_
#define GRAFO_H_

#include <iostream>
#include <vector>
#include <stdexcept>

using Adys = std::vector<int>;  // lista de adyacentes a un vértice

class Grafo {
   
   int _V;   // número de vértices
   int _E;   // número de aristas
   std::vector<Adys> _ady;   // vector de listas de adyacentes
   
public:
   
   /**
    * Crea un grafo con V vértices.
    */
   Grafo(int v) : _V(v), _E(0), _ady(_V) {}
   
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
   void ponArista(int v, int w) {
      if (v >= _V || w >= _V)
         throw std::invalid_argument("Vertice inexistente");
      ++_E;
      _ady[v].push_back(w);
      _ady[w].push_back(v);
   }
   
   
   /**
    * Devuelve la lista de adyacencia de v.
    * @throws invalid_argument si v no existe
    */
   Adys const& ady(int v) const {
      if (v >= _V)
         throw std::invalid_argument("Vertice inexistente");
      return _ady[v];
   }
   
   
   /**
    * Muestra el grafo en el stream de salida o (para depurar)
    */
   void print(std::ostream & o = std::cout) const {
      o << _V << " vértices, " << _E << " aristas\n";
      for (auto v = 0; v < _V; ++v) {
         o << v << ": ";
         for (auto w : _ady[v]) {
            o << w << " ";
         }
         o << "\n";
      }
   }
   
};

/**
 * Para mostrar grafos por la salida estándar
 */
inline std::ostream & operator<<(std::ostream & o, Grafo const& g){
   g.print(o);
   return o;
}


#endif /* GRAFO_H_ */
