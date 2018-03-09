#ifndef GRAPH_H
#define GRAPH_H

#include "common.h"
#include <iosfwd>



namespace dijkstra_algorithm {

  typedef unsigned int VertexId;
  typedef double TypeDistance;

  //optimization: for undirected graphs, avoiding duplicate edges.
  //
  enum class EdgeDirection{FROM_TO, // directed graph
                           BOTH};   // undirected graph

  const VertexId NOVERTEXID = 0;
  const TypeDistance TYPEDISTANCE_ZERO = 0.0;
  /* const TypeDistance TYPEDISTANCE_INFINITE =  */
  /*   std::numeric_limits<TypeDistance>::infinity(); */


  /**************************************************************************/
  /** @struct BaseVertex

      @brief A Graph's Vertex.

      - user_id(): id known by the user (creator) of the Vertex. 
      Used to communications User-Graph.
  
      - inner_id(): id to be used internally in the Graph logic.
  */
  struct BaseVertex
  {
  public:
    
    virtual VertexId user_id()const = 0;
    virtual VertexId inner_id()const = 0;

    virtual ~BaseVertex(){}
  };
 
  /**************************************************************************/
  /** @struct BaseEdge
      
      - from(): origin vertex of the edge.
      - to(): destination vertex of the edge.
      - weight(): distance (cost) value of the edge. Negative values allowed.
      - direction(): direction of the edge (directed or undirected G.)
  */
  struct BaseEdge
  {

    virtual VertexId from()const = 0;
    virtual VertexId to()const = 0;
    virtual TypeDistance weight()const = 0;      
    virtual EdgeDirection direction()const = 0;    

    virtual ~BaseEdge(){};
  };

  /**************************************************************************/
  /** class BaseGraph 

      Directed / undirected  graph: 
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
      (const VertexId &from, 
       const VertexId &to, 
       const TypeDistance & weight,
       const EdgeDirection & dir = EdgeDirection::FROM_TO)=0;


    /* ????  add_vertex required   ??? */



    // getters

    /** @return the number of vertex of the Graph */
    virtual unsigned int num_vertex()const=0;


    /**
     * Tries to return a pointer to the vertex referenced by user_id
     *
     * @param user_id: id known by the user (creator) of the Vertex. 
     *        Used to communications User-Graph.
     *
     * @return a pointer to the vertex.
     */
    //BaseVertex* get_vertex(const VertexId & user_id)=0;
    /** ESE_VIEJO_PRO impl. */
    /* BaseVertex* AlgorithmGraph::getVertex(const int &nodeId) */
    /* { */
    /*     BaseVertex &v_vertex = m_vertices[nodeId]; */
    /*     if (v_vertex.getId() != 0) */
    /*     { */
    /*         // Vertex already existed, return it, if it's open */
    /*         return v_vertex.isOpen() ? &v_vertex : 0; */
    /*     } else */
    /*     { */
    /*         // Vertex didn't exist until fetch, upate its id */
    /*         v_vertex.setId(nodeId); */
    /*         // Default vertex state is open, there's no need to check */
    /*         return &v_vertex; */
    /*     } */
    /* } */

  };

} //end-of dijkstra_algorithm
 
#endif
