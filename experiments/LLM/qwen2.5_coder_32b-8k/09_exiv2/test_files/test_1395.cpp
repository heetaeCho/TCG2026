#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Exiv2/exiv2.hpp>



using namespace Exiv2;

using namespace Exiv2::Internal;



class Print0x829aTest_1395 : public ::testing::Test {

protected:

    Value value;

};



TEST_F(Print0x829aTest_1395, EmptyValue_1395) {

    std::ostringstream os;

    print0x829a(os, value, nullptr);

    EXPECT_EQ(os.str(), "");

}



TEST_F(Print0x829aTest_1395, NonRationalType_1395) {

    value = Value::create(unknown);

    std::ostringstream os;

    print0x829a(os, value, nullptr);

    EXPECT_EQ(os.str(), "(Exiv2::Value*)");

}



TEST_F(Print0x829aTest_1395, RationalZeroNumerator_1395) {

    URational zeroRational{0, 1};

    value = Value::create(unsignedRational);

    value.rationals(zeroRational, 1);

    std::ostringstream os;

    print0x829a(os, value, nullptr);

    EXPECT_EQ(os.str(), "(0/1)");

}



TEST_F(Print0x829aTest_1395, RationalZeroDenominator_1395) {

    URational zeroRational{1, 0};

    value = Value::create(unsignedRational);

    value.rationals(zeroRational, 1);

    std::ostringstream os;

    print0x829a(os, value, nullptr);

    EXPECT_EQ(os.str(), "(1/0)");

}



TEST_F(Print0x829aTest_1395, RationalEqualNumeratorDenominator_1395) {

    URational equalRational{2, 2};

    value = Value::create(unsignedRational);

    value.rationals(equalRational, 1);

    std::ostringstream os;

    print0x829a(os, value, nullptr);

    EXPECT_EQ(os.str(), "1 s");

}



TEST_F(Print0x829aTest_1395, RationalDivisibleNumeratorDenominator_1395) {

    URational divisibleRational{4, 2};

    value = Value::create(unsignedRational);

    value.rationals(divisibleRational, 1);

    std::ostringstream os;

    print0x829a(os, value, nullptr);

    EXPECT_EQ(os.str(), "2 s");

}



TEST_F(Print0x829aTest_1395, RationalNonDivisibleNumeratorDenominator_1395) {

    URational nonDivisibleRational{5, 2};

    value = Value::create(unsignedRational);

    value.rationals(nonDivisibleRational, 1);

    std::ostringstream os;

    print0x829a(os, value, nullptr);

    EXPECT_EQ(os.str(), "2.5 s");

}
