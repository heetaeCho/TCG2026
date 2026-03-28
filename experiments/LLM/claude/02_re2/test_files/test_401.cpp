#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/sparse_array.h"
#include "re2/sparse_set.h"
#include "absl/strings/string_view.h"
#include <string>
#include <vector>

namespace re2 {

// Helper to compile a Regexp into a Prog for testing
class ProgTest_401 : public ::testing::Test {
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

// Test that a default-constructed Prog has expected initial state
TEST_F(ProgTest_401, DefaultConstructor_401) {
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

// Test setters and getters for start
TEST_F(ProgTest_401, SetStart_401) {
  Prog prog;
  prog.set_start(5);
  EXPECT_EQ(prog.start(), 5);
}

// Test setters and getters for start_unanchored
TEST_F(ProgTest_401, SetStartUnanchored_401) {
  Prog prog;
  prog.set_start_unanchored(10);
  EXPECT_EQ(prog.start_unanchored(), 10);
}

// Test setters and getters for reversed
TEST_F(ProgTest_401, SetReversed_401) {
  Prog prog;
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test setters and getters for anchor_start
TEST_F(ProgTest_401, SetAnchorStart_401) {
  Prog prog;
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test setters and getters for anchor_end
TEST_F(ProgTest_401, SetAnchorEnd_401) {
  Prog prog;
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test setters and getters for dfa_mem
TEST_F(ProgTest_401, SetDfaMem_401) {
  Prog prog;
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog.dfa_mem(), 1024 * 1024);
}

// Test Dump on a compiled program
TEST_F(ProgTest_401, DumpSimplePattern_401) {
  Prog* prog = CompileRegexp("a");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test DumpUnanchored on a compiled program
TEST_F(ProgTest_401, DumpUnanchoredSimplePattern_401) {
  Prog* prog = CompileRegexp("a");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test DumpByteMap on a compiled program
TEST_F(ProgTest_401, DumpByteMap_401) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test that a compiled program has non-zero size
TEST_F(ProgTest_401, CompiledProgramHasNonZeroSize_401) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test bytemap_range on a compiled program
TEST_F(ProgTest_401, BytemapRange_401) {
  Prog* prog = CompileRegexp("[a-z]+");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  delete prog;
}

// Test bytemap is not null on a compiled program
TEST_F(ProgTest_401, BytemapNotNull_401) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  delete prog;
}

// Test IsWordChar for various characters
TEST_F(ProgTest_401, IsWordChar_401) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
}

// Test EmptyFlags at the beginning of text
TEST_F(ProgTest_401, EmptyFlagsBeginning_401) {
  absl::string_view text = "hello";
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // At the beginning of text, kEmptyBeginText and kEmptyBeginLine should be set
  EXPECT_NE(flags & kEmptyBeginText, 0u);
  EXPECT_NE(flags & kEmptyBeginLine, 0u);
}

// Test EmptyFlags at the end of text
TEST_F(ProgTest_401, EmptyFlagsEnd_401) {
  absl::string_view text = "hello";
  uint32_t flags = Prog::EmptyFlags(text, text.data() + text.size());
  // At the end of text, kEmptyEndText and kEmptyEndLine should be set
  EXPECT_NE(flags & kEmptyEndText, 0u);
  EXPECT_NE(flags & kEmptyEndLine, 0u);
}

// Test EmptyFlags at word boundary
TEST_F(ProgTest_401, EmptyFlagsWordBoundary_401) {
  absl::string_view text = "a b";
  // At position between 'a' and ' ', there's a word boundary
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 1);
  EXPECT_NE(flags & kEmptyWordBoundary, 0u);
}

// Test EmptyFlags at non-word boundary
TEST_F(ProgTest_401, EmptyFlagsNonWordBoundary_401) {
  absl::string_view text = "ab";
  // Between 'a' and 'b', both are word chars, so no word boundary
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 1);
  EXPECT_NE(flags & kEmptyNonWordBoundary, 0u);
}

// Test Flatten on a compiled program
TEST_F(ProgTest_401, Flatten_401) {
  Prog* prog = CompileRegexp("a+b");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // After flatten, program should still be valid
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test Optimize on a compiled program
TEST_F(ProgTest_401, Optimize_401) {
  Prog* prog = CompileRegexp("[abc]+");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  prog->Optimize();
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test SearchNFA basic match
TEST_F(ProgTest_401, SearchNFA_BasicMatch_401) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "say hello world";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
  delete prog;
}

// Test SearchNFA no match
TEST_F(ProgTest_401, SearchNFA_NoMatch_401) {
  Prog* prog = CompileRegexp("xyz");
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "say hello world";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  delete prog;
}

// Test SearchNFA anchored match
TEST_F(ProgTest_401, SearchNFA_AnchoredMatch_401) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "hello world";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
  delete prog;
}

// Test SearchNFA anchored no match
TEST_F(ProgTest_401, SearchNFA_AnchoredNoMatch_401) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "say hello";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  delete prog;
}

// Test SearchDFA basic match
TEST_F(ProgTest_401, SearchDFA_BasicMatch_401) {
  Prog* prog = CompileRegexp("world");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text = "hello world";
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
TEST_F(ProgTest_401, SearchDFA_NoMatch_401) {
  Prog* prog = CompileRegexp("xyz");
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
  delete prog;
}

// Test PossibleMatchRange
TEST_F(ProgTest_401, PossibleMatchRange_401) {
  Prog* prog = CompileRegexp("[a-c]+");
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool ok = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(ok);
  EXPECT_LE(min_str, max_str);
  delete prog;
}

// Test PossibleMatchRange with maxlen 0
TEST_F(ProgTest_401, PossibleMatchRangeMaxlenZero_401) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  // maxlen of 0 should still work or return false
  prog->PossibleMatchRange(&min_str, &max_str, 0);
  delete prog;
}

// Test IsOnePass on a one-pass program
TEST_F(ProgTest_401, IsOnePass_401) {
  Prog* prog = CompileRegexp("^abc$");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // Just call it; result depends on the pattern
  bool onepass = prog->IsOnePass();
  // Simple anchored literal pattern should typically be one-pass
  EXPECT_TRUE(onepass);
  delete prog;
}

// Test SearchOnePass when pattern is one-pass
TEST_F(ProgTest_401, SearchOnePass_401) {
  Prog* prog = CompileRegexp("^abc$");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  if (prog->IsOnePass()) {
    absl::string_view text = "abc";
    absl::string_view match;
    bool found = prog->SearchOnePass(text, text, Prog::kAnchored,
                                      Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "abc");
  }
  delete prog;
}

// Test CanBitState
TEST_F(ProgTest_401, CanBitState_401) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  // CanBitState depends on program size; for small program it should be true
  EXPECT_TRUE(prog->CanBitState());
  delete prog;
}

// Test SearchBitState
TEST_F(ProgTest_401, SearchBitState_Match_401) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  if (prog->CanBitState()) {
    absl::string_view text = "say hello world";
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "hello");
  }
  delete prog;
}

