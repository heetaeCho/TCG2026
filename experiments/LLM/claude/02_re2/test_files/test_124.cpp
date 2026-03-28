#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"

namespace re2 {

class ProgTest_124 : public ::testing::Test {
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
TEST_F(ProgTest_124, DefaultConstructorAnchorStart_124) {
  EXPECT_FALSE(prog_->anchor_start());
}

TEST_F(ProgTest_124, DefaultConstructorAnchorEnd_124) {
  EXPECT_FALSE(prog_->anchor_end());
}

TEST_F(ProgTest_124, DefaultConstructorReversed_124) {
  EXPECT_FALSE(prog_->reversed());
}

TEST_F(ProgTest_124, DefaultConstructorStart_124) {
  EXPECT_EQ(0, prog_->start());
}

TEST_F(ProgTest_124, DefaultConstructorStartUnanchored_124) {
  EXPECT_EQ(0, prog_->start_unanchored());
}

TEST_F(ProgTest_124, DefaultConstructorSize_124) {
  EXPECT_EQ(0, prog_->size());
}

TEST_F(ProgTest_124, DefaultConstructorBytemapRange_124) {
  EXPECT_EQ(0, prog_->bytemap_range());
}

TEST_F(ProgTest_124, DefaultConstructorDfaMem_124) {
  EXPECT_EQ(0, prog_->dfa_mem());
}

TEST_F(ProgTest_124, DefaultConstructorCanPrefixAccel_124) {
  EXPECT_FALSE(prog_->can_prefix_accel());
}

// Test set_anchor_start
TEST_F(ProgTest_124, SetAnchorStartTrue_124) {
  prog_->set_anchor_start(true);
  EXPECT_TRUE(prog_->anchor_start());
}

TEST_F(ProgTest_124, SetAnchorStartFalse_124) {
  prog_->set_anchor_start(true);
  prog_->set_anchor_start(false);
  EXPECT_FALSE(prog_->anchor_start());
}

// Test set_anchor_end
TEST_F(ProgTest_124, SetAnchorEndTrue_124) {
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_end());
}

TEST_F(ProgTest_124, SetAnchorEndFalse_124) {
  prog_->set_anchor_end(true);
  prog_->set_anchor_end(false);
  EXPECT_FALSE(prog_->anchor_end());
}

// Test set_reversed
TEST_F(ProgTest_124, SetReversedTrue_124) {
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
}

TEST_F(ProgTest_124, SetReversedFalse_124) {
  prog_->set_reversed(true);
  prog_->set_reversed(false);
  EXPECT_FALSE(prog_->reversed());
}

// Test set_start
TEST_F(ProgTest_124, SetStart_124) {
  prog_->set_start(42);
  EXPECT_EQ(42, prog_->start());
}

TEST_F(ProgTest_124, SetStartZero_124) {
  prog_->set_start(10);
  prog_->set_start(0);
  EXPECT_EQ(0, prog_->start());
}

// Test set_start_unanchored
TEST_F(ProgTest_124, SetStartUnanchored_124) {
  prog_->set_start_unanchored(7);
  EXPECT_EQ(7, prog_->start_unanchored());
}

// Test set_dfa_mem
TEST_F(ProgTest_124, SetDfaMem_124) {
  prog_->set_dfa_mem(1024 * 1024);
  EXPECT_EQ(1024 * 1024, prog_->dfa_mem());
}

TEST_F(ProgTest_124, SetDfaMemZero_124) {
  prog_->set_dfa_mem(0);
  EXPECT_EQ(0, prog_->dfa_mem());
}

TEST_F(ProgTest_124, SetDfaMemLargeValue_124) {
  int64_t large = static_cast<int64_t>(1) << 30;
  prog_->set_dfa_mem(large);
  EXPECT_EQ(large, prog_->dfa_mem());
}

// Test IsWordChar static method
TEST_F(ProgTest_124, IsWordCharAlpha_124) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
}

TEST_F(ProgTest_124, IsWordCharDigit_124) {
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
}

TEST_F(ProgTest_124, IsWordCharUnderscore_124) {
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

TEST_F(ProgTest_124, IsWordCharNonWord_124) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
  EXPECT_FALSE(Prog::IsWordChar('!'));
}

// Test EmptyFlags static method
TEST_F(ProgTest_124, EmptyFlagsAtBeginning_124) {
  absl::string_view text("hello");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At the beginning of text, kEmptyBeginText should be set
  EXPECT_NE(0u, flags);
}

TEST_F(ProgTest_124, EmptyFlagsAtEnd_124) {
  absl::string_view text("hello");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At the end of text, kEmptyEndText should be set
  EXPECT_NE(0u, flags);
}

