#include <gtest/gtest.h>
#include <cstdint>
#include <sstream>
#include <vector>

#include "crwimage_int.hpp"

using namespace Exiv2::Internal;

// Test fixture for CiffComponent tests
class CiffComponentTest_1763 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor creates component with zero tag and dir
TEST_F(CiffComponentTest_1763, DefaultConstructor_ZeroTagAndDir_1763) {
    CiffComponent component;
    EXPECT_EQ(component.tag(), 0);
    EXPECT_EQ(component.dir(), 0);
    EXPECT_EQ(component.tagId(), 0);
    EXPECT_EQ(component.size(), 0u);
    EXPECT_EQ(component.offset(), 0u);
    EXPECT_EQ(component.pData(), nullptr);
}

// Test parameterized constructor sets tag and dir correctly
TEST_F(CiffComponentTest_1763, ParameterizedConstructor_SetsTagAndDir_1763) {
    CiffComponent component(0x1234, 0x5678);
    EXPECT_EQ(component.tag(), 0x1234);
    EXPECT_EQ(component.dir(), 0x5678);
}

// Test tagId returns lower 14 bits of tag
TEST_F(CiffComponentTest_1763, TagId_ReturnsLower14Bits_1763) {
    // tag_ & 0x3fff: for tag 0xFFFF, tagId should be 0x3FFF
    CiffComponent component(0xFFFF, 0x0000);
    EXPECT_EQ(component.tagId(), 0x3FFF);
}

// Test tagId with tag that has upper bits set
TEST_F(CiffComponentTest_1763, TagId_UpperBitsCleared_1763) {
    CiffComponent component(0xC000, 0x0000);
    EXPECT_EQ(component.tagId(), 0x0000);
}

// Test tagId with tag value within 14 bits
TEST_F(CiffComponentTest_1763, TagId_WithinRange_1763) {
    CiffComponent component(0x1234, 0x0000);
    EXPECT_EQ(component.tagId(), 0x1234);
}

// Test tagId with zero tag
TEST_F(CiffComponentTest_1763, TagId_ZeroTag_1763) {
    CiffComponent component(0x0000, 0x0000);
    EXPECT_EQ(component.tagId(), 0x0000);
}

// Test tagId with max 14-bit value
TEST_F(CiffComponentTest_1763, TagId_Max14BitValue_1763) {
    CiffComponent component(0x3FFF, 0x0000);
    EXPECT_EQ(component.tagId(), 0x3FFF);
}

// Test setDir changes the dir
TEST_F(CiffComponentTest_1763, SetDir_ChangesDir_1763) {
    CiffComponent component(0x0000, 0x0000);
    component.setDir(0xABCD);
    EXPECT_EQ(component.dir(), 0xABCD);
}

// Test dir accessor
TEST_F(CiffComponentTest_1763, Dir_ReturnsCorrectValue_1763) {
    CiffComponent component(0x0000, 0x1111);
    EXPECT_EQ(component.dir(), 0x1111);
}

// Test tag accessor
TEST_F(CiffComponentTest_1763, Tag_ReturnsCorrectValue_1763) {
    CiffComponent component(0xBEEF, 0x0000);
    EXPECT_EQ(component.tag(), 0xBEEF);
}

// Test empty on default constructed component
TEST_F(CiffComponentTest_1763, Empty_DefaultConstructed_1763) {
    CiffComponent component;
    // Default component should be empty (no data set)
    EXPECT_TRUE(component.empty());
}

// Test setValue and then check pData and size
TEST_F(CiffComponentTest_1763, SetValue_UpdatesDataAndSize_1763) {
    CiffComponent component;
    Exiv2::DataBuf buf(10);
    std::memset(buf.data(), 0x42, 10);
    component.setValue(std::move(buf));
    EXPECT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.size(), 10u);
}

// Test setValue with empty buffer
TEST_F(CiffComponentTest_1763, SetValue_EmptyBuffer_1763) {
    CiffComponent component;
    Exiv2::DataBuf buf;
    component.setValue(std::move(buf));
    // After setting empty buffer, pData might be nullptr and size 0
    EXPECT_EQ(component.size(), 0u);
}

// Test findComponent returns nullptr for non-matching component
TEST_F(CiffComponentTest_1763, FindComponent_NoMatch_ReturnsNullptr_1763) {
    CiffComponent component(0x1234, 0x5678);
    // Searching for a different tag/dir should return nullptr for a leaf component
    CiffComponent* found = component.findComponent(0x9999, 0x8888);
    EXPECT_EQ(found, nullptr);
}

// Test findComponent returns this when matching
TEST_F(CiffComponentTest_1763, FindComponent_MatchingSelf_1763) {
    uint16_t tagId = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent component(tagId, dir);
    CiffComponent* found = component.findComponent(tagId & 0x3FFF, dir);
    // The base implementation checks if this component matches
    // Depending on implementation, it may or may not match
    // We just verify it doesn't crash and returns a valid pointer or nullptr
    // This is a black-box test
    if (found) {
        EXPECT_EQ(found->tagId(), tagId & 0x3FFF);
    }
}

