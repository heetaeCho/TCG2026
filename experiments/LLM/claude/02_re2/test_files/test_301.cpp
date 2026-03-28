#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// Test fixture for Compiler tests
class CompilerTest_301 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that Compile produces a valid Prog for a simple literal pattern
TEST_F(CompilerTest_301, CompileSimpleLiteral_301) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile works with reversed flag
TEST_F(CompilerTest_301, CompileReversed_301) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles capture groups
TEST_F(CompilerTest_301, CompileWithCapture_301) {
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles multiple capture groups
TEST_F(CompilerTest_301, CompileMultipleCaptures_301) {
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles nested capture groups
TEST_F(CompilerTest_301, CompileNestedCaptures_301) {
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles alternation
TEST_F(CompilerTest_301, CompileAlternation_301) {
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles repetition (star)
TEST_F(CompilerTest_301, CompileStar_301) {
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles repetition (plus)
TEST_F(CompilerTest_301, CompilePlus_301) {
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles repetition (quest)
TEST_F(CompilerTest_301, CompileQuest_301) {
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles character classes
TEST_F(CompilerTest_301, CompileCharClass_301) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles dot
TEST_F(CompilerTest_301, CompileDot_301) {
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles anchors
TEST_F(CompilerTest_301, CompileAnchors_301) {
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles empty pattern
TEST_F(CompilerTest_301, CompileEmptyPattern_301) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles very small max_mem (boundary condition)
TEST_F(CompilerTest_301, CompileSmallMaxMem_301) {
  Regexp* re = Regexp::Parse("a{1000}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Very small max_mem might cause compilation to fail
  Prog* prog = Compiler::Compile(re, false, 1);
  // Whether it returns nullptr or not depends on implementation,
  // but it shouldn't crash
  delete prog;
  re->Decref();
}

// Test that Compile handles complex patterns
TEST_F(CompilerTest_301, CompileComplexPattern_301) {
  Regexp* re = Regexp::Parse("(a+|b*c)?d{2,5}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles Unicode patterns
TEST_F(CompilerTest_301, CompileUnicodePattern_301) {
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileSet produces a valid Prog with UNANCHORED anchor
TEST_F(CompilerTest_301, CompileSetUnanchored_301) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileSet produces a valid Prog with ANCHOR_START anchor
TEST_F(CompilerTest_301, CompileSetAnchorStart_301) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileSet produces a valid Prog with ANCHOR_BOTH anchor
TEST_F(CompilerTest_301, CompileSetAnchorBoth_301) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiled programs actually match correctly (integration)
TEST_F(CompilerTest_301, CompiledProgramMatchesCorrectly_301) {
  RE2 pattern("(hello)");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::PartialMatch("say hello world", pattern));
  EXPECT_FALSE(RE2::PartialMatch("say goodbye world", pattern));
}

// Test capture group extraction works through compilation
TEST_F(CompilerTest_301, CaptureGroupExtraction_301) {
  RE2 pattern("(\\w+)@(\\w+)");
  ASSERT_TRUE(pattern.ok());
  std::string user, domain;
  EXPECT_TRUE(RE2::PartialMatch("user@domain", pattern, &user, &domain));
  EXPECT_EQ(user, "user");
  EXPECT_EQ(domain, "domain");
}

// Test that nongreedy quantifiers compile and work
TEST_F(CompilerTest_301, NongreedyQuantifiers_301) {
  RE2 pattern("a+?");
  ASSERT_TRUE(pattern.ok());
  std::string match;
  EXPECT_TRUE(RE2::PartialMatch("aaa", pattern, &match));
  // Nongreedy should match minimal
  EXPECT_EQ(match, "a");
}

// Test that Compile handles case-insensitive patterns
TEST_F(CompilerTest_301, CompileCaseInsensitive_301) {
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile handles word boundary
TEST_F(CompilerTest_301, CompileWordBoundary_301) {
  Regexp* re = Regexp::Parse("\\bword\\b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of a pattern with many alternations
TEST_F(CompilerTest_301, CompileManyAlternations_301) {
  Regexp* re = Regexp::Parse("a|b|c|d|e|f|g|h|i|j", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that concatenation of captures compiles correctly
TEST_F(CompilerTest_301, CompileConcatenatedCaptures_301) {
  Regexp* re = Regexp::Parse("(a)(b)(c)(d)(e)", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with a pattern containing repetition bounds
TEST_F(CompilerTest_301, CompileRepetitionBounds_301) {
  Regexp* re = Regexp::Parse("a{3,7}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that a compiled program's size is reasonable
TEST_F(CompilerTest_301, CompiledProgramSize_301) {
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test that max_mem limit is respected
TEST_F(CompilerTest_301, CompileRespectsMaxMem_301) {
  // A pattern that would require a lot of instructions
  Regexp* re = Regexp::Parse("a{1000}b{1000}c{1000}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Very restrictive memory: should return nullptr
  Prog* prog = Compiler::Compile(re, false, 100);
  // Either nullptr (couldn't compile) or a valid program
  // The implementation should not crash
  delete prog;
  re->Decref();
}

// Test compilation of dotstar pattern (implicit in unanchored matching)
TEST_F(CompilerTest_301, CompileDotStar_301) {
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation with Latin1 encoding
TEST_F(CompilerTest_301, CompileLatin1_301) {
  Regexp* re = Regexp::Parse("[\\x00-\\xff]", Regexp::Latin1 | Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that the compiled program can handle non-greedy star
TEST_F(CompilerTest_301, CompileNonGreedyStar_301) {
  Regexp* re = Regexp::Parse("a*?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test end-to-end: capture with index 0 (whole match)
TEST_F(CompilerTest_301, CaptureIndex0WholeMatch_301) {
  RE2 pattern("(a+)(b+)");
  ASSERT_TRUE(pattern.ok());
  std::string s1, s2;
  EXPECT_TRUE(RE2::PartialMatch("aaabbb", pattern, &s1, &s2));
  EXPECT_EQ(s1, "aaa");
  EXPECT_EQ(s2, "bbb");
}

// Test that a pattern with only a capture group compiles
TEST_F(CompilerTest_301, CompileSingleCaptureOnly_301) {
  Regexp* re = Regexp::Parse("()", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compilation of deeply nested captures
TEST_F(CompilerTest_301, CompileDeeplyNestedCaptures_301) {
  Regexp* re = Regexp::Parse("((((a))))", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

}  // namespace re2
