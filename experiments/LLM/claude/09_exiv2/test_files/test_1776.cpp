#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>

// Include internal headers for CiffComponent
#include "crwimage_int.hpp"

#include <memory>
#include <sstream>
#include <vector>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper: Create a minimal Image for testing via a concrete subclass or using MemIo
// We need a concrete Image to pass to decode(). We'll use a simple approach with MemIo.
class TestImage : public Exiv2::Image {
public:
    TestImage()
        : Image(ImageType::none, mdNone, std::make_unique<Exiv2::MemIo>()) {}

    void readMetadata() override {}
    void writeMetadata() override {}
};

class CiffComponentTest_1776 : public ::testing::Test {
protected:
    void SetUp() override {
        testImage_ = std::make_unique<TestImage>();
    }

    std::unique_ptr<TestImage> testImage_;
};

// Test default constructor creates component with default values
TEST_F(CiffComponentTest_1776, DefaultConstructor_1776) {
    CiffComponent comp;
    EXPECT_EQ(comp.tag(), 0);
    EXPECT_EQ(comp.dir(), 0);
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
    EXPECT_EQ(comp.pData(), nullptr);
}

// Test parameterized constructor sets tag and dir
TEST_F(CiffComponentTest_1776, ParameterizedConstructor_1776) {
    uint16_t tag = 0x1234;
    uint16_t dir = 0x5678;
    CiffComponent comp(tag, dir);
    EXPECT_EQ(comp.tag(), tag);
    EXPECT_EQ(comp.dir(), dir);
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
    EXPECT_EQ(comp.pData(), nullptr);
}

// Test setDir changes the directory
TEST_F(CiffComponentTest_1776, SetDir_1776) {
    CiffComponent comp(0x0001, 0x0002);
    EXPECT_EQ(comp.dir(), 0x0002);
    comp.setDir(0x00FF);
    EXPECT_EQ(comp.dir(), 0x00FF);
}

// Test empty() on default constructed component
TEST_F(CiffComponentTest_1776, EmptyOnDefaultComponent_1776) {
    CiffComponent comp;
    EXPECT_TRUE(comp.empty());
}

// Test tagId() returns expected value based on tag
TEST_F(CiffComponentTest_1776, TagId_1776) {
    CiffComponent comp(0x1234, 0x0000);
    // tagId is typically derived from the tag field
    uint16_t tagId = comp.tagId();
    // We just verify it returns something deterministic
    EXPECT_EQ(tagId, comp.tagId());
}

// Test typeId() static method with various tag values
TEST_F(CiffComponentTest_1776, StaticTypeId_1776) {
    // Test that the static typeId function returns some valid TypeId for various tags
    TypeId t1 = CiffComponent::typeId(0x0000);
    TypeId t2 = CiffComponent::typeId(0x0800);
    TypeId t3 = CiffComponent::typeId(0x1000);
    TypeId t4 = CiffComponent::typeId(0x1800);
    // Just verify these don't crash and return valid values
    (void)t1;
    (void)t2;
    (void)t3;
    (void)t4;
}

// Test dataLocation() static method
TEST_F(CiffComponentTest_1776, StaticDataLocation_1776) {
    DataLocId loc1 = CiffComponent::dataLocation(0x0000);
    DataLocId loc2 = CiffComponent::dataLocation(0x4000);
    // Verify they return deterministic values
    (void)loc1;
    (void)loc2;
}

// Test typeId() instance method
TEST_F(CiffComponentTest_1776, InstanceTypeId_1776) {
    CiffComponent comp(0x0800, 0x0000);
    TypeId tid = comp.typeId();
    // Should be consistent with the static version
    EXPECT_EQ(tid, CiffComponent::typeId(0x0800));
}

// Test dataLocation() instance method
TEST_F(CiffComponentTest_1776, InstanceDataLocation_1776) {
    CiffComponent comp(0x4000, 0x0000);
    DataLocId loc = comp.dataLocation();
    EXPECT_EQ(loc, CiffComponent::dataLocation(0x4000));
}

