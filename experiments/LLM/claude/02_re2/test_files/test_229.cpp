#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include <string>

namespace re2 {

class AppendCCRangeTest_229 : public ::testing::Test {
protected:
};

// Test that a simple character class range is correctly converted to string
TEST_F(AppendCCRangeTest_229, SimpleRange_229) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::PerlX, NULL);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "[a-z]");
  re->Decref();
}

// Test single character class (lo == hi case)
TEST_F(AppendCCRangeTest_229, SingleCharClass_229) {
  Regexp* re = Regexp::Parse("[a]", Regexp::PerlX, NULL);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  // Single char class may be simplified to just "a" or "[a]"
  EXPECT_TRUE(s == "a" || s == "[a]");
  re->Decref();
}

// Test multiple ranges in a character class
TEST_F(AppendCCRangeTest_229, MultipleRanges_229) {
  Regexp* re = Regexp::Parse("[a-zA-Z]", Regexp::PerlX, NULL);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  // Should contain range representations
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test character class with digits
TEST_F(AppendCCRangeTest_229, DigitRange_229) {
  Regexp* re = Regexp::Parse("[0-9]", Regexp::PerlX, NULL);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test character class with adjacent characters (lo + 1 == hi)
TEST_F(AppendCCRangeTest_229, AdjacentChars_229) {
  Regexp* re = Regexp::Parse("[a-b]", Regexp::PerlX, NULL);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test character class with special characters that need escaping
TEST_F(AppendCCRangeTest_229, SpecialCharsInClass_229) {
  Regexp* re = Regexp::Parse("[\\x00-\\x1f]", Regexp::PerlX, NULL);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test negated character class
TEST_F(AppendCCRangeTest_229, NegatedClass_229) {
  Regexp* re = Regexp::Parse("[^a-z]", Regexp::PerlX, NULL);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test unicode range
TEST_F(AppendCCRangeTest_229, UnicodeRange_229) {
  Regexp* re = Regexp::Parse("[\\x{100}-\\x{1ff}]", Regexp::PerlX, NULL);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test dot (matches all) - exercises wide range
TEST_F(AppendCCRangeTest_229, DotMatchesAll_229) {
  Regexp* re = Regexp::Parse(".", Regexp::PerlX, NULL);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test character class with hyphen
TEST_F(AppendCCRangeTest_229, HyphenInClass_229) {
  Regexp* re = Regexp::Parse("[a-z0-9_-]", Regexp::PerlX, NULL);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

}  // namespace re2
