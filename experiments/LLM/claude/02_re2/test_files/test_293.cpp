#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// Test that basic compilation works for simple patterns
TEST(CompilerAltTest_293, CompileSimpleAlternation_293) {
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST(CompilerAltTest_293, CompileNestedAlternation_293) {
  Regexp* re = Regexp::Parse("a|b|c|d", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST(CompilerAltTest_293, CompileAlternationWithEmpty_293) {
  // Pattern that involves alternation with an empty match (e.g., a?)
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST(CompilerAltTest_293, CompileAlternationMatchesBothBranches_293) {
  // Verify that an alternation pattern matches both alternatives
  RE2 pattern("cat|dog");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("cat", pattern));
  EXPECT_TRUE(RE2::FullMatch("dog", pattern));
  EXPECT_FALSE(RE2::FullMatch("bird", pattern));
}

TEST(CompilerAltTest_293, CompileAlternationFirstBranch_293) {
  RE2 pattern("hello|world");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", pattern));
  EXPECT_TRUE(RE2::FullMatch("world", pattern));
  EXPECT_FALSE(RE2::FullMatch("helloworld", pattern));
}

TEST(CompilerAltTest_293, CompileAlternationWithNullable_293) {
  // One branch is nullable (empty string)
  RE2 pattern("|a");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("", pattern));
  EXPECT_TRUE(RE2::FullMatch("a", pattern));
}

TEST(CompilerAltTest_293, CompileAlternationBothNullable_293) {
  // Both branches are nullable
  RE2 pattern("a*|b*");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("", pattern));
  EXPECT_TRUE(RE2::FullMatch("aaa", pattern));
  EXPECT_TRUE(RE2::FullMatch("bbb", pattern));
}

TEST(CompilerAltTest_293, CompileAlternationSingleChar_293) {
  RE2 pattern("[abc]");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("a", pattern));
  EXPECT_TRUE(RE2::FullMatch("b", pattern));
  EXPECT_TRUE(RE2::FullMatch("c", pattern));
  EXPECT_FALSE(RE2::FullMatch("d", pattern));
}

TEST(CompilerAltTest_293, CompileAlternationComplex_293) {
  RE2 pattern("(ab|cd)(ef|gh)");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("abef", pattern));
  EXPECT_TRUE(RE2::FullMatch("abgh", pattern));
  EXPECT_TRUE(RE2::FullMatch("cdef", pattern));
  EXPECT_TRUE(RE2::FullMatch("cdgh", pattern));
  EXPECT_FALSE(RE2::FullMatch("abcd", pattern));
}

TEST(CompilerAltTest_293, CompileAlternationReversed_293) {
  Regexp* re = Regexp::Parse("foo|bar", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST(CompilerAltTest_293, CompileAlternationLowMemory_293) {
  // With very low memory, compilation might fail
  Regexp* re = Regexp::Parse("a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Very low memory limit - may or may not succeed, but should not crash
  Prog* prog = Compiler::Compile(re, false, 1);
  // prog may be nullptr if memory is too low
  delete prog;
  re->Decref();
}

TEST(CompilerAltTest_293, CompileAlternationManyBranches_293) {
  RE2 pattern("a|b|c|d|e|f|g|h|i|j");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("a", pattern));
  EXPECT_TRUE(RE2::FullMatch("e", pattern));
  EXPECT_TRUE(RE2::FullMatch("j", pattern));
  EXPECT_FALSE(RE2::FullMatch("k", pattern));
  EXPECT_FALSE(RE2::FullMatch("ab", pattern));
}

TEST(CompilerAltTest_293, CompileSetWithAlternation_293) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST(CompilerAltTest_293, CompileSetAnchoredWithAlternation_293) {
  Regexp* re = Regexp::Parse("x|y|z", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

TEST(CompilerAltTest_293, AlternationNullablePreservation_293) {
  // Verify that nullable property is properly propagated
  // "a*|b" - first branch nullable, second not
  RE2 pattern("a*|b");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("", pattern));
  EXPECT_TRUE(RE2::FullMatch("a", pattern));
  EXPECT_TRUE(RE2::FullMatch("aaa", pattern));
  EXPECT_TRUE(RE2::FullMatch("b", pattern));
}

TEST(CompilerAltTest_293, AlternationIdenticalBranches_293) {
  RE2 pattern("abc|abc");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", pattern));
  EXPECT_FALSE(RE2::FullMatch("ab", pattern));
}

TEST(CompilerAltTest_293, AlternationEmptyBranches_293) {
  // Both branches empty
  RE2 pattern("|");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("", pattern));
}

TEST(CompilerAltTest_293, AlternationWithQuantifiers_293) {
  RE2 pattern("a+|b+");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("aaa", pattern));
  EXPECT_TRUE(RE2::FullMatch("bbb", pattern));
  EXPECT_FALSE(RE2::FullMatch("", pattern));
  EXPECT_FALSE(RE2::FullMatch("ab", pattern));
}

TEST(CompilerAltTest_293, AlternationPartialMatch_293) {
  RE2 pattern("cat|dog");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::PartialMatch("I have a cat", pattern));
  EXPECT_TRUE(RE2::PartialMatch("I have a dog", pattern));
  EXPECT_FALSE(RE2::PartialMatch("I have a bird", pattern));
}

TEST(CompilerAltTest_293, AlternationWithCapture_293) {
  RE2 pattern("(a|b)(c|d)");
  ASSERT_TRUE(pattern.ok());
  std::string s1, s2;
  EXPECT_TRUE(RE2::FullMatch("ac", pattern, &s1, &s2));
  EXPECT_EQ(s1, "a");
  EXPECT_EQ(s2, "c");
  EXPECT_TRUE(RE2::FullMatch("bd", pattern, &s1, &s2));
  EXPECT_EQ(s1, "b");
  EXPECT_EQ(s2, "d");
}

}  // namespace re2
