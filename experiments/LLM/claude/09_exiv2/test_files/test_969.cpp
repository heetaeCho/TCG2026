#include <gtest/gtest.h>
#include <zlib.h>
#include <cstring>
#include <vector>

// Include exiv2 headers
#include "exiv2/types.hpp"

// Forward declare the function from pngimage.cpp
// Since it's static in the Exiv2 namespace (not anonymous), we attempt to link against it.
// If it's truly file-static, we include the source.
namespace Exiv2 {
bool zlibToCompressed(const byte* bytes, uLongf length, DataBuf& result);
}

class ZlibToCompressedTest_969 : public ::testing::Test {
protected:
    Exiv2::DataBuf result;
};

// Test: Compressing a simple non-empty byte array returns true
TEST_F(ZlibToCompressedTest_969, CompressSimpleData_969) {
    const char* input = "Hello, World! This is a test string for compression.";
    auto length = static_cast<uLongf>(std::strlen(input));

    bool success = Exiv2::zlibToCompressed(
        reinterpret_cast<const Exiv2::byte*>(input), length, result);

    EXPECT_TRUE(success);
    EXPECT_GT(result.size(), 0u);
}

// Test: Compressed data can be decompressed back to original
TEST_F(ZlibToCompressedTest_969, CompressedDataDecompressesToOriginal_969) {
    const char* input = "Hello, World! This is a test string for compression.";
    auto length = static_cast<uLongf>(std::strlen(input));

    bool success = Exiv2::zlibToCompressed(
        reinterpret_cast<const Exiv2::byte*>(input), length, result);

    ASSERT_TRUE(success);

    // Decompress and verify
    std::vector<Exiv2::byte> decompressed(length);
    uLongf decompressedLen = length;
    int zResult = uncompress(decompressed.data(), &decompressedLen,
                             result.c_data(0), static_cast<uLongf>(result.size()));

    EXPECT_EQ(zResult, Z_OK);
    EXPECT_EQ(decompressedLen, length);
    EXPECT_EQ(std::memcmp(decompressed.data(), input, length), 0);
}

// Test: Compressing a single byte succeeds
TEST_F(ZlibToCompressedTest_969, CompressSingleByte_969) {
    Exiv2::byte singleByte = 0x42;
    uLongf length = 1;

    bool success = Exiv2::zlibToCompressed(&singleByte, length, result);

    EXPECT_TRUE(success);
    EXPECT_GT(result.size(), 0u);

    // Verify decompression
    std::vector<Exiv2::byte> decompressed(1);
    uLongf decompressedLen = 1;
    int zResult = uncompress(decompressed.data(), &decompressedLen,
                             result.c_data(0), static_cast<uLongf>(result.size()));
    EXPECT_EQ(zResult, Z_OK);
    EXPECT_EQ(decompressedLen, 1u);
    EXPECT_EQ(decompressed[0], 0x42);
}

// Test: Compressing zero-length data
TEST_F(ZlibToCompressedTest_969, CompressZeroLength_969) {
    Exiv2::byte dummy = 0;
    uLongf length = 0;

    bool success = Exiv2::zlibToCompressed(&dummy, length, result);

    EXPECT_TRUE(success);
}

// Test: Compressing a larger data block
TEST_F(ZlibToCompressedTest_969, CompressLargerData_969) {
    std::vector<Exiv2::byte> largeData(10000, 'A');
    uLongf length = static_cast<uLongf>(largeData.size());

    bool success = Exiv2::zlibToCompressed(largeData.data(), length, result);

    EXPECT_TRUE(success);
    EXPECT_GT(result.size(), 0u);

    // Highly repetitive data should compress well
    EXPECT_LT(result.size(), largeData.size());

    // Verify decompression
    std::vector<Exiv2::byte> decompressed(length);
    uLongf decompressedLen = length;
    int zResult = uncompress(decompressed.data(), &decompressedLen,
                             result.c_data(0), static_cast<uLongf>(result.size()));
    EXPECT_EQ(zResult, Z_OK);
    EXPECT_EQ(decompressedLen, length);
    EXPECT_EQ(std::memcmp(decompressed.data(), largeData.data(), length), 0);
}

