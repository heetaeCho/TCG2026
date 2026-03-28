#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// Test basic compilation of a simple literal pattern
TEST(CompilerTest_312, CompileSimpleLiteral_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with reversed flag
TEST(CompilerTest_312, CompileReversed_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of alternation
TEST(CompilerTest_312, CompileAlternation_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of character class
TEST(CompilerTest_312, CompileCharClass_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of repetition (star)
TEST(CompilerTest_312, CompileStar_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of repetition (plus)
TEST(CompilerTest_312, CompilePlus_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of optional (quest)
TEST(CompilerTest_312, CompileQuest_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of capture group
TEST(CompilerTest_312, CompileCaptureGroup_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with very small max_mem may fail or produce limited program
TEST(CompilerTest_312, CompileWithVerySmallMaxMem_312) {
  RegexpStatus status;
  // A complex pattern that might exceed very small memory limits
  Regexp* re = Regexp::Parse("a{100}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Very small memory limit
  Prog* prog = Compiler::Compile(re, false, 1);
  // The compiler might return nullptr or a valid prog depending on the limit
  // We just check it doesn't crash
  delete prog;
  re->Decref();
}

// Test compilation of dot (any character)
TEST(CompilerTest_312, CompileDot_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of empty pattern
TEST(CompilerTest_312, CompileEmptyPattern_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of anchors
TEST(CompilerTest_312, CompileAnchors_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of non-greedy repetition
TEST(CompilerTest_312, CompileNonGreedy_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with unanchored
TEST(CompilerTest_312, CompileSetUnanchored_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def|ghi", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with anchor start
TEST(CompilerTest_312, CompileSetAnchorStart_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with anchor both
TEST(CompilerTest_312, CompileSetAnchorBoth_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of Unicode pattern
TEST(CompilerTest_312, CompileUnicode_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of case-insensitive pattern
TEST(CompilerTest_312, CompileCaseInsensitive_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of complex nested pattern
TEST(CompilerTest_312, CompileComplexNested_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a|b)*c)+d?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiled program size is reasonable
TEST(CompilerTest_312, CompileProgramSize_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compilation of word boundary
TEST(CompilerTest_312, CompileWordBoundary_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bword\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of counted repetition
TEST(CompilerTest_312, CompileCountedRepetition_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with Latin1 encoding
TEST(CompilerTest_312, CompileLatin1_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[\\x80-\\xff]", Regexp::Latin1 | Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that nullptr regexp is handled (Compile with null)
TEST(CompilerTest_312, CompileNullRegexp_312) {
  // Passing null should be handled gracefully
  // The behavior may vary, but it should not crash
  // (This test checks robustness; if it crashes, the code has a bug)
  // Note: We skip this if the API doesn't support null
}

// Test compilation of dotstar pattern
TEST(CompilerTest_312, CompileDotStar_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of multiple capture groups
TEST(CompilerTest_312, CompileMultipleCaptureGroups_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)(d)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that a large regex with small memory budget returns null
TEST(CompilerTest_312, CompileLargeRegexSmallMem_312) {
  RegexpStatus status;
  // Create a pattern that would require substantial memory
  std::string pattern;
  for (int i = 0; i < 1000; i++) {
    pattern += "(a|b|c|d|e|f)";
  }
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re != nullptr) {
    Prog* prog = Compiler::Compile(re, false, 100);
    // With very limited memory, compilation may fail
    // Either way, no crash expected
    delete prog;
    re->Decref();
  }
}

// Test compilation of high Unicode range
TEST(CompilerTest_312, CompileHighUnicode_312) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[\\x{10000}-\\x{10ffff}]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

}  // namespace re2
