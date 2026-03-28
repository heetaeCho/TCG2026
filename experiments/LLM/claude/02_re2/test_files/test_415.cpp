#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/sparse_array.h"
#include "re2/sparse_set.h"
#include <string>
#include <vector>
#include <memory>

namespace re2 {

// Helper to compile a regex pattern into a Prog
static Prog* CompileRegex(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

class ProgTest_415 : public ::testing::Test {
 protected:
  void TearDown() override {
    for (auto* p : progs_) {
      delete p;
    }
  }
  
  Prog* MakeProg(const char* pattern) {
    Prog* p = CompileRegex(pattern);
    if (p) progs_.push_back(p);
    return p;
  }
  
  std::vector<Prog*> progs_;
};

// Test basic Prog construction
TEST_F(ProgTest_415, DefaultConstruction_415) {
  Prog prog;
  EXPECT_EQ(prog.start(), 0);
  EXPECT_EQ(prog.start_unanchored(), 0);
  EXPECT_FALSE(prog.reversed());
  EXPECT_FALSE(prog.anchor_start());
  EXPECT_FALSE(prog.anchor_end());
}

// Test Dump produces non-empty output for a simple regex
TEST_F(ProgTest_415, DumpSimpleRegex_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

// Test DumpUnanchored produces non-empty output
TEST_F(ProgTest_415, DumpUnanchored_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

// Test DumpByteMap produces non-empty output
TEST_F(ProgTest_415, DumpByteMap_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
}

// Test size() returns positive for a compiled program
TEST_F(ProgTest_415, SizePositive_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
}

// Test bytemap_range returns positive
TEST_F(ProgTest_415, BytemapRange_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
}

// Test bytemap is not null
TEST_F(ProgTest_415, BytemapNotNull_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_NE(prog->bytemap(), nullptr);
}

// Test set_start and start
TEST_F(ProgTest_415, SetStart_415) {
  Prog prog;
  prog.set_start(5);
  EXPECT_EQ(prog.start(), 5);
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_415, SetStartUnanchored_415) {
  Prog prog;
  prog.set_start_unanchored(7);
  EXPECT_EQ(prog.start_unanchored(), 7);
}

// Test set_reversed and reversed
TEST_F(ProgTest_415, SetReversed_415) {
  Prog prog;
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test set_anchor_start and anchor_start
TEST_F(ProgTest_415, SetAnchorStart_415) {
  Prog prog;
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test set_anchor_end and anchor_end
TEST_F(ProgTest_415, SetAnchorEnd_415) {
  Prog prog;
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test set_dfa_mem and dfa_mem
TEST_F(ProgTest_415, SetDfaMem_415) {
  Prog prog;
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog.dfa_mem(), 1024 * 1024);
}

// Test EmptyFlags
TEST_F(ProgTest_415, EmptyFlagsAtBeginning_415) {
  std::string text = "hello";
  absl::string_view sv(text);
  uint32_t flags = Prog::EmptyFlags(sv, sv.data());
  // At the beginning of text, kEmptyBeginText and kEmptyBeginLine should be set
  EXPECT_NE(flags & kEmptyBeginText, 0u);
  EXPECT_NE(flags & kEmptyBeginLine, 0u);
}

TEST_F(ProgTest_415, EmptyFlagsAtEnd_415) {
  std::string text = "hello";
  absl::string_view sv(text);
  uint32_t flags = Prog::EmptyFlags(sv, sv.data() + sv.size());
  // At the end, kEmptyEndText and kEmptyEndLine should be set
  EXPECT_NE(flags & kEmptyEndText, 0u);
  EXPECT_NE(flags & kEmptyEndLine, 0u);
}

// Test IsWordChar
TEST_F(ProgTest_415, IsWordCharAlpha_415) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
}

TEST_F(ProgTest_415, IsWordCharDigit_415) {
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
}

TEST_F(ProgTest_415, IsWordCharUnderscore_415) {
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

TEST_F(ProgTest_415, IsWordCharNonWord_415) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
}

// Test Flatten
TEST_F(ProgTest_415, FlattenSimple_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // After flattening, the program should still work.
  // Size should be positive.
  EXPECT_GT(prog->size(), 0);
}

// Test Flatten with alternation
TEST_F(ProgTest_415, FlattenAlternation_415) {
  Prog* prog = MakeProg("a|b|c");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  EXPECT_GT(prog->size(), 0);
}

// Test Optimize
TEST_F(ProgTest_415, OptimizeSimple_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  // After optimizing, program should still be valid
  EXPECT_GT(prog->size(), 0);
}

// Test PossibleMatchRange
TEST_F(ProgTest_415, PossibleMatchRangeSimple_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool ok = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(ok);
  EXPECT_LE(min_str, max_str);
}

TEST_F(ProgTest_415, PossibleMatchRangeExact_415) {
  Prog* prog = MakeProg("^abc$");
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool ok = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(ok);
  EXPECT_EQ(min_str, "abc");
}

TEST_F(ProgTest_415, PossibleMatchRangeMaxLen_415) {
  Prog* prog = MakeProg(".*");
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool ok = prog->PossibleMatchRange(&min_str, &max_str, 5);
  // Should succeed even for .*
  // The result depends on implementation
  (void)ok;
}

// Test SearchNFA for a matching pattern
TEST_F(ProgTest_415, SearchNFAMatch_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xxxabcyyy");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

// Test SearchNFA for a non-matching pattern
TEST_F(ProgTest_415, SearchNFANoMatch_415) {
  Prog* prog = MakeProg("xyz");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test SearchNFA anchored
TEST_F(ProgTest_415, SearchNFAAnchored_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgTest_415, SearchNFAAnchoredNoMatch_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xabcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test Inst initialization and accessors
TEST_F(ProgTest_415, InstInitByteRange_415) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 0, 5);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.lo(), 'a');
  EXPECT_EQ(inst.hi(), 'z');
  EXPECT_EQ(inst.foldcase(), 0);
  EXPECT_EQ(inst.out(), 5);
}

TEST_F(ProgTest_415, InstInitMatch_415) {
  Prog::Inst inst;
  inst.InitMatch(42);
  EXPECT_EQ(inst.opcode(), kInstMatch);
  EXPECT_EQ(inst.match_id(), 42);
}

TEST_F(ProgTest_415, InstInitNop_415) {
  Prog::Inst inst;
  inst.InitNop(10);
  EXPECT_EQ(inst.opcode(), kInstNop);
  EXPECT_EQ(inst.out(), 10);
}

TEST_F(ProgTest_415, InstInitFail_415) {
  Prog::Inst inst;
  inst.InitFail();
  EXPECT_EQ(inst.opcode(), kInstFail);
}

TEST_F(ProgTest_415, InstInitAlt_415) {
  Prog::Inst inst;
  inst.InitAlt(3, 7);
  EXPECT_EQ(inst.opcode(), kInstAlt);
  EXPECT_EQ(inst.out(), 3);
  EXPECT_EQ(inst.out1(), 7);
}

TEST_F(ProgTest_415, InstInitCapture_415) {
  Prog::Inst inst;
  inst.InitCapture(2, 8);
  EXPECT_EQ(inst.opcode(), kInstCapture);
  EXPECT_EQ(inst.cap(), 2);
  EXPECT_EQ(inst.out(), 8);
}

TEST_F(ProgTest_415, InstInitEmptyWidth_415) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyBeginLine, 4);
  EXPECT_EQ(inst.opcode(), kInstEmptyWidth);
  EXPECT_EQ(inst.out(), 4);
}

// Test Inst Dump produces non-empty string
TEST_F(ProgTest_415, InstDump_415) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 0, 5);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Inst Matches
TEST_F(ProgTest_415, InstMatchesByteRange_415) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 0, 5);
  EXPECT_TRUE(inst.Matches('a'));
  EXPECT_TRUE(inst.Matches('m'));
  EXPECT_TRUE(inst.Matches('z'));
  EXPECT_FALSE(inst.Matches('A'));
  EXPECT_FALSE(inst.Matches('0'));
}

