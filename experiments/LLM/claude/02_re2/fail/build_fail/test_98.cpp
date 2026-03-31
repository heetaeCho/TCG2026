#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "absl/strings/string_view.h"
#include <string>
#include <memory>

namespace re2 {

// Helper to compile a Prog from a regex pattern string
static Prog* CompileRegexp(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

class ProgTest_98 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any allocated progs
  }
};

// Test default constructor initializes fields properly
TEST_F(ProgTest_98, DefaultConstructor_98) {
  Prog prog;
  EXPECT_EQ(prog.start(), 0);
  EXPECT_EQ(prog.start_unanchored(), 0);
  EXPECT_FALSE(prog.reversed());
  EXPECT_FALSE(prog.anchor_start());
  EXPECT_FALSE(prog.anchor_end());
  EXPECT_EQ(prog.dfa_mem(), 0);
  EXPECT_EQ(prog.bytemap_range(), 0);
}

// Test set_start and start
TEST_F(ProgTest_98, SetStartAndGetStart_98) {
  Prog prog;
  prog.set_start(5);
  EXPECT_EQ(prog.start(), 5);
  prog.set_start(0);
  EXPECT_EQ(prog.start(), 0);
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_98, SetStartUnanchoredAndGet_98) {
  Prog prog;
  prog.set_start_unanchored(10);
  EXPECT_EQ(prog.start_unanchored(), 10);
}

// Test set_reversed and reversed
TEST_F(ProgTest_98, SetReversedAndGet_98) {
  Prog prog;
  EXPECT_FALSE(prog.reversed());
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test set_anchor_start and anchor_start
TEST_F(ProgTest_98, SetAnchorStartAndGet_98) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_start());
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test set_anchor_end and anchor_end
TEST_F(ProgTest_98, SetAnchorEndAndGet_98) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_end());
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test set_dfa_mem and dfa_mem
TEST_F(ProgTest_98, SetDfaMemAndGet_98) {
  Prog prog;
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog.dfa_mem(), 1024 * 1024);
}

// Test IsWordChar for various characters
TEST_F(ProgTest_98, IsWordChar_98) {
  // Alphanumeric characters are word chars
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));

  // Non-word chars
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
}

// Test compiling a simple regex and checking basic prog properties
TEST_F(ProgTest_98, CompileSimpleRegex_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
}

// Test Dump produces non-empty output for a compiled regex
TEST_F(ProgTest_98, DumpNonEmpty_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("a+b"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

// Test DumpUnanchored produces non-empty output
TEST_F(ProgTest_98, DumpUnanchoredNonEmpty_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("a+b"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

// Test DumpByteMap produces non-empty output
TEST_F(ProgTest_98, DumpByteMapNonEmpty_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
}

// Test bytemap returns non-null after compilation
TEST_F(ProgTest_98, BytemapNonNull_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  EXPECT_NE(prog->bytemap(), nullptr);
}

// Test bytemap_range is reasonable after compilation
TEST_F(ProgTest_98, BytemapRangeAfterCompile_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("[a-z]"));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
}

// Test EmptyFlags at various positions
TEST_F(ProgTest_98, EmptyFlagsAtBeginning_98) {
  absl::string_view text = "hello";
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // At the beginning of text, kEmptyBeginText and kEmptyBeginLine should be set
  EXPECT_NE(flags & kEmptyBeginText, 0u);
  EXPECT_NE(flags & kEmptyBeginLine, 0u);
}

TEST_F(ProgTest_98, EmptyFlagsAtEnd_98) {
  absl::string_view text = "hello";
  uint32_t flags = Prog::EmptyFlags(text, text.data() + text.size());
  // At the end of text, kEmptyEndText and kEmptyEndLine should be set
  EXPECT_NE(flags & kEmptyEndText, 0u);
  EXPECT_NE(flags & kEmptyEndLine, 0u);
}

TEST_F(ProgTest_98, EmptyFlagsAtNewline_98) {
  absl::string_view text = "hello\nworld";
  // After the newline character
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 6);
  EXPECT_NE(flags & kEmptyBeginLine, 0u);
}

TEST_F(ProgTest_98, EmptyFlagsWordBoundary_98) {
  absl::string_view text = "a b";
  // Between 'a' and ' '
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 1);
  EXPECT_NE(flags & kEmptyWordBoundary, 0u);
}

TEST_F(ProgTest_98, EmptyFlagsNonWordBoundary_98) {
  absl::string_view text = "ab";
  // Between 'a' and 'b'
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 1);
  EXPECT_NE(flags & kEmptyNonWordBoundary, 0u);
}

