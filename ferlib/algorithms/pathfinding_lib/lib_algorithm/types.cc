#include "types.h"
#include <iostream>
#include <algorithm>

namespace path_finding {


  std::ostream& operator<<(std::ostream &out, 
			   const PathFindingSolutionData &value)
  {    
    out << "Distance (cost): " << value.the_total_distance << std::endl;
    out << "Shortest-Path's size (n. of vertex): " << value.the_path.size() 
    	<< std::endl;
    out << "Shortest-Path:   ";
     
    UserVertexId last_element = NOVERTEXUSERID;
    if(not value.the_path.empty())
      last_element = value.the_path.back();

    std::for_each(std::begin(value.the_path),
    		  std::end(value.the_path),
    		  [&out, last_element](const UserVertexId & id)
    		  {
    		    out << id;
    		    if(not (id==last_element)) { out << " -> "; }      
    		  });

    out << "\nShortest-Path edges:   ";
    std::for_each(std::begin(value.the_path_edges),
    		  std::end(value.the_path_edges),
    		  [&out](const UserEdgeId & id)
    		  {
    		    out << id << " ";
    		  });

    return out;
  }



} //end-of path_finding
  
