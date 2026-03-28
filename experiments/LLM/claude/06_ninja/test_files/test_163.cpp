#include "gtest/gtest.h"
#include "command_collector.h"
#include "graph.h"

// We need to create minimal Rule for non-phony edges
#include "state.h"

class CommandCollectorTest_163 : public ::testing::Test {
protected:
  State state_;

  // Helper to create a node
  Node* MakeNode(const std::string& path) {
    return state_.GetNode(path, 0);
  }

  // Helper to create a non-phony edge with a rule
  Edge* MakeEdge(const std::string& rule_name = "cat") {
    const Rule* rule = state_.bindings_.LookupRule(rule_name);
    if (!rule) {
      state_.bindings_.AddRule(new Rule(rule_name));
      rule = state_.bindings_.LookupRule(rule_name);
    }
    Edge* edge = state_.AddEdge(rule);
    return edge;
  }

  // Helper to create a phony edge
  Edge* MakePhonyEdge() {
    return state_.AddEdge(&State::kPhonyRule);
  }

  void AddInput(Edge* edge, Node* node) {
    edge->inputs_.push_back(node);
    node->AddOutEdge(edge);
  }

  void AddOutput(Edge* edge, Node* node) {
    edge->outputs_.push_back(node);
    node->set_in_edge(edge);
  }
};

// Test that collecting from a leaf node (no in_edge) results in no edges
TEST_F(CommandCollectorTest_163, LeafNodeProducesNoEdges_163) {
  Node* leaf = MakeNode("leaf.txt");

  CommandCollector collector;
  collector.CollectFrom(leaf);

  EXPECT_TRUE(collector.in_edges.empty());
}

// Test that collecting from a node with a single non-phony in_edge collects that edge
TEST_F(CommandCollectorTest_163, SingleNonPhonyEdge_163) {
  Node* input = MakeNode("input.txt");
  Node* output = MakeNode("output.txt");
  Edge* edge = MakeEdge("cat");
  AddInput(edge, input);
  AddOutput(edge, output);

  CommandCollector collector;
  collector.CollectFrom(output);

  ASSERT_EQ(1u, collector.in_edges.size());
  EXPECT_EQ(edge, collector.in_edges[0]);
}

// Test that collecting from a node with a phony in_edge does NOT add it to in_edges
TEST_F(CommandCollectorTest_163, PhonyEdgeNotCollected_163) {
  Node* input = MakeNode("input.txt");
  Node* output = MakeNode("output.txt");
  Edge* edge = MakePhonyEdge();
  AddInput(edge, input);
  AddOutput(edge, output);

  CommandCollector collector;
  collector.CollectFrom(output);

  EXPECT_TRUE(collector.in_edges.empty());
}

// Test collecting from a chain: A -> edge1 -> B -> edge2 -> C
// Both edges should be collected, with edge1 appearing before edge2
TEST_F(CommandCollectorTest_163, ChainOfEdges_163) {
  Node* a = MakeNode("a.txt");
  Node* b = MakeNode("b.txt");
  Node* c = MakeNode("c.txt");

  Edge* edge1 = MakeEdge("cat");
  AddInput(edge1, a);
  AddOutput(edge1, b);

  Edge* edge2 = MakeEdge("cat");
  AddInput(edge2, b);
  AddOutput(edge2, c);

  CommandCollector collector;
  collector.CollectFrom(c);

  ASSERT_EQ(2u, collector.in_edges.size());
  // edge1 should come before edge2 because inputs are recursed first
  EXPECT_EQ(edge1, collector.in_edges[0]);
  EXPECT_EQ(edge2, collector.in_edges[1]);
}

// Test that visiting the same node twice does not duplicate edges
TEST_F(CommandCollectorTest_163, DuplicateNodeVisitNoDuplication_163) {
  Node* input = MakeNode("input.txt");
  Node* output = MakeNode("output.txt");
  Edge* edge = MakeEdge("cat");
  AddInput(edge, input);
  AddOutput(edge, output);

  CommandCollector collector;
  collector.CollectFrom(output);
  collector.CollectFrom(output);

  ASSERT_EQ(1u, collector.in_edges.size());
  EXPECT_EQ(edge, collector.in_edges[0]);
}

// Test diamond dependency: D depends on B and C, both of which depend on A
TEST_F(CommandCollectorTest_163, DiamondDependency_163) {
  Node* a = MakeNode("a.txt");
  Node* b = MakeNode("b.txt");
  Node* c = MakeNode("c.txt");
  Node* d = MakeNode("d.txt");

  Edge* edgeAB = MakeEdge("cat");
  AddInput(edgeAB, a);
  AddOutput(edgeAB, b);

  Edge* edgeAC = MakeEdge("cat");
  AddInput(edgeAC, a);
  AddOutput(edgeAC, c);

  Edge* edgeBCD = MakeEdge("cat");
  AddInput(edgeBCD, b);
  AddInput(edgeBCD, c);
  AddOutput(edgeBCD, d);

  CommandCollector collector;
  collector.CollectFrom(d);

  // Should have 3 edges: edgeAB, edgeAC, edgeBCD
  ASSERT_EQ(3u, collector.in_edges.size());
  // edgeAB is collected first (recursing into b's inputs first)
  // Then edgeAC (recursing into c's inputs, a already visited)
  // Then edgeBCD
  EXPECT_EQ(edgeAB, collector.in_edges[0]);
  EXPECT_EQ(edgeAC, collector.in_edges[1]);
  EXPECT_EQ(edgeBCD, collector.in_edges[2]);
}

