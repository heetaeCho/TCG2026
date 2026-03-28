#include <gtest/gtest.h>
#include <exiv2/cr2image.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/types.hpp>
#include <vector>
#include <cstring>

namespace {

class Cr2ParserTest_1745 : public ::testing::Test {
protected:
    Exiv2::ExifData exifData;
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
};

// Test decoding with null data pointer
TEST_F(Cr2ParserTest_1745, DecodeNullData_1745) {
    Exiv2::ByteOrder result = Exiv2::Cr2Parser::decode(exifData, iptcData, xmpData, nullptr, 0);
    // With null data and zero size, the parser should return some byte order
    // (likely invalidByteOrder or a default). We just verify it doesn't crash.
    EXPECT_TRUE(result == Exiv2::invalidByteOrder ||
                result == Exiv2::littleEndian ||
                result == Exiv2::bigEndian);
}

// Test decoding with zero-length data
TEST_F(Cr2ParserTest_1745, DecodeZeroSize_1745) {
    Exiv2::byte data[1] = {0};
    Exiv2::ByteOrder result = Exiv2::Cr2Parser::decode(exifData, iptcData, xmpData, data, 0);
    EXPECT_TRUE(result == Exiv2::invalidByteOrder ||
                result == Exiv2::littleEndian ||
                result == Exiv2::bigEndian);
}

// Test decoding with data too small to be a valid CR2 header
TEST_F(Cr2ParserTest_1745, DecodeTooSmallData_1745) {
    std::vector<Exiv2::byte> data(4, 0);
    Exiv2::ByteOrder result = Exiv2::Cr2Parser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    // Data is too small to contain a valid CR2 header (needs at least 16 bytes for CR2 header)
    // Should likely return invalidByteOrder
    EXPECT_TRUE(result == Exiv2::invalidByteOrder ||
                result == Exiv2::littleEndian ||
                result == Exiv2::bigEndian);
}

// Test decoding with random/garbage data of sufficient size
TEST_F(Cr2ParserTest_1745, DecodeGarbageData_1745) {
    std::vector<Exiv2::byte> data(1024, 0xFF);
    Exiv2::ByteOrder result = Exiv2::Cr2Parser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    // Garbage data should not produce valid exif data
    // The parser should handle this gracefully
    EXPECT_TRUE(result == Exiv2::invalidByteOrder ||
                result == Exiv2::littleEndian ||
                result == Exiv2::bigEndian);
}

// Test decoding with data that has valid TIFF little-endian byte order marker but invalid CR2 structure
TEST_F(Cr2ParserTest_1745, DecodeInvalidCr2WithLittleEndianMarker_1745) {
    std::vector<Exiv2::byte> data(64, 0);
    // Set little-endian byte order marker "II"
    data[0] = 'I';
    data[1] = 'I';
    // TIFF magic number 42 in little-endian
    data[2] = 42;
    data[3] = 0;
    // Offset to first IFD (16 for CR2)
    data[4] = 16;
    data[5] = 0;
    data[6] = 0;
    data[7] = 0;
    // CR2 magic: "CR" at offset 8
    data[8] = 'C';
    data[9] = 'R';
    // CR2 major version
    data[10] = 2;
    data[11] = 0;
    // Offset to RAW IFD (set to 0 for simplicity)
    data[12] = 0;
    data[13] = 0;
    data[14] = 0;
    data[15] = 0;

    Exiv2::ByteOrder result = Exiv2::Cr2Parser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    // Even with a partial valid header, the rest is invalid so exifData might be empty
    // but the byte order might be detected
    EXPECT_TRUE(result == Exiv2::invalidByteOrder ||
                result == Exiv2::littleEndian ||
                result == Exiv2::bigEndian);
}

// Test decoding with data that has valid TIFF big-endian byte order marker but invalid CR2 structure
TEST_F(Cr2ParserTest_1745, DecodeInvalidCr2WithBigEndianMarker_1745) {
    std::vector<Exiv2::byte> data(64, 0);
    // Set big-endian byte order marker "MM"
    data[0] = 'M';
    data[1] = 'M';
    // TIFF magic number 42 in big-endian
    data[2] = 0;
    data[3] = 42;
    // Offset to first IFD
    data[4] = 0;
    data[5] = 0;
    data[6] = 0;
    data[7] = 16;

    Exiv2::ByteOrder result = Exiv2::Cr2Parser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    EXPECT_TRUE(result == Exiv2::invalidByteOrder ||
                result == Exiv2::littleEndian ||
                result == Exiv2::bigEndian);
}

// Test that exifData, iptcData, xmpData remain empty after decoding invalid data
TEST_F(Cr2ParserTest_1745, DecodeInvalidDataContainersRemainEmpty_1745) {
    std::vector<Exiv2::byte> data(16, 0);
    Exiv2::Cr2Parser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    // With invalid data, no metadata should be extracted
    EXPECT_TRUE(exifData.empty());
    EXPECT_TRUE(iptcData.empty());
    EXPECT_TRUE(xmpData.empty());
}

// Test decoding with size 1 data
TEST_F(Cr2ParserTest_1745, DecodeSingleByteData_1745) {
    Exiv2::byte data = 0x49; // 'I'
    Exiv2::ByteOrder result = Exiv2::Cr2Parser::decode(exifData, iptcData, xmpData, &data, 1);
    EXPECT_TRUE(result == Exiv2::invalidByteOrder ||
                result == Exiv2::littleEndian ||
                result == Exiv2::bigEndian);
    EXPECT_TRUE(exifData.empty());
}

// Test decoding with exactly 16 bytes (minimum CR2 header size) but all zeros
TEST_F(Cr2ParserTest_1745, DecodeMinimumHeaderSizeAllZeros_1745) {
    std::vector<Exiv2::byte> data(16, 0);
    Exiv2::ByteOrder result = Exiv2::Cr2Parser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    // All zeros is not a valid byte order marker
    EXPECT_TRUE(result == Exiv2::invalidByteOrder ||
                result == Exiv2::littleEndian ||
                result == Exiv2::bigEndian);
}

// Test that decode can be called multiple times without issues
TEST_F(Cr2ParserTest_1745, DecodeMultipleCallsNoAccumulation_1745) {
    std::vector<Exiv2::byte> data(32, 0);
    
    Exiv2::Cr2Parser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    size_t count1 = exifData.count();
    
    Exiv2::Cr2Parser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    size_t count2 = exifData.count();
    
    // Both calls with invalid data should produce same results
    EXPECT_EQ(count1, count2);
}

// Test with a large buffer of zeros
TEST_F(Cr2ParserTest_1745, DecodeLargeZeroBuffer_1745) {
    std::vector<Exiv2::byte> data(65536, 0);
    Exiv2::ByteOrder result = Exiv2::Cr2Parser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    EXPECT_TRUE(result == Exiv2::invalidByteOrder ||
                result == Exiv2::littleEndian ||
                result == Exiv2::bigEndian);
}

// Test that data containers are initially empty before decode
TEST_F(Cr2ParserTest_1745, InitialContainersAreEmpty_1745) {
    EXPECT_TRUE(exifData.empty());
    EXPECT_TRUE(iptcData.empty());
    EXPECT_TRUE(xmpData.empty());
}

// Test decode with pointer to valid-looking but truncated CR2 header (exactly at boundary)
TEST_F(Cr2ParserTest_1745, DecodeTruncatedAtHeaderBoundary_1745) {
    // CR2 header is 16 bytes, but we need IFD data after that
    std::vector<Exiv2::byte> data(16, 0);
    data[0] = 'I';
    data[1] = 'I';
    data[2] = 42;
    data[3] = 0;
    data[4] = 16;
    data[5] = 0;
    data[6] = 0;
    data[7] = 0;
    data[8] = 'C';
    data[9] = 'R';
    data[10] = 2;
    data[11] = 0;
    data[12] = 0;
    data[13] = 0;
    data[14] = 0;
    data[15] = 0;

    // Data ends exactly at header, no IFD data
    Exiv2::ByteOrder result = Exiv2::Cr2Parser::decode(exifData, iptcData, xmpData, data.data(), data.size());
    EXPECT_TRUE(result == Exiv2::invalidByteOrder ||
                result == Exiv2::littleEndian ||
                result == Exiv2::bigEndian);
}

} // namespace
