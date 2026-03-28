#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>
#include <sstream>
#include <vector>

#include "crwimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for CiffComponent tests
class CiffComponentTest_1772 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor initializes properly
TEST_F(CiffComponentTest_1772, DefaultConstructor_1772) {
    CiffComponent comp;
    EXPECT_EQ(comp.tag(), 0);
    EXPECT_EQ(comp.dir(), 0);
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
    EXPECT_EQ(comp.pData(), nullptr);
}

// Test parameterized constructor sets tag and dir
TEST_F(CiffComponentTest_1772, ParameterizedConstructor_1772) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent comp(tag, dir);
    EXPECT_EQ(comp.tag(), tag);
    EXPECT_EQ(comp.dir(), dir);
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
    EXPECT_EQ(comp.pData(), nullptr);
}

// Test setDir changes dir value
TEST_F(CiffComponentTest_1772, SetDir_1772) {
    CiffComponent comp;
    comp.setDir(0xABCD);
    EXPECT_EQ(comp.dir(), 0xABCD);
}

// Test empty returns true for default constructed component
TEST_F(CiffComponentTest_1772, EmptyOnDefault_1772) {
    CiffComponent comp;
    EXPECT_TRUE(comp.empty());
}

// Test tagId extracts tag ID portion
TEST_F(CiffComponentTest_1772, TagId_1772) {
    // tagId typically returns tag & 0x3fff
    uint16_t tag = 0x300A;
    uint16_t dir = 0x0000;
    CiffComponent comp(tag, dir);
    uint16_t tagId = comp.tagId();
    // tagId should mask out the type bits from the tag
    EXPECT_EQ(tagId, static_cast<uint16_t>(tag & 0x3fff));
}

// Test typeId returns type from tag
TEST_F(CiffComponentTest_1772, TypeIdFromTag_1772) {
    // typeId is a static function based on tag
    // The type is encoded in the upper 2 bits of the tag (bits 14-15)
    // We just test it doesn't crash and returns a valid TypeId
    TypeId t = CiffComponent::typeId(0x0000);
    // Just verify it returns something without crashing
    (void)t;
}

// Test dataLocation static method
TEST_F(CiffComponentTest_1772, DataLocationStatic_1772) {
    DataLocId loc = CiffComponent::dataLocation(0x0000);
    (void)loc; // just ensure no crash
}

// Test typeId instance method
TEST_F(CiffComponentTest_1772, TypeIdInstance_1772) {
    uint16_t tag = 0x0800; // some tag with type bits set
    CiffComponent comp(tag, 0);
    TypeId t = comp.typeId();
    (void)t;
}

// Test dataLocation instance method
TEST_F(CiffComponentTest_1772, DataLocationInstance_1772) {
    CiffComponent comp(0x0000, 0);
    DataLocId loc = comp.dataLocation();
    (void)loc;
}

