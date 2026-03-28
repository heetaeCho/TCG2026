#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "absl/strings/string_view.h"

namespace re2 {

// Test EmptyFlags which is the core dependency of the Satisfy function in onepass.cc

class EmptyFlagsTest_565 : public ::testing::Test {
 protected:
};

// Test kEmptyBeginText at the beginning of text
TEST_F(EmptyFlagsTest_565, BeginTextAtStart_565) {
  absl::string_view context("hello");
  const char* p = context.data();
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_TRUE(flags & kEmptyBeginText);
}

// Test kEmptyBeginText not set in the middle
TEST_F(EmptyFlagsTest_565, BeginTextNotInMiddle_565) {
  absl::string_view context("hello");
  const char* p = context.data() + 2;
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_FALSE(flags & kEmptyBeginText);
}

// Test kEmptyEndText at the end of text
TEST_F(EmptyFlagsTest_565, EndTextAtEnd_565) {
  absl::string_view context("hello");
  const char* p = context.data() + context.size();
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_TRUE(flags & kEmptyEndText);
}

// Test kEmptyEndText not set at beginning
TEST_F(EmptyFlagsTest_565, EndTextNotAtStart_565) {
  absl::string_view context("hello");
  const char* p = context.data();
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_FALSE(flags & kEmptyEndText);
}

// Test kEmptyBeginLine at the start of text
TEST_F(EmptyFlagsTest_565, BeginLineAtStart_565) {
  absl::string_view context("hello");
  const char* p = context.data();
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_TRUE(flags & kEmptyBeginLine);
}

// Test kEmptyBeginLine after a newline
TEST_F(EmptyFlagsTest_565, BeginLineAfterNewline_565) {
  absl::string_view context("he\nlo");
  const char* p = context.data() + 3;  // right after '\n'
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_TRUE(flags & kEmptyBeginLine);
}

// Test kEmptyBeginLine not set in the middle of a line
TEST_F(EmptyFlagsTest_565, BeginLineNotInMiddle_565) {
  absl::string_view context("hello");
  const char* p = context.data() + 2;
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_FALSE(flags & kEmptyBeginLine);
}

// Test kEmptyEndLine at end of text
TEST_F(EmptyFlagsTest_565, EndLineAtEnd_565) {
  absl::string_view context("hello");
  const char* p = context.data() + context.size();
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_TRUE(flags & kEmptyEndLine);
}

// Test kEmptyEndLine before a newline
TEST_F(EmptyFlagsTest_565, EndLineBeforeNewline_565) {
  absl::string_view context("he\nlo");
  const char* p = context.data() + 2;  // right before '\n'
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_TRUE(flags & kEmptyEndLine);
}

// Test kEmptyEndLine not set in the middle of a line
TEST_F(EmptyFlagsTest_565, EndLineNotInMiddle_565) {
  absl::string_view context("hello");
  const char* p = context.data() + 2;
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_FALSE(flags & kEmptyEndLine);
}

// Test kEmptyWordBoundary at transition from non-word to word
TEST_F(EmptyFlagsTest_565, WordBoundaryAtStart_565) {
  absl::string_view context("hello");
  const char* p = context.data();  // before 'h' (word char), nothing before
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_TRUE(flags & kEmptyWordBoundary);
}

// Test kEmptyWordBoundary at transition from word to non-word
TEST_F(EmptyFlagsTest_565, WordBoundaryAtEnd_565) {
  absl::string_view context("hello");
  const char* p = context.data() + context.size();  // after 'o' (word char)
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_TRUE(flags & kEmptyWordBoundary);
}

// Test kEmptyNonWordBoundary between two word characters
TEST_F(EmptyFlagsTest_565, NonWordBoundaryBetweenWordChars_565) {
  absl::string_view context("hello");
  const char* p = context.data() + 2;  // between 'e' and 'l'
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_TRUE(flags & kEmptyNonWordBoundary);
  EXPECT_FALSE(flags & kEmptyWordBoundary);
}

// Test kEmptyWordBoundary at word-to-space boundary
TEST_F(EmptyFlagsTest_565, WordBoundaryAtSpace_565) {
  absl::string_view context("hi there");
  const char* p = context.data() + 2;  // between 'i' and ' '
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_TRUE(flags & kEmptyWordBoundary);
}

// Test empty context
TEST_F(EmptyFlagsTest_565, EmptyContext_565) {
  absl::string_view context("");
  const char* p = context.data();
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_TRUE(flags & kEmptyBeginText);
  EXPECT_TRUE(flags & kEmptyEndText);
  EXPECT_TRUE(flags & kEmptyBeginLine);
  EXPECT_TRUE(flags & kEmptyEndLine);
}

// Test kEmptyNonWordBoundary between two non-word characters
TEST_F(EmptyFlagsTest_565, NonWordBoundaryBetweenNonWordChars_565) {
  absl::string_view context("  ");
  const char* p = context.data() + 1;  // between ' ' and ' '
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_TRUE(flags & kEmptyNonWordBoundary);
  EXPECT_FALSE(flags & kEmptyWordBoundary);
}

// Test IsWordChar
TEST_F(EmptyFlagsTest_565, IsWordCharLetters_565) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

TEST_F(EmptyFlagsTest_565, IsWordCharNonWord_565) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
}

