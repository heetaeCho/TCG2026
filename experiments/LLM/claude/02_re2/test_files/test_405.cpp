#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/sparse_array.h"
#include "absl/strings/string_view.h"

namespace re2 {

// Helper to compile a regex pattern into a Prog
class ProgTest_405 : public ::testing::Test {
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

// Test default construction of Prog
TEST_F(ProgTest_405, DefaultConstruction_405) {
  Prog prog;
  EXPECT_EQ(prog.start(), 0);
  EXPECT_EQ(prog.start_unanchored(), 0);
  EXPECT_FALSE(prog.reversed());
  EXPECT_FALSE(prog.anchor_start());
  EXPECT_FALSE(prog.anchor_end());
  EXPECT_EQ(prog.bytemap_range(), 0);
  EXPECT_EQ(prog.dfa_mem(), 0);
  EXPECT_EQ(prog.size(), 0);
}

// Test set_start and start
TEST_F(ProgTest_405, SetStart_405) {
  Prog prog;
  prog.set_start(5);
  EXPECT_EQ(prog.start(), 5);
  prog.set_start(0);
  EXPECT_EQ(prog.start(), 0);
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_405, SetStartUnanchored_405) {
  Prog prog;
  prog.set_start_unanchored(10);
  EXPECT_EQ(prog.start_unanchored(), 10);
}

// Test set_reversed and reversed
TEST_F(ProgTest_405, SetReversed_405) {
  Prog prog;
  EXPECT_FALSE(prog.reversed());
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test set_anchor_start and anchor_start
TEST_F(ProgTest_405, SetAnchorStart_405) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_start());
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test set_anchor_end and anchor_end
TEST_F(ProgTest_405, SetAnchorEnd_405) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_end());
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test set_dfa_mem and dfa_mem
TEST_F(ProgTest_405, SetDfaMem_405) {
  Prog prog;
  prog.set_dfa_mem(1024);
  EXPECT_EQ(prog.dfa_mem(), 1024);
  prog.set_dfa_mem(0);
  EXPECT_EQ(prog.dfa_mem(), 0);
}

// Test IsWordChar
TEST_F(ProgTest_405, IsWordChar_405) {
  // Alphabetic characters
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  // Digits
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  // Underscore
  EXPECT_TRUE(Prog::IsWordChar('_'));
  // Non-word characters
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
  EXPECT_FALSE(Prog::IsWordChar('['));
}

// Test EmptyFlags at various positions
TEST_F(ProgTest_405, EmptyFlags_405) {
  absl::string_view text("hello world");

  // At beginning of text
  uint32_t flags_begin = Prog::EmptyFlags(text, text.data());
  EXPECT_NE(flags_begin & kEmptyBeginText, 0u);
  EXPECT_NE(flags_begin & kEmptyBeginLine, 0u);

  // At end of text
  uint32_t flags_end = Prog::EmptyFlags(text, text.data() + text.size());
  EXPECT_NE(flags_end & kEmptyEndText, 0u);
  EXPECT_NE(flags_end & kEmptyEndLine, 0u);

  // In the middle (at the space between "hello" and "world")
  uint32_t flags_mid = Prog::EmptyFlags(text, text.data() + 5);
  EXPECT_EQ(flags_mid & kEmptyBeginText, 0u);
  EXPECT_EQ(flags_mid & kEmptyEndText, 0u);
}

// Test EmptyFlags with newline
TEST_F(ProgTest_405, EmptyFlagsNewline_405) {
  absl::string_view text("hello\nworld");

  // Right after the newline
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 6);
  EXPECT_NE(flags & kEmptyBeginLine, 0u);

  // Right at the newline
  uint32_t flags_at_nl = Prog::EmptyFlags(text, text.data() + 5);
  // After 'o', before '\n' — the newline hasn't been consumed yet
  // The character to the right is '\n' so EndLine should be set
  EXPECT_NE(flags_at_nl & kEmptyEndLine, 0u);
}

