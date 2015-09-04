// --------------------------
// projects/c++/graph/Graph.h
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector

/**
 * @param b the begin iterator
 * @param e the end iterator
 * @param x the object to find
 * @return the index of the object x in the list, -1 if not found
 */
template <typename II, typename T>
int my_find (II b, II e, const T& x) {
    int i = 0;
    while (b != e){
        if (*b == x){
            return i;
        }
        ++i;
        ++b;
    }
    return -1;
}

// -----
// Graph
// -----

class Graph {
    public:
        // --------
        // typedefs
        // --------

        typedef int vertex_descriptor;
        typedef int edge_descriptor;

        typedef std::vector<vertex_descriptor>::const_iterator vertex_iterator;
        typedef std::vector<edge_descriptor>::const_iterator   edge_iterator;
        typedef std::vector<vertex_descriptor>::const_iterator adjacency_iterator;

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * @param source a vertex_descriptor to connect
         * @param target a vertex_descriptor to connect
         * @param graph the graph containing the two vertex_descriptors
         * @return a std::pair. first is the edge. second is whether the edge was successfully added.
         * connects two points on the graph
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor source, vertex_descriptor target, Graph& graph) {
            // <your code>
            // make the pair
            const std::pair<vertex_descriptor, vertex_descriptor> desired_edge = std::make_pair(source, target);

            // if it exists
            const int index = my_find(graph.e_list.begin(), graph.e_list.end(), desired_edge);
            if (index >= 0){
                // return the existing edge
                return std::make_pair(index, false);
            }

            const vertices_size_type max = std::max(source, target);
            while (max >= graph.v_list.size()){
                // add enough vertices
                add_vertex(graph);
            }

            // add the adjacency
            graph.v_list[source].push_back(target);
            // add the edge
            graph.e_list.push_back(desired_edge);
            // add the edge descriptor
            graph.ed_list.push_back(graph.ed_list.size());

            return std::make_pair(graph.ed_list.size() - 1, true);
        }

        // ----------
        // add_vertex
        // ----------

        /**
         * @param graph the graph to add to
         * @return a vertex_descriptor
         * adds a point to a graph
         */
        friend vertex_descriptor add_vertex (Graph& graph) {
            int size = graph.v_list.size();
            graph.vd_list.push_back(size);
            graph.v_list.push_back(std::vector<vertex_descriptor>());
            return size;
        }

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * @param vertex the vertex_descriptor
         * @param graph the graph
         * @return a pair of iterators that refer to points a point connects to
         * get a pair of iterators for the vertex's adjacent verticies
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor vertex, const Graph& graph) {
            return std::make_pair(graph.v_list[vertex].begin(), graph.v_list[vertex].end());
        }

        // ----
        // edge
        // ----

        /**
         * @param source a vertex_descriptor
         * @param target a vertex_descriptor
         * @param graph the graph
         * @return a std::pair. first is the edge, second is whether it exists in the graph
         * checks if edge is in graph
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor source, vertex_descriptor target, const Graph& graph) {
            // <your code>
            //std::pair<vertex_descriptor, vertex_descriptor> desired_edge = std::make_pair(source, target);
            int index = my_find(graph.e_list.begin(), graph.e_list.end(), std::make_pair(source, target));
            if (index >= 0){
                return std::make_pair(index, true);
            }
            return std::make_pair(graph.e_list.size(), false);
        }

        // -----
        // edges
        // -----

        /**
         * @param graph the graph
         * @return a std::pair of iterators. first is the first edge. second is the last edge.
         * gets iterators that can be used to iterate over all edges on the graph
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& graph) {
            return std::make_pair(graph.ed_list.begin(), graph.ed_list.end());
        }

        // ---------
        // num_edges
        // ---------

        /**
         * @param graph the graph
         * @return the total number of edges in the graph
         */
        friend edges_size_type num_edges (const Graph& graph) {
            return graph.e_list.size();
        }

        // ------------
        // num_vertices
        // ------------

        /**
         * @param graph the graph
         * @return the total number of vertices in the graph
         */
        friend vertices_size_type num_vertices (const Graph& graph) {
            return graph.v_list.size();
        }

        // ------
        // source
        // ------

        /**
         * @param edge the edge to find the source of
         * @param graph the graph
         * @return the source vertex_descriptor in the edge
         */
        friend vertex_descriptor source (edge_descriptor edge, const Graph& graph) {
            return graph.e_list[edge].first;
        }

        // ------
        // target
        // ------

        /**
         * @param edge the edge to find the target of
         * @param graph the graph
         * @return the target vertex_descriptor in the edge
         */
        friend vertex_descriptor target (edge_descriptor edge, const Graph& graph) {
            return graph.e_list[edge].second;
        }

        // ------
        // vertex
        // ------

        /**
         * @param n the index
         * @param graph the graph
         * @return the nth vertex_descriptor in the graph
         * gets the nth vertex in the graph
         */
        friend vertex_descriptor vertex (vertices_size_type n, const Graph& graph) {
            return n;
        }

        // --------
        // vertices
        // --------

        /**
         * @param graph the graph
         * @return a std::pair of iterators. first is the first vertex. second is the last vertex.
         * gets iterators that can be used to iterate over all verticies on the graph
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& graph) {
            return std::make_pair(graph.vd_list.begin(), graph.vd_list.end());
        }

    private:
        // ----
        // data
        // ----

        std::vector< std::vector<vertex_descriptor> > v_list; // something like this
        std::vector< std::pair<vertex_descriptor, vertex_descriptor> > e_list;

        std::vector<vertex_descriptor> vd_list;
        std::vector<edge_descriptor>   ed_list;

        // -----
        // valid
        // -----

        /**
         * @return a bool indicating if any invariants have been broken.
         * class invariant, True = good, False = bad
         */
        bool valid () const {
            // <your code>
            // no two same edges
            // no two same vertices
            // each vertex should not have the same adjacent vertex twice
            return true;
        }

    public:
        // ------------
        // constructors
        // ------------

        /**
         * the default constructor for graph
         */
        Graph () {
            // <your code>
            assert(valid());
        }

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
};

#endif // Graph_h
