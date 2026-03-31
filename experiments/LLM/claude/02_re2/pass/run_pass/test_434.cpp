#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/set.h"
#include <string>
#include <vector>
#include <memory>

namespace re2 {

class DFATest_434 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic matching with DFA via RE2
TEST_F(DFATest_434, BasicMatch_434) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test partial match uses DFA search
TEST_F(DFATest_434, PartialMatch_434) {
  RE2 re("ell");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello", re));
  EXPECT_FALSE(RE2::PartialMatch("world", re));
}

// Test empty pattern
TEST_F(DFATest_434, EmptyPattern_434) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::PartialMatch("anything", re));
}

// Test empty text
TEST_F(DFATest_434, EmptyText_434) {
  RE2 re("a*");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
}

// Test anchored search (FullMatch is inherently anchored)
TEST_F(DFATest_434, AnchoredSearch_434) {
  RE2 re("^hello$");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("hello world", re));
}

// Test character classes
TEST_F(DFATest_434, CharacterClass_434) {
  RE2 re("[a-z]+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
  EXPECT_FALSE(RE2::FullMatch("123", re));
}

// Test alternation
TEST_F(DFATest_434, Alternation_434) {
  RE2 re("cat|dog");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("cat", re));
  EXPECT_TRUE(RE2::FullMatch("dog", re));
  EXPECT_FALSE(RE2::FullMatch("bird", re));
}

// Test repetition
TEST_F(DFATest_434, Repetition_434) {
  RE2 re("a{3,5}");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("aa", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaaa", re));
  EXPECT_FALSE(RE2::FullMatch("aaaaaa", re));
}

// Test PossibleMatchRange via RE2
TEST_F(DFATest_434, PossibleMatchRange_434) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::string min, max;
  EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, "hello");
  EXPECT_GE(max, "hello");
}

// Test PossibleMatchRange with wildcard
TEST_F(DFATest_434, PossibleMatchRangeWildcard_434) {
  RE2 re("h.*o");
  ASSERT_TRUE(re.ok());
  std::string min, max;
  EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  // min should start with 'h'
  EXPECT_FALSE(min.empty());
  EXPECT_EQ(min[0], 'h');
}

// Test PossibleMatchRange with maxlen boundary
TEST_F(DFATest_434, PossibleMatchRangeMaxlen_434) {
  RE2 re("[a-z]+");
  ASSERT_TRUE(re.ok());
  std::string min, max;
  EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 1));
  EXPECT_LE(min.size(), 1u);
}

// Test long text
TEST_F(DFATest_434, LongText_434) {
  RE2 re("needle");
  ASSERT_TRUE(re.ok());
  std::string haystack(10000, 'a');
  haystack += "needle";
  haystack += std::string(10000, 'b');
  EXPECT_TRUE(RE2::PartialMatch(haystack, re));
}

// Test with special characters
TEST_F(DFATest_434, SpecialCharacters_434) {
  RE2 re("\\.");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch(".", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
}

// Test dot matches any character
TEST_F(DFATest_434, DotMatchesAny_434) {
  RE2 re(".");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("1", re));
  EXPECT_TRUE(RE2::FullMatch(".", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
  EXPECT_FALSE(RE2::FullMatch("ab", re));
}

// Test star quantifier
TEST_F(DFATest_434, StarQuantifier_434) {
  RE2 re("a*");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_FALSE(RE2::FullMatch("b", re));
}

// Test plus quantifier
TEST_F(DFATest_434, PlusQuantifier_434) {
  RE2 re("a+");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
}

// Test question mark quantifier
TEST_F(DFATest_434, QuestionQuantifier_434) {
  RE2 re("a?");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::FullMatch("aa", re));
}

// Test with RE2::Set which exercises DFA BuildAllStates/Search
TEST_F(DFATest_434, RE2SetMatch_434) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  ASSERT_GE(s.Add("foo", nullptr), 0);
  ASSERT_GE(s.Add("bar", nullptr), 0);
  ASSERT_GE(s.Add("baz", nullptr), 0);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("foo", &matches));
  ASSERT_EQ(matches.size(), 1u);
  EXPECT_EQ(matches[0], 0);

  matches.clear();
  EXPECT_TRUE(s.Match("bar", &matches));
  ASSERT_EQ(matches.size(), 1u);
  EXPECT_EQ(matches[0], 1);

  matches.clear();
  EXPECT_FALSE(s.Match("qux", &matches));
  EXPECT_TRUE(matches.empty());
}

