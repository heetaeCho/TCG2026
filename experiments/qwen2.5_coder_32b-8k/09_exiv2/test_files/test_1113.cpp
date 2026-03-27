#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



class TypeInfoTest_1113 : public ::testing::Test {

protected:

    TypeInfo typeInfo;

};



TEST_F(TypeInfoTest_1113, KnownTypeNameReturnsCorrectTypeId_1113) {

    EXPECT_EQ(typeInfo.typeId("Byte"), unsignedByte);

    EXPECT_EQ(typeInfo.typeId("Ascii"), asciiString);

    EXPECT_EQ(typeInfo.typeId("Short"), unsignedShort);

    EXPECT_EQ(typeInfo.typeId("Long"), unsignedLong);

    EXPECT_EQ(typeInfo.typeId("Rational"), unsignedRational);

    EXPECT_EQ(typeInfo.typeId("SByte"), signedByte);

    EXPECT_EQ(typeInfo.typeId("Undefined"), undefined);

    EXPECT_EQ(typeInfo.typeId("SShort"), signedShort);

    EXPECT_EQ(typeInfo.typeId("SLong"), signedLong);

    EXPECT_EQ(typeInfo.typeId("SRational"), signedRational);

    EXPECT_EQ(typeInfo.typeId("Float"), tiffFloat);

    EXPECT_EQ(typeInfo.typeId("Double"), tiffDouble);

    EXPECT_EQ(typeInfo.typeId("Ifd"), tiffIfd);

    EXPECT_EQ(typeInfo.typeId("String"), string);

    EXPECT_EQ(typeInfo.typeId("Date"), date);

    EXPECT_EQ(typeInfo.typeId("Time"), time);

    EXPECT_EQ(typeInfo.typeId("Comment"), comment);

    EXPECT_EQ(typeInfo.typeId("Directory"), directory);

    EXPECT_EQ(typeInfo.typeId("XmpText"), xmpText);

    EXPECT_EQ(typeInfo.typeId("XmpAlt"), xmpAlt);

    EXPECT_EQ(typeInfo.typeId("XmpBag"), xmpBag);

    EXPECT_EQ(typeInfo.typeId("XmpSeq"), xmpSeq);

    EXPECT_EQ(typeInfo.typeId("LangAlt"), langAlt);

}



TEST_F(TypeInfoTest_1113, UnknownTypeNameReturnsInvalidTypeId_1113) {

    EXPECT_EQ(typeInfo.typeId("UnknownType"), invalidTypeId);

}



TEST_F(TypeInfoTest_1113, CaseSensitiveTypeNameLookup_1113) {

    EXPECT_NE(typeInfo.typeId("byte"), unsignedByte);

    EXPECT_NE(typeInfo.typeId("BYTE"), unsignedByte);

}
