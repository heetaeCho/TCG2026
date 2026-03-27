#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/value.cpp"



using namespace Exiv2;

using ::testing::Eq;



class XmpTextValueTest_839 : public ::testing::Test {

protected:

    XmpTextValue xmpTextValue;



    void SetUp() override {

        // Initialize value_ and ok_ as needed for testing

        xmpTextValue.value_ = "12345";

        xmpTextValue.ok_ = true;

    }

};



TEST_F(XmpTextValueTest_839, ToInt64NormalOperation_839) {

    int64_t result = xmpTextValue.toInt64(0);

    EXPECT_EQ(result, 12345);

}



TEST_F(XmpTextValueTest_839, ToInt64BoundaryConditionZero_839) {

    xmpTextValue.value_ = "0";

    int64_t result = xmpTextValue.toInt64(0);

    EXPECT_EQ(result, 0);

}



TEST_F(XmpTextValueTest_839, ToInt64BoundaryConditionMax_839) {

    xmpTextValue.value_ = std::to_string(std::numeric_limits<int64_t>::max());

    int64_t result = xmpTextValue.toInt64(0);

    EXPECT_EQ(result, std::numeric_limits<int64_t>::max());

}



TEST_F(XmpTextValueTest_839, ToInt64BoundaryConditionMin_839) {

    xmpTextValue.value_ = std::to_string(std::numeric_limits<int64_t>::min());

    int64_t result = xmpTextValue.toInt64(0);

    EXPECT_EQ(result, std::numeric_limits<int64_t>::min());

}



TEST_F(XmpTextValueTest_839, ToInt64InvalidInput_839) {

    xmpTextValue.value_ = "invalid";

    int64_t result = xmpTextValue.toInt64(0);

    EXPECT_EQ(result, 0); // Assuming parseInt64 returns 0 for invalid input when ok_ is false

}



TEST_F(XmpTextValueTest_839, ToInt64OkFlagFalse_839) {

    xmpTextValue.value_ = "12345";

    xmpTextValue.ok_ = false;

    int64_t result = xmpTextValue.toInt64(0);

    EXPECT_EQ(result, 0); // Assuming parseInt64 returns 0 when ok_ is false

}
