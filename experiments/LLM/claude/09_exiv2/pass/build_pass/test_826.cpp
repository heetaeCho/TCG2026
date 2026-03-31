#include <gtest/gtest.h>
#include <exiv2/value.hpp>

using namespace Exiv2;

// We need a concrete subclass of XmpValue since XmpValue inherits from Value
// and may be abstract. We'll use XmpTextValue which is a concrete XmpValue subclass.

class XmpValueTest_826 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test default XmpArrayType is xaNone
TEST_F(XmpValueTest_826, DefaultXmpArrayTypeIsNone_826) {
    XmpTextValue val;
    EXPECT_EQ(XmpValue::xaNone, val.xmpArrayType());
}

// Test default XmpStruct is xsNone
TEST_F(XmpValueTest_826, DefaultXmpStructIsNone_826) {
    XmpTextValue val;
    EXPECT_EQ(XmpValue::xsNone, val.xmpStruct());
}

// Test setXmpArrayType with xaAlt
TEST_F(XmpValueTest_826, SetXmpArrayTypeAlt_826) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaAlt);
    EXPECT_EQ(XmpValue::xaAlt, val.xmpArrayType());
}

// Test setXmpArrayType with xaBag
TEST_F(XmpValueTest_826, SetXmpArrayTypeBag_826) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaBag);
    EXPECT_EQ(XmpValue::xaBag, val.xmpArrayType());
}

// Test setXmpArrayType with xaSeq
TEST_F(XmpValueTest_826, SetXmpArrayTypeSeq_826) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaSeq);
    EXPECT_EQ(XmpValue::xaSeq, val.xmpArrayType());
}

// Test setXmpArrayType with xaNone
TEST_F(XmpValueTest_826, SetXmpArrayTypeNone_826) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaBag);
    EXPECT_EQ(XmpValue::xaBag, val.xmpArrayType());
    val.setXmpArrayType(XmpValue::xaNone);
    EXPECT_EQ(XmpValue::xaNone, val.xmpArrayType());
}

// Test setXmpStruct with xsStruct
TEST_F(XmpValueTest_826, SetXmpStructStruct_826) {
    XmpTextValue val;
    val.setXmpStruct(XmpValue::xsStruct);
    EXPECT_EQ(XmpValue::xsStruct, val.xmpStruct());
}

// Test setXmpStruct with xsNone
TEST_F(XmpValueTest_826, SetXmpStructNone_826) {
    XmpTextValue val;
    val.setXmpStruct(XmpValue::xsStruct);
    EXPECT_EQ(XmpValue::xsStruct, val.xmpStruct());
    val.setXmpStruct(XmpValue::xsNone);
    EXPECT_EQ(XmpValue::xsNone, val.xmpStruct());
}

// Test setXmpArrayType multiple times (overwrite)
TEST_F(XmpValueTest_826, SetXmpArrayTypeOverwrite_826) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaAlt);
    EXPECT_EQ(XmpValue::xaAlt, val.xmpArrayType());
    val.setXmpArrayType(XmpValue::xaSeq);
    EXPECT_EQ(XmpValue::xaSeq, val.xmpArrayType());
    val.setXmpArrayType(XmpValue::xaBag);
    EXPECT_EQ(XmpValue::xaBag, val.xmpArrayType());
}

// Test static xmpArrayType(TypeId) for xmpAlt
TEST_F(XmpValueTest_826, StaticXmpArrayTypeAlt_826) {
    EXPECT_EQ(XmpValue::xaAlt, XmpValue::xmpArrayType(xmpAlt));
}

// Test static xmpArrayType(TypeId) for xmpBag
TEST_F(XmpValueTest_826, StaticXmpArrayTypeBag_826) {
    EXPECT_EQ(XmpValue::xaBag, XmpValue::xmpArrayType(xmpBag));
}

// Test static xmpArrayType(TypeId) for xmpSeq
TEST_F(XmpValueTest_826, StaticXmpArrayTypeSeq_826) {
    EXPECT_EQ(XmpValue::xaSeq, XmpValue::xmpArrayType(xmpSeq));
}

// Test static xmpArrayType(TypeId) for xmpText (non-array type should return xaNone)
TEST_F(XmpValueTest_826, StaticXmpArrayTypeText_826) {
    EXPECT_EQ(XmpValue::xaNone, XmpValue::xmpArrayType(xmpText));
}

// Test read from string
TEST_F(XmpValueTest_826, ReadFromString_826) {
    XmpTextValue val;
    int result = val.read("Hello World");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Hello World", val.toString());
}

// Test read from empty string
TEST_F(XmpValueTest_826, ReadFromEmptyString_826) {
    XmpTextValue val;
    int result = val.read("");
    EXPECT_EQ(0, result);
}

// Test size after reading a string
TEST_F(XmpValueTest_826, SizeAfterRead_826) {
    XmpTextValue val;
    val.read("Test");
    EXPECT_EQ(4u, val.size());
}

// Test size of empty value
TEST_F(XmpValueTest_826, SizeEmpty_826) {
    XmpTextValue val;
    EXPECT_EQ(0u, val.size());
}

// Test copy function
TEST_F(XmpValueTest_826, CopyToBuffer_826) {
    XmpTextValue val;
    val.read("ABCD");
    byte buf[10] = {0};
    size_t copied = val.copy(buf, bigEndian);
    EXPECT_EQ(4u, copied);
    EXPECT_EQ('A', buf[0]);
    EXPECT_EQ('B', buf[1]);
    EXPECT_EQ('C', buf[2]);
    EXPECT_EQ('D', buf[3]);
}

// Test read from byte buffer
TEST_F(XmpValueTest_826, ReadFromByteBuffer_826) {
    XmpTextValue val;
    const byte data[] = {'H', 'i'};
    int result = val.read(data, 2, bigEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ("Hi", val.toString());
}

// Test that setXmpArrayType and setXmpStruct are independent
TEST_F(XmpValueTest_826, ArrayTypeAndStructIndependent_826) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaBag);
    val.setXmpStruct(XmpValue::xsStruct);
    EXPECT_EQ(XmpValue::xaBag, val.xmpArrayType());
    EXPECT_EQ(XmpValue::xsStruct, val.xmpStruct());
}

// Test reading longer string
TEST_F(XmpValueTest_826, ReadLongString_826) {
    XmpTextValue val;
    std::string longStr(1000, 'x');
    val.read(longStr);
    EXPECT_EQ(1000u, val.size());
    EXPECT_EQ(longStr, val.toString());
}

// Test XmpArrayValue with xaBag
TEST_F(XmpValueTest_826, XmpArrayValueBag_826) {
    XmpArrayValue val(xmpBag);
    EXPECT_EQ(XmpValue::xaBag, val.xmpArrayType());
}

// Test XmpArrayValue with xaSeq
TEST_F(XmpValueTest_826, XmpArrayValueSeq_826) {
    XmpArrayValue val(xmpSeq);
    EXPECT_EQ(XmpValue::xaSeq, val.xmpArrayType());
}

// Test XmpArrayValue with xaAlt
TEST_F(XmpValueTest_826, XmpArrayValueAlt_826) {
    XmpArrayValue val(xmpAlt);
    EXPECT_EQ(XmpValue::xaAlt, val.xmpArrayType());
}
