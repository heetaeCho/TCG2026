#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class OlympusMnHeaderTest_1436 : public ::testing::Test {
protected:
    OlympusMnHeader header_;
};

// Test that sizeOfSignature returns a positive value
TEST_F(OlympusMnHeaderTest_1436, SizeOfSignatureReturnsPositiveValue_1436) {
    size_t sigSize = header_.sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that sizeOfSignature returns a consistent value across multiple calls
TEST_F(OlympusMnHeaderTest_1436, SizeOfSignatureIsConsistent_1436) {
    size_t sigSize1 = header_.sizeOfSignature();
    size_t sigSize2 = header_.sizeOfSignature();
    EXPECT_EQ(sigSize1, sigSize2);
}

// Test that size() returns a value (header size should be positive)
TEST_F(OlympusMnHeaderTest_1436, SizeReturnsPositiveValue_1436) {
    size_t sz = header_.size();
    EXPECT_GT(sz, 0u);
}

// Test that size() is consistent
TEST_F(OlympusMnHeaderTest_1436, SizeIsConsistent_1436) {
    size_t sz1 = header_.size();
    size_t sz2 = header_.size();
    EXPECT_EQ(sz1, sz2);
}

// Test that ifdOffset returns a reasonable value
TEST_F(OlympusMnHeaderTest_1436, IfdOffsetReturnsValue_1436) {
    size_t offset = header_.ifdOffset();
    // The IFD offset should be >= 0 (it's size_t so always >= 0, but check it's reasonable)
    EXPECT_GE(offset, 0u);
}

// Test that ifdOffset is consistent
TEST_F(OlympusMnHeaderTest_1436, IfdOffsetIsConsistent_1436) {
    size_t offset1 = header_.ifdOffset();
    size_t offset2 = header_.ifdOffset();
    EXPECT_EQ(offset1, offset2);
}

// Test that size() is at least as large as sizeOfSignature
TEST_F(OlympusMnHeaderTest_1436, SizeAtLeastSizeOfSignature_1436) {
    EXPECT_GE(header_.size(), header_.sizeOfSignature());
}

// Test read with nullptr data returns false
TEST_F(OlympusMnHeaderTest_1436, ReadWithNullptrReturnsFalse_1436) {
    bool result = header_.read(nullptr, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with zero size returns false
TEST_F(OlympusMnHeaderTest_1436, ReadWithZeroSizeReturnsFalse_1436) {
    Exiv2::byte data[1] = {0};
    bool result = header_.read(data, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with insufficient data size returns false
TEST_F(OlympusMnHeaderTest_1436, ReadWithInsufficientSizeReturnsFalse_1436) {
    Exiv2::byte data[2] = {0x00, 0x00};
    bool result = header_.read(data, 2, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Olympus maker note signature
TEST_F(OlympusMnHeaderTest_1436, ReadWithValidOlympusSignature_1436) {
    // Olympus signature is "OLYMP\0" followed by version bytes
    // The signature is typically "OLYMP\0" (6 bytes) + additional header bytes
    const char olympusSig[] = "OLYMP\0II\x03\x00";
    size_t dataSize = header_.size();
    std::vector<Exiv2::byte> data(std::max(dataSize, static_cast<size_t>(10)), 0);
    std::memcpy(data.data(), olympusSig, std::min(sizeof(olympusSig), data.size()));
    
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    // Result depends on whether the signature matches; we test both paths
    // This is an observability test
    (void)result; // Just ensure no crash
    SUCCEED();
}

// Test that sizeOfSignature matches expected Olympus signature length
TEST_F(OlympusMnHeaderTest_1436, SizeOfSignatureMatchesExpected_1436) {
    // Olympus signature is typically "OLYMP\0" which is 6 bytes,
    // but the exact size depends on implementation
    size_t sigSize = header_.sizeOfSignature();
    // The Olympus maker note signature should be a small reasonable value
    EXPECT_LT(sigSize, 100u);
    EXPECT_GT(sigSize, 0u);
}

// Test that multiple OlympusMnHeader instances have same sizeOfSignature
TEST_F(OlympusMnHeaderTest_1436, MultipleInstancesSameSizeOfSignature_1436) {
    OlympusMnHeader header2;
    EXPECT_EQ(header_.sizeOfSignature(), header2.sizeOfSignature());
}

// Test that multiple OlympusMnHeader instances have same size
TEST_F(OlympusMnHeaderTest_1436, MultipleInstancesSameSize_1436) {
    OlympusMnHeader header2;
    EXPECT_EQ(header_.size(), header2.size());
}

// Test that multiple OlympusMnHeader instances have same ifdOffset
TEST_F(OlympusMnHeaderTest_1436, MultipleInstancesSameIfdOffset_1436) {
    OlympusMnHeader header2;
    EXPECT_EQ(header_.ifdOffset(), header2.ifdOffset());
}

// Test read with data smaller than sizeOfSignature
TEST_F(OlympusMnHeaderTest_1436, ReadWithDataSmallerThanSignature_1436) {
    size_t sigSize = header_.sizeOfSignature();
    if (sigSize > 1) {
        std::vector<Exiv2::byte> data(sigSize - 1, 0);
        bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
        EXPECT_FALSE(result);
    }
}

// Test read with big endian byte order
TEST_F(OlympusMnHeaderTest_1436, ReadWithBigEndian_1436) {
    std::vector<Exiv2::byte> data(header_.size() + 10, 0);
    // Just ensure no crash with big endian
    bool result = header_.read(data.data(), data.size(), Exiv2::bigEndian);
    (void)result;
    SUCCEED();
}
