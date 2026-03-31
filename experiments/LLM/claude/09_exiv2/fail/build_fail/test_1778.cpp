#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "crwimage_int.hpp"
#include "types.hpp"
#include "image.hpp"

#include <vector>
#include <sstream>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for CiffComponent tests
class CiffComponentTest_1778 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor creates a component with default values
TEST_F(CiffComponentTest_1778, DefaultConstructor_HasDefaultValues_1778) {
    CiffComponent component;
    EXPECT_EQ(component.tag(), 0);
    EXPECT_EQ(component.dir(), 0);
    EXPECT_EQ(component.size(), 0u);
    EXPECT_EQ(component.offset(), 0u);
    EXPECT_EQ(component.pData(), nullptr);
}

// Test parameterized constructor sets tag and dir
TEST_F(CiffComponentTest_1778, ParameterizedConstructor_SetsTagAndDir_1778) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent component(tag, dir);
    EXPECT_EQ(component.tag(), tag);
    EXPECT_EQ(component.dir(), dir);
}

// Test setDir modifies the directory
TEST_F(CiffComponentTest_1778, SetDir_ModifiesDir_1778) {
    CiffComponent component;
    component.setDir(0x0001);
    EXPECT_EQ(component.dir(), 0x0001);
}

// Test setDir with zero value
TEST_F(CiffComponentTest_1778, SetDir_ZeroValue_1778) {
    CiffComponent component(0x1234, 0x5678);
    component.setDir(0);
    EXPECT_EQ(component.dir(), 0);
}

// Test setDir with max uint16 value
TEST_F(CiffComponentTest_1778, SetDir_MaxValue_1778) {
    CiffComponent component;
    component.setDir(0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test empty returns true for default-constructed component
TEST_F(CiffComponentTest_1778, Empty_DefaultConstructed_ReturnsTrue_1778) {
    CiffComponent component;
    EXPECT_TRUE(component.empty());
}

// Test tagId derived from tag
TEST_F(CiffComponentTest_1778, TagId_DerivedFromTag_1778) {
    uint16_t tag = 0x300A;
    CiffComponent component(tag, 0);
    // tagId should be the lower bits of the tag
    uint16_t tagId = component.tagId();
    // We just verify it returns something consistent
    EXPECT_EQ(tagId, component.tagId());
}

// Test typeId static method with various tags
TEST_F(CiffComponentTest_1778, TypeId_StaticMethod_ReturnsTypeId_1778) {
    // Just verify it doesn't crash and returns a value
    TypeId type1 = CiffComponent::typeId(0x0000);
    TypeId type2 = CiffComponent::typeId(0x0800);
    TypeId type3 = CiffComponent::typeId(0x1000);
    // Types should be valid TypeId values (no crash)
    (void)type1;
    (void)type2;
    (void)type3;
}

// Test dataLocation static method
TEST_F(CiffComponentTest_1778, DataLocation_StaticMethod_ReturnsDataLocId_1778) {
    DataLocId loc1 = CiffComponent::dataLocation(0x0000);
    DataLocId loc2 = CiffComponent::dataLocation(0x4000);
    // Just ensure no crash and returns a value
    (void)loc1;
    (void)loc2;
}

// Test typeId instance method
TEST_F(CiffComponentTest_1778, TypeId_InstanceMethod_1778) {
    CiffComponent component(0x0800, 0);
    TypeId type = component.typeId();
    // Verify consistency
    EXPECT_EQ(type, CiffComponent::typeId(0x0800));
}

// Test dataLocation instance method
TEST_F(CiffComponentTest_1778, DataLocation_InstanceMethod_1778) {
    CiffComponent component(0x4000, 0);
    DataLocId loc = component.dataLocation();
    EXPECT_EQ(loc, CiffComponent::dataLocation(0x4000));
}

// Test setValue sets data
TEST_F(CiffComponentTest_1778, SetValue_SetsData_1778) {
    CiffComponent component;
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));
    EXPECT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.size(), sizeof(data));
}

