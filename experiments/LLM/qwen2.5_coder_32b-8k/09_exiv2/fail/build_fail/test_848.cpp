#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class XmpArrayValueTest_848 : public ::testing::Test {

protected:

    XmpArrayValue* xmpArrayValue;



    void SetUp() override {

        xmpArrayValue = new XmpArrayValue(TypeId::xmpText);

    }



    void TearDown() override {

        delete xmpArrayValue;

    }

};



TEST_F(XmpArrayValueTest_848, ToInt64_NormalOperation_848) {

    // Assuming read method is correctly implemented and sets the internal state

    std::string buffer = "123 456";

    xmpArrayValue->read(buffer);



    EXPECT_EQ(xmpArrayValue->toInt64(0), 123);

    EXPECT_EQ(xmpArrayValue->toInt64(1), 456);

}



TEST_F(XmpArrayValueTest_848, ToInt64_BoundaryCondition_EmptyString_848) {

    std::string buffer = "";

    xmpArrayValue->read(buffer);



    EXPECT_THROW(xmpArrayValue->toInt64(0), std::out_of_range);

}



TEST_F(XmpArrayValueTest_848, ToInt64_BoundaryCondition_OutOfRange_848) {

    std::string buffer = "123";

    xmpArrayValue->read(buffer);



    EXPECT_THROW(xmpArrayValue->toInt64(1), std::out_of_range);

}



TEST_F(XmpArrayValueTest_848, ToInt64_ErrorCase_NonNumericString_848) {

    std::string buffer = "abc def";

    xmpArrayValue->read(buffer);



    EXPECT_THROW(xmpArrayValue->toInt64(0), Exiv2::Error);

}



TEST_F(XmpArrayValueTest_848, Count_NormalOperation_848) {

    std::string buffer = "123 456";

    xmpArrayValue->read(buffer);



    EXPECT_EQ(xmpArrayValue->count(), 2u);

}



TEST_F(XmpArrayValueTest_848, Count_BoundaryCondition_EmptyString_848) {

    std::string buffer = "";

    xmpArrayValue->read(buffer);



    EXPECT_EQ(xmpArrayValue->count(), 0u);

}
