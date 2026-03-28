#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/testing/regexp_generator.h"
#include "absl/strings/string_view.h"

namespace re2 {

class ProgTest_122 : public ::testing::Test {
 protected:
  void SetUp() override {
    prog_ = new Prog();
  }

  void TearDown() override {
    delete prog_;
  }

  Prog* prog_;
};

// Test default construction values
TEST_F(ProgTest_122, DefaultConstruction_122) {
  EXPECT_EQ(prog_->dfa_mem(), 0);
  EXPECT_EQ(prog_->start(), 0);
  EXPECT_EQ(prog_->start_unanchored(), 0);
  EXPECT_EQ(prog_->size(), 0);
  EXPECT_FALSE(prog_->reversed());
  EXPECT_FALSE(prog_->anchor_start());
  EXPECT_FALSE(prog_->anchor_end());
  EXPECT_EQ(prog_->bytemap_range(), 0);
  EXPECT_FALSE(prog_->can_prefix_accel());
}

// Test set_dfa_mem and dfa_mem
TEST_F(ProgTest_122, SetAndGetDfaMem_122) {
  prog_->set_dfa_mem(1024);
  EXPECT_EQ(prog_->dfa_mem(), 1024);
}

// Test dfa_mem with zero value
TEST_F(ProgTest_122, DfaMemZero_122) {
  prog_->set_dfa_mem(0);
  EXPECT_EQ(prog_->dfa_mem(), 0);
}

// Test dfa_mem with large value
TEST_F(ProgTest_122, DfaMemLargeValue_122) {
  int64_t large_val = 1LL << 40;  // 1 TB
  prog_->set_dfa_mem(large_val);
  EXPECT_EQ(prog_->dfa_mem(), large_val);
}

// Test dfa_mem with negative value (edge case)
TEST_F(ProgTest_122, DfaMemNegativeValue_122) {
  prog_->set_dfa_mem(-1);
  EXPECT_EQ(prog_->dfa_mem(), -1);
}

// Test set_start and start
TEST_F(ProgTest_122, SetAndGetStart_122) {
  prog_->set_start(5);
  EXPECT_EQ(prog_->start(), 5);
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_122, SetAndGetStartUnanchored_122) {
  prog_->set_start_unanchored(10);
  EXPECT_EQ(prog_->start_unanchored(), 10);
}

// Test set_reversed and reversed
TEST_F(ProgTest_122, SetAndGetReversed_122) {
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
  prog_->set_reversed(false);
  EXPECT_FALSE(prog_->reversed());
}

// Test set_anchor_start and anchor_start
TEST_F(ProgTest_122, SetAndGetAnchorStart_122) {
  prog_->set_anchor_start(true);
  EXPECT_TRUE(prog_->anchor_start());
  prog_->set_anchor_start(false);
  EXPECT_FALSE(prog_->anchor_start());
}

// Test set_anchor_end and anchor_end
TEST_F(ProgTest_122, SetAndGetAnchorEnd_122) {
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_end());
  prog_->set_anchor_end(false);
  EXPECT_FALSE(prog_->anchor_end());
}

// Test IsWordChar with word characters
TEST_F(ProgTest_122, IsWordCharAlpha_122) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

// Test IsWordChar with non-word characters
TEST_F(ProgTest_122, IsWordCharNonWord_122) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\t'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
  EXPECT_FALSE(Prog::IsWordChar(0));
  EXPECT_FALSE(Prog::IsWordChar(255));
}

// Test EmptyFlags at various positions
TEST_F(ProgTest_122, EmptyFlagsBeginOfText_122) {
  absl::string_view text("hello");
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // At beginning of text, kEmptyBeginText and kEmptyBeginLine should be set
  EXPECT_NE(flags, 0u);
}

TEST_F(ProgTest_122, EmptyFlagsEndOfText_122) {
  absl::string_view text("hello");
  uint32_t flags = Prog::EmptyFlags(text, text.data() + text.size());
  // At end of text, kEmptyEndText and kEmptyEndLine should be set
  EXPECT_NE(flags, 0u);
}

TEST_F(ProgTest_122, EmptyFlagsEmptyText_122) {
  absl::string_view text("");
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // Both begin and end flags should be set
  EXPECT_NE(flags, 0u);
}

// Test bytemap access (default state)
TEST_F(ProgTest_122, BytemapNotNull_122) {
  const uint8_t* bm = prog_->bytemap();
  EXPECT_NE(bm, nullptr);
}

// Test using Prog compiled from a Regexp - more realistic scenario
class ProgCompileTest_122 : public ::testing::Test {
 protected:
  Prog* CompileRegexp(const char* pattern) {
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

TEST_F(ProgCompileTest_122, CompileSimplePattern_122) {
  Prog* p = CompileRegexp("hello");
  ASSERT_NE(p, nullptr);
  EXPECT_GT(p->size(), 0);
}

TEST_F(ProgCompileTest_122, DumpNotEmpty_122) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(p, nullptr);
  std::string dump = p->Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgCompileTest_122, DumpUnanchoredNotEmpty_122) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(p, nullptr);
  std::string dump = p->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgCompileTest_122, DumpByteMapNotEmpty_122) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(p, nullptr);
  p->ComputeByteMap();
  std::string dump = p->DumpByteMap();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgCompileTest_122, PossibleMatchRangeSimple_122) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(p, nullptr);
  std::string min_str, max_str;
  bool result = p->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_str, max_str);
}

