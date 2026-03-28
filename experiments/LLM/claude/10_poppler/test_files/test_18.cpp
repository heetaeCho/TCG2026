#include <gtest/gtest.h>
#include <cstring>
#include <cstdlib>
#include "gmem.h"

// Test normal operation: copying a simple string with its full length
TEST(CopyStringTest_18, CopiesFullString_18) {
    const char *original = "Hello, World!";
    size_t len = std::strlen(original);
    char *result = copyString(original, len);
    
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, original);
    EXPECT_EQ(std::strlen(result), len);
    
    gfree(result);
}

// Test copying a partial string (fewer characters than the full length)
TEST(CopyStringTest_18, CopiesPartialString_18) {
    const char *original = "Hello, World!";
    size_t n = 5;
    char *result = copyString(original, n);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(std::strlen(result), n);
    EXPECT_EQ(std::strncmp(result, "Hello", n), 0);
    EXPECT_EQ(result[n], '\0');
    
    gfree(result);
}

// Test boundary: copying zero characters
TEST(CopyStringTest_18, CopiesZeroCharacters_18) {
    const char *original = "Hello";
    char *result = copyString(original, 0);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], '\0');
    EXPECT_EQ(std::strlen(result), 0u);
    
    gfree(result);
}

// Test copying a single character
TEST(CopyStringTest_18, CopiesSingleCharacter_18) {
    const char *original = "A";
    char *result = copyString(original, 1);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], 'A');
    EXPECT_EQ(result[1], '\0');
    EXPECT_EQ(std::strlen(result), 1u);
    
    gfree(result);
}

// Test that the result is null-terminated even when n is less than string length
TEST(CopyStringTest_18, ResultIsNullTerminated_18) {
    const char *original = "ABCDEFGHIJ";
    size_t n = 3;
    char *result = copyString(original, n);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[n], '\0');
    EXPECT_EQ(std::strlen(result), n);
    
    gfree(result);
}

// Test that the returned string is a separate copy (not aliasing the original)
TEST(CopyStringTest_18, ReturnsSeparateCopy_18) {
    const char *original = "Test";
    size_t len = std::strlen(original);
    char *result = copyString(original, len);
    
    ASSERT_NE(result, nullptr);
    EXPECT_NE(result, original);
    EXPECT_STREQ(result, original);
    
    gfree(result);
}

// Test copying a string with embedded special characters
TEST(CopyStringTest_18, CopiesStringWithSpecialChars_18) {
    const char *original = "Hello\tWorld\n!";
    size_t len = std::strlen(original);
    char *result = copyString(original, len);
    
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, original);
    EXPECT_EQ(std::strlen(result), len);
    
    gfree(result);
}

// Test copying a longer string
TEST(CopyStringTest_18, CopiesLongerString_18) {
    const char *original = "This is a somewhat longer string used for testing the copyString function.";
    size_t len = std::strlen(original);
    char *result = copyString(original, len);
    
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, original);
    EXPECT_EQ(std::strlen(result), len);
    
    gfree(result);
}

// Test that copying with n equal to string length gives exact copy
TEST(CopyStringTest_18, CopyWithExactLength_18) {
    const char *original = "Exact";
    size_t len = std::strlen(original);
    char *result = copyString(original, len);
    
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Exact");
    EXPECT_EQ(result[len], '\0');
    
    gfree(result);
}

// Test copying a string containing spaces
TEST(CopyStringTest_18, CopiesStringWithSpaces_18) {
    const char *original = "   spaces   ";
    size_t len = std::strlen(original);
    char *result = copyString(original, len);
    
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, original);
    
    gfree(result);
}

// Test that modifying the copy does not affect original-like behavior
TEST(CopyStringTest_18, ModifyingCopyDoesNotAffectOriginal_18) {
    char original[] = "Mutable";
    size_t len = std::strlen(original);
    char *result = copyString(original, len);
    
    ASSERT_NE(result, nullptr);
    result[0] = 'X';
    EXPECT_EQ(original[0], 'M');
    EXPECT_EQ(result[0], 'X');
    
    gfree(result);
}