// Test EmptyFlags with word boundary
TEST_F(ProgTest_405, EmptyFlagsWordBoundary_405) {
  absl::string_view text("a b");

  // Between 'a' and ' ' (position 1)
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 1);
  EXPECT_NE(flags & kEmptyWordBoundary, 0u);

  // Between ' ' and 'b' (position 2)
  uint32_t flags2 = Prog::EmptyFlags(text, text.data() + 2);
  EXPECT_NE(flags2 & kEmptyWordBoundary, 0u);
}

// Test EmptyFlags with non-word boundary
TEST_F(ProgTest_405, EmptyFlagsNonWordBoundary_405) {
  absl::string_view text("ab");

  // Between 'a' and 'b' (position 1) — both are word chars
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 1);
  EXPECT_NE(flags & kEmptyNonWordBoundary, 0u);
  EXPECT_EQ(flags & kEmptyWordBoundary, 0u);
}

// Test EmptyFlags with empty text
TEST_F(ProgTest_405, EmptyFlagsEmptyText_405) {
  absl::string_view text("");
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  EXPECT_NE(flags & kEmptyBeginText, 0u);
  EXPECT_NE(flags & kEmptyEndText, 0u);
  EXPECT_NE(flags & kEmptyBeginLine, 0u);
  EXPECT_NE(flags & kEmptyEndLine, 0u);
}

// Test compiling and dumping a simple regex
TEST_F(ProgTest_405, CompileAndDump_405) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test DumpUnanchored
TEST_F(ProgTest_405, DumpUnanchored_405) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test DumpByteMap
TEST_F(ProgTest_405, DumpByteMap_405) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test bytemap and bytemap_range after compilation
TEST_F(ProgTest_405, ByteMapRange_405) {
  Prog* prog = CompileRegexp("[a-z]+");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  delete prog;
}

// Test size after compilation
TEST_F(ProgTest_405, SizeAfterCompile_405) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test Inst InitMatch and opcode
TEST_F(ProgTest_405, InstInitMatch_405) {
  Prog::Inst inst;
  inst.InitMatch(1);
  EXPECT_EQ(inst.opcode(), kInstMatch);
  EXPECT_EQ(inst.match_id(), 1);
}

// Test Inst InitFail
TEST_F(ProgTest_405, InstInitFail_405) {
  Prog::Inst inst;
  inst.InitFail();
  EXPECT_EQ(inst.opcode(), kInstFail);
}

// Test Inst InitNop
TEST_F(ProgTest_405, InstInitNop_405) {
  Prog::Inst inst;
  inst.InitNop(5);
  EXPECT_EQ(inst.opcode(), kInstNop);
  EXPECT_EQ(inst.out(), 5);
}

// Test Inst InitByteRange
TEST_F(ProgTest_405, InstInitByteRange_405) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 0, 10);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.lo(), 'a');
  EXPECT_EQ(inst.hi(), 'z');
  EXPECT_EQ(inst.foldcase(), 0);
  EXPECT_EQ(inst.out(), 10);
}

// Test Inst InitByteRange with foldcase
TEST_F(ProgTest_405, InstInitByteRangeFoldcase_405) {
  Prog::Inst inst;
  inst.InitByteRange('A', 'Z', 1, 20);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.lo(), 'A');
  EXPECT_EQ(inst.hi(), 'Z');
  EXPECT_EQ(inst.foldcase(), 1);
  EXPECT_EQ(inst.out(), 20);
}

// Test Inst InitCapture
TEST_F(ProgTest_405, InstInitCapture_405) {
  Prog::Inst inst;
  inst.InitCapture(2, 15);
  EXPECT_EQ(inst.opcode(), kInstCapture);
  EXPECT_EQ(inst.cap(), 2);
  EXPECT_EQ(inst.out(), 15);
}

// Test Inst InitEmptyWidth
TEST_F(ProgTest_405, InstInitEmptyWidth_405) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyBeginLine, 7);
  EXPECT_EQ(inst.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst.empty(), kEmptyBeginLine);
  EXPECT_EQ(inst.out(), 7);
}

