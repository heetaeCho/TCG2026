#include <gtest/gtest.h>

#include <catch2/generators/catch_generators_random.hpp>



using namespace Catch::Generators;



class RandomFloatingGeneratorTest_348 : public ::testing::Test {

protected:

    std::unique_ptr<RandomFloatingGenerator<long double>> generator;



    void SetUp() override {

        generator = std::make_unique<RandomFloatingGenerator<long double>>(0.0L, 1.0L, 42);

    }

};



TEST_F(RandomFloatingGeneratorTest_348, GetInitialValueInRange_348) {

    long double value = generator->get();

    EXPECT_GE(value, 0.0L);

    EXPECT_LE(value, 1.0L);

}



TEST_F(RandomFloatingGeneratorTest_348, NextAdvancesToNewValue_348) {

    long double first_value = generator->get();

    generator->next();

    long double second_value = generator->get();

    EXPECT_NE(first_value, second_value);

}



TEST_F(RandomFloatingGeneratorTest_348, BoundaryConditionMinValue_348) {

    // Given the random nature, this might not always pass. 

    // It's a probabilistic test to check if we ever get close to the boundary.

    bool got_min = false;

    for (size_t i = 0; i < 1000; ++i) {

        long double value = generator->get();

        generator->next();

        if (value <= 0.0L) {

            got_min = true;

            break;

        }

    }

    EXPECT_TRUE(got_min);

}



TEST_F(RandomFloatingGeneratorTest_348, BoundaryConditionMaxValue_348) {

    // Given the random nature, this might not always pass.

    // It's a probabilistic test to check if we ever get close to the boundary.

    bool got_max = false;

    for (size_t i = 0; i < 1000; ++i) {

        long double value = generator->get();

        generator->next();

        if (value >= 1.0L) {

            got_max = true;

            break;

        }

    }

    EXPECT_TRUE(got_max);

}



TEST_F(RandomFloatingGeneratorTest_348, NextReturnsTrue_348) {

    bool result = generator->next();

    EXPECT_TRUE(result);

}