TEST_F(ProgTest_415, InstMatchesByteRangeFoldcase_415) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 1, 5);
  EXPECT_TRUE(inst.Matches('a'));
  EXPECT_TRUE(inst.Matches('A'));
}

// Test Fanout
TEST_F(ProgTest_415, FanoutSimple_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);
  // Fanout should have some entries
  EXPECT_GE(fanout.size(), 0);
}

// Test ComputeByteMap
TEST_F(ProgTest_415, ComputeByteMap_415) {
  Prog* prog = MakeProg("[a-z]+");
  ASSERT_NE(prog, nullptr);
  // bytemap should map characters into equivalence classes
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
}

// Test IsOnePass
TEST_F(ProgTest_415, IsOnePassSimple_415) {
  Prog* prog = MakeProg("^abc$");
  ASSERT_NE(prog, nullptr);
  // Simple exact match should be one-pass
  bool onepass = prog->IsOnePass();
  // We just test it doesn't crash; result depends on pattern
  (void)onepass;
}

// Test CanBitState
TEST_F(ProgTest_415, CanBitState_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  // Small program should be able to use bit-state
  bool can = prog->CanBitState();
  // Just verify the call works
  (void)can;
}

// Test can_prefix_accel
TEST_F(ProgTest_415, CanPrefixAccel_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  // Not configured yet
  // After ConfigurePrefixAccel it may be true
  prog->ConfigurePrefixAccel("abc", false);
  // Just check it doesn't crash
  bool accel = prog->can_prefix_accel();
  (void)accel;
}

