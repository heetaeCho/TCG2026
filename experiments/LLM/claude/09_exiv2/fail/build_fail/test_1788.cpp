#include <gtest/gtest.h>
#include <cstdint>
#include "crwimage_int.hpp"

using namespace Exiv2::Internal;

class CiffComponentTest_1788 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor creates a component with default tag and dir values
TEST_F(CiffComponentTest_1788, DefaultConstructor_1788) {
    CiffComponent component;
    EXPECT_EQ(component.tag(), 0);
    EXPECT_EQ(component.dir(), 0);
    EXPECT_EQ(component.size(), 0u);
    EXPECT_EQ(component.offset(), 0u);
    EXPECT_EQ(component.pData(), nullptr);
}

// Test parameterized constructor sets tag and dir correctly
TEST_F(CiffComponentTest_1788, ParameterizedConstructor_1788) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent component(tag, dir);
    EXPECT_EQ(component.tag(), tag);
    EXPECT_EQ(component.dir(), dir);
}

// Test findComponent returns this when tag and dir match
TEST_F(CiffComponentTest_1788, FindComponentMatchingTagAndDir_1788) {
    uint16_t tag = 0x0001;
    uint16_t dir = 0x0002;
    CiffComponent component(tag, dir);
    
    // tagId() is derived from tag(), and dir() returns dir
    uint16_t crwTagId = component.tagId();
    uint16_t crwDir = component.dir();
    
    CiffComponent* result = component.findComponent(crwTagId, crwDir);
    EXPECT_EQ(result, &component);
}

// Test findComponent returns nullptr when tag doesn't match
TEST_F(CiffComponentTest_1788, FindComponentNonMatchingTag_1788) {
    uint16_t tag = 0x0001;
    uint16_t dir = 0x0002;
    CiffComponent component(tag, dir);
    
    uint16_t crwDir = component.dir();
    // Use a different tagId
    uint16_t wrongTagId = component.tagId() + 1;
    
    CiffComponent* result = component.findComponent(wrongTagId, crwDir);
    EXPECT_EQ(result, nullptr);
}

// Test findComponent returns nullptr when dir doesn't match
TEST_F(CiffComponentTest_1788, FindComponentNonMatchingDir_1788) {
    uint16_t tag = 0x0001;
    uint16_t dir = 0x0002;
    CiffComponent component(tag, dir);
    
    uint16_t crwTagId = component.tagId();
    uint16_t wrongDir = component.dir() + 1;
    
    CiffComponent* result = component.findComponent(crwTagId, wrongDir);
    EXPECT_EQ(result, nullptr);
}

// Test findComponent returns nullptr when neither tag nor dir match
TEST_F(CiffComponentTest_1788, FindComponentNeitherMatch_1788) {
    uint16_t tag = 0x0001;
    uint16_t dir = 0x0002;
    CiffComponent component(tag, dir);
    
    uint16_t wrongTagId = component.tagId() + 1;
    uint16_t wrongDir = component.dir() + 1;
    
    CiffComponent* result = component.findComponent(wrongTagId, wrongDir);
    EXPECT_EQ(result, nullptr);
}

// Test setDir changes the directory
TEST_F(CiffComponentTest_1788, SetDirChangesDir_1788) {
    CiffComponent component(0x0001, 0x0002);
    EXPECT_EQ(component.dir(), 0x0002);
    
    component.setDir(0x00FF);
    EXPECT_EQ(component.dir(), 0x00FF);
}

// Test empty() on default constructed component
TEST_F(CiffComponentTest_1788, EmptyOnDefaultComponent_1788) {
    CiffComponent component;
    bool isEmpty = component.empty();
    // Default component should likely be empty
    EXPECT_TRUE(isEmpty);
}

// Test setValue and then check pData and size
TEST_F(CiffComponentTest_1788, SetValueUpdatesDataAndSize_1788) {
    CiffComponent component(0x0001, 0x0002);
    
    Exiv2::DataBuf buf(10);
    std::memset(buf.data(), 0xAB, 10);
    
    component.setValue(std::move(buf));
    
    EXPECT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.size(), 10u);
}

