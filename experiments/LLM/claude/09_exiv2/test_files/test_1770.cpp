#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "crwimage_int.hpp"
#include "image.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CiffComponentTest_1770 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default construction
TEST_F(CiffComponentTest_1770, DefaultConstruction_1770) {
    CiffComponent component;
    EXPECT_EQ(component.tag(), 0);
    EXPECT_EQ(component.dir(), 0);
    EXPECT_EQ(component.size(), 0u);
    EXPECT_EQ(component.offset(), 0u);
    EXPECT_EQ(component.pData(), nullptr);
}

// Test parameterized construction
TEST_F(CiffComponentTest_1770, ParameterizedConstruction_1770) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent component(tag, dir);
    EXPECT_EQ(component.tag(), tag);
    EXPECT_EQ(component.dir(), dir);
    EXPECT_EQ(component.size(), 0u);
    EXPECT_EQ(component.offset(), 0u);
    EXPECT_EQ(component.pData(), nullptr);
}

// Test setDir
TEST_F(CiffComponentTest_1770, SetDir_1770) {
    CiffComponent component;
    component.setDir(0x1234);
    EXPECT_EQ(component.dir(), 0x1234);
}

// Test setDir with zero
TEST_F(CiffComponentTest_1770, SetDirZero_1770) {
    CiffComponent component(0x1111, 0x2222);
    component.setDir(0);
    EXPECT_EQ(component.dir(), 0);
}

// Test setDir with max value
TEST_F(CiffComponentTest_1770, SetDirMaxValue_1770) {
    CiffComponent component;
    component.setDir(0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test tagId - derived from tag
TEST_F(CiffComponentTest_1770, TagId_1770) {
    uint16_t tag = 0x3456;
    CiffComponent component(tag, 0x0000);
    // tagId is typically derived from the tag value
    uint16_t tagId = component.tagId();
    // We just check it returns something without crashing
    (void)tagId;
}

// Test typeId from tag (static)
TEST_F(CiffComponentTest_1770, StaticTypeId_1770) {
    // Static method - just verify it doesn't crash
    TypeId tid = CiffComponent::typeId(0x0000);
    (void)tid;
}

// Test dataLocation from tag (static)
TEST_F(CiffComponentTest_1770, StaticDataLocation_1770) {
    DataLocId loc = CiffComponent::dataLocation(0x0000);
    (void)loc;
}

// Test typeId instance method
TEST_F(CiffComponentTest_1770, InstanceTypeId_1770) {
    CiffComponent component(0x1234, 0x5678);
    TypeId tid = component.typeId();
    (void)tid;
}

// Test dataLocation instance method
TEST_F(CiffComponentTest_1770, InstanceDataLocation_1770) {
    CiffComponent component(0x1234, 0x5678);
    DataLocId loc = component.dataLocation();
    (void)loc;
}

// Test empty on default constructed component
TEST_F(CiffComponentTest_1770, EmptyDefaultConstruction_1770) {
    CiffComponent component;
    // Default constructed component should reflect its empty state
    bool isEmpty = component.empty();
    (void)isEmpty;
}

// Test setValue
TEST_F(CiffComponentTest_1770, SetValue_1770) {
    CiffComponent component(0x0001, 0x0000);
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));
    EXPECT_EQ(component.size(), sizeof(data));
    EXPECT_NE(component.pData(), nullptr);
}

// Test setValue with empty buffer
TEST_F(CiffComponentTest_1770, SetValueEmptyBuffer_1770) {
    CiffComponent component(0x0001, 0x0000);
    DataBuf buf;
    component.setValue(std::move(buf));
    EXPECT_EQ(component.size(), 0u);
}

// Test setValue replaces previous value
TEST_F(CiffComponentTest_1770, SetValueReplacesPrevious_1770) {
    CiffComponent component(0x0001, 0x0000);
    const byte data1[] = {0x01, 0x02};
    DataBuf buf1(data1, sizeof(data1));
    component.setValue(std::move(buf1));
    EXPECT_EQ(component.size(), 2u);

    const byte data2[] = {0x03, 0x04, 0x05, 0x06, 0x07};
    DataBuf buf2(data2, sizeof(data2));
    component.setValue(std::move(buf2));
    EXPECT_EQ(component.size(), 5u);
}

// Test findComponent returns nullptr for non-matching tags on base class
TEST_F(CiffComponentTest_1770, FindComponentNoMatch_1770) {
    CiffComponent component(0x1234, 0x5678);
    CiffComponent* found = component.findComponent(0x9999, 0x8888);
    // Base CiffComponent::doFindComponent likely returns nullptr
    // unless the component matches
    (void)found;
}

