#include <gtest/gtest.h>

#include <catch2/internal/catch_random_number_generator.hpp>



class SimplePcg32Test_328 : public ::testing::Test {

protected:

    Catch::SimplePcg32 rng;

};



TEST_F(SimplePcg32Test_328, DefaultConstructorSeedsWithDefaultSeed_328) {

    // Since we treat the implementation as a black box, we can only test observable behavior.

    // We assume that the default seed leads to a specific sequence of numbers.

    uint64_t first_random_number = rng();

    rng.seed(0xed743cc4U);

    EXPECT_EQ(first_random_number, rng());

}



TEST_F(SimplePcg32Test_328, ParameterizedConstructorSeedsCorrectly_328) {

    Catch::SimplePcg32 rng1(0xdeadbeefU);

    rng.seed(0xdeadbeefU);

    EXPECT_EQ(rng(), rng1());

}



TEST_F(SimplePcg32Test_328, SeedFunctionResetsSequence_328) {

    uint64_t first_random_number = rng();

    rng.seed(0xdeadbeefU);

    EXPECT_NE(first_random_number, rng());

    rng.seed(0xed743cc4U); // Reset to default seed

    EXPECT_EQ(first_random_number, rng());

}



TEST_F(SimplePcg32Test_328, DiscardFunctionAdvancesSequence_328) {

    uint64_t first_random_number = rng();

    rng.discard(1);

    EXPECT_NE(first_random_number, rng());

}



TEST_F(SimplePcg32Test_328, MinMaxConstantsAreCorrect_328) {

    EXPECT_EQ(Catch::SimplePcg32::min(), 0);

    // Assuming max is the maximum value for uint64_t

    EXPECT_EQ(Catch::SimplePcg32::max(), UINT64_MAX);

}



TEST_F(SimplePcg32Test_328, OperatorEqualsComparesStatesCorrectly_328) {

    Catch::SimplePcg32 rng1(0xdeadbeefU);

    Catch::SimplePcg32 rng2(0xdeadbeefU);

    EXPECT_TRUE(rng1 == rng2);



    rng2.seed(0xcafebabeU);

    EXPECT_FALSE(rng1 == rng2);

}



TEST_F(SimplePcg32Test_328, OperatorNotEqualsComparesStatesCorrectly_328) {

    Catch::SimplePcg32 rng1(0xdeadbeefU);

    Catch::SimplePcg32 rng2(0xdeadbeefU);

    EXPECT_FALSE(rng1 != rng2);



    rng2.seed(0xcafebabeU);

    EXPECT_TRUE(rng1 != rng2);

}
