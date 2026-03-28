#include <gtest/gtest.h>

// Include the necessary headers
#include "./TestProjects/poppler/poppler/UTF.h"

// Test Fixture class
class UnicodeIsValidTest_1021 : public ::testing::Test {
protected:
    // You can add setup and teardown functions here if needed
};

// Normal operation tests
TEST_F(UnicodeIsValidTest_1021, ValidUnicodeReturnsTrue_1021) {
    // Valid Unicode values
    EXPECT_TRUE(UnicodeIsValid(0x0041));   // 'A'
    EXPECT_TRUE(UnicodeIsValid(0x1F600));  // 😀
    EXPECT_TRUE(UnicodeIsValid(0x10FFFF)); // Maximum valid Unicode
}

TEST_F(UnicodeIsValidTest_1021, InvalidUnicodeReturnsFalse_1021) {
    // Invalid Unicode values
    EXPECT_FALSE(UnicodeIsValid(0xD800));  // Invalid high surrogate
    EXPECT_FALSE(UnicodeIsValid(0xFDD0));  // Reserved range
    EXPECT_FALSE(UnicodeIsValid(0xFFFE));  // Invalid value (Reserved)
    EXPECT_FALSE(UnicodeIsValid(0x110000)); // Invalid value (above max valid Unicode)
}

// Boundary condition tests
TEST_F(UnicodeIsValidTest_1021, BoundaryTests_1021) {
    // Testing boundary values
    EXPECT_FALSE(UnicodeIsValid(0xD7FF)); // Just below the invalid surrogate range
    EXPECT_FALSE(UnicodeIsValid(0xD800)); // Start of the invalid surrogate range
    EXPECT_FALSE(UnicodeIsValid(0xFDD0)); // Start of the reserved range
    EXPECT_FALSE(UnicodeIsValid(0xFDEF)); // End of the reserved range
    EXPECT_TRUE(UnicodeIsValid(0xFFFF));  // Just before the reserved range
    EXPECT_TRUE(UnicodeIsValid(0x10FFFF)); // Maximum valid Unicode
}

// Exceptional or error cases
TEST_F(UnicodeIsValidTest_1021, InvalidUtfRange_1021) {
    // Test values outside the valid Unicode range
    EXPECT_FALSE(UnicodeIsValid(0x110000)); // Above the max Unicode point
    EXPECT_FALSE(UnicodeIsValid(0xF00000)); // Invalid value far above max Unicode point
}