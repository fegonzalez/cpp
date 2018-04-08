
#include "types.h"
#include "path_finding_facade.h"
#include "BaseGraph.h"
#include "Dijkstra.h"


#include <iostream>
#include <vector>
#include <memory> // std::shared_ptr


namespace path_finding {

  namespace{

    typedef std::shared_ptr<DijkstraStrategy> DijkstraPtr;
  
    enum class GraphSize{FINITE, INFINITE};
  
    PathFindingSolutionData directed_ucs
      (const UserVertexId &start_node,
       const UserVertexId &target_node,
       const std::vector<TypeEdgeData> & edges,
       const GraphSize & size)
    {
      PathFindingSolutionData retval;

      DirectedGraph g;
      for (const TypeEdgeData& edgei : edges) 
	g.add_edge(edgei);
    
      // std::cout << g << std::endl;

      DijkstraPtr alg;
      if(size == GraphSize::INFINITE)
	alg = DijkstraPtr(new InfiniteGraphUniformCostSearch());
      else
	alg = DijkstraPtr(new FiniteGraphUniformCostSearch());

      DijkstraSolution solution=alg->shortest_path(g, start_node, target_node);
      retval.the_path = (*solution.path());
      retval.the_total_distance = solution.total_distance();
    
      return retval;
    }

    //--------------------------------------------------------------------------

    PathFindingSolutionData undirected_ucs
      (const UserVertexId &start_node,
       const UserVertexId &target_node,
       const std::vector<TypeEdgeData> & edges,
       const GraphSize & size)
    {
      PathFindingSolutionData retval;
    
      UndirectedGraph g;
      for (const TypeEdgeData& edgei : edges) 
	g.add_edge(edgei);
    
      //std::cout << g << std::endl;

      DijkstraPtr alg;
      if(size == GraphSize::INFINITE)
	alg = DijkstraPtr(new InfiniteGraphUniformCostSearch());
      else
	alg = DijkstraPtr(new FiniteGraphUniformCostSearch());
    
      DijkstraSolution solution=alg->shortest_path(g, start_node, target_node);
      retval.the_path = (*solution.path());
      retval.the_total_distance = solution.total_distance();
    
      return retval;
    }
  
  } //nonamed namespace

  
  //---------------------------------------------------------------------------
  
  PathFindingSolutionData dijkstra_shortest_path_directed_graph
  (const UserVertexId &start_node,
   const UserVertexId &target_node,
   const std::vector<TypeEdgeData> & edges)
  {
    return directed_ucs(start_node,
			target_node,
			edges,
			GraphSize::FINITE);
  }

  //---------------------------------------------------------------------------

  PathFindingSolutionData dijkstra_shortest_path_undirected_graph
  (const UserVertexId &start_node,
   const UserVertexId &target_node,
   const std::vector<TypeEdgeData> & edges)
  {
    return undirected_ucs(start_node,
			  target_node,
			  edges,
			  GraphSize::FINITE);
  }
  
  //---------------------------------------------------------------------------
  
  PathFindingSolutionData dijkstra_shortest_path_directed_infinite_graph
  (const UserVertexId &start_node,
   const UserVertexId &target_node,
   const std::vector<TypeEdgeData> & edges)
  {
    return directed_ucs(start_node,
			target_node,
			edges,
			GraphSize::INFINITE);
  }

  //---------------------------------------------------------------------------

  PathFindingSolutionData dijkstra_shortest_path_undirected_infinite_graph
  (const UserVertexId &start_node,
   const UserVertexId &target_node,
   const std::vector<TypeEdgeData> & edges)
  {
    return undirected_ucs(start_node,
			  target_node,
			  edges,
			  GraphSize::INFINITE);
  }
 
  
} //end-of path_finding
