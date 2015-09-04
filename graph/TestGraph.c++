// --------------------------------
// projects/g++/graph/TestGraph.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "gtest/gtest.h"

#include "Graph.h"

using namespace std;

using testing::Test;
using testing::Types;

// ---------
// TestGraph
// ---------

template <typename G>
struct TestGraph : Test {
    // --------
    // typedefs
    // --------

    typedef          G                     graph_type;
    typedef typename G::vertex_descriptor  vertex_descriptor;
    typedef typename G::edge_descriptor    edge_descriptor;
    typedef typename G::vertex_iterator    vertex_iterator;
    typedef typename G::edge_iterator      edge_iterator;
    typedef typename G::adjacency_iterator adjacency_iterator;
    typedef typename G::vertices_size_type vertices_size_type;
    typedef typename G::edges_size_type    edges_size_type;
};

// directed, sparse, unweighted
// possibly connected
// possibly cyclic
typedef Types<
            boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>,
            Graph>
        graph_types;

TYPED_TEST_CASE(TestGraph, graph_types);

TYPED_TEST(TestGraph, test_vertex) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;    
    typedef typename TestFixture::vertices_size_type vertices_size_type;
    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(1, vs);}

TYPED_TEST(TestGraph, test_edge) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::edges_size_type    edges_size_type;
    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    //cout << "\n--num edges: " << num_edges(g) << "--\n";
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    //cout << "\n--num edges: " << num_edges(g) << "--\n";
    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);

    pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);}

TYPED_TEST(TestGraph, test_vertices) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;
    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    ASSERT_EQ(e, b);}

TYPED_TEST(TestGraph, test_edges) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    typedef typename TestFixture::edge_iterator      edge_iterator;    
    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                      b = p.first;
    edge_iterator                      e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAC, ed);}
    ++b;
    ASSERT_EQ(e, b);}

TYPED_TEST(TestGraph, test_adjacent_vertices) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        //cout << *b << "   ";
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        //cout << *b << "\n";
        ASSERT_EQ(vdC, vd);}
    ++b;
    ASSERT_EQ(e, b);}

// -----------
// constructor
// -----------

TYPED_TEST(TestGraph, test_constructor_1) {
    typedef typename TestFixture::graph_type         graph_type;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));
}

TYPED_TEST(TestGraph, test_constructor_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;

    graph_type g;

    pair<vertex_iterator, vertex_iterator> iters = vertices(g);

    ASSERT_TRUE(iters.first == iters.second);
}

TYPED_TEST(TestGraph, test_constructor_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_iterator      edge_iterator;

    graph_type g;

    pair<edge_iterator, edge_iterator> iters = edges(g);

    ASSERT_TRUE(iters.first == iters.second);
}

// --------
// vertices
// --------

// std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& graph)

TYPED_TEST(TestGraph, test_vertices_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;

    graph_type g;
    pair<vertex_iterator, vertex_iterator> iters = vertices(g);

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_TRUE(iters.first == iters.second);

    add_vertex(g);

    iters = vertices(g);

    ASSERT_EQ(1, num_vertices(g));
    ASSERT_FALSE(iters.first == iters.second);
    ASSERT_EQ(0, *iters.first);
}

TYPED_TEST(TestGraph, test_vertices_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;

    graph_type g;

    for (int i = 0; i < 10; ++i){
        add_vertex(g);
    }

    ASSERT_EQ(10, num_vertices(g));

    pair<vertex_iterator, vertex_iterator> iters = vertices(g);
    vertex_iterator b = iters.first;
    vertex_iterator e = iters.second;

    for (int i = 0; i < 10; ++i){
        ASSERT_TRUE(b != e);
        ASSERT_EQ(*b, i);
        ++b;
    }

    ASSERT_TRUE(b == e);
}

TYPED_TEST(TestGraph, test_vertices_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_iterator    vertex_iterator;

    graph_type g;

    add_edge(8, 9, g);

    ASSERT_EQ(10, num_vertices(g));

    pair<vertex_iterator, vertex_iterator> iters = vertices(g);
    vertex_iterator b = iters.first;
    vertex_iterator e = iters.second;

    for (int i = 0; i < 10; ++i){
        ASSERT_TRUE(b != e);
        ASSERT_EQ(*b, i);
        ++b;
    }

    ASSERT_TRUE(b == e);
}

