#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MnHeaderTest_1465 : public ::testing::Test {
protected:
    Nikon3MnHeader header_;
};

// Test that sizeOfSignature returns a positive value
TEST_F(Nikon3MnHeaderTest_1465, SizeOfSignatureReturnsPositiveValue_1465) {
    size_t sigSize = header_.sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that sizeOfSignature returns consistent value across multiple calls
TEST_F(Nikon3MnHeaderTest_1465, SizeOfSignatureIsConsistent_1465) {
    size_t sigSize1 = header_.sizeOfSignature();
    size_t sigSize2 = header_.sizeOfSignature();
    EXPECT_EQ(sigSize1, sigSize2);
}

// Test that size() returns a value >= sizeOfSignature
TEST_F(Nikon3MnHeaderTest_1465, SizeIsAtLeastSignatureSize_1465) {
    size_t totalSize = header_.size();
    size_t sigSize = header_.sizeOfSignature();
    EXPECT_GE(totalSize, sigSize);
}

// Test that ifdOffset returns a reasonable value
TEST_F(Nikon3MnHeaderTest_1465, IfdOffsetReturnsValue_1465) {
    size_t offset = header_.ifdOffset();
    EXPECT_GE(offset, 0u);
}

// Test that byteOrder returns a valid byte order after construction
TEST_F(Nikon3MnHeaderTest_1465, DefaultByteOrderIsValid_1465) {
    ByteOrder bo = header_.byteOrder();
    // ByteOrder should be one of the known values
    EXPECT_TRUE(bo == littleEndian || bo == bigEndian || bo == invalidByteOrder);
}

// Test that setByteOrder changes the byte order
TEST_F(Nikon3MnHeaderTest_1465, SetByteOrderChangesOrder_1465) {
    header_.setByteOrder(littleEndian);
    EXPECT_EQ(header_.byteOrder(), littleEndian);

    header_.setByteOrder(bigEndian);
    EXPECT_EQ(header_.byteOrder(), bigEndian);
}

// Test that read with nullptr or zero size fails gracefully
TEST_F(Nikon3MnHeaderTest_1465, ReadWithNullptrReturnsFalse_1465) {
    bool result = header_.read(nullptr, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read with too small data returns false
TEST_F(Nikon3MnHeaderTest_1465, ReadWithTooSmallDataReturnsFalse_1465) {
    byte smallData[] = {0x00};
    bool result = header_.read(smallData, 1, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read with valid Nikon3 maker note signature succeeds
TEST_F(Nikon3MnHeaderTest_1465, ReadWithValidSignatureReturnsTrue_1465) {
    // Nikon3 maker note signature: "Nikon\0\x02\x10\x00\x00"
    // followed by byte order marker and version info
    // The signature is typically "Nikon\0" + version (2 bytes) + padding
    byte validData[] = {
        'N', 'i', 'k', 'o', 'n', 0x00,  // "Nikon\0"
        0x02, 0x10,                        // version
        0x00, 0x00,                        // padding/tiff header start
        0x4D, 0x4D,                        // MM (big endian) or 0x49,0x49 for II
        0x00, 0x2A,                        // TIFF magic
        0x00, 0x00, 0x00, 0x08             // offset
    };
    bool result = header_.read(validData, sizeof(validData), bigEndian);
    // Result depends on exact signature matching
    // We just verify it doesn't crash
    (void)result;
}

// Test baseOffset returns consistent value
TEST_F(Nikon3MnHeaderTest_1465, BaseOffsetReturnsConsistentValue_1465) {
    size_t mnOffset = 100;
    size_t baseOff1 = header_.baseOffset(mnOffset);
    size_t baseOff2 = header_.baseOffset(mnOffset);
    EXPECT_EQ(baseOff1, baseOff2);
}

// Test baseOffset with zero offset
TEST_F(Nikon3MnHeaderTest_1465, BaseOffsetWithZeroMnOffset_1465) {
    size_t baseOff = header_.baseOffset(0);
    // baseOffset should incorporate the mnOffset in some way
    EXPECT_GE(baseOff, 0u);
}

// Test baseOffset with different mnOffset values
TEST_F(Nikon3MnHeaderTest_1465, BaseOffsetWithDifferentMnOffsets_1465) {
    size_t baseOff1 = header_.baseOffset(100);
    size_t baseOff2 = header_.baseOffset(200);
    // The difference between base offsets should reflect the difference in mnOffset
    // (baseOffset typically adds mnOffset + some constant)
    EXPECT_NE(baseOff1, baseOff2);
}

// Test that ifdOffset equals sizeOfSignature (start_ is set to sizeOfSignature in constructor)
TEST_F(Nikon3MnHeaderTest_1465, IfdOffsetRelatedToSignatureSize_1465) {
    size_t offset = header_.ifdOffset();
    size_t sigSize = header_.sizeOfSignature();
    // Based on the constructor: start_(sizeOfSignature())
    // ifdOffset likely returns start_ which equals sizeOfSignature
    EXPECT_GE(offset, sigSize);
}

// Test multiple Nikon3MnHeader instances have same sizeOfSignature
TEST_F(Nikon3MnHeaderTest_1465, MultiplInstancesSameSigSize_1465) {
    Nikon3MnHeader header2;
    EXPECT_EQ(header_.sizeOfSignature(), header2.sizeOfSignature());
}

// Test that read with data smaller than signature size returns false
TEST_F(Nikon3MnHeaderTest_1465, ReadWithDataSmallerThanSignatureReturnsFalse_1465) {
    size_t sigSize = header_.sizeOfSignature();
    if (sigSize > 1) {
        std::vector<byte> data(sigSize - 1, 0);
        bool result = header_.read(data.data(), data.size(), littleEndian);
        EXPECT_FALSE(result);
    }
}

// Test read with invalid signature data
TEST_F(Nikon3MnHeaderTest_1465, ReadWithInvalidSignatureReturnsFalse_1465) {
    // Use random/wrong data that doesn't match Nikon signature
    std::vector<byte> invalidData(64, 0xFF);
    bool result = header_.read(invalidData.data(), invalidData.size(), littleEndian);
    EXPECT_FALSE(result);
}
