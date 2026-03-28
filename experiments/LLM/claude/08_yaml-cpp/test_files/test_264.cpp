#include <gtest/gtest.h>
#include <memory>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

// We need to include the internal header for AliasManager
// Since AliasManager is a nested class within NodeEvents, we include nodeevents.h
#include "nodeevents.h"

namespace YAML {
namespace {

class AliasManagerTest_264 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Setup if needed
  }

  void TearDown() override {
    // Cleanup if needed
  }
};

// Test that registering a reference and looking it up returns a non-zero anchor
TEST_F(AliasManagerTest_264, RegisterAndLookup_264) {
  NodeEvents::AliasManager manager;
  
  detail::node node1;
  manager.RegisterReference(node1);
  
  anchor_t anchor = manager.LookupAnchor(node1);
  EXPECT_NE(anchor, 0u);
}

// Test that looking up an unregistered node returns 0 (no anchor)
TEST_F(AliasManagerTest_264, LookupUnregisteredNode_264) {
  NodeEvents::AliasManager manager;
  
  detail::node node1;
  
  anchor_t anchor = manager.LookupAnchor(node1);
  EXPECT_EQ(anchor, 0u);
}

// Test that registering two different nodes gives different anchors
TEST_F(AliasManagerTest_264, RegisterTwoDifferentNodes_264) {
  NodeEvents::AliasManager manager;
  
  detail::node node1;
  detail::node node2;
  
  manager.RegisterReference(node1);
  manager.RegisterReference(node2);
  
  anchor_t anchor1 = manager.LookupAnchor(node1);
  anchor_t anchor2 = manager.LookupAnchor(node2);
  
  EXPECT_NE(anchor1, 0u);
  EXPECT_NE(anchor2, 0u);
  EXPECT_NE(anchor1, anchor2);
}

// Test that registering the same node twice doesn't change the anchor
TEST_F(AliasManagerTest_264, RegisterSameNodeTwice_264) {
  NodeEvents::AliasManager manager;
  
  detail::node node1;
  
  manager.RegisterReference(node1);
  anchor_t anchor_first = manager.LookupAnchor(node1);
  
  // Register same node again - insert with same key should not change
  manager.RegisterReference(node1);
  anchor_t anchor_second = manager.LookupAnchor(node1);
  
  EXPECT_EQ(anchor_first, anchor_second);
}

// Test that anchors are assigned incrementally (first anchor is 1)
TEST_F(AliasManagerTest_264, FirstAnchorIsOne_264) {
  NodeEvents::AliasManager manager;
  
  detail::node node1;
  manager.RegisterReference(node1);
  
  anchor_t anchor = manager.LookupAnchor(node1);
  EXPECT_EQ(anchor, 1u);
}

// Test registering multiple nodes produces sequential anchors
TEST_F(AliasManagerTest_264, SequentialAnchors_264) {
  NodeEvents::AliasManager manager;
  
  detail::node node1;
  detail::node node2;
  detail::node node3;
  
  manager.RegisterReference(node1);
  manager.RegisterReference(node2);
  manager.RegisterReference(node3);
  
  anchor_t anchor1 = manager.LookupAnchor(node1);
  anchor_t anchor2 = manager.LookupAnchor(node2);
  anchor_t anchor3 = manager.LookupAnchor(node3);
  
  EXPECT_EQ(anchor1, 1u);
  EXPECT_EQ(anchor2, 2u);
  EXPECT_EQ(anchor3, 3u);
}

// Test with a fresh AliasManager that no nodes are registered
TEST_F(AliasManagerTest_264, EmptyManagerLookup_264) {
  NodeEvents::AliasManager manager;
  
  detail::node node1;
  detail::node node2;
  
  EXPECT_EQ(manager.LookupAnchor(node1), 0u);
  EXPECT_EQ(manager.LookupAnchor(node2), 0u);
}

// Test that after registering one node, another unregistered node still returns 0
TEST_F(AliasManagerTest_264, MixedRegisteredAndUnregistered_264) {
  NodeEvents::AliasManager manager;
  
  detail::node node1;
  detail::node node2;
  
  manager.RegisterReference(node1);
  
  EXPECT_NE(manager.LookupAnchor(node1), 0u);
  EXPECT_EQ(manager.LookupAnchor(node2), 0u);
}

// Test registering many nodes
TEST_F(AliasManagerTest_264, RegisterManyNodes_264) {
  NodeEvents::AliasManager manager;
  
  const int N = 100;
  std::vector<std::unique_ptr<detail::node>> nodes;
  nodes.reserve(N);
  
  for (int i = 0; i < N; ++i) {
    nodes.push_back(std::make_unique<detail::node>());
    manager.RegisterReference(*nodes.back());
  }
  
  for (int i = 0; i < N; ++i) {
    anchor_t anchor = manager.LookupAnchor(*nodes[i]);
    EXPECT_EQ(anchor, static_cast<anchor_t>(i + 1));
  }
}

}  // namespace
}  // namespace YAML
