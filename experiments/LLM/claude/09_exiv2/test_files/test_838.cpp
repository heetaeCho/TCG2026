#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "exiv2/value.hpp"

using namespace Exiv2;

class XmpTextValueWriteTest_838 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Default XmpTextValue with no value writes empty string
TEST_F(XmpTextValueWriteTest_838, DefaultEmptyValue_838) {
    XmpTextValue val;
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "");
}

// Test: XmpTextValue with plain text, no array type or struct
TEST_F(XmpTextValueWriteTest_838, PlainTextNoTypeNoStruct_838) {
    XmpTextValue val;
    val.read("Hello World");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "Hello World");
}

// Test: XmpTextValue constructed with string argument
TEST_F(XmpTextValueWriteTest_838, ConstructorWithString_838) {
    XmpTextValue val("Test Value");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "Test Value");
}

// Test: XmpTextValue with xaAlt array type and non-empty value
TEST_F(XmpTextValueWriteTest_838, AltArrayTypeWithValue_838) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaAlt);
    val.read("some value");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "type=\"Alt\" some value");
}

// Test: XmpTextValue with xaBag array type and non-empty value
TEST_F(XmpTextValueWriteTest_838, BagArrayTypeWithValue_838) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaBag);
    val.read("bag value");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "type=\"Bag\" bag value");
}

// Test: XmpTextValue with xaSeq array type and non-empty value
TEST_F(XmpTextValueWriteTest_838, SeqArrayTypeWithValue_838) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaSeq);
    val.read("seq value");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "type=\"Seq\" seq value");
}

// Test: XmpTextValue with xaAlt array type and empty value (no space after type)
TEST_F(XmpTextValueWriteTest_838, AltArrayTypeEmptyValue_838) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaAlt);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "type=\"Alt\"");
}

// Test: XmpTextValue with xaBag array type and empty value
TEST_F(XmpTextValueWriteTest_838, BagArrayTypeEmptyValue_838) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaBag);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "type=\"Bag\"");
}

// Test: XmpTextValue with xaSeq array type and empty value
TEST_F(XmpTextValueWriteTest_838, SeqArrayTypeEmptyValue_838) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaSeq);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "type=\"Seq\"");
}

// Test: XmpTextValue with xsStruct and non-empty value
TEST_F(XmpTextValueWriteTest_838, StructTypeWithValue_838) {
    XmpTextValue val;
    val.setXmpStruct(XmpValue::xsStruct);
    val.read("struct value");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "type=\"Struct\" struct value");
}

// Test: XmpTextValue with xsStruct and empty value (no space)
TEST_F(XmpTextValueWriteTest_838, StructTypeEmptyValue_838) {
    XmpTextValue val;
    val.setXmpStruct(XmpValue::xsStruct);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "type=\"Struct\"");
}

// Test: XmpTextValue with xaNone array type behaves like no type
TEST_F(XmpTextValueWriteTest_838, NoneArrayTypeWithValue_838) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaNone);
    val.read("just text");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "just text");
}

// Test: XmpTextValue with xsNone struct type behaves like no type
TEST_F(XmpTextValueWriteTest_838, NoneStructTypeWithValue_838) {
    XmpTextValue val;
    val.setXmpStruct(XmpValue::xsNone);
    val.read("just text");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "just text");
}

// Test: Array type takes precedence over struct type when both are set
TEST_F(XmpTextValueWriteTest_838, ArrayTypePrecedenceOverStruct_838) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaBag);
    val.setXmpStruct(XmpValue::xsStruct);
    val.read("priority test");
    std::ostringstream os;
    val.write(os);
    // xmpArrayType != xaNone, so the array branch is taken first
    EXPECT_EQ(os.str(), "type=\"Bag\" priority test");
}

// Test: Write returns the ostream reference
TEST_F(XmpTextValueWriteTest_838, WriteReturnsOstream_838) {
    XmpTextValue val;
    val.read("test");
    std::ostringstream os;
    std::ostream& result = val.write(os);
    EXPECT_EQ(&result, &os);
}

// Test: Value with special characters
TEST_F(XmpTextValueWriteTest_838, SpecialCharactersInValue_838) {
    XmpTextValue val;
    val.read("value with <special> & \"chars\"");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "value with <special> & \"chars\"");
}

// Test: Value with newlines and whitespace
TEST_F(XmpTextValueWriteTest_838, ValueWithNewlines_838) {
    XmpTextValue val;
    val.read("line1\nline2\tline3");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "line1\nline2\tline3");
}

