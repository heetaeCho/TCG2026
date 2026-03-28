#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/testing/regexp_generator.h"
#include "absl/strings/string_view.h"

namespace re2 {

// Helper to compile a Prog from a pattern string
static Prog* CompilePattern(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

class ProgTest_114 : public ::testing::Test {
 protected:
  void TearDown() override {
    delete prog_;
    prog_ = nullptr;
  }
  Prog* prog_ = nullptr;
};

// Test default construction values
TEST_F(ProgTest_114, DefaultConstruction_114) {
  prog_ = new Prog();
  EXPECT_EQ(prog_->start(), 0);
  EXPECT_EQ(prog_->start_unanchored(), 0);
  EXPECT_FALSE(prog_->reversed());
  EXPECT_FALSE(prog_->anchor_start());
  EXPECT_FALSE(prog_->anchor_end());
  EXPECT_EQ(prog_->dfa_mem(), 0);
  EXPECT_EQ(prog_->bytemap_range(), 0);
}

// Test start and set_start
TEST_F(ProgTest_114, SetStart_114) {
  prog_ = new Prog();
  prog_->set_start(5);
  EXPECT_EQ(prog_->start(), 5);
}

// Test start_unanchored and set_start_unanchored
TEST_F(ProgTest_114, SetStartUnanchored_114) {
  prog_ = new Prog();
  prog_->set_start_unanchored(10);
  EXPECT_EQ(prog_->start_unanchored(), 10);
}

// Test start_unanchored default is 0
TEST_F(ProgTest_114, StartUnanchoredDefault_114) {
  prog_ = new Prog();
  EXPECT_EQ(prog_->start_unanchored(), 0);
}

// Test reversed and set_reversed
TEST_F(ProgTest_114, SetReversed_114) {
  prog_ = new Prog();
  EXPECT_FALSE(prog_->reversed());
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
  prog_->set_reversed(false);
  EXPECT_FALSE(prog_->reversed());
}

// Test anchor_start and set_anchor_start
TEST_F(ProgTest_114, SetAnchorStart_114) {
  prog_ = new Prog();
  EXPECT_FALSE(prog_->anchor_start());
  prog_->set_anchor_start(true);
  EXPECT_TRUE(prog_->anchor_start());
  prog_->set_anchor_start(false);
  EXPECT_FALSE(prog_->anchor_start());
}

// Test anchor_end and set_anchor_end
TEST_F(ProgTest_114, SetAnchorEnd_114) {
  prog_ = new Prog();
  EXPECT_FALSE(prog_->anchor_end());
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_end());
  prog_->set_anchor_end(false);
  EXPECT_FALSE(prog_->anchor_end());
}

// Test dfa_mem and set_dfa_mem
TEST_F(ProgTest_114, SetDfaMem_114) {
  prog_ = new Prog();
  EXPECT_EQ(prog_->dfa_mem(), 0);
  prog_->set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog_->dfa_mem(), 1024 * 1024);
}

// Test IsWordChar for various characters
TEST_F(ProgTest_114, IsWordChar_114) {
  // Letters should be word chars
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  // Digits should be word chars
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  // Underscore should be word char
  EXPECT_TRUE(Prog::IsWordChar('_'));
  // Non-word chars
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
}

// Test compiling a simple pattern and checking prog properties
TEST_F(ProgTest_114, CompileSimplePattern_114) {
  prog_ = CompilePattern("hello");
  ASSERT_NE(prog_, nullptr);
  EXPECT_GE(prog_->size(), 1);
  EXPECT_GE(prog_->start(), 0);
  EXPECT_GE(prog_->start_unanchored(), 0);
}

// Test Dump produces non-empty output
TEST_F(ProgTest_114, DumpNonEmpty_114) {
  prog_ = CompilePattern("abc");
  ASSERT_NE(prog_, nullptr);
  std::string dump = prog_->Dump();
  EXPECT_FALSE(dump.empty());
}

// Test DumpUnanchored produces non-empty output
TEST_F(ProgTest_114, DumpUnanchoredNonEmpty_114) {
  prog_ = CompilePattern("abc");
  ASSERT_NE(prog_, nullptr);
  std::string dump = prog_->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

// Test DumpByteMap produces non-empty output
TEST_F(ProgTest_114, DumpByteMapNonEmpty_114) {
  prog_ = CompilePattern("abc");
  ASSERT_NE(prog_, nullptr);
  prog_->ComputeByteMap();
  std::string dump = prog_->DumpByteMap();
  EXPECT_FALSE(dump.empty());
}

// Test bytemap_range after ComputeByteMap
TEST_F(ProgTest_114, BytemapRange_114) {
  prog_ = CompilePattern("[a-z]+");
  ASSERT_NE(prog_, nullptr);
  EXPECT_GE(prog_->bytemap_range(), 1);
}

// Test bytemap returns non-null
TEST_F(ProgTest_114, BytemapNonNull_114) {
  prog_ = CompilePattern("abc");
  ASSERT_NE(prog_, nullptr);
  const uint8_t* bm = prog_->bytemap();
  EXPECT_NE(bm, nullptr);
}

// Test PossibleMatchRange with simple pattern
TEST_F(ProgTest_114, PossibleMatchRange_114) {
  prog_ = CompilePattern("abc");
  ASSERT_NE(prog_, nullptr);
  std::string min_str, max_str;
  bool result = prog_->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_str, max_str);
}

