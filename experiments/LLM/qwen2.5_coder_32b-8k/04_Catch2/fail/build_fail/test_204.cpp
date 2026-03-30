#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/matchers/catch_matchers_floating_point.hpp"



using namespace Catch::Matchers;



class WithinULPMatcherTest_204 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(WithinULPMatcherTest_204, NormalOperationWithFloat_204) {

    float target = 1.0f;

    uint64_t maxUlpDiff = 1;

    WithinUlpsMatcher matcher(target, maxUlpDiff);

    EXPECT_TRUE(matcher.match(1.0f));

}



TEST_F(WithinULPMatcherTest_204, BoundaryConditionWithFloat_204) {

    float target = 1.0f;

    uint64_t maxUlpDiff = 1;

    WithinUlpsMatcher matcher(target, maxUlpDiff);

    EXPECT_FALSE(matcher.match(1.0000001f)); // Assuming this is outside 1 ULP for a float

}



TEST_F(WithinULPMatcherTest_204, ZeroMaxULPDiff_204) {

    float target = 1.0f;

    uint64_t maxUlpDiff = 0;

    WithinUlpsMatcher matcher(target, maxUlpDiff);

    EXPECT_TRUE(matcher.match(1.0f));

    EXPECT_FALSE(matcher.match(1.0000001f)); // Assuming this is outside 0 ULP for a float

}



TEST_F(WithinULPMatcherTest_204, LargeMaxULPDiff_204) {

    float target = 1.0f;

    uint64_t maxUlpDiff = 1000;

    WithinUlpsMatcher matcher(target, maxUlpDiff);

    EXPECT_TRUE(matcher.match(1.0000001f)); // Assuming this is within 1000 ULP for a float

}



TEST_F(WithinULPMatcherTest_204, NegativeTargetValue_204) {

    float target = -1.0f;

    uint64_t maxUlpDiff = 1;

    WithinUlpsMatcher matcher(target, maxUlpDiff);

    EXPECT_TRUE(matcher.match(-1.0f));

}



TEST_F(WithinULPMatcherTest_204, SmallFloatValues_204) {

    float target = 1e-38f; // Smallest positive normalized value

    uint64_t maxUlpDiff = 1;

    WithinUlpsMatcher matcher(target, maxUlpDiff);

    EXPECT_TRUE(matcher.match(1e-38f));

}



TEST_F(WithinULPMatcherTest_204, LargeFloatValues_204) {

    float target = 3.4e+38f; // Largest positive value

    uint64_t maxUlpDiff = 1;

    WithinUlpsMatcher matcher(target, maxUlpDiff);

    EXPECT_TRUE(matcher.match(3.4e+38f));

}
