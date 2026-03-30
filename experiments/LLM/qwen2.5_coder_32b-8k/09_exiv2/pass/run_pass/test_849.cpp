#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include <string>



namespace Exiv2 {

    class XmpArrayValue;

}



using namespace Exiv2;



class XmpArrayValueTest_849 : public ::testing::Test {

protected:

    void SetUp() override {

        xmpArrayValue = std::make_unique<XmpArrayValue>(TypeId::xmpText);

    }



    std::unique_ptr<XmpArrayValue> xmpArrayValue;

};



TEST_F(XmpArrayValueTest_849, ToUint32_NormalOperation_849) {

    xmpArrayValue->read("10 20 30");

    EXPECT_EQ(xmpArrayValue->toUint32(0), 10U);

    EXPECT_EQ(xmpArrayValue->toUint32(1), 20U);

    EXPECT_EQ(xmpArrayValue->toUint32(2), 30U);

}



TEST_F(XmpArrayValueTest_849, ToUint32_BoundaryCondition_EmptyString_849) {

    xmpArrayValue->read("");

    EXPECT_THROW(xmpArrayValue->toUint32(0), std::out_of_range);

}



TEST_F(XmpArrayValueTest_849, ToUint32_BoundaryCondition_OutOfRange_849) {

    xmpArrayValue->read("10 20");

    EXPECT_THROW(xmpArrayValue->toUint32(5), std::out_of_range);

}



TEST_F(XmpArrayValueTest_849, ToUint32_ErrorCase_NonNumericString_849) {

    xmpArrayValue->read("abc def ghi");

    EXPECT_EQ(xmpArrayValue->toUint32(0), 0U); // Assuming it returns 0 for non-numeric strings

}



TEST_F(XmpArrayValueTest_849, Count_NormalOperation_849) {

    xmpArrayValue->read("10 20 30");

    EXPECT_EQ(xmpArrayValue->count(), 3U);

}



TEST_F(XmpArrayValueTest_849, Count_BoundaryCondition_EmptyString_849) {

    xmpArrayValue->read("");

    EXPECT_EQ(xmpArrayValue->count(), 0U);

}



TEST_F(XmpArrayValueTest_849, ToString_NormalOperation_849) {

    xmpArrayValue->read("10 20 30");

    EXPECT_EQ(xmpArrayValue->toString(0), "10");

    EXPECT_EQ(xmpArrayValue->toString(1), "20");

    EXPECT_EQ(xmpArrayValue->toString(2), "30");

}



TEST_F(XmpArrayValueTest_849, ToString_BoundaryCondition_EmptyString_849) {

    xmpArrayValue->read("");

    EXPECT_THROW(xmpArrayValue->toString(0), std::out_of_range);

}



TEST_F(XmpArrayValueTest_849, ToString_BoundaryCondition_OutOfRange_849) {

    xmpArrayValue->read("10 20");

    EXPECT_THROW(xmpArrayValue->toString(5), std::out_of_range);

}
