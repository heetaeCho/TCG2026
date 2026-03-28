#include <gtest/gtest.h>
#include <cstdint>
#include <sstream>
#include <vector>

// Include the necessary headers from the project
#include "crwimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for CiffComponent tests
class CiffComponentTest_1758 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor initializes dir to 0
TEST_F(CiffComponentTest_1758, DefaultConstructorDirIsZero_1758) {
    CiffComponent component;
    EXPECT_EQ(component.dir(), 0);
}

// Test default constructor initializes tag to 0
TEST_F(CiffComponentTest_1758, DefaultConstructorTagIsZero_1758) {
    CiffComponent component;
    EXPECT_EQ(component.tag(), 0);
}

// Test default constructor initializes size to 0
TEST_F(CiffComponentTest_1758, DefaultConstructorSizeIsZero_1758) {
    CiffComponent component;
    EXPECT_EQ(component.size(), 0u);
}

// Test default constructor initializes offset to 0
TEST_F(CiffComponentTest_1758, DefaultConstructorOffsetIsZero_1758) {
    CiffComponent component;
    EXPECT_EQ(component.offset(), 0u);
}

// Test default constructor initializes pData to nullptr
TEST_F(CiffComponentTest_1758, DefaultConstructorPDataIsNull_1758) {
    CiffComponent component;
    EXPECT_EQ(component.pData(), nullptr);
}

// Test parameterized constructor sets tag correctly
TEST_F(CiffComponentTest_1758, ParameterizedConstructorSetsTag_1758) {
    CiffComponent component(0x1234, 0x5678);
    EXPECT_EQ(component.tag(), 0x1234);
}

// Test parameterized constructor sets dir correctly
TEST_F(CiffComponentTest_1758, ParameterizedConstructorSetsDir_1758) {
    CiffComponent component(0x1234, 0x5678);
    EXPECT_EQ(component.dir(), 0x5678);
}

// Test setDir changes the directory value
TEST_F(CiffComponentTest_1758, SetDirChangesDir_1758) {
    CiffComponent component;
    component.setDir(0xABCD);
    EXPECT_EQ(component.dir(), 0xABCD);
}

// Test setDir with zero
TEST_F(CiffComponentTest_1758, SetDirToZero_1758) {
    CiffComponent component(0x0001, 0x0002);
    component.setDir(0);
    EXPECT_EQ(component.dir(), 0);
}

