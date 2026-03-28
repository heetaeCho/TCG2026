#include <gtest/gtest.h>

namespace DN {
    namespace detail {
        inline unsigned char xtoi(unsigned char first, unsigned char second) {
            return 16 * xtoi(first) + xtoi(second);
        }
    }
}

// Test fixture to group xtoi related tests
class XtOITest_1940 : public ::testing::Test {
protected:
    // Setup and Tear down functions can be added here if needed
};

// Normal operation test: convert valid hex character pair "1A"
TEST_F(XtOITest_1940, xtoiValidInput_1940) {
    EXPECT_EQ(DN::detail::xtoi('1', 'A'), 26);  // 1A in hex is 26 in decimal
}

// Boundary condition test: smallest possible valid hex character pair "00"
TEST_F(XtOITest_1940, xtoiSmallestValue_1940) {
    EXPECT_EQ(DN::detail::xtoi('0', '0'), 0);  // 00 in hex is 0 in decimal
}

// Boundary condition test: largest possible valid hex character pair "FF"
TEST_F(XtOITest_1940, xtoiLargestValue_1940) {
    EXPECT_EQ(DN::detail::xtoi('F', 'F'), 255);  // FF in hex is 255 in decimal
}

// Exceptional or error case test: invalid input (e.g., 'G' is not a valid hex character)
TEST_F(XtOITest_1940, xtoiInvalidHexCharacter_1940) {
    // For this case, we can assume an error should be returned, as 'G' is not valid for hex
    EXPECT_THROW(DN::detail::xtoi('G', '1'), std::invalid_argument);  // Should throw if implemented properly
}

// Exceptional case test: invalid character range
TEST_F(XtOITest_1940, xtoiOutOfRangeCharacter_1940) {
    EXPECT_THROW(DN::detail::xtoi('G', 'Z'), std::invalid_argument);  // Should throw for invalid characters
}