#ifndef BASEGRAPH_H
#define BASEGRAPH_H

#include <iosfwd>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory> // std::shared_ptr


#include "types.h"

namespace path_finding {

  struct BaseVertex;
  struct BaseEdge;
  struct Edge;
  struct Vertex;

  
  typedef unsigned int VertexId;
  typedef unsigned int EdgeId;
  //  typedef double TypeDistance;

  // alias
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
  const InnerVertexId NOVERTEXID = 0;
  const EdgeId NOEDGEID = 0;
  const TypeDistance TYPEDISTANCE_ZERO = static_cast<TypeDistance>(0);


  
  /**************************************************************************/
  /** class BaseGraph 

      Interface for Directed or undirected graphs used as inputs for
      path-finding algorithms.

  */
  /**************************************************************************/
  class BaseGraph
  {

  public:
    
    virtual ~BaseGraph(){};
 

   /**	@brief add a new edge between to vertexes of the graph.

	@error If an edge between the two vertexes already exists.

	@warning If any of the vertex 'from' and/or 'to' does not
	exists yet, they also are created, thus this is the fastest
	way to fill the graph.	

	@warning Generic Graph, thus negative weight are allowed 	
   */    
    virtual void add_edge
      (const UserVertexId &from, 
       const UserVertexId &to, 
       const TypeDistance & weight,
       const UserEdgeId &edge_user_id)=0;

    virtual void add_edge
      (const TypeEdgeData &edge)=0;


   /**	
	@warning Recommended to add isolated vertex to the graph.

	@error If the vertex already exists.
   */        
    virtual void add_vertex(const UserVertexId &id)=0;


    /** @return the number of vertex of the Graph */
    virtual unsigned int num_vertex()const=0;

    /// @return true: if the vertex, as is known by the user of the
    /// algorithm, exists in the graph.
    virtual bool validUserVertex(const UserVertexId &id)const=0;    
  };


  
  /**************************************************************************/
  /** class Graph 

      Common data and functions to implement a directed/undirected graph
      Abstract class.
  */
  /**************************************************************************/
  class Graph: public BaseGraph
  {

    friend std::ostream& operator<<(std::ostream &, const Graph &);
	
    friend class UniformCostSearch;
  
  public:
       
    void add_edge
      (const UserVertexId &from, 
       const UserVertexId &to, 
       const TypeDistance & weight,
       const UserEdgeId &edge_user_id);

    virtual void add_edge
      (const TypeEdgeData &edge);

    void add_vertex(const UserVertexId &id);

    unsigned int num_vertex()const {return the_vertex_map.size();}


    /// @return true: if the vertex exists in the graph.
    bool validUserVertex(const UserVertexId &id)const
    {
      return(the_useridskeyed_map.find(id) not_eq the_useridskeyed_map.end());
    }

    InnerVertexId get_inner_id(const UserVertexId &id)const;
    UserVertexId get_user_id(const InnerVertexId &id)const;
    
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
				    const TypeDistance & weight,
				    const UserEdgeId &edge_user_id) = 0;


    /** @brief create & add the adjacency information to the data structures
     */
    virtual void insert_adjacency(const InnerVertexId &from,
				 const InnerVertexId &to, 
				 const AdjacEdge &edge) = 0;
    
    // data area
    
  protected:

    // Keeping the relation between user & inner vertex_ids
    // Two maps to optimize the search operations.
    std::unordered_map<UserVertexId, InnerVertexId> the_useridskeyed_map{};
    std::unordered_map<InnerVertexId, UserVertexId> the_inneridskeyed_map{};

    // edge storage, keyed by edge id.
    std::unordered_map<EdgeId, EdgeValue> the_edge_map{};

    // vertex storage, keyed by their id.
    std::unordered_map<InnerVertexId, VertexValue> the_vertex_map{};
    
