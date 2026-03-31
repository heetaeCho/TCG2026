#include <gtest/gtest.h>

// We need to access the static function MaxRune which is in the re2 namespace
// Since it's a static function in a .cc file, we need to include it or
// declare it. For testing purposes, we'll re-declare access to it.
// However, since the function is static (file-local linkage), we need
// a workaround. We'll include the source file directly for testing.

// Include necessary headers from re2
#include "re2/re2.h"
#include "util/utf.h"

// Since MaxRune is a static function within compile.cc, it has internal linkage.
// To test it, we need to either:
// 1. Include the .cc file (not ideal but necessary for static functions)
// 2. Or test it indirectly through the public interface that uses it.
//
// We'll test it indirectly through RE2's compilation behavior, which uses MaxRune
// internally when compiling regular expressions with UTF-8 character classes.

namespace {

// Test that RE2 can compile and match patterns involving various UTF-8 ranges,
// which internally exercise MaxRune for different byte lengths.

class MaxRuneIndirectTest_302 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test single-byte UTF-8 range (ASCII, len=1, MaxRune should be 127)
TEST_F(MaxRuneIndirectTest_302, SingleByteUTF8Range_302) {
    // ASCII characters are single-byte UTF-8 (0x00-0x7F)
    RE2 pattern("[a-z]");
    ASSERT_TRUE(pattern.ok()) << pattern.error();
    
    EXPECT_TRUE(RE2::FullMatch("a", pattern));
    EXPECT_TRUE(RE2::FullMatch("z", pattern));
    EXPECT_FALSE(RE2::FullMatch("A", pattern));
    EXPECT_FALSE(RE2::FullMatch("1", pattern));
}

// Test two-byte UTF-8 range (len=2, MaxRune should be 0x7FF)
TEST_F(MaxRuneIndirectTest_302, TwoByteUTF8Range_302) {
    // Characters in U+0080 to U+07FF range are two-byte UTF-8
    // Latin Extended characters like ñ (U+00F1) or ö (U+00F6)
    RE2 pattern("ñ");
    ASSERT_TRUE(pattern.ok()) << pattern.error();
    
    EXPECT_TRUE(RE2::FullMatch("ñ", pattern));
    EXPECT_FALSE(RE2::FullMatch("n", pattern));
}

// Test three-byte UTF-8 range (len=3, MaxRune should be 0xFFFF)
TEST_F(MaxRuneIndirectTest_302, ThreeByteUTF8Range_302) {
    // Characters in U+0800 to U+FFFF range are three-byte UTF-8
    // Chinese character 中 (U+4E2D)
    RE2 pattern("中");
    ASSERT_TRUE(pattern.ok()) << pattern.error();
    
    EXPECT_TRUE(RE2::FullMatch("中", pattern));
    EXPECT_FALSE(RE2::FullMatch("a", pattern));
}

// Test four-byte UTF-8 range (len=4)
TEST_F(MaxRuneIndirectTest_302, FourByteUTF8Range_302) {
    // Characters in U+10000 to U+10FFFF range are four-byte UTF-8
    // Emoji: 😀 (U+1F600)
    RE2 pattern("😀");
    ASSERT_TRUE(pattern.ok()) << pattern.error();
    
    EXPECT_TRUE(RE2::FullMatch("😀", pattern));
    EXPECT_FALSE(RE2::FullMatch("a", pattern));
}

// Test character class spanning multiple UTF-8 byte lengths
TEST_F(MaxRuneIndirectTest_302, CrossByteRangeCharClass_302) {
    // A character class that spans ASCII and multi-byte UTF-8
    RE2 pattern("[a-zà-ÿ]");
    ASSERT_TRUE(pattern.ok()) << pattern.error();
    
    EXPECT_TRUE(RE2::FullMatch("a", pattern));
    EXPECT_TRUE(RE2::FullMatch("z", pattern));
    EXPECT_TRUE(RE2::FullMatch("à", pattern));
    EXPECT_TRUE(RE2::FullMatch("ÿ", pattern));
    EXPECT_FALSE(RE2::FullMatch("1", pattern));
}

// Test dot matching across UTF-8 ranges
TEST_F(MaxRuneIndirectTest_302, DotMatchesMultiByteUTF8_302) {
    RE2 pattern(".");
    ASSERT_TRUE(pattern.ok()) << pattern.error();
    
    EXPECT_TRUE(RE2::FullMatch("a", pattern));    // 1-byte
    EXPECT_TRUE(RE2::FullMatch("ñ", pattern));    // 2-byte
    EXPECT_TRUE(RE2::FullMatch("中", pattern));   // 3-byte
    EXPECT_TRUE(RE2::FullMatch("😀", pattern));   // 4-byte
}

// Test Unicode property classes which exercise MaxRune boundaries
TEST_F(MaxRuneIndirectTest_302, UnicodePropertyClass_302) {
    RE2 pattern("\\pL");  // Unicode Letter property
    ASSERT_TRUE(pattern.ok()) << pattern.error();
    
    EXPECT_TRUE(RE2::FullMatch("a", pattern));
    EXPECT_TRUE(RE2::FullMatch("ñ", pattern));
    EXPECT_TRUE(RE2::FullMatch("中", pattern));
    EXPECT_FALSE(RE2::FullMatch("1", pattern));
}

// Test compilation of patterns with explicit Unicode ranges at boundaries
TEST_F(MaxRuneIndirectTest_302, BoundaryRuneValues_302) {
    // Test at the boundary of 1-byte (0x7F) and 2-byte (0x80) UTF-8
    RE2 pattern("[\\x{7E}-\\x{80}]");
    ASSERT_TRUE(pattern.ok()) << pattern.error();
    
    EXPECT_TRUE(RE2::FullMatch("~", pattern));  // U+007E
    EXPECT_TRUE(RE2::FullMatch("\x7f", pattern));  // U+007F (DEL)
    EXPECT_TRUE(RE2::FullMatch("\xc2\x80", pattern));  // U+0080
    EXPECT_FALSE(RE2::FullMatch("a", pattern));
}

// Test boundary between 2-byte and 3-byte UTF-8 (U+07FF and U+0800)
TEST_F(MaxRuneIndirectTest_302, TwoToThreeByteBoundary_302) {
    RE2 pattern("[\\x{7FE}-\\x{801}]");
    ASSERT_TRUE(pattern.ok()) << pattern.error();
    
    // U+07FE, U+07FF (2-byte max), U+0800 (3-byte min), U+0801
    // These should all match
    std::string u07fe = "\xdf\xbe";
    std::string u07ff = "\xdf\xbf";
    std::string u0800 = "\xe0\xa0\x80";
    std::string u0801 = "\xe0\xa0\x81";
    
    EXPECT_TRUE(RE2::FullMatch(u07fe, pattern));
    EXPECT_TRUE(RE2::FullMatch(u07ff, pattern));
    EXPECT_TRUE(RE2::FullMatch(u0800, pattern));
    EXPECT_TRUE(RE2::FullMatch(u0801, pattern));
}

// Test empty and simple patterns compile correctly
TEST_F(MaxRuneIndirectTest_302, SimplePatternCompilation_302) {
    RE2 empty("");
    ASSERT_TRUE(empty.ok());
    EXPECT_TRUE(RE2::FullMatch("", empty));
    
    RE2 literal("abc");
    ASSERT_TRUE(literal.ok());
    EXPECT_TRUE(RE2::FullMatch("abc", literal));
    EXPECT_FALSE(RE2::FullMatch("ab", literal));
}

// Test complex pattern with alternation across byte-length boundaries
TEST_F(MaxRuneIndirectTest_302, ComplexAlternation_302) {
    RE2 pattern("(a|ñ|中|😀)+");
    ASSERT_TRUE(pattern.ok()) << pattern.error();
    
    EXPECT_TRUE(RE2::FullMatch("a", pattern));
    EXPECT_TRUE(RE2::FullMatch("ñ", pattern));
    EXPECT_TRUE(RE2::FullMatch("中", pattern));
    EXPECT_TRUE(RE2::FullMatch("😀", pattern));
    EXPECT_TRUE(RE2::FullMatch("aañ中😀", pattern));
    EXPECT_FALSE(RE2::FullMatch("", pattern));
    EXPECT_FALSE(RE2::FullMatch("1", pattern));
}

// Test negated character class with multi-byte chars
TEST_F(MaxRuneIndirectTest_302, NegatedCharClass_302) {
    RE2 pattern("[^a-z]");
    ASSERT_TRUE(pattern.ok()) << pattern.error();
    
    EXPECT_FALSE(RE2::FullMatch("a", pattern));
    EXPECT_FALSE(RE2::FullMatch("z", pattern));
    EXPECT_TRUE(RE2::FullMatch("1", pattern));
    EXPECT_TRUE(RE2::FullMatch("ñ", pattern));
    EXPECT_TRUE(RE2::FullMatch("中", pattern));
}

}  // namespace
