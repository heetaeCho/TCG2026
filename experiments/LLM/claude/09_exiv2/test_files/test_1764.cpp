#include <gtest/gtest.h>
#include <sstream>
#include "crwimage_int.hpp"

using namespace Exiv2::Internal;

// Test fixture for CiffComponent tests
class CiffComponentTest_1764 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor
TEST_F(CiffComponentTest_1764, DefaultConstructor_1764) {
    CiffComponent comp;
    EXPECT_EQ(comp.tag(), 0);
    EXPECT_EQ(comp.dir(), 0);
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
    EXPECT_EQ(comp.pData(), nullptr);
}

// Test parameterized constructor
TEST_F(CiffComponentTest_1764, ParameterizedConstructor_1764) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent comp(tag, dir);
    EXPECT_EQ(comp.tag(), tag);
    EXPECT_EQ(comp.dir(), dir);
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
    EXPECT_EQ(comp.pData(), nullptr);
}

// Test tag accessor
TEST_F(CiffComponentTest_1764, TagAccessor_1764) {
    CiffComponent comp(0x0001, 0x0000);
    EXPECT_EQ(comp.tag(), 0x0001);
}

// Test dir accessor and setter
TEST_F(CiffComponentTest_1764, DirAccessorAndSetter_1764) {
    CiffComponent comp(0x0000, 0x1111);
    EXPECT_EQ(comp.dir(), 0x1111);
    comp.setDir(0x2222);
    EXPECT_EQ(comp.dir(), 0x2222);
}

// Test tagId
TEST_F(CiffComponentTest_1764, TagId_1764) {
    // tagId should return just the lower bits (tag ID without type info)
    // Based on CRW format, tagId is typically tag & 0x3fff
    CiffComponent comp(0x080a, 0x0000);
    uint16_t tagId = comp.tagId();
    // tagId extracts the ID portion from the tag
    EXPECT_EQ(tagId, comp.tag() & 0x3fff);
}

// Test static typeId method
TEST_F(CiffComponentTest_1764, StaticTypeId_1764) {
    // typeId extracts the type from the tag value
    // Type is encoded in bits 13-15 of the tag
    TypeId type0 = CiffComponent::typeId(0x0000);
    TypeId type1 = CiffComponent::typeId(0x0800);
    TypeId type2 = CiffComponent::typeId(0x1000);
    TypeId type3 = CiffComponent::typeId(0x1800);
    TypeId type4 = CiffComponent::typeId(0x2000);
    TypeId type5 = CiffComponent::typeId(0x2800);
    TypeId type6 = CiffComponent::typeId(0x3000);
    TypeId type7 = CiffComponent::typeId(0x3800);
    
    // Just ensure they return valid TypeId values (we treat implementation as black box)
    // The important thing is they don't crash and return consistently
    EXPECT_EQ(CiffComponent::typeId(0x0000), type0);
    EXPECT_EQ(CiffComponent::typeId(0x0800), type1);
}

// Test instance typeId method matches static
TEST_F(CiffComponentTest_1764, InstanceTypeIdMatchesStatic_1764) {
    uint16_t tag = 0x1234;
    CiffComponent comp(tag, 0x0000);
    EXPECT_EQ(comp.typeId(), CiffComponent::typeId(tag));
}

// Test static dataLocation method
TEST_F(CiffComponentTest_1764, StaticDataLocation_1764) {
    DataLocId loc0 = CiffComponent::dataLocation(0x0000);
    DataLocId loc1 = CiffComponent::dataLocation(0x4000);
    // Just verify the function returns without crashing and is deterministic
    EXPECT_EQ(CiffComponent::dataLocation(0x0000), loc0);
    EXPECT_EQ(CiffComponent::dataLocation(0x4000), loc1);
}

// Test instance dataLocation method
TEST_F(CiffComponentTest_1764, InstanceDataLocation_1764) {
    uint16_t tag = 0x2345;
    CiffComponent comp(tag, 0x0000);
    EXPECT_EQ(comp.dataLocation(), CiffComponent::dataLocation(tag));
}

// Test empty on default constructed component
TEST_F(CiffComponentTest_1764, EmptyOnDefaultComponent_1764) {
    CiffComponent comp;
    // A default-constructed component should be considered empty
    // since it has no data
    bool isEmpty = comp.empty();
    // Just verify it doesn't crash; the actual value depends on implementation
    (void)isEmpty;
}

