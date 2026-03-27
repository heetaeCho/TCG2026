#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class XmpArrayValueTest_847 : public ::testing::Test {

protected:

    void SetUp() override {

        value = std::make_unique<XmpArrayValue>(TypeId::xmpText);

    }



    std::unique_ptr<XmpArrayValue> value;

};



TEST_F(XmpArrayValueTest_847, ToStringNormalOperation_847) {

    value->read("value1\0value2\0value3", 21); // Assuming null-separated values

    EXPECT_EQ(value->toString(0), "value1");

    EXPECT_EQ(value->toString(1), "value2");

    EXPECT_EQ(value->toString(2), "value3");

}



TEST_F(XmpArrayValueTest_847, ToStringBoundaryCondition_847) {

    value->read("singleValue", 11);

    EXPECT_EQ(value->toString(0), "singleValue");

}



TEST_F(XmpArrayValueTest_847, ToStringExceptionalCase_847) {

    value->read("", 0);

    EXPECT_THROW(value->toString(0), std::out_of_range);



    value->read("value1\0value2", 13); // Two values

    EXPECT_THROW(value->toString(2), std::out_of_range); // Out of range index

}



TEST_F(XmpArrayValueTest_847, CountNormalOperation_847) {

    value->read("value1\0value2\0value3", 21);

    EXPECT_EQ(value->count(), 3U);

}



TEST_F(XmpArrayValueTest_847, CountBoundaryCondition_847) {

    value->read("", 0);

    EXPECT_EQ(value->count(), 0U);



    value->read("singleValue", 11);

    EXPECT_EQ(value->count(), 1U);

}
