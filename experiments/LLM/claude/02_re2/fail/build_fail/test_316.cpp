#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "util/utf.h"

// Since Compiler is internal to re2 and most methods are not directly accessible
// from outside, we test AddRuneRangeUTF8 indirectly through the public Compile
// interface, which exercises the code paths in AddRuneRangeUTF8.
// We verify correctness by compiling regexps that use various Unicode ranges
// and then matching against expected strings.

namespace re2 {

class CompilerAddRuneRangeUTF8Test_316 : public ::testing::Test {
 protected:
  // Helper to check if a pattern matches a given string
  bool Matches(const std::string& pattern, const std::string& text) {
    RE2 re(pattern);
    return RE2::FullMatch(text, re);
  }
};

// Test: lo > hi should effectively be a no-op (the range is empty)
// We test this indirectly: a character class that would produce lo > hi
// shouldn't match anything unexpected.
TEST_F(CompilerAddRuneRangeUTF8Test_316, EmptyRangeLoGreaterThanHi_316) {
  // [b-a] is an invalid range; RE2 should reject or handle it gracefully
  RE2 re("[b-a]");
  // RE2 should report this as an error
  EXPECT_FALSE(re.ok());
}

// Test: Single ASCII character (lo == hi, both < Runeself)
TEST_F(CompilerAddRuneRangeUTF8Test_316, SingleASCIICharacter_316) {
  EXPECT_TRUE(Matches("[a]", "a"));
  EXPECT_FALSE(Matches("[a]", "b"));
}

// Test: ASCII range (lo and hi both < 0x80)
TEST_F(CompilerAddRuneRangeUTF8Test_316, ASCIIRange_316) {
  EXPECT_TRUE(Matches("[a-z]", "a"));
  EXPECT_TRUE(Matches("[a-z]", "m"));
  EXPECT_TRUE(Matches("[a-z]", "z"));
  EXPECT_FALSE(Matches("[a-z]", "A"));
  EXPECT_FALSE(Matches("[a-z]", "0"));
}

// Test: 2-byte UTF-8 range (0x80 to 0x7FF)
TEST_F(CompilerAddRuneRangeUTF8Test_316, TwoByteUTF8Range_316) {
  // Latin Extended characters: U+00C0 to U+00FF
  EXPECT_TRUE(Matches("[À-ÿ]", "À"));  // U+00C0
  EXPECT_TRUE(Matches("[À-ÿ]", "ÿ"));  // U+00FF
  EXPECT_FALSE(Matches("[À-ÿ]", "a"));  // U+0061
}

// Test: 3-byte UTF-8 range (0x800 to 0xFFFF)
TEST_F(CompilerAddRuneRangeUTF8Test_316, ThreeByteUTF8Range_316) {
  // CJK Unified Ideographs: U+4E00 to U+9FFF
  EXPECT_TRUE(Matches("[一-鿿]", "中"));   // U+4E2D
  EXPECT_TRUE(Matches("[一-鿿]", "一"));   // U+4E00
  EXPECT_FALSE(Matches("[一-鿿]", "a"));
}

// Test: 4-byte UTF-8 range (0x10000 to 0x10FFFF)
TEST_F(CompilerAddRuneRangeUTF8Test_316, FourByteUTF8Range_316) {
  // Emoji range: U+1F600 to U+1F64F
  std::string emoji_pattern = "[\\x{1F600}-\\x{1F64F}]";
  RE2 re(emoji_pattern);
  ASSERT_TRUE(re.ok());
  // U+1F600 = 😀
  EXPECT_TRUE(RE2::FullMatch("😀", re));
  // U+1F64F = 🙏
  EXPECT_TRUE(RE2::FullMatch("🙏", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
}

// Test: Range spanning from 2-byte to 3-byte UTF-8 boundary
TEST_F(CompilerAddRuneRangeUTF8Test_316, CrossTwoToThreeByteUTF8Boundary_316) {
  // U+0080 to U+0800 spans 2-byte to 3-byte boundary
  std::string pattern = "[\\x{80}-\\x{800}]";
  RE2 re(pattern);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("\xc2\x80", re));       // U+0080
  EXPECT_TRUE(RE2::FullMatch("\xe0\xa0\x80", re));    // U+0800
  EXPECT_FALSE(RE2::FullMatch("a", re));              // U+0061
}

// Test: Range spanning from 3-byte to 4-byte UTF-8 boundary
TEST_F(CompilerAddRuneRangeUTF8Test_316, CrossThreeToFourByteUTF8Boundary_316) {
  // U+FFFF to U+10000 spans 3-byte to 4-byte boundary
  std::string pattern = "[\\x{FFFF}-\\x{10000}]";
  RE2 re(pattern);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("\xef\xbf\xbf", re));          // U+FFFF
  EXPECT_TRUE(RE2::FullMatch("\xf0\x90\x80\x80", re));      // U+10000
}

// Test: Full Unicode range (dot matches everything)
TEST_F(CompilerAddRuneRangeUTF8Test_316, FullUnicodeRange_316) {
  // "." in RE2 matches any character except newline by default
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re(".", opts);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("中", re));
  EXPECT_TRUE(RE2::FullMatch("😀", re));
}

