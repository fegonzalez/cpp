#include "common.h"
#include "graph_fase2.h"
#include "dijkstra.h"

#include <iostream>
#include <chrono>

using namespace dijkstra_algorithm;


// Test functions 


/// min. path from 'start' vertex to 'target' vertex.
void example_wiki();

/// min. path from the  'start' vertex to all the others.
//void example_wiki_all2all();
//void example1();



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




  //---------------------------------------------------------------

  // start -> ALL vertex

  // start = std::chrono::steady_clock::now();   // record start time

  // for (auto times = 0; times < TEST_NUM_ITERATIONS; ++times) 
  // {
  //   example_wiki_all2all();


  //   // RESULTADOS (time)
  //   //
  //   // fase-1: 
  //   // Time after 1e+07 examples (sin imprimir resultados): 54.3812
  //   //
  //   // fase-2: 
  //   // Time after 1e+06 examples (sin imprimir resultados): ????
  //   // Time after 1e+07 examples (sin imprimir resultados): ????
  // }

  // // record end time
  // end = std::chrono::steady_clock::now();
  // diff = end-start;
  // std::clog << "\nTime after " << TEST_NUM_ITERATIONS 
  // 	    << " examples (sin imprimir resultados): "
  // 	    << diff.count() <<  std::endl;



 
  // return 0;
}

//---------------------------------------------------------------------------

void example_wiki()
{
    // create the graph given in above fugure
    int n_vertex = 7;
    Fase2Graph g(n_vertex);

    g.add_edge(0, 1, TYPEDISTANCE_INFINITE);//WARNING: la
					    //impl. requiere nodo
					    //inicial = 0
    g.add_edge(1, 2, 7);    
    g.add_edge(1, 3, 9);
    g.add_edge(1, 6, 14);
    g.add_edge(2, 3, 10);
    g.add_edge(2, 4, 15);
    g.add_edge(3, 4, 11);
    g.add_edge(3, 6, 2);
    g.add_edge(4, 5, 6);
    g.add_edge(5, 6, 9);
    
    std::cout << g << std::endl;
    
    DijkstraFase2 alg; 
    DijkstraSolution solution = alg.shortest_path(g, 1, 5);
    
    std::cout << "Vertex Distance from Source" << std::endl;
    std::cout << solution << std::endl;
      

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


//---------------------------------------------------------------------------
/*
/// min. path from the  'start' vertex to all the others.
void example_wiki_all2all()
{
    // create the graph given in above fugure
    int n_vertex = 7;
    Fase2Graph g(n_vertex);

    //std::cout << g << std::endl;
    g.add_edge(0, 1, 0);      //WARNING: la impl. requiere nodo inicial = 0
    g.add_edge(1, 2, 7);    
    g.add_edge(1, 3, 9);
    g.add_edge(1, 6, 14);
    g.add_edge(2, 3, 10);
    g.add_edge(2, 4, 15);
    g.add_edge(3, 4, 11);
    g.add_edge(3, 6, 2);
    g.add_edge(4, 5, 6);
    g.add_edge(5, 6, 9);
    std::cout << g << std::endl;
    //DijkstraFase2 alg; 
    //    alg.shortest_paths(g, 1);
    
    // std::cout << "Vertex Distance from Source" << std::endl;
    // std::cout << solution << std::endl;
      

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

    // Vertex   Distance from Source
    // 0		 0
    // 1		 0
    // 2		 7
    // 3		 9
    // 4		 20
    // 5		 20
    // 6		 11

}


//---------------------------------------------------------------------------

// void example1()
// {
//     int n_vertex = 9;
//     Graph g(n_vertex);    
//     g.add_edge(0, 1, 4);
//     g.add_edge(0, 7, 8);
//     g.add_edge(1, 2, 8);
//     g.add_edge(1, 7, 11);
//     g.add_edge(2, 3, 7);
//     g.add_edge(2, 8, 2);
//     g.add_edge(2, 5, 4);
//     g.add_edge(3, 4, 9);
//     g.add_edge(3, 5, 14);
//     g.add_edge(4, 5, 10);
//     g.add_edge(5, 6, 2);
//     g.add_edge(6, 7, 1);
//     g.add_edge(6, 8, 6);
//     g.add_edge(7, 8, 7);

//     Dijkstra alg; 
//     alg.shortest_paths(g, 0);

    // Output :

    // Vertex    Distance from Source
    // 0          0
    // 1          4
    // 2          12
    // 3          19
    // 4          21
    // 5          11
    // 6          9
    // 7          8
    // 8          14

//}

*/
