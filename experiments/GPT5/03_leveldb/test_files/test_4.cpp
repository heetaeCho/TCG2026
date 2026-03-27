// File: slice_begin_test_4.cc
#include <gtest/gtest.h>
#include "leveldb/slice.h"
#include <string>
#include <cstring>

using leveldb::Slice;

class SliceBeginTest_4 : public ::testing::Test {};

// begin() should equal data() for any Slice
TEST_F(SliceBeginTest_4, BeginEqualsData_4) {
  Slice s("hello");
  EXPECT_EQ(s.begin(), s.data());
}

// begin() on an empty Slice should be a valid pointer and equal to end()
TEST_F(SliceBeginTest_4, BeginOnEmptySlice_4) {
  Slice s;                 // default-constructed empty slice
  EXPECT_EQ(s.size(), 0u);
  EXPECT_EQ(s.begin(), s.end());   // observable via public API
  // We do NOT dereference begin() here since size()==0.
}

// begin() should point to the first character when size() > 0
TEST_F(SliceBeginTest_4, BeginPointsToFirstChar_4) {
  const char* txt = "abc";
  Slice s(txt, 3);
  ASSERT_EQ(s.size(), 3u);
  EXPECT_EQ(*s.begin(), 'a');  // observable first byte
}

// remove_prefix(n) should advance begin() by n and reduce size() accordingly
TEST_F(SliceBeginTest_4, RemovePrefixUpdatesBegin_4) {
  const char* txt = "hello";
  Slice s(txt, 5);
  const char* old_begin = s.begin();

  s.remove_prefix(2);
  EXPECT_EQ(s.size(), 3u);
  EXPECT_EQ(s.begin(), old_begin + 2);
  EXPECT_EQ(*s.begin(), 'l');
}

// begin() should correctly expose embedded NUL bytes when constructed with (ptr, len)
TEST_F(SliceBeginTest_4, BeginHandlesEmbeddedNullBytes_4) {
  const char raw[] = {'a', '\0', 'b'};
  Slice s(raw, sizeof(raw));
  ASSERT_EQ(s.size(), 3u);
  EXPECT_EQ(*(s.begin() + 0), 'a');
  EXPECT_EQ(*(s.begin() + 1), '\0');
  EXPECT_EQ(*(s.begin() + 2), 'b');
}

// clear() should make the slice empty; begin() should equal end() afterwards
TEST_F(SliceBeginTest_4, ClearResetsToEmpty_4) {
  Slice s("xyz");
  s.clear();
  EXPECT_EQ(s.size(), 0u);
  EXPECT_EQ(s.begin(), s.end());
}

// Copy and assignment should preserve begin() (point to the same underlying data)
TEST_F(SliceBeginTest_4, CopyAndAssignmentPreserveBegin_4) {
  const char* txt = "copy";
  Slice s(txt, 4);
  Slice copy = s;               // copy-construct
  EXPECT_EQ(copy.begin(), s.begin());
  EXPECT_EQ(copy.size(), s.size());

  Slice assigned("temp");
  assigned = s;                 // copy-assign
  EXPECT_EQ(assigned.begin(), s.begin());
  EXPECT_EQ(assigned.size(), s.size());

  // Mutating the copy via remove_prefix should not alter the original
  const char* original_begin = s.begin();
  copy.remove_prefix(1);
  EXPECT_EQ(s.begin(), original_begin);
  EXPECT_EQ(s.size(), 4u);
}
