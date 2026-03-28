#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include "re2/re2.h"

namespace re2 {

// Helper to parse a regexp and return it (caller must Decref)
static Regexp* ParseRegexp(const char* pattern, Regexp::ParseFlags flags = Regexp::LikePerl) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, flags, &status);
  return re;
}

// Test that CompileToProg returns a non-null Prog for a simple literal pattern
TEST(CompileToProgTest_327, SimpleLiteral_327) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToProg works for an empty pattern
TEST(CompileToProgTest_327, EmptyPattern_327) {
  Regexp* re = ParseRegexp("");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToProg works for a dot-star pattern
TEST(CompileToProgTest_327, DotStar_327) {
  Regexp* re = ParseRegexp(".*");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToProg works for alternation
TEST(CompileToProgTest_327, Alternation_327) {
  Regexp* re = ParseRegexp("abc|def|ghi");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToProg works for character class
TEST(CompileToProgTest_327, CharacterClass_327) {
  Regexp* re = ParseRegexp("[a-z0-9]");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToProg works for repetition
TEST(CompileToProgTest_327, Repetition_327) {
  Regexp* re = ParseRegexp("a{3,5}");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToProg works for capture groups
TEST(CompileToProgTest_327, CaptureGroups_327) {
  Regexp* re = ParseRegexp("(a)(b)(c)");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToProg works for nested groups
TEST(CompileToProgTest_327, NestedGroups_327) {
  Regexp* re = ParseRegexp("((a|b)c)+");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToProg works with anchors
TEST(CompileToProgTest_327, Anchors_327) {
  Regexp* re = ParseRegexp("^abc$");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToProg with very small max_mem may return null for complex patterns
TEST(CompileToProgTest_327, VerySmallMaxMem_327) {
  Regexp* re = ParseRegexp("a{1000}b{1000}c{1000}");
  ASSERT_NE(re, nullptr);
  // With extremely small max_mem (e.g., 1 byte), compilation should fail
  Prog* prog = re->CompileToProg(1);
  // The result could be null if memory is too small
  // We just verify it doesn't crash; the behavior depends on implementation
  if (prog != nullptr) {
    delete prog;
  }
  re->Decref();
}

// Test that CompileToProg works for question mark (optional)
TEST(CompileToProgTest_327, Optional_327) {
  Regexp* re = ParseRegexp("ab?c");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToProg works for plus (one or more)
TEST(CompileToProgTest_327, PlusQuantifier_327) {
  Regexp* re = ParseRegexp("a+");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToProg works for star (zero or more)
TEST(CompileToProgTest_327, StarQuantifier_327) {
  Regexp* re = ParseRegexp("a*");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToProg works for Unicode patterns
TEST(CompileToProgTest_327, UnicodePattern_327) {
  Regexp* re = ParseRegexp("\\p{L}+");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToProg works for word boundary
TEST(CompileToProgTest_327, WordBoundary_327) {
  Regexp* re = ParseRegexp("\\bword\\b");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToProg with max_mem = 0 (default/unlimited) works for complex patterns
TEST(CompileToProgTest_327, DefaultMaxMemComplex_327) {
  Regexp* re = ParseRegexp("(a|b)*abb(a|b)*");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToReverseProg returns a non-null Prog for a simple pattern
TEST(CompileToReverseProgTest_327, SimpleLiteral_327) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToReverseProg works for an empty pattern
TEST(CompileToReverseProgTest_327, EmptyPattern_327) {
  Regexp* re = ParseRegexp("");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that CompileToReverseProg works for alternation
TEST(CompileToReverseProgTest_327, Alternation_327) {
  Regexp* re = ParseRegexp("abc|xyz");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToProg for a single character
TEST(CompileToProgTest_327, SingleChar_327) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToProg for a complex nested pattern
TEST(CompileToProgTest_327, ComplexNested_327) {
  Regexp* re = ParseRegexp("((([a-z]+)|([0-9]+))\\s*)+");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToProg with a large but reasonable max_mem
TEST(CompileToProgTest_327, LargeMaxMem_327) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(1 << 20);  // 1MB
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToProg for non-greedy quantifiers
TEST(CompileToProgTest_327, NonGreedyQuantifiers_327) {
  Regexp* re = ParseRegexp("a*?b+?c??");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToProg with case-insensitive flag
TEST(CompileToProgTest_327, CaseInsensitive_327) {
  Regexp* re = ParseRegexp("(?i)hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that the Prog produced by CompileToProg has a reasonable size
TEST(CompileToProgTest_327, ProgSize_327) {
  Regexp* re = ParseRegexp("abcdef");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg with very small max_mem
TEST(CompileToReverseProgTest_327, VerySmallMaxMem_327) {
  Regexp* re = ParseRegexp("a{1000}b{1000}");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(1);
  // May return null if memory is insufficient
  if (prog != nullptr) {
    delete prog;
  }
  re->Decref();
}

// Test that CompileToProg and CompileToReverseProg produce different programs
TEST(CompileToProgTest_327, ForwardVsReverse_327) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  Prog* forward = re->CompileToProg(0);
  Prog* reverse = re->CompileToReverseProg(0);
  ASSERT_NE(forward, nullptr);
  ASSERT_NE(reverse, nullptr);
  // They should be different program objects
  EXPECT_NE(forward, reverse);
  delete forward;
  delete reverse;
  re->Decref();
}

// Test CompileToProg for a pattern with named capture groups
TEST(CompileToProgTest_327, NamedCaptures_327) {
  Regexp* re = ParseRegexp("(?P<name>[a-z]+)");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToProg for escaped special characters
TEST(CompileToProgTest_327, EscapedSpecialChars_327) {
  Regexp* re = ParseRegexp("\\(\\)\\[\\]\\{\\}");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

}  // namespace re2
