#include "gtest/gtest.h"
#include "leveldb/iterator.h"

namespace leveldb {

// Test that a default-constructed CleanupNode (with function == nullptr) is empty
TEST(CleanupNodeTest_29, DefaultConstructedIsEmpty_29) {
  Iterator::CleanupNode node;
  node.function = nullptr;
  node.arg1 = nullptr;
  node.arg2 = nullptr;
  node.next = nullptr;
  EXPECT_TRUE(node.IsEmpty());
}

// Test that a CleanupNode with a non-null function is not empty
TEST(CleanupNodeTest_29, NonNullFunctionIsNotEmpty_29) {
  Iterator::CleanupNode node;
  node.function = [](void*, void*) {};
  node.arg1 = nullptr;
  node.arg2 = nullptr;
  node.next = nullptr;
  EXPECT_FALSE(node.IsEmpty());
}

// Test that setting function back to nullptr makes IsEmpty return true again
TEST(CleanupNodeTest_29, SetFunctionToNullMakesEmpty_29) {
  Iterator::CleanupNode node;
  node.function = [](void*, void*) {};
  EXPECT_FALSE(node.IsEmpty());
  node.function = nullptr;
  EXPECT_TRUE(node.IsEmpty());
}

// Test that Run invokes the cleanup function with the correct arguments
TEST(CleanupNodeTest_29, RunInvokesFunction_29) {
  static bool called = false;
  static void* captured_arg1 = nullptr;
  static void* captured_arg2 = nullptr;

  called = false;
  captured_arg1 = nullptr;
  captured_arg2 = nullptr;

  int a = 42;
  int b = 84;

  Iterator::CleanupNode node;
  node.function = [](void* arg1, void* arg2) {
    called = true;
    captured_arg1 = arg1;
    captured_arg2 = arg2;
  };
  node.arg1 = &a;
  node.arg2 = &b;
  node.next = nullptr;

  node.Run();

  EXPECT_TRUE(called);
  EXPECT_EQ(captured_arg1, &a);
  EXPECT_EQ(captured_arg2, &b);
}

// Test Run with nullptr arguments
TEST(CleanupNodeTest_29, RunWithNullArgs_29) {
  static bool called = false;
  static void* captured_arg1 = reinterpret_cast<void*>(0xDEAD);
  static void* captured_arg2 = reinterpret_cast<void*>(0xBEEF);

  called = false;

  Iterator::CleanupNode node;
  node.function = [](void* arg1, void* arg2) {
    called = true;
    captured_arg1 = arg1;
    captured_arg2 = arg2;
  };
  node.arg1 = nullptr;
  node.arg2 = nullptr;
  node.next = nullptr;

  node.Run();

  EXPECT_TRUE(called);
  EXPECT_EQ(captured_arg1, nullptr);
  EXPECT_EQ(captured_arg2, nullptr);
}

// Test that next pointer can be set and read
TEST(CleanupNodeTest_29, NextPointerChaining_29) {
  Iterator::CleanupNode node1;
  Iterator::CleanupNode node2;

  node1.function = nullptr;
  node1.arg1 = nullptr;
  node1.arg2 = nullptr;
  node1.next = &node2;

  node2.function = nullptr;
  node2.arg1 = nullptr;
  node2.arg2 = nullptr;
  node2.next = nullptr;

  EXPECT_EQ(node1.next, &node2);
  EXPECT_EQ(node2.next, nullptr);
}

// Test IsEmpty boundary: function pointer is the only thing that matters
TEST(CleanupNodeTest_29, IsEmptyOnlyDependsOnFunction_29) {
  int dummy = 0;
  Iterator::CleanupNode node;
  node.function = nullptr;
  node.arg1 = &dummy;
  node.arg2 = &dummy;
  node.next = &node;

  // Even with non-null arg1, arg2, and next, IsEmpty should be true
  // because function is nullptr
  EXPECT_TRUE(node.IsEmpty());
}

}  // namespace leveldb
