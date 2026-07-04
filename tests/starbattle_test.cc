#include "gtest/gtest.h"
#include "starbattle/maxflow.h"

TEST(MaxFlowTest, CorrectlyFindsMaxFlowSimple) {
  int s = 0;
  int t = 5;
  starbattle::internal::Network network(t + 1);
  network.Connect(s, 1, 7);
  network.Connect(s, 4, 4);
  network.Connect(1, 2, 5);
  network.Connect(1, 3, 3);
  network.Connect(2, t, 8);
  network.Connect(3, 2, 3);
  network.Connect(3, t, 5);
  network.Connect(4, 1, 3);
  network.Connect(4, 3, 2);

  const starbattle::internal::FlowNetwork flow_network =
      starbattle::EdmondKarp::MaxFlow(network, 0, 1);
  EXPECT_EQ(flow_network.GetMaxFlow(), 10);
}
