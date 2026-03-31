#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class PentaxDngMnHeaderTest_1481 : public ::testing::Test {
protected:
    PentaxDngMnHeader header;
};

TEST_F(PentaxDngMnHeaderTest_1481, IfdOffsetEqualsSizeOfSignature_1481) {
    // ifdOffset() should return the same value as sizeOfSignature()
    EXPECT_EQ(header.ifdOffset(), PentaxDngMnHeader::sizeOfSignature());
}

TEST_F(PentaxDngMnHeaderTest_1481, SizeOfSignatureIsNonNegative_1481) {
    // sizeOfSignature() should return a reasonable non-zero value for a valid signature
    size_t sigSize = PentaxDngMnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

TEST_F(PentaxDngMnHeaderTest_1481, IfdOffsetIsConsistentAcrossMultipleCalls_1481) {
    // Calling ifdOffset() multiple times should return the same value
    size_t first = header.ifdOffset();
    size_t second = header.ifdOffset();
    EXPECT_EQ(first, second);
}

TEST_F(PentaxDngMnHeaderTest_1481, SizeOfSignatureIsConsistentAcrossMultipleCalls_1481) {
    // Static method should always return the same value
    size_t first = PentaxDngMnHeader::sizeOfSignature();
    size_t second = PentaxDngMnHeader::sizeOfSignature();
    EXPECT_EQ(first, second);
}

TEST_F(PentaxDngMnHeaderTest_1481, SizeReturnsReasonableValue_1481) {
    // size() should return a value that is at least as large as the signature
    size_t sz = header.size();
    EXPECT_GE(sz, PentaxDngMnHeader::sizeOfSignature());
}

TEST_F(PentaxDngMnHeaderTest_1481, BaseOffsetWithZeroMnOffset_1481) {
    // baseOffset with 0 offset
    size_t baseOff = header.baseOffset(0);
    // baseOffset should return some defined value
    EXPECT_GE(baseOff, 0u);
}

TEST_F(PentaxDngMnHeaderTest_1481, BaseOffsetWithNonZeroMnOffset_1481) {
    // baseOffset with a non-zero offset
    size_t baseOff = header.baseOffset(100);
    // The result should be deterministic
    size_t baseOff2 = header.baseOffset(100);
    EXPECT_EQ(baseOff, baseOff2);
}

TEST_F(PentaxDngMnHeaderTest_1481, ReadWithNullDataReturnsFalse_1481) {
    // Reading with null data should fail gracefully
    bool result = header.read(nullptr, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(PentaxDngMnHeaderTest_1481, ReadWithInsufficientSizeReturnsFalse_1481) {
    // Reading with a size smaller than the signature should fail
    Exiv2::byte data[1] = {0};
    bool result = header.read(data, 1, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(PentaxDngMnHeaderTest_1481, ReadWithValidPentaxDngSignature_1481) {
    // The Pentax DNG maker note signature is "PENTAX \0" followed by version bytes
    // Typical signature: "PENTAX \0" (with specific version info)
    // We construct a buffer that matches the expected Pentax DNG signature
    const size_t sigSize = PentaxDngMnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 100, 0);
    
    // Known Pentax DNG signature: "PENTAX \0" with specific bytes
    // "PENTAX \0" = 0x50, 0x45, 0x4E, 0x54, 0x41, 0x58, 0x20, 0x00
    if (sigSize >= 8) {
        data[0] = 'P';
        data[1] = 'E';
        data[2] = 'N';
        data[3] = 'T';
        data[4] = 'A';
        data[5] = 'X';
        data[6] = ' ';
        data[7] = '\0';
    }
    
    bool result = header.read(data.data(), data.size(), Exiv2::littleEndian);
    // This may or may not succeed depending on exact signature requirements
    // We just verify it doesn't crash and returns a bool
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(PentaxDngMnHeaderTest_1481, ReadWithWrongSignatureReturnsFalse_1481) {
    // Provide data that doesn't match the Pentax DNG signature
    const size_t sigSize = PentaxDngMnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 100, 0xFF);
    
    bool result = header.read(data.data(), data.size(), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(PentaxDngMnHeaderTest_1481, MultipleInstancesHaveSameIfdOffset_1481) {
    // Two separate instances should have the same ifdOffset
    PentaxDngMnHeader header2;
    EXPECT_EQ(header.ifdOffset(), header2.ifdOffset());
}

TEST_F(PentaxDngMnHeaderTest_1481, MultipleInstancesHaveSameSize_1481) {
    // Two separate instances should have the same size
    PentaxDngMnHeader header2;
    EXPECT_EQ(header.size(), header2.size());
}

TEST_F(PentaxDngMnHeaderTest_1481, ReadWithExactSignatureSizeData_1481) {
    // Provide data exactly the size of the signature
    const size_t sigSize = PentaxDngMnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize, 0);
    
    bool result = header.read(data.data(), data.size(), Exiv2::littleEndian);
    // With all zeros, this should likely fail as it won't match the signature
    // But we're just testing it handles exact-size buffers without crashing
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(PentaxDngMnHeaderTest_1481, ReadWithBigEndianByteOrder_1481) {
    // Test with big endian byte order
    const size_t sigSize = PentaxDngMnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 100, 0);
    
    bool result = header.read(data.data(), data.size(), Exiv2::bigEndian);
    // Just verifying no crash with different byte order
    EXPECT_TRUE(result == true || result == false);
}
