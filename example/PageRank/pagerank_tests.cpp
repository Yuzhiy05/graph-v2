#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include "csv_routes.hpp"
#include "graph/graph.hpp"
#include "graph/container/dynamic_graph.hpp"
#include "graph/algorithm/pagerank.hpp"
#include "graph/views/incidence.hpp"
#include "graph/views/edgelist.hpp"
#include <cassert>
#ifdef _MSC_VER
#  include "Windows.h"
#endif

#define TEST_OPTION_OUTPUT (1) // output tests for visual inspection
#define TEST_OPTION_GEN (2)    // generate unit test code to be pasted into this file
#define TEST_OPTION_TEST (3)   // run unit tests
#define TEST_OPTION TEST_OPTION_OUTPUT

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

using routes_volf_graph_traits = graph::container::vofl_graph_traits<double, std::string, std::string>;
using routes_volf_graph_type   = graph::container::dynamic_adjacency_graph<routes_volf_graph_traits>;

TEST_CASE("PageRank", "[pagerank]") {
  init_console();
  using G  = routes_volf_graph_type;
  auto&& g = load_ordered_graph<G>(TEST_DATA_ROOT_DIR "germany_routes.csv", name_order_policy::source_order_found);

  std::vector<double> page_rank(size(vertices(g)));
  graph::pagerank(g, page_rank, 0.85, 1e-4, 10);

  std::vector<double> answer = {0.051086017487729, 0.065561667371485, 0.106818581147795, 0.141889899564636,
                                0.065561667371485, 0.078952299317762, 0.065561667371485, 0.078952299317762,
                                0.260972178563747, 0.084643725419772};

  for (auto&& [uid, u] : graph::views::vertexlist(g)) {
    REQUIRE(page_rank[uid] == Approx(answer[uid]).epsilon(1e-4));
  }
}