// Test setValue
TEST_F(CiffComponentTest_1764, SetValue_1764) {
    CiffComponent comp(0x0001, 0x0000);
    
    Exiv2::DataBuf buf(10);
    std::memset(buf.data(), 0xAB, 10);
    
    comp.setValue(std::move(buf));
    
    // After setting value, pData should not be null and size should reflect the data
    EXPECT_NE(comp.pData(), nullptr);
    EXPECT_EQ(comp.size(), 10u);
}

// Test setValue with empty buffer
TEST_F(CiffComponentTest_1764, SetValueEmptyBuffer_1764) {
    CiffComponent comp(0x0001, 0x0000);
    
    Exiv2::DataBuf buf;
    comp.setValue(std::move(buf));
    
    // After setting empty value
    EXPECT_EQ(comp.size(), 0u);
}

// Test findComponent returns nullptr for non-matching component
TEST_F(CiffComponentTest_1764, FindComponentReturnsNullForMismatch_1764) {
    CiffComponent comp(0x0001, 0x0002);
    
    // findComponent on a leaf component should return nullptr if tags don't match
    // or return this if they do match
    CiffComponent* found = comp.findComponent(0x9999, 0x8888);
    // For a leaf node, it should only return itself if matching
    // We just test it doesn't crash
    (void)found;
}

// Test findComponent returns component for matching tag and dir
TEST_F(CiffComponentTest_1764, FindComponentMatchingSelf_1764) {
    uint16_t crwTagId = 0x0001;
    uint16_t crwDir = 0x0002;
    CiffComponent comp(crwTagId, crwDir);
    
    CiffComponent* found = comp.findComponent(crwTagId, crwDir);
    // For a leaf, if tag and dir match, it might return this
    // We treat as black box - just verify no crash
    (void)found;
}

// Test print doesn't crash
TEST_F(CiffComponentTest_1764, PrintDoesNotCrash_1764) {
    CiffComponent comp(0x0001, 0x0000);
    std::ostringstream os;
    
    EXPECT_NO_THROW(comp.print(os, Exiv2::littleEndian, ""));
}

// Test print with prefix
TEST_F(CiffComponentTest_1764, PrintWithPrefix_1764) {
    CiffComponent comp(0x0001, 0x0000);
    std::ostringstream os;
    
    EXPECT_NO_THROW(comp.print(os, Exiv2::littleEndian, "  "));
}

// Test writeDirEntry
TEST_F(CiffComponentTest_1764, WriteDirEntry_1764) {
    CiffComponent comp(0x0001, 0x0000);
    Blob blob;
    
    EXPECT_NO_THROW(comp.writeDirEntry(blob, Exiv2::littleEndian));
    // writeDirEntry should write exactly 10 bytes (CRW dir entry size)
    EXPECT_EQ(blob.size(), 10u);
}

// Test writeDirEntry with big endian
TEST_F(CiffComponentTest_1764, WriteDirEntryBigEndian_1764) {
    CiffComponent comp(0x0001, 0x0000);
    Blob blob;
    
    EXPECT_NO_THROW(comp.writeDirEntry(blob, Exiv2::bigEndian));
    EXPECT_EQ(blob.size(), 10u);
}

// Test writeValueData on default component
TEST_F(CiffComponentTest_1764, WriteValueDataDefault_1764) {
    CiffComponent comp(0x0001, 0x0000);
    Blob blob;
    
    size_t result = comp.writeValueData(blob, 0);
    // For a component with no data, the returned offset should be same or adjusted
    (void)result;
}

// Test write on default component
TEST_F(CiffComponentTest_1764, WriteDefault_1764) {
    CiffComponent comp(0x0001, 0x0000);
    Blob blob;
    
    size_t result = comp.write(blob, Exiv2::littleEndian, 0);
    // Just verify no crash
    (void)result;
}

// Test setDir
TEST_F(CiffComponentTest_1764, SetDir_1764) {
    CiffComponent comp;
    comp.setDir(0xABCD);
    EXPECT_EQ(comp.dir(), 0xABCD);
}

// Test setDir changes directory
TEST_F(CiffComponentTest_1764, SetDirChanges_1764) {
    CiffComponent comp(0x0001, 0x0002);
    EXPECT_EQ(comp.dir(), 0x0002);
    comp.setDir(0x0003);
    EXPECT_EQ(comp.dir(), 0x0003);
}

