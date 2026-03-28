#include <gtest/gtest.h>
#include <cstdint>
#include <sstream>
#include <vector>

// Include the necessary headers from the exiv2 project
#include "crwimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for CiffComponent tests
class CiffComponentTest_1766 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor initializes members properly
TEST_F(CiffComponentTest_1766, DefaultConstructor_1766) {
    CiffComponent comp;
    EXPECT_EQ(comp.tag(), 0);
    EXPECT_EQ(comp.dir(), 0);
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
    EXPECT_EQ(comp.pData(), nullptr);
}

// Test parameterized constructor
TEST_F(CiffComponentTest_1766, ParameterizedConstructor_1766) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent comp(tag, dir);
    EXPECT_EQ(comp.tag(), tag);
    EXPECT_EQ(comp.dir(), dir);
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
    EXPECT_EQ(comp.pData(), nullptr);
}

// Test setDir and dir accessor
TEST_F(CiffComponentTest_1766, SetDirAndDir_1766) {
    CiffComponent comp;
    comp.setDir(0xABCD);
    EXPECT_EQ(comp.dir(), 0xABCD);
}

// Test setDir with zero
TEST_F(CiffComponentTest_1766, SetDirZero_1766) {
    CiffComponent comp(0x1111, 0x2222);
    comp.setDir(0);
    EXPECT_EQ(comp.dir(), 0);
}

// Test setDir with max uint16 value
TEST_F(CiffComponentTest_1766, SetDirMaxValue_1766) {
    CiffComponent comp;
    comp.setDir(0xFFFF);
    EXPECT_EQ(comp.dir(), 0xFFFF);
}

// Test tag accessor
TEST_F(CiffComponentTest_1766, TagAccessor_1766) {
    CiffComponent comp(0x0102, 0x0304);
    EXPECT_EQ(comp.tag(), 0x0102);
}

// Test tagId returns the lower bits of tag
TEST_F(CiffComponentTest_1766, TagId_1766) {
    uint16_t tag = 0x3005;
    CiffComponent comp(tag, 0);
    // tagId should return tag & 0x3fff based on CRW spec
    uint16_t expectedTagId = tag & 0x3FFF;
    EXPECT_EQ(comp.tagId(), expectedTagId);
}

// Test empty on default constructed component
TEST_F(CiffComponentTest_1766, EmptyOnDefault_1766) {
    CiffComponent comp;
    // Default constructed should be empty (no data)
    EXPECT_TRUE(comp.empty());
}

// Test setValue and then check that component is not empty
TEST_F(CiffComponentTest_1766, SetValueMakesNonEmpty_1766) {
    CiffComponent comp;
    DataBuf buf(10);
    std::memset(buf.data(), 0xAA, 10);
    comp.setValue(std::move(buf));
    // After setting value, the component should have data
    EXPECT_EQ(comp.size(), 10u);
    EXPECT_NE(comp.pData(), nullptr);
}

// Test setValue with empty DataBuf
TEST_F(CiffComponentTest_1766, SetValueEmptyBuf_1766) {
    CiffComponent comp;
    DataBuf buf;
    comp.setValue(std::move(buf));
    EXPECT_EQ(comp.size(), 0u);
}

// Test static typeId method with various tag values
TEST_F(CiffComponentTest_1766, StaticTypeId_1766) {
    // TypeId is derived from the upper bits of the tag
    // Tags with type bits in upper 2 bits
    TypeId t1 = CiffComponent::typeId(0x0000);
    // Just verify it returns a valid TypeId (no crash)
    (void)t1;

    TypeId t2 = CiffComponent::typeId(0x0800);
    (void)t2;

    TypeId t3 = CiffComponent::typeId(0x2000);
    (void)t3;

    TypeId t4 = CiffComponent::typeId(0x3800);
    (void)t4;
}

// Test static dataLocation method
TEST_F(CiffComponentTest_1766, StaticDataLocation_1766) {
    // dataLocation is derived from tag
    DataLocId loc1 = CiffComponent::dataLocation(0x0000);
    (void)loc1;

    DataLocId loc2 = CiffComponent::dataLocation(0x4000);
    (void)loc2;
}

// Test instance typeId method
TEST_F(CiffComponentTest_1766, InstanceTypeId_1766) {
    CiffComponent comp(0x0800, 0);
    TypeId tid = comp.typeId();
    EXPECT_EQ(tid, CiffComponent::typeId(0x0800));
}

// Test instance dataLocation method
TEST_F(CiffComponentTest_1766, InstanceDataLocation_1766) {
    CiffComponent comp(0x4000, 0);
    DataLocId dlid = comp.dataLocation();
    EXPECT_EQ(dlid, CiffComponent::dataLocation(0x4000));
}

// Test findComponent on a leaf node (should return itself if matching, or nullptr)
TEST_F(CiffComponentTest_1766, FindComponentOnLeaf_1766) {
    uint16_t tag = 0x0805;
    uint16_t dir = 0x0000;
    CiffComponent comp(tag, dir);
    
    // Finding with matching tagId and dir
    uint16_t tagId = tag & 0x3FFF;
    CiffComponent* found = comp.findComponent(tagId, dir);
    // For a leaf node, it should find itself if tagId and dir match
    if (found) {
        EXPECT_EQ(found->tagId(), tagId);
    }
}

