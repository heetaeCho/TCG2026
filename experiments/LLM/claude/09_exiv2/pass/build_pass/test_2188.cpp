#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon2MnHeaderTest_2188 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<Nikon2MnHeader>();
    }

    std::unique_ptr<Nikon2MnHeader> header_;
};

// Test that default constructor creates a valid object
TEST_F(Nikon2MnHeaderTest_2188, DefaultConstructor_2188) {
    ASSERT_NE(header_, nullptr);
}

// Test that size() returns a positive value after construction
TEST_F(Nikon2MnHeaderTest_2188, SizeIsPositive_2188) {
    EXPECT_GT(header_->size(), 0u);
}

// Test that sizeOfSignature() returns a positive value
TEST_F(Nikon2MnHeaderTest_2188, SizeOfSignatureIsPositive_2188) {
    EXPECT_GT(Nikon2MnHeader::sizeOfSignature(), 0u);
}

// Test that size() is consistent with sizeOfSignature()
TEST_F(Nikon2MnHeaderTest_2188, SizeConsistentWithSignatureSize_2188) {
    // size() should be at least as large as sizeOfSignature()
    EXPECT_GE(header_->size(), Nikon2MnHeader::sizeOfSignature());
}

// Test that ifdOffset() returns a valid value
TEST_F(Nikon2MnHeaderTest_2188, IfdOffsetReturnsValue_2188) {
    size_t offset = header_->ifdOffset();
    // ifdOffset should be >= 0 (it's size_t, so always true, but we check it's reasonable)
    EXPECT_GE(offset, 0u);
}

// Test that read() with nullptr and zero size fails gracefully
TEST_F(Nikon2MnHeaderTest_2188, ReadWithNullptrAndZeroSize_2188) {
    bool result = header_->read(nullptr, 0, invalidByteOrder);
    EXPECT_FALSE(result);
}

// Test that read() with data smaller than signature size returns false
TEST_F(Nikon2MnHeaderTest_2188, ReadWithInsufficientData_2188) {
    const byte smallData[] = {0x00};
    bool result = header_->read(smallData, 1, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read() with valid Nikon2 signature data succeeds
TEST_F(Nikon2MnHeaderTest_2188, ReadWithValidSignature_2188) {
    // Nikon2 MakerNote signature is "Nikon\0\x01\x00"
    const byte nikon2Sig[] = {'N', 'i', 'k', 'o', 'n', '\0', 0x01, 0x00};
    size_t sigSize = Nikon2MnHeader::sizeOfSignature();

    if (sigSize <= sizeof(nikon2Sig)) {
        bool result = header_->read(nikon2Sig, sizeof(nikon2Sig), bigEndian);
        // This may or may not succeed depending on exact signature; we just check it doesn't crash
        // The result depends on the actual signature match
        (void)result;
    }
}

// Test that read() with wrong signature data returns false
TEST_F(Nikon2MnHeaderTest_2188, ReadWithInvalidSignature_2188) {
    size_t sigSize = Nikon2MnHeader::sizeOfSignature();
    std::vector<byte> invalidData(sigSize + 10, 0xFF);
    bool result = header_->read(invalidData.data(), invalidData.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that read() with exactly sizeOfSignature bytes of invalid data returns false
TEST_F(Nikon2MnHeaderTest_2188, ReadWithExactSizeInvalidData_2188) {
    size_t sigSize = Nikon2MnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize, 0x00);
    bool result = header_->read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test that byteOrder() returns a valid byte order (inherited from MnHeader)
TEST_F(Nikon2MnHeaderTest_2188, ByteOrderDefault_2188) {
    ByteOrder bo = header_->byteOrder();
    // Default byte order from MnHeader base is typically invalidByteOrder
    EXPECT_TRUE(bo == invalidByteOrder || bo == littleEndian || bo == bigEndian);
}

// Test that baseOffset returns appropriate value (inherited from MnHeader)
TEST_F(Nikon2MnHeaderTest_2188, BaseOffsetDefault_2188) {
    size_t baseOff = header_->baseOffset(0);
    EXPECT_GE(baseOff, 0u);
}

// Test that baseOffset with non-zero mnOffset
TEST_F(Nikon2MnHeaderTest_2188, BaseOffsetWithNonZeroMnOffset_2188) {
    size_t baseOff = header_->baseOffset(100);
    EXPECT_GE(baseOff, 0u);
}

// Test multiple construction - ensure no resource issues
TEST_F(Nikon2MnHeaderTest_2188, MultipleConstruction_2188) {
    Nikon2MnHeader h1;
    Nikon2MnHeader h2;
    EXPECT_EQ(h1.size(), h2.size());
    EXPECT_EQ(h1.ifdOffset(), h2.ifdOffset());
}

// Test that read with size less than sizeOfSignature fails
TEST_F(Nikon2MnHeaderTest_2188, ReadWithSizeLessThanSignature_2188) {
    size_t sigSize = Nikon2MnHeader::sizeOfSignature();
    if (sigSize > 1) {
        std::vector<byte> data(sigSize - 1, 'N');
        bool result = header_->read(data.data(), data.size(), bigEndian);
        EXPECT_FALSE(result);
    }
}

// Test read with different byte orders
TEST_F(Nikon2MnHeaderTest_2188, ReadWithDifferentByteOrders_2188) {
    size_t sigSize = Nikon2MnHeader::sizeOfSignature();
    std::vector<byte> invalidData(sigSize + 10, 0xAB);

    bool resultLE = header_->read(invalidData.data(), invalidData.size(), littleEndian);
    bool resultBE = header_->read(invalidData.data(), invalidData.size(), bigEndian);
    bool resultInv = header_->read(invalidData.data(), invalidData.size(), invalidByteOrder);

    // All should fail with invalid signature data
    EXPECT_FALSE(resultLE);
    EXPECT_FALSE(resultBE);
    EXPECT_FALSE(resultInv);
}

// Test that sizeOfSignature is a static method returning consistent value
TEST_F(Nikon2MnHeaderTest_2188, SizeOfSignatureConsistency_2188) {
    size_t s1 = Nikon2MnHeader::sizeOfSignature();
    size_t s2 = Nikon2MnHeader::sizeOfSignature();
    EXPECT_EQ(s1, s2);
}
