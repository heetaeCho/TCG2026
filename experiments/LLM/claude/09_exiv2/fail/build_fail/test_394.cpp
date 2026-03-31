#include <gtest/gtest.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffIfdMakernoteTest_394 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with nullptr header and basic properties
TEST_F(TiffIfdMakernoteTest_394, ConstructWithNullHeader_394) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    EXPECT_EQ(makernote.tag(), 0x927c);
    EXPECT_EQ(makernote.group(), IfdId::exifId);
}

// Test byteOrder returns invalidByteOrder initially
TEST_F(TiffIfdMakernoteTest_394, InitialByteOrderIsInvalid_394) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    EXPECT_EQ(makernote.byteOrder(), invalidByteOrder);
}

// Test setByteOrder changes byte order
TEST_F(TiffIfdMakernoteTest_394, SetByteOrderChangesOrder_394) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    makernote.setByteOrder(littleEndian);
    EXPECT_EQ(makernote.byteOrder(), littleEndian);
    
    makernote.setByteOrder(bigEndian);
    EXPECT_EQ(makernote.byteOrder(), bigEndian);
}

// Test mnOffset returns 0 initially
TEST_F(TiffIfdMakernoteTest_394, InitialMnOffsetIsZero_394) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    EXPECT_EQ(makernote.mnOffset(), 0u);
}

// Test sizeHeader with null header returns 0
TEST_F(TiffIfdMakernoteTest_394, SizeHeaderWithNullHeaderReturnsZero_394) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    EXPECT_EQ(makernote.sizeHeader(), 0u);
}

// Test size() (doSize) with null header - should be sizeHeader() + ifd_.size()
TEST_F(TiffIfdMakernoteTest_394, SizeWithNullHeaderAndEmptyIfd_394) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    // With null header and empty IFD, size should be small (header size 0 + empty ifd size)
    size_t sz = makernote.size();
    // The IFD has at least a 2-byte count + 4-byte next-IFD-offset = 6 bytes when empty but present
    // But we can only verify it's >= sizeHeader()
    EXPECT_GE(sz, makernote.sizeHeader());
}

// Test readHeader with null header
TEST_F(TiffIfdMakernoteTest_394, ReadHeaderWithNullHeader_394) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    byte data[] = {0x00, 0x01, 0x02, 0x03};
    // With null header, readHeader should return true (no header to read)
    bool result = makernote.readHeader(data, sizeof(data), littleEndian);
    EXPECT_TRUE(result);
}

// Test readHeader with null data and null header
TEST_F(TiffIfdMakernoteTest_394, ReadHeaderWithNullDataAndNullHeader_394) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    bool result = makernote.readHeader(nullptr, 0, littleEndian);
    EXPECT_TRUE(result);
}

// Test ifdOffset with null header
TEST_F(TiffIfdMakernoteTest_394, IfdOffsetWithNullHeader_394) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    // With null header, ifdOffset should be 0
    EXPECT_EQ(makernote.ifdOffset(), 0u);
}

// Test baseOffset with null header
TEST_F(TiffIfdMakernoteTest_394, BaseOffsetWithNullHeader_394) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    // With null header, baseOffset should be 0
    EXPECT_EQ(makernote.baseOffset(), 0u);
}

// Test construction with hasNext = true
TEST_F(TiffIfdMakernoteTest_394, ConstructWithHasNextTrue_394) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, true);
    
    EXPECT_EQ(makernote.tag(), 0x927c);
    EXPECT_EQ(makernote.group(), IfdId::exifId);
}

// Test setImageByteOrder
TEST_F(TiffIfdMakernoteTest_394, SetImageByteOrder_394) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    // setImageByteOrder should not affect byteOrder() which is the makernote byte order
    makernote.setImageByteOrder(bigEndian);
    // byteOrder() should still be invalidByteOrder since setByteOrder wasn't called
    EXPECT_EQ(makernote.byteOrder(), invalidByteOrder);
}

// Test that setByteOrder to invalidByteOrder works
TEST_F(TiffIfdMakernoteTest_394, SetByteOrderToInvalid_394) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    makernote.setByteOrder(littleEndian);
    EXPECT_EQ(makernote.byteOrder(), littleEndian);
    
    makernote.setByteOrder(invalidByteOrder);
    EXPECT_EQ(makernote.byteOrder(), invalidByteOrder);
}

// Test different tag values
TEST_F(TiffIfdMakernoteTest_394, DifferentTagValues_394) {
    TiffIfdMakernote makernote1(0x0001, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote1.tag(), 0x0001);
    
    TiffIfdMakernote makernote2(0xFFFF, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote2.tag(), 0xFFFF);
    
    TiffIfdMakernote makernote3(0x0000, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote3.tag(), 0x0000);
}

// Test different group values
TEST_F(TiffIfdMakernoteTest_394, DifferentGroupValues_394) {
    TiffIfdMakernote makernote1(0x927c, IfdId::ifd0Id, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote1.group(), IfdId::ifd0Id);
    
    TiffIfdMakernote makernote2(0x927c, IfdId::exifId, IfdId::nikonId, nullptr, false);
    EXPECT_EQ(makernote2.group(), IfdId::exifId);
}

// Test start() returns nullptr initially
TEST_F(TiffIfdMakernoteTest_394, StartIsNullInitially_394) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    EXPECT_EQ(makernote.start(), nullptr);
}

// Test setStart
TEST_F(TiffIfdMakernoteTest_394, SetStartUpdatesPointer_394) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    byte data[] = {0x01, 0x02, 0x03};
    makernote.setStart(data);
    EXPECT_EQ(makernote.start(), data);
}

// Test count with empty makernote
TEST_F(TiffIfdMakernoteTest_394, CountWithEmptyMakernote_394) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    size_t cnt = makernote.count();
    // Empty makernote should have count of 0
    EXPECT_EQ(cnt, 0u);
}

// Test copy constructor is deleted (compile-time check - we just verify the object is non-copyable conceptually)
// This is a compile-time constraint, not a runtime test. We verify the class works correctly as move-only.
TEST_F(TiffIfdMakernoteTest_394, NonCopyable_394) {
    // Verify TiffIfdMakernote is not copy constructible
    EXPECT_FALSE(std::is_copy_constructible<TiffIfdMakernote>::value);
    EXPECT_FALSE(std::is_copy_assignable<TiffIfdMakernote>::value);
}
