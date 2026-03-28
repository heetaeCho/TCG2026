#include <gtest/gtest.h>
#include <string>
#include "poppler/PageLabelInfo_p.h"
#include "goo/GooString.h"

class ToRomanTest_1934 : public ::testing::Test {
protected:
    GooString str;
    
    void SetUp() override {
        // str is default constructed (empty)
    }
    
    std::string getRomanResult(int number, bool uppercase) {
        GooString s;
        toRoman(number, &s, uppercase);
        return s.toStr();
    }
};

// Test basic single-digit Roman numerals (uppercase)
TEST_F(ToRomanTest_1934, SingleDigitUppercase_1934) {
    EXPECT_EQ(getRomanResult(1, true), "I");
    EXPECT_EQ(getRomanResult(2, true), "II");
    EXPECT_EQ(getRomanResult(3, true), "III");
    EXPECT_EQ(getRomanResult(4, true), "IV");
    EXPECT_EQ(getRomanResult(5, true), "V");
    EXPECT_EQ(getRomanResult(6, true), "VI");
    EXPECT_EQ(getRomanResult(7, true), "VII");
    EXPECT_EQ(getRomanResult(8, true), "VIII");
    EXPECT_EQ(getRomanResult(9, true), "IX");
}

// Test basic single-digit Roman numerals (lowercase)
TEST_F(ToRomanTest_1934, SingleDigitLowercase_1934) {
    EXPECT_EQ(getRomanResult(1, false), "i");
    EXPECT_EQ(getRomanResult(2, false), "ii");
    EXPECT_EQ(getRomanResult(3, false), "iii");
    EXPECT_EQ(getRomanResult(4, false), "iv");
    EXPECT_EQ(getRomanResult(5, false), "v");
    EXPECT_EQ(getRomanResult(6, false), "vi");
    EXPECT_EQ(getRomanResult(7, false), "vii");
    EXPECT_EQ(getRomanResult(8, false), "viii");
    EXPECT_EQ(getRomanResult(9, false), "ix");
}

// Test tens
TEST_F(ToRomanTest_1934, TensUppercase_1934) {
    EXPECT_EQ(getRomanResult(10, true), "X");
    EXPECT_EQ(getRomanResult(20, true), "XX");
    EXPECT_EQ(getRomanResult(30, true), "XXX");
    EXPECT_EQ(getRomanResult(40, true), "XL");
    EXPECT_EQ(getRomanResult(50, true), "L");
    EXPECT_EQ(getRomanResult(60, true), "LX");
    EXPECT_EQ(getRomanResult(70, true), "LXX");
    EXPECT_EQ(getRomanResult(80, true), "LXXX");
    EXPECT_EQ(getRomanResult(90, true), "XC");
}

// Test hundreds
TEST_F(ToRomanTest_1934, HundredsUppercase_1934) {
    EXPECT_EQ(getRomanResult(100, true), "C");
    EXPECT_EQ(getRomanResult(200, true), "CC");
    EXPECT_EQ(getRomanResult(300, true), "CCC");
    EXPECT_EQ(getRomanResult(400, true), "CD");
    EXPECT_EQ(getRomanResult(500, true), "D");
    EXPECT_EQ(getRomanResult(600, true), "DC");
    EXPECT_EQ(getRomanResult(700, true), "DCC");
    EXPECT_EQ(getRomanResult(800, true), "DCCC");
    EXPECT_EQ(getRomanResult(900, true), "CM");
}

// Test thousands
TEST_F(ToRomanTest_1934, ThousandsUppercase_1934) {
    EXPECT_EQ(getRomanResult(1000, true), "M");
    EXPECT_EQ(getRomanResult(2000, true), "MM");
    EXPECT_EQ(getRomanResult(3000, true), "MMM");
}

// Test compound numbers
TEST_F(ToRomanTest_1934, CompoundNumbersUppercase_1934) {
    EXPECT_EQ(getRomanResult(14, true), "XIV");
    EXPECT_EQ(getRomanResult(42, true), "XLII");
    EXPECT_EQ(getRomanResult(99, true), "XCIX");
    EXPECT_EQ(getRomanResult(246, true), "CCXLVI");
    EXPECT_EQ(getRomanResult(789, true), "DCCLXXXIX");
    EXPECT_EQ(getRomanResult(1066, true), "MLXVI");
    EXPECT_EQ(getRomanResult(1999, true), "MCMXCIX");
    EXPECT_EQ(getRomanResult(2024, true), "MMXXIV");
    EXPECT_EQ(getRomanResult(3999, true), "MMMCMXCIX");
}

