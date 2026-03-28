#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "makernote_int.hpp"
#include "types.hpp"

// We need IoWrapper for write tests
#include "image_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Olympus2MnHeaderTest_2185 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<Olympus2MnHeader>();
    }

    std::unique_ptr<Olympus2MnHeader> header_;
};

// Test that default construction succeeds
TEST_F(Olympus2MnHeaderTest_2185, DefaultConstruction_2185) {
    EXPECT_NE(header_, nullptr);
}

// Test that sizeOfSignature returns a positive value
TEST_F(Olympus2MnHeaderTest_2185, SizeOfSignaturePositive_2185) {
    size_t sigSize = Olympus2MnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that size() returns a value consistent with sizeOfSignature
TEST_F(Olympus2MnHeaderTest_2185, SizeReturnsExpectedValue_2185) {
    size_t sz = header_->size();
    EXPECT_GT(sz, 0u);
    // Size should be at least as large as the signature
    EXPECT_GE(sz, Olympus2MnHeader::sizeOfSignature());
}

// Test that ifdOffset returns a value
TEST_F(Olympus2MnHeaderTest_2185, IfdOffsetReturnsValue_2185) {
    size_t offset = header_->ifdOffset();
    // The IFD offset should be related to the header size
    EXPECT_GE(offset, 0u);
}

// Test that baseOffset returns the mnOffset parameter
TEST_F(Olympus2MnHeaderTest_2185, BaseOffsetWithZero_2185) {
    size_t baseOff = header_->baseOffset(0);
    // Just check it returns some value without crashing
    EXPECT_GE(baseOff, 0u);
}

// Test baseOffset with a non-zero mnOffset
TEST_F(Olympus2MnHeaderTest_2185, BaseOffsetWithNonZero_2185) {
    size_t baseOff = header_->baseOffset(100);
    EXPECT_GE(baseOff, 0u);
}

// Test baseOffset with a large mnOffset
TEST_F(Olympus2MnHeaderTest_2185, BaseOffsetWithLargeValue_2185) {
    size_t baseOff = header_->baseOffset(0xFFFFFF);
    EXPECT_GE(baseOff, 0u);
}

// Test read with nullptr data - should fail or handle gracefully
TEST_F(Olympus2MnHeaderTest_2185, ReadWithNullData_2185) {
    bool result = header_->read(nullptr, 0, invalidByteOrder);
    EXPECT_FALSE(result);
}

// Test read with empty data (size 0)
TEST_F(Olympus2MnHeaderTest_2185, ReadWithZeroSize_2185) {
    byte data[] = {0};
    bool result = header_->read(data, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with data too small for signature
TEST_F(Olympus2MnHeaderTest_2185, ReadWithTooSmallData_2185) {
    byte data[] = {0x4F}; // Just one byte
    bool result = header_->read(data, 1, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Olympus II signature
// Olympus II maker note signature is "OLYMPUS\0II\x03\0"
TEST_F(Olympus2MnHeaderTest_2185, ReadWithValidOlympus2Signature_2185) {
    // "OLYMPUS\0II\x03\0"
    const byte validSig[] = {'O', 'L', 'Y', 'M', 'P', 'U', 'S', 0x00, 'I', 'I', 0x03, 0x00};
    size_t sigSize = Olympus2MnHeader::sizeOfSignature();
    
    // Ensure we have enough data
    std::vector<byte> data(validSig, validSig + sizeof(validSig));
    // Pad if needed
    while (data.size() < sigSize) {
        data.push_back(0);
    }
    
    bool result = header_->read(data.data(), data.size(), littleEndian);
    EXPECT_TRUE(result);
}

// Test read with invalid signature data
TEST_F(Olympus2MnHeaderTest_2185, ReadWithInvalidSignature_2185) {
    size_t sigSize = Olympus2MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize, 0x00); // All zeros - not valid Olympus sig
    bool result = header_->read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid signature and bigEndian
TEST_F(Olympus2MnHeaderTest_2185, ReadWithValidSigBigEndian_2185) {
    const byte validSig[] = {'O', 'L', 'Y', 'M', 'P', 'U', 'S', 0x00, 'I', 'I', 0x03, 0x00};
    size_t sigSize = Olympus2MnHeader::sizeOfSignature();
    
    std::vector<byte> data(validSig, validSig + sizeof(validSig));
    while (data.size() < sigSize) {
        data.push_back(0);
    }
    
    bool result = header_->read(data.data(), data.size(), bigEndian);
    // The result depends on whether byte order matters for reading
    // We just verify no crash
    (void)result;
}

// Test read with invalidByteOrder
TEST_F(Olympus2MnHeaderTest_2185, ReadWithInvalidByteOrder_2185) {
    const byte validSig[] = {'O', 'L', 'Y', 'M', 'P', 'U', 'S', 0x00, 'I', 'I', 0x03, 0x00};
    size_t sigSize = Olympus2MnHeader::sizeOfSignature();
    
    std::vector<byte> data(validSig, validSig + sizeof(validSig));
    while (data.size() < sigSize) {
        data.push_back(0);
    }
    
    bool result = header_->read(data.data(), data.size(), invalidByteOrder);
    // After default construction, the header was read with invalidByteOrder
    // Just check it doesn't crash
    (void)result;
}

// Test that byteOrder returns a valid ByteOrder after default construction
TEST_F(Olympus2MnHeaderTest_2185, ByteOrderAfterConstruction_2185) {
    ByteOrder bo = header_->byteOrder();
    // Should be one of the valid values
    EXPECT_TRUE(bo == invalidByteOrder || bo == littleEndian || bo == bigEndian);
}

// Test that sizeOfSignature is consistent across calls
TEST_F(Olympus2MnHeaderTest_2185, SizeOfSignatureConsistency_2185) {
    size_t s1 = Olympus2MnHeader::sizeOfSignature();
    size_t s2 = Olympus2MnHeader::sizeOfSignature();
    EXPECT_EQ(s1, s2);
}

// Test multiple Olympus2MnHeader instances have same properties
TEST_F(Olympus2MnHeaderTest_2185, MultipleInstancesConsistency_2185) {
    Olympus2MnHeader header2;
    EXPECT_EQ(header_->size(), header2.size());
    EXPECT_EQ(header_->ifdOffset(), header2.ifdOffset());
}

// Test read with data exactly the size of signature
TEST_F(Olympus2MnHeaderTest_2185, ReadWithExactSignatureSize_2185) {
    const byte validSig[] = {'O', 'L', 'Y', 'M', 'P', 'U', 'S', 0x00, 'I', 'I', 0x03, 0x00};
    size_t sigSize = Olympus2MnHeader::sizeOfSignature();
    
    std::vector<byte> data(validSig, validSig + std::min(sizeof(validSig), sigSize));
    while (data.size() < sigSize) {
        data.push_back(0);
    }
    
    bool result = header_->read(data.data(), sigSize, littleEndian);
    // Should succeed with exact size
    EXPECT_TRUE(result);
}

// Test read with data slightly smaller than signature size
TEST_F(Olympus2MnHeaderTest_2185, ReadWithSizeOneLessThanSignature_2185) {
    size_t sigSize = Olympus2MnHeader::sizeOfSignature();
    if (sigSize > 0) {
        const byte validSig[] = {'O', 'L', 'Y', 'M', 'P', 'U', 'S', 0x00, 'I', 'I', 0x03, 0x00};
        std::vector<byte> data(validSig, validSig + std::min(sizeof(validSig), sigSize - 1));
        while (data.size() < sigSize - 1) {
            data.push_back(0);
        }
        
        bool result = header_->read(data.data(), sigSize - 1, littleEndian);
        EXPECT_FALSE(result);
    }
}

// Test that ifdOffset is consistent with size
TEST_F(Olympus2MnHeaderTest_2185, IfdOffsetRelationToSize_2185) {
    size_t offset = header_->ifdOffset();
    size_t sz = header_->size();
    // IFD offset should not exceed the header size
    EXPECT_LE(offset, sz);
}
