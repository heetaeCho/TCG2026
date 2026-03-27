// File: HtmlFontAccu_test_2628.cpp
#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/HtmlFonts.h"

namespace {

class HtmlFontAccuTest_2628 : public ::testing::Test {
protected:
  HtmlFontAccu accu_;
};

// Helper: create a font instance without assuming internal semantics.
// This relies only on the type being constructible/copyable in the codebase.
static HtmlFont MakeFont_2628() {
  HtmlFont f{};
  return f;
}

TEST_F(HtmlFontAccuTest_2628, DefaultConstructedSizeIsZero_2628) {
  EXPECT_EQ(accu_.size(), 0);
}

TEST_F(HtmlFontAccuTest_2628, AddFontIncreasesSizeAndReturnsValidIndex_2628) {
  const int before = accu_.size();

  HtmlFont f1 = MakeFont_2628();
  int idx1 = accu_.AddFont(f1);

  EXPECT_EQ(accu_.size(), before + 1);
  EXPECT_GE(idx1, 0);
  EXPECT_LT(idx1, accu_.size());

  HtmlFont f2 = MakeFont_2628();
  int idx2 = accu_.AddFont(f2);

  EXPECT_EQ(accu_.size(), before + 2);
  EXPECT_GE(idx2, 0);
  EXPECT_LT(idx2, accu_.size());
}

TEST_F(HtmlFontAccuTest_2628, GetAfterSingleAddReturnsNonNullForIndex0_2628) {
  ASSERT_EQ(accu_.size(), 0);

  HtmlFont f = MakeFont_2628();
  accu_.AddFont(f);

  ASSERT_GE(accu_.size(), 1);
  const HtmlFont* got = accu_.Get(0);
  EXPECT_NE(got, nullptr);
}

TEST_F(HtmlFontAccuTest_2628, GetReturnsNonNullForAllValidIndices_2628) {
  // Add a few fonts to exercise boundary indices without using out-of-range.
  for (int k = 0; k < 3; ++k) {
    HtmlFont f = MakeFont_2628();
    accu_.AddFont(f);
  }

  const int n = accu_.size();
  ASSERT_GE(n, 3);

  for (int i = 0; i < n; ++i) {
    EXPECT_NE(accu_.Get(i), nullptr) << "i=" << i;
  }
}

TEST_F(HtmlFontAccuTest_2628, GetLastIndexReturnsNonNull_2628) {
  HtmlFont f1 = MakeFont_2628();
  HtmlFont f2 = MakeFont_2628();
  accu_.AddFont(f1);
  accu_.AddFont(f2);

  const int n = accu_.size();
  ASSERT_GE(n, 2);

  const HtmlFont* got_last = accu_.Get(n - 1);
  EXPECT_NE(got_last, nullptr);
}

TEST_F(HtmlFontAccuTest_2628, CSStyleReturnsNonNullForValidIndices_2628) {
  // Prepare at least two fonts so (0,1) is always in range.
  HtmlFont f1 = MakeFont_2628();
  HtmlFont f2 = MakeFont_2628();
  accu_.AddFont(f1);
  accu_.AddFont(f2);

  ASSERT_GE(accu_.size(), 2);

  auto css01 = accu_.CSStyle(0, 1);
  EXPECT_NE(css01, nullptr);

  // Boundary-like case using same index for i and j (still valid indices).
  auto css00 = accu_.CSStyle(0, 0);
  EXPECT_NE(css00, nullptr);
}

TEST_F(HtmlFontAccuTest_2628, CSStyleWorksForLastIndexPair_2628) {
  // Add several fonts and call CSStyle on the last valid indices.
  for (int k = 0; k < 4; ++k) {
    HtmlFont f = MakeFont_2628();
    accu_.AddFont(f);
  }

  const int n = accu_.size();
  ASSERT_GE(n, 4);

  auto css = accu_.CSStyle(n - 2, n - 1);
  EXPECT_NE(css, nullptr);
}

}  // namespace