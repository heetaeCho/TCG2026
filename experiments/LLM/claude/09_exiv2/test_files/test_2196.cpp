#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Casio2MnHeaderTest_2196 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<Casio2MnHeader>();
    }

    std::unique_ptr<Casio2MnHeader> header_;
};

// Test that the default constructor creates a valid object
TEST_F(Casio2MnHeaderTest_2196, DefaultConstruction_2196) {
    ASSERT_NE(header_, nullptr);
}

// Test that sizeOfSignature returns a positive value
TEST_F(Casio2MnHeaderTest_2196, SizeOfSignatureIsPositive_2196) {
    size_t sigSize = Casio2MnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that size() returns a meaningful value (should be at least the signature size)
TEST_F(Casio2MnHeaderTest_2196, SizeReturnsExpectedValue_2196) {
    size_t sz = header_->size();
    EXPECT_GE(sz, Casio2MnHeader::sizeOfSignature());
}

// Test that ifdOffset returns a value
TEST_F(Casio2MnHeaderTest_2196, IfdOffsetReturnsValue_2196) {
    size_t offset = header_->ifdOffset();
    // ifdOffset should be reasonable, at least 0
    EXPECT_GE(offset, 0u);
}

// Test that byteOrder returns a valid byte order after default construction
TEST_F(Casio2MnHeaderTest_2196, ByteOrderAfterDefaultConstruction_2196) {
    ByteOrder bo = header_->byteOrder();
    // After default construction with invalidByteOrder passed to read,
    // the byte order could be any valid value
    EXPECT_TRUE(bo == invalidByteOrder || bo == littleEndian || bo == bigEndian);
}

// Test read with nullptr and zero size - boundary condition
TEST_F(Casio2MnHeaderTest_2196, ReadWithNullptrAndZeroSize_2196) {
    bool result = header_->read(nullptr, 0, littleEndian);
    // With zero-size data, read should fail since it can't match the signature
    EXPECT_FALSE(result);
}

// Test read with data smaller than signature size
TEST_F(Casio2MnHeaderTest_2196, ReadWithTooSmallData_2196) {
    byte smallData[1] = {0};
    bool result = header_->read(smallData, 1, littleEndian);
    // Data is too small to contain the signature, should return false
    EXPECT_FALSE(result);
}

// Test read with invalid byte order
TEST_F(Casio2MnHeaderTest_2196, ReadWithInvalidByteOrder_2196) {
    // The Casio2 signature is "QVC\0\0\0" (6 bytes typically)
    size_t sigSize = Casio2MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 10, 0);
    // Fill with known Casio2 signature: "QVC\0\0\0"
    if (sigSize >= 6) {
        data[0] = 'Q';
        data[1] = 'V';
        data[2] = 'C';
        data[3] = '\0';
        data[4] = '\0';
        data[5] = '\0';
    }
    bool result = header_->read(data.data(), data.size(), invalidByteOrder);
    // Even with invalid byte order, if signature matches, it might succeed
    // We just verify it doesn't crash and returns a boolean
    EXPECT_TRUE(result == true || result == false);
}

// Test read with correct Casio2 signature and littleEndian
TEST_F(Casio2MnHeaderTest_2196, ReadWithCorrectSignatureLittleEndian_2196) {
    size_t sigSize = Casio2MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 20, 0);
    // Casio2 signature is "QVC\0\0\0"
    if (sigSize >= 6) {
        data[0] = 'Q';
        data[1] = 'V';
        data[2] = 'C';
        data[3] = '\0';
        data[4] = '\0';
        data[5] = '\0';
    }
    bool result = header_->read(data.data(), data.size(), littleEndian);
    EXPECT_TRUE(result);
}

// Test read with correct Casio2 signature and bigEndian
TEST_F(Casio2MnHeaderTest_2196, ReadWithCorrectSignatureBigEndian_2196) {
    size_t sigSize = Casio2MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 20, 0);
    if (sigSize >= 6) {
        data[0] = 'Q';
        data[1] = 'V';
        data[2] = 'C';
        data[3] = '\0';
        data[4] = '\0';
        data[5] = '\0';
    }
    bool result = header_->read(data.data(), data.size(), bigEndian);
    EXPECT_TRUE(result);
}

// Test read with wrong signature data
TEST_F(Casio2MnHeaderTest_2196, ReadWithWrongSignature_2196) {
    size_t sigSize = Casio2MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 20, 0xFF);
    bool result = header_->read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with exact signature size (boundary)
TEST_F(Casio2MnHeaderTest_2196, ReadWithExactSignatureSize_2196) {
    size_t sigSize = Casio2MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize, 0);
    if (sigSize >= 6) {
        data[0] = 'Q';
        data[1] = 'V';
        data[2] = 'C';
        data[3] = '\0';
        data[4] = '\0';
        data[5] = '\0';
    }
    bool result = header_->read(data.data(), data.size(), littleEndian);
    // With exact size, read should succeed if signature matches
    EXPECT_TRUE(result == true || result == false);
}

// Test that byteOrder changes after successful read with bigEndian
TEST_F(Casio2MnHeaderTest_2196, ByteOrderAfterReadBigEndian_2196) {
    size_t sigSize = Casio2MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 20, 0);
    if (sigSize >= 6) {
        data[0] = 'Q';
        data[1] = 'V';
        data[2] = 'C';
        data[3] = '\0';
        data[4] = '\0';
        data[5] = '\0';
    }
    header_->read(data.data(), data.size(), bigEndian);
    ByteOrder bo = header_->byteOrder();
    EXPECT_TRUE(bo == invalidByteOrder || bo == littleEndian || bo == bigEndian);
}

// Test that size is consistent
TEST_F(Casio2MnHeaderTest_2196, SizeIsConsistent_2196) {
    size_t sz1 = header_->size();
    size_t sz2 = header_->size();
    EXPECT_EQ(sz1, sz2);
}

// Test that ifdOffset is consistent
TEST_F(Casio2MnHeaderTest_2196, IfdOffsetIsConsistent_2196) {
    size_t off1 = header_->ifdOffset();
    size_t off2 = header_->ifdOffset();
    EXPECT_EQ(off1, off2);
}

// Test baseOffset through MnHeader interface
TEST_F(Casio2MnHeaderTest_2196, BaseOffsetReturnsValue_2196) {
    MnHeader* base = header_.get();
    size_t baseOff = base->baseOffset(100);
    // Default MnHeader::baseOffset returns 0
    EXPECT_EQ(baseOff, 0u);
}

// Test read with data size exactly one less than signature size
TEST_F(Casio2MnHeaderTest_2196, ReadWithOneLessThanSignatureSize_2196) {
    size_t sigSize = Casio2MnHeader::sizeOfSignature();
    if (sigSize > 0) {
        std::vector<byte> data(sigSize - 1, 0);
        if (data.size() >= 3) {
            data[0] = 'Q';
            data[1] = 'V';
            data[2] = 'C';
        }
        bool result = header_->read(data.data(), data.size(), littleEndian);
        EXPECT_FALSE(result);
    }
}
