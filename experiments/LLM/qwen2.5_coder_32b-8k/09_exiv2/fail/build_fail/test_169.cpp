#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using ::testing::Return;



class ValueTypeRationalTest_169 : public ::testing::Test {

protected:

    ValueType<Rational> rationalValue_;

};



TEST_F(ValueTypeRationalTest_169, NormalOperation_ReturnsCorrectRational_169) {

    Rational testRational{1, 2};

    rationalValue_.value_.push_back(testRational);

    EXPECT_EQ(rationalValue_.toRational(0), testRational);

}



TEST_F(ValueTypeRationalTest_169, BoundaryCondition_EmptyVector_ReturnsDefaultRational_169) {

    Rational defaultRational{0, 1};

    EXPECT_EQ(rationalValue_.toRational(0), defaultRational);

}



TEST_F(ValueTypeRationalTest_169, ExceptionalCase_OutOfBoundsAccess_ReturnsDefaultRational_169) {

    Rational testRational{3, 4};

    rationalValue_.value_.push_back(testRational);

    EXPECT_EQ(rationalValue_.toRational(1), Rational{0, 1});

}



TEST_F(ValueTypeRationalTest_169, NormalOperation_CorrectOkFlagAfterAccess_169) {

    Rational testRational{5, 6};

    rationalValue_.value_.push_back(testRational);

    rationalValue_.toRational(0);

    EXPECT_TRUE(rationalValue_.ok());

}



TEST_F(ValueTypeRationalTest_169, BoundaryCondition_EmptyVector_CorrectOkFlagAfterAccess_169) {

    rationalValue_.toRational(0);

    EXPECT_TRUE(rationalValue_.ok());

}
