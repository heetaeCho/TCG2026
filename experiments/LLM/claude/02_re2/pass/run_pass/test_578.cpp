#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "absl/strings/string_view.h"

namespace re2 {

// Helper function to compile a regex pattern into a Prog
static Prog* CompileProg(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

class SearchNFATest_578 : public ::testing::Test {
 protected:
  void TearDown() override {
    delete prog_;
    prog_ = nullptr;
  }
  Prog* prog_ = nullptr;
};

// Test basic matching with a simple literal pattern
TEST_F(SearchNFATest_578, SimpleLiteralMatch_578) {
  prog_ = CompileProg("hello");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "hello");
}

// Test no match case
TEST_F(SearchNFATest_578, NoMatch_578) {
  prog_ = CompileProg("xyz");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(result);
}

// Test anchored match at start
TEST_F(SearchNFATest_578, AnchoredMatchAtStart_578) {
  prog_ = CompileProg("hello");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kAnchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "hello");
}

// Test anchored match fails when pattern not at start
TEST_F(SearchNFATest_578, AnchoredMatchFails_578) {
  prog_ = CompileProg("world");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kAnchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(result);
}

// Test full match - pattern matches entire text
TEST_F(SearchNFATest_578, FullMatchSuccess_578) {
  prog_ = CompileProg("hello");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("hello");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFullMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "hello");
}

// Test full match - pattern doesn't match entire text
TEST_F(SearchNFATest_578, FullMatchFailsPartial_578) {
  prog_ = CompileProg("hello");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFullMatch, &match, 1);
  EXPECT_FALSE(result);
}

// Test with empty text
TEST_F(SearchNFATest_578, EmptyTextNoMatch_578) {
  prog_ = CompileProg("hello");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(result);
}

// Test empty pattern matches empty text
TEST_F(SearchNFATest_578, EmptyPatternEmptyText_578) {
  prog_ = CompileProg("");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFullMatch, &match, 1);
  EXPECT_TRUE(result);
}

// Test with capturing groups
TEST_F(SearchNFATest_578, CapturingGroups_578) {
  prog_ = CompileProg("(hel)(lo)");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("hello world");
  absl::string_view match[3];
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFirstMatch, match, 3);
  EXPECT_TRUE(result);
  EXPECT_EQ(match[0], "hello");
  EXPECT_EQ(match[1], "hel");
  EXPECT_EQ(match[2], "lo");
}

// Test longest match
TEST_F(SearchNFATest_578, LongestMatch_578) {
  prog_ = CompileProg("a+");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("aaa");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kLongestMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "aaa");
}

// Test first match (should be leftmost)
TEST_F(SearchNFATest_578, FirstMatch_578) {
  prog_ = CompileProg("a+");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("baaab");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  // The match should start at the first 'a'
  EXPECT_EQ(match.data(), text.data() + 1);
}

// Test with nmatch = 0
TEST_F(SearchNFATest_578, NmatchZero_578) {
  prog_ = CompileProg("hello");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("hello world");
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFirstMatch, nullptr, 0);
  EXPECT_TRUE(result);
}

// Test with nmatch = 0 and no match
TEST_F(SearchNFATest_578, NmatchZeroNoMatch_578) {
  prog_ = CompileProg("xyz");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("hello world");
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFirstMatch, nullptr, 0);
  EXPECT_FALSE(result);
}

// Test full match with nmatch = 0 (should still work because SearchNFA
// creates a local match when kFullMatch and nmatch==0)
TEST_F(SearchNFATest_578, FullMatchNmatchZero_578) {
  prog_ = CompileProg("hello");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("hello");
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFullMatch, nullptr, 0);
  EXPECT_TRUE(result);
}

// Test full match with nmatch = 0 fails when text doesn't fully match
TEST_F(SearchNFATest_578, FullMatchNmatchZeroFails_578) {
  prog_ = CompileProg("hel");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("hello");
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFullMatch, nullptr, 0);
  EXPECT_FALSE(result);
}

// Test with a complex regex pattern
TEST_F(SearchNFATest_578, ComplexPattern_578) {
  prog_ = CompileProg("[a-z]+@[a-z]+\\.[a-z]+");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("send to user@example.com please");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "user@example.com");
}

// Test with alternation
TEST_F(SearchNFATest_578, Alternation_578) {
  prog_ = CompileProg("cat|dog");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("I have a dog");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "dog");
}

// Test with repetition
TEST_F(SearchNFATest_578, Repetition_578) {
  prog_ = CompileProg("ab{2,4}");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("xabbbby");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  // Should match abb, abbb, or abbbb depending on first match semantics
  EXPECT_GE(match.size(), 3u);  // at least "abb"
  EXPECT_LE(match.size(), 5u);  // at most "abbbb"
}

// Test dot matches any character
TEST_F(SearchNFATest_578, DotMatch_578) {
  prog_ = CompileProg("a.c");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("abc");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "abc");
}

// Test context different from text
TEST_F(SearchNFATest_578, DifferentContext_578) {
  prog_ = CompileProg("hello");
  ASSERT_NE(prog_, nullptr);

  std::string full = "say hello world";
  absl::string_view context(full);
  absl::string_view text(full.data() + 4, full.size() - 4);  // "hello world"
  absl::string_view match;
  bool result = prog_->SearchNFA(text, context, Prog::kUnanchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "hello");
}

// Test anchored full match with .* pattern
TEST_F(SearchNFATest_578, FullMatchDotStar_578) {
  prog_ = CompileProg(".*");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("anything goes here");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFullMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, text);
}

// Test optional group
TEST_F(SearchNFATest_578, OptionalGroup_578) {
  prog_ = CompileProg("colou?r");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text1("color");
  absl::string_view match1;
  EXPECT_TRUE(prog_->SearchNFA(text1, text1, Prog::kUnanchored,
                                Prog::kFirstMatch, &match1, 1));
  EXPECT_EQ(match1, "color");

  absl::string_view text2("colour");
  absl::string_view match2;
  EXPECT_TRUE(prog_->SearchNFA(text2, text2, Prog::kUnanchored,
                                Prog::kFirstMatch, &match2, 1));
  EXPECT_EQ(match2, "colour");
}

// Test word boundary behavior with anchored search on partial text
TEST_F(SearchNFATest_578, AnchoredNoMatchInMiddle_578) {
  prog_ = CompileProg("world");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kAnchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(result);
}

// Test single character match
TEST_F(SearchNFATest_578, SingleCharMatch_578) {
  prog_ = CompileProg("a");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("a");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFullMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "a");
}

// Test empty pattern matches any text (full match on empty gives empty)
TEST_F(SearchNFATest_578, EmptyPatternNonEmptyTextFullMatch_578) {
  prog_ = CompileProg("");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("hello");
  absl::string_view match;
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFullMatch, &match, 1);
  // Empty pattern cannot match full non-empty text
  EXPECT_FALSE(result);
}

// Test multiple submatches with nested groups
TEST_F(SearchNFATest_578, NestedCapturingGroups_578) {
  prog_ = CompileProg("((a)(b))");
  ASSERT_NE(prog_, nullptr);

  absl::string_view text("ab");
  absl::string_view match[4];
  bool result = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                  Prog::kFirstMatch, match, 4);
  EXPECT_TRUE(result);
  EXPECT_EQ(match[0], "ab");
  EXPECT_EQ(match[1], "ab");
  EXPECT_EQ(match[2], "a");
  EXPECT_EQ(match[3], "b");
}

}  // namespace re2
