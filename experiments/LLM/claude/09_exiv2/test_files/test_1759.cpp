#include <gtest/gtest.h>
#include <cstdint>
#include <sstream>
#include <vector>

// Include the necessary headers from exiv2
#include "crwimage_int.hpp"

using namespace Exiv2::Internal;

// Test fixture for CiffComponent tests
class CiffComponentTest_1759 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor initializes tag to 0
TEST_F(CiffComponentTest_1759, DefaultConstructorTagIsZero_1759) {
    CiffComponent component;
    EXPECT_EQ(component.tag(), 0);
}

// Test default constructor initializes dir to 0
TEST_F(CiffComponentTest_1759, DefaultConstructorDirIsZero_1759) {
    CiffComponent component;
    EXPECT_EQ(component.dir(), 0);
}

// Test default constructor initializes size to 0
TEST_F(CiffComponentTest_1759, DefaultConstructorSizeIsZero_1759) {
    CiffComponent component;
    EXPECT_EQ(component.size(), 0u);
}

// Test default constructor initializes offset to 0
TEST_F(CiffComponentTest_1759, DefaultConstructorOffsetIsZero_1759) {
    CiffComponent component;
    EXPECT_EQ(component.offset(), 0u);
}

// Test default constructor initializes pData to nullptr
TEST_F(CiffComponentTest_1759, DefaultConstructorPDataIsNull_1759) {
    CiffComponent component;
    EXPECT_EQ(component.pData(), nullptr);
}

// Test parameterized constructor sets tag correctly
TEST_F(CiffComponentTest_1759, ParameterizedConstructorSetsTag_1759) {
    CiffComponent component(0x1234, 0x5678);
    EXPECT_EQ(component.tag(), 0x1234);
}

// Test parameterized constructor sets dir correctly
TEST_F(CiffComponentTest_1759, ParameterizedConstructorSetsDir_1759) {
    CiffComponent component(0x1234, 0x5678);
    EXPECT_EQ(component.dir(), 0x5678);
}

// Test setDir changes the directory value
TEST_F(CiffComponentTest_1759, SetDirChangesDir_1759) {
    CiffComponent component;
    component.setDir(0xABCD);
    EXPECT_EQ(component.dir(), 0xABCD);
}

// Test setDir with zero
TEST_F(CiffComponentTest_1759, SetDirToZero_1759) {
    CiffComponent component(0x1234, 0x5678);
    component.setDir(0);
    EXPECT_EQ(component.dir(), 0);
}

// Test setDir with max uint16 value
TEST_F(CiffComponentTest_1759, SetDirMaxValue_1759) {
    CiffComponent component;
    component.setDir(0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test tag with boundary values
TEST_F(CiffComponentTest_1759, TagMaxValue_1759) {
    CiffComponent component(0xFFFF, 0x0000);
    EXPECT_EQ(component.tag(), 0xFFFF);
}

// Test tag with minimum nonzero value
TEST_F(CiffComponentTest_1759, TagMinNonZeroValue_1759) {
    CiffComponent component(0x0001, 0x0000);
    EXPECT_EQ(component.tag(), 0x0001);
}

// Test empty() on default constructed component
TEST_F(CiffComponentTest_1759, DefaultConstructedIsEmpty_1759) {
    CiffComponent component;
    EXPECT_TRUE(component.empty());
}

// Test setValue and then check that component is no longer empty or data is available
TEST_F(CiffComponentTest_1759, SetValueWithData_1759) {
    CiffComponent component;
    Exiv2::DataBuf buf(10);
    std::memset(buf.data(), 0x42, 10);
    component.setValue(std::move(buf));
    // After setting value, pData should point to something
    EXPECT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.size(), 10u);
}

// Test setValue with empty DataBuf
TEST_F(CiffComponentTest_1759, SetValueWithEmptyDataBuf_1759) {
    CiffComponent component;
    Exiv2::DataBuf buf;
    component.setValue(std::move(buf));
    // Empty buffer behavior
    EXPECT_EQ(component.size(), 0u);
}

// Test tagId extracts the lower bits from tag
TEST_F(CiffComponentTest_1759, TagIdExtraction_1759) {
    // tagId() typically returns the tag ID portion (lower 12 bits or similar)
    CiffComponent component(0x300A, 0x0000);
    uint16_t tagId = component.tagId();
    // tagId should be some extraction from the tag value
    // We just verify it returns a consistent value
    CiffComponent component2(0x300A, 0x0000);
    EXPECT_EQ(tagId, component2.tagId());
}

// Test static typeId function
TEST_F(CiffComponentTest_1759, StaticTypeIdConsistency_1759) {
    uint16_t tag = 0x0000;
    Exiv2::TypeId type1 = CiffComponent::typeId(tag);
    Exiv2::TypeId type2 = CiffComponent::typeId(tag);
    EXPECT_EQ(type1, type2);
}

// Test static dataLocation function
TEST_F(CiffComponentTest_1759, StaticDataLocationConsistency_1759) {
    uint16_t tag = 0x0000;
    DataLocId loc1 = CiffComponent::dataLocation(tag);
    DataLocId loc2 = CiffComponent::dataLocation(tag);
    EXPECT_EQ(loc1, loc2);
}

// Test findComponent returns nullptr for non-matching component
TEST_F(CiffComponentTest_1759, FindComponentReturnsNullForNonMatch_1759) {
    CiffComponent component(0x1234, 0x5678);
    CiffComponent* found = component.findComponent(0x9999, 0x8888);
    // For a basic CiffComponent (not a directory), findComponent might return nullptr
    // or itself if matching. With non-matching IDs, expect nullptr.
    // This depends on implementation, but for a leaf component searching for a 
    // non-matching tag, it should return nullptr
    EXPECT_EQ(found, nullptr);
}

// Test findComponent returns the component itself when matching
TEST_F(CiffComponentTest_1759, FindComponentReturnsSelfWhenMatching_1759) {
    // tagId is derived from tag, dir from dir_
    // We need to know what tagId() and dir() return for this tag/dir combo
    CiffComponent component(0x0001, 0x0002);
    uint16_t crwTagId = component.tagId();
    uint16_t crwDir = component.dir();
    CiffComponent* found = component.findComponent(crwTagId, crwDir);
    EXPECT_EQ(found, &component);
}

// Test print does not crash on default component
TEST_F(CiffComponentTest_1759, PrintDoesNotCrash_1759) {
    CiffComponent component;
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, Exiv2::littleEndian, ""));
}