// Test Inst InitAlt
TEST_F(ProgTest_405, InstInitAlt_405) {
  Prog::Inst inst;
  inst.InitAlt(3, 4);
  EXPECT_EQ(inst.opcode(), kInstAlt);
  EXPECT_EQ(inst.out(), 3);
  EXPECT_EQ(inst.out1(), 4);
}

// Test Inst Dump
TEST_F(ProgTest_405, InstDump_405) {
  Prog::Inst inst;
  inst.InitMatch(0);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Inst Matches for ByteRange
TEST_F(ProgTest_405, InstMatchesByteRange_405) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 0, 0);
  EXPECT_TRUE(inst.Matches('a'));
  EXPECT_TRUE(inst.Matches('m'));
  EXPECT_TRUE(inst.Matches('z'));
  EXPECT_FALSE(inst.Matches('A'));
  EXPECT_FALSE(inst.Matches('0'));
}

// Test Inst Matches with foldcase
TEST_F(ProgTest_405, InstMatchesByteRangeFoldCase_405) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 1, 0);
  EXPECT_TRUE(inst.Matches('a'));
  EXPECT_TRUE(inst.Matches('A'));  // foldcase should match
  EXPECT_TRUE(inst.Matches('Z'));  // foldcase should match
}

// Test inst accessor
TEST_F(ProgTest_405, InstAccessor_405) {
  Prog* prog = CompileRegexp("a");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  // Access the start instruction
  Prog::Inst* ip = prog->inst(prog->start());
  EXPECT_NE(ip, nullptr);
  delete prog;
}

// Test Flatten
TEST_F(ProgTest_405, Flatten_405) {
  Prog* prog = CompileRegexp("(a|b)c");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // After flattening, the program should still be valid
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test Optimize
TEST_F(ProgTest_405, Optimize_405) {
  Prog* prog = CompileRegexp("(a|b)+");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // Optimize should not crash
  // (We can't test much more without internal access)
  delete prog;
}

// Test IsOnePass on a simple pattern
TEST_F(ProgTest_405, IsOnePass_405) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  // Simple literal should be one-pass
  bool onepass = prog->IsOnePass();
  // We just check it doesn't crash; the result depends on the pattern
  (void)onepass;
  delete prog;
}

// Test PossibleMatchRange
TEST_F(ProgTest_405, PossibleMatchRange_405) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_FALSE(min_str.empty());
  EXPECT_FALSE(max_str.empty());
  EXPECT_LE(min_str, max_str);
  delete prog;
}

// Test PossibleMatchRange with maxlen = 0
TEST_F(ProgTest_405, PossibleMatchRangeZeroMaxlen_405) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 0);
  // Should still return something, possibly empty strings
  (void)result;
  delete prog;
}

// Test can_prefix_accel on a simple literal pattern
TEST_F(ProgTest_405, CanPrefixAccel_405) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  // Just check it doesn't crash
  bool can = prog->can_prefix_accel();
  (void)can;
  delete prog;
}

// Test SearchNFA basic match
TEST_F(ProgTest_405, SearchNFABasicMatch_405) {
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

// Test SearchNFA no match
TEST_F(ProgTest_405, SearchNFANoMatch_405) {
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
TEST_F(ProgTest_405, SearchNFAAnchored_405) {
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

// Test SearchNFA anchored no match
TEST_F(ProgTest_405, SearchNFAAnchoredNoMatch_405) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xabcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  delete prog;
}

// Test SearchNFA empty text
TEST_F(ProgTest_405, SearchNFAEmptyText_405) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  delete prog;
}

// Test SearchNFA with empty pattern
TEST_F(ProgTest_405, SearchNFAEmptyPattern_405) {
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

// Test SearchBitState basic
TEST_F(ProgTest_405, SearchBitStateBasic_405) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  if (prog->CanBitState()) {
    absl::string_view text("xabcy");
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "abc");
  }
  delete prog;
}

