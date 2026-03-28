#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"

namespace re2 {

// Helper to compile a regex pattern into a Prog
class ProgTest_110 : public ::testing::Test {
 protected:
  Prog* CompileRegexp(const char* pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re == nullptr) return nullptr;
    Prog* prog = re->CompileToProg(0);
    re->Decref();
    return prog;
  }
};

// Test default constructor initializes fields properly
TEST_F(ProgTest_110, DefaultConstructor_110) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_start());
  EXPECT_FALSE(prog.anchor_end());
  EXPECT_FALSE(prog.reversed());
  EXPECT_EQ(prog.start(), 0);
  EXPECT_EQ(prog.start_unanchored(), 0);
  EXPECT_EQ(prog.size(), 0);
  EXPECT_EQ(prog.bytemap_range(), 0);
  EXPECT_EQ(prog.dfa_mem(), 0);
}

// Test set_start and start
TEST_F(ProgTest_110, SetAndGetStart_110) {
  Prog prog;
  prog.set_start(42);
  EXPECT_EQ(prog.start(), 42);
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_110, SetAndGetStartUnanchored_110) {
  Prog prog;
  prog.set_start_unanchored(99);
  EXPECT_EQ(prog.start_unanchored(), 99);
}

// Test set_anchor_start and anchor_start
TEST_F(ProgTest_110, SetAndGetAnchorStart_110) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_start());
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test set_anchor_end and anchor_end
TEST_F(ProgTest_110, SetAndGetAnchorEnd_110) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_end());
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test set_reversed and reversed
TEST_F(ProgTest_110, SetAndGetReversed_110) {
  Prog prog;
  EXPECT_FALSE(prog.reversed());
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test set_dfa_mem and dfa_mem
TEST_F(ProgTest_110, SetAndGetDfaMem_110) {
  Prog prog;
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog.dfa_mem(), 1024 * 1024);
}

// Test IsWordChar for various characters
TEST_F(ProgTest_110, IsWordChar_110) {
  // Alphanumeric and underscore should be word chars
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));

  // Non-word chars
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
  EXPECT_FALSE(Prog::IsWordChar(0));
}

// Test Dump on a compiled program
TEST_F(ProgTest_110, Dump_110) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test DumpUnanchored on a compiled program
TEST_F(ProgTest_110, DumpUnanchored_110) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test DumpByteMap on a compiled program
TEST_F(ProgTest_110, DumpByteMap_110) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test that a compiled program has positive size
TEST_F(ProgTest_110, CompiledProgramHasPositiveSize_110) {
  Prog* prog = CompileRegexp("a+b*c?");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test bytemap_range for a compiled program
TEST_F(ProgTest_110, BytemapRange_110) {
  Prog* prog = CompileRegexp("[a-z]+");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);
  delete prog;
}

// Test bytemap returns non-null for compiled program
TEST_F(ProgTest_110, BytemapNonNull_110) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  EXPECT_NE(prog->bytemap(), nullptr);
  delete prog;
}

// Test EmptyFlags at beginning of text
TEST_F(ProgTest_110, EmptyFlagsBeginning_110) {
  absl::string_view text("hello");
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // At the beginning, should have kEmptyBeginText and kEmptyBeginLine set
  EXPECT_NE(flags & kEmptyBeginText, 0u);
  EXPECT_NE(flags & kEmptyBeginLine, 0u);
}

// Test EmptyFlags at end of text
TEST_F(ProgTest_110, EmptyFlagsEnd_110) {
  absl::string_view text("hello");
  uint32_t flags = Prog::EmptyFlags(text, text.data() + text.size());
  // At the end, should have kEmptyEndText and kEmptyEndLine set
  EXPECT_NE(flags & kEmptyEndText, 0u);
  EXPECT_NE(flags & kEmptyEndLine, 0u);
}

// Test EmptyFlags in middle of text
TEST_F(ProgTest_110, EmptyFlagsMiddle_110) {
  absl::string_view text("hello");
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 2);
  // In the middle, should not have begin/end text flags
  EXPECT_EQ(flags & kEmptyBeginText, 0u);
  EXPECT_EQ(flags & kEmptyEndText, 0u);
}

// Test EmptyFlags at word boundary
TEST_F(ProgTest_110, EmptyFlagsWordBoundary_110) {
  absl::string_view text("a ");
  // At position 1, between 'a' and ' ', should have word boundary
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 1);
  EXPECT_NE(flags & kEmptyWordBoundary, 0u);
}

// Test EmptyFlags at non-word boundary
TEST_F(ProgTest_110, EmptyFlagsNonWordBoundary_110) {
  absl::string_view text("ab");
  // Between 'a' and 'b', should have non-word boundary
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 1);
  EXPECT_NE(flags & kEmptyNonWordBoundary, 0u);
}

// Test PossibleMatchRange
TEST_F(ProgTest_110, PossibleMatchRange_110) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_str, max_str);
  delete prog;
}

// Test PossibleMatchRange with maxlen of 0
TEST_F(ProgTest_110, PossibleMatchRangeZeroMaxlen_110) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 0);
  // The function may or may not succeed; we just verify it doesn't crash
  (void)result;
  delete prog;
}

