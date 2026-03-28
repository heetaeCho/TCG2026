// File: poppler-point-copy-test_2470.cc
#include <gtest/gtest.h>

#include <glib.h>

// Poppler GLib header that declares PopplerPoint and poppler_point_copy().
#include "poppler-page.h"

extern "C" {
PopplerPoint *poppler_point_copy(PopplerPoint *point);
}

class PopplerPointCopyTest_2470 : public ::testing::Test {
protected:
  void TearDown() override {
    // Ensure GLib slice allocator is in a clean state (not strictly required,
    // but keeps tests well-behaved across different GLib configurations).
    // No explicit teardown needed beyond freeing allocations in each test.
  }
};

TEST_F(PopplerPointCopyTest_2470, NullInputReturnsNull_2470) {
  PopplerPoint *copied = poppler_point_copy(nullptr);
  EXPECT_EQ(copied, nullptr);
}

TEST_F(PopplerPointCopyTest_2470, ValidInputReturnsNonNullDistinctPointer_2470) {
  PopplerPoint *p = g_slice_new0(PopplerPoint);
  ASSERT_NE(p, nullptr);

  PopplerPoint *copied = poppler_point_copy(p);
  ASSERT_NE(copied, nullptr);

  // Observable behavior: it should be a duplicate allocation, not the same pointer.
  EXPECT_NE(copied, p);

  g_slice_free(PopplerPoint, copied);
  g_slice_free(PopplerPoint, p);
}

TEST_F(PopplerPointCopyTest_2470, CopyCanBeCalledMultipleTimesAndEachCopyIsDistinct_2470) {
  PopplerPoint *p = g_slice_new0(PopplerPoint);
  ASSERT_NE(p, nullptr);

  PopplerPoint *c1 = poppler_point_copy(p);
  PopplerPoint *c2 = poppler_point_copy(p);

  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);

  EXPECT_NE(c1, p);
  EXPECT_NE(c2, p);
  EXPECT_NE(c1, c2);

  g_slice_free(PopplerPoint, c2);
  g_slice_free(PopplerPoint, c1);
  g_slice_free(PopplerPoint, p);
}

TEST_F(PopplerPointCopyTest_2470, CopyOfCopyProducesAnotherDistinctPointer_2470) {
  PopplerPoint *p = g_slice_new0(PopplerPoint);
  ASSERT_NE(p, nullptr);

  PopplerPoint *c1 = poppler_point_copy(p);
  ASSERT_NE(c1, nullptr);

  PopplerPoint *c2 = poppler_point_copy(c1);
  ASSERT_NE(c2, nullptr);

  EXPECT_NE(c1, p);
  EXPECT_NE(c2, p);
  EXPECT_NE(c2, c1);

  g_slice_free(PopplerPoint, c2);
  g_slice_free(PopplerPoint, c1);
  g_slice_free(PopplerPoint, p);
}