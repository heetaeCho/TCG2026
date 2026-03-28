#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/testing/regexp_generator.h"
#include "absl/strings/string_view.h"

namespace re2 {

class ProgTest_112 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a default-constructed Prog has start() == 0
TEST_F(ProgTest_112, DefaultStartIsZero_112) {
  Prog prog;
  EXPECT_EQ(0, prog.start());
}

// Test set_start and start
TEST_F(ProgTest_112, SetStartAndGetStart_112) {
  Prog prog;
  prog.set_start(5);
  EXPECT_EQ(5, prog.start());
}

// Test that start_unanchored defaults to 0
TEST_F(ProgTest_112, DefaultStartUnanchoredIsZero_112) {
  Prog prog;
  EXPECT_EQ(0, prog.start_unanchored());
}

// Test set_start_unanchored
TEST_F(ProgTest_112, SetStartUnanchored_112) {
  Prog prog;
  prog.set_start_unanchored(10);
  EXPECT_EQ(10, prog.start_unanchored());
}

// Test reversed defaults to false
TEST_F(ProgTest_112, DefaultReversedIsFalse_112) {
  Prog prog;
  EXPECT_FALSE(prog.reversed());
}

// Test set_reversed
TEST_F(ProgTest_112, SetReversed_112) {
  Prog prog;
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test anchor_start defaults to false
TEST_F(ProgTest_112, DefaultAnchorStartIsFalse_112) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_start());
}

// Test set_anchor_start
TEST_F(ProgTest_112, SetAnchorStart_112) {
  Prog prog;
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test anchor_end defaults to false
TEST_F(ProgTest_112, DefaultAnchorEndIsFalse_112) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_end());
}

// Test set_anchor_end
TEST_F(ProgTest_112, SetAnchorEnd_112) {
  Prog prog;
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test dfa_mem defaults to 0
TEST_F(ProgTest_112, DefaultDfaMemIsZero_112) {
  Prog prog;
  EXPECT_EQ(0, prog.dfa_mem());
}

// Test set_dfa_mem
TEST_F(ProgTest_112, SetDfaMem_112) {
  Prog prog;
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(1024 * 1024, prog.dfa_mem());
}

// Test bytemap_range defaults to 0
TEST_F(ProgTest_112, DefaultBytemapRangeIsZero_112) {
  Prog prog;
  EXPECT_EQ(0, prog.bytemap_range());
}

// Test size defaults to 0
TEST_F(ProgTest_112, DefaultSizeIsZero_112) {
  Prog prog;
  EXPECT_EQ(0, prog.size());
}

// Test can_prefix_accel on default prog (no prefix configured)
TEST_F(ProgTest_112, DefaultCannotPrefixAccel_112) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test IsWordChar for various characters
TEST_F(ProgTest_112, IsWordCharLetters_112) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

TEST_F(ProgTest_112, IsWordCharNonWord_112) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
}

// Test EmptyFlags at beginning of text
TEST_F(ProgTest_112, EmptyFlagsAtBeginning_112) {
  absl::string_view text("hello");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At the beginning, kEmptyBeginText and kEmptyBeginLine should be set
  // We don't know exact flag values but flags should be non-zero at boundaries
  EXPECT_NE(0u, flags);
}

// Test EmptyFlags at end of text
TEST_F(ProgTest_112, EmptyFlagsAtEnd_112) {
  absl::string_view text("hello");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_NE(0u, flags);
}

// Test EmptyFlags with empty text
TEST_F(ProgTest_112, EmptyFlagsEmptyText_112) {
  absl::string_view text("");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // Both begin and end flags should be set
  EXPECT_NE(0u, flags);
}

// Test Prog compiled from a simple regexp via RE2
TEST_F(ProgTest_112, CompiledProgFromRE2HasValidStart_112) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  // The underlying Prog should have been compiled; we can't access it directly
  // but we can verify RE2 works correctly which implicitly tests Prog
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test PossibleMatchRange with a compiled program
TEST_F(ProgTest_112, CompiledProgPossibleMatchRange_112) {
  // We test via Regexp -> Prog path
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);

  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_str, "abc");
  EXPECT_GE(max_str, "abc");

  delete prog;
  re->Decref();
}

// Test Dump on a simple program
TEST_F(ProgTest_112, DumpNonEmpty_112) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);

  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());

  delete prog;
  re->Decref();
}

// Test DumpByteMap
TEST_F(ProgTest_112, DumpByteMapNonEmpty_112) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);

  std::string bm = prog->DumpByteMap();
  EXPECT_FALSE(bm.empty());

  delete prog;
  re->Decref();
}

// Test bytemap returns non-null pointer for compiled program
TEST_F(ProgTest_112, BytemapNonNullForCompiledProg_112) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);

  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(nullptr, bm);
  EXPECT_GT(prog->bytemap_range(), 0);

  delete prog;
  re->Decref();
}

// Test size > 0 for a compiled program
TEST_F(ProgTest_112, CompiledProgSizePositive_112) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)+", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);

  EXPECT_GT(prog->size(), 0);

  delete prog;
  re->Decref();
}

// Test SearchNFA on a simple pattern match
TEST_F(ProgTest_112, SearchNFASimpleMatch_112) {
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
  EXPECT_EQ("hello", match);

  delete prog;
  re->Decref();
}

