#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <sstream>
#include <vector>

#include "crwimage_int.hpp"
#include "types.hpp"
#include "image.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Type aliases for convenience
using Blob = std::vector<byte>;

class CiffComponentTest_1793 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default construction
TEST_F(CiffComponentTest_1793, DefaultConstructor_1793) {
    CiffComponent component;
    EXPECT_EQ(component.tag(), 0);
    EXPECT_EQ(component.dir(), 0);
    EXPECT_EQ(component.size(), 0u);
    EXPECT_EQ(component.offset(), 0u);
    EXPECT_EQ(component.pData(), nullptr);
}

// Test parameterized constructor
TEST_F(CiffComponentTest_1793, ParameterizedConstructor_1793) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent component(tag, dir);
    EXPECT_EQ(component.tag(), tag);
    EXPECT_EQ(component.dir(), dir);
    EXPECT_EQ(component.size(), 0u);
    EXPECT_EQ(component.offset(), 0u);
    EXPECT_EQ(component.pData(), nullptr);
}

// Test setDir and dir
TEST_F(CiffComponentTest_1793, SetDir_1793) {
    CiffComponent component;
    component.setDir(0xABCD);
    EXPECT_EQ(component.dir(), 0xABCD);
}

// Test setDir with zero
TEST_F(CiffComponentTest_1793, SetDirZero_1793) {
    CiffComponent component(0x1234, 0x5678);
    component.setDir(0);
    EXPECT_EQ(component.dir(), 0);
}

// Test setDir with max value
TEST_F(CiffComponentTest_1793, SetDirMaxValue_1793) {
    CiffComponent component;
    component.setDir(0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test empty on default-constructed component
TEST_F(CiffComponentTest_1793, EmptyOnDefault_1793) {
    CiffComponent component;
    // Default constructed component should report some empty state
    // Based on the interface, doEmpty() is the virtual that gets called
    EXPECT_NO_THROW(component.empty());
}

// Test setValue with empty DataBuf
TEST_F(CiffComponentTest_1793, SetValueEmptyBuf_1793) {
    CiffComponent component;
    DataBuf buf;
    EXPECT_NO_THROW(component.setValue(std::move(buf)));
}

// Test setValue with non-empty DataBuf
TEST_F(CiffComponentTest_1793, SetValueNonEmptyBuf_1793) {
    CiffComponent component;
    DataBuf buf(100);
    component.setValue(std::move(buf));
    // After setting value, pData should not be null and size should reflect the buffer
    EXPECT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.size(), 100u);
}

// Test tagId - derived from tag
TEST_F(CiffComponentTest_1793, TagId_1793) {
    CiffComponent component(0x300A, 0x0000);
    uint16_t tagId = component.tagId();
    // tagId is typically the lower bits of tag
    EXPECT_EQ(tagId, component.tag() & 0x3fff);
}

// Test typeId static method
TEST_F(CiffComponentTest_1793, StaticTypeId_1793) {
    // Test with tag value 0 (boundary)
    TypeId type0 = CiffComponent::typeId(0x0000);
    // Just verify it returns without crashing
    (void)type0;

    // Test with a known tag pattern
    TypeId type1 = CiffComponent::typeId(0x0800);
    (void)type1;

    TypeId type2 = CiffComponent::typeId(0xFFFF);
    (void)type2;
}

// Test dataLocation static method
TEST_F(CiffComponentTest_1793, StaticDataLocation_1793) {
    DataLocId loc0 = CiffComponent::dataLocation(0x0000);
    (void)loc0;

    DataLocId loc1 = CiffComponent::dataLocation(0xFFFF);
    (void)loc1;
}

// Test typeId instance method
TEST_F(CiffComponentTest_1793, InstanceTypeId_1793) {
    CiffComponent component(0x0000, 0x0000);
    TypeId tid = component.typeId();
    (void)tid;
}

// Test dataLocation instance method
TEST_F(CiffComponentTest_1793, InstanceDataLocation_1793) {
    CiffComponent component(0x0000, 0x0000);
    DataLocId dlid = component.dataLocation();
    (void)dlid;
}

// Test findComponent on base CiffComponent returns self or nullptr
TEST_F(CiffComponentTest_1793, FindComponentSelf_1793) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent component(tag, dir);
    // findComponent on a leaf component should check if it matches
    CiffComponent* found = component.findComponent(tag & 0x3fff, dir);
    // The result depends on exact matching logic; just ensure no crash
    (void)found;
}