// Test RE2::Set with overlapping patterns
TEST_F(DFATest_434, RE2SetOverlapping_434) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  ASSERT_GE(s.Add("foo", nullptr), 0);
  ASSERT_GE(s.Add("foobar", nullptr), 0);
  ASSERT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("foobar", &matches));
  EXPECT_GE(matches.size(), 1u);
}

// Test with limited DFA memory to trigger cache resets
TEST_F(DFATest_434, LimitedMemory_434) {
  RE2::Options opts;
  opts.set_max_mem(1 << 14);  // very small memory
  RE2 re("[a-z]*hello[a-z]*", opts);
  ASSERT_TRUE(re.ok());
  
  // Run multiple searches to potentially trigger cache resets
  for (int i = 0; i < 100; i++) {
    std::string text(100, 'a' + (i % 26));
    RE2::PartialMatch(text, re);
  }
  EXPECT_TRUE(RE2::PartialMatch("xhellox", re));
}

// Test complex pattern
TEST_F(DFATest_434, ComplexPattern_434) {
  RE2 re("(a|b)*abb");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abb", re));
  EXPECT_TRUE(RE2::FullMatch("aabb", re));
  EXPECT_TRUE(RE2::FullMatch("babb", re));
  EXPECT_TRUE(RE2::FullMatch("abababb", re));
  EXPECT_FALSE(RE2::FullMatch("ab", re));
  EXPECT_FALSE(RE2::FullMatch("abc", re));
}

// Test binary data in text
TEST_F(DFATest_434, BinaryData_434) {
  RE2 re("\\x00\\x01\\x02");
  ASSERT_TRUE(re.ok());
  std::string text("\x00\x01\x02", 3);
  EXPECT_TRUE(RE2::FullMatch(text, re));
}

// Test unicode/UTF-8
TEST_F(DFATest_434, UTF8_434) {
  RE2 re("héllo");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("héllo", re));
  EXPECT_FALSE(RE2::FullMatch("hello", re));
}

// Test that DFA handles no-match on very long input
TEST_F(DFATest_434, NoMatchLongInput_434) {
  RE2 re("zzz");
  ASSERT_TRUE(re.ok());
  std::string text(100000, 'a');
  EXPECT_FALSE(RE2::PartialMatch(text, re));
}

// Test forward and reverse searches implicitly through RE2
TEST_F(DFATest_434, ForwardMatchEndpoint_434) {
  RE2 re("a+");
  ASSERT_TRUE(re.ok());
  absl::string_view match;
  EXPECT_TRUE(RE2::PartialMatch("bbbaaabb", re, &match));
  EXPECT_EQ(match, "aaa");
}

// Test boundary: single character text
TEST_F(DFATest_434, SingleCharText_434) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::FullMatch("b", re));
}

// Test boundary: single character pattern against long text
TEST_F(DFATest_434, SingleCharPatternLongText_434) {
  RE2 re("z");
  ASSERT_TRUE(re.ok());
  std::string text(10000, 'a');
  text[9999] = 'z';
  EXPECT_TRUE(RE2::PartialMatch(text, re));
}

// Test PossibleMatchRange with a pattern that matches everything
TEST_F(DFATest_434, PossibleMatchRangeMatchAll_434) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  std::string min, max;
  EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));
}

// Test word boundary patterns
TEST_F(DFATest_434, WordBoundary_434) {
  // Note: \b is not supported in RE2 at DFA level in the same way,
  // but word character classes are
  RE2 re("\\w+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello123", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
}

// Test nested quantifiers
TEST_F(DFATest_434, NestedQuantifiers_434) {
  RE2 re("(ab)+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("ab", re));
  EXPECT_TRUE(RE2::FullMatch("abab", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::FullMatch("aba", re));
}

// Test case insensitive matching (exercises different DFA paths)
TEST_F(DFATest_434, CaseInsensitive_434) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("HeLLo", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test that concurrent searches work (DFA is thread-safe)
TEST_F(DFATest_434, ConcurrentSearch_434) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  
  // Simple sequential simulation of what would be concurrent
  for (int i = 0; i < 1000; i++) {
    bool result = RE2::PartialMatch("say hello world", re);
    EXPECT_TRUE(result);
  }
}

// Test pattern with many states
TEST_F(DFATest_434, ManyStates_434) {
  // This creates a DFA with many states
  RE2 re("a{0,50}b");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("b", re));
  EXPECT_TRUE(RE2::FullMatch("ab", re));
  EXPECT_TRUE(RE2::FullMatch(std::string(50, 'a') + "b", re));
  EXPECT_FALSE(RE2::FullMatch(std::string(51, 'a') + "b", re));
}

}  // namespace re2
