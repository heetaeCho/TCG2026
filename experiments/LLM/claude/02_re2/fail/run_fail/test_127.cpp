#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/testing/regexp_generator.h"
#include "absl/strings/string_view.h"

namespace re2 {

class ProgTest_127 : public ::testing::Test {
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
TEST_F(ProgTest_127, DefaultConstructionValues_127) {
  EXPECT_FALSE(prog_->anchor_start());
  EXPECT_FALSE(prog_->anchor_end());
  EXPECT_FALSE(prog_->reversed());
  EXPECT_EQ(0, prog_->start());
  EXPECT_EQ(0, prog_->start_unanchored());
  EXPECT_EQ(0, prog_->size());
  EXPECT_EQ(0, prog_->bytemap_range());
  EXPECT_EQ(0, prog_->dfa_mem());
}

// Test set_anchor_end and anchor_end
TEST_F(ProgTest_127, SetAnchorEndTrue_127) {
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_end());
}

TEST_F(ProgTest_127, SetAnchorEndFalse_127) {
  prog_->set_anchor_end(true);
  prog_->set_anchor_end(false);
  EXPECT_FALSE(prog_->anchor_end());
}

// Test set_anchor_start and anchor_start
TEST_F(ProgTest_127, SetAnchorStartTrue_127) {
  prog_->set_anchor_start(true);
  EXPECT_TRUE(prog_->anchor_start());
}

TEST_F(ProgTest_127, SetAnchorStartFalse_127) {
  prog_->set_anchor_start(true);
  prog_->set_anchor_start(false);
  EXPECT_FALSE(prog_->anchor_start());
}

// Test set_reversed and reversed
TEST_F(ProgTest_127, SetReversedTrue_127) {
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
}

TEST_F(ProgTest_127, SetReversedFalse_127) {
  prog_->set_reversed(true);
  prog_->set_reversed(false);
  EXPECT_FALSE(prog_->reversed());
}

// Test set_start and start
TEST_F(ProgTest_127, SetStart_127) {
  prog_->set_start(42);
  EXPECT_EQ(42, prog_->start());
}

TEST_F(ProgTest_127, SetStartZero_127) {
  prog_->set_start(0);
  EXPECT_EQ(0, prog_->start());
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_127, SetStartUnanchored_127) {
  prog_->set_start_unanchored(7);
  EXPECT_EQ(7, prog_->start_unanchored());
}

// Test set_dfa_mem and dfa_mem
TEST_F(ProgTest_127, SetDfaMem_127) {
  prog_->set_dfa_mem(1024 * 1024);
  EXPECT_EQ(1024 * 1024, prog_->dfa_mem());
}

TEST_F(ProgTest_127, SetDfaMemZero_127) {
  prog_->set_dfa_mem(0);
  EXPECT_EQ(0, prog_->dfa_mem());
}

TEST_F(ProgTest_127, SetDfaMemLargeValue_127) {
  int64_t large_val = static_cast<int64_t>(1) << 30;
  prog_->set_dfa_mem(large_val);
  EXPECT_EQ(large_val, prog_->dfa_mem());
}

// Test can_prefix_accel on default prog (no prefix configured)
TEST_F(ProgTest_127, DefaultCanPrefixAccelFalse_127) {
  EXPECT_FALSE(prog_->can_prefix_accel());
}

// Test IsWordChar static method
TEST_F(ProgTest_127, IsWordCharAlpha_127) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
}

TEST_F(ProgTest_127, IsWordCharDigit_127) {
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
}

TEST_F(ProgTest_127, IsWordCharUnderscore_127) {
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

TEST_F(ProgTest_127, IsWordCharNonWord_127) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
}

// Test bytemap returns non-null
TEST_F(ProgTest_127, BytemapNotNull_127) {
  EXPECT_NE(nullptr, prog_->bytemap());
}

// Test set_anchor combinations
TEST_F(ProgTest_127, BothAnchors_127) {
  prog_->set_anchor_start(true);
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_start());
  EXPECT_TRUE(prog_->anchor_end());
}

TEST_F(ProgTest_127, ToggleAnchors_127) {
  prog_->set_anchor_start(true);
  prog_->set_anchor_end(true);
  prog_->set_anchor_start(false);
  EXPECT_FALSE(prog_->anchor_start());
  EXPECT_TRUE(prog_->anchor_end());
}

// Test EmptyFlags static method
TEST_F(ProgTest_127, EmptyFlagsAtBeginning_127) {
  absl::string_view text("hello");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At the beginning of text, kEmptyBeginText should be set
  // We just check it returns a non-arbitrary value; exact flags depend on implementation
  // but at least it shouldn't crash
  (void)flags;
}

