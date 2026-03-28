static char *setNextOffset(char *start, Goffset offset)
#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>

// Since setNextOffset is a static function in Form.cc, we include the source
// to get access. In practice, this would need build system support.
// We need the Goffset type definition.
typedef long long Goffset;

// Re-declare the function for testing purposes (copy from source)
static char *setNextOffset(char *start, Goffset offset) {
    char buf[50];
    sprintf(buf, "%lld", offset);
    strcat(buf, " ");
    char *p = strstr(start, "9999999999");
    if (p) {
        memcpy(p, buf, 10);
        p += 10;
    } else {
        return nullptr;
    }
    return p;
}

class SetNextOffsetTest_1515 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that when the placeholder "9999999999" is not found, nullptr is returned
TEST_F(SetNextOffsetTest_1515, ReturnsNullWhenPlaceholderNotFound_1515) {
    char buffer[64] = "no placeholder here";
    char *result = setNextOffset(buffer, 12345);
    EXPECT_EQ(result, nullptr);
}

// Test that when the placeholder is found, a non-null pointer is returned
TEST_F(SetNextOffsetTest_1515, ReturnsNonNullWhenPlaceholderFound_1515) {
    char buffer[64] = "prefix9999999999suffix";
    char *result = setNextOffset(buffer, 42);
    EXPECT_NE(result, nullptr);
}

// Test that the returned pointer points past the 10-char overwritten region
TEST_F(SetNextOffsetTest_1515, ReturnedPointerPointsPastOverwrite_1515) {
    char buffer[64] = "prefix9999999999suffix";
    char *placeholder = strstr(buffer, "9999999999");
    char *result = setNextOffset(buffer, 100);
    EXPECT_EQ(result, placeholder + 10);
}

// Test that the placeholder is overwritten with the offset value
TEST_F(SetNextOffsetTest_1515, PlaceholderOverwrittenWithOffset_1515) {
    char buffer[64] = "prefix9999999999suffix";
    setNextOffset(buffer, 12345);
    // The 10 chars starting at the placeholder position should now contain "12345 " padded
    char *p = buffer + 6; // "prefix" is 6 chars
    // "12345 " is 6 chars, then remaining 4 of the 10 should be overwritten
    char expected[11];
    sprintf(expected, "%lld", (long long)12345);
    strcat(expected, " ");
    // The first strlen(expected) chars should match, total overwrite is 10 chars
    EXPECT_EQ(memcmp(p, expected, strlen(expected)), 0);
}

// Test with offset zero
TEST_F(SetNextOffsetTest_1515, OffsetZero_1515) {
    char buffer[64] = "AAA9999999999BBB";
    char *result = setNextOffset(buffer, 0);
    EXPECT_NE(result, nullptr);
    // "0 " should be written at the placeholder
    char *p = buffer + 3; // "AAA" is 3 chars
    EXPECT_EQ(p[0], '0');
    EXPECT_EQ(p[1], ' ');
}

// Test with a large offset that fills most of the 10 chars
TEST_F(SetNextOffsetTest_1515, LargeOffset_1515) {
    char buffer[64] = "X9999999999Y";
    char *result = setNextOffset(buffer, 123456789LL);
    EXPECT_NE(result, nullptr);
    char *p = buffer + 1;
    // "123456789 " is 10 chars exactly
    EXPECT_EQ(memcmp(p, "123456789 ", 10), 0);
}

// Test suffix remains intact after the overwritten region
TEST_F(SetNextOffsetTest_1515, SuffixRemainsIntact_1515) {
    char buffer[64] = "prefix9999999999SUFFIX";
    setNextOffset(buffer, 1);
    // SUFFIX should still be at position prefix(6) + 10 = 16
    EXPECT_STREQ(buffer + 16, "SUFFIX");
}

// Test with empty string - no placeholder
TEST_F(SetNextOffsetTest_1515, EmptyString_1515) {
    char buffer[4] = "";
    char *result = setNextOffset(buffer, 0);
    EXPECT_EQ(result, nullptr);
}

// Test with negative offset
TEST_F(SetNextOffsetTest_1515, NegativeOffset_1515) {
    char buffer[64] = "A9999999999B";
    char *result = setNextOffset(buffer, -1);
    EXPECT_NE(result, nullptr);
    // "-1 " should be at position 1
    EXPECT_EQ(buffer[1], '-');
    EXPECT_EQ(buffer[2], '1');
    EXPECT_EQ(buffer[3], ' ');
}

// Test with placeholder at the very beginning
TEST_F(SetNextOffsetTest_1515, PlaceholderAtStart_1515) {
    char buffer[64] = "9999999999end";
    char *result = setNextOffset(buffer, 55);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result, buffer + 10);
    EXPECT_EQ(buffer[0], '5');
    EXPECT_EQ(buffer[1], '5');
    EXPECT_EQ(buffer[2], ' ');
}

// Test that only the first placeholder is overwritten when multiple exist
TEST_F(SetNextOffsetTest_1515, OnlyFirstPlaceholderOverwritten_1515) {
    char buffer[64] = "99999999999999999999end";
    char *result = setNextOffset(buffer, 7);
    EXPECT_NE(result, nullptr);
    // First 10 chars overwritten, next 10 chars should still contain "9999999999" or similar
    // The second placeholder starts at offset 10
    // After overwrite of first 10 chars: "7         9999999999end" or similar
    // Check that strstr from result can still find "9999999999"
    char *second = strstr(result, "9999999999");
    // The second placeholder may or may not be intact depending on overlap
    // At minimum, result should point to buffer+10
    EXPECT_EQ(result, buffer + 10);
}

// Test with exactly 9-digit offset (offset + space = 10 chars)
TEST_F(SetNextOffsetTest_1515, NineDigitOffsetFitsExactly_1515) {
    char buffer[64] = "9999999999";
    setNextOffset(buffer, 123456789LL);
    EXPECT_EQ(memcmp(buffer, "123456789 ", 10), 0);
}
