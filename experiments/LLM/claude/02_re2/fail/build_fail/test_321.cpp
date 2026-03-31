#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include "re2/stringpiece.h"

namespace re2 {

class CompilerPostVisitTest_321 : public ::testing::Test {
 protected:
  // Helper to compile a pattern and check it succeeds
  bool CompileSucceeds(const std::string& pattern) {
    RE2 re(pattern);
    return re.ok();
  }

  // Helper to check that a pattern matches a string
  bool Matches(const std::string& pattern, const std::string& text) {
    return RE2::FullMatch(text, pattern);
  }

  bool PartialMatches(const std::string& pattern, const std::string& text) {
    return RE2::PartialMatch(text, pattern);
  }
};

// Test kRegexpNoMatch - pattern that produces no match
TEST_F(CompilerPostVisitTest_321, NoMatchCompiles_321) {
  // [^\s\S] matches nothing
  EXPECT_TRUE(CompileSucceeds("[^\\s\\S]"));
  EXPECT_FALSE(Matches("[^\\s\\S]", "a"));
  EXPECT_FALSE(Matches("[^\\s\\S]", ""));
}

// Test kRegexpEmptyMatch
TEST_F(CompilerPostVisitTest_321, EmptyMatchPattern_321) {
  EXPECT_TRUE(CompileSucceeds(""));
  EXPECT_TRUE(Matches("", ""));
  EXPECT_FALSE(Matches("", "a"));
}

// Test kRegexpLiteral - single literal character
TEST_F(CompilerPostVisitTest_321, LiteralSingleChar_321) {
  EXPECT_TRUE(CompileSucceeds("a"));
  EXPECT_TRUE(Matches("a", "a"));
  EXPECT_FALSE(Matches("a", "b"));
  EXPECT_FALSE(Matches("a", ""));
}

// Test kRegexpLiteral with FoldCase
TEST_F(CompilerPostVisitTest_321, LiteralFoldCase_321) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("a", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("A", re));
  EXPECT_TRUE(RE2::FullMatch("a", re));
}

// Test kRegexpLiteralString - multiple literal characters
TEST_F(CompilerPostVisitTest_321, LiteralString_321) {
  EXPECT_TRUE(CompileSucceeds("hello"));
  EXPECT_TRUE(Matches("hello", "hello"));
  EXPECT_FALSE(Matches("hello", "hell"));
  EXPECT_FALSE(Matches("hello", "helloo"));
}

// Test kRegexpConcat - concatenation of patterns
TEST_F(CompilerPostVisitTest_321, Concat_321) {
  EXPECT_TRUE(CompileSucceeds("ab"));
  EXPECT_TRUE(Matches("ab", "ab"));
  EXPECT_FALSE(Matches("ab", "a"));
  EXPECT_FALSE(Matches("ab", "ba"));
}

// Test kRegexpConcat with multiple children
TEST_F(CompilerPostVisitTest_321, ConcatMultiple_321) {
  EXPECT_TRUE(CompileSucceeds("abcdef"));
  EXPECT_TRUE(Matches("abcdef", "abcdef"));
  EXPECT_FALSE(Matches("abcdef", "abcde"));
}

// Test kRegexpAlternate - alternation
TEST_F(CompilerPostVisitTest_321, Alternate_321) {
  EXPECT_TRUE(CompileSucceeds("a|b"));
  EXPECT_TRUE(Matches("a|b", "a"));
  EXPECT_TRUE(Matches("a|b", "b"));
  EXPECT_FALSE(Matches("a|b", "c"));
  EXPECT_FALSE(Matches("a|b", "ab"));
}

// Test kRegexpAlternate with multiple alternatives
TEST_F(CompilerPostVisitTest_321, AlternateMultiple_321) {
  EXPECT_TRUE(CompileSucceeds("a|b|c|d"));
  EXPECT_TRUE(Matches("a|b|c|d", "a"));
  EXPECT_TRUE(Matches("a|b|c|d", "b"));
  EXPECT_TRUE(Matches("a|b|c|d", "c"));
  EXPECT_TRUE(Matches("a|b|c|d", "d"));
  EXPECT_FALSE(Matches("a|b|c|d", "e"));
}