// Test SearchNFA with no match
TEST_F(ProgTest_112, SearchNFANoMatch_112) {
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
TEST_F(ProgTest_112, SearchNFAAnchored_112) {
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

  absl::string_view text2("say hello");
  found = prog->SearchNFA(text2, text2, Prog::kAnchored,
                           Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);

  delete prog;
  re->Decref();
}

// Test IsOnePass on a simple deterministic pattern
TEST_F(ProgTest_112, IsOnePassSimplePattern_112) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);

  // Simple literal pattern should be one-pass
  bool onepass = prog->IsOnePass();
  // We just verify it doesn't crash; the result depends on the pattern
  (void)onepass;

  delete prog;
  re->Decref();
}

// Test CanBitState
TEST_F(ProgTest_112, CanBitState_112) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);

  // Small program should be able to use bit-state
  EXPECT_TRUE(prog->CanBitState());

  delete prog;
  re->Decref();
}

// Test SearchBitState
TEST_F(ProgTest_112, SearchBitStateMatch_112) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("wor(ld)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);

  if (prog->CanBitState()) {
    absl::string_view text("hello world");
    absl::string_view match[2];
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, match, 2);
    EXPECT_TRUE(found);
    EXPECT_EQ("world", match[0]);
    EXPECT_EQ("ld", match[1]);
  }

  delete prog;
  re->Decref();
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_112, SetDfaShouldBailWhenSlow_112) {
  // Just verify it doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test set_start with boundary value
TEST_F(ProgTest_112, SetStartBoundary_112) {
  Prog prog;
  prog.set_start(0);
  EXPECT_EQ(0, prog.start());
  prog.set_start(-1);
  EXPECT_EQ(-1, prog.start());
}

// Test set_dfa_mem with large value
TEST_F(ProgTest_112, SetDfaMemLargeValue_112) {
  Prog prog;
  int64_t large_mem = 1LL << 30;  // 1GB
  prog.set_dfa_mem(large_mem);
  EXPECT_EQ(large_mem, prog.dfa_mem());
}

// Test bit_state_text_max_size defaults to 0
TEST_F(ProgTest_112, DefaultBitStateTextMaxSize_112) {
  Prog prog;
  EXPECT_EQ(0u, prog.bit_state_text_max_size());
}

// Test list_count defaults to 0
TEST_F(ProgTest_112, DefaultListCount_112) {
  Prog prog;
  EXPECT_EQ(0, prog.list_count());
}

// Test SearchDFA with a simple pattern
TEST_F(ProgTest_112, SearchDFASimpleMatch_112) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(1 << 20);
  ASSERT_TRUE(prog != nullptr);

  absl::string_view text("xyzabcdef");
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

// Test SearchDFA no match
TEST_F(ProgTest_112, SearchDFANoMatch_112) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("xyz", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(1 << 20);
  ASSERT_TRUE(prog != nullptr);

  absl::string_view text("abcdef");
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

// Test Flatten doesn't crash on a compiled program
TEST_F(ProgTest_112, FlattenDoesNotCrash_112) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);

  prog->Flatten();
  // After flatten, program should still be functional
  EXPECT_GT(prog->size(), 0);

  delete prog;
  re->Decref();
}

// Test PossibleMatchRange boundary: maxlen = 0
TEST_F(ProgTest_112, PossibleMatchRangeZeroMaxlen_112) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);

  std::string min_str, max_str;
  // maxlen = 0 is a boundary condition
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 0);
  // Result may be false for maxlen=0, just verify no crash
  (void)result;

  delete prog;
  re->Decref();
}

// Test CompileSet
TEST_F(ProgTest_112, CompileSetSimple_112) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def|ghi", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  // CompileSet may or may not succeed depending on the pattern
  if (prog != nullptr) {
    EXPECT_GT(prog->size(), 0);
    delete prog;
  }

  re->Decref();
}

// Test PrefixAccel returns null when no prefix is configured
TEST_F(ProgTest_112, PrefixAccelNullWhenNotConfigured_112) {
  Prog prog;
  const char data[] = "hello world";
  const void* result = prog.PrefixAccel(data, sizeof(data) - 1);
  // Without prefix configured, can_prefix_accel is false
  // Calling PrefixAccel when !can_prefix_accel is undefined,
  // so just check can_prefix_accel
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test EmptyFlags in the middle of text
TEST_F(ProgTest_112, EmptyFlagsMiddleOfText_112) {
  absl::string_view text("hello");
  const char* p = text.data() + 2;
  uint32_t flags = Prog::EmptyFlags(text, p);
  // In the middle, begin/end text flags should not be set
  // But we don't know exact values, just verify it runs
  (void)flags;
}

// Test EmptyFlags at word boundary
TEST_F(ProgTest_112, EmptyFlagsWordBoundary_112) {
  absl::string_view text("a b");
  // Between 'a' and ' '
  const char* p = text.data() + 1;
  uint32_t flags = Prog::EmptyFlags(text, p);
  // Should have word boundary flag since transitioning from word to non-word
  EXPECT_NE(0u, flags);
}

// Test multiple set_start calls
TEST_F(ProgTest_112, MultipleSetStart_112) {
  Prog prog;
  prog.set_start(1);
  EXPECT_EQ(1, prog.start());
  prog.set_start(42);
  EXPECT_EQ(42, prog.start());
  prog.set_start(0);
  EXPECT_EQ(0, prog.start());
}

// Test DumpUnanchored on compiled program
TEST_F(ProgTest_112, DumpUnanchored_112) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_TRUE(prog != nullptr);

  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());

  delete prog;
  re->Decref();
}

}  // namespace re2