// Test SearchNFA with simple pattern
TEST_F(ProgTest_110, SearchNFA_SimpleMatch_110) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xabcy");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
  delete prog;
}

// Test SearchNFA with no match
TEST_F(ProgTest_110, SearchNFA_NoMatch_110) {
  Prog* prog = CompileRegexp("xyz");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  delete prog;
}

// Test SearchNFA anchored
TEST_F(ProgTest_110, SearchNFA_Anchored_110) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
  delete prog;
}

// Test SearchNFA anchored fails when not at start
TEST_F(ProgTest_110, SearchNFA_AnchoredNoMatch_110) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xabcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  delete prog;
}

// Test Inst initialization with ByteRange
TEST_F(ProgTest_110, InstInitByteRange_110) {
  Prog::Inst inst;
  inst.InitByteRange(0x61, 0x7A, 0, 5);  // a-z, no foldcase, out=5
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.lo(), 0x61);
  EXPECT_EQ(inst.hi(), 0x7A);
  EXPECT_EQ(inst.foldcase(), 0);
  EXPECT_EQ(inst.out(), 5);
}

// Test Inst initialization with Match
TEST_F(ProgTest_110, InstInitMatch_110) {
  Prog::Inst inst;
  inst.InitMatch(42);
  EXPECT_EQ(inst.opcode(), kInstMatch);
  EXPECT_EQ(inst.match_id(), 42);
}

// Test Inst initialization with Nop
TEST_F(ProgTest_110, InstInitNop_110) {
  Prog::Inst inst;
  inst.InitNop(10);
  EXPECT_EQ(inst.opcode(), kInstNop);
  EXPECT_EQ(inst.out(), 10);
}

// Test Inst initialization with Fail
TEST_F(ProgTest_110, InstInitFail_110) {
  Prog::Inst inst;
  inst.InitFail();
  EXPECT_EQ(inst.opcode(), kInstFail);
}

// Test Inst initialization with Alt
TEST_F(ProgTest_110, InstInitAlt_110) {
  Prog::Inst inst;
  inst.InitAlt(3, 7);
  EXPECT_EQ(inst.opcode(), kInstAlt);
  EXPECT_EQ(inst.out(), 3);
  EXPECT_EQ(inst.out1(), 7);
}

// Test Inst initialization with Capture
TEST_F(ProgTest_110, InstInitCapture_110) {
  Prog::Inst inst;
  inst.InitCapture(2, 8);
  EXPECT_EQ(inst.opcode(), kInstCapture);
  EXPECT_EQ(inst.cap(), 2);
  EXPECT_EQ(inst.out(), 8);
}

// Test Inst initialization with EmptyWidth
TEST_F(ProgTest_110, InstInitEmptyWidth_110) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyBeginLine, 4);
  EXPECT_EQ(inst.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst.empty(), kEmptyBeginLine);
  EXPECT_EQ(inst.out(), 4);
}

// Test Inst Dump
TEST_F(ProgTest_110, InstDump_110) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 0, 5);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Inst Matches for ByteRange
TEST_F(ProgTest_110, InstMatchesByteRange_110) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 0, 5);
  EXPECT_TRUE(inst.Matches('a'));
  EXPECT_TRUE(inst.Matches('m'));
  EXPECT_TRUE(inst.Matches('z'));
  EXPECT_FALSE(inst.Matches('A'));
  EXPECT_FALSE(inst.Matches('0'));
}

// Test Inst Matches boundary cases for ByteRange
TEST_F(ProgTest_110, InstMatchesByteRangeBoundary_110) {
  Prog::Inst inst;
  inst.InitByteRange(0, 255, 0, 5);
  EXPECT_TRUE(inst.Matches(0));
  EXPECT_TRUE(inst.Matches(255));
  EXPECT_TRUE(inst.Matches(128));
}

// Test Inst Matches single char range
TEST_F(ProgTest_110, InstMatchesSingleCharRange_110) {
  Prog::Inst inst;
  inst.InitByteRange('x', 'x', 0, 5);
  EXPECT_TRUE(inst.Matches('x'));
  EXPECT_FALSE(inst.Matches('w'));
  EXPECT_FALSE(inst.Matches('y'));
}

