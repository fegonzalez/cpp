
#include "BaseGraph.h"

#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator>    // std::begin
#include <functional>  // std::bind
#include <utility>     // std::pair


//#define DEBUG_MODE_DIJKSTRA true


namespace path_finding {
   

  /**************************************************************************/
  /*  Graph  impl.
      Common data and functions to implement a directed/undirected  graph: 
  */
  /**************************************************************************/


  void Graph::add_edge(const TypeEdgeData &edge)
  {
    add_edge(edge.from, edge.to, edge.weight, edge.id);
  }

  //--------------------------------------------------------------------------
  
  void Graph::add_edge(const UserVertexId &from,
		       const UserVertexId &to, 
		       const TypeDistance &weight,
		       const UserEdgeId &edge_user_id)
  {
    bool invariant = not repeated_user_edge(from, to);
    assert(invariant);

    
    const auto search_to = the_useridskeyed_map.find(to);
    const auto search_from = the_useridskeyed_map.find(from);
    
    // case: none vertex exists
    if(search_from == the_useridskeyed_map.end() and
       search_to == the_useridskeyed_map.end())
    {
      // invariant = check the correction of the code
      const auto INVARIANT_N_USERS = the_useridskeyed_map.size();  // +2 expect
      const auto INVARIANT_N_INNERS = the_inneridskeyed_map.size();// +2 expect
      const auto INVARIANT_N_EDGES = num_edges(); // +1 expect
      const auto INVARIANT_N_VERTEX = num_inner_indexes(); // +2 expect
      //INVARIANT_ADJACENCY checked inside insert_adjacency() = f(g. direction)
    
      //actions
      InnerVertexId from_inner_id = num_inner_indexes() + 1;
      InnerVertexId to_inner_id = from_inner_id + 1; 
      BaseEdgePtr new_edge = insert_edge(from_inner_id, to_inner_id, weight,
					 edge_user_id);
      //adding 'from' vertex
      the_useridskeyed_map[from] = from_inner_id;
      the_inneridskeyed_map[from_inner_id] = from;
      the_vertex_map[from_inner_id] =
	VertexValue(new Vertex(from_inner_id, from));
      the_vertex_map[from_inner_id]->add_neighbor(new_edge);
      //adding 'to' vertex
      the_useridskeyed_map[to] = to_inner_id;
      the_inneridskeyed_map[to_inner_id] = to;
      the_vertex_map[to_inner_id] =
	VertexValue(new Vertex(to_inner_id, to));
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
      const auto INVARIANT_N_USERS = the_useridskeyed_map.size();  // +1 expect
      const auto INVARIANT_N_INNERS = the_inneridskeyed_map.size();// +1 expect
      const auto INVARIANT_N_EDGES = num_edges(); // +1 expect
      const auto INVARIANT_N_VERTEX = num_inner_indexes(); // +1 expect      

      //actions
      InnerVertexId from_inner_id = the_useridskeyed_map[from];
      InnerVertexId to_inner_id = num_inner_indexes() + 1;
      BaseEdgePtr new_edge = insert_edge(from_inner_id, to_inner_id, weight,
					 edge_user_id);
      the_vertex_map[from_inner_id]->add_neighbor(new_edge); // updating 'from'
      the_useridskeyed_map[to] = to_inner_id; //adding 'to' vertex
      the_inneridskeyed_map[to_inner_id] = to;
      the_vertex_map[to_inner_id] =
	VertexValue(new Vertex(to_inner_id, to));
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
      const auto INVARIANT_N_USERS = the_useridskeyed_map.size();  // +1 expect
      const auto INVARIANT_N_INNERS = the_inneridskeyed_map.size();// +1 expect
      const auto INVARIANT_N_EDGES = num_edges(); // +1 expect
      const auto INVARIANT_N_VERTEX = num_inner_indexes(); // +1 expect      

      //actions
      InnerVertexId to_inner_id = the_useridskeyed_map[to];
      InnerVertexId from_inner_id = num_inner_indexes() + 1;
      BaseEdgePtr new_edge = insert_edge(from_inner_id, to_inner_id, weight,
					 edge_user_id);
      the_useridskeyed_map[from] = from_inner_id; //adding 'from' vertex
      the_inneridskeyed_map[from_inner_id] = from;
      the_vertex_map[from_inner_id] =
	VertexValue(new Vertex(from_inner_id, from));
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
      const auto INVARIANT_N_USERS = the_useridskeyed_map.size();  // +0 expect
      const auto INVARIANT_N_INNERS = the_inneridskeyed_map.size();// +0 expect
      const auto INVARIANT_N_EDGES = num_edges(); // +1 expect
      const auto INVARIANT_N_VERTEX = num_inner_indexes(); // +0 expect      

      //actions
      InnerVertexId from_inner_id = the_useridskeyed_map[from];
      InnerVertexId to_inner_id = the_useridskeyed_map[to];
      BaseEdgePtr new_edge = insert_edge(from_inner_id, to_inner_id, weight,
					 edge_user_id);
      the_vertex_map[from_inner_id]->add_neighbor(new_edge);
      the_vertex_map[to_inner_id]->add_neighbor(new_edge);
      insert_adjacency(from_inner_id, to_inner_id, new_edge);
	    
      // verifying invariant 
      assert((INVARIANT_N_USERS  + 0 == the_useridskeyed_map.size()) and
	     (INVARIANT_N_INNERS + 0 == the_inneridskeyed_map.size()) and
	     (INVARIANT_N_EDGES  + 1 == num_edges()) and
	     (INVARIANT_N_VERTEX + 0 == num_inner_indexes()));      
    }


    
#ifdef DEBUG_MODE_DIJKSTRA
    
    std::clog << "\n########En: " << __FILE__
	      << " : in function " << __func__
	      << " at line " << __LINE__ << std::endl;


    //the_useridskeyed_map
    std::clog << "\nthe_useridskeyed_map<UserVertexId, InnerVertexId>:";
    std::for_each(std::begin(the_useridskeyed_map),
		  std::end(the_useridskeyed_map),
		  [] (const std::pair<UserVertexId, InnerVertexId> &val)
		  {
		    std::clog << "\nthe_useridskeyed_map[" << val.first
			      << "] = " << val.second;
		  });
    std::clog << std::endl;

    
    std::clog << "\nthe_inneridskeyed_map<InnerVertexId, UserVertexId>:";
    std::for_each(std::begin(the_inneridskeyed_map),
		  std::end(the_inneridskeyed_map),
		  [] (const std::pair<InnerVertexId, UserVertexId> &val)
		  {
		    std::clog << "\nthe_inneridskeyed_map[" << val.first
			      << "] = " << val.second;
		  });
    std::clog << std::endl;

    
    //the_vertex_map
    std::clog << "\nthe_vertex_map<InnerVertexId, VertexValue>:";
    std::for_each(std::begin(the_vertex_map),
		  std::end(the_vertex_map),
		  [] (const std::pair<InnerVertexId, VertexValue> &val)
		  {
		    std::clog << "\nthe_vertex_map[" << val.first
			      << "] = "
			      << "(" << val.second->user_id() << ", "
		      	      << val.second->inner_id() << ")";
		  });
    std::clog << std::endl;


    // the_edge_map
    std::clog << "\nthe_edge_map<EdgeId, EdgeValue>:";
    std::for_each(std::begin(the_edge_map),
		  std::end(the_edge_map),
		  [] (const std::pair<EdgeId, EdgeValue> &val)
		  {
		    std::clog
		      << "\nthe_edge_map[" << val.first
		      << "] = "
		      << val.second->from()
		      << ", " << val.second->to()
		      << ", " << val.second->weight()
		      << ", ";
		    const EdgeDirection & aux_dir = val.second->direction();
		    if (aux_dir==EdgeDirection::FROM_TO)
		      std::clog << "FROM_TO";
		    else
		      std::clog<< "BOTH";
		  });
    std::clog << std::endl;


    // The adjacency data
    std::clog
      << "\nthe_adjacency_data.the_outward_edges<InnerVertexId, AdjacEdge>:";
    std::for_each(std::begin(the_adjacency_data.the_outward_edges),
		  std::end(the_adjacency_data.the_outward_edges),
		  [] (const std::pair<InnerVertexId, AdjacEdge> &val)
		  {
		    std::clog
		      << "\nthe_adjacency_data.the_outward_edges["
		      << val.first << "] = "
		      << val.second->from()
		      << ", " << val.second->to()
		      << ", " << val.second->weight()
		      << ", ";
		    const EdgeDirection & aux_dir = val.second->direction();
		    if (aux_dir==EdgeDirection::FROM_TO)
		      std::clog << "FROM_TO";
		    else
		      std::clog<< "BOTH";
		  });
    std::clog << std::endl;

    
    std::clog
      << "\nthe_adjacency_data.the_inward_edges<InnerVertexId, AdjacEdge>:";
    std::for_each(std::begin(the_adjacency_data.the_inward_edges),
		  std::end(the_adjacency_data.the_inward_edges),
		  [] (const std::pair<InnerVertexId, AdjacEdge> &val)
		  {
		    std::clog
		      << "\nthe_adjacency_data.the_inward_edges["
		      << val.first << "] = "
		      << val.second->from()
		      << ", " << val.second->to()
		      << ", " << val.second->weight()
		      << ", ";
		    const EdgeDirection & aux_dir = val.second->direction();
		    if (aux_dir==EdgeDirection::FROM_TO)
		      std::clog << "FROM_TO";
		    else
		      std::clog<< "BOTH";
		  });
    std::clog << std::endl;
    
    std::clog << "\n##################\n" << std::endl;
    
#endif
    
  }

