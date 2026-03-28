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

// Test: CompileToReverseProg with a simple literal pattern
TEST(CompileToReverseProgTest_328, SimpleLiteral_328) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with a single character
TEST(CompileToReverseProgTest_328, SingleChar_328) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with alternation
TEST(CompileToReverseProgTest_328, Alternation_328) {
  Regexp* re = ParseRegexp("abc|def");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with repetition
TEST(CompileToReverseProgTest_328, Repetition_328) {
  Regexp* re = ParseRegexp("a*b+c?");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with character class
TEST(CompileToReverseProgTest_328, CharClass_328) {
  Regexp* re = ParseRegexp("[a-z0-9]");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with dot (any character)
TEST(CompileToReverseProgTest_328, DotAny_328) {
  Regexp* re = ParseRegexp(".*");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with capture groups
TEST(CompileToReverseProgTest_328, CaptureGroups_328) {
  Regexp* re = ParseRegexp("(abc)(def)");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with empty pattern
TEST(CompileToReverseProgTest_328, EmptyPattern_328) {
  Regexp* re = ParseRegexp("");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with very small max_mem that should cause failure
TEST(CompileToReverseProgTest_328, VerySmallMaxMem_328) {
  Regexp* re = ParseRegexp("abcdefghijklmnopqrstuvwxyz");
  ASSERT_NE(re, nullptr);
  // Use an extremely small max_mem that should be insufficient
  Prog* prog = re->CompileToReverseProg(1);
  // With extremely small memory, compilation might fail and return nullptr
  // or succeed depending on implementation. We just check it doesn't crash.
  if (prog != nullptr) {
    EXPECT_TRUE(prog->reversed());
    delete prog;
  }
  re->Decref();
}

// Test: CompileToReverseProg with complex pattern
TEST(CompileToReverseProgTest_328, ComplexPattern_328) {
  Regexp* re = ParseRegexp("(a|b)*abb");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with nested groups
TEST(CompileToReverseProgTest_328, NestedGroups_328) {
  Regexp* re = ParseRegexp("((a+)(b+))*");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with Unicode
TEST(CompileToReverseProgTest_328, UnicodePattern_328) {
  Regexp* re = ParseRegexp("\\p{L}+");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with anchors
TEST(CompileToReverseProgTest_328, Anchors_328) {
  Regexp* re = ParseRegexp("^abc$");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with bounded repetition
TEST(CompileToReverseProgTest_328, BoundedRepetition_328) {
  Regexp* re = ParseRegexp("a{2,5}");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with max_mem = 0 (default/unlimited)
TEST(CompileToReverseProgTest_328, DefaultMaxMem_328) {
  Regexp* re = ParseRegexp("foo|bar|baz");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg returns a Prog with positive size
TEST(CompileToReverseProgTest_328, ProgHasPositiveSize_328) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test: CompileToProg vs CompileToReverseProg differ in reversed flag
TEST(CompileToReverseProgTest_328, ForwardVsReverse_328) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  
  Prog* forward_prog = re->CompileToProg(0);
  ASSERT_NE(forward_prog, nullptr);
  EXPECT_FALSE(forward_prog->reversed());
  
  Prog* reverse_prog = re->CompileToReverseProg(0);
  ASSERT_NE(reverse_prog, nullptr);
  EXPECT_TRUE(reverse_prog->reversed());
  
  delete forward_prog;
  delete reverse_prog;
  re->Decref();
}

// Test: CompileToReverseProg with non-greedy quantifiers
TEST(CompileToReverseProgTest_328, NonGreedyQuantifiers_328) {
  Regexp* re = ParseRegexp("a*?b+?c??");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with case-insensitive flag
TEST(CompileToReverseProgTest_328, CaseInsensitive_328) {
  Regexp* re = ParseRegexp("(?i)abc");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

// Test: CompileToReverseProg with a large explicit max_mem
TEST(CompileToReverseProgTest_328, LargeMaxMem_328) {
  Regexp* re = ParseRegexp("(a|b|c|d|e|f|g){1,10}");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(1 << 20);  // 1MB
  ASSERT_NE(prog, nullptr);
  EXPECT_TRUE(prog->reversed());
  delete prog;
  re->Decref();
}

}  // namespace re2