// Test that multiple inputs from different nodes work correctly
TEST_F(CommandCollectorTest_163, MultipleInputs_163) {
  Node* in1 = MakeNode("in1.txt");
  Node* in2 = MakeNode("in2.txt");
  Node* out = MakeNode("out.txt");

  Edge* edge = MakeEdge("cat");
  AddInput(edge, in1);
  AddInput(edge, in2);
  AddOutput(edge, out);

  CommandCollector collector;
  collector.CollectFrom(out);

  ASSERT_EQ(1u, collector.in_edges.size());
  EXPECT_EQ(edge, collector.in_edges[0]);
}

// Test that collecting from two separate subgraphs works
TEST_F(CommandCollectorTest_163, TwoSeparateSubgraphs_163) {
  Node* a = MakeNode("a.txt");
  Node* b = MakeNode("b.txt");
  Edge* edge1 = MakeEdge("cat");
  AddInput(edge1, a);
  AddOutput(edge1, b);

  Node* c = MakeNode("c.txt");
  Node* d = MakeNode("d.txt");
  Edge* edge2 = MakeEdge("cat");
  AddInput(edge2, c);
  AddOutput(edge2, d);

  CommandCollector collector;
  collector.CollectFrom(b);
  collector.CollectFrom(d);

  ASSERT_EQ(2u, collector.in_edges.size());
  EXPECT_EQ(edge1, collector.in_edges[0]);
  EXPECT_EQ(edge2, collector.in_edges[1]);
}

// Test phony edge in the middle of a chain: A -> phony -> B -> real -> C
// Only the real edge should be collected
TEST_F(CommandCollectorTest_163, PhonyEdgeInMiddleOfChain_163) {
  Node* a = MakeNode("a.txt");
  Node* b = MakeNode("b.txt");
  Node* c = MakeNode("c.txt");

  Edge* phonyEdge = MakePhonyEdge();
  AddInput(phonyEdge, a);
  AddOutput(phonyEdge, b);

  Edge* realEdge = MakeEdge("cat");
  AddInput(realEdge, b);
  AddOutput(realEdge, c);

  CommandCollector collector;
  collector.CollectFrom(c);

  // The phony edge should not be in in_edges, but the real edge should
  ASSERT_EQ(1u, collector.in_edges.size());
  EXPECT_EQ(realEdge, collector.in_edges[0]);
}

// Test that in_edges is initially empty
TEST_F(CommandCollectorTest_163, InitiallyEmpty_163) {
  CommandCollector collector;
  EXPECT_TRUE(collector.in_edges.empty());
}

// Test collecting from a node whose in_edge has no inputs
TEST_F(CommandCollectorTest_163, EdgeWithNoInputs_163) {
  Node* out = MakeNode("out.txt");
  Edge* edge = MakeEdge("cat");
  AddOutput(edge, out);
  // No inputs added

  CommandCollector collector;
  collector.CollectFrom(out);

  ASSERT_EQ(1u, collector.in_edges.size());
  EXPECT_EQ(edge, collector.in_edges[0]);
}

// Test deep chain to verify recursion works
TEST_F(CommandCollectorTest_163, DeepChain_163) {
  const int depth = 20;
  std::vector<Node*> nodes;
  std::vector<Edge*> edges;

  for (int i = 0; i <= depth; ++i) {
    nodes.push_back(MakeNode("node" + std::to_string(i) + ".txt"));
  }

  for (int i = 0; i < depth; ++i) {
    Edge* edge = MakeEdge("cat");
    AddInput(edge, nodes[i]);
    AddOutput(edge, nodes[i + 1]);
    edges.push_back(edge);
  }

  CommandCollector collector;
  collector.CollectFrom(nodes[depth]);

  ASSERT_EQ(static_cast<size_t>(depth), collector.in_edges.size());
  for (int i = 0; i < depth; ++i) {
    EXPECT_EQ(edges[i], collector.in_edges[i]);
  }
}

// Test that the same edge shared by two different output nodes is only collected once
TEST_F(CommandCollectorTest_163, SharedEdgeCollectedOnce_163) {
  Node* input = MakeNode("input.txt");
  Node* out1 = MakeNode("out1.txt");
  Node* out2 = MakeNode("out2.txt");

  Edge* edge = MakeEdge("cat");
  AddInput(edge, input);
  AddOutput(edge, out1);
  AddOutput(edge, out2);

  CommandCollector collector;
  collector.CollectFrom(out1);
  collector.CollectFrom(out2);

  // Edge should appear only once even though we collected from two outputs of the same edge
  ASSERT_EQ(1u, collector.in_edges.size());
  EXPECT_EQ(edge, collector.in_edges[0]);
}
