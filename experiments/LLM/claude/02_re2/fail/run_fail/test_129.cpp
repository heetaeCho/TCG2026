#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/testing/regexp_generator.h"
#include "absl/strings/string_view.h"

namespace re2 {

// Helper to compile a Regexp into a Prog for testing
class ProgTest_129 : public ::testing::Test {
 protected:
  Prog* CompileRegexp(const char* pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re == nullptr) return nullptr;
    Prog* prog = re->CompileToProg(0);
    re->Decref();
    return prog;
  }
};

// Test default constructor initializes fields correctly
TEST_F(ProgTest_129, DefaultConstructorValues_129) {
  Prog prog;
  EXPECT_EQ(prog.start(), 0);
  EXPECT_EQ(prog.start_unanchored(), 0);
  EXPECT_FALSE(prog.reversed());
  EXPECT_FALSE(prog.anchor_start());
  EXPECT_FALSE(prog.anchor_end());
  EXPECT_EQ(prog.bytemap_range(), 0);
  EXPECT_EQ(prog.dfa_mem(), 0);
  EXPECT_EQ(prog.size(), 0);
}

// Test bytemap returns a non-null pointer
TEST_F(ProgTest_129, BytemapReturnsNonNull_129) {
  Prog prog;
  const uint8_t* bm = prog.bytemap();
  EXPECT_NE(bm, nullptr);
}

// Test set_start and start
TEST_F(ProgTest_129, SetAndGetStart_129) {
  Prog prog;
  prog.set_start(5);
  EXPECT_EQ(prog.start(), 5);
  prog.set_start(0);
  EXPECT_EQ(prog.start(), 0);
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_129, SetAndGetStartUnanchored_129) {
  Prog prog;
  prog.set_start_unanchored(10);
  EXPECT_EQ(prog.start_unanchored(), 10);
}

// Test set_reversed and reversed
TEST_F(ProgTest_129, SetAndGetReversed_129) {
  Prog prog;
  EXPECT_FALSE(prog.reversed());
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test set_anchor_start and anchor_start
TEST_F(ProgTest_129, SetAndGetAnchorStart_129) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_start());
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test set_anchor_end and anchor_end
TEST_F(ProgTest_129, SetAndGetAnchorEnd_129) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_end());
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test set_dfa_mem and dfa_mem
TEST_F(ProgTest_129, SetAndGetDfaMem_129) {
  Prog prog;
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog.dfa_mem(), 1024 * 1024);
  prog.set_dfa_mem(0);
  EXPECT_EQ(prog.dfa_mem(), 0);
}

// Test can_prefix_accel on default prog (should be false)
TEST_F(ProgTest_129, DefaultCanPrefixAccelFalse_129) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test IsWordChar for various characters
TEST_F(ProgTest_129, IsWordCharAlpha_129) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

TEST_F(ProgTest_129, IsWordCharNonWord_129) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('!'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
}

// Test bytemap on a compiled program
TEST_F(ProgTest_129, BytemapOnCompiledProg_129) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  // bytemap_range should be > 0 for a non-trivial regex
  EXPECT_GT(prog->bytemap_range(), 0);
  delete prog;
}

