#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits>       // std::numeric_limits
#include <list>

namespace path_finding {
  
  class Graph;
  struct BaseDijkstraSolution;
  struct DijkstraSolution;

  
  const TypeDistance TYPEDISTANCE_INFINITE = 
    std::numeric_limits<TypeDistance>::infinity();


  
  /**************************************************************************/
  /** @class DijkstraStrategy

      @brief Dijkstra's algorithm implementation interface.
  */

  class DijkstraStrategy
  {
  public:

    /** @ brief Calculation of all the shortest paths from start
	to all the other vertex of the graph.

	@param graph the graph to apply Dijkstra.
	@param start the initial vertex of the path
	@return The distance from start to all the other vertex.

    */
    virtual DijkstraSolution shortest_path(const Graph &graph, 
					   const UserVertexId &start,
					   const UserVertexId &target) = 0;
  };


  class UniformCostSearch: public DijkstraStrategy
  {
  public:

    virtual DijkstraSolution shortest_path(const Graph &graph, 
					   const UserVertexId &start,
					   const UserVertexId &target);
  };



  /**************************************************************************/

  /** @struct BaseDijkstraSolution

     @brief Interface class. Used to return the value of a call to
     Dijstra::shortest_path.

     @param the_path: list of vertex of the shortest path. The first
     value of the list is the 'start' node, and the last one is the
     'target' vertex.

     @warning the ids in the path represent the "user_ids" in a
     BaseVertex, not the "inner_ids".
    
     @sa wikipedia: 1 -> 3 -> 6 -> 5

     @retval: the_path is empty when a valid path wasn't found.
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