TEST_F(ProgCompileTest_122, PossibleMatchRangeMaxlenZero_122) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(p, nullptr);
  std::string min_str, max_str;
  // maxlen of 0 - boundary condition
  bool result = p->PossibleMatchRange(&min_str, &max_str, 0);
  // Result may or may not be true depending on implementation
  // but it should not crash
  (void)result;
}

TEST_F(ProgCompileTest_122, SearchNFASimpleMatch_122) {
  Prog* p = CompileRegexp("hello");
  ASSERT_NE(p, nullptr);
  absl::string_view text("say hello world");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kUnanchored,
                             Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgCompileTest_122, SearchNFANoMatch_122) {
  Prog* p = CompileRegexp("xyz");
  ASSERT_NE(p, nullptr);
  absl::string_view text("say hello world");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kUnanchored,
                             Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgCompileTest_122, SearchNFAAnchoredMatch_122) {
  Prog* p = CompileRegexp("say");
  ASSERT_NE(p, nullptr);
  absl::string_view text("say hello world");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kAnchored,
                             Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgCompileTest_122, SearchNFAAnchoredNoMatch_122) {
  Prog* p = CompileRegexp("hello");
  ASSERT_NE(p, nullptr);
  absl::string_view text("say hello world");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kAnchored,
                             Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgCompileTest_122, IsOnePassSimple_122) {
  Prog* p = CompileRegexp("^abc$");
  ASSERT_NE(p, nullptr);
  // Simple pattern should be one-pass
  bool onepass = p->IsOnePass();
  // We just test it doesn't crash; the result depends on the pattern
  (void)onepass;
}

TEST_F(ProgCompileTest_122, BytemapRangeAfterCompile_122) {
  Prog* p = CompileRegexp("[a-z]+");
  ASSERT_NE(p, nullptr);
  EXPECT_GT(p->bytemap_range(), 0);
}

TEST_F(ProgCompileTest_122, SizeAfterCompile_122) {
  Prog* p = CompileRegexp("a|b|c");
  ASSERT_NE(p, nullptr);
  EXPECT_GT(p->size(), 0);
}

TEST_F(ProgCompileTest_122, StartAfterCompile_122) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(p, nullptr);
  // Start should be a valid instruction index
  EXPECT_GE(p->start(), 0);
  EXPECT_LT(p->start(), p->size());
}

TEST_F(ProgCompileTest_122, StartUnanchoredAfterCompile_122) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(p, nullptr);
  EXPECT_GE(p->start_unanchored(), 0);
  EXPECT_LT(p->start_unanchored(), p->size());
}

