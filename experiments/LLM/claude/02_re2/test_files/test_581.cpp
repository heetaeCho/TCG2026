#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "absl/strings/string_view.h"

namespace re2 {

// Helper function to compile a regex pattern into a Prog
static Prog* CompilePattern(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

class SearchBitStateTest_581 : public ::testing::Test {
 protected:
  void TearDown() override {
    delete prog_;
    prog_ = nullptr;
  }

  Prog* prog_ = nullptr;
};

// Test basic matching with a simple pattern
TEST_F(SearchBitStateTest_581, SimpleMatch_581) {
  prog_ = CompilePattern("hello");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("hello world");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "hello");
}

// Test no match case
TEST_F(SearchBitStateTest_581, NoMatch_581) {
  prog_ = CompilePattern("xyz");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("hello world");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(result);
}

// Test anchored match at the beginning
TEST_F(SearchBitStateTest_581, AnchoredMatchAtStart_581) {
  prog_ = CompilePattern("hello");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("hello world");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kAnchored,
                                       Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "hello");
}

// Test anchored match fails when pattern is not at start
TEST_F(SearchBitStateTest_581, AnchoredMatchFails_581) {
  prog_ = CompilePattern("world");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("hello world");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kAnchored,
                                       Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(result);
}

// Test full match success
TEST_F(SearchBitStateTest_581, FullMatchSuccess_581) {
  prog_ = CompilePattern("hello");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("hello");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFullMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "hello");
}

// Test full match fails when text has extra characters
TEST_F(SearchBitStateTest_581, FullMatchFailsExtraChars_581) {
  prog_ = CompilePattern("hello");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("hello world");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFullMatch, &match, 1);
  EXPECT_FALSE(result);
}

// Test full match with nmatch = 0 (should still work internally)
TEST_F(SearchBitStateTest_581, FullMatchWithZeroNmatch_581) {
  prog_ = CompilePattern("hello");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("hello");
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFullMatch, nullptr, 0);
  EXPECT_TRUE(result);
}

// Test empty text with empty pattern
TEST_F(SearchBitStateTest_581, EmptyTextEmptyPattern_581) {
  prog_ = CompilePattern("");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
}

// Test empty text with non-empty pattern
TEST_F(SearchBitStateTest_581, EmptyTextNonEmptyPattern_581) {
  prog_ = CompilePattern("hello");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(result);
}

// Test longest match
TEST_F(SearchBitStateTest_581, LongestMatch_581) {
  prog_ = CompilePattern("a+");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("aaa");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kLongestMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "aaa");
}

// Test first match (should return first/shortest match for greedy)
TEST_F(SearchBitStateTest_581, FirstMatch_581) {
  prog_ = CompilePattern("a+");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("aaa");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  // The match should be non-empty (at least "a")
  EXPECT_FALSE(match.empty());
}

// Test with capture groups
TEST_F(SearchBitStateTest_581, CaptureGroups_581) {
  prog_ = CompilePattern("(a+)(b+)");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("aaabb");
  absl::string_view match[3];
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, match, 3);
  EXPECT_TRUE(result);
  EXPECT_EQ(match[0], "aaabb");
  EXPECT_EQ(match[1], "aaa");
  EXPECT_EQ(match[2], "bb");
}

// Test with context different from text
TEST_F(SearchBitStateTest_581, DifferentContext_581) {
  prog_ = CompilePattern("world");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view context("hello world");
  absl::string_view text = context.substr(6, 5);  // "world"
  absl::string_view match;
  bool result = prog_->SearchBitState(text, context, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "world");
}

// Test full match with entire pattern matching entire text
TEST_F(SearchBitStateTest_581, FullMatchExact_581) {
  prog_ = CompilePattern(".*");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("anything goes here");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFullMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, text);
}

// Test with alternation pattern
TEST_F(SearchBitStateTest_581, Alternation_581) {
  prog_ = CompilePattern("cat|dog");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("I have a dog");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "dog");
}

// Test unanchored search finds match in the middle
TEST_F(SearchBitStateTest_581, UnanchoredMiddleMatch_581) {
  prog_ = CompilePattern("middle");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("start middle end");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "middle");
}

// Test with nmatch = 0 and non-null match pointer
TEST_F(SearchBitStateTest_581, ZeroNmatch_581) {
  prog_ = CompilePattern("hello");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("hello");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 0);
  EXPECT_TRUE(result);
}

// Test with character class pattern
TEST_F(SearchBitStateTest_581, CharacterClass_581) {
  prog_ = CompilePattern("[0-9]+");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("abc123def");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "123");
}

// Test full match fails for partial pattern match
TEST_F(SearchBitStateTest_581, FullMatchPartialPatternFails_581) {
  prog_ = CompilePattern("[a-z]+");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("abc123");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFullMatch, &match, 1);
  EXPECT_FALSE(result);
}

// Test with dot-star pattern
TEST_F(SearchBitStateTest_581, DotStar_581) {
  prog_ = CompilePattern("a.*b");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("aXXXb");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "aXXXb");
}

// Test single character match
TEST_F(SearchBitStateTest_581, SingleCharMatch_581) {
  prog_ = CompilePattern(".");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("x");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match.size(), 1);
}

// Test repetition pattern with longest match
TEST_F(SearchBitStateTest_581, RepetitionLongestMatch_581) {
  prog_ = CompilePattern("a*");
  ASSERT_NE(prog_, nullptr);
  if (!prog_->CanBitState()) return;

  absl::string_view text("aaaa");
  absl::string_view match;
  bool result = prog_->SearchBitState(text, text, Prog::kAnchored,
                                       Prog::kLongestMatch, &match, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(match, "aaaa");
}

}  // namespace re2
