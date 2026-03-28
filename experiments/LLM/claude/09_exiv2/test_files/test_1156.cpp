#include <gtest/gtest.h>
#include "types.hpp"

// Test ID: 1156

class ExvGettextTest_1156 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that exvGettext returns a non-null pointer for a valid input string
TEST_F(ExvGettextTest_1156, ReturnsNonNullForValidString_1156) {
    const char* input = "Hello";
    const char* result = Exiv2::exvGettext(input);
    ASSERT_NE(result, nullptr);
}

// Test that exvGettext returns the same pointer or equivalent string for a simple string
// When NLS is not enabled, the function should return the input string as-is
TEST_F(ExvGettextTest_1156, ReturnsInputStringWhenNoTranslation_1156) {
    const char* input = "Some untranslatable test string 12345";
    const char* result = Exiv2::exvGettext(input);
    ASSERT_NE(result, nullptr);
    // The result should at minimum contain the same content as input
    // (either the same pointer or a translated version)
    // For strings without translation, it should return the original
    EXPECT_STREQ(result, input);
}

// Test with an empty string
TEST_F(ExvGettextTest_1156, HandlesEmptyString_1156) {
    const char* input = "";
    const char* result = Exiv2::exvGettext(input);
    ASSERT_NE(result, nullptr);
    // Empty string may return metadata in some gettext implementations,
    // but we just verify it doesn't crash and returns non-null
}

// Test that calling exvGettext multiple times returns consistent results
TEST_F(ExvGettextTest_1156, ConsistentResultsOnMultipleCalls_1156) {
    const char* input = "Consistent test string xyz";
    const char* result1 = Exiv2::exvGettext(input);
    const char* result2 = Exiv2::exvGettext(input);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result1, result2);
}

// Test with a string containing special characters
TEST_F(ExvGettextTest_1156, HandlesSpecialCharacters_1156) {
    const char* input = "Special chars: !@#$%^&*()_+-=[]{}|;':\",./<>?";
    const char* result = Exiv2::exvGettext(input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, input);
}

// Test with a longer string
TEST_F(ExvGettextTest_1156, HandlesLongString_1156) {
    const char* input = "This is a relatively long string that is used to test whether exvGettext "
                        "can handle strings of various lengths without any issues. It should "
                        "return the string as-is if no translation is available.";
    const char* result = Exiv2::exvGettext(input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, input);
}

// Test with a single character string
TEST_F(ExvGettextTest_1156, HandlesSingleCharString_1156) {
    const char* input = "X";
    const char* result = Exiv2::exvGettext(input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, input);
}

// Test with a string containing newlines and whitespace
TEST_F(ExvGettextTest_1156, HandlesWhitespaceAndNewlines_1156) {
    const char* input = "Line1\nLine2\tTabbed\r\nWindows line ending";
    const char* result = Exiv2::exvGettext(input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, input);
}

// Test with UTF-8 content
TEST_F(ExvGettextTest_1156, HandlesUTF8Content_1156) {
    const char* input = "UTF-8 content: \xC3\xA9\xC3\xA8\xC3\xAA";  // éèê in UTF-8
    const char* result = Exiv2::exvGettext(input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, input);
}

// Test that the function is idempotent (calling it on its own result gives the same result)
TEST_F(ExvGettextTest_1156, IdempotentBehavior_1156) {
    const char* input = "Idempotent test string 999";
    const char* result1 = Exiv2::exvGettext(input);
    const char* result2 = Exiv2::exvGettext(result1);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result1, result2);
}

// Test with a string containing null-like patterns (but still valid C string)
TEST_F(ExvGettextTest_1156, HandlesStringWithEscapedZeros_1156) {
    const char* input = "before\\0after";
    const char* result = Exiv2::exvGettext(input);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, input);
}

// Test calling the function from different "contexts" to ensure initialization is stable
TEST_F(ExvGettextTest_1156, StableAfterMultipleInvocations_1156) {
    for (int i = 0; i < 100; ++i) {
        const char* input = "Stability test string";
        const char* result = Exiv2::exvGettext(input);
        ASSERT_NE(result, nullptr);
        EXPECT_STREQ(result, input);
    }
}
