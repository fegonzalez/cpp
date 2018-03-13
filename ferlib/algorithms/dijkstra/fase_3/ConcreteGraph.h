#ifndef CONCRETE_GRAPH_H
#define CONCRETE_GRAPH_H

#include "BaseGraph.h"

#include <iosfwd>
#include <unordered_map>
#include <vector>
#include <cassert>


namespace dijkstra_algorithm {


  struct ConcreteEdge;
  struct ConcreteVertex;

  

  /**************************************************************************/
  /** @struct ConcreteVertex

      @brief A Graph's Vertex.

      @param the_user_id: id known by the user (creator) of the Vertex. 
      Used to communications User-Graph.
  
      @param the_inner_id: id to be used internally in the Graph logic.
  */
  struct ConcreteVertex: public BaseVertex
  {
    friend class ConcreteGraph;
    friend std::ostream& operator<<(std::ostream &, const BaseVertex &);

    /* friend class DirectedConcreteGraph; */
    /* friend class UnirectedConcreteGraph; */
    
  public:
	
    UserVertexId user_id()const {return the_user_id;}
    InnerVertexId inner_id()const {return the_inner_id;}

    void add_neighbor(BaseEdgePtr edge)
    { the_neighbourhood.push_back(edge); }

    /// @todo
    /* const std::shared_ptr<TypeNeighbors> neighbors()const */
    /* { return the_neighbourhood; } */
	
  protected:
    	
    /* ConcreteVertex(InnerVertexId inner, */
    /* 		   UserVertexId user, */
    /* 		   BaseEdgePtr edge) */
    /*   :the_inner_id(inner), the_user_id(user) */
    /* { the_neighbourhood.push_back(edge); } */

    
    ConcreteVertex(InnerVertexId inner,
    		   UserVertexId user)
      :the_inner_id(inner), the_user_id(user) {}

    
    // data area
	
  private:
    
    InnerVertexId the_inner_id = NOVERTEXID;
    UserVertexId the_user_id = the_inner_id;

    /** @ brief OPTIMIZATION: quick access to neighbors

	- undirected edges: edge.direction() == EdgeDirection::BOTH

	- directed outward edges: edge.direction() == EdgeDirection::FROM_TO and
	edge.from() == the_inner_id

	- directed inward edges: edge.direction() == EdgeDirection::FROM_TO and
	edge.to() == the_inner_id


	//typedef std::vector<BaseEdgePtr> TypeNeighbors;

    
	// optional optim: split the_neighbourhood in three vectors: 
	// inwards_only, outwards_only, undirected

    */
    TypeNeighbors the_neighbourhood{};

  };


  /**************************************************************************/
  /** @struct ConcreteEdge : public BaseEdge
   */
  struct ConcreteEdge : public BaseEdge
  {

    friend std::ostream& operator<<(std::ostream &, const BaseEdge &);

    
  public:

    InnerVertexId from()const { return the_from;}
    InnerVertexId to()const { return the_to;}
    TypeDistance weight()const { return the_weight;} 
    EdgeDirection direction()const { return the_direction;}

    ConcreteEdge(InnerVertexId from,
		 InnerVertexId to,
		 TypeDistance weight,
		 EdgeDirection direction)
      :the_from(from),
      the_to(to),
      the_weight(weight),      
      the_direction(direction)
      { }

    // data area 

  private: 
    InnerVertexId the_from;
    InnerVertexId the_to;
    TypeDistance the_weight;      
    EdgeDirection the_direction;
  };
  
  
  
  /**************************************************************************/
  /** class ConcreteGraph 

      Common data and functions to implement a directed/undirected  graph: 
  */
  /**************************************************************************/
  class ConcreteGraph: public BaseGraph
  {

    friend std::ostream& operator<<(std::ostream &, const ConcreteGraph &);
	
    friend class Dijkstra;
  
  public:
    
    
    void add_edge
      (const UserVertexId &from, 
       const UserVertexId &to, 
       const TypeDistance & weight);
    
    void add_vertex(const UserVertexId &id);
 
    
    /// @return the number of vertex of the Graph
    unsigned int num_vertex()const {return the_vertex_map.size();}

    //std::list<AdjPair> *adjac() const {return adj;};