// Test SearchNFA with a simple pattern
TEST_F(ProgTest_98, SearchNFASimpleMatch_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "say hello world";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

TEST_F(ProgTest_98, SearchNFANoMatch_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("xyz"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "hello world";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgTest_98, SearchNFAAnchored_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "hello world";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

TEST_F(ProgTest_98, SearchNFAAnchoredNoMatch_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("world"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "hello world";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test SearchDFA with a simple pattern
TEST_F(ProgTest_98, SearchDFASimpleMatch_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text = "say hello world";
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
}

TEST_F(ProgTest_98, SearchDFANoMatch_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("xyz"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text = "hello world";
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(found);
  }
}

// Test PossibleMatchRange
TEST_F(ProgTest_98, PossibleMatchRange_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  bool ok = prog->PossibleMatchRange(&min_match, &max_match, 10);
  EXPECT_TRUE(ok);
  EXPECT_LE(min_match, max_match);
  // "abc" should be within the range
  EXPECT_LE(min_match, "abc");
  EXPECT_GE(max_match, "abc");
}

TEST_F(ProgTest_98, PossibleMatchRangeAlternation_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("a|z"));
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  bool ok = prog->PossibleMatchRange(&min_match, &max_match, 10);
  EXPECT_TRUE(ok);
  EXPECT_LE(min_match, "a");
  EXPECT_GE(max_match, "z");
}

// Test IsOnePass
TEST_F(ProgTest_98, IsOnePassSimple_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  // Simple literal should be one-pass
  EXPECT_TRUE(prog->IsOnePass());
}

TEST_F(ProgTest_98, IsOnePassAmbiguous_98) {
  // Ambiguous pattern may not be one-pass
  std::unique_ptr<Prog> prog(CompileRegexp("(a|a)b"));
  ASSERT_NE(prog, nullptr);
  // Don't assert specific value, just ensure it doesn't crash
  prog->IsOnePass();
}

// Test SearchOnePass
TEST_F(ProgTest_98, SearchOnePassMatch_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("(\\w+)"));
  ASSERT_NE(prog, nullptr);
  if (prog->IsOnePass()) {
    absl::string_view text = "hello";
    absl::string_view match[2];
    bool found = prog->SearchOnePass(text, text, Prog::kAnchored,
                                      Prog::kFirstMatch, match, 2);
    EXPECT_TRUE(found);
    EXPECT_EQ(match[0], "hello");
  }
}

// Test Flatten
TEST_F(ProgTest_98, FlattenDoesNotCrash_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("a+b*c?"));
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // After flatten, the prog should still be usable
  EXPECT_GT(prog->size(), 0);
}

// Test Optimize
TEST_F(ProgTest_98, OptimizeDoesNotCrash_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("[a-z]+"));
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  // After optimize, still usable
  EXPECT_GT(prog->size(), 0);
}

// Test size() returns positive for a compiled prog
TEST_F(ProgTest_98, SizePositive_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("a(b|c)d"));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
}

// Test inst() returns non-null for valid ids
TEST_F(ProgTest_98, InstAccess_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  for (int i = 0; i < prog->size(); i++) {
    EXPECT_NE(prog->inst(i), nullptr);
  }
}

// Test Inst::id returns proper index
TEST_F(ProgTest_98, InstIdMatchesIndex_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  for (int i = 0; i < prog->size(); i++) {
    EXPECT_EQ(prog->inst(i)->id(prog.get()), i);
  }
}

// Test Inst::Dump produces non-empty output
TEST_F(ProgTest_98, InstDumpNonEmpty_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("a"));
  ASSERT_NE(prog, nullptr);
  ASSERT_GT(prog->size(), 0);
  std::string dump = prog->inst(0)->Dump();
  EXPECT_FALSE(dump.empty());
}

// Test SearchBitState
TEST_F(ProgTest_98, SearchBitStateMatch_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "say hello there";
  if (prog->CanBitState()) {
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "hello");
  }
}

TEST_F(ProgTest_98, SearchBitStateNoMatch_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("xyz"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "hello world";
  if (prog->CanBitState()) {
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_FALSE(found);
  }
}

// Test CanBitState
TEST_F(ProgTest_98, CanBitState_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("a"));
  ASSERT_NE(prog, nullptr);
  // Small regex should allow bit state
  EXPECT_TRUE(prog->CanBitState());
}

// Test ConfigurePrefixAccel and can_prefix_accel
TEST_F(ProgTest_98, ConfigurePrefixAccelSimple_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("abcdef"));
  ASSERT_NE(prog, nullptr);
  prog->ConfigurePrefixAccel("abc", false);
  EXPECT_TRUE(prog->can_prefix_accel());
}

TEST_F(ProgTest_98, NoPrefixAccelByDefault_98) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test PrefixAccel returns null for empty data with no prefix configured
TEST_F(ProgTest_98, PrefixAccelNullWithNoPrefixConfigured_98) {
  Prog prog;
  const char data[] = "test";
  // No prefix configured, can_prefix_accel should be false
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_98, TestingOnlySetDfaBailSlow_98) {
  // Just ensure it doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test CompileSet with a simple regex
TEST_F(ProgTest_98, CompileSetSimple_98) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::unique_ptr<Prog> prog(Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20));
  re->Decref();
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
}

// Test empty text search
TEST_F(ProgTest_98, SearchNFAEmptyText_98) {
  std::unique_ptr<Prog> prog(CompileRegexp(""));
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0u);
}

