#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"
#include <string>

namespace re2 {

class ProgTest_121 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor initializes bit_state_text_max_size to 0
TEST_F(ProgTest_121, DefaultConstructorBitStateTextMaxSize_121) {
  Prog prog;
  EXPECT_EQ(prog.bit_state_text_max_size(), 0u);
}

// Test default constructor initializes start to 0
TEST_F(ProgTest_121, DefaultConstructorStart_121) {
  Prog prog;
  EXPECT_EQ(prog.start(), 0);
}

// Test default constructor initializes start_unanchored to 0
TEST_F(ProgTest_121, DefaultConstructorStartUnanchored_121) {
  Prog prog;
  EXPECT_EQ(prog.start_unanchored(), 0);
}

// Test default constructor initializes reversed to false
TEST_F(ProgTest_121, DefaultConstructorReversed_121) {
  Prog prog;
  EXPECT_FALSE(prog.reversed());
}

// Test default constructor initializes anchor_start to false
TEST_F(ProgTest_121, DefaultConstructorAnchorStart_121) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_start());
}

// Test default constructor initializes anchor_end to false
TEST_F(ProgTest_121, DefaultConstructorAnchorEnd_121) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_end());
}

// Test default constructor initializes dfa_mem to 0
TEST_F(ProgTest_121, DefaultConstructorDfaMem_121) {
  Prog prog;
  EXPECT_EQ(prog.dfa_mem(), 0);
}

// Test default constructor initializes bytemap_range to 0
TEST_F(ProgTest_121, DefaultConstructorBytemapRange_121) {
  Prog prog;
  EXPECT_EQ(prog.bytemap_range(), 0);
}

// Test set_start and start
TEST_F(ProgTest_121, SetAndGetStart_121) {
  Prog prog;
  prog.set_start(5);
  EXPECT_EQ(prog.start(), 5);
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_121, SetAndGetStartUnanchored_121) {
  Prog prog;
  prog.set_start_unanchored(10);
  EXPECT_EQ(prog.start_unanchored(), 10);
}

// Test set_reversed and reversed
TEST_F(ProgTest_121, SetAndGetReversed_121) {
  Prog prog;
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test set_anchor_start and anchor_start
TEST_F(ProgTest_121, SetAndGetAnchorStart_121) {
  Prog prog;
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test set_anchor_end and anchor_end
TEST_F(ProgTest_121, SetAndGetAnchorEnd_121) {
  Prog prog;
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test set_dfa_mem and dfa_mem
TEST_F(ProgTest_121, SetAndGetDfaMem_121) {
  Prog prog;
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog.dfa_mem(), 1024 * 1024);
}

// Test default can_prefix_accel is false (no prefix configured)
TEST_F(ProgTest_121, DefaultCanPrefixAccelFalse_121) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test IsWordChar for various characters
TEST_F(ProgTest_121, IsWordCharAlpha_121) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

TEST_F(ProgTest_121, IsWordCharNonWord_121) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
}

// Test EmptyFlags at various positions
TEST_F(ProgTest_121, EmptyFlagsAtBeginning_121) {
  absl::string_view text = "hello";
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // At the beginning of text, kEmptyBeginText and kEmptyBeginLine should be set
  EXPECT_NE(flags, 0u);
}

TEST_F(ProgTest_121, EmptyFlagsAtEnd_121) {
  absl::string_view text = "hello";
  uint32_t flags = Prog::EmptyFlags(text, text.data() + text.size());
  // At the end of text, kEmptyEndText and kEmptyEndLine should be set
  EXPECT_NE(flags, 0u);
}

TEST_F(ProgTest_121, EmptyFlagsEmptyString_121) {
  absl::string_view text = "";
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // At start/end of empty string, multiple empty flags should be set
  EXPECT_NE(flags, 0u);
}

// Test using compiled Prog from RE2 for more complex operations
class ProgFromRE2Test_121 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test Dump produces non-empty output for a compiled program
TEST_F(ProgFromRE2Test_121, DumpNonEmpty_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
  
  delete prog;
  re->Decref();
}

// Test DumpUnanchored produces non-empty output
TEST_F(ProgFromRE2Test_121, DumpUnanchoredNonEmpty_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
  
  delete prog;
  re->Decref();
}

// Test DumpByteMap produces non-empty output
TEST_F(ProgFromRE2Test_121, DumpByteMapNonEmpty_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
  
  delete prog;
  re->Decref();
}

// Test size returns positive value for compiled program
TEST_F(ProgFromRE2Test_121, SizePositive_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  EXPECT_GT(prog->size(), 0);
  
  delete prog;
  re->Decref();
}

// Test bytemap returns non-null for compiled program
TEST_F(ProgFromRE2Test_121, BytemapNonNull_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  EXPECT_NE(prog->bytemap(), nullptr);
  
  delete prog;
  re->Decref();
}

// Test bytemap_range is positive after ComputeByteMap
TEST_F(ProgFromRE2Test_121, BytemapRangePositive_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  EXPECT_GT(prog->bytemap_range(), 0);
  
  delete prog;
  re->Decref();
}

// Test PossibleMatchRange
TEST_F(ProgFromRE2Test_121, PossibleMatchRange_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  std::string min_match, max_match;
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_match, max_match);
  
  delete prog;
  re->Decref();
}