// Test: Compressing random-like data (all byte values)
TEST_F(ZlibToCompressedTest_969, CompressRandomLikeData_969) {
    std::vector<Exiv2::byte> data(256);
    for (int i = 0; i < 256; ++i) {
        data[i] = static_cast<Exiv2::byte>(i);
    }
    uLongf length = static_cast<uLongf>(data.size());

    bool success = Exiv2::zlibToCompressed(data.data(), length, result);

    EXPECT_TRUE(success);
    EXPECT_GT(result.size(), 0u);

    // Verify decompression
    std::vector<Exiv2::byte> decompressed(length);
    uLongf decompressedLen = length;
    int zResult = uncompress(decompressed.data(), &decompressedLen,
                             result.c_data(0), static_cast<uLongf>(result.size()));
    EXPECT_EQ(zResult, Z_OK);
    EXPECT_EQ(decompressedLen, length);
    EXPECT_EQ(std::memcmp(decompressed.data(), data.data(), length), 0);
}

// Test: Compressing all zeros
TEST_F(ZlibToCompressedTest_969, CompressAllZeros_969) {
    std::vector<Exiv2::byte> data(1000, 0x00);
    uLongf length = static_cast<uLongf>(data.size());

    bool success = Exiv2::zlibToCompressed(data.data(), length, result);

    EXPECT_TRUE(success);
    EXPECT_GT(result.size(), 0u);

    // Verify decompression
    std::vector<Exiv2::byte> decompressed(length);
    uLongf decompressedLen = length;
    int zResult = uncompress(decompressed.data(), &decompressedLen,
                             result.c_data(0), static_cast<uLongf>(result.size()));
    EXPECT_EQ(zResult, Z_OK);
    EXPECT_EQ(decompressedLen, length);
    EXPECT_EQ(std::memcmp(decompressed.data(), data.data(), length), 0);
}

// Test: Result buffer is properly sized (not excessively large)
TEST_F(ZlibToCompressedTest_969, ResultBufferSizeMatchesCompressedSize_969) {
    const char* input = "Test data for compression size check";
    auto length = static_cast<uLongf>(std::strlen(input));

    bool success = Exiv2::zlibToCompressed(
        reinterpret_cast<const Exiv2::byte*>(input), length, result);

    ASSERT_TRUE(success);

    // The result size should be reasonable (at most compressBound)
    uLongf bound = compressBound(length);
    EXPECT_LE(result.size(), static_cast<size_t>(bound));
}

// Test: Calling the function multiple times with the same result buffer
TEST_F(ZlibToCompressedTest_969, ReuseSameResultBuffer_969) {
    const char* input1 = "First input string";
    auto length1 = static_cast<uLongf>(std::strlen(input1));

    bool success1 = Exiv2::zlibToCompressed(
        reinterpret_cast<const Exiv2::byte*>(input1), length1, result);
    EXPECT_TRUE(success1);

    size_t firstSize = result.size();

    const char* input2 = "Second input string which is a bit longer than the first one";
    auto length2 = static_cast<uLongf>(std::strlen(input2));

    bool success2 = Exiv2::zlibToCompressed(
        reinterpret_cast<const Exiv2::byte*>(input2), length2, result);
    EXPECT_TRUE(success2);

    // Verify second compression is correct
    std::vector<Exiv2::byte> decompressed(length2);
    uLongf decompressedLen = length2;
    int zResult = uncompress(decompressed.data(), &decompressedLen,
                             result.c_data(0), static_cast<uLongf>(result.size()));
    EXPECT_EQ(zResult, Z_OK);
    EXPECT_EQ(decompressedLen, length2);
    EXPECT_EQ(std::memcmp(decompressed.data(), input2, length2), 0);
}

// Test: Compressing two bytes
TEST_F(ZlibToCompressedTest_969, CompressTwoBytes_969) {
    Exiv2::byte twoBytes[] = {0xFF, 0x00};
    uLongf length = 2;

    bool success = Exiv2::zlibToCompressed(twoBytes, length, result);

    EXPECT_TRUE(success);
    EXPECT_GT(result.size(), 0u);

    std::vector<Exiv2::byte> decompressed(2);
    uLongf decompressedLen = 2;
    int zResult = uncompress(decompressed.data(), &decompressedLen,
                             result.c_data(0), static_cast<uLongf>(result.size()));
    EXPECT_EQ(zResult, Z_OK);
    EXPECT_EQ(decompressedLen, 2u);
    EXPECT_EQ(decompressed[0], 0xFF);
    EXPECT_EQ(decompressed[1], 0x00);
}
