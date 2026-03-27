// File: HtmlFonts_test_2629.cpp

#include <gtest/gtest.h>

#include <type_traits>

#include "TestProjects/poppler/utils/HtmlFonts.h"

class HtmlFontAccuTest_2629 : public ::testing::Test {
protected:
  HtmlFontAccu accu;
};

TEST_F(HtmlFontAccuTest_2629, DefaultConstructedHasZeroSize_2629) {
  // Observable behavior via public API: size()
  EXPECT_EQ(accu.size(), 0);
}

TEST_F(HtmlFontAccuTest_2629, SizeIsNonNegative_2629) {
  // Boundary/sanity: size should never be negative.
  EXPECT_GE(accu.size(), 0);
}

TEST_F(HtmlFontAccuTest_2629, SizeIsConstCallableAndStable_2629) {
  const HtmlFontAccu &caccu = accu;

  const int s1 = caccu.size();
  const int s2 = caccu.size();

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s1, accu.size());
}

TEST_F(HtmlFontAccuTest_2629, CopyOperationsAreDeleted_2629) {
  // Observable at compile-time based on the interface contract.
  static_assert(!std::is_copy_constructible<HtmlFontAccu>::value,
                "HtmlFontAccu must not be copy-constructible");
  static_assert(!std::is_copy_assignable<HtmlFontAccu>::value,
                "HtmlFontAccu must not be copy-assignable");

  SUCCEED();
}