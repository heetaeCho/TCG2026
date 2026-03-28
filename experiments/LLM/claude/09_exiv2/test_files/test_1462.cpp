#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class Nikon2MnHeaderTest_1462 : public ::testing::Test {
protected:
    Nikon2MnHeader header_;
};

// Test that a default-constructed Nikon2MnHeader returns a known ifdOffset
TEST_F(Nikon2MnHeaderTest_1462, DefaultIfdOffset_1462) {
    size_t offset = header_.ifdOffset();
    // The ifdOffset should return the value of start_, which for Nikon2MnHeader
    // is typically 8 (size of the "Nikon\0\x01\x00" signature)
    EXPECT_EQ(offset, 8u);
}

// Test that size() returns the expected header size
TEST_F(Nikon2MnHeaderTest_1462, DefaultSize_1462) {
    size_t sz = header_.size();
    // Nikon2 maker note header size should match the signature size
    EXPECT_GT(sz, 0u);
}

// Test that sizeOfSignature() returns a non-zero value
TEST_F(Nikon2MnHeaderTest_1462, SizeOfSignature_1462) {
    size_t sigSize = Nikon2MnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that size() and sizeOfSignature() are consistent
TEST_F(Nikon2MnHeaderTest_1462, SizeConsistentWithSignature_1462) {
    size_t sz = header_.size();
    size_t sigSize = Nikon2MnHeader::sizeOfSignature();
    EXPECT_EQ(sz, sigSize);
}

// Test that read fails with nullptr data
TEST_F(Nikon2MnHeaderTest_1462, ReadNullDataFails_1462) {
    bool result = header_.read(nullptr, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test that read fails with insufficient size
TEST_F(Nikon2MnHeaderTest_1462, ReadInsufficientSizeFails_1462) {
    Exiv2::byte data[] = {0x4E, 0x69, 0x6B}; // "Nik" - too short
    bool result = header_.read(data, sizeof(data), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test that read succeeds with valid Nikon2 maker note header
TEST_F(Nikon2MnHeaderTest_1462, ReadValidDataSucceeds_1462) {
    // Nikon2 signature: "Nikon\0\x01\x00"
    Exiv2::byte data[] = {0x4E, 0x69, 0x6B, 0x6F, 0x6E, 0x00, 0x01, 0x00};
    bool result = header_.read(data, sizeof(data), Exiv2::littleEndian);
    EXPECT_TRUE(result);
}

// Test that ifdOffset remains consistent after successful read
TEST_F(Nikon2MnHeaderTest_1462, IfdOffsetAfterValidRead_1462) {
    Exiv2::byte data[] = {0x4E, 0x69, 0x6B, 0x6F, 0x6E, 0x00, 0x01, 0x00};
    header_.read(data, sizeof(data), Exiv2::littleEndian);
    size_t offset = header_.ifdOffset();
    EXPECT_EQ(offset, 8u);
}

// Test that read fails with invalid signature
TEST_F(Nikon2MnHeaderTest_1462, ReadInvalidSignatureFails_1462) {
    Exiv2::byte data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool result = header_.read(data, sizeof(data), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with big endian byte order
TEST_F(Nikon2MnHeaderTest_1462, ReadValidDataBigEndian_1462) {
    Exiv2::byte data[] = {0x4E, 0x69, 0x6B, 0x6F, 0x6E, 0x00, 0x01, 0x00};
    bool result = header_.read(data, sizeof(data), Exiv2::bigEndian);
    EXPECT_TRUE(result);
}

// Test that read with size equal to zero fails
TEST_F(Nikon2MnHeaderTest_1462, ReadZeroSizeFails_1462) {
    Exiv2::byte data[] = {0x4E, 0x69, 0x6B, 0x6F, 0x6E, 0x00, 0x01, 0x00};
    bool result = header_.read(data, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test that read with exactly sizeOfSignature bytes with valid data succeeds
TEST_F(Nikon2MnHeaderTest_1462, ReadExactSignatureSize_1462) {
    Exiv2::byte data[] = {0x4E, 0x69, 0x6B, 0x6F, 0x6E, 0x00, 0x01, 0x00};
    size_t sigSize = Nikon2MnHeader::sizeOfSignature();
    bool result = header_.read(data, sigSize, Exiv2::littleEndian);
    EXPECT_TRUE(result);
}

// Test that read with data larger than signature size still succeeds
TEST_F(Nikon2MnHeaderTest_1462, ReadLargerDataSucceeds_1462) {
    Exiv2::byte data[] = {0x4E, 0x69, 0x6B, 0x6F, 0x6E, 0x00, 0x01, 0x00,
                          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    bool result = header_.read(data, sizeof(data), Exiv2::littleEndian);
    EXPECT_TRUE(result);
}

// Test multiple reads on the same header object
TEST_F(Nikon2MnHeaderTest_1462, MultipleReads_1462) {
    Exiv2::byte validData[] = {0x4E, 0x69, 0x6B, 0x6F, 0x6E, 0x00, 0x01, 0x00};
    Exiv2::byte invalidData[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    bool result1 = header_.read(validData, sizeof(validData), Exiv2::littleEndian);
    EXPECT_TRUE(result1);

    bool result2 = header_.read(invalidData, sizeof(invalidData), Exiv2::littleEndian);
    EXPECT_FALSE(result2);
}
