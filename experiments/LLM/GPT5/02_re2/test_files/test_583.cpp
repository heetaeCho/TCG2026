// File: sparse_array_move_test_583.cc

#include <gtest/gtest.h>
#include "re2/sparse_array.h"
#include <string>

using re2::SparseArray;

// Helper to populate a SparseArray with a few entries via the public API.
template <typename T>
static void Populate(SparseArray<T>& sa) {
  sa.set(0, static_cast<T>(T{ } + T(10)));  // index 0
  sa.set(3, static_cast<T>(T{ } + T(30)));  // index 3
  sa.set(9, static_cast<T>(T{ } + T(90)));  // index 9 (assuming max_size >= 10)
}

// Overloads for string to keep Populate() simple without inferring internals.
template <>
inline void Populate<std::string>(SparseArray<std::string>& sa) {
  sa.set(0, std::string("alpha"));
  sa.set(3, std::string("bravo"));
  sa.set(9, std::string("charlie"));
}

// --- Tests ---

// Verifies: moving a populated array transfers elements to the destination and
// resets the source's observable size. Also checks values via get_existing()
// and presence via has_index(), without touching internals.
TEST(SparseArrayMoveTest_583, MoveCtor_TransfersElementsAndResetsSource_583) {
  SparseArray<int> src(10);
  src.set(0, 10);
  src.set(3, 30);
  src.set(9, 90);

  ASSERT_EQ(src.size(), 3);
  ASSERT_TRUE(src.has_index(0));
  ASSERT_TRUE(src.has_index(3));
  ASSERT_TRUE(src.has_index(9));

  SparseArray<int> dst(std::move(src));

  // Destination received the elements.
  EXPECT_EQ(dst.size(), 3);
  EXPECT_TRUE(dst.has_index(0));
  EXPECT_TRUE(dst.has_index(3));
  EXPECT_TRUE(dst.has_index(9));
  EXPECT_EQ(dst.get_existing(0), 10);
  EXPECT_EQ(dst.get_existing(3), 30);
  EXPECT_EQ(dst.get_existing(9), 90);

  // Source is left in a valid, empty observable state (per public API).
  EXPECT_EQ(src.size(), 0);
  EXPECT_FALSE(src.has_index(0));
  EXPECT_FALSE(src.has_index(3));
  EXPECT_FALSE(src.has_index(9));
}

// Verifies: moving from an empty array yields an empty destination and an empty source.
TEST(SparseArrayMoveTest_583, MoveCtor_FromEmpty_583) {
  SparseArray<std::string> src(5);
  EXPECT_EQ(src.size(), 0);

  SparseArray<std::string> dst(std::move(src));

  EXPECT_EQ(dst.size(), 0);
  EXPECT_EQ(src.size(), 0);
  // Spot-check that previously unset index still reports absent.
  EXPECT_FALSE(dst.has_index(0));
  EXPECT_FALSE(src.has_index(0));
}

// Verifies: the moved-from source remains usable; we can insert new elements via public API.
TEST(SparseArrayMoveTest_583, MoveCtor_SourceReusableAfterMove_583) {
  SparseArray<int> src(10);
  src.set(0, 10);
  src.set(3, 30);

  SparseArray<int> dst(std::move(src));

  // Source should now appear empty.
  ASSERT_EQ(src.size(), 0);

  // Reuse the moved-from source.
  src.set(1, 111);
  EXPECT_EQ(src.size(), 1);
  EXPECT_TRUE(src.has_index(1));
  EXPECT_EQ(src.get_existing(1), 111);

  // Destination still has the original elements.
  EXPECT_EQ(dst.size(), 2);
  EXPECT_TRUE(dst.has_index(0));
  EXPECT_TRUE(dst.has_index(3));
  EXPECT_EQ(dst.get_existing(0), 10);
  EXPECT_EQ(dst.get_existing(3), 30);
}

// Verifies: chaining moves preserves contents through each move, and intermediate
// sources become observably empty.
TEST(SparseArrayMoveTest_583, MoveCtor_ChainedMovesPreserveContents_583) {
  SparseArray<std::string> a(12);
  Populate(a);  // indices: 0, 3, 9 -> "alpha", "bravo", "charlie"
  ASSERT_EQ(a.size(), 3);

  SparseArray<std::string> b(std::move(a));
  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(a.size(), 0);                 // moved-from appears empty
  EXPECT_TRUE(b.has_index(0));
  EXPECT_TRUE(b.has_index(3));
  EXPECT_TRUE(b.has_index(9));
  EXPECT_EQ(b.get_existing(0), "alpha");
  EXPECT_EQ(b.get_existing(3), "bravo");
  EXPECT_EQ(b.get_existing(9), "charlie");

  SparseArray<std::string> c(std::move(b));
  EXPECT_EQ(c.size(), 3);
  EXPECT_EQ(b.size(), 0);                 // moved-from appears empty
  EXPECT_TRUE(c.has_index(0));
  EXPECT_TRUE(c.has_index(3));
  EXPECT_TRUE(c.has_index(9));
  EXPECT_EQ(c.get_existing(0), "alpha");
  EXPECT_EQ(c.get_existing(3), "bravo");
  EXPECT_EQ(c.get_existing(9), "charlie");
}