// Test kRegexpStar - zero or more (greedy)
TEST_F(CompilerPostVisitTest_321, StarGreedy_321) {
  EXPECT_TRUE(CompileSucceeds("a*"));
  EXPECT_TRUE(Matches("a*", ""));
  EXPECT_TRUE(Matches("a*", "a"));
  EXPECT_TRUE(Matches("a*", "aaa"));
  EXPECT_FALSE(Matches("a*", "b"));
}

// Test kRegexpStar - non-greedy
TEST_F(CompilerPostVisitTest_321, StarNonGreedy_321) {
  EXPECT_TRUE(CompileSucceeds("a*?"));
  EXPECT_TRUE(Matches("a*?", ""));
  EXPECT_TRUE(Matches("a*?", "aaa"));
}

// Test kRegexpPlus - one or more (greedy)
TEST_F(CompilerPostVisitTest_321, PlusGreedy_321) {
  EXPECT_TRUE(CompileSucceeds("a+"));
  EXPECT_FALSE(Matches("a+", ""));
  EXPECT_TRUE(Matches("a+", "a"));
  EXPECT_TRUE(Matches("a+", "aaaa"));
  EXPECT_FALSE(Matches("a+", "b"));
}

// Test kRegexpPlus - non-greedy
TEST_F(CompilerPostVisitTest_321, PlusNonGreedy_321) {
  EXPECT_TRUE(CompileSucceeds("a+?"));
  EXPECT_FALSE(Matches("a+?", ""));
  EXPECT_TRUE(Matches("a+?", "a"));
  EXPECT_TRUE(Matches("a+?", "aaaa"));
}

// Test kRegexpQuest - zero or one (greedy)
TEST_F(CompilerPostVisitTest_321, QuestGreedy_321) {
  EXPECT_TRUE(CompileSucceeds("a?"));
  EXPECT_TRUE(Matches("a?", ""));
  EXPECT_TRUE(Matches("a?", "a"));
  EXPECT_FALSE(Matches("a?", "aa"));
}

// Test kRegexpQuest - non-greedy
TEST_F(CompilerPostVisitTest_321, QuestNonGreedy_321) {
  EXPECT_TRUE(CompileSucceeds("a??"));
  EXPECT_TRUE(Matches("a??", ""));
  EXPECT_TRUE(Matches("a??", "a"));
}

// Test kRegexpAnyChar - matches any character
TEST_F(CompilerPostVisitTest_321, AnyChar_321) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re(".", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("Z", re));
  EXPECT_TRUE(RE2::FullMatch("1", re));
  EXPECT_TRUE(RE2::FullMatch("\n", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
  EXPECT_FALSE(RE2::FullMatch("ab", re));
}

// Test kRegexpAnyByte
TEST_F(CompilerPostVisitTest_321, AnyByte_321) {
  EXPECT_TRUE(CompileSucceeds("\\C"));
  EXPECT_TRUE(PartialMatches("\\C", "a"));
}

// Test kRegexpCharClass - character class
TEST_F(CompilerPostVisitTest_321, CharClass_321) {
  EXPECT_TRUE(CompileSucceeds("[abc]"));
  EXPECT_TRUE(Matches("[abc]", "a"));
  EXPECT_TRUE(Matches("[abc]", "b"));
  EXPECT_TRUE(Matches("[abc]", "c"));
  EXPECT_FALSE(Matches("[abc]", "d"));
  EXPECT_FALSE(Matches("[abc]", ""));
}

// Test kRegexpCharClass with range
TEST_F(CompilerPostVisitTest_321, CharClassRange_321) {
  EXPECT_TRUE(CompileSucceeds("[a-z]"));
  EXPECT_TRUE(Matches("[a-z]", "a"));
  EXPECT_TRUE(Matches("[a-z]", "m"));
  EXPECT_TRUE(Matches("[a-z]", "z"));
  EXPECT_FALSE(Matches("[a-z]", "A"));
  EXPECT_FALSE(Matches("[a-z]", "0"));
}

// Test kRegexpCharClass with case folding
TEST_F(CompilerPostVisitTest_321, CharClassFoldCase_321) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("[a-z]", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("A", re));
  EXPECT_TRUE(RE2::FullMatch("Z", re));
}

