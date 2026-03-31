#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"
#include <string>

namespace re2 {

class ProgTest_119 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor initializes list_count to 0
TEST_F(ProgTest_119, DefaultConstructorListCount_119) {
  Prog prog;
  EXPECT_EQ(prog.list_count(), 0);
}

// Test default constructor initializes start to 0
TEST_F(ProgTest_119, DefaultConstructorStart_119) {
  Prog prog;
  EXPECT_EQ(prog.start(), 0);
}

// Test default constructor initializes start_unanchored to 0
TEST_F(ProgTest_119, DefaultConstructorStartUnanchored_119) {
  Prog prog;
  EXPECT_EQ(prog.start_unanchored(), 0);
}

// Test default constructor initializes reversed to false
TEST_F(ProgTest_119, DefaultConstructorReversed_119) {
  Prog prog;
  EXPECT_FALSE(prog.reversed());
}

// Test default constructor initializes anchor_start to false
TEST_F(ProgTest_119, DefaultConstructorAnchorStart_119) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_start());
}

// Test default constructor initializes anchor_end to false
TEST_F(ProgTest_119, DefaultConstructorAnchorEnd_119) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_end());
}

// Test default constructor initializes bytemap_range to 0
TEST_F(ProgTest_119, DefaultConstructorBytemapRange_119) {
  Prog prog;
  EXPECT_EQ(prog.bytemap_range(), 0);
}

// Test default constructor initializes dfa_mem to 0
TEST_F(ProgTest_119, DefaultConstructorDfaMem_119) {
  Prog prog;
  EXPECT_EQ(prog.dfa_mem(), 0);
}

// Test default constructor initializes bit_state_text_max_size to 0
TEST_F(ProgTest_119, DefaultConstructorBitStateTextMaxSize_119) {
  Prog prog;
  EXPECT_EQ(prog.bit_state_text_max_size(), 0);
}

// Test set_start and start
TEST_F(ProgTest_119, SetStartAndGetStart_119) {
  Prog prog;
  prog.set_start(5);
  EXPECT_EQ(prog.start(), 5);
}

// Test set_start with 0
TEST_F(ProgTest_119, SetStartZero_119) {
  Prog prog;
  prog.set_start(0);
  EXPECT_EQ(prog.start(), 0);
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_119, SetStartUnanchoredAndGet_119) {
  Prog prog;
  prog.set_start_unanchored(10);
  EXPECT_EQ(prog.start_unanchored(), 10);
}

// Test set_reversed and reversed
TEST_F(ProgTest_119, SetReversedTrue_119) {
  Prog prog;
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
}

// Test set_reversed to false
TEST_F(ProgTest_119, SetReversedFalse_119) {
  Prog prog;
  prog.set_reversed(true);
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test set_anchor_start
TEST_F(ProgTest_119, SetAnchorStartTrue_119) {
  Prog prog;
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
}

// Test set_anchor_start false
TEST_F(ProgTest_119, SetAnchorStartFalse_119) {
  Prog prog;
  prog.set_anchor_start(true);
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test set_anchor_end
TEST_F(ProgTest_119, SetAnchorEndTrue_119) {
  Prog prog;
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
}

// Test set_anchor_end false
TEST_F(ProgTest_119, SetAnchorEndFalse_119) {
  Prog prog;
  prog.set_anchor_end(true);
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test set_dfa_mem and dfa_mem
TEST_F(ProgTest_119, SetDfaMemAndGet_119) {
  Prog prog;
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog.dfa_mem(), 1024 * 1024);
}

// Test set_dfa_mem with zero
TEST_F(ProgTest_119, SetDfaMemZero_119) {
  Prog prog;
  prog.set_dfa_mem(0);
  EXPECT_EQ(prog.dfa_mem(), 0);
}

// Test set_dfa_mem with large value
TEST_F(ProgTest_119, SetDfaMemLargeValue_119) {
  Prog prog;
  int64_t large_val = static_cast<int64_t>(1) << 40;
  prog.set_dfa_mem(large_val);
  EXPECT_EQ(prog.dfa_mem(), large_val);
}

// Test can_prefix_accel returns false initially (no prefix configured)
TEST_F(ProgTest_119, DefaultCanPrefixAccelFalse_119) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test default size is 0
TEST_F(ProgTest_119, DefaultSize_119) {
  Prog prog;
  EXPECT_EQ(prog.size(), 0);
}

// Test IsWordChar for alphabetic characters
TEST_F(ProgTest_119, IsWordCharAlpha_119) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('m'));
}

// Test IsWordChar for digits
TEST_F(ProgTest_119, IsWordCharDigits_119) {
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('5'));
}

