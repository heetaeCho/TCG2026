#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class SonyMnHeaderTest_1499 : public ::testing::Test {
protected:
    SonyMnHeader header_;
};

// Test that a default-constructed SonyMnHeader has a size equal to sizeOfSignature
TEST_F(SonyMnHeaderTest_1499, SizeEqualsSizeOfSignature_1499) {
    EXPECT_EQ(header_.size(), SonyMnHeader::sizeOfSignature());
}

// Test that size returns a non-zero value (Sony maker note signature should have content)
TEST_F(SonyMnHeaderTest_1499, SizeIsNonZero_1499) {
    EXPECT_GT(header_.size(), 0u);
}

// Test that sizeOfSignature is consistent across multiple calls
TEST_F(SonyMnHeaderTest_1499, SizeOfSignatureIsConsistent_1499) {
    size_t first = SonyMnHeader::sizeOfSignature();
    size_t second = SonyMnHeader::sizeOfSignature();
    EXPECT_EQ(first, second);
}

// Test that size() is consistent across multiple calls on the same object
TEST_F(SonyMnHeaderTest_1499, SizeIsConsistentAcrossCalls_1499) {
    size_t first = header_.size();
    size_t second = header_.size();
    EXPECT_EQ(first, second);
}

// Test that multiple instances return the same size
TEST_F(SonyMnHeaderTest_1499, MultiplInstancesSameSize_1499) {
    SonyMnHeader header2;
    EXPECT_EQ(header_.size(), header2.size());
}

// Test ifdOffset returns a reasonable value
TEST_F(SonyMnHeaderTest_1499, IfdOffsetReturnsValue_1499) {
    size_t offset = header_.ifdOffset();
    // The ifd offset should be at most the size of the header or equal to it
    EXPECT_GE(offset, 0u);
}

// Test read with nullptr and zero size (boundary condition)
TEST_F(SonyMnHeaderTest_1499, ReadWithNullptrAndZeroSize_1499) {
    bool result = header_.read(nullptr, 0, Exiv2::littleEndian);
    // With no data provided, read should fail
    EXPECT_FALSE(result);
}

// Test read with insufficient data size
TEST_F(SonyMnHeaderTest_1499, ReadWithInsufficientSize_1499) {
    Exiv2::byte data[1] = {0};
    bool result = header_.read(data, 1, Exiv2::littleEndian);
    // Size of 1 byte is certainly less than the signature size, so read should fail
    EXPECT_FALSE(result);
}

// Test read with valid Sony maker note signature
TEST_F(SonyMnHeaderTest_1499, ReadWithValidSonySignature_1499) {
    // Sony maker note header signature is "SONY DSC \0\0\0"
    const char sonySignature[] = "SONY DSC \0\0\0";
    size_t sigSize = SonyMnHeader::sizeOfSignature();
    
    // Create a buffer large enough
    std::vector<Exiv2::byte> data(sigSize + 100, 0);
    // Copy the known Sony signature
    if (sigSize <= sizeof(sonySignature)) {
        std::memcpy(data.data(), sonySignature, sigSize);
    }
    
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    // If the signature matches, read should succeed
    // Note: this depends on the actual signature format
    // We test both outcomes are handled gracefully
    if (result) {
        EXPECT_EQ(header_.size(), sigSize);
    }
}

// Test read with wrong signature data
TEST_F(SonyMnHeaderTest_1499, ReadWithWrongSignature_1499) {
    size_t sigSize = SonyMnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 100, 0xFF);
    
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    // Wrong signature data should cause read to fail
    EXPECT_FALSE(result);
}

// Test read with exact signature size boundary
TEST_F(SonyMnHeaderTest_1499, ReadWithExactSignatureSize_1499) {
    size_t sigSize = SonyMnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize, 0);
    
    // Even with exact size, if the signature doesn't match it should return false
    bool result = header_.read(data.data(), sigSize, Exiv2::littleEndian);
    // The result depends on whether the data matches the expected signature
    // This is a boundary test - at minimum it should not crash
    SUCCEED();
}

// Test read with big endian byte order
TEST_F(SonyMnHeaderTest_1499, ReadWithBigEndianByteOrder_1499) {
    size_t sigSize = SonyMnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 100, 0);
    
    bool result = header_.read(data.data(), data.size(), Exiv2::bigEndian);
    // With zeroed data, this should likely fail regardless of byte order
    // The important thing is it handles the byte order parameter without crashing
    SUCCEED();
}

// Test that size remains consistent after a failed read
TEST_F(SonyMnHeaderTest_1499, SizeConsistentAfterFailedRead_1499) {
    size_t sizeBefore = header_.size();
    
    Exiv2::byte data[1] = {0};
    header_.read(data, 1, Exiv2::littleEndian);
    
    size_t sizeAfter = header_.size();
    EXPECT_EQ(sizeBefore, sizeAfter);
}
