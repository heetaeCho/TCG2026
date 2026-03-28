#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class XmpdatumTest_1288 : public testing::Test {

protected:

    XmpKey key;

    const Value* pValue = nullptr;

    Xmpdatum xmpDatum;



    XmpdatumTest_1288() : key("Xmp.dc.title"), xmpDatum(key, pValue) {}

};



TEST_F(XmpdatumTest_1288, TypeSize_ReturnsZero_1288) {

    EXPECT_EQ(xmpDatum.typeSize(), 0);

}



TEST_F(XmpdatumTest_1288, Copy_ReturnsExpectedSize_1288) {

    byte buffer[10];

    ByteOrder byteOrder = littleEndian;

    EXPECT_CALL(*xmpDatum.getValue().get(), size()).WillOnce(Return(5));

    EXPECT_EQ(xmpDatum.copy(buffer, byteOrder), 5);

}



TEST_F(XmpdatumTest_1288, Write_ReturnsStreamReference_1288) {

    std::ostringstream os;

    const ExifData* pMetadata = nullptr;

    auto& resultStream = xmpDatum.write(os, pMetadata);

    EXPECT_EQ(&resultStream, &os);

}



TEST_F(XmpdatumTest_1288, Key_ReturnsKeyString_1288) {

    EXPECT_EQ(xmpDatum.key(), "Xmp.dc.title");

}



TEST_F(XmpdatumTest_1288, FamilyName_ReturnsExpectedString_1288) {

    EXPECT_STREQ(xmpDatum.familyName(), "Xmp");

}



TEST_F(XmpdatumTest_1288, GroupName_ReturnsExpectedString_1288) {

    EXPECT_EQ(xmpDatum.groupName(), "dc");

}



TEST_F(XmpdatumTest_1288, TagName_ReturnsExpectedString_1288) {

    EXPECT_EQ(xmpDatum.tagName(), "title");

}



TEST_F(XmpdatumTest_1288, TagLabel_ReturnsEmptyString_1288) {

    EXPECT_EQ(xmpDatum.tagLabel(), "");

}



TEST_F(XmpdatumTest_1288, TagDesc_ReturnsEmptyString_1288) {

    EXPECT_EQ(xmpDatum.tagDesc(), "");

}



TEST_F(XmpdatumTest_1288, Tag_ReturnsZero_1288) {

    EXPECT_EQ(xmpDatum.tag(), 0);

}



TEST_F(XmpdatumTest_1288, TypeId_ReturnsUnknownType_1288) {

    EXPECT_EQ(xmpDatum.typeId(), unknownTypeId);

}



TEST_F(XmpdatumTest_1288, TypeName_ReturnsExpectedString_1288) {

    EXPECT_STREQ(xmpDatum.typeName(), "XmpText");

}



TEST_F(XmpdatumTest_1288, Count_ReturnsOne_1288) {

    EXPECT_EQ(xmpDatum.count(), 1);

}



TEST_F(XmpdatumTest_1288, Size_ReturnsZero_1288) {

    EXPECT_EQ(xmpDatum.size(), 0);

}



TEST_F(XmpdatumTest_1288, ToString_ReturnsEmptyString_1288) {

    EXPECT_EQ(xmpDatum.toString(), "");

}



TEST_F(XmpdatumTest_1288, ToStringWithIndex_ReturnsEmptyString_1288) {

    EXPECT_EQ(xmpDatum.toString(0), "");

}



TEST_F(XmpdatumTest_1288, ToInt64_ReturnsZero_1288) {

    EXPECT_EQ(xmpDatum.toInt64(0), 0);

}



TEST_F(XmpdatumTest_1288, ToFloat_ReturnsZero_1288) {

    EXPECT_FLOAT_EQ(xmpDatum.toFloat(0), 0.0f);

}



TEST_F(XmpdatumTest_1288, ToRational_ReturnsDefaultRational_1288) {

    Rational expectedRational;

    EXPECT_EQ(xmpDatum.toRational(0), expectedRational);

}



TEST_F(XmpdatumTest_1288, GetValue_ReturnsNonNullUniquePtr_1288) {

    EXPECT_NE(xmpDatum.getValue().get(), nullptr);

}



TEST_F(XmpdatumTest_1288, Value_ReturnsReferenceToValue_1288) {

    const Value& value = xmpDatum.value();

    EXPECT_EQ(&value, xmpDatum.getValue().get());

}



TEST_F(XmpdatumTest_1288, SetValueWithPointer_SetsNewValue_1288) {

    // This test assumes that setting a new value does not change the return of typeSize

    const Value* newValue = nullptr;

    xmpDatum.setValue(newValue);

    EXPECT_EQ(xmpDatum.typeSize(), 0);

}



TEST_F(XmpdatumTest_1288, SetValueWithString_SetsNewValue_1288) {

    // This test assumes that setting a new value does not change the return of typeSize

    int result = xmpDatum.setValue("New Value");

    EXPECT_EQ(result, 0);

    EXPECT_EQ(xmpDatum.typeSize(), 0);

}



TEST_F(XmpdatumTest_1288, OperatorEqualWithValue_SetsNewValue_1288) {

    // This test assumes that setting a new value does not change the return of typeSize

    const Value* newValue = nullptr;

    xmpDatum = *newValue;

    EXPECT_EQ(xmpDatum.typeSize(), 0);

}



TEST_F(XmpdatumTest_1288, OperatorEqualWithXmpdatum_SetsNewValue_1288) {

    // This test assumes that setting a new value does not change the return of typeSize

    Xmpdatum other(key, pValue);

    xmpDatum = other;

    EXPECT_EQ(xmpDatum.typeSize(), 0);

}
