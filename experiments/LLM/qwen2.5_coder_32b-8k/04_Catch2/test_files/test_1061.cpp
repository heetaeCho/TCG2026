#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_generators.hpp"

#include "catch2/catch_generators_random.hpp"



using namespace Catch::Generators;



class RandomFloatingGeneratorTest_1061 : public ::testing::Test {

protected:

    RandomFloatingGenerator<long double> generator_{0.0L, 1.0L, 42};



    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Teardown if necessary

    }

};



TEST_F(RandomFloatingGeneratorTest_1061, NextReturnsTrue_1061) {

    EXPECT_TRUE(generator_.next());

}



TEST_F(RandomFloatingGeneratorTest_1061, GetReturnsValueInRange_1061) {

    generator_.next();

    long double value = generator_.get();

    EXPECT_GE(value, 0.0L);

    EXPECT_LE(value, 1.0L);

}



TEST_F(RandomFloatingGeneratorTest_1061, GetConsistentWithNext_1061) {

    for (int i = 0; i < 10; ++i) {

        EXPECT_TRUE(generator_.next());

        long double value = generator_.get();

        EXPECT_GE(value, 0.0L);

        EXPECT_LE(value, 1.0L);

    }

}



TEST_F(RandomFloatingGeneratorTest_1061, ConstructorWithSeedProducesDeterministicSequence_1061) {

    RandomFloatingGenerator<long double> gen1{0.0L, 1.0L, 42};

    RandomFloatingGenerator<long double> gen2{0.0L, 1.0L, 42};



    for (int i = 0; i < 5; ++i) {

        EXPECT_TRUE(gen1.next());

        EXPECT_TRUE(gen2.next());

        EXPECT_EQ(gen1.get(), gen2.get());

    }

}



TEST_F(RandomFloatingGeneratorTest_1061, BoundaryValuesInConstructor_1061) {

    RandomFloatingGenerator<long double> gen_min{std::numeric_limits<long double>::lowest(), std::numeric_limits<long double>::max(), 42};

    EXPECT_TRUE(gen_min.next());

    long double value = gen_min.get();

    EXPECT_GE(value, std::numeric_limits<long double>::lowest());

    EXPECT_LE(value, std::numeric_limits<long double>::max());

}



TEST_F(RandomFloatingGeneratorTest_1061, SameRangeDifferentSeedsProduceDifferentSequences_1061) {

    RandomFloatingGenerator<long double> gen1{0.0L, 1.0L, 42};

    RandomFloatingGenerator<long double> gen2{0.0L, 1.0L, 84};



    EXPECT_TRUE(gen1.next());

    EXPECT_TRUE(gen2.next());



    EXPECT_NE(gen1.get(), gen2.get());

}
