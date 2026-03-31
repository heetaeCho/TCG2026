#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <chrono>
#include <string>

#include "catch_amalgamated.hpp"

using namespace Catch::Benchmark;
using namespace Catch::Benchmark::Detail;
using namespace std::chrono;

// Mock for IConfig
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

class BenchmarkPrepareTest_912 : public ::testing::Test {
protected:
    MockConfig mockConfig;

    Environment createEnvironment(FDuration clockResolutionMean, FDuration clockCostMean) {
        Environment env;
        env.clock_resolution.mean = clockResolutionMean;
        env.clock_resolution.outliers = {};
        env.clock_cost.mean = clockCostMean;
        env.clock_cost.outliers = {};
        return env;
    }
};

// Test that prepare returns an ExecutionPlan with positive iterations for typical config
TEST_F(BenchmarkPrepareTest_912, PrepareReturnsPositiveIterations_912) {
    using Clock = Catch::Benchmark::default_clock;

    ON_CALL(mockConfig, benchmarkWarmupTime())
        .WillByDefault(::testing::Return(std::chrono::milliseconds(100)));
    ON_CALL(mockConfig, benchmarkSamples())
        .WillByDefault(::testing::Return(100u));

    // clock_resolution.mean of 1 microsecond
    auto env = createEnvironment(
        FDuration(std::chrono::duration_cast<FDuration>(std::chrono::microseconds(1))),
        FDuration(std::chrono::duration_cast<FDuration>(std::chrono::microseconds(1)))
    );

    // Create a benchmark with a simple function
    Benchmark bench(std::string("test_bench"), [](Catch::Benchmark::Chronometer meter) {
        meter.measure([]{ return 1; });
    });

    auto plan = bench.prepare<Clock>(mockConfig, env);
    EXPECT_GT(plan.iterations, 0);
}

// Test that prepare uses warmup time from config
TEST_F(BenchmarkPrepareTest_912, PrepareUsesWarmupTimeFromConfig_912) {
    using Clock = Catch::Benchmark::default_clock;

    EXPECT_CALL(mockConfig, benchmarkWarmupTime())
        .WillRepeatedly(::testing::Return(std::chrono::milliseconds(200)));
    EXPECT_CALL(mockConfig, benchmarkSamples())
        .WillRepeatedly(::testing::Return(50u));

    auto env = createEnvironment(
        FDuration(std::chrono::duration_cast<FDuration>(std::chrono::microseconds(10))),
        FDuration(std::chrono::duration_cast<FDuration>(std::chrono::microseconds(5)))
    );

    Benchmark bench(std::string("warmup_test"), [](Catch::Benchmark::Chronometer meter) {
        meter.measure([]{ return 42; });
    });

    auto plan = bench.prepare<Clock>(mockConfig, env);
    // The warmup in the plan should match config's warmup time
    auto expectedWarmup = std::chrono::duration_cast<FDuration>(std::chrono::milliseconds(200));
    EXPECT_DOUBLE_EQ(plan.warmup_time.count(), expectedWarmup.count());
}

// Test that warmup_iterations in ExecutionPlan equals Detail::warmup_iterations
TEST_F(BenchmarkPrepareTest_912, PrepareUsesCorrectWarmupIterations_912) {
    using Clock = Catch::Benchmark::default_clock;

    ON_CALL(mockConfig, benchmarkWarmupTime())
        .WillByDefault(::testing::Return(std::chrono::milliseconds(100)));
    ON_CALL(mockConfig, benchmarkSamples())
        .WillByDefault(::testing::Return(100u));

    auto env = createEnvironment(
        FDuration(std::chrono::duration_cast<FDuration>(std::chrono::microseconds(1))),
        FDuration(std::chrono::duration_cast<FDuration>(std::chrono::microseconds(1)))
    );

    Benchmark bench(std::string("warmup_iter_test"), [](Catch::Benchmark::Chronometer meter) {
        meter.measure([]{ return 0; });
    });

    auto plan = bench.prepare<Clock>(mockConfig, env);
    EXPECT_EQ(plan.warmup_iterations, Detail::warmup_iterations);
    EXPECT_EQ(plan.warmup_iterations, 10000);
}

