//=======================================================================
// Copyright 2001 Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee,
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#include <boost/config.hpp>
#include <iostream>
#include <boost/graph/transpose_graph.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>

int main()
{
    using namespace boost;
    typedef adjacency_list< vecS, vecS, bidirectionalS,
        property< vertex_name_t, char > >
        graph_t;

    enum
    {
        a,
        b,
        c,
        d,
        e,
        f,
        g,
        N
    };
    graph_t G(N);
    property_map< graph_t, vertex_name_t >::type name_map = get(vertex_name, G);
    char name = 'a';
    graph_traits< graph_t >::vertex_iterator v, v_end;
    for (boost::tie(v, v_end) = vertices(G); v != v_end; ++v, ++name)
        name_map[*v] = name;

    typedef std::pair< int, int > E;
    E edge_array[] = { E(a, c), E(a, d), E(b, a), E(b, d), E(c, f), E(d, c),
        E(d, e), E(d, f), E(e, b), E(e, g), E(f, e), E(f, g) };
    for (int i = 0; i < 12; ++i)
        add_edge(edge_array[i].first, edge_array[i].second, G);

    print_graph(G, name_map);
    std::cout << std::endl;

    graph_t G_T;
    transpose_graph(G, G_T);

    print_graph(G_T, name_map);

    graph_traits< graph_t >::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(G); ei != ei_end; ++ei)
        assert(edge(target(*ei, G), source(*ei, G), G_T).second == true);
    return 0;
}
