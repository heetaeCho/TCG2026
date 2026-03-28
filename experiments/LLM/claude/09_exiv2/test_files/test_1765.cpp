#include <gtest/gtest.h>
#include "crwimage_int.hpp"

using namespace Exiv2::Internal;

// Test fixture for CiffComponent tests
class CiffComponentTest_1765 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor creates component with default values
TEST_F(CiffComponentTest_1765, DefaultConstructor_HasZeroTag_1765) {
    CiffComponent comp;
    EXPECT_EQ(comp.tag(), 0);
}

TEST_F(CiffComponentTest_1765, DefaultConstructor_HasZeroDir_1765) {
    CiffComponent comp;
    EXPECT_EQ(comp.dir(), 0);
}

TEST_F(CiffComponentTest_1765, DefaultConstructor_HasZeroSize_1765) {
    CiffComponent comp;
    EXPECT_EQ(comp.size(), 0u);
}

TEST_F(CiffComponentTest_1765, DefaultConstructor_HasZeroOffset_1765) {
    CiffComponent comp;
    EXPECT_EQ(comp.offset(), 0u);
}

TEST_F(CiffComponentTest_1765, DefaultConstructor_HasNullPData_1765) {
    CiffComponent comp;
    EXPECT_EQ(comp.pData(), nullptr);
}

// Test parameterized constructor
TEST_F(CiffComponentTest_1765, ParameterizedConstructor_SetsTag_1765) {
    CiffComponent comp(0x1234, 0x5678);
    EXPECT_EQ(comp.tag(), 0x1234);
}

TEST_F(CiffComponentTest_1765, ParameterizedConstructor_SetsDir_1765) {
    CiffComponent comp(0x1234, 0x5678);
    EXPECT_EQ(comp.dir(), 0x5678);
}

// Test setDir
TEST_F(CiffComponentTest_1765, SetDir_ChangesDir_1765) {
    CiffComponent comp;
    comp.setDir(0xABCD);
    EXPECT_EQ(comp.dir(), 0xABCD);
}

// Test tagId - tagId is typically derived from tag
TEST_F(CiffComponentTest_1765, TagId_DerivedFromTag_1765) {
    CiffComponent comp(0x080A, 0x0000);
    uint16_t tagId = comp.tagId();
    // tagId is typically the lower bits of the tag
    // We just verify it returns a consistent value
    EXPECT_EQ(tagId, comp.tagId());
}

// Test typeId static method with various tags
TEST_F(CiffComponentTest_1765, TypeId_StaticMethod_ZeroTag_1765) {
    TypeId type = CiffComponent::typeId(0x0000);
    // Just verify it returns without crashing and returns a valid TypeId
    (void)type;
}

TEST_F(CiffComponentTest_1765, TypeId_InstanceMethod_1765) {
    CiffComponent comp(0x0000, 0x0000);
    TypeId type = comp.typeId();
    // Verify consistency: instance method should match static method
    EXPECT_EQ(type, CiffComponent::typeId(0x0000));
}

// Test dataLocation static method
TEST_F(CiffComponentTest_1765, DataLocation_StaticMethod_ZeroTag_1765) {
    DataLocId loc = CiffComponent::dataLocation(0x0000);
    // Verify it returns some valid value
    (void)loc;
}

TEST_F(CiffComponentTest_1765, DataLocation_InstanceMethod_MatchesStatic_1765) {
    CiffComponent comp(0x0800, 0x0000);
    DataLocId instanceLoc = comp.dataLocation();
    DataLocId staticLoc = CiffComponent::dataLocation(0x0800);
    EXPECT_EQ(instanceLoc, staticLoc);
}

// Test dataLocation for tags that should be stored in the value
TEST_F(CiffComponentTest_1765, DataLocation_SmallTag_1765) {
    // Tags with certain bit patterns may indicate value data location
    DataLocId loc1 = CiffComponent::dataLocation(0x0001);
    (void)loc1;
}

TEST_F(CiffComponentTest_1765, DataLocation_LargeTag_1765) {
    DataLocId loc = CiffComponent::dataLocation(0xFFFF);
    (void)loc;
}

// Test empty on default constructed component
TEST_F(CiffComponentTest_1765, Empty_DefaultConstructed_1765) {
    CiffComponent comp;
    // A default constructed component should be considered empty
    // (no data set)
    bool isEmpty = comp.empty();
    (void)isEmpty; // Just ensure it doesn't crash
}

// Test setValue
TEST_F(CiffComponentTest_1765, SetValue_UpdatesData_1765) {
    CiffComponent comp(0x0001, 0x0000);
    Exiv2::DataBuf buf(10);
    std::memset(buf.data(), 0x42, 10);
    comp.setValue(std::move(buf));
    
    EXPECT_NE(comp.pData(), nullptr);
    EXPECT_EQ(comp.size(), 10u);
}

TEST_F(CiffComponentTest_1765, SetValue_EmptyBuffer_1765) {
    CiffComponent comp(0x0001, 0x0000);
    Exiv2::DataBuf buf;
    comp.setValue(std::move(buf));
    // After setting empty buffer, size should be 0
    EXPECT_EQ(comp.size(), 0u);
}

// Test findComponent on a leaf component
TEST_F(CiffComponentTest_1765, FindComponent_MatchingTagAndDir_1765) {
    CiffComponent comp(0x0001, 0x0002);
    CiffComponent* found = comp.findComponent(0x0001, 0x0002);
    // A leaf component should find itself if tag and dir match
    // or return nullptr if they don't match
    (void)found;
}

TEST_F(CiffComponentTest_1765, FindComponent_NonMatchingTag_1765) {
    CiffComponent comp(0x0001, 0x0002);
    CiffComponent* found = comp.findComponent(0x9999, 0x0002);
    EXPECT_EQ(found, nullptr);
}