// ------
// vertex
// ------

// vertex_descriptor vertex (vertices_size_type n, const Graph& graph)

TYPED_TEST(TestGraph, test_vertex_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));

    vertex_descriptor v = vertex(0, g);

    ASSERT_EQ(0, v);
    ASSERT_EQ(0, num_vertices(g));

    v = vertex(7, g);

    ASSERT_EQ(7, v);
    ASSERT_EQ(0, num_vertices(g));
}

TYPED_TEST(TestGraph, test_vertex_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));

    for (int i = 0; i < 100; ++i)
    {
        vertex_descriptor v1 = add_vertex(g);
        vertex_descriptor v2 = vertex(i, g);
        ASSERT_TRUE(v1 == v2);
        ASSERT_EQ(i + 1, num_vertices(g));
    }
}

TYPED_TEST(TestGraph, test_vertex_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));

    vertex_descriptor v1 = add_vertex(g);

    ASSERT_EQ(1, num_vertices(g));

    vertex_descriptor v2 = vertex(0, g);

    ASSERT_TRUE(v1 == v2);

    vertex_descriptor v3 = vertex(7, g);

    ASSERT_EQ(7, v3);
    ASSERT_FALSE(v3 == v2 || v3 == v1);
    ASSERT_EQ(1, num_vertices(g));
}

// ------
// target
// ------

// vertex_descriptor target (edge_descriptor edge, const Graph& graph)

TYPED_TEST(TestGraph, test_target_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    edge_descriptor e = add_edge(0, 1, g).first;

    ASSERT_EQ(2, num_vertices(g));
    ASSERT_EQ(1,    num_edges(g));

    ASSERT_EQ(1, target(e, g));
}

TYPED_TEST(TestGraph, test_target_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    edge_descriptor e = add_edge(0, 1, g).first;

    ASSERT_EQ(2, num_vertices(g));
    ASSERT_EQ(1,    num_edges(g));

    ASSERT_EQ(1, target(e, g));

    e = add_edge(1, 0, g).first;

    ASSERT_EQ(2, num_vertices(g));
    ASSERT_EQ(2,    num_edges(g));

    ASSERT_EQ(0, target(e, g));
}

TYPED_TEST(TestGraph, test_target_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    edge_descriptor e = add_edge(0, 12, g).first;

    ASSERT_EQ(13, num_vertices(g));
    ASSERT_EQ(1,    num_edges(g));

    ASSERT_EQ(12, target(e, g));

    e = add_edge(1, 12, g).first;

    ASSERT_EQ(13, num_vertices(g));
    ASSERT_EQ(2,    num_edges(g));

    ASSERT_EQ(12, target(e, g));
}

// ------
// source
// ------

// vertex_descriptor source (edge_descriptor edge, const Graph& graph)

TYPED_TEST(TestGraph, test_source_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    edge_descriptor e = add_edge(0, 1, g).first;

    ASSERT_EQ(2, num_vertices(g));
    ASSERT_EQ(1,    num_edges(g));

    ASSERT_EQ(0, source(e, g));
}

TYPED_TEST(TestGraph, test_source_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    add_edge(1, 0, g);
    add_edge(1, 2, g);
    edge_descriptor e = add_edge(1, 3, g).first;

    ASSERT_EQ(4, num_vertices(g));
    ASSERT_EQ(3,    num_edges(g));

    ASSERT_EQ(1, source(e, g));
}

TYPED_TEST(TestGraph, test_source_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    edge_descriptor e = add_edge(0, 0, g).first;
    add_edge(0, 0, g);
    add_edge(0, 0, g);
    add_edge(0, 0, g);

    ASSERT_EQ(1, num_vertices(g));
    ASSERT_EQ(1,    num_edges(g));

    ASSERT_EQ(0, source(e, g));
}

// ------------
// num_vertices
// ------------

// vertices_size_type num_vertices (const Graph& graph)

TYPED_TEST(TestGraph, test_num_vertices_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));

    vertex_descriptor v1 = add_vertex(g);

    ASSERT_EQ(0, v1);
    ASSERT_EQ(1, num_vertices(g));
}