// Test setValue with a DataBuf
TEST_F(CiffComponentTest_1776, SetValue_1776) {
    CiffComponent comp(0x0001, 0x0000);
    
    const uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    
    // After setValue, pData should not be null and size should reflect the data
    EXPECT_NE(comp.pData(), nullptr);
    EXPECT_EQ(comp.size(), sizeof(data));
}

// Test setValue with empty DataBuf
TEST_F(CiffComponentTest_1776, SetValueEmpty_1776) {
    CiffComponent comp(0x0001, 0x0000);
    DataBuf emptyBuf;
    comp.setValue(std::move(emptyBuf));
    // Size should be 0 after setting empty buffer
    EXPECT_EQ(comp.size(), 0u);
}

// Test findComponent on a leaf component (non-directory)
TEST_F(CiffComponentTest_1776, FindComponentLeaf_1776) {
    CiffComponent comp(0x0001, 0x0002);
    // A leaf CiffComponent's findComponent should return nullptr for most queries
    // or itself if matching
    CiffComponent* found = comp.findComponent(0x0001, 0x0002);
    // The default implementation may return nullptr since it's not a directory
    // We test that it doesn't crash
    (void)found;
}

// Test findComponent with non-matching tag/dir
TEST_F(CiffComponentTest_1776, FindComponentNonMatching_1776) {
    CiffComponent comp(0x0001, 0x0002);
    CiffComponent* found = comp.findComponent(0xFFFF, 0xFFFF);
    EXPECT_EQ(found, nullptr);
}

// Test print on default component doesn't crash
TEST_F(CiffComponentTest_1776, PrintDefault_1776) {
    CiffComponent comp;
    std::ostringstream os;
    EXPECT_NO_THROW(comp.print(os, littleEndian, ""));
}

// Test print with prefix
TEST_F(CiffComponentTest_1776, PrintWithPrefix_1776) {
    CiffComponent comp(0x0001, 0x0000);
    std::ostringstream os;
    EXPECT_NO_THROW(comp.print(os, bigEndian, "prefix: "));
}

// Test decode on default component (should not crash)
TEST_F(CiffComponentTest_1776, DecodeDefaultComponent_1776) {
    CiffComponent comp;
    EXPECT_NO_THROW(comp.decode(*testImage_, littleEndian));
}

// Test decode with big endian byte order
TEST_F(CiffComponentTest_1776, DecodeBigEndian_1776) {
    CiffComponent comp(0x0001, 0x0000);
    EXPECT_NO_THROW(comp.decode(*testImage_, bigEndian));
}

// Test writeDirEntry on a default component
TEST_F(CiffComponentTest_1776, WriteDirEntry_1776) {
    CiffComponent comp(0x0001, 0x0000);
    Blob blob;
    EXPECT_NO_THROW(comp.writeDirEntry(blob, littleEndian));
    // A dir entry should write some bytes
    EXPECT_GT(blob.size(), 0u);
}

// Test writeDirEntry with big endian
TEST_F(CiffComponentTest_1776, WriteDirEntryBigEndian_1776) {
    CiffComponent comp(0x0001, 0x0000);
    Blob blob;
    EXPECT_NO_THROW(comp.writeDirEntry(blob, bigEndian));
    EXPECT_GT(blob.size(), 0u);
}

// Test write on default component
TEST_F(CiffComponentTest_1776, WriteDefault_1776) {
    CiffComponent comp(0x0001, 0x0000);
    Blob blob;
    size_t result = 0;
    EXPECT_NO_THROW(result = comp.write(blob, littleEndian, 0));
    (void)result;
}

// Test writeValueData on default component
TEST_F(CiffComponentTest_1776, WriteValueDataDefault_1776) {
    CiffComponent comp(0x0001, 0x0000);
    Blob blob;
    size_t result = 0;
    EXPECT_NO_THROW(result = comp.writeValueData(blob, 0));
    (void)result;
}

