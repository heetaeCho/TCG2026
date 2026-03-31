#include <gtest/gtest.h>
#include <exiv2/value.hpp>

using namespace Exiv2;

// XmpTextValue is a concrete subclass of XmpValue that we can instantiate
class XmpValueTest_830 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test default xmpStruct value is xsNone
TEST_F(XmpValueTest_830, DefaultXmpStructIsNone_830) {
    XmpTextValue value;
    EXPECT_EQ(XmpValue::xsNone, value.xmpStruct());
}

// Test default xmpArrayType value is xaNone
TEST_F(XmpValueTest_830, DefaultXmpArrayTypeIsNone_830) {
    XmpTextValue value;
    EXPECT_EQ(XmpValue::xaNone, value.xmpArrayType());
}

// Test setXmpStruct and xmpStruct
TEST_F(XmpValueTest_830, SetXmpStructStruct_830) {
    XmpTextValue value;
    value.setXmpStruct(XmpValue::xsStruct);
    EXPECT_EQ(XmpValue::xsStruct, value.xmpStruct());
}

// Test setXmpStruct back to xsNone
TEST_F(XmpValueTest_830, SetXmpStructNone_830) {
    XmpTextValue value;
    value.setXmpStruct(XmpValue::xsStruct);
    value.setXmpStruct(XmpValue::xsNone);
    EXPECT_EQ(XmpValue::xsNone, value.xmpStruct());
}

// Test setXmpArrayType with xaAlt
TEST_F(XmpValueTest_830, SetXmpArrayTypeAlt_830) {
    XmpTextValue value;
    value.setXmpArrayType(XmpValue::xaAlt);
    EXPECT_EQ(XmpValue::xaAlt, value.xmpArrayType());
}

// Test setXmpArrayType with xaBag
TEST_F(XmpValueTest_830, SetXmpArrayTypeBag_830) {
    XmpTextValue value;
    value.setXmpArrayType(XmpValue::xaBag);
    EXPECT_EQ(XmpValue::xaBag, value.xmpArrayType());
}

// Test setXmpArrayType with xaSeq
TEST_F(XmpValueTest_830, SetXmpArrayTypeSeq_830) {
    XmpTextValue value;
    value.setXmpArrayType(XmpValue::xaSeq);
    EXPECT_EQ(XmpValue::xaSeq, value.xmpArrayType());
}

// Test setXmpArrayType back to xaNone
TEST_F(XmpValueTest_830, SetXmpArrayTypeNone_830) {
    XmpTextValue value;
    value.setXmpArrayType(XmpValue::xaSeq);
    value.setXmpArrayType(XmpValue::xaNone);
    EXPECT_EQ(XmpValue::xaNone, value.xmpArrayType());
}

// Test static xmpArrayType(TypeId) for xmpAlt
TEST_F(XmpValueTest_830, StaticXmpArrayTypeAlt_830) {
    EXPECT_EQ(XmpValue::xaAlt, XmpValue::xmpArrayType(xmpAlt));
}

// Test static xmpArrayType(TypeId) for xmpBag
TEST_F(XmpValueTest_830, StaticXmpArrayTypeBag_830) {
    EXPECT_EQ(XmpValue::xaBag, XmpValue::xmpArrayType(xmpBag));
}

// Test static xmpArrayType(TypeId) for xmpSeq
TEST_F(XmpValueTest_830, StaticXmpArrayTypeSeq_830) {
    EXPECT_EQ(XmpValue::xaSeq, XmpValue::xmpArrayType(xmpSeq));
}

// Test static xmpArrayType(TypeId) for xmpText returns xaNone
TEST_F(XmpValueTest_830, StaticXmpArrayTypeText_830) {
    EXPECT_EQ(XmpValue::xaNone, XmpValue::xmpArrayType(xmpText));
}

// Test read from string
TEST_F(XmpValueTest_830, ReadFromString_830) {
    XmpTextValue value;
    std::string testStr = "Hello World";
    int result = value.read(testStr);
    EXPECT_EQ(0, result);
    EXPECT_EQ(testStr, value.toString());
}

// Test read from empty string
TEST_F(XmpValueTest_830, ReadFromEmptyString_830) {
    XmpTextValue value;
    std::string testStr = "";
    int result = value.read(testStr);
    EXPECT_EQ(0, result);
}

