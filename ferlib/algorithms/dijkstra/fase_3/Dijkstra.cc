#include "common.h"
#include "BaseGraph.h"
#include "Dijkstra.h"
#include "ConcreteGraph.h"

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
  */

  DijkstraSolution DijkstraConcrete::shortest_path(const ConcreteGraph &graph, 
						const VertexId &start,
						const VertexId &target)
  {
    // 1) initialization step 
    
    DijkstraSolution retval;

    // distances: current total distance from the src vertex to all the rest.
    std::vector<TypeDistance> distances(graph.num_vertex(), 
					TYPEDISTANCE_INFINITE);
    distances[start] = TYPEDISTANCE_ZERO;


    /// previous: current prev. vertex in the optimal path for every
    //           vertex in the graph.
    //
    /// @todo OPTIM: usar map para ir metiendo SOLAMENE los nodos visitados
    // pasar a usar map 
    std::vector<VertexId> previous (graph.num_vertex(), NOVERTEXID);


    ///@param candidates: next nodes to visit (priority_queue)
    ///
    ///   @todo VERIFICAR el orden de los params y su uso [2].commentarios
    ///
    std::priority_queue< AdjPair,
			 std::vector <AdjPair> , 
			 std::greater<AdjPair> > candidates;


    // optimization: only insert the first vertex to visit (start)
    candidates.push(std::make_pair(0.0, start));  // AL REVEŚ ???


    // optimization: exit upon success
    bool target_found = false;


    //optimization: avoid process vertex already visited (old candidates)
    std::unordered_set<VertexId> visited;

    
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
		    [](const TypeDistance &val){std::clog << " " << val; }); 
      std::clog << std::endl ;
      std::clog << "previous: " ;
      std::for_each(std::begin(previous), std::end(previous), 
		    [](const VertexId &val) { std::clog << " " << val; }); 
      std::clog << std::endl ;
#endif
      // The first vertex in pair is the minimum distance
      // vertex, extract it from priority queue.
      // vertex label is stored in second of pair (it
      // has to be done this way to keep the vertices
      // sorted distance (distance must be first item
      // in pair)
      VertexId new_candidate = candidates.top().second; // VertexId
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
      
	///@todo 
	//
	// if (already_visited(neighbor)))
	// continue;
	//
	///\todo VERIFICAR OPTIMIZACIÓN siguiente:
	// 
	// if(visited[new_candidate])  // aquí, no en candidate pq empiezo solo con 'start' como candidato.
	// 	continue;
	// visited[new_candidate]=true;




      //optimization: stop if target vertex reached
      if(new_candidate == target)
      {
#ifdef DEBUG_MODE_DIJKSTRA
	std::clog << "target_found!" << std::endl;
#endif
	target_found = true;
	break;
      }
      
      //
      ///\todo VERIFICAR OPTIMIZACIÓN siguiente:
      // 
      // if(visited[new_candidate])
      // 	continue;
      // visited[new_candidate]=true;


      // for each neighbor of new_candidate

      /*

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


      
      
      for (auto itr = graph.adjac()[new_candidate].cbegin();
	   itr != graph.adjac()[new_candidate].cend();
	   ++itr)
      {
	// extracting the current minimum
	VertexId neighbor = (*itr).first;
	TypeDistance weight = (*itr).second;

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
      }
    }//end_while


    // 3) Rebuild (set-solution) step
    retval.set_distance(distances[target]);
    
    if(target_found)
    {
      VertexId current = target;
      while (current != start)
      {
	///@todo almacenar user_id, no inner_id = user_map.find(current)
	retval.push_front(current);
	current = previous[current];

	assert(retval.path()->size() < 10);
      }
      retval.push_front(start);     
    }
    
     return retval;
  }


  //--------------------------------------------------------------------------
  /* FOM source to ALL the rest */
  /*
  void DijkstraConcrete::shortest_paths(const ConcreteGraph &graph, 
				     const VertexId &start)
  {
    // next nodes to visit: priority_queue
    std::priority_queue< AdjPair, 
			 std::vector <AdjPair> , 
			 std::greater<AdjPair> > candidates;
 
    // Create a vector for distancesances and initialize all
    // distancesances as infinite (TYPEDISTANCE_INFINITE)
    std::vector<TypeDistance> distances(graph.num_vertex(), 
					TYPEDISTANCE_INFINITE);
 
    // Insert source itself in priority queue and initialize
    // its distance as 0.
    candidates.push(std::make_pair(0.0, start));
    distances[start] = 0;
 
    // Discovery step: find best path
    while (!candidates.empty())
      {
	// The first vertex in pair is the minimum distance
	// vertex, extract it from priority queue.
	// vertex label is stored in second of pair (it
	// has to be done this way to keep the vertices
	// sorted distance (distance must be first item
	// in pair)
      VertexId new_candidate = candidates.top().second;
      candidates.pop();

 
	// 'itr' is used to get all adjacent vertices of a vertex
	for (auto itr = graph.adjac()[new_candidate].cbegin();  //, end = v.end();
	     itr != graph.adjac()[new_candidate].cend();        // itr != end;
	     ++itr)
	  {
	    // Get vertex label and weight of current adjacent of u.
	    VertexId v = (*itr).first;
	    TypeDistance weight = (*itr).second;
	    //assert(weight >0); //!\warning weights MUST be non-negative [1]
	
 
	    //  If there is shorted path to v through u.
	    if (distances[v] > distances[new_candidate] + weight)
	      {
		// Updating distance of v
		distances[v] = distances[new_candidate] + weight;
		candidates.push(std::make_pair(distances[v], v));
	      }
	  }
      }
 
    // Get solution:
    std::cout << "Vertex   Distance from Source" << std::endl;
    for (unsigned int loopi = 0; loopi < graph.num_vertex(); ++loopi)
      std::cout << loopi << "\t\t " << distances[loopi] << std::endl;

  }
  */

  //--------------------------------------------------------------------------

  std::ostream& operator<<(std::ostream &out, 
			   const BaseDijkstraSolution &value)
  {
    out << "Distance (cost): " << value.total_distance() << std::endl;
    out << "Shortest-Path's size (n. of vertex): " << value.path()->size() 
	<< std::endl;
    out << "Shortest-Path: ";
     
    VertexId last_element = NOVERTEXID;
    if(not value.path()->empty())
    {
      last_element = value.path()->back();
    }

    std::for_each(std::begin(*value.path()),
		  std::end(*value.path()),
		  [&out, last_element](const VertexId & id)
    {
      //      static int num_veces = 0;
      out << id;
      if(not (id==last_element)) { out << " -> "; }
      //      assert(++num_veces < 30);
    });
    
    return out;
  }
    

} //end-of dijkstra_algorithm