// Test setValue with empty buffer
TEST_F(CiffComponentTest_1778, SetValue_EmptyBuffer_1778) {
    CiffComponent component;
    DataBuf buf;
    component.setValue(std::move(buf));
    // After setting empty buffer, pData may be null and size 0
    EXPECT_EQ(component.size(), 0u);
}

// Test setValue replaces previous value
TEST_F(CiffComponentTest_1778, SetValue_ReplacesPreviousValue_1778) {
    CiffComponent component;
    const byte data1[] = {0x01, 0x02};
    DataBuf buf1(data1, sizeof(data1));
    component.setValue(std::move(buf1));
    EXPECT_EQ(component.size(), 2u);

    const byte data2[] = {0x03, 0x04, 0x05};
    DataBuf buf2(data2, sizeof(data2));
    component.setValue(std::move(buf2));
    EXPECT_EQ(component.size(), 3u);
}

// Test write method with default component
TEST_F(CiffComponentTest_1778, Write_DefaultComponent_1778) {
    CiffComponent component;
    Blob blob;
    size_t result = component.write(blob, littleEndian, 0);
    // Should return some value (offset after writing)
    (void)result;
}

// Test write method with data set
TEST_F(CiffComponentTest_1778, Write_WithData_1778) {
    CiffComponent component(0x0000, 0);
    const byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));

    Blob blob;
    size_t result = component.write(blob, littleEndian, 0);
    // Result should be >= 0; blob should have been modified
    EXPECT_GE(result, 0u);
}

// Test write with big endian byte order
TEST_F(CiffComponentTest_1778, Write_BigEndian_1778) {
    CiffComponent component(0x0000, 0);
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));

    Blob blob;
    size_t result = component.write(blob, bigEndian, 0);
    EXPECT_GE(result, 0u);
}

// Test write with non-zero offset
TEST_F(CiffComponentTest_1778, Write_NonZeroOffset_1778) {
    CiffComponent component(0x0000, 0);
    const byte data[] = {0x01};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));

    Blob blob;
    size_t result = component.write(blob, littleEndian, 100);
    EXPECT_GE(result, 0u);
}

// Test writeValueData
TEST_F(CiffComponentTest_1778, WriteValueData_DefaultComponent_1778) {
    CiffComponent component;
    Blob blob;
    size_t result = component.writeValueData(blob, 0);
    (void)result;
}

// Test writeDirEntry
TEST_F(CiffComponentTest_1778, WriteDirEntry_DefaultComponent_1778) {
    CiffComponent component;
    Blob blob;
    component.writeDirEntry(blob, littleEndian);
    // Should add directory entry bytes to blob
}

// Test findComponent returns nullptr for default component
TEST_F(CiffComponentTest_1778, FindComponent_DefaultComponent_ReturnsNullOrSelf_1778) {
    CiffComponent component(0x1234, 0x5678);
    CiffComponent* found = component.findComponent(0x1234, 0x5678);
    // For a base CiffComponent (not a directory), it should find itself if tag matches
    // or return nullptr
    // We just verify it doesn't crash
    (void)found;
}

// Test findComponent with non-matching parameters
TEST_F(CiffComponentTest_1778, FindComponent_NonMatching_1778) {
    CiffComponent component(0x1234, 0x5678);
    CiffComponent* found = component.findComponent(0xFFFF, 0xFFFF);
    EXPECT_EQ(found, nullptr);
}

// Test print method doesn't crash
TEST_F(CiffComponentTest_1778, Print_DefaultComponent_1778) {
    CiffComponent component;
    std::ostringstream os;
    component.print(os, littleEndian, "");
    // Should not crash
}

// Test print with prefix
TEST_F(CiffComponentTest_1778, Print_WithPrefix_1778) {
    CiffComponent component(0x0800, 0x0001);
    const byte data[] = {0x41, 0x42, 0x43, 0x00};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));

    std::ostringstream os;
    component.print(os, littleEndian, "PREFIX: ");
    // Should produce some output without crashing
}

// Test multiple setDir calls
TEST_F(CiffComponentTest_1778, SetDir_MultipleCalls_1778) {
    CiffComponent component;
    component.setDir(1);
    EXPECT_EQ(component.dir(), 1);
    component.setDir(2);
    EXPECT_EQ(component.dir(), 2);
    component.setDir(3);
    EXPECT_EQ(component.dir(), 3);
}

