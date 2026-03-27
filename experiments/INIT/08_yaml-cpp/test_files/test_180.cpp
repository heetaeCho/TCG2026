// TEST_ID: 180
// File: node_iterator_value_operator_arrow_test_180.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_iterator.h"

namespace {

struct DummyNode_180 {
  int value = 0;
};

}  // namespace

TEST(NodeIteratorValueTest_180, OperatorArrowReturnsSameObjectAsConstructorArgument_180) {
  DummyNode_180 n;
  YAML::detail::node_iterator_value<DummyNode_180> it(n);

  DummyNode_180& ref = it.operator->();
  EXPECT_EQ(&ref, &n);
}

TEST(NodeIteratorValueTest_180, OperatorArrowWorksOnConstObject_180) {
  DummyNode_180 n;
  const YAML::detail::node_iterator_value<DummyNode_180> it(n);

  DummyNode_180& ref = it.operator->();
  EXPECT_EQ(&ref, &n);
}

TEST(NodeIteratorValueTest_180, OperatorArrowAllowsMutationThroughReturnedReference_180) {
  DummyNode_180 n;
  n.value = 7;

  YAML::detail::node_iterator_value<DummyNode_180> it(n);

  it.operator->().value = 42;
  EXPECT_EQ(n.value, 42);
}

TEST(NodeIteratorValueTest_180, CopyConstructionPreservesArrowTarget_180) {
  DummyNode_180 n;
  YAML::detail::node_iterator_value<DummyNode_180> it(n);
  YAML::detail::node_iterator_value<DummyNode_180> copy(it);

  EXPECT_EQ(&copy.operator->(), &n);
  EXPECT_EQ(&copy.operator->(), &it.operator->());
}

TEST(NodeIteratorValueTest_180, CopyAssignmentPreservesArrowTarget_180) {
  DummyNode_180 n1;
  DummyNode_180 n2;

  YAML::detail::node_iterator_value<DummyNode_180> it1(n1);
  YAML::detail::node_iterator_value<DummyNode_180> it2(n2);

  it2 = it1;

  EXPECT_EQ(&it2.operator->(), &n1);
  EXPECT_EQ(&it2.operator->(), &it1.operator->());
}