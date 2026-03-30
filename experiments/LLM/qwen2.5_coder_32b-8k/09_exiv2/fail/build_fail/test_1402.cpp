#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <exiv2/value.hpp>

#include <exiv2/exif.hpp>



using namespace Exiv2;

using namespace Exiv2::Internal;



class Print0x9204Test : public ::testing::Test {

protected:

    std::ostringstream os;

    Value value;

    const ExifData* exifData = nullptr; // Assuming this can be null for our tests

};



TEST_F(Print0x9204Test, NormalOperation_PositiveEV_1402) {

    Rational bias(3, 1);

    value._content.clear();

    value._content.push_back(bias.first);

    value._content.push_back(bias.second);



    print0x9204(os, value, exifData);

    EXPECT_EQ(os.str(), "+3 EV");

}



TEST_F(Print0x9204Test, NormalOperation_NegativeEV_1402) {

    Rational bias(-5, 1);

    value._content.clear();

    value._content.push_back(bias.first);

    value._content.push_back(bias.second);



    print0x9204(os, value, exifData);

    EXPECT_EQ(os.str(), "-5 EV");

}



TEST_F(Print0x9204Test, NormalOperation_FractionalEV_1402) {

    Rational bias(7, 3);

    value._content.clear();

    value._content.push_back(bias.first);

    value._content.push_back(bias.second);



    print0x9204(os, value, exifData);

    EXPECT_EQ(os.str(), "+7/3 EV");

}



TEST_F(Print0x9204Test, BoundaryCondition_ZeroEV_1402) {

    Rational bias(0, 1);

    value._content.clear();

    value._content.push_back(bias.first);

    value._content.push_back(bias.second);



    print0x9204(os, value, exifData);

    EXPECT_EQ(os.str(), "0 EV");

}



TEST_F(Print0x9204Test, BoundaryCondition_MinInt32EV_1402) {

    Rational bias(std::numeric_limits<std::int32_t>::min(), 1);

    value._content.clear();

    value._content.push_back(bias.first);

    value._content.push_back(bias.second);



    print0x9204(os, value, exifData);

    EXPECT_EQ(os.str(), "0 EV");

}



TEST_F(Print0x9204Test, BoundaryCondition_ZeroDenominator_1402) {

    Rational bias(3, 0);

    value._content.clear();

    value._content.push_back(bias.first);

    value._content.push_back(bias.second);



    print0x9204(os, value, exifData);

    EXPECT_EQ(os.str(), "(3/0)");

}



TEST_F(Print0x9204Test, BoundaryCondition_NegativeDenominator_1402) {

    Rational bias(3, -1);

    value._content.clear();

    value._content.push_back(bias.first);

    value._content.push_back(bias.second);



    print0x9204(os, value, exifData);

    EXPECT_EQ(os.str(), "+-3 EV");

}



TEST_F(Print0x9204Test, SimplifiedFraction_1402) {

    Rational bias(6, 2);

    value._content.clear();

    value._content.push_back(bias.first);

    value._content.push_back(bias.second);



    print0x9204(os, value, exifData);

    EXPECT_EQ(os.str(), "+3 EV");

}



TEST_F(Print0x9204Test, NegativeSimplifiedFraction_1402) {

    Rational bias(-8, 4);

    value._content.clear();

    value._content.push_back(bias.first);

    value._content.push_back(bias.second);



    print0x9204(os, value, exifData);

    EXPECT_EQ(os.str(), "-2 EV");

}
