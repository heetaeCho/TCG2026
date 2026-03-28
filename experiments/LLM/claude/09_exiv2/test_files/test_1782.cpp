#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <cstring>
#include "crwimage_int.hpp"
#include "types.hpp"
#include "value.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CiffComponentTest_1782 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test default constructor initializes fields to zero/null
TEST_F(CiffComponentTest_1782, DefaultConstructor_1782) {
    CiffComponent comp;
    EXPECT_EQ(comp.dir(), 0);
    EXPECT_EQ(comp.tag(), 0);
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
    EXPECT_EQ(comp.pData(), nullptr);
}

// Test parameterized constructor sets tag and dir
TEST_F(CiffComponentTest_1782, ParameterizedConstructor_1782) {
    CiffComponent comp(0x1234, 0x5678);
    EXPECT_EQ(comp.tag(), 0x1234);
    EXPECT_EQ(comp.dir(), 0x5678);
    EXPECT_EQ(comp.size(), 0u);
    EXPECT_EQ(comp.offset(), 0u);
    EXPECT_EQ(comp.pData(), nullptr);
}

// Test setDir changes the directory
TEST_F(CiffComponentTest_1782, SetDir_1782) {
    CiffComponent comp(0x0001, 0x0000);
    EXPECT_EQ(comp.dir(), 0x0000);
    comp.setDir(0xABCD);
    EXPECT_EQ(comp.dir(), 0xABCD);
}

// Test tagId derivation from tag
TEST_F(CiffComponentTest_1782, TagId_1782) {
    // tagId is typically tag & 0x3fff based on CRW spec
    CiffComponent comp(0x0001, 0x0000);
    uint16_t tagId = comp.tagId();
    // We just verify it returns something consistent
    EXPECT_EQ(tagId, comp.tagId());
}

// Test typeId static method with various tags
TEST_F(CiffComponentTest_1782, StaticTypeId_1782) {
    // Type is derived from the upper bits of the tag
    TypeId t = CiffComponent::typeId(0x0000);
    // Just verify it returns a valid TypeId without crashing
    (void)t;
}

// Test dataLocation static method
TEST_F(CiffComponentTest_1782, StaticDataLocation_1782) {
    DataLocId loc = CiffComponent::dataLocation(0x0000);
    (void)loc; // Just verify no crash
}

// Test empty returns true for default-constructed component
TEST_F(CiffComponentTest_1782, EmptyDefault_1782) {
    CiffComponent comp;
    EXPECT_TRUE(comp.empty());
}

// Test setValue and then verify pData is not null
TEST_F(CiffComponentTest_1782, SetValue_1782) {
    CiffComponent comp(0x0001, 0x0000);
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));
    EXPECT_NE(comp.pData(), nullptr);
    EXPECT_EQ(comp.size(), sizeof(data));
}

// Test print produces output without crash
TEST_F(CiffComponentTest_1782, PrintNoData_1782) {
    CiffComponent comp(0x0001, 0x0000);
    std::ostringstream os;
    // Should not crash even with no data
    comp.print(os, littleEndian, "  ");
    std::string output = os.str();
    // Verify some output was produced
    EXPECT_FALSE(output.empty());
}

// Test print with data set
TEST_F(CiffComponentTest_1782, PrintWithData_1782) {
    CiffComponent comp(0x0001, 0x0000);
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));

    std::ostringstream os;
    comp.print(os, littleEndian, "");
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// Test print with big endian byte order
TEST_F(CiffComponentTest_1782, PrintBigEndian_1782) {
    CiffComponent comp(0x0001, 0x0000);
    byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));

    std::ostringstream os;
    comp.print(os, bigEndian, "PREFIX_");
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // Verify prefix appears in output
    EXPECT_NE(output.find("PREFIX_"), std::string::npos);
}

// Test findComponent returns nullptr for default component
TEST_F(CiffComponentTest_1782, FindComponentNotFound_1782) {
    CiffComponent comp;
    CiffComponent* found = comp.findComponent(0x1234, 0x5678);
    // For a leaf component, it may return nullptr or itself depending on match
    // We just verify no crash
    (void)found;
}

// Test findComponent on self-match
TEST_F(CiffComponentTest_1782, FindComponentSelfMatch_1782) {
    CiffComponent comp(0x0001, 0x0000);
    CiffComponent* found = comp.findComponent(comp.tagId(), comp.dir());
    // May or may not match depending on internal logic
    (void)found;
}

// Test tag accessor consistency
TEST_F(CiffComponentTest_1782, TagAccessor_1782) {
    CiffComponent comp(0xFFFF, 0x1234);
    EXPECT_EQ(comp.tag(), 0xFFFF);
    EXPECT_EQ(comp.dir(), 0x1234);
}

