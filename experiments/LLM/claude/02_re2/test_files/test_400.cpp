#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/sparse_set.h"
#include "re2/sparse_array.h"
#include <string>
#include <memory>

namespace re2 {

// Helper to compile a regex pattern into a Prog
static Prog* CompilePattern(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

class ProgTest_400 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Programs are cleaned up individually in each test
  }
};

// Test that a simple regex compiles and produces a non-null Prog
TEST_F(ProgTest_400, CompileSimplePattern_400) {
  Prog* prog = CompilePattern("hello");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test Dump produces a non-empty string for a simple pattern
TEST_F(ProgTest_400, DumpNonEmpty_400) {
  Prog* prog = CompilePattern("a");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test DumpUnanchored produces a non-empty string
TEST_F(ProgTest_400, DumpUnanchoredNonEmpty_400) {
  Prog* prog = CompilePattern("a");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test DumpByteMap produces a non-empty string
TEST_F(ProgTest_400, DumpByteMapNonEmpty_400) {
  Prog* prog = CompilePattern("a");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test that start() returns a valid index
TEST_F(ProgTest_400, StartIsValid_400) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_GE(prog->start(), 0);
  EXPECT_LT(prog->start(), prog->size());
  delete prog;
}

// Test that start_unanchored() returns a valid index
TEST_F(ProgTest_400, StartUnanchoredIsValid_400) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_GE(prog->start_unanchored(), 0);
  EXPECT_LT(prog->start_unanchored(), prog->size());
  delete prog;
}

// Test set_start and start
TEST_F(ProgTest_400, SetStartAndGet_400) {
  Prog* prog = CompilePattern("a");
  ASSERT_NE(prog, nullptr);
  int original = prog->start();
  prog->set_start(0);
  EXPECT_EQ(prog->start(), 0);
  prog->set_start(original);
  EXPECT_EQ(prog->start(), original);
  delete prog;
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_400, SetStartUnanchoredAndGet_400) {
  Prog* prog = CompilePattern("a");
  ASSERT_NE(prog, nullptr);
  int original = prog->start_unanchored();
  prog->set_start_unanchored(0);
  EXPECT_EQ(prog->start_unanchored(), 0);
  prog->set_start_unanchored(original);
  EXPECT_EQ(prog->start_unanchored(), original);
  delete prog;
}

// Test reversed default is false
TEST_F(ProgTest_400, ReversedDefaultFalse_400) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_FALSE(prog->reversed());
  delete prog;
}

// Test set_reversed
TEST_F(ProgTest_400, SetReversed_400) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  prog->set_reversed(true);
  EXPECT_TRUE(prog->reversed());
  prog->set_reversed(false);
  EXPECT_FALSE(prog->reversed());
  delete prog;
}

// Test anchor_start default
TEST_F(ProgTest_400, AnchorStartDefault_400) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  // For unanchored pattern, anchor_start should be false
  EXPECT_FALSE(prog->anchor_start());
  delete prog;
}

// Test anchor_end default
TEST_F(ProgTest_400, AnchorEndDefault_400) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_FALSE(prog->anchor_end());
  delete prog;
}

// Test set_anchor_start
TEST_F(ProgTest_400, SetAnchorStart_400) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  prog->set_anchor_start(true);
  EXPECT_TRUE(prog->anchor_start());
  prog->set_anchor_start(false);
  EXPECT_FALSE(prog->anchor_start());
  delete prog;
}

// Test set_anchor_end
TEST_F(ProgTest_400, SetAnchorEnd_400) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  prog->set_anchor_end(true);
  EXPECT_TRUE(prog->anchor_end());
  prog->set_anchor_end(false);
  EXPECT_FALSE(prog->anchor_end());
  delete prog;
}

// Test bytemap_range is positive
TEST_F(ProgTest_400, BytemapRangePositive_400) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  delete prog;
}

// Test bytemap is not null
TEST_F(ProgTest_400, BytemapNotNull_400) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_NE(prog->bytemap(), nullptr);
  delete prog;
}

// Test size is positive for compiled pattern
TEST_F(ProgTest_400, SizePositive_400) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test inst returns a non-null pointer for valid id
TEST_F(ProgTest_400, InstValidId_400) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  for (int i = 0; i < prog->size(); i++) {
    EXPECT_NE(prog->inst(i), nullptr);
  }
  delete prog;
}

