// TEST_ID: 179
// File: yaml-cpp/node/detail/node_iterator_test_179.cpp

#include <gtest/gtest.h>

#include <string>
#include <type_traits>

// Include the real header under test (already implemented in the codebase).
#include "yaml-cpp/node/detail/node_iterator.h"

namespace {

class NodeIteratorValueTest_179 : public ::testing::Test {};

TEST_F(NodeIteratorValueTest_179, DereferenceReturnsReferenceToOriginalNode_179) {
  int x = 42;
  YAML::detail::node_iterator_value<int> it(x);

  int& ref = *it;

  // Observable behavior: dereference yields a reference to the same object.
  EXPECT_EQ(&ref, &x);
  EXPECT_EQ(ref, 42);
}

TEST_F(NodeIteratorValueTest_179, DereferenceAllowsMutationOfOriginalNode_179) {
  int x = 1;
  YAML::detail::node_iterator_value<int> it(x);

  (*it) = 99;

  // Observable behavior: modifying through the dereferenced reference changes the original.
  EXPECT_EQ(x, 99);
}

TEST_F(NodeIteratorValueTest_179, DereferenceOnConstObjectStillReturnsNonConstReference_179) {
  // This is intentionally checking the *declared* interface behavior:
  // operator*() is const, but returns V& (not const V&).
  int x = 7;
  const YAML::detail::node_iterator_value<int> it(x);

  static_assert(std::is_same_v<decltype(*it), int&>,
                "operator*() const is expected to return V& per the interface");

  (*it) = 8;
  EXPECT_EQ(x, 8);
}

TEST_F(NodeIteratorValueTest_179, DereferenceWorksForNonTrivialTypesAndPreservesIdentity_179) {
  std::string s = "hello";
  YAML::detail::node_iterator_value<std::string> it(s);

  std::string& ref = *it;

  EXPECT_EQ(&ref, &s);
  EXPECT_EQ(ref, "hello");

  ref += " world";
  EXPECT_EQ(s, "hello world");
}

}  // namespace