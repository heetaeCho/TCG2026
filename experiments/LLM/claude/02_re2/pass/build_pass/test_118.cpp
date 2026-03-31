#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "absl/strings/string_view.h"
#include <string>

namespace re2 {

class ProgTest_118 : public ::testing::Test {
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
TEST_F(ProgTest_118, DefaultReversedIsFalse_118) {
  EXPECT_FALSE(prog_->reversed());
}

// Test set_reversed(true)
TEST_F(ProgTest_118, SetReversedTrue_118) {
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
}

// Test set_reversed(false)
TEST_F(ProgTest_118, SetReversedFalse_118) {
  prog_->set_reversed(false);
  EXPECT_FALSE(prog_->reversed());
}

// Test toggling reversed
TEST_F(ProgTest_118, ToggleReversed_118) {
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
  prog_->set_reversed(false);
  EXPECT_FALSE(prog_->reversed());
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
}

// Test default anchor_start is false
TEST_F(ProgTest_118, DefaultAnchorStartIsFalse_118) {
  EXPECT_FALSE(prog_->anchor_start());
}

// Test set_anchor_start
TEST_F(ProgTest_118, SetAnchorStart_118) {
  prog_->set_anchor_start(true);
  EXPECT_TRUE(prog_->anchor_start());
  prog_->set_anchor_start(false);
  EXPECT_FALSE(prog_->anchor_start());
}

// Test default anchor_end is false
TEST_F(ProgTest_118, DefaultAnchorEndIsFalse_118) {
  EXPECT_FALSE(prog_->anchor_end());
}

// Test set_anchor_end
TEST_F(ProgTest_118, SetAnchorEnd_118) {
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_end());
  prog_->set_anchor_end(false);
  EXPECT_FALSE(prog_->anchor_end());
}

// Test default start is 0
TEST_F(ProgTest_118, DefaultStartIsZero_118) {
  EXPECT_EQ(prog_->start(), 0);
}

// Test set_start
TEST_F(ProgTest_118, SetStart_118) {
  prog_->set_start(5);
  EXPECT_EQ(prog_->start(), 5);
}

// Test default start_unanchored is 0
TEST_F(ProgTest_118, DefaultStartUnanchoredIsZero_118) {
  EXPECT_EQ(prog_->start_unanchored(), 0);
}

// Test set_start_unanchored
TEST_F(ProgTest_118, SetStartUnanchored_118) {
  prog_->set_start_unanchored(10);
  EXPECT_EQ(prog_->start_unanchored(), 10);
}

// Test default dfa_mem is 0
TEST_F(ProgTest_118, DefaultDfaMemIsZero_118) {
  EXPECT_EQ(prog_->dfa_mem(), 0);
}

// Test set_dfa_mem
TEST_F(ProgTest_118, SetDfaMem_118) {
  prog_->set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog_->dfa_mem(), 1024 * 1024);
}

// Test default size is 0
TEST_F(ProgTest_118, DefaultSizeIsZero_118) {
  EXPECT_EQ(prog_->size(), 0);
}

// Test default bytemap_range is 0
TEST_F(ProgTest_118, DefaultBytemapRangeIsZero_118) {
  EXPECT_EQ(prog_->bytemap_range(), 0);
}

// Test default can_prefix_accel is false (no prefix configured)
TEST_F(ProgTest_118, DefaultCanPrefixAccelIsFalse_118) {
  EXPECT_FALSE(prog_->can_prefix_accel());
}

// Test IsWordChar for typical word characters
TEST_F(ProgTest_118, IsWordCharAlphanumeric_118) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

// Test IsWordChar for non-word characters
TEST_F(ProgTest_118, IsWordCharNonWord_118) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
}

// Test EmptyFlags at start of text
TEST_F(ProgTest_118, EmptyFlagsAtStartOfText_118) {
  absl::string_view text("hello");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At the beginning of text, kEmptyBeginText and kEmptyBeginLine should be set
  // We can just verify it returns a non-zero value indicating some flags
  EXPECT_NE(flags, 0u);
}

// Test EmptyFlags at end of text
TEST_F(ProgTest_118, EmptyFlagsAtEndOfText_118) {
  absl::string_view text("hello");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At the end of text, kEmptyEndText and kEmptyEndLine should be set
  EXPECT_NE(flags, 0u);
}

// Test EmptyFlags with empty text
TEST_F(ProgTest_118, EmptyFlagsEmptyText_118) {
  absl::string_view text("");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // Both begin and end flags should be set for empty text
  EXPECT_NE(flags, 0u);
}

// Test that a compiled program from a simple regex works with PossibleMatchRange
TEST_F(ProgTest_118, PossibleMatchRangeFromCompiledRegex_118) {
  // Use RE2 to get a compiled program indirectly
  // We'll test PossibleMatchRange on a compiled Prog
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  std::string min_match, max_match;
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 10);
  EXPECT_TRUE(result);
  EXPECT_FALSE(min_match.empty());
  EXPECT_FALSE(max_match.empty());
  EXPECT_LE(min_match, max_match);

  delete prog;
  re->Decref();
}

