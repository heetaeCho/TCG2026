#include <gtest/gtest.h>

// The UnicodeIsWhitespace function being tested
bool UnicodeIsWhitespace(Unicode ucs4) {
    static Unicode const spaces[] = { 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x0020, 0x0085, 0x00A0, 
                                      0x2000, 0x2001, 0x2002, 0x2003, 0x2004, 0x2005, 0x2006, 0x2007, 
                                      0x2008, 0x2009, 0x200A, 0x2028, 0x2029, 0x202F, 0x205F, 0x3000 };
    Unicode const *end = spaces + sizeof(spaces) / sizeof(spaces[0]);
    Unicode const *i = std::lower_bound(spaces, end, ucs4);
    return (i != end && *i == ucs4);
}

// Test case for normal operation
TEST_F(UnicodeIsWhitespaceTest_1522, ValidWhitespaceCharacters_1522) {
    // Test with some valid Unicode whitespace characters
    EXPECT_TRUE(UnicodeIsWhitespace(0x0020));  // Space
    EXPECT_TRUE(UnicodeIsWhitespace(0x0009));  // Tab
    EXPECT_TRUE(UnicodeIsWhitespace(0x000A));  // Line feed
    EXPECT_TRUE(UnicodeIsWhitespace(0x202F));  // Narrow no-break space
    EXPECT_TRUE(UnicodeIsWhitespace(0x3000));  // Ideographic space
}

// Test case for boundary conditions
TEST_F(UnicodeIsWhitespaceTest_1522, BoundaryWhitespaceCharacters_1522) {
    // Test with boundary values that are at the edges of the list
    EXPECT_TRUE(UnicodeIsWhitespace(0x2000));  // En quad
    EXPECT_TRUE(UnicodeIsWhitespace(0x3000));  // Ideographic space
    EXPECT_FALSE(UnicodeIsWhitespace(0x200B));  // Zero width space (not in list)
}

// Test case for non-whitespace characters
TEST_F(UnicodeIsWhitespaceTest_1522, NonWhitespaceCharacters_1522) {
    // Test with non-whitespace characters
    EXPECT_FALSE(UnicodeIsWhitespace(0x0041));  // 'A'
    EXPECT_FALSE(UnicodeIsWhitespace(0x0031));  // '1'
    EXPECT_FALSE(UnicodeIsWhitespace(0x2028));  // Line separator (not a whitespace)
}

// Test case for exceptional or error cases
TEST_F(UnicodeIsWhitespaceTest_1522, InvalidUnicode_1522) {
    // Test with a Unicode that doesn't exist in the provided list
    EXPECT_FALSE(UnicodeIsWhitespace(0xFFFF));  // A non-defined Unicode character
}