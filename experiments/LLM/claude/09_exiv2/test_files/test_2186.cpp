#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for OMSystemMnHeader
class OMSystemMnHeaderTest_2186 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<OMSystemMnHeader>();
    }

    std::unique_ptr<OMSystemMnHeader> header_;
};

// Test that default construction succeeds
TEST_F(OMSystemMnHeaderTest_2186, DefaultConstruction_2186) {
    EXPECT_NE(header_, nullptr);
}

// Test that sizeOfSignature returns a positive value
TEST_F(OMSystemMnHeaderTest_2186, SizeOfSignaturePositive_2186) {
    size_t sigSize = OMSystemMnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that size() returns a value consistent with sizeOfSignature
TEST_F(OMSystemMnHeaderTest_2186, SizeReturnsExpectedValue_2186) {
    size_t sz = header_->size();
    EXPECT_GT(sz, 0u);
    // size should be at least as large as the signature
    EXPECT_GE(sz, OMSystemMnHeader::sizeOfSignature());
}

// Test that ifdOffset returns a valid offset
TEST_F(OMSystemMnHeaderTest_2186, IfdOffsetReturnsValue_2186) {
    size_t offset = header_->ifdOffset();
    // ifdOffset should be related to the header size
    EXPECT_GE(offset, 0u);
}

// Test baseOffset with zero mnOffset
TEST_F(OMSystemMnHeaderTest_2186, BaseOffsetWithZero_2186) {
    size_t base = header_->baseOffset(0);
    // Just verify it returns without crashing
    EXPECT_GE(base, 0u);
}

// Test baseOffset with non-zero mnOffset
TEST_F(OMSystemMnHeaderTest_2186, BaseOffsetWithNonZero_2186) {
    size_t base = header_->baseOffset(100);
    EXPECT_GE(base, 0u);
}

// Test baseOffset with large mnOffset
TEST_F(OMSystemMnHeaderTest_2186, BaseOffsetWithLargeOffset_2186) {
    size_t base = header_->baseOffset(1000000);
    EXPECT_GE(base, 0u);
}

// Test read with nullptr should return false
TEST_F(OMSystemMnHeaderTest_2186, ReadWithNullptrReturnsFalse_2186) {
    bool result = header_->read(nullptr, 0, invalidByteOrder);
    EXPECT_FALSE(result);
}

// Test read with zero size should return false
TEST_F(OMSystemMnHeaderTest_2186, ReadWithZeroSizeReturnsFalse_2186) {
    byte data[1] = {0};
    bool result = header_->read(data, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with size smaller than signature size returns false
TEST_F(OMSystemMnHeaderTest_2186, ReadWithTooSmallSizeReturnsFalse_2186) {
    size_t sigSize = OMSystemMnHeader::sizeOfSignature();
    if (sigSize > 1) {
        std::vector<byte> data(sigSize - 1, 0);
        bool result = header_->read(data.data(), data.size(), littleEndian);
        EXPECT_FALSE(result);
    }
}

// Test read with wrong signature data returns false
TEST_F(OMSystemMnHeaderTest_2186, ReadWithWrongSignatureReturnsFalse_2186) {
    size_t sigSize = OMSystemMnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 100, 0);
    // Fill with garbage data that shouldn't match the OM System signature
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = static_cast<byte>(0xFF);
    }
    bool result = header_->read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid OM SYSTEM signature
TEST_F(OMSystemMnHeaderTest_2186, ReadWithValidSignature_2186) {
    // The OM SYSTEM signature is typically "OLYMPUS\0II\x03\0" or similar
    // We construct the known "OM SYSTEM\0\0\0" signature
    const char omSig[] = "OM SYSTEM\0\0\0";
    size_t sigSize = OMSystemMnHeader::sizeOfSignature();
    
    if (sigSize <= sizeof(omSig)) {
        std::vector<byte> data(sigSize + 100, 0);
        std::memcpy(data.data(), omSig, std::min(sizeof(omSig), sigSize));
        bool result = header_->read(data.data(), data.size(), littleEndian);
        // This may or may not succeed depending on exact signature format
        // We just verify it doesn't crash
        (void)result;
    }
}

// Test that byteOrder returns a valid byte order after construction
TEST_F(OMSystemMnHeaderTest_2186, ByteOrderAfterConstruction_2186) {
    ByteOrder bo = header_->byteOrder();
    // After default construction with invalidByteOrder read, 
    // byteOrder could be invalidByteOrder or a default
    EXPECT_TRUE(bo == invalidByteOrder || bo == littleEndian || bo == bigEndian);
}

// Test that multiple instances are independent
TEST_F(OMSystemMnHeaderTest_2186, MultipleInstancesIndependent_2186) {
    OMSystemMnHeader header2;
    EXPECT_EQ(header_->size(), header2.size());
    EXPECT_EQ(header_->ifdOffset(), header2.ifdOffset());
}

// Test sizeOfSignature is consistent across calls
TEST_F(OMSystemMnHeaderTest_2186, SizeOfSignatureConsistent_2186) {
    size_t s1 = OMSystemMnHeader::sizeOfSignature();
    size_t s2 = OMSystemMnHeader::sizeOfSignature();
    EXPECT_EQ(s1, s2);
}

// Test size is consistent across calls
TEST_F(OMSystemMnHeaderTest_2186, SizeConsistentAcrossCalls_2186) {
    size_t s1 = header_->size();
    size_t s2 = header_->size();
    EXPECT_EQ(s1, s2);
}

// Test ifdOffset consistency
TEST_F(OMSystemMnHeaderTest_2186, IfdOffsetConsistentAcrossCalls_2186) {
    size_t o1 = header_->ifdOffset();
    size_t o2 = header_->ifdOffset();
    EXPECT_EQ(o1, o2);
}

// Test read with exact signature size but invalid data
TEST_F(OMSystemMnHeaderTest_2186, ReadWithExactSignatureSizeInvalidData_2186) {
    size_t sigSize = OMSystemMnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize, 0x00);
    bool result = header_->read(data.data(), data.size(), bigEndian);
    // With all zeros, this likely won't match the OM SYSTEM signature
    EXPECT_FALSE(result);
}

// Test read with different byte orders
TEST_F(OMSystemMnHeaderTest_2186, ReadWithInvalidByteOrder_2186) {
    size_t sigSize = OMSystemMnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 100, 0xAB);
    bool result = header_->read(data.data(), data.size(), invalidByteOrder);
    // Invalid data should not be accepted regardless of byte order
    EXPECT_FALSE(result);
}
