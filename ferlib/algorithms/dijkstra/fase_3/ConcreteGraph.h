#ifndef CONCRETE_GRAPH_H
#define CONCRETE_GRAPH_H

#include "BaseGraph.h"

#include <iosfwd>
#include <unordered_map>
//#include <unordered_multimap>
#include <vector>

//#include <utility> // std::pair



#include <list>


namespace dijkstra_algorithm {


  /**************************************************************************/

  ///@todo FIXME: use the proper adj. data structure
  //
  //  typedef std::pair<BaseVertex&, TypeDistance> AdjPair;
  //  typedef std::pair<InnerVertexId, TypeDistance> AdjPair;

  struct ConcreteEdge;
  struct ConcreteVertex;

  /**************************************************************************/
  /** class ConcreteGraph 

      Directed/ undirected  graph: 
      - vertex:                    TODO
      - edges: adjacency list      TODO

      [ Example 
      v1 -> v2: add_edgev1, v2, weight_v1-v2)
      v2 -> v1: add_edge(v2, v1, weight_v2_v1)
      end example ]
  */
  /**************************************************************************/
  class ConcreteGraph: public BaseGraph
  {

    friend std::ostream& operator<<(std::ostream &, const ConcreteGraph &);

  public:
    
    ConcreteGraph(unsigned int num_vertex);  // Constructor

    ~ConcreteGraph();
    
   /**	@warning If any of the vertex 'from' and/or 'to' does not
	exists yet, they also are created, thus this is the fastest
	way to fill the graph.

	@warning Generic Graph, thus negative weight are allowed 
	
	@error If the edge already exists.
   */
    virtual void add_edge
      (const UserVertexId &from, 
       const UserVertexId &to, 
       const TypeDistance & weight,
       const EdgeDirection & dir = EdgeDirection::FROM_TO);

    virtual void add_vertex(const UserVertexId &id);
 
    
    /// @return the number of vertex of the Graph
    unsigned int num_vertex()const {return the_num_vertex;}

    //std::list<AdjPair> *adjac() const {return adj;};


  protected:

    unsigned int next_inner_index()const {return the_num_vertex;}

    
    // data area
    
  protected:
    
    unsigned int the_num_vertex = 0; // curent num. of vertex in the graph

    // Keeping the relation between user & inner vertex_ids
    // Two maps to optimize the searchs operations.
    std::unordered_map<UserVertexId, InnerVertexId> the_useridskeyed_map;
    std::unordered_map<InnerVertexId, UserVertexId> the_inneridskeyed_map;

    // vertex storage, keyed by their id.
    typedef BaseVertexPtr VertexValue;
    std::unordered_map<InnerVertexId, VertexValue> the_vertex_map;

    // edge storage, keyed by edge id.
    typedef BaseEdgePtr EdgeValue;
    std::unordered_map<EdgeId, EdgeValue> the_edge_map;
  
    // The adjacency data
    typedef BaseEdgePtr AdjacEdge;  
    typedef struct
    {
      std::unordered_multimap<InnerVertexId, AdjacEdge> the_outward_edges;
      std::unordered_multimap<InnerVertexId, AdjacEdge> the_inward_edges;
    } the_adjacency_data;
    //
    // std::list<AdjPair> *adj; // edges: adjacency list 
    // ARRAY of 'the_num_vertex' std::list<AdjPair>

  };

    
  /**************************************************************************/
  /** @struct BaseVertex

      @brief A Graph's Vertex.

      @param the_user_id: id known by the user (creator) of the Vertex. 
      Used to communications User-Graph.
  
      @param the_inner_id: id to be used internally in the Graph logic.
  */
  struct ConcreteVertex: public BaseVertex
  {
    friend class ConcreteGraph;
    
  public:
    
    UserVertexId user_id()const {return the_user_id;}

    /// @todo
    /* const std::shared_ptr<TypeNeighbors> neighbors()const */
    /* { return the_neighbourhood; } */

    
  protected:
    
    InnerVertexId inner_id()const {return the_inner_id;}
	
    

    // data area
	
  private:	
    InnerVertexId the_inner_id;
    UserVertexId the_user_id = the_inner_id;

    //typedef std::vector<std::shared_ptr<BaseEdge> > TypeNeighbors; 
    TypeNeighbors the_neighbourhood{}; // OPTIMIZATION: quic access to neighbors
  };


  /**************************************************************************/
  /** @struct ConcreteEdge : public BaseEdge
   */
  struct ConcreteEdge : public BaseEdge
  {
    InnerVertexId from()const { return the_from;}
    InnerVertexId to()const { return the_to;}
    TypeDistance weight()const { return the_weight;} 
    EdgeDirection direction()const { return the_direction;}

    
    // data area 

  private: 
    InnerVertexId the_from;
    InnerVertexId the_to;
    TypeDistance the_weight;      
    EdgeDirection the_direction = EdgeDirection::FROM_TO;
  };



} //end-of dijkstra_algorithm
 
#endif
