#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>

namespace re2 {
namespace {

// Test that LazyRE2 can be initialized and accessed via operator->
TEST(LazyRE2Test_47, ArrowOperatorReturnsValidPointer_47) {
  static LazyRE2 re = {"hello"};
  RE2* ptr = re.operator->();
  ASSERT_NE(ptr, nullptr);
}

// Test that LazyRE2 pattern is correctly set
TEST(LazyRE2Test_47, PatternIsCorrect_47) {
  static LazyRE2 re = {"world"};
  EXPECT_EQ(re->pattern(), "world");
}

// Test that LazyRE2 get() returns the same pointer as operator->
TEST(LazyRE2Test_47, GetReturnsSameAsArrowOperator_47) {
  static LazyRE2 re = {"test"};
  EXPECT_EQ(re.get(), re.operator->());
}

// Test that LazyRE2 dereference operator returns a valid reference
TEST(LazyRE2Test_47, DereferenceOperatorReturnsValidReference_47) {
  static LazyRE2 re = {"abc"};
  RE2& ref = *re;
  EXPECT_EQ(ref.pattern(), "abc");
}

// Test that LazyRE2 with a simple regex can match
TEST(LazyRE2Test_47, SimpleMatchWorks_47) {
  static LazyRE2 re = {"\\d+"};
  EXPECT_TRUE(RE2::FullMatch("12345", *re));
  EXPECT_FALSE(RE2::FullMatch("abcde", *re));
}

// Test that LazyRE2 with a complex regex works
TEST(LazyRE2Test_47, ComplexPatternWorks_47) {
  static LazyRE2 re = {"([a-z]+)(\\d+)"};
  std::string word;
  int number;
  EXPECT_TRUE(RE2::FullMatch("hello123", *re, &word, &number));
  EXPECT_EQ(word, "hello");
  EXPECT_EQ(number, 123);
}

// Test that LazyRE2 ok() returns true for valid patterns
TEST(LazyRE2Test_47, ValidPatternIsOk_47) {
  static LazyRE2 re = {"valid"};
  EXPECT_TRUE(re->ok());
}

// Test that LazyRE2 with an invalid pattern reports not ok
TEST(LazyRE2Test_47, InvalidPatternIsNotOk_47) {
  static LazyRE2 re = {"("};  // unbalanced parenthesis
  EXPECT_FALSE(re->ok());
}

// Test that LazyRE2 with empty pattern works
TEST(LazyRE2Test_47, EmptyPatternWorks_47) {
  static LazyRE2 re = {""};
  EXPECT_TRUE(re->ok());
  EXPECT_TRUE(RE2::FullMatch("", *re));
  EXPECT_FALSE(RE2::FullMatch("notempty", *re));
}

// Test that LazyRE2 partial match works
TEST(LazyRE2Test_47, PartialMatchWorks_47) {
  static LazyRE2 re = {"\\d+"};
  EXPECT_TRUE(RE2::PartialMatch("abc123def", *re));
  EXPECT_FALSE(RE2::PartialMatch("abcdef", *re));
}

// Test that multiple LazyRE2 instances are independent
TEST(LazyRE2Test_47, MultipleInstancesAreIndependent_47) {
  static LazyRE2 re1 = {"foo"};
  static LazyRE2 re2 = {"bar"};
  EXPECT_NE(re1.get(), re2.get());
  EXPECT_EQ(re1->pattern(), "foo");
  EXPECT_EQ(re2->pattern(), "bar");
}

// Test that LazyRE2 get() is idempotent (returns same pointer on repeated calls)
TEST(LazyRE2Test_47, GetIsIdempotent_47) {
  static LazyRE2 re = {"idempotent"};
  RE2* first = re.get();
  RE2* second = re.get();
  EXPECT_EQ(first, second);
}

// Test LazyRE2 with a pattern containing special characters
TEST(LazyRE2Test_47, SpecialCharactersPattern_47) {
  static LazyRE2 re = {"\\.(cpp|h)$"};
  EXPECT_TRUE(RE2::PartialMatch("file.cpp", *re));
  EXPECT_TRUE(RE2::PartialMatch("file.h", *re));
  EXPECT_FALSE(RE2::PartialMatch("file.py", *re));
}

// Test LazyRE2 with dot-star pattern
TEST(LazyRE2Test_47, DotStarPatternMatchesAnything_47) {
  static LazyRE2 re = {".*"};
  EXPECT_TRUE(RE2::FullMatch("anything goes here!", *re));
  EXPECT_TRUE(RE2::FullMatch("", *re));
}

// Test that LazyRE2 with options can be used (default CannedOptions)
TEST(LazyRE2Test_47, WithOptionsWorks_47) {
  static LazyRE2 re = {"test", RE2::Latin1};
  EXPECT_TRUE(re->ok());
  EXPECT_TRUE(RE2::FullMatch("test", *re));
}

}  // namespace
}  // namespace re2