TYPED_TEST(TestGraph, test_num_vertices_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));

    for (int i = 0; i < 10; ++i){
        vertex_descriptor v = add_vertex(g);
        ASSERT_EQ(i, v);
    }

    ASSERT_EQ(10, num_vertices(g));
}

TYPED_TEST(TestGraph, test_num_vertices_3) {
    typedef typename TestFixture::graph_type         graph_type;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));

    add_edge(0, 1, g);
    add_edge(1, 0, g);

    add_edge(1, 2, g);
    add_edge(2, 1, g);

    add_edge(0, 2, g);
    add_edge(2, 0, g);

    ASSERT_EQ(3, num_vertices(g));
}

TYPED_TEST(TestGraph, test_num_vertices_4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));

    add_edge(1, 2, g);
    add_edge(2, 1, g);

    add_edge(2, 3, g);
    add_edge(3, 2, g);

    add_edge(1, 3, g);
    add_edge(3, 1, g);

    ASSERT_EQ(4, num_vertices(g));

    add_edge(0, 1, g);
    add_edge(3, 0, g);

    ASSERT_EQ(4, num_vertices(g));

    vertex_descriptor v1 = add_vertex(g);
    vertex_descriptor v2 = add_vertex(g);

    ASSERT_EQ(6, num_vertices(g));
    ASSERT_EQ(4, v1);
    ASSERT_EQ(5, v2);
}

// ---------
// num_edges
// ---------

// edges_size_type num_edges (const Graph& graph)

TYPED_TEST(TestGraph, test_num_edges_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;
    
    ASSERT_EQ(0, num_edges(g));

    vertex_descriptor s = 1;
    vertex_descriptor t = 2;

    add_edge (s, t, g);
    
    ASSERT_EQ(1, num_edges(g));
}

TYPED_TEST(TestGraph, test_num_edges_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;
    
    ASSERT_EQ(0, num_edges(g));

    vertex_descriptor s = 1;
    vertex_descriptor t = 2;

    add_edge (s, t, g);
    add_edge (s, t, g);
    add_edge (s, t, g);
    
    ASSERT_EQ(1, num_edges(g));
}

TYPED_TEST(TestGraph, test_num_edges_3) {
    typedef typename TestFixture::graph_type         graph_type;

    graph_type g;
    
    ASSERT_EQ(0, num_edges(g));

    add_edge (1, 2, g);
    add_edge (2, 3, g);
    add_edge (3, 1, g);
    
    ASSERT_EQ(3, num_edges(g));
}

TYPED_TEST(TestGraph, test_num_edges_4) {
    typedef typename TestFixture::graph_type         graph_type;

    graph_type g;
    
    ASSERT_EQ(0, num_edges(g));

    add_edge (1, 2, g);
    add_edge (2, 3, g);
    add_edge (3, 1, g);
    
    ASSERT_EQ(3, num_edges(g));

    add_edge (2, 1, g);
    add_edge (3, 2, g);
    add_edge (1, 3, g);
    
    ASSERT_EQ(6, num_edges(g));
}

// -----
// edges
// -----

// std::pair<edge_iterator, edge_iterator> edges (const Graph& graph)

TYPED_TEST(TestGraph, test_edges_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_iterator      edge_iterator;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    std::pair<edge_iterator, edge_iterator> iters = edges(g);

    ASSERT_TRUE(iters.first == iters.second);

    add_edge(0, 1, g);

    ASSERT_EQ(2, num_vertices(g));
    ASSERT_EQ(1,    num_edges(g));

    iters = edges(g);

    ASSERT_FALSE(iters.first == iters.second);
}

TYPED_TEST(TestGraph, test_edges_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    
    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    for (int i = 0; i < 8; ++i){
        add_edge(i, i + 1, g);
    }

    ASSERT_EQ(9, num_vertices(g));
    ASSERT_EQ(8,    num_edges(g));

    std::pair<edge_iterator, edge_iterator> iters = edges(g);

    for (int i = 0; i < 8; ++i){
        ASSERT_TRUE(iters.first != iters.second);
        ++iters.first;
    }

    ASSERT_TRUE(iters.first == iters.second);
}

