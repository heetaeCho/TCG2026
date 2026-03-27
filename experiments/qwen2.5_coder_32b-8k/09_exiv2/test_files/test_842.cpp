#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/value.cpp"



using namespace Exiv2;

using namespace testing;



class XmpTextValueTest_842 : public ::testing::Test {

protected:

    XmpTextValue value_;

};



TEST_F(XmpTextValueTest_842, ToRational_ValidInput_ReturnsExpectedRational_842) {

    // Arrange

    value_.value_ = "1/2";

    value_.ok_ = true;



    // Act

    Rational result = value_.toRational(0);



    // Assert

    EXPECT_EQ(result.first, 1);

    EXPECT_EQ(result.second, 2);

}



TEST_F(XmpTextValueTest_842, ToRational_ZeroN_ReturnsFirstRational_842) {

    // Arrange

    value_.value_ = "3/4 5/6";

    value_.ok_ = true;



    // Act

    Rational result = value_.toRational(0);



    // Assert

    EXPECT_EQ(result.first, 3);

    EXPECT_EQ(result.second, 4);

}



TEST_F(XmpTextValueTest_842, ToRational_NonZeroN_ReturnsCorrespondingRational_842) {

    // Arrange

    value_.value_ = "3/4 5/6";

    value_.ok_ = true;



    // Act

    Rational result = value_.toRational(1);



    // Assert

    EXPECT_EQ(result.first, 5);

    EXPECT_EQ(result.second, 6);

}



TEST_F(XmpTextValueTest_842, ToRational_OutOfBoundsN_ReturnsZeroRational_842) {

    // Arrange

    value_.value_ = "3/4";

    value_.ok_ = true;



    // Act

    Rational result = value_.toRational(1);



    // Assert

    EXPECT_EQ(result.first, 0);

    EXPECT_EQ(result.second, 0);

}



TEST_F(XmpTextValueTest_842, ToRational_InvalidInput_ReturnsZeroRational_842) {

    // Arrange

    value_.value_ = "invalid";

    value_.ok_ = false;



    // Act

    Rational result = value_.toRational(0);



    // Assert

    EXPECT_EQ(result.first, 0);

    EXPECT_EQ(result.second, 0);

}
