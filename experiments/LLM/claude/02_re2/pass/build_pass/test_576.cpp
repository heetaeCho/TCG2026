#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"

namespace re2 {

class NFATest_576 : public ::testing::Test {
 protected:
  Prog* CompileRegexp(const char* pattern) {
    RegexpStatus status;
    regexp_ = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (regexp_ == nullptr) return nullptr;
    prog_ = regexp_->CompileToProg(0);
    return prog_;
  }

  void TearDown() override {
    delete prog_;
    if (regexp_) regexp_->Decref();
  }

  Regexp* regexp_ = nullptr;
  Prog* prog_ = nullptr;
};

// Test simple literal match using NFA
TEST_F(NFATest_576, SimpleLiteralMatch_576) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

// Test no match
TEST_F(NFATest_576, NoMatch_576) {
  Prog* prog = CompileRegexp("xyz");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test unanchored search
TEST_F(NFATest_576, UnanchoredSearch_576) {
  Prog* prog = CompileRegexp("world");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "world");
}

// Test anchored search fails when pattern not at start
TEST_F(NFATest_576, AnchoredSearchFailsWhenNotAtStart_576) {
  Prog* prog = CompileRegexp("world");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test empty pattern
TEST_F(NFATest_576, EmptyPattern_576) {
  Prog* prog = CompileRegexp("");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0);
}

// Test empty text with empty pattern
TEST_F(NFATest_576, EmptyTextEmptyPattern_576) {
  Prog* prog = CompileRegexp("");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

// Test empty text with non-empty pattern
TEST_F(NFATest_576, EmptyTextNonEmptyPattern_576) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test with submatch captures
TEST_F(NFATest_576, SubmatchCaptures_576) {
  Prog* prog = CompileRegexp("(hel)(lo)");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match[3];
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, match, 3);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "hello");
  EXPECT_EQ(match[1], "hel");
  EXPECT_EQ(match[2], "lo");
}

// Test longest match mode
TEST_F(NFATest_576, LongestMatch_576) {
  Prog* prog = CompileRegexp("a+");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("aaaa");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kLongestMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "aaaa");
}

// Test first match mode
TEST_F(NFATest_576, FirstMatch_576) {
  Prog* prog = CompileRegexp("a+");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("aaaa");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  // First match should still match something
  EXPECT_FALSE(match.empty());
}

// Test with zero nsubmatch (just checking if match exists)
TEST_F(NFATest_576, ZeroSubmatch_576) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, nullptr, 0);
  EXPECT_TRUE(found);
}

// Test character class
TEST_F(NFATest_576, CharacterClass_576) {
  Prog* prog = CompileRegexp("[a-z]+");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello123");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kLongestMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

// Test alternation
TEST_F(NFATest_576, Alternation_576) {
  Prog* prog = CompileRegexp("cat|dog");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("dog");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "dog");
}

// Test repetition with optional
TEST_F(NFATest_576, OptionalMatch_576) {
  Prog* prog = CompileRegexp("ab?c");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("ac");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "ac");
}

// Test dot matches
TEST_F(NFATest_576, DotMatch_576) {
  Prog* prog = CompileRegexp("a.c");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("abc");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

// Test with context different from text
TEST_F(NFATest_576, ContextDifferentFromText_576) {
  Prog* prog = CompileRegexp("world");
  ASSERT_NE(prog, nullptr);

  absl::string_view context("hello world");
  absl::string_view text = context.substr(6);  // "world"
  absl::string_view match;
  bool found = prog->SearchNFA(text, context, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "world");
}

// Test star quantifier
TEST_F(NFATest_576, StarQuantifier_576) {
  Prog* prog = CompileRegexp("a*");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("aaa");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kLongestMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "aaa");
}

// Test star quantifier with no match characters (should match empty)
TEST_F(NFATest_576, StarQuantifierEmptyMatch_576) {
  Prog* prog = CompileRegexp("a*");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("bbb");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0);
}

// Test nested groups
TEST_F(NFATest_576, NestedGroups_576) {
  Prog* prog = CompileRegexp("((a)(b))");
  ASSERT_NE(prog, nullptr);

  absl::string_view text("ab");
  absl::string_view match[4];
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, match, 4);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "ab");
  EXPECT_EQ(match[1], "ab");
  EXPECT_EQ(match[2], "a");
  EXPECT_EQ(match[3], "b");
}

}  // namespace re2