// Test PossibleMatchRange with maxlen of 0
TEST_F(ProgTest_114, PossibleMatchRangeZeroMaxlen_114) {
  prog_ = CompilePattern("abc");
  ASSERT_NE(prog_, nullptr);
  std::string min_str, max_str;
  bool result = prog_->PossibleMatchRange(&min_str, &max_str, 0);
  // With maxlen 0, the behavior may vary, but it should not crash
  (void)result;
}

// Test can_prefix_accel returns false by default for simple patterns
TEST_F(ProgTest_114, CanPrefixAccelDefault_114) {
  prog_ = new Prog();
  EXPECT_FALSE(prog_->can_prefix_accel());
}

// Test Flatten on a compiled program
TEST_F(ProgTest_114, FlattenDoesNotCrash_114) {
  prog_ = CompilePattern("a|b|c");
  ASSERT_NE(prog_, nullptr);
  prog_->Flatten();
  // After flatten, the program should still be valid
  EXPECT_GE(prog_->size(), 1);
}

// Test Optimize on a compiled program
TEST_F(ProgTest_114, OptimizeDoesNotCrash_114) {
  prog_ = CompilePattern("a.*b");
  ASSERT_NE(prog_, nullptr);
  prog_->Flatten();
  prog_->Optimize();
  EXPECT_GE(prog_->size(), 1);
}

// Test EmptyFlags at beginning of text
TEST_F(ProgTest_114, EmptyFlagsBeginning_114) {
  absl::string_view text("hello world");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At the beginning of the text, we should see kEmptyBeginText
  EXPECT_NE(flags, 0u);
}

// Test EmptyFlags at end of text
TEST_F(ProgTest_114, EmptyFlagsEnd_114) {
  absl::string_view text("hello world");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At the end of the text, we should see kEmptyEndText
  EXPECT_NE(flags, 0u);
}

// Test EmptyFlags in middle of text
TEST_F(ProgTest_114, EmptyFlagsMiddle_114) {
  absl::string_view text("hello world");
  const char* p = text.data() + 5;  // at the space
  uint32_t flags = Prog::EmptyFlags(text, p);
  // In the middle, some flags may or may not be set; just verify it doesn't crash
  (void)flags;
}

// Test EmptyFlags on empty text
TEST_F(ProgTest_114, EmptyFlagsEmptyText_114) {
  absl::string_view text("");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // Empty text at beginning/end should have both begin and end flags
  EXPECT_NE(flags, 0u);
}

