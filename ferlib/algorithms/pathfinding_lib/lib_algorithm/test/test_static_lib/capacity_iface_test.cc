/**@file capacity_iface_test.cc

   @test Testing the capacity of the Dijkstra algorithm (size of the input G).

   - Test Graph: graph used in RMAN and RTP.
   
   - Test Complelxity: 

     TOTAL NODES = matrix (NUM_NODES_PER_INTERVAL * NUM_INTERVALS)
 
     TOTAL EDGES = BEGIN_EDGES + MIDDLE_EDGES + END_EDGES

     O(BEGIN-EDGES)  = constant = NUM_NODES_PER_INTERVAL
     O(END-EDGES)    = constant = NUM_NODES_PER_INTERVAL
     
     MIDDLE_EDGES = (2 exp (NUM_NODES_PER_INTERVAL)) * (NUM_INTERVALS-1) )

     case RTP: (NUM_NODES_PER_INTERVAL >> NUM_INTERVALS):
               O(TOTAL_EDGES) ~= 2 EXP NUM_NODES_PER_INTERVAL


NUM. EDGES per interval !!!!

>>> pow(15000, 2)
225000000


///////////////////////////////////////////////////////////////////////////////
//
//   Solución obtenida
//
//

Problem size: Intervals: 3; Nodes per interval: 4; Total Num nodes: 12; Num edges: 41
 >> Total Time after 1 examples (sin imprimir resultados): 0.000412689
 >> Time of data structs preparation : 0.000104033
 >> Time of Dijkstra execution: 0.000308656


// RMAN-size
Problem size: Intervals: 36; Nodes per interval: 6; Total Num nodes: 216; Num edges: 1273
Vertex Distance from Source
 >> Total Time after 1 examples (sin imprimir resultados): 0.00801358
 >> Time of data structs preparation : 0.000714434
 >> Time of Dijkstra execution: 0.00729915


Problem size: Intervals: 36; Nodes per interval: 100; Total Num nodes: 3600; Num edges: 350201
 >> Total Time after 1 examples (sin imprimir resultados): 6.06198
 >> Time of data structs preparation : 0.156159
 >> Time of Dijkstra execution: 5.90583
>>



// RTP size 
Problem size: Intervals: 36; Nodes per interval: 15000; Total Num nodes: 540000;
Num edges: ~ 7.875.030.000


ERROR:  SIN MEMORIA durante la creación de los edges => no llega a llamar al alg

terminate called after throwing an instance of 'std::bad_alloc'
  what():  std::bad_alloc


 */


#include <LcpfPublicTypes.h>
#include <LcpfPathfindingSolutionData.h>
#include <LcpfTypeUserEdgeData.h>
#include <LcpfFacade.h>


#include <string>
#include <iostream>
#include <chrono>
#include <cstdlib>


using namespace path_finding;


// Test functions 


/// min. path from 'start' vertex to 'target' vertex.
void example_capacity();

auto start_time = std::chrono::steady_clock::now();   // record start time
auto preparation_time = std::chrono::steady_clock::now();

int main()
{
  const auto TEST_NUM_ITERATIONS = 1; //1e7;


  // start -> target



  for (auto times = 0; times < TEST_NUM_ITERATIONS; ++times) 
  {
    example_capacity();


    // RESULTADOS (time)
    //
    // fase-2: 
    //
    // Time after 1e+07 examples (sin imprimir resultados):  ???
    // => WARNING: idem all2all
    //
    // Time after 1e+07 examples (sin imprimir resultados): ???
    // Comprobando si candidatos fueron ya explored! (solo hay un caso
    // en el ejemplo
    //
    //
  }

  // record end_time
  auto end_time = std::chrono::steady_clock::now();
  std::chrono::duration<double> diff = end_time - start_time;
  std::clog << "\n >> Total Time after " << TEST_NUM_ITERATIONS 
	    << " examples (sin imprimir resultados): "
	    << diff.count() <<  std::endl;

  diff = preparation_time - start_time;
  std::clog << " >> Time of data structs preparation : " 
	    << diff.count() <<  std::endl;

  diff = end_time - preparation_time;
  std::clog << " >> Time of Dijkstra execution: " 
	    << diff.count() <<  std::endl;


  return 0;

}

//---------------------------------------------------------------------------

