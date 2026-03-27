// slice_clear_test_7.cc
#include <gtest/gtest.h>
#include <string>
#include "leveldb/slice.h"

using leveldb::Slice;

class SliceClearTest_7 : public ::testing::Test {};

// Normal: clear after non-empty — size/empty/ToString/begin/end
TEST_F(SliceClearTest_7, ClearOnNonEmptyResetsState_7) {
  Slice s("hello");
  s.clear();
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.ToString(), std::string());
  EXPECT_EQ(s.begin(), s.end());  // observable via pointers
}

// Boundary: clear on already-empty slice
TEST_F(SliceClearTest_7, ClearOnAlreadyEmptyRemainsEmpty_7) {
  Slice s;           // default should be empty per interface
  s.clear();         // clear again
  EXPECT_EQ(s.size(), 0u);
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.ToString(), "");
  EXPECT_EQ(s.begin(), s.end());
}

// Boundary: idempotence — multiple clears keep state consistent
TEST_F(SliceClearTest_7, MultipleClearsAreIdempotent_7) {
  Slice s("x");
  s.clear();
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
  EXPECT_EQ(s.ToString(), "");
}

// Interaction: clearing one slice must not affect another copy
TEST_F(SliceClearTest_7, ClearDoesNotAffectCopies_7) {
  Slice original("abc");
  Slice copy = original;   // copy via interface
  original.clear();
  // copy remains unchanged (observable behavior)
  EXPECT_FALSE(copy.empty());
  EXPECT_EQ(copy.size(), 3u);
  EXPECT_EQ(copy.ToString(), "abc");

  // original is cleared
  EXPECT_TRUE(original.empty());
  EXPECT_EQ(original.size(), 0u);
}

// Compare semantics via observable equality with another empty slice
TEST_F(SliceClearTest_7, ClearedEqualsDefaultEmptyByCompare_7) {
  Slice s("data");
  s.clear();
  Slice empty;  // default empty
  // We only assert equality (== 0); we do not assume ordering signs.
  EXPECT_EQ(s.compare(empty), 0);
  EXPECT_EQ(empty.compare(s), 0);
}

// starts_with behavior after clear
TEST_F(SliceClearTest_7, StartsWithAfterClear_7) {
  Slice s("prefix");
  s.clear();
  Slice empty;           // empty prefix
  Slice non_empty("p");  // non-empty prefix
  EXPECT_TRUE(s.starts_with(empty));     // empty is a prefix of empty
  EXPECT_FALSE(s.starts_with(non_empty)); // non-empty is not a prefix of empty
}

// Begin/End observable boundary after clear from std::string-backed slice
TEST_F(SliceClearTest_7, ClearFromStdStringBackedSlice_7) {
  std::string backing = "xyz";
  Slice s(backing);
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
  EXPECT_EQ(s.begin(), s.end());
  EXPECT_EQ(s.ToString(), "");
}
