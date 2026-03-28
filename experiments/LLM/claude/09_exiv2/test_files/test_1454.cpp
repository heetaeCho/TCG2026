#include <gtest/gtest.h>
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class FujiMnHeaderTest_1454 : public ::testing::Test {
protected:
    FujiMnHeader header_;
};

// Test that default-constructed header has a non-zero size (signature + offset)
TEST_F(FujiMnHeaderTest_1454, DefaultConstructorSize_1454) {
    // FujiMnHeader should have a known header size after construction
    EXPECT_GT(header_.size(), 0u);
}

// Test that sizeOfSignature returns a positive value
TEST_F(FujiMnHeaderTest_1454, SizeOfSignature_1454) {
    size_t sigSize = FujiMnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that size() is consistent across multiple calls
TEST_F(FujiMnHeaderTest_1454, SizeIsConsistent_1454) {
    size_t s1 = header_.size();
    size_t s2 = header_.size();
    EXPECT_EQ(s1, s2);
}

// Test that byteOrder returns littleEndian for Fuji (Fuji uses Intel byte order)
TEST_F(FujiMnHeaderTest_1454, DefaultByteOrder_1454) {
    ByteOrder bo = header_.byteOrder();
    EXPECT_EQ(bo, littleEndian);
}

// Test that ifdOffset returns a value (typically 12 for Fuji)
TEST_F(FujiMnHeaderTest_1454, DefaultIfdOffset_1454) {
    size_t offset = header_.ifdOffset();
    EXPECT_GT(offset, 0u);
}

// Test read with data that is too small (less than header size)
TEST_F(FujiMnHeaderTest_1454, ReadWithTooSmallData_1454) {
    const byte smallData[] = {0x00, 0x01, 0x02};
    bool result = header_.read(smallData, sizeof(smallData), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with nullptr-like edge case (size 0)
TEST_F(FujiMnHeaderTest_1454, ReadWithZeroSize_1454) {
    const byte dummy = 0;
    bool result = header_.read(&dummy, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Fuji makernote header
TEST_F(FujiMnHeaderTest_1454, ReadWithValidFujiHeader_1454) {
    // Fuji makernote header: "FUJIFILM" followed by a 4-byte offset in little-endian
    // The signature is "FUJIFILM" (8 bytes) + 4 bytes for the IFD offset = 12 bytes
    const byte fujiHeader[] = {
        'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M',  // signature
        0x0C, 0x00, 0x00, 0x00                       // IFD offset = 12 (little-endian)
    };
    bool result = header_.read(fujiHeader, sizeof(fujiHeader), littleEndian);
    EXPECT_TRUE(result);
}

// Test read with valid header and verify ifdOffset after read
TEST_F(FujiMnHeaderTest_1454, IfdOffsetAfterValidRead_1454) {
    const byte fujiHeader[] = {
        'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M',
        0x0C, 0x00, 0x00, 0x00
    };
    header_.read(fujiHeader, sizeof(fujiHeader), littleEndian);
    size_t offset = header_.ifdOffset();
    EXPECT_EQ(offset, 12u);
}

// Test read with invalid signature
TEST_F(FujiMnHeaderTest_1454, ReadWithInvalidSignature_1454) {
    const byte invalidHeader[] = {
        'N', 'O', 'T', 'F', 'U', 'J', 'I', '!',
        0x0C, 0x00, 0x00, 0x00
    };
    bool result = header_.read(invalidHeader, sizeof(invalidHeader), littleEndian);
    EXPECT_FALSE(result);
}

// Test baseOffset returns expected value
TEST_F(FujiMnHeaderTest_1454, BaseOffsetReturnsExpected_1454) {
    size_t mnOffset = 100;
    size_t base = header_.baseOffset(mnOffset);
    // For Fuji, baseOffset should return the mnOffset itself
    EXPECT_EQ(base, mnOffset);
}

// Test baseOffset with zero
TEST_F(FujiMnHeaderTest_1454, BaseOffsetWithZero_1454) {
    size_t base = header_.baseOffset(0);
    EXPECT_EQ(base, 0u);
}

// Test byteOrder is littleEndian regardless of what's passed to read
TEST_F(FujiMnHeaderTest_1454, ByteOrderAfterReadWithBigEndian_1454) {
    const byte fujiHeader[] = {
        'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M',
        0x0C, 0x00, 0x00, 0x00
    };
    header_.read(fujiHeader, sizeof(fujiHeader), bigEndian);
    // Fuji always uses little endian
    EXPECT_EQ(header_.byteOrder(), littleEndian);
}

// Test read with exact minimum size
TEST_F(FujiMnHeaderTest_1454, ReadWithExactMinimumSize_1454) {
    const byte fujiHeader[] = {
        'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M',
        0x0C, 0x00, 0x00, 0x00
    };
    // size() should return the header size
    size_t headerSize = header_.size();
    bool result = header_.read(fujiHeader, headerSize, littleEndian);
    EXPECT_TRUE(result);
}

// Test read with data larger than header
TEST_F(FujiMnHeaderTest_1454, ReadWithLargerData_1454) {
    const byte fujiHeader[] = {
        'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M',
        0x0C, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // extra data
    };
    bool result = header_.read(fujiHeader, sizeof(fujiHeader), littleEndian);
    EXPECT_TRUE(result);
}

// Test ifdOffset with different offset value in header
TEST_F(FujiMnHeaderTest_1454, IfdOffsetWithCustomValue_1454) {
    const byte fujiHeader[] = {
        'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M',
        0x20, 0x00, 0x00, 0x00  // IFD offset = 32
    };
    bool readOk = header_.read(fujiHeader, sizeof(fujiHeader), littleEndian);
    if (readOk) {
        EXPECT_EQ(header_.ifdOffset(), 32u);
    }
}

// Test size of signature is less than or equal to size
TEST_F(FujiMnHeaderTest_1454, SignatureSizeLessOrEqualToTotalSize_1454) {
    EXPECT_LE(FujiMnHeader::sizeOfSignature(), header_.size());
}

// Test read with one byte less than required
TEST_F(FujiMnHeaderTest_1454, ReadWithOneByteLessThanRequired_1454) {
    const byte fujiHeader[] = {
        'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M',
        0x0C, 0x00, 0x00
    };
    size_t headerSize = header_.size();
    if (headerSize > 0) {
        bool result = header_.read(fujiHeader, headerSize - 1, littleEndian);
        EXPECT_FALSE(result);
    }
}
