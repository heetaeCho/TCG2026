#include <gtest/gtest.h>
#include <cstring>
#include "gmem.h"

// Test that copyString correctly copies a normal string
TEST(CopyStringTest_17, CopiesNormalString_17) {
    const char *original = "Hello, World!";
    char *copy = copyString(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy, original);
    EXPECT_NE(copy, original); // Must be a different pointer
    gfree(copy);
}

// Test that copyString correctly copies an empty string
TEST(CopyStringTest_17, CopiesEmptyString_17) {
    const char *original = "";
    char *copy = copyString(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy, "");
    EXPECT_EQ(std::strlen(copy), 0u);
    gfree(copy);
}

// Test that copyString correctly copies a single character string
TEST(CopyStringTest_17, CopiesSingleCharString_17) {
    const char *original = "A";
    char *copy = copyString(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy, "A");
    EXPECT_EQ(std::strlen(copy), 1u);
    gfree(copy);
}

// Test that copyString produces an independent copy (modifying copy doesn't affect original)
TEST(CopyStringTest_17, ProducesIndependentCopy_17) {
    const char *original = "Test String";
    char *copy = copyString(original);
    ASSERT_NE(copy, nullptr);
    copy[0] = 'X';
    EXPECT_EQ(original[0], 'T'); // Original should be unmodified
    EXPECT_EQ(copy[0], 'X');
    gfree(copy);
}

// Test that copyString correctly copies a string with special characters
TEST(CopyStringTest_17, CopiesStringWithSpecialChars_17) {
    const char *original = "Line1\nLine2\tTab\0Hidden";
    char *copy = copyString(original);
    ASSERT_NE(copy, nullptr);
    // copyString uses strlen, so it stops at the first null terminator
    EXPECT_STREQ(copy, "Line1\nLine2\tTab");
    gfree(copy);
}

// Test that copyString correctly copies a longer string
TEST(CopyStringTest_17, CopiesLongerString_17) {
    std::string longStr(1000, 'x');
    char *copy = copyString(longStr.c_str());
    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy, longStr.c_str());
    EXPECT_EQ(std::strlen(copy), 1000u);
    gfree(copy);
}

// Test that copyString includes null terminator
TEST(CopyStringTest_17, IncludesNullTerminator_17) {
    const char *original = "abc";
    char *copy = copyString(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy[3], '\0');
    gfree(copy);
}

// Test that copyString handles strings with embedded spaces
TEST(CopyStringTest_17, CopiesStringWithSpaces_17) {
    const char *original = "  spaces  everywhere  ";
    char *copy = copyString(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy, original);
    EXPECT_EQ(std::strlen(copy), std::strlen(original));
    gfree(copy);
}

// Test that multiple copies are independent
TEST(CopyStringTest_17, MultipleCopiesAreIndependent_17) {
    const char *original = "shared";
    char *copy1 = copyString(original);
    char *copy2 = copyString(original);
    ASSERT_NE(copy1, nullptr);
    ASSERT_NE(copy2, nullptr);
    EXPECT_NE(copy1, copy2); // Different allocations
    EXPECT_STREQ(copy1, copy2);
    copy1[0] = 'Z';
    EXPECT_NE(copy1[0], copy2[0]); // Modifying one doesn't affect the other
    gfree(copy1);
    gfree(copy2);
}

// Test copying a string containing only whitespace characters
TEST(CopyStringTest_17, CopiesWhitespaceOnlyString_17) {
    const char *original = " \t\n\r";
    char *copy = copyString(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy, original);
    EXPECT_EQ(std::strlen(copy), 4u);
    gfree(copy);
}
