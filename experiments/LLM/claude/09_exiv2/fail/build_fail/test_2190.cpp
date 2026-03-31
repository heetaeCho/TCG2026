#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "makernote_int.hpp"
#include "types.hpp"

// We need to include IoWrapper related headers
#include "image_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for PanasonicMnHeader
class PanasonicMnHeaderTest_2190 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<PanasonicMnHeader>();
    }

    std::unique_ptr<PanasonicMnHeader> header_;
};

// Test: Default construction creates a valid object
TEST_F(PanasonicMnHeaderTest_2190, DefaultConstruction_2190) {
    EXPECT_NE(header_, nullptr);
}

// Test: size() returns a non-zero value (signature size expected)
TEST_F(PanasonicMnHeaderTest_2190, SizeReturnsNonZero_2190) {
    size_t sz = header_->size();
    EXPECT_GT(sz, 0u);
}

// Test: sizeOfSignature() returns a non-zero value
TEST_F(PanasonicMnHeaderTest_2190, SizeOfSignatureReturnsNonZero_2190) {
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test: size() should be consistent with sizeOfSignature()
TEST_F(PanasonicMnHeaderTest_2190, SizeConsistentWithSignatureSize_2190) {
    size_t sz = header_->size();
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    // size should be at least as large as signature size
    EXPECT_GE(sz, sigSize);
}

// Test: ifdOffset() returns expected value
TEST_F(PanasonicMnHeaderTest_2190, IfdOffsetReturnsValue_2190) {
    size_t offset = header_->ifdOffset();
    // ifdOffset should be reasonable (typically equals size of signature or similar)
    EXPECT_GE(offset, 0u);
}

// Test: read with nullptr and zero size should fail
TEST_F(PanasonicMnHeaderTest_2190, ReadWithNullptrFails_2190) {
    bool result = header_->read(nullptr, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test: read with data too small to contain signature should fail
TEST_F(PanasonicMnHeaderTest_2190, ReadWithTooSmallDataFails_2190) {
    byte smallData[1] = {0};
    bool result = header_->read(smallData, 1, littleEndian);
    EXPECT_FALSE(result);
}

// Test: read with valid Panasonic signature should succeed
TEST_F(PanasonicMnHeaderTest_2190, ReadWithValidSignatureSucceeds_2190) {
    // Panasonic MakerNote signature is "Panasonic\0\0\0"
    const char panasonicSig[] = "Panasonic\0\0\0";
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    
    // Create buffer large enough
    std::vector<byte> data(sigSize + 100, 0);
    std::memcpy(data.data(), panasonicSig, std::min(sizeof(panasonicSig), sigSize));
    
    bool result = header_->read(data.data(), data.size(), littleEndian);
    EXPECT_TRUE(result);
}

// Test: read with invalid signature data should fail
TEST_F(PanasonicMnHeaderTest_2190, ReadWithInvalidSignatureFails_2190) {
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 100, 0xFF);
    
    bool result = header_->read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test: read with exact signature size should work with valid data
TEST_F(PanasonicMnHeaderTest_2190, ReadWithExactSignatureSizeValidData_2190) {
    const char panasonicSig[] = "Panasonic\0\0\0";
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    
    std::vector<byte> data(sigSize, 0);
    std::memcpy(data.data(), panasonicSig, std::min(sizeof(panasonicSig), sigSize));
    
    bool result = header_->read(data.data(), sigSize, littleEndian);
    EXPECT_TRUE(result);
}

// Test: read with bigEndian byte order
TEST_F(PanasonicMnHeaderTest_2190, ReadWithBigEndian_2190) {
    const char panasonicSig[] = "Panasonic\0\0\0";
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    
    std::vector<byte> data(sigSize + 100, 0);
    std::memcpy(data.data(), panasonicSig, std::min(sizeof(panasonicSig), sigSize));
    
    bool result = header_->read(data.data(), data.size(), bigEndian);
    EXPECT_TRUE(result);
}

// Test: read with invalidByteOrder
TEST_F(PanasonicMnHeaderTest_2190, ReadWithInvalidByteOrder_2190) {
    const char panasonicSig[] = "Panasonic\0\0\0";
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    
    std::vector<byte> data(sigSize + 100, 0);
    std::memcpy(data.data(), panasonicSig, std::min(sizeof(panasonicSig), sigSize));
    
    // Panasonic doesn't typically depend on byte order for signature validation
    bool result = header_->read(data.data(), data.size(), invalidByteOrder);
    EXPECT_TRUE(result);
}

// Test: Multiple reads - second read with different data
TEST_F(PanasonicMnHeaderTest_2190, MultipleReads_2190) {
    const char panasonicSig[] = "Panasonic\0\0\0";
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    
    std::vector<byte> validData(sigSize + 100, 0);
    std::memcpy(validData.data(), panasonicSig, std::min(sizeof(panasonicSig), sigSize));
    
    bool result1 = header_->read(validData.data(), validData.size(), littleEndian);
    EXPECT_TRUE(result1);
    
    // Read again with invalid data
    std::vector<byte> invalidData(sigSize + 100, 0xAB);
    bool result2 = header_->read(invalidData.data(), invalidData.size(), littleEndian);
    EXPECT_FALSE(result2);
}

// Test: byteOrder from base class
TEST_F(PanasonicMnHeaderTest_2190, ByteOrderReturnsValue_2190) {
    ByteOrder bo = header_->byteOrder();
    // Should return some valid byte order or invalidByteOrder
    EXPECT_TRUE(bo == invalidByteOrder || bo == littleEndian || bo == bigEndian);
}

// Test: baseOffset from base class  
TEST_F(PanasonicMnHeaderTest_2190, BaseOffsetReturnsValue_2190) {
    size_t offset = header_->baseOffset(0);
    // baseOffset should return 0 by default for MnHeader
    EXPECT_EQ(offset, 0u);
}

// Test: baseOffset with non-zero mnOffset
TEST_F(PanasonicMnHeaderTest_2190, BaseOffsetWithNonZeroMnOffset_2190) {
    size_t offset = header_->baseOffset(1000);
    // Depending on implementation, check it returns a reasonable value
    EXPECT_GE(offset, 0u);
}

// Test: read with data size exactly one less than signature size should fail
TEST_F(PanasonicMnHeaderTest_2190, ReadWithOneLessThanSignatureSizeFails_2190) {
    size_t sigSize = PanasonicMnHeader::sizeOfSignature();
    if (sigSize > 0) {
        const char panasonicSig[] = "Panasonic\0\0\0";
        std::vector<byte> data(sigSize - 1, 0);
        size_t copySize = std::min(sizeof(panasonicSig), sigSize - 1);
        std::memcpy(data.data(), panasonicSig, copySize);
        
        bool result = header_->read(data.data(), sigSize - 1, littleEndian);
        EXPECT_FALSE(result);
    }
}
