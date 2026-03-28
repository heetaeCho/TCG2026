#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpdatumTest_1283 : public ::testing::Test {

protected:

    XmpKey key;

    Value::UniquePtr value;

    Xmpdatum xmpDatum;



    XmpdatumTest_1283()

        : key("Xmp.dc.title"), value(new StringValue("Sample Title")), xmpDatum(key, value.get()) {}

};



TEST_F(XmpdatumTest_1283, TagLabel_ReturnsCorrectValue_1283) {

    EXPECT_EQ(xmpDatum.tagLabel(), "title");

}



TEST_F(XmpdatumTest_1283, Key_ReturnsCorrectValue_1283) {

    EXPECT_EQ(xmpDatum.key(), "Xmp.dc.title");

}



TEST_F(XmpdatumTest_1283, FamilyName_ReturnsCorrectValue_1283) {

    EXPECT_EQ(xmpDatum.familyName(), "Xmp");

}



TEST_F(XmpdatumTest_1283, GroupName_ReturnsCorrectValue_1283) {

    EXPECT_EQ(xmpDatum.groupName(), "dc");

}



TEST_F(XmpdatumTest_1283, TagName_ReturnsCorrectValue_1283) {

    EXPECT_EQ(xmpDatum.tagName(), "title");

}



TEST_F(XmpdatumTest_1283, TagDesc_ReturnsEmptyString_1283) {

    EXPECT_EQ(xmpDatum.tagDesc(), "");

}



TEST_F(XmpdatumTest_1283, Tag_ReturnsZero_1283) {

    EXPECT_EQ(xmpDatum.tag(), 0);

}



TEST_F(XmpdatumTest_1283, TypeId_ReturnsCorrectValue_1283) {

    EXPECT_EQ(xmpDatum.typeId(), asciiString);

}



TEST_F(XmpdatumTest_1283, TypeName_ReturnsCorrectValue_1283) {

    EXPECT_STREQ(xmpDatum.typeName(), "Ascii");

}



TEST_F(XmpdatumTest_1283, TypeSize_ReturnsOne_1283) {

    EXPECT_EQ(xmpDatum.typeSize(), 1);

}



TEST_F(XmpdatumTest_1283, Count_ReturnsOne_1283) {

    EXPECT_EQ(xmpDatum.count(), 1);

}



TEST_F(XmpdatumTest_1283, Size_ReturnsCorrectValue_1283) {

    EXPECT_EQ(xmpDatum.size(), static_cast<size_t>(value->size()));

}



TEST_F(XmpdatumTest_1283, ToString_ReturnsCorrectValue_1283) {

    EXPECT_EQ(xmpDatum.toString(), "Sample Title");

}



TEST_F(XmpdatumTest_1283, ToStringWithIndex_ReturnsCorrectValue_1283) {

    EXPECT_EQ(xmpDatum.toString(0), "Sample Title");

}



TEST_F(XmpdatumTest_1283, ToInt64_ThrowsExceptionForInvalidConversion_1283) {

    EXPECT_THROW(xmpDatum.toInt64(0), Error);

}



TEST_F(XmpdatumTest_1283, ToFloat_ThrowsExceptionForInvalidConversion_1283) {

    EXPECT_THROW(xmpDatum.toFloat(0), Error);

}



TEST_F(XmpdatumTest_1283, ToRational_ThrowsExceptionForInvalidConversion_1283) {

    EXPECT_THROW(xmpDatum.toRational(0), Error);

}
