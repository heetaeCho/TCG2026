#include <gtest/gtest.h>

#include <exiv2/types.hpp>



using namespace Exiv2;



class TypeInfoTest_1112 : public ::testing::Test {

protected:

    TypeInfo typeInfo;

};



TEST_F(TypeInfoTest_1112, ValidTypeIdReturnsCorrectName_1112) {

    EXPECT_STREQ(typeInfo.typeName(unsignedByte), "Byte");

    EXPECT_STREQ(typeInfo.typeName(unsignedShort), "Short");

    EXPECT_STREQ(typeInfo.typeName(unsignedLong), "Long");

}



TEST_F(TypeInfoTest_1112, InvalidTypeIdReturnsNullptr_1112) {

    EXPECT_EQ(typeInfo.typeName(invalidTypeId), nullptr);

}



TEST_F(TypeInfoTest_1112, BoundaryConditionFirstElement_1112) {

    EXPECT_STREQ(typeInfo.typeName(Exiv2::invalidTypeId), "Invalid");

}



TEST_F(TypeInfoTest_1112, BoundaryConditionLastElement_1112) {

    EXPECT_STREQ(typeInfo.typeName(langAlt), "LangAlt");

}



TEST_F(TypeInfoTest_1112, OutOfBoundsTypeIdReturnsNullptr_1112) {

    EXPECT_EQ(typeInfo.typeName(static_cast<TypeId>(25)), nullptr);

}
