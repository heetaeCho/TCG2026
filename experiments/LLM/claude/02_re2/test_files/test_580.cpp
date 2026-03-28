#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "absl/strings/string_view.h"

namespace re2 {

// Helper to compile a pattern into a Prog for testing SearchBitState
class BitStateTest_580 : public ::testing::Test {
 protected:
  // Compile a regex pattern into a Prog. Caller takes ownership via unique_ptr.
  std::unique_ptr<Prog> CompileProg(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re == nullptr) return nullptr;
    std::unique_ptr<Prog> prog(re->CompileToProg(0));
    re->Decref();
    return prog;
  }
};

// Test basic matching of a simple literal pattern
TEST_F(BitStateTest_580, SimpleLiteralMatch_580) {
  auto prog = CompileProg("hello");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

// Test that a non-matching pattern returns false
TEST_F(BitStateTest_580, NoMatch_580) {
  auto prog = CompileProg("xyz");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test anchored match at the beginning
TEST_F(BitStateTest_580, AnchoredMatchAtBeginning_580) {
  auto prog = CompileProg("hello");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

// Test anchored match fails when pattern is not at beginning
TEST_F(BitStateTest_580, AnchoredMatchFails_580) {
  auto prog = CompileProg("world");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test empty text with empty pattern
TEST_F(BitStateTest_580, EmptyTextEmptyPattern_580) {
  auto prog = CompileProg("");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "");
}

// Test empty text with non-empty pattern
TEST_F(BitStateTest_580, EmptyTextNonEmptyPattern_580) {
  auto prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test with submatch capture groups
TEST_F(BitStateTest_580, SubmatchCapture_580) {
  auto prog = CompileProg("(hel)(lo)");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("hello world");
  absl::string_view match[3];
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, match, 3);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "hello");
  EXPECT_EQ(match[1], "hel");
  EXPECT_EQ(match[2], "lo");
}

// Test with zero submatches (just check if match exists)
TEST_F(BitStateTest_580, ZeroSubmatches_580) {
  auto prog = CompileProg("hello");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("hello world");
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, nullptr, 0);
  EXPECT_TRUE(found);
}

// Test longest match mode
TEST_F(BitStateTest_580, LongestMatch_580) {
  auto prog = CompileProg("a+");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("aaa");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kLongestMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "aaa");
}

// Test first match mode with alternation
TEST_F(BitStateTest_580, FirstMatchWithAlternation_580) {
  auto prog = CompileProg("a|aa");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("aa");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  // First match should find something (exact result depends on implementation)
  EXPECT_FALSE(match.empty());
}

// Test matching with context different from text
TEST_F(BitStateTest_580, ContextDiffersFromText_580) {
  auto prog = CompileProg("llo");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  std::string full = "hello world";
  absl::string_view context(full);
  // Search within a substring of the context
  absl::string_view text(full.data() + 2, 5);  // "llo w"
  absl::string_view match;
  bool found = prog->SearchBitState(text, context, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "llo");
}

// Test pattern with start anchor (^)
TEST_F(BitStateTest_580, StartAnchorPattern_580) {
  auto prog = CompileProg("^hello");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

// Test pattern with start anchor that doesn't match
TEST_F(BitStateTest_580, StartAnchorPatternNoMatch_580) {
  auto prog = CompileProg("^world");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test pattern with end anchor ($)
TEST_F(BitStateTest_580, EndAnchorPattern_580) {
  auto prog = CompileProg("world$");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "world");
}

// Test with character class
TEST_F(BitStateTest_580, CharacterClass_580) {
  auto prog = CompileProg("[a-z]+");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("123abc456");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

// Test with repetition (star)
TEST_F(BitStateTest_580, StarRepetition_580) {
  auto prog = CompileProg("ab*c");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("abbbbc");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abbbbc");
}

// Test optional group
TEST_F(BitStateTest_580, OptionalGroup_580) {
  auto prog = CompileProg("colou?r");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text1("color");
  absl::string_view match1;
  bool found1 = prog->SearchBitState(text1, text1, Prog::kUnanchored,
                                      Prog::kFirstMatch, &match1, 1);
  EXPECT_TRUE(found1);
  EXPECT_EQ(match1, "color");

  absl::string_view text2("colour");
  absl::string_view match2;
  bool found2 = prog->SearchBitState(text2, text2, Prog::kUnanchored,
                                      Prog::kFirstMatch, &match2, 1);
  EXPECT_TRUE(found2);
  EXPECT_EQ(match2, "colour");
}

// Test single character text
TEST_F(BitStateTest_580, SingleCharText_580) {
  auto prog = CompileProg("a");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("a");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "a");
}

// Test single character text no match
TEST_F(BitStateTest_580, SingleCharTextNoMatch_580) {
  auto prog = CompileProg("b");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("a");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test dot matches any character
TEST_F(BitStateTest_580, DotMatchesAny_580) {
  auto prog = CompileProg("a.c");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("axc");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "axc");
}

// Test multiple capture groups
TEST_F(BitStateTest_580, MultipleCaptureGroups_580) {
  auto prog = CompileProg("(\\w+)@(\\w+)\\.(\\w+)");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("user@example.com");
  absl::string_view match[4];
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, match, 4);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "user@example.com");
  EXPECT_EQ(match[1], "user");
  EXPECT_EQ(match[2], "example");
  EXPECT_EQ(match[3], "com");
}

// Test leftmost match behavior
TEST_F(BitStateTest_580, LeftmostMatch_580) {
  auto prog = CompileProg("a");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("bba");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.data(), text.data() + 2);
  EXPECT_EQ(match, "a");
}

// Test with anchor_start and context not starting at text
TEST_F(BitStateTest_580, AnchorStartContextMismatch_580) {
  auto prog = CompileProg("^hello");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  std::string full = "XXhello";
  absl::string_view context(full);
  // text starts after the context beginning
  absl::string_view text(full.data() + 2, 5);  // "hello"
  absl::string_view match;
  // With anchor_start and context starting before text, should fail
  bool found = prog->SearchBitState(text, context, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test via RE2 interface for more realistic usage
TEST_F(BitStateTest_580, RE2SimpleMatch_580) {
  RE2 re("(\\d+)-(\\d+)");
  std::string s1, s2;
  EXPECT_TRUE(RE2::PartialMatch("abc 123-456 def", re, &s1, &s2));
  EXPECT_EQ(s1, "123");
  EXPECT_EQ(s2, "456");
}

// Test empty pattern matches anywhere
TEST_F(BitStateTest_580, EmptyPatternMatchesAnywhere_580) {
  auto prog = CompileProg("");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("hello");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0u);
}

// Test with nsubmatch=1 (only full match, no groups)
TEST_F(BitStateTest_580, OneSubmatchOnly_580) {
  auto prog = CompileProg("(a)(b)");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;

  absl::string_view text("ab");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "ab");
}

}  // namespace re2