// Test dfa_mem getter/setter
TEST_F(ProgTest_400, SetDfaMem_400) {
  Prog* prog = CompilePattern("a");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog->dfa_mem(), 1024 * 1024);
  delete prog;
}

// Test IsWordChar for typical chars
TEST_F(ProgTest_400, IsWordChar_400) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
}

// Test EmptyFlags at various positions
TEST_F(ProgTest_400, EmptyFlagsBeginning_400) {
  std::string text = "hello world";
  absl::string_view sv(text);
  uint32_t flags = Prog::EmptyFlags(sv, sv.data());
  // At the beginning of text, kEmptyBeginText and kEmptyBeginLine should be set
  EXPECT_NE(flags & kEmptyBeginText, 0u);
  EXPECT_NE(flags & kEmptyBeginLine, 0u);
}

TEST_F(ProgTest_400, EmptyFlagsEnd_400) {
  std::string text = "hello";
  absl::string_view sv(text);
  uint32_t flags = Prog::EmptyFlags(sv, sv.data() + sv.size());
  // At end of text, kEmptyEndText and kEmptyEndLine should be set
  EXPECT_NE(flags & kEmptyEndText, 0u);
  EXPECT_NE(flags & kEmptyEndLine, 0u);
}

TEST_F(ProgTest_400, EmptyFlagsMiddle_400) {
  std::string text = "hello";
  absl::string_view sv(text);
  uint32_t flags = Prog::EmptyFlags(sv, sv.data() + 2);
  // In the middle, neither begin nor end text
  EXPECT_EQ(flags & kEmptyBeginText, 0u);
  EXPECT_EQ(flags & kEmptyEndText, 0u);
}

// Test SearchNFA with anchored match
TEST_F(ProgTest_400, SearchNFAAnchored_400) {
  Prog* prog = CompilePattern("hello");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
  delete prog;
}

// Test SearchNFA with no match
TEST_F(ProgTest_400, SearchNFANoMatch_400) {
  Prog* prog = CompilePattern("xyz");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  delete prog;
}

// Test SearchNFA unanchored
TEST_F(ProgTest_400, SearchNFAUnanchored_400) {
  Prog* prog = CompilePattern("world");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "world");
  delete prog;
}

// Test SearchNFA with empty pattern
TEST_F(ProgTest_400, SearchNFAEmptyPattern_400) {
  Prog* prog = CompilePattern("");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("hello");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0u);
  delete prog;
}

// Test PossibleMatchRange
TEST_F(ProgTest_400, PossibleMatchRange_400) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  bool ok = prog->PossibleMatchRange(&min_match, &max_match, 10);
  EXPECT_TRUE(ok);
  EXPECT_LE(min_match, max_match);
  delete prog;
}

// Test PossibleMatchRange with wildcard
TEST_F(ProgTest_400, PossibleMatchRangeWildcard_400) {
  Prog* prog = CompilePattern("a.*z");
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  bool ok = prog->PossibleMatchRange(&min_match, &max_match, 10);
  EXPECT_TRUE(ok);
  delete prog;
}

// Test Inst::Dump for ByteRange instruction
TEST_F(ProgTest_400, InstDumpNotEmpty_400) {
  Prog* prog = CompilePattern("a");
  ASSERT_NE(prog, nullptr);
  for (int i = 0; i < prog->size(); i++) {
    Prog::Inst* ip = prog->inst(i);
    std::string dump = ip->Dump();
    EXPECT_FALSE(dump.empty());
  }
  delete prog;
}

// Test inst_count for various opcodes
TEST_F(ProgTest_400, InstCountNonNegative_400) {
  Prog* prog = CompilePattern("(a|b)*c");
  ASSERT_NE(prog, nullptr);
  for (int op = 0; op < kNumInst; op++) {
    EXPECT_GE(prog->inst_count(static_cast<InstOp>(op)), 0);
  }
  delete prog;
}

