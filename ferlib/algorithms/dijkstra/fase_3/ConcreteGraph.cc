#include "common.h"
#include "ConcreteGraph.h"

#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator>    // std::begin
#include <functional>  // std::bind
#include <utility>     // std::pair



namespace dijkstra_algorithm {
   

  /**************************************************************************/
  /*  ConcreteGraph  impl.
      Common data and functions to implement a directed/undirected  graph: 
  */
  /**************************************************************************/
  

  void ConcreteGraph::add_edge(const UserVertexId &from,
			       const UserVertexId &to, 
			       const TypeDistance & weight)
  {
    bool invariant = not repeated_user_edge(from, to);
    assert(invariant);

    
    const auto search_to = the_useridskeyed_map.find(to);
    const auto search_from = the_useridskeyed_map.find(from);
    
    // case: none vertex exists
    if(search_from == the_useridskeyed_map.end() and
       search_to == the_useridskeyed_map.end())
    {
      //just to check the goals
      const auto INVARIANT_N_USERS = the_useridskeyed_map.size();  // +2 expect
      const auto INVARIANT_N_INNERS = the_inneridskeyed_map.size();// +2 expect
      const auto INVARIANT_N_EDGES = num_edges(); // +1 expect
      const auto INVARIANT_N_VERTEX = num_inner_indexes(); // +2 expect
      //INVARIANT_ADJACENCY checked inside insert_adjacency() = f(g. direction)
    
      //actions
      InnerVertexId from_inner_id = num_inner_indexes() + 1;
      InnerVertexId to_inner_id = from_inner_id + 1; 
      BaseEdgePtr new_edge = insert_edge(from_inner_id, to_inner_id, weight);
      //adding 'from' vertex
      the_useridskeyed_map[from] = from_inner_id;
      the_inneridskeyed_map[from_inner_id] = from;
      the_vertex_map[from_inner_id] =
	VertexValue(new ConcreteVertex(from_inner_id, from));
      the_vertex_map[from_inner_id]->add_neighbor(new_edge);
      //adding 'to' vertex
      the_useridskeyed_map[to] = to_inner_id;
      the_inneridskeyed_map[to_inner_id] = to;
      the_vertex_map[to_inner_id] =
	VertexValue(new ConcreteVertex(to_inner_id, to));
      the_vertex_map[to_inner_id]->add_neighbor(new_edge);
      // adjacency data
      insert_adjacency(from_inner_id, to_inner_id, new_edge);
   
      assert((INVARIANT_N_USERS  + 2 == the_useridskeyed_map.size()) and
	     (INVARIANT_N_INNERS + 2 == the_inneridskeyed_map.size()) and
	     (INVARIANT_N_EDGES  + 1 == num_edges()) and
	     (INVARIANT_N_VERTEX + 2 == num_inner_indexes()));
    }

    // case: 'from' vertex exists / 'to' dosen't
    else if(search_to == the_useridskeyed_map.end())
    {
      //just to check the goals
      const auto INVARIANT_N_USERS = the_useridskeyed_map.size();  // +1 expect
      const auto INVARIANT_N_INNERS = the_inneridskeyed_map.size();// +1 expect
      const auto INVARIANT_N_EDGES = num_edges(); // +1 expect
      const auto INVARIANT_N_VERTEX = num_inner_indexes(); // +1 expect      

      //actions
      InnerVertexId from_inner_id = the_useridskeyed_map[from];
      InnerVertexId to_inner_id = num_inner_indexes() + 1;
      BaseEdgePtr new_edge = insert_edge(from_inner_id, to_inner_id, weight);
      the_vertex_map[from_inner_id]->add_neighbor(new_edge); // updating 'from'
      the_useridskeyed_map[to] = to_inner_id; //adding 'to' vertex
      the_inneridskeyed_map[to_inner_id] = to;
      the_vertex_map[to_inner_id] =
	VertexValue(new ConcreteVertex(to_inner_id, to));
      the_vertex_map[to_inner_id]->add_neighbor(new_edge);
      insert_adjacency(from_inner_id, to_inner_id, new_edge);

      // verifying invariant 
      assert((INVARIANT_N_USERS  + 1 == the_useridskeyed_map.size()) and
	     (INVARIANT_N_INNERS + 1 == the_inneridskeyed_map.size()) and
	     (INVARIANT_N_EDGES  + 1 == num_edges()) and
	     (INVARIANT_N_VERTEX + 1 == num_inner_indexes()));      
    }

    // case: 'to' vertex exists / 'from' dosen't
    else if(search_from == the_useridskeyed_map.end())
    {
      //just to check the goals
      const auto INVARIANT_N_USERS = the_useridskeyed_map.size();  // +1 expect
      const auto INVARIANT_N_INNERS = the_inneridskeyed_map.size();// +1 expect
      const auto INVARIANT_N_EDGES = num_edges(); // +1 expect
      const auto INVARIANT_N_VERTEX = num_inner_indexes(); // +1 expect      

      //actions
      InnerVertexId to_inner_id = the_useridskeyed_map[to];
      InnerVertexId from_inner_id = num_inner_indexes() + 1;
      BaseEdgePtr new_edge = insert_edge(from_inner_id, to_inner_id, weight);
      the_useridskeyed_map[from] = from_inner_id; //adding 'from' vertex
      the_inneridskeyed_map[from_inner_id] = from;
      the_vertex_map[from_inner_id] =
	VertexValue(new ConcreteVertex(from_inner_id, from));
      the_vertex_map[from_inner_id]->add_neighbor(new_edge);
      the_vertex_map[to_inner_id]->add_neighbor(new_edge); // updating 'to'
      insert_adjacency(from_inner_id, to_inner_id, new_edge);

      // verifying invariant 
      assert((INVARIANT_N_USERS  + 1 == the_useridskeyed_map.size()) and
	     (INVARIANT_N_INNERS + 1 == the_inneridskeyed_map.size()) and
	     (INVARIANT_N_EDGES  + 1 == num_edges()) and
	     (INVARIANT_N_VERTEX + 1 == num_inner_indexes()));
    }

    // both vertexes already exists
    else
    {
      //just to check the goals
      const auto INVARIANT_N_USERS = the_useridskeyed_map.size();  // +0 expect
      const auto INVARIANT_N_INNERS = the_inneridskeyed_map.size();// +0 expect
      const auto INVARIANT_N_EDGES = num_edges(); // +1 expect
      const auto INVARIANT_N_VERTEX = num_inner_indexes(); // +0 expect      

      //actions
      InnerVertexId from_inner_id = the_useridskeyed_map[from];
      InnerVertexId to_inner_id = the_useridskeyed_map[to];
      BaseEdgePtr new_edge = insert_edge(from_inner_id, to_inner_id, weight);
      the_vertex_map[from_inner_id]->add_neighbor(new_edge);
      the_vertex_map[to_inner_id]->add_neighbor(new_edge);
      insert_adjacency(from_inner_id, to_inner_id, new_edge);
	    
      // verifying invariant 
      assert((INVARIANT_N_USERS  + 0 == the_useridskeyed_map.size()) and
	     (INVARIANT_N_INNERS + 0 == the_inneridskeyed_map.size()) and
	     (INVARIANT_N_EDGES  + 1 == num_edges()) and
	     (INVARIANT_N_VERTEX + 0 == num_inner_indexes()));      
    }
    
  }

