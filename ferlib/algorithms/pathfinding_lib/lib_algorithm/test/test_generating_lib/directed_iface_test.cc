
#include <types.h>
#include <path_finding_facade.h>

#include <string>
#include <iostream>
#include <chrono>

//using namespace path_finding;


// Test functions 


/// min. path from 'start' vertex to 'target' vertex.
void example_wiki();

int main()
{
  example_wiki();

  return 0;
}

//---------------------------------------------------------------------------

void example_wiki()
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


  const auto TEST_NUM_ITERATIONS = 1; //1e7;
  path_finding::PathFindingSolutionData solution;
  
  std::cout << "\n1) Testing UCS for finite graphs" << std::endl;
  auto start = std::chrono::steady_clock::now();   // record start time
  for (auto times = 0; times < TEST_NUM_ITERATIONS; ++times) 
  {
    solution = dijkstra_shortest_path_directed_graph("11", "55", edges);
    
    // RESULTADOS (time)
    //
    // fase-2: 
    //
    // Time after 1e+07 examples (sin imprimir resultados): 55.4483
    // => WARNING: idem all2all
    //
    // Time after 1e+07 examples (sin imprimir resultados): 68.8308
    // Comprobando si candidatos fueron ya explored! (solo hay un caso
    // en el ejemplo
    //
    //
  }
  auto end = std::chrono::steady_clock::now();
  std::cout << "Vertex Distance from Source" << std::endl;
  std::cout << solution << std::endl;
  std::chrono::duration<double> diff = end-start;
  std::clog << "Time after " << TEST_NUM_ITERATIONS 
	    << " examples (sin imprimir resultados): "
	    << diff.count() <<  std::endl;

  

  std::cout << "\n2) Testing UCS for infinite graphs" << std::endl;
  start = std::chrono::steady_clock::now();   // record start time
  for (auto times = 0; times < TEST_NUM_ITERATIONS; ++times) 
  {
    solution = dijkstra_shortest_path_directed_infinite_graph("11", "55", edges);    

    // RESULTADOS (time)
    //
    // fase-2: 
    //
    // Time after 1e+07 examples (sin imprimir resultados): 55.4483
    // => WARNING: idem all2all
    //
    // Time after 1e+07 examples (sin imprimir resultados): 68.8308
    // Comprobando si candidatos fueron ya explored! (solo hay un caso
    // en el ejemplo
    //
    //
  }
  end = std::chrono::steady_clock::now();
  std::cout << "Vertex Distance from Source" << std::endl;
  std::cout << solution << std::endl;
  diff = end-start;
  std::clog << "Time after " << TEST_NUM_ITERATIONS 
	    << " examples (sin imprimir resultados): "
	    << diff.count() <<  std::endl;
  
  
//   Solución esperada:
// Vertex Distance from Source
// Distance (cost): 20
// Shortest-Path's size (n. of vertex): 4
// Shortest-Path: 11 -> 33 -> 66 -> 55
  
}



