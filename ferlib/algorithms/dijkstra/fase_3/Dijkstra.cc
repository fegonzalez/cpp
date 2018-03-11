#include "common.h"
#include "BaseGraph.h"
#include "ConcreteGraph.h"
#include "Dijkstra.h"
#include <iostream>
#include <algorithm>
#include <iterator>    // std::begin
#include <functional>  // std::bind
#include <utility> // std::pair
#include <queue>
#include <unordered_set>
#include <list>
#include <cassert>
//#include <limits>       // std::numeric_limits
//#include <memory> // std::unique_ptr , std::shared_ptr



//#define DEBUG_MODE_DIJKSTRA true


namespace dijkstra_algorithm {


  /** Reference docs:
      [1] https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

      [2] https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
  */
  //--------------------------------------------------------------------------


  /** @return result_path: list of nodes from the src to the target node. 

      e.g. wikipedia:  1 -> 3 -> 6 -> 5

      @ error is start or target are not nodes of the graph.


      //////////////////////////////////////
      // for each neighbor of new_candidate

     

      step 1: tengo InnerVertexID: new_candidate

modo-1:  1) the_vertex_map[new_candidate] : BaseVertex *  'cand_vertex'
             
            O(1)

         2) cand_vertex->neighbors():  todos los Edges que salen del nodo
             
            O(1)

         3) Para cada edge (ptr)           O(n)
            {
	      insertar pair(to(), weight()) en la cola de prioridad    O(cola)
            }




ESTE - ESTE - ESTE

             
modo-2  1) Para cada  Edge* en 
           the_adjacency_data.the_outward_edges[new_candidate]        O(n)
	   {
	     insertar pair(to(), weight()) en la cola de prioridad    O(cola)
	   }

  */
  DijkstraSolution DijkstraConcrete::shortest_path
   (const ConcreteGraph &graph,
    const UserVertexId &user_start,
    const UserVertexId &user_target)
  {
    bool invariant = (graph.validUserVertex(user_start) and
		      graph.validUserVertex(user_target));
    assert(invariant);

    
    // 1) initialization step 

    typedef std::pair<InnerVertexId, TypeDistance> AdjPair;  
    //  typedef std::pair<BaseVertex&, TypeDistance> AdjPair;
    

    DijkstraSolution retval;

    InnerVertexId start = graph.get_inner_id(user_start);
    InnerVertexId target = graph.get_inner_id(user_target);

    // distances: current total distance from the src vertex to all the rest.
    /// @todo OPTIM: ir metiendo SOLAMENE los nodos visitados
    std::unordered_map<InnerVertexId, TypeDistance> distances{};

    for(auto citer = graph.the_vertex_map.cbegin();
	citer != graph.the_vertex_map.cend();
	++citer)
    {
      distances[citer->first] = TYPEDISTANCE_INFINITE;
    }
    distances[start] = TYPEDISTANCE_ZERO;


    /// previous: current prev. vertex in the optimal path for every
    //           vertex in the graph.
    //
    /// @todo OPTIM: usar map para ir metiendo SOLAMENE los nodos visitados
    //
    // @bug REquiere map, no por optim, sino pq vvector usa pos. 0
    // 
    std::vector<InnerVertexId> previous (graph.num_vertex(), NOVERTEXID);


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


    while (!candidates.empty())
    {
      
#ifdef DEBUG_MODE_DIJKSTRA
      std::clog << "\ncandidates:" ;
      std::clog << "\nsize: " << candidates.size();
      std::clog << " ; top (most priority): " << candidates.top().second;
      std::clog << "\ndistances:" ;
      std::for_each(std::begin(distances), std::end(distances), 
		    [](const std::pair<InnerVertexId, TypeDistance> &val)
		    {std::clog << " " << val.second; });      
      std::clog << std::endl ;
      
      std::clog << "previous: " ;
      std::for_each(std::begin(previous), std::end(previous), 
		    [](const InnerVertexId &val) { std::clog << " " << val; }); 
      std::clog << std::endl ;
#endif


      // The first vertex in pair is the minimum distance vertex
      // (note.- distance must be first item in pair)
      InnerVertexId new_candidate = candidates.top().second; // InnerVertexId
      candidates.pop();
     
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


      
#ifdef DEBUG_MODE_DIJKSTRA
      std::clog << "new_candidate: " << new_candidate << std::endl;
#endif
      

      //optimization: stop if target vertex reached
      if(new_candidate == target)
      {
#ifdef DEBUG_MODE_DIJKSTRA
	std::clog << "target_found!" << std::endl;
#endif
	target_found = true;
	break;
      }

	
      // for (auto itr = graph.adjac()[new_candidate].cbegin();
      // 	   itr != graph.adjac()[new_candidate].cend();
      // 	   ++itr)
      const auto range =
	graph.the_adjacency_data.the_outward_edges.equal_range(new_candidate);
      for (auto itr = range.first;
      	   itr != range.second;
      	   ++itr)      
      {
	// extracting the current minimum
	InnerVertexId neighbor =  itr->second->to();
	TypeDistance weight = itr->second->weight();

#ifdef DEBUG_MODE_DIJKSTRA
	std::clog << "+ neighbor " << neighbor << " ; ";
	std::clog << "dist(" << new_candidate << ", " << neighbor << "): ";
	std::clog << weight << std::endl;
#endif
	assert(weight > TYPEDISTANCE_ZERO); //Dijkstra restriction [1]

			
	// relax phase: update shortest path (new_candidate -> neighbor)
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

      }//end_for



      //  dentro del while en alguna parte, casca
      //      assert(false);

      
      



      
    }//end_while
    
    // 3) Rebuild (set-solution) step
    retval.set_distance(distances[target]);
    
    if(target_found)
    {
      InnerVertexId current = target;
      while (current != start)
      {
    	///@todo almacenar user_id, no inner_id = user_map.find(current)
    	retval.push_front(current);
    	current = previous[current];


	/// @todo removeme por si hay infinite loops
    	assert(retval.path()->size() < 100);

	
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
    out << "Shortest-Path: ERROR!!! sacando inners-ids:   ";
     
    VertexId last_element = NOVERTEXID;
    if(not value.path()->empty())
    {
      last_element = value.path()->back();
    }

    std::for_each(std::begin(*value.path()),
		  std::end(*value.path()),
		  [&out, last_element](const VertexId & id)
    {
      static int num_veces = 0;	/// @todo removeme por si hay infinite loops

      out << id;
      if(not (id==last_element)) { out << " -> "; }

      
      assert(++num_veces < 30);	/// @todo removeme por si hay infinite loops

    });
  
    return out;
  }
    
} //end-of dijkstra_algorithm
