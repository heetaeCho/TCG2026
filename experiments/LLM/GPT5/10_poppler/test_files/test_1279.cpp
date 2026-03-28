#include <gtest/gtest.h>
#include <string_view>
#include "UTF.h"  // Include the header with the partial code

// Test for hasUnicodeByteOrderMarkLE function

// Test Case 1: Normal operation - when string starts with the Unicode Byte Order Mark (BOM) LE
TEST_F(UTFTest_1279, TestHasUnicodeByteOrderMarkLE_True_1279) {
    // Example string with BOM LE
    std::string_view testString = "\xFF\xFEHello World";  // BOM LE: 0xFF 0xFE followed by text

    // Assert that the function returns true when the string starts with BOM LE
    EXPECT_TRUE(hasUnicodeByteOrderMarkLE(testString));
}

// Test Case 2: Normal operation - when string does not start with the Unicode Byte Order Mark (BOM) LE
TEST_F(UTFTest_1280, TestHasUnicodeByteOrderMarkLE_False_1280) {
    // Example string without BOM LE
    std::string_view testString = "Hello World";

    // Assert that the function returns false when the string does not start with BOM LE
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(testString));
}

// Test Case 3: Boundary condition - Empty string, should not have BOM LE
TEST_F(UTFTest_1281, TestHasUnicodeByteOrderMarkLE_EmptyString_1281) {
    std::string_view testString = "";

    // Assert that the function returns false for an empty string
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(testString));
}

// Test Case 4: Boundary condition - string with only BOM LE (no content after it)
TEST_F(UTFTest_1282, TestHasUnicodeByteOrderMarkLE_BOMOnly_1282) {
    // String with only BOM LE
    std::string_view testString = "\xFF\xFE";

    // Assert that the function returns true for a string that contains only BOM LE
    EXPECT_TRUE(hasUnicodeByteOrderMarkLE(testString));
}

// Test Case 5: Exceptional case - string starts with an invalid BOM or different BOM
TEST_F(UTFTest_1283, TestHasUnicodeByteOrderMarkLE_InvalidBOM_1283) {
    // Example string with a different BOM or an invalid BOM
    std::string_view testString = "\xEF\xBB\xBFHello World";  // BOM for UTF-8

    // Assert that the function returns false when the string starts with a non-LE BOM
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(testString));
}