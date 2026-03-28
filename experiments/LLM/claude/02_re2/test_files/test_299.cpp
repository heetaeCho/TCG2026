#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"

namespace re2 {

// We test the Compiler primarily through its public static methods
// Compile and CompileSet, and through the RE2 interface which uses them.

class CompilerMatchTest_299 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that Compile produces a valid Prog for a simple literal regex
TEST_F(CompilerMatchTest_299, CompileSimpleLiteral_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile with reversed flag produces a valid Prog
TEST_F(CompilerMatchTest_299, CompileReversed_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that Compile returns nullptr for extremely small max_mem
TEST_F(CompilerMatchTest_299, CompileExtremelySmallMaxMem_299) {
  RegexpStatus status;
  // A complex regex that would need more memory
  Regexp* re = Regexp::Parse("(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p){10}", 
                              Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Very tiny max_mem - may return nullptr if can't fit
  Prog* prog = Compiler::Compile(re, false, 1);
  // It's possible it returns nullptr due to memory constraints
  // or a minimal prog. Just check it doesn't crash.
  delete prog;
  re->Decref();
}

// Test Compile with an alternation pattern
TEST_F(CompilerMatchTest_299, CompileAlternation_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("foo|bar|baz", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with character class
TEST_F(CompilerMatchTest_299, CompileCharacterClass_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z0-9]+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with repetition operators (Plus, Star, Quest)
TEST_F(CompilerMatchTest_299, CompileRepetitions_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b*c?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with capture groups
TEST_F(CompilerMatchTest_299, CompileCaptureGroups_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with empty width assertions
TEST_F(CompilerMatchTest_299, CompileEmptyWidth_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with nongreedy operators
TEST_F(CompilerMatchTest_299, CompileNonGreedy_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+?b*?c??", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with dot star pattern
TEST_F(CompilerMatchTest_299, CompileDotStar_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with UNANCHORED
TEST_F(CompilerMatchTest_299, CompileSetUnanchored_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("foo|bar", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_START
TEST_F(CompilerMatchTest_299, CompileSetAnchorStart_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("foo|bar", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with ANCHOR_BOTH
TEST_F(CompilerMatchTest_299, CompileSetAnchorBoth_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("foo|bar", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that a compiled program can actually match correctly
TEST_F(CompilerMatchTest_299, CompiledProgramMatchesCorrectly_299) {
  RE2 pattern("hello");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", pattern));
  EXPECT_FALSE(RE2::FullMatch("world", pattern));
}

// Test compiled program with alternation matching
TEST_F(CompilerMatchTest_299, CompiledAlternationMatches_299) {
  RE2 pattern("foo|bar|baz");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("foo", pattern));
  EXPECT_TRUE(RE2::FullMatch("bar", pattern));
  EXPECT_TRUE(RE2::FullMatch("baz", pattern));
  EXPECT_FALSE(RE2::FullMatch("qux", pattern));
}

// Test compiled program with repetition matching
TEST_F(CompilerMatchTest_299, CompiledRepetitionMatches_299) {
  RE2 pattern("a+b*c?");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("a", pattern));
  EXPECT_TRUE(RE2::FullMatch("aaa", pattern));
  EXPECT_TRUE(RE2::FullMatch("ab", pattern));
  EXPECT_TRUE(RE2::FullMatch("abc", pattern));
  EXPECT_TRUE(RE2::FullMatch("aabbc", pattern));
  EXPECT_FALSE(RE2::FullMatch("bc", pattern));
}

// Test compiled empty regex
TEST_F(CompilerMatchTest_299, CompileEmptyRegex_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiled program with Unicode patterns
TEST_F(CompilerMatchTest_299, CompileUnicode_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiled program with case folding
TEST_F(CompilerMatchTest_299, CompileCaseFolding_299) {
  RE2 pattern("(?i)hello");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", pattern));
  EXPECT_TRUE(RE2::FullMatch("HELLO", pattern));
  EXPECT_TRUE(RE2::FullMatch("Hello", pattern));
}

// Test that Compile handles complex nested regex
TEST_F(CompilerMatchTest_299, CompileComplexNested_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a|b)*c(d|e)+)?f", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Prog::Inst::InitMatch sets the match id correctly
TEST_F(CompilerMatchTest_299, ProgInstInitMatch_299) {
  Prog::Inst inst;
  inst.InitMatch(42);
  EXPECT_EQ(inst.match_id(), 42);
}

// Test Prog::Inst::InitMatch with zero match id
TEST_F(CompilerMatchTest_299, ProgInstInitMatchZero_299) {
  Prog::Inst inst;
  inst.InitMatch(0);
  EXPECT_EQ(inst.match_id(), 0);
}

// Test Prog::Inst::InitMatch with various match ids
TEST_F(CompilerMatchTest_299, ProgInstInitMatchVarious_299) {
  Prog::Inst inst;
  inst.InitMatch(1);
  EXPECT_EQ(inst.match_id(), 1);
  
  inst.InitMatch(100);
  EXPECT_EQ(inst.match_id(), 100);
  
  inst.InitMatch(999);
  EXPECT_EQ(inst.match_id(), 999);
}

// Test Prog::Inst opcode after InitMatch
TEST_F(CompilerMatchTest_299, ProgInstInitMatchOpcode_299) {
  Prog::Inst inst;
  inst.InitMatch(1);
  EXPECT_EQ(inst.opcode(), kInstMatch);
}

// Test that compiled regex with bounded repetition works
TEST_F(CompilerMatchTest_299, CompileBoundedRepetition_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Compile with moderate max_mem
TEST_F(CompilerMatchTest_299, CompileModerateMaxMem_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1024);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that the number of instructions in a compiled program is reasonable
TEST_F(CompilerMatchTest_299, CompileProgramSize_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  // A simple single-char regex should have a small number of instructions
  EXPECT_GT(prog->size(), 0);
  delete prog;
  re->Decref();
}

// Test Compile with word boundary
TEST_F(CompilerMatchTest_299, CompileWordBoundary_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bword\\b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test multiple match via RE2::Set-like pattern through CompileSet
TEST_F(CompilerMatchTest_299, CompileSetMultiplePatterns_299) {
  // Use RE2::Set to test CompileSet indirectly
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  EXPECT_GE(s.Add("foo", nullptr), 0);
  EXPECT_GE(s.Add("bar", nullptr), 0);
  EXPECT_GE(s.Add("baz", nullptr), 0);
  EXPECT_TRUE(s.Compile());

  std::vector<int> matches;
  EXPECT_TRUE(s.Match("foo", &matches));
  EXPECT_FALSE(matches.empty());
}

// Test CompileSet with very small max_mem
TEST_F(CompilerMatchTest_299, CompileSetSmallMaxMem_299) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p",
                              Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Very small max_mem - could fail
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1);
  // May return nullptr - just check no crash
  delete prog;
  re->Decref();
}

// Test Prog::Inst other initializations for completeness
TEST_F(CompilerMatchTest_299, ProgInstInitNop_299) {
  Prog::Inst inst;
  inst.InitNop(0);
  EXPECT_EQ(inst.opcode(), kInstNop);
}

TEST_F(CompilerMatchTest_299, ProgInstInitFail_299) {
  Prog::Inst inst;
  inst.InitFail();
  EXPECT_EQ(inst.opcode(), kInstFail);
}

TEST_F(CompilerMatchTest_299, ProgInstInitByteRange_299) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', 0, 0);
  EXPECT_EQ(inst.opcode(), kInstByteRange);
  EXPECT_EQ(inst.lo(), 'a');
  EXPECT_EQ(inst.hi(), 'z');
}

}  // namespace re2