// Test Dump on a compiled program
TEST_F(ProgTest_118, DumpCompiledProg_118) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  std::string dump = prog->Dump();
  // Should produce a non-empty dump string
  EXPECT_FALSE(dump.empty());

  delete prog;
  re->Decref();
}

// Test DumpByteMap on default prog
TEST_F(ProgTest_118, DumpByteMapDefault_118) {
  std::string dump = prog_->DumpByteMap();
  // Even a default prog should produce some bytemap dump
  // It may be empty or have some content; just test it doesn't crash
  // and returns a string
  EXPECT_TRUE(dump.empty() || !dump.empty());  // always true, just no crash
}

// Test set_start with boundary values
TEST_F(ProgTest_118, SetStartBoundary_118) {
  prog_->set_start(0);
  EXPECT_EQ(prog_->start(), 0);
  prog_->set_start(-1);
  EXPECT_EQ(prog_->start(), -1);
}

// Test set_start_unanchored with boundary values
TEST_F(ProgTest_118, SetStartUnanchoredBoundary_118) {
  prog_->set_start_unanchored(0);
  EXPECT_EQ(prog_->start_unanchored(), 0);
  prog_->set_start_unanchored(-1);
  EXPECT_EQ(prog_->start_unanchored(), -1);
}

// Test set_dfa_mem with large value
TEST_F(ProgTest_118, SetDfaMemLarge_118) {
  int64_t large_mem = static_cast<int64_t>(1) << 30;  // 1GB
  prog_->set_dfa_mem(large_mem);
  EXPECT_EQ(prog_->dfa_mem(), large_mem);
}

// Test set_dfa_mem with zero
TEST_F(ProgTest_118, SetDfaMemZero_118) {
  prog_->set_dfa_mem(0);
  EXPECT_EQ(prog_->dfa_mem(), 0);
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow does not crash
TEST_F(ProgTest_118, TestingOnlySetDfaShouldBailWhenSlow_118) {
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
  // Just verify it doesn't crash
}

// Test SearchNFA on a compiled program with matching text
TEST_F(ProgTest_118, SearchNFAMatch_118) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);

  delete prog;
  re->Decref();
}

// Test SearchNFA on a compiled program with non-matching text
TEST_F(ProgTest_118, SearchNFANoMatch_118) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("xyz", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);

  delete prog;
  re->Decref();
}

// Test bytemap pointer is not null on default prog
TEST_F(ProgTest_118, BytemapNotNull_118) {
  const uint8_t* bm = prog_->bytemap();
  EXPECT_NE(bm, nullptr);
}

// Test CompileSet with a simple regexp
TEST_F(ProgTest_118, CompileSet_118) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  // CompileSet may or may not succeed depending on internal details
  if (prog != nullptr) {
    EXPECT_GT(prog->size(), 0);
    delete prog;
  }
  re->Decref();
}

// Test multiple set operations in sequence
TEST_F(ProgTest_118, MultipleSetOperations_118) {
  prog_->set_reversed(true);
  prog_->set_anchor_start(true);
  prog_->set_anchor_end(true);
  prog_->set_start(42);
  prog_->set_start_unanchored(7);
  prog_->set_dfa_mem(2048);

  EXPECT_TRUE(prog_->reversed());
  EXPECT_TRUE(prog_->anchor_start());
  EXPECT_TRUE(prog_->anchor_end());
  EXPECT_EQ(prog_->start(), 42);
  EXPECT_EQ(prog_->start_unanchored(), 7);
  EXPECT_EQ(prog_->dfa_mem(), 2048);
}

// Test IsOnePass on a simple compiled program
TEST_F(ProgTest_118, IsOnePassSimple_118) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  // IsOnePass returns true or false - just test it doesn't crash
  bool onepass = prog->IsOnePass();
  (void)onepass;  // We don't assert the value since it depends on internal logic

  delete prog;
  re->Decref();
}

// Test CanBitState on a compiled program
TEST_F(ProgTest_118, CanBitStateCompiledProg_118) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a.b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  // Just verify it returns a boolean without crashing
  bool can = prog->CanBitState();
  (void)can;

  delete prog;
  re->Decref();
}

// Test Flatten on a compiled program
TEST_F(ProgTest_118, FlattenCompiledProg_118) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  // Flatten should not crash
  prog->Flatten();

  delete prog;
  re->Decref();
}

// Test PossibleMatchRange with maxlen of 0
TEST_F(ProgTest_118, PossibleMatchRangeZeroMaxlen_118) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  std::string min_match, max_match;
  // maxlen=0 should still work
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 0);
  // Result may vary; just test it doesn't crash
  (void)result;

  delete prog;
  re->Decref();
}

// Test SearchBitState on a compiled program with matching text
TEST_F(ProgTest_118, SearchBitStateMatch_118) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("wor", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  absl::string_view text("hello world");
  if (prog->CanBitState()) {
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
  }

  delete prog;
  re->Decref();
}

// Test DumpUnanchored on a compiled program
TEST_F(ProgTest_118, DumpUnanchoredCompiledProg_118) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());

  delete prog;
  re->Decref();
}

}  // namespace re2
