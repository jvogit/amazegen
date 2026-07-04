#ifndef STARBATTLE_MAXFLOW_H_
#define STARBATTLE_MAXFLOW_H_

#include <vector>

namespace starbattle {

namespace internal {

struct Node {
  int v;
  int capacity;
  int flow;
  bool residual;
};

using Graph = std::vector<std::vector<Node>>;

class Network {
 public:
  Network(int size) : graph_(Graph(size, std::vector<Node>())) {}
  void Connect(int u, int v, int capacity);

 private:
  Graph graph_;

  friend class FlowNetwork;
};

class FlowNetwork {
 public:
  explicit FlowNetwork(Network network);

  int GetMaxFlow() const { return max_flow_; };

 private:
  Graph graph_;
  int max_flow_ = 0;

  friend class EdmondKarp;
};

}  // namespace internal

class EdmondKarp {
 public:
  static internal::FlowNetwork MaxFlow(const internal::Network& network, int s,
                                       int t);
};

}  // namespace starbattle

#endif