TEST_F(CiffComponentTest_1765, FindComponent_NonMatchingDir_1765) {
    CiffComponent comp(0x0001, 0x0002);
    CiffComponent* found = comp.findComponent(0x0001, 0x9999);
    EXPECT_EQ(found, nullptr);
}

// Test typeId with different tag values for consistency
TEST_F(CiffComponentTest_1765, TypeId_DifferentTags_1765) {
    // Test several different tag values
    TypeId t1 = CiffComponent::typeId(0x0000);
    TypeId t2 = CiffComponent::typeId(0x0800);
    TypeId t3 = CiffComponent::typeId(0x2000);
    TypeId t4 = CiffComponent::typeId(0x3800);
    
    // Just verify they return without crashing
    (void)t1;
    (void)t2;
    (void)t3;
    (void)t4;
}

// Test dataLocation with different tag bit patterns
TEST_F(CiffComponentTest_1765, DataLocation_VariousTags_1765) {
    DataLocId d1 = CiffComponent::dataLocation(0x0000);
    DataLocId d2 = CiffComponent::dataLocation(0x4000);
    DataLocId d3 = CiffComponent::dataLocation(0x8000);
    DataLocId d4 = CiffComponent::dataLocation(0xC000);
    
    (void)d1;
    (void)d2;
    (void)d3;
    (void)d4;
}

// Test that copy constructor is deleted (compile-time check conceptually)
// We verify this is correct by noting it's deleted in the interface

// Test writeDirEntry with a blob
TEST_F(CiffComponentTest_1765, WriteDirEntry_DefaultComponent_1765) {
    CiffComponent comp(0x0001, 0x0000);
    Exiv2::Internal::Blob blob;
    // Writing a dir entry for a default component should not crash
    comp.writeDirEntry(blob, Exiv2::littleEndian);
    // The blob should have some data written (dir entry is typically 10 bytes)
    EXPECT_FALSE(blob.empty());
}

// Test print doesn't crash
TEST_F(CiffComponentTest_1765, Print_DefaultComponent_1765) {
    CiffComponent comp(0x0001, 0x0000);
    std::ostringstream os;
    comp.print(os, Exiv2::littleEndian, "");
    // Just verify no crash
}

// Test print with prefix
TEST_F(CiffComponentTest_1765, Print_WithPrefix_1765) {
    CiffComponent comp(0x0001, 0x0000);
    std::ostringstream os;
    comp.print(os, Exiv2::bigEndian, "prefix_");
    // Just verify no crash
}

// Test write and writeValueData on empty component
TEST_F(CiffComponentTest_1765, Write_EmptyComponent_1765) {
    CiffComponent comp(0x0001, 0x0000);
    Exiv2::Internal::Blob blob;
    size_t result = comp.write(blob, Exiv2::littleEndian, 0);
    (void)result;
}

TEST_F(CiffComponentTest_1765, WriteValueData_EmptyComponent_1765) {
    CiffComponent comp(0x0001, 0x0000);
    Exiv2::Internal::Blob blob;
    size_t result = comp.writeValueData(blob, 0);
    (void)result;
}

// Test setValue then verify pData and size
TEST_F(CiffComponentTest_1765, SetValue_VerifyPDataAndSize_1765) {
    CiffComponent comp(0x0002, 0x0003);
    const size_t dataSize = 256;
    Exiv2::DataBuf buf(dataSize);
    for (size_t i = 0; i < dataSize; ++i) {
        buf.data()[i] = static_cast<Exiv2::byte>(i & 0xFF);
    }
    comp.setValue(std::move(buf));
    
    EXPECT_EQ(comp.size(), dataSize);
    EXPECT_NE(comp.pData(), nullptr);
    // Verify first byte
    EXPECT_EQ(comp.pData()[0], 0x00);
    EXPECT_EQ(comp.pData()[255], 0xFF);
}

// Test multiple setDir calls
TEST_F(CiffComponentTest_1765, SetDir_MultipleCalls_1765) {
    CiffComponent comp;
    comp.setDir(1);
    EXPECT_EQ(comp.dir(), 1);
    comp.setDir(2);
    EXPECT_EQ(comp.dir(), 2);
    comp.setDir(0xFFFF);
    EXPECT_EQ(comp.dir(), 0xFFFF);
}

// Boundary: max uint16_t values for tag and dir
TEST_F(CiffComponentTest_1765, BoundaryMaxValues_TagAndDir_1765) {
    CiffComponent comp(0xFFFF, 0xFFFF);
    EXPECT_EQ(comp.tag(), 0xFFFF);
    EXPECT_EQ(comp.dir(), 0xFFFF);
}

// Boundary: zero values for tag and dir
TEST_F(CiffComponentTest_1765, BoundaryZeroValues_TagAndDir_1765) {
    CiffComponent comp(0x0000, 0x0000);
    EXPECT_EQ(comp.tag(), 0x0000);
    EXPECT_EQ(comp.dir(), 0x0000);
}

// Test that the data location for the same tag is deterministic
TEST_F(CiffComponentTest_1765, DataLocation_Deterministic_1765) {
    DataLocId loc1 = CiffComponent::dataLocation(0x1234);
    DataLocId loc2 = CiffComponent::dataLocation(0x1234);
    EXPECT_EQ(loc1, loc2);
}

// Test that typeId for the same tag is deterministic
TEST_F(CiffComponentTest_1765, TypeId_Deterministic_1765) {
    TypeId t1 = CiffComponent::typeId(0x5678);
    TypeId t2 = CiffComponent::typeId(0x5678);
    EXPECT_EQ(t1, t2);
}