// Test inst() accessor
TEST_F(ProgTest_415, InstAccessor_415) {
  Prog* prog = MakeProg("a");
  ASSERT_NE(prog, nullptr);
  // Access the first instruction
  Prog::Inst* ip = prog->inst(prog->start());
  EXPECT_NE(ip, nullptr);
}

// Test SearchDFA
TEST_F(ProgTest_415, SearchDFAMatch_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("xxxabcyyy");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
}

TEST_F(ProgTest_415, SearchDFANoMatch_415) {
  Prog* prog = MakeProg("xyz");
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

// Test with empty pattern
TEST_F(ProgTest_415, EmptyPatternMatch_415) {
  Prog* prog = MakeProg("");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abc");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0u);
}

// Test with complex regex
TEST_F(ProgTest_415, ComplexRegexMatch_415) {
  Prog* prog = MakeProg("(a+)(b+)");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("aaabbb");
  absl::string_view match[3];
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, match, 3);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "aaabbb");
  EXPECT_EQ(match[1], "aaa");
  EXPECT_EQ(match[2], "bbb");
}

// Test Flatten followed by search
TEST_F(ProgTest_415, FlattenThenSearch_415) {
  Prog* prog = MakeProg("a(b|c)d");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // After flattening, the program should still produce correct results via DFA
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("abd");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_415, SetDfaShouldBailWhenSlow_415) {
  // Just verify the static method doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test inst_count
TEST_F(ProgTest_415, InstCount_415) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  // Sum of all instruction types should equal total size
  int total = 0;
  for (int i = 0; i < kNumInst; i++) {
    int count = prog->inst_count(static_cast<InstOp>(i));
    EXPECT_GE(count, 0);
    total += count;
  }
  EXPECT_EQ(total, prog->size());
}

// Test SearchBitState
TEST_F(ProgTest_415, SearchBitStateMatch_415) {
  Prog* prog = MakeProg("a(b+)c");
  ASSERT_NE(prog, nullptr);
  if (prog->CanBitState()) {
    absl::string_view text("abbbbc");
    absl::string_view match[2];
    bool found = prog->SearchBitState(text, text, Prog::kAnchored,
                                       Prog::kFirstMatch, match, 2);
    EXPECT_TRUE(found);
    EXPECT_EQ(match[0], "abbbbc");
    EXPECT_EQ(match[1], "bbbb");
  }
}

// Test with character class
TEST_F(ProgTest_415, CharClassRegex_415) {
  Prog* prog = MakeProg("[0-9]+");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abc123def");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "123");
}

// Test EmptyFlags at a newline boundary
TEST_F(ProgTest_415, EmptyFlagsNewline_415) {
  std::string text = "abc\ndef";
  absl::string_view sv(text);
  // Point to the character right after the newline
  const char* p = sv.data() + 4;  // points to 'd'
  uint32_t flags = Prog::EmptyFlags(sv, p);
  EXPECT_NE(flags & kEmptyBeginLine, 0u);
}

}  // namespace re2
