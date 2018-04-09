#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "BaseGraph.h"
#include <types.h>

#include <limits>       // std::numeric_limits
#include <list>

namespace path_finding {
  
  //class Graph;
  struct BaseDijkstraSolution;
  struct DijkstraSolution;

  
  const TypeDistance TYPEDISTANCE_INFINITE = 
    std::numeric_limits<TypeDistance>::infinity();


  
  /**************************************************************************/
  /** @class DijkstraStrategy

      @brief Dijkstra's algorithm implementation interface.

      [1] dijkstra-wikipedia - 
          https://en.wikipedia.org/wiki/Dijkstra's_algorithm

  */
  /**************************************************************************/

  class DijkstraStrategy
  {
  public:

    /** @ brief Calculation of all the shortest paths from 'user_start'
	to all the other vertex of the graph.

	@param graph: the graph to apply Dijkstra.
	@param user_start: the initial vertex of the path.
	@return The distance from 'user_start' to 'user_target'.
	@return list of nodes from the start to the target node. 
	@ error if 'user_start' or 'user_target' are not vertex of the graph.
    */
    virtual DijkstraSolution shortest_path(const Graph &graph, 
					   const UserVertexId &user_start,
					   const UserVertexId &user_target) = 0;
  };

  
  /**************************************************************************/
  /** @class UniformCostSearch

      @brief Dijkstra's optimization: implementing the uniform-cost
      search algorithm. [1]
  */
  /**************************************************************************/
  
  class UniformCostSearch: public DijkstraStrategy
  {
  public:
    DijkstraSolution shortest_path(const Graph &graph, 
				   const UserVertexId &user_start,
				   const UserVertexId &user_target);

  protected:
    
    virtual void init_distances(const Graph &graph,
				const InnerVertexId &start,
				const InnerVertexId &target) = 0;
    
    virtual void init_distance(const InnerVertexId &vertex) = 0;


    virtual void init_previous(const Graph &graph,
				const InnerVertexId &start,
				const InnerVertexId &target) = 0;
      
    //data area

    /// @param distances: total (OPTIMAL) distance from 'start' to the rest.
    typedef std::unordered_map<InnerVertexId, TypeDistance> TDistances;
    TDistances distances{};

    		   
    /** @param previous: prev-vertex in the optimal-path for any
	vertex in graph. 
	(e.g.  Graph (1)-->(2) : previous[1] = NOVERTEXID; previous[2] = 1; )
    */
    typedef std::unordered_map<InnerVertexId, InnerVertexId> TPrevious;
    TPrevious previous{};
    
  };
  

  /**************************************************************************/
  /** @class InfiniteGraphUniformCostSearch

      @brief 'previous' and 'distances' are set ONLY to the explored
      vertexes in the graph; which allows the execution of UCS on
      infinite graphs or those too large to represent in memory.
  */
  /**************************************************************************/
  
  class InfiniteGraphUniformCostSearch: public UniformCostSearch
  {
  protected:
    
    virtual void init_distances(const Graph &graph,
			const InnerVertexId &start,
			const InnerVertexId &target);

    virtual void init_distance(const InnerVertexId &vertex);

    virtual void init_previous(const Graph &graph,
				const InnerVertexId &start,
				const InnerVertexId &target);

  };

  /**************************************************************************/
  /** @struct BaseDijkstraSolution

     @brief Interface class. Used to return the value of a call to
     Dijstra::shortest_path.

     @param path(): list of vertex of the shortest path. The first
     value of the list is the 'user_start' vertex, and the last one is
     the 'user_target' vertex.

     @warning the ids in the path represent the "user_ids" in a
     BaseVertex, not the "inner_ids".
    
     @sa wikipedia: 1 -> 3 -> 6 -> 5

     @retval: the path is empty when a valid path wasn't found.
  */
  /**************************************************************************/
  struct BaseDijkstraSolution
  {    
  public:
    virtual TypeDistance total_distance()const = 0;

    virtual const VertexPath * path()const = 0;

    virtual void set_distance(const TypeDistance &newval) = 0;

    virtual void push_front(const UserVertexId & newval) = 0;

    virtual ~BaseDijkstraSolution() {}
  };


  /**************************************************************************/
  /** @struct DijkstraSolution

     @brief Basic implementation of a BaseDijkstraSolution
  */
  /**************************************************************************/

  struct DijkstraSolution: public BaseDijkstraSolution
  {
  public:

    TypeDistance total_distance()const { return the_total_distance;}
    const VertexPath *path()const { return &the_path;}
    
    void set_distance(const TypeDistance &newval) 
    { the_total_distance = newval; }

    void push_front(const UserVertexId & newval) 
    { the_path.push_front(newval); }

  private:

    TypeDistance the_total_distance;
    VertexPath the_path;
  };


  /**************************************************************************/

  std::ostream& operator<<(std::ostream &, const BaseDijkstraSolution &);

  
} //end-of path_finding

#endif
