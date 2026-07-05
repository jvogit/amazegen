#include "maxflow.h"

#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

#include "absl/log/check.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"

namespace maxflow {

namespace {

constexpr int kNoParentSentinel = -1;
constexpr int kDummyParentSentinel = -2;

struct FoundAugmentPath {
  int flow;
  std::vector<int> parent;

  explicit operator bool() const { return flow > 0; }
};

FoundAugmentPath AugmentPath(const Graph& graph, size_t s, size_t t) {
  std::queue<std::tuple<int, int>> q;
  std::vector<int> parent(graph.size(), kNoParentSentinel);
  parent[s] = kDummyParentSentinel;
  q.emplace(s, std::numeric_limits<int>::max());

  while (q.size() > 0) {
    const auto [u, flow_u] = q.front();
    q.pop();
    for (const auto& node : graph[u]) {
      int residual_capacity = node.capacity - node.flow;
      if (parent[node.v] == kNoParentSentinel && residual_capacity > 0) {
        parent[node.v] = u;
        int flow = std::min(flow_u, residual_capacity);
        if (node.v == t) {
          return {flow, parent};
        }
        q.emplace(node.v, flow);
      }
    }
  }

  return {0, parent};
}

}  // namespace

void Network::Connect(size_t u, size_t v, int capacity) {
  CHECK_LE(u, graph_.size());
  CHECK_LE(v, graph_.size());

  graph_[u].push_back({
      .v = v,
      .capacity = capacity,
  });
}

FlowNetwork::FlowNetwork(Network network)
    : graph_(std::move(network.graph_)),
      lookup_(graph_.size(), std::vector<int>(graph_.size(), -1)) {
  for (size_t u = 0; u < graph_.size(); ++u) {
    for (size_t v_i = 0; v_i < graph_[u].size(); ++v_i) {
      auto& node = graph_[u][v_i];
      if (node.residual) continue;
      lookup_[u][node.v] = v_i;
      lookup_[node.v][u] = graph_[node.v].size();
      graph_[node.v].emplace_back(u, 0, -node.flow, true);
    }
  }
}

FlowNetwork EdmondKarp::MaxFlow(const Network& network, int s, int t) {
  FlowNetwork flow_network(network);
  auto augment_path = AugmentPath(flow_network.graph_, s, t);
  while (augment_path) {
    const auto& [flow, parent] = augment_path;
    flow_network.max_flow_ += flow;
    int v = t;
    while (v != s) {
      int u = parent[v];
      CHECK(flow_network.lookup_[u][v] != -1);
      CHECK(flow_network.lookup_[v][u] != -1);
      auto& uv = flow_network.graph_[u][flow_network.lookup_[u][v]];
      auto& vu = flow_network.graph_[v][flow_network.lookup_[v][u]];
      uv.flow += flow;
      vu.capacity -= flow;
      CHECK_LE(uv.flow, uv.capacity);
      CHECK_LE(vu.capacity, vu.flow);
      v = u;
    }

    augment_path = AugmentPath(flow_network.graph_, s, t);
  }

  return flow_network;
}

std::ostream& operator<<(std::ostream& os, const FlowNetwork& flow_network) {
  for (size_t u = 0; u < flow_network.graph_.size(); ++u) {
    for (const auto& node : flow_network.graph_[u]) {
      if (node.residual) continue;
      os << absl::StrCat(u, "->", node.v)
         << absl::StrFormat(" flow=%d cap=%d", node.flow, node.capacity)
         << "\n";
    }
  }

  return os;
}

}  // namespace maxflow
