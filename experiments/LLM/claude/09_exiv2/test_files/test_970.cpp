#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <vector>

// Assuming exiv2 headers
#include "exiv2/types.hpp"

// Since tEXtToDataBuf is a static function inside pngimage.cpp's namespace,
// we include the cpp to access it for testing purposes.
// In practice, this would be exposed via a test helper.
namespace Exiv2 {
bool tEXtToDataBuf(const byte* bytes, size_t length, DataBuf& result);
}

using Exiv2::DataBuf;
using Exiv2::byte;

class TEXtToDataBufTest_970 : public ::testing::Test {
protected:
    DataBuf result;
};

// Helper to create input with 3 newlines followed by hex data
static std::vector<byte> makeInput(const std::string& header, const std::string& hexData) {
    std::vector<byte> input;
    // Add header lines (3 newlines to skip)
    for (char c : header) {
        input.push_back(static_cast<byte>(c));
    }
    for (char c : hexData) {
        input.push_back(static_cast<byte>(c));
    }
    return input;
}

// Test with empty input
TEST_F(TEXtToDataBufTest_970, EmptyInput_970) {
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(nullptr, 0, result);
    EXPECT_TRUE(ret);
    // With 0 length, no data should be produced meaningfully
}

// Test with input that has no newlines and no hex chars
TEST_F(TEXtToDataBufTest_970, NoNewlinesNoHex_970) {
    std::string input = "zzzzz";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    // No newlines found, so length stays reduced but no hex chars recognized
}

// Test with exactly 3 newlines and valid hex data after
TEST_F(TEXtToDataBufTest_970, ThreeNewlinesFollowedByHexPair_970) {
    std::string input = "line1\nline2\nline3\nFF";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result.read_uint8(0), 0xFF);
}

// Test with hex data "00"
TEST_F(TEXtToDataBufTest_970, HexZeroZero_970) {
    std::string input = "\n\n\n00";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result.read_uint8(0), 0x00);
}

// Test with multiple hex bytes
TEST_F(TEXtToDataBufTest_970, MultipleHexBytes_970) {
    std::string input = "\n\n\nDEADBEEF";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(result.read_uint8(0), 0xDE);
    EXPECT_EQ(result.read_uint8(1), 0xAD);
    EXPECT_EQ(result.read_uint8(2), 0xBE);
    EXPECT_EQ(result.read_uint8(3), 0xEF);
}

// Test with lowercase hex
TEST_F(TEXtToDataBufTest_970, LowercaseHex_970) {
    std::string input = "\n\n\ndeadbeef";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(result.read_uint8(0), 0xDE);
    EXPECT_EQ(result.read_uint8(1), 0xAD);
    EXPECT_EQ(result.read_uint8(2), 0xBE);
    EXPECT_EQ(result.read_uint8(3), 0xEF);
}

// Test with mixed case hex
TEST_F(TEXtToDataBufTest_970, MixedCaseHex_970) {
    std::string input = "\n\n\nDe";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result.read_uint8(0), 0xDE);
}

// Test with non-hex characters interspersed (should be ignored)
TEST_F(TEXtToDataBufTest_970, NonHexCharsIgnored_970) {
    std::string input = "\n\n\nF F";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    // "F F" -> two hex chars 'F' and 'F', space ignored
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result.read_uint8(0), 0xFF);
}

// Test with odd number of hex digits
TEST_F(TEXtToDataBufTest_970, OddNumberOfHexDigits_970) {
    std::string input = "\n\n\nABC";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    // 3 hex chars -> (3+1)/2 = 2 bytes allocated, but only 1 full byte written (0xAB)
    // The leading nibble 'C' (0xC0) would be stored in n but not flushed
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result.read_uint8(0), 0xAB);
}

// Test with only newlines, no hex data
TEST_F(TEXtToDataBufTest_970, OnlyNewlines_970) {
    std::string input = "\n\n\n";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    // No hex data after 3 newlines, count of hex chars = 0, alloc((0+1)/2) = 0
    EXPECT_EQ(result.size(), 0u);
}

