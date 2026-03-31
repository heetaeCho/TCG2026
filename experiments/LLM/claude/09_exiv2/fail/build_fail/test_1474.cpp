#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class PanasonicMnHeaderTest_1474 : public ::testing::Test {
protected:
    PanasonicMnHeader header_;
};

TEST_F(PanasonicMnHeaderTest_1474, DefaultConstruction_1474) {
    // Test that a PanasonicMnHeader can be default constructed
    PanasonicMnHeader h;
    // Should not crash or throw
}

TEST_F(PanasonicMnHeaderTest_1474, SizeMatchesSizeOfSignature_1474) {
    // size() should return the same value as sizeOfSignature()
    EXPECT_EQ(header_.size(), PanasonicMnHeader::sizeOfSignature());
}

TEST_F(PanasonicMnHeaderTest_1474, SizeIsPositive_1474) {
    // The size of the Panasonic maker note header should be positive
    EXPECT_GT(header_.size(), 0u);
}

TEST_F(PanasonicMnHeaderTest_1474, SizeOfSignatureIsConsistent_1474) {
    // sizeOfSignature() is static and should return the same value on repeated calls
    size_t first = PanasonicMnHeader::sizeOfSignature();
    size_t second = PanasonicMnHeader::sizeOfSignature();
    EXPECT_EQ(first, second);
}

TEST_F(PanasonicMnHeaderTest_1474, SizeConsistentAcrossInstances_1474) {
    // Multiple instances should report the same size
    PanasonicMnHeader h1;
    PanasonicMnHeader h2;
    EXPECT_EQ(h1.size(), h2.size());
}

TEST_F(PanasonicMnHeaderTest_1474, IfdOffsetValue_1474) {
    // ifdOffset() should return a value (typically 12 for Panasonic)
    size_t offset = header_.ifdOffset();
    // The offset should be reasonable - at minimum 0 and at most the size
    EXPECT_GE(offset, 0u);
}

TEST_F(PanasonicMnHeaderTest_1474, ReadWithNullData_1474) {
    // Reading with null pointer and zero size should not succeed
    bool result = header_.read(nullptr, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(PanasonicMnHeaderTest_1474, ReadWithInsufficientSize_1474) {
    // Reading with size smaller than sizeOfSignature should fail
    Exiv2::byte data[4] = {0, 0, 0, 0};
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    if (sigSize > 4) {
        bool result = header_.read(data, 4, Exiv2::littleEndian);
        EXPECT_FALSE(result);
    }
}

TEST_F(PanasonicMnHeaderTest_1474, ReadWithValidPanasonicSignature_1474) {
    // The Panasonic signature is "Panasonic\0\0\0" (12 bytes)
    const char sig[] = "Panasonic\0\0\0";
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    
    std::vector<Exiv2::byte> data(sigSize + 100, 0);
    std::memcpy(data.data(), sig, std::min(sizeof(sig), sigSize));
    
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    EXPECT_TRUE(result);
}

TEST_F(PanasonicMnHeaderTest_1474, ReadWithInvalidSignature_1474) {
    // Providing garbage data should cause read to fail
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 100, 0xFF);
    
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

TEST_F(PanasonicMnHeaderTest_1474, ReadWithExactSize_1474) {
    // Read with exactly sizeOfSignature bytes containing valid signature
    const char sig[] = "Panasonic\0\0\0";
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    
    std::vector<Exiv2::byte> data(sigSize, 0);
    std::memcpy(data.data(), sig, std::min(sizeof(sig), sigSize));
    
    bool result = header_.read(data.data(), sigSize, Exiv2::littleEndian);
    EXPECT_TRUE(result);
}

TEST_F(PanasonicMnHeaderTest_1474, ReadWithBigEndianByteOrder_1474) {
    // Read with big endian byte order should also work with valid signature
    const char sig[] = "Panasonic\0\0\0";
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    
    std::vector<Exiv2::byte> data(sigSize + 100, 0);
    std::memcpy(data.data(), sig, std::min(sizeof(sig), sigSize));
    
    bool result = header_.read(data.data(), data.size(), Exiv2::bigEndian);
    EXPECT_TRUE(result);
}

TEST_F(PanasonicMnHeaderTest_1474, SizeAfterSuccessfulRead_1474) {
    // After a successful read, size should still be sizeOfSignature
    const char sig[] = "Panasonic\0\0\0";
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    
    std::vector<Exiv2::byte> data(sigSize + 100, 0);
    std::memcpy(data.data(), sig, std::min(sizeof(sig), sigSize));
    
    header_.read(data.data(), data.size(), Exiv2::littleEndian);
    EXPECT_EQ(header_.size(), sigSize);
}
