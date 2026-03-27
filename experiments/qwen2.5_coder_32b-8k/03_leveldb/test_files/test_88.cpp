#include <gtest/gtest.h>

#include "util/random.h"



namespace {



class RandomTest_88 : public ::testing::Test {

protected:

    leveldb::Random random;



    RandomTest_88() : random(1) {}  // Initialize with a fixed seed for consistent results

};



TEST_F(RandomTest_88, Next_ReturnsValue_88) {

    uint32_t result = random.Next();

    EXPECT_GE(result, 0);

}



TEST_F(RandomTest_88, Uniform_ZeroModulus_ReturnsZero_88) {

    int n = 0;

    uint32_t result = random.Uniform(n);

    EXPECT_EQ(result, 0);

}



TEST_F(RandomTest_88, Uniform_PositiveModulus_ReturnsLessThanN_88) {

    int n = 10;

    uint32_t result = random.Uniform(n);

    EXPECT_GE(result, 0);

    EXPECT_LT(result, n);

}



TEST_F(RandomTest_88, OneIn_ZeroDenominator_ReturnsTrue_88) {

    int n = 0;

    bool result = random.OneIn(n);

    EXPECT_TRUE(result);

}



TEST_F(RandomTest_88, OneIn_OneDenominator_ReturnsTrueOrFalseConsistently_88) {

    int n = 1;

    bool result1 = random.OneIn(n);

    bool result2 = random.OneIn(n);

    EXPECT_EQ(result1, true);

    EXPECT_EQ(result2, true);

}



TEST_F(RandomTest_88, OneIn_LargeDenominator_ReturnsFalseMostly_88) {

    int n = 100000;

    int trueCount = 0;

    for (int i = 0; i < n; ++i) {

        if (random.OneIn(n)) {

            ++trueCount;

        }

    }

    EXPECT_LE(trueCount, n / 10);  // Expect less than 1% to be true

}



TEST_F(RandomTest_88, Skewed_ZeroMaxLog_ReturnsZero_88) {

    int max_log = 0;

    uint32_t result = random.Skewed(max_log);

    EXPECT_EQ(result, 0);

}



TEST_F(RandomTest_88, Skewed_PositiveMaxLog_ReturnsLessThan2PowerMaxLog_88) {

    int max_log = 10;

    uint32_t result = random.Skewed(max_log);

    EXPECT_GE(result, 0);

    EXPECT_LT(result, 1 << max_log);

}



}  // namespace