// Test negated character class
TEST_F(CompilerPostVisitTest_321, CharClassNegated_321) {
  EXPECT_TRUE(CompileSucceeds("[^abc]"));
  EXPECT_FALSE(Matches("[^abc]", "a"));
  EXPECT_FALSE(Matches("[^abc]", "b"));
  EXPECT_TRUE(Matches("[^abc]", "d"));
  EXPECT_TRUE(Matches("[^abc]", "z"));
}

// Test kRegexpCapture
TEST_F(CompilerPostVisitTest_321, Capture_321) {
  std::string captured;
  EXPECT_TRUE(RE2::FullMatch("hello", "(hello)", &captured));
  EXPECT_EQ(captured, "hello");
}

// Test kRegexpCapture with nested captures
TEST_F(CompilerPostVisitTest_321, CaptureNested_321) {
  std::string outer, inner;
  EXPECT_TRUE(RE2::FullMatch("ab", "((a)b)", &outer, &inner));
  EXPECT_EQ(outer, "ab");
  EXPECT_EQ(inner, "a");
}

// Test kRegexpBeginLine
TEST_F(CompilerPostVisitTest_321, BeginLine_321) {
  EXPECT_TRUE(PartialMatches("^hello", "hello world"));
  EXPECT_TRUE(PartialMatches("^hello", "hello"));
}

// Test kRegexpEndLine
TEST_F(CompilerPostVisitTest_321, EndLine_321) {
  EXPECT_TRUE(PartialMatches("world$", "hello world"));
  EXPECT_TRUE(PartialMatches("world$", "world"));
}

// Test kRegexpBeginText
TEST_F(CompilerPostVisitTest_321, BeginText_321) {
  EXPECT_TRUE(PartialMatches("\\Ahello", "hello world"));
  EXPECT_FALSE(PartialMatches("\\Ahello", "say hello"));
}

// Test kRegexpEndText
TEST_F(CompilerPostVisitTest_321, EndText_321) {
  EXPECT_TRUE(PartialMatches("world\\z", "hello world"));
  EXPECT_FALSE(PartialMatches("world\\z", "world says"));
}

// Test kRegexpWordBoundary
TEST_F(CompilerPostVisitTest_321, WordBoundary_321) {
  EXPECT_TRUE(PartialMatches("\\bhello\\b", "say hello world"));
  EXPECT_FALSE(PartialMatches("\\bhello\\b", "sayhelloworld"));
}

// Test kRegexpNoWordBoundary
TEST_F(CompilerPostVisitTest_321, NoWordBoundary_321) {
  EXPECT_TRUE(PartialMatches("\\Bello", "hello"));
  EXPECT_FALSE(PartialMatches("\\Bello", "ello"));
}

// Test complex pattern combining multiple operations
TEST_F(CompilerPostVisitTest_321, ComplexPattern_321) {
  EXPECT_TRUE(CompileSucceeds("(a|b)*c+[d-f]?"));
  EXPECT_TRUE(Matches("(a|b)*c+[d-f]?", "c"));
  EXPECT_TRUE(Matches("(a|b)*c+[d-f]?", "abaccd"));
  EXPECT_TRUE(Matches("(a|b)*c+[d-f]?", "bbbccc"));
  EXPECT_TRUE(Matches("(a|b)*c+[d-f]?", "ccce"));
  EXPECT_FALSE(Matches("(a|b)*c+[d-f]?", ""));
  EXPECT_FALSE(Matches("(a|b)*c+[d-f]?", "ab"));
}

// Test ANCHOR_BOTH through FullMatch (which internally sets anchor)
TEST_F(CompilerPostVisitTest_321, AnchorBoth_321) {
  EXPECT_TRUE(RE2::FullMatch("abc", "abc"));
  EXPECT_FALSE(RE2::FullMatch("abcd", "abc"));
  EXPECT_FALSE(RE2::FullMatch("xabc", "abc"));
}

// Test dot without newline
TEST_F(CompilerPostVisitTest_321, DotNoNewline_321) {
  EXPECT_TRUE(Matches(".", "a"));
  EXPECT_FALSE(Matches(".", "\n"));
}