TYPED_TEST(TestGraph, test_edges_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    
    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    for (int i = 0; i < 100; ++i){
        add_edge(i, i + 1, g);
    }

    ASSERT_EQ(101, num_vertices(g));
    ASSERT_EQ(100,    num_edges(g));

    std::pair<edge_iterator, edge_iterator> iters = edges(g);

    for (int i = 0; i < 100; ++i){
        ASSERT_TRUE(iters.first != iters.second);
        ++iters.first;
    }

    ASSERT_TRUE(iters.first == iters.second);
}

// ----
// edge
// ----

// std::pair<edge_descriptor, bool> edge (vertex_descriptor source, vertex_descriptor target, const Graph& graph)

TYPED_TEST(TestGraph, test_edge_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    
    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    const edge_descriptor e = add_edge(0, 1, g).first;

    ASSERT_EQ(2, num_vertices(g));
    ASSERT_EQ(1,    num_edges(g));

    const std::pair<edge_descriptor, bool> p = edge(0, 1, g);

    ASSERT_TRUE(e == p.first);
    ASSERT_TRUE(p.second);
}

TYPED_TEST(TestGraph, test_edge_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    const edge_descriptor e = add_edge(0, 1, g).first;

    ASSERT_EQ(2, num_vertices(g));
    ASSERT_EQ(1,    num_edges(g));

    const std::pair<edge_descriptor, bool> p1 = edge(0, 1, g);
    const std::pair<edge_descriptor, bool> p2 = edge(1, 0, g);

    ASSERT_TRUE(p1.first == e);
    ASSERT_TRUE(p1.second);

    ASSERT_TRUE(p1.first == e);
    ASSERT_FALSE(p2.second);
}

TYPED_TEST(TestGraph, test_edge_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;
    
    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    for (int i = 0; i < 100; ++i){
        const edge_descriptor e = add_edge(i, i + 1, g).first;

        ASSERT_EQ(i + 2, num_vertices(g));
        ASSERT_EQ(i + 1,    num_edges(g));

        const std::pair<edge_descriptor, bool> p1 = edge(i, i + 1, g);
        const std::pair<edge_descriptor, bool> p2 = edge(i + 1, i, g);

        ASSERT_TRUE(p1.first == e);
        ASSERT_TRUE(p1.second);

        ASSERT_TRUE(p1.first == e);
        ASSERT_FALSE(p2.second);
    }
}

// ------
// vertex
// ------

// std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor vertex, const Graph& graph)

