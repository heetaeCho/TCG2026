#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

// Helper to parse a Regexp from a pattern string
static Regexp* ParseRegexp(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  return re;
}

// Test: CompileSet with a simple alternation and UNANCHORED
TEST(CompileSetTest_331, SimpleAlternationUnanchored_331) {
  // Create a simple alternation regexp: "a|b|c"
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog) {
    delete prog;
  }
  re->Decref();
}

// Test: CompileSet with ANCHOR_BOTH
TEST(CompileSetTest_331, SimplePatternAnchorBoth_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog) {
    delete prog;
  }
  re->Decref();
}

// Test: CompileSet with ANCHOR_START
TEST(CompileSetTest_331, SimplePatternAnchorStart_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("foo|bar", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog) {
    delete prog;
  }
  re->Decref();
}

// Test: CompileSet with very small max_mem might still succeed for tiny pattern
TEST(CompileSetTest_331, SmallMaxMem_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  // Very small memory limit - might still work for trivial patterns
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 256);
  // We don't assert success or failure since it depends on implementation
  // but we verify no crash
  if (prog) {
    delete prog;
  }
  re->Decref();
}

// Test: CompileSet with a single literal pattern
TEST(CompileSetTest_331, SingleLiteral_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("test", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog) {
    delete prog;
  }
  re->Decref();
}

// Test: CompileSet with character class
TEST(CompileSetTest_331, CharacterClass_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]+|[0-9]+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog) {
    delete prog;
  }
  re->Decref();
}

// Test: CompileSet with dot-star pattern
TEST(CompileSetTest_331, DotStarPattern_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*foo.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog) {
    delete prog;
  }
  re->Decref();
}

// Test: CompileSet result has valid start instruction
TEST(CompileSetTest_331, ValidStartInstruction_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def|ghi", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);

  // start() should return a valid index
  EXPECT_GE(prog->start(), 0);
  EXPECT_LT(prog->start(), prog->size());

  delete prog;
  re->Decref();
}

// Test: CompileSet with empty alternation (single empty string)
TEST(CompileSetTest_331, EmptyPattern_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  // Should produce a valid prog or nullptr, but not crash
  if (prog) {
    delete prog;
  }
  re->Decref();
}

// Test: CompileSet with complex alternation
TEST(CompileSetTest_331, ComplexAlternation_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc|def|ghi|jkl|mno)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog) {
    EXPECT_GT(prog->size(), 0);
    delete prog;
  }
  re->Decref();
}

// Test: CompileSet with repeated pattern
TEST(CompileSetTest_331, RepeatedPattern_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}|b{2,4}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog) {
    delete prog;
  }
  re->Decref();
}

// Test: CompileSet with unicode pattern
TEST(CompileSetTest_331, UnicodePattern_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{L}+|\\p{N}+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);

  if (prog) {
    delete prog;
  }
  re->Decref();
}

// Test: CompileSet prog has reasonable bytemap_range
TEST(CompileSetTest_331, BytemapRange_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|xyz", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);

  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);

  delete prog;
  re->Decref();
}

// Test: CompileSet with extremely limited memory for complex pattern
TEST(CompileSetTest_331, InsufficientMemoryComplexPattern_331) {
  RegexpStatus status;
  // A more complex pattern that requires more memory
  Regexp* re = Regexp::Parse(
      "abcdefghij|klmnopqrst|uvwxyz0123|4567890abc|defghijklm",
      Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  // Very tiny memory limit
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1);
  // With extremely limited memory, compilation may fail
  // Just verify no crash
  if (prog) {
    delete prog;
  }
  re->Decref();
}

// Test: CompileSet - verify prog size is positive for non-trivial pattern
TEST(CompileSetTest_331, ProgSizePositive_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello|world|test", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);

  EXPECT_GT(prog->size(), 0);

  delete prog;
  re->Decref();
}

// Test: Compile via CompileToProg (related code path)
TEST(CompileTest_331, CompileToProg_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = re->CompileToProg(1 << 20);
  ASSERT_NE(prog, nullptr);

  EXPECT_GT(prog->size(), 0);
  EXPECT_GE(prog->start(), 0);

  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg
TEST(CompileTest_331, CompileToReverseProg_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = re->CompileToReverseProg(1 << 20);
  ASSERT_NE(prog, nullptr);

  EXPECT_GT(prog->size(), 0);
  EXPECT_TRUE(prog->reversed());

  delete prog;
  re->Decref();
}

// Test: Compile forward prog should not be reversed
TEST(CompileTest_331, ForwardProgNotReversed_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("test", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = re->CompileToProg(1 << 20);
  ASSERT_NE(prog, nullptr);

  EXPECT_FALSE(prog->reversed());

  delete prog;
  re->Decref();
}

// Test: Compile with anchored pattern
TEST(CompileTest_331, AnchoredPattern_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = re->CompileToProg(1 << 20);
  ASSERT_NE(prog, nullptr);

  EXPECT_GT(prog->size(), 0);

  delete prog;
  re->Decref();
}

// Test: CompileSet and verify DFA memory setting
TEST(CompileSetTest_331, DfaMemDefault_331) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);

  // dfa_mem should be set to some reasonable value
  EXPECT_GT(prog->dfa_mem(), 0);

  delete prog;
  re->Decref();
}

}  // namespace re2