TEST_F(ProgCompileTest_122, SearchBitStateMatch_122) {
  Prog* p = CompileRegexp("hello");
  ASSERT_NE(p, nullptr);
  if (!p->CanBitState()) return;
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = p->SearchBitState(text, text, Prog::kUnanchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgCompileTest_122, SearchBitStateNoMatch_122) {
  Prog* p = CompileRegexp("xyz");
  ASSERT_NE(p, nullptr);
  if (!p->CanBitState()) return;
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = p->SearchBitState(text, text, Prog::kUnanchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgCompileTest_122, CanBitState_122) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(p, nullptr);
  // Should not crash
  bool can = p->CanBitState();
  (void)can;
}

TEST_F(ProgCompileTest_122, SearchDFAMatch_122) {
  Prog* p = CompileRegexp("hello");
  ASSERT_NE(p, nullptr);
  p->set_dfa_mem(1 << 20);
  absl::string_view text("say hello");
  absl::string_view match;
  bool failed = false;
  bool found = p->SearchDFA(text, text, Prog::kUnanchored,
                             Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
}

TEST_F(ProgCompileTest_122, SearchDFANoMatch_122) {
  Prog* p = CompileRegexp("xyz");
  ASSERT_NE(p, nullptr);
  p->set_dfa_mem(1 << 20);
  absl::string_view text("say hello");
  absl::string_view match;
  bool failed = false;
  bool found = p->SearchDFA(text, text, Prog::kUnanchored,
                             Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(found);
  }
}

TEST_F(ProgCompileTest_122, FlattenDoesNotCrash_122) {
  Prog* p = CompileRegexp("(a|b)*c");
  ASSERT_NE(p, nullptr);
  p->Flatten();
  // After flatten, the program should still work
  EXPECT_GT(p->size(), 0);
}

TEST_F(ProgCompileTest_122, OptimizeDoesNotCrash_122) {
  Prog* p = CompileRegexp("(a|b)*c");
  ASSERT_NE(p, nullptr);
  p->Optimize();
  // After optimize, the program should still work
  EXPECT_GT(p->size(), 0);
}

TEST_F(ProgCompileTest_122, SearchNFAEmptyPattern_122) {
  Prog* p = CompileRegexp("");
  ASSERT_NE(p, nullptr);
  absl::string_view text("hello");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kUnanchored,
                             Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgCompileTest_122, SearchNFAEmptyText_122) {
  Prog* p = CompileRegexp("a*");
  ASSERT_NE(p, nullptr);
  absl::string_view text("");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kUnanchored,
                             Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgCompileTest_122, SearchNFAEmptyTextNoMatch_122) {
  Prog* p = CompileRegexp("a+");
  ASSERT_NE(p, nullptr);
  absl::string_view text("");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kUnanchored,
                             Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgCompileTest_122, TestingOnlySetDfaShouldBail_122) {
  // Should not crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test setting and getting multiple properties in sequence
TEST_F(ProgTest_122, MultiplePropertySetGet_122) {
  prog_->set_dfa_mem(2048);
  prog_->set_anchor_start(true);
  prog_->set_anchor_end(true);
  prog_->set_reversed(true);
  prog_->set_start(3);
  prog_->set_start_unanchored(7);

  EXPECT_EQ(prog_->dfa_mem(), 2048);
  EXPECT_TRUE(prog_->anchor_start());
  EXPECT_TRUE(prog_->anchor_end());
  EXPECT_TRUE(prog_->reversed());
  EXPECT_EQ(prog_->start(), 3);
  EXPECT_EQ(prog_->start_unanchored(), 7);
}

// Test PossibleMatchRange with a complex pattern
TEST_F(ProgCompileTest_122, PossibleMatchRangeComplex_122) {
  Prog* p = CompileRegexp("[a-z]{2,5}");
  ASSERT_NE(p, nullptr);
  std::string min_str, max_str;
  bool result = p->PossibleMatchRange(&min_str, &max_str, 10);
  if (result) {
    EXPECT_LE(min_str, max_str);
  }
}

// Test with pattern that has prefix acceleration
TEST_F(ProgCompileTest_122, CanPrefixAccel_122) {
  Prog* p = CompileRegexp("hello.*world");
  ASSERT_NE(p, nullptr);
  // can_prefix_accel depends on the pattern; just ensure no crash
  bool can = p->can_prefix_accel();
  (void)can;
}

// Test ConfigurePrefixAccel
TEST_F(ProgTest_122, ConfigurePrefixAccel_122) {
  // On a default Prog this might not do much, but should not crash
  prog_->ConfigurePrefixAccel("test", false);
}

// Test PrefixAccel with no configuration
TEST_F(ProgTest_122, PrefixAccelWithoutConfig_122) {
  // Without prefix accel configured, can_prefix_accel should be false
  EXPECT_FALSE(prog_->can_prefix_accel());
}

// Compile a set and verify
TEST(ProgCompileSetTest_122, CompileSetNull_122) {
  // Passing nullptr should be handled (likely returns nullptr)
  // But we can't safely pass nullptr for Regexp*, so skip this
  // Instead test with a valid Regexp
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* p = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  if (p != nullptr) {
    EXPECT_GT(p->size(), 0);
    delete p;
  }
  re->Decref();
}

// Test SearchOnePass if pattern is one-pass
TEST_F(ProgCompileTest_122, SearchOnePassIfOnePass_122) {
  Prog* p = CompileRegexp("^abc$");
  ASSERT_NE(p, nullptr);
  if (p->IsOnePass()) {
    absl::string_view text("abc");
    absl::string_view match;
    bool found = p->SearchOnePass(text, text, Prog::kAnchored,
                                   Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
  }
}

TEST_F(ProgCompileTest_122, SearchOnePassNoMatch_122) {
  Prog* p = CompileRegexp("^abc$");
  ASSERT_NE(p, nullptr);
  if (p->IsOnePass()) {
    absl::string_view text("xyz");
    absl::string_view match;
    bool found = p->SearchOnePass(text, text, Prog::kAnchored,
                                   Prog::kFirstMatch, &match, 1);
    EXPECT_FALSE(found);
  }
}

// Test dfa_mem boundary: max int64_t
TEST_F(ProgTest_122, DfaMemMaxInt64_122) {
  int64_t max_val = INT64_MAX;
  prog_->set_dfa_mem(max_val);
  EXPECT_EQ(prog_->dfa_mem(), max_val);
}

// Test dfa_mem boundary: min int64_t
TEST_F(ProgTest_122, DfaMemMinInt64_122) {
  int64_t min_val = INT64_MIN;
  prog_->set_dfa_mem(min_val);
  EXPECT_EQ(prog_->dfa_mem(), min_val);
}

// Test overwriting dfa_mem
TEST_F(ProgTest_122, DfaMemOverwrite_122) {
  prog_->set_dfa_mem(100);
  EXPECT_EQ(prog_->dfa_mem(), 100);
  prog_->set_dfa_mem(200);
  EXPECT_EQ(prog_->dfa_mem(), 200);
}

}  // namespace re2
