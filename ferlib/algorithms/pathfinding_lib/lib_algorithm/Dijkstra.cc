
  /** @file Dijkstra.cc

      @brief Implementation of Dijkstra algorithm 

      [dijkstra-wikipedia] https://en.wikipedia.org/wiki/Dijkstra's_algorithm

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


namespace path_finding {


  /**************************************************************************/  
  /* InfiniteGraphUniformCostSearch class implementation                    */
  /**************************************************************************/

  void InfiniteGraphUniformCostSearch::init_distances
  (const Graph &graph,
   const InnerVertexId &start,
   const InnerVertexId &target)
  {
    (void) graph;
    distances[start] = TYPEDISTANCE_ZERO;
    distances[target] = TYPEDISTANCE_INFINITE; 
  }

  //--------------------------------------------------------------------------

  // Complexity (distances.find): Constant on average, worst case
  // linear in the size of the container.
  // (http://en.cppreference.com/w/cpp/container/unordered_map/find)
  void InfiniteGraphUniformCostSearch::init_distance
  (const InnerVertexId &vertex)
  {
    if(distances.find(vertex) == distances.end())
      distances[vertex] = TYPEDISTANCE_INFINITE;
  }

  //--------------------------------------------------------------------------

  // Complexity: Constant on average, worst case linear
  // in the size of the container.
  void InfiniteGraphUniformCostSearch::init_previous
  (const Graph &graph,
   const InnerVertexId &start,
   const InnerVertexId &target)
  {
    (void) graph;    
    previous[start] = NOVERTEXID;
    previous[target] = NOVERTEXID;
  }

  
  /**************************************************************************/  
  /* FiniteGraphUniformCostSearch class implementation                      */
  /**************************************************************************/

  // Complexity (for loop): linear.
  void FiniteGraphUniformCostSearch::init_distances
  (const Graph &graph,
   const InnerVertexId &start,
   const InnerVertexId &target)
  {
    for(auto citer = graph.the_vertex_map.cbegin();
    	citer != graph.the_vertex_map.cend();
    	++citer)
    {
      distances[citer->first] = TYPEDISTANCE_INFINITE;
    }
    distances[start] = TYPEDISTANCE_ZERO;
    distances[target] = TYPEDISTANCE_INFINITE;
  }

  //--------------------------------------------------------------------------

  void FiniteGraphUniformCostSearch::init_previous
  (const Graph &graph,
   const InnerVertexId &start,
   const InnerVertexId &target)
  {
    for(auto citer = graph.the_vertex_map.cbegin();
    	citer != graph.the_vertex_map.cend();
    	++citer)
    {
      previous[citer->first] = NOVERTEXID;
    }    
    previous[start] = NOVERTEXID;
    previous[target] = NOVERTEXID;
  }

  
  /**************************************************************************/  
  /* UniformCostSearch class implementation                                 */
  /**************************************************************************/

  DijkstraSolution UniformCostSearch::shortest_path
   (const Graph &graph,
    const UserVertexId &user_start,
    const UserVertexId &user_target)
  {

    assert(graph.validUserVertex(user_start) and
	   graph.validUserVertex(user_target));

    
    // 1) initialization step 

    typedef std::pair<InnerVertexId, TypeDistance> AdjPair;  
    
    DijkstraSolution retval;

    InnerVertexId start = graph.get_inner_id(user_start);
    InnerVertexId target = graph.get_inner_id(user_target);

    init_distances(graph, start, target);
    init_previous(graph, start, target);


    ///@param candidates: next nodes to explore (priority_queue)
    std::priority_queue< AdjPair,
			 std::vector <AdjPair> , 
			 std::greater<AdjPair> > candidates;

    // optimization: only insert the first vertex to explore (start)
    candidates.push(std::make_pair(TYPEDISTANCE_ZERO, start));

    // optimization: exit upon success
    bool target_found = false;

    //optimization: avoid process vertex already explored (old candidates)
    std::unordered_set<InnerVertexId> explored;

    
    
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

      std::clog << "explored: " ;
      std::for_each(std::begin(explored), std::end(explored), 
		    [](const InnerVertexId &val)
		    { std::clog << " " << val; }); 
      std::clog << std::endl ;

      // std::clog << "\n Press ENTER ... " << std::flush;  
      // std::cin.ignore();
#endif


      InnerVertexId new_candidate = candidates.top().second;
      candidates.pop();


#ifdef DEBUG_MODE_DIJKSTRA
      std::clog << "new_candidate: " << new_candidate << std::endl;
#endif

      
      if(new_candidate == target)
      {
#ifdef DEBUG_MODE_DIJKSTRA
	std::clog << "target_found!" << std::endl;
#endif
	target_found = true;
	break;
      }

      
      auto citr_explored = explored.find(new_candidate);
      if(citr_explored == explored.end())
      {
	explored.insert(new_candidate);
	init_distance(new_candidate);	
      }
      else //ignoring new candidates already explored
      {
#ifdef DEBUG_MODE_DIJKSTRA
	std::clog << "already explored: " << new_candidate << std::endl;
#endif
	continue;  
      }

      //check neighbors
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

	init_distance(neighbor);	
	TypeDistance weight = itr->second->weight();
	assert(weight >= TYPEDISTANCE_ZERO); //Dijkstra restriction [1]
	
#ifdef DEBUG_MODE_DIJKSTRA
	std::clog << "+ neighbor " << neighbor << " ; ";
	std::clog << "dist(" << new_candidate << ", " << neighbor << "): ";
	std::clog << weight << std::endl;
#endif
		
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
      }//end neighbors
    }//end_while
    

    // 3) Rebuild (set-solution) step

    assert(distances.find(target) not_eq distances.end());
    retval.set_distance(distances[target]);
    
    if(target_found)
    {
      InnerVertexId current = target;
      while (current not_eq start)
      {
    	retval.push_front(graph.get_user_id(current));
	assert(previous.find(current) not_eq previous.end());
    	current = previous[current];
      }
      retval.push_front(user_start);
    }

#ifdef DEBUG_MODE_DIJKSTRA
    if(not target_found)
    {
      std::clog << "\n\nerror: 'target' not reached from 'start' node! \n\n";
    }
#endif

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
     
    UserVertexId last_element = NOVERTEXUSERID;
    if(not value.path()->empty())
      last_element = value.path()->back();

    std::for_each(std::begin(*value.path()),
		  std::end(*value.path()),
		  [&out, last_element](const UserVertexId & id)
    {
      out << id;
      if(not (id==last_element)) { out << " -> "; }      
    });
  
    return out;
  }

} //end-of path_finding
