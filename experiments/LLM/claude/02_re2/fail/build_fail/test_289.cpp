#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// Test Compile with a simple regexp
TEST(CompilerTest_289, CompileSimpleRegexp_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test Compile with reversed flag
TEST(CompilerTest_289, CompileReversed_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test Compile with very small max_mem that should cause failure
TEST(CompilerTest_289, CompileWithVerySmallMaxMem_289) {
  RegexpStatus status;
  // Use a complex regexp that would require many instructions
  Regexp* re = Regexp::Parse("a{1000}b{1000}c{1000}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  // Very small memory limit - may return nullptr
  Prog* prog = Compiler::Compile(re, false, 1);
  // With extremely small memory, compilation should fail
  // (exact behavior depends on implementation, but we test it doesn't crash)
  delete prog;
  re->Decref();
}

// Test Compile with alternation
TEST(CompilerTest_289, CompileAlternation_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def|ghi", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test Compile with character classes
TEST(CompilerTest_289, CompileCharacterClass_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z0-9]+", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test Compile with repetition operators
TEST(CompilerTest_289, CompileRepetition_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*b+c?d{2,5}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test Compile with capture groups
TEST(CompilerTest_289, CompileCaptureGroups_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test Compile with empty regexp
TEST(CompilerTest_289, CompileEmptyRegexp_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test Compile with dot
TEST(CompilerTest_289, CompileDot_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test Compile with anchors
TEST(CompilerTest_289, CompileAnchors_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test Compile with Unicode
TEST(CompilerTest_289, CompileUnicode_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test CompileSet with unanchored
TEST(CompilerTest_289, CompileSetUnanchored_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test CompileSet with anchor start
TEST(CompilerTest_289, CompileSetAnchorStart_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test CompileSet with anchor both
TEST(CompilerTest_289, CompileSetAnchorBoth_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test that compiled program size is reasonable
TEST(CompilerTest_289, CompileProgramSize_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  EXPECT_GT(prog->size(), 0);
  
  delete prog;
  re->Decref();
}

// Test Compile with complex nested groups
TEST(CompilerTest_289, CompileComplexNested_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a|b)*c)+", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test Compile with case-insensitive flag
TEST(CompilerTest_289, CompileCaseInsensitive_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test Compile with word boundary
TEST(CompilerTest_289, CompileWordBoundary_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bfoo\\b", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test that larger max_mem allows compilation of complex regexps
TEST(CompilerTest_289, CompileLargeMaxMem_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]{1,100}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::Compile(re, false, 1 << 24);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Test Compile with non-greedy operators
TEST(CompilerTest_289, CompileNonGreedy_289) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*?b+?c??", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_TRUE(prog != nullptr);
  
  delete prog;
  re->Decref();
}

// Integration: verify compiled program can match correctly via RE2
TEST(CompilerTest_289, IntegrationSimpleMatch_289) {
  RE2 pattern("hello");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", pattern));
  EXPECT_FALSE(RE2::FullMatch("world", pattern));
}

// Integration: verify compiled program handles alternation matching
TEST(CompilerTest_289, IntegrationAlternationMatch_289) {
  RE2 pattern("cat|dog|bird");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::PartialMatch("I have a cat", pattern));
  EXPECT_TRUE(RE2::PartialMatch("I have a dog", pattern));
  EXPECT_TRUE(RE2::PartialMatch("I have a bird", pattern));
  EXPECT_FALSE(RE2::PartialMatch("I have a fish", pattern));
}

// Integration: verify compiled program handles quantifiers
TEST(CompilerTest_289, IntegrationQuantifiers_289) {
  RE2 pattern("a{2,4}");
  ASSERT_TRUE(pattern.ok());
  EXPECT_FALSE(RE2::FullMatch("a", pattern));
  EXPECT_TRUE(RE2::FullMatch("aa", pattern));
  EXPECT_TRUE(RE2::FullMatch("aaa", pattern));
  EXPECT_TRUE(RE2::FullMatch("aaaa", pattern));
  EXPECT_FALSE(RE2::FullMatch("aaaaa", pattern));
}

// Test Compile with nullptr (edge case)
TEST(CompilerTest_289, CompileNullRegexp_289) {
  // Passing nullptr should not crash; it may return nullptr
  Prog* prog = Compiler::Compile(nullptr, false, 1 << 20);
  // We just ensure no crash; result may vary
  delete prog;
}

}  // namespace re2
