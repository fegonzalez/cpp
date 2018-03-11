#include "common.h"
#include "ConcreteGraph.h"

#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator>    // std::begin
#include <functional>  // std::bind
#include <utility> // std::pair


//#include <list>



namespace dijkstra_algorithm {

  //--------------------------------------------------------------------------

  ConcreteGraph::ConcreteGraph()
    :the_num_vertex(0)
  {
  }
   
  //--------------------------------------------------------------------------

  void ConcreteGraph::add_edge(const UserVertexId &from,
			       const UserVertexId &to, 
			       const TypeDistance & weight,
			       const EdgeDirection & dir)
  {
    (void) dir;
    (void) from;
    (void) to;
    (void) weight;
    
    bool invariant = not repeated_user_edge(from, to);
    assert(invariant);
    
AKI LKO DEJO
    add   from   // si no existe

    add to   // si no existe
      
    
    
    /*
    
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

  void ConcreteGraph::add_vertex(const VertexId &id)
  {
    (void) id;
    assert(false); /// @todo implement me

    // assert(id not already in the graph);


  }

  
  //--------------------------------------------------------------------------

  bool ConcreteGraph::repeated_user_edge(const UserVertexId &from,
					 const UserVertexId to)const
  {
    (void) from;
    (void) to;
    const bool REPEATED = true;
    const bool NOT_REPEATED = false;
    bool retval = NOT_REPEATED;
    bool invariant = (retval == NOT_REPEATED);
    const auto search_to = the_useridskeyed_map.find(to);
    if(search_to == the_useridskeyed_map.end())
      return NOT_REPEATED;

    const auto search_from = the_useridskeyed_map.find(from);
    if(search_from == the_useridskeyed_map.end())
      return NOT_REPEATED;


    // from -> to exists ?
    InnerVertexId from_inner_id = search_from->second; 
    const auto from_outward_edges_range =
      the_adjacency_data.the_outward_edges.equal_range(from_inner_id);
    for(auto next_edge = from_outward_edges_range.first;
	next_edge != from_outward_edges_range.second;
	++next_edge)
    {
      if(next_edge->second->to() == search_to->second) 
      {
	retval = REPEATED;
	return retval;;
      }
    }
    invariant = (retval == NOT_REPEATED);
    assert(invariant);
      
    return retval;
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
