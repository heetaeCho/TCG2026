#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/sparse_set.h"
#include "absl/strings/string_view.h"

namespace re2 {

// Helper to compile a Regexp into a Prog for testing
class SearchDFATest_454 : public ::testing::Test {
 protected:
  Prog* CompileRegexp(const std::string& pattern, Regexp::ParseFlags flags = Regexp::LikePerl) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, flags, &status);
    if (re == nullptr) return nullptr;
    Prog* prog = re->CompileToProg(0);
    re->Decref();
    return prog;
  }
};

// Test basic match with a simple pattern
TEST_F(SearchDFATest_454, SimpleMatch_454) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("hello world");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  EXPECT_EQ(match, "hello");
  
  delete prog;
}

// Test no match
TEST_F(SearchDFATest_454, NoMatch_454) {
  Prog* prog = CompileRegexp("xyz");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("hello world");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_FALSE(matched);
  
  delete prog;
}

// Test anchored match at start
TEST_F(SearchDFATest_454, AnchoredMatchAtStart_454) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("hello world");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  EXPECT_EQ(match, "hello");
  
  delete prog;
}

// Test anchored match fails when pattern not at start
TEST_F(SearchDFATest_454, AnchoredNoMatch_454) {
  Prog* prog = CompileRegexp("world");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("hello world");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_FALSE(matched);
  
  delete prog;
}

// Test empty text
TEST_F(SearchDFATest_454, EmptyText_454) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_FALSE(matched);
  
  delete prog;
}

// Test empty pattern matches empty text
TEST_F(SearchDFATest_454, EmptyPatternEmptyText_454) {
  Prog* prog = CompileRegexp("");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  
  delete prog;
}

// Test empty pattern matches non-empty text
TEST_F(SearchDFATest_454, EmptyPatternNonEmptyText_454) {
  Prog* prog = CompileRegexp("");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("hello");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  
  delete prog;
}

// Test full match with kFullMatch
TEST_F(SearchDFATest_454, FullMatchSuccess_454) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("hello");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kFullMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  EXPECT_EQ(match, "hello");
  
  delete prog;
}

// Test full match fails when text is longer
TEST_F(SearchDFATest_454, FullMatchFailure_454) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("hello world");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kFullMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_FALSE(matched);
  
  delete prog;
}

// Test longest match
TEST_F(SearchDFATest_454, LongestMatch_454) {
  Prog* prog = CompileRegexp("a+");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("aaaa");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kAnchored, Prog::kLongestMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  EXPECT_EQ(match, "aaaa");
  
  delete prog;
}

// Test with match0 == nullptr (just checking if it matches)
TEST_F(SearchDFATest_454, NullMatch0_454) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("hello world");
  bool matched = prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, nullptr, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  
  delete prog;
}

// Test with context different from text
TEST_F(SearchDFATest_454, DifferentContext_454) {
  Prog* prog = CompileRegexp("world");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  std::string full_text = "hello world";
  absl::string_view context(full_text);
  absl::string_view text(full_text.data() + 6, 5);  // "world"
  absl::string_view match;
  bool matched = prog->SearchDFA(text, context, Prog::kUnanchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  EXPECT_EQ(match, "world");
  
  delete prog;
}

// Test with null context - should default to text
TEST_F(SearchDFATest_454, NullContext_454) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("hello");
  absl::string_view context;  // null data
  absl::string_view match;
  bool matched = prog->SearchDFA(text, context, Prog::kUnanchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  
  delete prog;
}

// Test with dot-star pattern
TEST_F(SearchDFATest_454, DotStarPattern_454) {
  Prog* prog = CompileRegexp(".*");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("anything goes here");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kAnchored, Prog::kLongestMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  EXPECT_EQ(match, "anything goes here");
  
  delete prog;
}

// Test character class pattern
TEST_F(SearchDFATest_454, CharacterClass_454) {
  Prog* prog = CompileRegexp("[a-z]+");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("123abc456");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  
  delete prog;
}

// Test alternation
TEST_F(SearchDFATest_454, Alternation_454) {
  Prog* prog = CompileRegexp("cat|dog");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("I have a dog");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  
  delete prog;
}

// Test with anchor_start set in the compiled regexp (using ^)
TEST_F(SearchDFATest_454, AnchorStartPattern_454) {
  Prog* prog = CompileRegexp("^hello");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("hello world");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  
  delete prog;
}

// Test with anchor_end set in the compiled regexp (using $)
TEST_F(SearchDFATest_454, AnchorEndPattern_454) {
  Prog* prog = CompileRegexp("world$");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("hello world");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kLongestMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  
  delete prog;
}

// Test repeated pattern
TEST_F(SearchDFATest_454, RepeatedPattern_454) {
  Prog* prog = CompileRegexp("ab{2,4}");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("abbb");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  
  delete prog;
}

// Test single character match
TEST_F(SearchDFATest_454, SingleCharMatch_454) {
  Prog* prog = CompileRegexp("a");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("a");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  EXPECT_EQ(match, "a");
  
  delete prog;
}

// Test BuildEntireDFA basic functionality
TEST_F(SearchDFATest_454, BuildEntireDFA_454) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  
  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);
  
  delete prog;
}