// Test PossibleMatchRange with maxlen 0
TEST_F(ProgFromRE2Test_121, PossibleMatchRangeMaxlenZero_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  std::string min_match, max_match;
  // maxlen = 0 should still work (may return empty or very short strings)
  prog->PossibleMatchRange(&min_match, &max_match, 0);
  
  delete prog;
  re->Decref();
}

// Test IsOnePass for a simple pattern
TEST_F(ProgFromRE2Test_121, IsOnePassSimple_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  // Simple literal pattern should be one-pass
  bool one_pass = prog->IsOnePass();
  // We don't assert the value since it depends on internal optimizations,
  // but we verify it doesn't crash
  (void)one_pass;
  
  delete prog;
  re->Decref();
}

// Test CanBitState for a compiled program
TEST_F(ProgFromRE2Test_121, CanBitState_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  // Small pattern should be able to use bit state
  bool can = prog->CanBitState();
  (void)can;  // Just verify no crash
  
  delete prog;
  re->Decref();
}

// Test SearchNFA with matching text
TEST_F(ProgFromRE2Test_121, SearchNFAMatch_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  absl::string_view text = "xabcy";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
  
  delete prog;
  re->Decref();
}

// Test SearchNFA with non-matching text
TEST_F(ProgFromRE2Test_121, SearchNFANoMatch_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  absl::string_view text = "xyz";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  
  delete prog;
  re->Decref();
}

// Test SearchNFA anchored at start
TEST_F(ProgFromRE2Test_121, SearchNFAAnchoredMatch_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  absl::string_view text = "abcdef";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
  
  delete prog;
  re->Decref();
}

// Test SearchNFA anchored at start with no match
TEST_F(ProgFromRE2Test_121, SearchNFAAnchoredNoMatch_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  absl::string_view text = "xabcdef";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  
  delete prog;
  re->Decref();
}

// Test SearchBitState with matching text
TEST_F(ProgFromRE2Test_121, SearchBitStateMatch_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  if (prog->CanBitState()) {
    absl::string_view text = "xabcy";
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "abc");
  }
  
  delete prog;
  re->Decref();
}

// Test SearchBitState with non-matching text
TEST_F(ProgFromRE2Test_121, SearchBitStateNoMatch_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  if (prog->CanBitState()) {
    absl::string_view text = "xyz";
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_FALSE(found);
  }
  
  delete prog;
  re->Decref();
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgFromRE2Test_121, TestingOnlySetDfaShouldBailWhenSlow_121) {
  // Just verify it doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test CompileSet
TEST_F(ProgFromRE2Test_121, CompileSet_121) {
  Regexp* re = Regexp::Parse("abc|def|ghi", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  // CompileSet might or might not succeed depending on implementation
  if (prog != nullptr) {
    EXPECT_GT(prog->size(), 0);
    delete prog;
  }
  
  re->Decref();
}

// Test with empty pattern
TEST_F(ProgFromRE2Test_121, EmptyPattern_121) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  absl::string_view text = "anything";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0u);
  
  delete prog;
  re->Decref();
}