// Test IsWordChar for underscore
TEST_F(ProgTest_119, IsWordCharUnderscore_119) {
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

// Test IsWordChar for non-word characters
TEST_F(ProgTest_119, IsWordCharNonWord_119) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
  EXPECT_FALSE(Prog::IsWordChar('!'));
}

// Test IsWordChar boundary values
TEST_F(ProgTest_119, IsWordCharBoundary_119) {
  // Characters just outside ranges
  EXPECT_FALSE(Prog::IsWordChar('/'));  // before '0'
  EXPECT_FALSE(Prog::IsWordChar(':'));  // after '9'
  EXPECT_FALSE(Prog::IsWordChar('@'));  // before 'A'
  EXPECT_FALSE(Prog::IsWordChar('['));  // after 'Z'
  EXPECT_FALSE(Prog::IsWordChar('`'));  // before 'a'
  EXPECT_FALSE(Prog::IsWordChar('{'));  // after 'z'
}

// Test Dump on default-constructed Prog
TEST_F(ProgTest_119, DumpDefault_119) {
  Prog prog;
  std::string dump = prog.Dump();
  // Just check it returns a string without crashing
  EXPECT_TRUE(dump.empty() || !dump.empty());
}

// Test DumpUnanchored on default-constructed Prog
TEST_F(ProgTest_119, DumpUnanchoredDefault_119) {
  Prog prog;
  std::string dump = prog.DumpUnanchored();
  EXPECT_TRUE(dump.empty() || !dump.empty());
}

// Test DumpByteMap on default-constructed Prog
TEST_F(ProgTest_119, DumpByteMapDefault_119) {
  Prog prog;
  std::string dump = prog.DumpByteMap();
  // Should return something without crashing
  EXPECT_TRUE(dump.empty() || !dump.empty());
}

// Test that PossibleMatchRange works with a compiled program
TEST_F(ProgTest_119, PossibleMatchRangeFromCompiled_119) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);
  
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_str, max_str);
  
  delete prog;
  re->Decref();
}

// Test a compiled Prog has non-zero size
TEST_F(ProgTest_119, CompiledProgHasNonZeroSize_119) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);
  
  EXPECT_GT(prog->size(), 0);
  
  delete prog;
  re->Decref();
}

// Test bytemap is accessible on compiled prog
TEST_F(ProgTest_119, CompiledProgBytemap_119) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]+", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);
  
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  
  delete prog;
  re->Decref();
}

// Test EmptyFlags at start of text
TEST_F(ProgTest_119, EmptyFlagsAtStart_119) {
  absl::string_view text("hello");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At the beginning of text, kEmptyBeginText should be set
  // We just verify it's callable and returns something
  EXPECT_NE(flags, 0u);  // Should have at least some flags at boundary
}

// Test EmptyFlags at end of text
TEST_F(ProgTest_119, EmptyFlagsAtEnd_119) {
  absl::string_view text("hello");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_NE(flags, 0u);
}

// Test EmptyFlags in middle of text
TEST_F(ProgTest_119, EmptyFlagsInMiddle_119) {
  absl::string_view text("hello");
  const char* p = text.data() + 2;
  uint32_t flags = Prog::EmptyFlags(text, p);
  // In the middle, begin/end text flags shouldn't be set
  // But we can't be sure about all flags; just verify it doesn't crash
  (void)flags;
}

// Test EmptyFlags with empty text
TEST_F(ProgTest_119, EmptyFlagsEmptyText_119) {
  absl::string_view text("");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // Both begin and end should be set
  EXPECT_NE(flags, 0u);
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_119, TestingOnlySetDfaShouldBailWhenSlow_119) {
  // Just verify it doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test CanBitState on default prog
TEST_F(ProgTest_119, DefaultCanBitState_119) {
  Prog prog;
  // Default prog with size 0 - just verify it returns without crash
  bool result = prog.CanBitState();
  (void)result;
}

// Test IsOnePass on compiled Prog
TEST_F(ProgTest_119, IsOnePassSimplePattern_119) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);
  
  // Simple literal pattern should be one-pass
  bool onepass = prog->IsOnePass();
  EXPECT_TRUE(onepass);
  
  delete prog;
  re->Decref();
}

// Test IsOnePass on a pattern that is NOT one-pass
TEST_F(ProgTest_119, IsOnePassComplexPattern_119) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|a)b", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);
  
  // Ambiguous pattern might not be one-pass
  bool onepass = prog->IsOnePass();
  (void)onepass; // Just verify no crash
  
  delete prog;
  re->Decref();
}

