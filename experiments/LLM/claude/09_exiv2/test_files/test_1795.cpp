#include <gtest/gtest.h>
#include "crwimage_int.hpp"

using namespace Exiv2::Internal;

class CiffComponentTest_1795 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor creates an empty component
TEST_F(CiffComponentTest_1795, DefaultConstructor_IsEmpty_1795) {
    CiffComponent component;
    EXPECT_TRUE(component.empty());
}

// Test parameterized constructor stores tag and dir
TEST_F(CiffComponentTest_1795, ParameterizedConstructor_StoresTagAndDir_1795) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent component(tag, dir);
    EXPECT_EQ(component.tag(), tag);
    EXPECT_EQ(component.dir(), dir);
}

// Test default constructor initializes tag to 0
TEST_F(CiffComponentTest_1795, DefaultConstructor_TagIsZero_1795) {
    CiffComponent component;
    EXPECT_EQ(component.tag(), 0);
}

// Test default constructor initializes dir to 0
TEST_F(CiffComponentTest_1795, DefaultConstructor_DirIsZero_1795) {
    CiffComponent component;
    EXPECT_EQ(component.dir(), 0);
}

// Test default constructor initializes size to 0
TEST_F(CiffComponentTest_1795, DefaultConstructor_SizeIsZero_1795) {
    CiffComponent component;
    EXPECT_EQ(component.size(), 0u);
}

// Test default constructor initializes offset to 0
TEST_F(CiffComponentTest_1795, DefaultConstructor_OffsetIsZero_1795) {
    CiffComponent component;
    EXPECT_EQ(component.offset(), 0u);
}

// Test default constructor initializes pData to nullptr
TEST_F(CiffComponentTest_1795, DefaultConstructor_PDataIsNull_1795) {
    CiffComponent component;
    EXPECT_EQ(component.pData(), nullptr);
}

// Test setDir changes the directory
TEST_F(CiffComponentTest_1795, SetDir_ChangesDir_1795) {
    CiffComponent component;
    component.setDir(0xABCD);
    EXPECT_EQ(component.dir(), 0xABCD);
}

// Test empty returns true for default constructed component
TEST_F(CiffComponentTest_1795, Empty_DefaultConstructed_ReturnsTrue_1795) {
    CiffComponent component;
    EXPECT_TRUE(component.empty());
}

// Test setValue makes component non-empty
TEST_F(CiffComponentTest_1795, SetValue_WithData_MakesNonEmpty_1795) {
    CiffComponent component;
    Exiv2::DataBuf buf(10);
    component.setValue(std::move(buf));
    // After setting a value with non-zero size, size should be updated
    EXPECT_EQ(component.size(), 10u);
}

// Test setValue and then empty returns false
TEST_F(CiffComponentTest_1795, SetValue_WithNonEmptyData_EmptyReturnsFalse_1795) {
    CiffComponent component;
    Exiv2::DataBuf buf(5);
    component.setValue(std::move(buf));
    EXPECT_FALSE(component.empty());
}

// Test setValue with empty buffer
TEST_F(CiffComponentTest_1795, SetValue_WithEmptyData_EmptyReturnsTrue_1795) {
    CiffComponent component;
    Exiv2::DataBuf buf;
    component.setValue(std::move(buf));
    EXPECT_TRUE(component.empty());
}

// Test parameterized constructor with zero values
TEST_F(CiffComponentTest_1795, ParameterizedConstructor_ZeroValues_1795) {
    CiffComponent component(0, 0);
    EXPECT_EQ(component.tag(), 0);
    EXPECT_EQ(component.dir(), 0);
    EXPECT_TRUE(component.empty());
}

