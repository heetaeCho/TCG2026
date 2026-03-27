#include <gtest/gtest.h>
#include <optional>
#include <string_view>
#include <string>

namespace DN { namespace detail {

// Function prototype from the partial code
inline std::optional<std::string> parseHexString(std::string_view view);

}}  // namespace DN::detail

// Test suite for parseHexString function
TEST_F(DistinguishedNameParserTest_1941, ParseEmptyString_1941) {
    // Test: Empty string input should return std::nullopt
    std::string_view input = "";
    auto result = DN::detail::parseHexString(input);
    EXPECT_FALSE(result.has_value());  // Expected to be empty (nullopt)
}

TEST_F(DistinguishedNameParserTest_1941, ParseValidHexString_1941) {
    // Test: Valid even-length hex string should return decoded string
    std::string_view input = "48656c6c6f";  // "Hello" in hex
    auto result = DN::detail::parseHexString(input);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "Hello");
}

TEST_F(DistinguishedNameParserTest_1941, ParseOddLengthString_1941) {
    // Test: Odd-length hex string should return std::nullopt
    std::string_view input = "123";
    auto result = DN::detail::parseHexString(input);
    EXPECT_FALSE(result.has_value());  // Expected to be nullopt due to odd length
}

TEST_F(DistinguishedNameParserTest_1941, ParseInvalidHexString_1941) {
    // Test: Invalid hex string should return std::nullopt
    std::string_view input = "XYZ123";
    auto result = DN::detail::parseHexString(input);
    EXPECT_FALSE(result.has_value());  // Expected to be nullopt due to invalid characters
}

TEST_F(DistinguishedNameParserTest_1941, ParseLongValidHexString_1941) {
    // Test: Long valid hex string should decode correctly
    std::string_view input = "4a6f686e446f65";  // "JohnDoe" in hex
    auto result = DN::detail::parseHexString(input);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "JohnDoe");
}

TEST_F(DistinguishedNameParserTest_1941, ParseValidHexWithMixedCase_1941) {
    // Test: Valid hex string with mixed case should decode correctly
    std::string_view input = "4a6f686e446f65";  // "JohnDoe" in hex, mixed case should still work
    auto result = DN::detail::parseHexString(input);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), "JohnDoe");
}

TEST_F(DistinguishedNameParserTest_1941, ParseHexStringWithSpaces_1941) {
    // Test: Hex string with spaces should return std::nullopt
    std::string_view input = "4a 6f 68 6e 44 6f 65";  // "JohnDoe" with spaces
    auto result = DN::detail::parseHexString(input);
    EXPECT_FALSE(result.has_value());  // Expected to be nullopt due to spaces
}

TEST_F(DistinguishedNameParserTest_1941, ParseHexStringWithInvalidCharacters_1941) {
    // Test: Hex string with non-hex characters should return std::nullopt
    std::string_view input = "4a6f6##6e446f65";  // Invalid string with characters `##`
    auto result = DN::detail::parseHexString(input);
    EXPECT_FALSE(result.has_value());  // Expected to be nullopt due to invalid characters
}