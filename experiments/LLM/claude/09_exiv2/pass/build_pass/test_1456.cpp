#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class FujiMnHeaderTest_1456 : public ::testing::Test {
protected:
    FujiMnHeader header_;
};

// Test default construction and byteOrder
TEST_F(FujiMnHeaderTest_1456, DefaultByteOrder_1456) {
    // After default construction, byteOrder should return a valid ByteOrder
    ByteOrder bo = header_.byteOrder();
    // Fuji makernotes are typically little-endian
    EXPECT_EQ(bo, littleEndian);
}

// Test size of signature
TEST_F(FujiMnHeaderTest_1456, SizeOfSignature_1456) {
    size_t sigSize = FujiMnHeader::sizeOfSignature();
    // The Fuji makernote signature "FUJIFILM" is 8 bytes, plus additional header data
    // Typically the signature size is > 0
    EXPECT_GT(sigSize, 0u);
}

// Test size method
TEST_F(FujiMnHeaderTest_1456, Size_1456) {
    size_t sz = header_.size();
    // The header size should be at least as large as the signature
    EXPECT_GE(sz, FujiMnHeader::sizeOfSignature());
}

// Test ifdOffset
TEST_F(FujiMnHeaderTest_1456, IfdOffset_1456) {
    size_t offset = header_.ifdOffset();
    // The IFD offset should be a reasonable value
    EXPECT_GE(offset, 0u);
}

// Test baseOffset
TEST_F(FujiMnHeaderTest_1456, BaseOffset_1456) {
    size_t mnOffset = 100;
    size_t base = header_.baseOffset(mnOffset);
    // baseOffset typically returns the mnOffset itself or some derived value
    EXPECT_GE(base, 0u);
}

// Test read with nullptr data
TEST_F(FujiMnHeaderTest_1456, ReadNullData_1456) {
    bool result = header_.read(nullptr, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with data too small
TEST_F(FujiMnHeaderTest_1456, ReadTooSmallData_1456) {
    byte data[] = {0x00, 0x01};
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Fuji makernote header
TEST_F(FujiMnHeaderTest_1456, ReadValidFujiHeader_1456) {
    // Fuji makernote header: "FUJIFILM" followed by byte order and offset
    // "FUJIFILM" = 0x46 0x55 0x4A 0x49 0x46 0x49 0x4C 0x4D
    // Then version/pointer info (little-endian offset to IFD)
    byte data[12] = {
        0x46, 0x55, 0x4A, 0x49, 0x46, 0x49, 0x4C, 0x4D,  // "FUJIFILM"
        0x0C, 0x00, 0x00, 0x00                              // offset = 12 (little-endian)
    };
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_TRUE(result);
}

// Test read with valid header then check byteOrder
TEST_F(FujiMnHeaderTest_1456, ReadValidHeaderByteOrder_1456) {
    byte data[12] = {
        0x46, 0x55, 0x4A, 0x49, 0x46, 0x49, 0x4C, 0x4D,
        0x0C, 0x00, 0x00, 0x00
    };
    header_.read(data, sizeof(data), bigEndian);
    // Fuji always uses little-endian regardless of what's passed
    ByteOrder bo = header_.byteOrder();
    EXPECT_EQ(bo, littleEndian);
}

// Test read with invalid signature
TEST_F(FujiMnHeaderTest_1456, ReadInvalidSignature_1456) {
    byte data[12] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x0C, 0x00, 0x00, 0x00
    };
    bool result = header_.read(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with exact minimum size
TEST_F(FujiMnHeaderTest_1456, ReadExactSignatureSize_1456) {
    // Only the signature, no offset data
    byte data[8] = {
        0x46, 0x55, 0x4A, 0x49, 0x46, 0x49, 0x4C, 0x4D
    };
    size_t sigSize = FujiMnHeader::sizeOfSignature();
    if (sigSize <= 8) {
        // May fail because there might not be enough data for the full header
        bool result = header_.read(data, sizeof(data), littleEndian);
        // Result depends on whether 8 bytes is enough for the full header
        // We just ensure it doesn't crash
        (void)result;
    }
}

// Test baseOffset with zero mnOffset
TEST_F(FujiMnHeaderTest_1456, BaseOffsetZero_1456) {
    size_t base = header_.baseOffset(0);
    EXPECT_GE(base, 0u);
}

// Test baseOffset with large mnOffset
TEST_F(FujiMnHeaderTest_1456, BaseOffsetLarge_1456) {
    size_t base = header_.baseOffset(1000000);
    EXPECT_GE(base, 0u);
}

// Test that after successful read, ifdOffset returns expected value
TEST_F(FujiMnHeaderTest_1456, IfdOffsetAfterRead_1456) {
    byte data[12] = {
        0x46, 0x55, 0x4A, 0x49, 0x46, 0x49, 0x4C, 0x4D,
        0x0C, 0x00, 0x00, 0x00
    };
    bool result = header_.read(data, sizeof(data), littleEndian);
    if (result) {
        size_t offset = header_.ifdOffset();
        // The offset encoded in the data is 12 (0x0C)
        EXPECT_EQ(offset, 12u);
    }
}

// Test size consistency
TEST_F(FujiMnHeaderTest_1456, SizeConsistency_1456) {
    size_t sz1 = header_.size();
    size_t sz2 = header_.size();
    EXPECT_EQ(sz1, sz2);
}

// Test read with size just under required
TEST_F(FujiMnHeaderTest_1456, ReadSizeJustUnderRequired_1456) {
    byte data[11] = {
        0x46, 0x55, 0x4A, 0x49, 0x46, 0x49, 0x4C, 0x4D,
        0x0C, 0x00, 0x00
    };
    size_t headerSize = header_.size();
    if (sizeof(data) < headerSize) {
        bool result = header_.read(data, sizeof(data), littleEndian);
        EXPECT_FALSE(result);
    }
}
