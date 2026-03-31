#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/testing/regexp_generator.h"
#include "absl/strings/string_view.h"

namespace re2 {

class ProgTest_120 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default construction of Prog
TEST_F(ProgTest_120, DefaultConstruction_120) {
  Prog prog;
  EXPECT_EQ(prog.start(), 0);
  EXPECT_EQ(prog.start_unanchored(), 0);
  EXPECT_FALSE(prog.reversed());
  EXPECT_FALSE(prog.anchor_start());
  EXPECT_FALSE(prog.anchor_end());
  EXPECT_EQ(prog.size(), 0);
  EXPECT_EQ(prog.bytemap_range(), 0);
  EXPECT_EQ(prog.dfa_mem(), 0);
}

// Test set_start and start
TEST_F(ProgTest_120, SetStart_120) {
  Prog prog;
  prog.set_start(5);
  EXPECT_EQ(prog.start(), 5);
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_120, SetStartUnanchored_120) {
  Prog prog;
  prog.set_start_unanchored(10);
  EXPECT_EQ(prog.start_unanchored(), 10);
}

// Test set_reversed and reversed
TEST_F(ProgTest_120, SetReversed_120) {
  Prog prog;
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test set_anchor_start and anchor_start
TEST_F(ProgTest_120, SetAnchorStart_120) {
  Prog prog;
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test set_anchor_end and anchor_end
TEST_F(ProgTest_120, SetAnchorEnd_120) {
  Prog prog;
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test set_dfa_mem and dfa_mem
TEST_F(ProgTest_120, SetDfaMem_120) {
  Prog prog;
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog.dfa_mem(), 1024 * 1024);
}

// Test inst_count for default-constructed Prog (should be 0 for all ops)
TEST_F(ProgTest_120, InstCountDefault_120) {
  Prog prog;
  for (int i = 0; i < 8; i++) {
    EXPECT_EQ(prog.inst_count(static_cast<InstOp>(i)), 0);
  }
}

// Test can_prefix_accel on default prog
TEST_F(ProgTest_120, CanPrefixAccelDefault_120) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test IsWordChar for various characters
TEST_F(ProgTest_120, IsWordChar_120) {
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
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
  EXPECT_FALSE(Prog::IsWordChar('['));
}

// Test EmptyFlags at various positions
TEST_F(ProgTest_120, EmptyFlagsBeginningOfText_120) {
  absl::string_view text("hello");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At beginning of text, kEmptyBeginText and kEmptyBeginLine should be set
  EXPECT_NE(flags & kEmptyBeginText, 0u);
  EXPECT_NE(flags & kEmptyBeginLine, 0u);
}

TEST_F(ProgTest_120, EmptyFlagsEndOfText_120) {
  absl::string_view text("hello");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At end of text, kEmptyEndText and kEmptyEndLine should be set
  EXPECT_NE(flags & kEmptyEndText, 0u);
  EXPECT_NE(flags & kEmptyEndLine, 0u);
}

TEST_F(ProgTest_120, EmptyFlagsMiddleOfText_120) {
  absl::string_view text("hello");
  const char* p = text.data() + 2;
  uint32_t flags = Prog::EmptyFlags(text, p);
  // In the middle, neither begin/end text should be set
  EXPECT_EQ(flags & kEmptyBeginText, 0u);
  EXPECT_EQ(flags & kEmptyEndText, 0u);
}

TEST_F(ProgTest_120, EmptyFlagsWordBoundary_120) {
  absl::string_view text("a b");
  const char* p = text.data() + 1;  // between 'a' and ' '
  uint32_t flags = Prog::EmptyFlags(text, p);
  // There should be a word boundary between 'a' and ' '
  EXPECT_NE(flags & kEmptyWordBoundary, 0u);
}

TEST_F(ProgTest_120, EmptyFlagsNonWordBoundary_120) {
  absl::string_view text("ab");
  const char* p = text.data() + 1;  // between 'a' and 'b'
  uint32_t flags = Prog::EmptyFlags(text, p);
  // No word boundary between 'a' and 'b'
  EXPECT_NE(flags & kEmptyNonWordBoundary, 0u);
}

// Test Prog compiled from a simple regex via RE2 internals
class ProgCompileTest_120 : public ::testing::Test {
 protected:
  Prog* CompileRegex(const char* pattern) {
    RegexpStatus status;
    re_ = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re_ == nullptr) return nullptr;
    prog_ = re_->CompileToProg(0);
    return prog_;
  }

  void TearDown() override {
    delete prog_;
    if (re_) re_->Decref();
  }

  Regexp* re_ = nullptr;
  Prog* prog_ = nullptr;
};

TEST_F(ProgCompileTest_120, SimplePatternCompiles_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
}

TEST_F(ProgCompileTest_120, DumpNotEmpty_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgCompileTest_120, DumpUnanchoredNotEmpty_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgCompileTest_120, DumpByteMapNotEmpty_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgCompileTest_120, BytemapNotNull_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_NE(prog->bytemap(), nullptr);
}

TEST_F(ProgCompileTest_120, BytemapRangePositive_120) {
  Prog* prog = CompileRegex("[a-z]");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
}

TEST_F(ProgCompileTest_120, PossibleMatchRange_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_str, max_str);
}

TEST_F(ProgCompileTest_120, PossibleMatchRangeMaxlenZero_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  // maxlen of 0 is a boundary condition
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 0);
  // The result depends on the implementation, but it should not crash
  (void)result;
}