// Tests for OnePass search via RE2 interface
class OnePassSearchTest_565 : public ::testing::Test {
 protected:
};

// Test IsOnePass through a simple pattern
TEST_F(OnePassSearchTest_565, SimplePatternIsOnePass_565) {
  // Simple literal patterns should be onepass
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
}

// Test SearchOnePass via RE2 with a simple match
TEST_F(OnePassSearchTest_565, SimpleMatch_565) {
  RE2 re("h(e)(l)lo");
  ASSERT_TRUE(re.ok());
  std::string s1, s2;
  EXPECT_TRUE(RE2::FullMatch("hello", re, &s1, &s2));
  EXPECT_EQ("e", s1);
  EXPECT_EQ("l", s2);
}

// Test no match
TEST_F(OnePassSearchTest_565, NoMatch_565) {
  RE2 re("^hello$");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test anchored match
TEST_F(OnePassSearchTest_565, AnchoredMatch_565) {
  RE2 re("^abc");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("abcdef", re));
  EXPECT_FALSE(RE2::PartialMatch("xabc", re));
}

// Test partial match
TEST_F(OnePassSearchTest_565, PartialMatch_565) {
  RE2 re("world");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello world", re));
}

// Test with empty string
TEST_F(OnePassSearchTest_565, EmptyPattern_565) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
}

// Test with empty text and non-empty pattern
TEST_F(OnePassSearchTest_565, EmptyTextNonEmptyPattern_565) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("", re));
}

// Test word boundary in pattern
TEST_F(OnePassSearchTest_565, WordBoundaryPattern_565) {
  RE2 re("\\bhello\\b");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("say hello world", re));
  EXPECT_FALSE(RE2::PartialMatch("sayhelloworld", re));
}

// Test begin/end of line
TEST_F(OnePassSearchTest_565, BeginEndLine_565) {
  RE2 re("^hello$");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("hello\n", re));
}

// Test capturing groups
TEST_F(OnePassSearchTest_565, CapturingGroups_565) {
  RE2 re("(\\w+)@(\\w+)\\.(\\w+)");
  ASSERT_TRUE(re.ok());
  std::string user, domain, tld;
  EXPECT_TRUE(RE2::FullMatch("user@example.com", re, &user, &domain, &tld));
  EXPECT_EQ("user", user);
  EXPECT_EQ("example", domain);
  EXPECT_EQ("com", tld);
}

// Test character class
TEST_F(OnePassSearchTest_565, CharacterClass_565) {
  RE2 re("[a-z]+");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("HELLO", re));
}

// Test alternation - may or may not be onepass but should still work
TEST_F(OnePassSearchTest_565, Alternation_565) {
  RE2 re("cat|dog");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("cat", re));
  EXPECT_TRUE(RE2::FullMatch("dog", re));
  EXPECT_FALSE(RE2::FullMatch("bird", re));
}

// Test context around newlines for line anchors
TEST_F(OnePassSearchTest_565, NewlineContext_565) {
  absl::string_view context("line1\nline2\nline3");
  // EmptyFlags at position right after first \n
  const char* p = context.data() + 6;  // start of "line2"
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_TRUE(flags & kEmptyBeginLine);
  EXPECT_FALSE(flags & kEmptyBeginText);
}

// Test that only newline triggers begin/end line, not other whitespace
TEST_F(OnePassSearchTest_565, OnlyNewlineTriggers_565) {
  absl::string_view context("a\tb");
  const char* p = context.data() + 1;  // at '\t'
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_FALSE(flags & kEmptyBeginLine);
  EXPECT_FALSE(flags & kEmptyEndLine);
}

// Test multiple newlines
TEST_F(OnePassSearchTest_565, MultipleNewlines_565) {
  absl::string_view context("\n\n");
  // At position 1: after first \n, before second \n
  const char* p = context.data() + 1;
  uint32_t flags = Prog::EmptyFlags(context, p);
  EXPECT_TRUE(flags & kEmptyBeginLine);
  EXPECT_TRUE(flags & kEmptyEndLine);
}

// Test kEmptyAllFlags value
TEST_F(EmptyFlagsTest_565, AllFlagsValue_565) {
  EXPECT_EQ(63u, static_cast<uint32_t>(kEmptyAllFlags));
}

// Test individual EmptyOp values
TEST_F(EmptyFlagsTest_565, IndividualOpValues_565) {
  EXPECT_EQ(1u, static_cast<uint32_t>(kEmptyBeginLine));
  EXPECT_EQ(2u, static_cast<uint32_t>(kEmptyEndLine));
  EXPECT_EQ(4u, static_cast<uint32_t>(kEmptyBeginText));
  EXPECT_EQ(8u, static_cast<uint32_t>(kEmptyEndText));
  EXPECT_EQ(16u, static_cast<uint32_t>(kEmptyWordBoundary));
  EXPECT_EQ(32u, static_cast<uint32_t>(kEmptyNonWordBoundary));
}

}  // namespace re2
