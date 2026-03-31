#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <vector>
#include <cstdint>

#include "crwimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for CiffComponent tests
class CiffComponentTest_1781 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor
TEST_F(CiffComponentTest_1781, DefaultConstructor_1781) {
    CiffComponent component;
    EXPECT_EQ(component.tag(), 0);
    EXPECT_EQ(component.dir(), 0);
    EXPECT_EQ(component.size(), 0u);
    EXPECT_EQ(component.offset(), 0u);
    EXPECT_EQ(component.pData(), nullptr);
}

// Test parameterized constructor
TEST_F(CiffComponentTest_1781, ParameterizedConstructor_1781) {
    uint16_t tag = 0x0805;
    uint16_t dir = 0x300a;
    CiffComponent component(tag, dir);
    EXPECT_EQ(component.tag(), tag);
    EXPECT_EQ(component.dir(), dir);
    EXPECT_EQ(component.size(), 0u);
    EXPECT_EQ(component.offset(), 0u);
    EXPECT_EQ(component.pData(), nullptr);
}

// Test setDir
TEST_F(CiffComponentTest_1781, SetDir_1781) {
    CiffComponent component;
    component.setDir(0x1234);
    EXPECT_EQ(component.dir(), 0x1234);
}

// Test tagId extraction (lower bits of tag)
TEST_F(CiffComponentTest_1781, TagId_1781) {
    uint16_t tag = 0x0805;
    uint16_t dir = 0x0000;
    CiffComponent component(tag, dir);
    // tagId should return the tag with the type bits masked out
    uint16_t tagId = component.tagId();
    // tagId is typically tag & 0x3fff
    EXPECT_EQ(tagId, tag & 0x3fff);
}

// Test typeId static method with various tag values
TEST_F(CiffComponentTest_1781, StaticTypeId_1781) {
    // typeId is derived from tag bits - testing the static version
    // The type is encoded in bits 13-14 of the tag
    TypeId type0 = CiffComponent::typeId(0x0000);  // type bits = 0
    TypeId type1 = CiffComponent::typeId(0x2000);  // type bits = 1
    TypeId type2 = CiffComponent::typeId(0x4000);  // type bits = 2
    TypeId type3 = CiffComponent::typeId(0x6000);  // type bits = 3
    TypeId type4 = CiffComponent::typeId(0x8000);  // type bits = 4

    // We just verify the function returns without crashing and produces some result
    // The actual mapping is implementation-defined
    (void)type0;
    (void)type1;
    (void)type2;
    (void)type3;
    (void)type4;
}

// Test dataLocation static method
TEST_F(CiffComponentTest_1781, StaticDataLocation_1781) {
    DataLocId loc1 = CiffComponent::dataLocation(0x0000);
    DataLocId loc2 = CiffComponent::dataLocation(0x4000);
    DataLocId loc3 = CiffComponent::dataLocation(0x8000);
    // Just verify the function is callable
    (void)loc1;
    (void)loc2;
    (void)loc3;
}

// Test instance typeId method
TEST_F(CiffComponentTest_1781, InstanceTypeId_1781) {
    CiffComponent component(0x2000, 0x0000);
    TypeId type = component.typeId();
    EXPECT_EQ(type, CiffComponent::typeId(0x2000));
}

// Test instance dataLocation method
TEST_F(CiffComponentTest_1781, InstanceDataLocation_1781) {
    CiffComponent component(0x4000, 0x0000);
    DataLocId loc = component.dataLocation();
    EXPECT_EQ(loc, CiffComponent::dataLocation(0x4000));
}

// Test empty on default constructed component
TEST_F(CiffComponentTest_1781, EmptyDefault_1781) {
    CiffComponent component;
    bool isEmpty = component.empty();
    // Default constructed should be empty (no data)
    (void)isEmpty;  // Just verify it doesn't crash
}

// Test print method on default component
TEST_F(CiffComponentTest_1781, PrintDefault_1781) {
    CiffComponent component;
    std::ostringstream oss;
    // Print should not crash even on a default-constructed component
    component.print(oss, littleEndian, "");
    // Verify something was written or at least no crash
    std::string output = oss.str();
    // Output content is implementation-defined
}

// Test print with a prefix
TEST_F(CiffComponentTest_1781, PrintWithPrefix_1781) {
    CiffComponent component(0x0805, 0x300a);
    std::ostringstream oss;
    component.print(oss, littleEndian, "  ");
    std::string output = oss.str();
    // We just verify the function works without crashing
}

// Test print with bigEndian byte order
TEST_F(CiffComponentTest_1781, PrintBigEndian_1781) {
    CiffComponent component(0x0805, 0x300a);
    std::ostringstream oss;
    component.print(oss, bigEndian, "prefix:");
    std::string output = oss.str();
    // Verify it doesn't crash
}

// Test setValue
TEST_F(CiffComponentTest_1781, SetValue_1781) {
    CiffComponent component(0x0805, 0x0000);
    
    // Create a DataBuf with some data
    DataBuf buf(10);
    std::memset(buf.data(), 0xAB, 10);
    
    component.setValue(std::move(buf));
    
    // After setting value, pData should not be null and size should be updated
    EXPECT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.size(), 10u);
}

// Test setValue with empty buffer
TEST_F(CiffComponentTest_1781, SetValueEmpty_1781) {
    CiffComponent component(0x0805, 0x0000);
    DataBuf buf;  // empty buffer
    component.setValue(std::move(buf));
    // Depending on implementation, pData might be null for empty buf
    EXPECT_EQ(component.size(), 0u);
}

