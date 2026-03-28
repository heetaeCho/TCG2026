#include <gtest/gtest.h>
#include <exiv2/value.hpp>

using namespace Exiv2;

// We need a concrete subclass of XmpValue since XmpValue is abstract
// XmpTextValue is a concrete subclass available in exiv2
class XmpValueTest_828 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that default xmpArrayType is xaNone
TEST_F(XmpValueTest_828, DefaultXmpArrayTypeIsNone_828) {
    XmpTextValue value;
    EXPECT_EQ(XmpValue::xaNone, value.xmpArrayType());
}

// Test that default xmpStruct is xsNone
TEST_F(XmpValueTest_828, DefaultXmpStructIsNone_828) {
    XmpTextValue value;
    EXPECT_EQ(XmpValue::xsNone, value.xmpStruct());
}

// Test setXmpArrayType and xmpArrayType getter
TEST_F(XmpValueTest_828, SetXmpArrayTypeAlt_828) {
    XmpTextValue value;
    value.setXmpArrayType(XmpValue::xaAlt);
    EXPECT_EQ(XmpValue::xaAlt, value.xmpArrayType());
}

TEST_F(XmpValueTest_828, SetXmpArrayTypeBag_828) {
    XmpTextValue value;
    value.setXmpArrayType(XmpValue::xaBag);
    EXPECT_EQ(XmpValue::xaBag, value.xmpArrayType());
}

TEST_F(XmpValueTest_828, SetXmpArrayTypeSeq_828) {
    XmpTextValue value;
    value.setXmpArrayType(XmpValue::xaSeq);
    EXPECT_EQ(XmpValue::xaSeq, value.xmpArrayType());
}

TEST_F(XmpValueTest_828, SetXmpArrayTypeNone_828) {
    XmpTextValue value;
    value.setXmpArrayType(XmpValue::xaBag);
    value.setXmpArrayType(XmpValue::xaNone);
    EXPECT_EQ(XmpValue::xaNone, value.xmpArrayType());
}

// Test setXmpStruct and xmpStruct getter
TEST_F(XmpValueTest_828, SetXmpStructStruct_828) {
    XmpTextValue value;
    value.setXmpStruct(XmpValue::xsStruct);
    EXPECT_EQ(XmpValue::xsStruct, value.xmpStruct());
}

TEST_F(XmpValueTest_828, SetXmpStructNone_828) {
    XmpTextValue value;
    value.setXmpStruct(XmpValue::xsStruct);
    value.setXmpStruct(XmpValue::xsNone);
    EXPECT_EQ(XmpValue::xsNone, value.xmpStruct());
}

// Test read from string
TEST_F(XmpValueTest_828, ReadStringNormal_828) {
    XmpTextValue value;
    int result = value.read("Hello World");
    EXPECT_EQ(0, result);
}

// Test size after reading a string
TEST_F(XmpValueTest_828, SizeAfterReadString_828) {
    XmpTextValue value;
    value.read("Hello");
    EXPECT_EQ(5u, value.size());
}

// Test size of empty value
TEST_F(XmpValueTest_828, SizeEmpty_828) {
    XmpTextValue value;
    value.read("");
    EXPECT_EQ(0u, value.size());
}

// Test read from byte buffer
TEST_F(XmpValueTest_828, ReadFromByteBuffer_828) {
    XmpTextValue value;
    const std::string data = "Test data";
    int result = value.read(reinterpret_cast<const byte*>(data.c_str()), data.size(), littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ(data.size(), value.size());
}

// Test copy to buffer
TEST_F(XmpValueTest_828, CopyToBuffer_828) {
    XmpTextValue value;
    value.read("ABCDE");
    byte buf[10] = {0};
    size_t copied = value.copy(buf, littleEndian);
    EXPECT_EQ(5u, copied);
    EXPECT_EQ('A', buf[0]);
    EXPECT_EQ('B', buf[1]);
    EXPECT_EQ('C', buf[2]);
    EXPECT_EQ('D', buf[3]);
    EXPECT_EQ('E', buf[4]);
}

// Test copy with big endian (should not affect XmpValue)
TEST_F(XmpValueTest_828, CopyToBufferBigEndian_828) {
    XmpTextValue value;
    value.read("XYZ");
    byte buf[10] = {0};
    size_t copied = value.copy(buf, bigEndian);
    EXPECT_EQ(3u, copied);
    EXPECT_EQ('X', buf[0]);
    EXPECT_EQ('Y', buf[1]);
    EXPECT_EQ('Z', buf[2]);
}

// Test static xmpArrayType(TypeId) method
TEST_F(XmpValueTest_828, StaticXmpArrayTypeFromTypeIdXmpAlt_828) {
    EXPECT_EQ(XmpValue::xaAlt, XmpValue::xmpArrayType(xmpAlt));
}

TEST_F(XmpValueTest_828, StaticXmpArrayTypeFromTypeIdXmpBag_828) {
    EXPECT_EQ(XmpValue::xaBag, XmpValue::xmpArrayType(xmpBag));
}

TEST_F(XmpValueTest_828, StaticXmpArrayTypeFromTypeIdXmpSeq_828) {
    EXPECT_EQ(XmpValue::xaSeq, XmpValue::xmpArrayType(xmpSeq));
}

TEST_F(XmpValueTest_828, StaticXmpArrayTypeFromTypeIdXmpText_828) {
    EXPECT_EQ(XmpValue::xaNone, XmpValue::xmpArrayType(xmpText));
}

// Test overwriting array type multiple times
TEST_F(XmpValueTest_828, OverwriteXmpArrayTypeMultipleTimes_828) {
    XmpTextValue value;
    value.setXmpArrayType(XmpValue::xaAlt);
    EXPECT_EQ(XmpValue::xaAlt, value.xmpArrayType());
    value.setXmpArrayType(XmpValue::xaBag);
    EXPECT_EQ(XmpValue::xaBag, value.xmpArrayType());
    value.setXmpArrayType(XmpValue::xaSeq);
    EXPECT_EQ(XmpValue::xaSeq, value.xmpArrayType());
}

// Test reading a long string
TEST_F(XmpValueTest_828, ReadLongString_828) {
    XmpTextValue value;
    std::string longStr(10000, 'A');
    int result = value.read(longStr);
    EXPECT_EQ(0, result);
    EXPECT_EQ(10000u, value.size());
}

// Test that copy size matches the value size
TEST_F(XmpValueTest_828, CopySizeMatchesValueSize_828) {
    XmpTextValue value;
    value.read("Test123");
    byte buf[20] = {0};
    size_t copied = value.copy(buf, littleEndian);
    EXPECT_EQ(value.size(), copied);
}

// Test XmpArrayValue with xaBag
TEST_F(XmpValueTest_828, XmpArrayValueBag_828) {
    XmpArrayValue value(xmpBag);
    EXPECT_EQ(XmpValue::xaBag, value.xmpArrayType());
}

// Test XmpArrayValue with xaSeq
TEST_F(XmpValueTest_828, XmpArrayValueSeq_828) {
    XmpArrayValue value(xmpSeq);
    EXPECT_EQ(XmpValue::xaSeq, value.xmpArrayType());
}

// Test XmpArrayValue with xaAlt
TEST_F(XmpValueTest_828, XmpArrayValueAlt_828) {
    XmpArrayValue value(xmpAlt);
    EXPECT_EQ(XmpValue::xaAlt, value.xmpArrayType());
}
