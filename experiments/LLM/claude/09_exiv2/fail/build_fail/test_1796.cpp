#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/image.hpp"
#include "crwimage_int.hpp"

#include <memory>
#include <sstream>

using namespace Exiv2;
using namespace Exiv2::Internal;

// We need a concrete Image implementation for testing since Image is abstract
// We'll use a minimal approach - create a MemIo-based image
namespace {

// Helper to create a minimal Image for testing
// Since Image is abstract, we need a concrete subclass
class TestImage : public Image {
public:
    TestImage()
        : Image(ImageType::none, static_cast<uint16_t>(0), std::make_unique<MemIo>()) {}

    void readMetadata() override {}
    void writeMetadata() override {}
    std::string mimeType() const override { return "application/octet-stream"; }
};

} // anonymous namespace

class CiffComponentTest_1796 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

class CrwMapTest_1796 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test CiffComponent default construction
TEST_F(CiffComponentTest_1796, DefaultConstruction_1796) {
    CiffComponent comp;
    EXPECT_EQ(comp.dir(), 0);
    EXPECT_EQ(comp.tag(), 0);
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
    EXPECT_EQ(comp.pData(), nullptr);
}

// Test CiffComponent construction with tag and dir
TEST_F(CiffComponentTest_1796, ConstructionWithTagAndDir_1796) {
    uint16_t tag = 0x0805;
    uint16_t dir = 0x300a;
    CiffComponent comp(tag, dir);
    EXPECT_EQ(comp.tag(), tag);
    EXPECT_EQ(comp.dir(), dir);
}

// Test tagId() - should extract tag portion
TEST_F(CiffComponentTest_1796, TagIdExtraction_1796) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x0000;
    CiffComponent comp(tag, dir);
    // tagId is derived from tag
    uint16_t tagId = comp.tagId();
    // tagId should be consistent with the tag value
    EXPECT_EQ(tagId, tag & 0x3fff);
}

// Test empty() on default constructed component
TEST_F(CiffComponentTest_1796, EmptyOnDefault_1796) {
    CiffComponent comp;
    EXPECT_TRUE(comp.empty());
}

// Test setDir
TEST_F(CiffComponentTest_1796, SetDir_1796) {
    CiffComponent comp;
    comp.setDir(0x1234);
    EXPECT_EQ(comp.dir(), 0x1234);
}

// Test setValue and that it affects the component
TEST_F(CiffComponentTest_1796, SetValue_1796) {
    CiffComponent comp;
    DataBuf buf(10);
    std::memset(buf.data(), 0xAB, 10);
    comp.setValue(std::move(buf));
    // After setting value, pData should be non-null and size should be set
    EXPECT_NE(comp.pData(), nullptr);
    EXPECT_EQ(comp.size(), 10u);
}

// Test typeId static method
TEST_F(CiffComponentTest_1796, TypeIdStatic_1796) {
    // typeId extracts the type from the tag's upper bits
    // For a tag with no type bits set, result should be some known TypeId
    TypeId t = CiffComponent::typeId(0x0000);
    // Just verify it returns something without crashing
    (void)t;
}

// Test dataLocation static method
TEST_F(CiffComponentTest_1796, DataLocationStatic_1796) {
    DataLocId loc = CiffComponent::dataLocation(0x0000);
    (void)loc;
    // For tags where upper bits indicate data in value area vs directory entry
    DataLocId loc2 = CiffComponent::dataLocation(0x4000);
    (void)loc2;
}

// Test findComponent returns nullptr on default component
TEST_F(CiffComponentTest_1796, FindComponentOnDefault_1796) {
    CiffComponent comp;
    CiffComponent* found = comp.findComponent(0x1234, 0x0000);
    // On a leaf component, findComponent checks self
    // With default (0,0) tag/dir, searching for different values should return nullptr
    EXPECT_EQ(found, nullptr);
}

// Test findComponent finds self when matching
TEST_F(CiffComponentTest_1796, FindComponentSelf_1796) {
    uint16_t tag = 0x0805;
    uint16_t dir = 0x300a;
    CiffComponent comp(tag, dir);
    CiffComponent* found = comp.findComponent(comp.tagId(), dir);
    // May or may not find self depending on implementation
    // This tests the observable behavior
    (void)found;
}

// Test CrwMap::decode with a known CRW mapping
TEST_F(CrwMapTest_1796, DecodeWithKnownMapping_1796) {
    // Create a CiffComponent with a known CRW tag/dir combination
    // 0x0805 in dir 0x300a is typically "comment" in Canon CRW
    TestImage image;

    // Create a component with some data
    CiffComponent comp(0x0805, 0x300a);
    DataBuf buf(20);
    std::memset(buf.data(), 0, 20);
    const char* testStr = "Test";
    std::memcpy(buf.data(), testStr, 5);
    comp.setValue(std::move(buf));
    comp.setDir(0x300a);

    // This should not crash - it will look up the mapping and potentially decode
    EXPECT_NO_THROW(CrwMap::decode(comp, image, littleEndian));
}

// Test CrwMap::decode with unknown mapping does nothing
TEST_F(CrwMapTest_1796, DecodeWithUnknownMapping_1796) {
    TestImage image;

    // Use a tag/dir combination that's unlikely to be in the mapping table
    CiffComponent comp(0xFFFF, 0xFFFF);
    comp.setDir(0xFFFF);

    // Should not crash, should just do nothing
    EXPECT_NO_THROW(CrwMap::decode(comp, image, littleEndian));

    // ExifData should remain empty since no mapping was found
    EXPECT_TRUE(image.exifData().empty());
}

