#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"

namespace re2 {

class ProgTest_126 : public ::testing::Test {
 protected:
  void SetUp() override {
    prog_ = new Prog();
  }
  void TearDown() override {
    delete prog_;
    prog_ = nullptr;
  }
  Prog* prog_;
};

// Test default construction values
TEST_F(ProgTest_126, DefaultConstruction_AnchorEnd_126) {
  EXPECT_FALSE(prog_->anchor_end());
}

TEST_F(ProgTest_126, DefaultConstruction_AnchorStart_126) {
  EXPECT_FALSE(prog_->anchor_start());
}

TEST_F(ProgTest_126, DefaultConstruction_Reversed_126) {
  EXPECT_FALSE(prog_->reversed());
}

TEST_F(ProgTest_126, DefaultConstruction_Start_126) {
  EXPECT_EQ(0, prog_->start());
}

TEST_F(ProgTest_126, DefaultConstruction_StartUnanchored_126) {
  EXPECT_EQ(0, prog_->start_unanchored());
}

TEST_F(ProgTest_126, DefaultConstruction_BytemapRange_126) {
  EXPECT_EQ(0, prog_->bytemap_range());
}

TEST_F(ProgTest_126, DefaultConstruction_DfaMem_126) {
  EXPECT_EQ(0, prog_->dfa_mem());
}

// Test set_anchor_end
TEST_F(ProgTest_126, SetAnchorEndTrue_126) {
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_end());
}

TEST_F(ProgTest_126, SetAnchorEndFalse_126) {
  prog_->set_anchor_end(true);
  prog_->set_anchor_end(false);
  EXPECT_FALSE(prog_->anchor_end());
}

// Test set_anchor_start
TEST_F(ProgTest_126, SetAnchorStartTrue_126) {
  prog_->set_anchor_start(true);
  EXPECT_TRUE(prog_->anchor_start());
}

TEST_F(ProgTest_126, SetAnchorStartFalse_126) {
  prog_->set_anchor_start(true);
  prog_->set_anchor_start(false);
  EXPECT_FALSE(prog_->anchor_start());
}

// Test set_reversed
TEST_F(ProgTest_126, SetReversedTrue_126) {
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
}

TEST_F(ProgTest_126, SetReversedFalse_126) {
  prog_->set_reversed(true);
  prog_->set_reversed(false);
  EXPECT_FALSE(prog_->reversed());
}

// Test set_start
TEST_F(ProgTest_126, SetStart_126) {
  prog_->set_start(42);
  EXPECT_EQ(42, prog_->start());
}

TEST_F(ProgTest_126, SetStartZero_126) {
  prog_->set_start(10);
  prog_->set_start(0);
  EXPECT_EQ(0, prog_->start());
}

// Test set_start_unanchored
TEST_F(ProgTest_126, SetStartUnanchored_126) {
  prog_->set_start_unanchored(99);
  EXPECT_EQ(99, prog_->start_unanchored());
}

// Test set_dfa_mem
TEST_F(ProgTest_126, SetDfaMem_126) {
  prog_->set_dfa_mem(1024 * 1024);
  EXPECT_EQ(1024 * 1024, prog_->dfa_mem());
}

TEST_F(ProgTest_126, SetDfaMemZero_126) {
  prog_->set_dfa_mem(0);
  EXPECT_EQ(0, prog_->dfa_mem());
}

TEST_F(ProgTest_126, SetDfaMemLarge_126) {
  int64_t large_val = static_cast<int64_t>(1) << 30;
  prog_->set_dfa_mem(large_val);
  EXPECT_EQ(large_val, prog_->dfa_mem());
}

// Test can_prefix_accel on default prog (no prefix configured)
TEST_F(ProgTest_126, DefaultCanPrefixAccel_126) {
  EXPECT_FALSE(prog_->can_prefix_accel());
}

// Test IsWordChar static method
TEST_F(ProgTest_126, IsWordCharAlpha_126) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
}

TEST_F(ProgTest_126, IsWordCharDigit_126) {
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
}

TEST_F(ProgTest_126, IsWordCharUnderscore_126) {
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

TEST_F(ProgTest_126, IsWordCharSpace_126) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
}

TEST_F(ProgTest_126, IsWordCharSpecial_126) {
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
}

// Test EmptyFlags static method
TEST_F(ProgTest_126, EmptyFlagsAtBeginning_126) {
  absl::string_view text("hello");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At beginning of text, kEmptyBeginText and kEmptyBeginLine should be set
  // We can at least verify it returns a non-zero value (begin of text)
  EXPECT_NE(0u, flags);
}

