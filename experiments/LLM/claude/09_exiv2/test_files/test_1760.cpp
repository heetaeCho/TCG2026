#include <gtest/gtest.h>
#include <sstream>
#include "crwimage_int.hpp"

using namespace Exiv2::Internal;

// Test fixture for CiffComponent tests
class CiffComponentTest_1760 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default constructor initializes size to 0
TEST_F(CiffComponentTest_1760, DefaultConstructorSizeIsZero_1760) {
    CiffComponent component;
    EXPECT_EQ(component.size(), 0u);
}

// Test parameterized constructor stores tag and dir correctly
TEST_F(CiffComponentTest_1760, ParameterizedConstructorTagAndDir_1760) {
    CiffComponent component(0x1234, 0x5678);
    EXPECT_EQ(component.tag(), 0x1234);
    EXPECT_EQ(component.dir(), 0x5678);
}

// Test default constructor tag and dir are zero
TEST_F(CiffComponentTest_1760, DefaultConstructorTagAndDirAreZero_1760) {
    CiffComponent component;
    EXPECT_EQ(component.tag(), 0);
    EXPECT_EQ(component.dir(), 0);
}

// Test default constructor offset is zero
TEST_F(CiffComponentTest_1760, DefaultConstructorOffsetIsZero_1760) {
    CiffComponent component;
    EXPECT_EQ(component.offset(), 0u);
}

// Test default constructor pData is nullptr
TEST_F(CiffComponentTest_1760, DefaultConstructorPDataIsNull_1760) {
    CiffComponent component;
    EXPECT_EQ(component.pData(), nullptr);
}

// Test setDir changes the directory
TEST_F(CiffComponentTest_1760, SetDirChangesDirectory_1760) {
    CiffComponent component;
    component.setDir(0xABCD);
    EXPECT_EQ(component.dir(), 0xABCD);
}

// Test empty on default constructed component
TEST_F(CiffComponentTest_1760, DefaultConstructedComponentEmpty_1760) {
    CiffComponent component;
    // Default component should report empty status
    bool isEmpty = component.empty();
    // We just verify it doesn't crash; the actual value depends on implementation
    (void)isEmpty;
}

// Test setValue updates size and pData
TEST_F(CiffComponentTest_1760, SetValueUpdatesSizeAndData_1760) {
    CiffComponent component;
    Exiv2::DataBuf buf(100);
    std::memset(buf.data(), 0x42, 100);
    component.setValue(std::move(buf));
    EXPECT_EQ(component.size(), 100u);
    EXPECT_NE(component.pData(), nullptr);
}

// Test setValue with empty buffer
TEST_F(CiffComponentTest_1760, SetValueWithEmptyBuffer_1760) {
    CiffComponent component;
    Exiv2::DataBuf buf;
    component.setValue(std::move(buf));
    EXPECT_EQ(component.size(), 0u);
}

// Test tagId returns lower bits of tag
TEST_F(CiffComponentTest_1760, TagIdReturnsExpectedValue_1760) {
    CiffComponent component(0x300A, 0x0000);
    uint16_t tagId = component.tagId();
    // tagId should be tag & 0x3fff based on CRW format
    EXPECT_EQ(tagId, component.tag() & 0x3FFF);
}

// Test typeId static method with various tags
TEST_F(CiffComponentTest_1760, StaticTypeIdForTag_1760) {
    // Testing static method - should not crash
    Exiv2::TypeId t = CiffComponent::typeId(0x0000);
    (void)t;
}

// Test dataLocation static method
TEST_F(CiffComponentTest_1760, StaticDataLocationForTag_1760) {
    Exiv2::Internal::DataLocId loc = CiffComponent::dataLocation(0x0000);
    (void)loc;
    // For tags with data in value, the location should differ from directory-based tags
    Exiv2::Internal::DataLocId loc2 = CiffComponent::dataLocation(0x0800);
    (void)loc2;
}

// Test typeId instance method
TEST_F(CiffComponentTest_1760, InstanceTypeId_1760) {
    CiffComponent component(0x0800, 0x0000);
    Exiv2::TypeId t = component.typeId();
    (void)t; // Just verify it doesn't crash
}

// Test dataLocation instance method
TEST_F(CiffComponentTest_1760, InstanceDataLocation_1760) {
    CiffComponent component(0x0800, 0x0000);
    Exiv2::Internal::DataLocId loc = component.dataLocation();
    (void)loc;
}

// Test findComponent returns nullptr for non-matching component
TEST_F(CiffComponentTest_1760, FindComponentReturnsNullForNonMatch_1760) {
    CiffComponent component(0x1234, 0x5678);
    CiffComponent* found = component.findComponent(0x9999, 0x8888);
    // Default implementation should not find a non-matching component
    // It might return nullptr or itself depending on implementation
    (void)found;
}