void example_capacity()
{
  std::cout << "\n\nDijkstra example on a DIRECTED graph. Very big Input Graph."
  	    <<  std::endl;

 
 const int MAX_COST = 10000;
 const int NUM_INTERVALS = 36;
 const int RMAN_NODES_PER_INTERVAL = 6;
 const int RTP_NODES_PER_INTERVAL = 15000;
 (void) RMAN_NODES_PER_INTERVAL;
 (void) RTP_NODES_PER_INTERVAL;

 const int NUM_NODES_PER_INTERVAL = RMAN_NODES_PER_INTERVAL;
 std::vector<path_finding::TypeUserEdgeData> edges;
 std::srand(std::time(nullptr)); // use current time as seed for random generator

 //BEGIN NODE
 for (int node = 1; node <= NUM_NODES_PER_INTERVAL; ++node)
   {
     // std::cout << "\nfrom-to: " << "begin" << '-' << std::to_string(node)
     // 	       << " : " << 0.0;

     std::string node_id = std::string("edge_") + 
       std::string("begin") + 
       std::string("_") + 
       std::to_string(node);

     edges.push_back(TypeUserEdgeData("begin",std::to_string(node),0.0,node_id));
   }
 // std::cout << std::endl;

 // MIDDLe NODES

 int first_node_last_interval = 0;
 for (int ti = 1; ti < NUM_INTERVALS; ++ti) // ti: creates nodes for ti+1
 {
   for (int node = 1; node <= NUM_NODES_PER_INTERVAL; ++node)
   {
     // get ramdom cost value [0, MAX_COST]
     int current_cost = MAX_COST + 1;
     while(current_cost > MAX_COST) 
       {
	 current_cost = 1 + std::rand()/((RAND_MAX + 1u)/MAX_COST);
       }

     //create  nodes & edges
     int first_node_next_interval = 1 + (NUM_NODES_PER_INTERVAL*ti);
     std::string idfrom = std::to_string(node+(NUM_NODES_PER_INTERVAL*(ti-1)));
     for(int node_to = first_node_next_interval;
	 node_to < ( first_node_next_interval + NUM_NODES_PER_INTERVAL );
	 ++node_to)
       {
	 //	   std::cout << "\n node - node_to: " << node << '-' << node_to;
	 std::string idto = std::to_string(node_to);
	 // std::cout << "\nfrom-to: " << idfrom << '-' << idto 
	 // 	   << " : " << static_cast<double> (current_cost);

	 std::string node_id = std::string("edge_") + idfrom + "_" + idto;
	 
	 edges.push_back(TypeUserEdgeData
			 (idfrom, 
			  idto, 
			  current_cost, 
			  node_id));
       }
     // edges.push_back(TypeUserEdgeData("11", "22", 7.0, "edge11_22"));

     // std::cout << std::endl;

     first_node_last_interval = first_node_next_interval;
   }
 }

//END NODE
 for (int node = first_node_last_interval; 
      node <= first_node_last_interval + NUM_NODES_PER_INTERVAL; ++node)
 {
   // std::cout << "\nfrom-to: " << std::to_string(node) << '-' << "end" 
   // 	       << " : " << 0.0;


   std::string node_id = std::string("edge_") + std::to_string(node) + 
                         std::string("_") + "end";
	 
   edges.push_back(TypeUserEdgeData
		   (std::to_string(node),
		    "end", 
		    0.0,
		    node_id));
 }


  // record Data structure creation time
  preparation_time = std::chrono::steady_clock::now();
  std::chrono::duration<double> diff = preparation_time - start_time;
  std::clog << "\n >> Time after edges construction (before calling Dijkstra): "
	    << diff.count() <<  std::endl;


 std::cout << std::endl;
 std::cout << "\nProblem size: "
	   << "Intervals: " << NUM_INTERVALS
	   << "; Nodes per interval: " << NUM_NODES_PER_INTERVAL
	   << "; Total Num nodes: " << (NUM_NODES_PER_INTERVAL * NUM_INTERVALS)
	   << "; Num edges: " << edges.size();
 std::cout << std::endl;


  PathfindingSolutionData solution =
    dijkstra_shortest_path_undirected_graph("begin", "end", edges);

  std::cout << "Vertex Distance from Source" << std::endl;
  std::cout << solution << std::endl;

}

