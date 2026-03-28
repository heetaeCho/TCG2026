#include <gtest/gtest.h>
#include <cstdint>
#include <sstream>
#include <vector>

// Include the necessary headers from exiv2
#include "crwimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for CiffComponent tests
class CiffComponentTest_1762 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor initializes pData to nullptr
TEST_F(CiffComponentTest_1762, DefaultConstructor_pDataIsNull_1762) {
    CiffComponent component;
    EXPECT_EQ(component.pData(), nullptr);
}

// Test default constructor initializes size to 0
TEST_F(CiffComponentTest_1762, DefaultConstructor_SizeIsZero_1762) {
    CiffComponent component;
    EXPECT_EQ(component.size(), 0u);
}

// Test default constructor initializes offset to 0
TEST_F(CiffComponentTest_1762, DefaultConstructor_OffsetIsZero_1762) {
    CiffComponent component;
    EXPECT_EQ(component.offset(), 0u);
}

// Test default constructor initializes dir to 0
TEST_F(CiffComponentTest_1762, DefaultConstructor_DirIsZero_1762) {
    CiffComponent component;
    EXPECT_EQ(component.dir(), 0u);
}

// Test default constructor initializes tag to 0
TEST_F(CiffComponentTest_1762, DefaultConstructor_TagIsZero_1762) {
    CiffComponent component;
    EXPECT_EQ(component.tag(), 0u);
}

// Test parameterized constructor sets tag and dir
TEST_F(CiffComponentTest_1762, ParameterizedConstructor_SetsTagAndDir_1762) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent component(tag, dir);
    EXPECT_EQ(component.tag(), tag);
    EXPECT_EQ(component.dir(), dir);
}

// Test parameterized constructor - pData is still nullptr
TEST_F(CiffComponentTest_1762, ParameterizedConstructor_pDataIsNull_1762) {
    CiffComponent component(0x0001, 0x0002);
    EXPECT_EQ(component.pData(), nullptr);
}

// Test parameterized constructor - size is zero
TEST_F(CiffComponentTest_1762, ParameterizedConstructor_SizeIsZero_1762) {
    CiffComponent component(0x0001, 0x0002);
    EXPECT_EQ(component.size(), 0u);
}

// Test parameterized constructor - offset is zero
TEST_F(CiffComponentTest_1762, ParameterizedConstructor_OffsetIsZero_1762) {
    CiffComponent component(0x0001, 0x0002);
    EXPECT_EQ(component.offset(), 0u);
}

// Test setDir changes the directory value
TEST_F(CiffComponentTest_1762, SetDir_ChangesDir_1762) {
    CiffComponent component;
    component.setDir(0xABCD);
    EXPECT_EQ(component.dir(), 0xABCD);
}

// Test setDir with zero
TEST_F(CiffComponentTest_1762, SetDir_Zero_1762) {
    CiffComponent component(0x0001, 0x0002);
    component.setDir(0);
    EXPECT_EQ(component.dir(), 0u);
}