// Test PossibleMatchRange
TEST_F(SearchDFATest_454, PossibleMatchRange_454) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  
  std::string min_str, max_str;
  bool ok = prog->PossibleMatchRange(&min_str, &max_str, 10);
  
  EXPECT_TRUE(ok);
  EXPECT_LE(min_str, "abc");
  EXPECT_GE(max_str, "abc");
  
  delete prog;
}

// Test context subset where text starts after context
TEST_F(SearchDFATest_454, ContextSubsetText_454) {
  Prog* prog = CompileRegexp("^hello");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  std::string full = "hello world";
  absl::string_view context(full);
  // text is a substring starting at offset 6 ("world")
  absl::string_view text(full.data() + 6, 5);
  absl::string_view match;
  
  // With anchor_start pattern and context starting before text,
  // the caret check should cause a mismatch
  bool matched = prog->SearchDFA(text, context, Prog::kUnanchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  // "^hello" shouldn't match "world" even unanchored
  EXPECT_FALSE(matched);
  
  delete prog;
}

// Test with a large text
TEST_F(SearchDFATest_454, LargeText_454) {
  Prog* prog = CompileRegexp("needle");
  ASSERT_NE(prog, nullptr);
  
  std::string haystack(10000, 'a');
  haystack += "needle";
  haystack += std::string(10000, 'b');
  
  bool failed = false;
  absl::string_view text(haystack);
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  
  delete prog;
}

// Test FullMatch with regex that matches exactly
TEST_F(SearchDFATest_454, FullMatchExact_454) {
  Prog* prog = CompileRegexp("[0-9]+");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("12345");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kFullMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_TRUE(matched);
  EXPECT_EQ(match, "12345");
  
  delete prog;
}

// Test FullMatch with regex that doesn't match entire string
TEST_F(SearchDFATest_454, FullMatchPartial_454) {
  Prog* prog = CompileRegexp("[0-9]+");
  ASSERT_NE(prog, nullptr);
  
  bool failed = false;
  absl::string_view text("123abc");
  absl::string_view match;
  bool matched = prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kFullMatch, &match, &failed, nullptr);
  
  EXPECT_FALSE(failed);
  EXPECT_FALSE(matched);
  
  delete prog;
}

// Test that the failed flag can be set when DFA runs out of memory
TEST_F(SearchDFATest_454, DFABailout_454) {
  // Use a complex pattern with minimal memory to potentially trigger failure
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  
  // Use a pattern that may cause DFA to bail
  Prog* prog = CompileRegexp("(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)*");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(256);  // Very small memory budget
  
  bool failed = false;
  std::string large_text(1000, 'a');
  absl::string_view text(large_text);
  absl::string_view match;
  // This may or may not fail depending on DFA internals - just verify no crash
  prog->SearchDFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, &failed, nullptr);
  
  // We just verify it doesn't crash; failed may or may not be set
  
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
  delete prog;
}

}  // namespace re2
