#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include "UTF.h"

class HasUnicodeByteOrderMarkTest_1278 : public ::testing::Test {
protected:
    // The Unicode BOM for UTF-8 is typically "\xFE\xFF" for UTF-16 BE
    // or for poppler's context, it depends on the unicodeByteOrderMark constant.
    // We test based on observable behavior.
};

// Test that a string starting with the Unicode BOM returns true
TEST_F(HasUnicodeByteOrderMarkTest_1278, StringWithBOMReturnsTrue_1278) {
    // The unicodeByteOrderMark in poppler is typically "\xFE\xFF" (UTF-16 BE BOM)
    std::string withBOM = std::string("\xFE\xFF") + "Hello";
    EXPECT_TRUE(hasUnicodeByteOrderMark(withBOM));
}

// Test that an empty string returns false
TEST_F(HasUnicodeByteOrderMarkTest_1278, EmptyStringReturnsFalse_1278) {
    std::string_view empty = "";
    EXPECT_FALSE(hasUnicodeByteOrderMark(empty));
}

// Test that a regular ASCII string without BOM returns false
TEST_F(HasUnicodeByteOrderMarkTest_1278, PlainASCIIStringReturnsFalse_1278) {
    std::string_view plain = "Hello, World!";
    EXPECT_FALSE(hasUnicodeByteOrderMark(plain));
}

// Test that a string with only the BOM returns true
TEST_F(HasUnicodeByteOrderMarkTest_1278, OnlyBOMReturnsTrue_1278) {
    std::string onlyBOM = "\xFE\xFF";
    EXPECT_TRUE(hasUnicodeByteOrderMark(onlyBOM));
}

// Test that a string with BOM in the middle (not at start) returns false
TEST_F(HasUnicodeByteOrderMarkTest_1278, BOMInMiddleReturnsFalse_1278) {
    std::string midBOM = std::string("Hello") + "\xFE\xFF" + "World";
    EXPECT_FALSE(hasUnicodeByteOrderMark(midBOM));
}

// Test that a string starting with only the first byte of BOM returns false
TEST_F(HasUnicodeByteOrderMarkTest_1278, PartialBOMFirstByteOnlyReturnsFalse_1278) {
    std::string partial = "\xFE";
    EXPECT_FALSE(hasUnicodeByteOrderMark(partial));
}

// Test that a string starting with reversed BOM bytes returns false
TEST_F(HasUnicodeByteOrderMarkTest_1278, ReversedBOMReturnsFalse_1278) {
    std::string reversed = "\xFF\xFE";
    EXPECT_FALSE(hasUnicodeByteOrderMark(reversed));
}

// Test that a string with BOM followed by more content works correctly
TEST_F(HasUnicodeByteOrderMarkTest_1278, BOMFollowedByUTF16ContentReturnsTrue_1278) {
    std::string content = std::string("\xFE\xFF") + std::string("\x00\x41\x00\x42", 4);
    EXPECT_TRUE(hasUnicodeByteOrderMark(content));
}

// Test with a single null byte
TEST_F(HasUnicodeByteOrderMarkTest_1278, SingleNullByteReturnsFalse_1278) {
    std::string_view nullByte("\0", 1);
    EXPECT_FALSE(hasUnicodeByteOrderMark(nullByte));
}

// Test with string_view containing null bytes after BOM
TEST_F(HasUnicodeByteOrderMarkTest_1278, BOMWithNullBytesReturnsTrue_1278) {
    std::string withNulls = std::string("\xFE\xFF") + std::string("\x00\x00", 2);
    std::string_view sv(withNulls.data(), withNulls.size());
    EXPECT_TRUE(hasUnicodeByteOrderMark(sv));
}

// Test UTF-8 BOM should return false (poppler uses UTF-16 BE BOM)
TEST_F(HasUnicodeByteOrderMarkTest_1278, UTF8BOMReturnsFalse_1278) {
    std::string utf8BOM = "\xEF\xBB\xBF";
    EXPECT_FALSE(hasUnicodeByteOrderMark(utf8BOM));
}

// Test with a string that has 0xFE but different second byte
TEST_F(HasUnicodeByteOrderMarkTest_1278, FirstByteFEDifferentSecondByteReturnsFalse_1278) {
    std::string almostBOM = "\xFE\xFE";
    EXPECT_FALSE(hasUnicodeByteOrderMark(almostBOM));
}

// Test with a long string starting with BOM
TEST_F(HasUnicodeByteOrderMarkTest_1278, LongStringWithBOMReturnsTrue_1278) {
    std::string longStr = "\xFE\xFF";
    longStr.append(10000, 'A');
    EXPECT_TRUE(hasUnicodeByteOrderMark(longStr));
}

// Test with a long string without BOM
TEST_F(HasUnicodeByteOrderMarkTest_1278, LongStringWithoutBOMReturnsFalse_1278) {
    std::string longStr(10000, 'A');
    EXPECT_FALSE(hasUnicodeByteOrderMark(longStr));
}