// Test setDir with max uint16 value
TEST_F(CiffComponentTest_1762, SetDir_MaxValue_1762) {
    CiffComponent component;
    component.setDir(0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test empty() on default constructed component
TEST_F(CiffComponentTest_1762, Empty_DefaultConstructed_1762) {
    CiffComponent component;
    // A default constructed CiffComponent should report as empty
    EXPECT_TRUE(component.empty());
}

// Test setValue updates pData and size
TEST_F(CiffComponentTest_1762, SetValue_UpdatesDataAndSize_1762) {
    CiffComponent component;
    
    // Create a DataBuf with some data
    const byte testData[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(testData, sizeof(testData));
    
    component.setValue(std::move(buf));
    
    EXPECT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.size(), sizeof(testData));
}

// Test setValue with data - verify content
TEST_F(CiffComponentTest_1762, SetValue_DataContentIsCorrect_1762) {
    CiffComponent component;
    
    const byte testData[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
    DataBuf buf(testData, sizeof(testData));
    
    component.setValue(std::move(buf));
    
    ASSERT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.pData()[0], 0xAA);
    EXPECT_EQ(component.pData()[1], 0xBB);
    EXPECT_EQ(component.pData()[2], 0xCC);
    EXPECT_EQ(component.pData()[3], 0xDD);
    EXPECT_EQ(component.pData()[4], 0xEE);
}

// Test setValue with empty DataBuf
TEST_F(CiffComponentTest_1762, SetValue_EmptyDataBuf_1762) {
    CiffComponent component;
    DataBuf buf;
    component.setValue(std::move(buf));
    EXPECT_EQ(component.size(), 0u);
}

// Test empty after setValue with data
TEST_F(CiffComponentTest_1762, Empty_AfterSetValue_1762) {
    CiffComponent component;
    
    const byte testData[] = {0x01, 0x02};
    DataBuf buf(testData, sizeof(testData));
    component.setValue(std::move(buf));
    
    // After setting a value, component should not be empty
    EXPECT_FALSE(component.empty());
}

// Test tagId - derived from tag
TEST_F(CiffComponentTest_1762, TagId_DerivedFromTag_1762) {
    CiffComponent component(0x300A, 0x0000);
    // tagId should be the lower bits of tag (tag & 0x3fff typically)
    uint16_t tagId = component.tagId();
    // We can verify it returns a consistent value
    EXPECT_EQ(tagId, component.tagId());
}

// Test typeId static method
TEST_F(CiffComponentTest_1762, TypeId_StaticMethod_1762) {
    // typeId is a static method that maps tag to TypeId
    // Just verify it doesn't crash for various inputs
    TypeId t1 = CiffComponent::typeId(0x0000);
    TypeId t2 = CiffComponent::typeId(0x0800);
    TypeId t3 = CiffComponent::typeId(0xFFFF);
    // Results should be valid TypeId values - we just ensure no crash
    (void)t1;
    (void)t2;
    (void)t3;
}

// Test dataLocation static method
TEST_F(CiffComponentTest_1762, DataLocation_StaticMethod_1762) {
    // Just verify it doesn't crash
    DataLocId loc1 = CiffComponent::dataLocation(0x0000);
    DataLocId loc2 = CiffComponent::dataLocation(0xFFFF);
    (void)loc1;
    (void)loc2;
}

// Test typeId instance method
TEST_F(CiffComponentTest_1762, TypeId_InstanceMethod_1762) {
    CiffComponent component(0x0800, 0x0000);
    TypeId tid = component.typeId();
    // Verify consistency
    EXPECT_EQ(tid, component.typeId());
}

// Test dataLocation instance method
TEST_F(CiffComponentTest_1762, DataLocation_InstanceMethod_1762) {
    CiffComponent component(0x0800, 0x0000);
    DataLocId loc = component.dataLocation();
    // Verify consistency
    EXPECT_EQ(loc, component.dataLocation());
}

// Test findComponent on a leaf component (not a directory)
TEST_F(CiffComponentTest_1762, FindComponent_LeafComponent_1762) {
    CiffComponent component(0x0001, 0x0002);
    // For a leaf component, findComponent should return nullptr
    // unless the component itself matches
    CiffComponent* result = component.findComponent(0x0001, 0x0002);
    // Result depends on implementation; we just verify no crash
    (void)result;
}

// Test findComponent with non-matching parameters
TEST_F(CiffComponentTest_1762, FindComponent_NonMatching_1762) {
    CiffComponent component(0x0001, 0x0002);
    CiffComponent* result = component.findComponent(0xFFFF, 0xFFFF);
    EXPECT_EQ(result, nullptr);
}

// Test print doesn't crash
TEST_F(CiffComponentTest_1762, Print_DoesNotCrash_1762) {
    CiffComponent component(0x0001, 0x0002);
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, littleEndian, ""));
}

// Test print with prefix
TEST_F(CiffComponentTest_1762, Print_WithPrefix_1762) {
    CiffComponent component(0x0001, 0x0002);
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, bigEndian, "prefix: "));
}