// Test findComponent returns nullptr for default component
TEST_F(CiffComponentTest_1781, FindComponentDefault_1781) {
    CiffComponent component;
    CiffComponent* found = component.findComponent(0x0805, 0x300a);
    // A plain CiffComponent (not a directory) won't contain sub-components
    // It might return itself if tag/dir match, or nullptr otherwise
    (void)found;
}

// Test findComponent on a component that matches its own tag/dir
TEST_F(CiffComponentTest_1781, FindComponentSelf_1781) {
    uint16_t tag = 0x0805;
    uint16_t dir = 0x300a;
    CiffComponent component(tag, dir);
    
    // tagId is tag & 0x3fff
    uint16_t crwTagId = tag & 0x3fff;
    CiffComponent* found = component.findComponent(crwTagId, dir);
    // The base implementation might return this component itself
    // or nullptr - depends on implementation
    (void)found;
}

// Test writeDirEntry
TEST_F(CiffComponentTest_1781, WriteDirEntry_1781) {
    CiffComponent component(0x0805, 0x0000);
    
    DataBuf buf(8);
    std::memset(buf.data(), 0x42, 8);
    component.setValue(std::move(buf));
    
    Blob blob;
    component.writeDirEntry(blob, littleEndian);
    
    // A directory entry typically has a fixed size (10 bytes: tag(2) + size(4) + offset(4))
    EXPECT_GT(blob.size(), 0u);
}

// Test write
TEST_F(CiffComponentTest_1781, Write_1781) {
    CiffComponent component(0x0805, 0x0000);
    
    DataBuf buf(4);
    std::memset(buf.data(), 0x01, 4);
    component.setValue(std::move(buf));
    
    Blob blob;
    size_t result = component.write(blob, littleEndian, 0);
    
    // write should return a value representing the new offset or bytes written
    (void)result;
}

// Test writeValueData
TEST_F(CiffComponentTest_1781, WriteValueData_1781) {
    CiffComponent component(0x0805, 0x0000);
    
    DataBuf buf(16);
    std::memset(buf.data(), 0xCC, 16);
    component.setValue(std::move(buf));
    
    Blob blob;
    size_t result = component.writeValueData(blob, 0);
    
    // Should return updated offset
    (void)result;
}

// Test copy constructor is deleted (compile-time check - just documenting)
// CiffComponent is non-copyable, non-assignable
// This is verified by the = delete declarations

// Test that multiple setDir calls work
TEST_F(CiffComponentTest_1781, SetDirMultiple_1781) {
    CiffComponent component;
    component.setDir(0x0001);
    EXPECT_EQ(component.dir(), 0x0001);
    component.setDir(0x0002);
    EXPECT_EQ(component.dir(), 0x0002);
    component.setDir(0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test boundary: max uint16_t values for tag and dir
TEST_F(CiffComponentTest_1781, BoundaryMaxValues_1781) {
    CiffComponent component(0xFFFF, 0xFFFF);
    EXPECT_EQ(component.tag(), 0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test boundary: zero values for tag and dir
TEST_F(CiffComponentTest_1781, BoundaryZeroValues_1781) {
    CiffComponent component(0x0000, 0x0000);
    EXPECT_EQ(component.tag(), 0x0000);
    EXPECT_EQ(component.dir(), 0x0000);
}

// Test setValue then print
TEST_F(CiffComponentTest_1781, SetValueThenPrint_1781) {
    CiffComponent component(0x0805, 0x300a);
    
    DataBuf buf(8);
    for (size_t i = 0; i < 8; ++i) {
        buf.data()[i] = static_cast<byte>(i);
    }
    component.setValue(std::move(buf));
    
    std::ostringstream oss;
    component.print(oss, littleEndian, "");
    // Just verify no crash and some output
    (void)oss.str();
}

// Test setValue replaces previous value
TEST_F(CiffComponentTest_1781, SetValueReplace_1781) {
    CiffComponent component(0x0805, 0x0000);
    
    DataBuf buf1(4);
    std::memset(buf1.data(), 0xAA, 4);
    component.setValue(std::move(buf1));
    EXPECT_EQ(component.size(), 4u);
    
    DataBuf buf2(8);
    std::memset(buf2.data(), 0xBB, 8);
    component.setValue(std::move(buf2));
    EXPECT_EQ(component.size(), 8u);
}

// Test empty after setValue with data
TEST_F(CiffComponentTest_1781, EmptyAfterSetValue_1781) {
    CiffComponent component;
    
    DataBuf buf(4);
    std::memset(buf.data(), 0x01, 4);
    component.setValue(std::move(buf));
    
    // After setting a value, component should not be empty
    // (Though this depends on the doEmpty implementation)
    bool result = component.empty();
    (void)result;
}

// Test that typeId and dataLocation are consistent between static and instance versions
TEST_F(CiffComponentTest_1781, TypeIdConsistency_1781) {
    for (uint16_t tag : {0x0000, 0x0805, 0x2000, 0x4000, 0x6000, 0x8000, 0xFFFF}) {
        CiffComponent component(tag, 0x0000);
        EXPECT_EQ(component.typeId(), CiffComponent::typeId(tag));
        EXPECT_EQ(component.dataLocation(), CiffComponent::dataLocation(tag));
    }
}