// Test SearchBitState no match
TEST_F(ProgTest_401, SearchBitState_NoMatch_401) {
  Prog* prog = CompileRegexp("xyz");
  ASSERT_NE(prog, nullptr);
  if (prog->CanBitState()) {
    absl::string_view text = "hello world";
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_FALSE(found);
  }
  delete prog;
}

// Test Fanout
TEST_F(ProgTest_401, Fanout_401) {
  Prog* prog = CompileRegexp("a|b|c");
  ASSERT_NE(prog, nullptr);
  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);
  // Just verify it doesn't crash and produces some entries
  delete prog;
}

// Test Inst::Dump for various instruction types
TEST_F(ProgTest_401, InstDump_401) {
  Prog::Inst inst;
  inst.InitMatch(1);
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Inst::InitByteRange
TEST_F(ProgTest_401, InstInitByteRange_401) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 0, 5);
  EXPECT_EQ(inst.lo(), 'a');
  EXPECT_EQ(inst.hi(), 'z');
  EXPECT_EQ(inst.foldcase(), 0);
  EXPECT_EQ(inst.out(), 5);
}

// Test Inst::InitCapture
TEST_F(ProgTest_401, InstInitCapture_401) {
  Prog::Inst inst;
  inst.InitCapture(2, 10);
  EXPECT_EQ(inst.cap(), 2);
  EXPECT_EQ(inst.out(), 10);
}

// Test Inst::InitEmptyWidth
TEST_F(ProgTest_401, InstInitEmptyWidth_401) {
  Prog::Inst inst;
  inst.InitEmptyWidth(kEmptyBeginLine, 3);
  EXPECT_EQ(inst.empty(), kEmptyBeginLine);
  EXPECT_EQ(inst.out(), 3);
}

// Test Inst::InitMatch
TEST_F(ProgTest_401, InstInitMatch_401) {
  Prog::Inst inst;
  inst.InitMatch(42);
  EXPECT_EQ(inst.match_id(), 42);
}

// Test Inst::InitNop
TEST_F(ProgTest_401, InstInitNop_401) {
  Prog::Inst inst;
  inst.InitNop(7);
  EXPECT_EQ(inst.out(), 7);
}

