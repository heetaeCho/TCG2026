#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

// Since Compiler is not directly accessible through the public API in a straightforward way,
// we test its behavior through the public static methods Compile and CompileSet,
// as well as through the RE2 interface which uses Compiler internally.

// Test basic compilation through RE2 interface
TEST(CompilerTest_324, BasicCompile_324) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_324, CompileEmptyPattern_324) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_324, CompileSingleChar_324) {
  RE2 re("a");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::FullMatch("b", re));
}

TEST(CompilerTest_324, CompileCharClass_324) {
  RE2 re("[a-z]");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("m", re));
  EXPECT_FALSE(RE2::FullMatch("M", re));
}

TEST(CompilerTest_324, CompileDot_324) {
  RE2 re(".");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("x", re));
  EXPECT_FALSE(RE2::FullMatch("", re));
}

TEST(CompilerTest_324, CompileAlternation_324) {
  RE2 re("cat|dog");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("cat", re));
  EXPECT_TRUE(RE2::FullMatch("dog", re));
  EXPECT_FALSE(RE2::FullMatch("bird", re));
}

TEST(CompilerTest_324, CompileRepetitionStar_324) {
  RE2 re("a*");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_FALSE(RE2::FullMatch("b", re));
}

TEST(CompilerTest_324, CompileRepetitionPlus_324) {
  RE2 re("a+");
  EXPECT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
}

TEST(CompilerTest_324, CompileRepetitionQuest_324) {
  RE2 re("a?");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::FullMatch("aa", re));
}

TEST(CompilerTest_324, CompileCapture_324) {
  RE2 re("(hello)");
  EXPECT_TRUE(re.ok());
  std::string captured;
  EXPECT_TRUE(RE2::FullMatch("hello", re, &captured));
  EXPECT_EQ(captured, "hello");
}

TEST(CompilerTest_324, CompileNestedCapture_324) {
  RE2 re("((a)(b))");
  EXPECT_TRUE(re.ok());
  std::string s1, s2, s3;
  EXPECT_TRUE(RE2::FullMatch("ab", re, &s1, &s2, &s3));
  EXPECT_EQ(s1, "ab");
  EXPECT_EQ(s2, "a");
  EXPECT_EQ(s3, "b");
}

TEST(CompilerTest_324, CompileLatin1_324) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re("\\xc0", opts);
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_324, CompileUTF8_324) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingUTF8);
  RE2 re("\\x{100}", opts);
  EXPECT_TRUE(re.ok());
}

// Test max_mem boundary conditions through RE2 options
TEST(CompilerTest_324, MaxMemZero_324) {
  RE2::Options opts;
  opts.set_max_mem(0);
  // With max_mem=0, the compiler should still work (uses default 100000 max_ninst)
  RE2 re("a", opts);
  // The pattern is simple enough it should compile
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_324, MaxMemNegative_324) {
  RE2::Options opts;
  opts.set_max_mem(-1);
  // With negative max_mem, the compiler uses default 100000 max_ninst
  RE2 re("a", opts);
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_324, MaxMemVerySmall_324) {
  RE2::Options opts;
  // Set max_mem to sizeof(Prog) or less - should set max_ninst_ to 0
  opts.set_max_mem(1);
  RE2 re("a", opts);
  // With max_ninst_=0, compilation should fail for most patterns
  EXPECT_FALSE(re.ok());
}

TEST(CompilerTest_324, MaxMemSmall_324) {
  RE2::Options opts;
  opts.set_max_mem(256);
  RE2 re("a", opts);
  // Simple pattern may or may not compile with very small memory
  // We just verify no crash
}

TEST(CompilerTest_324, MaxMemLarge_324) {
  RE2::Options opts;
  opts.set_max_mem(1 << 25);  // 32MB
  RE2 re("hello world", opts);
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_324, MaxMemVeryLarge_324) {
  RE2::Options opts;
  opts.set_max_mem(static_cast<int64_t>(1) << 30);  // 1GB
  RE2 re("(a+)(b+)(c+)", opts);
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_324, CompileComplexPattern_324) {
  RE2 re("^([a-zA-Z0-9_.+-]+)@([a-zA-Z0-9-]+)\\.([a-zA-Z0-9-.]+)$");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("user@example.com", re));
  EXPECT_FALSE(RE2::FullMatch("not-an-email", re));
}

TEST(CompilerTest_324, CompileEmptyWidth_324) {
  RE2 re("^hello$");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("hello\n", re));
}

TEST(CompilerTest_324, CompileWordBoundary_324) {
  RE2 re("\\bhello\\b");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("say hello world", re));
  EXPECT_FALSE(RE2::PartialMatch("sayhelloworld", re));
}

TEST(CompilerTest_324, CompileNonGreedy_324) {
  RE2 re("a+?");
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_324, CompileFoldCase_324) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("hello", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HeLlO", re));
}

