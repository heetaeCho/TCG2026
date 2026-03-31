#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/testing/regexp_generator.h"
#include "absl/strings/string_view.h"

namespace re2 {

class ProgTest_117 : public ::testing::Test {
 protected:
  void SetUp() override {
    prog_ = new Prog();
  }

  void TearDown() override {
    delete prog_;
  }

  Prog* prog_;
};

// Test default constructor initializes reversed to false
TEST_F(ProgTest_117, DefaultReversedIsFalse_117) {
  EXPECT_FALSE(prog_->reversed());
}

// Test set_reversed and reversed getter
TEST_F(ProgTest_117, SetReversedTrue_117) {
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
}

TEST_F(ProgTest_117, SetReversedFalse_117) {
  prog_->set_reversed(true);
  prog_->set_reversed(false);
  EXPECT_FALSE(prog_->reversed());
}

// Test default anchor_start is false
TEST_F(ProgTest_117, DefaultAnchorStartIsFalse_117) {
  EXPECT_FALSE(prog_->anchor_start());
}

// Test set_anchor_start
TEST_F(ProgTest_117, SetAnchorStartTrue_117) {
  prog_->set_anchor_start(true);
  EXPECT_TRUE(prog_->anchor_start());
}

TEST_F(ProgTest_117, SetAnchorStartFalse_117) {
  prog_->set_anchor_start(true);
  prog_->set_anchor_start(false);
  EXPECT_FALSE(prog_->anchor_start());
}

// Test default anchor_end is false
TEST_F(ProgTest_117, DefaultAnchorEndIsFalse_117) {
  EXPECT_FALSE(prog_->anchor_end());
}

// Test set_anchor_end
TEST_F(ProgTest_117, SetAnchorEndTrue_117) {
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_end());
}

TEST_F(ProgTest_117, SetAnchorEndFalse_117) {
  prog_->set_anchor_end(true);
  prog_->set_anchor_end(false);
  EXPECT_FALSE(prog_->anchor_end());
}

// Test default start is 0
TEST_F(ProgTest_117, DefaultStartIsZero_117) {
  EXPECT_EQ(prog_->start(), 0);
}

// Test set_start
TEST_F(ProgTest_117, SetStart_117) {
  prog_->set_start(5);
  EXPECT_EQ(prog_->start(), 5);
}

// Test default start_unanchored is 0
TEST_F(ProgTest_117, DefaultStartUnanchoredIsZero_117) {
  EXPECT_EQ(prog_->start_unanchored(), 0);
}

// Test set_start_unanchored
TEST_F(ProgTest_117, SetStartUnanchored_117) {
  prog_->set_start_unanchored(10);
  EXPECT_EQ(prog_->start_unanchored(), 10);
}

// Test default dfa_mem is 0
TEST_F(ProgTest_117, DefaultDfaMemIsZero_117) {
  EXPECT_EQ(prog_->dfa_mem(), 0);
}

// Test set_dfa_mem
TEST_F(ProgTest_117, SetDfaMem_117) {
  prog_->set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog_->dfa_mem(), 1024 * 1024);
}

// Test default size is 0
TEST_F(ProgTest_117, DefaultSizeIsZero_117) {
  EXPECT_EQ(prog_->size(), 0);
}

// Test default bytemap_range is 0
TEST_F(ProgTest_117, DefaultBytemapRangeIsZero_117) {
  EXPECT_EQ(prog_->bytemap_range(), 0);
}

// Test default can_prefix_accel is false (no prefix configured)
TEST_F(ProgTest_117, DefaultCanPrefixAccelIsFalse_117) {
  EXPECT_FALSE(prog_->can_prefix_accel());
}

// Test IsWordChar for various characters
TEST_F(ProgTest_117, IsWordCharAlpha_117) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
}

TEST_F(ProgTest_117, IsWordCharDigit_117) {
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
}

