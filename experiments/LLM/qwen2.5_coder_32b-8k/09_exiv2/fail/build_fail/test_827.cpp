#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class XmpValueTest_827 : public ::testing::Test {

protected:

    XmpValue xmpValue;

};



TEST_F(XmpValueTest_827, SetXmpStructAndGet_827) {

    XmpStruct expectedStruct = xsAltText;

    xmpValue.setXmpStruct(expectedStruct);

    EXPECT_EQ(xmpValue.xmpStruct(), expectedStruct);

}



TEST_F(XmpValueTest_827, DefaultXmpStruct_827) {

    EXPECT_EQ(xmpValue.xmpStruct(), xsNone);

}



TEST_F(XmpValueTest_827, SetXmpArrayTypeAndGet_827) {

    XmpArrayType expectedArrayType = xaSeq;

    xmpValue.setXmpArrayType(expectedArrayType);

    EXPECT_EQ(xmpValue.xmpArrayType(), expectedArrayType);

}



TEST_F(XmpValueTest_827, DefaultXmpArrayType_827) {

    EXPECT_EQ(xmpValue.xmpArrayType(), xaNone);

}
