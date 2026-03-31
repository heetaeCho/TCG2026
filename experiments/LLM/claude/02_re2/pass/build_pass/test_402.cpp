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

// Helper function to compile a regex pattern into a Prog
static Prog* CompileRegexp(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

class ProgTest_402 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Progs are owned and must be deleted
  }
};

// Test that a default-constructed Prog has expected initial values
TEST_F(ProgTest_402, DefaultConstructor_402) {
  Prog prog;
  EXPECT_EQ(prog.start(), 0);
  EXPECT_EQ(prog.start_unanchored(), 0);
  EXPECT_EQ(prog.size(), 0);
  EXPECT_FALSE(prog.reversed());
  EXPECT_FALSE(prog.anchor_start());
  EXPECT_FALSE(prog.anchor_end());
  EXPECT_EQ(prog.dfa_mem(), 0);
  EXPECT_EQ(prog.bytemap_range(), 0);
}

// Test set_start and start accessors
TEST_F(ProgTest_402, SetStart_402) {
  Prog prog;
  prog.set_start(5);
  EXPECT_EQ(prog.start(), 5);
  prog.set_start(0);
  EXPECT_EQ(prog.start(), 0);
}

// Test set_start_unanchored and start_unanchored accessors
TEST_F(ProgTest_402, SetStartUnanchored_402) {
  Prog prog;
  prog.set_start_unanchored(10);
  EXPECT_EQ(prog.start_unanchored(), 10);
}

// Test set_reversed and reversed accessors
TEST_F(ProgTest_402, SetReversed_402) {
  Prog prog;
  EXPECT_FALSE(prog.reversed());
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test set_anchor_start and anchor_start accessors
TEST_F(ProgTest_402, SetAnchorStart_402) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_start());
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test set_anchor_end and anchor_end accessors
TEST_F(ProgTest_402, SetAnchorEnd_402) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_end());
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test set_dfa_mem and dfa_mem accessors
TEST_F(ProgTest_402, SetDfaMem_402) {
  Prog prog;
  EXPECT_EQ(prog.dfa_mem(), 0);
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog.dfa_mem(), 1024 * 1024);
}

// Test Dump on a simple compiled program
TEST_F(ProgTest_402, DumpSimplePattern_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("a"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

// Test DumpUnanchored on a simple compiled program
TEST_F(ProgTest_402, DumpUnanchoredSimplePattern_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("a"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

// Test DumpByteMap on a compiled program
TEST_F(ProgTest_402, DumpByteMap_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
}

// Test Dump after Flatten
TEST_F(ProgTest_402, DumpAfterFlatten_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("a|b"));
  ASSERT_NE(prog, nullptr);
  std::string dumpBefore = prog->Dump();
  prog->Flatten();
  std::string dumpAfter = prog->Dump();
  // Both dumps should be non-empty
  EXPECT_FALSE(dumpBefore.empty());
  EXPECT_FALSE(dumpAfter.empty());
}

// Test that size > 0 for a compiled program
TEST_F(ProgTest_402, CompiledProgramSize_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
}

// Test bytemap_range for a compiled program
TEST_F(ProgTest_402, BytemapRange_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
}

// Test bytemap is not null for a compiled program
TEST_F(ProgTest_402, BytemapNotNull_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  EXPECT_NE(prog->bytemap(), nullptr);
}

// Test IsWordChar
TEST_F(ProgTest_402, IsWordChar_402) {
  // Standard word characters: [a-zA-Z0-9_]
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));
  
  // Non-word characters
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
}

// Test PossibleMatchRange on a simple pattern
TEST_F(ProgTest_402, PossibleMatchRange_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_FALSE(min_str.empty());
  EXPECT_FALSE(max_str.empty());
  EXPECT_LE(min_str, max_str);
}

// Test PossibleMatchRange with maxlen = 0
TEST_F(ProgTest_402, PossibleMatchRangeZeroMaxlen_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 0);
  // With maxlen 0, behavior may vary but should not crash
  (void)result;
}

// Test EmptyFlags at various positions
TEST_F(ProgTest_402, EmptyFlagsAtBoundaries_402) {
  absl::string_view text("hello world");
  
  // At the beginning of text
  uint32_t flags_begin = Prog::EmptyFlags(text, text.data());
  // Should have some flags set (at least beginning of text)
  // We just check it doesn't crash and returns something
  (void)flags_begin;
  
  // At the end of text
  uint32_t flags_end = Prog::EmptyFlags(text, text.data() + text.size());
  (void)flags_end;
  
  // In the middle
  uint32_t flags_mid = Prog::EmptyFlags(text, text.data() + 5);
  (void)flags_mid;
}

// Test EmptyFlags with empty text
TEST_F(ProgTest_402, EmptyFlagsEmptyText_402) {
  absl::string_view text("");
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // Should not crash
  (void)flags;
}