TEST_F(ProgTest_126, EmptyFlagsAtEnd_126) {
  absl::string_view text("hello");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At end of text, kEmptyEndText and kEmptyEndLine should be set
  EXPECT_NE(0u, flags);
}

TEST_F(ProgTest_126, EmptyFlagsEmptyString_126) {
  absl::string_view text("");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // Both begin and end flags should be set
  EXPECT_NE(0u, flags);
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_126, SetDfaShouldBailWhenSlow_126) {
  // Just verify it doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Tests using compiled programs from regexps
class ProgFromRegexpTest_126 : public ::testing::Test {
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
    prog_ = nullptr;
    if (re_) {
      re_->Decref();
      re_ = nullptr;
    }
  }

  Regexp* re_ = nullptr;
  Prog* prog_ = nullptr;
};

TEST_F(ProgFromRegexpTest_126, SimplePatternDump_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  std::string dump = p->Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexpTest_126, SimplePatternSize_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  EXPECT_GT(p->size(), 0);
}

TEST_F(ProgFromRegexpTest_126, AnchoredPatternStart_126) {
  Prog* p = CompileRegexp("^abc$");
  ASSERT_NE(nullptr, p);
  // The anchor flags should reflect the pattern
  // ^abc$ should have anchor_start and anchor_end set
  // (depending on compilation, these may or may not be set, 
  //  but we can still test the getters work)
  // Just verify no crash
  p->anchor_start();
  p->anchor_end();
}

TEST_F(ProgFromRegexpTest_126, BytemapNotNull_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  p->ComputeByteMap();
  const uint8_t* bm = p->bytemap();
  EXPECT_NE(nullptr, bm);
  EXPECT_GT(p->bytemap_range(), 0);
}

TEST_F(ProgFromRegexpTest_126, DumpByteMap_126) {
  Prog* p = CompileRegexp("[a-z]+");
  ASSERT_NE(nullptr, p);
  p->ComputeByteMap();
  std::string dump = p->DumpByteMap();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexpTest_126, DumpUnanchored_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  std::string dump = p->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexpTest_126, PossibleMatchRange_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  std::string min_str, max_str;
  bool result = p->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_str, max_str);
}

TEST_F(ProgFromRegexpTest_126, PossibleMatchRangeMaxLenZero_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  std::string min_str, max_str;
  // maxlen of 0 is an edge case
  bool result = p->PossibleMatchRange(&min_str, &max_str, 0);
  // Just verify no crash - result may or may not be true
  (void)result;
}

TEST_F(ProgFromRegexpTest_126, IsOnePassSimple_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  // Simple literal should be one-pass
  bool onepass = p->IsOnePass();
  // We just test it doesn't crash; the result depends on the pattern
  (void)onepass;
}

TEST_F(ProgFromRegexpTest_126, CanBitState_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  bool can = p->CanBitState();
  // For a simple pattern with default mem, this should generally be true
  (void)can;
}

TEST_F(ProgFromRegexpTest_126, Flatten_126) {
  Prog* p = CompileRegexp("a|b|c");
  ASSERT_NE(nullptr, p);
  p->Flatten();
  // After flattening, dump should still work
  std::string dump = p->Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexpTest_126, Optimize_126) {
  Prog* p = CompileRegexp("a|b|c");
  ASSERT_NE(nullptr, p);
  p->Optimize();
  // After optimizing, dump should still work
  std::string dump = p->Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexpTest_126, ConfigurePrefixAccelSimple_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  p->ComputeByteMap();
  p->ConfigurePrefixAccel("abc", false);
  // After configuring, can_prefix_accel might be true
  // Just verify no crash
  p->can_prefix_accel();
}

TEST_F(ProgFromRegexpTest_126, SearchNFASimpleMatch_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  absl::string_view text("xabcy");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kUnanchored,
                             Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ("abc", match);
}

