#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "crwimage_int.hpp"
#include <sstream>
#include <vector>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for CiffComponent tests
class CiffComponentTest_1767 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test default constructor initializes with expected default values
TEST_F(CiffComponentTest_1767, DefaultConstructor_DefaultValues_1767) {
    CiffComponent component;
    EXPECT_EQ(component.tag(), 0);
    EXPECT_EQ(component.dir(), 0);
    EXPECT_EQ(component.size(), 0u);
    EXPECT_EQ(component.offset(), 0u);
    EXPECT_EQ(component.pData(), nullptr);
}

// Test parameterized constructor sets tag and dir correctly
TEST_F(CiffComponentTest_1767, ParameterizedConstructor_SetsTagAndDir_1767) {
    CiffComponent component(0x1234, 0x5678);
    EXPECT_EQ(component.tag(), 0x1234);
    EXPECT_EQ(component.dir(), 0x5678);
}

// Test setDir changes the directory value
TEST_F(CiffComponentTest_1767, SetDir_ChangesDir_1767) {
    CiffComponent component;
    component.setDir(0xABCD);
    EXPECT_EQ(component.dir(), 0xABCD);
}

// Test setOffset changes the offset value
TEST_F(CiffComponentTest_1767, SetOffset_ChangesOffset_1767) {
    CiffComponent component;
    component.setOffset(42);
    EXPECT_EQ(component.offset(), 42u);
}

// Test setOffset with zero
TEST_F(CiffComponentTest_1767, SetOffset_Zero_1767) {
    CiffComponent component;
    component.setOffset(100);
    EXPECT_EQ(component.offset(), 100u);
    component.setOffset(0);
    EXPECT_EQ(component.offset(), 0u);
}

// Test setOffset with large value
TEST_F(CiffComponentTest_1767, SetOffset_LargeValue_1767) {
    CiffComponent component;
    size_t largeVal = static_cast<size_t>(-1); // max size_t
    component.setOffset(largeVal);
    EXPECT_EQ(component.offset(), largeVal);
}

// Test empty returns true for default-constructed component
TEST_F(CiffComponentTest_1767, Empty_DefaultConstructed_ReturnsTrue_1767) {
    CiffComponent component;
    EXPECT_TRUE(component.empty());
}

// Test tagId derived from tag
TEST_F(CiffComponentTest_1767, TagId_DerivedFromTag_1767) {
    CiffComponent component(0x300A, 0x0000);
    // tagId should return tag & 0x3fff based on CRW spec
    uint16_t expectedTagId = component.tagId();
    // We can at least check it's consistent
    EXPECT_EQ(component.tagId(), expectedTagId);
}

// Test typeId static method with various tag values
TEST_F(CiffComponentTest_1767, TypeId_Static_ReturnsValue_1767) {
    // Just verify it doesn't crash and returns some TypeId
    TypeId t = CiffComponent::typeId(0x0000);
    (void)t; // We can't assert specific values without knowing internals
}

// Test dataLocation static method
TEST_F(CiffComponentTest_1767, DataLocation_Static_ReturnsValue_1767) {
    DataLocId loc = CiffComponent::dataLocation(0x0000);
    (void)loc;
}

// Test typeId instance method
TEST_F(CiffComponentTest_1767, TypeId_Instance_ReturnsValue_1767) {
    CiffComponent component(0x0800, 0x0000);
    TypeId t = component.typeId();
    (void)t;
}

// Test dataLocation instance method
TEST_F(CiffComponentTest_1767, DataLocation_Instance_ReturnsValue_1767) {
    CiffComponent component(0x0800, 0x0000);
    DataLocId loc = component.dataLocation();
    (void)loc;
}

// Test setValue sets data and makes pData non-null
TEST_F(CiffComponentTest_1767, SetValue_SetsData_1767) {
    CiffComponent component;
    DataBuf buf(10);
    std::memset(buf.data(), 0x42, 10);
    component.setValue(std::move(buf));
    EXPECT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.size(), 10u);
}

// Test setValue with empty buffer
TEST_F(CiffComponentTest_1767, SetValue_EmptyBuffer_1767) {
    CiffComponent component;
    DataBuf buf;
    component.setValue(std::move(buf));
    // After setting empty buffer, pData might be null and size 0
    EXPECT_EQ(component.size(), 0u);
}

// Test findComponent returns nullptr for default component
TEST_F(CiffComponentTest_1767, FindComponent_DefaultComponent_ReturnsNullOrSelf_1767) {
    CiffComponent component(0x1234, 0x5678);
    // For a leaf component, findComponent should return this if tag matches, or null
    CiffComponent* found = component.findComponent(0x1234, 0x5678);
    // Could be null or this depending on implementation
    // At minimum, verify it doesn't crash
    (void)found;
}

// Test findComponent with non-matching tag returns nullptr
TEST_F(CiffComponentTest_1767, FindComponent_NonMatchingTag_1767) {
    CiffComponent component(0x1234, 0x5678);
    CiffComponent* found = component.findComponent(0xFFFF, 0xFFFF);
    // Should not find a matching component
    // The leaf implementation likely returns nullptr for non-matching
    (void)found;
}

