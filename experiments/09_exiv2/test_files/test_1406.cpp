#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Exiv2/value.hpp>

#include <Exiv2/exif.hpp>

#include <sstream>



using namespace Exiv2;

using namespace Exiv2::Internal;



class Print0x920aTest : public ::testing::Test {

protected:

    std::ostringstream os;

    Value value;

    const ExifData* exifData = nullptr;

};



TEST_F(Print0x920aTest, NormalOperation_1406) {

    Rational rationalValue(10, 2);

    value.setValue(&rationalValue, 1);

    print0x920a(os, value, exifData);

    EXPECT_EQ(os.str(), "5.0 mm");

}



TEST_F(Print0x920aTest, ZeroDenominator_1406) {

    Rational rationalValue(10, 0);

    value.setValue(&rationalValue, 1);

    print0x920a(os, value, exifData);

    EXPECT_EQ(os.str(), "(Rational(10/0))");

}



TEST_F(Print0x920aTest, LargeNumbers_1406) {

    Rational rationalValue(123456789, 98765432);

    value.setValue(&rationalValue, 1);

    print0x920a(os, value, exifData);

    EXPECT_EQ(os.str(), "1.2 mm");

}



TEST_F(Print0x920aTest, SmallNumbers_1406) {

    Rational rationalValue(1, 3);

    value.setValue(&rationalValue, 1);

    print0x920a(os, value, exifData);

    EXPECT_EQ(os.str(), "0.3 mm");

}



TEST_F(Print0x920aTest, NegativeNumbers_1406) {

    Rational rationalValue(-5, 2);

    value.setValue(&rationalValue, 1);

    print0x920a(os, value, exifData);

    EXPECT_EQ(os.str(), "-2.5 mm");

}



TEST_F(Print0x920aTest, LargeDenominator_1406) {

    Rational rationalValue(1, 1000000);

    value.setValue(&rationalValue, 1);

    print0x920a(os, value, exifData);

    EXPECT_EQ(os.str(), "0.0 mm");

}