// Test size after reading a string
TEST_F(XmpValueTest_830, SizeAfterRead_830) {
    XmpTextValue value;
    std::string testStr = "TestValue";
    value.read(testStr);
    EXPECT_EQ(testStr.size(), value.size());
}

// Test size of empty value
TEST_F(XmpValueTest_830, SizeEmpty_830) {
    XmpTextValue value;
    value.read("");
    EXPECT_EQ(0u, value.size());
}

// Test copy function
TEST_F(XmpValueTest_830, CopyFunction_830) {
    XmpTextValue value;
    std::string testStr = "CopyTest";
    value.read(testStr);
    
    std::vector<byte> buf(testStr.size());
    size_t copied = value.copy(buf.data(), bigEndian);
    EXPECT_EQ(testStr.size(), copied);
    
    std::string result(reinterpret_cast<char*>(buf.data()), copied);
    EXPECT_EQ(testStr, result);
}

// Test read from byte buffer
TEST_F(XmpValueTest_830, ReadFromByteBuffer_830) {
    XmpTextValue value;
    std::string testStr = "ByteBuffer";
    const byte* buf = reinterpret_cast<const byte*>(testStr.c_str());
    int result = value.read(buf, testStr.size(), bigEndian);
    EXPECT_EQ(0, result);
    EXPECT_EQ(testStr, value.toString());
}

// Test that read overwrites previous value
TEST_F(XmpValueTest_830, ReadOverwritesPreviousValue_830) {
    XmpTextValue value;
    value.read("First");
    EXPECT_EQ("First", value.toString());
    
    value.read("Second");
    EXPECT_EQ("Second", value.toString());
}

// Test multiple set operations on xmpStruct
TEST_F(XmpValueTest_830, MultipleSetXmpStruct_830) {
    XmpTextValue value;
    value.setXmpStruct(XmpValue::xsStruct);
    EXPECT_EQ(XmpValue::xsStruct, value.xmpStruct());
    value.setXmpStruct(XmpValue::xsNone);
    EXPECT_EQ(XmpValue::xsNone, value.xmpStruct());
    value.setXmpStruct(XmpValue::xsStruct);
    EXPECT_EQ(XmpValue::xsStruct, value.xmpStruct());
}

// Test multiple set operations on xmpArrayType
TEST_F(XmpValueTest_830, MultipleSetXmpArrayType_830) {
    XmpTextValue value;
    value.setXmpArrayType(XmpValue::xaAlt);
    EXPECT_EQ(XmpValue::xaAlt, value.xmpArrayType());
    value.setXmpArrayType(XmpValue::xaBag);
    EXPECT_EQ(XmpValue::xaBag, value.xmpArrayType());
    value.setXmpArrayType(XmpValue::xaSeq);
    EXPECT_EQ(XmpValue::xaSeq, value.xmpArrayType());
    value.setXmpArrayType(XmpValue::xaNone);
    EXPECT_EQ(XmpValue::xaNone, value.xmpArrayType());
}

// Test copy with byte order littleEndian (should not matter for XmpValue)
TEST_F(XmpValueTest_830, CopyLittleEndian_830) {
    XmpTextValue value;
    std::string testStr = "EndianTest";
    value.read(testStr);
    
    std::vector<byte> buf(testStr.size());
    size_t copied = value.copy(buf.data(), littleEndian);
    EXPECT_EQ(testStr.size(), copied);
    
    std::string result(reinterpret_cast<char*>(buf.data()), copied);
    EXPECT_EQ(testStr, result);
}

// Test reading a long string
TEST_F(XmpValueTest_830, ReadLongString_830) {
    XmpTextValue value;
    std::string longStr(10000, 'A');
    int result = value.read(longStr);
    EXPECT_EQ(0, result);
    EXPECT_EQ(longStr.size(), value.size());
    EXPECT_EQ(longStr, value.toString());
}

// Test xmpArrayType with xmpText TypeId
TEST_F(XmpValueTest_830, StaticXmpArrayTypeForNonArrayType_830) {
    // For types that are not xmpBag, xmpSeq, or xmpAlt, should return xaNone
    EXPECT_EQ(XmpValue::xaNone, XmpValue::xmpArrayType(unsignedShort));
}
