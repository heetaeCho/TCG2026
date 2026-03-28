#include <gtest/gtest.h>
#include <zlib.h>
#include <vector>
#include <cstring>

// Include necessary Exiv2 headers
#include "exiv2/types.hpp"

// Since zlibToDataBuf is a static function in pngimage.cpp, we need to access it.
// One common approach for testing static functions is to include the .cpp file.
// This may require careful handling of ODR, but is a standard testing technique.
namespace Exiv2 {
bool zlibToDataBuf(const byte* bytes, uLongf length, DataBuf& result);
}

// If the above declaration doesn't link, include the source directly:
// #include "pngimage.cpp"

namespace {

// Helper: compress data using zlib
std::vector<Exiv2::byte> compressData(const std::vector<Exiv2::byte>& input) {
    uLongf compressedSize = compressBound(static_cast<uLong>(input.size()));
    std::vector<Exiv2::byte> compressed(compressedSize);
    int ret = compress(compressed.data(), &compressedSize, input.data(), static_cast<uLong>(input.size()));
    EXPECT_EQ(ret, Z_OK);
    compressed.resize(compressedSize);
    return compressed;
}

class ZlibToDataBufTest_968 : public ::testing::Test {
protected:
    Exiv2::DataBuf result;
};

// Test normal decompression of a simple string
TEST_F(ZlibToDataBufTest_968, DecompressSimpleString_968) {
    const std::string original = "Hello, World! This is a test string for zlib compression.";
    std::vector<Exiv2::byte> input(original.begin(), original.end());
    std::vector<Exiv2::byte> compressed = compressData(input);

    bool success = Exiv2::zlibToDataBuf(compressed.data(), static_cast<uLongf>(compressed.size()), result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), original.size());
    EXPECT_EQ(std::memcmp(result.c_data(0), original.data(), original.size()), 0);
}

// Test decompression of an empty payload (zlib compressed empty data)
TEST_F(ZlibToDataBufTest_968, DecompressEmptyData_968) {
    std::vector<Exiv2::byte> input;
    // Compress empty data
    uLongf compressedSize = compressBound(0);
    std::vector<Exiv2::byte> compressed(compressedSize);
    int ret = compress(compressed.data(), &compressedSize, nullptr, 0);
    // compress with 0 length may need a valid pointer
    Exiv2::byte dummy = 0;
    ret = compress(compressed.data(), &compressedSize, &dummy, 0);
    ASSERT_EQ(ret, Z_OK);
    compressed.resize(compressedSize);

    bool success = Exiv2::zlibToDataBuf(compressed.data(), static_cast<uLongf>(compressed.size()), result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), 0u);
}

// Test decompression of a single byte
TEST_F(ZlibToDataBufTest_968, DecompressSingleByte_968) {
    std::vector<Exiv2::byte> input = {0x42};
    std::vector<Exiv2::byte> compressed = compressData(input);

    bool success = Exiv2::zlibToDataBuf(compressed.data(), static_cast<uLongf>(compressed.size()), result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result.c_data(0)[0], 0x42);
}

// Test with invalid/corrupt compressed data
TEST_F(ZlibToDataBufTest_968, InvalidCompressedDataReturnsFalse_968) {
    // Random garbage bytes that are not valid zlib data
    std::vector<Exiv2::byte> garbage = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    bool success = Exiv2::zlibToDataBuf(garbage.data(), static_cast<uLongf>(garbage.size()), result);

    EXPECT_FALSE(success);
}

// Test decompression of data that is much larger when uncompressed
// (tests the buffer doubling logic in the while loop)
TEST_F(ZlibToDataBufTest_968, DecompressLargeExpansionRatio_968) {
    // Create highly compressible data (all zeros)
    std::vector<Exiv2::byte> input(100000, 0x00);
    std::vector<Exiv2::byte> compressed = compressData(input);

    // The compressed size should be much smaller than 100000
    ASSERT_LT(compressed.size(), input.size());

    bool success = Exiv2::zlibToDataBuf(compressed.data(), static_cast<uLongf>(compressed.size()), result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), input.size());
    EXPECT_EQ(std::memcmp(result.c_data(0), input.data(), input.size()), 0);
}

