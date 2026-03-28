#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "crwimage_int.hpp"
#include "image.hpp"
#include "types.hpp"

#include <sstream>
#include <vector>
#include <cstdint>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for CiffComponent tests
class CiffComponentTest_1787 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default construction
TEST_F(CiffComponentTest_1787, DefaultConstruction_1787) {
    CiffComponent component;
    EXPECT_EQ(component.tag(), 0);
    EXPECT_EQ(component.dir(), 0);
    EXPECT_EQ(component.size(), 0u);
    EXPECT_EQ(component.offset(), 0u);
    EXPECT_EQ(component.pData(), nullptr);
}

// Test parameterized construction
TEST_F(CiffComponentTest_1787, ParameterizedConstruction_1787) {
    uint16_t tag = 0x0805;
    uint16_t dir = 0x300a;
    CiffComponent component(tag, dir);
    EXPECT_EQ(component.tag(), tag);
    EXPECT_EQ(component.dir(), dir);
    EXPECT_EQ(component.size(), 0u);
    EXPECT_EQ(component.offset(), 0u);
    EXPECT_EQ(component.pData(), nullptr);
}

// Test setDir method
TEST_F(CiffComponentTest_1787, SetDir_1787) {
    CiffComponent component;
    component.setDir(0x1234);
    EXPECT_EQ(component.dir(), 0x1234);
}

// Test setDir with zero
TEST_F(CiffComponentTest_1787, SetDirZero_1787) {
    CiffComponent component(0x01, 0x02);
    component.setDir(0);
    EXPECT_EQ(component.dir(), 0);
}

// Test setDir with max value
TEST_F(CiffComponentTest_1787, SetDirMaxValue_1787) {
    CiffComponent component;
    component.setDir(0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test tag accessor
TEST_F(CiffComponentTest_1787, TagAccessor_1787) {
    CiffComponent component(0xABCD, 0x1234);
    EXPECT_EQ(component.tag(), 0xABCD);
}

// Test tagId - returns tag without the type bits
TEST_F(CiffComponentTest_1787, TagId_1787) {
    CiffComponent component(0x0805, 0x0000);
    uint16_t tagId = component.tagId();
    // tagId should mask out the upper bits (type info)
    EXPECT_EQ(tagId, component.tag() & 0x3fff);
}

// Test typeId static method with various tags
TEST_F(CiffComponentTest_1787, StaticTypeId_1787) {
    // Type is encoded in bits 13-14 of the tag
    TypeId type0 = CiffComponent::typeId(0x0000); // type bits = 0
    TypeId type1 = CiffComponent::typeId(0x0800); // type bits in the tag
    // Just verify it returns some valid TypeId without crashing
    (void)type0;
    (void)type1;
}

// Test typeId instance method
TEST_F(CiffComponentTest_1787, InstanceTypeId_1787) {
    CiffComponent component(0x0805, 0x0000);
    TypeId type = component.typeId();
    // Should be consistent with static version
    EXPECT_EQ(type, CiffComponent::typeId(0x0805));
}

// Test dataLocation static method
TEST_F(CiffComponentTest_1787, StaticDataLocation_1787) {
    DataLocId loc = CiffComponent::dataLocation(0x0000);
    // Just verify it returns without crashing
    (void)loc;
}

// Test dataLocation instance method
TEST_F(CiffComponentTest_1787, InstanceDataLocation_1787) {
    CiffComponent component(0x0805, 0x0000);
    DataLocId loc = component.dataLocation();
    EXPECT_EQ(loc, CiffComponent::dataLocation(0x0805));
}

// Test empty on default constructed component
TEST_F(CiffComponentTest_1787, EmptyDefault_1787) {
    CiffComponent component;
    // Default constructed component should report some state for empty
    bool isEmpty = component.empty();
    (void)isEmpty; // Just verify no crash
}

// Test setValue
TEST_F(CiffComponentTest_1787, SetValue_1787) {
    CiffComponent component;
    DataBuf buf(10);
    std::memset(buf.data(), 0x42, 10);
    component.setValue(std::move(buf));
    EXPECT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.size(), 10u);
}

// Test setValue with empty buffer
TEST_F(CiffComponentTest_1787, SetValueEmptyBuffer_1787) {
    CiffComponent component;
    DataBuf buf;
    component.setValue(std::move(buf));
    // After setting empty buffer
    EXPECT_EQ(component.size(), 0u);
}

// Test setValue replaces previous value
TEST_F(CiffComponentTest_1787, SetValueReplace_1787) {
    CiffComponent component;
    DataBuf buf1(5);
    std::memset(buf1.data(), 0x11, 5);
    component.setValue(std::move(buf1));
    EXPECT_EQ(component.size(), 5u);

    DataBuf buf2(20);
    std::memset(buf2.data(), 0x22, 20);
    component.setValue(std::move(buf2));
    EXPECT_EQ(component.size(), 20u);
}

// Test findComponent on base class returns nullptr for non-matching
TEST_F(CiffComponentTest_1787, FindComponentReturnsNull_1787) {
    CiffComponent component(0x0001, 0x0002);
    CiffComponent* found = component.findComponent(0x9999, 0x9999);
    EXPECT_EQ(found, nullptr);
}

// Test findComponent matching own tag and dir (base class behavior)
TEST_F(CiffComponentTest_1787, FindComponentBaseClass_1787) {
    CiffComponent component(0x0001, 0x0002);
    // The base doFindComponent returns nullptr by default
    CiffComponent* found = component.findComponent(0x0001, 0x0002);
    // Base class implementation returns nullptr
    EXPECT_EQ(found, nullptr);
}

// Test print does not crash
TEST_F(CiffComponentTest_1787, PrintDoesNotCrash_1787) {
    CiffComponent component(0x0805, 0x0000);
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, littleEndian, ""));
}