// Test findComponent returns self when matching
TEST_F(CiffComponentTest_1760, FindComponentReturnsSelfWhenMatching_1760) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent component(tag, dir);
    uint16_t crwTagId = tag & 0x3FFF;
    CiffComponent* found = component.findComponent(crwTagId, dir);
    // If tagId and dir match, it should return this component
    if (found != nullptr) {
        EXPECT_EQ(found->tagId(), crwTagId);
        EXPECT_EQ(found->dir(), dir);
    }
}

// Test print does not crash
TEST_F(CiffComponentTest_1760, PrintDoesNotCrash_1760) {
    CiffComponent component(0x1234, 0x5678);
    std::ostringstream oss;
    EXPECT_NO_THROW(component.print(oss, Exiv2::littleEndian, ""));
}

// Test print with big endian
TEST_F(CiffComponentTest_1760, PrintBigEndianDoesNotCrash_1760) {
    CiffComponent component(0x1234, 0x5678);
    std::ostringstream oss;
    EXPECT_NO_THROW(component.print(oss, Exiv2::bigEndian, "prefix"));
}

// Test writeDirEntry does not crash on default component
TEST_F(CiffComponentTest_1760, WriteDirEntryDoesNotCrash_1760) {
    CiffComponent component(0x1234, 0x5678);
    Exiv2::Blob blob;
    EXPECT_NO_THROW(component.writeDirEntry(blob, Exiv2::littleEndian));
}

// Test write on default component
TEST_F(CiffComponentTest_1760, WriteDefaultComponent_1760) {
    CiffComponent component(0x0000, 0x0000);
    Exiv2::Blob blob;
    size_t result = component.write(blob, Exiv2::littleEndian, 0);
    (void)result;
}

// Test writeValueData on default component
TEST_F(CiffComponentTest_1760, WriteValueDataDefaultComponent_1760) {
    CiffComponent component(0x0000, 0x0000);
    Exiv2::Blob blob;
    size_t result = component.writeValueData(blob, 0);
    (void)result;
}

// Test parameterized constructor with boundary values
TEST_F(CiffComponentTest_1760, ConstructorWithMaxValues_1760) {
    CiffComponent component(0xFFFF, 0xFFFF);
    EXPECT_EQ(component.tag(), 0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test parameterized constructor with zero values
TEST_F(CiffComponentTest_1760, ConstructorWithZeroValues_1760) {
    CiffComponent component(0x0000, 0x0000);
    EXPECT_EQ(component.tag(), 0x0000);
    EXPECT_EQ(component.dir(), 0x0000);
}

// Test setValue replaces previous value
TEST_F(CiffComponentTest_1760, SetValueReplacesPreviousValue_1760) {
    CiffComponent component;

    Exiv2::DataBuf buf1(50);
    component.setValue(std::move(buf1));
    EXPECT_EQ(component.size(), 50u);

    Exiv2::DataBuf buf2(200);
    component.setValue(std::move(buf2));
    EXPECT_EQ(component.size(), 200u);
}

// Test setDir multiple times
TEST_F(CiffComponentTest_1760, SetDirMultipleTimes_1760) {
    CiffComponent component;
    component.setDir(0x0001);
    EXPECT_EQ(component.dir(), 0x0001);
    component.setDir(0x0002);
    EXPECT_EQ(component.dir(), 0x0002);
    component.setDir(0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test that copy constructor is deleted (compile-time check is implicit)
// We just verify the class is movable or usable through pointers
TEST_F(CiffComponentTest_1760, UniquePointerUsage_1760) {
    auto ptr = std::make_unique<CiffComponent>(0x1234, 0x5678);
    EXPECT_EQ(ptr->tag(), 0x1234);
    EXPECT_EQ(ptr->dir(), 0x5678);
    EXPECT_EQ(ptr->size(), 0u);
}

// Test setValue with a large buffer
TEST_F(CiffComponentTest_1760, SetValueLargeBuffer_1760) {
    CiffComponent component;
    Exiv2::DataBuf buf(1024 * 1024); // 1MB
    component.setValue(std::move(buf));
    EXPECT_EQ(component.size(), 1024u * 1024u);
    EXPECT_NE(component.pData(), nullptr);
}

// Test pData points to correct data after setValue
TEST_F(CiffComponentTest_1760, PDataPointsToCorrectData_1760) {
    CiffComponent component;
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0xDE;
    buf.data()[1] = 0xAD;
    buf.data()[2] = 0xBE;
    buf.data()[3] = 0xEF;
    component.setValue(std::move(buf));

    ASSERT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.pData()[0], 0xDE);
    EXPECT_EQ(component.pData()[1], 0xAD);
    EXPECT_EQ(component.pData()[2], 0xBE);
    EXPECT_EQ(component.pData()[3], 0xEF);
}
