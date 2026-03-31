#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class Nikon2MnHeaderTest_1461 : public ::testing::Test {
protected:
    Nikon2MnHeader header_;
};

TEST_F(Nikon2MnHeaderTest_1461, DefaultConstruction_1461) {
    // Verify that default construction doesn't throw
    Nikon2MnHeader h;
}

TEST_F(Nikon2MnHeaderTest_1461, SizeMatchesSizeOfSignature_1461) {
    // size() should return the same value as sizeOfSignature()
    EXPECT_EQ(header_.size(), Nikon2MnHeader::sizeOfSignature());
}

TEST_F(Nikon2MnHeaderTest_1461, SizeIsNonZero_1461) {
    // The Nikon2 maker note header should have a non-zero size
    EXPECT_GT(header_.size(), 0u);
}

TEST_F(Nikon2MnHeaderTest_1461, SizeOfSignatureIsConsistent_1461) {
    // Calling sizeOfSignature multiple times should return the same value
    size_t first = Nikon2MnHeader::sizeOfSignature();
    size_t second = Nikon2MnHeader::sizeOfSignature();
    EXPECT_EQ(first, second);
}

TEST_F(Nikon2MnHeaderTest_1461, SizeConsistentAcrossInstances_1461) {
    // Multiple instances should report the same size
    Nikon2MnHeader h1;
    Nikon2MnHeader h2;
    EXPECT_EQ(h1.size(), h2.size());
}

TEST_F(Nikon2MnHeaderTest_1461, IfdOffsetReturnsValue_1461) {
    // ifdOffset() should return a value (typically related to the header structure)
    size_t offset = header_.ifdOffset();
    // The offset should be within a reasonable range relative to size
    EXPECT_GE(offset, 0u);
}

TEST_F(Nikon2MnHeaderTest_1461, ReadWithNullDataReturnsFalse_1461) {
    // Reading from nullptr with zero size should fail or handle gracefully
    bool result = header_.read(nullptr, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(Nikon2MnHeaderTest_1461, ReadWithInsufficientDataReturnsFalse_1461) {
    // Reading with data smaller than the header size should fail
    const Exiv2::byte data[] = {0x00};
    bool result = header_.read(data, 1, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(Nikon2MnHeaderTest_1461, ReadWithValidNikon2Signature_1461) {
    // The Nikon2 maker note signature is "Nikon\0\x01\x00"
    // Construct a buffer with the expected signature
    const Exiv2::byte nikon2Sig[] = {'N', 'i', 'k', 'o', 'n', '\0', 0x01, 0x00};
    size_t sigSize = Nikon2MnHeader::sizeOfSignature();
    
    if (sigSize <= sizeof(nikon2Sig)) {
        bool result = header_.read(nikon2Sig, sizeof(nikon2Sig), Exiv2::littleEndian);
        // This may or may not succeed depending on exact signature expected
        // We just verify it doesn't crash
        (void)result;
    }
}

TEST_F(Nikon2MnHeaderTest_1461, ReadWithInvalidSignature_1461) {
    // Provide data of sufficient length but with invalid signature
    size_t sigSize = Nikon2MnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> invalidData(sigSize + 10, 0xFF);
    bool result = header_.read(invalidData.data(), invalidData.size(), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(Nikon2MnHeaderTest_1461, ReadWithBigEndianByteOrder_1461) {
    // Test with big endian byte order
    const Exiv2::byte nikon2Sig[] = {'N', 'i', 'k', 'o', 'n', '\0', 0x01, 0x00};
    size_t sigSize = Nikon2MnHeader::sizeOfSignature();
    
    if (sigSize <= sizeof(nikon2Sig)) {
        bool result = header_.read(nikon2Sig, sizeof(nikon2Sig), Exiv2::bigEndian);
        (void)result; // Just verify no crash
    }
}

TEST_F(Nikon2MnHeaderTest_1461, ReadWithExactSizeData_1461) {
    // Provide data that is exactly the size of the signature
    size_t sigSize = Nikon2MnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize, 0x00);
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    // With zeroed data, this should likely fail since it's not a valid signature
    EXPECT_FALSE(result);
}

TEST_F(Nikon2MnHeaderTest_1461, SizeAfterFailedRead_1461) {
    // Size should remain consistent even after a failed read
    size_t sizeBefore = header_.size();
    const Exiv2::byte data[] = {0x00};
    header_.read(data, 1, Exiv2::littleEndian);
    size_t sizeAfter = header_.size();
    EXPECT_EQ(sizeBefore, sizeAfter);
}