TEST_F(ProgFromRegexpTest_126, SearchNFANoMatch_126) {
  Prog* p = CompileRegexp("xyz");
  ASSERT_NE(nullptr, p);
  absl::string_view text("abc");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kUnanchored,
                             Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgFromRegexpTest_126, SearchNFAAnchored_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kAnchored,
                             Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgFromRegexpTest_126, SearchNFAAnchoredNoMatch_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  absl::string_view text("xabc");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kAnchored,
                             Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgFromRegexpTest_126, SearchDFASimpleMatch_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  p->set_dfa_mem(1 << 20);
  absl::string_view text("xabcy");
  absl::string_view match;
  bool failed = false;
  bool found = p->SearchDFA(text, text, Prog::kUnanchored,
                              Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_TRUE(found);
}

TEST_F(ProgFromRegexpTest_126, SearchDFANoMatch_126) {
  Prog* p = CompileRegexp("xyz");
  ASSERT_NE(nullptr, p);
  p->set_dfa_mem(1 << 20);
  absl::string_view text("abc");
  absl::string_view match;
  bool failed = false;
  bool found = p->SearchDFA(text, text, Prog::kUnanchored,
                              Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  EXPECT_FALSE(found);
}

TEST_F(ProgFromRegexpTest_126, SearchBitStateSimpleMatch_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  if (!p->CanBitState()) return;
  absl::string_view text("xabcy");
  absl::string_view match;
  bool found = p->SearchBitState(text, text, Prog::kUnanchored,
                                   Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ("abc", match);
}

TEST_F(ProgFromRegexpTest_126, SearchBitStateNoMatch_126) {
  Prog* p = CompileRegexp("xyz");
  ASSERT_NE(nullptr, p);
  if (!p->CanBitState()) return;
  absl::string_view text("abc");
  absl::string_view match;
  bool found = p->SearchBitState(text, text, Prog::kUnanchored,
                                   Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgFromRegexpTest_126, SearchOnePassSimpleMatch_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  if (!p->IsOnePass()) return;
  absl::string_view text("abc");
  absl::string_view match;
  bool found = p->SearchOnePass(text, text, Prog::kAnchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ("abc", match);
}

TEST_F(ProgFromRegexpTest_126, SearchOnePassNoMatch_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  if (!p->IsOnePass()) return;
  absl::string_view text("xyz");
  absl::string_view match;
  bool found = p->SearchOnePass(text, text, Prog::kAnchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgFromRegexpTest_126, EmptyPattern_126) {
  Prog* p = CompileRegexp("");
  ASSERT_NE(nullptr, p);
  absl::string_view text("abc");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kUnanchored,
                             Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ("", match);
}

TEST_F(ProgFromRegexpTest_126, EmptyText_126) {
  Prog* p = CompileRegexp("abc");
  ASSERT_NE(nullptr, p);
  absl::string_view text("");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kUnanchored,
                             Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgFromRegexpTest_126, EmptyPatternEmptyText_126) {
  Prog* p = CompileRegexp("");
  ASSERT_NE(nullptr, p);
  absl::string_view text("");
  absl::string_view match;
  bool found = p->SearchNFA(text, text, Prog::kUnanchored,
                             Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ("", match);
}

// Test CompileSet
TEST(ProgCompileSetTest_126, CompileSetBasic_126) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* p = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(nullptr, p);
  delete p;
  re->Decref();
}

// Test toggle anchor values multiple times
TEST_F(ProgTest_126, ToggleAnchorEnd_126) {
  EXPECT_FALSE(prog_->anchor_end());
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_end());
  prog_->set_anchor_end(false);
  EXPECT_FALSE(prog_->anchor_end());
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_end());
}

TEST_F(ProgTest_126, ToggleAnchorStart_126) {
  EXPECT_FALSE(prog_->anchor_start());
  prog_->set_anchor_start(true);
  EXPECT_TRUE(prog_->anchor_start());
  prog_->set_anchor_start(false);
  EXPECT_FALSE(prog_->anchor_start());
}

// Test size on default prog
TEST_F(ProgTest_126, DefaultSize_126) {
  EXPECT_EQ(0, prog_->size());
}

// Test bytemap on default prog
TEST_F(ProgTest_126, DefaultBytemap_126) {
  const uint8_t* bm = prog_->bytemap();
  EXPECT_NE(nullptr, bm);
}

// Test PrefixAccel on default prog (no prefix configured)
TEST_F(ProgTest_126, DefaultPrefixAccelReturnsNull_126) {
  EXPECT_FALSE(prog_->can_prefix_accel());
}

// Test BuildEntireDFA
TEST_F(ProgFromRegexpTest_126, BuildEntireDFA_126) {
  Prog* p = CompileRegexp("a[bc]d");
  ASSERT_NE(nullptr, p);
  p->set_dfa_mem(1 << 20);
  int num_states = p->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(num_states, 0);
}

}  // namespace re2
