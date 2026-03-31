#include <gtest/gtest.h>
#include <string>
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"

// Tests exercise the DFA through RE2's public interface since
// dfa.cc is an internal implementation file.

class DFATest_440 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic full match - exercises DFA matching path
TEST_F(DFATest_440, BasicFullMatch_440) {
  RE2 re("hello");
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("hello world", re));
  EXPECT_FALSE(RE2::FullMatch("hell", re));
}

// Test basic partial match - exercises DFA search
TEST_F(DFATest_440, BasicPartialMatch_440) {
  RE2 re("hello");
  EXPECT_TRUE(RE2::PartialMatch("hello world", re));
  EXPECT_TRUE(RE2::PartialMatch("say hello", re));
  EXPECT_FALSE(RE2::PartialMatch("helo", re));
}

// Test empty pattern
TEST_F(DFATest_440, EmptyPattern_440) {
  RE2 re("");
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::PartialMatch("anything", re));
}

// Test empty input string
TEST_F(DFATest_440, EmptyInput_440) {
  RE2 re("a*");
  EXPECT_TRUE(RE2::FullMatch("", re));

  RE2 re2("a+");
  EXPECT_FALSE(RE2::FullMatch("", re2));
}

// Test character classes - exercises DFA state transitions
TEST_F(DFATest_440, CharacterClasses_440) {
  RE2 re("[a-z]+");
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_FALSE(RE2::FullMatch("ABC", re));
  EXPECT_FALSE(RE2::FullMatch("abc123", re));
}

// Test alternation - exercises DFA branching
TEST_F(DFATest_440, Alternation_440) {
  RE2 re("cat|dog|bird");
  EXPECT_TRUE(RE2::FullMatch("cat", re));
  EXPECT_TRUE(RE2::FullMatch("dog", re));
  EXPECT_TRUE(RE2::FullMatch("bird", re));
  EXPECT_FALSE(RE2::FullMatch("fish", re));
}

// Test repetition - exercises DFA looping states
TEST_F(DFATest_440, Repetition_440) {
  RE2 re("a{3,5}");
  EXPECT_FALSE(RE2::FullMatch("aa", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaaa", re));
  EXPECT_FALSE(RE2::FullMatch("aaaaaa", re));
}

// Test anchored matching
TEST_F(DFATest_440, AnchoredMatch_440) {
  RE2 re("^hello$");
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("hello\n", re));
}

// Test dot matching - exercises byte-level DFA transitions
TEST_F(DFATest_440, DotMatching_440) {
  RE2 re("a.b");
  EXPECT_TRUE(RE2::FullMatch("axb", re));
  EXPECT_TRUE(RE2::FullMatch("a1b", re));
  EXPECT_FALSE(RE2::FullMatch("ab", re));
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));  // dot doesn't match newline by default
}

// Test longer input to exercise DFA caching/state reuse
TEST_F(DFATest_440, LongerInput_440) {
  RE2 re("[0-9]+");
  std::string long_digits(10000, '5');
  EXPECT_TRUE(RE2::FullMatch(long_digits, re));

  std::string almost_digits = long_digits + "a";
  EXPECT_FALSE(RE2::FullMatch(almost_digits, re));
}

// Test invalid pattern
TEST_F(DFATest_440, InvalidPattern_440) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
}

// Test with special bytes (null bytes in input)
TEST_F(DFATest_440, NullBytesInInput_440) {
  RE2 re("a.b");
  std::string input("a\0b", 3);
  EXPECT_TRUE(RE2::FullMatch(input, re));
}

// Test partial match with capture groups (DFA is used for finding match location)
TEST_F(DFATest_440, PartialMatchWithCapture_440) {
  RE2 re("(\\d+)");
  std::string captured;
  EXPECT_TRUE(RE2::PartialMatch("abc 123 def", re, &captured));
  EXPECT_EQ("123", captured);
}

// Test DFA with word boundaries exercised through complex patterns
TEST_F(DFATest_440, ComplexPattern_440) {
  RE2 re("(a|b)*abb");
  EXPECT_TRUE(RE2::FullMatch("abb", re));
  EXPECT_TRUE(RE2::FullMatch("aabb", re));
  EXPECT_TRUE(RE2::FullMatch("babb", re));
  EXPECT_FALSE(RE2::FullMatch("ab", re));
}

// Test DeadState-like behavior: pattern that can never match
TEST_F(DFATest_440, NeverMatchPattern_440) {
  RE2 re("[^\\s\\S]");  // matches nothing
  EXPECT_FALSE(RE2::FullMatch("", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::PartialMatch("anything", re));
}

// Test FullMatch-like behavior: pattern that always matches full string
TEST_F(DFATest_440, AlwaysMatchPattern_440) {
  RE2 re(".*");
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("anything goes here", re));
}

// Test with high byte values to exercise BytePtr-like byte handling
TEST_F(DFATest_440, HighByteValues_440) {
  RE2 re("[\x80-\xff]+");
  std::string input;
  input.push_back('\x80');
  input.push_back('\xff');
  input.push_back('\xab');
  EXPECT_TRUE(RE2::FullMatch(input, re));

  EXPECT_FALSE(RE2::FullMatch("abc", re));
}

// Test single character match
TEST_F(DFATest_440, SingleCharMatch_440) {
  RE2 re("x");
  EXPECT_TRUE(RE2::FullMatch("x", re));
  EXPECT_FALSE(RE2::FullMatch("y", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
  EXPECT_FALSE(RE2::FullMatch("xx", re));
}

// Test optional matching
TEST_F(DFATest_440, OptionalMatch_440) {
  RE2 re("ab?c");
  EXPECT_TRUE(RE2::FullMatch("ac", re));
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_FALSE(RE2::FullMatch("abbc", re));
}

// Test DFA with multiple simultaneous RE2 objects
TEST_F(DFATest_440, MultipleDFAs_440) {
  RE2 re1("foo");
  RE2 re2("bar");
  RE2 re3("baz");

  EXPECT_TRUE(RE2::PartialMatch("foobar", re1));
  EXPECT_TRUE(RE2::PartialMatch("foobar", re2));
  EXPECT_FALSE(RE2::PartialMatch("foobar", re3));
}
