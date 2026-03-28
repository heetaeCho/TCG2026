#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/testing/regexp_generator.h"
#include "absl/strings/string_view.h"

namespace re2 {

class ProgTest_123 : public ::testing::Test {
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
TEST_F(ProgTest_123, DefaultConstructionValues_123) {
  EXPECT_EQ(prog_->start(), 0);
  EXPECT_EQ(prog_->start_unanchored(), 0);
  EXPECT_EQ(prog_->size(), 0);
  EXPECT_FALSE(prog_->reversed());
  EXPECT_FALSE(prog_->anchor_start());
  EXPECT_FALSE(prog_->anchor_end());
  EXPECT_EQ(prog_->dfa_mem(), 0);
  EXPECT_EQ(prog_->bytemap_range(), 0);
}

// Test set_dfa_mem and dfa_mem
TEST_F(ProgTest_123, SetDfaMem_123) {
  prog_->set_dfa_mem(1024);
  EXPECT_EQ(prog_->dfa_mem(), 1024);
}

TEST_F(ProgTest_123, SetDfaMemZero_123) {
  prog_->set_dfa_mem(0);
  EXPECT_EQ(prog_->dfa_mem(), 0);
}

TEST_F(ProgTest_123, SetDfaMemLargeValue_123) {
  int64_t large_val = static_cast<int64_t>(1) << 40;  // 1TB
  prog_->set_dfa_mem(large_val);
  EXPECT_EQ(prog_->dfa_mem(), large_val);
}

TEST_F(ProgTest_123, SetDfaMemNegativeValue_123) {
  prog_->set_dfa_mem(-1);
  EXPECT_EQ(prog_->dfa_mem(), -1);
}

TEST_F(ProgTest_123, SetDfaMemOverwrite_123) {
  prog_->set_dfa_mem(100);
  EXPECT_EQ(prog_->dfa_mem(), 100);
  prog_->set_dfa_mem(200);
  EXPECT_EQ(prog_->dfa_mem(), 200);
}

// Test set_start and start
TEST_F(ProgTest_123, SetStart_123) {
  prog_->set_start(5);
  EXPECT_EQ(prog_->start(), 5);
}

TEST_F(ProgTest_123, SetStartZero_123) {
  prog_->set_start(0);
  EXPECT_EQ(prog_->start(), 0);
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_123, SetStartUnanchored_123) {
  prog_->set_start_unanchored(3);
  EXPECT_EQ(prog_->start_unanchored(), 3);
}

// Test set_reversed and reversed
TEST_F(ProgTest_123, SetReversedTrue_123) {
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
}

TEST_F(ProgTest_123, SetReversedFalse_123) {
  prog_->set_reversed(false);
  EXPECT_FALSE(prog_->reversed());
}

TEST_F(ProgTest_123, SetReversedToggle_123) {
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
  prog_->set_reversed(false);
  EXPECT_FALSE(prog_->reversed());
}

// Test set_anchor_start and anchor_start
TEST_F(ProgTest_123, SetAnchorStartTrue_123) {
  prog_->set_anchor_start(true);
  EXPECT_TRUE(prog_->anchor_start());
}

TEST_F(ProgTest_123, SetAnchorStartFalse_123) {
  prog_->set_anchor_start(false);
  EXPECT_FALSE(prog_->anchor_start());
}

// Test set_anchor_end and anchor_end
TEST_F(ProgTest_123, SetAnchorEndTrue_123) {
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_end());
}

TEST_F(ProgTest_123, SetAnchorEndFalse_123) {
  prog_->set_anchor_end(false);
  EXPECT_FALSE(prog_->anchor_end());
}

// Test can_prefix_accel on default constructed prog (no prefix configured)
TEST_F(ProgTest_123, DefaultCanPrefixAccelFalse_123) {
  EXPECT_FALSE(prog_->can_prefix_accel());
}

// Test IsWordChar static method
TEST_F(ProgTest_123, IsWordCharAlpha_123) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
}

TEST_F(ProgTest_123, IsWordCharDigit_123) {
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
}

TEST_F(ProgTest_123, IsWordCharUnderscore_123) {
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

TEST_F(ProgTest_123, IsWordCharNonWord_123) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
}

// Test EmptyFlags static method
TEST_F(ProgTest_123, EmptyFlagsAtBeginning_123) {
  absl::string_view text("hello");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At beginning of text, kEmptyBeginText and kEmptyBeginLine should be set
  // We just verify it returns some flags (non-zero at beginning)
  EXPECT_NE(flags, 0u);
}