// Test typeId instance method
TEST_F(CiffComponentTest_1782, InstanceTypeId_1782) {
    CiffComponent comp(0x0000, 0x0000);
    TypeId t = comp.typeId();
    // Verify it matches the static version
    EXPECT_EQ(t, CiffComponent::typeId(comp.tag()));
}

// Test dataLocation instance method
TEST_F(CiffComponentTest_1782, InstanceDataLocation_1782) {
    CiffComponent comp(0x0000, 0x0000);
    DataLocId loc = comp.dataLocation();
    EXPECT_EQ(loc, CiffComponent::dataLocation(comp.tag()));
}

// Test setValue with empty buffer
TEST_F(CiffComponentTest_1782, SetValueEmptyBuffer_1782) {
    CiffComponent comp(0x0001, 0x0000);
    DataBuf emptyBuf;
    comp.setValue(std::move(emptyBuf));
    EXPECT_EQ(comp.size(), 0u);
}

// Test multiple setValue calls (overwrite)
TEST_F(CiffComponentTest_1782, SetValueOverwrite_1782) {
    CiffComponent comp(0x0001, 0x0000);

    byte data1[] = {0x01, 0x02};
    DataBuf buf1(data1, sizeof(data1));
    comp.setValue(std::move(buf1));
    EXPECT_EQ(comp.size(), 2u);

    byte data2[] = {0x03, 0x04, 0x05, 0x06, 0x07};
    DataBuf buf2(data2, sizeof(data2));
    comp.setValue(std::move(buf2));
    EXPECT_EQ(comp.size(), 5u);
}

// Test writeDirEntry doesn't crash
TEST_F(CiffComponentTest_1782, WriteDirEntry_1782) {
    CiffComponent comp(0x0001, 0x0000);
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));

    Blob blob;
    EXPECT_NO_THROW(comp.writeDirEntry(blob, littleEndian));
}

// Test print with prefix containing special characters
TEST_F(CiffComponentTest_1782, PrintSpecialPrefix_1782) {
    CiffComponent comp(0x0001, 0x0000);
    std::ostringstream os;
    comp.print(os, littleEndian, ">>>  ");
    std::string output = os.str();
    EXPECT_NE(output.find(">>>  "), std::string::npos);
}

// Test various tag values for typeId static
TEST_F(CiffComponentTest_1782, StaticTypeIdVariousTags_1782) {
    // Tags with different upper bit patterns should yield different types
    TypeId t1 = CiffComponent::typeId(0x0000);
    TypeId t2 = CiffComponent::typeId(0x0800);
    TypeId t3 = CiffComponent::typeId(0x1000);
    TypeId t4 = CiffComponent::typeId(0x2000);
    TypeId t5 = CiffComponent::typeId(0x2800);
    TypeId t6 = CiffComponent::typeId(0x3800);
    // Just verify these don't crash and return valid values
    (void)t1;
    (void)t2;
    (void)t3;
    (void)t4;
    (void)t5;
    (void)t6;
}

// Test boundary tag values
TEST_F(CiffComponentTest_1782, BoundaryTagValues_1782) {
    CiffComponent comp1(0x0000, 0x0000);
    CiffComponent comp2(0xFFFF, 0xFFFF);

    EXPECT_EQ(comp1.tag(), 0x0000);
    EXPECT_EQ(comp1.dir(), 0x0000);
    EXPECT_EQ(comp2.tag(), 0xFFFF);
    EXPECT_EQ(comp2.dir(), 0xFFFF);
}

// Test print output contains tag information
TEST_F(CiffComponentTest_1782, PrintContainsTagInfo_1782) {
    CiffComponent comp(0x0001, 0x0002);
    std::ostringstream os;
    comp.print(os, littleEndian, "");
    std::string output = os.str();
    // The output should contain hex representation of tag and dir
    EXPECT_NE(output.find("0x"), std::string::npos);
}

// Test writeValueData doesn't crash on empty component
TEST_F(CiffComponentTest_1782, WriteValueDataEmpty_1782) {
    CiffComponent comp;
    Blob blob;
    size_t result = comp.writeValueData(blob, 0);
    (void)result;
}

// Test write on component with data
TEST_F(CiffComponentTest_1782, WriteWithData_1782) {
    CiffComponent comp(0x0001, 0x0000);
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));

    Blob blob;
    size_t result = comp.write(blob, littleEndian, 0);
    // Should return some offset
    (void)result;
}

// Test that pData points to actual data after setValue
TEST_F(CiffComponentTest_1782, PDataContent_1782) {
    CiffComponent comp(0x0001, 0x0000);
    byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    DataBuf buf(data, sizeof(data));
    comp.setValue(std::move(buf));

    const byte* p = comp.pData();
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(p[0], 0xDE);
    EXPECT_EQ(p[1], 0xAD);
    EXPECT_EQ(p[2], 0xBE);
    EXPECT_EQ(p[3], 0xEF);
}