// Test: Multiple writes to same stream
TEST_F(XmpTextValueWriteTest_838, MultipleWritesToSameStream_838) {
    XmpTextValue val1;
    val1.read("first");
    XmpTextValue val2;
    val2.setXmpArrayType(XmpValue::xaAlt);
    val2.read("second");

    std::ostringstream os;
    val1.write(os);
    os << "|";
    val2.write(os);
    EXPECT_EQ(os.str(), "first|type=\"Alt\" second");
}

// Test: Very long value string
TEST_F(XmpTextValueWriteTest_838, LongValueString_838) {
    std::string longStr(10000, 'x');
    XmpTextValue val;
    val.read(longStr);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), longStr);
}

// Test: Long value string with array type
TEST_F(XmpTextValueWriteTest_838, LongValueStringWithArrayType_838) {
    std::string longStr(1000, 'a');
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaSeq);
    val.read(longStr);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "type=\"Seq\" " + longStr);
}

// Test: Empty string value with neither array type nor struct
TEST_F(XmpTextValueWriteTest_838, EmptyStringNoTypeNoStruct_838) {
    XmpTextValue val;
    val.read("");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "");
}

// Test: Value containing only spaces
TEST_F(XmpTextValueWriteTest_838, ValueContainingOnlySpaces_838) {
    XmpTextValue val;
    val.read("   ");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "   ");
}

// Test: Value containing only spaces with array type
TEST_F(XmpTextValueWriteTest_838, SpacesValueWithArrayType_838) {
    XmpTextValue val;
    val.setXmpArrayType(XmpValue::xaBag);
    val.read("   ");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "type=\"Bag\"    ");
}

// Test: size() returns correct size for text value
TEST_F(XmpTextValueWriteTest_838, SizeReturnsCorrectValue_838) {
    XmpTextValue val;
    val.read("hello");
    EXPECT_EQ(val.size(), 5u);
}

// Test: count() for text value
TEST_F(XmpTextValueWriteTest_838, CountForTextValue_838) {
    XmpTextValue val;
    val.read("test");
    EXPECT_EQ(val.count(), 1u);
}

// Test: read() returns 0 on success
TEST_F(XmpTextValueWriteTest_838, ReadReturnsZero_838) {
    XmpTextValue val;
    int result = val.read("test string");
    EXPECT_EQ(result, 0);
}

// Test: toInt64 for numeric string
TEST_F(XmpTextValueWriteTest_838, ToInt64ForNumericString_838) {
    XmpTextValue val;
    val.read("42");
    EXPECT_EQ(val.toInt64(0), 42);
}

// Test: toUint32 for numeric string
TEST_F(XmpTextValueWriteTest_838, ToUint32ForNumericString_838) {
    XmpTextValue val;
    val.read("100");
    EXPECT_EQ(val.toUint32(0), 100u);
}

// Test: toFloat for numeric string
TEST_F(XmpTextValueWriteTest_838, ToFloatForNumericString_838) {
    XmpTextValue val;
    val.read("3.14");
    EXPECT_NEAR(val.toFloat(0), 3.14f, 0.01f);
}

// Test: clone produces equivalent value
TEST_F(XmpTextValueWriteTest_838, CloneProducesEquivalentValue_838) {
    XmpTextValue val;
    val.read("clone test");
    val.setXmpArrayType(XmpValue::xaBag);
    auto cloned = val.clone();
    
    std::ostringstream os1, os2;
    val.write(os1);
    cloned->write(os2);
    EXPECT_EQ(os1.str(), os2.str());
}

// Test: xmpArrayType getter returns what was set
TEST_F(XmpTextValueWriteTest_838, XmpArrayTypeGetterSetter_838) {
    XmpTextValue val;
    EXPECT_EQ(val.xmpArrayType(), XmpValue::xaNone);
    val.setXmpArrayType(XmpValue::xaAlt);
    EXPECT_EQ(val.xmpArrayType(), XmpValue::xaAlt);
    val.setXmpArrayType(XmpValue::xaBag);
    EXPECT_EQ(val.xmpArrayType(), XmpValue::xaBag);
    val.setXmpArrayType(XmpValue::xaSeq);
    EXPECT_EQ(val.xmpArrayType(), XmpValue::xaSeq);
}

// Test: xmpStruct getter returns what was set
TEST_F(XmpTextValueWriteTest_838, XmpStructGetterSetter_838) {
    XmpTextValue val;
    EXPECT_EQ(val.xmpStruct(), XmpValue::xsNone);
    val.setXmpStruct(XmpValue::xsStruct);
    EXPECT_EQ(val.xmpStruct(), XmpValue::xsStruct);
}
