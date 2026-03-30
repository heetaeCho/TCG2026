#include <gtest/gtest.h>
#include <string_view>

const std::string_view unicodeByteOrderMarkLE = "\377\376";

// Function to test
inline bool hasUnicodeByteOrderMarkLE(std::string_view s) {
    return s.starts_with(unicodeByteOrderMarkLE);
}

// Test Fixture for testing the hasUnicodeByteOrderMarkLE function
class UnicodeTest_1023 : public ::testing::Test {
protected:
    // You can set up any common test data here if needed
};

// Normal operation test
TEST_F(UnicodeTest_1023, HasUnicodeByteOrderMarkLE_NormalCase_1023) {
    // Case where the string has the Unicode Byte Order Mark LE at the beginning
    std::string_view testStr = "\377\376Hello, World!";
    EXPECT_TRUE(hasUnicodeByteOrderMarkLE(testStr));
}

// Boundary condition: Empty string
TEST_F(UnicodeTest_1023, HasUnicodeByteOrderMarkLE_EmptyString_1023) {
    std::string_view testStr = "";
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(testStr));
}

// Boundary condition: String without the Byte Order Mark
TEST_F(UnicodeTest_1023, HasUnicodeByteOrderMarkLE_NoByteOrderMark_1023) {
    std::string_view testStr = "Hello, World!";
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(testStr));
}

// Boundary condition: String with Byte Order Mark at the end
TEST_F(UnicodeTest_1023, HasUnicodeByteOrderMarkLE_ByteOrderMarkAtEnd_1023) {
    std::string_view testStr = "Hello, World!\377\376";
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(testStr));
}

// Exceptional case: Invalid characters in string
TEST_F(UnicodeTest_1023, HasUnicodeByteOrderMarkLE_InvalidString_1023) {
    std::string_view testStr = "Hello, World! \377";
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(testStr));
}