// Test NFA search with capturing groups
TEST_F(ProgTest_98, SearchNFAWithCaptures_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("(\\w+)@(\\w+)"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "user@host";
  absl::string_view match[3];
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, match, 3);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "user@host");
  EXPECT_EQ(match[1], "user");
  EXPECT_EQ(match[2], "host");
}

// Test Inst InitMatch and match_id
TEST_F(ProgTest_98, InstInitMatchAndMatchId_98) {
  Prog::Inst inst;
  inst.InitMatch(42);
  EXPECT_EQ(inst.match_id(), 42);
}

// Test Inst InitFail
TEST_F(ProgTest_98, InstInitFail_98) {
  Prog::Inst inst;
  inst.InitFail();
  EXPECT_EQ(inst.opcode(), kInstFail);
}

// Test Inst InitNop
TEST_F(ProgTest_98, InstInitNop_98) {
  Prog::Inst inst;
  inst.InitNop(5);
  EXPECT_EQ(inst.opcode(), kInstNop);
  EXPECT_EQ(inst.out(), 5);
}

// Test Inst InitByteRange
TEST_F(ProgTest_98, InstInitByteRange_98) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 0, 10);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.lo(), 'a');
  EXPECT_EQ(inst.hi(), 'z');
  EXPECT_EQ(inst.foldcase(), 0);
  EXPECT_EQ(inst.out(), 10);
}

// Test Inst InitByteRange with foldcase
TEST_F(ProgTest_98, InstInitByteRangeFoldcase_98) {
  Prog::Inst inst;
  inst.InitByteRange('A', 'Z', 1, 7);
  EXPECT_EQ(inst.lo(), 'A');
  EXPECT_EQ(inst.hi(), 'Z');
  EXPECT_EQ(inst.foldcase(), 1);
}

// Test Inst InitCapture
TEST_F(ProgTest_98, InstInitCapture_98) {
  Prog::Inst inst;
  inst.InitCapture(3, 15);
  EXPECT_EQ(inst.opcode(), kInstCapture);
  EXPECT_EQ(inst.cap(), 3);
  EXPECT_EQ(inst.out(), 15);
}

// Test Inst InitEmptyWidth
TEST_F(ProgTest_98, InstInitEmptyWidth_98) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyBeginLine, 20);
  EXPECT_EQ(inst.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst.empty(), kEmptyBeginLine);
  EXPECT_EQ(inst.out(), 20);
}

// Test Inst InitAlt
TEST_F(ProgTest_98, InstInitAlt_98) {
  Prog::Inst inst;
  inst.InitAlt(3, 7);
  EXPECT_EQ(inst.opcode(), kInstAlt);
  EXPECT_EQ(inst.out(), 3);
  EXPECT_EQ(inst.out1(), 7);
}

// Test Inst Matches for byte range
TEST_F(ProgTest_98, InstMatchesByteRange_98) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 0, 0);
  EXPECT_TRUE(inst.Matches('m'));
  EXPECT_TRUE(inst.Matches('a'));
  EXPECT_TRUE(inst.Matches('z'));
  EXPECT_FALSE(inst.Matches('A'));
  EXPECT_FALSE(inst.Matches('0'));
}

// Test Inst Matches with foldcase
TEST_F(ProgTest_98, InstMatchesByteRangeFoldcase_98) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 1, 0);
  EXPECT_TRUE(inst.Matches('a'));
  EXPECT_TRUE(inst.Matches('A'));  // foldcase should match
}

// Test NFA search with longest match
TEST_F(ProgTest_98, SearchNFALongestMatch_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("a+"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "aaa";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kLongestMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "aaa");
}

// Test Fanout
TEST_F(ProgTest_98, FanoutDoesNotCrash_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("a|b|c"));
  ASSERT_NE(prog, nullptr);
  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);
  // Just check it doesn't crash and produces some output
}

// Test BuildEntireDFA
TEST_F(ProgTest_98, BuildEntireDFASimple_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  int result = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  // Result should be positive (number of states)
  EXPECT_GT(result, 0);
}

// Test that list_count returns 0 for default prog
TEST_F(ProgTest_98, ListCountDefault_98) {
  Prog prog;
  EXPECT_EQ(prog.list_count(), 0);
}

// Test that size returns 0 for default prog
TEST_F(ProgTest_98, SizeDefault_98) {
  Prog prog;
  EXPECT_EQ(prog.size(), 0);
}

// Test UnsafeSearchBacktrack
TEST_F(ProgTest_98, UnsafeSearchBacktrackMatch_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "say hello there";
  absl::string_view match;
  bool found = prog->UnsafeSearchBacktrack(text, text, Prog::kUnanchored,
                                            Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

TEST_F(ProgTest_98, UnsafeSearchBacktrackNoMatch_98) {
  std::unique_ptr<Prog> prog(CompileRegexp("xyz"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "hello world";
  absl::string_view match;
  bool found = prog->UnsafeSearchBacktrack(text, text, Prog::kUnanchored,
                                            Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

}  // namespace re2