// Test Flatten
TEST_F(ProgTest_400, FlattenDoesNotCrash_400) {
  Prog* prog = CompilePattern("(a|b)+c");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // After flatten, the program should still be functional
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test Optimize
TEST_F(ProgTest_400, OptimizeDoesNotCrash_400) {
  Prog* prog = CompilePattern("abc|def");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test IsOnePass
TEST_F(ProgTest_400, IsOnePassSimple_400) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  // Simple literal pattern should be one-pass
  bool onepass = prog->IsOnePass();
  // We just verify it doesn't crash; the result depends on the pattern
  (void)onepass;
  delete prog;
}

// Test complex pattern compilation
TEST_F(ProgTest_400, ComplexPatternCompiles_400) {
  Prog* prog = CompilePattern("(foo|bar)+(baz)?[0-9]{2,4}");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test Dump output contains instruction info
TEST_F(ProgTest_400, DumpContainsInstructionInfo_400) {
  Prog* prog = CompilePattern("a");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  // Dump should contain some numbers (instruction indices)
  bool has_digit = false;
  for (char c : dump) {
    if (c >= '0' && c <= '9') {
      has_digit = true;
      break;
    }
  }
  EXPECT_TRUE(has_digit);
  delete prog;
}

// Test Inst opcode
TEST_F(ProgTest_400, InstOpcodeValid_400) {
  Prog* prog = CompilePattern("a");
  ASSERT_NE(prog, nullptr);
  for (int i = 0; i < prog->size(); i++) {
    Prog::Inst* ip = prog->inst(i);
    InstOp op = ip->opcode();
    EXPECT_GE(static_cast<int>(op), 0);
    EXPECT_LT(static_cast<int>(op), kNumInst);
  }
  delete prog;
}

// Test that a match instruction has valid match_id
TEST_F(ProgTest_400, MatchInstruction_400) {
  Prog* prog = CompilePattern("hello");
  ASSERT_NE(prog, nullptr);
  bool found_match = false;
  for (int i = 0; i < prog->size(); i++) {
    Prog::Inst* ip = prog->inst(i);
    if (ip->opcode() == kInstMatch) {
      found_match = true;
      EXPECT_GE(ip->match_id(), 0);
    }
  }
  EXPECT_TRUE(found_match);
  delete prog;
}

// Test Inst out() for non-fail instructions
TEST_F(ProgTest_400, InstOutValid_400) {
  Prog* prog = CompilePattern("ab");
  ASSERT_NE(prog, nullptr);
  for (int i = 0; i < prog->size(); i++) {
    Prog::Inst* ip = prog->inst(i);
    if (ip->opcode() != kInstFail && ip->opcode() != kInstMatch) {
      int out = ip->out();
      EXPECT_GE(out, 0);
    }
  }
  delete prog;
}

// Test can_prefix_accel
TEST_F(ProgTest_400, CanPrefixAccel_400) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  // Just ensure it doesn't crash
  bool accel = prog->can_prefix_accel();
  (void)accel;
  delete prog;
}

// Test Fanout
TEST_F(ProgTest_400, FanoutDoesNotCrash_400) {
  Prog* prog = CompilePattern("(a|b|c)d");
  ASSERT_NE(prog, nullptr);
  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);
  delete prog;
}

// Test anchored pattern with ^ 
TEST_F(ProgTest_400, AnchoredPatternStart_400) {
  Prog* prog = CompilePattern("^abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->anchor_start());
  delete prog;
}

// Test anchored pattern with $
TEST_F(ProgTest_400, AnchoredPatternEnd_400) {
  Prog* prog = CompilePattern("abc$");
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->anchor_end());
  delete prog;
}

// Test searching empty text
TEST_F(ProgTest_400, SearchEmptyText_400) {
  Prog* prog = CompilePattern("a");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  delete prog;
}

// Test searching empty text with empty pattern
TEST_F(ProgTest_400, SearchEmptyTextEmptyPattern_400) {
  Prog* prog = CompilePattern("");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0u);
  delete prog;
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_400, TestingOnlySetDfaBail_400) {
  // Just ensure this doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test SearchNFA with capture groups
TEST_F(ProgTest_400, SearchNFAWithCaptures_400) {
  Prog* prog = CompilePattern("(hel)(lo)");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("hello world");
  absl::string_view matches[3];
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, matches, 3);
  EXPECT_TRUE(found);
  EXPECT_EQ(matches[0], "hello");
  EXPECT_EQ(matches[1], "hel");
  EXPECT_EQ(matches[2], "lo");
  delete prog;
}

