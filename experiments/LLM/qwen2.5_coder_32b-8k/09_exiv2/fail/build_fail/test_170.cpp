#include <gtest/gtest.h>

#include <exiv2/value.hpp>



using namespace Exiv2;



class ValueTypeURationalTest_170 : public ::testing::Test {

protected:

    ValueType<URational> urationalValue;

};



TEST_F(ValueTypeURationalTest_170, ToRationalValidIndex_170) {

    URational testRational = {1, 2};

    urationalValue.value_.push_back(testRational);

    EXPECT_EQ(urationalValue.toRational(0), testRational);

}



TEST_F(ValueTypeURationalTest_170, ToRationalBoundaryIndex_170) {

    URational testRational = {3, 4};

    urationalValue.value_.push_back(testRational);

    EXPECT_EQ(urationalValue.toRational(0), testRational);

}



TEST_F(ValueTypeURationalTest_170, ToRationalOutOfRangeIndex_170) {

    URational testRational = {5, 6};

    urationalValue.value_.push_back(testRational);

    EXPECT_THROW(urationalValue.toRational(1), std::out_of_range);

}



TEST_F(ValueTypeURationalTest_170, ToRationalEmptyVector_170) {

    EXPECT_THROW(urationalValue.toRational(0), std::out_of_range);

}
