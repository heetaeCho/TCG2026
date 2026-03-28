#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/generators/catch_generators_random.hpp"

#include <random>



using namespace Catch::Generators;



class RandomIntegerGeneratorTest : public ::testing::Test {

protected:

    void SetUp() override {

        rng = std::mt19937(42); // Using a fixed seed for reproducibility

        lower_bound = 0;

        upper_bound = 100;

        generator = new RandomIntegerGenerator<int>(lower_bound, upper_bound, rng());

    }



    void TearDown() override {

        delete generator;

    }



    std::mt19937 rng;

    int lower_bound;

    int upper_bound;

    RandomIntegerGenerator<int>* generator;

};



TEST_F(RandomIntegerGeneratorTest_350, NextGeneratesRandomNumberWithinRange_350) {

    EXPECT_TRUE(generator->next());

    int generated_number = generator->get();

    EXPECT_GE(generated_number, lower_bound);

    EXPECT_LE(generated_number, upper_bound);

}



TEST_F(RandomIntegerGeneratorTest_350, GetReturnsSameValueAfterNext_350) {

    generator->next();

    int first_call = generator->get();

    int second_call = generator->get();

    EXPECT_EQ(first_call, second_call);

}



TEST_F(RandomIntegerGeneratorTest_350, NextGeneratesDifferentNumbersOnConsecutiveCalls_350) {

    std::set<int> generated_numbers;

    for (int i = 0; i < 100; ++i) {

        generator->next();

        int number = generator->get();

        generated_numbers.insert(number);

    }

    EXPECT_LT(1, generated_numbers.size());

}



TEST_F(RandomIntegerGeneratorTest_350, NextAlwaysReturnsTrue_350) {

    for (int i = 0; i < 100; ++i) {

        EXPECT_TRUE(generator->next());

    }

}
