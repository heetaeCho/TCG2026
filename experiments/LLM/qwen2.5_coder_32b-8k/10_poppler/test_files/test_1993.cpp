#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GooString.h"

#include "DateInfo.h"



class DateInfoTest_1993 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(DateInfoTest_1993, NormalOperation_1993) {

    time_t testTime = 1609459200; // Corresponds to 2021-01-01T00:00:00Z

    auto result = timeToDateString(&testTime);

    EXPECT_EQ(result->c_str(), "D:20210101000000+00'00'");

}



TEST_F(DateInfoTest_1993, BoundaryCondition_StartOfYear_1993) {

    time_t testTime = 1609459199; // Corresponds to 2020-12-31T23:59:59Z

    auto result = timeToDateString(&testTime);

    EXPECT_EQ(result->c_str(), "D:20201231235959+00'00'");

}



TEST_F(DateInfoTest_1993, BoundaryCondition_EndOfYear_1993) {

    time_t testTime = 1640995200; // Corresponds to 2022-01-01T00:00:00Z

    auto result = timeToDateString(&testTime);

    EXPECT_EQ(result->c_str(), "D:20220101000000+00'00'");

}



TEST_F(DateInfoTest_1993, NullTimePointer_1993) {

    auto result = timeToDateString(nullptr);

    EXPECT_TRUE(result->isEmpty());

}
