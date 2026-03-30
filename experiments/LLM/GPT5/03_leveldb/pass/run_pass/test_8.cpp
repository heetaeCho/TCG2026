// File: slice_remove_prefix_test_8.cc
#include <gtest/gtest.h>
#include "leveldb/slice.h"

using leveldb::Slice;

class SliceRemovePrefixTest_8 : public ::testing::Test {};

// Normal operation: removing 0 should leave the slice unchanged.
TEST_F(SliceRemovePrefixTest_8, RemoveZeroKeepsSliceUnchanged_8) {
  const char* s = "abcdef";
  Slice slice(s, 6);

  // Snapshot before
  const char* before_data = slice.data();
  size_t before_size = slice.size();

  slice.remove_prefix(0);

  EXPECT_EQ(before_data, slice.data());
  EXPECT_EQ(before_size, slice.size());
  EXPECT_FALSE(slice.empty());
  // Optional: confirm textual view is unchanged through public API
  EXPECT_EQ(std::string("abcdef"), slice.ToString());
}

// Normal operation: removing a proper prefix advances data() and reduces size().
TEST_F(SliceRemovePrefixTest_8, RemovePartialPrefixUpdatesDataAndSize_8) {
  const char* s = "abcdef";
  Slice slice(s, 6);

  slice.remove_prefix(2); // expect remaining "cdef"

  EXPECT_EQ(4u, slice.size());
  ASSERT_NE(nullptr, slice.data());
  EXPECT_EQ('c', slice.data()[0]);
  EXPECT_EQ(std::string("cdef"), slice.ToString());
  EXPECT_FALSE(slice.empty());
}

// Boundary: removing exactly size() should yield an empty slice.
TEST_F(SliceRemovePrefixTest_8, RemoveEntireSliceResultsInEmpty_8) {
  const char* s = "abcdef";
  Slice slice(s, 6);

  slice.remove_prefix(6);

  EXPECT_EQ(0u, slice.size());
  EXPECT_TRUE(slice.empty());
  EXPECT_EQ(std::string(""), slice.ToString());
  // data() is still a valid pointer per interface expectations; we won't dereference it.
  ASSERT_NE(nullptr, slice.data());
}

// Exceptional / error case (observable via assert in debug builds):
// removing more than size() should trigger an assertion failure.
// Guarded so it only runs when death tests are available and asserts are enabled.
#if GTEST_HAS_DEATH_TEST && !defined(NDEBUG)
TEST_F(SliceRemovePrefixTest_8, RemoveMoreThanSizeTriggersAssert_8) {
  const char* s = "abc";
  Slice slice(s, 3);

  // Expect process death due to failed assert(n <= size()).
  EXPECT_DEATH(
      {
        // Use an inline block so EXPECT_DEATH captures only the call.
        slice.remove_prefix(4);
      },
      ".*");
}
#endif
