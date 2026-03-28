#include <gtest/gtest.h>
#include "makernote_int.hpp"

namespace {

using namespace Exiv2::Internal;

// Test fixture for SonyMnHeader
class SonyMnHeaderTest_1498 : public ::testing::Test {
protected:
    SonyMnHeader header_;
};

// Test that sizeOfSignature returns a non-zero value
TEST_F(SonyMnHeaderTest_1498, SizeOfSignatureReturnsNonZero_1498) {
    size_t sigSize = header_.sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that sizeOfSignature returns a consistent value across multiple calls
TEST_F(SonyMnHeaderTest_1498, SizeOfSignatureIsConsistent_1498) {
    size_t sigSize1 = header_.sizeOfSignature();
    size_t sigSize2 = header_.sizeOfSignature();
    EXPECT_EQ(sigSize1, sigSize2);
}

// Test that size() returns a value (should be at least as large as the signature)
TEST_F(SonyMnHeaderTest_1498, SizeReturnsExpectedValue_1498) {
    size_t headerSize = header_.size();
    size_t sigSize = header_.sizeOfSignature();
    EXPECT_GE(headerSize, sigSize);
}

// Test that ifdOffset returns a value
TEST_F(SonyMnHeaderTest_1498, IfdOffsetReturnsValue_1498) {
    size_t offset = header_.ifdOffset();
    // The IFD offset should be reasonable (at least 0)
    EXPECT_GE(offset, 0u);
}

// Test read with nullptr data and zero size
TEST_F(SonyMnHeaderTest_1498, ReadWithNullDataReturnsFalse_1498) {
    bool result = header_.read(nullptr, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with data that is too small
TEST_F(SonyMnHeaderTest_1498, ReadWithTooSmallDataReturnsFalse_1498) {
    Exiv2::byte smallData[] = {0x00};
    bool result = header_.read(smallData, 1, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Sony maker note signature
TEST_F(SonyMnHeaderTest_1498, ReadWithValidSonySignature_1498) {
    // Sony maker note signature is "SONY DSC \0\0\0"
    const char sonySignature[] = "SONY DSC \0\0\0";
    size_t sigSize = header_.sizeOfSignature();
    
    // Create buffer large enough
    std::vector<Exiv2::byte> data(std::max(sigSize + 16, (size_t)64), 0);
    // Copy the Sony signature
    if (sigSize <= data.size()) {
        std::memcpy(data.data(), sonySignature, std::min(sizeof(sonySignature), sigSize));
    }
    
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    // The result depends on whether the signature matches
    // We just verify it doesn't crash
    (void)result;
}

// Test read with invalid signature data
TEST_F(SonyMnHeaderTest_1498, ReadWithInvalidSignatureReturnsFalse_1498) {
    size_t sigSize = header_.sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 16, 0xFF);
    
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with big endian byte order
TEST_F(SonyMnHeaderTest_1498, ReadWithBigEndian_1498) {
    size_t sigSize = header_.sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 16, 0x00);
    
    bool result = header_.read(data.data(), data.size(), Exiv2::bigEndian);
    // Just ensure it doesn't crash; result depends on data validity
    (void)result;
}

// Test read with exact signature size
TEST_F(SonyMnHeaderTest_1498, ReadWithExactSignatureSize_1498) {
    size_t sigSize = header_.sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize, 0x00);
    
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    // May or may not succeed depending on if size == sigSize is sufficient
    (void)result;
}

// Test that multiple SonyMnHeader instances have same sizeOfSignature
TEST_F(SonyMnHeaderTest_1498, MultiplInstancesSameSizeOfSignature_1498) {
    SonyMnHeader header2;
    EXPECT_EQ(header_.sizeOfSignature(), header2.sizeOfSignature());
}

// Test that multiple SonyMnHeader instances have same size
TEST_F(SonyMnHeaderTest_1498, MultipleInstancesSameSize_1498) {
    SonyMnHeader header2;
    EXPECT_EQ(header_.size(), header2.size());
}

// Test that multiple SonyMnHeader instances have same ifdOffset
TEST_F(SonyMnHeaderTest_1498, MultipleInstancesSameIfdOffset_1498) {
    SonyMnHeader header2;
    EXPECT_EQ(header_.ifdOffset(), header2.ifdOffset());
}

// Test that size and sizeOfSignature have a reasonable relationship
TEST_F(SonyMnHeaderTest_1498, SizeAndSignatureSizeRelationship_1498) {
    size_t headerSize = header_.size();
    size_t sigSize = header_.sizeOfSignature();
    // Header size should be at least the signature size
    EXPECT_GE(headerSize, sigSize);
}

// Test ifdOffset is within reasonable bounds relative to size
TEST_F(SonyMnHeaderTest_1498, IfdOffsetWithinBounds_1498) {
    size_t offset = header_.ifdOffset();
    size_t headerSize = header_.size();
    EXPECT_LE(offset, headerSize);
}

}  // namespace