// Test Inst::InitAlt
TEST_F(ProgTest_401, InstInitAlt_401) {
  Prog::Inst inst;
  inst.InitAlt(3, 5);
  EXPECT_EQ(inst.out(), 3);
  EXPECT_EQ(inst.out1(), 5);
}

// Test Inst::Matches for ByteRange
TEST_F(ProgTest_401, InstMatches_401) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 0, 0);
  EXPECT_TRUE(inst.Matches('a'));
  EXPECT_TRUE(inst.Matches('m'));
  EXPECT_TRUE(inst.Matches('z'));
  EXPECT_FALSE(inst.Matches('A'));
  EXPECT_FALSE(inst.Matches('0'));
}

// Test Inst::Matches with foldcase
TEST_F(ProgTest_401, InstMatchesFoldcase_401) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 1, 0);
  EXPECT_TRUE(inst.Matches('a'));
  EXPECT_TRUE(inst.Matches('A'));  // foldcase should match
  EXPECT_TRUE(inst.Matches('z'));
  EXPECT_TRUE(inst.Matches('Z'));
}

// Test can_prefix_accel on default Prog
TEST_F(ProgTest_401, CanPrefixAccelDefault_401) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test ConfigurePrefixAccel and can_prefix_accel
TEST_F(ProgTest_401, ConfigurePrefixAccel_401) {
  Prog* prog = CompileRegexp("hello.*world");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // ConfigurePrefixAccel may or may not enable accel depending on prefix
  prog->ConfigurePrefixAccel("hello", false);
  // Just ensure no crash
  delete prog;
}

// Test CompileSet
TEST_F(ProgTest_401, CompileSet_401) {
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
TEST_F(ProgTest_401, EmptyPattern_401) {
  Prog* prog = CompileRegexp("");
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "anything";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  // Empty pattern should match empty string at beginning
  EXPECT_EQ(match.size(), 0u);
  delete prog;
}

// Test SearchNFA with empty text
TEST_F(ProgTest_401, SearchNFA_EmptyText_401) {
  Prog* prog = CompileRegexp("a*");
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0u);
  delete prog;
}

// Test SearchNFA with nmatch 0 (just check for existence)
TEST_F(ProgTest_401, SearchNFA_NmatchZero_401) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "hello world";
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, nullptr, 0);
  EXPECT_TRUE(found);
  delete prog;
}

// Test BuildEntireDFA
TEST_F(ProgTest_401, BuildEntireDFA_401) {
  Prog* prog = CompileRegexp("[ab]");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  int states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(states, 0);
  delete prog;
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_401, DFAShouldBailWhenSlow_401) {
  // Just test that the function can be called without crashing
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test inst_count on a compiled program
TEST_F(ProgTest_401, InstCount_401) {
  Prog* prog = CompileRegexp("a(b)c");
  ASSERT_NE(prog, nullptr);
  // Just verify it doesn't crash and returns non-negative values
  for (int op = 0; op < 8; op++) {
    EXPECT_GE(prog->inst_count(static_cast<Prog::InstOp>(op)), 0);
  }
  delete prog;
}

// Test inst access on compiled program
TEST_F(ProgTest_401, InstAccess_401) {
  Prog* prog = CompileRegexp("ab");
  ASSERT_NE(prog, nullptr);
  for (int i = 0; i < prog->size(); i++) {
    Prog::Inst* ip = prog->inst(i);
    ASSERT_NE(ip, nullptr);
    // Just verify Dump works on each instruction
    std::string dump = ip->Dump();
    EXPECT_FALSE(dump.empty());
  }
  delete prog;
}

// Test Inst::InitFail
TEST_F(ProgTest_401, InstInitFail_401) {
  Prog::Inst inst;
  inst.InitFail();
  std::string dump = inst.Dump();
  EXPECT_FALSE(dump.empty());
}

// Test complex pattern SearchNFA with captures
TEST_F(ProgTest_401, SearchNFA_WithCaptures_401) {
  Prog* prog = CompileRegexp("(\\w+)@(\\w+)");
  ASSERT_NE(prog, nullptr);
  absl::string_view text = "user@host";
  absl::string_view match[3];
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, match, 3);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "user@host");
  EXPECT_EQ(match[1], "user");
  EXPECT_EQ(match[2], "host");
  delete prog;
}

// Test multiple Flatten calls (should be idempotent or safe)
TEST_F(ProgTest_401, DoubleFlatten_401) {
  Prog* prog = CompileRegexp("a+b+");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  int size_after_first = prog->size();
  // Flatten again - should not crash
  prog->Flatten();
  EXPECT_EQ(prog->size(), size_after_first);
  delete prog;
}

}  // namespace re2
