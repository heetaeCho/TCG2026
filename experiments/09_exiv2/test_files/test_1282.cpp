#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpdatumTest_1282 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create an XmpKey for use in tests

        xmpKey = std::make_unique<XmpKey>("Xmp.dc.title", "Title");

        xmpDatum = std::make_unique<Xmpdatum>(*xmpKey, nullptr);

    }



    std::unique_ptr<XmpKey> xmpKey;

    std::unique_ptr<Xmpdatum> xmpDatum;

};



TEST_F(XmpdatumTest_1282, TagName_ReturnsCorrectValue_1282) {

    EXPECT_EQ(xmpDatum->tagName(), "title");

}



TEST_F(XmpdatumTest_1282, Key_ReturnsCorrectValue_1282) {

    EXPECT_EQ(xmpDatum->key(), "Xmp.dc.title");

}



TEST_F(XmpdatumTest_1282, FamilyName_ReturnsCorrectValue_1282) {

    EXPECT_EQ(xmpDatum->familyName(), "Xmp");

}



TEST_F(XmpdatumTest_1282, GroupName_ReturnsCorrectValue_1282) {

    EXPECT_EQ(xmpDatum->groupName(), "dc");

}



TEST_F(XmpdatumTest_1282, TagLabel_ReturnsEmptyString_1282) {

    EXPECT_EQ(xmpDatum->tagLabel(), "");

}



TEST_F(XmpdatumTest_1282, TagDesc_ReturnsEmptyString_1282) {

    EXPECT_EQ(xmpDatum->tagDesc(), "");

}



TEST_F(XmpdatumTest_1282, Tag_ReturnsZero_1282) {

    EXPECT_EQ(xmpDatum->tag(), 0);

}



TEST_F(XmpdatumTest_1282, TypeId_ReturnsUnknown_1282) {

    EXPECT_EQ(xmpDatum->typeId(), Exiv2::undefined);

}



TEST_F(XmpdatumTest_1282, TypeName_ReturnsEmptyString_1282) {

    EXPECT_EQ(xmpDatum->typeName(), "");

}



TEST_F(XmpdatumTest_1282, TypeSize_ReturnsZero_1282) {

    EXPECT_EQ(xmpDatum->typeSize(), 0);

}



TEST_F(XmpdatumTest_1282, Count_ReturnsZero_1282) {

    EXPECT_EQ(xmpDatum->count(), 0);

}



TEST_F(XmpdatumTest_1282, Size_ReturnsZero_1282) {

    EXPECT_EQ(xmpDatum->size(), 0);

}



TEST_F(XmpdatumTest_1282, ToString_ReturnsEmptyString_1282) {

    EXPECT_EQ(xmpDatum->toString(), "");

}



TEST_F(XmpdatumTest_1282, ToInt64_ReturnsZero_1282) {

    EXPECT_EQ(xmpDatum->toInt64(0), 0);

}



TEST_F(XmpdatumTest_1282, ToFloat_ReturnsZero_1282) {

    EXPECT_FLOAT_EQ(xmpDatum->toFloat(0), 0.0f);

}



TEST_F(XmpdatumTest_1282, ToRational_ReturnsZeroOverOne_1282) {

    EXPECT_EQ(xmpDatum->toRational(0), Rational(0, 1));

}
