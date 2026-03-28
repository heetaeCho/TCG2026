#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <chrono>
#include <vector>
#include <string>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Benchmark;
using namespace Catch::Benchmark::Detail;

// Mock IConfig
class MockConfig : public Catch::IConfig {
public:
    ~MockConfig() override = default;

    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(Catch::StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(const Catch::TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(Catch::TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

// Helper to create a default Environment with zero clock cost
Environment makeEnvironment(FDuration clockCostMean = FDuration::zero()) {
    Environment env;
    env.clock_resolution.mean = FDuration::zero();
    env.clock_resolution.outliers = OutlierClassification{};
    env.clock_cost.mean = clockCostMean;
    env.clock_cost.outliers = OutlierClassification{};
    return env;
}

class ExecutionPlanTest_906 : public ::testing::Test {
protected:
    MockConfig config;

    void SetUp() override {
        // Default config setup
        ON_CALL(config, benchmarkSamples()).WillByDefault(::testing::Return(10));
    }
};

// Test that run() returns the correct number of samples
TEST_F(ExecutionPlanTest_906, RunReturnsCorrectNumberOfSamples_906) {
    ExecutionPlan plan;
    plan.iterations_per_sample = 1;
    plan.estimated_duration = FDuration::zero();
    plan.warmup_time = FDuration::zero();
    plan.warmup_iterations = 1;
    plan.benchmark = BenchmarkFunction([](Chronometer) {});

    EXPECT_CALL(config, benchmarkSamples()).WillRepeatedly(::testing::Return(10));

    Environment env = makeEnvironment();
    auto results = plan.run<std::chrono::steady_clock>(config, env);

    EXPECT_EQ(results.size(), 10u);
}

// Test with 1 sample
TEST_F(ExecutionPlanTest_906, RunReturnsOneSample_906) {
    ExecutionPlan plan;
    plan.iterations_per_sample = 1;
    plan.estimated_duration = FDuration::zero();
    plan.warmup_time = FDuration::zero();
    plan.warmup_iterations = 1;
    plan.benchmark = BenchmarkFunction([](Chronometer) {});

    EXPECT_CALL(config, benchmarkSamples()).WillRepeatedly(::testing::Return(1));

    Environment env = makeEnvironment();
    auto results = plan.run<std::chrono::steady_clock>(config, env);

    EXPECT_EQ(results.size(), 1u);
}

// Test with 0 samples — edge case
TEST_F(ExecutionPlanTest_906, RunReturnsZeroSamplesWhenConfigured_906) {
    ExecutionPlan plan;
    plan.iterations_per_sample = 1;
    plan.estimated_duration = FDuration::zero();
    plan.warmup_time = FDuration::zero();
    plan.warmup_iterations = 1;
    plan.benchmark = BenchmarkFunction([](Chronometer) {});

    EXPECT_CALL(config, benchmarkSamples()).WillRepeatedly(::testing::Return(0));

    Environment env = makeEnvironment();
    auto results = plan.run<std::chrono::steady_clock>(config, env);

    EXPECT_EQ(results.size(), 0u);
}

// Test that all returned durations are non-negative
TEST_F(ExecutionPlanTest_906, AllSamplesAreNonNegative_906) {
    ExecutionPlan plan;
    plan.iterations_per_sample = 1;
    plan.estimated_duration = FDuration::zero();
    plan.warmup_time = FDuration::zero();
    plan.warmup_iterations = 1;
    plan.benchmark = BenchmarkFunction([](Chronometer) {});

    EXPECT_CALL(config, benchmarkSamples()).WillRepeatedly(::testing::Return(20));

    // Set a very high clock cost to force negative sample times to be clamped to zero
    Environment env = makeEnvironment(FDuration(1000.0));
    auto results = plan.run<std::chrono::steady_clock>(config, env);

    for (const auto& t : results) {
        EXPECT_GE(t.count(), 0.0);
    }
}

// Test that large clock cost results in zero durations (clamping behavior)
TEST_F(ExecutionPlanTest_906, LargeClockCostClampsSamplesToZero_906) {
    ExecutionPlan plan;
    plan.iterations_per_sample = 1;
    plan.estimated_duration = FDuration::zero();
    plan.warmup_time = FDuration::zero();
    plan.warmup_iterations = 1;
    // A trivial benchmark that does nothing
    plan.benchmark = BenchmarkFunction([](Chronometer) {});

    EXPECT_CALL(config, benchmarkSamples()).WillRepeatedly(::testing::Return(5));

    // Very large clock cost should make (elapsed - clock_cost) negative, clamped to 0
    Environment env = makeEnvironment(FDuration(999999.0));
    auto results = plan.run<std::chrono::steady_clock>(config, env);

    EXPECT_EQ(results.size(), 5u);
    for (const auto& t : results) {
        EXPECT_DOUBLE_EQ(t.count(), 0.0);
    }
}

// Test with zero clock cost mean
TEST_F(ExecutionPlanTest_906, ZeroClockCostProducesValidResults_906) {
    ExecutionPlan plan;
    plan.iterations_per_sample = 1;
    plan.estimated_duration = FDuration::zero();
    plan.warmup_time = FDuration::zero();
    plan.warmup_iterations = 1;
    plan.benchmark = BenchmarkFunction([](Chronometer) {});

    EXPECT_CALL(config, benchmarkSamples()).WillRepeatedly(::testing::Return(5));

    Environment env = makeEnvironment(FDuration::zero());
    auto results = plan.run<std::chrono::steady_clock>(config, env);

    EXPECT_EQ(results.size(), 5u);
    for (const auto& t : results) {
        EXPECT_GE(t.count(), 0.0);
    }
}

// Test with multiple iterations per sample
TEST_F(ExecutionPlanTest_906, MultipleIterationsPerSampleDividesDuration_906) {
    ExecutionPlan plan;
    plan.iterations_per_sample = 100;
    plan.estimated_duration = FDuration::zero();
    plan.warmup_time = FDuration::zero();
    plan.warmup_iterations = 1;
    plan.benchmark = BenchmarkFunction([](Chronometer) {});

    EXPECT_CALL(config, benchmarkSamples()).WillRepeatedly(::testing::Return(5));

    Environment env = makeEnvironment(FDuration::zero());
    auto results = plan.run<std::chrono::steady_clock>(config, env);

    EXPECT_EQ(results.size(), 5u);
    for (const auto& t : results) {
        EXPECT_GE(t.count(), 0.0);
    }
}

// Test that the benchmark function is actually called during run
TEST_F(ExecutionPlanTest_906, BenchmarkFunctionIsInvoked_906) {
    int callCount = 0;
    ExecutionPlan plan;
    plan.iterations_per_sample = 1;
    plan.estimated_duration = FDuration::zero();
    plan.warmup_time = FDuration::zero();
    plan.warmup_iterations = 1;
    plan.benchmark = BenchmarkFunction([&callCount](Chronometer) {
        ++callCount;
    });

    EXPECT_CALL(config, benchmarkSamples()).WillRepeatedly(::testing::Return(3));

    Environment env = makeEnvironment();
    auto results = plan.run<std::chrono::steady_clock>(config, env);

    // The benchmark function should be called once per sample
    EXPECT_EQ(callCount, 3);
    EXPECT_EQ(results.size(), 3u);
}

// Test with large number of samples
TEST_F(ExecutionPlanTest_906, LargeNumberOfSamples_906) {
    ExecutionPlan plan;
    plan.iterations_per_sample = 1;
    plan.estimated_duration = FDuration::zero();
    plan.warmup_time = FDuration::zero();
    plan.warmup_iterations = 1;
    plan.benchmark = BenchmarkFunction([](Chronometer) {});

    EXPECT_CALL(config, benchmarkSamples()).WillRepeatedly(::testing::Return(1000));

    Environment env = makeEnvironment();
    auto results = plan.run<std::chrono::steady_clock>(config, env);

    EXPECT_EQ(results.size(), 1000u);
}

// Test with non-zero warmup time and iterations
TEST_F(ExecutionPlanTest_906, NonZeroWarmupProducesValidResults_906) {
    ExecutionPlan plan;
    plan.iterations_per_sample = 1;
    plan.estimated_duration = FDuration(1.0);
    plan.warmup_time = FDuration(0.001); // 1ms warmup
    plan.warmup_iterations = 10;
    plan.benchmark = BenchmarkFunction([](Chronometer) {});

    EXPECT_CALL(config, benchmarkSamples()).WillRepeatedly(::testing::Return(5));

    Environment env = makeEnvironment();
    auto results = plan.run<std::chrono::steady_clock>(config, env);

    EXPECT_EQ(results.size(), 5u);
    for (const auto& t : results) {
        EXPECT_GE(t.count(), 0.0);
    }
}

// Test default constructed ExecutionPlan members
TEST_F(ExecutionPlanTest_906, DefaultConstructedPlanFields_906) {
    ExecutionPlan plan;
    // Default BenchmarkFunction should be a do_nothing, which means run should work
    plan.iterations_per_sample = 1;
    plan.warmup_time = FDuration::zero();
    plan.warmup_iterations = 1;

    EXPECT_CALL(config, benchmarkSamples()).WillRepeatedly(::testing::Return(2));

    Environment env = makeEnvironment();
    auto results = plan.run<std::chrono::steady_clock>(config, env);

    EXPECT_EQ(results.size(), 2u);
}

// Test that with iterations_per_sample > 1, times are divided
TEST_F(ExecutionPlanTest_906, TimeDividedByIterationsPerSample_906) {
    ExecutionPlan plan;
    plan.iterations_per_sample = 10;
    plan.estimated_duration = FDuration::zero();
    plan.warmup_time = FDuration::zero();
    plan.warmup_iterations = 1;

    // A benchmark that does a tiny bit of work
    plan.benchmark = BenchmarkFunction([](Chronometer meter) {
        meter.measure([]() { volatile int x = 0; (void)x; });
    });

    EXPECT_CALL(config, benchmarkSamples()).WillRepeatedly(::testing::Return(5));

    Environment env = makeEnvironment();
    auto results = plan.run<std::chrono::steady_clock>(config, env);

    EXPECT_EQ(results.size(), 5u);
    // Each result should be non-negative (sample_time / iterations_per_sample)
    for (const auto& t : results) {
        EXPECT_GE(t.count(), 0.0);
    }
}
