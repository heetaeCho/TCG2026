#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/generators/catch_generators_random.hpp"



using namespace Catch::Generators;



class RandomIntegerGeneratorTest_349 : public ::testing::Test {

protected:

    std::uint32_t seed = 12345;

    int lower_bound = 0;

    int upper_bound = 100;

    RandomIntegerGenerator<int> generator{lower_bound, upper_bound, seed};



    void SetUp() override {

        // Reset the generator if needed

        generator.next();

    }

};



TEST_F(RandomIntegerGeneratorTest_349, GetReturnsInitialValue_349) {

    auto initial_value = generator.get();

    EXPECT_GE(initial_value, lower_bound);

    EXPECT_LE(initial_value, upper_bound);

}



TEST_F(RandomIntegerGeneratorTest_349, NextChangesValue_349) {

    auto initial_value = generator.get();

    generator.next();

    auto new_value = generator.get();

    EXPECT_NE(initial_value, new_value);

}



TEST_F(RandomIntegerGeneratorTest_349, GetWithinBoundsAfterNext_349) {

    generator.next();

    auto value = generator.get();

    EXPECT_GE(value, lower_bound);

    EXPECT_LE(value, upper_bound);

}



TEST_F(RandomIntegerGeneratorTest_349, BoundaryConditionLowerBound_349) {

    RandomIntegerGenerator<int> boundary_generator{lower_bound, lower_bound, seed};

    EXPECT_EQ(boundary_generator.get(), lower_bound);

}



TEST_F(RandomIntegerGeneratorTest_349, BoundaryConditionUpperBound_349) {

    RandomIntegerGenerator<int> boundary_generator{upper_bound, upper_bound, seed};

    EXPECT_EQ(boundary_generator.get(), upper_bound);

}



// Assuming there are no exceptional cases for this generator based on the interface

```


