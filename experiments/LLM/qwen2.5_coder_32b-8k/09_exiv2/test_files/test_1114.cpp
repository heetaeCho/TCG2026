#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



class TypeInfoTest : public ::testing::Test {

protected:

    TypeInfo typeInfo;

};



TEST_F(TypeInfoTest_1114, TypeSizeInvalidTypeId_ReturnsZero_1114) {

    EXPECT_EQ(typeInfo.typeSize(invalidTypeId), 0);

}



TEST_F(TypeInfoTest_1114, TypeSizeUnsignedByte_ReturnsOne_1114) {

    EXPECT_EQ(typeInfo.typeSize(unsignedByte), 1);

}



TEST_F(TypeInfoTest_1114, TypeSizeAsciiString_ReturnsOne_1114) {

    EXPECT_EQ(typeInfo.typeSize(asciiString), 1);

}



TEST_F(TypeInfoTest_1114, TypeSizeUnsignedShort_ReturnsTwo_1114) {

    EXPECT_EQ(typeInfo.typeSize(unsignedShort), 2);

}



TEST_F(TypeInfoTest_1114, TypeSizeUnsignedLong_ReturnsFour_1114) {

    EXPECT_EQ(typeInfo.typeSize(unsignedLong), 4);

}



TEST_F(TypeInfoTest_1114, TypeSizeUnsignedRational_ReturnsEight_1114) {

    EXPECT_EQ(typeInfo.typeSize(unsignedRational), 8);

}



TEST_F(TypeInfoTest_1114, TypeSizeSignedByte_ReturnsOne_1114) {

    EXPECT_EQ(typeInfo.typeSize(signedByte), 1);

}



TEST_F(TypeInfoTest_1114, TypeSizeUndefined_ReturnsOne_1114) {

    EXPECT_EQ(typeInfo.typeSize(undefined), 1);

}



TEST_F(TypeInfoTest_1114, TypeSizeSignedShort_ReturnsTwo_1114) {

    EXPECT_EQ(typeInfo.typeSize(signedShort), 2);

}



TEST_F(TypeInfoTest_1114, TypeSizeSignedLong_ReturnsFour_1114) {

    EXPECT_EQ(typeInfo.typeSize(signedLong), 4);

}



TEST_F(TypeInfoTest_1114, TypeSizeSignedRational_ReturnsEight_1114) {

    EXPECT_EQ(typeInfo.typeSize(signedRational), 8);

}



TEST_F(TypeInfoTest_1114, TypeSizeTiffFloat_ReturnsFour_1114) {

    EXPECT_EQ(typeInfo.typeSize(tiffFloat), 4);

}



TEST_F(TypeInfoTest_1114, TypeSizeTiffDouble_ReturnsEight_1114) {

    EXPECT_EQ(typeInfo.typeSize(tiffDouble), 8);

}



TEST_F(TypeInfoTest_1114, TypeSizeTiffIfd_ReturnsFour_1114) {

    EXPECT_EQ(typeInfo.typeSize(tiffIfd), 4);

}



TEST_F(TypeInfoTest_1114, TypeSizeString_ReturnsOne_1114) {

    EXPECT_EQ(typeInfo.typeSize(string), 1);

}



TEST_F(TypeInfoTest_1114, TypeSizeDate_ReturnsEight_1114) {

    EXPECT_EQ(typeInfo.typeSize(date), 8);

}



TEST_F(TypeInfoTest_1114, TypeSizeTime_ReturnsEleven_1114) {

    EXPECT_EQ(typeInfo.typeSize(time), 11);

}



TEST_F(TypeInfoTest_1114, TypeSizeComment_ReturnsOne_1114) {

    EXPECT_EQ(typeInfo.typeSize(comment), 1);

}



TEST_F(TypeInfoTest_1114, TypeSizeDirectory_ReturnsOne_1114) {

    EXPECT_EQ(typeInfo.typeSize(directory), 1);

}



TEST_F(TypeInfoTest_1114, TypeSizeXmpText_ReturnsOne_1114) {

    EXPECT_EQ(typeInfo.typeSize(xmpText), 1);

}



TEST_F(TypeInfoTest_1114, TypeSizeXmpAlt_ReturnsOne_1114) {

    EXPECT_EQ(typeInfo.typeSize(xmpAlt), 1);

}



TEST_F(TypeInfoTest_1114, TypeSizeXmpBag_ReturnsOne_1114) {

    EXPECT_EQ(typeInfo.typeSize(xmpBag), 1);

}



TEST_F(TypeInfoTest_1114, TypeSizeXmpSeq_ReturnsOne_1114) {

    EXPECT_EQ(typeInfo.typeSize(xmpSeq), 1);

}



TEST_F(TypeInfoTest_1114, TypeSizeLangAlt_ReturnsOne_1114) {

    EXPECT_EQ(typeInfo.typeSize(langAlt), 1);

}
