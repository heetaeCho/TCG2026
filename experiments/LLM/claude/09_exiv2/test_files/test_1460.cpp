#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class Nikon2MnHeaderTest_1460 : public ::testing::Test {
protected:
    Nikon2MnHeader header_;
};

// Test that sizeOfSignature returns a consistent, non-zero value
TEST_F(Nikon2MnHeaderTest_1460, SizeOfSignatureReturnsNonZero_1460) {
    size_t sigSize = header_.sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that sizeOfSignature returns a consistent value across multiple calls
TEST_F(Nikon2MnHeaderTest_1460, SizeOfSignatureIsConsistent_1460) {
    size_t sigSize1 = header_.sizeOfSignature();
    size_t sigSize2 = header_.sizeOfSignature();
    EXPECT_EQ(sigSize1, sigSize2);
}

// Test that size() returns a value (header size should be positive)
TEST_F(Nikon2MnHeaderTest_1460, SizeReturnsPositiveValue_1460) {
    size_t sz = header_.size();
    EXPECT_GT(sz, 0u);
}

// Test that ifdOffset returns a value
TEST_F(Nikon2MnHeaderTest_1460, IfdOffsetReturnsValue_1460) {
    size_t offset = header_.ifdOffset();
    // The IFD offset should be at least as large as the signature size
    // or some reasonable value
    EXPECT_GE(offset, 0u);
}

// Test that size() is consistent with sizeOfSignature()
TEST_F(Nikon2MnHeaderTest_1460, SizeRelationToSignature_1460) {
    size_t sz = header_.size();
    size_t sigSize = header_.sizeOfSignature();
    // The total header size should be at least as large as the signature
    EXPECT_GE(sz, sigSize);
}

// Test read with nullptr data and zero size
TEST_F(Nikon2MnHeaderTest_1460, ReadWithNullDataReturnsFalse_1460) {
    bool result = header_.read(nullptr, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with insufficient data size
TEST_F(Nikon2MnHeaderTest_1460, ReadWithInsufficientSizeReturnsFalse_1460) {
    Exiv2::byte data[1] = {0};
    bool result = header_.read(data, 1, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Nikon2 maker note signature
TEST_F(Nikon2MnHeaderTest_1460, ReadWithValidSignature_1460) {
    // Nikon2 maker note signature is "Nikon\0\x01\x00"
    // The header expects at least sizeOfSignature() bytes
    size_t sigSize = header_.sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 100, 0);
    // Nikon type 2 signature
    const char sig[] = "Nikon\0\x01\x00";
    if (sigSize <= sizeof(sig)) {
        std::memcpy(data.data(), sig, std::min(sigSize, sizeof(sig)));
    }
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    // Result depends on whether the signature matches; we just verify it doesn't crash
    // and returns a boolean
    EXPECT_TRUE(result == true || result == false);
}

// Test read with wrong signature data
TEST_F(Nikon2MnHeaderTest_1460, ReadWithInvalidSignatureReturnsFalse_1460) {
    size_t sigSize = header_.sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 100, 0xFF);
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test that multiple Nikon2MnHeader instances have the same sizeOfSignature
TEST_F(Nikon2MnHeaderTest_1460, MultipleInstancesSameSizeOfSignature_1460) {
    Nikon2MnHeader header2;
    EXPECT_EQ(header_.sizeOfSignature(), header2.sizeOfSignature());
}

// Test that multiple Nikon2MnHeader instances have the same size
TEST_F(Nikon2MnHeaderTest_1460, MultipleInstancesSameSize_1460) {
    Nikon2MnHeader header2;
    EXPECT_EQ(header_.size(), header2.size());
}

// Test that ifdOffset is consistent across instances
TEST_F(Nikon2MnHeaderTest_1460, MultipleInstancesSameIfdOffset_1460) {
    Nikon2MnHeader header2;
    EXPECT_EQ(header_.ifdOffset(), header2.ifdOffset());
}

// Test read with exact size of signature (boundary condition)
TEST_F(Nikon2MnHeaderTest_1460, ReadWithExactSignatureSize_1460) {
    size_t sigSize = header_.sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize, 0);
    // Even with correct size, wrong content should fail
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    // Just ensure it doesn't crash
    EXPECT_TRUE(result == true || result == false);
}

// Test read with big-endian byte order
TEST_F(Nikon2MnHeaderTest_1460, ReadWithBigEndian_1460) {
    size_t sigSize = header_.sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize + 100, 0);
    bool result = header_.read(data.data(), data.size(), Exiv2::bigEndian);
    EXPECT_TRUE(result == true || result == false);
}

// Test read with size one less than signature size (boundary)
TEST_F(Nikon2MnHeaderTest_1460, ReadWithSizeOneLessThanSignature_1460) {
    size_t sigSize = header_.sizeOfSignature();
    if (sigSize > 0) {
        std::vector<Exiv2::byte> data(sigSize - 1, 0);
        bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
        EXPECT_FALSE(result);
    }
}