  //--------------------------------------------------------------------------

  void ConcreteGraph::add_vertex(const UserVertexId &id)
  {
    const auto search_id = the_useridskeyed_map.find(id);

    bool invariant = (search_id == the_useridskeyed_map.end());
    assert(invariant);
    const auto INVARIANT_N_USERS = the_useridskeyed_map.size();  // +1 expect
    const auto INVARIANT_N_INNERS = the_inneridskeyed_map.size();// +1 expect
    const auto INVARIANT_N_VERTEX = num_inner_indexes();         // +1 expect

    //adding 'from' vertex
    InnerVertexId id_inner_id = num_inner_indexes() + 1;
    the_useridskeyed_map[id] = id_inner_id;
    the_inneridskeyed_map[id_inner_id] = id;
    the_vertex_map[id_inner_id] =
      VertexValue(new ConcreteVertex(id_inner_id, id));
    
    invariant = invariant and 
      ((INVARIANT_N_USERS  + 1 == the_useridskeyed_map.size()) and
       (INVARIANT_N_INNERS + 1 == the_inneridskeyed_map.size()) and
       (INVARIANT_N_VERTEX + 1 == num_inner_indexes()));
    assert(invariant);
  }
  
  //--------------------------------------------------------------------------

  // Idem for DIRECTED & UNDIRECTED graphs
  //
  bool ConcreteGraph::repeated_user_edge(const UserVertexId &from,
					 const UserVertexId to)const
  {
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


  /**************************************************************************/
  /** DirectedConcreteGraph  impl.

      Directed graph specialization of a ConcreteGraph.
  */
  /**************************************************************************/
  
  BaseEdgePtr DirectedConcreteGraph::insert_edge(const InnerVertexId &from,
						 const InnerVertexId &to, 
						 const TypeDistance & weight)
  {
    auto invariant = num_edges();

    BaseEdgePtr new_value(new ConcreteEdge(from, to, weight,
					   EdgeDirection::FROM_TO));    
    the_edge_map[num_edges() + 1] = new_value;
    assert(invariant == num_edges()-1);
    return new_value;
  }
     
  //--------------------------------------------------------------------------

  void DirectedConcreteGraph::insert_adjacency(const InnerVertexId &from,
					       const InnerVertexId &to, 
					       const AdjacEdge &edge)
  {
    const auto INVARIANT_OUTSIZE = the_adjacency_data.the_outward_edges.size();
    const auto INVARIANT_INSIZE = the_adjacency_data.the_inward_edges.size();
    unsigned int INVARIANT_NCHANGES = 1;
      
    the_adjacency_data.the_outward_edges.insert(std::make_pair(from, edge));
    the_adjacency_data.the_inward_edges.insert(std::make_pair(to, edge));
  	    
    bool invariant =
      (INVARIANT_OUTSIZE == the_adjacency_data.the_outward_edges.size() -
       INVARIANT_NCHANGES) and
      (INVARIANT_INSIZE == the_adjacency_data.the_inward_edges.size() -
       INVARIANT_NCHANGES);
    assert (invariant);
  }

  //--------------------------------------------------------------------------


  /**************************************************************************/
  /** UndirectedConcreteGraph  impl.

      Undirected graph specialization of a ConcreteGraph.
  */
  /**************************************************************************/
  
  BaseEdgePtr UndirectedConcreteGraph::insert_edge(const InnerVertexId &from,
						 const InnerVertexId &to, 
						 const TypeDistance & weight)
  {
    auto invariant = num_edges();
    
    BaseEdgePtr new_value(new ConcreteEdge(from, to, weight,
					   EdgeDirection::BOTH));
    the_edge_map[num_edges() + 1] = new_value;
    assert(invariant == num_edges()-1);
    return new_value;
  }
     
  //--------------------------------------------------------------------------

  void UndirectedConcreteGraph::insert_adjacency(const InnerVertexId &from,
					       const InnerVertexId &to, 
					       const AdjacEdge &edge)
  {
    const auto INVARIANT_OUTSIZE = the_adjacency_data.the_outward_edges.size();
    const auto INVARIANT_INSIZE = the_adjacency_data.the_inward_edges.size();
    unsigned int INVARIANT_NCHANGES = 2;
  
    the_adjacency_data.the_outward_edges.insert(std::make_pair(from, edge));
    the_adjacency_data.the_inward_edges.insert(std::make_pair(to, edge));
    the_adjacency_data.the_outward_edges.insert(std::make_pair(to, edge));
    the_adjacency_data.the_inward_edges.insert(std::make_pair(from, edge));
	    
    bool invariant =
      (INVARIANT_OUTSIZE == the_adjacency_data.the_outward_edges.size() -
       INVARIANT_NCHANGES) and
      (INVARIANT_INSIZE == the_adjacency_data.the_inward_edges.size() -
       INVARIANT_NCHANGES);
    assert (invariant);
  }

  //--------------------------------------------------------------------------


} //end-of namespace dijkstra_algorithm
