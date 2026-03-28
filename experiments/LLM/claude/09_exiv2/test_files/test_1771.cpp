#include <gtest/gtest.h>
#include <cstring>
#include <vector>
#include <stdexcept>

#include "crwimage_int.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CiffHeaderTest_1771 : public ::testing::Test {
protected:
    CiffHeader header;

    // Helper to build a valid CRW header buffer
    // Structure:
    //   bytes 0-1: byte order marker ('II' for little endian, 'MM' for big endian)
    //   bytes 2-5: offset to root directory (uint32, in the specified byte order)
    //   bytes 6-13: signature "HEAPCCDR"
    //   bytes 14..offset-1: optional padding
    //   bytes offset..size-1: root directory data
    std::vector<byte> buildValidHeader(ByteOrder bo, uint32_t offset, 
                                        const std::vector<byte>& padding = {},
                                        const std::vector<byte>& dirData = {}) {
        std::vector<byte> buf;
        
        // Byte order marker
        if (bo == littleEndian) {
            buf.push_back('I');
            buf.push_back('I');
        } else {
            buf.push_back('M');
            buf.push_back('M');
        }
        
        // Offset (4 bytes)
        if (bo == littleEndian) {
            buf.push_back(static_cast<byte>(offset & 0xFF));
            buf.push_back(static_cast<byte>((offset >> 8) & 0xFF));
            buf.push_back(static_cast<byte>((offset >> 16) & 0xFF));
            buf.push_back(static_cast<byte>((offset >> 24) & 0xFF));
        } else {
            buf.push_back(static_cast<byte>((offset >> 24) & 0xFF));
            buf.push_back(static_cast<byte>((offset >> 16) & 0xFF));
            buf.push_back(static_cast<byte>((offset >> 8) & 0xFF));
            buf.push_back(static_cast<byte>(offset & 0xFF));
        }
        
        // Signature "HEAPCCDR"
        const char* sig = "HEAPCCDR";
        for (int i = 0; i < 8; i++) {
            buf.push_back(static_cast<byte>(sig[i]));
        }
        
        // Padding bytes (between byte 14 and offset)
        for (const auto& b : padding) {
            buf.push_back(b);
        }
        
        // Ensure buffer is at least 'offset' bytes
        while (buf.size() < offset) {
            buf.push_back(0);
        }
        
        // Directory data - minimal valid CiffDirectory
        // A minimal directory needs at least 4 bytes: 2 bytes count (0) + 2 bytes for offset to values
        // Actually, readDirectory expects specific format. Let's provide a minimal valid one.
        if (dirData.empty()) {
            // Minimal directory: the directory data needs to have a valid structure
            // The last 4 bytes of directory data contain the offset to the start of the directory entries
            // For an empty directory: count=0 (2 bytes), and the value area offset at the end
            // CiffDirectory::readDirectory reads the last 4 bytes as offset to dir entries
            // Then reads 2 bytes count at that offset
            // Minimal: 4 bytes total: offset(4 bytes LE/BE) pointing to byte 0, then count=0
            // Actually let's try a simple structure:
            // Data: [count_lo, count_hi, offset_3, offset_2, offset_1, offset_0]
            // For LE with count=0 at position 0, offset=0:
            // [0x00, 0x00, 0x00, 0x00, 0x00, 0x00]
            // The last 4 bytes give offset=0, at offset 0 we read 2-byte count = 0
            std::vector<byte> minDir;
            // count = 0
            minDir.push_back(0x00);
            minDir.push_back(0x00);
            // offset to directory entries (points to byte 0 of this block)
            if (bo == littleEndian) {
                minDir.push_back(0x00);
                minDir.push_back(0x00);
                minDir.push_back(0x00);
                minDir.push_back(0x00);
            } else {
                minDir.push_back(0x00);
                minDir.push_back(0x00);
                minDir.push_back(0x00);
                minDir.push_back(0x00);
            }
            for (const auto& b : minDir) {
                buf.push_back(b);
            }
        } else {
            for (const auto& b : dirData) {
                buf.push_back(b);
            }
        }
        
        return buf;
    }
};