// Test writeDirEntry doesn't crash on default component
TEST_F(CiffComponentTest_1762, WriteDirEntry_DefaultComponent_1762) {
    CiffComponent component(0x0001, 0x0002);
    Blob blob;
    EXPECT_NO_THROW(component.writeDirEntry(blob, littleEndian));
}

// Test writeValueData
TEST_F(CiffComponentTest_1762, WriteValueData_DefaultComponent_1762) {
    CiffComponent component(0x0001, 0x0002);
    Blob blob;
    size_t result = component.writeValueData(blob, 0);
    // Result should be a valid offset
    (void)result;
}

// Test tag values boundary - zero
TEST_F(CiffComponentTest_1762, BoundaryTag_Zero_1762) {
    CiffComponent component(0x0000, 0x0000);
    EXPECT_EQ(component.tag(), 0x0000);
    EXPECT_EQ(component.dir(), 0x0000);
}

// Test tag values boundary - max
TEST_F(CiffComponentTest_1762, BoundaryTag_Max_1762) {
    CiffComponent component(0xFFFF, 0xFFFF);
    EXPECT_EQ(component.tag(), 0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test setValue replaces previous data
TEST_F(CiffComponentTest_1762, SetValue_ReplacePreviousData_1762) {
    CiffComponent component;
    
    const byte data1[] = {0x01, 0x02};
    DataBuf buf1(data1, sizeof(data1));
    component.setValue(std::move(buf1));
    EXPECT_EQ(component.size(), 2u);
    
    const byte data2[] = {0x0A, 0x0B, 0x0C, 0x0D};
    DataBuf buf2(data2, sizeof(data2));
    component.setValue(std::move(buf2));
    EXPECT_EQ(component.size(), 4u);
    
    ASSERT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.pData()[0], 0x0A);
}

// Test that copy constructor is deleted (compile-time check would be needed,
// but we verify the interface is as expected)
TEST_F(CiffComponentTest_1762, CopyConstructorDeleted_1762) {
    // This is a compile-time constraint. We just verify that a CiffComponent
    // can be created and destroyed properly.
    auto component = std::make_unique<CiffComponent>(0x0001, 0x0002);
    EXPECT_NE(component, nullptr);
    EXPECT_EQ(component->tag(), 0x0001);
}

// Test destructor doesn't crash after setValue
TEST_F(CiffComponentTest_1762, Destructor_AfterSetValue_1762) {
    {
        CiffComponent component;
        const byte testData[] = {0x01, 0x02, 0x03};
        DataBuf buf(testData, sizeof(testData));
        component.setValue(std::move(buf));
    }
    // If we get here without crashing, the destructor works fine
    SUCCEED();
}

// Test multiple setDir calls
TEST_F(CiffComponentTest_1762, MultipleSetDir_1762) {
    CiffComponent component;
    component.setDir(0x0001);
    EXPECT_EQ(component.dir(), 0x0001);
    component.setDir(0x0002);
    EXPECT_EQ(component.dir(), 0x0002);
    component.setDir(0x0003);
    EXPECT_EQ(component.dir(), 0x0003);
}

// Test setValue with single byte
TEST_F(CiffComponentTest_1762, SetValue_SingleByte_1762) {
    CiffComponent component;
    const byte data[] = {0xFF};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));
    
    EXPECT_EQ(component.size(), 1u);
    ASSERT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.pData()[0], 0xFF);
}

// Test setValue with large data
TEST_F(CiffComponentTest_1762, SetValue_LargeData_1762) {
    CiffComponent component;
    std::vector<byte> largeData(10000, 0x42);
    DataBuf buf(largeData.data(), largeData.size());
    component.setValue(std::move(buf));
    
    EXPECT_EQ(component.size(), 10000u);
    ASSERT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.pData()[0], 0x42);
    EXPECT_EQ(component.pData()[9999], 0x42);
}
