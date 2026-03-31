#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "gbase64.h"

// Test empty input returns empty string
TEST(Gbase64EncodeTest_35, EmptyInputReturnsEmptyString_35) {
    std::vector<unsigned char> input;
    std::string result = gbase64Encode(input);
    EXPECT_TRUE(result.empty());
}

// Test single byte input
TEST(Gbase64EncodeTest_35, SingleByteInput_35) {
    std::vector<unsigned char> input = { 'A' };
    std::string result = gbase64Encode(input);
    EXPECT_FALSE(result.empty());
    // Base64 of 'A' (0x41) is "QQ=="
    EXPECT_EQ(result, "QQ==");
}

// Test two byte input
TEST(Gbase64EncodeTest_35, TwoByteInput_35) {
    std::vector<unsigned char> input = { 'A', 'B' };
    std::string result = gbase64Encode(input);
    // Base64 of "AB" is "QUI="
    EXPECT_EQ(result, "QUI=");
}

// Test three byte input (no padding needed)
TEST(Gbase64EncodeTest_35, ThreeByteInputNoPadding_35) {
    std::vector<unsigned char> input = { 'A', 'B', 'C' };
    std::string result = gbase64Encode(input);
    // Base64 of "ABC" is "QUJD"
    EXPECT_EQ(result, "QUJD");
}

// Test well-known string "Hello, World!"
TEST(Gbase64EncodeTest_35, HelloWorldEncoding_35) {
    std::string str = "Hello, World!";
    std::vector<unsigned char> input(str.begin(), str.end());
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "SGVsbG8sIFdvcmxkIQ==");
}

// Test encoding of "Man"
TEST(Gbase64EncodeTest_35, ManEncoding_35) {
    std::string str = "Man";
    std::vector<unsigned char> input(str.begin(), str.end());
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "TWFu");
}

// Test encoding of "Ma"
TEST(Gbase64EncodeTest_35, MaEncoding_35) {
    std::string str = "Ma";
    std::vector<unsigned char> input(str.begin(), str.end());
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "TWE=");
}

// Test encoding of "M"
TEST(Gbase64EncodeTest_35, MEncoding_35) {
    std::string str = "M";
    std::vector<unsigned char> input(str.begin(), str.end());
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "TQ==");
}

// Test binary data with null bytes
TEST(Gbase64EncodeTest_35, BinaryDataWithNullBytes_35) {
    std::vector<unsigned char> input = { 0x00, 0x00, 0x00 };
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "AAAA");
}

// Test all 0xFF bytes
TEST(Gbase64EncodeTest_35, AllFFBytes_35) {
    std::vector<unsigned char> input = { 0xFF, 0xFF, 0xFF };
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "////");
}

// Test single null byte
TEST(Gbase64EncodeTest_35, SingleNullByte_35) {
    std::vector<unsigned char> input = { 0x00 };
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "AA==");
}

// Test longer input - "The quick brown fox jumps over the lazy dog"
TEST(Gbase64EncodeTest_35, LongerStringEncoding_35) {
    std::string str = "The quick brown fox jumps over the lazy dog";
    std::vector<unsigned char> input(str.begin(), str.end());
    std::string result = gbase64Encode(input);
    EXPECT_EQ(result, "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw==");
}

// Test encoding produces valid base64 characters only
TEST(Gbase64EncodeTest_35, OutputContainsOnlyValidBase64Characters_35) {
    std::vector<unsigned char> input = { 0x14, 0xFB, 0x9C, 0x03, 0xD9, 0x7E };
    std::string result = gbase64Encode(input);
    EXPECT_FALSE(result.empty());
    const std::string validChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    for (char c : result) {
        EXPECT_NE(validChars.find(c), std::string::npos) << "Invalid base64 character: " << c;
    }
}

// Test that output length is a multiple of 4
TEST(Gbase64EncodeTest_35, OutputLengthIsMultipleOfFour_35) {
    for (size_t len = 1; len <= 10; ++len) {
        std::vector<unsigned char> input(len, 'X');
        std::string result = gbase64Encode(input);
        EXPECT_EQ(result.size() % 4, 0u) << "For input length " << len << ", output length " << result.size() << " is not a multiple of 4";
    }
}

// Test encoding of "foobar" and its substrings (RFC 4648 test vectors)
TEST(Gbase64EncodeTest_35, RFC4648TestVectors_35) {
    {
        std::string str = "f";
        std::vector<unsigned char> input(str.begin(), str.end());
        EXPECT_EQ(gbase64Encode(input), "Zg==");
    }
    {
        std::string str = "fo";
        std::vector<unsigned char> input(str.begin(), str.end());
        EXPECT_EQ(gbase64Encode(input), "Zm8=");
    }
    {
        std::string str = "foo";
        std::vector<unsigned char> input(str.begin(), str.end());
        EXPECT_EQ(gbase64Encode(input), "Zm9v");
    }
    {
        std::string str = "foob";
        std::vector<unsigned char> input(str.begin(), str.end());
        EXPECT_EQ(gbase64Encode(input), "Zm9vYg==");
    }
    {
        std::string str = "fooba";
        std::vector<unsigned char> input(str.begin(), str.end());
        EXPECT_EQ(gbase64Encode(input), "Zm9vYmE=");
    }
    {
        std::string str = "foobar";
        std::vector<unsigned char> input(str.begin(), str.end());
        EXPECT_EQ(gbase64Encode(input), "Zm9vYmFy");
    }
}