// Test with complex pattern
TEST_F(ProgFromRE2Test_121, ComplexPattern_121) {
  Regexp* re = Regexp::Parse("[a-z]+@[a-z]+\\.[a-z]+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  absl::string_view text = "send to user@example.com please";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "user@example.com");
  
  delete prog;
  re->Decref();
}

// Test set_dfa_mem with large value
TEST_F(ProgFromRE2Test_121, SetDfaMemLargeValue_121) {
  Prog prog;
  int64_t large_mem = static_cast<int64_t>(1) << 30;  // 1GB
  prog.set_dfa_mem(large_mem);
  EXPECT_EQ(prog.dfa_mem(), large_mem);
}

// Test set_start with negative value (boundary)
TEST_F(ProgFromRE2Test_121, SetStartNegative_121) {
  Prog prog;
  prog.set_start(-1);
  EXPECT_EQ(prog.start(), -1);
}

// Test Flatten on compiled program
TEST_F(ProgFromRE2Test_121, Flatten_121) {
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  // Flatten should not crash and program should still work after
  prog->Flatten();
  
  absl::string_view text = "xdefy";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "def");
  
  delete prog;
  re->Decref();
}

// Test ConfigurePrefixAccel and can_prefix_accel
TEST_F(ProgFromRE2Test_121, ConfigurePrefixAccel_121) {
  Regexp* re = Regexp::Parse("abcdef", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  prog->ConfigurePrefixAccel("abc", false);
  // After configuring, can_prefix_accel might be true
  // We just verify no crash
  bool can = prog->can_prefix_accel();
  (void)can;
  
  delete prog;
  re->Decref();
}

// Test SearchOnePass when pattern is one-pass
TEST_F(ProgFromRE2Test_121, SearchOnePassIfAvailable_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  if (prog->IsOnePass()) {
    absl::string_view text = "abc";
    absl::string_view match;
    bool found = prog->SearchOnePass(text, text, Prog::kAnchored,
                                      Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "abc");
  }
  
  delete prog;
  re->Decref();
}

// Test list_count for a default Prog
TEST_F(ProgFromRE2Test_121, DefaultListCount_121) {
  Prog prog;
  EXPECT_EQ(prog.list_count(), 0);
}

// Test EmptyFlags at word boundary
TEST_F(ProgFromRE2Test_121, EmptyFlagsWordBoundary_121) {
  absl::string_view text = "a b";
  // At position between 'a' and ' ', there should be a word boundary
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 1);
  // We just check it returns something (not necessarily specific bits)
  (void)flags;
}

// Test SearchDFA with matching text
TEST_F(ProgFromRE2Test_121, SearchDFAMatch_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(1 << 20);
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  
  absl::string_view text = "xabcy";
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

// Test SearchDFA with non-matching text
TEST_F(ProgFromRE2Test_121, SearchDFANoMatch_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(1 << 20);
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  
  absl::string_view text = "xyz";
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(found);
  }
  
  delete prog;
  re->Decref();
}

// Test with Unicode-like pattern
TEST_F(ProgFromRE2Test_121, UnicodePattern_121) {
  Regexp* re = Regexp::Parse("\\w+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  absl::string_view text = "  hello  ";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
  
  delete prog;
  re->Decref();
}

// Test SearchNFA with empty text
TEST_F(ProgFromRE2Test_121, SearchNFAEmptyText_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  absl::string_view text = "";
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  
  delete prog;
  re->Decref();
}

// Test SearchNFA with nmatch = 0
TEST_F(ProgFromRE2Test_121, SearchNFANmatchZero_121) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  
  absl::string_view text = "xabcy";
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, nullptr, 0);
  EXPECT_TRUE(found);
  
  delete prog;
  re->Decref();
}

}  // namespace re2
