// Boost.Graph library isomorphism test

// Copyright (C) 2001-20044 Douglas Gregor (dgregor at cs dot indiana dot edu)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org
//
// Revision History:
//
// 29 Nov 2001    Jeremy Siek
//      Changed to use Boost.Random.
// 29 Nov 2001    Doug Gregor
//      Initial checkin.

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <time.h> // clock used without std:: qualifier?
#include <boost/core/lightweight_test.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/isomorphism.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/lexical_cast.hpp>

#ifndef BOOST_NO_CXX11_HDR_RANDOM
#include <random>
typedef std::mt19937 random_generator_type;
#else
typedef boost::mt19937 random_generator_type;
#endif

using namespace boost;

#ifndef BOOST_NO_CXX98_RANDOM_SHUFFLE
template < typename Generator > struct random_functor
{
    random_functor(Generator& g) : g(g) {}
    std::size_t operator()(std::size_t n)
    {
        boost::uniform_int< std::size_t > distrib(0, n - 1);
        boost::variate_generator< random_generator_type&,
            boost::uniform_int< std::size_t > >
            x(g, distrib);
        return x();
    }
    Generator& g;
};
#endif

template < typename Graph1, typename Graph2 >
std::map<
    typename graph_traits< Graph1 >::vertex_descriptor,
    typename graph_traits< Graph2 >::vertex_descriptor
>
randomly_permute_graph(const Graph1& g1, Graph2& g2)
{
    // Need a clean graph to start with
    BOOST_TEST(num_vertices(g2) == 0);
    BOOST_TEST(num_edges(g2) == 0);

    typedef typename graph_traits< Graph1 >::vertex_descriptor vertex1;
    typedef typename graph_traits< Graph2 >::vertex_descriptor vertex2;
    typedef typename graph_traits< Graph1 >::edge_iterator edge_iterator;

    random_generator_type gen;

#ifndef BOOST_NO_CXX98_RANDOM_SHUFFLE
    random_functor< random_generator_type > rand_fun(gen);
#endif

    // Decide new order
    std::vector< vertex1 > orig_vertices;
    std::copy(vertices(g1).first, vertices(g1).second,
        std::back_inserter(orig_vertices));
#ifndef BOOST_NO_CXX98_RANDOM_SHUFFLE
    std::random_shuffle(orig_vertices.begin(), orig_vertices.end(), rand_fun);
#else
    std::shuffle(orig_vertices.begin(), orig_vertices.end(), gen);
#endif
    std::map< vertex1, vertex2 > vertex_map;

    for (std::size_t i = 0; i < num_vertices(g1); ++i)
    {
        vertex_map[orig_vertices[i]] = add_vertex(g2);
    }

    for (edge_iterator e = edges(g1).first; e != edges(g1).second; ++e)
    {
        add_edge(vertex_map[source(*e, g1)], vertex_map[target(*e, g1)], g2);
    }

    return vertex_map;
}

template < typename Graph >
void generate_random_digraph(Graph& g, double edge_probability)
{
    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator;
    random_generator_type random_gen;
    boost::uniform_real< double > distrib(0.0, 1.0);
    boost::variate_generator< random_generator_type&,
        boost::uniform_real< double > >
        random_dist(random_gen, distrib);

    for (vertex_iterator u = vertices(g).first; u != vertices(g).second; ++u)
    {
        vertex_iterator v = u;
        ++v;
        for (; v != vertices(g).second; ++v)
        {
            if (random_dist() <= edge_probability)
                add_edge(*u, *v, g);
        }
    }
}

