
//pathfinding lib. interface
#include <types.h>
#include <path_finding_facade.h>


#include <string>
#include <iostream>
#include <chrono>


// Test functions 
void example_wiki(const unsigned int &MAX_NUM_NODOS,
		  const unsigned int &TEST_NUM_ITERATIONS);


int main()
{
  /// @test Test of use
  example_wiki(1, 1);



  /** @test performance tests

      @test example_wiki [1]

      solution sub-graph size = explored nodes = 6 nodes, (*)

      solution: 
      Distance (cost): 20
      Shortest-Path's size (n. of vertex): 4
      Shortest-Path: 11 -> 33 -> 66 -> 55


     (*) The rest of the nodes are never explored. They are used to
         compare the performance difference between
         InfiniteGraphUniformCostSearch and
         FiniteGraphUniformCostSearch. (see Dijkstra.h):

	 FiniteGraphUniformCostSearch: all the nodes are initialized in
	 both 'distances' & 'previous' data structs.

	 InfiniteGraphUniformCostSearch: only the explored nodes are
	 initialized in both 'distances' & 'previous' data structs.
  */

 
  // - short graphs: conclusions: short graphs => same performance
  //example_wiki(1, 1e6); // @todo probar en maquina NO virtual
  //
  // try 1:
  // 1) Testing UCS for finite graphs
  // Nodes: 11; Iterations: 1000000; Time: 17410.5 (ms) 
  // 2) Testing UCS for infinite graphs
  // Nodes: 11; Iterations: 1000000; Time: 17468.5 (ms)
  //
  // try n:
  // 1) Testing UCS for finite graphs
  // Nodes: 11; Iterations: 1000000; Time: 17620.5 (ms) 
  // 2) Testing UCS for infinite graphs
  // Nodes: 11; Iterations: 1000000; Time: 17263.6 (ms)



  // - very large graphs: conclusions: InfiniteGraphUniformCostSearch is better
  //example_wiki(1e6,1); // @todo probar en maquina NO virtual
  //
  // 1) Testing UCS for finite graphs
  // Nodes: 999911; Iterations: 1; Time: 3859.93 (ms)
  // 2) Testing UCS for infinite graphs
  // Nodes: 999911; Iterations: 1; Time: 3485.5 (ms)


  
  // - intermediate graphs: conclusions: ??? @todo probar en maquina NO virtual
  //example_wiki(1000,1);
  //
  // 1) Testing UCS for finite graphs
  // Nodes: 1021; Iterations: 1; Time: 1.XXX (ms) 
  // 2) Testing UCS for infinite graphs
  // Nodes: 1021; Iterations: 1; Time: 1.XXX (ms) 

  return 0;
}

//---------------------------------------------------------------------------

void example_wiki(const unsigned int &MAX_NUM_NODOS,
		  const unsigned int &TEST_NUM_ITERATIONS)
{
  std::cout << "\n\nWikipedia's Dijkstra example on a UNDIRECTED graph "
	    << "(through interface).\n"
  	    <<  std::endl;

  std::vector<path_finding::TypeEdgeData> edges;
  edges.push_back(path_finding::TypeEdgeData("11", "22", 7.0, "edge11_22"));
  edges.push_back(path_finding::TypeEdgeData("11", "33", 9.0, "edge11_33"));
  edges.push_back(path_finding::TypeEdgeData("22", "44", 15.0, "edge22_44"));
  edges.push_back(path_finding::TypeEdgeData("44", "55", 6.0, "edge44_55"));
  edges.push_back(path_finding::TypeEdgeData("11", "66", 14.0, "edge11_66"));
  edges.push_back(path_finding::TypeEdgeData("22", "33", 10.0, "edge22_33"));
  edges.push_back(path_finding::TypeEdgeData("33", "44", 11.0, "edge33_44"));
  edges.push_back(path_finding::TypeEdgeData("33", "66", 2.0, "edge33_66"));
  edges.push_back(path_finding::TypeEdgeData("55", "66", 9.0, "edge55_66"));
  //added additional vertex (off the optimal path) to check weights of value 0.
  edges.push_back(path_finding::TypeEdgeData("66", "77", 0.0, "edge66_77"));
  //added additional isolated vertex to check that they are ignoraed by the alg.
  edges.push_back(path_finding::TypeEdgeData("88", "99", 1.0, "edge88_99"));

  //adding edges to compare on large graphs the performance difference between
  //InfiniteGraphUniformCostSearch and FiniteGraphUniformCostSearch.
  for (unsigned int inner_id = 100; inner_id < MAX_NUM_NODOS; ++inner_id) 
  {    
    edges.push_back(path_finding::TypeEdgeData
		    (std::to_string(inner_id),
		     std::to_string(inner_id+1),
		     1.0, std::string("edge"+std::to_string(inner_id))));
  }
  
  path_finding::PathFindingSolutionData solution;
  
  std::cout << "\n1) Testing UCS for finite graphs" << std::endl;
  auto start = std::chrono::steady_clock::now();   // record start time
  for (unsigned int times = 0; times < TEST_NUM_ITERATIONS; ++times) 
  {
    solution = dijkstra_shortest_path_undirected_graph("11", "55", edges);
  }
  auto end = std::chrono::steady_clock::now();
  std::cout << "Vertex Distance from Source" << std::endl;
  std::cout << solution << std::endl;
  std::chrono::duration<double> diff = end-start;
  std::clog << "Nodes: " << edges.size()
  	    << "; Iterations: " << TEST_NUM_ITERATIONS 
  	    << "; Time: "
	    << diff.count() * 1000 <<  " (ms) " << std::endl;

  

  std::cout << "\n2) Testing UCS for infinite graphs" << std::endl;
  start = std::chrono::steady_clock::now();   // record start time
  for (unsigned int times = 0; times < TEST_NUM_ITERATIONS; ++times) 
  {
    solution =
      dijkstra_shortest_path_undirected_infinite_graph("11", "55", edges);    
  }
  end = std::chrono::steady_clock::now();
  std::cout << "Vertex Distance from Source" << std::endl;
  std::cout << solution << std::endl;
  diff = end-start;
  std::clog << "Nodes: " << edges.size()
	    << "; Iterations: " << TEST_NUM_ITERATIONS 
	    << "; Time: "
	    << diff.count() * 1000 <<  " (ms) " << std::endl;
  
  
  
//   Solución esperada:
// Vertex Distance from Source
// Distance (cost): 20
// Shortest-Path's size (n. of vertex): 4
// Shortest-Path: 11 -> 33 -> 66 -> 55
  
}
