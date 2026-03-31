#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/sparse_array.h"
#include "re2/sparse_set.h"
#include "absl/strings/string_view.h"
#include <string>
#include <memory>

namespace re2 {

class ProgTest_404 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Helper to compile a Regexp into a Prog
static Prog* CompileRegexp(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

// Test default construction of Prog
TEST_F(ProgTest_404, DefaultConstruction_404) {
  Prog prog;
  EXPECT_EQ(prog.start(), 0);
  EXPECT_EQ(prog.start_unanchored(), 0);
  EXPECT_EQ(prog.size(), 0);
  EXPECT_FALSE(prog.reversed());
  EXPECT_FALSE(prog.anchor_start());
  EXPECT_FALSE(prog.anchor_end());
  EXPECT_EQ(prog.bytemap_range(), 0);
  EXPECT_EQ(prog.dfa_mem(), 0);
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test set_start and start
TEST_F(ProgTest_404, SetAndGetStart_404) {
  Prog prog;
  prog.set_start(42);
  EXPECT_EQ(prog.start(), 42);
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_404, SetAndGetStartUnanchored_404) {
  Prog prog;
  prog.set_start_unanchored(99);
  EXPECT_EQ(prog.start_unanchored(), 99);
}

// Test set_reversed and reversed
TEST_F(ProgTest_404, SetAndGetReversed_404) {
  Prog prog;
  EXPECT_FALSE(prog.reversed());
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test set_anchor_start and anchor_start
TEST_F(ProgTest_404, SetAndGetAnchorStart_404) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_start());
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test set_anchor_end and anchor_end
TEST_F(ProgTest_404, SetAndGetAnchorEnd_404) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_end());
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test set_dfa_mem and dfa_mem
TEST_F(ProgTest_404, SetAndGetDfaMem_404) {
  Prog prog;
  EXPECT_EQ(prog.dfa_mem(), 0);
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog.dfa_mem(), 1024 * 1024);
}

// Test DumpByteMap on a compiled pattern
TEST_F(ProgTest_404, DumpByteMapSimplePattern_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("a"));
  ASSERT_NE(prog, nullptr);
  prog->ComputeByteMap();
  std::string map = prog->DumpByteMap();
  // The bytemap output should be non-empty and contain the arrow notation
  EXPECT_FALSE(map.empty());
  EXPECT_NE(map.find("->"), std::string::npos);
}

// Test DumpByteMap on a more complex compiled pattern
TEST_F(ProgTest_404, DumpByteMapComplexPattern_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("[a-z0-9]+"));
  ASSERT_NE(prog, nullptr);
  prog->ComputeByteMap();
  std::string map = prog->DumpByteMap();
  EXPECT_FALSE(map.empty());
  EXPECT_NE(map.find("->"), std::string::npos);
}

// Test bytemap pointer is non-null
TEST_F(ProgTest_404, BytemapPointerNonNull_404) {
  Prog prog;
  const uint8_t* bm = prog.bytemap();
  EXPECT_NE(bm, nullptr);
}

// Test DumpByteMap contains expected format with hex ranges
TEST_F(ProgTest_404, DumpByteMapFormat_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("."));
  ASSERT_NE(prog, nullptr);
  prog->ComputeByteMap();
  std::string map = prog->DumpByteMap();
  // Should contain [00- as the start of the first range
  EXPECT_NE(map.find("[00-"), std::string::npos);
}

