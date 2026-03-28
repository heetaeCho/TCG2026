#include "gtest/gtest.h"
#include "leveldb/iterator.h"

#include <cstdlib>
#include <vector>

namespace leveldb {

// Helper tracking function for cleanup callbacks
static std::vector<std::pair<void*, void*>> g_cleanup_calls;

static void TrackingCleanupFunction(void* arg1, void* arg2) {
  g_cleanup_calls.push_back({arg1, arg2});
}

static void FreeCleanupFunction(void* arg1, void* arg2) {
  // Just track the call
  g_cleanup_calls.push_back({arg1, arg2});
}

static int g_counter = 0;

static void IncrementCounter(void* arg1, void* arg2) {
  g_counter++;
}

class CleanupNodeTest_30 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_cleanup_calls.clear();
    g_counter = 0;
  }
};

// Test that Run() invokes the registered cleanup function with correct arguments
TEST_F(CleanupNodeTest_30, RunInvokesFunction_30) {
  Iterator::CleanupNode node;
  int a = 42;
  int b = 99;
  node.function = TrackingCleanupFunction;
  node.arg1 = &a;
  node.arg2 = &b;
  node.next = nullptr;

  node.Run();

  ASSERT_EQ(g_cleanup_calls.size(), 1u);
  EXPECT_EQ(g_cleanup_calls[0].first, &a);
  EXPECT_EQ(g_cleanup_calls[0].second, &b);
}

// Test that Run() passes nullptr arguments correctly
TEST_F(CleanupNodeTest_30, RunWithNullArgs_30) {
  Iterator::CleanupNode node;
  node.function = TrackingCleanupFunction;
  node.arg1 = nullptr;
  node.arg2 = nullptr;
  node.next = nullptr;

  node.Run();

  ASSERT_EQ(g_cleanup_calls.size(), 1u);
  EXPECT_EQ(g_cleanup_calls[0].first, nullptr);
  EXPECT_EQ(g_cleanup_calls[0].second, nullptr);
}

// Test that Run() can be called multiple times
TEST_F(CleanupNodeTest_30, RunCanBeCalledMultipleTimes_30) {
  Iterator::CleanupNode node;
  node.function = IncrementCounter;
  node.arg1 = nullptr;
  node.arg2 = nullptr;
  node.next = nullptr;

  node.Run();
  node.Run();
  node.Run();

  EXPECT_EQ(g_counter, 3);
}

// Test IsEmpty when function is nullptr
TEST_F(CleanupNodeTest_30, IsEmptyWhenFunctionIsNull_30) {
  Iterator::CleanupNode node;
  node.function = nullptr;
  node.arg1 = nullptr;
  node.arg2 = nullptr;
  node.next = nullptr;

  EXPECT_TRUE(node.IsEmpty());
}

// Test IsEmpty when function is set
TEST_F(CleanupNodeTest_30, IsNotEmptyWhenFunctionIsSet_30) {
  Iterator::CleanupNode node;
  node.function = TrackingCleanupFunction;
  node.arg1 = nullptr;
  node.arg2 = nullptr;
  node.next = nullptr;

  EXPECT_FALSE(node.IsEmpty());
}

// Test that Run() passes different arg1 and arg2 correctly
TEST_F(CleanupNodeTest_30, RunWithDifferentArgs_30) {
  Iterator::CleanupNode node;
  char data1[] = "hello";
  char data2[] = "world";
  node.function = TrackingCleanupFunction;
  node.arg1 = data1;
  node.arg2 = data2;
  node.next = nullptr;

  node.Run();

  ASSERT_EQ(g_cleanup_calls.size(), 1u);
  EXPECT_EQ(g_cleanup_calls[0].first, static_cast<void*>(data1));
  EXPECT_EQ(g_cleanup_calls[0].second, static_cast<void*>(data2));
}

// Test chaining of cleanup nodes via next pointer
TEST_F(CleanupNodeTest_30, NextPointerChaining_30) {
  Iterator::CleanupNode node1;
  Iterator::CleanupNode node2;
  Iterator::CleanupNode node3;

  int val1 = 1, val2 = 2, val3 = 3;

  node1.function = TrackingCleanupFunction;
  node1.arg1 = &val1;
  node1.arg2 = nullptr;
  node1.next = &node2;

  node2.function = TrackingCleanupFunction;
  node2.arg1 = &val2;
  node2.arg2 = nullptr;
  node2.next = &node3;

  node3.function = TrackingCleanupFunction;
  node3.arg1 = &val3;
  node3.arg2 = nullptr;
  node3.next = nullptr;

  // Simulate walking the chain
  Iterator::CleanupNode* current = &node1;
  while (current != nullptr) {
    if (!current->IsEmpty()) {
      current->Run();
    }
    current = current->next;
  }

  ASSERT_EQ(g_cleanup_calls.size(), 3u);
  EXPECT_EQ(g_cleanup_calls[0].first, &val1);
  EXPECT_EQ(g_cleanup_calls[1].first, &val2);
  EXPECT_EQ(g_cleanup_calls[2].first, &val3);
}

// Test that arg1 only is non-null
TEST_F(CleanupNodeTest_30, RunWithOnlyArg1NonNull_30) {
  Iterator::CleanupNode node;
  int a = 10;
  node.function = TrackingCleanupFunction;
  node.arg1 = &a;
  node.arg2 = nullptr;
  node.next = nullptr;

  node.Run();

  ASSERT_EQ(g_cleanup_calls.size(), 1u);
  EXPECT_EQ(g_cleanup_calls[0].first, &a);
  EXPECT_EQ(g_cleanup_calls[0].second, nullptr);
}

// Test that arg2 only is non-null
TEST_F(CleanupNodeTest_30, RunWithOnlyArg2NonNull_30) {
  Iterator::CleanupNode node;
  int b = 20;
  node.function = TrackingCleanupFunction;
  node.arg1 = nullptr;
  node.arg2 = &b;
  node.next = nullptr;

  node.Run();

  ASSERT_EQ(g_cleanup_calls.size(), 1u);
  EXPECT_EQ(g_cleanup_calls[0].first, nullptr);
  EXPECT_EQ(g_cleanup_calls[0].second, &b);
}

}  // namespace leveldb