TEST_F(ProgCompileTest_120, FlattenDoesNotCrash_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // After flatten, size should still be > 0
  EXPECT_GT(prog->size(), 0);
}

TEST_F(ProgCompileTest_120, OptimizeDoesNotCrash_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
}

TEST_F(ProgCompileTest_120, IsOnePassSimple_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  // Simple literal pattern should be one-pass
  EXPECT_TRUE(prog->IsOnePass());
}

TEST_F(ProgCompileTest_120, IsOnePassComplex_120) {
  Prog* prog = CompileRegex("(a*)(a*)");
  ASSERT_NE(prog, nullptr);
  // Ambiguous pattern may not be one-pass
  // Just verify it doesn't crash
  prog->IsOnePass();
}

TEST_F(ProgCompileTest_120, CanBitState_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  // Small program should support bit-state
  EXPECT_TRUE(prog->CanBitState());
}

TEST_F(ProgCompileTest_120, SearchNFAMatch_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xabcy");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

TEST_F(ProgCompileTest_120, SearchNFANoMatch_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xyz");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgCompileTest_120, SearchNFAAnchored_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

TEST_F(ProgCompileTest_120, SearchNFAAnchoredNoMatch_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xabc");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgCompileTest_120, SearchDFAMatch_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("xabcy");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(found);
}

TEST_F(ProgCompileTest_120, SearchDFANoMatch_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("xyz");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_FALSE(found);
}

TEST_F(ProgCompileTest_120, SearchBitStateMatch_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xabcy");
  absl::string_view match;
  if (prog->CanBitState()) {
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "abc");
  }
}

TEST_F(ProgCompileTest_120, SearchBitStateNoMatch_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xyz");
  absl::string_view match;
  if (prog->CanBitState()) {
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_FALSE(found);
  }
}

TEST_F(ProgCompileTest_120, SearchOnePassMatch_120) {
  Prog* prog = CompileRegex("abc");
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

TEST_F(ProgCompileTest_120, SearchOnePassNoMatch_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  if (prog->IsOnePass()) {
    absl::string_view text("xyz");
    absl::string_view match;
    bool found = prog->SearchOnePass(text, text, Prog::kUnanchored,
                                      Prog::kFirstMatch, &match, 1);
    EXPECT_FALSE(found);
  }
}

TEST_F(ProgCompileTest_120, EmptyPattern_120) {
  Prog* prog = CompileRegex("");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("anything");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "");
}

TEST_F(ProgCompileTest_120, EmptyText_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgCompileTest_120, EmptyPatternEmptyText_120) {
  Prog* prog = CompileRegex("");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgCompileTest_120, InstCountAfterCompile_120) {
  Prog* prog = CompileRegex("a(b|c)d");
  ASSERT_NE(prog, nullptr);
  // The total of all inst_count values should relate to the program size
  int total = 0;
  for (int i = 0; i < 8; i++) {
    int count = prog->inst_count(static_cast<InstOp>(i));
    EXPECT_GE(count, 0);
    total += count;
  }
  EXPECT_GT(total, 0);
}

TEST_F(ProgCompileTest_120, ConfigurePrefixAccelAndCanPrefixAccel_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  prog->ConfigurePrefixAccel("abc", false);
  // After configuring with a prefix, can_prefix_accel may become true
  // (depends on implementation details, but should not crash)
  // Just verify no crash
  prog->can_prefix_accel();
}

TEST_F(ProgCompileTest_120, PrefixAccelNullWhenNotConfigured_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  // Without ConfigurePrefixAccel, can_prefix_accel should be false
  if (!prog->can_prefix_accel()) {
    const char data[] = "xyzabc";
    const void* result = prog->PrefixAccel(data, sizeof(data) - 1);
    // When not configured, behavior depends on implementation
    (void)result;
  }
}

TEST_F(ProgCompileTest_120, BuildEntireDFA_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  int states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(states, 0);
}

TEST_F(ProgCompileTest_120, CompileSetSimple_120) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgCompileTest_120, TestingOnlySetDfaShouldBailWhenSlow_120) {
  // Just verify it doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test Fanout
TEST_F(ProgCompileTest_120, FanoutDoesNotCrash_120) {
  Prog* prog = CompileRegex("a(b|c|d)e");
  ASSERT_NE(prog, nullptr);
  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);
}

// Test with regex that produces multiple instruction types
TEST_F(ProgCompileTest_120, ComplexPattern_120) {
  Prog* prog = CompileRegex("(foo|bar)+baz.*qux");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);

  absl::string_view text("foofoobarbazxyzqux");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

// Test longest match kind
TEST_F(ProgCompileTest_120, SearchNFALongestMatch_120) {
  Prog* prog = CompileRegex("a+");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("aaaa");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kLongestMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "aaaa");
}

// Test SearchNFA with nmatch = 0 (existence check only)
TEST_F(ProgCompileTest_120, SearchNFANoCapture_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xabcy");
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, nullptr, 0);
  EXPECT_TRUE(found);
}

// Test bit_state_text_max_size
TEST_F(ProgCompileTest_120, BitStateTextMaxSize_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  // Just verify it returns a value without crashing
  size_t max_size = prog->bit_state_text_max_size();
  (void)max_size;
}

// Test list_count
TEST_F(ProgCompileTest_120, ListCount_120) {
  Prog* prog = CompileRegex("abc");
  ASSERT_NE(prog, nullptr);
  int lc = prog->list_count();
  EXPECT_GE(lc, 0);
}

}  // namespace re2
