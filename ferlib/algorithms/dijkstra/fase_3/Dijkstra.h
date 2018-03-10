#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits>       // std::numeric_limits
#include <list>

namespace dijkstra_algorithm {
  
  class BaseGraph;
  class ConcreteGraph;
  struct BaseDijkstraSolution;
  struct DijkstraSolution;;

  /* Data struct returning a list of vertex following a path, where
     the first value is the first node of the path */
  typedef std::list<VertexId> VertexPath;

  const TypeDistance TYPEDISTANCE_INFINITE = 
    std::numeric_limits<TypeDistance>::infinity();


  /* Función de optimización:   std::function<void (int)> func */

  
  /**************************************************************************/
  /** @class Dijkstra

     @brief Dijkstra algorithm implementation.



@warning clase Dijkstra requiere template. No funciona la herencia de
las funciones 'shortest...' pq dependen de la impl. interna de las
est. datos (i.e. adj en Concrete)

  */
  /*
  class Dijkstra
  {
  public:

    //@ brief Calculation of all the shortest paths from start
    //	to all the other vertex of the graph.
    ////
    //@param graph the graph to apply Dijkstra.
    //	@param start the initial vertex of the path
    //	@return The distance from start to all the other vertex.
    
       virtual void shortest_path(const BaseGraph &graph, 
		       const VertexId &start,
		       const VertexId &target)=0;
       //    @fn void shortest_paths(const BaseGraph &graph, int start);
       //	
       //	@ brief Calculation of all the shortest paths from start
       //	to all the other vertex of the graph.

       //	@param graph the graph to apply Dijkstra.
       //	@param start the initial vertex of the path
       //	@return The distance from start to all the other vertex.
    virtual void shortest_paths
      (const BaseGraph &graph, const VertexId &start)=0;

  };
*/


  /**************************************************************************/
  /** @class DijkstraConcrete

      @brief Dijkstra algorithm implementation.

@warning clase Dijkstra requiere template. No funciona la herencia de
las funciones 'shortest...' pq dependen de la impl. interna de las
est. datos (i.e. adj en Concrete)

  */

  //  class DijkstraConcrete: public Dijkstra // see waring above
  class DijkstraConcrete
  {
  public:

    /** @ brief Calculation of all the shortest paths from start
	to all the other vertex of the graph.

	@param graph the graph to apply Dijkstra.
	@param start the initial vertex of the path
	@return The distance from start to all the other vertex.
    */
    DijkstraSolution shortest_path(const ConcreteGraph &graph, 
				   const VertexId &start,
				   const VertexId &target);


    /** @fn void shortest_paths(const BaseGraph &graph, int start);
	
	@ brief Calculation of all the shortest paths from start
	to all the other vertex of the graph.

	@param graph the graph to apply Dijkstra.
	@param start the initial vertex of the path
	@return The distance from start to all the other vertex.
    */
    // void shortest_paths(const ConcreteGraph &graph, const VertexId &start);


    /* see waring above */
    /* void shortest_paths(const BaseGraph &graph, const VertexId &start) */
    /* { */
    /*   (void) graph; */
    /*   (void) start; */
    /* } */

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
    /* virtual const VertexPath path()const = 0; */

    virtual void set_distance(const TypeDistance &newval) = 0;

    virtual void push_front(const VertexId & newval) = 0;

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
    //const VertexPath path()const { return the_path;}

    
    void set_distance(const TypeDistance &newval) 
    { the_total_distance = newval; }

    void push_front(const VertexId & newval) {the_path.push_front(newval);}

  private:

    TypeDistance the_total_distance;
    VertexPath the_path;
  };



  /**************************************************************************/

  std::ostream& operator<<(std::ostream &, const BaseDijkstraSolution &);

  
} //end-of dijkstra_algorithm

#endif
