// File: HtmlFonts_test_2624.cpp
#include <gtest/gtest.h>

// Adjust include path as needed for your build system/include dirs.
#include "TestProjects/poppler/utils/HtmlFonts.h"

class HtmlFontTest_2624 : public ::testing::Test {
 protected:
  HtmlFont font_;
};

// Since the provided public interface only exposes setLineSize(int) and does not
// provide any observable getter in the partial code, these tests focus on
// observable behavior via the interface: the call should be safe for typical
// and boundary integer values and support repeated updates.

TEST_F(HtmlFontTest_2624, SetLineSizeAcceptsZero_2624) {
  EXPECT_NO_THROW(font_.setLineSize(0));
}

TEST_F(HtmlFontTest_2624, SetLineSizeAcceptsPositive_2624) {
  EXPECT_NO_THROW(font_.setLineSize(1));
  EXPECT_NO_THROW(font_.setLineSize(12));
  EXPECT_NO_THROW(font_.setLineSize(100));
}

TEST_F(HtmlFontTest_2624, SetLineSizeAcceptsNegative_2624) {
  // Boundary/error-like input: negative line size.
  // Interface doesn't specify validation or errors; we only assert it is callable.
  EXPECT_NO_THROW(font_.setLineSize(-1));
  EXPECT_NO_THROW(font_.setLineSize(-999));
}

TEST_F(HtmlFontTest_2624, SetLineSizeAcceptsIntExtremes_2624) {
  EXPECT_NO_THROW(font_.setLineSize(std::numeric_limits<int>::min()));
  EXPECT_NO_THROW(font_.setLineSize(std::numeric_limits<int>::max()));
}

TEST_F(HtmlFontTest_2624, SetLineSizeCanBeCalledRepeatedly_2624) {
  EXPECT_NO_THROW(font_.setLineSize(10));
  EXPECT_NO_THROW(font_.setLineSize(10));   // same value again
  EXPECT_NO_THROW(font_.setLineSize(11));   // different value
  EXPECT_NO_THROW(font_.setLineSize(-10));  // switch sign
  EXPECT_NO_THROW(font_.setLineSize(0));    // back to zero
}