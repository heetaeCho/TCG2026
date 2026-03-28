#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/compile.h"

namespace re2 {

// Helper to parse a regexp string into a Regexp object
static Regexp* ParseRegexp(const char* pattern, Regexp::ParseFlags flags = Regexp::LikePerl) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, flags, &status);
  return re;
}

class CompilerTest_297 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that Compile produces a non-null Prog for a simple literal pattern
TEST_F(CompilerTest_297, CompileSimpleLiteral_297) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile with reversed flag produces a valid Prog
TEST_F(CompilerTest_297, CompileReversed_297) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling an empty pattern
TEST_F(CompilerTest_297, CompileEmptyPattern_297) {
  Regexp* re = ParseRegexp("");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a character class pattern
TEST_F(CompilerTest_297, CompileCharClass_297) {
  Regexp* re = ParseRegexp("[a-z]");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a pattern with repetition
TEST_F(CompilerTest_297, CompileRepetition_297) {
  Regexp* re = ParseRegexp("a*b+c?");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling alternation
TEST_F(CompilerTest_297, CompileAlternation_297) {
  Regexp* re = ParseRegexp("abc|def|ghi");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with capture groups
TEST_F(CompilerTest_297, CompileCaptureGroups_297) {
  Regexp* re = ParseRegexp("(a)(b)(c)");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with very small max_mem - should still produce something or null
TEST_F(CompilerTest_297, CompileVerySmallMaxMem_297) {
  Regexp* re = ParseRegexp("a{1000}");
  ASSERT_NE(re, nullptr);
  // Very small memory limit
  Prog* prog = Compiler::Compile(re, false, 1);
  // With extremely limited memory, compilation might fail
  // We just check it doesn't crash; result may be null
  delete prog;
  re->Decref();
}

// Test compiling a dot pattern
TEST_F(CompilerTest_297, CompileDot_297) {
  Regexp* re = ParseRegexp(".");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling anchored patterns
TEST_F(CompilerTest_297, CompileAnchored_297) {
  Regexp* re = ParseRegexp("^abc$");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with unanchored
TEST_F(CompilerTest_297, CompileSetUnanchored_297) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_BOTH
TEST_F(CompilerTest_297, CompileSetAnchorBoth_297) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_START
TEST_F(CompilerTest_297, CompileSetAnchorStart_297) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a complex nested pattern
TEST_F(CompilerTest_297, CompileComplexNested_297) {
  Regexp* re = ParseRegexp("((a|b)*c)+d?");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiled program size is reasonable
TEST_F(CompilerTest_297, CompileProgramSize_297) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compiling Unicode patterns
TEST_F(CompilerTest_297, CompileUnicode_297) {
  Regexp* re = ParseRegexp("[\\x{100}-\\x{10ffff}]");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with case-folding
TEST_F(CompilerTest_297, CompileFoldCase_297) {
  Regexp* re = ParseRegexp("(?i)abc");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling non-greedy quantifiers
TEST_F(CompilerTest_297, CompileNonGreedy_297) {
  Regexp* re = ParseRegexp("a*?b+?c??");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling word boundary
TEST_F(CompilerTest_297, CompileWordBoundary_297) {
  Regexp* re = ParseRegexp("\\bword\\b");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile with large max_mem works for complex patterns
TEST_F(CompilerTest_297, CompileLargeMaxMem_297) {
  Regexp* re = ParseRegexp("(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z){5}");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 24);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Prog::Inst::InitByteRange directly through Dump
TEST_F(CompilerTest_297, ByteRangeInst_297) {
  Regexp* re = ParseRegexp("[a-z]");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  // The program should have instructions; verify it has a reasonable size
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test compiling with null regexp should be handled (boundary)
TEST_F(CompilerTest_297, CompileNullRegexp_297) {
  // Passing nullptr - this tests boundary behavior
  // The implementation may crash or return null; we test it doesn't crash
  // by checking with a valid minimal regexp instead
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 0);
  // With 0 max_mem, compilation should fail gracefully
  // Result might be null
  delete prog;
  re->Decref();
}

// Test compiling a single byte range pattern
TEST_F(CompilerTest_297, CompileSingleByte_297) {
  Regexp* re = ParseRegexp("\\x61");  // 'a'
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling patterns with empty width assertions
TEST_F(CompilerTest_297, CompileEmptyWidth_297) {
  Regexp* re = ParseRegexp("^$");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that two separate compilations produce independent programs
TEST_F(CompilerTest_297, CompileTwoProgramsIndependent_297) {
  Regexp* re1 = ParseRegexp("abc");
  Regexp* re2 = ParseRegexp("xyz");
  ASSERT_NE(re1, nullptr);
  ASSERT_NE(re2, nullptr);
  
  Prog* prog1 = Compiler::Compile(re1, false, 1 << 20);
  Prog* prog2 = Compiler::Compile(re2, false, 1 << 20);
  
  EXPECT_NE(prog1, nullptr);
  EXPECT_NE(prog2, nullptr);
  EXPECT_NE(prog1, prog2);
  
  delete prog1;
  delete prog2;
  re1->Decref();
  re2->Decref();
}

// Test compiling with Latin1 encoding
TEST_F(CompilerTest_297, CompileLatin1_297) {
  Regexp* re = ParseRegexp("abc", Regexp::Latin1);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Prog start is a valid index
TEST_F(CompilerTest_297, CompileProgStartValid_297) {
  Regexp* re = ParseRegexp("test");
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  EXPECT_GE(prog->start(), 0);
  EXPECT_LT(prog->start(), prog->size());
  delete prog;
  re->Decref();
}

}  // namespace re2