    bool validUserVertex(const UserVertexId &id)const
    {
      return(the_useridskeyed_map.find(id) not_eq the_useridskeyed_map.end());
    }


    //inline 
    InnerVertexId get_inner_id(const UserVertexId &id)const;

    inline UserVertexId get_user_id(const InnerVertexId &id)const;
    
  protected:

    typedef BaseVertexPtr VertexValue;
    typedef BaseEdgePtr EdgeValue;
    typedef BaseEdgePtr AdjacEdge;  

    
    unsigned int num_inner_indexes()const {return the_vertex_map.size();}
    unsigned int num_edges()const { return the_edge_map.size(); }
    bool repeated_user_edge(const UserVertexId &from,
			    const UserVertexId to)const;


    /** @brief create & add a NEW edge to the data structures.
    */
    virtual BaseEdgePtr insert_edge(const InnerVertexId &from,
				    const InnerVertexId &to, 
				    const TypeDistance & weight) = 0;


    /** @brief create & add the adjacency information to the data structures
     */
    virtual void insert_adjacency(const InnerVertexId &from,
				 const InnerVertexId &to, 
				 const AdjacEdge &edge) = 0;
    
    // data area
    
  protected:

    // Keeping the relation between user & inner vertex_ids
    // Two maps to optimize the searchs operations.
    std::unordered_map<UserVertexId, InnerVertexId> the_useridskeyed_map{};
    std::unordered_map<InnerVertexId, UserVertexId> the_inneridskeyed_map{};

    // edge storage, keyed by edge id.
    std::unordered_map<EdgeId, EdgeValue> the_edge_map{};

    // vertex storage, keyed by their id.
    std::unordered_map<InnerVertexId, VertexValue> the_vertex_map{};
    
    // The adjacency data
    struct
    {
      std::unordered_multimap<InnerVertexId, AdjacEdge> the_outward_edges{};
      std::unordered_multimap<InnerVertexId, AdjacEdge> the_inward_edges{};
    } the_adjacency_data;
    //
    // std::list<AdjPair> *adj; // edges: adjacency list 
    // ARRAY of 'num_vertex()' std::list<AdjPair>

  };

  
  /**************************************************************************/
  /** class DirectedConcreteGraph 

      Directed graph specialization of a ConcreteGraph.
  */
  /**************************************************************************/

  class DirectedConcreteGraph: public ConcreteGraph
  {

    friend std::ostream& operator<<(std::ostream &, const ConcreteGraph &);
    friend class Dijkstra;

    
  public:
    
    explicit DirectedConcreteGraph() = default;
    explicit DirectedConcreteGraph(const DirectedConcreteGraph&) = delete;
    //    ~DirectedConcreteGraph() = default;

    
  protected:
    
    
    /** @brief create & add a NEW edge to the data structures.
    */
    virtual BaseEdgePtr insert_edge(const InnerVertexId &from,
				    const InnerVertexId &to, 
				    const TypeDistance & weight);
    //				    const EdgeDirection & dir);


    /** @brief create & add the adjacency information to the data structures
     */
    inline void insert_adjacency(const InnerVertexId &from,
				 const InnerVertexId &to, 
				 const AdjacEdge &edge);
  };

  
  /**************************************************************************/
  /** class UndirectedConcreteGraph 

      Undirected graph specialization of a ConcreteGraph.
  */
  /**************************************************************************/

  class UndirectedConcreteGraph: public ConcreteGraph
  {

    friend std::ostream& operator<<(std::ostream &, const ConcreteGraph &);
    friend class Dijkstra;

  public:
    
    explicit UndirectedConcreteGraph() = default;
    explicit UndirectedConcreteGraph(const UndirectedConcreteGraph&) = delete;
    //    ~UndirectedConcreteGraph() = default;

    
  protected:
    
    
    /** @brief create & add a NEW edge to the data structures.
    */
    virtual BaseEdgePtr insert_edge(const InnerVertexId &from,
				    const InnerVertexId &to, 
				    const TypeDistance & weight);
    //				    const EdgeDirection & dir);


    /** @brief create & add the adjacency information to the data structures
     */
    inline void insert_adjacency(const InnerVertexId &from,
				 const InnerVertexId &to, 
				 const AdjacEdge &edge);
  };
  
    
} //end-of dijkstra_algorithm
 
#endif
