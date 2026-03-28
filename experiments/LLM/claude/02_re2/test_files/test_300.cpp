#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include "re2/re2.h"

#include <string>
#include <memory>

namespace re2 {

// Test fixture for Compiler tests via the public Compile/CompileSet interface
class CompilerTest_300 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Helper to parse a regexp and compile it
static Prog* CompileRegexp(const char* pattern, int64_t max_mem = 0) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  if (max_mem == 0) max_mem = 8 << 20;  // 8MB default
  Prog* prog = Compiler::Compile(re, false, max_mem);
  re->Decref();
  return prog;
}

// Test: Compiling a simple literal pattern succeeds
TEST_F(CompilerTest_300, CompileSimpleLiteral_300) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiling an empty pattern succeeds
TEST_F(CompilerTest_300, CompileEmptyPattern_300) {
  Prog* prog = CompileRegexp("");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiling a pattern with alternation
TEST_F(CompilerTest_300, CompileAlternation_300) {
  Prog* prog = CompileRegexp("a|b|c");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiling a pattern with repetition (star)
TEST_F(CompilerTest_300, CompileStar_300) {
  Prog* prog = CompileRegexp("a*");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiling a pattern with repetition (plus)
TEST_F(CompilerTest_300, CompilePlus_300) {
  Prog* prog = CompileRegexp("a+");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiling a pattern with repetition (question mark)
TEST_F(CompilerTest_300, CompileQuest_300) {
  Prog* prog = CompileRegexp("a?");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiling a pattern with capture groups
TEST_F(CompilerTest_300, CompileCapture_300) {
  Prog* prog = CompileRegexp("(a)(b)(c)");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiling a pattern with character classes
TEST_F(CompilerTest_300, CompileCharClass_300) {
  Prog* prog = CompileRegexp("[a-z]");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiling a pattern with dot (any character)
TEST_F(CompilerTest_300, CompileDot_300) {
  Prog* prog = CompileRegexp(".*");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiling a pattern with anchors (empty width)
TEST_F(CompilerTest_300, CompileAnchors_300) {
  Prog* prog = CompileRegexp("^hello$");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiling a pattern with word boundary (empty width)
TEST_F(CompilerTest_300, CompileWordBoundary_300) {
  Prog* prog = CompileRegexp("\\bhello\\b");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiling a complex pattern
TEST_F(CompilerTest_300, CompileComplexPattern_300) {
  Prog* prog = CompileRegexp("(a+b*|c?)d{2,5}[e-h]");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiling a pattern with non-greedy repetition
TEST_F(CompilerTest_300, CompileNonGreedy_300) {
  Prog* prog = CompileRegexp("a*?b+?c??");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiling reversed
TEST_F(CompilerTest_300, CompileReversed_300) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 8 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test: Compiling with very small max_mem may fail or produce limited prog
TEST_F(CompilerTest_300, CompileWithVerySmallMaxMem_300) {
  // With extremely small max_mem, compilation might still succeed for trivial patterns
  // or return nullptr for complex ones
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{1000}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Very small memory limit
  Prog* prog = Compiler::Compile(re, false, 1);
  // The result could be nullptr or a valid prog depending on implementation
  // We just verify no crash
  if (prog != nullptr) {
    delete prog;
  }
  re->Decref();
}

// Test: CompileSet with unanchored anchor
TEST_F(CompilerTest_300, CompileSetUnanchored_300) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 8 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test: CompileSet with ANCHOR_BOTH
TEST_F(CompilerTest_300, CompileSetAnchorBoth_300) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 8 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test: CompileSet with ANCHOR_START
TEST_F(CompilerTest_300, CompileSetAnchorStart_300) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 8 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test: Compiling a pattern with unicode ranges
TEST_F(CompilerTest_300, CompileUnicodeRange_300) {
  Prog* prog = CompileRegexp("[\\x{0080}-\\x{10FFFF}]");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiling a pattern with nested groups and quantifiers
TEST_F(CompilerTest_300, CompileNestedGroups_300) {
  Prog* prog = CompileRegexp("((a+)(b*)?)+");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiled program can match simple strings correctly
TEST_F(CompilerTest_300, CompiledProgramMatchesCorrectly_300) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test: Compiled program with alternation matches correctly
TEST_F(CompilerTest_300, CompiledAlternationMatches_300) {
  RE2 re("cat|dog");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("I have a cat", re));
  EXPECT_TRUE(RE2::PartialMatch("I have a dog", re));
  EXPECT_FALSE(RE2::PartialMatch("I have a fish", re));
}

// Test: Compiled program with anchors
TEST_F(CompilerTest_300, CompiledAnchorsMatch_300) {
  RE2 re("^start");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("start of line", re));
  EXPECT_FALSE(RE2::PartialMatch("not start of line", re));
}

// Test: Compiled program with star quantifier
TEST_F(CompilerTest_300, CompiledStarQuantifier_300) {
  RE2 re("^a*$");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_FALSE(RE2::FullMatch("b", re));
}

// Test: Compiled program with plus quantifier
TEST_F(CompilerTest_300, CompiledPlusQuantifier_300) {
  RE2 re("^a+$");
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_FALSE(RE2::FullMatch("b", re));
}

// Test: Compiled program with question mark quantifier
TEST_F(CompilerTest_300, CompiledQuestQuantifier_300) {
  RE2 re("^a?$");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::FullMatch("aa", re));
}

// Test: Compiling case-insensitive byte range
TEST_F(CompilerTest_300, CompileCaseInsensitive_300) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("HeLLo", re));
}

// Test: Compile with capture and extraction
TEST_F(CompilerTest_300, CompileCaptureExtraction_300) {
  std::string captured;
  EXPECT_TRUE(RE2::FullMatch("hello123", "(\\w+)(\\d+)", &captured));
  // captured should be "hello" (first group)
  EXPECT_EQ(captured, "hello");
}

// Test: Compile a single byte range pattern
TEST_F(CompilerTest_300, CompileSingleByteRange_300) {
  Prog* prog = CompileRegexp("[a-z]");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compile Latin1 range pattern
TEST_F(CompilerTest_300, CompileLatin1Range_300) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[\\x00-\\xff]", Regexp::Latin1 | Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 8 << 20);
  ASSERT_NE(prog, nullptr);
  re->Decref();
  delete prog;
}

// Test: Compile program size is reasonable
TEST_F(CompilerTest_300, CompileProgramSize_300) {
  Prog* prog = CompileRegexp("abc");
  ASSERT_NE(prog, nullptr);
  // A simple 3-letter pattern should have a small number of instructions
  EXPECT_GT(prog->size(), 0);
  delete prog;
}

// Test: Compiling a pattern with nested alternation and concatenation
TEST_F(CompilerTest_300, CompileNestedAltCat_300) {
  Prog* prog = CompileRegexp("(ab|cd)(ef|gh)");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiling a pattern with repetition count
TEST_F(CompilerTest_300, CompileRepetitionCount_300) {
  Prog* prog = CompileRegexp("a{3,5}");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Compiled program handles empty width operators correctly
TEST_F(CompilerTest_300, CompiledEmptyWidthBeginLine_300) {
  RE2 re("^abc");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("abc", re));
  EXPECT_TRUE(RE2::PartialMatch("abcdef", re));
  EXPECT_FALSE(RE2::PartialMatch("xabc", re));
}

// Test: Compiled program handles end-of-line anchor
TEST_F(CompilerTest_300, CompiledEmptyWidthEndLine_300) {
  RE2 re("abc$");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("abc", re));
  EXPECT_TRUE(RE2::PartialMatch("xyzabc", re));
  EXPECT_FALSE(RE2::PartialMatch("abcx", re));
}

// Test: Compiling nullptr regexp should be handled gracefully
TEST_F(CompilerTest_300, CompileNullRegexp_300) {
  // Passing nullptr - implementation should handle this or we verify no crash
  // This test primarily verifies robustness
  Prog* prog = Compiler::Compile(nullptr, false, 8 << 20);
  // May return nullptr - just check no crash
  if (prog != nullptr) {
    delete prog;
  }
}

// Test: Compiling a very long alternation
TEST_F(CompilerTest_300, CompileLongAlternation_300) {
  std::string pattern;
  for (int i = 0; i < 100; i++) {
    if (i > 0) pattern += "|";
    pattern += "word" + std::to_string(i);
  }
  Prog* prog = CompileRegexp(pattern.c_str());
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: Ensure compiled programs with different patterns are distinct
TEST_F(CompilerTest_300, DifferentPatternsProduceDifferentProgs_300) {
  Prog* prog1 = CompileRegexp("abc");
  Prog* prog2 = CompileRegexp("xyz");
  ASSERT_NE(prog1, nullptr);
  ASSERT_NE(prog2, nullptr);
  // They should be different program objects
  EXPECT_NE(prog1, prog2);
  delete prog1;
  delete prog2;
}

// Test: Compile with foldcase byte range
TEST_F(CompilerTest_300, CompileFoldcaseByteRange_300) {
  RE2 re("(?i)[a-z]");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("A", re));
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("Z", re));
  EXPECT_TRUE(RE2::FullMatch("z", re));
  EXPECT_FALSE(RE2::FullMatch("1", re));
}

// Test: Compile with high Unicode code points
TEST_F(CompilerTest_300, CompileHighUnicode_300) {
  Prog* prog = CompileRegexp("[\\x{10000}-\\x{10FFFF}]");
  ASSERT_NE(prog, nullptr);
  delete prog;
}

// Test: DotStar is implicitly used in unanchored matching
TEST_F(CompilerTest_300, UnanchoredMatchImpliesDotStar_300) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("say hello world", re));
}

}  // namespace re2