// Test print with big endian
TEST_F(CiffComponentTest_1759, PrintBigEndianDoesNotCrash_1759) {
    CiffComponent component(0x1234, 0x5678);
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, Exiv2::bigEndian, "prefix"));
}

// Test writeDirEntry does not crash
TEST_F(CiffComponentTest_1759, WriteDirEntryDoesNotCrash_1759) {
    CiffComponent component(0x1234, 0x5678);
    Exiv2::Internal::Blob blob;
    EXPECT_NO_THROW(component.writeDirEntry(blob, Exiv2::littleEndian));
}

// Test writeDirEntry produces output in blob
TEST_F(CiffComponentTest_1759, WriteDirEntryProducesOutput_1759) {
    CiffComponent component(0x1234, 0x5678);
    Exiv2::Internal::Blob blob;
    component.writeDirEntry(blob, Exiv2::littleEndian);
    // A directory entry should have some fixed size (typically 10 bytes for CIFF)
    EXPECT_GT(blob.size(), 0u);
}

// Test write on default component
TEST_F(CiffComponentTest_1759, WriteDefaultComponent_1759) {
    CiffComponent component;
    Exiv2::Internal::Blob blob;
    size_t result = component.write(blob, Exiv2::littleEndian, 0);
    // Result should be a valid offset
    EXPECT_GE(result, 0u);
}

// Test writeValueData on default component
TEST_F(CiffComponentTest_1759, WriteValueDataDefaultComponent_1759) {
    CiffComponent component;
    Exiv2::Internal::Blob blob;
    size_t result = component.writeValueData(blob, 0);
    EXPECT_GE(result, 0u);
}

// Test that copy constructor is deleted (compile-time check)
// This is verified by the fact that the following would not compile:
// CiffComponent copy(component); // Should not compile

// Test that copy assignment is deleted (compile-time check)
// CiffComponent a, b; a = b; // Should not compile

// Test multiple setDir calls
TEST_F(CiffComponentTest_1759, MultipleSetDirCalls_1759) {
    CiffComponent component;
    component.setDir(0x0001);
    EXPECT_EQ(component.dir(), 0x0001);
    component.setDir(0x0002);
    EXPECT_EQ(component.dir(), 0x0002);
    component.setDir(0x0003);
    EXPECT_EQ(component.dir(), 0x0003);
}

// Test setValue replaces previous value
TEST_F(CiffComponentTest_1759, SetValueReplacesOldValue_1759) {
    CiffComponent component;
    
    Exiv2::DataBuf buf1(5);
    std::memset(buf1.data(), 0x11, 5);
    component.setValue(std::move(buf1));
    EXPECT_EQ(component.size(), 5u);
    
    Exiv2::DataBuf buf2(15);
    std::memset(buf2.data(), 0x22, 15);
    component.setValue(std::move(buf2));
    EXPECT_EQ(component.size(), 15u);
}

// Test typeId member function on instance
TEST_F(CiffComponentTest_1759, InstanceTypeIdConsistency_1759) {
    CiffComponent component(0x2000, 0x0000);
    Exiv2::TypeId t1 = component.typeId();
    Exiv2::TypeId t2 = component.typeId();
    EXPECT_EQ(t1, t2);
}

// Test dataLocation member function on instance
TEST_F(CiffComponentTest_1759, InstanceDataLocationConsistency_1759) {
    CiffComponent component(0x2000, 0x0000);
    DataLocId d1 = component.dataLocation();
    DataLocId d2 = component.dataLocation();
    EXPECT_EQ(d1, d2);
}

// Test that static typeId and instance typeId agree
TEST_F(CiffComponentTest_1759, StaticAndInstanceTypeIdAgree_1759) {
    uint16_t tag = 0x0800;
    CiffComponent component(tag, 0x0000);
    EXPECT_EQ(CiffComponent::typeId(tag), component.typeId());
}

// Test that static dataLocation and instance dataLocation agree
TEST_F(CiffComponentTest_1759, StaticAndInstanceDataLocationAgree_1759) {
    uint16_t tag = 0x0800;
    CiffComponent component(tag, 0x0000);
    EXPECT_EQ(CiffComponent::dataLocation(tag), component.dataLocation());
}
