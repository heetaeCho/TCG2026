#include <gtest/gtest.h>
#include <climits>

// Function from the provided code
static int fromRoman(const char *buffer) {
    int digit_value, prev_digit_value, value;
    int i;
    prev_digit_value = INT_MAX;
    value = 0;
    
    for (i = 0; buffer[i] != '\0'; i++) {
        switch (buffer[i]) {
            case 'm': case 'M': digit_value = 1000; break;
            case 'd': case 'D': digit_value = 500; break;
            case 'c': case 'C': digit_value = 100; break;
            case 'l': case 'L': digit_value = 50; break;
            case 'x': case 'X': digit_value = 10; break;
            case 'v': case 'V': digit_value = 5; break;
            case 'i': case 'I': digit_value = 1; break;
            default: return -1;
        }

        if (digit_value <= prev_digit_value) {
            value += digit_value;
        } else {
            value += digit_value - prev_digit_value * 2;
        }

        prev_digit_value = digit_value;
    }

    return value;
}

// TEST CASES

TEST(FromRomanTest_1933, ValidRomanNumerals_1933) {
    // Test for valid Roman numerals
    EXPECT_EQ(fromRoman("III"), 3);
    EXPECT_EQ(fromRoman("IV"), 4);
    EXPECT_EQ(fromRoman("IX"), 9);
    EXPECT_EQ(fromRoman("LVIII"), 58);
    EXPECT_EQ(fromRoman("MCMXCIV"), 1994);
}

TEST(FromRomanTest_1934, InvalidRomanNumerals_1934) {
    // Test for invalid Roman numerals
    EXPECT_EQ(fromRoman("IIII"), -1); // Invalid Roman numeral
    EXPECT_EQ(fromRoman("IC"), -1);   // Invalid Roman numeral
    EXPECT_EQ(fromRoman("VV"), -1);   // Invalid Roman numeral
}

TEST(FromRomanTest_1935, MixedCaseRomanNumerals_1935) {
    // Test for case insensitivity
    EXPECT_EQ(fromRoman("xv"), 15);
    EXPECT_EQ(fromRoman("Xv"), 15);
    EXPECT_EQ(fromRoman("IX"), 9);
    EXPECT_EQ(fromRoman("ix"), 9);
}

TEST(FromRomanTest_1936, EdgeCases_1936) {
    // Test for boundary cases
    EXPECT_EQ(fromRoman(""), 0); // Empty string
    EXPECT_EQ(fromRoman("I"), 1); // Smallest valid Roman numeral
    EXPECT_EQ(fromRoman("MMMCMXCIV"), 3994); // Largest valid Roman numeral under 4000
}

TEST(FromRomanTest_1937, InvalidCharacter_1937) {
    // Test for string with invalid characters
    EXPECT_EQ(fromRoman("123"), -1); // Invalid input with numbers
    EXPECT_EQ(fromRoman("ABC"), -1); // Invalid input with letters that are not Roman numerals
}

TEST(FromRomanTest_1938, BoundaryConditions_1938) {
    // Test for boundary conditions (e.g., maximum valid input)
    EXPECT_EQ(fromRoman("MMM"), 3000); // Upper limit case
}