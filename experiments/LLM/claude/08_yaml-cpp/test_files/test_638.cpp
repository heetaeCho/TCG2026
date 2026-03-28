#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>

#include "yaml-cpp/binary.h"
#include "yaml-cpp/ostream_wrapper.h"

// Forward declaration of the function under test
namespace YAML {
namespace Utils {
bool WriteBinary(ostream_wrapper& out, const Binary& binary);
}
}

using namespace YAML;

class WriteBinaryTest_638 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that WriteBinary returns true for empty binary data
TEST_F(WriteBinaryTest_638, EmptyBinaryReturnsTrue_638) {
    ostream_wrapper out;
    Binary binary(nullptr, 0);
    bool result = Utils::WriteBinary(out, binary);
    EXPECT_TRUE(result);
}

// Test that WriteBinary returns true for non-empty binary data
TEST_F(WriteBinaryTest_638, NonEmptyBinaryReturnsTrue_638) {
    ostream_wrapper out;
    const unsigned char data[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F}; // "Hello"
    Binary binary(data, sizeof(data));
    bool result = Utils::WriteBinary(out, binary);
    EXPECT_TRUE(result);
}

// Test that WriteBinary writes output to ostream_wrapper (non-empty output for non-empty data)
TEST_F(WriteBinaryTest_638, WritesOutputForNonEmptyData_638) {
    ostream_wrapper out;
    const unsigned char data[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F}; // "Hello"
    Binary binary(data, sizeof(data));
    Utils::WriteBinary(out, binary);
    
    // The output should contain something (base64 encoded and double-quoted)
    const char* output = out.str();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    EXPECT_FALSE(outputStr.empty());
}

// Test that WriteBinary produces double-quoted output (starts and ends with quotes)
TEST_F(WriteBinaryTest_638, OutputIsDoubleQuoted_638) {
    ostream_wrapper out;
    const unsigned char data[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F}; // "Hello"
    Binary binary(data, sizeof(data));
    Utils::WriteBinary(out, binary);
    
    const char* output = out.str();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    EXPECT_GE(outputStr.size(), 2u);
    EXPECT_EQ(outputStr.front(), '"');
    EXPECT_EQ(outputStr.back(), '"');
}

// Test that WriteBinary writes to a stream-backed ostream_wrapper
TEST_F(WriteBinaryTest_638, WritesToStreamBackedWrapper_638) {
    std::stringstream ss;
    ostream_wrapper out(ss);
    const unsigned char data[] = {0x01, 0x02, 0x03};
    Binary binary(data, sizeof(data));
    bool result = Utils::WriteBinary(out, binary);
    EXPECT_TRUE(result);
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.front(), '"');
    EXPECT_EQ(output.back(), '"');
}

// Test that WriteBinary produces valid base64 content inside the quotes
TEST_F(WriteBinaryTest_638, OutputContainsBase64Characters_638) {
    ostream_wrapper out;
    const unsigned char data[] = {0x00, 0xFF, 0x80, 0x7F};
    Binary binary(data, sizeof(data));
    Utils::WriteBinary(out, binary);
    
    const char* output = out.str();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    
    // Remove the surrounding quotes
    ASSERT_GE(outputStr.size(), 2u);
    std::string content = outputStr.substr(1, outputStr.size() - 2);
    
    // Base64 characters should be alphanumeric, +, /, or =
    for (char c : content) {
        bool isBase64Char = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
                            (c >= '0' && c <= '9') || c == '+' || c == '/' || c == '=';
        EXPECT_TRUE(isBase64Char) << "Unexpected character in base64: " << c;
    }
}

// Test with empty binary produces double-quoted empty string
TEST_F(WriteBinaryTest_638, EmptyBinaryProducesEmptyQuotedString_638) {
    ostream_wrapper out;
    Binary binary;
    Utils::WriteBinary(out, binary);
    
    const char* output = out.str();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    // Should be just two quotes for empty base64
    EXPECT_EQ(outputStr, "\"\"");
}

