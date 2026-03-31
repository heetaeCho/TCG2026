#include <gtest/gtest.h>
#include <exiv2/value.hpp>

using namespace Exiv2;

// We need a concrete subclass of XmpValue since XmpValue inherits from Value
// and may be abstract. We'll use XmpTextValue which is a concrete XmpValue subclass.

class XmpValueTest_827 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that setXmpStruct sets the struct type and xmpStruct() returns it
TEST_F(XmpValueTest_827, SetXmpStructNone_827) {
    XmpTextValue val;
    val.setXmpStruct(XmpValue::xsNone);
    EXPECT_EQ(XmpValue::xsNone, val.xmpStruct());
}

TEST_F(XmpValueTest_827, SetXmpStructStruct_827) {
    XmpTextValue val;
    val.setXmpStruct(XmpValue::xsStruct);
    EXPECT_EQ(XmpValue::xsStruct, val.xmpStruct());
}

// Test that default xmpStruct is xsNone
TEST_F(XmpValueTest_827, DefaultXmpStructIsNone_827) {
    XmpTextValue val;
    EXPECT_EQ(XmpValue::xsNone, val.xmpStruct());
}

// Test that setXmpArrayType sets the array type and xmpArrayType() returns it
TEST_F(XmpValueTest_827, SetXmpArrayTypeNone_827) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaNone);
    EXPECT_EQ(XmpValue::xaNone, val.xmpArrayType());
}

TEST_F(XmpValueTest_827, SetXmpArrayTypeAlt_827) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaAlt);
    EXPECT_EQ(XmpValue::xaAlt, val.xmpArrayType());
}

TEST_F(XmpValueTest_827, SetXmpArrayTypeBag_827) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaBag);
    EXPECT_EQ(XmpValue::xaBag, val.xmpArrayType());
}

TEST_F(XmpValueTest_827, SetXmpArrayTypeSeq_827) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaSeq);
    EXPECT_EQ(XmpValue::xaSeq, val.xmpArrayType());
}

// Test that default xmpArrayType is xaNone
TEST_F(XmpValueTest_827, DefaultXmpArrayTypeIsNone_827) {
    XmpTextValue val;
    EXPECT_EQ(XmpValue::xaNone, val.xmpArrayType());
}

// Test read from string
TEST_F(XmpValueTest_827, ReadFromString_827) {
    XmpTextValue val;
    int result = val.read("Hello World");
    EXPECT_EQ(0, result);
    EXPECT_EQ("Hello World", val.toString());
}

// Test read from empty string
TEST_F(XmpValueTest_827, ReadFromEmptyString_827) {
    XmpTextValue val;
    int result = val.read("");
    EXPECT_EQ(0, result);
    EXPECT_EQ("", val.toString());
}

// Test size after reading
TEST_F(XmpValueTest_827, SizeAfterRead_827) {
    XmpTextValue val;
    val.read("test");
    EXPECT_EQ(4u, val.size());
}

// Test size of empty value
TEST_F(XmpValueTest_827, SizeOfEmptyValue_827) {
    XmpTextValue val;
    val.read("");
    EXPECT_EQ(0u, val.size());
}

// Test copy
TEST_F(XmpValueTest_827, CopyToBuffer_827) {
    XmpTextValue val;
    val.read("ABCD");
    byte buf[10] = {0};
    size_t copied = val.copy(buf, littleEndian);
    EXPECT_EQ(4u, copied);
    EXPECT_EQ('A', static_cast<char>(buf[0]));
    EXPECT_EQ('B', static_cast<char>(buf[1]));
    EXPECT_EQ('C', static_cast<char>(buf[2]));
    EXPECT_EQ('D', static_cast<char>(buf[3]));
}

// Test read from byte buffer
TEST_F(XmpValueTest_827, ReadFromByteBuffer_827) {
    XmpTextValue val;
    const byte buf[] = {'H', 'e', 'l', 'l', 'o'};
    int result = val.read(buf, 5, littleEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ("Hello", val.toString());
}

// Test overwriting with setXmpStruct
TEST_F(XmpValueTest_827, OverwriteXmpStruct_827) {
    XmpTextValue val;
    val.setXmpStruct(XmpValue::xsStruct);
    EXPECT_EQ(XmpValue::xsStruct, val.xmpStruct());
    val.setXmpStruct(XmpValue::xsNone);
    EXPECT_EQ(XmpValue::xsNone, val.xmpStruct());
}

// Test overwriting with setXmpArrayType
TEST_F(XmpValueTest_827, OverwriteXmpArrayType_827) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaSeq);
    EXPECT_EQ(XmpValue::xaSeq, val.xmpArrayType());
    val.setXmpArrayType(XmpValue::xaBag);
    EXPECT_EQ(XmpValue::xaBag, val.xmpArrayType());
}

// Test static xmpArrayType(TypeId)
TEST_F(XmpValueTest_827, StaticXmpArrayTypeFromTypeId_xmpSeq_827) {
    EXPECT_EQ(XmpValue::xaSeq, XmpValue::xmpArrayType(xmpSeq));
}

TEST_F(XmpValueTest_827, StaticXmpArrayTypeFromTypeId_xmpBag_827) {
    EXPECT_EQ(XmpValue::xaBag, XmpValue::xmpArrayType(xmpBag));
}

TEST_F(XmpValueTest_827, StaticXmpArrayTypeFromTypeId_xmpAlt_827) {
    EXPECT_EQ(XmpValue::xaAlt, XmpValue::xmpArrayType(xmpAlt));
}

TEST_F(XmpValueTest_827, StaticXmpArrayTypeFromTypeId_xmpText_827) {
    EXPECT_EQ(XmpValue::xaNone, XmpValue::xmpArrayType(xmpText));
}

// Test that re-reading overwrites previous value
TEST_F(XmpValueTest_827, ReReadOverwritesPreviousValue_827) {
    XmpTextValue val;
    val.read("first");
    EXPECT_EQ("first", val.toString());
    val.read("second");
    EXPECT_EQ("second", val.toString());
}

// Test reading a long string
TEST_F(XmpValueTest_827, ReadLongString_827) {
    XmpTextValue val;
    std::string longStr(10000, 'x');
    int result = val.read(longStr);
    EXPECT_EQ(0, result);
    EXPECT_EQ(10000u, val.size());
    EXPECT_EQ(longStr, val.toString());
}

// Test that setXmpStruct and setXmpArrayType are independent
TEST_F(XmpValueTest_827, StructAndArrayTypeIndependent_827) {
    XmpTextValue val;
    val.setXmpStruct(XmpValue::xsStruct);
    val.setXmpArrayType(XmpValue::xaSeq);
    EXPECT_EQ(XmpValue::xsStruct, val.xmpStruct());
    EXPECT_EQ(XmpValue::xaSeq, val.xmpArrayType());
}
