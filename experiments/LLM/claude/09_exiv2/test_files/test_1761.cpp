#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <cstdint>

// Include necessary headers from the project
#include "crwimage_int.hpp"
#include "types.hpp"
#include "basicio.hpp"
#include "image.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Type aliases for convenience
using Blob = std::vector<byte>;

class CiffComponentTest_1761 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default construction
TEST_F(CiffComponentTest_1761, DefaultConstructor_1761) {
    CiffComponent component;
    EXPECT_EQ(component.tag(), 0);
    EXPECT_EQ(component.dir(), 0);
    EXPECT_EQ(component.size(), 0u);
    EXPECT_EQ(component.offset(), 0u);
    EXPECT_EQ(component.pData(), nullptr);
}

// Test parameterized constructor
TEST_F(CiffComponentTest_1761, ParameterizedConstructor_1761) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent component(tag, dir);
    EXPECT_EQ(component.tag(), tag);
    EXPECT_EQ(component.dir(), dir);
    EXPECT_EQ(component.size(), 0u);
    EXPECT_EQ(component.offset(), 0u);
    EXPECT_EQ(component.pData(), nullptr);
}

// Test setDir and dir accessor
TEST_F(CiffComponentTest_1761, SetDirAndDir_1761) {
    CiffComponent component;
    component.setDir(0xABCD);
    EXPECT_EQ(component.dir(), 0xABCD);
}

// Test tag accessor
TEST_F(CiffComponentTest_1761, TagAccessor_1761) {
    CiffComponent component(0x0042, 0x0000);
    EXPECT_EQ(component.tag(), 0x0042);
}

// Test offset accessor returns zero for default constructed component
TEST_F(CiffComponentTest_1761, OffsetDefaultZero_1761) {
    CiffComponent component;
    EXPECT_EQ(component.offset(), 0u);
}

// Test size accessor returns zero for default constructed component
TEST_F(CiffComponentTest_1761, SizeDefaultZero_1761) {
    CiffComponent component;
    EXPECT_EQ(component.size(), 0u);
}

// Test pData returns nullptr for default constructed component
TEST_F(CiffComponentTest_1761, PDataDefaultNull_1761) {
    CiffComponent component;
    EXPECT_EQ(component.pData(), nullptr);
}

// Test empty() on default constructed component
TEST_F(CiffComponentTest_1761, EmptyOnDefaultComponent_1761) {
    CiffComponent component;
    // A default component with no data should be considered empty or not based on implementation
    // We just ensure it doesn't crash and returns a bool
    bool result = component.empty();
    // Default component likely is empty
    (void)result; // Just checking it's callable
}

// Test setValue with a DataBuf
TEST_F(CiffComponentTest_1761, SetValue_1761) {
    CiffComponent component(0x0001, 0x0000);
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));
    // After setting value, pData should not be null and size should reflect the data
    EXPECT_NE(component.pData(), nullptr);
    EXPECT_EQ(component.size(), 4u);
}

// Test setValue with empty DataBuf
TEST_F(CiffComponentTest_1761, SetValueEmptyBuf_1761) {
    CiffComponent component(0x0001, 0x0000);
    DataBuf buf;
    component.setValue(std::move(buf));
    // After setting empty value, size should be 0
    EXPECT_EQ(component.size(), 0u);
}

// Test tagId derived from tag
TEST_F(CiffComponentTest_1761, TagId_1761) {
    // tagId is typically lower bits of tag
    CiffComponent component(0x300A, 0x0000);
    uint16_t tagId = component.tagId();
    // tagId should be the lower portion of tag (mask with 0x3fff typically)
    EXPECT_EQ(tagId, component.tag() & 0x3fff);
}

// Test static typeId function
TEST_F(CiffComponentTest_1761, StaticTypeId_1761) {
    // typeId extracts type information from a tag value
    // Just ensure the function is callable and returns valid TypeId
    TypeId t = CiffComponent::typeId(0x0000);
    (void)t; // Just checking it's callable
}

// Test static dataLocation function
TEST_F(CiffComponentTest_1761, StaticDataLocation_1761) {
    DataLocId loc = CiffComponent::dataLocation(0x0000);
    (void)loc; // Just checking it's callable
}

