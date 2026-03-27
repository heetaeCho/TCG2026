// ============================================================================
// tests_minoltamn_int_split_1016.cpp
// Unit tests for Exiv2::Internal::split (from minoltamn_int.cpp)
// TEST_ID: 1016
// ============================================================================

#include <gtest/gtest.h>

#include <string>
#include <vector>

// NOTE:
// split() is declared "static" inside minoltamn_int.cpp (internal linkage).
// To test it via its real interface, we include the .cpp into this test TU.
#include "minoltamn_int.cpp"

namespace {

class SplitTest_1016 : public ::testing::Test {
 protected:
  static void ExpectEq(const std::vector<std::string>& actual,
                       const std::vector<std::string>& expected) {
    ASSERT_EQ(actual.size(), expected.size());
    for (size_t i = 0; i < actual.size(); ++i) {
      EXPECT_EQ(actual[i], expected[i]) << "index=" << i;
    }
  }
};

TEST_F(SplitTest_1016, SplitsSimpleCommaSeparated_1016) {
  const std::string s = "a,b,c";
  const std::string delim = ",";

  auto out = Exiv2::Internal::split(s, delim);

  ExpectEq(out, {"a", "b", "c"});
}

TEST_F(SplitTest_1016, NoDelimiterReturnsWholeString_1016) {
  const std::string s = "abc";
  const std::string delim = ",";

  auto out = Exiv2::Internal::split(s, delim);

  ExpectEq(out, {"abc"});
}

TEST_F(SplitTest_1016, EmptyInputReturnsEmptyVector_1016) {
  const std::string s;
  const std::string delim = ",";

  auto out = Exiv2::Internal::split(s, delim);

  EXPECT_TRUE(out.empty());
}

TEST_F(SplitTest_1016, LeadingDelimiterDoesNotProduceEmptyToken_1016) {
  const std::string s = ",a,b";
  const std::string delim = ",";

  auto out = Exiv2::Internal::split(s, delim);

  ExpectEq(out, {"a", "b"});
}

TEST_F(SplitTest_1016, TrailingDelimiterDoesNotProduceEmptyToken_1016) {
  const std::string s = "a,b,";
  const std::string delim = ",";

  auto out = Exiv2::Internal::split(s, delim);

  ExpectEq(out, {"a", "b"});
}

TEST_F(SplitTest_1016, ConsecutiveDelimitersSkipEmptyTokens_1016) {
  const std::string s = "a,,b,,,c";
  const std::string delim = ",";

  auto out = Exiv2::Internal::split(s, delim);

  ExpectEq(out, {"a", "b", "c"});
}

TEST_F(SplitTest_1016, DelimiterLongerThanOneCharacter_1016) {
  const std::string s = "a::b::::c";
  const std::string delim = "::";

  auto out = Exiv2::Internal::split(s, delim);

  // "a::b::::c" split by "::" => ["a","b","c"] (empty tokens skipped)
  ExpectEq(out, {"a", "b", "c"});
}

TEST_F(SplitTest_1016, DelimiterNotPresentWithMultiCharDelim_1016) {
  const std::string s = "a:b:c";
  const std::string delim = "::";

  auto out = Exiv2::Internal::split(s, delim);

  ExpectEq(out, {"a:b:c"});
}

TEST_F(SplitTest_1016, StringEqualsDelimiterReturnsEmptyVector_1016) {
  const std::string s = ",";
  const std::string delim = ",";

  auto out = Exiv2::Internal::split(s, delim);

  EXPECT_TRUE(out.empty());
}

TEST_F(SplitTest_1016, OnlyDelimitersReturnsEmptyVector_1016) {
  const std::string s = ",,,";
  const std::string delim = ",";

  auto out = Exiv2::Internal::split(s, delim);

  EXPECT_TRUE(out.empty());
}

TEST_F(SplitTest_1016, PreservesWhitespaceInTokens_1016) {
  const std::string s = " a ,  b, c ";
  const std::string delim = ",";

  auto out = Exiv2::Internal::split(s, delim);

  // split() does not trim (observable behavior from returned tokens)
  ExpectEq(out, {" a ", "  b", " c "});
}

TEST_F(SplitTest_1016, HandlesDelimiterAtBothEnds_1016) {
  const std::string s = ",a,b,";
  const std::string delim = ",";

  auto out = Exiv2::Internal::split(s, delim);

  ExpectEq(out, {"a", "b"});
}

TEST_F(SplitTest_1016, LargeInputManyTokens_1016) {
  std::string s;
  const std::string delim = "|";

  // Build: "t0|t1|...|t99"
  std::vector<std::string> expected;
  expected.reserve(100);
  for (int i = 0; i < 100; ++i) {
    std::string tok = "t" + std::to_string(i);
    expected.push_back(tok);
    s += tok;
    if (i != 99) s += delim;
  }

  auto out = Exiv2::Internal::split(s, delim);

  ExpectEq(out, expected);
}

}  // namespace