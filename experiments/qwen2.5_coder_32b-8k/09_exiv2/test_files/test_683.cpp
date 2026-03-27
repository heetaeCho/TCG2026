#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;

using ::testing::Return;



class IptcdatumTest : public ::testing::Test {

protected:

    MockValue* mockValue;

    Iptcdatum iptcdatum;



    class MockValue : public Value {

    public:

        MOCK_METHOD(size_t, count, (), (const, override));

        MOCK_METHOD(Rational, toRational, (size_t), (const, override));

    };



    IptcdatumTest() 

        : mockValue(new MockValue(TypeId::undefined)), iptcdatum(IptcKey("IptcKey"), mockValue) {

        ON_CALL(*mockValue, count()).WillByDefault(Return(1));

    }

};



TEST_F(IptcdatumTest_683, ToRational_ReturnsNegativeOneWhenNoValue_683) {

    Iptcdatum iptcdatumWithoutValue(IptcKey("IptcKey"), nullptr);

    EXPECT_EQ(iptcdatumWithoutValue.toRational(0), Rational(-1, 1));

}



TEST_F(IptcdatumTest_683, ToRational_CallsToRationalOnValue_683) {

    EXPECT_CALL(*mockValue, toRational(0)).WillOnce(Return(Rational(1, 2)));

    EXPECT_EQ(iptcdatum.toRational(0), Rational(1, 2));

}



TEST_F(IptcdatumTest_683, ToRational_ReturnsFirstElementWhenIndexZero_683) {

    EXPECT_CALL(*mockValue, count()).WillOnce(Return(2));

    EXPECT_CALL(*mockValue, toRational(0)).WillOnce(Return(Rational(1, 3)));

    EXPECT_EQ(iptcdatum.toRational(0), Rational(1, 3));

}



TEST_F(IptcdatumTest_683, ToRational_ReturnsCorrectElementWhenIndexWithinBounds_683) {

    EXPECT_CALL(*mockValue, count()).WillOnce(Return(2));

    EXPECT_CALL(*mockValue, toRational(1)).WillOnce(Return(Rational(2, 3)));

    EXPECT_EQ(iptcdatum.toRational(1), Rational(2, 3));

}



TEST_F(IptcdatumTest_683, ToRational_ReturnsNegativeOneWhenIndexOutOfUpperBounds_683) {

    EXPECT_CALL(*mockValue, count()).WillOnce(Return(1));

    EXPECT_EQ(iptcdatum.toRational(1), Rational(-1, 1));

}



TEST_F(IptcdatumTest_683, ToRational_ReturnsNegativeOneWhenIndexOutOfLowerBounds_683) {

    EXPECT_CALL(*mockValue, count()).WillOnce(Return(1));

    EXPECT_EQ(iptcdatum.toRational(-1), Rational(-1, 1));

}