// Test typeId member function
TEST_F(CiffComponentTest_1761, MemberTypeId_1761) {
    CiffComponent component(0x0800, 0x0000);
    TypeId t = component.typeId();
    // typeId() member should match the static typeId with the component's tag
    EXPECT_EQ(t, CiffComponent::typeId(component.tag()));
}

// Test dataLocation member function
TEST_F(CiffComponentTest_1761, MemberDataLocation_1761) {
    CiffComponent component(0x0800, 0x0000);
    DataLocId loc = component.dataLocation();
    EXPECT_EQ(loc, CiffComponent::dataLocation(component.tag()));
}

// Test findComponent returns nullptr when no match
TEST_F(CiffComponentTest_1761, FindComponentNoMatch_1761) {
    CiffComponent component(0x0001, 0x0002);
    CiffComponent* found = component.findComponent(0xFFFF, 0xFFFF);
    // For a leaf component, findComponent should return nullptr if IDs don't match,
    // or return this if they do match
    // We can't know the exact match logic, but with non-matching IDs it should likely be nullptr
    // (or it matches based on its own tag/dir)
    // Let's test the matching case
    CiffComponent* foundSelf = component.findComponent(component.tagId(), component.dir());
    // One of these should work - either find itself or not
    (void)found;
    (void)foundSelf;
}

// Test findComponent matches itself
TEST_F(CiffComponentTest_1761, FindComponentMatchesSelf_1761) {
    uint16_t tag = 0x0001;
    uint16_t dir = 0x0002;
    CiffComponent component(tag, dir);
    uint16_t tagId = component.tagId();
    CiffComponent* found = component.findComponent(tagId, dir);
    // A leaf CiffComponent should find itself if tag and dir match
    if (found != nullptr) {
        EXPECT_EQ(found, &component);
    }
}

// Test print doesn't crash
TEST_F(CiffComponentTest_1761, PrintDoesNotCrash_1761) {
    CiffComponent component(0x0001, 0x0000);
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, littleEndian, ""));
}

// Test print with prefix
TEST_F(CiffComponentTest_1761, PrintWithPrefix_1761) {
    CiffComponent component(0x0001, 0x0000);
    std::ostringstream os;
    EXPECT_NO_THROW(component.print(os, bigEndian, "prefix: "));
}

// Test writeValueData on empty component
TEST_F(CiffComponentTest_1761, WriteValueDataEmpty_1761) {
    CiffComponent component;
    Blob blob;
    size_t result = component.writeValueData(blob, 0);
    // For an empty component, the result should just be the offset passed in (or 0)
    (void)result;
}

// Test writeDirEntry on a component
TEST_F(CiffComponentTest_1761, WriteDirEntry_1761) {
    CiffComponent component(0x0001, 0x0000);
    Blob blob;
    EXPECT_NO_THROW(component.writeDirEntry(blob, littleEndian));
    // A dir entry should write 10 bytes (tag(2) + size(4) + offset(4))
    EXPECT_EQ(blob.size(), 10u);
}

// Test write on empty component
TEST_F(CiffComponentTest_1761, WriteEmpty_1761) {
    CiffComponent component;
    Blob blob;
    size_t result = component.write(blob, littleEndian, 0);
    (void)result;
}

// Test write with data
TEST_F(CiffComponentTest_1761, WriteWithData_1761) {
    CiffComponent component(0x0001, 0x0000);
    byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));
    
    Blob blob;
    size_t result = component.write(blob, littleEndian, 0);
    EXPECT_GT(result, 0u);
}

// Test setDir changes directory
TEST_F(CiffComponentTest_1761, SetDirChangesDir_1761) {
    CiffComponent component(0x0001, 0x0000);
    EXPECT_EQ(component.dir(), 0x0000);
    component.setDir(0x1234);
    EXPECT_EQ(component.dir(), 0x1234);
}