// Test with truncated compressed data
TEST_F(ZlibToDataBufTest_968, TruncatedCompressedDataReturnsFalse_968) {
    const std::string original = "This is some test data that will be compressed and then truncated.";
    std::vector<Exiv2::byte> input(original.begin(), original.end());
    std::vector<Exiv2::byte> compressed = compressData(input);

    // Truncate the compressed data
    ASSERT_GT(compressed.size(), 4u);
    size_t truncatedSize = compressed.size() / 2;

    bool success = Exiv2::zlibToDataBuf(compressed.data(), static_cast<uLongf>(truncatedSize), result);

    EXPECT_FALSE(success);
}

// Test decompression with various data patterns
TEST_F(ZlibToDataBufTest_968, DecompressRepeatingPattern_968) {
    std::vector<Exiv2::byte> input;
    for (int i = 0; i < 1000; ++i) {
        input.push_back(static_cast<Exiv2::byte>(i % 256));
    }
    std::vector<Exiv2::byte> compressed = compressData(input);

    bool success = Exiv2::zlibToDataBuf(compressed.data(), static_cast<uLongf>(compressed.size()), result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), input.size());
    EXPECT_EQ(std::memcmp(result.c_data(0), input.data(), input.size()), 0);
}

// Test with a single-byte compressed stream that's invalid
TEST_F(ZlibToDataBufTest_968, SingleByteInvalidData_968) {
    std::vector<Exiv2::byte> singleByte = {0xFF};

    bool success = Exiv2::zlibToDataBuf(singleByte.data(), static_cast<uLongf>(singleByte.size()), result);

    EXPECT_FALSE(success);
}

// Test that the result DataBuf is properly sized after successful decompression
TEST_F(ZlibToDataBufTest_968, ResultSizeMatchesOriginal_968) {
    const std::string original = "Exact size verification test string with known length.";
    std::vector<Exiv2::byte> input(original.begin(), original.end());
    std::vector<Exiv2::byte> compressed = compressData(input);

    bool success = Exiv2::zlibToDataBuf(compressed.data(), static_cast<uLongf>(compressed.size()), result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), original.size());
}

// Test decompression of binary data (all byte values)
TEST_F(ZlibToDataBufTest_968, DecompressAllByteValues_968) {
    std::vector<Exiv2::byte> input(256);
    for (int i = 0; i < 256; ++i) {
        input[i] = static_cast<Exiv2::byte>(i);
    }
    std::vector<Exiv2::byte> compressed = compressData(input);

    bool success = Exiv2::zlibToDataBuf(compressed.data(), static_cast<uLongf>(compressed.size()), result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), 256u);
    for (int i = 0; i < 256; ++i) {
        EXPECT_EQ(result.c_data(0)[i], static_cast<Exiv2::byte>(i));
    }
}

// Test with corrupted header (modify zlib header bytes)
TEST_F(ZlibToDataBufTest_968, CorruptedZlibHeader_968) {
    const std::string original = "Test data for corruption test.";
    std::vector<Exiv2::byte> input(original.begin(), original.end());
    std::vector<Exiv2::byte> compressed = compressData(input);

    // Corrupt the first two bytes (zlib header)
    ASSERT_GE(compressed.size(), 2u);
    compressed[0] ^= 0xFF;
    compressed[1] ^= 0xFF;

    bool success = Exiv2::zlibToDataBuf(compressed.data(), static_cast<uLongf>(compressed.size()), result);

    EXPECT_FALSE(success);
}

// Test with moderately sized data to ensure intermediate buffer sizing works
TEST_F(ZlibToDataBufTest_968, DecompressModerateSizeData_968) {
    // Create data that's around 10KB
    std::vector<Exiv2::byte> input(10240);
    for (size_t i = 0; i < input.size(); ++i) {
        input[i] = static_cast<Exiv2::byte>((i * 7 + 13) % 256);
    }
    std::vector<Exiv2::byte> compressed = compressData(input);

    bool success = Exiv2::zlibToDataBuf(compressed.data(), static_cast<uLongf>(compressed.size()), result);

    EXPECT_TRUE(success);
    EXPECT_EQ(result.size(), input.size());
    EXPECT_EQ(std::memcmp(result.c_data(0), input.data(), input.size()), 0);
}

}  // namespace
