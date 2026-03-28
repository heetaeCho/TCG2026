#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/poppler/poppler/DistinguishedNameParser.h"

// We need to also understand there's likely a single-char xtoi overload.
// Based on the two-char version: 16 * xtoi(first) + xtoi(second)
// This implies xtoi(char) converts a hex character to its numeric value.

class XtoiTest_1940 : public ::testing::Test {
protected:
    // Helper to call the two-argument xtoi
    unsigned char callXtoi(unsigned char first, unsigned char second) {
        return DN::detail::xtoi(first, second);
    }
};

// Test normal hex digit pairs - lowercase
TEST_F(XtoiTest_1940, LowercaseHexDigits_1940) {
    // 'a' = 10, 'b' = 11 => 16*10 + 11 = 171
    EXPECT_EQ(callXtoi('a', 'b'), 0xab);
}

TEST_F(XtoiTest_1940, LowercaseHexDigits_cd_1940) {
    EXPECT_EQ(callXtoi('c', 'd'), 0xcd);
}

TEST_F(XtoiTest_1940, LowercaseHexDigits_ef_1940) {
    EXPECT_EQ(callXtoi('e', 'f'), 0xef);
}

// Test normal hex digit pairs - uppercase
TEST_F(XtoiTest_1940, UppercaseHexDigits_AB_1940) {
    EXPECT_EQ(callXtoi('A', 'B'), 0xAB);
}

TEST_F(XtoiTest_1940, UppercaseHexDigits_CD_1940) {
    EXPECT_EQ(callXtoi('C', 'D'), 0xCD);
}

TEST_F(XtoiTest_1940, UppercaseHexDigits_EF_1940) {
    EXPECT_EQ(callXtoi('E', 'F'), 0xEF);
}

// Test numeric digits
TEST_F(XtoiTest_1940, NumericDigits_00_1940) {
    EXPECT_EQ(callXtoi('0', '0'), 0x00);
}

TEST_F(XtoiTest_1940, NumericDigits_99_1940) {
    EXPECT_EQ(callXtoi('9', '9'), 0x99);
}

TEST_F(XtoiTest_1940, NumericDigits_12_1940) {
    EXPECT_EQ(callXtoi('1', '2'), 0x12);
}

TEST_F(XtoiTest_1940, NumericDigits_45_1940) {
    EXPECT_EQ(callXtoi('4', '5'), 0x45);
}

// Test mixed case and digits
TEST_F(XtoiTest_1940, MixedCaseAndDigits_3f_1940) {
    EXPECT_EQ(callXtoi('3', 'f'), 0x3f);
}

TEST_F(XtoiTest_1940, MixedCaseAndDigits_F3_1940) {
    EXPECT_EQ(callXtoi('F', '3'), 0xF3);
}

TEST_F(XtoiTest_1940, MixedUpperLower_aF_1940) {
    // 'a' = 10, 'F' = 15 => 16*10 + 15 = 175 = 0xAF
    EXPECT_EQ(callXtoi('a', 'F'), 0xAF);
}

TEST_F(XtoiTest_1940, MixedUpperLower_Fa_1940) {
    // 'F' = 15, 'a' = 10 => 16*15 + 10 = 250 = 0xFA
    EXPECT_EQ(callXtoi('F', 'a'), 0xFA);
}

// Boundary values
TEST_F(XtoiTest_1940, MaxValue_FF_1940) {
    EXPECT_EQ(callXtoi('F', 'F'), 0xFF);
}

TEST_F(XtoiTest_1940, MaxValueLower_ff_1940) {
    EXPECT_EQ(callXtoi('f', 'f'), 0xFF);
}

TEST_F(XtoiTest_1940, MinValue_00_1940) {
    EXPECT_EQ(callXtoi('0', '0'), 0x00);
}

TEST_F(XtoiTest_1940, Value_01_1940) {
    EXPECT_EQ(callXtoi('0', '1'), 0x01);
}

TEST_F(XtoiTest_1940, Value_10_1940) {
    EXPECT_EQ(callXtoi('1', '0'), 0x10);
}

// Verify specific known values
TEST_F(XtoiTest_1940, Value_7E_1940) {
    // '7' = 7, 'E' = 14 => 16*7 + 14 = 126 = 0x7E
    EXPECT_EQ(callXtoi('7', 'E'), 0x7E);
}

TEST_F(XtoiTest_1940, Value_2A_1940) {
    // '2' = 2, 'A' = 10 => 16*2 + 10 = 42 = 0x2A
    EXPECT_EQ(callXtoi('2', 'A'), 0x2A);
}

TEST_F(XtoiTest_1940, Value_80_1940) {
    EXPECT_EQ(callXtoi('8', '0'), 0x80);
}

TEST_F(XtoiTest_1940, ReturnTypeIsUnsignedChar_1940) {
    unsigned char result = callXtoi('F', 'F');
    EXPECT_EQ(result, 255);
}
