
//pathfinding lib. interface
#include <types.h>
#include <path_finding_facade.h>


#include <string>
#include <iostream>
#include <chrono>

// [1] dijkstra-wikipedia - https://en.wikipedia.org/wiki/Dijkstra's_algorithm


// Test functions 
void example_wiki(const unsigned int &MAX_NUM_NODOS,
		  const unsigned int &TEST_NUM_ITERATIONS);


int main()
{
  /// @test Test of use
  example_wiki(1, 1);


  /** @test performance tests

      @warning This aren't good performance times because it has been
      tested (by executing the loop directly at "alg->shortest_path"
      on path_finding_facade.cc), that most of the test time is used
      on copying the vector of edges to the graph, rather than in the
      algorithm execution itself:
      e.g. example_wiki(1e6, 10): from here: 32977.8 (ms) ; alg.: 3064.33 (ms)
      e.g. example_wiki(1e6, 1000):                       ; alg.: 3090.93 (ms)


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
  // Nodes: 21; Iterations: 1000000; Time: 11917 (ms) 

  // - very large graphs:
  // example_wiki(1e6,1); //  example_wiki(1e6, 10); 
  // example_wiki(1e6, 1); 
  //
  // 1) Testing UCS.
  // Nodes: 1999821; Iterations: 1; Time: 2958.73 (ms)
  //
  // 1) Testing UCS.
  // Nodes: 1999821; Iterations: 10; Time: 32977.8 (ms) 

  
  // - intermediate graphs: 
  //example_wiki(600,1);
  //
  // 1) Testing UCS.
  // Nodes: 1021; Iterations: 1; Time: 0.582559 (ms)

  return 0;
}

//---------------------------------------------------------------------------

void example_wiki(const unsigned int &MAX_NUM_NODOS,
		  const unsigned int &TEST_NUM_ITERATIONS)
{
  std::cout << "\n\nWikipedia's Dijkstra example on a DIRECTED graph "
	    << "(through interface).\n"
  	    <<  std::endl;

  std::vector<path_finding::TypeEdgeData> edges;
  edges.push_back(path_finding::TypeEdgeData("11", "22", 7.0, "edge11_22"));
  edges.push_back(path_finding::TypeEdgeData("22", "11", 7.0, "edge22_11"));
  edges.push_back(path_finding::TypeEdgeData("11", "33", 9.0, "edge11_33"));
  edges.push_back(path_finding::TypeEdgeData("33", "11", 9.0, "edge33_11"));
  edges.push_back(path_finding::TypeEdgeData("22", "44", 15.0, "edge22_44"));
  edges.push_back(path_finding::TypeEdgeData("44", "22", 15.0, "edge44_22"));
  edges.push_back(path_finding::TypeEdgeData("44", "55", 6.0, "edge44_55"));
  edges.push_back(path_finding::TypeEdgeData("55", "44", 6.0, "edge55_44"));  
  edges.push_back(path_finding::TypeEdgeData("11", "66", 14.0, "edge11_66"));
  edges.push_back(path_finding::TypeEdgeData("66", "11", 14.0, "edge66_11"));
  edges.push_back(path_finding::TypeEdgeData("22", "33", 10.0, "edge22_33"));
  edges.push_back(path_finding::TypeEdgeData("33", "22", 10.0, "edge33_22"));
  edges.push_back(path_finding::TypeEdgeData("33", "44", 11.0, "edge33_44"));
  edges.push_back(path_finding::TypeEdgeData("44", "33", 11.0, "edge44_33"));
  edges.push_back(path_finding::TypeEdgeData("33", "66", 2.0, "edge33_66"));
  edges.push_back(path_finding::TypeEdgeData("66", "33", 2.0, "edge66_33"));
  edges.push_back(path_finding::TypeEdgeData("55", "66", 9.0, "edge55_66"));
  edges.push_back(path_finding::TypeEdgeData("66", "55", 9.0, "edge66_55"));
  //added additional vertex (off the optimal path) to check weights of value 0.
  edges.push_back(path_finding::TypeEdgeData("66", "77", 0.0, "edge66_77"));
  edges.push_back(path_finding::TypeEdgeData("77", "66", 0.0, "edge77_66"));
  //added additional isolated vertex to check that they are ignoraed by the alg.
  edges.push_back(path_finding::TypeEdgeData("88", "99", 1.0, "edge88_99"));
  //adding edges to compare on large graphs the performance
  for (unsigned int inner_id = 100; inner_id < MAX_NUM_NODOS; ++inner_id) 
  {    
    edges.push_back(path_finding::TypeEdgeData
		    (std::to_string(inner_id),
		     std::to_string(inner_id+1),
		     1.0, std::string("edge"+std::to_string(inner_id))));
    
    edges.push_back(path_finding::TypeEdgeData
		    (std::to_string(inner_id+1),
		     std::to_string(inner_id),
		     1.0, std::string("edge"+std::to_string(inner_id)+"bis")));
  }
  
  path_finding::PathFindingSolutionData solution;
  
  std::cout << "\n1) Testing UCS." << std::endl;
  auto start = std::chrono::steady_clock::now();   // record start time
  for (unsigned int times = 0; times < TEST_NUM_ITERATIONS; ++times) 
  {
    solution = dijkstra_shortest_path_directed_graph("11", "55", edges);
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