// Test can_prefix_accel on default Prog
TEST_F(ProgTest_110, CanPrefixAccelDefault_110) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_110, TestingOnlySetDfaShouldBail_110) {
  // Just verify this doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test Optimize on a compiled program doesn't crash
TEST_F(ProgTest_110, Optimize_110) {
  Prog* prog = CompileRegexp("a+b+c+");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  // After optimization, the program should still be valid
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test Flatten on a compiled program
TEST_F(ProgTest_110, Flatten_110) {
  Prog* prog = CompileRegexp("(a|b)+c");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test IsOnePass
TEST_F(ProgTest_110, IsOnePass_SimplePattern_110) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  // Simple literal pattern should be one-pass
  bool onepass = prog->IsOnePass();
  // Just verify it doesn't crash; the result depends on implementation
  (void)onepass;
  delete prog;
}

// Test SearchBitState
TEST_F(ProgTest_110, SearchBitState_Match_110) {
  Prog* prog = CompileRegexp("a(b+)c");
  ASSERT_NE(prog, nullptr);
  if (prog->CanBitState()) {
    absl::string_view text("xabbcy");
    absl::string_view match[2];
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, match, 2);
    EXPECT_TRUE(found);
    EXPECT_EQ(match[0], "abbc");
    EXPECT_EQ(match[1], "bb");
  }
  delete prog;
}

// Test SearchBitState no match
TEST_F(ProgTest_110, SearchBitState_NoMatch_110) {
  Prog* prog = CompileRegexp("xyz");
  ASSERT_NE(prog, nullptr);
  if (prog->CanBitState()) {
    absl::string_view text("abcdef");
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_FALSE(found);
  }
  delete prog;
}

// Test CompileSet
TEST_F(ProgTest_110, CompileSet_110) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def|ghi", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test empty pattern
TEST_F(ProgTest_110, EmptyPattern_110) {
  Prog* prog = CompileRegexp("");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abc");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0u);
  delete prog;
}

// Test SearchDFA
TEST_F(ProgTest_110, SearchDFA_Match_110) {
  Prog* prog = CompileRegexp("abc");
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
  delete prog;
}

// Test SearchDFA no match
TEST_F(ProgTest_110, SearchDFA_NoMatch_110) {
  Prog* prog = CompileRegexp("xyz");
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
  delete prog;
}

// Test inst access on compiled program
TEST_F(ProgTest_110, InstAccess_110) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  // Access instruction at start
  Prog::Inst* inst = prog->inst(prog->start());
  EXPECT_NE(inst, nullptr);
  // Verify opcode is a valid instruction type
  EXPECT_GE(inst->opcode(), kInstAlt);
  EXPECT_LT(inst->opcode(), kNumInst);
  delete prog;
}

// Test Inst with foldcase
TEST_F(ProgTest_110, InstByteRangeFoldcase_110) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 1, 5);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.foldcase(), 1);
  EXPECT_EQ(inst.lo(), 'a');
  EXPECT_EQ(inst.hi(), 'z');
}

// Test inst_count
TEST_F(ProgTest_110, InstCount_110) {
  Prog* prog = CompileRegexp("a+b+");
  ASSERT_NE(prog, nullptr);
  // Total inst_count across all types should equal size
  int total = 0;
  for (int i = 0; i < kNumInst; i++) {
    int count = prog->inst_count(static_cast<InstOp>(i));
    EXPECT_GE(count, 0);
    total += count;
  }
  EXPECT_EQ(total, prog->size());
  delete prog;
}

// Test Fanout
TEST_F(ProgTest_110, Fanout_110) {
  Prog* prog = CompileRegexp("(a|b|c)+");
  ASSERT_NE(prog, nullptr);
  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);
  // Just verify it doesn't crash and produces some data
  delete prog;
}

// Test CanBitState
TEST_F(ProgTest_110, CanBitState_110) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  // Small patterns should be able to use bit state
  bool can = prog->CanBitState();
  (void)can;  // Just verify it doesn't crash
  delete prog;
}

// Test ConfigurePrefixAccel and can_prefix_accel
TEST_F(ProgTest_110, ConfigurePrefixAccel_110) {
  Prog* prog = CompileRegexp("abc.*xyz");
  ASSERT_NE(prog, nullptr);
  prog->ConfigurePrefixAccel("abc", false);
  // After configuration, prefix accel may or may not be available
  // depending on the implementation, but it shouldn't crash
  delete prog;
}

// Test PrefixAccel on null data
TEST_F(ProgTest_110, PrefixAccelNullData_110) {
  Prog prog;
  // Without configuration, can_prefix_accel should be false
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test EmptyFlags with empty text
TEST_F(ProgTest_110, EmptyFlagsEmptyText_110) {
  absl::string_view text("");
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // For empty text, begin and end text should both be set
  EXPECT_NE(flags & kEmptyBeginText, 0u);
  EXPECT_NE(flags & kEmptyEndText, 0u);
  EXPECT_NE(flags & kEmptyBeginLine, 0u);
  EXPECT_NE(flags & kEmptyEndLine, 0u);
}

// Test EmptyFlags at newline boundary
TEST_F(ProgTest_110, EmptyFlagsNewline_110) {
  absl::string_view text("a\nb");
  // At position after newline
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 2);
  EXPECT_NE(flags & kEmptyBeginLine, 0u);
}

// Test SearchOnePass if one-pass
TEST_F(ProgTest_110, SearchOnePass_110) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  if (prog->IsOnePass()) {
    absl::string_view text("xabcy");
    absl::string_view match;
    bool found = prog->SearchOnePass(text, text, Prog::kUnanchored,
                                      Prog::kFirstMatch, &match, 1);
    // One-pass search is typically anchored; unanchored may not work
    // Just verify it doesn't crash
    (void)found;
  }
  delete prog;
}

// Test BuildEntireDFA
TEST_F(ProgTest_110, BuildEntireDFA_110) {
  Prog* prog = CompileRegexp("[a-c]");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  int num_states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);
  delete prog;
}

}  // namespace re2