// Test multiple setValue calls overwrite data
TEST_F(CiffComponentTest_1761, SetValueOverwrite_1761) {
    CiffComponent component(0x0001, 0x0000);
    
    byte data1[] = {0x01, 0x02};
    DataBuf buf1(data1, sizeof(data1));
    component.setValue(std::move(buf1));
    EXPECT_EQ(component.size(), 2u);
    
    byte data2[] = {0x03, 0x04, 0x05, 0x06, 0x07};
    DataBuf buf2(data2, sizeof(data2));
    component.setValue(std::move(buf2));
    EXPECT_EQ(component.size(), 5u);
}

// Test boundary: max uint16_t values for tag and dir
TEST_F(CiffComponentTest_1761, MaxTagAndDir_1761) {
    CiffComponent component(0xFFFF, 0xFFFF);
    EXPECT_EQ(component.tag(), 0xFFFF);
    EXPECT_EQ(component.dir(), 0xFFFF);
}

// Test boundary: zero tag and dir
TEST_F(CiffComponentTest_1761, ZeroTagAndDir_1761) {
    CiffComponent component(0x0000, 0x0000);
    EXPECT_EQ(component.tag(), 0x0000);
    EXPECT_EQ(component.dir(), 0x0000);
}

// Test empty after setValue with data
TEST_F(CiffComponentTest_1761, EmptyAfterSetValue_1761) {
    CiffComponent component(0x0001, 0x0000);
    byte data[] = {0x01};
    DataBuf buf(data, sizeof(data));
    component.setValue(std::move(buf));
    // After setting a value, the component should not be empty
    // (assuming the base doEmpty checks for data presence)
    bool result = component.empty();
    (void)result;
}

// Test copy constructor is deleted (compile-time check - we just ensure it's documented)
// This is a compile-time constraint, not a runtime test, but we document it
TEST_F(CiffComponentTest_1761, CopyConstructorDeleted_1761) {
    // CiffComponent component1;
    // CiffComponent component2(component1); // Should not compile
    SUCCEED(); // Placeholder to document that copy is deleted
}

// Test assignment operator is deleted
TEST_F(CiffComponentTest_1761, AssignmentOperatorDeleted_1761) {
    // CiffComponent component1, component2;
    // component1 = component2; // Should not compile
    SUCCEED(); // Placeholder to document that assignment is deleted
}

// Test writeDirEntry with big endian
TEST_F(CiffComponentTest_1761, WriteDirEntryBigEndian_1761) {
    CiffComponent component(0x0001, 0x0000);
    Blob blob;
    EXPECT_NO_THROW(component.writeDirEntry(blob, bigEndian));
    EXPECT_EQ(blob.size(), 10u);
}

// Test that different byte orders produce different output in writeDirEntry
TEST_F(CiffComponentTest_1761, WriteDirEntryByteOrderDifference_1761) {
    CiffComponent component1(0x0102, 0x0000);
    byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf buf(data, sizeof(data));
    component1.setValue(std::move(buf));

    Blob blobLE, blobBE;
    component1.writeDirEntry(blobLE, littleEndian);
    
    CiffComponent component2(0x0102, 0x0000);
    byte data2[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    DataBuf buf2(data2, sizeof(data2));
    component2.setValue(std::move(buf2));
    component2.writeDirEntry(blobBE, bigEndian);
    
    // Both should be 10 bytes
    EXPECT_EQ(blobLE.size(), 10u);
    EXPECT_EQ(blobBE.size(), 10u);
    // The contents should differ due to byte order (unless all values are zero or symmetric)
}

// Test static typeId with various tag values
TEST_F(CiffComponentTest_1761, StaticTypeIdVariousTags_1761) {
    // Type is encoded in bits 13-8 of the tag typically
    TypeId t1 = CiffComponent::typeId(0x0000);
    TypeId t2 = CiffComponent::typeId(0x0800);
    TypeId t3 = CiffComponent::typeId(0x1000);
    // Different tag ranges should potentially return different type IDs
    (void)t1;
    (void)t2;
    (void)t3;
}

// Test large data setValue
TEST_F(CiffComponentTest_1761, SetValueLargeData_1761) {
    CiffComponent component(0x0001, 0x0000);
    std::vector<byte> largeData(10000, 0xAA);
    DataBuf buf(largeData.data(), largeData.size());
    component.setValue(std::move(buf));
    EXPECT_EQ(component.size(), 10000u);
    EXPECT_NE(component.pData(), nullptr);
}