TEST_F(ProgTest_117, IsWordCharUnderscore_117) {
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

TEST_F(ProgTest_117, IsWordCharNonWord_117) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_117, SetDfaShouldBailWhenSlow_117) {
  // Just verify it doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test bytemap returns non-null pointer
TEST_F(ProgTest_117, BytemapReturnsNonNull_117) {
  EXPECT_NE(prog_->bytemap(), nullptr);
}

// Test EmptyFlags with various positions
TEST_F(ProgTest_117, EmptyFlagsAtBeginningOfText_117) {
  absl::string_view text("hello");
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // At the beginning of text, kEmptyBeginText and kEmptyBeginLine should be set
  EXPECT_NE(flags, 0u);
}

TEST_F(ProgTest_117, EmptyFlagsAtEndOfText_117) {
  absl::string_view text("hello");
  uint32_t flags = Prog::EmptyFlags(text, text.data() + text.size());
  // At the end of text, kEmptyEndText and kEmptyEndLine should be set
  EXPECT_NE(flags, 0u);
}

TEST_F(ProgTest_117, EmptyFlagsEmptyText_117) {
  absl::string_view text("");
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // Both begin and end flags should be set
  EXPECT_NE(flags, 0u);
}

// Test PossibleMatchRange on a default-constructed Prog
// (This is an edge case — behavior depends on implementation, but it should not crash)
TEST_F(ProgTest_117, PossibleMatchRangeOnDefaultProg_117) {
  std::string min_str, max_str;
  // With a default prog (size 0), this may return false
  prog_->PossibleMatchRange(&min_str, &max_str, 10);
  // Just ensure it doesn't crash
}

// Test with a compiled program from a simple regex
class ProgFromRegexTest_117 : public ::testing::Test {
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

TEST_F(ProgFromRegexTest_117, SimpleLiteralDump_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  std::string dump = p->Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexTest_117, SimpleLiteralSize_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  EXPECT_GT(p->size(), 0);
}

TEST_F(ProgFromRegexTest_117, BytemapRangeAfterCompile_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  EXPECT_GT(p->bytemap_range(), 0);
}

TEST_F(ProgFromRegexTest_117, SearchNFAMatch_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  absl::string_view text("xabcx");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

TEST_F(ProgFromRegexTest_117, SearchNFANoMatch_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  absl::string_view text("xyz");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgFromRegexTest_117, SearchDFAMatch_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  p->set_dfa_mem(1 << 20);
  absl::string_view text("xabcx");
  absl::string_view match;
  bool failed = false;
  bool found = p->SearchDFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
}

TEST_F(ProgFromRegexTest_117, SearchDFANoMatch_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  p->set_dfa_mem(1 << 20);
  absl::string_view text("xyz");
  absl::string_view match;
  bool failed = false;
  bool found = p->SearchDFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(found);
  }
}

TEST_F(ProgFromRegexTest_117, IsOnePassSimpleRegex_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  // Just test that IsOnePass doesn't crash and returns a valid bool
  bool onepass = p->IsOnePass();
  (void)onepass;
}

TEST_F(ProgFromRegexTest_117, CanBitStateSimpleRegex_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  // Just test that CanBitState returns a valid result
  bool can = p->CanBitState();
  (void)can;
}

TEST_F(ProgFromRegexTest_117, SearchBitStateMatch_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  if (p->CanBitState()) {
    absl::string_view text("xabcx");
    absl::string_view match;
    bool found = p->SearchBitState(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "abc");
  }
}

TEST_F(ProgFromRegexTest_117, SearchBitStateNoMatch_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  if (p->CanBitState()) {
    absl::string_view text("xyz");
    absl::string_view match;
    bool found = p->SearchBitState(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, 1);
    EXPECT_FALSE(found);
  }
}

TEST_F(ProgFromRegexTest_117, PossibleMatchRangeForSimpleRegex_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  std::string min_str, max_str;
  bool ok = p->PossibleMatchRange(&min_str, &max_str, 10);
  if (ok) {
    EXPECT_LE(min_str, "abc");
    EXPECT_GE(max_str, "abc");
  }
}

TEST_F(ProgFromRegexTest_117, DumpUnanchored_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  std::string dump = p->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexTest_117, DumpByteMap_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  std::string dump = p->DumpByteMap();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexTest_117, FlattenDoesNotCrash_117) {
  Prog* p = CompileRegex("a|b|c");
  ASSERT_NE(p, nullptr);
  p->Flatten();
  // After flattening, the program should still be usable
  EXPECT_GT(p->size(), 0);
}

TEST_F(ProgFromRegexTest_117, OptimizeDoesNotCrash_117) {
  Prog* p = CompileRegex("a|b|c");
  ASSERT_NE(p, nullptr);
  p->Optimize();
  EXPECT_GT(p->size(), 0);
}

TEST_F(ProgFromRegexTest_117, AnchoredSearchNFA_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

TEST_F(ProgFromRegexTest_117, AnchoredSearchNFANoMatch_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  absl::string_view text("xabc");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kAnchored, Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgFromRegexTest_117, SearchNFAEmptyText_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  absl::string_view text("");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgFromRegexTest_117, SearchNFAEmptyPattern_117) {
  Prog* p = CompileRegex("");
  ASSERT_NE(p, nullptr);
  absl::string_view text("abc");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kUnanchored, Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0u);
}

TEST_F(ProgFromRegexTest_117, ConfigurePrefixAccelDoesNotCrash_117) {
  Prog* p = CompileRegex("abc");
  ASSERT_NE(p, nullptr);
  p->ConfigurePrefixAccel("abc", false);
  // After configuring prefix accel, can_prefix_accel may become true
  // depending on implementation
}

TEST_F(ProgFromRegexTest_117, BuildEntireDFA_117) {
  Prog* p = CompileRegex("a");
  ASSERT_NE(p, nullptr);
  p->set_dfa_mem(1 << 20);
  int states = p->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GE(states, 0);
}

// Test CompileSet
TEST(ProgCompileSetTest_117, CompileSetSimple_117) {
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

// Test multiple set/get cycles for reversed
TEST_F(ProgTest_117, ReversedToggle_117) {
  EXPECT_FALSE(prog_->reversed());
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
  prog_->set_reversed(false);
  EXPECT_FALSE(prog_->reversed());
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
}

// Test multiple set/get cycles for dfa_mem
TEST_F(ProgTest_117, DfaMemMultipleSet_117) {
  prog_->set_dfa_mem(100);
  EXPECT_EQ(prog_->dfa_mem(), 100);
  prog_->set_dfa_mem(0);
  EXPECT_EQ(prog_->dfa_mem(), 0);
  prog_->set_dfa_mem(INT64_MAX);
  EXPECT_EQ(prog_->dfa_mem(), INT64_MAX);
}

// Test set_start with boundary values
TEST_F(ProgTest_117, SetStartBoundary_117) {
  prog_->set_start(0);
  EXPECT_EQ(prog_->start(), 0);
  prog_->set_start(-1);
  EXPECT_EQ(prog_->start(), -1);
}

// Test set_start_unanchored with boundary values
TEST_F(ProgTest_117, SetStartUnanchoredBoundary_117) {
  prog_->set_start_unanchored(0);
  EXPECT_EQ(prog_->start_unanchored(), 0);
  prog_->set_start_unanchored(-1);
  EXPECT_EQ(prog_->start_unanchored(), -1);
}

}  // namespace re2
