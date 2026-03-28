// deps_log_test_83.cc
#include <cstdint>
#include "gtest/gtest.h"

#include "deps_log.h"  // ./TestProjects/ninja/src/deps_log.h

// For convenience in tests.
using Deps = DepsLog::Deps;

// Test fixture for DepsLog::Deps
class DepsTest_83 : public ::testing::Test {};

//------------------------------------------------------------------------------
// Normal operation
//------------------------------------------------------------------------------

TEST_F(DepsTest_83, ConstructorInitializesMembers_83) {
  // Arrange
  int64_t mtime = 123456789;
  int node_count = 3;

  // Act
  Deps deps(mtime, node_count);

  // Assert
  EXPECT_EQ(mtime, deps.mtime);
  EXPECT_EQ(node_count, deps.node_count);
  // For a positive node_count we expect an allocated array pointer.
  EXPECT_NE(nullptr, deps.nodes);
}

TEST_F(DepsTest_83, NodesArrayIsWritable_83) {
  // Arrange
  int64_t mtime = 42;
  int node_count = 2;
  Deps deps(mtime, node_count);

  ASSERT_NE(nullptr, deps.nodes);

  // Act: We only treat Node* as opaque pointers; we do not dereference.
  deps.nodes[0] = nullptr;
  deps.nodes[1] = nullptr;

  // Assert
  EXPECT_EQ(nullptr, deps.nodes[0]);
  EXPECT_EQ(nullptr, deps.nodes[1]);
}

//------------------------------------------------------------------------------
// Boundary conditions
//------------------------------------------------------------------------------

TEST_F(DepsTest_83, ZeroNodeCountIsHandled_83) {
  // Arrange
  int64_t mtime = 0;
  int node_count = 0;

  // Act
  Deps deps(mtime, node_count);

  // Assert
  EXPECT_EQ(mtime, deps.mtime);
  EXPECT_EQ(0, deps.node_count);

  // For node_count == 0, the behavior of the nodes pointer (nullptr vs
  // non-null) is implementation-defined, so we only assert that construction
  // and destruction do not crash.
}

//------------------------------------------------------------------------------
// Destructor / lifetime behavior (exceptional/error-like safety)
//------------------------------------------------------------------------------

TEST_F(DepsTest_83, DestructorIsSafeForStackAllocatedObject_83) {
  // This test ensures that constructing and then going out of scope
  // (invoking ~Deps) does not crash for a non-trivial node_count.
  {
    Deps deps(100, 5);
    ASSERT_NE(nullptr, deps.nodes);
  }
  // If there is a problem in the destructor (e.g., invalid delete[]),
  // this test would typically fail under ASan/Valgrind or crash.
  SUCCEED();
}

TEST_F(DepsTest_83, DestructorIsSafeForHeapAllocatedObject_83) {
  // This test exercises the destructor for a heap-allocated instance.
  Deps* deps = new Deps(200, 4);
  ASSERT_NE(nullptr, deps->nodes);

  // Act & Assert: delete must not crash or cause double-free issues.
  delete deps;

  SUCCEED();
}
