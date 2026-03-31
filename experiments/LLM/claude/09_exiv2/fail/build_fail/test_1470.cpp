#include <gtest/gtest.h>
#include <cstring>

// Include necessary Exiv2 headers
#include "makernote_int.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MnHeaderTest_1470 : public ::testing::Test {
protected:
    Nikon3MnHeader header_;
    
    // The Nikon3 makernote signature: "Nikon\0" followed by type info
    // Full signature is: "Nikon\0\2\x10\0\0" (10 bytes) + TIFF header (8 bytes)
    
    // Helper to build a valid Nikon3 makernote header
    std::vector<Exiv2::byte> buildValidHeader(ByteOrder bo = littleEndian) {
        std::vector<Exiv2::byte> data(18, 0);
        
        // Signature: "Nikon\0"
        data[0] = 'N';
        data[1] = 'i';
        data[2] = 'k';
        data[3] = 'o';
        data[4] = 'n';
        data[5] = '\0';
        
        // Version info
        data[6] = 0x02;
        data[7] = 0x10;
        data[8] = 0x00;
        data[9] = 0x00;
        
        // TIFF header at offset 10
        if (bo == littleEndian) {
            data[10] = 'I';
            data[11] = 'I';
        } else {
            data[10] = 'M';
            data[11] = 'M';
        }
        
        // TIFF magic number 42
        if (bo == littleEndian) {
            data[12] = 0x2A;
            data[13] = 0x00;
        } else {
            data[12] = 0x00;
            data[13] = 0x2A;
        }
        
        // Offset to first IFD (typically 8)
        if (bo == littleEndian) {
            data[14] = 0x08;
            data[15] = 0x00;
            data[16] = 0x00;
            data[17] = 0x00;
        } else {
            data[14] = 0x00;
            data[15] = 0x00;
            data[16] = 0x00;
            data[17] = 0x08;
        }
        
        return data;
    }
};

