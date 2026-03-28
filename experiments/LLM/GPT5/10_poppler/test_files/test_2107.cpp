// poppler-annot-callout-line-copy-test_2107.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler-annot.h" // for PopplerAnnotCalloutLine / _PopplerAnnotCalloutLine
// The function under test is implemented in poppler-annot.cc in the project.
extern "C" PopplerAnnotCalloutLine *poppler_annot_callout_line_copy(PopplerAnnotCalloutLine *callout);

class PopplerAnnotCalloutLineCopyTest_2107 : public ::testing::Test {
protected:
  void TearDown() override {
    // Ensure GLib allocations are freed if a test forgets (best-effort).
  }
};

TEST_F(PopplerAnnotCalloutLineCopyTest_2107, NullInputReturnsNull_2107) {
  PopplerAnnotCalloutLine *copy = poppler_annot_callout_line_copy(nullptr);
  EXPECT_EQ(copy, nullptr);
}

TEST_F(PopplerAnnotCalloutLineCopyTest_2107, ReturnsDistinctPointerForValidInput_2107) {
  PopplerAnnotCalloutLine original;
  original.multiline = 1;
  original.x3 = 10;
  original.y3 = 20;

  PopplerAnnotCalloutLine *copy = poppler_annot_callout_line_copy(&original);
  ASSERT_NE(copy, nullptr);
  EXPECT_NE(copy, &original);

  g_free(copy);
}

TEST_F(PopplerAnnotCalloutLineCopyTest_2107, CopiesAllFieldsExactly_2107) {
  PopplerAnnotCalloutLine original;
  original.multiline = 0;
  original.x3 = -123;
  original.y3 = 456;

  PopplerAnnotCalloutLine *copy = poppler_annot_callout_line_copy(&original);
  ASSERT_NE(copy, nullptr);

  EXPECT_EQ(copy->multiline, original.multiline);
  EXPECT_EQ(copy->x3, original.x3);
  EXPECT_EQ(copy->y3, original.y3);

  g_free(copy);
}

TEST_F(PopplerAnnotCalloutLineCopyTest_2107, CopyUnaffectedBySubsequentOriginalMutation_2107) {
  PopplerAnnotCalloutLine original;
  original.multiline = 1;
  original.x3 = 7;
  original.y3 = 8;

  PopplerAnnotCalloutLine *copy = poppler_annot_callout_line_copy(&original);
  ASSERT_NE(copy, nullptr);

  // Mutate original after copying; copy should preserve the snapshot values.
  original.multiline = 0;
  original.x3 = 999;
  original.y3 = -999;

  EXPECT_EQ(copy->multiline, 1);
  EXPECT_EQ(copy->x3, 7);
  EXPECT_EQ(copy->y3, 8);

  g_free(copy);
}

TEST_F(PopplerAnnotCalloutLineCopyTest_2107, HandlesBoundaryIntegerValues_2107) {
  PopplerAnnotCalloutLine original;
  original.multiline = G_MAXINT;
  original.x3 = G_MININT;
  original.y3 = G_MAXINT;

  PopplerAnnotCalloutLine *copy = poppler_annot_callout_line_copy(&original);
  ASSERT_NE(copy, nullptr);

  EXPECT_EQ(copy->multiline, G_MAXINT);
  EXPECT_EQ(copy->x3, G_MININT);
  EXPECT_EQ(copy->y3, G_MAXINT);

  g_free(copy);
}