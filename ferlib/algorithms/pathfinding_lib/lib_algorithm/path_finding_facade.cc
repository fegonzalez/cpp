
#include "types.h"
#include "path_finding_facade.h"
#include "BaseGraph.h"
#include "Dijkstra.h"


#include <iostream>
#include <vector>

namespace path_finding {

  
  PathFindingSolutionData dijkstra_shortest_path_directed_graph
  (const UserVertexId &start_node,
   const UserVertexId &target_node,
   const std::vector<TypeEdgeData> & edges)
  {
    PathFindingSolutionData retval;

    DirectedGraph g;
    for (const TypeEdgeData& edgei : edges) 
      g.add_edge(edgei);
    
    // std::cout << g << std::endl;    

    Dijkstra alg; 
    DijkstraSolution solution = alg.shortest_path(g, start_node, target_node);
    retval.the_path = (*solution.path());
    retval.the_total_distance = solution.total_distance();
    
    return retval;
  }

  //---------------------------------------------------------------------------

  PathFindingSolutionData dijkstra_shortest_path_undirected_graph
  (const UserVertexId &start_node,
   const UserVertexId &target_node,
   const std::vector<TypeEdgeData> & edges)
  {
    PathFindingSolutionData retval;
    
    UndirectedGraph g;
    for (const TypeEdgeData& edgei : edges) 
      g.add_edge(edgei);
    
    //std::cout << g << std::endl;    
    
    Dijkstra alg; 
    DijkstraSolution solution = alg.shortest_path(g, start_node, target_node);
    retval.the_path = (*solution.path());
    retval.the_total_distance = solution.total_distance();
    
    return retval;
  }
                 
} //end-of path_finding