    struct
    {
      std::unordered_multimap<InnerVertexId, AdjacEdge> the_outward_edges{};
      std::unordered_multimap<InnerVertexId, AdjacEdge> the_inward_edges{};
    } the_adjacency_data;

  };


  
  /**************************************************************************/
  /** class DirectedGraph 

      Directed graph specialization of a Graph.
  */
  /**************************************************************************/

  class DirectedGraph: public Graph
  {

    friend std::ostream& operator<<(std::ostream &, const Graph &);
    friend class Dijkstra;

    
  public:
    
    explicit DirectedGraph() = default;
    explicit DirectedGraph(const DirectedGraph&) = delete;
    DirectedGraph& operator=(const DirectedGraph&) = delete;
    explicit DirectedGraph(const DirectedGraph&&) = delete;
    DirectedGraph& operator=(const DirectedGraph&&) = delete;
    
  protected:
    
    BaseEdgePtr insert_edge(const InnerVertexId &from,
			    const InnerVertexId &to, 
			    const TypeDistance & weight,
			    const UserEdgeId &edge_user_id);

    inline void insert_adjacency(const InnerVertexId &from,
				 const InnerVertexId &to, 
				 const AdjacEdge &edge);
  };

  
  /**************************************************************************/
  /** class UndirectedGraph 

      Undirected graph specialization of a Graph.
  */
  /**************************************************************************/

  class UndirectedGraph: public Graph
  {

    friend std::ostream& operator<<(std::ostream &, const Graph &);
    friend class Dijkstra;

  public:
    
    explicit UndirectedGraph() = default;
    explicit UndirectedGraph(const UndirectedGraph&) = delete;
    UndirectedGraph& operator=(const UndirectedGraph&) = delete;
    explicit UndirectedGraph(const UndirectedGraph&&) = delete;
    UndirectedGraph& operator=(const UndirectedGraph&&) = delete;

  protected:
    
    BaseEdgePtr insert_edge(const InnerVertexId &from,
			    const InnerVertexId &to, 
			    const TypeDistance & weight,
			    const UserEdgeId &edge_user_id);

    inline void insert_adjacency(const InnerVertexId &from,
				 const InnerVertexId &to, 
				 const AdjacEdge &edge);
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
    
    virtual ~BaseVertex(){}

    virtual UserVertexId user_id()const = 0;
    virtual InnerVertexId inner_id()const = 0;
    
    /// @brief (Optimization) Add an edge to connect to a neighbor vertex
    virtual void add_neighbor(BaseEdgePtr edge) = 0;


    /// @todo ?
    //  virtual const std::shared_ptr<TypeNeighbors> neighbors()const = 0;
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


  /**************************************************************************/
  /** @struct Vertex
  */
  struct Vertex: public BaseVertex
  {
    friend class Graph;
    friend std::ostream& operator<<(std::ostream &, const BaseVertex &);
    
  public:
	
    UserVertexId user_id()const {return the_user_id;}
    InnerVertexId inner_id()const {return the_inner_id;}

    void add_neighbor(BaseEdgePtr edge)
    { the_neighbourhood.push_back(edge); }

    /// @todo?
    /* const std::shared_ptr<TypeNeighbors> neighbors()const */
    /* { return the_neighbourhood; } */

	
  protected:
    
    Vertex(InnerVertexId inner,
    		   UserVertexId user)
      :the_inner_id(inner), the_user_id(user) {}

    
    // data area
	
  private:
    
    InnerVertexId the_inner_id = NOVERTEXID;
    UserVertexId the_user_id = std::to_string(the_inner_id);

    /** @brief OPTIMIZATION: quick access to neighbors

	- undirected-graph edges: edge.direction() == EdgeDirection::BOTH
	
	- directed-graph edges: edge.direction() == EdgeDirection::BOTH
	
	   - outward edge iff: edge.from() == the_inner_id

	   - inward edge iff: edge.to() == the_inner_id

        - loop edge (both directed & undirected): edge.from() == edge.to()


	// optional optim: split the_neighbourhood in three vectors: 
	// inwards_only, outwards_only, undirected
    */
    TypeNeighbors the_neighbourhood{};
  };


  /**************************************************************************/
  /** @struct Edge : public BaseEdge
   */
  struct Edge : public BaseEdge
  {
    friend std::ostream& operator<<(std::ostream &, const BaseEdge &);
    
  public:

    InnerVertexId from()const { return the_from;}
    InnerVertexId to()const { return the_to;}
    TypeDistance weight()const { return the_weight;} 
    EdgeDirection direction()const { return the_direction;}

    Edge(InnerVertexId from,
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

} //end-of path_finding
 
#endif