TEST_F(ProgTest_127, EmptyFlagsAtEnd_127) {
  absl::string_view text("hello");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  (void)flags;
}

TEST_F(ProgTest_127, EmptyFlagsEmptyText_127) {
  absl::string_view text("");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  (void)flags;
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_127, SetDfaShouldBailWhenSlow_127) {
  // This is a static method; just verify it doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test with a compiled Prog via RE2 internals (using Regexp::Parse and Compile)
class ProgCompiledTest_127 : public ::testing::Test {
 protected:
  void SetUp() override {
    RegexpStatus status;
    re_ = Regexp::Parse("a+b", Regexp::LikePerl, &status);
    ASSERT_NE(nullptr, re_);
    prog_ = re_->CompileToProg(0);
    ASSERT_NE(nullptr, prog_);
  }
  void TearDown() override {
    delete prog_;
    re_->Decref();
  }
  Regexp* re_;
  Prog* prog_;
};

TEST_F(ProgCompiledTest_127, DumpNotEmpty_127) {
  std::string dump = prog_->Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgCompiledTest_127, DumpUnanchoredNotEmpty_127) {
  std::string dump = prog_->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgCompiledTest_127, DumpByteMapNotEmpty_127) {
  std::string dump = prog_->DumpByteMap();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgCompiledTest_127, SizePositive_127) {
  EXPECT_GT(prog_->size(), 0);
}

TEST_F(ProgCompiledTest_127, BytemapRangePositive_127) {
  EXPECT_GT(prog_->bytemap_range(), 0);
}

TEST_F(ProgCompiledTest_127, PossibleMatchRange_127) {
  std::string min_str, max_str;
  bool result = prog_->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_str, max_str);
}

TEST_F(ProgCompiledTest_127, PossibleMatchRangeMaxLenZero_127) {
  std::string min_str, max_str;
  // maxlen of 0 is a boundary condition
  bool result = prog_->PossibleMatchRange(&min_str, &max_str, 0);
  // Just ensure no crash; result may vary
  (void)result;
}