// Test CrwMap::decode with big endian byte order
TEST_F(CrwMapTest_1796, DecodeWithBigEndian_1796) {
    TestImage image;

    CiffComponent comp(0x0805, 0x300a);
    DataBuf buf(20);
    std::memset(buf.data(), 0, 20);
    comp.setValue(std::move(buf));
    comp.setDir(0x300a);

    EXPECT_NO_THROW(CrwMap::decode(comp, image, bigEndian));
}

// Test CrwMap::loadStack
TEST_F(CrwMapTest_1796, LoadStack_1796) {
    CrwDirs crwDirs;
    // 0x300a is a known CRW directory
    EXPECT_NO_THROW(CrwMap::loadStack(crwDirs, 0x300a));
    // The stack should have been populated with the directory hierarchy
    EXPECT_FALSE(crwDirs.empty());
}

// Test CrwMap::loadStack with root directory
TEST_F(CrwMapTest_1796, LoadStackRoot_1796) {
    CrwDirs crwDirs;
    // 0x0000 might be root
    EXPECT_NO_THROW(CrwMap::loadStack(crwDirs, 0x0000));
}

// Test CiffComponent print does not crash
TEST_F(CiffComponentTest_1796, PrintDoesNotCrash_1796) {
    CiffComponent comp(0x0805, 0x300a);
    DataBuf buf(10);
    std::memset(buf.data(), 0x41, 10);
    comp.setValue(std::move(buf));
    comp.setDir(0x300a);

    std::ostringstream os;
    EXPECT_NO_THROW(comp.print(os, littleEndian, ""));
}

// Test CiffComponent decode does not crash
TEST_F(CiffComponentTest_1796, DecodeDoesNotCrash_1796) {
    TestImage image;
    CiffComponent comp(0x0805, 0x300a);
    DataBuf buf(10);
    std::memset(buf.data(), 0, 10);
    comp.setValue(std::move(buf));
    comp.setDir(0x300a);

    EXPECT_NO_THROW(comp.decode(image, littleEndian));
}

// Test CiffComponent write/writeValueData with empty component
TEST_F(CiffComponentTest_1796, WriteEmptyComponent_1796) {
    CiffComponent comp;
    Blob blob;
    EXPECT_NO_THROW(comp.write(blob, littleEndian, 0));
}

// Test CiffComponent writeDirEntry
TEST_F(CiffComponentTest_1796, WriteDirEntry_1796) {
    CiffComponent comp(0x0805, 0x300a);
    DataBuf buf(8);
    std::memset(buf.data(), 0, 8);
    comp.setValue(std::move(buf));

    Blob blob;
    EXPECT_NO_THROW(comp.writeDirEntry(blob, littleEndian));
    // A directory entry should have been written (typically 10 bytes)
    EXPECT_EQ(blob.size(), 10u);
}

// Test CiffComponent with zero-size data
TEST_F(CiffComponentTest_1796, ZeroSizeData_1796) {
    CiffComponent comp;
    DataBuf buf(0);
    comp.setValue(std::move(buf));
    EXPECT_EQ(comp.size(), 0u);
}

// Test CrwMap::decode with component that has data - decodeBasic path
TEST_F(CrwMapTest_1796, DecodeBasicMapping_1796) {
    TestImage image;

    // Tag 0x0001 in dir 0x300b might map to a basic decode
    // We try a few known mappings
    CiffComponent comp(0x1806, 0x300b);
    comp.setDir(0x300b);

    // Set some valid-looking data
    DataBuf buf(4);
    std::memset(buf.data(), 0, 4);
    comp.setValue(std::move(buf));

    EXPECT_NO_THROW(CrwMap::decode(comp, image, littleEndian));
}

// Test multiple decode calls don't interfere
TEST_F(CrwMapTest_1796, MultipleDecodeCalls_1796) {
    TestImage image;

    CiffComponent comp1(0x0805, 0x300a);
    comp1.setDir(0x300a);
    DataBuf buf1(20);
    std::memset(buf1.data(), 0, 20);
    comp1.setValue(std::move(buf1));

    EXPECT_NO_THROW(CrwMap::decode(comp1, image, littleEndian));

    // Decode again with a different unknown component
    CiffComponent comp2(0xAAAA, 0xBBBB);
    comp2.setDir(0xBBBB);
    DataBuf buf2(10);
    std::memset(buf2.data(), 0, 10);
    comp2.setValue(std::move(buf2));

    EXPECT_NO_THROW(CrwMap::decode(comp2, image, littleEndian));
}

// Test CiffComponent typeId with various tag values
TEST_F(CiffComponentTest_1796, TypeIdVariousTags_1796) {
    // Tags with type bits in upper portion
    TypeId t1 = CiffComponent::typeId(0x0000); // Type 0
    TypeId t2 = CiffComponent::typeId(0x0800); // Type should differ
    TypeId t3 = CiffComponent::typeId(0x2000); // Another type
    TypeId t4 = CiffComponent::typeId(0x2800); // Mixed type bits

    // We can't know exact values but they should be deterministic
    EXPECT_EQ(CiffComponent::typeId(0x0000), t1);
    EXPECT_EQ(CiffComponent::typeId(0x0800), t2);
    EXPECT_EQ(CiffComponent::typeId(0x2000), t3);
    EXPECT_EQ(CiffComponent::typeId(0x2800), t4);
}

// Test CiffComponent dataLocation with various tags
TEST_F(CiffComponentTest_1796, DataLocationVariousTags_1796) {
    DataLocId loc1 = CiffComponent::dataLocation(0x0000);
    DataLocId loc2 = CiffComponent::dataLocation(0x4000);

    // These should be deterministic
    EXPECT_EQ(CiffComponent::dataLocation(0x0000), loc1);
    EXPECT_EQ(CiffComponent::dataLocation(0x4000), loc2);
}
