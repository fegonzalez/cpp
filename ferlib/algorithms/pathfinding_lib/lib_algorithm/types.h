/** @file types.h

    @brief Basic types of the path_finding library. Types required by
    the external users of the library (through the library interface).
*/
#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <list>

namespace path_finding {

  
  //
  // types section
  //
  
  typedef std::string UserVertexId;
  typedef std::string UserEdgeId; 
  typedef double TypeDistance;      // distance/weight of an edge.


  /* Data struct returning a list of vertex following a path, where
     the first value is the first node of the path */
  typedef std::list<UserVertexId> VertexPath;

  
  /** @struct TypeEdgeData

      @brief Edge's data.

      @param from: src vertex of the edge in directed graphs;
      one of the two edges in undirected.
      @param to: destination vertex of the edge in directed graphs;
      one of the two edges in undirected.		 
  */
  struct TypeEdgeData
  {
  TypeEdgeData(const UserVertexId &from,
	       const UserVertexId &to,
	       const TypeDistance &weight,
	       const UserEdgeId &id):
    from(from), to(to), weight(weight), id(id)
    {}

    
    UserVertexId from;
    UserVertexId to;
    TypeDistance weight;
    UserEdgeId id;
  };


  struct PathFindingSolutionData
  {
    TypeDistance the_total_distance;
    VertexPath the_path;
  };


  //
  // constants section
  //
  
  const UserVertexId NOVERTEXUSERID = "";


  //
  // fns. section
  //

  std::ostream& operator<<(std::ostream &out, 
			   const PathFindingSolutionData &value);

  
} //end-of path_finding

#endif  /* TYPES_H */
