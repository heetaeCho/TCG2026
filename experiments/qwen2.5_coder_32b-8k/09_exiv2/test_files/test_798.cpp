#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class DataValueTest_798 : public ::testing::Test {

protected:

    DataValue dataValue_{static_cast<TypeId>(1)};

};



TEST_F(DataValueTest_798, ToStringNormalOperation_798) {

    // Assuming value_.at(0) is set to 42 for this test case

    EXPECT_EQ(dataValue_.toString(0), "42");

}



TEST_F(DataValueTest_798, ToStringBoundaryCondition_798) {

    // Test with the minimum possible index

    EXPECT_EQ(dataValue_.toString(0), "0");



    // Assuming value_ has at least 1 element, test with the maximum index

    EXPECT_THROW(dataValue_.toString(1), std::out_of_range); // Adjust expectation based on actual behavior

}



TEST_F(DataValueTest_798, ToStringExceptionalCase_798) {

    // Test out of range access

    EXPECT_THROW(dataValue_.toString(10), std::out_of_range);

}