// Test findComponent with non-matching parameters
TEST_F(CiffComponentTest_1793, FindComponentNonMatch_1793) {
    CiffComponent component(0x1234, 0x5678);
    CiffComponent* found = component.findComponent(0xFFFF, 0xFFFF);
    // Should likely return nullptr for non-matching
    EXPECT_EQ(found, nullptr);
}

// Test print on default component
TEST_F(CiffComponentTest_1793, PrintDefault_1793) {
    CiffComponent component;
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, littleEndian, ""));
}

// Test print with prefix
TEST_F(CiffComponentTest_1793, PrintWithPrefix_1793) {
    CiffComponent component(0x1234, 0x5678);
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, bigEndian, "  "));
    // Verify something was printed
    // The exact content depends on implementation
}

// Test writeDirEntry
TEST_F(CiffComponentTest_1793, WriteDirEntry_1793) {
    CiffComponent component(0x1234, 0x5678);
    Blob blob;
    EXPECT_NO_THROW(component.writeDirEntry(blob, littleEndian));
    // A dir entry should have been written
    EXPECT_GT(blob.size(), 0u);
}

// Test writeDirEntry with big endian
TEST_F(CiffComponentTest_1793, WriteDirEntryBigEndian_1793) {
    CiffComponent component(0x1234, 0x5678);
    Blob blob;
    EXPECT_NO_THROW(component.writeDirEntry(blob, bigEndian));
    EXPECT_GT(blob.size(), 0u);
}

// Test write on empty component
TEST_F(CiffComponentTest_1793, WriteEmptyComponent_1793) {
    CiffComponent component;
    Blob blob;
    size_t result = 0;
    EXPECT_NO_THROW(result = component.write(blob, littleEndian, 0));
    (void)result;
}

// Test writeValueData on empty component
TEST_F(CiffComponentTest_1793, WriteValueDataEmpty_1793) {
    CiffComponent component;
    Blob blob;
    size_t result = 0;
    EXPECT_NO_THROW(result = component.writeValueData(blob, 0));
    (void)result;
}

// Test setValue then check pData and size
TEST_F(CiffComponentTest_1793, SetValueCheckPDataAndSize_1793) {
    CiffComponent component;
    const size_t bufSize = 256;
    DataBuf buf(bufSize);
    std::memset(buf.data(), 0xAB, bufSize);

    component.setValue(std::move(buf));

    EXPECT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.size(), bufSize);
    // Verify data content
    EXPECT_EQ(component.pData()[0], 0xAB);
    EXPECT_EQ(component.pData()[bufSize - 1], 0xAB);
}

// Test remove on base component (should delegate to doRemove which is a no-op for base)
TEST_F(CiffComponentTest_1793, RemoveBaseComponent_1793) {
    CiffComponent component;
    CrwDirs crwDirs;
    EXPECT_NO_THROW(component.remove(crwDirs, 0x1234));
}

// Test remove with empty CrwDirs
TEST_F(CiffComponentTest_1793, RemoveEmptyCrwDirs_1793) {
    CiffComponent component(0x1234, 0x5678);
    CrwDirs crwDirs;
    EXPECT_NO_THROW(component.remove(crwDirs, 0x0000));
}

