#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;

using namespace Catch::Clara::Detail;



class BoundFlagRefTest_657 : public ::testing::Test {

protected:

    bool flagValue = false;

    BoundFlagRef boundFlagRef;



    BoundFlagRefTest_657() : boundFlagRef(flagValue) {}

};



TEST_F(BoundFlagRefTest_657, SetFlagTrue_ReturnsMatched_657) {

    auto result = boundFlagRef.setFlag(true);

    EXPECT_TRUE(result);

    EXPECT_EQ(result.type(), ParseResultType::Matched);

    EXPECT_TRUE(flagValue);

}



TEST_F(BoundFlagRefTest_657, SetFlagFalse_ReturnsMatched_657) {

    auto result = boundFlagRef.setFlag(false);

    EXPECT_TRUE(result);

    EXPECT_EQ(result.type(), ParseResultType::Matched);

    EXPECT_FALSE(flagValue);

}



TEST_F(BoundFlagRefTest_657, SetFlagMultipleTimes_657) {

    auto result1 = boundFlagRef.setFlag(true);

    EXPECT_TRUE(result1);

    EXPECT_EQ(result1.type(), ParseResultType::Matched);

    EXPECT_TRUE(flagValue);



    auto result2 = boundFlagRef.setFlag(false);

    EXPECT_TRUE(result2);

    EXPECT_EQ(result2.type(), ParseResultType::Matched);

    EXPECT_FALSE(flagValue);

}