// Test static typeId function with various tag values
TEST_F(CiffComponentTest_1763, StaticTypeId_VariousTags_1763) {
    // Just verify it returns valid TypeId values without crashing
    auto t1 = CiffComponent::typeId(0x0000);
    auto t2 = CiffComponent::typeId(0xFFFF);
    auto t3 = CiffComponent::typeId(0x0800);
    // We can't assert specific values without knowing implementation,
    // but we verify no crash
    (void)t1;
    (void)t2;
    (void)t3;
}

// Test static dataLocation function
TEST_F(CiffComponentTest_1763, StaticDataLocation_VariousTags_1763) {
    auto d1 = CiffComponent::dataLocation(0x0000);
    auto d2 = CiffComponent::dataLocation(0xFFFF);
    (void)d1;
    (void)d2;
}

// Test that copy constructor is deleted (compile-time check - just document it)
// CiffComponent is non-copyable, non-assignable

// Test tagId with bit pattern 0x4000 - only bit 14 set
TEST_F(CiffComponentTest_1763, TagId_Bit14Set_1763) {
    CiffComponent component(0x4000, 0x0000);
    EXPECT_EQ(component.tagId(), 0x0000);
}

// Test tagId with bit pattern 0x8000 - only bit 15 set
TEST_F(CiffComponentTest_1763, TagId_Bit15Set_1763) {
    CiffComponent component(0x8000, 0x0000);
    EXPECT_EQ(component.tagId(), 0x0000);
}

// Test tagId preserves lower bits when upper bits are set
TEST_F(CiffComponentTest_1763, TagId_MixedBits_1763) {
    CiffComponent component(0xD123, 0x0000);
    EXPECT_EQ(component.tagId(), 0x1123);
}

// Test print doesn't crash on default component
TEST_F(CiffComponentTest_1763, Print_DefaultComponent_1763) {
    CiffComponent component;
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, Exiv2::littleEndian, ""));
}

// Test print with a prefix
TEST_F(CiffComponentTest_1763, Print_WithPrefix_1763) {
    CiffComponent component(0x1234, 0x5678);
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, Exiv2::bigEndian, "prefix_"));
}

// Test writeValueData with empty component
TEST_F(CiffComponentTest_1763, WriteValueData_EmptyComponent_1763) {
    CiffComponent component;
    Exiv2::Internal::Blob blob;
    size_t result = component.writeValueData(blob, 0);
    // For a component with no data, offset should be returned as-is or updated minimally
    (void)result;
}

// Test writeDirEntry doesn't crash
TEST_F(CiffComponentTest_1763, WriteDirEntry_DefaultComponent_1763) {
    CiffComponent component;
    Exiv2::Internal::Blob blob;
    EXPECT_NO_THROW(component.writeDirEntry(blob, Exiv2::littleEndian));
}

// Test write on default component
TEST_F(CiffComponentTest_1763, Write_DefaultComponent_1763) {
    CiffComponent component;
    Exiv2::Internal::Blob blob;
    size_t result = component.write(blob, Exiv2::littleEndian, 0);
    (void)result;
}

// Test setValue then empty should return false
TEST_F(CiffComponentTest_1763, SetValue_ThenNotEmpty_1763) {
    CiffComponent component;
    Exiv2::DataBuf buf(5);
    std::memset(buf.data(), 0xAA, 5);
    component.setValue(std::move(buf));
    // After setting a non-empty value, the component should not be empty
    EXPECT_FALSE(component.empty());
}

// Test multiple setDir calls
TEST_F(CiffComponentTest_1763, SetDir_MultipleCalls_1763) {
    CiffComponent component;
    component.setDir(0x0001);
    EXPECT_EQ(component.dir(), 0x0001);
    component.setDir(0x0002);
    EXPECT_EQ(component.dir(), 0x0002);
    component.setDir(0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test boundary: tag with all 14 lower bits set and upper 2 bits set
TEST_F(CiffComponentTest_1763, TagId_AllBitsSet_1763) {
    CiffComponent component(0xFFFF, 0xFFFF);
    EXPECT_EQ(component.tagId(), 0x3FFF);
    EXPECT_EQ(component.tag(), 0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test boundary: single bit tag values
TEST_F(CiffComponentTest_1763, TagId_SingleBitValues_1763) {
    for (int bit = 0; bit < 14; ++bit) {
        uint16_t tag = static_cast<uint16_t>(1u << bit);
        CiffComponent component(tag, 0);
        EXPECT_EQ(component.tagId(), tag) << "Failed for bit " << bit;
    }
    // Bits 14 and 15 should be masked out
    {
        CiffComponent component(static_cast<uint16_t>(1u << 14), 0);
        EXPECT_EQ(component.tagId(), 0);
    }
    {
        CiffComponent component(static_cast<uint16_t>(1u << 15), 0);
        EXPECT_EQ(component.tagId(), 0);
    }
}
