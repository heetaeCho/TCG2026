// File: workq_insert_new_test_447.cc
#include <gtest/gtest.h>

// If your project exposes a header for DFA/Workq, prefer including it.
// These headers are common in re2; adjust include paths as needed.
#include "re2/dfa.h"        // for re2::DFA::Workq
#include "re2/sparse_set.h" // for SparseSet interface (contains(), begin(), end(), size())

using re2::DFA;

class WorkqInsertNewTest_447 : public ::testing::Test {
protected:
  // Helper to make a small Workq with room for marks.
  // We avoid any assumptions about internal logic or ranges beyond ctor params.
  DFA::Workq MakeWorkq(int n = 8, int maxmark = 4) {
    return DFA::Workq(n, maxmark);
  }
};

// Normal operation: inserting a single new id should add it and be findable via base SparseSet API.
TEST_F(WorkqInsertNewTest_447, InsertsAndIsContained_447) {
  auto w = MakeWorkq(8, 4);
  const int id = 5;

  const int size_before = w.size();
  w.insert_new(id);

  EXPECT_EQ(w.size(), size_before + 1);
  // Rely only on the public SparseSet interface exposed via public inheritance.
  EXPECT_TRUE(w.contains(id));
}

// Normal operation: multiple unique inserts should each increase the size by one and be present.
TEST_F(WorkqInsertNewTest_447, MultipleUniqueInsertsIncreaseSize_447) {
  auto w = MakeWorkq(8, 4);

  const int ids[] = {0, 3, 6};
  int expected_size = w.size();

  for (int id : ids) {
    w.insert_new(id);
    ++expected_size;
    EXPECT_EQ(w.size(), expected_size);
    EXPECT_TRUE(w.contains(id));
  }
}

// Boundary conditions: lowest and highest ids within the constructed capacity should be insertable.
// We do NOT assert anything about invalid ids or ranges beyond ctor-provided capacity.
TEST_F(WorkqInsertNewTest_447, BoundaryIdsInsertable_447) {
  const int n = 8;
  const int maxmark = 4;
  auto w = MakeWorkq(n, maxmark);

  const int lowest = 0;
  const int highest = n + maxmark - 1;

  int size_before = w.size();
  w.insert_new(lowest);
  EXPECT_EQ(w.size(), size_before + 1);
  EXPECT_TRUE(w.contains(lowest));

  size_before = w.size();
  w.insert_new(highest);
  EXPECT_EQ(w.size(), size_before + 1);
  EXPECT_TRUE(w.contains(highest));
}

// Interaction with mark(): inserting a new id after calling mark() should still add exactly one new element.
// We do NOT assert anything about what mark() itself does internally (black-box).
TEST_F(WorkqInsertNewTest_447, InsertNewAfterMarkAddsExactlyOne_447) {
  auto w = MakeWorkq(8, 4);

  // We treat mark() as black-box; only compare sizes around insert_new.
  w.mark();

  const int size_before = w.size();
  w.insert_new(2);
  EXPECT_EQ(w.size(), size_before + 1);
  EXPECT_TRUE(w.contains(2));
}

// Clearing the Workq should remove previously inserted items (observable via size() and contains()).
TEST_F(WorkqInsertNewTest_447, ClearRemovesInsertedItems_447) {
  auto w = MakeWorkq(8, 4);

  w.insert_new(1);
  w.insert_new(4);
  ASSERT_TRUE(w.contains(1));
  ASSERT_TRUE(w.contains(4));
  ASSERT_GT(w.size(), 0);

  w.clear();
  EXPECT_EQ(w.size(), 0);
  EXPECT_FALSE(w.contains(1));
  EXPECT_FALSE(w.contains(4));
}

// maxmark() should report the constructor-provided maximum number of marks (observable via return value).
TEST_F(WorkqInsertNewTest_447, MaxmarkReflectsCtorValue_447) {
  {
    auto w = MakeWorkq(8, 4);
    EXPECT_EQ(w.maxmark(), 4);
  }
  {
    auto w = MakeWorkq(10, 1);
    EXPECT_EQ(w.maxmark(), 1);
  }
}

// Safety / error-ish observable case: calling insert_new with a value already present is not tested,
// since behavior of SparseSet::insert_new on duplicates is not specified in the provided interface.
// We intentionally avoid constructing such a case to adhere to the black-box constraint.
