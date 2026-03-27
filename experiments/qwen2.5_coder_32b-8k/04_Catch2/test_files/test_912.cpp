#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"



using namespace Catch::Benchmark;

using namespace testing;



class MockIConfig : public IConfig {

public:

    MOCK_METHOD(bool, allowThrows, (), (const override));

    MOCK_METHOD(StringRef, name, (), (const override));

    MOCK_METHOD(bool, includeSuccessfulResults, (), (const override));

    MOCK_METHOD(bool, shouldDebugBreak, (), (const override));

    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const override));

    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const override));

    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const override));

    MOCK_METHOD(int, abortAfter, (), (const override));

    MOCK_METHOD(bool, showInvisibles, (), (const override));

    MOCK_METHOD(ShowDurations, showDurations, (), (const override));

    MOCK_METHOD(double, minDuration, (), (const override));

    MOCK_METHOD(const TestSpec&, testSpec, (), (const override));

    MOCK_METHOD(bool, hasTestFilters, (), (const override));

    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const override));

    MOCK_METHOD(TestRunOrder, runOrder, (), (const override));

    MOCK_METHOD(uint32_t, rngSeed, (), (const override));

    MOCK_METHOD(unsigned int, shardCount, (), (const override));

    MOCK_METHOD(unsigned int, shardIndex, (), (const override));

    MOCK_METHOD(ColourMode, defaultColourMode, (), (const override));

    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const override));

    MOCK_METHOD(Verbosity, verbosity, (), (const override));

    MOCK_METHOD(bool, skipBenchmarks, (), (const override));

    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const override));

    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const override));

    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const override));

    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const override));

    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const override));

};



class BenchmarkTest_912 : public ::testing::Test {

protected:

    MockIConfig mock_cfg;

    Environment env;

    Benchmark benchmark{"test_benchmark"};



    void SetUp() override {

        // Setup any common state here

        using namespace std::chrono_literals;

        ON_CALL(mock_cfg, benchmarkWarmupTime()).WillByDefault(Return(10ms));

        env.clock_resolution.mean = 1.0s; // Example value for mean clock resolution

    }

};



TEST_F(BenchmarkTest_912, PrepareCalculatesCorrectRunTime_912) {

    using namespace std::chrono_literals;

    EXPECT_CALL(mock_cfg, benchmarkWarmupTime()).WillOnce(Return(15ms));



    auto plan = benchmark.prepare<std::chrono::high_resolution_clock>(mock_cfg, env);

    EXPECT_GE(plan.run_time.count(), 1000 * 15); // min_time should be at least clock_resolution.mean * minimum_ticks

}



TEST_F(BenchmarkTest_912, PrepareCalculatesCorrectIterations_912) {

    using namespace std::chrono_literals;

    EXPECT_CALL(mock_cfg, benchmarkWarmupTime()).WillOnce(Return(10ms));

    EXPECT_CALL(mock_cfg, benchmarkSamples()).WillOnce(Return(5));



    auto plan = benchmark.prepare<std::chrono::high_resolution_clock>(mock_cfg, env);

    double expected_iterations = std::ceil(1.0 * 1000 * Detail::minimum_ticks / plan.elapsed.count()) * plan.elapsed.count() / 1.0 * 5;

    EXPECT_EQ(plan.iterations, static_cast<int>(expected_iterations));

}



TEST_F(BenchmarkTest_912, PrepareUsesBenchmarkSamplesFromConfig_912) {

    using namespace std::chrono_literals;

    EXPECT_CALL(mock_cfg, benchmarkWarmupTime()).WillOnce(Return(10ms));

    EXPECT_CALL(mock_cfg, benchmarkSamples()).WillOnce(Return(3));



    auto plan = benchmark.prepare<std::chrono::high_resolution_clock>(mock_cfg, env);

    EXPECT_EQ(plan.samples, 3);

}



TEST_F(BenchmarkTest_912, PrepareCalculatesMinTimeWhenWarmupIsLessThanMeanTicks_912) {

    using namespace std::chrono_literals;

    EXPECT_CALL(mock_cfg, benchmarkWarmupTime()).WillOnce(Return(1ms));



    auto plan = benchmark.prepare<std::chrono::high_resolution_clock>(mock_cfg, env);

    EXPECT_GE(plan.run_time.count(), 1000 * 1); // min_time should be at least clock_resolution.mean * minimum_ticks

}



TEST_F(BenchmarkTest_912, PrepareCalculatesRunTimeWhenWarmupIsGreaterThanMeanTicks_912) {

    using namespace std::chrono_literals;

    EXPECT_CALL(mock_cfg, benchmarkWarmupTime()).WillOnce(Return(5s));



    auto plan = benchmark.prepare<std::chrono::high_resolution_clock>(mock_cfg, env);

    EXPECT_EQ(plan.run_time.count(), 5000); // run_time should be equal to warmup time in milliseconds

}