TEST(CompilerTest_324, CompileDotNL_324) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST(CompilerTest_324, CompileNeverCapture_324) {
  RE2::Options opts;
  opts.set_never_capture(true);
  RE2 re("(hello)", opts);
  EXPECT_TRUE(re.ok());
  // With NeverCapture, the group count should be 0
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(CompilerTest_324, CompileReversed_324) {
  // Test through RE2 which internally uses reversed compilation for some operations
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  // PartialMatch exercises both forward and reverse programs
  EXPECT_TRUE(RE2::PartialMatch("say hello world", re));
}

// Test that compilation produces working programs for various anchoring modes
TEST(CompilerTest_324, AnchorUnanchored_324) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("say hello world", re));
}

TEST(CompilerTest_324, AnchorFullMatch_324) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("say hello world", re));
}

// Test that very complex patterns with many instructions compile within limits
TEST(CompilerTest_324, CompileManyAlternations_324) {
  std::string pattern;
  for (int i = 0; i < 100; i++) {
    if (i > 0) pattern += "|";
    pattern += "word" + std::to_string(i);
  }
  RE2 re(pattern);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("word50", re));
  EXPECT_FALSE(RE2::FullMatch("word100", re));
}

TEST(CompilerTest_324, CompileDeepNesting_324) {
  std::string pattern = "a";
  for (int i = 0; i < 50; i++) {
    pattern = "(" + pattern + ")";
  }
  RE2 re(pattern);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
}

TEST(CompilerTest_324, CompileUnicodeRange_324) {
  RE2 re("[\\x{0100}-\\x{01FF}]");
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_324, CompileLiteralMode_324) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  // In literal mode, "." is treated as a literal dot
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("axb", re));
}

// Test CompileSet via RE2::Set
TEST(CompilerTest_324, CompileSet_324) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  EXPECT_GE(s.Add("hello", nullptr), 0);
  EXPECT_GE(s.Add("world", nullptr), 0);
  EXPECT_TRUE(s.Compile());
}

TEST(CompilerTest_324, CompileSetAnchored_324) {
  RE2::Set s(RE2::DefaultOptions, RE2::ANCHOR_BOTH);
  EXPECT_GE(s.Add("hello", nullptr), 0);
  EXPECT_GE(s.Add("world", nullptr), 0);
  EXPECT_TRUE(s.Compile());
  
  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello", &matches));
  EXPECT_EQ(matches.size(), 1);
  EXPECT_EQ(matches[0], 0);
}

TEST(CompilerTest_324, CompileSetAnchorStart_324) {
  RE2::Set s(RE2::DefaultOptions, RE2::ANCHOR_START);
  EXPECT_GE(s.Add("hello", nullptr), 0);
  EXPECT_TRUE(s.Compile());
  
  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello world", &matches));
  EXPECT_FALSE(s.Match("say hello", &matches));
}

TEST(CompilerTest_324, CompileSetEmpty_324) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  // Compiling an empty set
  EXPECT_FALSE(s.Compile());
}

// Edge case: pattern that exercises the ByteRange instruction
TEST(CompilerTest_324, CompileByteRange_324) {
  RE2 re("[\\x00-\\xff]");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("\x00", re));
}

// Test pattern with repetition count
TEST(CompilerTest_324, CompileRepetitionCount_324) {
  RE2 re("a{3,5}");
  EXPECT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("aa", re));
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaaa", re));
  EXPECT_FALSE(RE2::FullMatch("aaaaaa", re));
}

// Test pattern with concatenation
TEST(CompilerTest_324, CompileConcatenation_324) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_FALSE(RE2::FullMatch("ab", re));
  EXPECT_FALSE(RE2::FullMatch("abcd", re));
}

// Test memory limits that are exactly sizeof(Prog)
TEST(CompilerTest_324, MaxMemEqualSizeofProg_324) {
  RE2::Options opts;
  // We don't know exact sizeof(Prog) but we can try a small value
  // that's likely close to or equal to sizeof(Prog)
  opts.set_max_mem(64);
  RE2 re("a+b+c+", opts);
  // With very small memory, compilation likely fails
  // But we just ensure no crash
}

// Test OneLine flag
TEST(CompilerTest_324, CompileOneLine_324) {
  RE2::Options opts;
  opts.set_one_line(true);
  RE2 re("^hello$", opts);
  EXPECT_TRUE(re.ok());
}

// Test Perl-like features
TEST(CompilerTest_324, CompilePerlFeatures_324) {
  RE2 re("\\d+\\.\\d+");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("3.14", re));
  EXPECT_FALSE(RE2::FullMatch("abc", re));
}

TEST(CompilerTest_324, CompileWordChar_324) {
  RE2 re("\\w+");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello123", re));
}

}  // namespace re2