  //--------------------------------------------------------------------------

  void Graph::add_vertex(const UserVertexId &id)
  {
    const auto search_id = the_useridskeyed_map.find(id);
    assert(search_id == the_useridskeyed_map.end());

    //adding 'from' vertex
    InnerVertexId id_inner_id = num_inner_indexes() + 1;
    the_useridskeyed_map[id] = id_inner_id;
    the_inneridskeyed_map[id_inner_id] = id;
    the_vertex_map[id_inner_id] = VertexValue(new Vertex(id_inner_id, id));    
  }
  
  //--------------------------------------------------------------------------
  bool Graph::repeated_user_edge(const UserVertexId &from,
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

  InnerVertexId Graph::get_inner_id(const UserVertexId &id)const
  {
    auto search = the_useridskeyed_map.find(id);
    assert(search not_eq the_useridskeyed_map.end());
    return search->second;
  }
  
  //--------------------------------------------------------------------------
  UserVertexId Graph::get_user_id(const InnerVertexId &id)const
  {
    auto search = the_inneridskeyed_map.find(id);
    assert(search not_eq the_inneridskeyed_map.end());
    return search->second;
  }


  /**************************************************************************/
  /** DirectedGraph  impl.

      Directed graph specialization of a Graph.
  */
  /**************************************************************************/

  /// @todo aquí añadir el campo edge_id (std::string)
  BaseEdgePtr DirectedGraph::insert_edge(const InnerVertexId &from,
					 const InnerVertexId &to, 
					 const TypeDistance & weight,
					 const UserEdgeId &edge_user_id)
  {
    (void) edge_user_id;
    BaseEdgePtr new_value(new Edge(from, to, weight,
				   EdgeDirection::FROM_TO));    
    the_edge_map[num_edges() + 1] = new_value;
    return new_value;
  }
     
  //--------------------------------------------------------------------------

  void DirectedGraph::insert_adjacency(const InnerVertexId &from,
					       const InnerVertexId &to, 
					       const AdjacEdge &edge)
  {
    the_adjacency_data.the_outward_edges.insert(std::make_pair(from, edge));
    the_adjacency_data.the_inward_edges.insert(std::make_pair(to, edge));
  }


  /**************************************************************************/
  /** UndirectedGraph  impl.

      Undirected graph specialization of a Graph.
  */
  /**************************************************************************/
  
  BaseEdgePtr UndirectedGraph::insert_edge(const InnerVertexId &from,
					   const InnerVertexId &to, 
					   const TypeDistance & weight,
					   const UserEdgeId &edge_user_id)
  {
    (void) edge_user_id;
    BaseEdgePtr new_value(new Edge(from, to, weight,
				   EdgeDirection::BOTH));
    the_edge_map[num_edges() + 1] = new_value;
    return new_value;
  }
     
  //--------------------------------------------------------------------------

  void UndirectedGraph::insert_adjacency(const InnerVertexId &from,
					       const InnerVertexId &to, 
					       const AdjacEdge &edge)
  {
    the_adjacency_data.the_outward_edges.insert(std::make_pair(from, edge));
    the_adjacency_data.the_inward_edges.insert(std::make_pair(to, edge));
    the_adjacency_data.the_outward_edges.insert(std::make_pair(to, edge));
    the_adjacency_data.the_inward_edges.insert(std::make_pair(from, edge));
  }


  //--------------------------------------------------------------------------

  std::ostream& operator<<(std::ostream &out, const Graph &g)
  {
    auto print_edge = [&out](const UserVertexId &edge_src,
			     const UserVertexId &from,
    			     const UserVertexId &to,
    			     const TypeDistance  &weight,
			     const EdgeDirection &direction)
      {
	if(direction==EdgeDirection::FROM_TO)
	  out << "\t" << from << "\t" << to << "\t" << weight << std::endl;
	else
	{
	  if (edge_src == from)
	    out << "\t" << from << "\t" << to << "\t" << weight << std::endl;
	  else
	    out << "\t" << to << "\t" << from << "\t" << weight << std::endl;
	}
      };

    
    out << "Nodes: " << g.num_vertex() << std::endl;

    out << "----------------" << std::endl;
    out << " (InnerId)\tUser IDs" << std::endl;
    out << "----------------" << std::endl;
    out << "(inner)\tFROM\tTO\tWEIGHT" << std::endl;
    
    for(auto citer = g.the_inneridskeyed_map.cbegin();
     	citer != g.the_inneridskeyed_map.cend();
     	++citer)
    {
      out << "(" << citer->first << ")"; //inner_id
      const auto range =
	g.the_adjacency_data.the_outward_edges.equal_range(citer->first);
      for (auto local_itr = range.first;
      	   local_itr != range.second;
      	   ++local_itr)
	{
	  print_edge(g.get_user_id(citer->first),
		     g.get_user_id(local_itr->second->from()),
		     g.get_user_id(local_itr->second->to()),
		     local_itr->second->weight(),
		     local_itr->second->direction());
      }
  }
    out << "----------------" << std::endl;
    return out;
  }
  
  //--------------------------------------------------------------------------

  std::ostream& operator<<(std::ostream &out, const BaseVertex &vertex)
  {
    out << "\nuser: " << vertex.user_id()
	<< "\tinner: " << vertex.inner_id()
	<< std::endl;
    
    return out;
  }
  
  //--------------------------------------------------------------------------

  std::ostream& operator<<(std::ostream &out, const BaseEdgePtr &edge)
  {
    out << "\n" << edge->from()
    	<< "\t" << edge->to()
    	<< "\t"	<< edge->weight()
    	<< "\t";
    const EdgeDirection & aux_dir = edge->direction();
    if (aux_dir==EdgeDirection::FROM_TO)
      out << "FROM_TO";
    else
      out << "BOTH";
    out << std::endl;

    return out;
  }
  
  //--------------------------------------------------------------------------


} //end-of namespace path_finding