TEST_F(ProgTest_124, EmptyFlagsEmptyString_124) {
  absl::string_view text("");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // Both begin and end flags should be set for empty string
  EXPECT_NE(0u, flags);
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_124, SetDfaShouldBailWhenSlow_124) {
  // Just verify it doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Tests using compiled programs via RE2/Regexp
class ProgFromRegexpTest_124 : public ::testing::Test {
 protected:
};

TEST_F(ProgFromRegexpTest_124, DumpSimplePattern_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, DumpUnanchoredSimplePattern_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, DumpByteMapSimplePattern_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, SizeNonZeroForCompiledProg_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, BytemapRangeNonZero_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]+", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_NE(nullptr, prog->bytemap());
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, PossibleMatchRangeSimple_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);
  std::string min_str, max_str;
  bool ok = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(ok);
  if (ok) {
    EXPECT_LE(min_str, max_str);
  }
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, PossibleMatchRangeMaxlen1_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);
  std::string min_str, max_str;
  bool ok = prog->PossibleMatchRange(&min_str, &max_str, 1);
  // Should still succeed or fail gracefully
  if (ok) {
    EXPECT_LE(min_str, max_str);
  }
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, SearchNFAMatch_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);

  absl::string_view text("xabcx");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  if (found) {
    EXPECT_EQ("abc", match);
  }
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, SearchNFANoMatch_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("xyz", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);

  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, SearchDFAMatch_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(1 << 20);
  ASSERT_NE(nullptr, prog);
  prog->set_dfa_mem(1 << 20);

  absl::string_view text("xabcx");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  if (!failed) {
    EXPECT_TRUE(found);
  }
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, SearchDFANoMatch_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("xyz", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(1 << 20);
  ASSERT_NE(nullptr, prog);
  prog->set_dfa_mem(1 << 20);

  absl::string_view text("abcdef");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  EXPECT_FALSE(failed);
  if (!failed) {
    EXPECT_FALSE(found);
  }
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, IsOnePassSimple_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);
  // Simple literal pattern should be one-pass
  bool onepass = prog->IsOnePass();
  // Just check it doesn't crash; result depends on pattern
  (void)onepass;
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, SearchBitStateMatch_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b)c", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);

  if (prog->CanBitState()) {
    absl::string_view text("xabcx");
    absl::string_view match[2];
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, match, 2);
    EXPECT_TRUE(found);
    if (found) {
      EXPECT_EQ("abc", match[0]);
      EXPECT_EQ("b", match[1]);
    }
  }
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, SearchBitStateNoMatch_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("xyz", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);

  if (prog->CanBitState()) {
    absl::string_view text("abcdef");
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_FALSE(found);
  }
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, CanBitState_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);
  // For a small pattern, CanBitState should return true
  EXPECT_TRUE(prog->CanBitState());
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, AnchoredSearch_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);

  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  if (found) {
    EXPECT_EQ("abc", match);
  }
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, AnchoredSearchNoMatch_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);

  absl::string_view text("xabcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, FlattenDoesNotCrash_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);
  prog->Flatten();
  // Verify program still works after flatten
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, OptimizeDoesNotCrash_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b+c+", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);
  prog->Optimize();
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, EmptyPatternSearch_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);

  absl::string_view text("hello");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  if (found) {
    EXPECT_EQ("", match);
  }
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, PrefixAccelNullWhenNotConfigured_124) {
  Prog* prog = new Prog();
  EXPECT_FALSE(prog->can_prefix_accel());
  delete prog;
}

TEST_F(ProgFromRegexpTest_124, SearchOnePassIfOnePass_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);

  if (prog->IsOnePass()) {
    absl::string_view text("abc");
    absl::string_view match;
    bool found = prog->SearchOnePass(text, text, Prog::kAnchored,
                                      Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    if (found) {
      EXPECT_EQ("abc", match);
    }
  }
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, SearchOnePassNoMatch_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(nullptr, prog);

  if (prog->IsOnePass()) {
    absl::string_view text("xyz");
    absl::string_view match;
    bool found = prog->SearchOnePass(text, text, Prog::kAnchored,
                                      Prog::kFirstMatch, &match, 1);
    EXPECT_FALSE(found);
  }
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, BuildEntireDFA_124) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab|cd", Regexp::LikePerl, &status);
  ASSERT_NE(nullptr, re);
  Prog* prog = re->CompileToProg(1 << 20);
  ASSERT_NE(nullptr, prog);
  prog->set_dfa_mem(1 << 20);

  int states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(states, 0);
  delete prog;
  re->Decref();
}

TEST_F(ProgFromRegexpTest_124, SetMultipleProperties_124) {
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

TEST_F(ProgFromRegexpTest_124, IsWordCharBoundaryValues_124) {
  // Test boundary ASCII values
  EXPECT_FALSE(Prog::IsWordChar(0));    // null
  EXPECT_FALSE(Prog::IsWordChar(47));   // '/' just before '0'
  EXPECT_TRUE(Prog::IsWordChar(48));    // '0'
  EXPECT_TRUE(Prog::IsWordChar(57));    // '9'
  EXPECT_FALSE(Prog::IsWordChar(58));   // ':' just after '9'
  EXPECT_FALSE(Prog::IsWordChar(64));   // '@' just before 'A'
  EXPECT_TRUE(Prog::IsWordChar(65));    // 'A'
  EXPECT_TRUE(Prog::IsWordChar(90));    // 'Z'
  EXPECT_FALSE(Prog::IsWordChar(91));   // '[' just after 'Z'
  EXPECT_TRUE(Prog::IsWordChar(95));    // '_'
  EXPECT_FALSE(Prog::IsWordChar(96));   // '`' just before 'a'
  EXPECT_TRUE(Prog::IsWordChar(97));    // 'a'
  EXPECT_TRUE(Prog::IsWordChar(122));   // 'z'
  EXPECT_FALSE(Prog::IsWordChar(123));  // '{' just after 'z'
  EXPECT_FALSE(Prog::IsWordChar(255));  // max uint8_t
}

}  // namespace re2
