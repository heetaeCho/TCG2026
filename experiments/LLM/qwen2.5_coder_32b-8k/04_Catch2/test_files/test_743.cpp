#include <gtest/gtest.h>

#include "catch2/catch_config.hpp"



class CatchConfigTest : public ::testing::Test {

protected:

    Catch::ConfigData data;

    Catch::Config config;



    void SetUp() override {

        data.benchmarkConfidenceInterval = 0.95;

        config = Catch::Config(data);

    }

};



TEST_F(CatchConfigTest_NormalOperation_743, BenchmarkConfidenceInterval_ReturnsCorrectValue_743) {

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.95);

}



TEST_F(CatchConfigTest_BoundaryConditions_743, BenchmarkConfidenceInterval_MinimumValue_743) {

    data.benchmarkConfidenceInterval = 0.0;

    config = Catch::Config(data);

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 0.0);

}



TEST_F(CatchConfigTest_BoundaryConditions_743, BenchmarkConfidenceInterval_MaximumValue_743) {

    data.benchmarkConfidenceInterval = 1.0;

    config = Catch::Config(data);

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.0);

}



TEST_F(CatchConfigTest_ExceptionalCases_743, BenchmarkConfidenceInterval_OutOfRange_Low_743) {

    data.benchmarkConfidenceInterval = -0.1;

    config = Catch::Config(data);

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), -0.1); // Assuming no clamping or validation

}



TEST_F(CatchConfigTest_ExceptionalCases_743, BenchmarkConfidenceInterval_OutOfRange_High_743) {

    data.benchmarkConfidenceInterval = 1.1;

    config = Catch::Config(data);

    EXPECT_DOUBLE_EQ(config.benchmarkConfidenceInterval(), 1.1); // Assuming no clamping or validation

}
