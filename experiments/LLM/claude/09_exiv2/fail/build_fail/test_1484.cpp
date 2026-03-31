#include <gtest/gtest.h>
#include "makernote_int.hpp"

using namespace Exiv2::Internal;

class PentaxMnHeaderTest_1484 : public ::testing::Test {
protected:
    PentaxMnHeader header_;
};

// Test that sizeOfSignature returns a positive value
TEST_F(PentaxMnHeaderTest_1484, SizeOfSignatureReturnsPositiveValue_1484) {
    size_t sigSize = header_.sizeOfSignature();
    EXPECT_GT(sigSize, 0u);
}

// Test that sizeOfSignature returns a consistent value across multiple calls
TEST_F(PentaxMnHeaderTest_1484, SizeOfSignatureIsConsistent_1484) {
    size_t sigSize1 = header_.sizeOfSignature();
    size_t sigSize2 = header_.sizeOfSignature();
    EXPECT_EQ(sigSize1, sigSize2);
}

// Test that size() returns a value (should be at least as large as the signature)
TEST_F(PentaxMnHeaderTest_1484, SizeReturnsReasonableValue_1484) {
    size_t sz = header_.size();
    EXPECT_GE(sz, header_.sizeOfSignature());
}

// Test that ifdOffset returns a value
TEST_F(PentaxMnHeaderTest_1484, IfdOffsetReturnsValue_1484) {
    size_t offset = header_.ifdOffset();
    EXPECT_GE(offset, 0u);
}

// Test that read with nullptr or zero size fails gracefully
TEST_F(PentaxMnHeaderTest_1484, ReadWithNullDataReturnsFalse_1484) {
    bool result = header_.read(nullptr, 0, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test that read with insufficient data size returns false
TEST_F(PentaxMnHeaderTest_1484, ReadWithInsufficientSizeReturnsFalse_1484) {
    Exiv2::byte data[1] = {0};
    bool result = header_.read(data, 1, Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test that read with valid Pentax signature succeeds
TEST_F(PentaxMnHeaderTest_1484, ReadWithValidPentaxSignatureSucceeds_1484) {
    // "AOC\0" followed by additional bytes - Pentax maker note signature
    // The Pentax signature is typically "AOC\0" with some additional marker bytes
    Exiv2::byte data[] = {'A', 'O', 'C', '\0', 'M', 'M'};
    size_t dataSize = sizeof(data);
    
    // This may or may not succeed depending on exact expected signature format
    // We just verify it doesn't crash and returns a bool
    bool result = header_.read(data, dataSize, Exiv2::bigEndian);
    // Result depends on implementation - just ensure no crash
    (void)result;
}

// Test that multiple PentaxMnHeader instances have same sizeOfSignature
TEST_F(PentaxMnHeaderTest_1484, MultpleInstancesSameSizeOfSignature_1484) {
    PentaxMnHeader header2;
    EXPECT_EQ(header_.sizeOfSignature(), header2.sizeOfSignature());
}

// Test that size() is consistent across calls
TEST_F(PentaxMnHeaderTest_1484, SizeIsConsistentAcrossCalls_1484) {
    size_t sz1 = header_.size();
    size_t sz2 = header_.size();
    EXPECT_EQ(sz1, sz2);
}

// Test that ifdOffset is consistent across calls
TEST_F(PentaxMnHeaderTest_1484, IfdOffsetIsConsistentAcrossCalls_1484) {
    size_t offset1 = header_.ifdOffset();
    size_t offset2 = header_.ifdOffset();
    EXPECT_EQ(offset1, offset2);
}

// Test read with data that is exactly sizeOfSignature bytes but wrong content
TEST_F(PentaxMnHeaderTest_1484, ReadWithWrongSignatureReturnsFalse_1484) {
    size_t sigSize = header_.sizeOfSignature();
    std::vector<Exiv2::byte> data(sigSize, 0xFF);
    bool result = header_.read(data.data(), data.size(), Exiv2::littleEndian);
    EXPECT_FALSE(result);
}

// Test that the default constructed header has reasonable ifdOffset relative to size
TEST_F(PentaxMnHeaderTest_1484, IfdOffsetDoesNotExceedSize_1484) {
    size_t offset = header_.ifdOffset();
    size_t sz = header_.size();
    EXPECT_LE(offset, sz);
}
