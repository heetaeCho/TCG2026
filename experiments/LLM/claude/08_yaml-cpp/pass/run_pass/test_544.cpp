#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

namespace YAML {
std::string EncodeBase64(const unsigned char *data, std::size_t size);
}

class EncodeBase64Test_544 : public ::testing::Test {
protected:
};

// Test encoding empty data
TEST_F(EncodeBase64Test_544, EmptyInput_544) {
    const unsigned char data[] = {};
    std::string result = YAML::EncodeBase64(data, 0);
    EXPECT_EQ(result, "");
}

// Test encoding a single byte (remainder == 1)
TEST_F(EncodeBase64Test_544, SingleByte_544) {
    const unsigned char data[] = { 'M' };  // 'M' = 0x4D
    std::string result = YAML::EncodeBase64(data, 1);
    EXPECT_EQ(result, "TQ==");
}

// Test encoding two bytes (remainder == 2)
TEST_F(EncodeBase64Test_544, TwoBytes_544) {
    const unsigned char data[] = { 'M', 'a' };
    std::string result = YAML::EncodeBase64(data, 2);
    EXPECT_EQ(result, "TWE=");
}

// Test encoding three bytes (exact chunk, remainder == 0)
TEST_F(EncodeBase64Test_544, ThreeBytes_544) {
    const unsigned char data[] = { 'M', 'a', 'n' };
    std::string result = YAML::EncodeBase64(data, 3);
    EXPECT_EQ(result, "TWFu");
}

// Test encoding "Man" - classic base64 example
TEST_F(EncodeBase64Test_544, ClassicManExample_544) {
    const std::string input = "Man";
    std::string result = YAML::EncodeBase64(
        reinterpret_cast<const unsigned char*>(input.data()), input.size());
    EXPECT_EQ(result, "TWFu");
}

// Test encoding "Ma" 
TEST_F(EncodeBase64Test_544, ClassicMaExample_544) {
    const std::string input = "Ma";
    std::string result = YAML::EncodeBase64(
        reinterpret_cast<const unsigned char*>(input.data()), input.size());
    EXPECT_EQ(result, "TWE=");
}

// Test encoding "M"
TEST_F(EncodeBase64Test_544, ClassicMExample_544) {
    const std::string input = "M";
    std::string result = YAML::EncodeBase64(
        reinterpret_cast<const unsigned char*>(input.data()), input.size());
    EXPECT_EQ(result, "TQ==");
}

// Test encoding six bytes (two complete chunks)
TEST_F(EncodeBase64Test_544, SixBytes_544) {
    const unsigned char data[] = { 'M', 'a', 'n', 'M', 'a', 'n' };
    std::string result = YAML::EncodeBase64(data, 6);
    EXPECT_EQ(result, "TWFuTWFu");
}

// Test encoding four bytes (one chunk + remainder 1)
TEST_F(EncodeBase64Test_544, FourBytes_544) {
    const std::string input = "Many";
    std::string result = YAML::EncodeBase64(
        reinterpret_cast<const unsigned char*>(input.data()), input.size());
    // "Man" -> "TWFu", "y" -> remainder 1 -> "eQ=="
    EXPECT_EQ(result, "TWFueQ==");
}

// Test encoding five bytes (one chunk + remainder 2)
TEST_F(EncodeBase64Test_544, FiveBytes_544) {
    const std::string input = "Many1";
    std::string result = YAML::EncodeBase64(
        reinterpret_cast<const unsigned char*>(input.data()), input.size());
    // "Man" -> "TWFu", "y1" -> remainder 2 -> "eTE="
    EXPECT_EQ(result, "TWFueTE=");
}

// Test encoding all zero bytes
TEST_F(EncodeBase64Test_544, AllZeroBytes_544) {
    const unsigned char data[] = { 0, 0, 0 };
    std::string result = YAML::EncodeBase64(data, 3);
    EXPECT_EQ(result, "AAAA");
}

// Test encoding all 0xFF bytes
TEST_F(EncodeBase64Test_544, AllFFBytes_544) {
    const unsigned char data[] = { 0xFF, 0xFF, 0xFF };
    std::string result = YAML::EncodeBase64(data, 3);
    EXPECT_EQ(result, "////");
}

// Test encoding a single zero byte
TEST_F(EncodeBase64Test_544, SingleZeroByte_544) {
    const unsigned char data[] = { 0x00 };
    std::string result = YAML::EncodeBase64(data, 1);
    EXPECT_EQ(result, "AA==");
}

// Test encoding two zero bytes
TEST_F(EncodeBase64Test_544, TwoZeroBytes_544) {
    const unsigned char data[] = { 0x00, 0x00 };
    std::string result = YAML::EncodeBase64(data, 2);
    EXPECT_EQ(result, "AAA=");
}