// Test: Special case lo=0x80, hi=0x10FFFF triggers Add_80_10ffff
TEST_F(CompilerAddRuneRangeUTF8Test_316, SpecialCase80To10FFFF_316) {
  // [^\x00-\x7f] matches any non-ASCII Unicode character
  std::string pattern = "[\\x{80}-\\x{10FFFF}]";
  RE2 re(pattern);
  ASSERT_TRUE(re.ok());
  EXPECT_FALSE(RE2::FullMatch("a", re));         // ASCII
  EXPECT_TRUE(RE2::FullMatch("中", re));          // 3-byte
  EXPECT_TRUE(RE2::FullMatch("😀", re));          // 4-byte
  EXPECT_TRUE(RE2::FullMatch("\xc2\x80", re));   // U+0080
}

// Test: Single code point at boundary (U+007F, last ASCII)
TEST_F(CompilerAddRuneRangeUTF8Test_316, BoundaryLastASCII_316) {
  std::string pattern = "[\\x{7F}]";
  RE2 re(pattern);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("\x7f", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
}

// Test: Single code point at boundary (U+0080, first 2-byte)
TEST_F(CompilerAddRuneRangeUTF8Test_316, BoundaryFirst2Byte_316) {
  std::string pattern = "[\\x{80}]";
  RE2 re(pattern);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("\xc2\x80", re));    // U+0080
  EXPECT_FALSE(RE2::FullMatch("a", re));
}

// Test: lo == hi for multi-byte character
TEST_F(CompilerAddRuneRangeUTF8Test_316, SingleMultiByteCharacter_316) {
  // U+4E2D = 中
  std::string pattern = "[\\x{4E2D}]";
  RE2 re(pattern);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("中", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
  EXPECT_FALSE(RE2::FullMatch("一", re));
}

// Test: Case folding with ASCII range
TEST_F(CompilerAddRuneRangeUTF8Test_316, CaseFoldingASCII_316) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("[a-z]", opts);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("A", re));
  EXPECT_TRUE(RE2::FullMatch("Z", re));
}

// Test: Case folding with Unicode range
TEST_F(CompilerAddRuneRangeUTF8Test_316, CaseFoldingUnicode_316) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("[à-ö]", opts);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("à", re));  // U+00E0
  EXPECT_TRUE(RE2::FullMatch("À", re));  // U+00C0 (uppercase equivalent)
}

// Test: Reversed compilation (used for reverse matching)
TEST_F(CompilerAddRuneRangeUTF8Test_316, ReversedCompilation_316) {
  // RE2 uses reversed compilation internally for some operations.
  // We test indirectly through RE2's matching which may use reversed progs.
  RE2 re("中");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello中world", re));
  EXPECT_FALSE(RE2::PartialMatch("helloworld", re));
}

// Test: Range at max Unicode codepoint
TEST_F(CompilerAddRuneRangeUTF8Test_316, MaxUnicodeCodepoint_316) {
  std::string pattern = "[\\x{10FFFF}]";
  RE2 re(pattern);
  ASSERT_TRUE(re.ok());
  // U+10FFFF in UTF-8: F4 8F BF BF
  EXPECT_TRUE(RE2::FullMatch("\xf4\x8f\xbf\xbf", re));
  EXPECT_FALSE(RE2::FullMatch("a", re));
}

// Test: Wide range spanning all UTF-8 byte lengths
TEST_F(CompilerAddRuneRangeUTF8Test_316, WideRangeAllByteLengths_316) {
  // U+0041 (1-byte 'A') to U+10FFFF (4-byte max)
  std::string pattern = "[\\x{41}-\\x{10FFFF}]";
  RE2 re(pattern);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("A", re));             // 1-byte
  EXPECT_TRUE(RE2::FullMatch("\xc2\x80", re));      // 2-byte U+0080
  EXPECT_TRUE(RE2::FullMatch("中", re));              // 3-byte
  EXPECT_TRUE(RE2::FullMatch("😀", re));              // 4-byte
  EXPECT_FALSE(RE2::FullMatch("@", re));             // U+0040, below range
}

