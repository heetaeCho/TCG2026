#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "goo/gbase64.h"

class Gbase64Test_34 : public ::testing::Test {
protected:
};

// Test encoding an empty vector returns an empty string
TEST_F(Gbase64Test_34, EmptyInputReturnsEmptyString_34) {
    std::vector<char> input;
    std::string result = gbase64Encode(input);
    EXPECT_TRUE(result.empty());
}

// Test encoding a single byte
TEST_F(Gbase64Test_34, SingleByteEncoding_34) {
    std::vector<char> input = {'A'};
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "QQ==");
}

// Test encoding two bytes (padding with one '=')
TEST_F(Gbase64Test_34, TwoBytesEncoding_34) {
    std::vector<char> input = {'A', 'B'};
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "QUI=");
}

// Test encoding three bytes (no padding needed)
TEST_F(Gbase64Test_34, ThreeBytesNoPadding_34) {
    std::vector<char> input = {'A', 'B', 'C'};
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "QUJD");
}

// Test encoding the classic "Hello" string
TEST_F(Gbase64Test_34, HelloEncoding_34) {
    std::string hello = "Hello";
    std::vector<char> input(hello.begin(), hello.end());
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "SGVsbG8=");
}

// Test encoding "Hello, World!"
TEST_F(Gbase64Test_34, HelloWorldEncoding_34) {
    std::string hw = "Hello, World!";
    std::vector<char> input(hw.begin(), hw.end());
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "SGVsbG8sIFdvcmxkIQ==");
}

// Test encoding "Man" — classic base64 example
TEST_F(Gbase64Test_34, ManEncoding_34) {
    std::string s = "Man";
    std::vector<char> input(s.begin(), s.end());
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "TWFu");
}

// Test encoding "Ma" — classic base64 example with one pad
TEST_F(Gbase64Test_34, MaEncoding_34) {
    std::string s = "Ma";
    std::vector<char> input(s.begin(), s.end());
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "TWE=");
}

// Test encoding "M" — classic base64 example with two pads
TEST_F(Gbase64Test_34, MEncoding_34) {
    std::string s = "M";
    std::vector<char> input(s.begin(), s.end());
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "TQ==");
}

// Test encoding binary data with null bytes
TEST_F(Gbase64Test_34, BinaryDataWithNullBytes_34) {
    std::vector<char> input = {'\0', '\0', '\0'};
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "AAAA");
}

// Test encoding binary data with all 0xFF bytes
TEST_F(Gbase64Test_34, AllOnesBytes_34) {
    std::vector<char> input = {static_cast<char>(0xFF), static_cast<char>(0xFF), static_cast<char>(0xFF)};
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "////");
}

// Test encoding a single null byte
TEST_F(Gbase64Test_34, SingleNullByte_34) {
    std::vector<char> input = {'\0'};
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "AA==");
}

// Test encoding four bytes
TEST_F(Gbase64Test_34, FourBytesEncoding_34) {
    std::vector<char> input = {'A', 'B', 'C', 'D'};
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "QUJDRA==");
}

// Test encoding six bytes (exact multiple of 3)
TEST_F(Gbase64Test_34, SixBytesExactMultiple_34) {
    std::vector<char> input = {'A', 'B', 'C', 'D', 'E', 'F'};
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "QUJDREVG");
}

// Test encoding a longer string
TEST_F(Gbase64Test_34, LongerStringEncoding_34) {
    std::string s = "The quick brown fox jumps over the lazy dog";
    std::vector<char> input(s.begin(), s.end());
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw==");
}

// Test result is non-empty for non-empty input
TEST_F(Gbase64Test_34, NonEmptyInputProducesNonEmptyOutput_34) {
    std::vector<char> input = {'x'};
    std::string result = gbase64Encode(input);
    EXPECT_FALSE(result.empty());
}

// Test that output length is correct (base64 output length should be ceil(n/3)*4)
TEST_F(Gbase64Test_34, OutputLengthCorrect_34) {
    for (size_t len = 1; len <= 12; ++len) {
        std::vector<char> input(len, 'A');
        std::string result = gbase64Encode(input);
        size_t expected_len = ((len + 2) / 3) * 4;
        EXPECT_EQ(result.size(), expected_len) << "Failed for input length " << len;
    }
}

// Test encoding with various byte values 0x00-0x05
TEST_F(Gbase64Test_34, SequentialBytesEncoding_34) {
    std::vector<char> input = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "AAECAwQF");
}
