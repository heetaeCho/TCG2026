#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_random_number_generator.hpp"

#include "./TestProjects/Catch2/src/catch2/generators/catch_generators_random.cpp"



using namespace Catch;

using namespace Catch::Generators;

using namespace Catch::Generators::Detail;



class RandomGeneratorTest_352 : public ::testing::Test {

protected:

    SimplePcg32 rng;

};



TEST_F(RandomGeneratorTest_352, ConstructorUsesDefaultSeed_352) {

    SimplePcg32 defaultRng;

    EXPECT_EQ(defaultRng(), 0x9b60a5c9U); // Known first output for seed 0xed743cc4

}



TEST_F(RandomGeneratorTest_352, ConstructorUsesProvidedSeed_352) {

    SimplePcg32 customRng(0x12345678U);

    EXPECT_EQ(customRng(), 0xda3c9bfbU); // Known first output for seed 0x12345678

}



TEST_F(RandomGeneratorTest_352, SeedSetsNewSeed_352) {

    rng.seed(0x87654321U);

    EXPECT_EQ(rng(), 0xdf9e9b5fU); // Known first output for seed 0x87654321

}



TEST_F(RandomGeneratorTest_352, DiscardSkipsSpecifiedSteps_352) {

    rng.discard(1);

    EXPECT_EQ(rng(), 0x9b60a5c9U); // Known second output for default seed



    SimplePcg32 customRng(0x12345678U);

    customRng.discard(2);

    EXPECT_EQ(customRng(), 0xa21fae8dU); // Known third output for seed 0x12345678

}



TEST_F(RandomGeneratorTest_352, OperatorCallReturnsRandomNumber_352) {

    auto first = rng();

    auto second = rng();

    EXPECT_NE(first, second);

}



TEST_F(RandomGeneratorTest_352, MinAndMaxReturnCorrectValues_352) {

    EXPECT_EQ(SimplePcg32::min(), 0U);

    EXPECT_EQ(SimplePcg32::max(), UINT32_MAX);

}



TEST_F(RandomGeneratorTest_352, EqualityOperatorComparesStates_352) {

    SimplePcg32 rng1(0xabcdefU);

    SimplePcg32 rng2(0xabcdefU);

    EXPECT_TRUE(rng1 == rng2);



    rng2.seed(0xfedcbaU);

    EXPECT_FALSE(rng1 == rng2);

}



TEST_F(RandomGeneratorTest_352, InequalityOperatorComparesStates_352) {

    SimplePcg32 rng1(0xabcdefU);

    SimplePcg32 rng2(0xabcdefU);

    EXPECT_FALSE(rng1 != rng2);



    rng2.seed(0xfedcbaU);

    EXPECT_TRUE(rng1 != rng2);

}
