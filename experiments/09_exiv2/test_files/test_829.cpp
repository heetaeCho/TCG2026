#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;



class XmpValueTest_829 : public ::testing::Test {

protected:

    XmpValue xmpValue;

};



TEST_F(XmpValueTest_829, XmpArrayType_XmpAlt_829) {

    TypeId typeId = xmpAlt;

    EXPECT_EQ(xmpValue.xmpArrayType(typeId), XmpArrayType::xaAlt);

}



TEST_F(XmpValueTest_829, XmpArrayType_XmpBag_829) {

    TypeId typeId = xmpBag;

    EXPECT_EQ(xmpValue.xmpArrayType(typeId), XmpArrayType::xaBag);

}



TEST_F(XmpValueTest_829, XmpArrayType_XmpSeq_829) {

    TypeId typeId = xmpSeq;

    EXPECT_EQ(xmpValue.xmpArrayType(typeId), XmpArrayType::xaSeq);

}



TEST_F(XmpValueTest_829, XmpArrayType_DefaultCase_829) {

    TypeId typeId = unsignedByte; // Example of a type ID that does not match any case

    EXPECT_EQ(xmpValue.xmpArrayType(typeId), XmpArrayType::xaNone);

}



TEST_F(XmpValueTest_829, XmpArrayType_XmpAlt_SetAndGet_829) {

    xmpValue.setXmpArrayType(XmpArrayType::xaAlt);

    EXPECT_EQ(xmpValue.xmpArrayType(), XmpArrayType::xaAlt);

}



TEST_F(XmpValueTest_829, XmpArrayType_XmpBag_SetAndGet_829) {

    xmpValue.setXmpArrayType(XmpArrayType::xaBag);

    EXPECT_EQ(xmpValue.xmpArrayType(), XmpArrayType::xaBag);

}



TEST_F(XmpValueTest_829, XmpArrayType_XmpSeq_SetAndGet_829) {

    xmpValue.setXmpArrayType(XmpArrayType::xaSeq);

    EXPECT_EQ(xmpValue.xmpArrayType(), XmpArrayType::xaSeq);

}



TEST_F(XmpValueTest_829, XmpArrayType_Default_SetAndGet_829) {

    xmpValue.setXmpArrayType(XmpArrayType::xaNone);

    EXPECT_EQ(xmpValue.xmpArrayType(), XmpArrayType::xaNone);

}