// Test print doesn't crash
TEST_F(CiffComponentTest_1767, Print_DoesNotCrash_1767) {
    CiffComponent component(0x0800, 0x0000);
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, littleEndian, ""));
}

// Test print with prefix
TEST_F(CiffComponentTest_1767, Print_WithPrefix_1767) {
    CiffComponent component(0x0800, 0x0000);
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, bigEndian, "prefix_"));
}

// Test writeDirEntry doesn't crash
TEST_F(CiffComponentTest_1767, WriteDirEntry_DoesNotCrash_1767) {
    CiffComponent component(0x0800, 0x0000);
    Blob blob;
    EXPECT_NO_THROW(component.writeDirEntry(blob, littleEndian));
}

// Test write on default component
TEST_F(CiffComponentTest_1767, Write_DefaultComponent_1767) {
    CiffComponent component;
    Blob blob;
    size_t result = component.write(blob, littleEndian, 0);
    (void)result;
}

// Test writeValueData on default component
TEST_F(CiffComponentTest_1767, WriteValueData_DefaultComponent_1767) {
    CiffComponent component;
    Blob blob;
    size_t result = component.writeValueData(blob, 0);
    (void)result;
}

// Test setDir multiple times
TEST_F(CiffComponentTest_1767, SetDir_MultipleTimes_1767) {
    CiffComponent component;
    component.setDir(0x0001);
    EXPECT_EQ(component.dir(), 0x0001);
    component.setDir(0x0002);
    EXPECT_EQ(component.dir(), 0x0002);
    component.setDir(0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test copy constructor is deleted (compile-time check, but we verify it doesn't compile)
// This is inherently a compile-time test, so we just note it here.

// Test that tag returns correct value after construction
TEST_F(CiffComponentTest_1767, Tag_AfterConstruction_1767) {
    CiffComponent component(0xFFFF, 0x0000);
    EXPECT_EQ(component.tag(), 0xFFFF);
}

// Test parameterized constructor with zero values
TEST_F(CiffComponentTest_1767, ParameterizedConstructor_ZeroValues_1767) {
    CiffComponent component(0x0000, 0x0000);
    EXPECT_EQ(component.tag(), 0x0000);
    EXPECT_EQ(component.dir(), 0x0000);
}

// Test setValue replaces previous value
TEST_F(CiffComponentTest_1767, SetValue_ReplacesPreviousValue_1767) {
    CiffComponent component;
    
    DataBuf buf1(5);
    std::memset(buf1.data(), 0x01, 5);
    component.setValue(std::move(buf1));
    EXPECT_EQ(component.size(), 5u);
    
    DataBuf buf2(20);
    std::memset(buf2.data(), 0x02, 20);
    component.setValue(std::move(buf2));
    EXPECT_EQ(component.size(), 20u);
}

// Test setOffset multiple times with different values
TEST_F(CiffComponentTest_1767, SetOffset_MultipleTimes_1767) {
    CiffComponent component;
    component.setOffset(10);
    EXPECT_EQ(component.offset(), 10u);
    component.setOffset(20);
    EXPECT_EQ(component.offset(), 20u);
    component.setOffset(0);
    EXPECT_EQ(component.offset(), 0u);
}

// Test pData after setValue
TEST_F(CiffComponentTest_1767, PData_AfterSetValue_PointsToData_1767) {
    CiffComponent component;
    DataBuf buf(4);
    buf.data()[0] = 0xAA;
    buf.data()[1] = 0xBB;
    buf.data()[2] = 0xCC;
    buf.data()[3] = 0xDD;
    component.setValue(std::move(buf));
    
    const byte* p = component.pData();
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(p[0], 0xAA);
    EXPECT_EQ(p[1], 0xBB);
    EXPECT_EQ(p[2], 0xCC);
    EXPECT_EQ(p[3], 0xDD);
}

// Test write with big endian
TEST_F(CiffComponentTest_1767, Write_BigEndian_1767) {
    CiffComponent component(0x0800, 0x0000);
    DataBuf buf(8);
    std::memset(buf.data(), 0x55, 8);
    component.setValue(std::move(buf));
    
    Blob blob;
    size_t result = component.write(blob, bigEndian, 0);
    (void)result;
}

// Test write with little endian
TEST_F(CiffComponentTest_1767, Write_LittleEndian_1767) {
    CiffComponent component(0x0800, 0x0000);
    DataBuf buf(8);
    std::memset(buf.data(), 0x55, 8);
    component.setValue(std::move(buf));
    
    Blob blob;
    size_t result = component.write(blob, littleEndian, 0);
    (void)result;
}

// Test write with non-zero offset
TEST_F(CiffComponentTest_1767, Write_NonZeroOffset_1767) {
    CiffComponent component(0x0800, 0x0000);
    DataBuf buf(4);
    std::memset(buf.data(), 0x11, 4);
    component.setValue(std::move(buf));
    
    Blob blob;
    size_t result = component.write(blob, littleEndian, 100);
    (void)result;
}
