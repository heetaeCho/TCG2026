// File: graph_inputscollector_test_71.cc

#include "graph.h"

#include "gtest/gtest.h"

#include <algorithm>

// Helper: minimal graph with a single leaf input feeding a single output.
struct SingleEdgeGraph {
  Node in;
  Node out;
  Edge edge;

  SingleEdgeGraph()
      : in("in", 0u),
        out("out", 0u),
        edge() {
    // Wire edge <-> nodes.
    edge.inputs_.push_back(&in);
    edge.outputs_.push_back(&out);
    out.set_in_edge(&edge);
    in.AddOutEdge(&edge);
  }
};

// Helper: graph where one input is shared by two different outputs.
//
//   in  ->  out1
//    \
//     ->  out2
//
struct SharedInputGraph {
  Node in;
  Node out1;
  Node out2;
  Edge edge1;
  Edge edge2;

  SharedInputGraph()
      : in("in", 0u),
        out1("out1", 0u),
        out2("out2", 0u),
        edge1(),
        edge2() {
    edge1.inputs_.push_back(&in);
    edge1.outputs_.push_back(&out1);
    out1.set_in_edge(&edge1);
    in.AddOutEdge(&edge1);

    edge2.inputs_.push_back(&in);
    edge2.outputs_.push_back(&out2);
    out2.set_in_edge(&edge2);
    in.AddOutEdge(&edge2);
  }
};

// Helper: simple chain in -> mid -> out (for transitive-input behavior).
struct ChainGraph {
  Node in;
  Node mid;
  Node out;
  Edge edge_in_mid;
  Edge edge_mid_out;

  ChainGraph()
      : in("in", 0u),
        mid("mid", 0u),
        out("out", 0u),
        edge_in_mid(),
        edge_mid_out() {
    // in -> mid
    edge_in_mid.inputs_.push_back(&in);
    edge_in_mid.outputs_.push_back(&mid);
    mid.set_in_edge(&edge_in_mid);
    in.AddOutEdge(&edge_in_mid);

    // mid -> out
    edge_mid_out.inputs_.push_back(&mid);
    edge_mid_out.outputs_.push_back(&out);
    out.set_in_edge(&edge_mid_out);
    mid.AddOutEdge(&edge_mid_out);
  }
};

struct InputsCollectorTest_71 : public ::testing::Test {};

// 1) Brand-new collector should expose an empty inputs() vector.
TEST_F(InputsCollectorTest_71, InitiallyEmpty_71) {
  InputsCollector collector;

  const std::vector<const Node*>& inputs = collector.inputs();
  EXPECT_TRUE(inputs.empty());
}

// 2) Visiting a node with a single leaf input should collect that input.
TEST_F(InputsCollectorTest_71, CollectsDirectLeafInput_71) {
  SingleEdgeGraph g;
  InputsCollector collector;

  collector.VisitNode(&g.out);
  const std::vector<const Node*>& inputs = collector.inputs();

  ASSERT_EQ(1u, inputs.size());
  EXPECT_EQ(&g.in, inputs[0]);
}

// 3) Visiting two different roots that share the same input should not
//    duplicate that input in the returned inputs().
TEST_F(InputsCollectorTest_71, AvoidsDuplicateInputsForSharedLeaf_71) {
  SharedInputGraph g;
  InputsCollector collector;

  // Visit both outputs that depend on the same leaf.
  collector.VisitNode(&g.out1);
  collector.VisitNode(&g.out2);

  const std::vector<const Node*>& inputs = collector.inputs();

  // We expect the shared input to appear exactly once.
  ASSERT_EQ(1u, inputs.size());
  EXPECT_EQ(&g.in, inputs[0]);
}

// 4) Reset() should clear both collected inputs and any internal visitation
//    state so that a second traversal behaves like a first one.
TEST_F(InputsCollectorTest_71, ResetClearsInputsAndVisitedNodes_71) {
  SingleEdgeGraph g;
  InputsCollector collector;

  // First traversal: should collect the single leaf.
  collector.VisitNode(&g.out);
  ASSERT_EQ(1u, collector.inputs().size());
  EXPECT_EQ(&g.in, collector.inputs()[0]);

  // Reset and traverse again; behavior should be identical.
  collector.Reset();
  EXPECT_TRUE(collector.inputs().empty());

  collector.VisitNode(&g.out);
  ASSERT_EQ(1u, collector.inputs().size());
  EXPECT_EQ(&g.in, collector.inputs()[0]);
}

// 5) Visiting a node at the end of a simple chain (in -> mid -> out)
//    should at least collect the original leaf input (transitive behavior)
//    regardless of whether intermediate nodes are treated as inputs.
TEST_F(InputsCollectorTest_71, CollectsTransitiveLeafInputs_71) {
  ChainGraph g;
  InputsCollector collector;

  collector.VisitNode(&g.out);
  const std::vector<const Node*>& inputs = collector.inputs();

  // The original leaf node must be present somewhere in the collected inputs.
  auto it = std::find(inputs.begin(), inputs.end(), &g.in);
  EXPECT_NE(it, inputs.end());
}