void test_isomorphism2()
{
    using namespace boost::graph::keywords;
    typedef adjacency_list< vecS, vecS, bidirectionalS > graph1;
    typedef adjacency_list< listS, listS, bidirectionalS,
        property< vertex_index_t, int > >
        graph2;

    graph1 g1(2);
    add_edge(vertex(0, g1), vertex(1, g1), g1);
    add_edge(vertex(1, g1), vertex(1, g1), g1);
    graph2 g2;
    randomly_permute_graph(g1, g2);

    int v_idx = 0;
    for (graph2::vertex_iterator v = vertices(g2).first;
         v != vertices(g2).second; ++v)
    {
        put(vertex_index_t(), g2, *v, v_idx++);
    }

    std::map< graph1::vertex_descriptor, graph2::vertex_descriptor > mapping;

    bool isomorphism_correct;
    clock_t start = clock();
    BOOST_TEST(isomorphism_correct = boost::graph::isomorphism(g1, g2,
                    _vertex_index1_map = get(vertex_index, g1),
                    _isomorphism_map = make_assoc_property_map(mapping)));
    clock_t end = clock();

    std::cout << "Elapsed time (clock cycles): " << (end - start) << std::endl;

    bool verify_correct;
    BOOST_TEST(verify_correct
        = verify_isomorphism(g1, g2, make_assoc_property_map(mapping)));

    if (!isomorphism_correct || !verify_correct)
    {
        // Output graph 1
        {
            std::ofstream out("isomorphism_failure.bg1");
            out << num_vertices(g1) << std::endl;
            for (graph1::edge_iterator e = edges(g1).first;
                 e != edges(g1).second; ++e)
            {
                out << get(vertex_index_t(), g1, source(*e, g1)) << ' '
                    << get(vertex_index_t(), g1, target(*e, g1)) << std::endl;
            }
        }

        // Output graph 2
        {
            std::ofstream out("isomorphism_failure.bg2");
            out << num_vertices(g2) << std::endl;
            for (graph2::edge_iterator e = edges(g2).first;
                 e != edges(g2).second; ++e)
            {
                out << get(vertex_index_t(), g2, source(*e, g2)) << ' '
                    << get(vertex_index_t(), g2, target(*e, g2)) << std::endl;
            }
        }
    }
}

void test_isomorphism(int n, double edge_probability)
{
    using namespace boost::graph::keywords;
    typedef adjacency_list< vecS, vecS, bidirectionalS > graph1;
    typedef adjacency_list< listS, listS, bidirectionalS,
        property< vertex_index_t, int > >
        graph2;

    graph1 g1(n);
    generate_random_digraph(g1, edge_probability);
    graph2 g2;
    randomly_permute_graph(g1, g2);

    int v_idx = 0;
    for (graph2::vertex_iterator v = vertices(g2).first;
         v != vertices(g2).second; ++v)
    {
        put(vertex_index_t(), g2, *v, v_idx++);
    }

    std::map< graph1::vertex_descriptor, graph2::vertex_descriptor > mapping;

    bool isomorphism_correct;
    clock_t start = clock();
    BOOST_TEST(isomorphism_correct = boost::graph::isomorphism(g1, g2,
                    _isomorphism_map = make_assoc_property_map(mapping)));
    clock_t end = clock();

    std::cout << "Elapsed time (clock cycles): " << (end - start) << std::endl;

    bool verify_correct;
    BOOST_TEST(verify_correct
        = verify_isomorphism(g1, g2, make_assoc_property_map(mapping)));

    if (!isomorphism_correct || !verify_correct)
    {
        // Output graph 1
        {
            std::ofstream out("isomorphism_failure.bg1");
            out << num_vertices(g1) << std::endl;
            for (graph1::edge_iterator e = edges(g1).first;
                 e != edges(g1).second; ++e)
            {
                out << get(vertex_index_t(), g1, source(*e, g1)) << ' '
                    << get(vertex_index_t(), g1, target(*e, g1)) << std::endl;
            }
        }

        // Output graph 2
        {
            std::ofstream out("isomorphism_failure.bg2");
            out << num_vertices(g2) << std::endl;
            for (graph2::edge_iterator e = edges(g2).first;
                 e != edges(g2).second; ++e)
            {
                out << get(vertex_index_t(), g2, source(*e, g2)) << ' '
                    << get(vertex_index_t(), g2, target(*e, g2)) << std::endl;
            }
        }
    }
}

template<typename Graph>
struct ColorFunctor {
    typedef typename graph_traits< Graph >::vertex_descriptor argument_type;
    typedef int result_type;

    ColorFunctor(const Graph& g) : graph(g) {}

    inline result_type operator() (argument_type v) const {
        return get(vertex_color_t(), graph)(v);
    }

    inline result_type max() const {
      result_type max_result = std::numeric_limits<result_type>::min();
      typedef typename graph_traits< Graph >::vertex_iterator vertex_iter;
      for(vertex_iter iter = vertices(graph).first; iter != vertices(graph).second; ++iter) {
        max_result = std::max(max_result, this->operator()(*iter));
      }
      return max_result + 1;
    }

    const Graph& graph;
};