// Test that read returns false when passed a null pointer
TEST_F(Nikon3MnHeaderTest_1470, ReadNullPointerReturnsFalse_1470) {
    bool result = header_.read(nullptr, 100, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when size is too small (less than signature size)
TEST_F(Nikon3MnHeaderTest_1470, ReadTooSmallSizeReturnsFalse_1470) {
    std::vector<Exiv2::byte> data(5, 0);
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when size is zero
TEST_F(Nikon3MnHeaderTest_1470, ReadZeroSizeReturnsFalse_1470) {
    Exiv2::byte data[1] = {0};
    bool result = header_.read(data, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when signature doesn't match
TEST_F(Nikon3MnHeaderTest_1470, ReadWrongSignatureReturnsFalse_1470) {
    std::vector<Exiv2::byte> data(18, 0);
    data[0] = 'C';
    data[1] = 'a';
    data[2] = 'n';
    data[3] = 'o';
    data[4] = 'n';
    data[5] = '\0';
    
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read succeeds with a valid little-endian header
TEST_F(Nikon3MnHeaderTest_1470, ReadValidLittleEndianHeaderSucceeds_1470) {
    auto data = buildValidHeader(littleEndian);
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_TRUE(result);
}

// Test that read succeeds with a valid big-endian header
TEST_F(Nikon3MnHeaderTest_1470, ReadValidBigEndianHeaderSucceeds_1470) {
    auto data = buildValidHeader(bigEndian);
    bool result = header_.read(data.data(), data.size(), bigEndian);
    EXPECT_TRUE(result);
}

// Test that read returns false when signature is partially correct
TEST_F(Nikon3MnHeaderTest_1470, ReadPartiallyCorrectSignatureReturnsFalse_1470) {
    auto data = buildValidHeader(littleEndian);
    // Corrupt one byte of the "Nikon\0" signature
    data[3] = 'X';
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when TIFF header within the data is invalid
TEST_F(Nikon3MnHeaderTest_1470, ReadInvalidTiffHeaderReturnsFalse_1470) {
    auto data = buildValidHeader(littleEndian);
    // Corrupt the TIFF magic number
    data[10] = 'X';
    data[11] = 'X';
    data[12] = 0x00;
    data[13] = 0x00;
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read returns false when data has correct signature but is too short for TIFF header
TEST_F(Nikon3MnHeaderTest_1470, ReadSignatureOkButTooShortForTiffReturnsFalse_1470) {
    // Build data that has just the signature but not enough for TIFF header
    std::vector<Exiv2::byte> data(12, 0);
    data[0] = 'N';
    data[1] = 'i';
    data[2] = 'k';
    data[3] = 'o';
    data[4] = 'n';
    data[5] = '\0';
    data[6] = 0x02;
    data[7] = 0x10;
    data[8] = 0x00;
    data[9] = 0x00;
    // Only 2 bytes of TIFF header - not enough
    data[10] = 'I';
    data[11] = 'I';
    
    // This might return false because the TIFF header can't be read from only 2 bytes
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read handles exactly the minimum valid size
TEST_F(Nikon3MnHeaderTest_1470, ReadExactMinimumValidSize_1470) {
    auto data = buildValidHeader(littleEndian);
    // 18 bytes = 10 (signature) + 8 (TIFF header)
    bool result = header_.read(data.data(), 18, littleEndian);
    EXPECT_TRUE(result);
}

// Test that read returns false with TIFF header having wrong magic number (42)
TEST_F(Nikon3MnHeaderTest_1470, ReadTiffWrongMagicNumberReturnsFalse_1470) {
    auto data = buildValidHeader(littleEndian);
    // Set magic number to something other than 42
    data[12] = 0x00;
    data[13] = 0x00;
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that the byte order reported by header matches what's in the TIFF header
TEST_F(Nikon3MnHeaderTest_1470, ByteOrderMatchesTiffHeaderLE_1470) {
    auto data = buildValidHeader(littleEndian);
    ASSERT_TRUE(header_.read(data.data(), data.size(), littleEndian));
    EXPECT_EQ(header_.byteOrder(), littleEndian);
}

// Test that the byte order reported by header matches big-endian TIFF header
TEST_F(Nikon3MnHeaderTest_1470, ByteOrderMatchesTiffHeaderBE_1470) {
    auto data = buildValidHeader(bigEndian);
    ASSERT_TRUE(header_.read(data.data(), data.size(), bigEndian));
    EXPECT_EQ(header_.byteOrder(), bigEndian);
}

// Test that start() returns expected offset after successful read
TEST_F(Nikon3MnHeaderTest_1470, StartOffsetAfterSuccessfulRead_1470) {
    auto data = buildValidHeader(littleEndian);
    ASSERT_TRUE(header_.read(data.data(), data.size(), littleEndian));
    // start_ = 10 + th.offset(), where th.offset() is 8 (the offset in our TIFF header)
    EXPECT_EQ(header_.start(), static_cast<uint32_t>(10 + 8));
}

// Test that sizeOfSignature returns expected value
TEST_F(Nikon3MnHeaderTest_1470, SizeOfSignature_1470) {
    // The sizeOfSignature should return the size of the Nikon3 header signature
    // Based on the code, it checks 6 bytes for "Nikon\0" and allocates sizeOfSignature() bytes
    // The signature area is typically 10 bytes
    uint32_t sigSize = header_.size();
    // Just verify it's a reasonable positive value
    EXPECT_GT(sigSize, 0u);
}

// Test reading with all zeros (wrong signature)
TEST_F(Nikon3MnHeaderTest_1470, ReadAllZerosReturnsFalse_1470) {
    std::vector<Exiv2::byte> data(100, 0);
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that reading with extra data beyond minimum still works
TEST_F(Nikon3MnHeaderTest_1470, ReadWithExtraDataSucceeds_1470) {
    auto data = buildValidHeader(littleEndian);
    // Add extra bytes
    data.resize(100, 0);
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_TRUE(result);
}

// Test reading with the 6th byte of signature not being null
TEST_F(Nikon3MnHeaderTest_1470, ReadSignatureSixthByteNotNullReturnsFalse_1470) {
    auto data = buildValidHeader(littleEndian);
    data[5] = 'X'; // Should be '\0'
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}