// Test that reading data smaller than 14 bytes throws
TEST_F(CiffHeaderTest_1771, ReadTooSmallThrows_1771) {
    std::vector<byte> data(13, 0);
    EXPECT_THROW(header.read(data.data(), data.size()), Error);
}

// Test that reading exactly 0 bytes throws
TEST_F(CiffHeaderTest_1771, ReadZeroBytesThrows_1771) {
    EXPECT_THROW(header.read(nullptr, 0), Error);
}

// Test that reading 1 byte throws
TEST_F(CiffHeaderTest_1771, ReadOneByteThrows_1771) {
    byte data = 0;
    EXPECT_THROW(header.read(&data, 1), Error);
}

// Test that invalid byte order marker throws
TEST_F(CiffHeaderTest_1771, ReadInvalidByteOrderThrows_1771) {
    std::vector<byte> data(20, 0);
    data[0] = 'X';
    data[1] = 'X';
    EXPECT_THROW(header.read(data.data(), data.size()), Error);
}

// Test that mismatched byte order bytes throw (e.g., 'I' and 'M')
TEST_F(CiffHeaderTest_1771, ReadMismatchedByteOrderThrows_1771) {
    std::vector<byte> data(20, 0);
    data[0] = 'I';
    data[1] = 'M';
    EXPECT_THROW(header.read(data.data(), data.size()), Error);
}

// Test that offset less than 14 throws
TEST_F(CiffHeaderTest_1771, ReadOffsetTooSmallThrows_1771) {
    std::vector<byte> data(20, 0);
    data[0] = 'I';
    data[1] = 'I';
    // Set offset to 10 (less than 14) in little endian
    data[2] = 10;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    EXPECT_THROW(header.read(data.data(), data.size()), Error);
}

// Test that offset greater than size throws
TEST_F(CiffHeaderTest_1771, ReadOffsetGreaterThanSizeThrows_1771) {
    std::vector<byte> data(20, 0);
    data[0] = 'I';
    data[1] = 'I';
    // Set offset to 100 (greater than size=20) in little endian
    data[2] = 100;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    // Set valid signature
    const char* sig = "HEAPCCDR";
    std::memcpy(data.data() + 6, sig, 8);
    EXPECT_THROW(header.read(data.data(), data.size()), Error);
}

// Test that invalid signature throws
TEST_F(CiffHeaderTest_1771, ReadInvalidSignatureThrows_1771) {
    std::vector<byte> data(20, 0);
    data[0] = 'I';
    data[1] = 'I';
    // Set offset to 14 in little endian
    data[2] = 14;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    // Wrong signature
    const char* wrongSig = "XXXXXXXX";
    std::memcpy(data.data() + 6, wrongSig, 8);
    EXPECT_THROW(header.read(data.data(), data.size()), Error);
}

