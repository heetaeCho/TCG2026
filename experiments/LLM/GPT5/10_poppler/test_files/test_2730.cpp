// File: print_matrix_test_2730.cc
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <limits>
#include <regex>
#include <string>

// Include the production .cc directly so we can reach the internal-linkage helper.
// This is a common testing technique for file-local helpers (static functions).
#include "TestProjects/poppler/utils/HtmlOutputDev.cc"

using ::testing::HasSubstr;
using ::testing::Not;

namespace {

class HtmlOutputDevPrintMatrixTest_2730 : public ::testing::Test {
protected:
  static void ExpectBracketedFourFields(const std::string &s) {
    ASSERT_FALSE(s.empty());
    EXPECT_TRUE(!s.empty() && s.front() == '[');
    EXPECT_TRUE(!s.empty() && s.back() == ']');

    // Expect exactly 4 fields separated by single spaces inside brackets:
    // "[<a> <b> <c> <d>]"
    // Keep it tolerant to numeric formatting by allowing any non-space sequences.
    static const std::regex kRe(R"(^\[[^ ]+ [^ ]+ [^ ]+ [^ ]+\]$)");
    EXPECT_TRUE(std::regex_match(s, kRe)) << "got: " << s;
  }
};

TEST_F(HtmlOutputDevPrintMatrixTest_2730, BasicIntegersExact_2730) {
  const std::array<double, 4> mat = {1.0, 2.0, 3.0, 4.0};
  const std::string s = print_matrix(mat);

  // For %g-style formatting, integer-valued doubles should typically render as integers.
  EXPECT_EQ(s, "[1 2 3 4]");
}

TEST_F(HtmlOutputDevPrintMatrixTest_2730, MixedFloatsHaveExpectedStructure_2730) {
  const std::array<double, 4> mat = {0.5, -2.25, 3.0, 4.75};
  const std::string s = print_matrix(mat);

  ExpectBracketedFourFields(s);

  // Check some stable substrings (avoid over-specifying formatting).
  EXPECT_THAT(s, HasSubstr("0.5"));
  EXPECT_THAT(s, HasSubstr("-2.25"));
  EXPECT_THAT(s, HasSubstr("4.75"));
  // 3.0 might render as "3" in %g formatting, so just ensure it's present as a token-ish.
  EXPECT_THAT(s, HasSubstr(" 3 "));
}

TEST_F(HtmlOutputDevPrintMatrixTest_2730, ZerosAndNegativesAreRepresented_2730) {
  const std::array<double, 4> mat = {-0.0, 0.0, -1.0, 1.0};
  const std::string s = print_matrix(mat);

  ExpectBracketedFourFields(s);

  // -0.0 can be rendered as "0" or "-0" depending on formatting implementation,
  // so avoid asserting its exact spelling. Check the others.
  EXPECT_THAT(s, HasSubstr("-1"));
  EXPECT_THAT(s, HasSubstr(" 1]"));  // last token is 1
}

TEST_F(HtmlOutputDevPrintMatrixTest_2730, LargeAndSmallMagnitudesDoNotBreakFormat_2730) {
  const std::array<double, 4> mat = {1e308, 1e-308, -1e100, 0.0};
  const std::string s = print_matrix(mat);

  ExpectBracketedFourFields(s);

  // For very large/small magnitudes, %g typically uses scientific notation.
  // Don't overfit exact exponent formatting; just ensure there's some scientific marker.
  EXPECT_TRUE(s.find('e') != std::string::npos || s.find('E') != std::string::npos)
      << "expected scientific notation somewhere, got: " << s;
}

TEST_F(HtmlOutputDevPrintMatrixTest_2730, NaNAndInfinityDoNotCrashAndKeepShape_2730) {
  const double nan = std::numeric_limits<double>::quiet_NaN();
  const double inf = std::numeric_limits<double>::infinity();

  const std::array<double, 4> mat = {nan, inf, -inf, 0.0};
  const std::string s = print_matrix(mat);

  // Observable behavior: returns a bracketed 4-field string, no crash.
  ExpectBracketedFourFields(s);

  // Also ensure it still contains at least 3 separators between 4 fields.
  const auto spaces = std::count(s.begin(), s.end(), ' ');
  EXPECT_GE(spaces, 3) << "got: " << s;
}

}  // namespace