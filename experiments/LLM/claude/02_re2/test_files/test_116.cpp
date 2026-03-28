#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/testing/regexp_generator.h"
#include "absl/strings/string_view.h"

namespace re2 {

// Helper to compile a Regexp into a Prog for testing
class ProgTest_116 : public ::testing::Test {
 protected:
  Prog* CompileRegexp(const char* pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::PerlX|Regexp::Latin1, &status);
    if (re == nullptr) return nullptr;
    Prog* prog = re->CompileToProg(0);
    re->Decref();
    return prog;
  }
};

// Test default construction of Prog
TEST_F(ProgTest_116, DefaultConstruction_116) {
  Prog prog;
  EXPECT_EQ(0, prog.size());
  EXPECT_EQ(0, prog.start());
  EXPECT_EQ(0, prog.start_unanchored());
  EXPECT_FALSE(prog.reversed());
  EXPECT_FALSE(prog.anchor_start());
  EXPECT_FALSE(prog.anchor_end());
  EXPECT_EQ(0, prog.bytemap_range());
  EXPECT_EQ(0, prog.dfa_mem());
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test size() for a compiled program
TEST_F(ProgTest_116, SizeNonZeroAfterCompile_116) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(nullptr, prog);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test start() and set_start()
TEST_F(ProgTest_116, SetAndGetStart_116) {
  Prog prog;
  prog.set_start(5);
  EXPECT_EQ(5, prog.start());
  prog.set_start(0);
  EXPECT_EQ(0, prog.start());
}

// Test start_unanchored() and set_start_unanchored()
TEST_F(ProgTest_116, SetAndGetStartUnanchored_116) {
  Prog prog;
  prog.set_start_unanchored(10);
  EXPECT_EQ(10, prog.start_unanchored());
  prog.set_start_unanchored(0);
  EXPECT_EQ(0, prog.start_unanchored());
}

// Test reversed() and set_reversed()
TEST_F(ProgTest_116, SetAndGetReversed_116) {
  Prog prog;
  EXPECT_FALSE(prog.reversed());
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test anchor_start() and set_anchor_start()
TEST_F(ProgTest_116, SetAndGetAnchorStart_116) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_start());
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test anchor_end() and set_anchor_end()
TEST_F(ProgTest_116, SetAndGetAnchorEnd_116) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_end());
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test dfa_mem() and set_dfa_mem()
TEST_F(ProgTest_116, SetAndGetDfaMem_116) {
  Prog prog;
  EXPECT_EQ(0, prog.dfa_mem());
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(1024 * 1024, prog.dfa_mem());
}

// Test bytemap() is not null after ComputeByteMap on a compiled Prog
TEST_F(ProgTest_116, BytemapNotNullAfterCompile_116) {
  Prog* prog = CompileRegexp("a");
  ASSERT_NE(nullptr, prog);
  EXPECT_NE(nullptr, prog->bytemap());
  delete prog;
}

// Test bytemap_range() for a compiled program
TEST_F(ProgTest_116, BytemapRangeAfterCompile_116) {
  Prog* prog = CompileRegexp("[a-z]");
  ASSERT_NE(nullptr, prog);
  EXPECT_GT(prog->bytemap_range(), 0);
  delete prog;
}

// Test Dump() returns non-empty string
TEST_F(ProgTest_116, DumpReturnsNonEmpty_116) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(nullptr, prog);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test DumpUnanchored() returns non-empty string
TEST_F(ProgTest_116, DumpUnanchoredReturnsNonEmpty_116) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(nullptr, prog);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test DumpByteMap() returns non-empty string
TEST_F(ProgTest_116, DumpByteMapReturnsNonEmpty_116) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(nullptr, prog);
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test IsWordChar
TEST_F(ProgTest_116, IsWordCharLetters_116) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

TEST_F(ProgTest_116, IsWordCharNonWord_116) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
}

// Test EmptyFlags at various positions
TEST_F(ProgTest_116, EmptyFlagsAtBeginning_116) {
  absl::string_view text("hello");
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // At the beginning of text, beginning-of-text flag should be set
  EXPECT_NE(0u, flags);
}

