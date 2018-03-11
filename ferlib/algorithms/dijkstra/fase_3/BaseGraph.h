#ifndef GRAPH_H
#define GRAPH_H

#include "common.h"
#include <iosfwd>
#include <vector>
#include <memory> // std::shared_ptr

namespace dijkstra_algorithm {

  struct BaseVertex;
  struct BaseEdge;

  
  typedef unsigned int VertexId;
  typedef unsigned int EdgeId;
  typedef double TypeDistance;

  // alias
  typedef VertexId UserVertexId;      // any value
  typedef VertexId InnerVertexId;     // 1, 2, ... (0 reserved as NOVERTEXID)
  //  typedef InnerVertexId FromVertexId; // 1, 2, ...
  typedef std::shared_ptr<BaseEdge> BaseEdgePtr;
  typedef std::vector<BaseEdgePtr> TypeNeighbors;
  typedef std::shared_ptr<BaseVertex> BaseVertexPtr;
 

  // types

  //optimization: for undirected graphs, avoiding duplicate edges.
  enum class EdgeDirection{FROM_TO, // directed graph
                           BOTH};   // undirected graph
    
  // initialization
  const VertexId NOVERTEXID = 0;
  const EdgeId NOEDGEID = 0;
  const TypeDistance TYPEDISTANCE_ZERO = 0.0;


  /**************************************************************************/
  /** class BaseGraph 

      Directed or undirected  graph: 
      - vertex:                    TODO
      - edges: adjacency list      TODO

      [ Example directed graph
      
        // two edges required: because weight could be different
	// Can be optimized in concrete Graph sub-classes.

	v1 -> v2: add_edge(v1, v2, weight_v1_v2, FROM_TO)
	v2 -> v1: add_edge(v2, v1, weight_v2_v1, FROM_TO)
      end example ]


      [ Example undirected graph
        v1 -- v2: add_edge(v1, v2, weight_v1_v2, BOTH)
      end example ]

  */
  /**************************************************************************/
  class BaseGraph
  {
    //    friend std::ostream& operator<<(std::ostream &, const BaseGraph &);
  public:
    
    virtual ~BaseGraph(){};
 

    /**	@warning Generic Graph, thus negative weight are allowed */
    virtual void add_edge
      (const UserVertexId &from, 
       const UserVertexId &to, 
       const TypeDistance & weight,
       const EdgeDirection & dir = EdgeDirection::FROM_TO)=0;

    virtual void add_vertex(const UserVertexId &id)=0;


    /** @return the number of vertex of the Graph */
    virtual unsigned int num_vertex()const=0;

  };

  
  /**************************************************************************/
  /** @struct BaseVertex

      @brief A Graph's Vertex.

      - user_id(): id known by the user (creator) of the Vertex. 
  
      - inner_id(): id to be used internally in the Graph logic.
  */
  struct BaseVertex
  {
  public:
    
    virtual UserVertexId user_id()const = 0;

    
    /// @todo
    //    virtual const std::shared_ptr<TypeNeighbors> neighbors()const = 0;

    virtual ~BaseVertex(){}

  protected:
    
    virtual InnerVertexId inner_id()const = 0;
  };
 
  /**************************************************************************/
  /** @struct BaseEdge

      @brief A Graph's Vertex. Inner data structure to be used
             internally in the Graph logic.

      - from(): origin vertex of the edge.
      - to(): destination vertex of the edge.
      - weight(): distance (cost) value of the edge. Negative values allowed.
      - direction(): direction of the edge (directed or undirected G.)
  */
  struct BaseEdge
  {

    virtual InnerVertexId from()const = 0;
    virtual InnerVertexId to()const = 0;
    virtual TypeDistance weight()const = 0;      
    virtual EdgeDirection direction()const = 0;    

    virtual ~BaseEdge(){};
  };

} //end-of dijkstra_algorithm
 
#endif
