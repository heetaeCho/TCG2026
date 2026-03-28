#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>

// Function to be tested
static char *setNextOffset(char *start, Goffset offset) {
    char buf[50];
    sprintf(buf, "%lld", offset);
    strcat(buf, " "); // add some padding
    char *p = strstr(start, "9999999999");
    if (p) {
        memcpy(p, buf, 10); // overwrite exact size
        p += 10;
    } else {
        return nullptr;
    }
    return p;
}

// Test Fixture class
class SetNextOffsetTest_1515 : public ::testing::Test {
protected:
    // Helper function for test setup
    void SetUp() override {
        // No specific setup needed
    }
};

// Normal Operation Test
TEST_F(SetNextOffsetTest_1515, NormalOperation_1515) {
    char str[] = "Some string with 9999999999 and more text.";
    Goffset offset = 12345;
    
    char* result = setNextOffset(str, offset);
    
    EXPECT_NE(result, nullptr);  // Ensure the result is not nullptr
    EXPECT_EQ(strncmp(str, "Some string with 12345 ", 23), 0);  // Check the first part of the string is updated correctly
    EXPECT_EQ(strncmp(result, "and more text.", 14), 0);  // Ensure the rest of the string remains unchanged
}

// Boundary Condition Test 1: When offset is 0
TEST_F(SetNextOffsetTest_1515, OffsetZero_1515) {
    char str[] = "Some string with 9999999999 and more text.";
    Goffset offset = 0;

    char* result = setNextOffset(str, offset);

    EXPECT_NE(result, nullptr);  // Ensure the result is not nullptr
    EXPECT_EQ(strncmp(str, "Some string with 0 ", 20), 0);  // Check if the offset 0 is correctly written
    EXPECT_EQ(strncmp(result, "and more text.", 14), 0);  // Ensure the rest of the string remains unchanged
}

// Boundary Condition Test 2: When offset is negative
TEST_F(SetNextOffsetTest_1515, OffsetNegative_1515) {
    char str[] = "Some string with 9999999999 and more text.";
    Goffset offset = -12345;

    char* result = setNextOffset(str, offset);

    EXPECT_NE(result, nullptr);  // Ensure the result is not nullptr
    EXPECT_EQ(strncmp(str, "Some string with -12345 ", 23), 0);  // Check if the negative offset is correctly written
    EXPECT_EQ(strncmp(result, "and more text.", 14), 0);  // Ensure the rest of the string remains unchanged
}

// Exceptional Case Test: When the substring "9999999999" is not present
TEST_F(SetNextOffsetTest_1515, NoMatchSubstring_1515) {
    char str[] = "Some string without the target number.";
    Goffset offset = 12345;

    char* result = setNextOffset(str, offset);

    EXPECT_EQ(result, nullptr);  // Ensure the result is nullptr when no match is found
}

// Boundary Case Test: When the string is exactly "9999999999"
TEST_F(SetNextOffsetTest_1515, ExactMatch_1515) {
    char str[] = "9999999999";
    Goffset offset = 12345;

    char* result = setNextOffset(str, offset);

    EXPECT_NE(result, nullptr);  // Ensure the result is not nullptr
    EXPECT_EQ(strncmp(str, "12345 ", 6), 0);  // Check if the offset is correctly written
}

// Edge Test Case: When the string contains the target number multiple times
TEST_F(SetNextOffsetTest_1515, MultipleMatches_1515) {
    char str[] = "9999999999 and some 9999999999 more 9999999999 text.";
    Goffset offset = 98765;

    char* result = setNextOffset(str, offset);

    EXPECT_NE(result, nullptr);  // Ensure the result is not nullptr
    EXPECT_EQ(strncmp(str, "98765 ", 6), 0);  // Check if the first occurrence of "9999999999" is replaced with the offset
    EXPECT_EQ(strncmp(result, " and some 9999999999 more 9999999999 text.", 41), 0);  // Ensure rest of the string is unchanged after the first match
}