TEST_F(ProgTest_116, EmptyFlagsAtEnd_116) {
  absl::string_view text("hello");
  uint32_t flags = Prog::EmptyFlags(text, text.data() + text.size());
  // At the end of text, end-of-text flag should be set
  EXPECT_NE(0u, flags);
}

TEST_F(ProgTest_116, EmptyFlagsEmptyString_116) {
  absl::string_view text("");
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // Both beginning and end of text flags should be set
  EXPECT_NE(0u, flags);
}

// Test can_prefix_accel() on default Prog
TEST_F(ProgTest_116, CanPrefixAccelDefault_116) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test PossibleMatchRange
TEST_F(ProgTest_116, PossibleMatchRangeSimple_116) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(nullptr, prog);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_FALSE(min_str.empty());
  EXPECT_FALSE(max_str.empty());
  EXPECT_LE(min_str, max_str);
  delete prog;
}

TEST_F(ProgTest_116, PossibleMatchRangeMaxLenZero_116) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(nullptr, prog);
  std::string min_str, max_str;
  // maxlen of 0 is a boundary case
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 0);
  // Result may be true or false depending on implementation
  // Just ensure it doesn't crash
  (void)result;
  delete prog;
}

// Test IsOnePass for a simple pattern
TEST_F(ProgTest_116, IsOnePassSimple_116) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(nullptr, prog);
  // Simple literal patterns are typically one-pass
  bool onepass = prog->IsOnePass();
  EXPECT_TRUE(onepass);
  delete prog;
}

// Test IsOnePass for a pattern that is not one-pass
TEST_F(ProgTest_116, IsOnePassComplex_116) {
  // Patterns with ambiguity are typically not one-pass
  Prog* prog = CompileRegexp("(a|a)b");
  ASSERT_NE(nullptr, prog);
  // This may or may not be one-pass, just ensure no crash
  bool onepass = prog->IsOnePass();
  (void)onepass;
  delete prog;
}

// Test SearchNFA for a matching pattern
TEST_F(ProgTest_116, SearchNFAMatch_116) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(nullptr, prog);
  absl::string_view text("xabcy");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ("abc", match);
  delete prog;
}

// Test SearchNFA for a non-matching pattern
TEST_F(ProgTest_116, SearchNFANoMatch_116) {
  Prog* prog = CompileRegexp("xyz");
  ASSERT_NE(nullptr, prog);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  delete prog;
}

// Test SearchNFA with anchored search
TEST_F(ProgTest_116, SearchNFAAnchored_116) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(nullptr, prog);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ("abc", match);
  delete prog;
}

TEST_F(ProgTest_116, SearchNFAAnchoredNoMatch_116) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(nullptr, prog);
  absl::string_view text("xabcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  delete prog;
}

// Test SearchDFA
TEST_F(ProgTest_116, SearchDFAMatch_116) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(nullptr, prog);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("xabcy");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  if (!failed) {
    EXPECT_TRUE(found);
  }
  delete prog;
}

TEST_F(ProgTest_116, SearchDFANoMatch_116) {
  Prog* prog = CompileRegexp("xyz");
  ASSERT_NE(nullptr, prog);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(found);
  }
  delete prog;
}

// Test SearchBitState
TEST_F(ProgTest_116, SearchBitStateMatch_116) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(nullptr, prog);
  if (prog->CanBitState()) {
    absl::string_view text("xabcy");
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ("abc", match);
  }
  delete prog;
}

TEST_F(ProgTest_116, SearchBitStateNoMatch_116) {
  Prog* prog = CompileRegexp("xyz");
  ASSERT_NE(nullptr, prog);
  if (prog->CanBitState()) {
    absl::string_view text("abcdef");
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_FALSE(found);
  }
  delete prog;
}

// Test CanBitState
TEST_F(ProgTest_116, CanBitStateSmallProgram_116) {
  Prog* prog = CompileRegexp("a");
  ASSERT_NE(nullptr, prog);
  // Small programs should be amenable to bit-state
  EXPECT_TRUE(prog->CanBitState());
  delete prog;
}

// Test SearchOnePass for a one-pass pattern
TEST_F(ProgTest_116, SearchOnePassMatch_116) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(nullptr, prog);
  if (prog->IsOnePass()) {
    absl::string_view text("abc");
    absl::string_view match;
    bool found = prog->SearchOnePass(text, text, Prog::kAnchored,
                                      Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ("abc", match);
  }
  delete prog;
}