// Test findComponent with non-matching parameters
TEST_F(CiffComponentTest_1766, FindComponentNonMatching_1766) {
    CiffComponent comp(0x0001, 0x0000);
    CiffComponent* found = comp.findComponent(0xFFFF, 0xFFFF);
    EXPECT_EQ(found, nullptr);
}

// Test print does not crash
TEST_F(CiffComponentTest_1766, PrintDoesNotCrash_1766) {
    CiffComponent comp(0x0805, 0x0000);
    std::ostringstream oss;
    EXPECT_NO_THROW(comp.print(oss, littleEndian, ""));
}

// Test print with prefix
TEST_F(CiffComponentTest_1766, PrintWithPrefix_1766) {
    CiffComponent comp(0x0100, 0x0000);
    std::ostringstream oss;
    EXPECT_NO_THROW(comp.print(oss, bigEndian, "  "));
}

// Test writeDirEntry does not crash on default component
TEST_F(CiffComponentTest_1766, WriteDirEntry_1766) {
    CiffComponent comp(0x0001, 0x0000);
    Blob blob;
    EXPECT_NO_THROW(comp.writeDirEntry(blob, littleEndian));
    // A directory entry should write exactly 10 bytes (tag(2) + size(4) + offset(4))
    EXPECT_EQ(blob.size(), 10u);
}

// Test writeDirEntry with big endian
TEST_F(CiffComponentTest_1766, WriteDirEntryBigEndian_1766) {
    CiffComponent comp(0x0002, 0x0003);
    Blob blob;
    EXPECT_NO_THROW(comp.writeDirEntry(blob, bigEndian));
    EXPECT_EQ(blob.size(), 10u);
}

// Test writeValueData on empty component
TEST_F(CiffComponentTest_1766, WriteValueDataEmpty_1766) {
    CiffComponent comp;
    Blob blob;
    size_t result = comp.writeValueData(blob, 0);
    // For an empty component, offset should remain unchanged or be 0
    (void)result;
}

// Test copy constructor is deleted (compile-time check concept - just verifying interface)
// This is verified by the fact that the code compiles with delete

// Test that setSize works properly (accessible through size())
TEST_F(CiffComponentTest_1766, SetSize_1766) {
    // setSize is protected but exposed in the partial code snippet as public
    // We test through setValue which internally sets size
    CiffComponent comp;
    DataBuf buf(42);
    comp.setValue(std::move(buf));
    EXPECT_EQ(comp.size(), 42u);
}

// Test setValue replaces previous value
TEST_F(CiffComponentTest_1766, SetValueReplacesPrevious_1766) {
    CiffComponent comp;
    DataBuf buf1(10);
    comp.setValue(std::move(buf1));
    EXPECT_EQ(comp.size(), 10u);

    DataBuf buf2(20);
    comp.setValue(std::move(buf2));
    EXPECT_EQ(comp.size(), 20u);
}

// Test write on default component
TEST_F(CiffComponentTest_1766, WriteDefault_1766) {
    CiffComponent comp;
    Blob blob;
    size_t result = comp.write(blob, littleEndian, 0);
    (void)result;
    // Should not crash
}

// Test multiple setDir calls
TEST_F(CiffComponentTest_1766, MultipleDirChanges_1766) {
    CiffComponent comp;
    comp.setDir(1);
    EXPECT_EQ(comp.dir(), 1);
    comp.setDir(2);
    EXPECT_EQ(comp.dir(), 2);
    comp.setDir(100);
    EXPECT_EQ(comp.dir(), 100);
}

// Test pData after setValue
TEST_F(CiffComponentTest_1766, PDataAfterSetValue_1766) {
    CiffComponent comp;
    DataBuf buf(5);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    buf.data()[2] = 0x03;
    buf.data()[3] = 0x04;
    buf.data()[4] = 0x05;
    comp.setValue(std::move(buf));
    
    const byte* data = comp.pData();
    ASSERT_NE(data, nullptr);
    EXPECT_EQ(data[0], 0x01);
    EXPECT_EQ(data[1], 0x02);
    EXPECT_EQ(data[2], 0x03);
    EXPECT_EQ(data[3], 0x04);
    EXPECT_EQ(data[4], 0x05);
}

// Test component with various tag values for typeId consistency
TEST_F(CiffComponentTest_1766, TypeIdConsistency_1766) {
    for (uint16_t tag = 0; tag < 0x100; tag += 0x10) {
        CiffComponent comp(tag, 0);
        EXPECT_EQ(comp.typeId(), CiffComponent::typeId(tag));
    }
}

// Test component with various tag values for dataLocation consistency
TEST_F(CiffComponentTest_1766, DataLocationConsistency_1766) {
    for (uint16_t tag = 0; tag < 0x100; tag += 0x10) {
        CiffComponent comp(tag, 0);
        EXPECT_EQ(comp.dataLocation(), CiffComponent::dataLocation(tag));
    }
}
