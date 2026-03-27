// File: iterator_isempty_test.cc

#include "leveldb/iterator.h"
#include <gtest/gtest.h>
#include <utility>  // for std::declval

namespace {

using CleanupNode = leveldb::Iterator::CleanupNode;
// Deduce the function pointer type without assuming its signature.
using CleanupFunction = decltype(std::declval<CleanupNode>().function);

// A dummy function with a generic signature; we'll reinterpret_cast to CleanupFunction.
static void DummyCleanup(void*, void*) {}

}  // namespace

// Normal operation: returns true when function is nullptr.
TEST(IteratorCleanupNodeTest_29, IsEmpty_ReturnsTrueWhenFunctionIsNull_29) {
  CleanupNode node{};  // value-init: all members zero-initialized
  node.function = nullptr;

  EXPECT_TRUE(node.IsEmpty());
}

// Normal operation: returns false when function is non-null.
TEST(IteratorCleanupNodeTest_29, IsEmpty_ReturnsFalseWhenFunctionIsNonNull_29) {
  CleanupNode node{};
  node.function = reinterpret_cast<CleanupFunction>(&DummyCleanup);

  EXPECT_FALSE(node.IsEmpty());
}

// Boundary: default-initialized (via aggregate value-init) node should be empty.
TEST(IteratorCleanupNodeTest_29, IsEmpty_DefaultInitializedNodeIsEmpty_29) {
  CleanupNode node{};  // aggregate value-initialization
  EXPECT_TRUE(node.IsEmpty());
}

// Stability: calling IsEmpty() must not mutate observable state.
TEST(IteratorCleanupNodeTest_29, IsEmpty_DoesNotModifyFunctionField_29) {
  CleanupNode node{};
  node.function = reinterpret_cast<CleanupFunction>(&DummyCleanup);

  // Call multiple times and ensure function pointer remains unchanged.
  (void)node.IsEmpty();
  auto before = node.function;
  (void)node.IsEmpty();
  EXPECT_EQ(before, node.function);
}

// Independence: arg1/arg2/next changes do not affect IsEmpty() result.
TEST(IteratorCleanupNodeTest_29, IsEmpty_IgnoresOtherFields_29) {
  CleanupNode node{};

  // Case A: function is nullptr -> should be empty even if other fields are non-null.
  node.function = nullptr;
  node.arg1 = reinterpret_cast<void*>(0x1);
  node.arg2 = reinterpret_cast<void*>(0x2);
  node.next  = reinterpret_cast<CleanupNode*>(0x3);
  EXPECT_TRUE(node.IsEmpty());

  // Case B: function is non-null -> should be non-empty even if other fields are null.
  node.function = reinterpret_cast<CleanupFunction>(&DummyCleanup);
  node.arg1 = nullptr;
  node.arg2 = nullptr;
  node.next  = nullptr;
  EXPECT_FALSE(node.IsEmpty());
}
