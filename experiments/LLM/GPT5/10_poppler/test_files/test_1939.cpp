#include <gtest/gtest.h>

namespace DN {
    namespace detail {
        // Function to be tested
        inline unsigned char xtoi(unsigned char c) {
            if (c <= '9') {
                return c - '0';
            }
            if (c <= 'F') {
                return c - 'A' + 10;
            }
            return c - 'a' + 10;
        }
    }
}

// Test Fixture
class DistinguishedNameParserTest_1939 : public ::testing::Test {
protected:
    // You can add setup code here if needed
};

// Normal Operation Tests
TEST_F(DistinguishedNameParserTest_1939, xtoi_ValidDigits_0_9) {
    EXPECT_EQ(DN::detail::xtoi('0'), 0);
    EXPECT_EQ(DN::detail::xtoi('9'), 9);
}

TEST_F(DistinguishedNameParserTest_1939, xtoi_ValidHexCharacters_A_F) {
    EXPECT_EQ(DN::detail::xtoi('A'), 10);
    EXPECT_EQ(DN::detail::xtoi('F'), 15);
}

TEST_F(DistinguishedNameParserTest_1939, xtoi_ValidLowercaseHexCharacters_a_f) {
    EXPECT_EQ(DN::detail::xtoi('a'), 10);
    EXPECT_EQ(DN::detail::xtoi('f'), 15);
}

// Boundary Tests
TEST_F(DistinguishedNameParserTest_1939, xtoi_ValidBoundaryConditions) {
    EXPECT_EQ(DN::detail::xtoi('0'), 0);  // Lower boundary for digits
    EXPECT_EQ(DN::detail::xtoi('9'), 9);  // Upper boundary for digits
    EXPECT_EQ(DN::detail::xtoi('A'), 10); // Lower boundary for uppercase letters
    EXPECT_EQ(DN::detail::xtoi('F'), 15); // Upper boundary for uppercase letters
    EXPECT_EQ(DN::detail::xtoi('a'), 10); // Lower boundary for lowercase letters
    EXPECT_EQ(DN::detail::xtoi('f'), 15); // Upper boundary for lowercase letters
}

// Exceptional or Error Case Tests (Invalid Input)
TEST_F(DistinguishedNameParserTest_1939, xtoi_InvalidCharacters) {
    // Assuming the behavior is to return invalid results for non-hex characters,
    // but the actual implementation does not handle errors, so this would be a test
    // for a possible extension to handle exceptions or errors in the future.
    EXPECT_EQ(DN::detail::xtoi('G'), 16);  // Invalid char (G is beyond F)
    EXPECT_EQ(DN::detail::xtoi('z'), 35);  // Invalid char (z is beyond f)
    EXPECT_EQ(DN::detail::xtoi('$'), 0);  // Invalid char ($ should be handled differently)
}