#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class DataValueTest_799 : public ::testing::Test {

protected:

    void SetUp() override {

        dataValue = std::make_unique<DataValue>(TypeId::undefined);

    }



    std::unique_ptr<DataValue> dataValue;

};



TEST_F(DataValueTest_799, ToInt64_NormalOperation_799) {

    // Assuming the value_ vector is initialized with some values

    dataValue->value_.push_back(123456);

    EXPECT_EQ(dataValue->toInt64(0), 123456);

}



TEST_F(DataValueTest_799, ToInt64_BoundaryCondition_EmptyVector_799) {

    // Test behavior when the vector is empty

    EXPECT_THROW(dataValue->toInt64(0), std::out_of_range);

}



TEST_F(DataValueTest_799, ToInt64_BoundaryCondition_OutOfRangeIndex_799) {

    dataValue->value_.push_back(123456);

    EXPECT_THROW(dataValue->toInt64(1), std::out_of_range); // Index out of range

}



TEST_F(DataValueTest_799, ToInt64_ErrorCase_NegativeIndex_799) {

    dataValue->value_.push_back(123456);

    EXPECT_THROW(dataValue->toInt64(-1), std::out_of_range); // Negative index should throw

}
