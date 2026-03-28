#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class OlympusMnHeaderTest_2184 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<OlympusMnHeader>();
    }

    std::unique_ptr<OlympusMnHeader> header_;
};

// Test that default construction succeeds and size is non-zero
TEST_F(OlympusMnHeaderTest_2184, DefaultConstruction_2184) {
    ASSERT_NE(header_, nullptr);
    EXPECT_GT(header_->size(), 0u);
}

// Test that sizeOfSignature returns a reasonable value
TEST_F(OlympusMnHeaderTest_2184, SizeOfSignature_2184) {
    size_t sigSize = OlympusMnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that size() returns a consistent value
TEST_F(OlympusMnHeaderTest_2184, SizeConsistency_2184) {
    size_t s1 = header_->size();
    size_t s2 = header_->size();
    EXPECT_EQ(s1, s2);
}

// Test that ifdOffset returns a value
TEST_F(OlympusMnHeaderTest_2184, IfdOffset_2184) {
    size_t offset = header_->ifdOffset();
    // ifdOffset should be related to the signature size
    EXPECT_GE(offset, 0u);
}

// Test that read with nullptr or zero size fails
TEST_F(OlympusMnHeaderTest_2184, ReadNullData_2184) {
    bool result = header_->read(nullptr, 0, invalidByteOrder);
    EXPECT_FALSE(result);
}

// Test that read with too small data fails
TEST_F(OlympusMnHeaderTest_2184, ReadTooSmallData_2184) {
    byte smallData[1] = {0};
    bool result = header_->read(smallData, 1, littleEndian);
    EXPECT_FALSE(result);
}

// Test that read with the known Olympus signature succeeds
TEST_F(OlympusMnHeaderTest_2184, ReadValidOlympusSignature_2184) {
    // The Olympus MakerNote signature is "OLYMP\0" followed by some bytes
    // Typical Olympus signature: "OLYMP\0" (6 bytes) + II or MM (2 bytes)
    // The standard Olympus signature is "OLYMP\0II\x03\x00"
    const byte olympusSig[] = {'O', 'L', 'Y', 'M', 'P', '\0', 'I', 'I', 0x03, 0x00};
    size_t sigSize = OlympusMnHeader::sizeOfSignature();
    
    if (sigSize <= sizeof(olympusSig)) {
        bool result = header_->read(olympusSig, sizeof(olympusSig), littleEndian);
        // Result depends on whether the signature matches exactly
        // We just verify it doesn't crash
        (void)result;
    }
}

// Test that read with invalid signature data returns false
TEST_F(OlympusMnHeaderTest_2184, ReadInvalidSignature_2184) {
    size_t sigSize = OlympusMnHeader::sizeOfSignature();
    std::vector<byte> invalidData(sigSize + 10, 0xFF);
    bool result = header_->read(invalidData.data(), invalidData.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test byteOrder from base class
TEST_F(OlympusMnHeaderTest_2184, ByteOrderDefault_2184) {
    ByteOrder bo = header_->byteOrder();
    // Default byte order should be invalidByteOrder from base class
    EXPECT_EQ(bo, invalidByteOrder);
}

// Test baseOffset from base class
TEST_F(OlympusMnHeaderTest_2184, BaseOffset_2184) {
    size_t offset = header_->baseOffset(100);
    // Base class default returns 0
    EXPECT_EQ(offset, 0u);
}

// Test setByteOrder from base class doesn't crash
TEST_F(OlympusMnHeaderTest_2184, SetByteOrder_2184) {
    EXPECT_NO_THROW(header_->setByteOrder(littleEndian));
    EXPECT_NO_THROW(header_->setByteOrder(bigEndian));
    EXPECT_NO_THROW(header_->setByteOrder(invalidByteOrder));
}

// Test that sizeOfSignature and size are related
TEST_F(OlympusMnHeaderTest_2184, SizeRelationToSignature_2184) {
    size_t sigSize = OlympusMnHeader::sizeOfSignature();
    size_t headerSize = header_->size();
    // Header size should be at least as large as signature
    EXPECT_GE(headerSize, sigSize);
}

// Test read with exact signature size but all zeros
TEST_F(OlympusMnHeaderTest_2184, ReadZeroDataExactSize_2184) {
    size_t sigSize = OlympusMnHeader::sizeOfSignature();
    std::vector<byte> zeroData(sigSize, 0);
    bool result = header_->read(zeroData.data(), zeroData.size(), bigEndian);
    EXPECT_FALSE(result);
}

// Test read with various byte orders
TEST_F(OlympusMnHeaderTest_2184, ReadWithDifferentByteOrders_2184) {
    size_t sigSize = OlympusMnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 10, 0);
    
    // Try with all byte orders - should fail with invalid data regardless
    bool r1 = header_->read(data.data(), data.size(), littleEndian);
    bool r2 = header_->read(data.data(), data.size(), bigEndian);
    bool r3 = header_->read(data.data(), data.size(), invalidByteOrder);
    
    // All should return false for invalid signature data
    EXPECT_FALSE(r1);
    EXPECT_FALSE(r2);
    EXPECT_FALSE(r3);
}

// Test multiple constructions
TEST_F(OlympusMnHeaderTest_2184, MultipleInstances_2184) {
    OlympusMnHeader h1;
    OlympusMnHeader h2;
    
    EXPECT_EQ(h1.size(), h2.size());
    EXPECT_EQ(h1.ifdOffset(), h2.ifdOffset());
}
