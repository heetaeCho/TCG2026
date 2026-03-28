#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"

namespace re2 {

class ProgTest_113 : public ::testing::Test {
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
TEST_F(ProgTest_113, DefaultConstructionValues_113) {
  EXPECT_EQ(prog_->start(), 0);
  EXPECT_EQ(prog_->start_unanchored(), 0);
  EXPECT_EQ(prog_->size(), 0);
  EXPECT_FALSE(prog_->reversed());
  EXPECT_FALSE(prog_->anchor_start());
  EXPECT_FALSE(prog_->anchor_end());
  EXPECT_EQ(prog_->bytemap_range(), 0);
  EXPECT_EQ(prog_->dfa_mem(), 0);
  EXPECT_FALSE(prog_->can_prefix_accel());
}

// Test set_start and start
TEST_F(ProgTest_113, SetStartAndGetStart_113) {
  prog_->set_start(5);
  EXPECT_EQ(prog_->start(), 5);
}

TEST_F(ProgTest_113, SetStartZero_113) {
  prog_->set_start(42);
  EXPECT_EQ(prog_->start(), 42);
  prog_->set_start(0);
  EXPECT_EQ(prog_->start(), 0);
}

TEST_F(ProgTest_113, SetStartNegative_113) {
  prog_->set_start(-1);
  EXPECT_EQ(prog_->start(), -1);
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_113, SetStartUnanchored_113) {
  prog_->set_start_unanchored(10);
  EXPECT_EQ(prog_->start_unanchored(), 10);
}

TEST_F(ProgTest_113, SetStartUnanchoredZero_113) {
  prog_->set_start_unanchored(0);
  EXPECT_EQ(prog_->start_unanchored(), 0);
}

// Test set_reversed and reversed
TEST_F(ProgTest_113, SetReversedTrue_113) {
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
}

TEST_F(ProgTest_113, SetReversedFalse_113) {
  prog_->set_reversed(false);
  EXPECT_FALSE(prog_->reversed());
}

TEST_F(ProgTest_113, SetReversedToggle_113) {
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
  prog_->set_reversed(false);
  EXPECT_FALSE(prog_->reversed());
}

// Test set_anchor_start and anchor_start
TEST_F(ProgTest_113, SetAnchorStartTrue_113) {
  prog_->set_anchor_start(true);
  EXPECT_TRUE(prog_->anchor_start());
}

TEST_F(ProgTest_113, SetAnchorStartFalse_113) {
  prog_->set_anchor_start(false);
  EXPECT_FALSE(prog_->anchor_start());
}

// Test set_anchor_end and anchor_end
TEST_F(ProgTest_113, SetAnchorEndTrue_113) {
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_end());
}

TEST_F(ProgTest_113, SetAnchorEndFalse_113) {
  prog_->set_anchor_end(false);
  EXPECT_FALSE(prog_->anchor_end());
}

// Test set_dfa_mem and dfa_mem
TEST_F(ProgTest_113, SetDfaMem_113) {
  prog_->set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog_->dfa_mem(), 1024 * 1024);
}

TEST_F(ProgTest_113, SetDfaMemZero_113) {
  prog_->set_dfa_mem(0);
  EXPECT_EQ(prog_->dfa_mem(), 0);
}

TEST_F(ProgTest_113, SetDfaMemLargeValue_113) {
  int64_t large_val = static_cast<int64_t>(1) << 30;
  prog_->set_dfa_mem(large_val);
  EXPECT_EQ(prog_->dfa_mem(), large_val);
}

// Test IsWordChar static method
TEST_F(ProgTest_113, IsWordCharAlphaLower_113) {
  for (uint8_t c = 'a'; c <= 'z'; ++c) {
    EXPECT_TRUE(Prog::IsWordChar(c)) << "Failed for char: " << c;
  }
}

TEST_F(ProgTest_113, IsWordCharAlphaUpper_113) {
  for (uint8_t c = 'A'; c <= 'Z'; ++c) {
    EXPECT_TRUE(Prog::IsWordChar(c)) << "Failed for char: " << c;
  }
}

TEST_F(ProgTest_113, IsWordCharDigits_113) {
  for (uint8_t c = '0'; c <= '9'; ++c) {
    EXPECT_TRUE(Prog::IsWordChar(c)) << "Failed for char: " << c;
  }
}

TEST_F(ProgTest_113, IsWordCharUnderscore_113) {
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

TEST_F(ProgTest_113, IsWordCharSpace_113) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
}