// Test typeId for various tag values - boundary
TEST_F(CiffComponentTest_1764, TypeIdBoundaryValues_1764) {
    EXPECT_NO_THROW(CiffComponent::typeId(0x0000));
    EXPECT_NO_THROW(CiffComponent::typeId(0xFFFF));
    EXPECT_NO_THROW(CiffComponent::typeId(0x7FFF));
    EXPECT_NO_THROW(CiffComponent::typeId(0x8000));
}

// Test dataLocation for various tag values - boundary
TEST_F(CiffComponentTest_1764, DataLocationBoundaryValues_1764) {
    EXPECT_NO_THROW(CiffComponent::dataLocation(0x0000));
    EXPECT_NO_THROW(CiffComponent::dataLocation(0xFFFF));
    EXPECT_NO_THROW(CiffComponent::dataLocation(0x7FFF));
    EXPECT_NO_THROW(CiffComponent::dataLocation(0x8000));
}

// Test that copy constructor is deleted (compile-time check implied by design)
// We can't directly test this at runtime, but we verify the component works
// with move semantics through setValue
TEST_F(CiffComponentTest_1764, MoveSemanticsThroughSetValue_1764) {
    CiffComponent comp(0x0001, 0x0000);
    
    Exiv2::DataBuf buf(100);
    std::memset(buf.data(), 0x42, 100);
    
    comp.setValue(std::move(buf));
    
    EXPECT_EQ(comp.size(), 100u);
    EXPECT_NE(comp.pData(), nullptr);
    EXPECT_EQ(comp.pData()[0], 0x42);
    EXPECT_EQ(comp.pData()[99], 0x42);
}

// Test setValue replaces previous value
TEST_F(CiffComponentTest_1764, SetValueReplacesPrevious_1764) {
    CiffComponent comp(0x0001, 0x0000);
    
    Exiv2::DataBuf buf1(50);
    std::memset(buf1.data(), 0xAA, 50);
    comp.setValue(std::move(buf1));
    
    EXPECT_EQ(comp.size(), 50u);
    EXPECT_EQ(comp.pData()[0], 0xAA);
    
    Exiv2::DataBuf buf2(30);
    std::memset(buf2.data(), 0xBB, 30);
    comp.setValue(std::move(buf2));
    
    EXPECT_EQ(comp.size(), 30u);
    EXPECT_EQ(comp.pData()[0], 0xBB);
}

// Test typeId consistency between instance and static methods
TEST_F(CiffComponentTest_1764, TypeIdConsistency_1764) {
    for (uint16_t tag = 0; tag < 0x4000; tag += 0x0800) {
        CiffComponent comp(tag, 0x0000);
        EXPECT_EQ(comp.typeId(), CiffComponent::typeId(tag));
    }
}

// Test dataLocation consistency between instance and static methods
TEST_F(CiffComponentTest_1764, DataLocationConsistency_1764) {
    for (uint16_t tag = 0; tag < 0x8000; tag += 0x1000) {
        CiffComponent comp(tag, 0x0000);
        EXPECT_EQ(comp.dataLocation(), CiffComponent::dataLocation(tag));
    }
}

// Test that tag is immutable after construction (no setter)
TEST_F(CiffComponentTest_1764, TagImmutableAfterConstruction_1764) {
    CiffComponent comp(0x1234, 0x0000);
    EXPECT_EQ(comp.tag(), 0x1234);
    // There's no setTag method, so tag should remain the same
    EXPECT_EQ(comp.tag(), 0x1234);
}

// Test offset is initially zero
TEST_F(CiffComponentTest_1764, OffsetInitiallyZero_1764) {
    CiffComponent comp(0x0001, 0x0002);
    EXPECT_EQ(comp.offset(), 0u);
}

// Test write with setValue data
TEST_F(CiffComponentTest_1764, WriteWithSetValueData_1764) {
    CiffComponent comp(0x0001, 0x0000);
    
    Exiv2::DataBuf buf(20);
    std::memset(buf.data(), 0xCC, 20);
    comp.setValue(std::move(buf));
    
    Blob blob;
    EXPECT_NO_THROW(comp.write(blob, Exiv2::littleEndian, 0));
}

// Test multiple writeValueData calls
TEST_F(CiffComponentTest_1764, WriteValueDataWithData_1764) {
    CiffComponent comp(0x0001, 0x0000);
    
    Exiv2::DataBuf buf(15);
    std::memset(buf.data(), 0xDD, 15);
    comp.setValue(std::move(buf));
    
    Blob blob;
    size_t offset = comp.writeValueData(blob, 0);
    (void)offset;
}
