#include <gtest/gtest.h>

#include <catch2/matchers/catch_matchers_floating_point.hpp>



using namespace Catch::Matchers;



class WithinRelMatcherTest_1051 : public ::testing::Test {

protected:

    double target = 1.0;

    double epsilon = 1e-6;

    WithinRelMatcher matcher{target, epsilon};

};



TEST_F(WithinRelMatcherTest_1051, Match_ReturnsTrueForExactMatch_1051) {

    EXPECT_TRUE(matcher.match(target));

}



TEST_F(WithinRelMatcherTest_1051, Match_ReturnsTrueForValueWithinEpsilon_1051) {

    double value = target * (1 + 0.99 * epsilon);

    EXPECT_TRUE(matcher.match(value));

}



TEST_F(WithinRelMatcherTest_1051, Match_ReturnsFalseForValueOutsideEpsilon_1051) {

    double value = target * (1 + epsilon);

    EXPECT_FALSE(matcher.match(value));

}



TEST_F(WithinRelMatcherTest_1051, Match_HandlesNegativeTarget_1051) {

    WithinRelMatcher negativeMatcher{-1.0, epsilon};

    double value = -1.0 * (1 - 0.99 * epsilon);

    EXPECT_TRUE(negativeMatcher.match(value));

}



TEST_F(WithinRelMatcherTest_1051, Match_HandlesZeroTarget_1051) {

    WithinRelMatcher zeroMatcher{0.0, epsilon};

    double value = epsilon;

    EXPECT_FALSE(zeroMatcher.match(value));

}



TEST_F(WithinRelMatcherTest_1051, Constructor_ThrowsOnNegativeEpsilon_1051) {

    EXPECT_THROW({ WithinRelMatcher invalidMatcher(target, -epsilon); }, std::domain_error);

}



TEST_F(WithinRelMatcherTest_1051, Constructor_ThrowsOnEpsilonEqualToOne_1051) {

    EXPECT_THROW({ WithinRelMatcher invalidMatcher(target, 1.0); }, std::domain_error);

}



TEST_F(WithinRelMatcherTest_1051, Describe_ReturnsCorrectDescription_1051) {

    std::string expectedDescription = "is within " + std::to_string(epsilon * 100) + "% of " + std::to_string(target);

    EXPECT_EQ(matcher.describe(), expectedDescription);

}
