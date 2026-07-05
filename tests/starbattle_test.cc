#include "gtest/gtest.h"
#include "maxflow/maxflow.h"

TEST(MaxFlowTest, CorrectlyFindsMaxFlowA) {
  int s = 0;
  int t = 5;
  maxflow::Network network(t + 1);
  network.Connect(s, 1, 7);
  network.Connect(s, 4, 4);
  network.Connect(1, 2, 5);
  network.Connect(1, 3, 3);
  network.Connect(2, t, 8);
  network.Connect(3, 2, 3);
  network.Connect(3, t, 5);
  network.Connect(4, 1, 3);
  network.Connect(4, 3, 2);

  const maxflow::FlowNetwork flow_network =
      maxflow::EdmondKarp::MaxFlow(network, s, t);

  EXPECT_EQ(flow_network.GetMaxFlow(), 10);
}

TEST(MaxFlowTest, CorrectlyFindsMaxFlowB) {
  int s = 0;
  int t = 6;
  maxflow::Network network(t + 1);
  network.Connect(s, 1, 4);
  network.Connect(s, 3, 8);
  network.Connect(s, 2, 2);
  network.Connect(1, 4, 2);
  network.Connect(1, 3, 5);
  network.Connect(2, 3, 6);
  network.Connect(2, 5, 9);
  network.Connect(3, 4, 1);
  network.Connect(3, t, 4);
  network.Connect(3, 5, 3);
  network.Connect(4, t, 7);
  network.Connect(5, t, 5);

  const maxflow::FlowNetwork flow_network =
      maxflow::EdmondKarp::MaxFlow(network, s, t);

  EXPECT_EQ(flow_network.GetMaxFlow(), 12);
}