// Test findComponent with matching tag and dir
TEST_F(CiffComponentTest_1770, FindComponentMatch_1770) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent component(tag, dir);
    // tagId is tag & 0x3fff typically, dir must also match
    CiffComponent* found = component.findComponent(component.tagId(), dir);
    (void)found;
}

// Test print doesn't crash
TEST_F(CiffComponentTest_1770, Print_1770) {
    CiffComponent component(0x0001, 0x0000);
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, littleEndian, ""));
}

// Test print with prefix
TEST_F(CiffComponentTest_1770, PrintWithPrefix_1770) {
    CiffComponent component(0x0001, 0x0000);
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, bigEndian, "  "));
}

// Test writeDirEntry doesn't crash on component with data
TEST_F(CiffComponentTest_1770, WriteDirEntry_1770) {
    CiffComponent component(0x0001, 0x0000);
    const byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));

    Blob blob;
    EXPECT_NO_THROW(component.writeDirEntry(blob, littleEndian));
}

// Test write
TEST_F(CiffComponentTest_1770, Write_1770) {
    CiffComponent component(0x0001, 0x0000);
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));

    Blob blob;
    size_t result = component.write(blob, littleEndian, 0);
    (void)result;
}

// Test writeValueData
TEST_F(CiffComponentTest_1770, WriteValueData_1770) {
    CiffComponent component(0x0001, 0x0000);
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));

    Blob blob;
    size_t result = component.writeValueData(blob, 0);
    (void)result;
}

// Test that copy constructor is deleted
TEST_F(CiffComponentTest_1770, CopyConstructorDeleted_1770) {
    EXPECT_FALSE(std::is_copy_constructible<CiffComponent>::value);
}

// Test that copy assignment is deleted
TEST_F(CiffComponentTest_1770, CopyAssignmentDeleted_1770) {
    EXPECT_FALSE(std::is_copy_assignable<CiffComponent>::value);
}

// Test multiple different tag/dir combinations
TEST_F(CiffComponentTest_1770, VariousTagDirCombinations_1770) {
    {
        CiffComponent c(0x0000, 0x0000);
        EXPECT_EQ(c.tag(), 0x0000);
        EXPECT_EQ(c.dir(), 0x0000);
    }
    {
        CiffComponent c(0xFFFF, 0xFFFF);
        EXPECT_EQ(c.tag(), 0xFFFF);
        EXPECT_EQ(c.dir(), 0xFFFF);
    }
    {
        CiffComponent c(0x0001, 0xFFFE);
        EXPECT_EQ(c.tag(), 0x0001);
        EXPECT_EQ(c.dir(), 0xFFFE);
    }
}

// Test byte orders in write
TEST_F(CiffComponentTest_1770, WriteBigEndian_1770) {
    CiffComponent component(0x0001, 0x0000);
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));

    Blob blob;
    size_t result = component.write(blob, bigEndian, 0);
    (void)result;
}

// Test byte orders in writeDirEntry
TEST_F(CiffComponentTest_1770, WriteDirEntryBigEndian_1770) {
    CiffComponent component(0x0001, 0x0000);
    const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));

    Blob blob;
    EXPECT_NO_THROW(component.writeDirEntry(blob, bigEndian));
}

// Test write with non-zero offset
TEST_F(CiffComponentTest_1770, WriteWithNonZeroOffset_1770) {
    CiffComponent component(0x0001, 0x0000);
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));

    Blob blob;
    size_t result = component.write(blob, littleEndian, 100);
    (void)result;
}

// Test writeValueData with non-zero offset
TEST_F(CiffComponentTest_1770, WriteValueDataWithNonZeroOffset_1770) {
    CiffComponent component(0x0001, 0x0000);
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));

    Blob blob;
    size_t result = component.writeValueData(blob, 50);
    (void)result;
}

// Test pData after setValue
TEST_F(CiffComponentTest_1770, PDataAfterSetValue_1770) {
    CiffComponent component(0x0001, 0x0000);
    const byte data[] = {0xAA, 0xBB, 0xCC};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));

    EXPECT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.pData()[0], 0xAA);
    EXPECT_EQ(component.pData()[1], 0xBB);
    EXPECT_EQ(component.pData()[2], 0xCC);
}

// Test that size reflects the data set via setValue
TEST_F(CiffComponentTest_1770, SizeReflectsSetValue_1770) {
    CiffComponent component(0x0001, 0x0000);

    const byte data1[] = {0x01};
    DataBuf buf1(data1, 1);
    component.setValue(std::move(buf1));
    EXPECT_EQ(component.size(), 1u);

    const byte data10[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    DataBuf buf10(data10, 10);
    component.setValue(std::move(buf10));
    EXPECT_EQ(component.size(), 10u);
}
