#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;



class NearestTowardMinusInfinityTest_366 : public ::testing::Test {

protected:

    nearest_toward_minus_infinity_t policy;

};



TEST_F(NearestTowardMinusInfinityTest_366, ShorterInterval_NegativeSignificand_366) {

    auto s = SignedSignificandBits{-1};

    auto result = policy.shorter_interval(s);

    EXPECT_TRUE(result.is_negative());

}



TEST_F(NearestTowardMinusInfinityTest_366, ShorterInterval_ZeroSignificand_366) {

    auto s = SignedSignificandBits{0};

    auto result = policy.shorter_interval(s);

    EXPECT_FALSE(result.is_negative());

}



TEST_F(NearestTowardMinusInfinityTest_366, ShorterInterval_PositiveSignificand_366) {

    auto s = SignedSignificandBits{1};

    auto result = policy.shorter_interval(s);

    EXPECT_FALSE(result.is_negative());

}

```


