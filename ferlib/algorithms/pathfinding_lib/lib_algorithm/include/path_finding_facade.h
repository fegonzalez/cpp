/** @file path_finding_facade.h

    @brief Basic path_finding_facade (interface) of the path_finding library. 
*/
#ifndef PATH_FINDING_FACADE_H
#define PATH_FINDING_FACADE_H

#include "types.h"

#include <vector>

namespace path_finding {


  /***************************************************************************/
  /*shortest path functions: cost function = minimum distance from start_node*/
  /***************************************************************************/

  
  /** @brief Applies the Dijkstra algorithm on a directed (finite or
      infinite) graph to find the shortest path from 'start_node' to
      'target_node'.

      (*) infinite graphs: infinite or too large to represent in memory.

      @param start_node: the first node of the path to find.
      @param target_node: the last node of the path to find.
      @param edges: the list of edges of the graph.

      @warning The list of edges provide enough information to create
      the graph. Any node off the edge list would be irrelevant to
      find the path.
  */
  PathFindingSolutionData dijkstra_shortest_path_directed_graph
    (const UserVertexId &start_node,
     const UserVertexId &target_node,
     const std::vector<TypeEdgeData> & edges);



    /** @brief Applies the Dijkstra algorithm on an undirected (finite
      or infinite) graph to find the shortest path from 'start_node'
      to 'target_node'.

      (*) infinite graphs: infinite or too large to represent in memory.

      @param start_node: the first node of the path to find.
      @param target_node: the last node of the path to find.
      @param edges: the list of edges of the graph.

      @warning The list of edges provide enough information to create
      the graph. Any node off the edge list would be irrelevant to
      find the path.
    */    
    PathFindingSolutionData dijkstra_shortest_path_undirected_graph
    (const UserVertexId &start_node,
     const UserVertexId &target_node,
     const std::vector<TypeEdgeData> & edges);

             
    } //end-of path_finding

#endif  /* PATH_FINDING_FACADE_H */
