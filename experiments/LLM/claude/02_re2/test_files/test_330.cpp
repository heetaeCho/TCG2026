#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class CompileSetTest_330 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test CompileSet with a simple literal pattern and UNANCHORED anchor
TEST_F(CompileSetTest_330, SimpleLiteralUnanchored_330) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog != nullptr) {
    EXPECT_TRUE(prog->anchor_start());
    EXPECT_TRUE(prog->anchor_end());
    delete prog;
  }
  re->Decref();
}

// Test CompileSet with ANCHOR_BOTH
TEST_F(CompileSetTest_330, SimpleLiteralAnchorBoth_330) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog != nullptr) {
    EXPECT_TRUE(prog->anchor_start());
    EXPECT_TRUE(prog->anchor_end());
    delete prog;
  }
  re->Decref();
}

// Test CompileSet with ANCHOR_START
TEST_F(CompileSetTest_330, SimpleLiteralAnchorStart_330) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("foo", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog != nullptr) {
    EXPECT_TRUE(prog->anchor_start());
    EXPECT_TRUE(prog->anchor_end());
    delete prog;
  }
  re->Decref();
}

// Test CompileSet with character class pattern
TEST_F(CompileSetTest_330, CharacterClassPattern_330) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog != nullptr) {
    delete prog;
  }
  re->Decref();
}

// Test CompileSet with alternation pattern
TEST_F(CompileSetTest_330, AlternationPattern_330) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def|ghi", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog != nullptr) {
    delete prog;
  }
  re->Decref();
}

// Test CompileSet with very small max_mem - may fail due to memory constraints
TEST_F(CompileSetTest_330, VerySmallMaxMem_330) {
  RegexpStatus status;
  // Use a pattern complex enough to exceed tiny memory budget
  Regexp* re = Regexp::Parse(
      "abcdefghijklmnopqrstuvwxyz|ABCDEFGHIJKLMNOPQRSTUVWXYZ|0123456789",
      Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  // With a very small memory limit, the compilation might fail
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1);
  // It may or may not be null; the important thing is no crash
  if (prog != nullptr) {
    delete prog;
  }
  re->Decref();
}

// Test CompileSet with empty pattern
TEST_F(CompileSetTest_330, EmptyPattern_330) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  // Empty pattern should compile successfully
  if (prog != nullptr) {
    EXPECT_TRUE(prog->anchor_start());
    EXPECT_TRUE(prog->anchor_end());
    delete prog;
  }
  re->Decref();
}

// Test CompileSet with dot-star pattern
TEST_F(CompileSetTest_330, DotStarPattern_330) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog != nullptr) {
    delete prog;
  }
  re->Decref();
}

// Test CompileSet with a single character pattern
TEST_F(CompileSetTest_330, SingleCharPattern_330) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog != nullptr) {
    delete prog;
  }
  re->Decref();
}

// Test CompileSet with repetition pattern
TEST_F(CompileSetTest_330, RepetitionPattern_330) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog != nullptr) {
    delete prog;
  }
  re->Decref();
}

// Test CompileSet with Unicode pattern
TEST_F(CompileSetTest_330, UnicodePattern_330) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog != nullptr) {
    delete prog;
  }
  re->Decref();
}

// Test CompileSet - the compiled program can search via DFA
TEST_F(CompileSetTest_330, CompiledProgCanSearchDFA_330) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);

  bool dfa_failed = false;
  absl::string_view text = "say hello world";
  bool matched = prog->SearchDFA(text, text, Prog::kAnchored,
                                  Prog::kManyMatch, nullptr, &dfa_failed,
                                  nullptr);
  // With anchored search on "say hello world" for pattern "hello" (unanchored compiled set),
  // the DFA should not fail since CompileSet already verified DFA works
  EXPECT_FALSE(dfa_failed);

  delete prog;
  re->Decref();
}

// Test CompileSet with nested groups
TEST_F(CompileSetTest_330, NestedGroupsPattern_330) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a(b(c)))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog != nullptr) {
    delete prog;
  }
  re->Decref();
}

// Test CompileSet with large memory budget
TEST_F(CompileSetTest_330, LargeMemoryBudget_330) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(foo|bar|baz)+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 24);
  EXPECT_NE(prog, nullptr);

  if (prog != nullptr) {
    delete prog;
  }
  re->Decref();
}

// Test that start and start_unanchored are set to the same value
TEST_F(CompileSetTest_330, StartAndStartUnanchoredSame_330) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("test", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);

  // According to CompileSet, set_start and set_start_unanchored are both set to all.begin
  EXPECT_EQ(prog->start(), prog->start_unanchored());

  delete prog;
  re->Decref();
}

// Test CompileSet with case-insensitive flag
TEST_F(CompileSetTest_330, CaseInsensitivePattern_330) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog != nullptr) {
    delete prog;
  }
  re->Decref();
}

}  // namespace re2
