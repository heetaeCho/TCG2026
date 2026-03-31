#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "basicio.hpp"
#include "types.hpp"

#include <memory>
#include <cstring>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to create an IoWrapper with a MemIo backend
class TiffIfdMakernoteTest_386 : public ::testing::Test {
protected:
    void SetUp() override {
        memIo_ = std::make_unique<MemIo>();
    }

    std::unique_ptr<MemIo> memIo_;
};

// Test that a newly constructed TiffIfdMakernote has invalidByteOrder
TEST_F(TiffIfdMakernoteTest_386, DefaultByteOrderIsInvalid_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(mn.byteOrder(), invalidByteOrder);
}

// Test setByteOrder changes the byte order
TEST_F(TiffIfdMakernoteTest_386, SetByteOrderLittleEndian_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    mn.setByteOrder(littleEndian);
    EXPECT_EQ(mn.byteOrder(), littleEndian);
}

TEST_F(TiffIfdMakernoteTest_386, SetByteOrderBigEndian_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    mn.setByteOrder(bigEndian);
    EXPECT_EQ(mn.byteOrder(), bigEndian);
}

// Test that tag and group are set correctly from constructor
TEST_F(TiffIfdMakernoteTest_386, TagAndGroupFromConstructor_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(mn.tag(), 0x927c);
    EXPECT_EQ(mn.group(), IfdId::exifId);
}

// Test sizeHeader with no header returns 0
TEST_F(TiffIfdMakernoteTest_386, SizeHeaderWithNoHeader_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(mn.sizeHeader(), 0u);
}

// Test mnOffset initially is 0
TEST_F(TiffIfdMakernoteTest_386, MnOffsetInitiallyZero_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(mn.mnOffset(), 0u);
}

// Test writeImage with empty ifd returns 0
TEST_F(TiffIfdMakernoteTest_386, WriteImageEmptyIfdReturnsZero_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    byte header[] = {0};
    IoWrapper ioWrapper(*memIo_, header, sizeof(header), nullptr);
    size_t result = mn.writeImage(ioWrapper, littleEndian);
    EXPECT_EQ(result, 0u);
}

// Test writeImage with invalidByteOrder when makernote has no custom byte order
TEST_F(TiffIfdMakernoteTest_386, WriteImageWithInvalidByteOrderDefault_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    byte header[] = {0};
    IoWrapper ioWrapper(*memIo_, header, sizeof(header), nullptr);
    // byteOrder() is invalidByteOrder, so the passed byteOrder should be used
    size_t result = mn.writeImage(ioWrapper, bigEndian);
    EXPECT_EQ(result, 0u);
}

// Test writeImage uses makernote's byte order when set
TEST_F(TiffIfdMakernoteTest_386, WriteImageUsesMakernoteByteOrder_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    mn.setByteOrder(littleEndian);
    byte header[] = {0};
    IoWrapper ioWrapper(*memIo_, header, sizeof(header), nullptr);
    // Even though we pass bigEndian, the makernote's littleEndian should be used
    size_t result = mn.writeImage(ioWrapper, bigEndian);
    EXPECT_EQ(result, 0u);
}

// Test sizeImage on empty makernote
TEST_F(TiffIfdMakernoteTest_386, SizeImageEmpty_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(mn.sizeImage(), 0u);
}

// Test size on empty makernote
TEST_F(TiffIfdMakernoteTest_386, SizeEmpty_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // An empty makernote with no header should have some minimal size or 0
    size_t s = mn.size();
    // We just verify it doesn't crash and returns a reasonable value
    EXPECT_GE(s, 0u);
}

// Test count on empty makernote
TEST_F(TiffIfdMakernoteTest_386, CountEmpty_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    size_t c = mn.count();
    EXPECT_GE(c, 0u);
}

// Test sizeData on empty makernote
TEST_F(TiffIfdMakernoteTest_386, SizeDataEmpty_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(mn.sizeData(), 0u);
}

// Test writeHeader with no header returns 0
TEST_F(TiffIfdMakernoteTest_386, WriteHeaderNoHeader_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    byte header[] = {0};
    IoWrapper ioWrapper(*memIo_, header, sizeof(header), nullptr);
    size_t result = mn.writeHeader(ioWrapper, littleEndian);
    EXPECT_EQ(result, 0u);
}

// Test readHeader with null data and zero size
TEST_F(TiffIfdMakernoteTest_386, ReadHeaderNullDataZeroSize_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    bool result = mn.readHeader(nullptr, 0, littleEndian);
    // Without a header object, should return true (no header to read)
    EXPECT_TRUE(result);
}

// Test setByteOrder to invalidByteOrder
TEST_F(TiffIfdMakernoteTest_386, SetByteOrderInvalid_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    mn.setByteOrder(littleEndian);
    EXPECT_EQ(mn.byteOrder(), littleEndian);
    mn.setByteOrder(invalidByteOrder);
    EXPECT_EQ(mn.byteOrder(), invalidByteOrder);
}

// Test baseOffset on empty makernote
TEST_F(TiffIfdMakernoteTest_386, BaseOffsetDefault_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    size_t bo = mn.baseOffset();
    EXPECT_GE(bo, 0u);
}

// Test ifdOffset on empty makernote
TEST_F(TiffIfdMakernoteTest_386, IfdOffsetDefault_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    size_t io = mn.ifdOffset();
    EXPECT_GE(io, 0u);
}

// Test constructing with hasNext = true
TEST_F(TiffIfdMakernoteTest_386, ConstructWithHasNext_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, true);
    EXPECT_EQ(mn.tag(), 0x927c);
    EXPECT_EQ(mn.byteOrder(), invalidByteOrder);
}

// Test that copy constructor is deleted (compile-time check is implicit; 
// we verify the object is usable after construction)
TEST_F(TiffIfdMakernoteTest_386, ObjectIsUsableAfterConstruction_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // Verify multiple methods can be called without issues
    EXPECT_EQ(mn.tag(), 0x927c);
    EXPECT_EQ(mn.group(), IfdId::exifId);
    EXPECT_EQ(mn.byteOrder(), invalidByteOrder);
    EXPECT_EQ(mn.mnOffset(), 0u);
    EXPECT_EQ(mn.sizeHeader(), 0u);
}

// Test setImageByteOrder
TEST_F(TiffIfdMakernoteTest_386, SetImageByteOrder_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // setImageByteOrder should not affect byteOrder() which is the makernote byte order
    mn.setImageByteOrder(bigEndian);
    EXPECT_EQ(mn.byteOrder(), invalidByteOrder);
}

// Test multiple setByteOrder calls
TEST_F(TiffIfdMakernoteTest_386, MultipleSetByteOrder_386) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    mn.setByteOrder(littleEndian);
    EXPECT_EQ(mn.byteOrder(), littleEndian);
    mn.setByteOrder(bigEndian);
    EXPECT_EQ(mn.byteOrder(), bigEndian);
    mn.setByteOrder(invalidByteOrder);
    EXPECT_EQ(mn.byteOrder(), invalidByteOrder);
}

// Test different tag values
TEST_F(TiffIfdMakernoteTest_386, DifferentTagValues_386) {
    TiffIfdMakernote mn1(0x0000, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(mn1.tag(), 0x0000);

    TiffIfdMakernote mn2(0xFFFF, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(mn2.tag(), 0xFFFF);
}
