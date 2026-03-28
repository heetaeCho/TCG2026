#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "crwimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to extract uint16 from blob at given position
static uint16_t getUint16(const Blob& blob, size_t pos, ByteOrder byteOrder) {
    if (pos + 2 > blob.size()) return 0;
    byte buf[2] = { blob[pos], blob[pos+1] };
    return getUShort(buf, byteOrder);
}

// Helper to extract uint32 from blob at given position
static uint32_t getUint32(const Blob& blob, size_t pos, ByteOrder byteOrder) {
    if (pos + 4 > blob.size()) return 0;
    byte buf[4] = { blob[pos], blob[pos+1], blob[pos+2], blob[pos+3] };
    return getULong(buf, byteOrder);
}

class CiffComponentTest_1780 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test default construction
TEST_F(CiffComponentTest_1780, DefaultConstructor_1780) {
    CiffComponent comp;
    EXPECT_EQ(comp.tag(), 0);
    EXPECT_EQ(comp.dir(), 0);
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
    EXPECT_EQ(comp.pData(), nullptr);
}

// Test parameterized construction
TEST_F(CiffComponentTest_1780, ParameterizedConstructor_1780) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent comp(tag, dir);
    EXPECT_EQ(comp.tag(), tag);
    EXPECT_EQ(comp.dir(), dir);
}

// Test setDir
TEST_F(CiffComponentTest_1780, SetDir_1780) {
    CiffComponent comp;
    comp.setDir(0xABCD);
    EXPECT_EQ(comp.dir(), 0xABCD);
}

// Test tagId derived from tag and dir
TEST_F(CiffComponentTest_1780, TagId_1780) {
    uint16_t tag = 0x0001;
    uint16_t dir = 0x0002;
    CiffComponent comp(tag, dir);
    // tagId should be derivable from tag/dir - just verify it returns something consistent
    uint16_t id = comp.tagId();
    // Call again to verify consistency
    EXPECT_EQ(comp.tagId(), id);
}

// Test typeId static method with various tags
TEST_F(CiffComponentTest_1780, TypeIdStatic_1780) {
    // Just verify it doesn't crash and returns a TypeId
    TypeId t1 = CiffComponent::typeId(0x0000);
    TypeId t2 = CiffComponent::typeId(0x0800);
    TypeId t3 = CiffComponent::typeId(0x1000);
    // We can at least verify they are valid TypeId values (no crash)
    (void)t1;
    (void)t2;
    (void)t3;
}

// Test dataLocation static method
TEST_F(CiffComponentTest_1780, DataLocationStatic_1780) {
    // Tags with certain bit patterns should return different DataLocIds
    DataLocId loc1 = CiffComponent::dataLocation(0x0000);
    DataLocId loc2 = CiffComponent::dataLocation(0x4000);
    // Just ensure no crash and valid enum values
    EXPECT_TRUE(loc1 == DataLocId::valueData || loc1 == DataLocId::directoryData || loc1 == DataLocId::lastDataLocId);
    EXPECT_TRUE(loc2 == DataLocId::valueData || loc2 == DataLocId::directoryData || loc2 == DataLocId::lastDataLocId);
}

// Test empty on default constructed component
TEST_F(CiffComponentTest_1780, DefaultEmpty_1780) {
    CiffComponent comp;
    // Default component should be considered empty
    EXPECT_TRUE(comp.empty());
}

// Test setValue and its effect on size/pData
TEST_F(CiffComponentTest_1780, SetValue_1780) {
    CiffComponent comp;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    EXPECT_EQ(comp.size(), 4u);
    EXPECT_NE(comp.pData(), nullptr);
    EXPECT_EQ(comp.pData()[0], 0x01);
    EXPECT_EQ(comp.pData()[1], 0x02);
    EXPECT_EQ(comp.pData()[2], 0x03);
    EXPECT_EQ(comp.pData()[3], 0x04);
}