TEST_F(ProgCompiledTest_127, SearchNFAMatch_127) {
  absl::string_view text("aaab");
  absl::string_view match;
  bool found = prog_->SearchNFA(text, text, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgCompiledTest_127, SearchNFANoMatch_127) {
  absl::string_view text("cccc");
  absl::string_view match;
  bool found = prog_->SearchNFA(text, text, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgCompiledTest_127, SearchBitStateMatch_127) {
  if (!prog_->CanBitState()) return;
  absl::string_view text("aaab");
  absl::string_view match;
  bool found = prog_->SearchBitState(text, text, Prog::kAnchored,
                                      Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgCompiledTest_127, SearchBitStateNoMatch_127) {
  if (!prog_->CanBitState()) return;
  absl::string_view text("cccc");
  absl::string_view match;
  bool found = prog_->SearchBitState(text, text, Prog::kAnchored,
                                      Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgCompiledTest_127, SearchDFAMatch_127) {
  prog_->set_dfa_mem(1 << 20);
  absl::string_view text("aaab");
  absl::string_view match;
  bool failed = false;
  bool found = prog_->SearchDFA(text, text, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
}

TEST_F(ProgCompiledTest_127, SearchDFANoMatch_127) {
  prog_->set_dfa_mem(1 << 20);
  absl::string_view text("cccc");
  absl::string_view match;
  bool failed = false;
  bool found = prog_->SearchDFA(text, text, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(found);
  }
}

TEST_F(ProgCompiledTest_127, IsOnePassCheck_127) {
  // Just ensure it doesn't crash and returns a bool
  bool result = prog_->IsOnePass();
  (void)result;
}

TEST_F(ProgCompiledTest_127, CanBitStateCheck_127) {
  bool result = prog_->CanBitState();
  (void)result;
}

TEST_F(ProgCompiledTest_127, FlattenDoesNotCrash_127) {
  prog_->Flatten();
  // After flattening, size should still be positive
  EXPECT_GT(prog_->size(), 0);
}

TEST_F(ProgCompiledTest_127, OptimizeDoesNotCrash_127) {
  prog_->Optimize();
}

// Test with a more complex pattern
class ProgComplexTest_127 : public ::testing::Test {
 protected:
  void SetUp() override {
    RegexpStatus status;
    re_ = Regexp::Parse("(foo|bar)baz", Regexp::LikePerl, &status);
    ASSERT_NE(nullptr, re_);
    prog_ = re_->CompileToProg(1 << 20);
    ASSERT_NE(nullptr, prog_);
  }
  void TearDown() override {
    delete prog_;
    re_->Decref();
  }
  Regexp* re_;
  Prog* prog_;
};

TEST_F(ProgComplexTest_127, SearchNFAMatchFoo_127) {
  absl::string_view text("foobaz");
  absl::string_view match[2];
  bool found = prog_->SearchNFA(text, text, Prog::kAnchored,
                                 Prog::kFirstMatch, match, 2);
  EXPECT_TRUE(found);
}

TEST_F(ProgComplexTest_127, SearchNFAMatchBar_127) {
  absl::string_view text("barbaz");
  absl::string_view match[2];
  bool found = prog_->SearchNFA(text, text, Prog::kAnchored,
                                 Prog::kFirstMatch, match, 2);
  EXPECT_TRUE(found);
}

TEST_F(ProgComplexTest_127, SearchNFANoMatch_127) {
  absl::string_view text("quxbaz");
  absl::string_view match[2];
  bool found = prog_->SearchNFA(text, text, Prog::kAnchored,
                                 Prog::kFirstMatch, match, 2);
  EXPECT_FALSE(found);
}

TEST_F(ProgComplexTest_127, UnanchoredSearch_127) {
  absl::string_view text("xxxfoobazyyy");
  absl::string_view match[2];
  bool found = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                 Prog::kFirstMatch, match, 2);
  EXPECT_TRUE(found);
}

// Test CompileSet
TEST(ProgCompileSetTest_127, CompileSetBasic_127) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  // CompileSet may or may not succeed depending on internals
  if (prog != nullptr) {
    EXPECT_GT(prog->size(), 0);
    delete prog;
  }
  re->Decref();
}

// Test setting multiple properties in sequence
TEST_F(ProgTest_127, SetMultipleProperties_127) {
  prog_->set_anchor_start(true);
  prog_->set_anchor_end(true);
  prog_->set_reversed(true);
  prog_->set_start(5);
  prog_->set_start_unanchored(3);
  prog_->set_dfa_mem(2048);

  EXPECT_TRUE(prog_->anchor_start());
  EXPECT_TRUE(prog_->anchor_end());
  EXPECT_TRUE(prog_->reversed());
  EXPECT_EQ(5, prog_->start());
  EXPECT_EQ(3, prog_->start_unanchored());
  EXPECT_EQ(2048, prog_->dfa_mem());
}

// Test PrefixAccel on default prog (no prefix configured)
TEST_F(ProgTest_127, PrefixAccelNullWhenNotConfigured_127) {
  const char data[] = "hello world";
  const void* result = prog_->PrefixAccel(data, sizeof(data) - 1);
  // Without prefix acceleration configured, should return nullptr
  EXPECT_EQ(nullptr, result);
}

// Test IsWordChar boundary values
TEST_F(ProgTest_127, IsWordCharBoundaryValues_127) {
  // '/' is just before '0'
  EXPECT_FALSE(Prog::IsWordChar('/'));
  // ':' is just after '9'
  EXPECT_FALSE(Prog::IsWordChar(':'));
  // '@' is just before 'A'
  EXPECT_FALSE(Prog::IsWordChar('@'));
  // '[' is just after 'Z'
  EXPECT_FALSE(Prog::IsWordChar('['));
  // '`' is just before 'a'
  EXPECT_FALSE(Prog::IsWordChar('`'));
  // '{' is just after 'z'
  EXPECT_FALSE(Prog::IsWordChar('{'));
  // '^' is between 'Z'+1 and 'a'-1 but not '_'
  EXPECT_FALSE(Prog::IsWordChar('^'));
}

TEST_F(ProgTest_127, IsWordCharAllDigits_127) {
  for (char c = '0'; c <= '9'; ++c) {
    EXPECT_TRUE(Prog::IsWordChar(static_cast<uint8_t>(c))) << "char: " << c;
  }
}

TEST_F(ProgTest_127, IsWordCharAllLower_127) {
  for (char c = 'a'; c <= 'z'; ++c) {
    EXPECT_TRUE(Prog::IsWordChar(static_cast<uint8_t>(c))) << "char: " << c;
  }
}

TEST_F(ProgTest_127, IsWordCharAllUpper_127) {
  for (char c = 'A'; c <= 'Z'; ++c) {
    EXPECT_TRUE(Prog::IsWordChar(static_cast<uint8_t>(c))) << "char: " << c;
  }
}

}  // namespace re2