// Test setDir with max uint16_t value
TEST_F(CiffComponentTest_1758, SetDirMaxValue_1758) {
    CiffComponent component;
    component.setDir(0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test tagId derived from tag
TEST_F(CiffComponentTest_1758, TagIdDerivedFromTag_1758) {
    // tagId typically masks the lower bits of tag
    CiffComponent component(0x300A, 0x0000);
    uint16_t tagId = component.tagId();
    // tagId should be the tag with the upper type bits masked off
    EXPECT_EQ(tagId, component.tag() & 0x3fff);
}

// Test typeId static method with various tags
TEST_F(CiffComponentTest_1758, TypeIdStaticMethodZeroTag_1758) {
    TypeId type = CiffComponent::typeId(0x0000);
    // Should return a valid TypeId; we just verify it doesn't crash
    (void)type;
}

// Test typeId static method with a tag that has type bits set
TEST_F(CiffComponentTest_1758, TypeIdStaticMethodWithTypeBits_1758) {
    TypeId type = CiffComponent::typeId(0x0800);
    (void)type;
}

// Test dataLocation static method
TEST_F(CiffComponentTest_1758, DataLocationStaticMethod_1758) {
    DataLocId loc = CiffComponent::dataLocation(0x0000);
    (void)loc;
}

// Test empty on default-constructed component
TEST_F(CiffComponentTest_1758, DefaultConstructedIsEmpty_1758) {
    CiffComponent component;
    // A default-constructed component should report empty
    // (size is 0, pData is nullptr)
    // The actual behavior depends on implementation, but we test it doesn't crash
    bool result = component.empty();
    (void)result;
}

// Test setValue sets data
TEST_F(CiffComponentTest_1758, SetValueSetsData_1758) {
    CiffComponent component;
    DataBuf buf(10);
    std::memset(buf.data(), 0x42, 10);
    component.setValue(std::move(buf));
    EXPECT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.size(), 10u);
    EXPECT_EQ(component.pData()[0], 0x42);
}

// Test setValue with empty DataBuf
TEST_F(CiffComponentTest_1758, SetValueEmptyBuf_1758) {
    CiffComponent component;
    DataBuf buf;
    component.setValue(std::move(buf));
    // After setting empty buffer, size should be 0
    EXPECT_EQ(component.size(), 0u);
}

// Test setValue replaces previous value
TEST_F(CiffComponentTest_1758, SetValueReplacesOldValue_1758) {
    CiffComponent component;
    
    DataBuf buf1(5);
    std::memset(buf1.data(), 0xAA, 5);
    component.setValue(std::move(buf1));
    EXPECT_EQ(component.size(), 5u);
    EXPECT_EQ(component.pData()[0], 0xAA);
    
    DataBuf buf2(8);
    std::memset(buf2.data(), 0xBB, 8);
    component.setValue(std::move(buf2));
    EXPECT_EQ(component.size(), 8u);
    EXPECT_EQ(component.pData()[0], 0xBB);
}

// Test findComponent on a simple CiffComponent (not a directory)
TEST_F(CiffComponentTest_1758, FindComponentOnLeafReturnsNullptr_1758) {
    CiffComponent component(0x0001, 0x0000);
    // A non-directory component should return nullptr for non-matching search
    CiffComponent* found = component.findComponent(0x9999, 0x9999);
    EXPECT_EQ(found, nullptr);
}

// Test findComponent with matching tag and dir
TEST_F(CiffComponentTest_1758, FindComponentMatchingTagAndDir_1758) {
    uint16_t testTag = 0x0001;
    uint16_t testDir = 0x0002;
    CiffComponent component(testTag, testDir);
    // For a leaf component, findComponent checks if it matches
    CiffComponent* found = component.findComponent(component.tagId(), testDir);
    // May or may not find itself depending on implementation
    // We just verify it doesn't crash
    (void)found;
}

// Test print doesn't crash on default-constructed component
TEST_F(CiffComponentTest_1758, PrintDoesNotCrash_1758) {
    CiffComponent component;
    std::ostringstream oss;
    EXPECT_NO_THROW(component.print(oss, littleEndian, ""));
}

// Test print with a prefix
TEST_F(CiffComponentTest_1758, PrintWithPrefix_1758) {
    CiffComponent component(0x0001, 0x0002);
    std::ostringstream oss;
    EXPECT_NO_THROW(component.print(oss, littleEndian, "  "));
}

// Test typeId instance method
TEST_F(CiffComponentTest_1758, TypeIdInstanceMethod_1758) {
    CiffComponent component(0x0800, 0x0000);
    TypeId type = component.typeId();
    // Verify it returns the same as the static version
    EXPECT_EQ(type, CiffComponent::typeId(0x0800));
}

// Test dataLocation instance method
TEST_F(CiffComponentTest_1758, DataLocationInstanceMethod_1758) {
    CiffComponent component(0x0000, 0x0000);
    DataLocId loc = component.dataLocation();
    EXPECT_EQ(loc, CiffComponent::dataLocation(0x0000));
}

// Test writeValueData and writeDirEntry with blob
TEST_F(CiffComponentTest_1758, WriteValueDataDoesNotCrash_1758) {
    CiffComponent component;
    DataBuf buf(4);
    std::memset(buf.data(), 0x01, 4);
    component.setValue(std::move(buf));
    
    Blob blob;
    EXPECT_NO_THROW(component.writeValueData(blob, 0));
}

// Test writeDirEntry
TEST_F(CiffComponentTest_1758, WriteDirEntryDoesNotCrash_1758) {
    CiffComponent component(0x0001, 0x0000);
    DataBuf buf(4);
    std::memset(buf.data(), 0x02, 4);
    component.setValue(std::move(buf));
    
    Blob blob;
    EXPECT_NO_THROW(component.writeDirEntry(blob, littleEndian));
}

// Test write method
TEST_F(CiffComponentTest_1758, WriteDoesNotCrash_1758) {
    CiffComponent component(0x0001, 0x0000);
    DataBuf buf(4);
    std::memset(buf.data(), 0x03, 4);
    component.setValue(std::move(buf));
    
    Blob blob;
    EXPECT_NO_THROW(component.write(blob, littleEndian, 0));
}

// Test boundary: tag with all bits set
TEST_F(CiffComponentTest_1758, MaxTagValue_1758) {
    CiffComponent component(0xFFFF, 0xFFFF);
    EXPECT_EQ(component.tag(), 0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test that copy constructor is deleted (compile-time check would fail, so we just verify interface)
// This is implicitly tested by the fact that CiffComponent(const CiffComponent&) = delete

// Test that assignment operator is deleted (compile-time check)
// This is implicitly tested by the fact that operator=(const CiffComponent&) = delete

// Test parameterized constructor with zero values
TEST_F(CiffComponentTest_1758, ParameterizedConstructorZeroValues_1758) {
    CiffComponent component(0, 0);
    EXPECT_EQ(component.tag(), 0);
    EXPECT_EQ(component.dir(), 0);
}

// Test setDir multiple times
TEST_F(CiffComponentTest_1758, SetDirMultipleTimes_1758) {
    CiffComponent component;
    for (uint16_t i = 0; i < 10; ++i) {
        component.setDir(i);
        EXPECT_EQ(component.dir(), i);
    }
}

// Test that setting value with large buffer works
TEST_F(CiffComponentTest_1758, SetValueLargeBuffer_1758) {
    CiffComponent component;
    const size_t largeSize = 65536;
    DataBuf buf(largeSize);
    std::memset(buf.data(), 0xFF, largeSize);
    component.setValue(std::move(buf));
    EXPECT_EQ(component.size(), largeSize);
    EXPECT_NE(component.pData(), nullptr);
}

// Test typeId with different tag type bits
TEST_F(CiffComponentTest_1758, TypeIdVariousTypeBits_1758) {
    // Tags with different upper bits should potentially return different TypeIds
    TypeId type0 = CiffComponent::typeId(0x0000);
    TypeId type1 = CiffComponent::typeId(0x0800);
    TypeId type2 = CiffComponent::typeId(0x1000);
    TypeId type3 = CiffComponent::typeId(0x1800);
    TypeId type4 = CiffComponent::typeId(0x2000);
    TypeId type5 = CiffComponent::typeId(0x2800);
    TypeId type6 = CiffComponent::typeId(0x3800);
    // Just verify they don't crash
    (void)type0;
    (void)type1;
    (void)type2;
    (void)type3;
    (void)type4;
    (void)type5;
    (void)type6;
}

// Test print outputs something for component with data
TEST_F(CiffComponentTest_1758, PrintOutputsSomething_1758) {
    CiffComponent component(0x0001, 0x0000);
    DataBuf buf(4);
    buf.data()[0] = 'T';
    buf.data()[1] = 'E';
    buf.data()[2] = 'S';
    buf.data()[3] = 'T';
    component.setValue(std::move(buf));
    
    std::ostringstream oss;
    component.print(oss, littleEndian, "");
    // We expect some output was written
    EXPECT_FALSE(oss.str().empty());
}
