#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include "csv_routes.hpp"
#include "graph/graph.hpp"
#include "graph/algorithm/mis.hpp"
#include "graph/container/dynamic_graph.hpp"
#include "graph/views/incidence.hpp"
#ifdef _MSC_VER
#  include "Windows.h"
#endif

#define TEST_OPTION_OUTPUT (1) // output tests for visual inspection
#define TEST_OPTION_GEN (2)    // generate unit test code to be pasted into this file
#define TEST_OPTION_TEST (3)   // run unit tests
#define TEST_OPTION TEST_OPTION_TEST

using std::cout;
using std::endl;

using graph::vertex_t;
using graph::vertex_id_t;
using graph::vertex_reference_t;
using graph::vertex_iterator_t;
using graph::vertex_edge_range_t;
using graph::edge_t;

using graph::vertices;
using graph::edges;
using graph::vertex_value;
using graph::target_id;
using graph::target;
using graph::edge_value;
using graph::find_vertex;
using graph::vertex_id;

using routes_vol_graph_traits = graph::container::vol_graph_traits<double, std::string, std::string>;
using routes_vol_graph_type   = graph::container::dynamic_adjacency_graph<routes_vol_graph_traits>;

#if TEST_OPTION == TEST_OPTION_OUTPUT
TEST_CASE("Maximal Independent Set Algorithm", "[mis]") {
  init_console();
  using G  = routes_vol_graph_type;
  auto&& g = load_ordered_graph<G>(TEST_DATA_ROOT_DIR "germany_routes.csv", name_order_policy::source_order_found);

  SECTION("default seed(0)") {
    std::set<vertex_id_t<G>> mis;
    cout << "MIS seed with " << vertex_value(g, *find_vertex(g, 0)) << endl;
    graph::maximal_independent_set(g, std::inserter(mis, mis.begin()));

    for (auto&& uid : mis) {
      cout << uid << " " << vertex_value(g, *find_vertex(g, uid)) << endl;
    }
  }
  SECTION("seed=4") {
    std::vector<vertex_id_t<G>> mis;
    cout << "MIS seed with " << vertex_value(g, *find_vertex(g, 4)) << endl;
    graph::maximal_independent_set(g, std::back_inserter(mis), 4);

    for (auto&& uid : mis) {
      cout << uid << " " << vertex_value(g, *find_vertex(g, uid)) << endl;
    }
  }
}
#elif TEST_OPTION == TEST_OPTION_TEST
TEST_CASE("Maximal Independent Set Algorithm", "[mis]") {
  init_console();
  using G  = routes_vol_graph_type;
  auto&& g = load_ordered_graph<G>(TEST_DATA_ROOT_DIR "germany_routes.csv", name_order_policy::source_order_found);

  SECTION("default seed(0)") {
    std::set<vertex_id_t<G>> mis;
    graph::maximal_independent_set(g, std::inserter(mis, mis.begin()));

    for (auto&& uid : mis) {
      for (auto&& [vid, v] : graph::views::incidence(g, uid)) {
        REQUIRE(mis.find(vid) == mis.end());
      }
    }
  }
  SECTION("seed=4") {
    std::vector<vertex_id_t<G>> mis;
    graph::maximal_independent_set(g, std::back_inserter(mis), 4);
    REQUIRE(mis.size() == 5);
  }
}
#endif