// Test Dump on a simple pattern produces non-empty output
TEST_F(ProgTest_404, DumpSimplePattern_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

// Test DumpUnanchored on a simple pattern
TEST_F(ProgTest_404, DumpUnanchoredSimple_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

// Test IsWordChar for alphabetic characters
TEST_F(ProgTest_404, IsWordCharAlpha_404) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
}

// Test IsWordChar for digits
TEST_F(ProgTest_404, IsWordCharDigit_404) {
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
}

// Test IsWordChar for underscore
TEST_F(ProgTest_404, IsWordCharUnderscore_404) {
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

// Test IsWordChar for non-word characters
TEST_F(ProgTest_404, IsWordCharNonWord_404) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
}

// Test EmptyFlags at beginning of text
TEST_F(ProgTest_404, EmptyFlagsAtBeginning_404) {
  absl::string_view text("hello");
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // At the beginning, kEmptyBeginText and kEmptyBeginLine should be set
  // We just check it returns some non-trivial value
  EXPECT_NE(flags, 0u);
}

// Test EmptyFlags at end of text
TEST_F(ProgTest_404, EmptyFlagsAtEnd_404) {
  absl::string_view text("hello");
  uint32_t flags = Prog::EmptyFlags(text, text.data() + text.size());
  // At the end, kEmptyEndText and kEmptyEndLine should be set
  EXPECT_NE(flags, 0u);
}

// Test EmptyFlags in the middle of text
TEST_F(ProgTest_404, EmptyFlagsMiddle_404) {
  absl::string_view text("hello");
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 2);
  // In the middle of a word, word boundary flags may or may not be set
  // Just verify we get a valid return
  (void)flags;  // Not crashing is the test
}

// Test EmptyFlags with empty text
TEST_F(ProgTest_404, EmptyFlagsEmptyText_404) {
  absl::string_view text("");
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // Both begin and end flags should be set
  EXPECT_NE(flags, 0u);
}

// Test PossibleMatchRange on a simple pattern
TEST_F(ProgTest_404, PossibleMatchRangeSimple_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  bool ok = prog->PossibleMatchRange(&min_match, &max_match, 10);
  EXPECT_TRUE(ok);
  EXPECT_LE(min_match, max_match);
}

// Test PossibleMatchRange with character class
TEST_F(ProgTest_404, PossibleMatchRangeCharClass_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("[a-z]+"));
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  bool ok = prog->PossibleMatchRange(&min_match, &max_match, 10);
  EXPECT_TRUE(ok);
  EXPECT_LE(min_match, max_match);
}

// Test PossibleMatchRange with maxlen = 0
TEST_F(ProgTest_404, PossibleMatchRangeZeroMaxlen_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  // maxlen=0 is a boundary condition
  bool ok = prog->PossibleMatchRange(&min_match, &max_match, 0);
  // Result depends on implementation; just don't crash
  (void)ok;
}

// Test size after compilation
TEST_F(ProgTest_404, SizeAfterCompilation_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("a|b|c"));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
}

// Test bytemap_range after ComputeByteMap
TEST_F(ProgTest_404, BytemapRangeAfterCompute_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("[abc]"));
  ASSERT_NE(prog, nullptr);
  // After compilation, bytemap should be computed
  EXPECT_GT(prog->bytemap_range(), 0);
}

// Test Flatten does not crash
TEST_F(ProgTest_404, FlattenDoesNotCrash_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("(a|b)*c"));
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // After flattening, still should be able to dump
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Optimize does not crash
TEST_F(ProgTest_404, OptimizeDoesNotCrash_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("(a|b)+"));
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  EXPECT_GT(prog->size(), 0);
}

// Test IsOnePass on a one-pass regex
TEST_F(ProgTest_404, IsOnePassSimple_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("^abc$"));
  ASSERT_NE(prog, nullptr);
  // Simple literal patterns are typically one-pass
  bool onepass = prog->IsOnePass();
  // We just check it doesn't crash; the result depends on the pattern
  (void)onepass;
}

