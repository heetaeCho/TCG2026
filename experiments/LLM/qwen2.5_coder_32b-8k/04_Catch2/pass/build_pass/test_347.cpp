#include <gtest/gtest.h>

#include "catch2/generators/catch_generators_random.hpp"



using namespace Catch::Generators;



class RandomFloatingGeneratorTest_347 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup for tests if needed

    }



    void TearDown() override {

        // Cleanup after tests if needed

    }

};



TEST_F(RandomFloatingGeneratorTest_347, NextReturnsTrue_347) {

    RandomFloatingGenerator<double> gen(0.0, 1.0, 42);

    EXPECT_TRUE(gen.next());

}



TEST_F(RandomFloatingGeneratorTest_347, GetProvidesValidValueInRange_347) {

    RandomFloatingGenerator<float> gen(-5.0f, 5.0f, 42);

    gen.next();

    float value = gen.get();

    EXPECT_GE(value, -5.0f);

    EXPECT_LE(value, 5.0f);

}



TEST_F(RandomFloatingGeneratorTest_347, LongDoubleNextReturnsTrue_347) {

    RandomFloatingGenerator<long double> gen(0.0L, 1.0L, 42);

    EXPECT_TRUE(gen.next());

}



TEST_F(RandomFloatingGeneratorTest_347, LongDoubleGetProvidesValidValueInRange_347) {

    RandomFloatingGenerator<long double> gen(-5.0L, 5.0L, 42);

    gen.next();

    long double value = gen.get();

    EXPECT_GE(value, -5.0L);

    EXPECT_LE(value, 5.0L);

}



TEST_F(RandomFloatingGeneratorTest_347, MultipleNextCallsProduceDifferentValues_347) {

    RandomFloatingGenerator<double> gen(0.0, 1.0, 42);

    gen.next();

    double firstValue = gen.get();

    gen.next();

    double secondValue = gen.get();

    EXPECT_NE(firstValue, secondValue);

}



TEST_F(RandomFloatingGeneratorTest_347, LongDoubleMultipleNextCallsProduceDifferentValues_347) {

    RandomFloatingGenerator<long double> gen(0.0L, 1.0L, 42);

    gen.next();

    long double firstValue = gen.get();

    gen.next();

    long double secondValue = gen.get();

    EXPECT_NE(firstValue, secondValue);

}
