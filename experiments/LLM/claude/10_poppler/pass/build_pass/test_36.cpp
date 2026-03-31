#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

// Declaration of the function under test
std::string gbase64Encode(const void *input, size_t len);

class Gbase64EncodeTest_36 : public ::testing::Test {
protected:
};

// Test encoding an empty input
TEST_F(Gbase64EncodeTest_36, EmptyInput_36) {
    std::string result = gbase64Encode("", 0);
    EXPECT_EQ(result, "");
}

// Test encoding a single byte (padding case: 1 remaining byte)
TEST_F(Gbase64EncodeTest_36, SingleByte_36) {
    // 'M' = 0x4D -> base64 "TQ=="
    const char input[] = "M";
    std::string result = gbase64Encode(input, 1);
    EXPECT_EQ(result, "TQ==");
}

// Test encoding two bytes (padding case: 2 remaining bytes)
TEST_F(Gbase64EncodeTest_36, TwoBytes_36) {
    // 'Ma' -> base64 "TWE="
    const char input[] = "Ma";
    std::string result = gbase64Encode(input, 2);
    EXPECT_EQ(result, "TWE=");
}

// Test encoding three bytes (exact multiple of 3, no padding)
TEST_F(Gbase64EncodeTest_36, ThreeBytes_36) {
    // 'Man' -> base64 "TWFu"
    const char input[] = "Man";
    std::string result = gbase64Encode(input, 3);
    EXPECT_EQ(result, "TWFu");
}

// Test encoding four bytes (3 + 1 remaining)
TEST_F(Gbase64EncodeTest_36, FourBytes_36) {
    // 'Many' -> base64 "TWFueQ=="
    // M a n = TWFu, y = eQ==
    const char input[] = "Many";
    std::string result = gbase64Encode(input, 4);
    EXPECT_EQ(result, "TWFueQ==");
}

// Test encoding five bytes (3 + 2 remaining)
TEST_F(Gbase64EncodeTest_36, FiveBytes_36) {
    // 'Hello' -> base64 "SGVsbG8="
    // Actually: H e l = SGVs, l o = bG8=
    const char input[] = "Hello";
    std::string result = gbase64Encode(input, 5);
    EXPECT_EQ(result, "SGVsbG8=");
}

// Test encoding six bytes (exact multiple of 3, no padding)
TEST_F(Gbase64EncodeTest_36, SixBytes_36) {
    // 'Hello!' -> base64 "SGVsbG8h"
    // Actually let me compute: H(72) e(101) l(108) -> SGVs, l(108) o(111) !(33) -> bG8h
    // Wait: 'Hello!' is H e l l o !
    // Hel -> SGVs, lo! -> bG8h
    // Actually: l=108, o=111, !=33
    // 108*65536 + 111*256 + 33 = 7110433
    // 108 << 16 | 111 << 8 | 33 = 0x6C6F21
    // bits: 011011 000110 111100 100001 -> b G 8 h
    const char input[] = "Hello!";
    std::string result = gbase64Encode(input, 6);
    EXPECT_EQ(result, "SGVsbG8h");
}

// Test well-known base64 encoding
TEST_F(Gbase64EncodeTest_36, WellKnownString_36) {
    // "pleasure." -> base64 "cGxlYXN1cmUu"
    const char input[] = "pleasure.";
    std::string result = gbase64Encode(input, 9);
    EXPECT_EQ(result, "cGxlYXN1cmUu");
}

// Test encoding with null bytes in input
TEST_F(Gbase64EncodeTest_36, NullBytesInInput_36) {
    // Three null bytes -> base64 "AAAA"
    const unsigned char input[] = {0x00, 0x00, 0x00};
    std::string result = gbase64Encode(input, 3);
    EXPECT_EQ(result, "AAAA");
}

