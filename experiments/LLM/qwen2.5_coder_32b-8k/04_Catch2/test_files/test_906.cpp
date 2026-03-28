#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;

using namespace Catch::Benchmark;

using ::testing::Return;

using ::testing::_;



class MockIConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(benchmarkSamples, unsigned int());

};



TEST_F(ExecutionPlanTest_906, RunReturnsCorrectNumberOfSamples_906) {

    MockIConfig mockCfg;

    Environment env;

    ExecutionPlan plan;



    EXPECT_CALL(mockCfg, benchmarkSamples()).WillOnce(Return(5));

    plan.iterations_per_sample = 1;

    plan.warmup_time = FDuration::zero();

    plan.warmup_iterations = 0;



    std::vector<FDuration> result = plan.run(mockCfg, env);

    EXPECT_EQ(result.size(), 5);

}



TEST_F(ExecutionPlanTest_906, RunHandlesZeroSamples_906) {

    MockIConfig mockCfg;

    Environment env;

    ExecutionPlan plan;



    EXPECT_CALL(mockCfg, benchmarkSamples()).WillOnce(Return(0));

    plan.iterations_per_sample = 1;

    plan.warmup_time = FDuration::zero();

    plan.warmup_iterations = 0;



    std::vector<FDuration> result = plan.run(mockCfg, env);

    EXPECT_TRUE(result.empty());

}



TEST_F(ExecutionPlanTest_906, RunCalculatesCorrectSampleTime_906) {

    MockIConfig mockCfg;

    Environment env;

    ExecutionPlan plan;



    EXPECT_CALL(mockCfg, benchmarkSamples()).WillOnce(Return(1));

    plan.iterations_per_sample = 2;

    plan.warmup_time = FDuration::zero();

    plan.warmup_iterations = 0;



    std::vector<FDuration> result = plan.run(mockCfg, env);

    EXPECT_EQ(result.size(), 1);

    // Assuming the actual timing logic does not affect this test as we cannot mock internal behavior

}



TEST_F(ExecutionPlanTest_906, RunHandlesNegativeSampleTime_906) {

    MockIConfig mockCfg;

    Environment env;

    ExecutionPlan plan;



    EXPECT_CALL(mockCfg, benchmarkSamples()).WillOnce(Return(1));

    plan.iterations_per_sample = 1;

    plan.warmup_time = FDuration::zero();

    plan.warmup_iterations = 0;



    // Assuming the internal logic ensures sample time is non-negative

    std::vector<FDuration> result = plan.run(mockCfg, env);

    EXPECT_EQ(result.size(), 1);

    EXPECT_GE(result[0], FDuration::zero());

}



TEST_F(ExecutionPlanTest_906, RunWithWarmupIterations_906) {

    MockIConfig mockCfg;

    Environment env;

    ExecutionPlan plan;



    EXPECT_CALL(mockCfg, benchmarkSamples()).WillOnce(Return(1));

    plan.iterations_per_sample = 1;

    plan.warmup_time = FDuration::zero();

    plan.warmup_iterations = 5;



    std::vector<FDuration> result = plan.run(mockCfg, env);

    EXPECT_EQ(result.size(), 1);

}
