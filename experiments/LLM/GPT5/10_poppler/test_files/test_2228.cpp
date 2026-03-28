// File: poppler-fonts-iter-next-test_2228.cc
#include <gtest/gtest.h>

#include <vector>

// Minimal GLib-like compatibility (avoid depending on glib headers for this unit test).
using gboolean = int;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

// Minimal type definition required by the provided interface usage.
// NOTE: This matches what poppler_fonts_iter_next() dereferences in the provided snippet.
struct _PopplerFontsIter {
  int index = 0;
  std::vector<int> items;
};
using PopplerFontsIter = _PopplerFontsIter;

extern "C" {
gboolean poppler_fonts_iter_next(PopplerFontsIter *iter);
}

class PopplerFontsIterNextTest_2228 : public ::testing::Test {};

TEST_F(PopplerFontsIterNextTest_2228, NullIterReturnsFalse_2228) {
  EXPECT_EQ(poppler_fonts_iter_next(nullptr), FALSE);
}

TEST_F(PopplerFontsIterNextTest_2228, EmptyItemsReturnsFalse_2228) {
  PopplerFontsIter iter;
  iter.index = -1;            // so the first call increments to 0
  iter.items.clear();         // size == 0
  EXPECT_EQ(poppler_fonts_iter_next(&iter), FALSE);
}

TEST_F(PopplerFontsIterNextTest_2228, SingleItemAtStartReturnsFalse_2228) {
  // If index is already 0 and size is 1, the call increments to 1 and should fail.
  PopplerFontsIter iter;
  iter.index = 0;
  iter.items = {42};          // size == 1
  EXPECT_EQ(poppler_fonts_iter_next(&iter), FALSE);
}

TEST_F(PopplerFontsIterNextTest_2228, SingleItemFromBeforeStartReturnsTrueThenFalse_2228) {
  PopplerFontsIter iter;
  iter.index = -1;            // before first element
  iter.items = {7};           // size == 1

  EXPECT_EQ(poppler_fonts_iter_next(&iter), TRUE);   // -1 -> 0, within range
  EXPECT_EQ(poppler_fonts_iter_next(&iter), FALSE);  // 0 -> 1, out of range
}

TEST_F(PopplerFontsIterNextTest_2228, TwoItemsAdvancesTwiceThenStops_2228) {
  PopplerFontsIter iter;
  iter.index = -1;
  iter.items = {1, 2};        // size == 2

  EXPECT_EQ(poppler_fonts_iter_next(&iter), TRUE);   // -1 -> 0
  EXPECT_EQ(poppler_fonts_iter_next(&iter), TRUE);   // 0 -> 1
  EXPECT_EQ(poppler_fonts_iter_next(&iter), FALSE);  // 1 -> 2 (end)
}

TEST_F(PopplerFontsIterNextTest_2228, OncePastEndRemainsFalseOnSubsequentCalls_2228) {
  PopplerFontsIter iter;
  iter.index = 0;
  iter.items = {9};           // size == 1

  // First call puts it past the end.
  EXPECT_EQ(poppler_fonts_iter_next(&iter), FALSE);

  // Further calls should continue to report FALSE (still out of range).
  EXPECT_EQ(poppler_fonts_iter_next(&iter), FALSE);
  EXPECT_EQ(poppler_fonts_iter_next(&iter), FALSE);
}