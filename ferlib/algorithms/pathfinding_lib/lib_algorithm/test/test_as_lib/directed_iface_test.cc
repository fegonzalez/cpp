
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
  const auto TEST_NUM_ITERATIONS = 1; //1e7;


  // start -> target

  auto start = std::chrono::steady_clock::now();   // record start time

  for (auto times = 0; times < TEST_NUM_ITERATIONS; ++times) 
  {
    example_wiki();


    // RESULTADOS (time)
    //
    // fase-2: 
    //
    // Time after 1e+07 examples (sin imprimir resultados): 55.4483
    // => WARNING: idem all2all
    //
    // Time after 1e+07 examples (sin imprimir resultados): 68.8308
    // Comprobando si candidatos fueron ya visited! (solo hay un caso
    // en el ejemplo
    //
    //
  }

  // record end time
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> diff = end-start;
  std::clog << "\nTime after " << TEST_NUM_ITERATIONS 
	    << " examples (sin imprimir resultados): "
	    << diff.count() <<  std::endl;

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

  path_finding::PathFindingSolutionData solution =
    dijkstra_shortest_path_directed_graph("11", "55", edges);

  std::cout << "Vertex Distance from Source" << std::endl;
  std::cout << solution << std::endl;

  
//   Solución esperada:
// Vertex Distance from Source
// Distance (cost): 20
// Shortest-Path's size (n. of vertex): 4
// Shortest-Path: 11 -> 33 -> 66 -> 55
  
}



