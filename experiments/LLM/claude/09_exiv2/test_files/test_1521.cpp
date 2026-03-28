#include <gtest/gtest.h>
#include <cstdint>
#include <memory>
#include <vector>

// Include necessary Exiv2 headers
#include "makernote_int.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewPanasonicMnTest_1521 : public ::testing::Test {
protected:
    uint16_t tag_ = 0x927c;  // MakerNote tag
    IfdId group_ = IfdId::ifd0Id;
    IfdId mnGroup_ = IfdId::panasonicId;
    ByteOrder byteOrder_ = littleEndian;
};

// Test that nullptr is returned when size is 0 (below threshold)
TEST_F(NewPanasonicMnTest_1521, ReturnsNullptrWhenSizeIsZero_1521) {
    const byte data[] = {0};
    auto result = newPanasonicMn(tag_, group_, mnGroup_, data, 0, byteOrder_);
    EXPECT_EQ(result, nullptr);
}

// Test that nullptr is returned when size is 1 (well below threshold)
TEST_F(NewPanasonicMnTest_1521, ReturnsNullptrWhenSizeIsOne_1521) {
    const byte data[] = {0};
    auto result = newPanasonicMn(tag_, group_, mnGroup_, data, 1, byteOrder_);
    EXPECT_EQ(result, nullptr);
}

// Test that nullptr is returned when size is exactly at the boundary minus one
TEST_F(NewPanasonicMnTest_1521, ReturnsNullptrWhenSizeIsBelowThreshold_1521) {
    // PanasonicMnHeader::sizeOfSignature() + 14 is the minimum required
    // We need to figure out the threshold. The signature for Panasonic is "Panasonic\0\0\0"
    // which is 12 bytes. So threshold = 12 + 14 = 26. Size < 26 returns nullptr.
    // Let's test with size = 25 (just below threshold)
    std::vector<byte> data(25, 0);
    auto result = newPanasonicMn(tag_, group_, mnGroup_, data.data(), 25, byteOrder_);
    EXPECT_EQ(result, nullptr);
}

// Test that nullptr is returned for a small buffer
TEST_F(NewPanasonicMnTest_1521, ReturnsNullptrForSmallBuffer_1521) {
    std::vector<byte> data(10, 0);
    auto result = newPanasonicMn(tag_, group_, mnGroup_, data.data(), 10, byteOrder_);
    EXPECT_EQ(result, nullptr);
}

// Test that a valid TiffIfdMakernote is returned when size meets the threshold
TEST_F(NewPanasonicMnTest_1521, ReturnsValidMakernoteWhenSizeMeetsThreshold_1521) {
    // PanasonicMnHeader signature is "Panasonic\0\0\0" = 12 bytes
    // Threshold = 12 + 14 = 26
    std::vector<byte> data(26, 0);
    auto result = newPanasonicMn(tag_, group_, mnGroup_, data.data(), 26, byteOrder_);
    EXPECT_NE(result, nullptr);
}

// Test that a valid TiffIfdMakernote is returned when size exceeds the threshold
TEST_F(NewPanasonicMnTest_1521, ReturnsValidMakernoteWhenSizeExceedsThreshold_1521) {
    std::vector<byte> data(100, 0);
    auto result = newPanasonicMn(tag_, group_, mnGroup_, data.data(), 100, byteOrder_);
    EXPECT_NE(result, nullptr);
}

// Test with a large buffer
TEST_F(NewPanasonicMnTest_1521, ReturnsValidMakernoteForLargeBuffer_1521) {
    std::vector<byte> data(10000, 0);
    auto result = newPanasonicMn(tag_, group_, mnGroup_, data.data(), 10000, byteOrder_);
    EXPECT_NE(result, nullptr);
}

// Test that exact boundary size works (size == sizeOfSignature + 14)
TEST_F(NewPanasonicMnTest_1521, ReturnsValidMakernoteAtExactBoundary_1521) {
    // Exactly at the boundary: size == PanasonicMnHeader::sizeOfSignature() + 14
    size_t signatureSize = PanasonicMnHeader::sizeOfSignature();
    size_t threshold = signatureSize + 14;
    std::vector<byte> data(threshold, 0);
    auto result = newPanasonicMn(tag_, group_, mnGroup_, data.data(), threshold, byteOrder_);
    EXPECT_NE(result, nullptr);
}

// Test that size one below boundary returns nullptr
TEST_F(NewPanasonicMnTest_1521, ReturnsNullptrAtBoundaryMinusOne_1521) {
    size_t signatureSize = PanasonicMnHeader::sizeOfSignature();
    size_t belowThreshold = signatureSize + 14 - 1;
    std::vector<byte> data(belowThreshold, 0);
    auto result = newPanasonicMn(tag_, group_, mnGroup_, data.data(), belowThreshold, byteOrder_);
    EXPECT_EQ(result, nullptr);
}

// Test with big endian byte order
TEST_F(NewPanasonicMnTest_1521, WorksWithBigEndianByteOrder_1521) {
    std::vector<byte> data(100, 0);
    auto result = newPanasonicMn(tag_, group_, mnGroup_, data.data(), 100, bigEndian);
    EXPECT_NE(result, nullptr);
}

// Test that the data pointer content doesn't affect the size check for nullptr case
TEST_F(NewPanasonicMnTest_1521, DataContentDoesNotAffectSizeCheck_1521) {
    // Even with valid-looking data, if size is too small, should return nullptr
    std::vector<byte> data = {'P', 'a', 'n', 'a', 's', 'o', 'n', 'i', 'c', 0, 0, 0};
    auto result = newPanasonicMn(tag_, group_, mnGroup_, data.data(), data.size(), byteOrder_);
    EXPECT_EQ(result, nullptr);
}

// Test with different tag values
TEST_F(NewPanasonicMnTest_1521, WorksWithDifferentTagValues_1521) {
    std::vector<byte> data(100, 0);
    auto result = newPanasonicMn(0x0001, group_, mnGroup_, data.data(), 100, byteOrder_);
    EXPECT_NE(result, nullptr);
}

// Test that size exactly equal to signature size returns nullptr (missing 14 extra bytes)
TEST_F(NewPanasonicMnTest_1521, ReturnsNullptrWhenSizeEqualsSignatureSize_1521) {
    size_t signatureSize = PanasonicMnHeader::sizeOfSignature();
    std::vector<byte> data(signatureSize, 0);
    auto result = newPanasonicMn(tag_, group_, mnGroup_, data.data(), signatureSize, byteOrder_);
    EXPECT_EQ(result, nullptr);
}
