
#include "BaseGraph.h"
#include "Dijkstra.h"

#include <string>
#include <iostream>
#include <chrono>

using namespace path_finding;


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
  std::cout << "\n\nWikipedia's Dijkstra example on a DIRECTED graph.\n"
  	    <<  std::endl;

  DirectedGraph g;
      
  /// @warning add_edge incluye add_vertex implícitamente

  //warning: ejemplo wiki es grafo no dirigido => doble edge en grafo dirigido
  
  g.add_edge(11, 22, 7.0);   g.add_edge(22, 11, 7.0);
  g.add_edge(11, 33, 9.0);   g.add_edge(33, 11, 9.0);
  g.add_edge(22, 44, 15.0);  g.add_edge(44, 22, 15.0);
  g.add_edge(44, 55, 6.0);   g.add_edge(55, 44, 6.0);
  g.add_edge(11, 66, 14.0);  g.add_edge(66, 11, 14.0);
  g.add_edge(22, 33, 10.0);  g.add_edge(33, 22, 10.0);
  g.add_edge(33, 44, 11.0);  g.add_edge(44, 33, 11.0);
  g.add_edge(33, 66, 2.0);   g.add_edge(66, 33, 2.0);
  g.add_edge(55, 66, 9.0);   g.add_edge(66, 55, 9.0);

   std::cout << g << std::endl;    

  Dijkstra alg; 
  DijkstraSolution solution = alg.shortest_path(g, 11, 55);
  
  std::cout << "Vertex Distance from Source" << std::endl;
  std::cout << solution << std::endl;

//   Solución esperada:
// Vertex Distance from Source
// Distance (cost): 20
// Shortest-Path's size (n. of vertex): 4
// Shortest-Path: 11 -> 33 -> 66 -> 55
  
}

