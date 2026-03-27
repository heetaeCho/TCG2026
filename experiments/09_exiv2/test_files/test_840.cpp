#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/value.cpp"



using namespace Exiv2;



class XmpTextValueTest_840 : public ::testing::Test {

protected:

    XmpTextValue xmpTextValue;

};



TEST_F(XmpTextValueTest_840, ToUint32_NormalOperation_840) {

    xmpTextValue.value_ = "12345";

    xmpTextValue.ok_ = true;

    EXPECT_EQ(xmpTextValue.toUint32(0), 12345);

}



TEST_F(XmpTextValueTest_840, ToUint32_BoundaryCondition_Zero_840) {

    xmpTextValue.value_ = "0";

    xmpTextValue.ok_ = true;

    EXPECT_EQ(xmpTextValue.toUint32(0), 0);

}



TEST_F(XmpTextValueTest_840, ToUint32_BoundaryCondition_MaxUint32_840) {

    xmpTextValue.value_ = "4294967295";

    xmpTextValue.ok_ = true;

    EXPECT_EQ(xmpTextValue.toUint32(0), 4294967295);

}



TEST_F(XmpTextValueTest_840, ToUint32_Exceptional_NegativeNumber_840) {

    xmpTextValue.value_ = "-1";

    xmpTextValue.ok_ = false;

    EXPECT_EQ(xmpTextValue.toUint32(0), 0); // Assuming it returns 0 when ok_ is false

}



TEST_F(XmpTextValueTest_840, ToUint32_Exceptional_NonNumericString_840) {

    xmpTextValue.value_ = "abc";

    xmpTextValue.ok_ = false;

    EXPECT_EQ(xmpTextValue.toUint32(0), 0); // Assuming it returns 0 when ok_ is false

}



TEST_F(XmpTextValueTest_840, ToUint32_Exceptional_EmptyString_840) {

    xmpTextValue.value_ = "";

    xmpTextValue.ok_ = false;

    EXPECT_EQ(xmpTextValue.toUint32(0), 0); // Assuming it returns 0 when ok_ is false

}
