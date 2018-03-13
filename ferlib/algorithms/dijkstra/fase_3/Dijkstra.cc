
  /** @file Dijkstra.cc

      @brief Implementation of Dijkstra algorithm 

      (https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
  */


#include "BaseGraph.h"
#include "Dijkstra.h"
#include <iostream>
#include <algorithm>
#include <iterator>    // std::begin
#include <functional>  // std::bind
#include <utility> // std::pair
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <cassert>


//#define DEBUG_MODE_DIJKSTRA true


namespace dijkstra_algorithm {

  /** @return result_path: list of nodes from the src to the target node. 

      e.g. wikipedia:  1 -> 3 -> 6 -> 5

      @ error is start or target are not vertex of the graph.
  */
  DijkstraSolution Dijkstra::shortest_path
   (const ConcreteGraph &graph,
    const UserVertexId &user_start,
    const UserVertexId &user_target)
  {
    assert(graph.validUserVertex(user_start) and
	   graph.validUserVertex(user_target));

    
    // 1) initialization step 

    typedef std::pair<InnerVertexId, TypeDistance> AdjPair;  
    //  typedef std::pair<BaseVertex&, TypeDistance> AdjPair;
    
    DijkstraSolution retval;

    InnerVertexId start = graph.get_inner_id(user_start);
    InnerVertexId target = graph.get_inner_id(user_target);

    // distances: total (OPTIMAL) distance from 'start' to all the rest.
    /// @todo OPTIM: ir metiendo SOLAMENE los nodos visitados
    std::unordered_map<InnerVertexId, TypeDistance> distances{};

    for(auto citer = graph.the_vertex_map.cbegin();
	citer != graph.the_vertex_map.cend();
	++citer)
    {
      distances[citer->first] = TYPEDISTANCE_INFINITE;
    }
    distances[start] = TYPEDISTANCE_ZERO;


    /// previous: prev-vertex in the optimal-path for every vertex in graph.
    /// @todo OPTIM: ir metiendo SOLAMENE los nodos visitados
    std::unordered_map<InnerVertexId, InnerVertexId> previous{};

    for(auto citer = graph.the_vertex_map.cbegin();
	citer != graph.the_vertex_map.cend();
	++citer)
    {
      previous[citer->first] = NOVERTEXID;
    }


    ///@param candidates: next nodes to visit (priority_queue)
    std::priority_queue< AdjPair,
			 std::vector <AdjPair> , 
			 std::greater<AdjPair> > candidates;

    // optimization: only insert the first vertex to visit (start)
    candidates.push(std::make_pair(TYPEDISTANCE_ZERO, start));

    // optimization: exit upon success
    bool target_found = false;

    //optimization: avoid process vertex already visited (old candidates)
    std::unordered_set<InnerVertexId> visited;

    
    
    // 2) Discovery step: find best path

#ifdef DEBUG_MODE_DIJKSTRA    
    std::clog << "\nDiscovery step: find best path" << std::endl;
#endif

    while (not candidates.empty())
    {
      
#ifdef DEBUG_MODE_DIJKSTRA
      std::clog << "\ncandidates:   " ;
      std::clog << "size: " << candidates.size();
      std::clog << " ; top (most priority): " << candidates.top().second;
      //warning: iteration over a priority queue without pop() is not possible

      std::clog << "\ndistances:" ;
      std::for_each(std::begin(distances), std::end(distances), 
		    [](const std::pair<InnerVertexId, TypeDistance> &val)
		    {std::clog << " " << val.second; });      
      std::clog << std::endl ;
      
      std::clog << "previous: " ;
      std::for_each(std::begin(previous), std::end(previous), 
		    [](const std::pair<InnerVertexId, InnerVertexId> &val)
		    { std::clog << " " << val.second; }); 
      std::clog << std::endl ;

      std::clog << "visited: " ;
      std::for_each(std::begin(visited), std::end(visited), 
		    [](const InnerVertexId &val)
		    { std::clog << " " << val; }); 
      std::clog << std::endl ;

      // std::clog << "\n Press ENTER ... " << std::flush;  
      // std::cin.ignore();
#endif


      // The first vertex in pair is the minimum distance vertex
      // (note.- distance must be first item in pair)
      InnerVertexId new_candidate = candidates.top().second;
      candidates.pop();

#ifdef DEBUG_MODE_DIJKSTRA
      std::clog << "new_candidate: " << new_candidate << std::endl;
#endif
     
      auto citr_visited = visited.find(new_candidate);
      if(citr_visited == visited.end())
      {
	visited.insert(new_candidate);
      }
      else
      {
#ifdef DEBUG_MODE_DIJKSTRA
	std::clog << "already visited: " << new_candidate << std::endl;
#endif
	continue;
      }

      //optimization: stop if target vertex reached
      if(new_candidate == target)
      {
#ifdef DEBUG_MODE_DIJKSTRA
	std::clog << "target_found!" << std::endl;
#endif
	target_found = true;
	break;
      }
	
      const auto range =
	graph.the_adjacency_data.the_outward_edges.equal_range(new_candidate);
      for (auto itr = range.first;
      	   itr != range.second;
      	   ++itr)      
      {
	// extracting the current minimum

	/**@warning It has been discarded a possible optimization
	   based on detect and ignore neighbors already handle in the
	   opposite direction:

	   - i.e. the other vertex in an unordered graph.
	   - i.e. previous directed vertex: neighbor->new_candidate.

	   The reasons are:
	   
	   a) Because the current logic is correct: it will never end in the
	   re-addition of a former candidate.

	   b) And the cost of this detection could be greater than
	     the current calculations.
	 */
	InnerVertexId neighbor = NOVERTEXID;

	// case: directed graph
	if(itr->second->direction() == EdgeDirection::FROM_TO)
	{
	  neighbor = itr->second->to();
	}
	else // case: undirected graph
	{
	  if(itr->second->from() == new_candidate)
	  {
	    neighbor = itr->second->to();
	  }
	  else
	  {
	    neighbor = itr->second->from();
	  }
	}

	TypeDistance weight = itr->second->weight();

#ifdef DEBUG_MODE_DIJKSTRA
	std::clog << "+ neighbor " << neighbor << " ; ";
	std::clog << "dist(" << new_candidate << ", " << neighbor << "): ";
	std::clog << weight << std::endl;
#endif
	assert(weight > TYPEDISTANCE_ZERO); //Dijkstra restriction [1]

			
	// relax phase: update shortest path (new_candidate -> neighbor)

	assert(distances.find(new_candidate) not_eq distances.end());
	assert(distances.find(neighbor) not_eq distances.end());
        TypeDistance neighbor_distance = distances[new_candidate] + weight;
	if (neighbor_distance < distances[neighbor])
	{
	  distances[neighbor] = neighbor_distance;
	  previous[neighbor] = new_candidate;
	  candidates.push(std::make_pair(distances[neighbor], neighbor));

#ifdef DEBUG_MODE_DIJKSTRA
	  std::clog << "better_distance found! = ";
	  std::clog << neighbor_distance << std::endl;
	  std::clog << "candidates.push( " << distances[neighbor];
	  std::clog << ", " << neighbor << ")"  << std::endl;
#endif
	}
      }
    }//end_while
    

    // 3) Rebuild (set-solution) step

    assert(distances.find(target) not_eq distances.end());
    retval.set_distance(distances[target]);
    
    if(target_found)
    {
      InnerVertexId current = target;
      while (current not_eq start)
      {
    	///@todo almacenar user_id, no inner_id = user_map.find(current)
    	retval.push_front(current);
	assert(previous.find(current) not_eq previous.end());
    	current = previous[current];

	/// @todo removeme por si hay infinite loops
	//    	assert(retval.path()->size() < 100);
      }
      retval.push_front(start);     
    }

     return retval;
  }

  //--------------------------------------------------------------------------

  std::ostream& operator<<(std::ostream &out, 
			   const BaseDijkstraSolution &value)
  {
    out << "Distance (cost): " << value.total_distance() << std::endl;
    out << "Shortest-Path's size (n. of vertex): " << value.path()->size() 
	<< std::endl;
    out << "Shortest-Path:   ";
     
    InnerVertexId last_element = NOVERTEXID;
    if(not value.path()->empty())
    {
      last_element = value.path()->back();
    }

    std::for_each(std::begin(*value.path()),
		  std::end(*value.path()),
		  [&out, last_element](const InnerVertexId & id)
    {
      // static int num_veces = 0; /// @todo removeme: prevent infinite loops

      /// @bug Printing inner ids,  user ids required (get_user_id(id);)
      out << id;
      if(not (id==last_element)) { out << " -> "; }
      
      // assert(++num_veces < 30); /// @todo removeme: prevent infinite loops
    });
  
    return out;
  }

    
} //end-of dijkstra_algorithm
