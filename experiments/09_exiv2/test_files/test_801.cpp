#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class DataValueTest_801 : public ::testing::Test {

protected:

    TypeId typeId = static_cast<TypeId>(0); // Assuming a valid TypeId for testing purposes

    std::unique_ptr<DataValue> dataValue;



    void SetUp() override {

        dataValue = std::make_unique<DataValue>(typeId);

    }

};



TEST_F(DataValueTest_801, toFloat_NormalOperation_801) {

    // Assuming value_.at(n) is set correctly in the implementation

    size_t n = 0;

    float expected = 3.14f; // Example expected value

    dataValue->value_.push_back(expected);

    EXPECT_FLOAT_EQ(dataValue->toFloat(n), expected);

}



TEST_F(DataValueTest_801, toFloat_BoundaryCondition_ZeroIndex_801) {

    size_t n = 0;

    float expected = 2.71f; // Example expected value

    dataValue->value_.push_back(expected);

    EXPECT_FLOAT_EQ(dataValue->toFloat(n), expected);

}



TEST_F(DataValueTest_801, toFloat_BoundaryCondition_MaxIndex_801) {

    size_t n = 999; // Assuming a large enough vector for testing

    float expected = 1.41f; // Example expected value

    dataValue->value_.resize(1000);

    dataValue->value_[n] = expected;

    EXPECT_FLOAT_EQ(dataValue->toFloat(n), expected);

}



TEST_F(DataValueTest_801, toFloat_ExceptionalCase_OutOfBounds_801) {

    size_t n = 1; // Assuming value_.size() is 1 for this test

    dataValue->value_.push_back(3.14f);

    EXPECT_THROW(dataValue->toFloat(n), std::out_of_range); // Assuming out_of_range is thrown on invalid index

}
