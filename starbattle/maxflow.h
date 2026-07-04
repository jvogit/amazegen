#ifndef STARBATTLE_MAXFLOW_H_
#define STARBATTLE_MAXFLOW_H_

#include <ostream>
#include <vector>

namespace starbattle {

struct Node {
  size_t v;
  int capacity;
  int flow;
  bool residual;
};

using Graph = std::vector<std::vector<Node>>;
using Lookup = std::vector<std::vector<int>>;

class Network {
 public:
  Network(int size) : graph_(Graph(size, std::vector<Node>())) {}
  void Connect(size_t u, size_t v, int capacity);

 private:
  Graph graph_;

  friend class FlowNetwork;
};

class FlowNetwork {
 public:
  explicit FlowNetwork(Network network);

  int GetMaxFlow() const { return max_flow_; };

  friend std::ostream& operator<<(std::ostream& os,
                                  const FlowNetwork& flow_network);

 private:
  Graph graph_;
  Lookup lookup_;
  int max_flow_ = 0;

  friend class EdmondKarp;
};

class EdmondKarp {
 public:
  static FlowNetwork MaxFlow(const Network& network, int s, int t);
};

}  // namespace starbattle

#endif