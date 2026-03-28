// File: tests/ExecutionPlan_run_906.tests.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Benchmark;

// Simple helper to make an Environment with a specific clock-cost mean.
static Environment makeEnvWithClockCostMean(Catch::Benchmark::FDuration mean) {
    Environment env{};
    env.clock_cost.mean = mean;
    // The rest of Environment fields are irrelevant to the observable behavior we test.
    return env;
}

// Minimal concrete IConfig for tests: we only rely on benchmarkSamples() in the SUT,
// but we must implement the interface to pass a reference into ExecutionPlan::run.
// All other methods provide harmless defaults.
struct StubConfig : Catch::IConfig {
    explicit StubConfig(unsigned int samples) : samples_(samples) {}

    // ---- Methods actually used by SUT under test ----
    unsigned int benchmarkSamples() const override { return samples_; }

    // ---- Everything below is stubbed to safe defaults (unused here) ----
    bool allowThrows() const override { return true; }
    Catch::StringRef name() const override { static const std::string n = "stub"; return Catch::StringRef(n); }
    bool includeSuccessfulResults() const override { return false; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return true; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    Catch::ShowDurations showDurations() const override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() const override { return 0.0; }
    const Catch::TestSpec& testSpec() const override { static Catch::TestSpec s; return s; }
    bool hasTestFilters() const override { return false; }
    const std::vector<std::string>& getTestsOrTags() const override { static std::vector<std::string> v; return v; }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0; }
    unsigned int shardCount() const override { return 1; }
    unsigned int shardIndex() const override { return 0; }
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::PlatformDefault; }
    const std::vector<std::string>& getSectionsToRun() const override { static std::vector<std::string> v; return v; }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
    bool skipBenchmarks() const override { return false; }
    bool benchmarkNoAnalysis() const override { return false; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 0; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }

private:
    unsigned int samples_;
};

// Test fixture (keeps naming consistent with requested pattern)
class ExecutionPlanRunTest_906 : public ::testing::Test {
protected:
    using Clock = std::chrono::steady_clock; // Any std::steady clock works for black-box timing
};

// --- Tests ---

// Ensures run() returns exactly benchmarkSamples() results.
TEST_F(ExecutionPlanRunTest_906, ReturnsRequestedNumberOfSamples_906) {
    const unsigned int S = 3;
    StubConfig cfg{S};

    // Count invocations of the benchmark functor (external interaction verification)
    int callCount = 0;
    ExecutionPlan plan{};
    plan.iterations_per_sample = 1;
    plan.warmup_time = Catch::Benchmark::FDuration::zero();
    plan.warmup_iterations = 0;
    plan.benchmark = Detail::BenchmarkFunction([&](Catch::Benchmark::Chronometer) {
        ++callCount; // observable side effect for verification
    });

    auto env = makeEnvWithClockCostMean(Catch::Benchmark::FDuration::zero());
    auto times = plan.run<Clock>(cfg, env);

    EXPECT_EQ(times.size(), S);
    EXPECT_EQ(callCount, static_cast<int>(S)); // called once per sample
}

// Boundary: benchmarkSamples()==0 -> returns empty vector and does not call the functor.
TEST_F(ExecutionPlanRunTest_906, ZeroSamplesReturnsEmptyAndNoCalls_906) {
    const unsigned int S = 0;
    StubConfig cfg{S};

    int callCount = 0;
    ExecutionPlan plan{};
    plan.iterations_per_sample = 1;
    plan.warmup_time = Catch::Benchmark::FDuration::zero();
    plan.warmup_iterations = 0;
    plan.benchmark = Detail::BenchmarkFunction([&](Catch::Benchmark::Chronometer) {
        ++callCount;
    });

    auto env = makeEnvWithClockCostMean(Catch::Benchmark::FDuration::zero());
    auto times = plan.run<Clock>(cfg, env);

    EXPECT_TRUE(times.empty());
    EXPECT_EQ(callCount, 0);
}

// Error/edge handling that is observable: if (elapsed - clock_cost.mean) < 0, it's clamped to 0.
// We force it by setting a very large positive clock_cost.mean so the sample becomes negative.
TEST_F(ExecutionPlanRunTest_906, NegativeSampleTimeIsClampedToZero_906) {
    const unsigned int S = 4;
    StubConfig cfg{S};

    ExecutionPlan plan{};
    plan.iterations_per_sample = 1; // division by 1 makes clamping check straightforward
    plan.warmup_time = Catch::Benchmark::FDuration::zero();
    plan.warmup_iterations = 0;
    plan.benchmark = Detail::BenchmarkFunction(
        [](Catch::Benchmark::Chronometer) {
            // Black-box: do nothing; elapsed should be small compared to a huge mean
        }
    );

    // Make mean enormous so (elapsed - mean) is definitely negative
    auto hugeMean = std::chrono::hours(1);
    auto env = makeEnvWithClockCostMean(std::chrono::duration_cast<Catch::Benchmark::FDuration>(hugeMean));

    auto times = plan.run<Clock>(cfg, env);

    ASSERT_EQ(times.size(), S);
    for (const auto& t : times) {
        EXPECT_EQ(t, Catch::Benchmark::FDuration::zero());
    }
}

// Normal flow sanity: with a negative clock_cost.mean, the adjusted sample time should be > 0
// (since sample_time = elapsed - mean = elapsed + |mean|). We do NOT assert exact values,
// only observable positivity and vector size.
TEST_F(ExecutionPlanRunTest_906, PositiveAdjustedTimesWhenClockCostIsNegative_906) {
    const unsigned int S = 2;
    StubConfig cfg{S};

    ExecutionPlan plan{};
    plan.iterations_per_sample = 1;
    plan.warmup_time = Catch::Benchmark::FDuration::zero();
    plan.warmup_iterations = 0;
    plan.benchmark = Detail::BenchmarkFunction(
        [](Catch::Benchmark::Chronometer) {
            // Black-box: we do not assume anything about how the meter is used
        }
    );

    // Negative mean (e.g., -1s) should bias adjusted time upward, making it > 0
    auto negativeMean = -std::chrono::seconds(1);
    auto env = makeEnvWithClockCostMean(std::chrono::duration_cast<Catch::Benchmark::FDuration>(negativeMean));

    auto times = plan.run<Clock>(cfg, env);

    ASSERT_EQ(times.size(), S);
    for (const auto& t : times) {
        EXPECT_GT(t, Catch::Benchmark::FDuration::zero());
    }
}

// Sanity: if iterations_per_sample > 0, outputs are non-negative (post-clamp) and the
// benchmark functor still runs exactly once per sample.
TEST_F(ExecutionPlanRunTest_906, InvokesBenchmarkOncePerSampleAndNonNegativeOutputs_906) {
    const unsigned int S = 5;
    StubConfig cfg{S};

    int calls = 0;
    ExecutionPlan plan{};
    plan.iterations_per_sample = 7; // arbitrary positive boundary
    plan.warmup_time = Catch::Benchmark::FDuration::zero();
    plan.warmup_iterations = 0;
    plan.benchmark = Detail::BenchmarkFunction(
        [&](Catch::Benchmark::Chronometer) { ++calls; }
    );

    auto env = makeEnvWithClockCostMean(Catch::Benchmark::FDuration::zero());
    auto times = plan.run<Clock>(cfg, env);

    ASSERT_EQ(times.size(), S);
    EXPECT_EQ(calls, static_cast<int>(S));
    for (const auto& t : times) {
        EXPECT_GE(t, Catch::Benchmark::FDuration::zero());
    }
}