TEST_F(ProgTest_123, EmptyFlagsAtEnd_123) {
  absl::string_view text("hello");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At end of text, kEmptyEndText and kEmptyEndLine should be set
  EXPECT_NE(flags, 0u);
}

TEST_F(ProgTest_123, EmptyFlagsEmptyText_123) {
  absl::string_view text("");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // Both begin and end flags should be set
  EXPECT_NE(flags, 0u);
}

// Tests using compiled programs from RE2
class ProgFromRE2Test_123 : public ::testing::Test {
 protected:
};

TEST_F(ProgFromRE2Test_123, DumpSimplePattern_123) {
  // Use Regexp to compile a simple pattern
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, DumpUnanchoredSimplePattern_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, DumpByteMapSimplePattern_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, SizeNonZeroAfterCompile_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b+c+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  EXPECT_GT(prog->size(), 0);
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, BytemapRangeNonZeroAfterCompile_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_NE(prog->bytemap(), nullptr);
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, SearchNFASimpleMatch_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  absl::string_view text("say hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, SearchNFANoMatch_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("xyz", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  absl::string_view text("say hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, SearchNFAAnchored_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
  
  // Anchored should not match if pattern not at start
  absl::string_view text2("say hello");
  bool found2 = prog->SearchNFA(text2, text2, Prog::kAnchored,
                                  Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found2);
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, PossibleMatchRange_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc[def]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  std::string min_val, max_val;
  bool ok = prog->PossibleMatchRange(&min_val, &max_val, 10);
  EXPECT_TRUE(ok);
  EXPECT_LE(min_val, max_val);
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, PossibleMatchRangeMaxlenZero_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  std::string min_val, max_val;
  // maxlen of 0 should still work
  bool ok = prog->PossibleMatchRange(&min_val, &max_val, 0);
  // Result depends on implementation but shouldn't crash
  (void)ok;
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, IsOnePassSimple_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  prog->Flatten();
  // Simple patterns like ^abc$ are typically one-pass
  bool onepass = prog->IsOnePass();
  // We can just verify the call doesn't crash; the result is pattern-dependent
  (void)onepass;
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, SearchDFASimpleMatch_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(1 << 20);
  ASSERT_NE(prog, nullptr);
  
  prog->set_dfa_mem(1 << 20);
  
  absl::string_view text("hello world");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, SearchBitStateSimpleMatch_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  absl::string_view text("hello world");
  absl::string_view match;
  
  if (prog->CanBitState()) {
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "world");
  }
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, CanBitState_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  // Small pattern should be eligible for bit state
  // Just verify the call doesn't crash
  bool can = prog->CanBitState();
  (void)can;
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, CompileSetSimple_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def|ghi", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  // CompileSet may or may not succeed depending on the pattern
  if (prog != nullptr) {
    EXPECT_GT(prog->size(), 0);
    delete prog;
  }
  
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, FlattenDoesNotCrash_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  // Flatten should not crash
  prog->Flatten();
  
  // After flatten, the prog should still have valid size
  EXPECT_GT(prog->size(), 0);
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, OptimizeDoesNotCrash_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  prog->Optimize();
  EXPECT_GT(prog->size(), 0);
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, ConfigurePrefixAccelAndSearch_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello.*world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  prog->ConfigurePrefixAccel("hello", false);
  // After configuring prefix accel, can_prefix_accel may be true
  // depending on the implementation
  if (prog->can_prefix_accel()) {
    const char* data = "xxhelloxxworld";
    const void* result = prog->PrefixAccel(data, strlen(data));
    // Result should point somewhere in data or be null
    if (result != nullptr) {
      EXPECT_GE(static_cast<const char*>(result), data);
      EXPECT_LE(static_cast<const char*>(result), data + strlen(data));
    }
  }
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, PrefixAccelNullWhenNotConfigured_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  EXPECT_FALSE(prog->can_prefix_accel());
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, TestingOnlySetDfaShouldBailWhenSlow_123) {
  // Just verify it doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

TEST_F(ProgFromRE2Test_123, SearchNFAEmptyPattern_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  absl::string_view text("hello");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0u);
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, SearchNFAEmptyText_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, SearchNFAEmptyPatternEmptyText_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, BuildEntireDFA_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(1 << 20);
  ASSERT_NE(prog, nullptr);
  
  prog->set_dfa_mem(1 << 20);
  
  int states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  // Should return a non-negative number of states
  EXPECT_GE(states, 0);
  
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRE2Test_123, FanoutDoesNotCrash_123) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)d", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);
  
  delete prog;
  re->Decref();
}

}  // namespace re2