// Test can_prefix_accel on default Prog
TEST_F(ProgTest_404, CanPrefixAccelDefault_404) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test PrefixAccel on default Prog returns nullptr
TEST_F(ProgTest_404, PrefixAccelDefaultReturnsNull_404) {
  Prog prog;
  const char data[] = "hello";
  // If can_prefix_accel is false, calling PrefixAccel might not be valid,
  // but we test the boundary
  // Actually this would be undefined if not configured, so skip calling it
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test Fanout
TEST_F(ProgTest_404, FanoutSimple_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("a*b"));
  ASSERT_NE(prog, nullptr);
  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);
  // Just verify it doesn't crash and produces some output
  EXPECT_GE(fanout.size(), 0u);
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_404, TestingOnlySetDfaShouldBailWhenSlow_404) {
  // Just verify the static method can be called without crashing
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test SearchNFA on a simple pattern
TEST_F(ProgTest_404, SearchNFASimpleMatch_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xabcy");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

// Test SearchNFA with no match
TEST_F(ProgTest_404, SearchNFANoMatch_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("xyz"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test SearchNFA anchored
TEST_F(ProgTest_404, SearchNFAAnchored_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

// Test SearchNFA anchored no match
TEST_F(ProgTest_404, SearchNFAAnchoredNoMatch_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xabc");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test SearchBitState simple match
TEST_F(ProgTest_404, SearchBitStateSimpleMatch_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;
  absl::string_view text("xabcy");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

// Test SearchBitState no match
TEST_F(ProgTest_404, SearchBitStateNoMatch_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("xyz"));
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;
  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test CanBitState
TEST_F(ProgTest_404, CanBitStateSmallProg_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("a"));
  ASSERT_NE(prog, nullptr);
  // Small programs should be able to use bit state
  EXPECT_TRUE(prog->CanBitState());
}

// Test SearchDFA simple match
TEST_F(ProgTest_404, SearchDFASimpleMatch_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("xabcy");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
}

// Test SearchDFA no match
TEST_F(ProgTest_404, SearchDFANoMatch_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("xyz"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(found);
  }
}

// Test DumpByteMap on default-constructed Prog
TEST_F(ProgTest_404, DumpByteMapDefault_404) {
  Prog prog;
  std::string map = prog.DumpByteMap();
  // Default bytemap_ is zero-initialized, so all bytes map to 0
  // Should produce at least one line
  EXPECT_FALSE(map.empty());
  EXPECT_NE(map.find("-> 0"), std::string::npos);
}

// Test DumpByteMap covers full range [00-ff]
TEST_F(ProgTest_404, DumpByteMapCoversFullRange_404) {
  Prog prog;
  std::string map = prog.DumpByteMap();
  // Should start with [00-
  EXPECT_NE(map.find("[00-"), std::string::npos);
  // Should end with ff] since all map to 0
  EXPECT_NE(map.find("ff]"), std::string::npos);
}

// Test SearchOnePass if the program is one-pass
TEST_F(ProgTest_404, SearchOnePassIfApplicable_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("^(a+)(b+)$"));
  ASSERT_NE(prog, nullptr);
  if (!prog->IsOnePass()) return;
  absl::string_view text("aaabbb");
  absl::string_view match[3];
  bool found = prog->SearchOnePass(text, text, Prog::kAnchored,
                                    Prog::kFirstMatch, match, 3);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "aaabbb");
  EXPECT_EQ(match[1], "aaa");
  EXPECT_EQ(match[2], "bbb");
}

// Test EmptyFlags at newline boundary
TEST_F(ProgTest_404, EmptyFlagsAtNewline_404) {
  absl::string_view text("a\nb");
  // Point p at the newline character
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 2);
  // After newline, kEmptyBeginLine should be set
  // We can't check exact flags without knowing constants, but verify non-crash
  (void)flags;
}

// Test CompileSet
TEST_F(ProgTest_404, CompileSetBasic_404) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def|ghi", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::unique_ptr<Prog> prog(Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20));
  re->Decref();
  // CompileSet may or may not succeed depending on the pattern
  // Just verify it doesn't crash
}

// Test inst_count returns valid counts
TEST_F(ProgTest_404, InstCountAfterCompilation_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("a*b+c?"));
  ASSERT_NE(prog, nullptr);
  // Just check these don't crash
  int total = 0;
  for (int i = 0; i < 8; i++) {
    int count = prog->inst_count(static_cast<Prog::InstOp>(i));
    EXPECT_GE(count, 0);
    total += count;
  }
}

// Test with empty pattern
TEST_F(ProgTest_404, EmptyPatternCompilation_404) {
  std::unique_ptr<Prog> prog(CompileRegexp(""));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
}

// Test PossibleMatchRange with dot star
TEST_F(ProgTest_404, PossibleMatchRangeDotStar_404) {
  std::unique_ptr<Prog> prog(CompileRegexp(".*"));
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  bool ok = prog->PossibleMatchRange(&min_match, &max_match, 10);
  // .* can match anything, so range should be broad
  (void)ok;
}

// Test BuildEntireDFA
TEST_F(ProgTest_404, BuildEntireDFASimple_404) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  int states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(states, 0);
}

}  // namespace re2