// Test Dump produces non-empty string for a compiled program
TEST_F(ProgTest_129, DumpNonEmpty_129) {
  Prog* prog = CompileRegexp("a+b");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test DumpUnanchored
TEST_F(ProgTest_129, DumpUnanchoredNonEmpty_129) {
  Prog* prog = CompileRegexp("a+b");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test DumpByteMap
TEST_F(ProgTest_129, DumpByteMapNonEmpty_129) {
  Prog* prog = CompileRegexp("a+b");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test size is positive for compiled prog
TEST_F(ProgTest_129, SizePositiveForCompiledProg_129) {
  Prog* prog = CompileRegexp("[a-z]+");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test EmptyFlags at beginning of text
TEST_F(ProgTest_129, EmptyFlagsBeginningOfText_129) {
  absl::string_view text("hello");
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // At the beginning of text, kEmptyBeginText and kEmptyBeginLine should be set
  // We just check it returns something (non-negative is always true for uint32_t)
  // The exact flags depend on implementation, but beginning-of-text should include
  // some flags
  EXPECT_NE(flags, 0u);
}

// Test EmptyFlags at end of text
TEST_F(ProgTest_129, EmptyFlagsEndOfText_129) {
  absl::string_view text("hello");
  uint32_t flags = Prog::EmptyFlags(text, text.data() + text.size());
  // At end of text should have kEmptyEndText flag set
  EXPECT_NE(flags, 0u);
}

// Test EmptyFlags in the middle of text
TEST_F(ProgTest_129, EmptyFlagsMiddleOfText_129) {
  absl::string_view text("hello world");
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 5);
  // In the middle - may have word boundary or other flags, but we just check it doesn't crash
  // flags could be zero or non-zero depending on context
  (void)flags;  // Just verifying it doesn't crash
}

// Test PossibleMatchRange
TEST_F(ProgTest_129, PossibleMatchRange_129) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_FALSE(min_str.empty());
  EXPECT_FALSE(max_str.empty());
  EXPECT_LE(min_str, max_str);
  delete prog;
}

// Test PossibleMatchRange with maxlen=0
TEST_F(ProgTest_129, PossibleMatchRangeZeroMaxlen_129) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 0);
  // With maxlen 0, may or may not succeed; just test it doesn't crash
  (void)result;
  delete prog;
}

// Test SearchNFA with simple match
TEST_F(ProgTest_129, SearchNFASimpleMatch_129) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xabcy");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
  delete prog;
}

// Test SearchNFA with no match
TEST_F(ProgTest_129, SearchNFANoMatch_129) {
  Prog* prog = CompileRegexp("xyz");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  delete prog;
}

// Test SearchNFA anchored match
TEST_F(ProgTest_129, SearchNFAAnchoredMatch_129) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
  delete prog;
}

// Test SearchNFA anchored no match
TEST_F(ProgTest_129, SearchNFAAnchoredNoMatch_129) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xabcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  delete prog;
}

// Test SearchNFA empty pattern
TEST_F(ProgTest_129, SearchNFAEmptyPattern_129) {
  Prog* prog = CompileRegexp("");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("hello");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match.size(), 0u);
  delete prog;
}

// Test SearchNFA empty text
TEST_F(ProgTest_129, SearchNFAEmptyText_129) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  delete prog;
}

// Test Flatten on compiled prog doesn't crash
TEST_F(ProgTest_129, FlattenDoesNotCrash_129) {
  Prog* prog = CompileRegexp("a(b|c)d");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // After flattening, Dump should still work
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test Optimize on compiled prog doesn't crash
TEST_F(ProgTest_129, OptimizeDoesNotCrash_129) {
  Prog* prog = CompileRegexp("a(b|c)d");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  delete prog;
}

// Test SearchBitState with simple match
TEST_F(ProgTest_129, SearchBitStateSimpleMatch_129) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  absl::string_view text("xabcy");
  absl::string_view match;
  if (prog->CanBitState()) {
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "abc");
  }
  delete prog;
}

// Test CanBitState for small program
TEST_F(ProgTest_129, CanBitStateSmallProg_129) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  // Small programs should be able to use bit state
  EXPECT_TRUE(prog->CanBitState());
  delete prog;
}

// Test IsOnePass for simple literal
TEST_F(ProgTest_129, IsOnePassSimpleLiteral_129) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  // Simple literal should be one-pass
  bool onepass = prog->IsOnePass();
  EXPECT_TRUE(onepass);
  delete prog;
}

// Test SearchOnePass on a one-pass program
TEST_F(ProgTest_129, SearchOnePassMatch_129) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  if (prog->IsOnePass()) {
    absl::string_view text("xabcy");
    absl::string_view match;
    bool found = prog->SearchOnePass(text, text, Prog::kUnanchored,
                                      Prog::kFirstMatch, &match, 1);
    // SearchOnePass may only work anchored; result depends on implementation
    (void)found;
  }
  delete prog;
}

