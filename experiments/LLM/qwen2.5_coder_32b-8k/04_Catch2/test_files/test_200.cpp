#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_matchers_floating_point.hpp"



using namespace Catch::Matchers;

using namespace Detail;



class WithinUlpsMatcherTest_200 : public ::testing::Test {

protected:

    WithinUlpsMatcher matcherDouble;

    WithinUlpsMatcher matcherFloat;



    WithinUlpsMatcherTest_200()

        : matcherDouble(1.0, 4, FloatingPointKind::Double),

          matcherFloat(1.0f, 4, FloatingPointKind::Float) {}

};



TEST_F(WithinUlpsMatcherTest_200, DescribeGeneratesCorrectStringForDouble_200) {

    std::string description = matcherDouble.describe();

    EXPECT_EQ(description, "is within 4 ULPs of 1 ([-1.00000000000000035527136788005009e-15, 3])");

}



TEST_F(WithinUlpsMatcherTest_200, DescribeGeneratesCorrectStringForFloat_200) {

    std::string description = matcherFloat.describe();

    EXPECT_EQ(description, "is within 4 ULPs of 1f ([0.9999980335712432861328125, 1.0000029754638671875])");

}



TEST_F(WithinUlpsMatcherTest_200, MatchReturnsTrueForValueWithinUlpsDouble_200) {

    EXPECT_TRUE(matcherDouble.match(1.0 + std::numeric_limits<double>::epsilon() * 2));

}



TEST_F(WithinUlpsMatcherTest_200, MatchReturnsFalseForValueOutsideUlpsDouble_200) {

    EXPECT_FALSE(matcherDouble.match(1.0 + std::numeric_limits<double>::epsilon() * 5));

}



TEST_F(WithinUlpsMatcherTest_200, MatchReturnsTrueForValueWithinUlpsFloat_200) {

    EXPECT_TRUE(matcherFloat.match(1.0f + std::numeric_limits<float>::epsilon() * 2));

}



TEST_F(WithinUlpsMatcherTest_200, MatchReturnsFalseForValueOutsideUlpsFloat_200) {

    EXPECT_FALSE(matcherFloat.match(1.0f + std::numeric_limits<float>::epsilon() * 5));

}
