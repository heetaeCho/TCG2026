// File: sparse_set_dtor_test_96.cc
#include <gtest/gtest.h>
#include "re2/sparse_set.h"

using re2::SparseSetT;

// NOTE: We cannot (and do not) verify internal invariants or private calls.
// These tests ensure the destructor is safely invokable across typical states.

TEST(SparseSetT_96, Destructor_EmptySet_NoCrash_96) {
  {
    SparseSetT<int> s;
    // No operations; ensure going out of scope (dtor) is safe.
  }
  SUCCEED();
}

TEST(SparseSetT_96, Destructor_WithInsertedElements_NoCrash_96) {
  {
    SparseSetT<int> s;
    // Insert a few values via the public interface.
    s.insert(0);
    s.insert(5);
    s.insert(42);
    ASSERT_TRUE(s.contains(0));
    ASSERT_TRUE(s.contains(5));
    ASSERT_TRUE(s.contains(42));
    ASSERT_GE(s.size(), 0);  // Basic observable queries
  }
  SUCCEED();
}

TEST(SparseSetT_96, Destructor_AfterClear_NoCrash_96) {
  {
    SparseSetT<int> s;
    s.insert(1);
    s.insert(2);
    ASSERT_TRUE(s.contains(1));
    s.clear();
    // After clear, allow destructor to run.
    ASSERT_TRUE(s.empty());
  }
  SUCCEED();
}

TEST(SparseSetT_96, Destructor_AfterResizeGrowAndShrink_NoCrash_96) {
  {
    SparseSetT<int> s;
    // Resize up, perform operations
    s.resize(100);
    s.insert(10);
    s.insert(20);
    ASSERT_TRUE(s.contains(10));
    ASSERT_TRUE(s.contains(20));

    // Resize down/up around operations to cover various internal states
    s.resize(50);
    s.resize(150);
    s.insert(149);
    ASSERT_TRUE(s.contains(149));
  }
  SUCCEED();
}

TEST(SparseSetT_96, Destructor_MultipleInstances_NoCrash_96) {
  {
    SparseSetT<int> a;
    SparseSetT<int> b;
    a.insert(3);
    b.insert(7);
    ASSERT_TRUE(a.contains(3));
    ASSERT_TRUE(b.contains(7));

    // Create a nested scope to exercise interleaved destruction.
    {
      SparseSetT<int> c;
      c.insert(11);
      ASSERT_TRUE(c.contains(11));
    }  // c destroyed here
    // a and b remain alive; then will be destroyed at end of outer scope.
  }
  SUCCEED();
}
