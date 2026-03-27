#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class XmpdatumTest_1279 : public ::testing::Test {

protected:

    std::string testKey = "Xmp.dc.title";

    XmpKey xmpKey;

    Xmpdatum xmpDatum;



    void SetUp() override {

        xmpKey = XmpKey(testKey);

        xmpDatum = Xmpdatum(xmpKey, nullptr);

    }

};



TEST_F(XmpdatumTest_1279, Key_ReturnsCorrectValue_1279) {

    EXPECT_EQ(xmpDatum.key(), testKey);

}



TEST_F(XmpdatumTest_1279, FamilyName_ReturnsCorrectValue_1279) {

    EXPECT_EQ(xmpDatum.familyName(), "Xmp");

}



TEST_F(XmpdatumTest_1279, GroupName_ReturnsCorrectValue_1279) {

    EXPECT_EQ(xmpDatum.groupName(), "dc");

}



TEST_F(XmpdatumTest_1279, TagName_ReturnsCorrectValue_1279) {

    EXPECT_EQ(xmpDatum.tagName(), "title");

}



TEST_F(XmpdatumTest_1279, TagLabel_ReturnsEmptyString_1279) {

    EXPECT_EQ(xmpDatum.tagLabel(), "");

}



TEST_F(XmpdatumTest_1279, TagDesc_ReturnsEmptyString_1279) {

    EXPECT_EQ(xmpDatum.tagDesc(), "");

}



TEST_F(XmpdatumTest_1279, Tag_ReturnsZero_1279) {

    EXPECT_EQ(xmpDatum.tag(), 0);

}



TEST_F(XmpdatumTest_1279, TypeId_ReturnsUnknownType_1279) {

    EXPECT_EQ(xmpDatum.typeId(), Exiv2::undefined);

}



TEST_F(XmpdatumTest_1279, TypeName_ReturnsEmptyString_1279) {

    EXPECT_STREQ(xmpDatum.typeName(), "");

}



TEST_F(XmpdatumTest_1279, TypeSize_ReturnsZero_1279) {

    EXPECT_EQ(xmpDatum.typeSize(), 0);

}



TEST_F(XmpdatumTest_1279, Count_ReturnsOne_1279) {

    EXPECT_EQ(xmpDatum.count(), 1);

}



TEST_F(XmpdatumTest_1279, Size_ReturnsZero_1279) {

    EXPECT_EQ(xmpDatum.size(), 0);

}



TEST_F(XmpdatumTest_1279, ToString_ReturnsEmptyString_1279) {

    EXPECT_EQ(xmpDatum.toString(), "");

}



TEST_F(XmpdatumTest_1279, ToInt64_ReturnsZero_1279) {

    EXPECT_EQ(xmpDatum.toInt64(0), 0);

}



TEST_F(XmpdatumTest_1279, ToFloat_ReturnsZero_1279) {

    EXPECT_FLOAT_EQ(xmpDatum.toFloat(0), 0.0f);

}



TEST_F(XmpdatumTest_1279, ToRational_ReturnsDefaultRational_1279) {

    EXPECT_EQ(xmpDatum.toRational(0), Rational(0, 1));

}
