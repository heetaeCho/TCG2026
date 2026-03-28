// File: iterator_cleanupnode_run_test.cc
#include <gtest/gtest.h>
#include "leveldb/iterator.h"

namespace {

using leveldb::Iterator;

// Test fixture to record callback invocations without peeking into internals.
class IteratorCleanupNodeTest_30 : public ::testing::Test {
protected:
  static void Reset() {
    calls_ = 0;
    last_arg1_ = nullptr;
    last_arg2_ = nullptr;
  }

  // Callback matching CleanupFunction signature: void(void*, void*)
  static void Recorder(void* a1, void* a2) {
    ++calls_;
    last_arg1_ = a1;
    last_arg2_ = a2;
  }

  static int calls_;
  static void* last_arg1_;
  static void* last_arg2_;
};

int IteratorCleanupNodeTest_30::calls_ = 0;
void* IteratorCleanupNodeTest_30::last_arg1_ = nullptr;
void* IteratorCleanupNodeTest_30::last_arg2_ = nullptr;

// Normal operation: Run() should invoke the provided function with the stored args.
TEST_F(IteratorCleanupNodeTest_30, CallsFunctionWithArgs_30) {
  Iterator::CleanupNode node;
  int x = 123;
  double y = 4.5;

  IteratorCleanupNodeTest_30::Reset();
  node.function = &IteratorCleanupNodeTest_30::Recorder;
  node.arg1 = &x;
  node.arg2 = &y;
  node.next = nullptr;  // Not used by the test; set explicitly to avoid UB assumptions.

  node.Run();

  EXPECT_EQ(1, calls_);
  EXPECT_EQ(&x, last_arg1_);
  EXPECT_EQ(&y, last_arg2_);
}

// Boundary condition: Run() should pass through nullptr arguments unchanged.
TEST_F(IteratorCleanupNodeTest_30, AllowsNullArguments_30) {
  Iterator::CleanupNode node;
  int y = 7;

  IteratorCleanupNodeTest_30::Reset();
  node.function = &IteratorCleanupNodeTest_30::Recorder;
  node.arg1 = nullptr;     // boundary: nullptr
  node.arg2 = &y;          // non-null to distinguish
  node.next = nullptr;

  node.Run();

  EXPECT_EQ(1, calls_);
  EXPECT_EQ(nullptr, last_arg1_);
  EXPECT_EQ(&y, last_arg2_);
}

// Error/exceptional case: if function is nullptr, Run() should assert (death test).
// This uses EXPECT_DEATH_IF_SUPPORTED to remain portable across platforms/configs.
// Note: assert(...) is active in non-NDEBUG builds.
TEST_F(IteratorCleanupNodeTest_30, NullFunctionTriggersAssert_30) {
  Iterator::CleanupNode node;
  node.function = nullptr;  // triggers assert in Run()
  node.arg1 = nullptr;
  node.arg2 = nullptr;
  node.next = nullptr;

  // Use a lambda to ensure the expression is a single statement for the macro.
  EXPECT_DEATH_IF_SUPPORTED({ node.Run(); }, ".*");
}

}  // namespace
