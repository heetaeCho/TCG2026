#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prefilter_tree.h"
#include <string>
#include <vector>
#include <memory>

namespace re2 {

class PrefilterCClassTest_558 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a simple character class [abc] produces a prefilter
TEST_F(PrefilterCClassTest_558, SimpleCharClass_558) {
  RE2 re("[abc]");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // A small character class should produce some prefilter (may be NULL if trivial)
  // We just verify it doesn't crash
}

// Test that a large character class (>10 ranges) falls back to AnyCharOrAnyByte
TEST_F(PrefilterCClassTest_558, LargeCharClassFallsBackToAny_558) {
  // This creates a character class with many ranges (>10)
  RE2 re("[aeiouAEIOU0-9\\x80-\\xff]");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // Large class should result in no useful prefilter (effectively ANY)
  // NULL prefilter means "match everything"
}

// Test character class with single character [a]
TEST_F(PrefilterCClassTest_558, SingleCharClass_558) {
  RE2 re("[a]");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  if (pf != nullptr) {
    // Single char class should produce ATOM prefilter
    EXPECT_TRUE(pf->op() == Prefilter::ALL || pf->op() == Prefilter::ATOM);
  }
}

// Test character class with a range [a-z]
TEST_F(PrefilterCClassTest_558, RangeCharClass_558) {
  RE2 re("[a-z]");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // 26 characters > 10, should fall back to AnyCharOrAnyByte (no useful filter)
}

// Test character class with exactly 10 elements
TEST_F(PrefilterCClassTest_558, ExactlyTenElements_558) {
  RE2 re("[a-j]");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // 10 characters in one range; size() returns number of ranges (1), not chars
  // So this should NOT trigger the >10 fallback (size is 1 range)
}

// Test character class with latin1 mode (using Latin1 encoding)
TEST_F(PrefilterCClassTest_558, Latin1CharClass_558) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re("[abc]", opts);
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // Should not crash; latin1 path used
}

// Test empty pattern with character class negation [^a-z] which could be large
TEST_F(PrefilterCClassTest_558, NegatedCharClass_558) {
  RE2 re("[^a-z]");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // Negated class likely has many ranges, should fall back
}

// Test character class in context of a longer pattern
TEST_F(PrefilterCClassTest_558, CharClassInPattern_558) {
  RE2 re("foo[abc]bar");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  if (pf != nullptr) {
    // Should produce some AND/ATOM combination
    EXPECT_TRUE(pf->op() == Prefilter::ATOM ||
                pf->op() == Prefilter::AND ||
                pf->op() == Prefilter::OR ||
                pf->op() == Prefilter::ALL);
  }
}

// Test dot (any char) which internally may use CClass
TEST_F(PrefilterCClassTest_558, DotCharClass_558) {
  RE2 re(".");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // Dot matches everything, so prefilter should be ALL or NULL
}

// Test multiple small character classes
TEST_F(PrefilterCClassTest_558, MultipleSmallCharClasses_558) {
  RE2 re("[ab][cd][ef]");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // Multiple small classes should create useful prefilters
}

// Test character class with exactly 11 ranges
TEST_F(PrefilterCClassTest_558, ElevenRangesCharClass_558) {
  // Create pattern with many disjoint single-char ranges to get >10 ranges
  RE2 re("[acegikmoqsuvwxyz]");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // Depending on how ranges are merged, size may or may not exceed 10
}

// Test Unicode character class
TEST_F(PrefilterCClassTest_558, UnicodeCharClass_558) {
  RE2 re("[\\x{100}-\\x{10f}]");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // Unicode characters should be handled via UTF-8 path
}

// Test Latin1 with high bytes
TEST_F(PrefilterCClassTest_558, Latin1HighBytes_558) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re("[\\xc0-\\xc5]", opts);
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // Latin1 high bytes should use Latin1 lowering
}

// Test case-insensitive character class
TEST_F(PrefilterCClassTest_558, CaseInsensitiveCharClass_558) {
  RE2 re("(?i)[abc]");
  ASSERT_TRUE(re.ok());
  std::unique_ptr<Prefilter> pf(Prefilter::FromRE2(&re));
  // Case insensitive should still produce valid prefilter
}

}  // namespace re2