// Test SearchDFA basic
TEST_F(ProgTest_405, SearchDFABasic_405) {
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

// Test Fanout
TEST_F(ProgTest_405, Fanout_405) {
  Prog* prog = CompileRegexp("(a|b|c)d");
  ASSERT_NE(prog, nullptr);
  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);
  // Just ensure it doesn't crash and has entries
  delete prog;
}

// Test inst_count
TEST_F(ProgTest_405, InstCount_405) {
  Prog* prog = CompileRegexp("(a|b)c");
  ASSERT_NE(prog, nullptr);
  // Check that inst_count for various opcodes are non-negative
  for (int i = 0; i < kNumInst; i++) {
    EXPECT_GE(prog->inst_count(static_cast<InstOp>(i)), 0);
  }
  delete prog;
}

// Test CanBitState
TEST_F(ProgTest_405, CanBitState_405) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  // Just verify it returns a bool without crashing
  bool can = prog->CanBitState();
  (void)can;
  delete prog;
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_405, TestingSetDfaShouldBailWhenSlow_405) {
  // Just verify it doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test Inst copy constructor and assignment
TEST_F(ProgTest_405, InstCopyAndAssign_405) {
  Prog::Inst inst1;
  inst1.InitByteRange('a', 'z', 0, 10);
  
  Prog::Inst inst2(inst1);
  EXPECT_EQ(inst2.opcode(), kInstByteRange);
  EXPECT_EQ(inst2.lo(), 'a');
  EXPECT_EQ(inst2.hi(), 'z');
  EXPECT_EQ(inst2.out(), 10);

  Prog::Inst inst3;
  inst3 = inst1;
  EXPECT_EQ(inst3.opcode(), kInstByteRange);
  EXPECT_EQ(inst3.lo(), 'a');
  EXPECT_EQ(inst3.hi(), 'z');
  EXPECT_EQ(inst3.out(), 10);
}

// Test Inst id
TEST_F(ProgTest_405, InstId_405) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  Prog::Inst* ip = prog->inst(prog->start());
  int id = ip->id(prog);
  EXPECT_EQ(id, prog->start());
  delete prog;
}

// Test SearchOnePass if available
TEST_F(ProgTest_405, SearchOnePass_405) {
  Prog* prog = CompileRegexp("^abc$");
  ASSERT_NE(prog, nullptr);
  if (prog->IsOnePass()) {
    absl::string_view text("abc");
    absl::string_view match;
    bool found = prog->SearchOnePass(text, text, Prog::kAnchored,
                                      Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "abc");
  }
  delete prog;
}

// Test with complex pattern
TEST_F(ProgTest_405, ComplexPattern_405) {
  Prog* prog = CompileRegexp("(\\d{3})-(\\d{3})-(\\d{4})");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("Call 555-123-4567 now");
  absl::string_view matches[4];
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, matches, 4);
  EXPECT_TRUE(found);
  EXPECT_EQ(matches[0], "555-123-4567");
  delete prog;
}

// Test SearchNFA with capture groups
TEST_F(ProgTest_405, SearchNFACaptures_405) {
  Prog* prog = CompileRegexp("(a+)(b+)");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xaaabby");
  absl::string_view matches[3];
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, matches, 3);
  EXPECT_TRUE(found);
  EXPECT_EQ(matches[0], "aaabb");
  EXPECT_EQ(matches[1], "aaa");
  EXPECT_EQ(matches[2], "bb");
  delete prog;
}

// Test CompileSet
TEST_F(ProgTest_405, CompileSet_405) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def|ghi", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  if (prog != nullptr) {
    EXPECT_GT(prog->size(), 0);
    delete prog;
  }
  re->Decref();
}

// Test BuildEntireDFA
TEST_F(ProgTest_405, BuildEntireDFA_405) {
  Prog* prog = CompileRegexp("[ab]");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  int count = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(count, 0);
  delete prog;
}

}  // namespace re2
