#include <gtest/gtest.h>

#include "catch2/generators/catch_generators_random.hpp"



using namespace Catch::Generators;



class RandomFloatingGeneratorTest_1059 : public ::testing::Test {

protected:

    const double lower_bound = 0.0;

    const double upper_bound = 1.0;

    const std::uint32_t seed = 42;



    RandomFloatingGenerator<double> generator{lower_bound, upper_bound, seed};

};



TEST_F(RandomFloatingGeneratorTest_1059, GetReturnsValueInRange_1059) {

    EXPECT_GE(generator.get(), lower_bound);

    EXPECT_LE(generator.get(), upper_bound);

}



TEST_F(RandomFloatingGeneratorTest_1059, NextAdvancesToNewValue_1059) {

    const auto first_value = generator.get();

    generator.next();

    const auto second_value = generator.get();

    EXPECT_NE(first_value, second_value);

}



TEST_F(RandomFloatingGeneratorTest_1059, NextReturnsTrueOnSuccess_1059) {

    EXPECT_TRUE(generator.next());

}



// Boundary conditions

TEST_F(RandomFloatingGeneratorTest_1059, GetSameValueAfterResetSeed_1059) {

    const auto first_value = generator.get();

    RandomFloatingGenerator<double> same_seed_generator{lower_bound, upper_bound, seed};

    EXPECT_EQ(first_value, same_seed_generator.get());

}



// Exceptional or error cases

TEST_F(RandomFloatingGeneratorTest_1059, GetDoesNotThrowException_1059) {

    EXPECT_NO_THROW(generator.get());

}



TEST_F(RandomFloatingGeneratorTest_1059, NextDoesNotThrowException_1059) {

    EXPECT_NO_THROW(generator.next());

}
