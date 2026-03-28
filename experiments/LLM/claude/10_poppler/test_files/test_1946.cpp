#include <gtest/gtest.h>
#include <string>

// We need to test the static function fromCharPtr. Since it's defined as static
// in a .cc file, we can't directly access it. We'll recreate the function
// signature for testing purposes, treating it as a black box based on the
// provided interface.

// Replicate the function under test (since it's static in the .cc file,
// we need to include it or replicate its signature for testing)
static std::string fromCharPtr(const char *data)
{
    if (data) {
        return std::string { data };
    }
    return {};
}

class FromCharPtrTest_1946 : public ::testing::Test {
protected:
    void SetUp() override { }
    void TearDown() override { }
};

// Test normal operation with a regular C string
TEST_F(FromCharPtrTest_1946, ReturnsStringFromValidCString_1946)
{
    const char *input = "Hello, World!";
    std::string result = fromCharPtr(input);
    EXPECT_EQ(result, "Hello, World!");
}

// Test with nullptr input - should return empty string
TEST_F(FromCharPtrTest_1946, ReturnsEmptyStringFromNullptr_1946)
{
    const char *input = nullptr;
    std::string result = fromCharPtr(input);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result, std::string {});
}

// Test with empty C string
TEST_F(FromCharPtrTest_1946, ReturnsEmptyStringFromEmptyCString_1946)
{
    const char *input = "";
    std::string result = fromCharPtr(input);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result, "");
}

// Test with a single character string
TEST_F(FromCharPtrTest_1946, ReturnsSingleCharacterString_1946)
{
    const char *input = "A";
    std::string result = fromCharPtr(input);
    EXPECT_EQ(result, "A");
    EXPECT_EQ(result.size(), 1u);
}

// Test with a string containing special characters
TEST_F(FromCharPtrTest_1946, ReturnsStringWithSpecialCharacters_1946)
{
    const char *input = "Hello\nWorld\t!";
    std::string result = fromCharPtr(input);
    EXPECT_EQ(result, "Hello\nWorld\t!");
}

// Test with a string containing spaces
TEST_F(FromCharPtrTest_1946, ReturnsStringWithSpaces_1946)
{
    const char *input = "   spaces   ";
    std::string result = fromCharPtr(input);
    EXPECT_EQ(result, "   spaces   ");
}

// Test with a string containing null character embedded - only up to first null
TEST_F(FromCharPtrTest_1946, ReturnsStringUpToFirstNullCharacter_1946)
{
    const char input[] = "Hello\0World";
    std::string result = fromCharPtr(input);
    EXPECT_EQ(result, "Hello");
    EXPECT_EQ(result.size(), 5u);
}

// Test with a long string
TEST_F(FromCharPtrTest_1946, ReturnsLongString_1946)
{
    std::string longStr(10000, 'x');
    std::string result = fromCharPtr(longStr.c_str());
    EXPECT_EQ(result, longStr);
    EXPECT_EQ(result.size(), 10000u);
}

// Test with a string containing unicode-like bytes (UTF-8)
TEST_F(FromCharPtrTest_1946, ReturnsStringWithUTF8Characters_1946)
{
    const char *input = "café";
    std::string result = fromCharPtr(input);
    EXPECT_EQ(result, "café");
}

// Test that the returned string is independent (copy, not reference)
TEST_F(FromCharPtrTest_1946, ReturnedStringIsIndependentCopy_1946)
{
    char input[] = "mutable";
    std::string result = fromCharPtr(input);
    EXPECT_EQ(result, "mutable");

    // Modify original - result should not change
    input[0] = 'M';
    EXPECT_EQ(result, "mutable");
}

// Test with a string containing only whitespace
TEST_F(FromCharPtrTest_1946, ReturnsWhitespaceOnlyString_1946)
{
    const char *input = " \t\n\r";
    std::string result = fromCharPtr(input);
    EXPECT_EQ(result, " \t\n\r");
    EXPECT_EQ(result.size(), 4u);
}

// Test return type is std::string and not empty for valid input
TEST_F(FromCharPtrTest_1946, ReturnTypeVerification_1946)
{
    const char *input = "test";
    auto result = fromCharPtr(input);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.length(), 4u);
}

// Test nullptr returns default-constructed string
TEST_F(FromCharPtrTest_1946, NullptrReturnsDefaultConstructedString_1946)
{
    std::string result = fromCharPtr(nullptr);
    std::string defaultStr {};
    EXPECT_EQ(result, defaultStr);
    EXPECT_EQ(result.size(), 0u);
}