// Test that benchmarkSamples is called and affects estimated_duration
TEST_F(BenchmarkPrepareTest_912, PrepareCallsBenchmarkSamples_912) {
    using Clock = Catch::Benchmark::default_clock;

    EXPECT_CALL(mockConfig, benchmarkWarmupTime())
        .WillRepeatedly(::testing::Return(std::chrono::milliseconds(100)));
    EXPECT_CALL(mockConfig, benchmarkSamples())
        .Times(::testing::AtLeast(1))
        .WillRepeatedly(::testing::Return(200u));

    auto env = createEnvironment(
        FDuration(std::chrono::duration_cast<FDuration>(std::chrono::microseconds(1))),
        FDuration(std::chrono::duration_cast<FDuration>(std::chrono::microseconds(1)))
    );

    Benchmark bench(std::string("samples_test"), [](Catch::Benchmark::Chronometer meter) {
        meter.measure([]{ return 1; });
    });

    auto plan = bench.prepare<Clock>(mockConfig, env);
    // estimated_duration should be positive
    EXPECT_GT(plan.estimated_duration.count(), 0.0);
}

// Test with small warmup time - min_time should dominate
TEST_F(BenchmarkPrepareTest_912, PrepareWithSmallWarmupTime_912) {
    using Clock = Catch::Benchmark::default_clock;

    ON_CALL(mockConfig, benchmarkWarmupTime())
        .WillByDefault(::testing::Return(std::chrono::milliseconds(0)));
    ON_CALL(mockConfig, benchmarkSamples())
        .WillByDefault(::testing::Return(100u));

    // Large clock resolution mean so min_time = mean * 1000 is significant
    auto env = createEnvironment(
        FDuration(std::chrono::duration_cast<FDuration>(std::chrono::microseconds(100))),
        FDuration(std::chrono::duration_cast<FDuration>(std::chrono::microseconds(1)))
    );

    Benchmark bench(std::string("small_warmup_test"), [](Catch::Benchmark::Chronometer meter) {
        meter.measure([]{ return 1; });
    });

    auto plan = bench.prepare<Clock>(mockConfig, env);
    EXPECT_GT(plan.iterations, 0);
}

// Test with single sample
TEST_F(BenchmarkPrepareTest_912, PrepareWithSingleSample_912) {
    using Clock = Catch::Benchmark::default_clock;

    ON_CALL(mockConfig, benchmarkWarmupTime())
        .WillByDefault(::testing::Return(std::chrono::milliseconds(100)));
    ON_CALL(mockConfig, benchmarkSamples())
        .WillByDefault(::testing::Return(1u));

    auto env = createEnvironment(
        FDuration(std::chrono::duration_cast<FDuration>(std::chrono::microseconds(1))),
        FDuration(std::chrono::duration_cast<FDuration>(std::chrono::microseconds(1)))
    );

    Benchmark bench(std::string("single_sample_test"), [](Catch::Benchmark::Chronometer meter) {
        meter.measure([]{ return 1; });
    });

    auto plan = bench.prepare<Clock>(mockConfig, env);
    EXPECT_GT(plan.iterations, 0);
}

// Test that Benchmark is truthy when constructed with a function
TEST_F(BenchmarkPrepareTest_912, BenchmarkBoolOperatorTrueWhenFunctionSet_912) {
    Benchmark bench(std::string("bool_test"), [](Catch::Benchmark::Chronometer meter) {
        meter.measure([]{ return 1; });
    });

    EXPECT_TRUE(static_cast<bool>(bench));
}

