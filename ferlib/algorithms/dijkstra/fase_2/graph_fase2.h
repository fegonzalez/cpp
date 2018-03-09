#ifndef GRAPH_FASE2_H
#define GRAPH_FASE2_H

#include "graph.h"

#include <iosfwd>
#include <list>
#include <utility> // std::pair


namespace dijkstra_algorithm {


  /**************************************************************************/

  ///@todo FIXME: use the proper adj. data structure
  //
  //  typedef std::pair<BaseVertex&, TypeDistance> AdjPair;
  typedef std::pair<VertexId, TypeDistance> AdjPair;


  /**************************************************************************/
  /** @struct BaseVertex

      @brief A Graph's Vertex.

      @param the_user_id: id known by the user (creator) of the Vertex. 
                          Used to communications User-Graph.
  
      @param the_id: id to be used internally in the Graph logic.
  */
  struct Fase2Vertex: public BaseVertex
  {
  public:
    
    VertexId user_id()const {return the_user_id;}
    VertexId inner_id()const {return the_id;}

  protected: 

    VertexId the_id;               
    VertexId the_user_id = the_id;
  };


  /**************************************************************************/
  /** @struct Fase2Edge
      
      - from(): origin vertex of the edge.
      - to(): destination vertex of the edge.
      - weight(): distance (cost) value of the edge. Negative values allowed.
      - direction(): direction of the edge (directed or undirected G.)
  */
  struct Fase2Edge : public BaseEdge
  {
    VertexId from()const { return the_from;}
    VertexId to()const { return the_to;}
    TypeDistance weight()const { return the_weight;} 
    EdgeDirection direction()const { return the_direction;}

  protected: 
    VertexId the_from;
    VertexId the_to;
    TypeDistance the_weight;      
    EdgeDirection the_direction = EdgeDirection::BOTH;    
  };


  /**************************************************************************/
  /** class Fase2Graph 

      Directed/ undirected  graph: 
      - vertex:                    TODO
      - edges: adjacency list      TODO

      [ Example 
      v1 -> v2: add_edge(v1, v2, weight_v1-v2)
      v2 -> v1: add_edge(v2, v1, weight_v2_v1)
      end example ]
  */
  /**************************************************************************/
  class Fase2Graph: public BaseGraph
  {

    friend std::ostream& operator<<(std::ostream &, const Fase2Graph &);

  public:
    
    Fase2Graph(unsigned int num_vertex);  // Constructor

    ~Fase2Graph();
 
    /**	@warning Generic Graph, thus negative weight are allowed */
    virtual void add_edge
      (const VertexId &from, 
       const VertexId &to, 
       const TypeDistance & weight,
       const EdgeDirection & dir = EdgeDirection::FROM_TO);



    /** @return the number of vertex of the Graph */
    unsigned int num_vertex()const {return the_num_vertex;}

    std::list<AdjPair> *adjac() const {return adj;};


  protected:

    unsigned int the_num_vertex;    // No. of vertices

    std::list<AdjPair> *adj; // edges: adjacency list 
    // ARRAY of 'the_num_vertex' std::list<AdjPair>





    /** Map of edge weights, keyed by edge id */
    //  boost::unordered_map<int, double> m_edgeWeights;

    /** Map of all vertices, keyed by their id */
    //   boost::unordered_map<int, BaseVertex> m_vertices;
  
  };

} //end-of dijkstra_algorithm
 
#endif
