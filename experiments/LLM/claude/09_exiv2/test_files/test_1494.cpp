#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class SigmaMnHeaderTest_1494 : public ::testing::Test {
protected:
    SigmaMnHeader header_;
};

// Test that size() returns the same value as sizeOfSignature()
TEST_F(SigmaMnHeaderTest_1494, SizeReturnsSizeOfSignature_1494) {
    size_t expectedSize = SigmaMnHeader::sizeOfSignature();
    EXPECT_EQ(header_.size(), expectedSize);
}

// Test that size() returns a non-zero value (signature should have some length)
TEST_F(SigmaMnHeaderTest_1494, SizeIsNonZero_1494) {
    EXPECT_GT(header_.size(), 0u);
}

// Test that sizeOfSignature() is consistent across multiple calls
TEST_F(SigmaMnHeaderTest_1494, SizeOfSignatureIsConsistent_1494) {
    size_t first = SigmaMnHeader::sizeOfSignature();
    size_t second = SigmaMnHeader::sizeOfSignature();
    EXPECT_EQ(first, second);
}

// Test that size() is consistent across multiple calls
TEST_F(SigmaMnHeaderTest_1494, SizeIsConsistent_1494) {
    size_t first = header_.size();
    size_t second = header_.size();
    EXPECT_EQ(first, second);
}

// Test that multiple instances return the same size
TEST_F(SigmaMnHeaderTest_1494, MultiplInstancesSameSize_1494) {
    SigmaMnHeader header2;
    EXPECT_EQ(header_.size(), header2.size());
}

// Test that ifdOffset() returns a valid value
TEST_F(SigmaMnHeaderTest_1494, IfdOffsetReturnsValue_1494) {
    size_t offset = header_.ifdOffset();
    // The ifd offset should be reasonable - at least 0 and no greater than size
    EXPECT_GE(offset, 0u);
}

// Test read with nullptr data returns false (or handles gracefully)
TEST_F(SigmaMnHeaderTest_1494, ReadWithNullptrData_1494) {
    bool result = header_.read(nullptr, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with size smaller than signature size returns false
TEST_F(SigmaMnHeaderTest_1494, ReadWithInsufficientSize_1494) {
    size_t sigSize = SigmaMnHeader::sizeOfSignature();
    if (sigSize > 0) {
        std::vector<Exiv2::byte> data(sigSize - 1, 0);
        bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
        EXPECT_FALSE(result);
    }
}

// Test read with invalid signature data
TEST_F(SigmaMnHeaderTest_1494, ReadWithInvalidSignature_1494) {
    size_t sigSize = SigmaMnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 10, 0xFF);
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    // Invalid signature data should fail
    EXPECT_FALSE(result);
}

// Test read with valid "SIGMA" signature
TEST_F(SigmaMnHeaderTest_1494, ReadWithSigmaSignature_1494) {
    // Sigma makernote typically starts with "SIGMA\0\0\0" or "FOVEON\0\0"
    size_t sigSize = SigmaMnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 100, 0);
    
    // Try "SIGMA\0\0\0\0\0"
    const char* sigma = "SIGMA\0\0\0\0\0";
    if (sigSize >= 10) {
        std::memcpy(data.data(), sigma, 10);
    }
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    // Result depends on exact expected signature format
    // We just verify the function doesn't crash
    (void)result;
}

// Test read with valid "FOVEON" signature
TEST_F(SigmaMnHeaderTest_1494, ReadWithFoveonSignature_1494) {
    size_t sigSize = SigmaMnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 100, 0);
    
    const char* foveon = "FOVEON\0\0\0\0";
    if (sigSize >= 10) {
        std::memcpy(data.data(), foveon, 10);
    }
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    (void)result;
}

// Test that size and ifdOffset have a reasonable relationship
TEST_F(SigmaMnHeaderTest_1494, IfdOffsetRelationToSize_1494) {
    size_t sz = header_.size();
    size_t offset = header_.ifdOffset();
    // The IFD offset should typically be at or after the header
    EXPECT_LE(offset, sz);
}

// Test read with both byte orders
TEST_F(SigmaMnHeaderTest_1494, ReadWithBigEndian_1494) {
    size_t sigSize = SigmaMnHeader::sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 10, 0);
    // Just verify it doesn't crash with big endian
    bool result = header_.read(data.data(), data.size(), Exiv2::bigEndian);
    (void)result;
}

// Test default construction results in consistent state
TEST_F(SigmaMnHeaderTest_1494, DefaultConstruction_1494) {
    SigmaMnHeader h;
    EXPECT_EQ(h.size(), SigmaMnHeader::sizeOfSignature());
}
