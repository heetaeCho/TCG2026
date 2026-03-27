#include <gtest/gtest.h>
#include <string_view>

// Include the actual implementation of the function (usually in a separate header)
inline bool isUtf8WithBom(std::string_view str) {
    if (str.size() < 4) {
        return false;
    }
    if (str[0] == '\xef' && str[1] == '\xbb' && str[2] == '\xbf') {
        return true;
    }
    return false;
}

// Test fixture for UTF tests
class UTFTest_1025 : public ::testing::Test {};

// Test case for normal operation, where the input string has BOM
TEST_F(UTFTest_1025, ValidUtf8WithBom_1025) {
    std::string_view str = "\xef\xbb\xbfHello, World!";
    EXPECT_TRUE(isUtf8WithBom(str));
}

// Test case for normal operation, where the input string does not have BOM
TEST_F(UTFTest_1025, ValidUtf8WithoutBom_1025) {
    std::string_view str = "Hello, World!";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Test case for boundary condition: input string of size 3 (smaller than BOM size)
TEST_F(UTFTest_1025, TooSmallForBom_1025) {
    std::string_view str = "\xef\xbb";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Test case for boundary condition: input string of size 4 (exact size for BOM check)
TEST_F(UTFTest_1025, ExactBOMSize_1025) {
    std::string_view str = "\xef\xbb\xbf";
    EXPECT_TRUE(isUtf8WithBom(str));
}

// Test case for error condition: input string smaller than 4 characters
TEST_F(UTFTest_1025, StringTooShort_1025) {
    std::string_view str = "\xef";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Test case for error condition: input string with incorrect BOM
TEST_F(UTFTest_1025, IncorrectBom_1025) {
    std::string_view str = "\xef\xbb\xff";  // Incorrect BOM
    EXPECT_FALSE(isUtf8WithBom(str));
}