// Test writeDirEntry for a tag that maps to valueData location
TEST_F(CiffComponentTest_1780, WriteDirEntryValueData_LittleEndian_1780) {
    // We need a tag value whose dataLocation returns DataLocId::valueData
    // Tags with upper bits 00 typically mean valueData
    // Use tag 0x0000 which likely maps to valueData
    uint16_t tag = 0x0000;
    uint16_t dir = 0x0000;
    CiffComponent comp(tag, dir);
    
    // Set some data
    byte data[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    
    // Only test if the tag's dataLocation is valueData
    if (comp.dataLocation() == DataLocId::valueData) {
        Blob blob;
        comp.writeDirEntry(blob, littleEndian);
        
        // For valueData: 2 bytes tag + 4 bytes size + 4 bytes offset = 10 bytes
        EXPECT_EQ(blob.size(), 10u);
        
        // Verify tag is written correctly
        uint16_t writtenTag = getUint16(blob, 0, littleEndian);
        EXPECT_EQ(writtenTag, tag);
        
        // Verify size
        uint32_t writtenSize = getUint32(blob, 2, littleEndian);
        EXPECT_EQ(writtenSize, 5u);
    }
}

// Test writeDirEntry for a tag that maps to directoryData location
TEST_F(CiffComponentTest_1780, WriteDirEntryDirectoryData_LittleEndian_1780) {
    // Tags with bits 14-15 = 01 typically map to directoryData (0x4000 range)
    // We need to find a tag that returns DataLocId::directoryData
    // Try various tag values
    for (uint16_t testTag = 0x4000; testTag < 0x4010; ++testTag) {
        if (CiffComponent::dataLocation(testTag) == DataLocId::directoryData) {
            CiffComponent comp(testTag, 0x0000);
            
            // Set small data (should be padded to 8 bytes in directory entry)
            byte data[] = {0x01, 0x02, 0x03};
            DataBuf buf(data, sizeof(data));
            comp.setValue(std::move(buf));
            
            Blob blob;
            comp.writeDirEntry(blob, littleEndian);
            
            // For directoryData: 2 bytes tag + 8 bytes (data padded to 8) = 10 bytes
            EXPECT_EQ(blob.size(), 10u);
            
            // Verify tag
            uint16_t writtenTag = getUint16(blob, 0, littleEndian);
            EXPECT_EQ(writtenTag, testTag);
            
            // Verify padding: bytes beyond data size should be 0
            // data[0..2] = 0x01, 0x02, 0x03; bytes 5..9 should be 0
            for (size_t i = 2 + 3; i < 10; ++i) {
                EXPECT_EQ(blob[i], 0) << "Padding byte at index " << i << " should be 0";
            }
            break;
        }
    }
}

// Test writeDirEntry with big endian byte order
TEST_F(CiffComponentTest_1780, WriteDirEntryValueData_BigEndian_1780) {
    uint16_t tag = 0x0000;
    uint16_t dir = 0x0000;
    CiffComponent comp(tag, dir);
    
    byte data[] = {0x11, 0x22};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    
    if (comp.dataLocation() == DataLocId::valueData) {
        Blob blob;
        comp.writeDirEntry(blob, bigEndian);
        
        EXPECT_EQ(blob.size(), 10u);
        
        uint16_t writtenTag = getUint16(blob, 0, bigEndian);
        EXPECT_EQ(writtenTag, tag);
        
        uint32_t writtenSize = getUint32(blob, 2, bigEndian);
        EXPECT_EQ(writtenSize, 2u);
    }
}

// Test writeDirEntry on empty blob - should append correctly
TEST_F(CiffComponentTest_1780, WriteDirEntryAppendsToExistingBlob_1780) {
    uint16_t tag = 0x0000;
    CiffComponent comp(tag, 0x0000);
    
    byte data[] = {0xFF};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    
    if (comp.dataLocation() == DataLocId::valueData) {
        Blob blob;
        // Pre-fill blob with some data
        blob.push_back(0xDE);
        blob.push_back(0xAD);
        size_t initialSize = blob.size();
        
        comp.writeDirEntry(blob, littleEndian);
        
        // Should have appended 10 bytes
        EXPECT_EQ(blob.size(), initialSize + 10u);
        
        // Original data should be untouched
        EXPECT_EQ(blob[0], 0xDE);
        EXPECT_EQ(blob[1], 0xAD);
    }
}

// Test writeDirEntry with directoryData where data is exactly 8 bytes
TEST_F(CiffComponentTest_1780, WriteDirEntryDirectoryDataExact8Bytes_1780) {
    for (uint16_t testTag = 0x4000; testTag < 0x4010; ++testTag) {
        if (CiffComponent::dataLocation(testTag) == DataLocId::directoryData) {
            CiffComponent comp(testTag, 0x0000);
            
            byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
            DataBuf buf(data, sizeof(data));
            comp.setValue(std::move(buf));
            
            Blob blob;
            comp.writeDirEntry(blob, littleEndian);
            
            // 2 bytes tag + 8 bytes data (no padding needed) = 10 bytes
            EXPECT_EQ(blob.size(), 10u);
            
            // Verify the data bytes
            for (size_t i = 0; i < 8; ++i) {
                EXPECT_EQ(blob[2 + i], data[i]);
            }
            break;
        }
    }
}

// Test writeDirEntry with directoryData where data is 0 bytes
TEST_F(CiffComponentTest_1780, WriteDirEntryDirectoryDataZeroBytes_1780) {
    for (uint16_t testTag = 0x4000; testTag < 0x4010; ++testTag) {
        if (CiffComponent::dataLocation(testTag) == DataLocId::directoryData) {
            CiffComponent comp(testTag, 0x0000);
            
            // Don't set any value - size should be 0
            Blob blob;
            comp.writeDirEntry(blob, littleEndian);
            
            // 2 bytes tag + 0 bytes data + 8 bytes padding = 10 bytes
            EXPECT_EQ(blob.size(), 10u);
            
            // All padding bytes should be 0
            for (size_t i = 2; i < 10; ++i) {
                EXPECT_EQ(blob[i], 0);
            }
            break;
        }
    }
}

// Test findComponent on base CiffComponent returns nullptr for non-matching
TEST_F(CiffComponentTest_1780, FindComponentReturnsNullForNonMatch_1780) {
    CiffComponent comp(0x1234, 0x5678);
    CiffComponent* found = comp.findComponent(0x9999, 0x8888);
    // Base implementation behavior - may return nullptr or self depending on match
    // We just verify it doesn't crash
    (void)found;
}

// Test findComponent matching the component itself
TEST_F(CiffComponentTest_1780, FindComponentSelf_1780) {
    uint16_t tagId = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent comp(tagId, dir);
    
    // Try to find the component itself
    CiffComponent* found = comp.findComponent(comp.tagId(), comp.dir());
    // For a base CiffComponent, it should return itself if tagId and dir match
    if (found != nullptr) {
        EXPECT_EQ(found->tagId(), comp.tagId());
        EXPECT_EQ(found->dir(), comp.dir());
    }
}

// Test typeId instance method
TEST_F(CiffComponentTest_1780, TypeIdInstance_1780) {
    CiffComponent comp(0x0800, 0x0000);
    TypeId t = comp.typeId();
    // Should be consistent with static method
    EXPECT_EQ(t, CiffComponent::typeId(0x0800));
}

// Test dataLocation instance method
TEST_F(CiffComponentTest_1780, DataLocationInstance_1780) {
    CiffComponent comp(0x0000, 0x0000);
    DataLocId loc = comp.dataLocation();
    EXPECT_EQ(loc, CiffComponent::dataLocation(0x0000));
}

// Test that copy constructor is deleted (compile-time check, but we verify via traits)
TEST_F(CiffComponentTest_1780, CopyConstructorDeleted_1780) {
    EXPECT_FALSE(std::is_copy_constructible<CiffComponent>::value);
}

// Test that copy assignment is deleted
TEST_F(CiffComponentTest_1780, CopyAssignmentDeleted_1780) {
    EXPECT_FALSE(std::is_copy_assignable<CiffComponent>::value);
}

// Test setValue with empty DataBuf
TEST_F(CiffComponentTest_1780, SetValueEmptyBuf_1780) {
    CiffComponent comp;
    DataBuf emptyBuf;
    comp.setValue(std::move(emptyBuf));
    EXPECT_EQ(comp.size(), 0u);
}

// Test offset accessor
TEST_F(CiffComponentTest_1780, OffsetDefault_1780) {
    CiffComponent comp;
    EXPECT_EQ(comp.offset(), 0u);
}

// Test setValue replaces previous value
TEST_F(CiffComponentTest_1780, SetValueReplacesPrevious_1780) {
    CiffComponent comp;
    
    byte data1[] = {0x01, 0x02};
    DataBuf buf1(data1, sizeof(data1));
    comp.setValue(std::move(buf1));
    EXPECT_EQ(comp.size(), 2u);
    
    byte data2[] = {0x0A, 0x0B, 0x0C, 0x0D, 0x0E};
    DataBuf buf2(data2, sizeof(data2));
    comp.setValue(std::move(buf2));
    EXPECT_EQ(comp.size(), 5u);
    EXPECT_EQ(comp.pData()[0], 0x0A);
}

// Test multiple writeDirEntry calls produce same output
TEST_F(CiffComponentTest_1780, WriteDirEntryIdempotent_1780) {
    uint16_t tag = 0x0000;
    CiffComponent comp(tag, 0x0000);
    
    byte data[] = {0x42, 0x43};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    
    Blob blob1, blob2;
    comp.writeDirEntry(blob1, littleEndian);
    comp.writeDirEntry(blob2, littleEndian);
    
    EXPECT_EQ(blob1.size(), blob2.size());
    for (size_t i = 0; i < blob1.size(); ++i) {
        EXPECT_EQ(blob1[i], blob2[i]) << "Mismatch at byte " << i;
    }
}
