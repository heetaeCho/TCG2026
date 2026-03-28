#include <gtest/gtest.h>
#include <string_view>
#include "UTF.h"

class HasUnicodeByteOrderMarkTest_1022 : public ::testing::Test {
protected:
};

// Normal operation: string starts with BOM (0xFE 0xFF)
TEST_F(HasUnicodeByteOrderMarkTest_1022, ReturnsTrueWhenStringStartsWithBOM_1022) {
    std::string s("\xFE\xFF", 2);
    EXPECT_TRUE(hasUnicodeByteOrderMark(s));
}

// Normal operation: string starts with BOM followed by additional content
TEST_F(HasUnicodeByteOrderMarkTest_1022, ReturnsTrueWhenStringStartsWithBOMFollowedByContent_1022) {
    std::string s("\xFE\xFF\x00\x41\x00\x42", 6);
    EXPECT_TRUE(hasUnicodeByteOrderMark(s));
}

// Boundary condition: empty string
TEST_F(HasUnicodeByteOrderMarkTest_1022, ReturnsFalseForEmptyString_1022) {
    std::string_view s("");
    EXPECT_FALSE(hasUnicodeByteOrderMark(s));
}

// Boundary condition: single character matching first byte of BOM
TEST_F(HasUnicodeByteOrderMarkTest_1022, ReturnsFalseForSingleByteFE_1022) {
    std::string s("\xFE", 1);
    EXPECT_FALSE(hasUnicodeByteOrderMark(s));
}

// Boundary condition: single character matching second byte of BOM
TEST_F(HasUnicodeByteOrderMarkTest_1022, ReturnsFalseForSingleByteFF_1022) {
    std::string s("\xFF", 1);
    EXPECT_FALSE(hasUnicodeByteOrderMark(s));
}

// Error case: reversed BOM bytes (0xFF 0xFE) - this is UTF-16LE BOM, not UTF-16BE
TEST_F(HasUnicodeByteOrderMarkTest_1022, ReturnsFalseForReversedBOM_1022) {
    std::string s("\xFF\xFE", 2);
    EXPECT_FALSE(hasUnicodeByteOrderMark(s));
}

// Error case: string does not start with BOM
TEST_F(HasUnicodeByteOrderMarkTest_1022, ReturnsFalseForRegularASCIIString_1022) {
    std::string_view s("Hello, World!");
    EXPECT_FALSE(hasUnicodeByteOrderMark(s));
}

// Error case: BOM appears in the middle but not at the start
TEST_F(HasUnicodeByteOrderMarkTest_1022, ReturnsFalseWhenBOMInMiddle_1022) {
    std::string s("AB\xFE\xFF", 4);
    EXPECT_FALSE(hasUnicodeByteOrderMark(s));
}

// Boundary condition: exact BOM with no trailing content
TEST_F(HasUnicodeByteOrderMarkTest_1022, ReturnsTrueForExactBOMOnly_1022) {
    std::string s("\xFE\xFF", 2);
    EXPECT_TRUE(hasUnicodeByteOrderMark(s));
}

// Error case: first byte matches but second doesn't
TEST_F(HasUnicodeByteOrderMarkTest_1022, ReturnsFalseWhenFirstByteMatchesButSecondDoesNot_1022) {
    std::string s("\xFE\x00", 2);
    EXPECT_FALSE(hasUnicodeByteOrderMark(s));
}

// Error case: second byte matches but first doesn't
TEST_F(HasUnicodeByteOrderMarkTest_1022, ReturnsFalseWhenSecondByteMatchesButFirstDoesNot_1022) {
    std::string s("\x00\xFF", 2);
    EXPECT_FALSE(hasUnicodeByteOrderMark(s));
}

// Error case: UTF-8 BOM (0xEF 0xBB 0xBF) should not match UTF-16BE BOM
TEST_F(HasUnicodeByteOrderMarkTest_1022, ReturnsFalseForUTF8BOM_1022) {
    std::string s("\xEF\xBB\xBF", 3);
    EXPECT_FALSE(hasUnicodeByteOrderMark(s));
}

// Normal operation: string with null bytes after BOM
TEST_F(HasUnicodeByteOrderMarkTest_1022, ReturnsTrueWhenBOMFollowedByNullBytes_1022) {
    std::string s("\xFE\xFF\x00\x00", 4);
    EXPECT_TRUE(hasUnicodeByteOrderMark(s));
}

// Boundary condition: string with embedded null byte before BOM pattern
TEST_F(HasUnicodeByteOrderMarkTest_1022, ReturnsFalseWhenNullByteBeforeBOM_1022) {
    std::string s("\x00\xFE\xFF", 3);
    EXPECT_FALSE(hasUnicodeByteOrderMark(s));
}

// Error case: all 0xFF bytes
TEST_F(HasUnicodeByteOrderMarkTest_1022, ReturnsFalseForAllFFBytes_1022) {
    std::string s("\xFF\xFF", 2);
    EXPECT_FALSE(hasUnicodeByteOrderMark(s));
}

// Error case: all 0xFE bytes
TEST_F(HasUnicodeByteOrderMarkTest_1022, ReturnsFalseForAllFEBytes_1022) {
    std::string s("\xFE\xFE", 2);
    EXPECT_FALSE(hasUnicodeByteOrderMark(s));
}