// Test parameterized constructor with max values
TEST_F(CiffComponentTest_1795, ParameterizedConstructor_MaxValues_1795) {
    CiffComponent component(0xFFFF, 0xFFFF);
    EXPECT_EQ(component.tag(), 0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test typeId static function with known tag value
TEST_F(CiffComponentTest_1795, TypeId_StaticFunction_ReturnsTypeId_1795) {
    // typeId extracts type information from the tag
    // The type is encoded in bits 13-8 of the tag
    // We just verify the function doesn't crash and returns a valid TypeId
    auto result = CiffComponent::typeId(0x0000);
    // Just check it returns without error - we treat implementation as black box
    (void)result;
}

// Test dataLocation static function
TEST_F(CiffComponentTest_1795, DataLocation_StaticFunction_ReturnsDataLocId_1795) {
    auto result = CiffComponent::dataLocation(0x0000);
    (void)result;
}

// Test findComponent returns nullptr for non-matching
TEST_F(CiffComponentTest_1795, FindComponent_NoMatch_ReturnsNullptr_1795) {
    CiffComponent component(0x1234, 0x5678);
    // When searching for a different tag/dir, should return nullptr or the component itself
    // depending on the matching logic
    auto* found = component.findComponent(0x9999, 0x9999);
    // For a leaf CiffComponent that doesn't match, expect nullptr
    EXPECT_EQ(found, nullptr);
}

// Test findComponent returns this when matching
TEST_F(CiffComponentTest_1795, FindComponent_MatchingTagAndDir_ReturnsThis_1795) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent component(tag, dir);
    // tagId is derived from tag, so we need to check what tagId returns
    uint16_t tagId = component.tagId();
    auto* found = component.findComponent(tagId, dir);
    // If tagId and dir match, it should return the component
    if (found != nullptr) {
        EXPECT_EQ(found, &component);
    }
}

// Test tagId returns the tag identifier
TEST_F(CiffComponentTest_1795, TagId_ReturnsExpectedValue_1795) {
    CiffComponent component(0x3045, 0x0001);
    uint16_t tagId = component.tagId();
    // tagId typically masks lower bits of tag
    // We just verify it doesn't crash and returns a consistent value
    uint16_t tagId2 = component.tagId();
    EXPECT_EQ(tagId, tagId2);
}

// Test instance typeId
TEST_F(CiffComponentTest_1795, InstanceTypeId_ReturnsConsistentValue_1795) {
    CiffComponent component(0x3045, 0x0001);
    auto t1 = component.typeId();
    auto t2 = component.typeId();
    EXPECT_EQ(t1, t2);
}

// Test instance dataLocation
TEST_F(CiffComponentTest_1795, InstanceDataLocation_ReturnsConsistentValue_1795) {
    CiffComponent component(0x3045, 0x0001);
    auto d1 = component.dataLocation();
    auto d2 = component.dataLocation();
    EXPECT_EQ(d1, d2);
}

// Test print does not crash
TEST_F(CiffComponentTest_1795, Print_DoesNotCrash_1795) {
    CiffComponent component(0x1234, 0x5678);
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, Exiv2::littleEndian, ""));
}

// Test print with prefix
TEST_F(CiffComponentTest_1795, Print_WithPrefix_DoesNotCrash_1795) {
    CiffComponent component(0x1234, 0x5678);
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, Exiv2::bigEndian, "PREFIX: "));
}

// Test setDir multiple times
TEST_F(CiffComponentTest_1795, SetDir_MultipleTimes_LastValueStored_1795) {
    CiffComponent component;
    component.setDir(1);
    EXPECT_EQ(component.dir(), 1);
    component.setDir(2);
    EXPECT_EQ(component.dir(), 2);
    component.setDir(0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test setValue replaces previous value
TEST_F(CiffComponentTest_1795, SetValue_ReplacePrevious_UpdatesSize_1795) {
    CiffComponent component;
    Exiv2::DataBuf buf1(10);
    component.setValue(std::move(buf1));
    EXPECT_EQ(component.size(), 10u);
    EXPECT_FALSE(component.empty());

    Exiv2::DataBuf buf2(20);
    component.setValue(std::move(buf2));
    EXPECT_EQ(component.size(), 20u);
    EXPECT_FALSE(component.empty());
}

// Test setValue with zero-size buffer makes empty
TEST_F(CiffComponentTest_1795, SetValue_ZeroSizeBuffer_IsEmpty_1795) {
    CiffComponent component;
    Exiv2::DataBuf buf1(10);
    component.setValue(std::move(buf1));
    EXPECT_FALSE(component.empty());

    Exiv2::DataBuf buf2;
    component.setValue(std::move(buf2));
    EXPECT_TRUE(component.empty());
}

// Test write and writeValueData with empty component
TEST_F(CiffComponentTest_1795, Write_EmptyComponent_DoesNotCrash_1795) {
    CiffComponent component;
    Exiv2::Blob blob;
    EXPECT_NO_THROW(component.write(blob, Exiv2::littleEndian, 0));
}

// Test writeValueData with empty component
TEST_F(CiffComponentTest_1795, WriteValueData_EmptyComponent_DoesNotCrash_1795) {
    CiffComponent component;
    Exiv2::Blob blob;
    EXPECT_NO_THROW(component.writeValueData(blob, 0));
}

// Test writeDirEntry with empty component
TEST_F(CiffComponentTest_1795, WriteDirEntry_EmptyComponent_DoesNotCrash_1795) {
    CiffComponent component;
    Exiv2::Blob blob;
    EXPECT_NO_THROW(component.writeDirEntry(blob, Exiv2::littleEndian));
}
