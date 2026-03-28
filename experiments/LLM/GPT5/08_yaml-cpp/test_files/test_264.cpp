// TEST_ID: 264
//
// Unit tests for YAML::NodeEvents::AliasManager
//
// Focus: observable behavior via the public interface:
//  - RegisterReference(const detail::node&)
//  - LookupAnchor(const detail::node&) const
//
// Constraints respected:
//  - Treat implementation as black box (no assumptions about internal data structures)
//  - Only verify observable outcomes (returned anchors, stability, uniqueness, no-throw)

#include <gtest/gtest.h>

#include <set>
#include <vector>

#include "TestProjects/yaml-cpp/src/nodeevents.h"
#include "yaml-cpp/node/detail/node.h"

namespace {

class AliasManagerTest_264 : public ::testing::Test {
protected:
  using AliasManager = YAML::NodeEvents::AliasManager;
  using Node = YAML::detail::node;
};

TEST_F(AliasManagerTest_264, LookupOnUnregisteredNodeReturnsDefaultAnchor_264) {
  AliasManager mgr;
  Node n;

  // If a node hasn't been registered, LookupAnchor should be safe to call and
  // should return a default/empty anchor (observable contract by type semantics).
  const YAML::anchor_t a = mgr.LookupAnchor(n);
  EXPECT_EQ(a, YAML::anchor_t());
}

TEST_F(AliasManagerTest_264, RegisterReferenceMakesLookupReturnNonDefaultAnchor_264) {
  AliasManager mgr;
  Node n;

  mgr.RegisterReference(n);

  const YAML::anchor_t a = mgr.LookupAnchor(n);
  EXPECT_NE(a, YAML::anchor_t());
}

TEST_F(AliasManagerTest_264, RegisterReferenceIsIdempotentForSameNodeIdentity_264) {
  AliasManager mgr;
  Node n;

  mgr.RegisterReference(n);
  const YAML::anchor_t a1 = mgr.LookupAnchor(n);

  // Registering the same node again should not change the observable anchor for that node.
  mgr.RegisterReference(n);
  const YAML::anchor_t a2 = mgr.LookupAnchor(n);

  EXPECT_NE(a1, YAML::anchor_t());
  EXPECT_EQ(a1, a2);
}

TEST_F(AliasManagerTest_264, DifferentNodesGetDifferentAnchorsAfterRegistration_264) {
  AliasManager mgr;
  Node n1;
  Node n2;

  mgr.RegisterReference(n1);
  mgr.RegisterReference(n2);

  const YAML::anchor_t a1 = mgr.LookupAnchor(n1);
  const YAML::anchor_t a2 = mgr.LookupAnchor(n2);

  EXPECT_NE(a1, YAML::anchor_t());
  EXPECT_NE(a2, YAML::anchor_t());
  EXPECT_NE(a1, a2);
}

TEST_F(AliasManagerTest_264, ManyRegistrationsProduceUniqueAnchors_264) {
  AliasManager mgr;

  // Use a vector so node objects have stable addresses/identities for the test duration.
  std::vector<Node> nodes;
  nodes.resize(64);

  std::set<YAML::anchor_t> anchors;

  for (auto& n : nodes) {
    mgr.RegisterReference(n);
    const YAML::anchor_t a = mgr.LookupAnchor(n);

    EXPECT_NE(a, YAML::anchor_t());
    anchors.insert(a);
  }

  // Each registered node should map to a distinct anchor.
  EXPECT_EQ(anchors.size(), nodes.size());
}

TEST_F(AliasManagerTest_264, LookupIsStableAcrossInterleavedRegistrations_264) {
  AliasManager mgr;
  Node a;
  Node b;
  Node c;

  mgr.RegisterReference(a);
  const YAML::anchor_t a_before = mgr.LookupAnchor(a);

  mgr.RegisterReference(b);
  mgr.RegisterReference(c);

  const YAML::anchor_t a_after = mgr.LookupAnchor(a);
  EXPECT_EQ(a_before, a_after);
}

TEST_F(AliasManagerTest_264, RegisterAndLookupDoNotThrow_264) {
  AliasManager mgr;
  Node n;

  EXPECT_NO_THROW(mgr.RegisterReference(n));
  EXPECT_NO_THROW((void)mgr.LookupAnchor(n));
  EXPECT_NO_THROW(mgr.RegisterReference(n));  // repeat registration
}

}  // namespace