// Test with single byte data
TEST_F(WriteBinaryTest_638, SingleByteData_638) {
    ostream_wrapper out;
    const unsigned char data[] = {0x41}; // 'A'
    Binary binary(data, 1);
    bool result = Utils::WriteBinary(out, binary);
    EXPECT_TRUE(result);
    
    const char* output = out.str();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    EXPECT_EQ(outputStr.front(), '"');
    EXPECT_EQ(outputStr.back(), '"');
    // Base64 of single byte 'A' (0x41) is "QQ=="
    EXPECT_EQ(outputStr, "\"QQ==\"");
}

// Test with known base64 encoding: "Hello" -> "SGVsbG8="
TEST_F(WriteBinaryTest_638, KnownBase64Encoding_638) {
    ostream_wrapper out;
    const unsigned char data[] = {'H', 'e', 'l', 'l', 'o'};
    Binary binary(data, sizeof(data));
    Utils::WriteBinary(out, binary);
    
    const char* output = out.str();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    EXPECT_EQ(outputStr, "\"SGVsbG8=\"");
}

// Test with 3-byte aligned data (no padding in base64)
TEST_F(WriteBinaryTest_638, ThreeByteAlignedData_638) {
    ostream_wrapper out;
    const unsigned char data[] = {0x4D, 0x61, 0x6E}; // "Man"
    Binary binary(data, sizeof(data));
    Utils::WriteBinary(out, binary);
    
    const char* output = out.str();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    // Base64 of "Man" is "TWFu"
    EXPECT_EQ(outputStr, "\"TWFu\"");
}

// Test with larger data
TEST_F(WriteBinaryTest_638, LargerBinaryData_638) {
    ostream_wrapper out;
    std::vector<unsigned char> data(256);
    for (int i = 0; i < 256; ++i) {
        data[i] = static_cast<unsigned char>(i);
    }
    Binary binary(data.data(), data.size());
    bool result = Utils::WriteBinary(out, binary);
    EXPECT_TRUE(result);
    
    const char* output = out.str();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    EXPECT_EQ(outputStr.front(), '"');
    EXPECT_EQ(outputStr.back(), '"');
    // 256 bytes -> base64 length should be ceil(256/3)*4 = 344 chars, plus 2 quotes
    EXPECT_EQ(outputStr.size(), 344u + 2u);
}

// Test that pos is updated after WriteBinary
TEST_F(WriteBinaryTest_638, PosUpdatedAfterWrite_638) {
    ostream_wrapper out;
    EXPECT_EQ(out.pos(), 0u);
    
    const unsigned char data[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F};
    Binary binary(data, sizeof(data));
    Utils::WriteBinary(out, binary);
    
    EXPECT_GT(out.pos(), 0u);
}

// Test with all zero bytes
TEST_F(WriteBinaryTest_638, AllZeroBytes_638) {
    ostream_wrapper out;
    const unsigned char data[] = {0x00, 0x00, 0x00};
    Binary binary(data, sizeof(data));
    bool result = Utils::WriteBinary(out, binary);
    EXPECT_TRUE(result);
    
    const char* output = out.str();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    // Base64 of three zero bytes is "AAAA"
    EXPECT_EQ(outputStr, "\"AAAA\"");
}

// Test with all 0xFF bytes
TEST_F(WriteBinaryTest_638, AllFFBytes_638) {
    ostream_wrapper out;
    const unsigned char data[] = {0xFF, 0xFF, 0xFF};
    Binary binary(data, sizeof(data));
    bool result = Utils::WriteBinary(out, binary);
    EXPECT_TRUE(result);
    
    const char* output = out.str();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    // Base64 of three 0xFF bytes is "////"
    EXPECT_EQ(outputStr, "\"////\"");
}

// Test with two bytes (one padding char in base64)
TEST_F(WriteBinaryTest_638, TwoBytesPaddingOne_638) {
    ostream_wrapper out;
    const unsigned char data[] = {0x4D, 0x61}; // "Ma"
    Binary binary(data, sizeof(data));
    Utils::WriteBinary(out, binary);
    
    const char* output = out.str();
    ASSERT_NE(output, nullptr);
    std::string outputStr(output);
    // Base64 of "Ma" is "TWE="
    EXPECT_EQ(outputStr, "\"TWE=\"");
}
