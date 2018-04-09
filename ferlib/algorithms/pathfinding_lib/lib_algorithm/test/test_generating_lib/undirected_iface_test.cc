
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

     @warning This aren't good performance times because it has been
     tested (by executing the loop directly at "alg->shortest_path" on
     path_finding_facade.cc), that most of the test time is used on
     copying the vector of edges to the graph, rather than in the
     algorithm execution itself:
     e.g. example_wiki(1, 1e6): here: 9673.68 (ms); alg. only(**): 453.35 (ms)
     e.g. example_wiki(1e6, 40): here: 94074.7 (ms); alg.: 2371.13 (ms)
     e.g. example_wiki(1e6, 1000):                   alg.: 2421.57 (ms) 
     e.g. example_wiki(1000, 100); here: 91.4363 (ms) ; alg.: 1.32089 (ms) 
     e.g. example_wiki(1000, 1e6); alg.: 469.888 (ms) 
     (**) include one copy of 'edges' to the graph.

     @test example_wiki [1]

     solution sub-graph size = explored nodes = 6 nodes, (*)

     solution: 
     Distance (cost): 20
     Shortest-Path's size (n. of vertex): 4
     Shortest-Path: 11 -> 33 -> 66 -> 55

     (*) The rest of the nodes are never explored. They are used to
         compare the performance in large graphs.
  */

 
  // - short graphs:
  //example_wiki(1, 1e6);
  //
  // try 1:
  // 1) Testing UCS.
  // Nodes: 11; Iterations: 1000000; Time: 9673.68 (ms) 


  // - very large graphs: 
  //example_wiki(1e6, 1); //  example_wiki(1e6, 40); 
  //
  // 1) Testing UCS.
  // Nodes: 999911; Iterations: 1; Time: 2366.98 (ms) 
  //
  // 1) Testing UCS.
  // Nodes: 999911; Iterations: 40; Time:  94074.7 (ms)


  // - intermediate graphs: 
  //example_wiki(1000, 1);  //  example_wiki(1000, 100);
  //
  // 1) Testing UCS.
  // Nodes: 911; Iterations: 1; Time: 0.97884 (ms) 
  //
  // 1) Testing UCS.
  // Nodes: 911; Iterations: 100; Time: 91.4363 (ms) 


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
  //adding edges to compare on large graphs the performance
  for (unsigned int inner_id = 100; inner_id < MAX_NUM_NODOS; ++inner_id) 
  {    
    edges.push_back(path_finding::TypeEdgeData
		    (std::to_string(inner_id),
		     std::to_string(inner_id+1),
		     1.0, std::string("edge"+std::to_string(inner_id))));
  }
  
  path_finding::PathFindingSolutionData solution;
  
  std::cout << "\n1) Testing UCS." << std::endl;
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
  
//   Solución esperada:
// Vertex Distance from Source
// Distance (cost): 20
// Shortest-Path's size (n. of vertex): 4
// Shortest-Path: 11 -> 33 -> 66 -> 55
  
}