// Test: Compile and match with character class negation
TEST_F(CompilerAddRuneRangeUTF8Test_316, NegatedCharacterClass_316) {
  // [^a-z] should match non-lowercase-ASCII characters
  EXPECT_FALSE(Matches("[^a-z]", "a"));
  EXPECT_FALSE(Matches("[^a-z]", "z"));
  EXPECT_TRUE(Matches("[^a-z]", "A"));
  EXPECT_TRUE(Matches("[^a-z]", "0"));
  EXPECT_TRUE(Matches("[^a-z]", "中"));
}

// Test: Compile with a complex pattern using multiple Unicode ranges
TEST_F(CompilerAddRuneRangeUTF8Test_316, ComplexMultipleUnicodeRanges_316) {
  // Match either ASCII letters or CJK characters
  std::string pattern = "[a-zA-Z\\x{4E00}-\\x{9FFF}]";
  RE2 re(pattern);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
  EXPECT_TRUE(RE2::FullMatch("Z", re));
  EXPECT_TRUE(RE2::FullMatch("中", re));
  EXPECT_FALSE(RE2::FullMatch("0", re));
  EXPECT_FALSE(RE2::FullMatch("😀", re));
}

// Test: Compile with set (CompileSet path)
TEST_F(CompilerAddRuneRangeUTF8Test_316, CompileSetMultiplePatterns_316) {
  RE2::Set s(RE2::DefaultOptions, RE2::UNANCHORED);
  ASSERT_EQ(s.Add("hello", nullptr), 0);
  ASSERT_EQ(s.Add("中文", nullptr), 1);
  ASSERT_TRUE(s.Compile());
  
  std::vector<int> matches;
  EXPECT_TRUE(s.Match("hello world", &matches));
  ASSERT_FALSE(matches.empty());
  EXPECT_EQ(matches[0], 0);
  
  matches.clear();
  EXPECT_TRUE(s.Match("中文测试", &matches));
  ASSERT_FALSE(matches.empty());
  EXPECT_EQ(matches[0], 1);
}

// Test: Range within 2-byte space that requires splitting
TEST_F(CompilerAddRuneRangeUTF8Test_316, TwoByteRangeSplitting_316) {
  // U+0100 to U+017F (Latin Extended-A)
  std::string pattern = "[\\x{100}-\\x{17F}]";
  RE2 re(pattern);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("\xc4\x80", re));    // U+0100
  EXPECT_TRUE(RE2::FullMatch("\xc5\xbf", re));    // U+017F
  EXPECT_FALSE(RE2::FullMatch("\xc3\xbf", re));   // U+00FF (below range)
  EXPECT_FALSE(RE2::FullMatch("\xc6\x80", re));   // U+0180 (above range)
}

// Test: Boundary at MaxRune(1) = 0x7F
TEST_F(CompilerAddRuneRangeUTF8Test_316, BoundaryAtMaxRune1_316) {
  // Range that spans exactly from ASCII to 2-byte boundary
  std::string pattern = "[\\x{7E}-\\x{80}]";
  RE2 re(pattern);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("~", re));           // U+007E
  EXPECT_TRUE(RE2::FullMatch("\x7f", re));         // U+007F
  EXPECT_TRUE(RE2::FullMatch("\xc2\x80", re));    // U+0080
  EXPECT_FALSE(RE2::FullMatch("a", re));
}

// Test: Boundary at MaxRune(2) = 0x7FF
TEST_F(CompilerAddRuneRangeUTF8Test_316, BoundaryAtMaxRune2_316) {
  // Range that spans 2-byte to 3-byte boundary
  std::string pattern = "[\\x{7FE}-\\x{801}]";
  RE2 re(pattern);
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("\xdf\xbe", re));          // U+07FE
  EXPECT_TRUE(RE2::FullMatch("\xdf\xbf", re));          // U+07FF
  EXPECT_TRUE(RE2::FullMatch("\xe0\xa0\x80", re));       // U+0800
  EXPECT_TRUE(RE2::FullMatch("\xe0\xa0\x81", re));       // U+0801
}

}  // namespace re2
