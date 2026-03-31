#include <gtest/gtest.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to create a TiffIfdMakernote with no header
static std::unique_ptr<TiffIfdMakernote> createMakernote(
    uint16_t tag = 0x927c,
    IfdId group = IfdId::exifId,
    IfdId mnGroup = IfdId::canonId,
    std::unique_ptr<MnHeader> header = nullptr,
    bool hasNext = false)
{
    return std::make_unique<TiffIfdMakernote>(tag, group, mnGroup, std::move(header), hasNext);
}

class TiffIfdMakernoteTest_246 : public ::testing::Test {
protected:
    void SetUp() override {
        makernote_ = createMakernote();
    }

    std::unique_ptr<TiffIfdMakernote> makernote_;
};

// Test that setImageByteOrder sets the image byte order
TEST_F(TiffIfdMakernoteTest_246, SetImageByteOrder_LittleEndian_246) {
    makernote_->setImageByteOrder(littleEndian);
    // We can't directly verify imageByteOrder_ since it's private,
    // but we ensure no crash and the method is callable
    SUCCEED();
}

TEST_F(TiffIfdMakernoteTest_246, SetImageByteOrder_BigEndian_246) {
    makernote_->setImageByteOrder(bigEndian);
    SUCCEED();
}

TEST_F(TiffIfdMakernoteTest_246, SetImageByteOrder_InvalidByteOrder_246) {
    makernote_->setImageByteOrder(invalidByteOrder);
    SUCCEED();
}

// Test byteOrder() - default byte order when no header is provided
TEST_F(TiffIfdMakernoteTest_246, ByteOrder_Default_246) {
    ByteOrder bo = makernote_->byteOrder();
    // With no header, byte order should be invalidByteOrder
    EXPECT_EQ(bo, invalidByteOrder);
}

// Test setByteOrder and byteOrder interaction
TEST_F(TiffIfdMakernoteTest_246, SetByteOrder_LittleEndian_246) {
    makernote_->setByteOrder(littleEndian);
    // byteOrder() may or may not reflect this depending on header logic
    // but we test the method is callable
    SUCCEED();
}

TEST_F(TiffIfdMakernoteTest_246, SetByteOrder_BigEndian_246) {
    makernote_->setByteOrder(bigEndian);
    SUCCEED();
}

// Test mnOffset with default construction
TEST_F(TiffIfdMakernoteTest_246, MnOffset_Default_246) {
    size_t offset = makernote_->mnOffset();
    EXPECT_EQ(offset, 0u);
}

// Test ifdOffset with default (no header)
TEST_F(TiffIfdMakernoteTest_246, IfdOffset_NoHeader_246) {
    size_t offset = makernote_->ifdOffset();
    EXPECT_EQ(offset, 0u);
}

// Test baseOffset with default (no header)
TEST_F(TiffIfdMakernoteTest_246, BaseOffset_NoHeader_246) {
    size_t offset = makernote_->baseOffset();
    EXPECT_EQ(offset, 0u);
}

// Test sizeHeader with no header
TEST_F(TiffIfdMakernoteTest_246, SizeHeader_NoHeader_246) {
    size_t size = makernote_->sizeHeader();
    EXPECT_EQ(size, 0u);
}

// Test readHeader with no header and null data
TEST_F(TiffIfdMakernoteTest_246, ReadHeader_NoHeader_NullData_246) {
    bool result = makernote_->readHeader(nullptr, 0, littleEndian);
    EXPECT_TRUE(result);
}

// Test readHeader with no header and some data
TEST_F(TiffIfdMakernoteTest_246, ReadHeader_NoHeader_WithData_246) {
    const byte data[] = {0x00, 0x01, 0x02, 0x03};
    bool result = makernote_->readHeader(data, sizeof(data), bigEndian);
    EXPECT_TRUE(result);
}

// Test that copy constructor is deleted (compile-time check, just verify object is usable)
TEST_F(TiffIfdMakernoteTest_246, NonCopyable_246) {
    EXPECT_TRUE(std::is_copy_constructible<TiffIfdMakernote>::value == false);
    EXPECT_TRUE(std::is_copy_assignable<TiffIfdMakernote>::value == false);
}

// Test construction with hasNext=true
TEST_F(TiffIfdMakernoteTest_246, ConstructWithHasNext_246) {
    auto mn = createMakernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, true);
    EXPECT_NE(mn, nullptr);
    EXPECT_EQ(mn->sizeHeader(), 0u);
}

// Test construction with hasNext=false
TEST_F(TiffIfdMakernoteTest_246, ConstructWithHasNextFalse_246) {
    auto mn = createMakernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_NE(mn, nullptr);
}

// Test multiple setImageByteOrder calls
TEST_F(TiffIfdMakernoteTest_246, SetImageByteOrder_MultipleCalls_246) {
    makernote_->setImageByteOrder(littleEndian);
    makernote_->setImageByteOrder(bigEndian);
    makernote_->setImageByteOrder(invalidByteOrder);
    makernote_->setImageByteOrder(littleEndian);
    SUCCEED();
}

// Test setByteOrder with invalidByteOrder
TEST_F(TiffIfdMakernoteTest_246, SetByteOrder_Invalid_246) {
    makernote_->setByteOrder(invalidByteOrder);
    SUCCEED();
}

// Test readHeader with zero-length data and valid pointer
TEST_F(TiffIfdMakernoteTest_246, ReadHeader_ZeroLength_246) {
    const byte data[] = {0x00};
    bool result = makernote_->readHeader(data, 0, littleEndian);
    EXPECT_TRUE(result);
}
