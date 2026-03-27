// File: test/yaml_iterator_base_eq_test_201.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/detail/iterator.h"

namespace {

using YAML::Node;

class IteratorBaseEqualityTest_201 : public ::testing::Test {};

TEST_F(IteratorBaseEqualityTest_201, ReflexiveEquality_DefaultConstructed_201) {
  YAML::detail::iterator_base<Node> it;
  EXPECT_TRUE(it == it);
}

TEST_F(IteratorBaseEqualityTest_201, TwoDefaultConstructedIteratorsCompareEqual_201) {
  YAML::detail::iterator_base<Node> a;
  YAML::detail::iterator_base<Node> b;

  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == a);
}

TEST_F(IteratorBaseEqualityTest_201, CopyConstructedIteratorComparesEqualToSource_201) {
  YAML::detail::iterator_base<Node> src;
  YAML::detail::iterator_base<Node> copy(src);

  EXPECT_TRUE(copy == src);
  EXPECT_TRUE(src == copy);
}

TEST_F(IteratorBaseEqualityTest_201, CrossTypeEquality_ConvertibleValueType_201) {
  // If Node* is convertible to const Node*, the cross-type ctor should be viable.
  YAML::detail::iterator_base<Node> mutable_it;
  YAML::detail::iterator_base<const Node> const_it(mutable_it);

  // operator== is templated, so cross-type comparisons should compile and be observable.
  EXPECT_TRUE(mutable_it == const_it);
  EXPECT_TRUE(const_it == mutable_it);
}

TEST_F(IteratorBaseEqualityTest_201, TransitiveEquality_ForDefaultAndCopies_201) {
  YAML::detail::iterator_base<Node> a;
  YAML::detail::iterator_base<Node> b(a);
  YAML::detail::iterator_base<const Node> c(b);  // cross-type copy (Node -> const Node)

  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == c);
  EXPECT_TRUE(a == c);
}

}  // namespace
`