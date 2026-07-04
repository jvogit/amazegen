#include "maxflow.h"

#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

#include "absl/log/check.h"

namespace starbattle {

namespace {

constexpr int kNoParentSentinel = -1;

int AugmentPath(internal::Graph graph, int s, int t) {
  std::queue<std::tuple<int, int>> q;
  std::vector<int> parent(graph.size(), kNoParentSentinel);
  parent[s] = -2;
  q.emplace(s, std::numeric_limits<int>::max());

  while (q.size() > 0) {
    const auto [u, flow_u] = q.front();
    q.pop();
    for (const auto& node : graph[u]) {
      int capacity = node.residual ? node.capacity : node.capacity - node.flow;
      if (parent[node.v] == kNoParentSentinel && node.capacity > 0) {
        parent[node.v] = u;
        int flow = std::min(flow_u, node.capacity);
        if (node.v == t) {
          return flow;
        }
        q.emplace(node.v, flow);
      }
    }
  }

  return 0;
}

}  // namespace
namespace internal {

void Network::Connect(int u, int v, int capacity) {
  CHECK(u < graph_.size());
  CHECK(v < graph_.size());

  graph_[u].push_back({
      .v = v,
      .capacity = capacity,
  });
}

FlowNetwork::FlowNetwork(Network network) : graph_(std::move(network.graph_)) {
  for (auto u = 0; u < network.graph_.size(); ++u) {
    for (const auto& node : network.graph_[u]) {
      if (node.residual) continue;
      graph_[node.v].emplace_back(u, node.capacity, 0, true);
    }
  }
}

}  // namespace internal

internal::FlowNetwork EdmondKarp::MaxFlow(const internal::Network& network,
                                          int s, int t) {
  internal::FlowNetwork flow_network(network);

  return flow_network;
}

}  // namespace starbattle
