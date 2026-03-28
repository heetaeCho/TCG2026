#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/OutputDev.h"



using ::testing::Eq;

using ::testing::NotNull;



class OutputDevTest : public ::testing::Test {

protected:

    OutputDev outputDev;

};



TEST_F(OutputDevTest_GetProfileHash_1075, ReturnsNonNullPointer_1075) {

    auto profileHash = outputDev.getProfileHash();

    EXPECT_THAT(profileHash, NotNull());

}



TEST_F(OutputDevTest_GetProfileHash_1075, ReturnsSamePointerOnSubsequentCalls_1075) {

    auto firstCall = outputDev.getProfileHash();

    auto secondCall = outputDev.getProfileHash();

    EXPECT_EQ(firstCall, secondCall);

}