// Test print with prefix
TEST_F(CiffComponentTest_1787, PrintWithPrefix_1787) {
    CiffComponent component(0x0805, 0x0000);
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, bigEndian, "PREFIX: "));
}

// Test writeDirEntry does not crash
TEST_F(CiffComponentTest_1787, WriteDirEntryDoesNotCrash_1787) {
    CiffComponent component(0x0001, 0x0002);
    Blob blob;
    EXPECT_NO_THROW(component.writeDirEntry(blob, littleEndian));
}

// Test writeValueData
TEST_F(CiffComponentTest_1787, WriteValueData_1787) {
    CiffComponent component(0x0001, 0x0002);
    Blob blob;
    size_t result = component.writeValueData(blob, 0);
    // For an empty component, the offset returned should be sensible
    (void)result;
}

// Test copy constructor is deleted (compile-time check, not runtime)
// This is verified by the interface: CiffComponent(const CiffComponent&) = delete;

// Test assignment operator is deleted (compile-time check)
// This is verified by the interface: operator=(const CiffComponent&) = delete;

// Test construction with boundary tag values
TEST_F(CiffComponentTest_1787, BoundaryTagValues_1787) {
    CiffComponent comp1(0x0000, 0x0000);
    EXPECT_EQ(comp1.tag(), 0x0000);
    EXPECT_EQ(comp1.dir(), 0x0000);

    CiffComponent comp2(0xFFFF, 0xFFFF);
    EXPECT_EQ(comp2.tag(), 0xFFFF);
    EXPECT_EQ(comp2.dir(), 0xFFFF);
}

// Test multiple setDir calls
TEST_F(CiffComponentTest_1787, MultipleDirChanges_1787) {
    CiffComponent component;
    for (uint16_t i = 0; i < 100; ++i) {
        component.setDir(i);
        EXPECT_EQ(component.dir(), i);
    }
}

// Test that setValue with large buffer works
TEST_F(CiffComponentTest_1787, SetValueLargeBuffer_1787) {
    CiffComponent component;
    const size_t largeSize = 100000;
    DataBuf buf(largeSize);
    std::memset(buf.data(), 0xAA, largeSize);
    component.setValue(std::move(buf));
    EXPECT_EQ(component.size(), largeSize);
    EXPECT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.pData()[0], 0xAA);
    EXPECT_EQ(component.pData()[largeSize - 1], 0xAA);
}

// Test typeId with various tag type encodings
TEST_F(CiffComponentTest_1787, TypeIdVariousEncodings_1787) {
    // Tags with different type bits should produce potentially different TypeIds
    TypeId t1 = CiffComponent::typeId(0x0000);
    TypeId t2 = CiffComponent::typeId(0x2000);
    TypeId t3 = CiffComponent::typeId(0x4000);
    // We can't know exact values, but they should be valid
    (void)t1;
    (void)t2;
    (void)t3;
}

// Test write on default component
TEST_F(CiffComponentTest_1787, WriteDefaultComponent_1787) {
    CiffComponent component;
    Blob blob;
    size_t result = component.write(blob, littleEndian, 0);
    (void)result; // Just verify no crash
}

// Test write with big endian
TEST_F(CiffComponentTest_1787, WriteBigEndian_1787) {
    CiffComponent component(0x0001, 0x0002);
    DataBuf buf(4);
    std::memset(buf.data(), 0x55, 4);
    component.setValue(std::move(buf));
    Blob blob;
    size_t result = component.write(blob, bigEndian, 0);
    (void)result;
}

// Test add with UniquePtr
TEST_F(CiffComponentTest_1787, AddComponent_1787) {
    CiffComponent component;
    auto child = std::make_unique<CiffComponent>(0x0001, 0x0002);
    // Base class doAdd throws, so we expect an exception
    EXPECT_THROW(component.add(std::move(child)), Exiv2::Error);
}

// Test remove on base class (should throw)
TEST_F(CiffComponentTest_1787, RemoveOnBaseClass_1787) {
    CiffComponent component;
    CrwDirs dirs;
    EXPECT_THROW(component.remove(dirs, 0x0001), Exiv2::Error);
}
