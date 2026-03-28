#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string_view>

// Assuming the partial code has been included here as an inline function
inline bool hasUnicodeByteOrderMark(std::string_view s) { return s.starts_with("\xEF\xBB\xBF"); }

// TEST_ID: 1278
TEST_F(UTFTest_1278, HasUnicodeByteOrderMark_ReturnsTrueWhenStartsWithBOM_1278) {
    std::string_view input = "\xEF\xBB\xBFHello, World!";
    EXPECT_TRUE(hasUnicodeByteOrderMark(input));
}

// TEST_ID: 1278
TEST_F(UTFTest_1278, HasUnicodeByteOrderMark_ReturnsFalseWhenNoBOM_1278) {
    std::string_view input = "Hello, World!";
    EXPECT_FALSE(hasUnicodeByteOrderMark(input));
}

// TEST_ID: 1278
TEST_F(UTFTest_1278, HasUnicodeByteOrderMark_EmptyString_ReturnsFalse_1278) {
    std::string_view input = "";
    EXPECT_FALSE(hasUnicodeByteOrderMark(input));
}

// TEST_ID: 1278
TEST_F(UTFTest_1278, HasUnicodeByteOrderMark_ReturnsFalseWhenStartsWithDifferentSequence_1278) {
    std::string_view input = "\x00\x00\x00Hello, World!";
    EXPECT_FALSE(hasUnicodeByteOrderMark(input));
}