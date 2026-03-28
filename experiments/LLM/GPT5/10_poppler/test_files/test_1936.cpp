#include <gtest/gtest.h>
#include "GooString.h"  // Assuming GooString is defined in this file

// Forward declaration of the function to be tested
static void toLatin(int number, GooString *str, bool uppercase);

// Test fixture for the function
class ToLatinTest_1936 : public ::testing::Test {
protected:
    GooString result;
};

// Test for normal operation with number 1 (should return "A" or "a")
TEST_F(ToLatinTest_1936, ConvertsOneToLatin_1936) {
    toLatin(1, &result, true);
    EXPECT_EQ(result.toStr(), "A");

    toLatin(1, &result, false);
    EXPECT_EQ(result.toStr(), "a");
}

// Test for normal operation with a number in the middle range (e.g., number 27, which should give "AA" or "aa")
TEST_F(ToLatinTest_1936, ConvertsNumberToLatin_1936) {
    toLatin(27, &result, true);
    EXPECT_EQ(result.toStr(), "AA");

    toLatin(27, &result, false);
    EXPECT_EQ(result.toStr(), "aa");
}

// Test for boundary conditions with number 26 (should return "Z" or "z")
TEST_F(ToLatinTest_1936, ConvertsZToLatin_1936) {
    toLatin(26, &result, true);
    EXPECT_EQ(result.toStr(), "Z");

    toLatin(26, &result, false);
    EXPECT_EQ(result.toStr(), "z");
}

// Test for boundary condition with a number beyond Z (e.g., number 52, should return "AZ" or "az")
TEST_F(ToLatinTest_1936, ConvertsBeyondZToLatin_1936) {
    toLatin(52, &result, true);
    EXPECT_EQ(result.toStr(), "AZ");

    toLatin(52, &result, false);
    EXPECT_EQ(result.toStr(), "az");
}

// Test for exceptional case where number is zero (although the behavior for zero isn't defined, we can test it for robustness)
TEST_F(ToLatinTest_1936, HandlesZeroInput_1936) {
    toLatin(0, &result, true);
    // Expect the function to not crash, result should remain empty or in an undefined state
    EXPECT_EQ(result.toStr(), "");
}

// Test for large number input (e.g., 703, which should return "AAA" or "aaa")
TEST_F(ToLatinTest_1936, HandlesLargeNumber_1936) {
    toLatin(703, &result, true);
    EXPECT_EQ(result.toStr(), "AAA");

    toLatin(703, &result, false);
    EXPECT_EQ(result.toStr(), "aaa");
}