// Test with boundary tag values (0x0000)
TEST_F(CiffComponentTest_1788, BoundaryTagZero_1788) {
    CiffComponent component(0x0000, 0x0000);
    EXPECT_EQ(component.tag(), 0x0000);
    EXPECT_EQ(component.dir(), 0x0000);
    
    uint16_t crwTagId = component.tagId();
    uint16_t crwDir = component.dir();
    
    CiffComponent* result = component.findComponent(crwTagId, crwDir);
    EXPECT_EQ(result, &component);
}

// Test with boundary tag values (0xFFFF)
TEST_F(CiffComponentTest_1788, BoundaryTagMaxValue_1788) {
    CiffComponent component(0xFFFF, 0xFFFF);
    EXPECT_EQ(component.tag(), 0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test typeId static method with various tags
TEST_F(CiffComponentTest_1788, StaticTypeIdMethod_1788) {
    // Just verify it doesn't crash with various inputs
    auto t1 = CiffComponent::typeId(0x0000);
    auto t2 = CiffComponent::typeId(0x0001);
    auto t3 = CiffComponent::typeId(0xFFFF);
    // We can't assert specific values without knowing implementation,
    // but we verify they return valid TypeId values
    (void)t1;
    (void)t2;
    (void)t3;
}

// Test dataLocation static method with various tags
TEST_F(CiffComponentTest_1788, StaticDataLocationMethod_1788) {
    // Just verify it doesn't crash with various inputs
    auto d1 = CiffComponent::dataLocation(0x0000);
    auto d2 = CiffComponent::dataLocation(0x0001);
    auto d3 = CiffComponent::dataLocation(0xFFFF);
    (void)d1;
    (void)d2;
    (void)d3;
}

// Test tagId() is consistent with tag()
TEST_F(CiffComponentTest_1788, TagIdDerivedFromTag_1788) {
    CiffComponent component1(0x0001, 0x0002);
    CiffComponent component2(0x0001, 0x0003);
    
    // Same tag should give same tagId regardless of dir
    EXPECT_EQ(component1.tagId(), component2.tagId());
}

// Test that typeId() instance method works
TEST_F(CiffComponentTest_1788, InstanceTypeIdMethod_1788) {
    CiffComponent component(0x0001, 0x0002);
    auto tid = component.typeId();
    // Should be same as static method with same tag
    EXPECT_EQ(tid, CiffComponent::typeId(0x0001));
}

// Test that dataLocation() instance method works
TEST_F(CiffComponentTest_1788, InstanceDataLocationMethod_1788) {
    CiffComponent component(0x0001, 0x0002);
    auto dloc = component.dataLocation();
    EXPECT_EQ(dloc, CiffComponent::dataLocation(0x0001));
}

// Test setValue with empty DataBuf
TEST_F(CiffComponentTest_1788, SetValueEmptyBuf_1788) {
    CiffComponent component(0x0001, 0x0002);
    Exiv2::DataBuf emptyBuf;
    component.setValue(std::move(emptyBuf));
    EXPECT_EQ(component.size(), 0u);
}

// Test writeValueData on component with no data
TEST_F(CiffComponentTest_1788, WriteValueDataNoData_1788) {
    CiffComponent component;
    Exiv2::Blob blob;
    size_t result = component.writeValueData(blob, 0);
    // With no data, the returned offset should be the same as input or minimal
    (void)result;
}

// Test writeDirEntry on a basic component
TEST_F(CiffComponentTest_1788, WriteDirEntryBasic_1788) {
    CiffComponent component(0x0001, 0x0002);
    Exiv2::Blob blob;
    // Should not crash
    component.writeDirEntry(blob, Exiv2::littleEndian);
    // Dir entry should add some bytes to blob
    EXPECT_GT(blob.size(), 0u);
}

// Test print doesn't crash
TEST_F(CiffComponentTest_1788, PrintDoesNotCrash_1788) {
    CiffComponent component(0x0001, 0x0002);
    std::ostringstream os;
    component.print(os, Exiv2::littleEndian, "");
    // Just verify it doesn't crash; output format is implementation detail
}