// Test that Benchmark is falsy when constructed without a function
TEST_F(BenchmarkPrepareTest_912, BenchmarkBoolOperatorFalseWhenNoFunction_912) {
    Benchmark bench(std::string("empty_bench"));
    EXPECT_FALSE(static_cast<bool>(bench));
}

// Test assignment operator sets function
TEST_F(BenchmarkPrepareTest_912, BenchmarkAssignmentOperatorSetsFunction_912) {
    Benchmark bench(std::string("assign_test"));
    EXPECT_FALSE(static_cast<bool>(bench));

    bench = [](Catch::Benchmark::Chronometer meter) {
        meter.measure([]{ return 42; });
    };

    EXPECT_TRUE(static_cast<bool>(bench));
}

// Test with different sample counts produce different estimated durations
TEST_F(BenchmarkPrepareTest_912, DifferentSampleCountsProduceDifferentEstimatedDuration_912) {
    using Clock = Catch::Benchmark::default_clock;

    auto env = createEnvironment(
        FDuration(std::chrono::duration_cast<FDuration>(std::chrono::microseconds(1))),
        FDuration(std::chrono::duration_cast<FDuration>(std::chrono::microseconds(1)))
    );

    // First with 10 samples
    MockConfig config1;
    ON_CALL(config1, benchmarkWarmupTime())
        .WillByDefault(::testing::Return(std::chrono::milliseconds(100)));
    ON_CALL(config1, benchmarkSamples())
        .WillByDefault(::testing::Return(10u));

    Benchmark bench1(std::string("samples_10"), [](Catch::Benchmark::Chronometer meter) {
        meter.measure([]{ return 1; });
    });
    auto plan1 = bench1.prepare<Clock>(config1, env);

    // Then with 1000 samples
    MockConfig config2;
    ON_CALL(config2, benchmarkWarmupTime())
        .WillByDefault(::testing::Return(std::chrono::milliseconds(100)));
    ON_CALL(config2, benchmarkSamples())
        .WillByDefault(::testing::Return(1000u));

    Benchmark bench2(std::string("samples_1000"), [](Catch::Benchmark::Chronometer meter) {
        meter.measure([]{ return 1; });
    });
    auto plan2 = bench2.prepare<Clock>(config2, env);

    // More samples should produce a larger estimated duration (proportionally)
    // Since estimated_duration = (elapsed/iterations * new_iters * samples)
    // With same iterations but different samples, duration should scale
    EXPECT_GT(plan2.estimated_duration.count(), plan1.estimated_duration.count());
}

// Test minimum_ticks constant
TEST_F(BenchmarkPrepareTest_912, MinimumTicksValue_912) {
    EXPECT_EQ(Detail::minimum_ticks, 1000);
}

// Test warmup_iterations constant
TEST_F(BenchmarkPrepareTest_912, WarmupIterationsValue_912) {
    EXPECT_EQ(Detail::warmup_iterations, 10000);
}

// Test iterations are at least 1 (ceil guarantees at least 1)
TEST_F(BenchmarkPrepareTest_912, PrepareIterationsAtLeastOne_912) {
    using Clock = Catch::Benchmark::default_clock;

    ON_CALL(mockConfig, benchmarkWarmupTime())
        .WillByDefault(::testing::Return(std::chrono::milliseconds(100)));
    ON_CALL(mockConfig, benchmarkSamples())
        .WillByDefault(::testing::Return(100u));

    // Very small clock resolution
    auto env = createEnvironment(
        FDuration(std::chrono::duration_cast<FDuration>(std::chrono::nanoseconds(1))),
        FDuration(std::chrono::duration_cast<FDuration>(std::chrono::nanoseconds(1)))
    );

    Benchmark bench(std::string("min_iter_test"), [](Catch::Benchmark::Chronometer meter) {
        meter.measure([]{ return 1; });
    });

    auto plan = bench.prepare<Clock>(mockConfig, env);
    EXPECT_GE(plan.iterations, 1);
}
