#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;

using namespace Catch::Clara::Detail;



class BoundValueRefTest_378 : public ::testing::Test {

protected:

    std::vector<int> vecRef;

    BoundValueRef<std::vector<int>> boundRef;



    BoundValueRefTest_378() : vecRef(), boundRef(vecRef) {}

};



TEST_F(BoundValueRefTest_378, PutIncreasesCount_378) {

    ASSERT_EQ(0, vecRef.size());

    auto result = boundRef.setValue("42");

    EXPECT_TRUE(result);

    EXPECT_EQ(1, vecRef.size());

}



TEST_F(BoundValueRefTest_378, InvalidInputDoesNotIncreaseCount_378) {

    ASSERT_EQ(0, vecRef.size());

    auto result = boundRef.setValue("invalid");

    EXPECT_FALSE(result);

    EXPECT_EQ(0, vecRef.size());

}



TEST_F(BoundValueRefTest_378, MultipleValidInputsIncreaseCount_378) {

    ASSERT_EQ(0, vecRef.size());

    auto result1 = boundRef.setValue("42");

    auto result2 = boundRef.setValue("99");

    EXPECT_TRUE(result1);

    EXPECT_TRUE(result2);

    EXPECT_EQ(2, vecRef.size());

}



TEST_F(BoundValueRefTest_378, BoundaryConditionEmptyString_378) {

    ASSERT_EQ(0, vecRef.size());

    auto result = boundRef.setValue("");

    EXPECT_FALSE(result);

    EXPECT_EQ(0, vecRef.size());

}