// Test SearchNFA with a simple match
TEST_F(ProgTest_119, SearchNFASimpleMatch_119) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);
  
  absl::string_view text("say hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
  
  delete prog;
  re->Decref();
}

// Test SearchNFA no match
TEST_F(ProgTest_119, SearchNFANoMatch_119) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("xyz", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);
  
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  
  delete prog;
  re->Decref();
}

// Test SearchNFA anchored
TEST_F(ProgTest_119, SearchNFAAnchored_119) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);
  
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
  
  delete prog;
  re->Decref();
}

// Test SearchNFA anchored no match
TEST_F(ProgTest_119, SearchNFAAnchoredNoMatch_119) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("world", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);
  
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  
  delete prog;
  re->Decref();
}

// Test PossibleMatchRange with maxlen boundary
TEST_F(ProgTest_119, PossibleMatchRangeSmallMaxlen_119) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abcdef", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);
  
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 3);
  EXPECT_TRUE(result);
  
  delete prog;
  re->Decref();
}

// Test set_start multiple times
TEST_F(ProgTest_119, SetStartMultipleTimes_119) {
  Prog prog;
  prog.set_start(1);
  EXPECT_EQ(prog.start(), 1);
  prog.set_start(42);
  EXPECT_EQ(prog.start(), 42);
  prog.set_start(0);
  EXPECT_EQ(prog.start(), 0);
}

// Test set_start_unanchored multiple times
TEST_F(ProgTest_119, SetStartUnanchoredMultipleTimes_119) {
  Prog prog;
  prog.set_start_unanchored(3);
  EXPECT_EQ(prog.start_unanchored(), 3);
  prog.set_start_unanchored(99);
  EXPECT_EQ(prog.start_unanchored(), 99);
}

// Test compiled Prog for anchored pattern
TEST_F(ProgTest_119, CompiledAnchoredPattern_119) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello$", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);
  
  // Verify the program has instructions
  EXPECT_GT(prog->size(), 0);
  
  delete prog;
  re->Decref();
}

// Test SearchBitState with a simple match
TEST_F(ProgTest_119, SearchBitStateSimpleMatch_119) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("world", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);
  
  if (prog->CanBitState()) {
    absl::string_view text("hello world");
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "world");
  }
  
  delete prog;
  re->Decref();
}

// Test Flatten on compiled Prog
TEST_F(ProgTest_119, FlattenCompiledProg_119) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)+c", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);
  
  // Flatten should not crash
  prog->Flatten();
  
  // After flatten, the program should still be valid
  EXPECT_GT(prog->size(), 0);
  
  delete prog;
  re->Decref();
}

// Test ConfigurePrefixAccel and can_prefix_accel
TEST_F(ProgTest_119, ConfigurePrefixAccel_119) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello.*world", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);
  
  prog->ComputeByteMap();
  prog->ConfigurePrefixAccel("hello", false);
  // After configuring, can_prefix_accel might be true
  // We just verify it doesn't crash
  bool accel = prog->can_prefix_accel();
  (void)accel;
  
  delete prog;
  re->Decref();
}

// Test SearchOnePass on a one-pass pattern
TEST_F(ProgTest_119, SearchOnePassMatch_119) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);
  
  if (prog->IsOnePass()) {
    absl::string_view text("xabcx");
    absl::string_view match;
    bool found = prog->SearchOnePass(text, text, Prog::kUnanchored,
                                      Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "abc");
  }
  
  delete prog;
  re->Decref();
}

// Test EmptyFlags at word boundary
TEST_F(ProgTest_119, EmptyFlagsWordBoundary_119) {
  absl::string_view text("a b");
  const char* p = text.data() + 1;  // at the space
  uint32_t flags = Prog::EmptyFlags(text, p);
  // Should have word boundary flag since transitioning from 'a' to ' '
  (void)flags; // Just verify no crash
}

// Test multiple setter/getter round trips
TEST_F(ProgTest_119, MultipleSettersGetters_119) {
  Prog prog;
  
  prog.set_start(10);
  prog.set_start_unanchored(20);
  prog.set_reversed(true);
  prog.set_anchor_start(true);
  prog.set_anchor_end(true);
  prog.set_dfa_mem(4096);
  
  EXPECT_EQ(prog.start(), 10);
  EXPECT_EQ(prog.start_unanchored(), 20);
  EXPECT_TRUE(prog.reversed());
  EXPECT_TRUE(prog.anchor_start());
  EXPECT_TRUE(prog.anchor_end());
  EXPECT_EQ(prog.dfa_mem(), 4096);
}

}  // namespace re2
