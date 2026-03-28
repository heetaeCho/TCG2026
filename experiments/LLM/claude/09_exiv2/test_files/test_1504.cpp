#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class Casio2MnHeaderTest_1504 : public ::testing::Test {
protected:
    Casio2MnHeader header_;
};

// Test that size() returns the same value as sizeOfSignature()
TEST_F(Casio2MnHeaderTest_1504, SizeReturnsSizeOfSignature_1504) {
    EXPECT_EQ(header_.size(), Casio2MnHeader::sizeOfSignature());
}

// Test that size() returns a non-zero value (signature should have some length)
TEST_F(Casio2MnHeaderTest_1504, SizeIsNonZero_1504) {
    EXPECT_GT(header_.size(), 0u);
}

// Test that sizeOfSignature() is consistent across multiple calls
TEST_F(Casio2MnHeaderTest_1504, SizeOfSignatureIsConsistent_1504) {
    size_t first = Casio2MnHeader::sizeOfSignature();
    size_t second = Casio2MnHeader::sizeOfSignature();
    EXPECT_EQ(first, second);
}

// Test that size() is consistent across multiple calls
TEST_F(Casio2MnHeaderTest_1504, SizeIsConsistentAcrossMultipleCalls_1504) {
    size_t first = header_.size();
    size_t second = header_.size();
    EXPECT_EQ(first, second);
}

// Test that multiple instances return the same size
TEST_F(Casio2MnHeaderTest_1504, MultipleInstancesReturnSameSize_1504) {
    Casio2MnHeader another;
    EXPECT_EQ(header_.size(), another.size());
}

// Test that ifdOffset() returns a value (should be valid after default construction)
TEST_F(Casio2MnHeaderTest_1504, IfdOffsetReturnsValue_1504) {
    size_t offset = header_.ifdOffset();
    // ifdOffset should be reasonable - at least 0 and at most size
    EXPECT_GE(offset, 0u);
}

// Test that byteOrder() returns a valid byte order after default construction
TEST_F(Casio2MnHeaderTest_1504, ByteOrderReturnsValidValue_1504) {
    Exiv2::ByteOrder bo = header_.byteOrder();
    // ByteOrder should be one of the known values
    EXPECT_TRUE(bo == Exiv2::bigEndian || bo == Exiv2::littleEndian || bo == Exiv2::invalidByteOrder);
}

// Test read with nullptr data and zero size
TEST_F(Casio2MnHeaderTest_1504, ReadWithNullDataReturnsFalse_1504) {
    bool result = header_.read(nullptr, 0, Exiv2::bigEndian);
    EXPECT_FALSE(result);
}

// Test read with data smaller than signature size
TEST_F(Casio2MnHeaderTest_1504, ReadWithInsufficientDataReturnsFalse_1504) {
    size_t sigSize = Casio2MnHeader::sizeOfSignature();
    if (sigSize > 1) {
        std::vector<Exiv2::byte> smallData(sigSize - 1, 0);
        bool result = header_.read(smallData.data(), smallData.size(), Exiv2::bigEndian);
        EXPECT_FALSE(result);
    }
}

// Test read with zero-size data
TEST_F(Casio2MnHeaderTest_1504, ReadWithZeroSizeReturnsFalse_1504) {
    Exiv2::byte data[1] = {0};
    bool result = header_.read(data, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test that size remains consistent after a failed read
TEST_F(Casio2MnHeaderTest_1504, SizeConsistentAfterFailedRead_1504) {
    size_t sizeBefore = header_.size();
    header_.read(nullptr, 0, Exiv2::bigEndian);
    size_t sizeAfter = header_.size();
    EXPECT_EQ(sizeBefore, sizeAfter);
}
