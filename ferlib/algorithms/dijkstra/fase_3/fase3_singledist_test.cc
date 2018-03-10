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

        /*
    const unsigned_int N_VERTEX = 7;

    ConcreteGraph g();

    // add_vertex solo recomendado para vertex aislados
    // for (auto loopi=1; loopi<=N_VERTEX; ++loopi)
    // {
    //   g.add_vertex(std::to_string(loopi));
    // }

    //add_edge incluye add_vertex implícitamente
    g.add_edge(1, 2, 7.0);
    g.add_edge(1, 3, 9.0);
    g.add_edge(1, 6, 14.0);
    g.add_edge(2, 3, 10.0);
    g.add_edge(2, 4, 15.0);
    g.add_edge(3, 4, 11.0);
    g.add_edge(3, 6, 2.0);
    g.add_edge(4, 5, 6.0);
    g.add_edge(5, 6, 9.0);
    
    std::cout << g << std::endl;
    
    DijkstraConcrete alg; 
    DijkstraSolution solution = alg.shortest_path(g, 1, 5);
    
    std::cout << "Vertex Distance from Source" << std::endl;
    std::cout << solution << std::endl;
      */

    
    /*  i.e user_ids as strings

    ConcreteGraph g();

    for (auto loopi=1; loopi<=N_VERTEX; ++loopi)
    {
      g.add_vertex(std::to_string(loopi));
    }


    
    g.add_edge("0", "1", TYPEDISTANCE_INFINITE);//WARNING: la
					    //impl. requiere nodo
					    //inicial = 0
    g.add_edge("1", "2", 7.0);
    g.add_edge("1", "3", 9.0);
    g.add_edge("1", "6", 14.0);
    g.add_edge("2", "3", 10.0);
    g.add_edge("2", "4", 15.0);
    g.add_edge("3", "4", 11.0);
    g.add_edge("3", "6", 2.0);
    g.add_edge("4", "5", 6.0);
    g.add_edge("5", "6", 9.0);
    
    std::cout << g << std::endl;
    
    DijkstraConcrete alg; 
    DijkstraSolution solution = alg.shortest_path(g, 1, 5);
    
    std::cout << "Vertex Distance from Source" << std::endl;
    std::cout << solution << std::endl;
      */

    // Output :
    // Nodes: 7
    // FROM	TO	WEIGHT
    //  0	1	0
    //  1	0	0
    //  1	2	7
    //  1	3	9
    //  1	6	14
    //  2	1	7
    //  2	3	10
    //  2	4	15
    //  3	1	9
    //  3	2	10
    //  3	4	11
    //  3	6	2
    //  4	2	15
    //  4	3	11
    //  4	5	6
    //  5	4	6
    //  5	6	9
    //  6	1	14
    //  6	3	2
    //  6	5	9

    // Vertex Distance from Source
    // Distance (cost): 20
    // Shortest-Path: 1 -> 3 -> 6 -> 5

}

