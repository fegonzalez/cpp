#include "common.h"
#include "ConcreteGraph.h"

#include <iostream>
#include <algorithm>
#include <iterator>    // std::begin
#include <functional>  // std::bind


#include <list>
#include <utility> // std::pair

namespace dijkstra_algorithm {

  //--------------------------------------------------------------------------

  // Allocates memory for adjacency list
  ConcreteGraph::ConcreteGraph(unsigned int num_vertex)
  {
    this->the_num_vertex = num_vertex;
    //adj = new std::list<AdjPair> [num_vertex];
  }

  //--------------------------------------------------------------------------
 
  ConcreteGraph::~ConcreteGraph()
  {
    //    delete [] adj;
  }

  //--------------------------------------------------------------------------

  // void ConcreteGraph::add_vertex(const VertexId &id)
  // {
  //   assert(id not already in the graph);

  //   ConcreteVertex
  // }
   

  //--------------------------------------------------------------------------

  void ConcreteGraph::add_edge(const VertexId &from, 
			    const VertexId &to, 
			    const TypeDistance & weight,
			    const EdgeDirection & dir)
  {
    (void) dir;
    (void) from;
    (void) to;
    (void) weight;
    /*
    buscar from 

    buscar to

    
    assert( not (edge ya existe)); // existe from y tiene a 'to' como vecino OR 
                                   // viceversa

    update mapa de ids (inner, user)
      
    #crear nodo from
    a) inner id = nxt id = num_nodos +1
    b) the_vertexid_map[inner]=user

    crear nodo to

    
    crear Edge data struct

    (void) dir;

*/


    
    /** @info undirected graph */
    // adj[from].push_back(std::make_pair(to, weight));
    // adj[to].push_back(std::make_pair(from, weight));



    
  }

  //--------------------------------------------------------------------------

  std::ostream& operator<<(std::ostream &out, const ConcreteGraph &g)
  {
    out << "Nodes: " << g.num_vertex() << std::endl;
    out << "FROM\tTO\tWEIGHT" << std::endl;

    // auto print_edge = [](const int & from, const AdjPair& p) 
    //   {std::cout << " " << from << "\t" << p.first << "\t"
    //    << p.second << std::endl;};

    // for (unsigned int loopi=0; loopi<g.num_vertex();++loopi)
    // {
    //   std::for_each(std::begin(g.adjac()[loopi]),
    // 		    std::end(g.adjac()[loopi]), 
    // 		    std::bind(print_edge, loopi, std::placeholders::_1));
    // }

    return out;
  }

  //--------------------------------------------------------------------------



} //end-of namespace dijkstra_algorithm
