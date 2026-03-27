#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/generators/catch_generators_random.hpp"



using namespace Catch::Generators;

using ::testing::Eq;



class RandomGeneratorTest_351 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if necessary

};



TEST_F(RandomGeneratorTest_351, GeneratesValueWithinRange_351) {

    auto gen = random(0, 10);

    for (int i = 0; i < 100; ++i) {

        int value = gen.get();

        EXPECT_GE(value, 0);

        EXPECT_LE(value, 10);

        gen.next();

    }

}



TEST_F(RandomGeneratorTest_351, GeneratesDifferentValues_351) {

    auto gen = random(0, 10);

    std::set<int> values;

    for (int i = 0; i < 10; ++i) {

        int value = gen.get();

        values.insert(value);

        gen.next();

    }

    EXPECT_LT(values.size(), 10); // It's probabilistic, but with a small range and count, we expect some repetition

}



TEST_F(RandomGeneratorTest_351, BoundaryConditionZeroRange_351) {

    auto gen = random(5, 5);

    for (int i = 0; i < 10; ++i) {

        int value = gen.get();

        EXPECT_EQ(value, 5);

        gen.next();

    }

}



TEST_F(RandomGeneratorTest_351, BoundaryConditionNegativeRange_351) {

    auto gen = random(-10, -5);

    for (int i = 0; i < 100; ++i) {

        int value = gen.get();

        EXPECT_GE(value, -10);

        EXPECT_LE(value, -5);

        gen.next();

    }

}



TEST_F(RandomGeneratorTest_351, BoundaryConditionMixedSignRange_351) {

    auto gen = random(-5, 5);

    for (int i = 0; i < 100; ++i) {

        int value = gen.get();

        EXPECT_GE(value, -5);

        EXPECT_LE(value, 5);

        gen.next();

    }

}
