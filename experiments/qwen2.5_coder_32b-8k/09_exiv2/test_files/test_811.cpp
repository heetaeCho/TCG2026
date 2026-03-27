#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class StringValueBaseTest_811 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary data before each test

        testData = "1.0 2.5 3.7";

        stringValueBase = std::make_unique<StringValueBase>(stringType, testData);

    }



    std::unique_ptr<StringValueBase> stringValueBase;

    std::string testData;

};



TEST_F(StringValueBaseTest_811, toFloatNormalOperation_811) {

    float result = stringValueBase->toFloat(0);

    EXPECT_FLOAT_EQ(result, 1.0f);



    result = stringValueBase->toFloat(1);

    EXPECT_FLOAT_EQ(result, 2.5f);



    result = stringValueBase->toFloat(2);

    EXPECT_FLOAT_EQ(result, 3.7f);

}



TEST_F(StringValueBaseTest_811, toFloatBoundaryConditions_811) {

    // Test with the first element

    float result = stringValueBase->toFloat(0);

    EXPECT_FLOAT_EQ(result, 1.0f);



    // Test with the last element

    result = stringValueBase->toFloat(stringValueBase->count() - 1);

    EXPECT_FLOAT_EQ(result, 3.7f);

}



TEST_F(StringValueBaseTest_811, toFloatExceptionalCases_811) {

    // Test with out-of-bounds index

    EXPECT_THROW(stringValueBase->toFloat(stringValueBase->count()), std::out_of_range);



    // Test with invalid float string

    testData = "abc";

    stringValueBase = std::make_unique<StringValueBase>(stringType, testData);

    EXPECT_THROW(stringValueBase->toFloat(0), Exiv2::Error);

}



TEST_F(StringValueBaseTest_811, countNormalOperation_811) {

    size_t result = stringValueBase->count();

    EXPECT_EQ(result, 3);

}



TEST_F(StringValueBaseTest_811, okMethodAfterFloatConversion_811) {

    stringValueBase->toFloat(0);

    EXPECT_TRUE(stringValueBase->ok());

}
