#include <gtest/gtest.h>
#include <vector>
#include <string>

namespace YAML {
std::vector<unsigned char> DecodeBase64(const std::string &input);
}

// Test empty input returns empty vector
TEST(DecodeBase64Test_545, EmptyInput_545) {
    auto result = YAML::DecodeBase64("");
    EXPECT_TRUE(result.empty());
}

// Test decoding a simple base64 string "TWFu" -> "Man"
TEST(DecodeBase64Test_545, DecodeMan_545) {
    auto result = YAML::DecodeBase64("TWFu");
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 'M');
    EXPECT_EQ(result[1], 'a');
    EXPECT_EQ(result[2], 'n');
}

// Test decoding with one padding character "TWE=" -> "Ma"
TEST(DecodeBase64Test_545, DecodeWithOnePadding_545) {
    auto result = YAML::DecodeBase64("TWE=");
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], 'M');
    EXPECT_EQ(result[1], 'a');
}

// Test decoding with two padding characters "TQ==" -> "M"
TEST(DecodeBase64Test_545, DecodeWithTwoPadding_545) {
    auto result = YAML::DecodeBase64("TQ==");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 'M');
}

// Test decoding "SGVsbG8gV29ybGQ=" -> "Hello World"
TEST(DecodeBase64Test_545, DecodeHelloWorld_545) {
    auto result = YAML::DecodeBase64("SGVsbG8gV29ybGQ=");
    std::string decoded(result.begin(), result.end());
    EXPECT_EQ(decoded, "Hello World");
}

// Test decoding "QUJD" -> "ABC"
TEST(DecodeBase64Test_545, DecodeABC_545) {
    auto result = YAML::DecodeBase64("QUJD");
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 'A');
    EXPECT_EQ(result[1], 'B');
    EXPECT_EQ(result[2], 'C');
}

// Test that whitespace in the input is ignored
TEST(DecodeBase64Test_545, WhitespaceIgnored_545) {
    auto result = YAML::DecodeBase64("T W F u");
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 'M');
    EXPECT_EQ(result[1], 'a');
    EXPECT_EQ(result[2], 'n');
}

// Test that newlines are ignored
TEST(DecodeBase64Test_545, NewlinesIgnored_545) {
    auto result = YAML::DecodeBase64("TWFu\nQUJD");
    ASSERT_EQ(result.size(), 6u);
    EXPECT_EQ(result[0], 'M');
    EXPECT_EQ(result[1], 'a');
    EXPECT_EQ(result[2], 'n');
    EXPECT_EQ(result[3], 'A');
    EXPECT_EQ(result[4], 'B');
    EXPECT_EQ(result[5], 'C');
}

// Test invalid character returns empty vector
TEST(DecodeBase64Test_545, InvalidCharacterReturnsEmpty_545) {
    auto result = YAML::DecodeBase64("TW!u");
    EXPECT_TRUE(result.empty());
}

// Test another invalid character
TEST(DecodeBase64Test_545, InvalidCharacterHash_545) {
    auto result = YAML::DecodeBase64("TW#u");
    EXPECT_TRUE(result.empty());
}

// Test decoding "AAAA" -> three zero bytes
TEST(DecodeBase64Test_545, DecodeAllZeros_545) {
    auto result = YAML::DecodeBase64("AAAA");
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], 0);
}

// Test decoding "////" -> three bytes of 0xFF
TEST(DecodeBase64Test_545, DecodeAllOnes_545) {
    auto result = YAML::DecodeBase64("////");
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 0xFF);
    EXPECT_EQ(result[1], 0xFF);
    EXPECT_EQ(result[2], 0xFF);
}

// Test decoding with + character (base64 value 62)
TEST(DecodeBase64Test_545, DecodePlusCharacter_545) {
    auto result = YAML::DecodeBase64("++++");
    ASSERT_EQ(result.size(), 3u);
    // + maps to 62 = 0x3E
    // value = (62 << 18) | (62 << 12) | (62 << 6) | 62
    // = 0x0F8F8F8 + 62 ... let's just check it's non-empty and correct size
    // 62,62,62,62 -> binary: 111110 111110 111110 111110
    // bytes: 11111011 11101111 10111110 = 0xFB 0xEF 0xBE
    EXPECT_EQ(result[0], 0xFB);
    EXPECT_EQ(result[1], 0xEF);
    EXPECT_EQ(result[2], 0xBE);
}

// Test longer string: "SGVsbG8=" -> "Hello"
TEST(DecodeBase64Test_545, DecodeHello_545) {
    auto result = YAML::DecodeBase64("SGVsbG8=");
    std::string decoded(result.begin(), result.end());
    EXPECT_EQ(decoded, "Hello");
}

// Test decoding with tabs as whitespace
TEST(DecodeBase64Test_545, TabsIgnored_545) {
    auto result = YAML::DecodeBase64("\tTWFu\t");
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 'M');
    EXPECT_EQ(result[1], 'a');
    EXPECT_EQ(result[2], 'n');
}

// Test with only whitespace input - should not have complete quads, returns empty
TEST(DecodeBase64Test_545, OnlyWhitespace_545) {
    auto result = YAML::DecodeBase64("   \n\t  ");
    EXPECT_TRUE(result.empty());
}

// Test multiple groups: "TWFuTWFu" -> "ManMan"
TEST(DecodeBase64Test_545, MultipleGroups_545) {
    auto result = YAML::DecodeBase64("TWFuTWFu");
    ASSERT_EQ(result.size(), 6u);
    std::string decoded(result.begin(), result.end());
    EXPECT_EQ(decoded, "ManMan");
}

// Test single character with invalid base64 char at position
TEST(DecodeBase64Test_545, InvalidAtSign_545) {
    auto result = YAML::DecodeBase64("@@@@");
    EXPECT_TRUE(result.empty());
}

// Test encoding of binary data: base64 "AQID" -> {1, 2, 3}
TEST(DecodeBase64Test_545, DecodeBinaryData_545) {
    auto result = YAML::DecodeBase64("AQID");
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
}

// Test decoding "YQ==" -> "a"
TEST(DecodeBase64Test_545, DecodeSingleChar_a_545) {
    auto result = YAML::DecodeBase64("YQ==");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 'a');
}

// Test decoding "YWI=" -> "ab"
TEST(DecodeBase64Test_545, DecodeTwoChars_ab_545) {
    auto result = YAML::DecodeBase64("YWI=");
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], 'a');
    EXPECT_EQ(result[1], 'b');
}

// Test decoding "YWJj" -> "abc"
TEST(DecodeBase64Test_545, DecodeThreeChars_abc_545) {
    auto result = YAML::DecodeBase64("YWJj");
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 'a');
    EXPECT_EQ(result[1], 'b');
    EXPECT_EQ(result[2], 'c');
}

// Test that digits 0-9 are valid base64 characters
TEST(DecodeBase64Test_545, DigitsAreValid_545) {
    // "MDEyMzQ1Njc4OQ==" -> "0123456789"
    auto result = YAML::DecodeBase64("MDEyMzQ1Njc4OQ==");
    std::string decoded(result.begin(), result.end());
    EXPECT_EQ(decoded, "0123456789");
}

// Test carriage return is also treated as whitespace
TEST(DecodeBase64Test_545, CarriageReturnIgnored_545) {
    auto result = YAML::DecodeBase64("TW\rFu");
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 'M');
    EXPECT_EQ(result[1], 'a');
    EXPECT_EQ(result[2], 'n');
}
