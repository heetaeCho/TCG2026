#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

class GPGMECryptoSignBackendTest_1946 : public ::testing::Test {
protected:
    // You can set up any common state for all tests here if necessary
};

// Test case for normal operation
TEST_F(GPGMECryptoSignBackendTest_1946, fromCharPtr_ReturnsStringWhenDataIsNonNull_1946) {
    const char *data = "test_data";
    std::string result = fromCharPtr(data);
    
    EXPECT_EQ(result, "test_data");
}

// Test case for boundary condition: empty string input
TEST_F(GPGMECryptoSignBackendTest_1946, fromCharPtr_ReturnsEmptyStringWhenDataIsNull_1946) {
    const char *data = nullptr;
    std::string result = fromCharPtr(data);

    EXPECT_EQ(result, "");
}

// Test case for boundary condition: empty string as input
TEST_F(GPGMECryptoSignBackendTest_1946, fromCharPtr_ReturnsEmptyStringWhenDataIsEmpty_1946) {
    const char *data = "";
    std::string result = fromCharPtr(data);

    EXPECT_EQ(result, "");
}

// Test case for exceptional/error case (observed behavior when NULL pointer is passed)
TEST_F(GPGMECryptoSignBackendTest_1946, fromCharPtr_ReturnsEmptyStringWhenDataIsNullptr_1946) {
    const char *data = nullptr;
    std::string result = fromCharPtr(data);

    EXPECT_EQ(result, "");
}

// Test case for normal operation with string that contains special characters
TEST_F(GPGMECryptoSignBackendTest_1946, fromCharPtr_ReturnsStringWithSpecialCharacters_1946) {
    const char *data = "test@#data!";
    std::string result = fromCharPtr(data);
    
    EXPECT_EQ(result, "test@#data!");
}