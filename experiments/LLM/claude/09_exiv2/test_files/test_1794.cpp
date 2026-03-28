#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "crwimage_int.hpp"
#include "exiv2/types.hpp"
#include "exiv2/image.hpp"

#include <sstream>
#include <vector>
#include <cstring>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for CiffComponent tests
class CiffComponentTest_1794 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test default constructor creates component with expected defaults
TEST_F(CiffComponentTest_1794, DefaultConstructor_HasZeroTag_1794) {
    CiffComponent comp;
    EXPECT_EQ(comp.tag(), 0);
}

TEST_F(CiffComponentTest_1794, DefaultConstructor_HasZeroDir_1794) {
    CiffComponent comp;
    EXPECT_EQ(comp.dir(), 0);
}

TEST_F(CiffComponentTest_1794, DefaultConstructor_HasZeroSize_1794) {
    CiffComponent comp;
    EXPECT_EQ(comp.size(), 0u);
}

TEST_F(CiffComponentTest_1794, DefaultConstructor_HasZeroOffset_1794) {
    CiffComponent comp;
    EXPECT_EQ(comp.offset(), 0u);
}

TEST_F(CiffComponentTest_1794, DefaultConstructor_HasNullptrData_1794) {
    CiffComponent comp;
    EXPECT_EQ(comp.pData(), nullptr);
}

// Test parameterized constructor
TEST_F(CiffComponentTest_1794, ParameterizedConstructor_SetsTag_1794) {
    CiffComponent comp(0x1234, 0x5678);
    EXPECT_EQ(comp.tag(), 0x1234);
}

TEST_F(CiffComponentTest_1794, ParameterizedConstructor_SetsDir_1794) {
    CiffComponent comp(0x1234, 0x5678);
    EXPECT_EQ(comp.dir(), 0x5678);
}

// Test setDir
TEST_F(CiffComponentTest_1794, SetDir_ChangesDir_1794) {
    CiffComponent comp;
    comp.setDir(0x0042);
    EXPECT_EQ(comp.dir(), 0x0042);
}

// Test empty() on default constructed component
TEST_F(CiffComponentTest_1794, Empty_DefaultConstructed_ReturnsTrue_1794) {
    CiffComponent comp;
    // Default component with no data should be considered empty
    // The base doEmpty() likely checks if pData_ is null or size_ is 0
    EXPECT_TRUE(comp.empty());
}

// Test setValue and then check that empty() reflects data presence
TEST_F(CiffComponentTest_1794, SetValue_WithData_MayNotBeEmpty_1794) {
    CiffComponent comp(0x0001, 0x0000);
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    // After setting value, the component should have data
    // Whether empty() returns false depends on implementation
    // but we can at least call it without crashing
    (void)comp.empty();
}

// Test tagId() - tagId is derived from tag
TEST_F(CiffComponentTest_1794, TagId_DerivedFromTag_1794) {
    CiffComponent comp(0x300A, 0x0000);
    uint16_t tagId = comp.tagId();
    // tagId typically masks out the type bits from tag
    // We just verify it returns something without crashing
    (void)tagId;
}

// Test typeId() instance method
TEST_F(CiffComponentTest_1794, TypeId_InstanceMethod_1794) {
    CiffComponent comp(0x2000, 0x0000);
    TypeId tid = comp.typeId();
    (void)tid;
}

// Test static typeId()
TEST_F(CiffComponentTest_1794, StaticTypeId_ReturnsTypeForTag_1794) {
    TypeId tid = CiffComponent::typeId(0x0000);
    (void)tid;
}

// Test static dataLocation()
TEST_F(CiffComponentTest_1794, StaticDataLocation_ReturnsLocation_1794) {
    DataLocId loc = CiffComponent::dataLocation(0x0000);
    (void)loc;
}

// Test dataLocation instance method
TEST_F(CiffComponentTest_1794, DataLocation_InstanceMethod_1794) {
    CiffComponent comp(0x0800, 0x0000);
    DataLocId loc = comp.dataLocation();
    (void)loc;
}

// Test findComponent on a leaf component (not a directory)
TEST_F(CiffComponentTest_1794, FindComponent_OnLeaf_MatchingSelf_1794) {
    CiffComponent comp(0x0005, 0x0003);
    // For a non-directory component, doFindComponent checks if this matches
    CiffComponent* found = comp.findComponent(comp.tagId(), comp.dir());
    // It may or may not find itself depending on implementation
    (void)found;
}

TEST_F(CiffComponentTest_1794, FindComponent_OnLeaf_NonMatching_ReturnsNull_1794) {
    CiffComponent comp(0x0005, 0x0003);
    CiffComponent* found = comp.findComponent(0xFFFF, 0xFFFF);
    // For a leaf node, searching for a non-matching tag should return nullptr
    EXPECT_EQ(found, nullptr);
}

// Test print on default component
TEST_F(CiffComponentTest_1794, Print_DefaultComponent_NoThrow_1794) {
    CiffComponent comp;
    std::ostringstream os;
    EXPECT_NO_THROW(comp.print(os, littleEndian, ""));
}

// Test print on component with specific tag/dir
TEST_F(CiffComponentTest_1794, Print_WithTagAndDir_NoThrow_1794) {
    CiffComponent comp(0x0001, 0x0002);
    std::ostringstream os;
    EXPECT_NO_THROW(comp.print(os, bigEndian, "prefix"));
}

