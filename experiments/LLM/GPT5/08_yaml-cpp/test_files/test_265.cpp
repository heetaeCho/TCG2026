// File: ./TestProjects/yaml-cpp/test/nodeevents_aliasmanager_test_265.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/nodeevents.h"
#include "yaml-cpp/node/detail/node.h"

namespace {

class AliasManagerTest_265 : public ::testing::Test {
 protected:
  YAML::NodeEvents::AliasManager manager;
};

TEST_F(AliasManagerTest_265, LookupAnchor_UnregisteredReturnsZero_265) {
  YAML::detail::node n;
  EXPECT_EQ(0, manager.LookupAnchor(n));
}

TEST_F(AliasManagerTest_265, LookupAnchor_MultipleUnregisteredNodesReturnZero_265) {
  YAML::detail::node n1;
  YAML::detail::node n2;

  EXPECT_EQ(0, manager.LookupAnchor(n1));
  EXPECT_EQ(0, manager.LookupAnchor(n2));
}

TEST_F(AliasManagerTest_265, RegisterReferenceThenLookupReturnsNonZero_265) {
  YAML::detail::node n;

  manager.RegisterReference(n);

  const auto anchor = manager.LookupAnchor(n);
  EXPECT_NE(0, anchor);
}

TEST_F(AliasManagerTest_265, LookupAnchor_IsStableAcrossCallsAfterRegistration_265) {
  YAML::detail::node n;

  manager.RegisterReference(n);

  const auto a1 = manager.LookupAnchor(n);
  const auto a2 = manager.LookupAnchor(n);
  const auto a3 = manager.LookupAnchor(n);

  EXPECT_NE(0, a1);
  EXPECT_EQ(a1, a2);
  EXPECT_EQ(a1, a3);
}

TEST_F(AliasManagerTest_265, RegisterSameNodeTwice_AnchorRemainsStable_265) {
  YAML::detail::node n;

  manager.RegisterReference(n);
  const auto a1 = manager.LookupAnchor(n);

  manager.RegisterReference(n);
  const auto a2 = manager.LookupAnchor(n);

  EXPECT_NE(0, a1);
  EXPECT_EQ(a1, a2);
}

TEST_F(AliasManagerTest_265, RegisterOneNode_DoesNotAffectAnotherUnregisteredNode_265) {
  YAML::detail::node registered;
  YAML::detail::node unregistered;

  manager.RegisterReference(registered);

  EXPECT_NE(0, manager.LookupAnchor(registered));
  EXPECT_EQ(0, manager.LookupAnchor(unregistered));
}

TEST_F(AliasManagerTest_265, NodesSharingRefShareAnchorAfterRegisteringOne_265) {
  YAML::detail::node n1;
  YAML::detail::node n2;

  // Make n2 reference the same underlying node_ref as n1 (observable via ref()).
  n2.set_ref(n1);

  // Before registration, both should have no anchor.
  EXPECT_EQ(0, manager.LookupAnchor(n1));
  EXPECT_EQ(0, manager.LookupAnchor(n2));

  manager.RegisterReference(n1);

  const auto a1 = manager.LookupAnchor(n1);
  const auto a2 = manager.LookupAnchor(n2);

  EXPECT_NE(0, a1);
  EXPECT_EQ(a1, a2);
}

TEST_F(AliasManagerTest_265, RegisterViaOneAlias_AllAliasesResolveToSameAnchor_265) {
  YAML::detail::node base;
  YAML::detail::node alias1;
  YAML::detail::node alias2;

  alias1.set_ref(base);
  alias2.set_ref(base);

  manager.RegisterReference(alias1);

  const auto a_base = manager.LookupAnchor(base);
  const auto a_alias1 = manager.LookupAnchor(alias1);
  const auto a_alias2 = manager.LookupAnchor(alias2);

  EXPECT_NE(0, a_alias1);
  EXPECT_EQ(a_alias1, a_base);
  EXPECT_EQ(a_alias1, a_alias2);
}

}  // namespace