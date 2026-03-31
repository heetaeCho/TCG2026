#include <cstdint>
#include <memory>
#include <string>

#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"

namespace re2 {

class FindByteRangeTest_311 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that compiling a simple literal pattern succeeds
TEST_F(FindByteRangeTest_311, CompileSimpleLiteral_311) {
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a character class (exercises FindByteRange with byte ranges)
TEST_F(FindByteRangeTest_311, CompileCharacterClass_311) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a character class with multiple ranges
TEST_F(FindByteRangeTest_311, CompileMultipleRanges_311) {
  Regexp* re = Regexp::Parse("[a-zA-Z0-9]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with reversed flag (exercises reversed_ path in FindByteRange)
TEST_F(FindByteRangeTest_311, CompileReversed_311) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling Unicode range (exercises UTF8 byte range paths)
TEST_F(FindByteRangeTest_311, CompileUnicodeRange_311) {
  Regexp* re = Regexp::Parse("[\\x{100}-\\x{1FF}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling wide Unicode range (exercises Add_80_10ffff and complex byte ranges)
TEST_F(FindByteRangeTest_311, CompileWideUnicodeRange_311) {
  Regexp* re = Regexp::Parse("[\\x{80}-\\x{10FFFF}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling reversed Unicode range
TEST_F(FindByteRangeTest_311, CompileReversedUnicodeRange_311) {
  Regexp* re = Regexp::Parse("[\\x{100}-\\x{1FF}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling a dot pattern (exercises DotStar/byte range)
TEST_F(FindByteRangeTest_311, CompileDot_311) {
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling with foldcase (case-insensitive byte ranges)
TEST_F(FindByteRangeTest_311, CompileFoldCase_311) {
  Regexp* re = Regexp::Parse("(?i)[a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling an alternation of character classes
TEST_F(FindByteRangeTest_311, CompileAlternationOfClasses_311) {
  Regexp* re = Regexp::Parse("[a-f]|[g-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling empty pattern
TEST_F(FindByteRangeTest_311, CompileEmptyPattern_311) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with unanchored anchor
TEST_F(FindByteRangeTest_311, CompileSetUnanchored_311) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with anchored start
TEST_F(FindByteRangeTest_311, CompileSetAnchorStart_311) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_START, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileSet with anchored both ends
TEST_F(FindByteRangeTest_311, CompileSetAnchorBoth_311) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::CompileSet(re, RE2::ANCHOR_BOTH, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that very small memory limit may cause compilation to return null or limited prog
TEST_F(FindByteRangeTest_311, CompileSmallMemoryLimit_311) {
  Regexp* re = Regexp::Parse("[\\x{80}-\\x{10FFFF}]+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  // Very small memory limit - may fail
  Prog* prog = Compiler::Compile(re, false, 1);
  // prog may be nullptr if memory is insufficient
  delete prog;
  re->Decref();
}

// Test compiling overlapping byte ranges (exercises suffix sharing in FindByteRange)
TEST_F(FindByteRangeTest_311, CompileOverlappingRanges_311) {
  Regexp* re = Regexp::Parse("[\\x{100}-\\x{200}\\x{180}-\\x{280}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling single byte character class
TEST_F(FindByteRangeTest_311, CompileSingleByteClass_311) {
  Regexp* re = Regexp::Parse("[a]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test Latin1 range compilation
TEST_F(FindByteRangeTest_311, CompileLatin1Range_311) {
  Regexp* re = Regexp::Parse("[\\x{00}-\\x{FF}]", Regexp::Latin1 | Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling reversed with multi-byte Unicode (exercises reversed_ branch in FindByteRange)
TEST_F(FindByteRangeTest_311, CompileReversedMultiByte_311) {
  Regexp* re = Regexp::Parse("[\\x{1000}-\\x{2000}]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, true, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that compiled prog can match expected strings (functional correctness)
TEST_F(FindByteRangeTest_311, CompiledProgMatchesFunctional_311) {
  RE2 pattern("[a-f]+");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", pattern));
  EXPECT_TRUE(RE2::FullMatch("def", pattern));
  EXPECT_FALSE(RE2::FullMatch("xyz", pattern));
  EXPECT_FALSE(RE2::FullMatch("", pattern));
}

// Test that compiled prog with Unicode range matches correctly
TEST_F(FindByteRangeTest_311, CompiledUnicodeMatchFunctional_311) {
  RE2 pattern("[\\x{100}-\\x{1FF}]+");
  ASSERT_TRUE(pattern.ok());
  EXPECT_TRUE(RE2::FullMatch("\xc4\x80", pattern));  // U+0100
  EXPECT_FALSE(RE2::FullMatch("a", pattern));
}

// Test complex pattern combining byte ranges
TEST_F(FindByteRangeTest_311, CompileComplexByteRangePattern_311) {
  Regexp* re = Regexp::Parse("[a-z][A-Z][0-9]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test that repeated character classes compile correctly
TEST_F(FindByteRangeTest_311, CompileRepeatedCharClass_311) {
  Regexp* re = Regexp::Parse("[a-z]+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test compiling negated character class
TEST_F(FindByteRangeTest_311, CompileNegatedCharClass_311) {
  Regexp* re = Regexp::Parse("[^a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = Compiler::Compile(re, false, 1 << 20);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

}  // namespace re2
