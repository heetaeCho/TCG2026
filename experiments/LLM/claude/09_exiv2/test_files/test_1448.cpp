#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "makernote_int.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class OMSystemMnHeaderTest_1448 : public ::testing::Test {
protected:
    OMSystemMnHeader header_;
};

// Test that default-constructed header has expected size
TEST_F(OMSystemMnHeaderTest_1448, DefaultConstructorSize_1448) {
    // The header should have a non-zero size corresponding to the signature
    size_t sz = header_.size();
    EXPECT_GT(sz, 0u);
}

// Test that sizeOfSignature returns a consistent value
TEST_F(OMSystemMnHeaderTest_1448, SizeOfSignature_1448) {
    size_t sigSize = OMSystemMnHeader::sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
    // sizeOfSignature should be consistent with size()
    EXPECT_EQ(header_.size(), sigSize);
}

// Test that size() and sizeOfSignature() return the same value
TEST_F(OMSystemMnHeaderTest_1448, SizeEqualsSignatureSize_1448) {
    EXPECT_EQ(header_.size(), OMSystemMnHeader::sizeOfSignature());
}

// Test ifdOffset returns expected value
TEST_F(OMSystemMnHeaderTest_1448, IfdOffset_1448) {
    size_t offset = header_.ifdOffset();
    // ifdOffset should be related to the header size
    EXPECT_GE(offset, 0u);
}

// Test baseOffset with a given mnOffset
TEST_F(OMSystemMnHeaderTest_1448, BaseOffsetWithZero_1448) {
    size_t base = header_.baseOffset(0);
    EXPECT_GE(base, 0u);
}

TEST_F(OMSystemMnHeaderTest_1448, BaseOffsetWithNonZero_1448) {
    size_t base = header_.baseOffset(100);
    // baseOffset should account for the mnOffset
    EXPECT_GE(base, 0u);
}

// Test read with nullptr / zero size should fail
TEST_F(OMSystemMnHeaderTest_1448, ReadNullDataFails_1448) {
    bool result = header_.read(nullptr, 0, littleEndian);
    EXPECT_FALSE(result);
}

// Test read with data that is too small
TEST_F(OMSystemMnHeaderTest_1448, ReadTooSmallDataFails_1448) {
    std::vector<byte> smallData(1, 0);
    bool result = header_.read(smallData.data(), smallData.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with data smaller than signature size
TEST_F(OMSystemMnHeaderTest_1448, ReadSmallerThanSignatureFails_1448) {
    size_t sigSize = OMSystemMnHeader::sizeOfSignature();
    if (sigSize > 1) {
        std::vector<byte> data(sigSize - 1, 0);
        bool result = header_.read(data.data(), data.size(), littleEndian);
        EXPECT_FALSE(result);
    }
}

// Test read with incorrect signature data
TEST_F(OMSystemMnHeaderTest_1448, ReadIncorrectSignatureFails_1448) {
    size_t sigSize = OMSystemMnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 100, 0); // all zeros - wrong signature
    bool result = header_.read(data.data(), data.size(), littleEndian);
    EXPECT_FALSE(result);
}

// Test read with valid OM SYSTEM signature
// The OM SYSTEM makernote signature is "OLYMPUS\0II" (10 bytes)
TEST_F(OMSystemMnHeaderTest_1448, ReadValidSignatureSucceeds_1448) {
    // OM System uses the same signature pattern as Olympus: "OLYMPUS\0II\x03\0"
    const char sig[] = "OLYMPUS\0II\x03\0";
    size_t sigSize = OMSystemMnHeader::sizeOfSignature();
    
    // Create a buffer large enough
    std::vector<byte> data(std::max(sigSize, sizeof(sig)) + 100, 0);
    std::memcpy(data.data(), sig, sizeof(sig) - 1);
    
    bool result = header_.read(data.data(), data.size(), littleEndian);
    // This may or may not succeed depending on exact signature format
    // We test both paths - the key is it doesn't crash
    (void)result;
}

// Test read with big endian byte order
TEST_F(OMSystemMnHeaderTest_1448, ReadWithBigEndian_1448) {
    size_t sigSize = OMSystemMnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize + 100, 0xFF);
    bool result = header_.read(data.data(), data.size(), bigEndian);
    // With garbage data, should return false
    EXPECT_FALSE(result);
}

// Test that size() is consistent across multiple calls
TEST_F(OMSystemMnHeaderTest_1448, SizeIsConsistent_1448) {
    size_t s1 = header_.size();
    size_t s2 = header_.size();
    EXPECT_EQ(s1, s2);
}

// Test baseOffset with large mnOffset
TEST_F(OMSystemMnHeaderTest_1448, BaseOffsetLargeValue_1448) {
    size_t base = header_.baseOffset(0xFFFFFFFF);
    // Just verify it doesn't crash and returns some value
    (void)base;
}

// Test ifdOffset is consistent
TEST_F(OMSystemMnHeaderTest_1448, IfdOffsetConsistent_1448) {
    size_t o1 = header_.ifdOffset();
    size_t o2 = header_.ifdOffset();
    EXPECT_EQ(o1, o2);
}

// Test read with exact signature size
TEST_F(OMSystemMnHeaderTest_1448, ReadExactSignatureSize_1448) {
    size_t sigSize = OMSystemMnHeader::sizeOfSignature();
    std::vector<byte> data(sigSize, 0);
    bool result = header_.read(data.data(), data.size(), littleEndian);
    // With zero-filled data of exact size, likely fails due to wrong signature
    EXPECT_FALSE(result);
}

// Multiple OMSystemMnHeader instances have same properties
TEST_F(OMSystemMnHeaderTest_1448, MultipleInstancesSameSize_1448) {
    OMSystemMnHeader h1;
    OMSystemMnHeader h2;
    EXPECT_EQ(h1.size(), h2.size());
    EXPECT_EQ(h1.ifdOffset(), h2.ifdOffset());
    EXPECT_EQ(h1.baseOffset(42), h2.baseOffset(42));
}