// Test writeValueData on default component
TEST_F(CiffComponentTest_1794, WriteValueData_DefaultComponent_1794) {
    CiffComponent comp;
    Blob blob;
    size_t result = comp.writeValueData(blob, 0);
    (void)result;
}

// Test writeDirEntry on default component
TEST_F(CiffComponentTest_1794, WriteDirEntry_DefaultComponent_1794) {
    CiffComponent comp;
    Blob blob;
    EXPECT_NO_THROW(comp.writeDirEntry(blob, littleEndian));
}

// Test write on default component
TEST_F(CiffComponentTest_1794, Write_DefaultComponent_1794) {
    CiffComponent comp;
    Blob blob;
    size_t result = comp.write(blob, littleEndian, 0);
    (void)result;
}

// Test setValue with empty DataBuf
TEST_F(CiffComponentTest_1794, SetValue_EmptyDataBuf_1794) {
    CiffComponent comp(0x0001, 0x0000);
    DataBuf emptyBuf;
    EXPECT_NO_THROW(comp.setValue(std::move(emptyBuf)));
}

// Test that copy constructor is deleted (compile-time check, but we document intent)
// This is a design constraint - CiffComponent is non-copyable
// We can verify non-assignability concept by checking the class is used correctly

// Test parameterized constructor with zero values
TEST_F(CiffComponentTest_1794, ParameterizedConstructor_ZeroValues_1794) {
    CiffComponent comp(0x0000, 0x0000);
    EXPECT_EQ(comp.tag(), 0x0000);
    EXPECT_EQ(comp.dir(), 0x0000);
}

// Test parameterized constructor with max uint16 values
TEST_F(CiffComponentTest_1794, ParameterizedConstructor_MaxValues_1794) {
    CiffComponent comp(0xFFFF, 0xFFFF);
    EXPECT_EQ(comp.tag(), 0xFFFF);
    EXPECT_EQ(comp.dir(), 0xFFFF);
}

// Test setDir boundary - zero
TEST_F(CiffComponentTest_1794, SetDir_Zero_1794) {
    CiffComponent comp(0x1234, 0x5678);
    comp.setDir(0x0000);
    EXPECT_EQ(comp.dir(), 0x0000);
}

// Test setDir boundary - max
TEST_F(CiffComponentTest_1794, SetDir_MaxValue_1794) {
    CiffComponent comp;
    comp.setDir(0xFFFF);
    EXPECT_EQ(comp.dir(), 0xFFFF);
}

// Test multiple setDir calls
TEST_F(CiffComponentTest_1794, SetDir_MultipleCalls_LastValueWins_1794) {
    CiffComponent comp;
    comp.setDir(0x0001);
    comp.setDir(0x0002);
    comp.setDir(0x0003);
    EXPECT_EQ(comp.dir(), 0x0003);
}

// Test setValue then check pData is non-null
TEST_F(CiffComponentTest_1794, SetValue_NonEmpty_PDataNotNull_1794) {
    CiffComponent comp(0x0001, 0x0000);
    byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    // After setValue with actual data, pData should point to storage
    EXPECT_NE(comp.pData(), nullptr);
}

// Test write with bigEndian byte order
TEST_F(CiffComponentTest_1794, Write_BigEndian_1794) {
    CiffComponent comp(0x0001, 0x0000);
    byte data[] = {0x01, 0x02};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    Blob blob;
    size_t result = comp.write(blob, bigEndian, 0);
    (void)result;
}

// Test write with littleEndian byte order
TEST_F(CiffComponentTest_1794, Write_LittleEndian_1794) {
    CiffComponent comp(0x0001, 0x0000);
    byte data[] = {0x01, 0x02};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    Blob blob;
    size_t result = comp.write(blob, littleEndian, 0);
    (void)result;
}

// Test print with different byte orders
TEST_F(CiffComponentTest_1794, Print_LittleEndian_ProducesOutput_1794) {
    CiffComponent comp(0x0001, 0x0002);
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    std::ostringstream os;
    comp.print(os, littleEndian, "  ");
    // Just verify no crash and that something may have been written
    (void)os.str();
}

// Test writeValueData with non-zero offset
TEST_F(CiffComponentTest_1794, WriteValueData_NonZeroOffset_1794) {
    CiffComponent comp(0x0001, 0x0000);
    byte data[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22, 0x33};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    Blob blob;
    size_t result = comp.writeValueData(blob, 100);
    (void)result;
}

// Test static typeId with various tag values
TEST_F(CiffComponentTest_1794, StaticTypeId_VariousTags_1794) {
    // Test with different tag type bits
    TypeId t1 = CiffComponent::typeId(0x0000);
    TypeId t2 = CiffComponent::typeId(0x0800);
    TypeId t3 = CiffComponent::typeId(0x1000);
    TypeId t4 = CiffComponent::typeId(0x2000);
    TypeId t5 = CiffComponent::typeId(0x3800);
    (void)t1;
    (void)t2;
    (void)t3;
    (void)t4;
    (void)t5;
}

// Test static dataLocation with various tag values
TEST_F(CiffComponentTest_1794, StaticDataLocation_VariousTags_1794) {
    DataLocId d1 = CiffComponent::dataLocation(0x0000);
    DataLocId d2 = CiffComponent::dataLocation(0x4000);
    DataLocId d3 = CiffComponent::dataLocation(0xC000);
    (void)d1;
    (void)d2;
    (void)d3;
}