// Test SearchNFA on a simple matching case
TEST_F(ProgTest_402, SearchNFAMatch_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("say hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored, 
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

// Test SearchNFA no match
TEST_F(ProgTest_402, SearchNFANoMatch_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("xyz"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored, 
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test SearchNFA anchored match
TEST_F(ProgTest_402, SearchNFAAnchored_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, 
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

// Test SearchNFA anchored no match
TEST_F(ProgTest_402, SearchNFAAnchoredNoMatch_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("world"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, 
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test SearchDFA on a simple matching case
TEST_F(ProgTest_402, SearchDFAMatch_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("say hello world");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
}

// Test SearchDFA no match
TEST_F(ProgTest_402, SearchDFANoMatch_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("xyz"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("hello world");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(found);
  }
}

// Test can_prefix_accel on a simple program (no prefix configured)
TEST_F(ProgTest_402, CanPrefixAccelDefault_402) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test Flatten does not crash on a compiled program
TEST_F(ProgTest_402, FlattenDoesNotCrash_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("a(b|c)d"));
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // After flatten, the program should still be valid
  EXPECT_GT(prog->size(), 0);
}

// Test Optimize does not crash
TEST_F(ProgTest_402, OptimizeDoesNotCrash_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("a+b*c?"));
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  EXPECT_GT(prog->size(), 0);
}

// Test IsOnePass on a one-pass program
TEST_F(ProgTest_402, IsOnePassSimple_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  // Simple literal patterns should be one-pass
  bool onepass = prog->IsOnePass();
  EXPECT_TRUE(onepass);
}

// Test IsOnePass on a non-one-pass program
TEST_F(ProgTest_402, IsOnePassComplex_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("(a*)(a*)"));
  ASSERT_NE(prog, nullptr);
  // Ambiguous patterns are not one-pass
  bool onepass = prog->IsOnePass();
  // We just check it returns a boolean without crashing
  (void)onepass;
}

// Test SearchOnePass when pattern is one-pass
TEST_F(ProgTest_402, SearchOnePassMatch_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  if (prog->IsOnePass()) {
    absl::string_view text("xabcy");
    absl::string_view match;
    bool found = prog->SearchOnePass(text, text, Prog::kUnanchored,
                                      Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "abc");
  }
}

// Test CanBitState
TEST_F(ProgTest_402, CanBitState_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  // Small programs should support bit-state
  bool can = prog->CanBitState();
  // We just check it doesn't crash
  (void)can;
}

// Test SearchBitState on a simple matching case
TEST_F(ProgTest_402, SearchBitStateMatch_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  if (prog->CanBitState()) {
    absl::string_view text("say hello world");
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "hello");
  }
}

// Test SearchBitState no match
TEST_F(ProgTest_402, SearchBitStateNoMatch_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("xyz"));
  ASSERT_NE(prog, nullptr);
  if (prog->CanBitState()) {
    absl::string_view text("hello world");
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_FALSE(found);
  }
}

// Test SearchNFA with empty text
TEST_F(ProgTest_402, SearchNFAEmptyText_402) {
  std::unique_ptr<Prog> prog(CompileRegexp(""));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  // Empty pattern should match empty text
  EXPECT_TRUE(found);
}

// Test SearchNFA with empty pattern on non-empty text
TEST_F(ProgTest_402, SearchNFAEmptyPatternNonEmptyText_402) {
  std::unique_ptr<Prog> prog(CompileRegexp(""));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("hello");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

// Test Fanout does not crash
TEST_F(ProgTest_402, FanoutDoesNotCrash_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("a|b|c"));
  ASSERT_NE(prog, nullptr);
  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);
  // Just check it doesn't crash
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_402, TestingOnlySetDfaShouldBailWhenSlow_402) {
  // Should not crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test inst accessor
TEST_F(ProgTest_402, InstAccessor_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  ASSERT_GT(prog->size(), 0);
  // Access first instruction - should not crash
  Prog::Inst* inst = prog->inst(0);
  EXPECT_NE(inst, nullptr);
}

// Test Dump on pattern with alternation
TEST_F(ProgTest_402, DumpAlternation_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("cat|dog"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Dump on pattern with repetition
TEST_F(ProgTest_402, DumpRepetition_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("a+b*c?"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

// Test PossibleMatchRange with character class
TEST_F(ProgTest_402, PossibleMatchRangeCharClass_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("[a-z]+"));
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 10);
  if (result) {
    EXPECT_LE(min_str, max_str);
  }
}

// Test that ConfigurePrefixAccel works without crash
TEST_F(ProgTest_402, ConfigurePrefixAccel_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  // Should not crash
  prog->ConfigurePrefixAccel("hello", false);
}

// Test ConfigurePrefixAccel with foldcase
TEST_F(ProgTest_402, ConfigurePrefixAccelFoldcase_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("(?i)hello"));
  ASSERT_NE(prog, nullptr);
  prog->ConfigurePrefixAccel("hello", true);
}

// Test SearchNFA with capturing groups
TEST_F(ProgTest_402, SearchNFAWithCaptures_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("(hello) (world)"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("say hello world now");
  absl::string_view match[3];
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, match, 3);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "hello world");
  EXPECT_EQ(match[1], "hello");
  EXPECT_EQ(match[2], "world");
}

// Test bit_state_text_max_size accessor
TEST_F(ProgTest_402, BitStateTextMaxSize_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  size_t max_size = prog->bit_state_text_max_size();
  // Should be a reasonable value
  (void)max_size;
}

// Test CompileSet
TEST_F(ProgTest_402, CompileSet_402) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::unique_ptr<Prog> prog(Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20));
  re->Decref();
  // CompileSet may or may not succeed depending on the pattern
  // Just check no crash
}

// Test BuildEntireDFA
TEST_F(ProgTest_402, BuildEntireDFA_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("a|b|c"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  int states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(states, 0);
}

// Test that multiple Flatten calls don't crash
TEST_F(ProgTest_402, DoubleFlatten_402) {
  std::unique_ptr<Prog> prog(CompileRegexp("a(b|c)d"));
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // Second flatten should be a no-op or safe
  prog->Flatten();
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

}  // namespace re2
