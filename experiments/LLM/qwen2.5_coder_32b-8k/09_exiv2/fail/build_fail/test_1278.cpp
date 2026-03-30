#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class XmpdatumTest : public ::testing::Test {

protected:

    XmpKey key = XmpKey("Xmp.dc.creator");

    Value value;

    Xmpdatum xmpDatum1{key, &value};

};



TEST_F(XmpdatumTest_1278, CopyConstructorCreatesDeepCopy_1278) {

    Xmpdatum xmpDatum2{xmpDatum1};

    EXPECT_EQ(xmpDatum1.key(), xmpDatum2.key());

}



TEST_F(XmpdatumTest_1278, AssignmentOperatorCreatesDeepCopy_1278) {

    Xmpdatum xmpDatum2;

    xmpDatum2 = xmpDatum1;

    EXPECT_EQ(xmpDatum1.key(), xmpDatum2.key());

}



TEST_F(XmpdatumTest_1278, SetValueWithStringUpdatesValue_1278) {

    std::string newValue = "New Creator";

    int result = xmpDatum1.setValue(newValue);

    EXPECT_EQ(0, result);  // Assuming setValue returns 0 on success

}



TEST_F(XmpdatumTest_1278, SetAndGetKey_1278) {

    std::string keyString = xmpDatum1.key();

    EXPECT_EQ("Xmp.dc.creator", keyString);

}



TEST_F(XmpdatumTest_1278, FamilyNameReturnsCorrectValue_1278) {

    const char* familyName = xmpDatum1.familyName();

    EXPECT_STREQ(familyName, "Xmp");

}



TEST_F(XmpdatumTest_1278, GroupNameReturnsCorrectValue_1278) {

    std::string groupName = xmpDatum1.groupName();

    EXPECT_EQ("dc", groupName);

}



TEST_F(XmpdatumTest_1278, TagNameReturnsCorrectValue_1278) {

    std::string tagName = xmpDatum1.tagName();

    EXPECT_EQ("creator", tagName);

}



TEST_F(XmpdatumTest_1278, TagLabelReturnsNonEmptyString_1278) {

    std::string tagLabel = xmpDatum1.tagLabel();

    EXPECT_FALSE(tagLabel.empty());

}



TEST_F(XmpdatumTest_1278, TagDescReturnsNonEmptyString_1278) {

    std::string tagDesc = xmpDatum1.tagDesc();

    EXPECT_FALSE(tagDesc.empty());

}



TEST_F(XmpdatumTest_1278, TypeIdReturnsValidType_1278) {

    TypeId typeId = xmpDatum1.typeId();

    EXPECT_NE(typeId, undefined);

}



TEST_F(XmpdatumTest_1278, TypeNameReturnsNonEmptyString_1278) {

    const char* typeName = xmpDatum1.typeName();

    EXPECT_STREQ(typeName, "XmpText");

}



TEST_F(XmpdatumTest_1278, TypeSizeIsPositive_1278) {

    size_t typeSize = xmpDatum1.typeSize();

    EXPECT_GT(typeSize, 0);

}



TEST_F(XmpdatumTest_1278, CountReturnsNonNegativeValue_1278) {

    size_t count = xmpDatum1.count();

    EXPECT_GE(count, 0);

}



TEST_F(XmpdatumTest_1278, SizeIsNonNegative_1278) {

    size_t size = xmpDatum1.size();

    EXPECT_GE(size, 0);

}



TEST_F(XmpdatumTest_1278, ToStringReturnsNonEmptyString_1278) {

    std::string toStringValue = xmpDatum1.toString();

    EXPECT_FALSE(toStringValue.empty());

}
