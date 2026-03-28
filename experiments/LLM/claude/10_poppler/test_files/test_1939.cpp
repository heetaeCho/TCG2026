#include <gtest/gtest.h>
#include "./TestProjects/poppler/poppler/DistinguishedNameParser.h"

// Tests for DN::detail::xtoi function
// This function converts a hex character to its integer value.

class XtoiTest_1939 : public ::testing::Test {
protected:
};

// Normal operation: digit characters '0' through '9'
TEST_F(XtoiTest_1939, ConvertDigit0_1939) {
    EXPECT_EQ(0, DN::detail::xtoi('0'));
}

TEST_F(XtoiTest_1939, ConvertDigit1_1939) {
    EXPECT_EQ(1, DN::detail::xtoi('1'));
}

TEST_F(XtoiTest_1939, ConvertDigit5_1939) {
    EXPECT_EQ(5, DN::detail::xtoi('5'));
}

TEST_F(XtoiTest_1939, ConvertDigit9_1939) {
    EXPECT_EQ(9, DN::detail::xtoi('9'));
}

// Normal operation: uppercase hex letters 'A' through 'F'
TEST_F(XtoiTest_1939, ConvertUpperA_1939) {
    EXPECT_EQ(10, DN::detail::xtoi('A'));
}

TEST_F(XtoiTest_1939, ConvertUpperB_1939) {
    EXPECT_EQ(11, DN::detail::xtoi('B'));
}

TEST_F(XtoiTest_1939, ConvertUpperC_1939) {
    EXPECT_EQ(12, DN::detail::xtoi('C'));
}

TEST_F(XtoiTest_1939, ConvertUpperD_1939) {
    EXPECT_EQ(13, DN::detail::xtoi('D'));
}

TEST_F(XtoiTest_1939, ConvertUpperE_1939) {
    EXPECT_EQ(14, DN::detail::xtoi('E'));
}

TEST_F(XtoiTest_1939, ConvertUpperF_1939) {
    EXPECT_EQ(15, DN::detail::xtoi('F'));
}

// Normal operation: lowercase hex letters 'a' through 'f'
TEST_F(XtoiTest_1939, ConvertLowerA_1939) {
    EXPECT_EQ(10, DN::detail::xtoi('a'));
}

TEST_F(XtoiTest_1939, ConvertLowerB_1939) {
    EXPECT_EQ(11, DN::detail::xtoi('b'));
}

TEST_F(XtoiTest_1939, ConvertLowerC_1939) {
    EXPECT_EQ(12, DN::detail::xtoi('c'));
}

TEST_F(XtoiTest_1939, ConvertLowerD_1939) {
    EXPECT_EQ(13, DN::detail::xtoi('d'));
}

TEST_F(XtoiTest_1939, ConvertLowerE_1939) {
    EXPECT_EQ(14, DN::detail::xtoi('e'));
}

TEST_F(XtoiTest_1939, ConvertLowerF_1939) {
    EXPECT_EQ(15, DN::detail::xtoi('f'));
}

// Boundary conditions: edges of digit range
TEST_F(XtoiTest_1939, BoundaryDigitLow_1939) {
    // '0' is the lowest valid digit
    EXPECT_EQ(0, DN::detail::xtoi('0'));
}

TEST_F(XtoiTest_1939, BoundaryDigitHigh_1939) {
    // '9' is the highest valid digit
    EXPECT_EQ(9, DN::detail::xtoi('9'));
}

// Boundary conditions: edges of uppercase hex range
TEST_F(XtoiTest_1939, BoundaryUpperHexLow_1939) {
    EXPECT_EQ(10, DN::detail::xtoi('A'));
}

TEST_F(XtoiTest_1939, BoundaryUpperHexHigh_1939) {
    EXPECT_EQ(15, DN::detail::xtoi('F'));
}

// Boundary conditions: edges of lowercase hex range
TEST_F(XtoiTest_1939, BoundaryLowerHexLow_1939) {
    EXPECT_EQ(10, DN::detail::xtoi('a'));
}

TEST_F(XtoiTest_1939, BoundaryLowerHexHigh_1939) {
    EXPECT_EQ(15, DN::detail::xtoi('f'));
}

// Test all digits systematically
TEST_F(XtoiTest_1939, AllDigits_1939) {
    for (unsigned char c = '0'; c <= '9'; ++c) {
        EXPECT_EQ(c - '0', DN::detail::xtoi(c)) << "Failed for character: " << c;
    }
}

// Test all uppercase hex letters systematically
TEST_F(XtoiTest_1939, AllUppercaseHex_1939) {
    for (unsigned char c = 'A'; c <= 'F'; ++c) {
        EXPECT_EQ(c - 'A' + 10, DN::detail::xtoi(c)) << "Failed for character: " << c;
    }
}

// Test all lowercase hex letters systematically
TEST_F(XtoiTest_1939, AllLowercaseHex_1939) {
    for (unsigned char c = 'a'; c <= 'f'; ++c) {
        EXPECT_EQ(c - 'a' + 10, DN::detail::xtoi(c)) << "Failed for character: " << c;
    }
}

// Test that uppercase and lowercase produce same results
TEST_F(XtoiTest_1939, UpperAndLowerCaseMatch_1939) {
    EXPECT_EQ(DN::detail::xtoi('A'), DN::detail::xtoi('a'));
    EXPECT_EQ(DN::detail::xtoi('B'), DN::detail::xtoi('b'));
    EXPECT_EQ(DN::detail::xtoi('C'), DN::detail::xtoi('c'));
    EXPECT_EQ(DN::detail::xtoi('D'), DN::detail::xtoi('d'));
    EXPECT_EQ(DN::detail::xtoi('E'), DN::detail::xtoi('e'));
    EXPECT_EQ(DN::detail::xtoi('F'), DN::detail::xtoi('f'));
}

// Test middle digit values
TEST_F(XtoiTest_1939, ConvertDigit2_1939) {
    EXPECT_EQ(2, DN::detail::xtoi('2'));
}

TEST_F(XtoiTest_1939, ConvertDigit3_1939) {
    EXPECT_EQ(3, DN::detail::xtoi('3'));
}

TEST_F(XtoiTest_1939, ConvertDigit4_1939) {
    EXPECT_EQ(4, DN::detail::xtoi('4'));
}

TEST_F(XtoiTest_1939, ConvertDigit6_1939) {
    EXPECT_EQ(6, DN::detail::xtoi('6'));
}

TEST_F(XtoiTest_1939, ConvertDigit7_1939) {
    EXPECT_EQ(7, DN::detail::xtoi('7'));
}

TEST_F(XtoiTest_1939, ConvertDigit8_1939) {
    EXPECT_EQ(8, DN::detail::xtoi('8'));
}
