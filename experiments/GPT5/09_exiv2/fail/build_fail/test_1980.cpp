#include <gtest/gtest.h>
#include <stdexcept>
#include <limits>
#include "XMPUtils.h"  // Assuming the necessary header is included for GatherInt

// Mocking the XMP_Throw function for testing
void MockXMP_Throw(const char* errMsg, int errCode) {
    throw std::runtime_error("Error: " + std::string(errMsg));
}

class XMPUtilsTest : public ::testing::Test {
protected:
    // Set up any common test fixtures here if necessary
    void SetUp() override {
        // You could redirect XMP_Throw to MockXMP_Throw for tests
        // Example: Redirecting to MockXMP_Throw if necessary
    }
};

// Test for normal operation
TEST_F(XMPUtilsTest, GatherInt_NormalOperation_1980) {
    const char* strValue = "12345";
    size_t pos = 0;
    const char* errMsg = "Invalid integer format";

    // Expected result: GatherInt should successfully parse the integer
    XMP_Int32 result = GatherInt(strValue, &pos, errMsg);

    EXPECT_EQ(result, 12345);
    EXPECT_EQ(pos, 5);  // position should be updated to 5 after parsing the entire number
}

// Test for boundary condition (testing max value for XMP_Int32)
TEST_F(XMPUtilsTest, GatherInt_MaxValue_1981) {
    const char* strValue = "2147483647";  // Max XMP_Int32 value
    size_t pos = 0;
    const char* errMsg = "Invalid integer format";

    // Expected result: GatherInt should successfully parse the max integer
    XMP_Int32 result = GatherInt(strValue, &pos, errMsg);

    EXPECT_EQ(result, std::numeric_limits<XMP_Int32>::max());
    EXPECT_EQ(pos, 10);  // position should be updated to 10 after parsing the entire number
}

// Test for boundary condition (testing overflow error)
TEST_F(XMPUtilsTest, GatherInt_Overflow_1982) {
    const char* strValue = "2147483648";  // Overflow for XMP_Int32
    size_t pos = 0;
    const char* errMsg = "Invalid integer format";

    // Expected result: Should throw an error due to overflow
    EXPECT_THROW(GatherInt(strValue, &pos, errMsg), std::runtime_error);
}

// Test for invalid input (non-numeric characters)
TEST_F(XMPUtilsTest, GatherInt_InvalidCharacter_1983) {
    const char* strValue = "12a45";  // Invalid character 'a'
    size_t pos = 0;
    const char* errMsg = "Invalid integer format";

    // Expected result: Should throw an error due to invalid characters
    EXPECT_THROW(GatherInt(strValue, &pos, errMsg), std::runtime_error);
}

// Test for case where no digits are present
TEST_F(XMPUtilsTest, GatherInt_NoDigits_1984) {
    const char* strValue = "abc";  // No digits to parse
    size_t pos = 0;
    const char* errMsg = "Invalid integer format";

    // Expected result: Should throw an error as there are no digits to parse
    EXPECT_THROW(GatherInt(strValue, &pos, errMsg), std::runtime_error);
}