// Test digit character class
TEST_F(CompilerPostVisitTest_321, DigitClass_321) {
  EXPECT_TRUE(Matches("\\d+", "12345"));
  EXPECT_FALSE(Matches("\\d+", "abcde"));
  EXPECT_FALSE(Matches("\\d+", ""));
}

// Test whitespace character class
TEST_F(CompilerPostVisitTest_321, WhitespaceClass_321) {
  EXPECT_TRUE(Matches("\\s+", "   "));
  EXPECT_FALSE(Matches("\\s+", "abc"));
}

// Test word character class
TEST_F(CompilerPostVisitTest_321, WordCharClass_321) {
  EXPECT_TRUE(Matches("\\w+", "hello_123"));
  EXPECT_FALSE(Matches("\\w+", "!@#"));
}

// Test repeated group
TEST_F(CompilerPostVisitTest_321, RepeatedGroup_321) {
  EXPECT_TRUE(Matches("(ab)+", "ababab"));
  EXPECT_FALSE(Matches("(ab)+", ""));
  EXPECT_FALSE(Matches("(ab)+", "a"));
}

// Test empty alternation (edge case)
TEST_F(CompilerPostVisitTest_321, AlternateWithEmpty_321) {
  EXPECT_TRUE(CompileSucceeds("(a|)"));
  EXPECT_TRUE(Matches("(a|)", "a"));
  EXPECT_TRUE(Matches("(a|)", ""));
}

// Test very long literal string
TEST_F(CompilerPostVisitTest_321, LongLiteralString_321) {
  std::string pattern(100, 'x');
  std::string text(100, 'x');
  EXPECT_TRUE(CompileSucceeds(pattern));
  EXPECT_TRUE(Matches(pattern, text));
  EXPECT_FALSE(Matches(pattern, text + "x"));
  EXPECT_FALSE(Matches(pattern, text.substr(0, 99)));
}

// Test character class with multiple ranges
TEST_F(CompilerPostVisitTest_321, CharClassMultipleRanges_321) {
  EXPECT_TRUE(CompileSucceeds("[a-zA-Z0-9]"));
  EXPECT_TRUE(Matches("[a-zA-Z0-9]", "a"));
  EXPECT_TRUE(Matches("[a-zA-Z0-9]", "Z"));
  EXPECT_TRUE(Matches("[a-zA-Z0-9]", "5"));
  EXPECT_FALSE(Matches("[a-zA-Z0-9]", "!"));
}

// Test compilation with max repetition
TEST_F(CompilerPostVisitTest_321, BoundedRepetition_321) {
  EXPECT_TRUE(CompileSucceeds("a{3,5}"));
  EXPECT_FALSE(Matches("a{3,5}", "aa"));
  EXPECT_TRUE(Matches("a{3,5}", "aaa"));
  EXPECT_TRUE(Matches("a{3,5}", "aaaa"));
  EXPECT_TRUE(Matches("a{3,5}", "aaaaa"));
  EXPECT_FALSE(Matches("a{3,5}", "aaaaaa"));
}

// Test HaveMatch via set operations (multiple patterns)
TEST_F(CompilerPostVisitTest_321, HaveMatchViaSet_321) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  ASSERT_GE(s.Add("foo", nullptr), 0);
  ASSERT_GE(s.Add("bar", nullptr), 0);
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
  EXPECT_TRUE(s.Match("foobar", &matches));
  EXPECT_GE(matches.size(), 1u);

  matches.clear();
  EXPECT_FALSE(s.Match("baz", &matches));
}

// Test non-capturing group
TEST_F(CompilerPostVisitTest_321, NonCapturingGroup_321) {
  EXPECT_TRUE(CompileSucceeds("(?:abc)+"));
  EXPECT_TRUE(Matches("(?:abc)+", "abc"));
  EXPECT_TRUE(Matches("(?:abc)+", "abcabc"));
  EXPECT_FALSE(Matches("(?:abc)+", ""));
}

// Test unicode char in literal
TEST_F(CompilerPostVisitTest_321, UnicodeLiteral_321) {
  EXPECT_TRUE(CompileSucceeds("é"));
  EXPECT_TRUE(Matches("é", "é"));
  EXPECT_FALSE(Matches("é", "e"));
}

}  // namespace re2
