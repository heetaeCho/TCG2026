#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class PanasonicMnHeaderTest_1473 : public ::testing::Test {
protected:
    PanasonicMnHeader header_;
};

// Test that sizeOfSignature returns a positive value
TEST_F(PanasonicMnHeaderTest_1473, SizeOfSignatureReturnsPositiveValue_1473) {
    size_t sigSize = header_.sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that sizeOfSignature returns a consistent value across multiple calls
TEST_F(PanasonicMnHeaderTest_1473, SizeOfSignatureIsConsistent_1473) {
    size_t sigSize1 = header_.sizeOfSignature();
    size_t sigSize2 = header_.sizeOfSignature();
    EXPECT_EQ(sigSize1, sigSize2);
}

// Test that size() returns a value (at least as large as signature)
TEST_F(PanasonicMnHeaderTest_1473, SizeReturnsExpectedValue_1473) {
    size_t sz = header_.size();
    EXPECT_GT(sz, 0u);
    EXPECT_GE(sz, header_.sizeOfSignature());
}

// Test that ifdOffset returns a value
TEST_F(PanasonicMnHeaderTest_1473, IfdOffsetReturnsValue_1473) {
    size_t offset = header_.ifdOffset();
    // The offset should be reasonable - at least 0
    EXPECT_GE(offset, 0u);
}

// Test read with nullptr data and zero size
TEST_F(PanasonicMnHeaderTest_1473, ReadWithNullptrReturnsFalse_1473) {
    bool result = header_.read(nullptr, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with insufficient data size
TEST_F(PanasonicMnHeaderTest_1473, ReadWithInsufficientSizeReturnsFalse_1473) {
    Exiv2::byte smallData[1] = {0};
    bool result = header_.read(smallData, 1, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Panasonic signature
TEST_F(PanasonicMnHeaderTest_1473, ReadWithValidSignatureReturnsTrue_1473) {
    // Panasonic makernote signature is "Panasonic\0\0\0"
    const char panasonicSig[] = "Panasonic\0\0\0";
    size_t sigSize = header_.sizeOfSignature();
    
    // Create a buffer large enough for the header
    std::vector<Exiv2::byte> data(std::max(sigSize + 8, header_.size() + 8), 0);
    std::memcpy(data.data(), panasonicSig, std::min(sizeof(panasonicSig), data.size()));
    
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    EXPECT_TRUE(result);
}

// Test read with invalid signature data
TEST_F(PanasonicMnHeaderTest_1473, ReadWithInvalidSignatureReturnsFalse_1473) {
    size_t sz = header_.size();
    std::vector<Exiv2::byte> data(sz + 16, 0xFF);
    
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test that size and sizeOfSignature have a reasonable relationship
TEST_F(PanasonicMnHeaderTest_1473, SizeRelationship_1473) {
    size_t sz = header_.size();
    size_t sigSz = header_.sizeOfSignature();
    // Size should be at least the signature size
    EXPECT_GE(sz, sigSz);
}

// Test read with exact minimum size boundary
TEST_F(PanasonicMnHeaderTest_1473, ReadWithExactMinimumSizeBoundary_1473) {
    size_t sz = header_.size();
    // Size exactly equal to sizeOfSignature - 1 should fail
    if (sz > 0) {
        std::vector<Exiv2::byte> data(sz - 1, 0);
        bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
        EXPECT_FALSE(result);
    }
}

// Test with big endian byte order
TEST_F(PanasonicMnHeaderTest_1473, ReadWithBigEndian_1473) {
    const char panasonicSig[] = "Panasonic\0\0\0";
    size_t sigSize = header_.sizeOfSignature();
    
    std::vector<Exiv2::byte> data(std::max(sigSize + 8, header_.size() + 8), 0);
    std::memcpy(data.data(), panasonicSig, std::min(sizeof(panasonicSig), data.size()));
    
    bool result = header_.read(data.data(), data.size(), Exiv2::bigEndian);
    EXPECT_TRUE(result);
}

// Test multiple PanasonicMnHeader instances have the same sizeOfSignature
TEST_F(PanasonicMnHeaderTest_1473, MultipeInstancesSameSizeOfSignature_1473) {
    PanasonicMnHeader header2;
    EXPECT_EQ(header_.sizeOfSignature(), header2.sizeOfSignature());
}

// Test multiple PanasonicMnHeader instances have the same size
TEST_F(PanasonicMnHeaderTest_1473, MultipleInstancesSameSize_1473) {
    PanasonicMnHeader header2;
    EXPECT_EQ(header_.size(), header2.size());
}

// Test multiple PanasonicMnHeader instances have the same ifdOffset
TEST_F(PanasonicMnHeaderTest_1473, MultipleInstancesSameIfdOffset_1473) {
    PanasonicMnHeader header2;
    EXPECT_EQ(header_.ifdOffset(), header2.ifdOffset());
}
