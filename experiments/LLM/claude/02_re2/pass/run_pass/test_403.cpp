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

// Helper to compile a Regexp into a Prog
static Prog* CompileRegexp(const std::string& pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

class ProgTest_403 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Programs are cleaned up individually in tests
  }
};

// Test default constructor initializes fields correctly
TEST_F(ProgTest_403, DefaultConstructor_403) {
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

// Test set_start and start
TEST_F(ProgTest_403, SetStart_403) {
  Prog prog;
  prog.set_start(5);
  EXPECT_EQ(prog.start(), 5);
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_403, SetStartUnanchored_403) {
  Prog prog;
  prog.set_start_unanchored(10);
  EXPECT_EQ(prog.start_unanchored(), 10);
}

// Test set_reversed and reversed
TEST_F(ProgTest_403, SetReversed_403) {
  Prog prog;
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test set_anchor_start and anchor_start
TEST_F(ProgTest_403, SetAnchorStart_403) {
  Prog prog;
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test set_anchor_end and anchor_end
TEST_F(ProgTest_403, SetAnchorEnd_403) {
  Prog prog;
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test set_dfa_mem and dfa_mem
TEST_F(ProgTest_403, SetDfaMem_403) {
  Prog prog;
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog.dfa_mem(), 1024 * 1024);
}

// Test Dump on a simple regex
TEST_F(ProgTest_403, DumpSimpleRegex_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

// Test DumpUnanchored on a simple regex
TEST_F(ProgTest_403, DumpUnanchoredSimpleRegex_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

// Test DumpByteMap
TEST_F(ProgTest_403, DumpByteMap_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
}

// Test IsWordChar
TEST_F(ProgTest_403, IsWordCharAlpha_403) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

TEST_F(ProgTest_403, IsWordCharNonWord_403) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
}

// Test EmptyFlags
TEST_F(ProgTest_403, EmptyFlagsAtBeginning_403) {
  std::string text = "hello";
  absl::string_view sv(text);
  uint32_t flags = Prog::EmptyFlags(sv, sv.data());
  // At beginning of text, kEmptyBeginText should be set
  EXPECT_NE(flags, 0u);
}

TEST_F(ProgTest_403, EmptyFlagsAtEnd_403) {
  std::string text = "hello";
  absl::string_view sv(text);
  uint32_t flags = Prog::EmptyFlags(sv, sv.data() + sv.size());
  // At end of text, kEmptyEndText should be set
  EXPECT_NE(flags, 0u);
}

TEST_F(ProgTest_403, EmptyFlagsEmptyString_403) {
  std::string text = "";
  absl::string_view sv(text);
  uint32_t flags = Prog::EmptyFlags(sv, sv.data());
  // Both begin and end flags should be set for empty string
  EXPECT_NE(flags, 0u);
}

// Test compilation and search with NFA
TEST_F(ProgTest_403, SearchNFAMatch_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string text = "xabcy";
  absl::string_view sv(text);
  absl::string_view match;
  bool found = prog->SearchNFA(sv, sv, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

TEST_F(ProgTest_403, SearchNFANoMatch_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("xyz"));
  ASSERT_NE(prog, nullptr);
  std::string text = "abc";
  absl::string_view sv(text);
  absl::string_view match;
  bool found = prog->SearchNFA(sv, sv, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test SearchNFA with anchored match
TEST_F(ProgTest_403, SearchNFAAnchored_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string text = "abcdef";
  absl::string_view sv(text);
  absl::string_view match;
  bool found = prog->SearchNFA(sv, sv, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

TEST_F(ProgTest_403, SearchNFAAnchoredNoMatch_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string text = "xabc";
  absl::string_view sv(text);
  absl::string_view match;
  bool found = prog->SearchNFA(sv, sv, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test SearchDFA
TEST_F(ProgTest_403, SearchDFAMatch_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  std::string text = "xabcy";
  absl::string_view sv(text);
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(sv, sv, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
}

TEST_F(ProgTest_403, SearchDFANoMatch_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("xyz"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  std::string text = "abc";
  absl::string_view sv(text);
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(sv, sv, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(found);
  }
}

// Test PossibleMatchRange
TEST_F(ProgTest_403, PossibleMatchRange_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  bool ok = prog->PossibleMatchRange(&min_match, &max_match, 10);
  EXPECT_TRUE(ok);
  EXPECT_LE(min_match, max_match);
}

TEST_F(ProgTest_403, PossibleMatchRangeMaxlen1_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  bool ok = prog->PossibleMatchRange(&min_match, &max_match, 1);
  // Should succeed even with small maxlen
  // (result depends on the regex)
  EXPECT_TRUE(ok);
}

// Test Flatten
TEST_F(ProgTest_403, Flatten_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("a(b|c)d"));
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // After flattening, Dump and DumpUnanchored should still work
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
  std::string dump_unanchored = prog->DumpUnanchored();
  EXPECT_FALSE(dump_unanchored.empty());
}

// Test DumpUnanchored after Flatten (did_flatten_ = true path)
TEST_F(ProgTest_403, DumpUnanchoredAfterFlatten_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  std::string before = prog->DumpUnanchored();
  prog->Flatten();
  std::string after = prog->DumpUnanchored();
  EXPECT_FALSE(before.empty());
  EXPECT_FALSE(after.empty());
}

// Test bytemap_range
TEST_F(ProgTest_403, BytemapRange_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
}

// Test bytemap pointer is non-null
TEST_F(ProgTest_403, Bytemap_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  EXPECT_NE(prog->bytemap(), nullptr);
}

// Test size after compilation
TEST_F(ProgTest_403, SizeAfterCompile_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
}

// Test inst access
TEST_F(ProgTest_403, InstAccess_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  for (int i = 0; i < prog->size(); i++) {
    EXPECT_NE(prog->inst(i), nullptr);
  }
}

// Test Optimize
TEST_F(ProgTest_403, Optimize_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("a(b|c)*d"));
  ASSERT_NE(prog, nullptr);
  // Optimize should not crash
  prog->Optimize();
  // Program should still be functional after optimization
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

// Test IsOnePass on a one-pass regex
TEST_F(ProgTest_403, IsOnePassSimple_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  // "abc" is a simple literal, should be one-pass
  bool onepass = prog->IsOnePass();
  // Just verify it doesn't crash; result depends on implementation
  (void)onepass;
}

// Test SearchBitState
TEST_F(ProgTest_403, SearchBitStateMatch_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("a.c"));
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;
  std::string text = "xabcy";
  absl::string_view sv(text);
  absl::string_view match;
  bool found = prog->SearchBitState(sv, sv, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

TEST_F(ProgTest_403, SearchBitStateNoMatch_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("xyz"));
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;
  std::string text = "abc";
  absl::string_view sv(text);
  absl::string_view match;
  bool found = prog->SearchBitState(sv, sv, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test CanBitState
TEST_F(ProgTest_403, CanBitState_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  // Just test it doesn't crash
  bool can = prog->CanBitState();
  (void)can;
}

// Test can_prefix_accel
TEST_F(ProgTest_403, CanPrefixAccelDefault_403) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test ConfigurePrefixAccel
TEST_F(ProgTest_403, ConfigurePrefixAccel_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  prog->ConfigurePrefixAccel("abc", false);
  // After configuring, can_prefix_accel may or may not be true
  // depending on implementation details, just verify no crash
}

// Test Fanout
TEST_F(ProgTest_403, Fanout_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("a(b|c)d"));
  ASSERT_NE(prog, nullptr);
  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);
  // Fanout should have some entries
  // Just verify no crash
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_403, TestingOnlySetDfaShouldBailWhenSlow_403) {
  // Just verify it doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test with empty regex
TEST_F(ProgTest_403, EmptyRegex_403) {
  std::unique_ptr<Prog> prog(CompileRegexp(""));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

// Test with complex regex
TEST_F(ProgTest_403, ComplexRegex_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("(a+|b*)(c{2,5}|d?)e"));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

// Test SearchOnePass if applicable
TEST_F(ProgTest_403, SearchOnePassMatch_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  if (!prog->IsOnePass()) return;
  std::string text = "abc";
  absl::string_view sv(text);
  absl::string_view match;
  bool found = prog->SearchOnePass(sv, sv, Prog::kAnchored,
                                    Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

TEST_F(ProgTest_403, SearchOnePassNoMatch_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  if (!prog->IsOnePass()) return;
  std::string text = "xyz";
  absl::string_view sv(text);
  absl::string_view match;
  bool found = prog->SearchOnePass(sv, sv, Prog::kAnchored,
                                    Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test multiple capture groups with NFA
TEST_F(ProgTest_403, SearchNFACaptureGroups_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("(a)(b)(c)"));
  ASSERT_NE(prog, nullptr);
  std::string text = "abc";
  absl::string_view sv(text);
  absl::string_view match[4];
  bool found = prog->SearchNFA(sv, sv, Prog::kAnchored,
                                Prog::kFirstMatch, match, 4);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "abc");
  EXPECT_EQ(match[1], "a");
  EXPECT_EQ(match[2], "b");
  EXPECT_EQ(match[3], "c");
}

// Test list_count
TEST_F(ProgTest_403, ListCount_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  // list_count may be zero before flatten
  int lc = prog->list_count();
  (void)lc;
}

// Test bit_state_text_max_size
TEST_F(ProgTest_403, BitStateTextMaxSize_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  size_t max_size = prog->bit_state_text_max_size();
  // Just verify it doesn't crash and returns something
  (void)max_size;
}

// Test with alternation regex for DumpUnanchored
TEST_F(ProgTest_403, DumpUnanchoredAlternation_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("foo|bar|baz"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

// Test CompileSet
TEST_F(ProgTest_403, CompileSet_403) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::unique_ptr<Prog> prog(Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20));
  re->Decref();
  // CompileSet may or may not succeed depending on implementation
  // Just verify no crash
}

// Test BuildEntireDFA
TEST_F(ProgTest_403, BuildEntireDFA_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  int count = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GE(count, 0);
}

// Test empty text search
TEST_F(ProgTest_403, SearchNFAEmptyText_403) {
  std::unique_ptr<Prog> prog(CompileRegexp(""));
  ASSERT_NE(prog, nullptr);
  std::string text = "";
  absl::string_view sv(text);
  absl::string_view match;
  bool found = prog->SearchNFA(sv, sv, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

// Test Flatten and then search
TEST_F(ProgTest_403, FlattenAndSearchNFA_403) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  std::string text = "xabcy";
  absl::string_view sv(text);
  absl::string_view match;
  bool found = prog->SearchNFA(sv, sv, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

}  // namespace re2