TYPED_TEST(TestGraph, test_adjacent_vertices_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    
    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    add_vertex(g);

    ASSERT_EQ(1, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    std::pair<adjacency_iterator, adjacency_iterator> iters = adjacent_vertices(0, g);

    ASSERT_TRUE(iters.first == iters.second);

    add_edge(0, 1, g);

    ASSERT_EQ(2, num_vertices(g));
    ASSERT_EQ(1,    num_edges(g));

    iters = adjacent_vertices(0, g);

    ASSERT_FALSE(iters.first == iters.second);
    ASSERT_EQ(1, *iters.first);
    ASSERT_TRUE(++iters.first == iters.second);
}

TYPED_TEST(TestGraph, test_adjacent_vertices_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::adjacency_iterator adjacency_iterator;
    
    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    add_edge(0, 1, g);
    add_edge(0, 2, g);
    add_edge(0, 3, g);

    ASSERT_EQ(4, num_vertices(g));
    ASSERT_EQ(3,    num_edges(g));

    std::pair<adjacency_iterator, adjacency_iterator> iters = adjacent_vertices(0, g);

    ASSERT_FALSE(iters.first == iters.second);
    ASSERT_EQ(1, *iters.first);
    ++iters.first;

    ASSERT_FALSE(iters.first == iters.second);
    ASSERT_EQ(2, *iters.first);
    ++iters.first;

    ASSERT_FALSE(iters.first == iters.second);
    ASSERT_EQ(3, *iters.first);
    ++iters.first;

    ASSERT_TRUE(iters.first == iters.second);
}

// ----------
// add_vertex
// ----------

// vertex_descriptor add_vertex (Graph& graph)

TYPED_TEST(TestGraph, test_add_vertex_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    vertex_descriptor v1 = add_vertex(g);

    ASSERT_EQ(1, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    ASSERT_EQ(0, v1);
}

TYPED_TEST(TestGraph, test_add_vertex_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    for (int i = 0; i < 100; ++i){
        vertex_descriptor v = add_vertex(g);
        ASSERT_EQ(i, v);
        ASSERT_EQ(i + 1, num_vertices(g));
    }

    ASSERT_EQ(0,    num_edges(g));
}

TYPED_TEST(TestGraph, test_add_vertex_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    add_edge(5, 6, g);

    ASSERT_EQ(7, num_vertices(g));
    ASSERT_EQ(1,    num_edges(g));

    vertex_descriptor v = add_vertex(g);

    ASSERT_EQ(8, num_vertices(g));
    ASSERT_EQ(1,    num_edges(g));
    ASSERT_EQ(7, v);

    add_edge(91, 87, g);

    ASSERT_EQ(92, num_vertices(g));
    ASSERT_EQ(2,    num_edges(g));

    v = add_vertex(g);

    ASSERT_EQ(93, num_vertices(g));
    ASSERT_EQ(2,    num_edges(g));
    ASSERT_EQ(92, v);
}

// --------
// add_edge
// --------

// std::pair<edge_descriptor, bool> add_edge (vertex_descriptor source, vertex_descriptor target, Graph& graph)

TYPED_TEST(TestGraph, test_add_edge_1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    std::pair<edge_descriptor, bool> e = add_edge(0, 1, g);

    ASSERT_EQ(true, e.second);

    ASSERT_EQ(2, num_vertices(g));
    ASSERT_EQ(1,    num_edges(g));
}

TYPED_TEST(TestGraph, test_add_edge_2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    std::pair<edge_descriptor, bool> e = add_edge(0, 1, g);

    ASSERT_EQ(true, e.second);

    ASSERT_EQ(2, num_vertices(g));
    ASSERT_EQ(1,    num_edges(g));

    e = add_edge(0, 1, g);

    ASSERT_EQ(false, e.second);

    ASSERT_EQ(2, num_vertices(g));
    ASSERT_EQ(1,    num_edges(g));
}

TYPED_TEST(TestGraph, test_add_edge_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    std::pair<edge_descriptor, bool> e1 = add_edge(0, 1, g);
    std::pair<edge_descriptor, bool> e2 = add_edge(1, 0, g);
    std::pair<edge_descriptor, bool> e3 = add_edge(0, 1, g);
    std::pair<edge_descriptor, bool> e4 = add_edge(0, 0, g);

    ASSERT_EQ(true, e1.second);
    ASSERT_EQ(true, e2.second);
    ASSERT_EQ(false, e3.second);
    ASSERT_EQ(true, e4.second);

    ASSERT_EQ(2, num_vertices(g));
    ASSERT_EQ(3,    num_edges(g));
}

// -------
// my_find
// -------

TEST(MyFunctions, test_my_find_1) {
    const std::vector<int> x = {0, 1, 2, 3, 4, 5};
    const int index = my_find(x.begin(), x.end(), 3);

    ASSERT_EQ(3, index);
}

TEST(MyFunctions, test_my_find_2) {
    std::vector<int> x(100);
    for (int i = 0; i < 100; ++i){
        x[i] = i;
    }

    ASSERT_EQ(100, x.size());

    for (int i = 0; i < 100; ++i){
        const int index = my_find(x.begin(), x.end(), i);
        ASSERT_EQ(i, index);
    }

    ASSERT_EQ(-1, my_find(x.begin(), x.end(), 100));
    ASSERT_EQ(-1, my_find(x.begin(), x.end(), -1));
    ASSERT_EQ(-1, my_find(x.begin(), x.end(), 1234));
    ASSERT_EQ(-1, my_find(x.begin(), x.end(), 9999));
}

TYPED_TEST(TestGraph, test_my_find_3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_iterator      edge_iterator;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));
    ASSERT_EQ(0,    num_edges(g));

    const edge_descriptor e1 = add_edge(0, 1, g).first;
    const edge_descriptor e2 = add_edge(1, 2, g).first;
    const edge_descriptor e3 = add_edge(2, 3, g).first;

    ASSERT_EQ(4, num_vertices(g));
    ASSERT_EQ(3,    num_edges(g));

    const std::pair<edge_iterator, edge_iterator> iters = edges(g);

    ASSERT_EQ(0, my_find(iters.first, iters.second, e1));
    ASSERT_EQ(1, my_find(iters.first, iters.second, e2));
    ASSERT_EQ(2, my_find(iters.first, iters.second, e3));
}
