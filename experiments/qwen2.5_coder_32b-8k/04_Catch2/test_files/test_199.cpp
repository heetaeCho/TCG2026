#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_floating_point.hpp"



using namespace Catch::Matchers;



class WithinUlpsMatcherTest_199 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(WithinUlpsMatcherTest_199, MatchDoubleExactMatch_199) {

    WithinUlpsMatcher matcher(3.0, 0, Detail::FloatingPointKind::Double);

    EXPECT_TRUE(matcher.match(3.0));

}



TEST_F(WithinUlpsMatcherTest_199, MatchDoubleWithinUlps_199) {

    WithinUlpsMatcher matcher(3.0, 4, Detail::FloatingPointKind::Double);

    EXPECT_TRUE(matcher.match(3.0 + std::numeric_limits<double>::epsilon() * 2));

}



TEST_F(WithinUlpsMatcherTest_199, MatchDoubleOutsideUlps_199) {

    WithinUlpsMatcher matcher(3.0, 4, Detail::FloatingPointKind::Double);

    EXPECT_FALSE(matcher.match(3.0 + std::numeric_limits<double>::epsilon() * 5));

}



TEST_F(WithinUlpsMatcherTest_199, MatchFloatExactMatch_199) {

    WithinUlpsMatcher matcher(static_cast<float>(3.0), 0, Detail::FloatingPointKind::Float);

    EXPECT_TRUE(matcher.match(static_cast<float>(3.0)));

}



TEST_F(WithinUlpsMatcherTest_199, MatchFloatWithinUlps_199) {

    WithinUlpsMatcher matcher(static_cast<float>(3.0), 4, Detail::FloatingPointKind::Float);

    EXPECT_TRUE(matcher.match(static_cast<float>(3.0 + std::numeric_limits<float>::epsilon() * 2)));

}



TEST_F(WithinUlpsMatcherTest_199, MatchFloatOutsideUlps_199) {

    WithinUlpsMatcher matcher(static_cast<float>(3.0), 4, Detail::FloatingPointKind::Float);

    EXPECT_FALSE(matcher.match(static_cast<float>(3.0 + std::numeric_limits<float>::epsilon() * 5)));

}



TEST_F(WithinUlpsMatcherTest_199, DescribeDoubleMatch_199) {

    WithinUlpsMatcher matcher(3.0, 4, Detail::FloatingPointKind::Double);

    EXPECT_EQ(matcher.describe(), "is within 4 ulp(s) of 3");

}



TEST_F(WithinUlpsMatcherTest_199, DescribeFloatMatch_199) {

    WithinUlpsMatcher matcher(static_cast<float>(3.0), 4, Detail::FloatingPointKind::Float);

    EXPECT_EQ(matcher.describe(), "is within 4 ulp(s) of 3");

}



TEST_F(WithinUlpsMatcherTest_199, InvalidType_199) {

    WithinUlpsMatcher matcher(3.0, 4, static_cast<Detail::FloatingPointKind>(2));

    EXPECT_THROW(matcher.match(3.0), std::logic_error);

}