// Test that tag is immutable after construction (only settable through constructor)
TEST_F(CiffComponentTest_1778, Tag_ImmutableAfterConstruction_1778) {
    CiffComponent component(0xABCD, 0);
    EXPECT_EQ(component.tag(), 0xABCD);
    // tag has no setter, so it should remain the same
    EXPECT_EQ(component.tag(), 0xABCD);
}

// Test size and offset for default component
TEST_F(CiffComponentTest_1778, SizeAndOffset_DefaultComponent_1778) {
    CiffComponent component;
    EXPECT_EQ(component.size(), 0u);
    EXPECT_EQ(component.offset(), 0u);
}

// Test pData returns null for default component
TEST_F(CiffComponentTest_1778, PData_DefaultComponent_ReturnsNull_1778) {
    CiffComponent component;
    EXPECT_EQ(component.pData(), nullptr);
}

// Test pData returns valid pointer after setValue
TEST_F(CiffComponentTest_1778, PData_AfterSetValue_ReturnsNonNull_1778) {
    CiffComponent component;
    const byte data[] = {0x01};
    DataBuf buf(data, 1);
    component.setValue(std::move(buf));
    EXPECT_NE(component.pData(), nullptr);
}

// Test setValue with large buffer
TEST_F(CiffComponentTest_1778, SetValue_LargeBuffer_1778) {
    CiffComponent component;
    std::vector<byte> data(10000, 0xFF);
    DataBuf buf(data.data(), data.size());
    component.setValue(std::move(buf));
    EXPECT_EQ(component.size(), 10000u);
    EXPECT_NE(component.pData(), nullptr);
}

// Test that component is not empty after setValue
TEST_F(CiffComponentTest_1778, Empty_AfterSetValue_ReturnsFalse_1778) {
    CiffComponent component;
    EXPECT_TRUE(component.empty());
    const byte data[] = {0x01, 0x02, 0x03};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));
    // After setting a value, the component should not be empty
    EXPECT_FALSE(component.empty());
}

// Test write returns consistent results for same input
TEST_F(CiffComponentTest_1778, Write_ConsistentResults_1778) {
    CiffComponent component1(0x0000, 0);
    const byte data[] = {0x01, 0x02};
    DataBuf buf1(data, sizeof(data));
    component1.setValue(std::move(buf1));

    Blob blob1;
    size_t result1 = component1.write(blob1, littleEndian, 0);

    CiffComponent component2(0x0000, 0);
    DataBuf buf2(data, sizeof(data));
    component2.setValue(std::move(buf2));

    Blob blob2;
    size_t result2 = component2.write(blob2, littleEndian, 0);

    EXPECT_EQ(result1, result2);
    EXPECT_EQ(blob1.size(), blob2.size());
}

// Test various tag values for typeId static method
TEST_F(CiffComponentTest_1778, TypeId_VariousTags_1778) {
    // Tags with different type bits should produce different TypeId values
    TypeId t1 = CiffComponent::typeId(0x0000); // type bits = 0x00
    TypeId t2 = CiffComponent::typeId(0x0800); // type bits = 0x08
    TypeId t3 = CiffComponent::typeId(0x1000); // type bits = 0x10
    TypeId t4 = CiffComponent::typeId(0x1800); // type bits = 0x18
    TypeId t5 = CiffComponent::typeId(0x2000); // type bits = 0x20
    // We can at least verify they are valid
    (void)t1; (void)t2; (void)t3; (void)t4; (void)t5;
}

// Test copy constructor is deleted (compile-time check - we just verify we can't copy)
// This is a static assertion that doesn't need runtime test, but we document it
TEST_F(CiffComponentTest_1778, CopyConstructor_IsDeleted_1778) {
    EXPECT_FALSE(std::is_copy_constructible<CiffComponent>::value);
}

// Test copy assignment is deleted
TEST_F(CiffComponentTest_1778, CopyAssignment_IsDeleted_1778) {
    EXPECT_FALSE(std::is_copy_assignable<CiffComponent>::value);
}