// Test encoding "Hello World"
TEST_F(EncodeBase64Test_544, HelloWorld_544) {
    const std::string input = "Hello World";
    std::string result = YAML::EncodeBase64(
        reinterpret_cast<const unsigned char*>(input.data()), input.size());
    EXPECT_EQ(result, "SGVsbG8gV29ybGQ=");
}

// Test result length is always a multiple of 4 for non-empty input
TEST_F(EncodeBase64Test_544, ResultLengthMultipleOf4_544) {
    for (std::size_t len = 1; len <= 20; ++len) {
        std::vector<unsigned char> data(len, 'A');
        std::string result = YAML::EncodeBase64(data.data(), data.size());
        EXPECT_EQ(result.size() % 4, 0u) << "Failed for input length " << len;
    }
}

// Test encoding binary data with specific known values
TEST_F(EncodeBase64Test_544, BinaryData_544) {
    // Encoding {0xFB, 0xEF, 0xBE} should produce a known base64 string
    const unsigned char data[] = { 0xFB, 0xEF, 0xBE };
    std::string result = YAML::EncodeBase64(data, 3);
    // 0xFB = 11111011, 0xEF = 11101111, 0xBE = 10111110
    // chunk: 111110 111110 111110 111110 -> "++++""
    EXPECT_EQ(result, "++++" );
}

// Test encoding "light work." - another classic base64 test vector
TEST_F(EncodeBase64Test_544, LightWork_544) {
    const std::string input = "light work.";
    std::string result = YAML::EncodeBase64(
        reinterpret_cast<const unsigned char*>(input.data()), input.size());
    EXPECT_EQ(result, "bGlnaHQgd29yay4=");
}

// Test encoding "light work" (without period, different padding)
TEST_F(EncodeBase64Test_544, LightWorkNoPeriod_544) {
    const std::string input = "light work";
    std::string result = YAML::EncodeBase64(
        reinterpret_cast<const unsigned char*>(input.data()), input.size());
    EXPECT_EQ(result, "bGlnaHQgd29yaw==");
}

// Test encoding "light wor" (9 bytes, no padding needed)
TEST_F(EncodeBase64Test_544, LightWor_544) {
    const std::string input = "light wor";
    std::string result = YAML::EncodeBase64(
        reinterpret_cast<const unsigned char*>(input.data()), input.size());
    EXPECT_EQ(result, "bGlnaHQgd29y");
}

// Test that output only contains valid base64 characters
TEST_F(EncodeBase64Test_544, OutputContainsOnlyValidChars_544) {
    const std::string valid_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    for (std::size_t len = 1; len <= 30; ++len) {
        std::vector<unsigned char> data(len);
        for (std::size_t i = 0; i < len; ++i) {
            data[i] = static_cast<unsigned char>(i * 7 + 13);
        }
        std::string result = YAML::EncodeBase64(data.data(), data.size());
        for (char c : result) {
            EXPECT_NE(valid_chars.find(c), std::string::npos)
                << "Invalid character '" << c << "' found for input length " << len;
        }
    }
}

// Test encoding a larger buffer
TEST_F(EncodeBase64Test_544, LargerBuffer_544) {
    std::vector<unsigned char> data(256);
    for (int i = 0; i < 256; i++) {
        data[i] = static_cast<unsigned char>(i);
    }
    std::string result = YAML::EncodeBase64(data.data(), data.size());
    // 256 bytes -> 256/3 = 85 chunks + 1 remainder byte
    // output length: 85*4 + 4 = 344
    EXPECT_EQ(result.size(), 344u);
    // Should end with == since remainder is 1 byte (256 % 3 == 1)
    EXPECT_EQ(result.substr(result.size() - 2), "==");
}

// Test encoding single byte 0xFF
TEST_F(EncodeBase64Test_544, SingleByteFF_544) {
    const unsigned char data[] = { 0xFF };
    std::string result = YAML::EncodeBase64(data, 1);
    // 0xFF = 11111111
    // first 6 bits: 111111 -> '/'
    // next 6 bits (padded): 110000 -> 'w' (index 48)
    // Wait: ((0xFF & 0x3) << 4) = (3 << 4) = 48 -> 'w'
    // So: "/w=="
    EXPECT_EQ(result, "/w==");
}

// Test encoding two bytes 0xFF 0xFF
TEST_F(EncodeBase64Test_544, TwoBytesFF_544) {
    const unsigned char data[] = { 0xFF, 0xFF };
    std::string result = YAML::EncodeBase64(data, 2);
    // 0xFF >> 2 = 63 -> '/'
    // ((0xFF & 0x3) << 4) | (0xFF >> 4) = (3<<4) | 15 = 48+15 = 63 -> '/'
    // ((0xFF & 0xf) << 2) = (15 << 2) = 60 -> '8'
    EXPECT_EQ(result, "//8=");
}