void test_colored_isomorphism(int n, double edge_probability)
{
    using namespace boost::graph::keywords;
    typedef adjacency_list< vecS, vecS, bidirectionalS, property< vertex_color_t, int > > graph1;
    typedef adjacency_list< listS, listS, bidirectionalS,
        property< vertex_index_t, int, property< vertex_color_t, int >
        >
    > graph2;

    typedef graph_traits< graph1 >::vertex_descriptor vertex1_t;
    typedef graph_traits< graph2 >::vertex_descriptor vertex2_t;
    typedef std::map< vertex1_t, vertex2_t > vertex_map_t;

    graph1 g1(n);
    generate_random_digraph(g1, edge_probability);

    graph2 g2;
    vertex_map_t vertex_map = randomly_permute_graph(g1, g2);

    std::vector< int > colors(n);
    typedef std::vector< int >::iterator colors_iter;
    colors_iter midpoint = colors.begin() + n / 2;
    std::fill(colors.begin(), midpoint, 0);
    std::fill(midpoint, colors.end(), 1);

    random_generator_type gen;

#ifndef BOOST_NO_CXX98_RANDOM_SHUFFLE
    random_functor< random_generator_type > rand_fun(gen);
    std::random_shuffle(colors.begin(), colors.end(), rand_fun);
#else
    std::shuffle(colors.begin(), colors.end(), gen);
#endif

    int v_idx = 0;
    for (graph1::vertex_iterator v = vertices(g1).first;
         v != vertices(g1).second; ++v)
    {
        put(get(vertex_color_t(), g1), *v, colors[v_idx]);
        put(get(vertex_color_t(), g2), vertex_map[*v], colors[v_idx]);
        v_idx += 1;
    }

    v_idx = 0;
    for (graph2::vertex_iterator v = vertices(g2).first;
         v != vertices(g2).second; ++v)
    {
        put(get(vertex_index_t(), g2), *v, v_idx);
        v_idx += 1;
    }

    typedef std::map< graph1::vertex_descriptor, graph2::vertex_descriptor > iso_map;
    iso_map mapping;

    bool isomorphism_correct;
    clock_t start = clock();
    BOOST_TEST(
        isomorphism_correct = isomorphism(
            g1,
            g2,
            isomorphism_map(make_assoc_property_map(mapping))
            .vertex_invariant1(ColorFunctor<graph1>(g1))
            .vertex_invariant2(ColorFunctor<graph2>(g2))
        )
    );
    clock_t end = clock();

    std::cout << "Elapsed time (clock cycles): " << (end - start) << std::endl;

    bool verify_correct;
    BOOST_TEST(verify_correct
        = verify_isomorphism(g1, g2, make_assoc_property_map(mapping)));

    if (!isomorphism_correct || !verify_correct)
    {
        // Output graph 1
        {
            std::ofstream out("colored_isomorphism_failure.bg1");
            out << num_vertices(g1) << std::endl;
            for (graph1::edge_iterator e = edges(g1).first;
                 e != edges(g1).second; ++e)
            {
                out << get(vertex_index_t(), g1, source(*e, g1)) << ' '
                    << get(vertex_index_t(), g1, target(*e, g1)) << std::endl;
            }
        }

        // Output graph 2
        {
            std::ofstream out("colored_isomorphism_failure.bg2");
            out << num_vertices(g2) << std::endl;
            for (graph2::edge_iterator e = edges(g2).first;
                 e != edges(g2).second; ++e)
            {
                out << get(vertex_index_t(), g2, source(*e, g2)) << ' '
                    << get(vertex_index_t(), g2, target(*e, g2)) << std::endl;
            }
        }
    }

    bool map_contains_null_vertices = false;
    {
        typedef graph_traits< graph2 >::vertex_descriptor vertex2_t;
        const vertex2_t g2_null_vertex = graph2::null_vertex();

        typedef iso_map::iterator map_iter;
        const map_iter end = mapping.end();
        for(map_iter iter = mapping.begin(); iter != end; ++iter) {
            if(iter->second == g2_null_vertex) {
                map_contains_null_vertices = true;
                break;
            }
        }
    }

    BOOST_TEST(!map_contains_null_vertices);

    // Map is bijective if each vertex of the second graph occurs only once
    {
      typedef graph_traits< graph2 >::vertex_descriptor vertex2_t;
      std::set< vertex2_t > vertex_set;

      typedef iso_map::iterator map_iter;
      const map_iter end = mapping.end();
      for(map_iter iter = mapping.begin(); iter != end; ++iter) {
        vertex_set.insert(iter->second);
      }

      BOOST_TEST(vertex_set.size() == mapping.size());
    }
}

int main(int argc, char* argv[])
{
    int n = argc < 3 ? 30 : boost::lexical_cast< int >(argv[1]);
    double edge_prob = argc < 3 ? 0.45 : boost::lexical_cast< double >(argv[2]);
    test_isomorphism(n, edge_prob);
    test_colored_isomorphism(n, edge_prob);

    return boost::report_errors();
}