// Test encoding a single null byte
TEST_F(Gbase64EncodeTest_36, SingleNullByte_36) {
    const unsigned char input[] = {0x00};
    std::string result = gbase64Encode(input, 1);
    EXPECT_EQ(result, "AA==");
}

// Test encoding all 0xFF bytes
TEST_F(Gbase64EncodeTest_36, AllOnesThreeBytes_36) {
    // 0xFF 0xFF 0xFF -> base64 "////"
    const unsigned char input[] = {0xFF, 0xFF, 0xFF};
    std::string result = gbase64Encode(input, 3);
    EXPECT_EQ(result, "////");
}

// Test encoding binary data
TEST_F(Gbase64EncodeTest_36, BinaryData_36) {
    // 0x00 0x01 0x02 -> base64 "AAEC"
    const unsigned char input[] = {0x00, 0x01, 0x02};
    std::string result = gbase64Encode(input, 3);
    EXPECT_EQ(result, "AAEC");
}

// Test that result length is always a multiple of 4
TEST_F(Gbase64EncodeTest_36, OutputLengthMultipleOfFour_36) {
    for (size_t len = 0; len <= 20; ++len) {
        std::vector<unsigned char> input(len, 'A');
        std::string result = gbase64Encode(input.data(), len);
        if (len == 0) {
            EXPECT_EQ(result.size(), 0u) << "Failed for len=" << len;
        } else {
            EXPECT_EQ(result.size() % 4, 0u) << "Failed for len=" << len;
        }
    }
}

// Test the classic "base64" test vectors
TEST_F(Gbase64EncodeTest_36, RFC4648TestVector_f_36) {
    EXPECT_EQ(gbase64Encode("f", 1), "Zg==");
}

TEST_F(Gbase64EncodeTest_36, RFC4648TestVector_fo_36) {
    EXPECT_EQ(gbase64Encode("fo", 2), "Zm8=");
}

TEST_F(Gbase64EncodeTest_36, RFC4648TestVector_foo_36) {
    EXPECT_EQ(gbase64Encode("foo", 3), "Zm9v");
}

TEST_F(Gbase64EncodeTest_36, RFC4648TestVector_foob_36) {
    EXPECT_EQ(gbase64Encode("foob", 4), "Zm9vYg==");
}

TEST_F(Gbase64EncodeTest_36, RFC4648TestVector_fooba_36) {
    EXPECT_EQ(gbase64Encode("fooba", 5), "Zm9vYmE=");
}

TEST_F(Gbase64EncodeTest_36, RFC4648TestVector_foobar_36) {
    EXPECT_EQ(gbase64Encode("foobar", 6), "Zm9vYmFy");
}

// Test longer input
TEST_F(Gbase64EncodeTest_36, LongerInput_36) {
    const char *input = "The quick brown fox jumps over the lazy dog";
    std::string result = gbase64Encode(input, strlen(input));
    EXPECT_EQ(result, "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw==");
}

// Test encoding two null bytes
TEST_F(Gbase64EncodeTest_36, TwoNullBytes_36) {
    const unsigned char input[] = {0x00, 0x00};
    std::string result = gbase64Encode(input, 2);
    EXPECT_EQ(result, "AAA=");
}

// Test specific byte values to verify correct bit manipulation
TEST_F(Gbase64EncodeTest_36, SpecificByteValues_36) {
    // 0xFB 0xEF 0xBE -> base64 "+++"  wait let me calculate
    // 0xFB = 251, 0xEF = 239, 0xBE = 190
    // Combined: 251*65536 + 239*256 + 190 = 16510910
    // Indices: 251>>2=62(+), ((251&3)<<4)|(239>>4)=((3)<<4)|14=48+14=62(+), ((239&15)<<2)|(190>>6)=((15)<<2)|2=60+2=62(+), 190&63=62(+)
    // So "++++"
    const unsigned char input[] = {0xFB, 0xEF, 0xBE};
    std::string result = gbase64Encode(input, 3);
    EXPECT_EQ(result, "++++");
}
