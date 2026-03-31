#include <string>
#include <memory>

#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"

namespace re2 {

class PossibleMatchRangeTest_457 : public ::testing::Test {
 protected:
  // Helper to test PossibleMatchRange via RE2's public interface
  // RE2 exposes PossibleMatchRange which internally delegates to DFA::PossibleMatchRange
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a simple literal pattern produces a valid min/max range
TEST_F(PossibleMatchRangeTest_457, SimpleLiteralPattern_457) {
  RE2 re("hello");
  std::string min, max;
  ASSERT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_FALSE(min.empty());
  EXPECT_FALSE(max.empty());
  EXPECT_LE(min, "hello");
  EXPECT_GE(max, "hello");
}

// Test that a single character pattern works
TEST_F(PossibleMatchRangeTest_457, SingleCharPattern_457) {
  RE2 re("a");
  std::string min, max;
  ASSERT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_EQ(min, "a");
  EXPECT_EQ(max, "a");
}

// Test that a character class produces correct range
TEST_F(PossibleMatchRangeTest_457, CharacterClassRange_457) {
  RE2 re("[a-z]");
  std::string min, max;
  ASSERT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_EQ(min, "a");
  EXPECT_EQ(max, "z");
}

// Test boundary: maxlen of 0
TEST_F(PossibleMatchRangeTest_457, MaxlenZero_457) {
  RE2 re("abc");
  std::string min, max;
  // With maxlen 0, the function should still return but min/max may be empty or limited
  bool result = re.PossibleMatchRange(&min, &max, 0);
  // We just test it doesn't crash; result may vary
  (void)result;
}

// Test boundary: maxlen of 1
TEST_F(PossibleMatchRangeTest_457, MaxlenOne_457) {
  RE2 re("abc");
  std::string min, max;
  ASSERT_TRUE(re.PossibleMatchRange(&min, &max, 1));
  EXPECT_LE(min.size(), static_cast<size_t>(1));
}

// Test that a dot-star pattern (matches everything) returns false
TEST_F(PossibleMatchRangeTest_457, MatchesEverything_457) {
  RE2 re(".*");
  std::string min, max;
  // .* matches every string, so there's no finite max
  bool result = re.PossibleMatchRange(&min, &max, 10);
  // The function should return false because every string matches
  EXPECT_FALSE(result);
}

// Test a pattern that matches nothing
TEST_F(PossibleMatchRangeTest_457, MatchesNothing_457) {
  RE2 re("(?!.*)impossible_to_match_this_really");
  // Use a pattern known to have no matches or a dead state
  // Actually, let's use a contradictory pattern
  RE2 re2("[^\\s\\S]");  // matches nothing - complement of everything
  std::string min, max;
  bool result = re2.PossibleMatchRange(&min, &max, 10);
  if (result) {
    EXPECT_TRUE(min.empty());
    EXPECT_TRUE(max.empty());
  }
}

// Test with an alternation pattern
TEST_F(PossibleMatchRangeTest_457, AlternationPattern_457) {
  RE2 re("abc|xyz");
  std::string min, max;
  ASSERT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, "abc");
  EXPECT_GE(max, "xyz");
}

// Test that min <= max when both are non-empty
TEST_F(PossibleMatchRangeTest_457, MinLessThanOrEqualMax_457) {
  RE2 re("[b-y]");
  std::string min, max;
  ASSERT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, max);
}

// Test with a longer maxlen
TEST_F(PossibleMatchRangeTest_457, LargeMaxlen_457) {
  RE2 re("hello world");
  std::string min, max;
  ASSERT_TRUE(re.PossibleMatchRange(&min, &max, 100));
  EXPECT_LE(min, "hello world");
  EXPECT_GE(max, "hello world");
}

// Test with pattern containing repetition
TEST_F(PossibleMatchRangeTest_457, RepetitionPattern_457) {
  RE2 re("a{3,5}");
  std::string min, max;
  ASSERT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, "aaa");
  EXPECT_GE(max, "aaaaa");
}

// Test with optional characters
TEST_F(PossibleMatchRangeTest_457, OptionalCharPattern_457) {
  RE2 re("ab?c");
  std::string min, max;
  ASSERT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, "abc");
  EXPECT_GE(max, "ac");
  EXPECT_LE(min, max);
}

// Test with digit class
TEST_F(PossibleMatchRangeTest_457, DigitClassPattern_457) {
  RE2 re("[0-9]+");
  std::string min, max;
  bool result = re.PossibleMatchRange(&min, &max, 5);
  if (result) {
    EXPECT_LE(min, max);
  }
}

// Test that an invalid regex returns false via ok()
TEST_F(PossibleMatchRangeTest_457, InvalidRegex_457) {
  RE2 re("(unclosed", RE2::Quiet);
  std::string min, max;
  // If the regex is invalid, the DFA should not be ok, and PossibleMatchRange should return false
  EXPECT_FALSE(re.ok());
}

// Test with a prefix pattern
TEST_F(PossibleMatchRangeTest_457, PrefixPattern_457) {
  RE2 re("abc.*");
  std::string min, max;
  bool result = re.PossibleMatchRange(&min, &max, 10);
  // abc.* may or may not have a finite range depending on implementation
  if (result) {
    EXPECT_LE(min, "abc");
  }
}

// Test multiple calls produce consistent results
TEST_F(PossibleMatchRangeTest_457, ConsistentResults_457) {
  RE2 re("test");
  std::string min1, max1, min2, max2;
  ASSERT_TRUE(re.PossibleMatchRange(&min1, &max1, 10));
  ASSERT_TRUE(re.PossibleMatchRange(&min2, &max2, 10));
  EXPECT_EQ(min1, min2);
  EXPECT_EQ(max1, max2);
}

// Test with a complex alternation
TEST_F(PossibleMatchRangeTest_457, ComplexAlternation_457) {
  RE2 re("alpha|beta|gamma|delta");
  std::string min, max;
  ASSERT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, "alpha");
  EXPECT_GE(max, "gamma");
  EXPECT_LE(min, max);
}

// Test maxlen equal to pattern length
TEST_F(PossibleMatchRangeTest_457, MaxlenEqualPatternLength_457) {
  RE2 re("abc");
  std::string min, max;
  ASSERT_TRUE(re.PossibleMatchRange(&min, &max, 3));
  EXPECT_EQ(min, "abc");
  EXPECT_EQ(max, "abc");
}

// Test maxlen shorter than pattern length
TEST_F(PossibleMatchRangeTest_457, MaxlenShorterThanPattern_457) {
  RE2 re("abcdef");
  std::string min, max;
  bool result = re.PossibleMatchRange(&min, &max, 3);
  if (result) {
    EXPECT_LE(min.size(), static_cast<size_t>(3));
    EXPECT_LE(min, max);
  }
}

// Test with a case-insensitive pattern
TEST_F(PossibleMatchRangeTest_457, CaseInsensitivePattern_457) {
  RE2 re("(?i)abc");
  std::string min, max;
  ASSERT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, max);
}

}  // namespace re2
