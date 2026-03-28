#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/generators/catch_generators_random.hpp"



using namespace Catch::Generators;



class RandomIntegerGeneratorTest_1060 : public ::testing::Test {

protected:

    std::uint32_t seed = 42;

};



TEST_F(RandomIntegerGeneratorTest_1060, ConstructorInitializesRange_1060) {

    RandomIntegerGenerator<int> gen(1, 10, seed);

    EXPECT_GE(gen.get(), 1);

    EXPECT_LE(gen.get(), 10);

}



TEST_F(RandomIntegerGeneratorTest_1060, NextGeneratesNewNumber_1060) {

    RandomIntegerGenerator<int> gen(1, 10, seed);

    int first = gen.get();

    gen.next();

    int second = gen.get();

    EXPECT_NE(first, second);

}



TEST_F(RandomIntegerGeneratorTest_1060, NextReturnsTrueOnSuccess_1060) {

    RandomIntegerGenerator<int> gen(1, 10, seed);

    EXPECT_TRUE(gen.next());

}



TEST_F(RandomIntegerGeneratorTest_1060, BoundaryConditionMinimumRange_1060) {

    RandomIntegerGenerator<int> gen(5, 5, seed);

    EXPECT_EQ(gen.get(), 5);

    EXPECT_FALSE(gen.next()); // Since there's no range to move in

}



TEST_F(RandomIntegerGeneratorTest_1060, LargeRangeValuesWithinBounds_1060) {

    RandomIntegerGenerator<int> gen(INT_MIN, INT_MAX, seed);

    for (int i = 0; i < 100; ++i) {

        EXPECT_GE(gen.get(), INT_MIN);

        EXPECT_LE(gen.get(), INT_MAX);

        gen.next();

    }

}
