#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/generators/catch_generators_random.hpp"



using namespace Catch::Generators;



class RandomFloatingGeneratorTest_346 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize with a fixed seed for reproducibility

        gen = std::make_unique<RandomFloatingGenerator<double>>(0.0, 1.0, 42);

    }



    std::unique_ptr<RandomFloatingGenerator<double>> gen;

};



TEST_F(RandomFloatingGeneratorTest_346, GetInitialValueWithinRange_346) {

    double value = gen->get();

    EXPECT_GE(value, 0.0);

    EXPECT_LE(value, 1.0);

}



TEST_F(RandomFloatingGeneratorTest_346, NextAdvancesToNextValue_346) {

    double firstValue = gen->get();

    gen->next();

    double secondValue = gen->get();

    EXPECT_NE(firstValue, secondValue);

}



TEST_F(RandomFloatingGeneratorTest_346, GetConsistentAfterMultipleNextCalls_346) {

    for (int i = 0; i < 10; ++i) {

        double value = gen->get();

        EXPECT_GE(value, 0.0);

        EXPECT_LE(value, 1.0);

        gen->next();

    }

}



TEST_F(RandomFloatingGeneratorTest_346, BoundaryConditionMinValue_346) {

    gen.reset(new RandomFloatingGenerator<double>(-1.0, -1.0, 42));

    double value = gen->get();

    EXPECT_DOUBLE_EQ(value, -1.0);

}



TEST_F(RandomFloatingGeneratorTest_346, BoundaryConditionMaxValue_346) {

    gen.reset(new RandomFloatingGenerator<double>(1.0, 1.0, 42));

    double value = gen->get();

    EXPECT_DOUBLE_EQ(value, 1.0);

}
