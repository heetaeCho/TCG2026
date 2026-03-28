#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "makernote_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewOMSystemMnTest_1514 : public ::testing::Test {
protected:
    // We need a buffer large enough for tests
    static constexpr size_t kMaxBufSize = 1024;
    byte buffer_[kMaxBufSize] = {};
    
    uint16_t tag_ = 0x927c;  // Typical MakerNote tag
    IfdId group_ = IfdId::ifd0Id;
    IfdId mnGroup_ = IfdId::olympusId;
    ByteOrder byteOrder_ = littleEndian;
    
    size_t threshold() {
        return OMSystemMnHeader::sizeOfSignature() + 18;
    }
};

TEST_F(NewOMSystemMnTest_1514, ReturnsNullptrWhenSizeIsZero_1514) {
    auto result = newOMSystemMn(tag_, group_, mnGroup_, buffer_, 0, byteOrder_);
    EXPECT_EQ(result, nullptr);
}

TEST_F(NewOMSystemMnTest_1514, ReturnsNullptrWhenSizeBelowThreshold_1514) {
    size_t tooSmall = threshold() - 1;
    auto result = newOMSystemMn(tag_, group_, mnGroup_, buffer_, tooSmall, byteOrder_);
    EXPECT_EQ(result, nullptr);
}

TEST_F(NewOMSystemMnTest_1514, ReturnsNullptrWhenSizeIsOne_1514) {
    auto result = newOMSystemMn(tag_, group_, mnGroup_, buffer_, 1, byteOrder_);
    EXPECT_EQ(result, nullptr);
}

TEST_F(NewOMSystemMnTest_1514, ReturnsNonNullWhenSizeEqualsThreshold_1514) {
    size_t exactThreshold = threshold();
    auto result = newOMSystemMn(tag_, group_, mnGroup_, buffer_, exactThreshold, byteOrder_);
    EXPECT_NE(result, nullptr);
}

TEST_F(NewOMSystemMnTest_1514, ReturnsNonNullWhenSizeAboveThreshold_1514) {
    size_t aboveThreshold = threshold() + 1;
    auto result = newOMSystemMn(tag_, group_, mnGroup_, buffer_, aboveThreshold, byteOrder_);
    EXPECT_NE(result, nullptr);
}

TEST_F(NewOMSystemMnTest_1514, ReturnsNonNullWhenSizeIsLarge_1514) {
    size_t largeSize = threshold() + 500;
    auto result = newOMSystemMn(tag_, group_, mnGroup_, buffer_, largeSize, byteOrder_);
    EXPECT_NE(result, nullptr);
}

TEST_F(NewOMSystemMnTest_1514, ReturnsTiffIfdMakernoteForValidSize_1514) {
    size_t validSize = threshold();
    auto result = newOMSystemMn(tag_, group_, mnGroup_, buffer_, validSize, byteOrder_);
    ASSERT_NE(result, nullptr);
    // Verify it's a proper TiffIfdMakernote by checking it's a valid unique_ptr
    TiffIfdMakernote* raw = result.get();
    EXPECT_NE(raw, nullptr);
}

TEST_F(NewOMSystemMnTest_1514, NullBufferWithSizeBelowThresholdReturnsNull_1514) {
    // When size is below threshold, buffer content shouldn't matter
    auto result = newOMSystemMn(tag_, group_, mnGroup_, nullptr, 0, byteOrder_);
    EXPECT_EQ(result, nullptr);
}

TEST_F(NewOMSystemMnTest_1514, BigEndianByteOrderWithValidSize_1514) {
    size_t validSize = threshold();
    auto result = newOMSystemMn(tag_, group_, mnGroup_, buffer_, validSize, bigEndian);
    EXPECT_NE(result, nullptr);
}

TEST_F(NewOMSystemMnTest_1514, BoundaryExactlyAtSignaturePlusSeventeen_1514) {
    // size = sizeOfSignature() + 17, which is threshold - 1
    size_t justBelow = OMSystemMnHeader::sizeOfSignature() + 17;
    auto result = newOMSystemMn(tag_, group_, mnGroup_, buffer_, justBelow, byteOrder_);
    EXPECT_EQ(result, nullptr);
}

TEST_F(NewOMSystemMnTest_1514, ThresholdValueIsConsistent_1514) {
    // Verify that the threshold boundary is exactly sizeOfSignature + 18
    size_t t = threshold();
    
    auto belowResult = newOMSystemMn(tag_, group_, mnGroup_, buffer_, t - 1, byteOrder_);
    EXPECT_EQ(belowResult, nullptr);
    
    auto atResult = newOMSystemMn(tag_, group_, mnGroup_, buffer_, t, byteOrder_);
    EXPECT_NE(atResult, nullptr);
}