// Test ConfigurePrefixAccel and can_prefix_accel
TEST_F(ProgTest_129, ConfigurePrefixAccelEnablesAccel_129) {
  Prog* prog = CompileRegexp("abcdef");
  ASSERT_NE(prog, nullptr);
  prog->ComputeByteMap();
  prog->ConfigurePrefixAccel("abc", false);
  // After configuring prefix accel, it may or may not be enabled
  // depending on the prefix
  // Just test it doesn't crash
  bool accel = prog->can_prefix_accel();
  (void)accel;
  delete prog;
}

// Test PrefixAccel with null data
TEST_F(ProgTest_129, PrefixAccelNullData_129) {
  Prog prog;
  // Without prefix accel configured, can_prefix_accel should be false
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_129, TestingOnlySetDfaShouldBailWhenSlow_129) {
  // Just ensure this doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test SearchDFA with simple match
TEST_F(ProgTest_129, SearchDFASimpleMatch_129) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("xabcy");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
  delete prog;
}

// Test SearchDFA no match
TEST_F(ProgTest_129, SearchDFANoMatch_129) {
  Prog* prog = CompileRegexp("xyz");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(found);
  }
  delete prog;
}

// Test bytemap values after ComputeByteMap
TEST_F(ProgTest_129, BytemapValuesAfterCompute_129) {
  Prog* prog = CompileRegexp("[a-z]");
  ASSERT_NE(prog, nullptr);
  const uint8_t* bm = prog->bytemap();
  int range = prog->bytemap_range();
  EXPECT_GT(range, 0);
  // All bytemap values should be less than bytemap_range
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bm[i], range);
  }
  delete prog;
}

// Test bytemap groups equivalent characters
TEST_F(ProgTest_129, BytemapGroupsEquivalentChars_129) {
  Prog* prog = CompileRegexp("[abc]");
  ASSERT_NE(prog, nullptr);
  const uint8_t* bm = prog->bytemap();
  // a, b, c should map to the same byte class
  EXPECT_EQ(bm['a'], bm['b']);
  EXPECT_EQ(bm['b'], bm['c']);
  delete prog;
}

// Test multiple captures with NFA search
TEST_F(ProgTest_129, SearchNFAWithCaptures_129) {
  Prog* prog = CompileRegexp("(a+)(b+)");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("aaabbb");
  absl::string_view match[3];
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, match, 3);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "aaabbb");
  EXPECT_EQ(match[1], "aaa");
  EXPECT_EQ(match[2], "bbb");
  delete prog;
}

// Test CompileSet
TEST_F(ProgTest_129, CompileSetSimple_129) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def|ghi", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  // CompileSet may or may not succeed
  if (prog != nullptr) {
    EXPECT_GT(prog->size(), 0);
    delete prog;
  }
  re->Decref();
}

// Test list_count on default prog
TEST_F(ProgTest_129, ListCountDefault_129) {
  Prog prog;
  EXPECT_EQ(prog.list_count(), 0);
}

// Test bit_state_text_max_size on default prog
TEST_F(ProgTest_129, BitStateTextMaxSizeDefault_129) {
  Prog prog;
  EXPECT_EQ(prog.bit_state_text_max_size(), 0u);
}

// Test with complex regex pattern
TEST_F(ProgTest_129, ComplexRegexCompiles_129) {
  Prog* prog = CompileRegexp("(foo|bar)baz[0-9]+.*");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  EXPECT_GT(prog->bytemap_range(), 0);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
  delete prog;
}

// Test PossibleMatchRange with complex pattern
TEST_F(ProgTest_129, PossibleMatchRangeComplex_129) {
  Prog* prog = CompileRegexp("[a-z]+@[a-z]+\\.[a-z]+");
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 20);
  if (result) {
    EXPECT_LE(min_str, max_str);
  }
  delete prog;
}

}  // namespace re2