// Test compound numbers (lowercase)
TEST_F(ToRomanTest_1934, CompoundNumbersLowercase_1934) {
    EXPECT_EQ(getRomanResult(14, false), "xiv");
    EXPECT_EQ(getRomanResult(42, false), "xlii");
    EXPECT_EQ(getRomanResult(99, false), "xcix");
    EXPECT_EQ(getRomanResult(1999, false), "mcmxcix");
    EXPECT_EQ(getRomanResult(3999, false), "mmmcmxcix");
}

// Test boundary: number >= 4000 should not produce output (error case)
TEST_F(ToRomanTest_1934, NumberTooLargeReturnsEmpty_1934) {
    // For numbers >= 4000, the function should return early without appending
    EXPECT_EQ(getRomanResult(4000, true), "");
    EXPECT_EQ(getRomanResult(4001, true), "");
    EXPECT_EQ(getRomanResult(5000, true), "");
    EXPECT_EQ(getRomanResult(10000, true), "");
    EXPECT_EQ(getRomanResult(4000, false), "");
}

// Test zero - all digits are 0 so nothing should be appended
TEST_F(ToRomanTest_1934, ZeroProducesEmptyString_1934) {
    EXPECT_EQ(getRomanResult(0, true), "");
    EXPECT_EQ(getRomanResult(0, false), "");
}

// Test that the function appends to an existing string
TEST_F(ToRomanTest_1934, AppendsToExistingString_1934) {
    GooString s("prefix");
    toRoman(10, &s, true);
    EXPECT_EQ(s.toStr(), "prefixX");
}

// Test specific well-known numbers
TEST_F(ToRomanTest_1934, WellKnownNumbers_1934) {
    EXPECT_EQ(getRomanResult(11, true), "XI");
    EXPECT_EQ(getRomanResult(15, true), "XV");
    EXPECT_EQ(getRomanResult(19, true), "XIX");
    EXPECT_EQ(getRomanResult(44, true), "XLIV");
    EXPECT_EQ(getRomanResult(49, true), "XLIX");
    EXPECT_EQ(getRomanResult(99, true), "XCIX");
    EXPECT_EQ(getRomanResult(444, true), "CDXLIV");
    EXPECT_EQ(getRomanResult(888, true), "DCCCLXXXVIII");
    EXPECT_EQ(getRomanResult(999, true), "CMXCIX");
    EXPECT_EQ(getRomanResult(1444, true), "MCDXLIV");
    EXPECT_EQ(getRomanResult(1776, true), "MDCCLXXVI");
    EXPECT_EQ(getRomanResult(1918, true), "MCMXVIII");
    EXPECT_EQ(getRomanResult(2023, true), "MMXXIII");
}

// Test boundary: 3999 is the maximum valid number
TEST_F(ToRomanTest_1934, MaxValidNumber_1934) {
    EXPECT_EQ(getRomanResult(3999, true), "MMMCMXCIX");
    EXPECT_EQ(getRomanResult(3999, false), "mmmcmxcix");
}

// Test number 1 as minimum meaningful Roman numeral
TEST_F(ToRomanTest_1934, MinimumMeaningfulNumber_1934) {
    EXPECT_EQ(getRomanResult(1, true), "I");
    EXPECT_EQ(getRomanResult(1, false), "i");
}

// Test that uppercase and lowercase produce correctly cased output for same number
TEST_F(ToRomanTest_1934, CaseConsistency_1934) {
    std::string upper = getRomanResult(1999, true);
    std::string lower = getRomanResult(1999, false);
    
    // They should have the same length
    EXPECT_EQ(upper.length(), lower.length());
    
    // Each character in upper should be uppercase version of corresponding lower
    for (size_t i = 0; i < upper.length(); i++) {
        EXPECT_EQ(std::tolower(upper[i]), lower[i]);
    }
}

// Test multiple calls to toRoman append sequentially
TEST_F(ToRomanTest_1934, MultipleCallsAppend_1934) {
    GooString s;
    toRoman(1, &s, true);
    toRoman(2, &s, true);
    EXPECT_EQ(s.toStr(), "III");
}