// Test with fewer than 3 newlines - all content consumed looking for newlines
TEST_F(TEXtToDataBufTest_970, FewerThanThreeNewlines_970) {
    std::string input = "ab\ncd\nFF";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    // Only 2 newlines found before length runs out; remaining length after scanning = "FF" portion
    // depends on how much is consumed
}

// Test with data "0123456789abcdef" after header
TEST_F(TEXtToDataBufTest_970, AllHexDigits_970) {
    std::string input = "\n\n\n0123456789abcdef";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    ASSERT_EQ(result.size(), 8u);
    EXPECT_EQ(result.read_uint8(0), 0x01);
    EXPECT_EQ(result.read_uint8(1), 0x23);
    EXPECT_EQ(result.read_uint8(2), 0x45);
    EXPECT_EQ(result.read_uint8(3), 0x67);
    EXPECT_EQ(result.read_uint8(4), 0x89);
    EXPECT_EQ(result.read_uint8(5), 0xAB);
    EXPECT_EQ(result.read_uint8(6), 0xCD);
    EXPECT_EQ(result.read_uint8(7), 0xEF);
}

// Test with uppercase hex digits ABCDEF
TEST_F(TEXtToDataBufTest_970, UppercaseABCDEF_970) {
    std::string input = "\n\n\nABCDEF";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result.read_uint8(0), 0xAB);
    EXPECT_EQ(result.read_uint8(1), 0xCD);
    EXPECT_EQ(result.read_uint8(2), 0xEF);
}

// Test always returns true
TEST_F(TEXtToDataBufTest_970, AlwaysReturnsTrue_970) {
    std::string input = "\n\n\n";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
}

// Test with header content before newlines
TEST_F(TEXtToDataBufTest_970, HeaderContentBeforeNewlines_970) {
    std::string input = "header1\nheader2\nheader3\nAA";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result.read_uint8(0), 0xAA);
}

// Test with spaces and newlines in hex area
TEST_F(TEXtToDataBufTest_970, SpacesInHexArea_970) {
    std::string input = "\n\n\nA B C D";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result.read_uint8(0), 0xAB);
    EXPECT_EQ(result.read_uint8(1), 0xCD);
}

// Test single hex digit
TEST_F(TEXtToDataBufTest_970, SingleHexDigit_970) {
    std::string input = "\n\n\nA";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    // 1 hex char -> alloc((1+1)/2) = 1, but only leading nibble set
    ASSERT_EQ(result.size(), 1u);
}

// Test with newlines inside hex data (more than 3 newlines total)
TEST_F(TEXtToDataBufTest_970, NewlinesInHexData_970) {
    std::string input = "\n\n\nAB\nCD";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    // After 3 newlines, remaining is "AB\nCD"
    // Hex chars: A, B, C, D (newline is not hex) -> 4 hex chars -> 2 bytes
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result.read_uint8(0), 0xAB);
    EXPECT_EQ(result.read_uint8(1), 0xCD);
}

// Test with 'g' character (not a valid hex digit)
TEST_F(TEXtToDataBufTest_970, InvalidHexCharG_970) {
    std::string input = "\n\n\ngAB";
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(reinterpret_cast<const byte*>(input.data()), input.size(), result);
    EXPECT_TRUE(ret);
    // 'g' is ignored, hex chars are A and B -> 1 byte
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result.read_uint8(0), 0xAB);
}

// Test with length 1 (single non-newline char)
TEST_F(TEXtToDataBufTest_970, LengthOneNonNewline_970) {
    byte input = 'A';
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(&input, 1, result);
    EXPECT_TRUE(ret);
    // No 3 newlines found, length becomes 0, no hex processing
}

// Test with length 1 (single newline char)
TEST_F(TEXtToDataBufTest_970, LengthOneNewline_970) {
    byte input = '\n';
    DataBuf result;
    bool ret = Exiv2::tEXtToDataBuf(&input, 1, result);
    EXPECT_TRUE(ret);
}