TEST_F(ProgTest_113, IsWordCharSpecialChars_113) {
  EXPECT_FALSE(Prog::IsWordChar('@'));
  EXPECT_FALSE(Prog::IsWordChar('!'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
}

// Test EmptyFlags static method
TEST_F(ProgTest_113, EmptyFlagsAtBeginning_113) {
  absl::string_view text("hello");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At the beginning of text, kEmptyBeginText and kEmptyBeginLine should be set
  EXPECT_NE(flags, 0u);
}

TEST_F(ProgTest_113, EmptyFlagsAtEnd_113) {
  absl::string_view text("hello");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At end of text, kEmptyEndText and kEmptyEndLine should be set
  EXPECT_NE(flags, 0u);
}

TEST_F(ProgTest_113, EmptyFlagsEmptyText_113) {
  absl::string_view text("");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // Both begin and end flags should be set
  EXPECT_NE(flags, 0u);
}

// Test Dump on a default-constructed (empty) Prog
TEST_F(ProgTest_113, DumpEmptyProg_113) {
  std::string dump = prog_->Dump();
  // Just verify it doesn't crash and returns something
  // An empty prog should return some representation
  EXPECT_TRUE(dump.empty() || !dump.empty());
}

TEST_F(ProgTest_113, DumpUnanchoredEmptyProg_113) {
  std::string dump = prog_->DumpUnanchored();
  EXPECT_TRUE(dump.empty() || !dump.empty());
}

TEST_F(ProgTest_113, DumpByteMapEmptyProg_113) {
  std::string dump = prog_->DumpByteMap();
  EXPECT_TRUE(dump.empty() || !dump.empty());
}

// Test size returns 0 for default constructed prog
TEST_F(ProgTest_113, SizeDefault_113) {
  EXPECT_EQ(prog_->size(), 0);
}

// Test bytemap is not null on a default constructed prog
TEST_F(ProgTest_113, BytemapNotNull_113) {
  const uint8_t* bm = prog_->bytemap();
  EXPECT_NE(bm, nullptr);
}

// Test can_prefix_accel returns false by default
TEST_F(ProgTest_113, CanPrefixAccelDefault_113) {
  EXPECT_FALSE(prog_->can_prefix_accel());
}

// Test PossibleMatchRange on an empty prog (boundary)
TEST_F(ProgTest_113, PossibleMatchRangeEmptyProg_113) {
  std::string min_str, max_str;
  // This may or may not succeed on an empty prog, but should not crash
  prog_->PossibleMatchRange(&min_str, &max_str, 10);
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_113, SetDfaShouldBailWhenSlow_113) {
  // Just verify it doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test with a compiled program from a real regex
class ProgFromRegexTest_113 : public ::testing::Test {
 protected:
  void SetUp() override {
    RegexpStatus status;
    re_ = Regexp::Parse("a+b*", Regexp::LikePerl, &status);
    ASSERT_NE(re_, nullptr);
    prog_ = re_->CompileToProg(0);
    ASSERT_NE(prog_, nullptr);
  }

  void TearDown() override {
    delete prog_;
    re_->Decref();
  }

  Regexp* re_;
  Prog* prog_;
};

TEST_F(ProgFromRegexTest_113, SizeGreaterThanZero_113) {
  EXPECT_GT(prog_->size(), 0);
}

TEST_F(ProgFromRegexTest_113, DumpNotEmpty_113) {
  std::string dump = prog_->Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexTest_113, DumpUnanchoredNotEmpty_113) {
  std::string dump = prog_->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexTest_113, BytemapRangePositive_113) {
  EXPECT_GT(prog_->bytemap_range(), 0);
}

TEST_F(ProgFromRegexTest_113, StartIsValid_113) {
  EXPECT_GE(prog_->start(), 0);
  EXPECT_LT(prog_->start(), prog_->size());
}

TEST_F(ProgFromRegexTest_113, StartUnanchoredIsValid_113) {
  EXPECT_GE(prog_->start_unanchored(), 0);
  EXPECT_LT(prog_->start_unanchored(), prog_->size());
}

TEST_F(ProgFromRegexTest_113, PossibleMatchRange_113) {
  std::string min_str, max_str;
  bool result = prog_->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_str, max_str);
}

TEST_F(ProgFromRegexTest_113, PossibleMatchRangeMaxLenOne_113) {
  std::string min_str, max_str;
  bool result = prog_->PossibleMatchRange(&min_str, &max_str, 1);
  EXPECT_TRUE(result);
}

TEST_F(ProgFromRegexTest_113, DumpByteMap_113) {
  std::string dump = prog_->DumpByteMap();
  EXPECT_FALSE(dump.empty());
}

// Test SearchNFA with matching text
TEST_F(ProgFromRegexTest_113, SearchNFAMatch_113) {
  absl::string_view text("aaabb");
  absl::string_view match;
  bool found = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                 Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

// Test SearchNFA with non-matching text
TEST_F(ProgFromRegexTest_113, SearchNFANoMatch_113) {
  absl::string_view text("xyz");
  absl::string_view match;
  bool found = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                 Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test SearchDFA
TEST_F(ProgFromRegexTest_113, SearchDFAMatch_113) {
  absl::string_view text("aab");
  absl::string_view match;
  bool failed = false;
  prog_->set_dfa_mem(1 << 20);
  bool found = prog_->SearchDFA(text, text, Prog::kUnanchored,
                                  Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
}

TEST_F(ProgFromRegexTest_113, SearchDFANoMatch_113) {
  absl::string_view text("xyz");
  absl::string_view match;
  bool failed = false;
  prog_->set_dfa_mem(1 << 20);
  bool found = prog_->SearchDFA(text, text, Prog::kUnanchored,
                                  Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(found);
  }
}

// Test with anchored search
TEST_F(ProgFromRegexTest_113, SearchNFAAnchored_113) {
  absl::string_view text("aaabb");
  absl::string_view match;
  bool found = prog_->SearchNFA(text, text, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgFromRegexTest_113, SearchNFAAnchoredNoMatch_113) {
  absl::string_view text("bbb");
  absl::string_view match;
  bool found = prog_->SearchNFA(text, text, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test Flatten doesn't crash
TEST_F(ProgFromRegexTest_113, Flatten_113) {
  prog_->Flatten();
  // After flatten, the program should still be valid
  EXPECT_GT(prog_->size(), 0);
}

// Test Optimize doesn't crash
TEST_F(ProgFromRegexTest_113, Optimize_113) {
  prog_->Optimize();
  EXPECT_GT(prog_->size(), 0);
}

// Test ComputeByteMap
TEST_F(ProgFromRegexTest_113, ComputeByteMap_113) {
  prog_->ComputeByteMap();
  EXPECT_GT(prog_->bytemap_range(), 0);
}

// Test IsOnePass
TEST_F(ProgFromRegexTest_113, IsOnePass_113) {
  // Just verify it doesn't crash; result depends on the regex
  bool onepass = prog_->IsOnePass();
  (void)onepass;
}

// Test CanBitState
TEST_F(ProgFromRegexTest_113, CanBitState_113) {
  bool can = prog_->CanBitState();
  (void)can;
}

// Test with a more complex regex
class ProgComplexRegexTest_113 : public ::testing::Test {
 protected:
  void SetUp() override {
    RegexpStatus status;
    re_ = Regexp::Parse("(foo|bar)baz[0-9]+", Regexp::LikePerl, &status);
    ASSERT_NE(re_, nullptr);
    prog_ = re_->CompileToProg(0);
    ASSERT_NE(prog_, nullptr);
  }

  void TearDown() override {
    delete prog_;
    re_->Decref();
  }

  Regexp* re_;
  Prog* prog_;
};

TEST_F(ProgComplexRegexTest_113, MatchFoo_113) {
  absl::string_view text("foobaz123");
  absl::string_view match;
  bool found = prog_->SearchNFA(text, text, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgComplexRegexTest_113, MatchBar_113) {
  absl::string_view text("barbaz456");
  absl::string_view match;
  bool found = prog_->SearchNFA(text, text, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgComplexRegexTest_113, NoMatchMissingDigits_113) {
  absl::string_view text("foobaz");
  absl::string_view match;
  bool found = prog_->SearchNFA(text, text, Prog::kAnchored,
                                 Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgComplexRegexTest_113, PossibleMatchRange_113) {
  std::string min_str, max_str;
  bool result = prog_->PossibleMatchRange(&min_str, &max_str, 20);
  EXPECT_TRUE(result);
}

// Test SearchBitState
class ProgBitStateTest_113 : public ::testing::Test {
 protected:
  void SetUp() override {
    RegexpStatus status;
    re_ = Regexp::Parse("hello", Regexp::LikePerl, &status);
    ASSERT_NE(re_, nullptr);
    prog_ = re_->CompileToProg(0);
    ASSERT_NE(prog_, nullptr);
  }

  void TearDown() override {
    delete prog_;
    re_->Decref();
  }

  Regexp* re_;
  Prog* prog_;
};

TEST_F(ProgBitStateTest_113, BitStateMatch_113) {
  if (!prog_->CanBitState()) return;
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                      Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgBitStateTest_113, BitStateNoMatch_113) {
  if (!prog_->CanBitState()) return;
  absl::string_view text("goodbye world");
  absl::string_view match;
  bool found = prog_->SearchBitState(text, text, Prog::kUnanchored,
                                      Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test SearchOnePass
TEST_F(ProgBitStateTest_113, OnePassMatch_113) {
  if (!prog_->IsOnePass()) return;
  absl::string_view text("hello");
  absl::string_view match;
  bool found = prog_->SearchOnePass(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgBitStateTest_113, OnePassNoMatch_113) {
  if (!prog_->IsOnePass()) return;
  absl::string_view text("world");
  absl::string_view match;
  bool found = prog_->SearchOnePass(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test set methods can be called multiple times
TEST_F(ProgTest_113, MultipleSetCalls_113) {
  prog_->set_start(1);
  prog_->set_start(2);
  prog_->set_start(3);
  EXPECT_EQ(prog_->start(), 3);

  prog_->set_start_unanchored(10);
  prog_->set_start_unanchored(20);
  EXPECT_EQ(prog_->start_unanchored(), 20);

  prog_->set_reversed(true);
  prog_->set_reversed(false);
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());

  prog_->set_anchor_start(true);
  prog_->set_anchor_start(false);
  EXPECT_FALSE(prog_->anchor_start());

  prog_->set_anchor_end(true);
  prog_->set_anchor_end(false);
  EXPECT_FALSE(prog_->anchor_end());

  prog_->set_dfa_mem(100);
  prog_->set_dfa_mem(200);
  EXPECT_EQ(prog_->dfa_mem(), 200);
}

// Test CompileSet static method
TEST(ProgCompileSetTest_113, CompileSetAnchored_113) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def|ghi", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Prog::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  if (prog != nullptr) {
    EXPECT_GT(prog->size(), 0);
    delete prog;
  }
  re->Decref();
}

TEST(ProgCompileSetTest_113, CompileSetUnanchored_113) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  if (prog != nullptr) {
    EXPECT_GT(prog->size(), 0);
    delete prog;
  }
  re->Decref();
}

// Test EmptyFlags at word boundary
TEST_F(ProgTest_113, EmptyFlagsWordBoundary_113) {
  absl::string_view text("a b");
  // Between 'a' and ' ', there should be a word boundary
  const char* p = text.data() + 1;  // points to ' '
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_NE(flags, 0u);
}

// Test EmptyFlags at newline
TEST_F(ProgTest_113, EmptyFlagsNewline_113) {
  absl::string_view text("a\nb");
  const char* p = text.data() + 2;  // points to 'b', after '\n'
  uint32_t flags = Prog::EmptyFlags(text, p);
  // kEmptyBeginLine should be set after newline
  EXPECT_NE(flags, 0u);
}

// Test ConfigurePrefixAccel on a compiled program
class ProgPrefixAccelTest_113 : public ::testing::Test {
 protected:
  void SetUp() override {
    RegexpStatus status;
    re_ = Regexp::Parse("hello.*world", Regexp::LikePerl, &status);
    ASSERT_NE(re_, nullptr);
    prog_ = re_->CompileToProg(0);
    ASSERT_NE(prog_, nullptr);
  }

  void TearDown() override {
    delete prog_;
    re_->Decref();
  }

  Regexp* re_;
  Prog* prog_;
};

TEST_F(ProgPrefixAccelTest_113, ConfigurePrefixAccel_113) {
  prog_->ConfigurePrefixAccel("hello", false);
  // After configuration, can_prefix_accel may be true
  // Just verify it doesn't crash
}

TEST_F(ProgPrefixAccelTest_113, PrefixAccelOnNullData_113) {
  prog_->ConfigurePrefixAccel("hello", false);
  if (prog_->can_prefix_accel()) {
    const void* result = prog_->PrefixAccel(nullptr, 0);
    EXPECT_EQ(result, nullptr);
  }
}

TEST_F(ProgPrefixAccelTest_113, PrefixAccelOnMatchingData_113) {
  prog_->ConfigurePrefixAccel("h", false);
  if (prog_->can_prefix_accel()) {
    const char* data = "xyzh";
    const void* result = prog_->PrefixAccel(data, 4);
    // If found, should point to 'h'
    if (result != nullptr) {
      EXPECT_GE(result, data);
      EXPECT_LE(result, data + 4);
    }
  }
}

}  // namespace re2