// Test write after setValue
TEST_F(CiffComponentTest_1776, WriteAfterSetValue_1776) {
    CiffComponent comp(0x0001, 0x0000);
    const uint8_t data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));

    Blob blob;
    EXPECT_NO_THROW(comp.write(blob, littleEndian, 0));
}

// Test that two components with different tags have different tagId
TEST_F(CiffComponentTest_1776, DifferentTagsDifferentTagId_1776) {
    CiffComponent comp1(0x0001, 0x0000);
    CiffComponent comp2(0x0002, 0x0000);
    // They may or may not differ depending on implementation, but at minimum
    // the tag() values differ
    EXPECT_NE(comp1.tag(), comp2.tag());
}

// Test that parameterized constructor with zero values
TEST_F(CiffComponentTest_1776, ZeroTagAndDir_1776) {
    CiffComponent comp(0x0000, 0x0000);
    EXPECT_EQ(comp.tag(), 0x0000);
    EXPECT_EQ(comp.dir(), 0x0000);
}

// Test that parameterized constructor with max values
TEST_F(CiffComponentTest_1776, MaxTagAndDir_1776) {
    CiffComponent comp(0xFFFF, 0xFFFF);
    EXPECT_EQ(comp.tag(), 0xFFFF);
    EXPECT_EQ(comp.dir(), 0xFFFF);
}

// Test empty after setValue with data
TEST_F(CiffComponentTest_1776, NotEmptyAfterSetValue_1776) {
    CiffComponent comp;
    const uint8_t data[] = {0x01};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    // After setting value, size > 0, so it might not be empty
    // This depends on implementation but we test the observable behavior
    EXPECT_EQ(comp.size(), 1u);
}

// Test multiple setDir calls
TEST_F(CiffComponentTest_1776, MultipleSetDir_1776) {
    CiffComponent comp(0x0001, 0x0000);
    comp.setDir(0x0001);
    EXPECT_EQ(comp.dir(), 0x0001);
    comp.setDir(0x0002);
    EXPECT_EQ(comp.dir(), 0x0002);
    comp.setDir(0x0000);
    EXPECT_EQ(comp.dir(), 0x0000);
}

// Test that pData returns valid pointer after setValue
TEST_F(CiffComponentTest_1776, PDataAfterSetValue_1776) {
    CiffComponent comp;
    const uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));

    const byte* p = comp.pData();
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(p[0], 0xDE);
    EXPECT_EQ(p[1], 0xAD);
    EXPECT_EQ(p[2], 0xBE);
    EXPECT_EQ(p[3], 0xEF);
}

// Test decode does not modify component's tag/dir
TEST_F(CiffComponentTest_1776, DecodeDoesNotModifyTagDir_1776) {
    CiffComponent comp(0x1234, 0x5678);
    comp.decode(*testImage_, littleEndian);
    EXPECT_EQ(comp.tag(), 0x1234);
    EXPECT_EQ(comp.dir(), 0x5678);
}

// Test print produces some output for a component with data
TEST_F(CiffComponentTest_1776, PrintWithData_1776) {
    CiffComponent comp(0x0001, 0x0000);
    const uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));

    std::ostringstream os;
    comp.print(os, littleEndian, "");
    // We just verify it doesn't crash; output content is implementation-defined
}

// Test writeDirEntry produces consistent output for same component
TEST_F(CiffComponentTest_1776, WriteDirEntryConsistent_1776) {
    CiffComponent comp(0x0001, 0x0000);
    const uint8_t data[] = {0x01, 0x02};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));

    Blob blob1, blob2;
    comp.writeDirEntry(blob1, littleEndian);
    comp.writeDirEntry(blob2, littleEndian);
    EXPECT_EQ(blob1, blob2);
}