// Test setValue with a DataBuf
TEST_F(CiffComponentTest_1772, SetValue_1772) {
    CiffComponent comp(0x0001, 0x0000);
    
    // Create a DataBuf with some data
    byte testData[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(testData, 4);
    
    comp.setValue(std::move(buf));
    
    // After setValue, pData should point to the stored data
    EXPECT_NE(comp.pData(), nullptr);
    EXPECT_EQ(comp.size(), 4u);
}

// Test findComponent on a leaf component returns itself if matching, nullptr otherwise
TEST_F(CiffComponentTest_1772, FindComponentNoMatch_1772) {
    CiffComponent comp(0x1234, 0x5678);
    // findComponent on a leaf with non-matching tag/dir
    CiffComponent* found = comp.findComponent(0x0000, 0x0000);
    // A base CiffComponent's doFindComponent returns nullptr (or this if matching)
    // We test for the non-matching case
    EXPECT_EQ(found, nullptr);
}

// Test print doesn't crash
TEST_F(CiffComponentTest_1772, PrintNoData_1772) {
    CiffComponent comp(0x0001, 0x0000);
    std::ostringstream os;
    // Should not crash even with no data
    EXPECT_NO_THROW(comp.print(os, littleEndian, ""));
}

// Test read with nullptr and zero size should throw or handle gracefully
TEST_F(CiffComponentTest_1772, ReadNullData_1772) {
    CiffComponent comp;
    // Reading with nullptr and size 0 and start 0 
    // This may throw due to invalid access
    EXPECT_ANY_THROW(comp.read(nullptr, 0, 0, littleEndian));
}

// Test read with valid minimal data
TEST_F(CiffComponentTest_1772, ReadWithValidData_1772) {
    CiffComponent comp;
    // CRW entry in data: need at minimum 10 bytes for a directory entry
    // A CIFF value record has tag(2) + size(4) + offset(4) = 10 bytes
    // The start parameter points into the data
    // For a simple value entry, we need proper structure
    // This tests that read doesn't crash with some minimal valid-looking data
    std::vector<byte> data(26, 0);
    // Set up a minimal structure - this is exploratory
    // The read function reads from pData + start, expecting a specific format
    // With all zeros, it might still parse but produce a zero-sized component
    // We just check it doesn't crash or handles error appropriately
    try {
        comp.read(data.data(), data.size(), 0, littleEndian);
    } catch (...) {
        // It's acceptable if it throws due to invalid CRW structure
    }
}

// Test write with empty component
TEST_F(CiffComponentTest_1772, WriteEmpty_1772) {
    CiffComponent comp(0x0001, 0x0000);
    Blob blob;
    // Write should handle empty component
    size_t result = comp.write(blob, littleEndian, 0);
    (void)result;
}

// Test writeValueData with empty component
TEST_F(CiffComponentTest_1772, WriteValueDataEmpty_1772) {
    CiffComponent comp(0x0001, 0x0000);
    Blob blob;
    size_t result = comp.writeValueData(blob, 0);
    (void)result;
}

// Test writeDirEntry
TEST_F(CiffComponentTest_1772, WriteDirEntry_1772) {
    CiffComponent comp(0x0001, 0x0000);
    Blob blob;
    EXPECT_NO_THROW(comp.writeDirEntry(blob, littleEndian));
    // A directory entry should write 10 bytes (tag + size + offset)
    EXPECT_EQ(blob.size(), 10u);
}

// Test that copy constructor is deleted
TEST_F(CiffComponentTest_1772, CopyConstructorDeleted_1772) {
    EXPECT_FALSE(std::is_copy_constructible<CiffComponent>::value);
}

// Test that copy assignment is deleted
TEST_F(CiffComponentTest_1772, CopyAssignmentDeleted_1772) {
    EXPECT_FALSE(std::is_copy_assignable<CiffComponent>::value);
}

// Test setValue with empty DataBuf
TEST_F(CiffComponentTest_1772, SetValueEmptyBuf_1772) {
    CiffComponent comp(0x0001, 0x0000);
    DataBuf emptyBuf;
    comp.setValue(std::move(emptyBuf));
    EXPECT_EQ(comp.size(), 0u);
}

// Test multiple setDir calls
TEST_F(CiffComponentTest_1772, SetDirMultiple_1772) {
    CiffComponent comp;
    comp.setDir(0x0001);
    EXPECT_EQ(comp.dir(), 0x0001);
    comp.setDir(0x0002);
    EXPECT_EQ(comp.dir(), 0x0002);
    comp.setDir(0xFFFF);
    EXPECT_EQ(comp.dir(), 0xFFFF);
}

// Test tag returns correct value from constructor
TEST_F(CiffComponentTest_1772, TagAccessor_1772) {
    CiffComponent comp(0xFFFF, 0x0000);
    EXPECT_EQ(comp.tag(), 0xFFFF);
}

// Test with big endian byte order
TEST_F(CiffComponentTest_1772, PrintBigEndian_1772) {
    CiffComponent comp(0x0001, 0x0000);
    std::ostringstream os;
    EXPECT_NO_THROW(comp.print(os, bigEndian, "PREFIX:"));
}

// Test typeId static with various tags
TEST_F(CiffComponentTest_1772, TypeIdVariousTags_1772) {
    // Type bits are in bits 13-15 of the tag
    // 0x0000 = type 0 (unsignedByte or similar)
    // 0x2000 = type 1
    // 0x4000 = type 2
    // etc.
    TypeId t0 = CiffComponent::typeId(0x0000);
    TypeId t1 = CiffComponent::typeId(0x2000);
    TypeId t2 = CiffComponent::typeId(0x4000);
    TypeId t3 = CiffComponent::typeId(0x8000);
    
    // Just ensure they don't all return the same thing (type bits matter)
    // At least some should differ
    bool allSame = (t0 == t1) && (t1 == t2) && (t2 == t3);
    // Not necessarily all different but the function should differentiate some
    (void)allSame;
}

// Test setValue then check pData points to valid data
TEST_F(CiffComponentTest_1772, SetValueCheckData_1772) {
    CiffComponent comp(0x0001, 0x0000);
    byte testData[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE};
    DataBuf buf(testData, 6);
    comp.setValue(std::move(buf));
    
    ASSERT_NE(comp.pData(), nullptr);
    EXPECT_EQ(comp.size(), 6u);
    EXPECT_EQ(comp.pData()[0], 0xDE);
    EXPECT_EQ(comp.pData()[1], 0xAD);
    EXPECT_EQ(comp.pData()[2], 0xBE);
    EXPECT_EQ(comp.pData()[3], 0xEF);
    EXPECT_EQ(comp.pData()[4], 0xCA);
    EXPECT_EQ(comp.pData()[5], 0xFE);
}

// Test offset returns 0 for default component
TEST_F(CiffComponentTest_1772, OffsetDefault_1772) {
    CiffComponent comp;
    EXPECT_EQ(comp.offset(), 0u);
}

// Test size returns 0 for default component
TEST_F(CiffComponentTest_1772, SizeDefault_1772) {
    CiffComponent comp;
    EXPECT_EQ(comp.size(), 0u);
}
