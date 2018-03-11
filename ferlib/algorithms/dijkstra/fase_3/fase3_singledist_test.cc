#include "common.h"
#include "ConcreteGraph.h"
#include "Dijkstra.h"

#include <string>
#include <iostream>
#include <chrono>

using namespace dijkstra_algorithm;


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
  DirectedConcreteGraph g;
      
  //add_edge incluye add_vertex implícitamente
  // g.add_edge(1, 2, 7.0);
  // g.add_edge(1, 3, 9.0);
  // g.add_edge(1, 6, 14.0);
  // g.add_edge(2, 3, 10.0);
  // g.add_edge(2, 4, 15.0);
  // g.add_edge(3, 4, 11.0);  
  // g.add_edge(3, 6, 2.0);

  // g.add_edge(4, 5, 6.0);
  
  // g.add_edge(5, 6, 9.0);
  // std::cout << g << std::endl;    
  // DijkstraConcrete alg; 
  // DijkstraSolution solution = alg.shortest_path(g, 1, 5);

  /*
  g.add_edge(1, 2, 7.0);
  g.add_edge(1, 3, 9.0);
  g.add_edge(1, 6, 14.0);
  g.add_edge(2, 3, 10.0);
  g.add_edge(2, 4, 15.0);
  g.add_edge(3, 4, 11.0);
  g.add_edge(3, 6, 2.0);
  g.add_edge(4, 5, 6.0); // CORE DUMPED
  std::cout << g << std::endl;    
  DijkstraConcrete alg; 
  //DijkstraSolution solution = alg.shortest_path(g, 1, 4); // OK
  DijkstraSolution solution = alg.shortest_path(g, 1, 5);  // CORE DUMPED
  */

  g.add_edge(1, 2, 7.0);
  // g.add_edge(1, 6, 14.0); // CORE DUMPED
  g.add_edge(2, 3, 10.0);
  g.add_edge(2, 4, 15.0);
  g.add_edge(4, 5, 6.0); 
  std::cout << g << std::endl;    
  DijkstraConcrete alg; 
  DijkstraSolution solution = alg.shortest_path(g, 1, 5);
  
  
  std::cout << "Vertex Distance from Source" << std::endl;
  std::cout << solution << std::endl;

    
}