// Test ComputeByteMap doesn't crash when called
TEST_F(ProgTest_400, ComputeByteMapDoesNotCrash_400) {
  Prog* prog = CompilePattern("[a-z]+");
  ASSERT_NE(prog, nullptr);
  // ComputeByteMap is typically called during compilation, but we can call it again
  prog->ComputeByteMap();
  EXPECT_GT(prog->bytemap_range(), 0);
  delete prog;
}

// Test character class patterns
TEST_F(ProgTest_400, CharClassPattern_400) {
  Prog* prog = CompilePattern("[abc]");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("b");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "b");
  delete prog;
}

// Test no match with character class
TEST_F(ProgTest_400, CharClassNoMatch_400) {
  Prog* prog = CompilePattern("[abc]");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("d");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  delete prog;
}

// Test Inst::InitAlt
TEST_F(ProgTest_400, InstInitAlt_400) {
  Prog::Inst inst;
  inst.InitAlt(1, 2);
  EXPECT_EQ(inst.opcode(), kInstAlt);
  EXPECT_EQ(inst.out(), 1);
  EXPECT_EQ(inst.out1(), 2);
}

// Test Inst::InitByteRange
TEST_F(ProgTest_400, InstInitByteRange_400) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 0, 5);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.lo(), 'a');
  EXPECT_EQ(inst.hi(), 'z');
  EXPECT_EQ(inst.foldcase(), 0);
  EXPECT_EQ(inst.out(), 5);
}

// Test Inst::InitCapture
TEST_F(ProgTest_400, InstInitCapture_400) {
  Prog::Inst inst;
  inst.InitCapture(3, 7);
  EXPECT_EQ(inst.opcode(), kInstCapture);
  EXPECT_EQ(inst.cap(), 3);
  EXPECT_EQ(inst.out(), 7);
}

// Test Inst::InitMatch
TEST_F(ProgTest_400, InstInitMatch_400) {
  Prog::Inst inst;
  inst.InitMatch(42);
  EXPECT_EQ(inst.opcode(), kInstMatch);
  EXPECT_EQ(inst.match_id(), 42);
}

// Test Inst::InitNop
TEST_F(ProgTest_400, InstInitNop_400) {
  Prog::Inst inst;
  inst.InitNop(10);
  EXPECT_EQ(inst.opcode(), kInstNop);
  EXPECT_EQ(inst.out(), 10);
}

// Test Inst::InitFail
TEST_F(ProgTest_400, InstInitFail_400) {
  Prog::Inst inst;
  inst.InitFail();
  EXPECT_EQ(inst.opcode(), kInstFail);
}

// Test Inst::Matches for ByteRange
TEST_F(ProgTest_400, InstMatchesByteRange_400) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 0, 0);
  EXPECT_TRUE(inst.Matches('a'));
  EXPECT_TRUE(inst.Matches('m'));
  EXPECT_TRUE(inst.Matches('z'));
  EXPECT_FALSE(inst.Matches('A'));
  EXPECT_FALSE(inst.Matches('0'));
}

// Test Inst::Matches with foldcase
TEST_F(ProgTest_400, InstMatchesFoldcase_400) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 1, 0);
  EXPECT_TRUE(inst.Matches('a'));
  EXPECT_TRUE(inst.Matches('A'));
  EXPECT_TRUE(inst.Matches('z'));
  EXPECT_TRUE(inst.Matches('Z'));
}

// Test Inst::Dump produces non-empty for various types
TEST_F(ProgTest_400, InstDumpAlt_400) {
  Prog::Inst inst;
  inst.InitAlt(1, 2);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgTest_400, InstDumpMatch_400) {
  Prog::Inst inst;
  inst.InitMatch(0);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgTest_400, InstDumpFail_400) {
  Prog::Inst inst;
  inst.InitFail();
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgTest_400, InstDumpNop_400) {
  Prog::Inst inst;
  inst.InitNop(0);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

}  // namespace re2
