#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/value.hpp>

#include <exiv2/exifdata.hpp>

#include <sstream>



using namespace Exiv2::Internal;

using namespace testing;



class PrintInt64Test_1377 : public Test {

protected:

    Value mockValue;

    std::ostringstream oss;

};



TEST_F(PrintInt64Test_1377, NormalOperation_1377) {

    EXPECT_CALL(mockValue, toRational()).WillOnce(Return(Rational(5, 2)));

    printInt64(oss, mockValue, nullptr);

    EXPECT_EQ("2", oss.str());

}



TEST_F(PrintInt64Test_1377, ZeroDenominator_1377) {

    EXPECT_CALL(mockValue, toRational()).WillOnce(Return(Rational(5, 0)));

    printInt64(oss, mockValue, nullptr);

    EXPECT_EQ("(value)", oss.str()); // Assuming (value) is the string representation of Value when denominator is zero

}



TEST_F(PrintInt64Test_1377, NegativeNumeratorPositiveDenominator_1377) {

    EXPECT_CALL(mockValue, toRational()).WillOnce(Return(Rational(-5, 2)));

    printInt64(oss, mockValue, nullptr);

    EXPECT_EQ("-2", oss.str());

}



TEST_F(PrintInt64Test_1377, PositiveNumeratorNegativeDenominator_1377) {

    EXPECT_CALL(mockValue, toRational()).WillOnce(Return(Rational(5, -2)));

    printInt64(oss, mockValue, nullptr);

    EXPECT_EQ("-2", oss.str());

}



TEST_F(PrintInt64Test_1377, LargeNumbers_1377) {

    EXPECT_CALL(mockValue, toRational()).WillOnce(Return(Rational(1000000000, 500000000)));

    printInt64(oss, mockValue, nullptr);

    EXPECT_EQ("2", oss.str());

}



TEST_F(PrintInt64Test_1377, ExifDataNotNull_1377) {

    Exiv2::ExifData exifData;

    EXPECT_CALL(mockValue, toRational()).WillOnce(Return(Rational(5, 2)));

    printInt64(oss, mockValue, &exifData);

    EXPECT_EQ("2", oss.str());

}
