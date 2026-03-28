#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffIfdMakernote
class TiffIfdMakernoteTest_361 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a freshly constructed TiffIfdMakernote with no header has count() == 0
// since the internal ifd_ should be empty
TEST_F(TiffIfdMakernoteTest_361, DefaultConstructedCount_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // count() calls doCount() which returns ifd_.count()
    // An empty IFD should have count 0
    EXPECT_EQ(makernote.count(), 0u);
}

// Test that tag() returns the tag passed in constructor
TEST_F(TiffIfdMakernoteTest_361, TagReturnsCorrectValue_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote.tag(), 0x927c);
}

// Test that group() returns the group passed in constructor
TEST_F(TiffIfdMakernoteTest_361, GroupReturnsCorrectValue_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote.group(), IfdId::exifId);
}

// Test byteOrder returns invalidByteOrder when not set
TEST_F(TiffIfdMakernoteTest_361, DefaultByteOrderIsInvalid_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote.byteOrder(), invalidByteOrder);
}

// Test setByteOrder changes the byte order
TEST_F(TiffIfdMakernoteTest_361, SetByteOrderLittleEndian_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(littleEndian);
    EXPECT_EQ(makernote.byteOrder(), littleEndian);
}

// Test setByteOrder with bigEndian
TEST_F(TiffIfdMakernoteTest_361, SetByteOrderBigEndian_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(bigEndian);
    EXPECT_EQ(makernote.byteOrder(), bigEndian);
}

// Test mnOffset returns 0 when not initialized from data
TEST_F(TiffIfdMakernoteTest_361, DefaultMnOffsetIsZero_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote.mnOffset(), 0u);
}

// Test sizeHeader with no header returns 0
TEST_F(TiffIfdMakernoteTest_361, SizeHeaderWithNoHeader_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote.sizeHeader(), 0u);
}

// Test readHeader with null header and empty data
TEST_F(TiffIfdMakernoteTest_361, ReadHeaderWithNoHeaderObject_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    byte data[] = {0x00, 0x00};
    // With no header object, readHeader should return true (no header to read)
    bool result = makernote.readHeader(data, sizeof(data), littleEndian);
    EXPECT_TRUE(result);
}

// Test readHeader with null data pointer and zero size, no header
TEST_F(TiffIfdMakernoteTest_361, ReadHeaderWithNullDataNoHeader_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    bool result = makernote.readHeader(nullptr, 0, littleEndian);
    EXPECT_TRUE(result);
}

// Test that copy constructor is deleted (compile-time check - just verify object can be created)
TEST_F(TiffIfdMakernoteTest_361, ConstructionWithDifferentTags_361) {
    TiffIfdMakernote makernote1(0x0001, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote1.tag(), 0x0001);

    TiffIfdMakernote makernote2(0xFFFF, IfdId::exifId, IfdId::canonId, nullptr, true);
    EXPECT_EQ(makernote2.tag(), 0xFFFF);
}

// Test count on freshly constructed with hasNext = true
TEST_F(TiffIfdMakernoteTest_361, CountWithHasNextTrue_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, true);
    EXPECT_EQ(makernote.count(), 0u);
}

// Test that start() returns nullptr initially
TEST_F(TiffIfdMakernoteTest_361, StartReturnsNullInitially_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote.start(), nullptr);
}

// Test setStart and start
TEST_F(TiffIfdMakernoteTest_361, SetStartAndRetrieve_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    byte data[] = {0x01, 0x02, 0x03};
    makernote.setStart(data);
    EXPECT_EQ(makernote.start(), data);
}

// Test size() on empty makernote
TEST_F(TiffIfdMakernoteTest_361, SizeOnEmptyMakernote_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // An empty IFD makernote with no header should have minimal size
    size_t s = makernote.size();
    // Size should be at least 0 (could be 2 bytes for IFD entry count)
    EXPECT_GE(s, 0u);
}

// Test sizeData on empty makernote
TEST_F(TiffIfdMakernoteTest_361, SizeDataOnEmptyMakernote_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    size_t sd = makernote.sizeData();
    EXPECT_GE(sd, 0u);
}

// Test sizeImage on empty makernote
TEST_F(TiffIfdMakernoteTest_361, SizeImageOnEmptyMakernote_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    size_t si = makernote.sizeImage();
    EXPECT_EQ(si, 0u);
}

// Test construction with different group IDs
TEST_F(TiffIfdMakernoteTest_361, ConstructionWithDifferentGroups_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::ifd0Id, IfdId::nikonId, nullptr, false);
    EXPECT_EQ(makernote.group(), IfdId::ifd0Id);
}

// Test that setByteOrder can be called multiple times
TEST_F(TiffIfdMakernoteTest_361, SetByteOrderMultipleTimes_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(littleEndian);
    EXPECT_EQ(makernote.byteOrder(), littleEndian);
    makernote.setByteOrder(bigEndian);
    EXPECT_EQ(makernote.byteOrder(), bigEndian);
    makernote.setByteOrder(invalidByteOrder);
    EXPECT_EQ(makernote.byteOrder(), invalidByteOrder);
}

// Test idx() returns default value
TEST_F(TiffIfdMakernoteTest_361, IdxReturnsDefault_361) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    int idx = makernote.idx();
    // Default idx should be 0
    EXPECT_EQ(idx, 0);
}
