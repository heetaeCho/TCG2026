#include <gtest/gtest.h>

#include "catch_random_number_generator.hpp"



using namespace Catch;



class SimplePcg32Test : public ::testing::Test {

protected:

    SimplePcg32 rng;

};



TEST_F(SimplePcg32Test_642, DefaultConstructorInitializesWithSeed_642) {

    SimplePcg32 defaultRng;

    EXPECT_EQ(defaultRng.m_state, 0xed743cc4U);

}



TEST_F(SimplePcg32Test_642, SeedConstructorSetsState_642) {

    SimplePcg32 rng(12345U);

    EXPECT_EQ(rng.m_state, 12345U);

}



TEST_F(SimplePcg32Test_642, SeedMethodUpdatesState_642) {

    rng.seed(54321U);

    EXPECT_EQ(rng.m_state, 54321U);

}



TEST_F(SimplePcg32Test_642, DiscardAdvancesState_642) {

    std::uint64_t initialState = rng.m_state;

    rng.discard(10);

    EXPECT_NE(rng.m_state, initialState);

}



TEST_F(SimplePcg32Test_642, OperatorCallGeneratesNumberInRange_642) {

    result_type number = rng();

    EXPECT_GE(number, SimplePcg32::min());

    EXPECT_LE(number, SimplePcg32::max());

}



TEST_F(SimplePcg32Test_642, MinMaxAreConstants_642) {

    EXPECT_EQ(SimplePcg32::min(), 0U);

    EXPECT_EQ(SimplePcg32::max(), UINT32_MAX);

}



TEST_F(SimplePcg32Test_642, EqualityOperatorComparesState_642) {

    SimplePcg32 rng1(12345U);

    SimplePcg32 rng2(12345U);

    EXPECT_EQ(rng1, rng2);



    SimplePcg32 rng3(54321U);

    EXPECT_NE(rng1, rng3);

}



TEST_F(SimplePcg32Test_642, InequalityOperatorComparesState_642) {

    SimplePcg32 rng1(12345U);

    SimplePcg32 rng2(12345U);

    EXPECT_FALSE(rng1 != rng2);



    SimplePcg32 rng3(54321U);

    EXPECT_TRUE(rng1 != rng3);

}

```



Note: The above test cases assume that `m_state` is accessible for the sake of validation. However, according to the constraints, we should not access private/internal state directly. Therefore, the tests involving `m_state` should be reconsidered based on observable behavior only.



Here is a revised version without direct access to `m_state`:



```cpp

#include <gtest/gtest.h>

#include "catch_random_number_generator.hpp"



using namespace Catch;



class SimplePcg32Test : public ::testing::Test {

protected:

    SimplePcg32 rng;

};



TEST_F(SimplePcg32Test_642, DefaultConstructorInitializesConsistently_642) {

    SimplePcg32 defaultRng1;

    SimplePcg32 defaultRng2;

    EXPECT_EQ(defaultRng1(), defaultRng2());

}



TEST_F(SimplePcg32Test_642, SeedConstructorSetsStateConsistently_642) {

    SimplePcg32 rng1(12345U);

    SimplePcg32 rng2(12345U);

    EXPECT_EQ(rng1(), rng2());

}



TEST_F(SimplePcg32Test_642, SeedMethodUpdatesStateConsistently_642) {

    rng.seed(54321U);

    SimplePcg32 rng2;

    rng2.seed(54321U);

    EXPECT_EQ(rng(), rng2());

}



TEST_F(SimplePcg32Test_642, DiscardAdvancesStateConsistently_642) {

    rng.discard(10);

    SimplePcg32 rng2;

    rng2.discard(10);

    EXPECT_EQ(rng(), rng2());

}



TEST_F(SimplePcg32Test_642, OperatorCallGeneratesNumberInRange_642) {

    result_type number = rng();

    EXPECT_GE(number, SimplePcg32::min());

    EXPECT_LE(number, SimplePcg32::max());

}



TEST_F(SimplePcg32Test_642, MinMaxAreConstants_642) {

    EXPECT_EQ(SimplePcg32::min(), 0U);

    EXPECT_EQ(SimplePcg32::max(), UINT32_MAX);

}



TEST_F(SimplePcg32Test_642, EqualityOperatorComparesConsistently_642) {

    SimplePcg32 rng1(12345U);

    SimplePcg32 rng2(12345U);

    EXPECT_TRUE(rng1 == rng2);



    SimplePcg32 rng3(54321U);

    EXPECT_FALSE(rng1 == rng3);

}



TEST_F(SimplePcg32Test_642, InequalityOperatorComparesConsistently_642) {

    SimplePcg32 rng1(12345U);

    SimplePcg32 rng2(12345U);

    EXPECT_FALSE(rng1 != rng2);



    SimplePcg32 rng3(54321U);

    EXPECT_TRUE(rng1 != rng3);

}