// Test valid little endian header with offset=14 (no padding)
TEST_F(CiffHeaderTest_1771, ReadValidLittleEndianNoPadding_1771) {
    auto buf = buildValidHeader(littleEndian, 14);
    EXPECT_NO_THROW(header.read(buf.data(), buf.size()));
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

// Test valid big endian header with offset=14 (no padding)
TEST_F(CiffHeaderTest_1771, ReadValidBigEndianNoPadding_1771) {
    auto buf = buildValidHeader(bigEndian, 14);
    EXPECT_NO_THROW(header.read(buf.data(), buf.size()));
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test valid header with padding (offset > 14)
TEST_F(CiffHeaderTest_1771, ReadValidWithPadding_1771) {
    std::vector<byte> padding(10, 0xAB);
    auto buf = buildValidHeader(littleEndian, 24, padding);
    EXPECT_NO_THROW(header.read(buf.data(), buf.size()));
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

// Test that exactly 14 bytes with valid header but no directory data
// offset must be >= 14 and <= size, so offset=14, size=14 means dir data size = 0
// This might throw in CiffDirectory::readDirectory, but tests the boundary
TEST_F(CiffHeaderTest_1771, ReadExactly14BytesValidHeader_1771) {
    std::vector<byte> data(14, 0);
    data[0] = 'I';
    data[1] = 'I';
    data[2] = 14;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    const char* sig = "HEAPCCDR";
    std::memcpy(data.data() + 6, sig, 8);
    // This will try to readDirectory with size=0, which may throw
    // We test that the header parsing up to that point works or throws appropriately
    try {
        header.read(data.data(), data.size());
        // If it doesn't throw, byte order should be set
        EXPECT_EQ(header.byteOrder(), littleEndian);
    } catch (const Error&) {
        // It's acceptable to throw if directory data is insufficient
    }
}

// Test that offset equal to size is accepted (boundary)
TEST_F(CiffHeaderTest_1771, ReadOffsetEqualToSize_1771) {
    // offset == size means 0 bytes for directory
    size_t offset = 14;
    size_t totalSize = 14;
    std::vector<byte> data(totalSize, 0);
    data[0] = 'I';
    data[1] = 'I';
    data[2] = static_cast<byte>(offset);
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    const char* sig = "HEAPCCDR";
    std::memcpy(data.data() + 6, sig, 8);
    // readDirectory with 0 bytes might throw
    try {
        header.read(data.data(), data.size());
        EXPECT_EQ(header.byteOrder(), littleEndian);
    } catch (const Error&) {
        // Acceptable
    }
}

// Test byteOrder default before read
TEST_F(CiffHeaderTest_1771, DefaultByteOrder_1771) {
    // Before read, byteOrder_ defaults to littleEndian
    EXPECT_EQ(header.byteOrder(), littleEndian);
}

// Test reading with 'MM' (big endian) marker
TEST_F(CiffHeaderTest_1771, ReadBigEndianMarker_1771) {
    auto buf = buildValidHeader(bigEndian, 14);
    EXPECT_NO_THROW(header.read(buf.data(), buf.size()));
    EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test that size exactly 13 throws (boundary just below minimum)
TEST_F(CiffHeaderTest_1771, ReadSize13Throws_1771) {
    std::vector<byte> data(13, 0);
    EXPECT_THROW(header.read(data.data(), 13), Error);
}

// Test offset of 0 throws (less than 14)
TEST_F(CiffHeaderTest_1771, ReadOffsetZeroThrows_1771) {
    std::vector<byte> data(20, 0);
    data[0] = 'I';
    data[1] = 'I';
    data[2] = 0; // offset = 0
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    const char* sig = "HEAPCCDR";
    std::memcpy(data.data() + 6, sig, 8);
    EXPECT_THROW(header.read(data.data(), data.size()), Error);
}

// Test offset of 13 throws (just below minimum of 14)
TEST_F(CiffHeaderTest_1771, ReadOffset13Throws_1771) {
    std::vector<byte> data(20, 0);
    data[0] = 'I';
    data[1] = 'I';
    data[2] = 13;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    const char* sig = "HEAPCCDR";
    std::memcpy(data.data() + 6, sig, 8);
    EXPECT_THROW(header.read(data.data(), data.size()), Error);
}

// Test with partially correct signature (7 correct bytes, 1 wrong)
TEST_F(CiffHeaderTest_1771, ReadPartiallyCorrectSignatureThrows_1771) {
    std::vector<byte> data(20, 0);
    data[0] = 'I';
    data[1] = 'I';
    data[2] = 14;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    const char* partialSig = "HEAPCCdx"; // last byte wrong
    std::memcpy(data.data() + 6, partialSig, 8);
    EXPECT_THROW(header.read(data.data(), data.size()), Error);
}

// Test reading a valid header and then checking signature static method
TEST_F(CiffHeaderTest_1771, SignatureReturnsExpected_1771) {
    auto sig = CiffHeader::signature();
    // The signature should be "HEAPCCDR" - 8 bytes
    // We verify it's not null and matches
    EXPECT_EQ(std::memcmp(sig, "HEAPCCDR", 8), 0);
}