// Test SearchNFA on a simple pattern
TEST_F(ProgTest_114, SearchNFASimpleMatch_114) {
  prog_ = CompilePattern("hello");
  ASSERT_NE(prog_, nullptr);
  absl::string_view text("say hello world");
  absl::string_view match;
  bool found = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                 Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

// Test SearchNFA no match
TEST_F(ProgTest_114, SearchNFANoMatch_114) {
  prog_ = CompilePattern("xyz");
  ASSERT_NE(prog_, nullptr);
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                 Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test SearchNFA anchored
TEST_F(ProgTest_114, SearchNFAAnchored_114) {
  prog_ = CompilePattern("hello");
  ASSERT_NE(prog_, nullptr);
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog_->SearchNFA(text, text, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

// Test SearchNFA anchored fails when not at start
TEST_F(ProgTest_114, SearchNFAAnchoredFail_114) {
  prog_ = CompilePattern("world");
  ASSERT_NE(prog_, nullptr);
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog_->SearchNFA(text, text, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test IsOnePass on a simple deterministic pattern
TEST_F(ProgTest_114, IsOnePassSimple_114) {
  prog_ = CompilePattern("abc");
  ASSERT_NE(prog_, nullptr);
  prog_->Flatten();
  // abc is a simple literal, should be one-pass
  bool onepass = prog_->IsOnePass();
  // Just verify it doesn't crash; result depends on pattern
  (void)onepass;
}

// Test SearchBitState simple match
TEST_F(ProgTest_114, SearchBitStateSimpleMatch_114) {
  prog_ = CompilePattern("wor(ld)");
  ASSERT_NE(prog_, nullptr);
  absl::string_view text("hello world");
  absl::string_view match[2];
  if (prog_->CanBitState()) {
    bool found = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                        Prog::kFirstMatch, match, 2);
    EXPECT_TRUE(found);
  }
}

// Test CanBitState
TEST_F(ProgTest_114, CanBitState_114) {
  prog_ = CompilePattern("abc");
  ASSERT_NE(prog_, nullptr);
  // Small patterns should be eligible for bit-state
  bool can = prog_->CanBitState();
  // Just verify it returns a bool without crashing
  (void)can;
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_114, TestingOnlySetDfaShouldBailWhenSlow_114) {
  // Just verify it doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test set_start_unanchored with negative value
TEST_F(ProgTest_114, SetStartUnanchoredNegative_114) {
  prog_ = new Prog();
  prog_->set_start_unanchored(-1);
  EXPECT_EQ(prog_->start_unanchored(), -1);
}

// Test set_start with various values
TEST_F(ProgTest_114, SetStartVariousValues_114) {
  prog_ = new Prog();
  prog_->set_start(0);
  EXPECT_EQ(prog_->start(), 0);
  prog_->set_start(100);
  EXPECT_EQ(prog_->start(), 100);
  prog_->set_start(-1);
  EXPECT_EQ(prog_->start(), -1);
}

// Test set_dfa_mem with large value
TEST_F(ProgTest_114, SetDfaMemLargeValue_114) {
  prog_ = new Prog();
  int64_t large_mem = 1LL << 30;  // 1GB
  prog_->set_dfa_mem(large_mem);
  EXPECT_EQ(prog_->dfa_mem(), large_mem);
}

// Test compiling alternation pattern
TEST_F(ProgTest_114, CompileAlternation_114) {
  prog_ = CompilePattern("(foo|bar|baz)");
  ASSERT_NE(prog_, nullptr);
  EXPECT_GE(prog_->size(), 1);
}

// Test SearchDFA simple match
TEST_F(ProgTest_114, SearchDFASimpleMatch_114) {
  prog_ = CompilePattern("hello");
  ASSERT_NE(prog_, nullptr);
  prog_->set_dfa_mem(1 << 20);
  absl::string_view text("say hello world");
  absl::string_view match;
  bool failed = false;
  bool found = prog_->SearchDFA(text, text, Prog::kUnanchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
}

// Test SearchDFA no match
TEST_F(ProgTest_114, SearchDFANoMatch_114) {
  prog_ = CompilePattern("xyz123");
  ASSERT_NE(prog_, nullptr);
  prog_->set_dfa_mem(1 << 20);
  absl::string_view text("hello world");
  absl::string_view match;
  bool failed = false;
  bool found = prog_->SearchDFA(text, text, Prog::kUnanchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(found);
  }
}

// Test PossibleMatchRange for dot-star pattern
TEST_F(ProgTest_114, PossibleMatchRangeDotStar_114) {
  prog_ = CompilePattern(".*");
  ASSERT_NE(prog_, nullptr);
  std::string min_str, max_str;
  bool result = prog_->PossibleMatchRange(&min_str, &max_str, 10);
  // .* matches everything, so range should be broad
  (void)result;
}

// Test size after compilation
TEST_F(ProgTest_114, SizeAfterCompile_114) {
  prog_ = CompilePattern("a(b+)c");
  ASSERT_NE(prog_, nullptr);
  EXPECT_GT(prog_->size(), 0);
}

// Test start_unanchored after compilation of unanchored pattern
TEST_F(ProgTest_114, StartUnanchoredAfterCompile_114) {
  prog_ = CompilePattern("abc");
  ASSERT_NE(prog_, nullptr);
  // start_unanchored should be a valid instruction index
  EXPECT_GE(prog_->start_unanchored(), 0);
  EXPECT_LT(prog_->start_unanchored(), prog_->size());
}

// Test start after compilation
TEST_F(ProgTest_114, StartAfterCompile_114) {
  prog_ = CompilePattern("^abc$");
  ASSERT_NE(prog_, nullptr);
  EXPECT_GE(prog_->start(), 0);
  EXPECT_LT(prog_->start(), prog_->size());
}

// Test ConfigurePrefixAccel and can_prefix_accel
TEST_F(ProgTest_114, ConfigurePrefixAccel_114) {
  prog_ = CompilePattern("hello.*world");
  ASSERT_NE(prog_, nullptr);
  prog_->ComputeByteMap();
  prog_->ConfigurePrefixAccel("hello", false);
  // After configuring, can_prefix_accel might be true
  // Just verify no crash
  bool can = prog_->can_prefix_accel();
  (void)can;
}

// Test SearchNFA with empty text
TEST_F(ProgTest_114, SearchNFAEmptyText_114) {
  prog_ = CompilePattern("");
  ASSERT_NE(prog_, nullptr);
  absl::string_view text("");
  absl::string_view match;
  bool found = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                 Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

// Test SearchNFA with empty pattern on non-empty text
TEST_F(ProgTest_114, SearchNFAEmptyPatternNonEmptyText_114) {
  prog_ = CompilePattern("");
  ASSERT_NE(prog_, nullptr);
  absl::string_view text("hello");
  absl::string_view match;
  bool found = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                 Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0u);
}

}  // namespace re2
