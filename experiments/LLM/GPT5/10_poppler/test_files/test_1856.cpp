#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/PDFDoc.h"
#include "./TestProjects/poppler/goo/GooString.h"

#define pdfIdLength 32  // Defining this constant to match the code context

// Test case for normal operation of the get_id function
TEST_F(PDFDocTest_1856, GetId_NormalOperation_1856) {
    GooString encodedidstring("1234567890abcdef1234567890abcdef");
    GooString id;

    // Expect the function to return true for a valid 32-character hex string
    bool result = get_id(&encodedidstring, &id);

    EXPECT_TRUE(result);
    EXPECT_EQ(id.toStr(), "1234567890abcdef1234567890abcdef");
}

// Test case for invalid encodedidstring length (less than required)
TEST_F(PDFDocTest_1856, GetId_InvalidLength_1856) {
    GooString encodedidstring("1234");  // Too short, less than 32 characters
    GooString id;

    // Expect the function to return false for an invalid input length
    bool result = get_id(&encodedidstring, &id);

    EXPECT_FALSE(result);
}

// Test case for invalid encodedidstring length (greater than required)
TEST_F(PDFDocTest_1856, GetId_InvalidLengthTooLong_1856) {
    GooString encodedidstring("1234567890abcdef1234567890abcdef1234567890abcdef1234567890abcdef");
    GooString id;

    // Expect the function to return false for an invalid input length (too long)
    bool result = get_id(&encodedidstring, &id);

    EXPECT_FALSE(result);
}

// Test case for incorrect hex encoding (non-hex characters)
TEST_F(PDFDocTest_1856, GetId_InvalidHexCharacters_1856) {
    GooString encodedidstring("123z567890abcdef1234567890abcdef");  // Invalid 'z' character
    GooString id;

    // Expect the function to return false when the string contains non-hex characters
    bool result = get_id(&encodedidstring, &id);

    EXPECT_FALSE(result);
}

// Test case for empty encodedidstring
TEST_F(PDFDocTest_1856, GetId_EmptyString_1856) {
    GooString encodedidstring("");
    GooString id;

    // Expect the function to return false for an empty input string
    bool result = get_id(&encodedidstring, &id);

    EXPECT_FALSE(result);
}

// Test case for valid encodedidstring with leading/trailing spaces (should not be valid)
TEST_F(PDFDocTest_1856, GetId_WithSpaces_1856) {
    GooString encodedidstring(" 1234567890abcdef1234567890abcdef ");
    GooString id;

    // Expect the function to return false for a string with spaces
    bool result = get_id(&encodedidstring, &id);

    EXPECT_FALSE(result);
}

// Test case for boundary condition: exactly 32 characters
TEST_F(PDFDocTest_1856, GetId_BoundaryCondition_1856) {
    GooString encodedidstring("0123456789abcdef0123456789abcdef");
    GooString id;

    // Expect the function to return true for exactly 32 hex characters
    bool result = get_id(&encodedidstring, &id);

    EXPECT_TRUE(result);
    EXPECT_EQ(id.toStr(), "0123456789abcdef0123456789abcdef");
}