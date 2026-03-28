#include <gtest/gtest.h>

#include "graph.h"

class NodeValidationOutEdgesTest_51 : public ::testing::Test {};

// Helper to create distinct dummy Edge* values without needing real Edge instances.
// Node and the tests only store/compare pointers; they never dereference them.
static Edge* DummyEdgePtr(int id) {
  return reinterpret_cast<Edge*>(static_cast<uintptr_t>(id));
}

// 1) Normal case: a freshly constructed Node has no validation out edges.
TEST_F(NodeValidationOutEdgesTest_51, InitiallyEmpty_51) {
  Node node("path", /*slash_bits=*/0);

  const std::vector<Edge*>& validation_edges = node.validation_out_edges();
  EXPECT_TRUE(validation_edges.empty());
}

// 2) Normal case: adding a single validation out edge makes it visible via
//    validation_out_edges(), and the pointer is preserved.
TEST_F(NodeValidationOutEdgesTest_51, AddSingleValidationOutEdge_51) {
  Node node("path", /*slash_bits=*/0);
  Edge* edge1 = DummyEdgePtr(1);

  node.AddValidationOutEdge(edge1);

  const std::vector<Edge*>& validation_edges = node.validation_out_edges();
  ASSERT_EQ(validation_edges.size(), 1u);
  EXPECT_EQ(validation_edges[0], edge1);
}

// 3) Normal case: adding multiple validation out edges preserves insertion order.
TEST_F(NodeValidationOutEdgesTest_51, AddMultipleValidationOutEdgesPreservesOrder_51) {
  Node node("path", /*slash_bits=*/0);
  Edge* edge1 = DummyEdgePtr(1);
  Edge* edge2 = DummyEdgePtr(2);
  Edge* edge3 = DummyEdgePtr(3);

  node.AddValidationOutEdge(edge1);
  node.AddValidationOutEdge(edge2);
  node.AddValidationOutEdge(edge3);

  const std::vector<Edge*>& validation_edges = node.validation_out_edges();
  ASSERT_EQ(validation_edges.size(), 3u);
  EXPECT_EQ(validation_edges[0], edge1);
  EXPECT_EQ(validation_edges[1], edge2);
  EXPECT_EQ(validation_edges[2], edge3);
}

// 4) Boundary / interaction: normal out_edges added via AddOutEdge()
//    should not appear in validation_out_edges().
TEST_F(NodeValidationOutEdgesTest_51, OutEdgesDoNotAffectValidationOutEdges_51) {
  Node node("path", /*slash_bits=*/0);
  Edge* normal_edge = DummyEdgePtr(10);
  Edge* validation_edge = DummyEdgePtr(20);

  node.AddOutEdge(normal_edge);

  // validation_out_edges() should still be empty.
  EXPECT_TRUE(node.validation_out_edges().empty());

  node.AddValidationOutEdge(validation_edge);

  // Now only the validation edge should be present.
  const std::vector<Edge*>& validation_edges = node.validation_out_edges();
  ASSERT_EQ(validation_edges.size(), 1u);
  EXPECT_EQ(validation_edges[0], validation_edge);
}

// 5) Boundary case: the same Edge* can be added multiple times as a validation
//    out edge; all entries should be observable.
TEST_F(NodeValidationOutEdgesTest_51, AllowsDuplicateValidationEdges_51) {
  Node node("path", /*slash_bits=*/0);
  Edge* edge = DummyEdgePtr(1);

  node.AddValidationOutEdge(edge);
  node.AddValidationOutEdge(edge);

  const std::vector<Edge*>& validation_edges = node.validation_out_edges();
  ASSERT_EQ(validation_edges.size(), 2u);
  EXPECT_EQ(validation_edges[0], edge);
  EXPECT_EQ(validation_edges[1], edge);
}
