//
//  GrafoDirigido.h
//
//  Implementación de grafos dirigidos
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2015-2018  Alberto Verdejo
//

#ifndef GRAFODIRIGIDO_H_
#define GRAFODIRIGIDO_H_

#include <iostream>
#include <stdexcept>
#include <vector>

using Adys = std::vector<int>;  // lista de adyacentes a un vértice

class GrafoDirigido {
   
   int _V;   // número de vértices
   int _E;   // número de aristas
   std::vector<Adys> _ady;   // vector de listas de adyacentes
   
public:
   
   /**
    * Crea un grafo dirigido con V vértices.
    */
   GrafoDirigido(int v) : _V(v), _E(0), _ady(_V) {}
   
   
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
   void ponArista(int v, int w) {
      if (v >= _V || w >= _V)
         throw std::invalid_argument("Vertice inexistente");
      ++_E;
      _ady[v].push_back(w);
   }
   
   
   /**
    * Comprueba si hay arista de u a v.
    */
   bool hayArista(int u, int v) const {
      for (auto w : _ady[u])
         if (w == v) return true;
      return false;
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
    * Devuelve el grafo dirigido inverso.
    */
   GrafoDirigido inverso() const {
      GrafoDirigido R(_V);
      for (auto v = 0; v < _V; ++v) {
         for (auto w : _ady[v]) {
            R.ponArista(w, v);
         }
      }
      return R;
   }
   
   
   /**
    * Muestra el grafo en el stream de salida o (para depurar)
    */
   void print(std::ostream& o = std::cout) const {
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
 * Para mostrar grafos por la salida estándar.
 */
inline std::ostream & operator<<(std::ostream & o, GrafoDirigido const& g) {
   g.print(o);
   return o;
}


#endif /* GRAFODIRIGIDO_H_ */
