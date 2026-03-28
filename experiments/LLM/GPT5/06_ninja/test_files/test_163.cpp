// File: command_collector_test_163.cc

#include "command_collector.h"
#include "graph.h"
#include "state.h"

#include "gtest/gtest.h"

class CommandCollectorTest_163 : public ::testing::Test {
protected:
  CommandCollector collector_;
};

// Node with no in_edge(): nothing should be collected.
TEST_F(CommandCollectorTest_163, NodeWithoutInEdgeProducesNoEdges_163) {
  Node node("out", 0);

  collector_.CollectFrom(&node);

  EXPECT_TRUE(collector_.in_edges.empty());
}

// Single non-phony edge reachable from the start node is collected once.
TEST_F(CommandCollectorTest_163, SingleNonPhonyEdgeCollectedOnce_163) {
  Node input("in", 0);
  Node output("out", 0);
  Edge edge;

  edge.inputs_.push_back(&input);
  edge.outputs_.push_back(&output);
  output.set_in_edge(&edge);

  collector_.CollectFrom(&output);

  ASSERT_EQ(1u, collector_.in_edges.size());
  EXPECT_EQ(&edge, collector_.in_edges[0]);
}

// A simple chain A -> e1 -> B -> e2 -> C is collected in order [e1, e2],
// i.e. from requisites toward dependents.
TEST_F(CommandCollectorTest_163, ChainCollectedInRequisiteToDependentOrder_163) {
  Node a("a", 0);
  Node b("b", 0);
  Node c("c", 0);

  Edge e1;  // a -> b
  e1.inputs_.push_back(&a);
  e1.outputs_.push_back(&b);
  b.set_in_edge(&e1);

  Edge e2;  // b -> c
  e2.inputs_.push_back(&b);
  e2.outputs_.push_back(&c);
  c.set_in_edge(&e2);

  collector_.CollectFrom(&c);

  ASSERT_EQ(2u, collector_.in_edges.size());
  EXPECT_EQ(&e1, collector_.in_edges[0]);
  EXPECT_EQ(&e2, collector_.in_edges[1]);
}

// Starting from a node whose in_edge is phony: that phony edge should NOT
// appear in the result, but its inputs (and their producing non-phony edges)
// are still traversed and collected.
TEST_F(CommandCollectorTest_163, PhonyEdgeSkippedButInputsTraversed_163) {
  Node source("src", 0);
  Node phony_input("phony_input", 0);
  Node root("root", 0);

  // real_edge: source -> phony_input (non-phony)
  Edge real_edge;
  real_edge.inputs_.push_back(&source);
  real_edge.outputs_.push_back(&phony_input);
  phony_input.set_in_edge(&real_edge);

  // phony_edge: phony_input -> root (phony)
  Edge phony_edge;
  phony_edge.rule_ = const_cast<Rule*>(&State::kPhonyRule);
  phony_edge.inputs_.push_back(&phony_input);
  phony_edge.outputs_.push_back(&root);
  root.set_in_edge(&phony_edge);

  collector_.CollectFrom(&root);

  // Only the real edge should be recorded; the phony one is followed but not
  // added to in_edges.
  ASSERT_EQ(1u, collector_.in_edges.size());
  EXPECT_EQ(&real_edge, collector_.in_edges[0]);
}

// If the same Edge is reachable from multiple starting nodes, it should
// be collected only once thanks to visited_edges_.
TEST_F(CommandCollectorTest_163, SharedEdgeCollectedOnlyOnceFromMultipleRoots_163) {
  Node input("input", 0);
  Node out1("out1", 0);
  Node out2("out2", 0);

  Edge shared_edge;
  shared_edge.inputs_.push_back(&input);
  shared_edge.outputs_.push_back(&out1);
  shared_edge.outputs_.push_back(&out2);

  out1.set_in_edge(&shared_edge);
  out2.set_in_edge(&shared_edge);

  collector_.CollectFrom(&out1);
  collector_.CollectFrom(&out2);

  ASSERT_EQ(1u, collector_.in_edges.size());
  EXPECT_EQ(&shared_edge, collector_.in_edges[0]);
}

// A cyclic graph reachable via in_edge()/inputs_ should not cause infinite
// recursion because visited_nodes_ short-circuits revisits.
TEST_F(CommandCollectorTest_163, CyclicGraphDoesNotInfiniteLoopAndCollectsEachEdgeOnce_163) {
  Node a("a", 0);
  Node b("b", 0);

  Edge e1;  // b -> a
  e1.inputs_.push_back(&b);
  e1.outputs_.push_back(&a);
  a.set_in_edge(&e1);

  Edge e2;  // a -> b
  e2.inputs_.push_back(&a);
  e2.outputs_.push_back(&b);
  b.set_in_edge(&e2);

  collector_.CollectFrom(&a);

  ASSERT_EQ(2u, collector_.in_edges.size());
  // The deeper edge (e2) is visited first, then e1.
  EXPECT_EQ(&e2, collector_.in_edges[0]);
  EXPECT_EQ(&e1, collector_.in_edges[1]);
}
