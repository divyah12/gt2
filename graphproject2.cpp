/*
Name : Divyashree Hanaganhalli Boregowda
Roster No. : 5
The following program provides a minimum spanning tree using kruskals algorithm.
Output : In console, the minimun edge's are printed out and a dot file is generated.
This dot file contains the graph of minimun spanning tree for the given project.
This project uses the boost library and its applications. The adjacency list header
is used to declare the edges and weights for the graph. However, to compute the MST
the predefined kruskal's algorithm is included in the project.
Furthermore, the following code was retrived from boost library example (its link
is : http://www.boost.org/doc/libs/1_35_0/libs/graph/example/kruskal-example.cpp).
Link to boost installation is https://www.youtube.com/watch?v=GOhHMS4I9Zw .
Finally, This project document contains the code(graphproject.cpp), console output,
kruskal-eg.dot, kruskal-eg.png and a screenshot of the console.
NOTE: In the kruskal-eg.png file the minimun spanning edge is highlighted on
the given graph. It provides an visual differance on the graph.
*/
// graphproject2.cpp : Defines the entry point for the console application.
//
//=======================================================================
// Copyright 2001 Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee, 
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================


#include "stdafx.h"
#include<stdio.h>
#include <iostream>
#include<fstream>
#include "boost/graph/adjacency_list.hpp"
#include <boost/graph/kruskal_min_spanning_tree.hpp>

using namespace std;

int main()
{
	using namespace boost;
	//adjacency list
	typedef adjacency_list < vecS, vecS, undirectedS,
		no_property, property < edge_weight_t, int > > Graph;
	typedef graph_traits < Graph >::edge_descriptor Edge;
	typedef graph_traits < Graph >::vertex_descriptor Vertex;
	typedef std::pair<int, int> E;
	//declaring the edges
	const int num_nodes = 11;
	E edge_array[] = { E(0, 7), E(0,5), E(0,1), E(1, 3), E(1,4), E(2,4), E(2,8), E(3,5),
		E(4,5), E(4,6), E(5,7), E(6,7), E(6,8), E(6,9), E(7,10), E(8,9), E(8,10) };
	int weights[] = { 2,5,3,5,1,2,5,7,3,3,1,4,2,3,8,4,1 };
	std::size_t num_edges = sizeof(edge_array) / sizeof(E);
	//assign weight to edge
#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
	Graph g(num_nodes);
	property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, g);
	for (std::size_t j = 0; j < num_edges; ++j) {
		Edge e; bool inserted;
		tie(e, inserted) = add_edge(edge_array[j].first, edge_array[j].second, g);
		weightmap[e] = weights[j];
	}
#else
	Graph g(edge_array, edge_array + num_edges, weights, num_nodes);
#endif

	//kruskal algorithm
	property_map < Graph, edge_weight_t >::type weight = get(edge_weight, g);
	std::vector < Edge > spanning_tree;

	kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));
	//prints the minimun edges of the given graph
	std::cout << "Print the edges in the MST:" << std::endl;
	for (std::vector < Edge >::iterator ei = spanning_tree.begin();
	ei != spanning_tree.end(); ++ei) {
		std::cout << source(*ei, g) << " <--> " << target(*ei, g)
			<< " with weight of " << weight[*ei]
			<< std::endl;
	}
	//create dot file and write the graph
	std::ofstream fout("figs/kruskal-eg.dot");
	fout << "graph A {\n"
		<< " rankdir=LR\n"
		<< " size=\"3,3\"\n"
		<< " ratio=\"filled\"\n"
		<< " edge[style=\"bold\"]\n" << " node[shape=\"circle\"]\n";
	graph_traits<Graph>::edge_iterator eiter, eiter_end;
	for (tie(eiter, eiter_end) = edges(g); eiter != eiter_end; ++eiter) {
		fout << source(*eiter, g) << " -- " << target(*eiter, g);
		if (std::find(spanning_tree.begin(), spanning_tree.end(), *eiter)
			!= spanning_tree.end())
			fout << "[color=\"black\", label=\"" << get(edge_weight, g, *eiter)
			<< "\"];\n";
		else
			fout << "[color=\"gray\", label=\"" << get(edge_weight, g, *eiter)
			<< "\"];\n";
	}
	fout << "}\n";
	return EXIT_SUCCESS;
	//return 0;
}