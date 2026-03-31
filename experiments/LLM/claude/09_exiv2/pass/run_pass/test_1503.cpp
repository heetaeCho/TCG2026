#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class Casio2MnHeaderTest_1503 : public ::testing::Test {
protected:
    Casio2MnHeader header_;
};

// Test that sizeOfSignature returns a non-zero value
TEST_F(Casio2MnHeaderTest_1503, SizeOfSignatureReturnsNonZero_1503) {
    size_t sigSize = header_.sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that sizeOfSignature returns a consistent value across multiple calls
TEST_F(Casio2MnHeaderTest_1503, SizeOfSignatureIsConsistent_1503) {
    size_t sigSize1 = header_.sizeOfSignature();
    size_t sigSize2 = header_.sizeOfSignature();
    EXPECT_EQ(sigSize1, sigSize2);
}

// Test that size() returns a value (header size should be positive)
TEST_F(Casio2MnHeaderTest_1503, SizeReturnsPositiveValue_1503) {
    size_t sz = header_.size();
    EXPECT_GT(sz, 0u);
}

// Test that size() is at least as large as sizeOfSignature
TEST_F(Casio2MnHeaderTest_1503, SizeAtLeastSignatureSize_1503) {
    size_t sz = header_.size();
    size_t sigSize = header_.sizeOfSignature();
    EXPECT_GE(sz, sigSize);
}

// Test that ifdOffset returns a value
TEST_F(Casio2MnHeaderTest_1503, IfdOffsetReturnsValue_1503) {
    size_t offset = header_.ifdOffset();
    // The IFD offset should be a reasonable value (>= 0, which is always true for size_t)
    EXPECT_GE(offset, 0u);
}

// Test that byteOrder returns a valid byte order
TEST_F(Casio2MnHeaderTest_1503, ByteOrderReturnsValidValue_1503) {
    Exiv2::ByteOrder bo = header_.byteOrder();
    // ByteOrder should be one of the valid enumerations
    EXPECT_TRUE(bo == Exiv2::bigEndian || bo == Exiv2::littleEndian || bo == Exiv2::invalidByteOrder);
}

// Test that read with nullptr and zero size handles gracefully (should return false)
TEST_F(Casio2MnHeaderTest_1503, ReadWithNullptrReturnsFalse_1503) {
    bool result = header_.read(nullptr, 0, Exiv2::bigEndian);
    EXPECT_FALSE(result);
}

// Test that read with insufficient data returns false
TEST_F(Casio2MnHeaderTest_1503, ReadWithInsufficientDataReturnsFalse_1503) {
    Exiv2::byte data[1] = {0};
    bool result = header_.read(data, 1, Exiv2::bigEndian);
    EXPECT_FALSE(result);
}

// Test that read with size less than header size returns false
TEST_F(Casio2MnHeaderTest_1503, ReadWithSizeLessThanHeaderReturnsFalse_1503) {
    size_t headerSize = header_.size();
    if (headerSize > 1) {
        std::vector<Exiv2::byte> data(headerSize - 1, 0);
        bool result = header_.read(data.data(), data.size(), Exiv2::bigEndian);
        EXPECT_FALSE(result);
    }
}

// Test that read with valid Casio2 signature data succeeds
TEST_F(Casio2MnHeaderTest_1503, ReadWithValidSignatureReturnsTrue_1503) {
    // Casio2 maker note signature is typically "QVC\0\0\0"
    const Exiv2::byte casio2Sig[] = {'Q', 'V', 'C', '\0', '\0', '\0'};
    size_t headerSize = header_.size();
    std::vector<Exiv2::byte> data(std::max(headerSize, sizeof(casio2Sig)) + 100, 0);
    std::copy(std::begin(casio2Sig), std::end(casio2Sig), data.begin());
    
    bool result = header_.read(data.data(), data.size(), Exiv2::bigEndian);
    EXPECT_TRUE(result);
}

// Test that read with invalid signature data returns false
TEST_F(Casio2MnHeaderTest_1503, ReadWithInvalidSignatureReturnsFalse_1503) {
    size_t headerSize = header_.size();
    std::vector<Exiv2::byte> data(headerSize + 100, 0xFF);
    bool result = header_.read(data.data(), data.size(), Exiv2::bigEndian);
    EXPECT_FALSE(result);
}

// Test multiple Casio2MnHeader instances have the same sizeOfSignature
TEST_F(Casio2MnHeaderTest_1503, MultiplInstancesSameSizeOfSignature_1503) {
    Casio2MnHeader header2;
    EXPECT_EQ(header_.sizeOfSignature(), header2.sizeOfSignature());
}

// Test multiple Casio2MnHeader instances have the same size
TEST_F(Casio2MnHeaderTest_1503, MultipleInstancesSameSize_1503) {
    Casio2MnHeader header2;
    EXPECT_EQ(header_.size(), header2.size());
}

// Test that ifdOffset is consistent across multiple calls
TEST_F(Casio2MnHeaderTest_1503, IfdOffsetIsConsistent_1503) {
    size_t offset1 = header_.ifdOffset();
    size_t offset2 = header_.ifdOffset();
    EXPECT_EQ(offset1, offset2);
}

// Test that byteOrder is consistent across multiple calls
TEST_F(Casio2MnHeaderTest_1503, ByteOrderIsConsistent_1503) {
    Exiv2::ByteOrder bo1 = header_.byteOrder();
    Exiv2::ByteOrder bo2 = header_.byteOrder();
    EXPECT_EQ(bo1, bo2);
}