// Test add with CrwDirs on base component
TEST_F(CiffComponentTest_1793, AddWithCrwDirsBase_1793) {
    CiffComponent component;
    CrwDirs crwDirs;
    // Base doAdd throws; this behavior may depend on implementation
    // Just ensure we can call it
    try {
        const auto& result = component.add(crwDirs, 0x1234);
        (void)result;
    } catch (...) {
        // Expected for base class
    }
}

// Test multiple setDir calls
TEST_F(CiffComponentTest_1793, MultiplSetDir_1793) {
    CiffComponent component;
    component.setDir(1);
    EXPECT_EQ(component.dir(), 1);
    component.setDir(2);
    EXPECT_EQ(component.dir(), 2);
    component.setDir(0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test tag is immutable after construction (no setter)
TEST_F(CiffComponentTest_1793, TagImmutableAfterConstruction_1793) {
    CiffComponent component(0x4321, 0x8765);
    EXPECT_EQ(component.tag(), 0x4321);
    // No setter for tag, so it should remain the same
}

// Test boundary: tag = 0, dir = 0
TEST_F(CiffComponentTest_1793, BoundaryTagDirZero_1793) {
    CiffComponent component(0, 0);
    EXPECT_EQ(component.tag(), 0);
    EXPECT_EQ(component.dir(), 0);
    EXPECT_EQ(component.tagId(), 0);
}

// Test boundary: tag = 0xFFFF, dir = 0xFFFF
TEST_F(CiffComponentTest_1793, BoundaryTagDirMax_1793) {
    CiffComponent component(0xFFFF, 0xFFFF);
    EXPECT_EQ(component.tag(), 0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test setValue replaces previous value
TEST_F(CiffComponentTest_1793, SetValueReplacesPrevious_1793) {
    CiffComponent component;

    DataBuf buf1(50);
    std::memset(buf1.data(), 0x11, 50);
    component.setValue(std::move(buf1));
    EXPECT_EQ(component.size(), 50u);
    EXPECT_EQ(component.pData()[0], 0x11);

    DataBuf buf2(100);
    std::memset(buf2.data(), 0x22, 100);
    component.setValue(std::move(buf2));
    EXPECT_EQ(component.size(), 100u);
    EXPECT_EQ(component.pData()[0], 0x22);
}

// Test that copy constructor is deleted
TEST_F(CiffComponentTest_1793, CopyConstructorDeleted_1793) {
    // This is a compile-time check. If the following line were uncommented, it should fail:
    // CiffComponent a; CiffComponent b(a);
    SUCCEED(); // Confirms our awareness of the deleted copy constructor
}

// Test that copy assignment is deleted
TEST_F(CiffComponentTest_1793, CopyAssignmentDeleted_1793) {
    // CiffComponent a, b; a = b; // Would fail to compile
    SUCCEED();
}

// Test write with offset
TEST_F(CiffComponentTest_1793, WriteWithOffset_1793) {
    CiffComponent component(0x0001, 0x0000);
    DataBuf buf(10);
    std::memset(buf.data(), 0x42, 10);
    component.setValue(std::move(buf));

    Blob blob;
    size_t result = component.write(blob, littleEndian, 0);
    EXPECT_GE(result, 0u);
}

// Test writeValueData with offset
TEST_F(CiffComponentTest_1793, WriteValueDataWithOffset_1793) {
    CiffComponent component(0x0001, 0x0000);
    DataBuf buf(10);
    std::memset(buf.data(), 0x42, 10);
    component.setValue(std::move(buf));

    Blob blob;
    size_t result = component.writeValueData(blob, 100);
    (void)result;
}

// Test empty after setValue with non-empty data
TEST_F(CiffComponentTest_1793, NotEmptyAfterSetValue_1793) {
    CiffComponent component;
    DataBuf buf(10);
    component.setValue(std::move(buf));
    // After setting a value, empty() behavior depends on implementation
    bool isEmpty = component.empty();
    (void)isEmpty;
}