TEST_F(ProgTest_116, SearchOnePassNoMatch_116) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(nullptr, prog);
  if (prog->IsOnePass()) {
    absl::string_view text("xyz");
    absl::string_view match;
    bool found = prog->SearchOnePass(text, text, Prog::kAnchored,
                                      Prog::kFirstMatch, &match, 1);
    EXPECT_FALSE(found);
  }
  delete prog;
}

// Test Flatten doesn't crash
TEST_F(ProgTest_116, FlattenDoesNotCrash_116) {
  Prog* prog = CompileRegexp("abc|def");
  ASSERT_NE(nullptr, prog);
  prog->Flatten();
  // After flatten, program should still work
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test Optimize doesn't crash
TEST_F(ProgTest_116, OptimizeDoesNotCrash_116) {
  Prog* prog = CompileRegexp("abc|def");
  ASSERT_NE(nullptr, prog);
  prog->Optimize();
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_116, TestingOnlySetDfaShouldBailWhenSlow_116) {
  // Just ensure the function can be called without crashing
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test empty pattern
TEST_F(ProgTest_116, EmptyPattern_116) {
  Prog* prog = CompileRegexp("");
  ASSERT_NE(nullptr, prog);
  EXPECT_GT(prog->size(), 0);
  
  absl::string_view text("anything");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ("", match);
  delete prog;
}

// Test complex pattern with groups
TEST_F(ProgTest_116, ComplexPatternWithGroups_116) {
  Prog* prog = CompileRegexp("(a+)(b+)");
  ASSERT_NE(nullptr, prog);
  EXPECT_GT(prog->size(), 0);
  
  absl::string_view text("xaaabby");
  absl::string_view match[3];
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, match, 3);
  EXPECT_TRUE(found);
  EXPECT_EQ("aaabb", match[0]);
  EXPECT_EQ("aaa", match[1]);
  EXPECT_EQ("bb", match[2]);
  delete prog;
}

// Test inst() accessor
TEST_F(ProgTest_116, InstAccessor_116) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(nullptr, prog);
  ASSERT_GT(prog->size(), 0);
  // Access first instruction
  Prog::Inst* inst = prog->inst(0);
  EXPECT_NE(nullptr, inst);
  delete prog;
}

// Test PossibleMatchRange with different patterns
TEST_F(ProgTest_116, PossibleMatchRangeAlternation_116) {
  Prog* prog = CompileRegexp("abc|xyz");
  ASSERT_NE(nullptr, prog);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_str, max_str);
  delete prog;
}

// Test PossibleMatchRange with dot star
TEST_F(ProgTest_116, PossibleMatchRangeDotStar_116) {
  Prog* prog = CompileRegexp(".*");
  ASSERT_NE(nullptr, prog);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 10);
  // .* matches everything, so range should be quite broad
  (void)result;  // May or may not succeed
  delete prog;
}

// Test SearchNFA with empty text
TEST_F(ProgTest_116, SearchNFAEmptyText_116) {
  Prog* prog = CompileRegexp("a*");
  ASSERT_NE(nullptr, prog);
  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ("", match);
  delete prog;
}

// Test SearchNFA with nmatch = 0
TEST_F(ProgTest_116, SearchNFAZeroNmatch_116) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(nullptr, prog);
  absl::string_view text("abc");
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, nullptr, 0);
  EXPECT_TRUE(found);
  delete prog;
}

// Test BuildEntireDFA
TEST_F(ProgTest_116, BuildEntireDFA_116) {
  Prog* prog = CompileRegexp("[ab]");
  ASSERT_NE(nullptr, prog);
  prog->set_dfa_mem(1 << 20);
  int states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(states, 0);
  delete prog;
}

// Test CompileSet
TEST_F(ProgTest_116, CompileSetBasic_116) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX|Regexp::Latin1, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(nullptr, prog);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test bit_state_text_max_size
TEST_F(ProgTest_116, BitStateTextMaxSize_116) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(nullptr, prog);
  // bit_state_text_max_size should be computed
  size_t max_size = prog->bit_state_text_max_size();
  EXPECT_GT(max_size, 0u);
  delete prog;
}

}  // namespace re2
