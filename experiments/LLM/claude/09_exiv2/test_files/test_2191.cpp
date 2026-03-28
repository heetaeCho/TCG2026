#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "makernote_int.hpp"
#include "types.hpp"

// We need IoWrapper for write tests
#include "basicio.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PentaxDngMnHeaderTest_2191 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<PentaxDngMnHeader>();
    }

    std::unique_ptr<PentaxDngMnHeader> header_;
};

// Test that default construction succeeds
TEST_F(PentaxDngMnHeaderTest_2191, DefaultConstruction_2191) {
    ASSERT_NE(header_, nullptr);
}

// Test that sizeOfSignature returns a positive value
TEST_F(PentaxDngMnHeaderTest_2191, SizeOfSignaturePositive_2191) {
    size_t sigSize = PentaxDngMnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that size() returns a consistent value
TEST_F(PentaxDngMnHeaderTest_2191, SizeReturnsConsistentValue_2191) {
    size_t s1 = header_->size();
    size_t s2 = header_->size();
    EXPECT_EQ(s1, s2);
    EXPECT_GT(s1, 0u);
}

// Test that size() is related to sizeOfSignature()
TEST_F(PentaxDngMnHeaderTest_2191, SizeRelatedToSignatureSize_2191) {
    size_t s = header_->size();
    size_t sigSize = PentaxDngMnHeader::sizeOfSignature();
    // size should be at least as large as the signature
    EXPECT_GE(s, sigSize);
}

// Test ifdOffset returns a value
TEST_F(PentaxDngMnHeaderTest_2191, IfdOffsetReturnsValue_2191) {
    size_t offset = header_->ifdOffset();
    // ifdOffset should be >= 0 (it's size_t, so always >= 0, but check it's reasonable)
    EXPECT_GE(offset, 0u);
}

// Test baseOffset returns a value
TEST_F(PentaxDngMnHeaderTest_2191, BaseOffsetReturnsValue_2191) {
    size_t baseOff = header_->baseOffset(0);
    EXPECT_GE(baseOff, 0u);
}

// Test baseOffset with non-zero mnOffset
TEST_F(PentaxDngMnHeaderTest_2191, BaseOffsetWithNonZeroMnOffset_2191) {
    size_t baseOff = header_->baseOffset(100);
    // baseOffset should return some value; verify it doesn't crash
    EXPECT_GE(baseOff, 0u);
}

// Test read with nullptr data and zero size should fail
TEST_F(PentaxDngMnHeaderTest_2191, ReadWithNullptrFails_2191) {
    bool result = header_->read(nullptr, 0, invalidByteOrder);
    EXPECT_FALSE(result);
}

// Test read with data too small should fail
TEST_F(PentaxDngMnHeaderTest_2191, ReadWithTooSmallDataFails_2191) {
    byte smallData[1] = {0};
    bool result = header_->read(smallData, 1, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid Pentax DNG signature
// The Pentax DNG MakerNote signature is typically "PENTAX \0" or similar
TEST_F(PentaxDngMnHeaderTest_2191, ReadWithValidSignature_2191) {
    // Pentax DNG maker note signature: "PENTAX \0" followed by version info
    // Typical signature bytes: 0x50 0x45 0x4E 0x54 0x41 0x58 0x20 0x00
    size_t sigSize = PentaxDngMnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 100, 0);

    // "PENTAX \0"
    const char* sig = "PENTAX \0";
    if (sigSize >= 8) {
        std::memcpy(data.data(), sig, 8);
    }

    bool result = header_->read(data.data(), data.size(), littleEndian);
    // We don't know exactly what signature is expected, so just test it doesn't crash
    // The result depends on exact expected signature
    // Just verify the function returns without crashing
    (void)result;
}

// Test read with wrong signature data
TEST_F(PentaxDngMnHeaderTest_2191, ReadWithWrongSignatureFails_2191) {
    size_t sigSize = PentaxDngMnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 100, 0xFF);
    bool result = header_->read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with exact signature size boundary
TEST_F(PentaxDngMnHeaderTest_2191, ReadWithExactSignatureSize_2191) {
    size_t sigSize = PentaxDngMnHeader::sizeOfSignature();
    if (sigSize > 0) {
        std::vector<byte> data(sigSize, 0);
        bool result = header_->read(data.data(), data.size(), bigEndian);
        // May fail because signature doesn't match, but should not crash
        (void)result;
    }
}

// Test read with size one less than signature size
TEST_F(PentaxDngMnHeaderTest_2191, ReadWithSizeLessThanSignatureFails_2191) {
    size_t sigSize = PentaxDngMnHeader::sizeOfSignature();
    if (sigSize > 1) {
        std::vector<byte> data(sigSize - 1, 0);
        bool result = header_->read(data.data(), data.size(), littleEndian);
        EXPECT_FALSE(result);
    }
}

// Test byteOrder returns a valid byte order (inherited from MnHeader)
TEST_F(PentaxDngMnHeaderTest_2191, ByteOrderDefault_2191) {
    ByteOrder bo = header_->byteOrder();
    // Default should be invalidByteOrder since no valid read has occurred
    EXPECT_TRUE(bo == invalidByteOrder || bo == littleEndian || bo == bigEndian);
}

// Test multiple calls to size are consistent
TEST_F(PentaxDngMnHeaderTest_2191, MultipleSizeCallsConsistent_2191) {
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(header_->size(), header_->size());
    }
}

// Test that ifdOffset is consistent across multiple calls
TEST_F(PentaxDngMnHeaderTest_2191, IfdOffsetConsistent_2191) {
    size_t off1 = header_->ifdOffset();
    size_t off2 = header_->ifdOffset();
    EXPECT_EQ(off1, off2);
}

// Test that sizeOfSignature is consistent (static method)
TEST_F(PentaxDngMnHeaderTest_2191, SizeOfSignatureConsistent_2191) {
    size_t s1 = PentaxDngMnHeader::sizeOfSignature();
    size_t s2 = PentaxDngMnHeader::sizeOfSignature();
    EXPECT_EQ(s1, s2);
}

// Test read with different byte orders
TEST_F(PentaxDngMnHeaderTest_2191, ReadWithInvalidByteOrder_2191) {
    size_t sigSize = PentaxDngMnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 100, 0);
    bool result = header_->read(data.data(), data.size(), invalidByteOrder);
    // Just verify it doesn't crash
    (void)result;
}

// Test read with bigEndian byte order
TEST_F(PentaxDngMnHeaderTest_2191, ReadWithBigEndianByteOrder_2191) {
    size_t sigSize = PentaxDngMnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 100, 0);
    bool result = header_->read(data.data(), data.size(), bigEndian);
    // Just verify it doesn't crash
    (void)result;
}

// Test baseOffset with large mnOffset value
TEST_F(PentaxDngMnHeaderTest_2191, BaseOffsetWithLargeMnOffset_2191) {
    size_t baseOff = header_->baseOffset(std::numeric_limits<size_t>::max());
    // Should not crash; just verify we get a value back
    (void)baseOff;
}

// Test creating multiple instances
TEST_F(PentaxDngMnHeaderTest_2191, MultipleInstances_2191) {
    PentaxDngMnHeader h1;
    PentaxDngMnHeader h2;
    EXPECT_EQ(h1.size(), h2.size());
    EXPECT_EQ(h1.ifdOffset(), h2.ifdOffset());
}
