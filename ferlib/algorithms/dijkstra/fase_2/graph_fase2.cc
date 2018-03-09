#include "common.h"
#include "graph_fase2.h"

#include <iostream>
#include <algorithm>
#include <iterator>    // std::begin
#include <functional>  // std::bind


#include <list>
#include <utility> // std::pair

namespace dijkstra_algorithm {

  //--------------------------------------------------------------------------

  // Allocates memory for adjacency list
  Fase2Graph::Fase2Graph(unsigned int num_vertex)
  {
    this->the_num_vertex = num_vertex;
    adj = new std::list<AdjPair> [num_vertex];
  }

  //--------------------------------------------------------------------------
 
  Fase2Graph::~Fase2Graph()
  {
    delete [] adj;
  }

  //--------------------------------------------------------------------------

  void Fase2Graph::add_edge(const VertexId &from, 
			    const VertexId &to, 
			    const TypeDistance & weight,
			    const EdgeDirection & dir)
  {
    (void) dir;
    /** @info undirected graph */
    adj[from].push_back(std::make_pair(to, weight));
    adj[to].push_back(std::make_pair(from, weight));
  }

  //--------------------------------------------------------------------------

  std::ostream& operator<<(std::ostream &out, const Fase2Graph &g)
  {
    out << "Nodes: " << g.num_vertex() << std::endl;
    out << "FROM\tTO\tWEIGHT" << std::endl;

    auto print_edge = [](const int & from, const AdjPair& p) 
      {std::cout << " " << from << "\t" << p.first << "\t"
       << p.second << std::endl;};

    for (unsigned int loopi=0; loopi<g.num_vertex();++loopi)
    {
      std::for_each(std::begin(g.adjac()[loopi]),
    		    std::end(g.adjac()[loopi]), 
    		    std::bind(print_edge, loopi, std::placeholders::_1));
    }

    return out;
  }

  //--------------------------------------------------------------------------



} //end-of namespace dijkstra_algorithm
