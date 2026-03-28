// File: benchmark_prepare_912_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <chrono>
#include <cmath>
#include <cstdint>
#include <functional>
#include <string>
#include <utility>

using ::testing::Return;

// ----------------------- Minimal public surface & test doubles -----------------------
// Namespace layout mirrors the partial code so we can compile the member function
// under test as-is, while treating its dependencies as external collaborators.

namespace Catch {
namespace Benchmark {

// Forward decls needed by the interface
using FDuration = std::chrono::duration<double>;
using IDuration = std::chrono::duration<double>;
using default_clock = std::chrono::steady_clock;

struct OutlierClassification {};

// From partial code
struct EnvironmentEstimate {
    FDuration mean{};
    OutlierClassification outliers{};
};

struct Environment {
    EnvironmentEstimate clock_resolution{};
    EnvironmentEstimate clock_cost{};
};

namespace Detail {
    // Global constants from partial code
    inline const int warmup_iterations = 10000;
    inline const int minimum_ticks = 1000;

    // "BenchmarkFunction" used by ExecutionPlan ctor in the snippet
    using BenchmarkFunction = std::function<void()>;

    // ---- Test seam for the external collaborator run_for_at_least ----
    template <typename Clock>
    struct RunResult {
        int iterations{};
        IDuration elapsed{};
    };

    // We capture the last duration passed in, so tests can verify what prepare()
    // asked for. We also provide controllable results via globals set by tests.
    inline IDuration g_last_requested_duration{};
    inline int g_run_iters = 0;
    inline IDuration g_run_elapsed{};

    template <typename Clock>
    RunResult<Clock> run_for_at_least(IDuration requested, int /*min_iters*/, BenchmarkFunction& /*fun*/) {
        g_last_requested_duration = requested;
        return { g_run_iters, g_run_elapsed };
    }

    // Utility trait used in the class template signature (minimal)
    template <typename A, typename B>
    struct is_related : std::false_type {};
} // namespace Detail

// --------------------- ExecutionPlan test double ---------------------
// We provide a ctor that matches the initializer used by the partial code.
// The fields are public so tests can *observe* the values computed by prepare().
struct ExecutionPlan {
    int new_iterations{};
    IDuration estimated_total{};
    Detail::BenchmarkFunction fun{};
    FDuration warmup{};
    int warmup_iters{};

    ExecutionPlan(int iters,
                  IDuration est,
                  Detail::BenchmarkFunction f,
                  FDuration w,
                  int warmup_iters_in)
        : new_iterations(iters)
        , estimated_total(est)
        , fun(std::move(f))
        , warmup(w)
        , warmup_iters(warmup_iters_in) {}
};

// --------------------- IConfig mock ---------------------
namespace Detail { struct NonCopyable { NonCopyable() = default; NonCopyable(const NonCopyable&) = delete; NonCopyable& operator=(const NonCopyable&) = delete; }; }

enum class ShowDurations { DefaultForReporter, Always, Never };
enum class TestRunOrder { Declared, LexicographicallySorted, Random };
enum class ColourMode { PlatformDefault, ANSI, None };
enum class Verbosity { Quiet, Normal, High };

class IConfig : public Detail::NonCopyable {
public:
    virtual ~IConfig() = default;
    // Only the two used by the code under test are behaviorally relevant.
    virtual unsigned int benchmarkSamples() const = 0;
    virtual std::chrono::milliseconds benchmarkWarmupTime() const = 0;

    // The rest are irrelevant for these tests; provide default stubs to satisfy vtable.
    virtual bool allowThrows() const { return true; }
    virtual const char* name() const { return ""; }
    virtual bool includeSuccessfulResults() const { return false; }
    virtual bool shouldDebugBreak() const { return false; }
    virtual bool warnAboutMissingAssertions() const { return false; }
    virtual bool warnAboutUnmatchedTestSpecs() const { return false; }
    virtual bool zeroTestsCountAsSuccess() const { return false; }
    virtual int abortAfter() const { return 0; }
    virtual bool showInvisibles() const { return false; }
    virtual ShowDurations showDurations() const { return ShowDurations::DefaultForReporter; }
    virtual double minDuration() const { return 0.0; }
    // Omitting other members from the partial header as they are unused.
};

// A simple gMock-derived config so we can set expectations on the two used methods.
class MockConfig : public IConfig {
public:
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

// --------------------- Class under test (public interface) ---------------------
namespace Benchmark {

class Benchmark {
    Catch::Benchmark::Detail::BenchmarkFunction fun;
    std::string name;

public:
    explicit Benchmark(std::string&& benchmarkName)
        : name(std::move(benchmarkName)) {}

    template <class FUN>
    Benchmark(std::string&& benchmarkName, FUN&& func)
        : fun(std::forward<FUN>(func)), name(std::move(benchmarkName)) {}

    template <typename Clock>
    ExecutionPlan prepare(const IConfig& cfg, Environment env) {
        auto min_time = env.clock_resolution.mean * Detail::minimum_ticks;
        auto run_time = std::max(min_time,
            std::chrono::duration_cast<decltype(min_time)>(cfg.benchmarkWarmupTime()));
        auto&& test = Detail::run_for_at_least<Clock>(
            std::chrono::duration_cast<IDuration>(run_time), 1, fun);
        int new_iters = static_cast<int>(std::ceil(min_time * test.iterations / test.elapsed));
        return {
            new_iters,
            test.elapsed / test.iterations * new_iters * cfg.benchmarkSamples(),
            std::move(fun),
            std::chrono::duration_cast<FDuration>(cfg.benchmarkWarmupTime()),
            Detail::warmup_iterations
        };
    }
};

} // namespace Benchmark
} // namespace Benchmark
} // namespace Catch

// -------------------------------------- Tests --------------------------------------

using Catch::Benchmark::Benchmark::Benchmark;
using Catch::Benchmark::Environment;
using Catch::Benchmark::EnvironmentEstimate;
using Catch::Benchmark::Detail::g_last_requested_duration;
using Catch::Benchmark::Detail::g_run_elapsed;
using Catch::Benchmark::Detail::g_run_iters;
using Catch::Benchmark::ExecutionPlan;
using Catch::Benchmark::FDuration;
using Catch::Benchmark::IDuration;

// Helper to compare chrono durations with a tolerance
template <typename DurA, typename DurB>
static ::testing::AssertionResult DurationNear(const DurA& a, const DurB& b, double eps_ratio = 1e-9) {
    const double ad = std::chrono::duration<double>(a).count();
    const double bd = std::chrono::duration<double>(b).count();
    const double diff = std::abs(ad - bd);
    const double scale = std::max(1.0, std::abs(bd));
    if (diff <= eps_ratio * scale) return ::testing::AssertionSuccess();
    return ::testing::AssertionFailure() << "durations differ: " << ad << " vs " << bd;
}

// Normal case: warmup < min_time, so min_time is used for run_for_at_least.
TEST(BenchmarkPrepareTest_912, UsesMinTimeWhenWarmupSmaller_912) {
    using Clock = Catch::Benchmark::default_clock;

    // Arrange
    MockConfig cfg;
    // env.clock_resolution.mean = 1 microsecond -> min_time = 1000 * 1us = 1ms
    Environment env;
    env.clock_resolution.mean = std::chrono::microseconds(1);

    EXPECT_CALL(cfg, benchmarkWarmupTime())
        .WillRepeatedly(Return(std::chrono::microseconds(100))); // 100us < 1ms
    EXPECT_CALL(cfg, benchmarkSamples())
        .WillRepeatedly(Return(3u));

    // Configure the collaborator's return
    g_run_iters = 5;
    g_run_elapsed = std::chrono::milliseconds(5); // elapsed across the 5 iterations

    int counter = 0;
    Benchmark bench{"bm", [&] { ++counter; }};

    // Act
    ExecutionPlan plan = bench.prepare<Clock>(cfg, env);

    // Assert
    // run_for_at_least should have been called with min_time = 1ms
    ASSERT_TRUE(DurationNear(g_last_requested_duration, std::chrono::milliseconds(1)));

    // new_iters = ceil( (1ms * 5) / 5ms ) = ceil(1/5) = 1
    EXPECT_EQ(plan.new_iterations, 1);

    // estimated_total = (5ms / 5) * 1 * samples(3) = 3ms
    ASSERT_TRUE(DurationNear(plan.estimated_total, std::chrono::milliseconds(3)));

    // warmup propagated from cfg (100us)
    ASSERT_TRUE(DurationNear(plan.warmup, FDuration(std::chrono::microseconds(100))));

    // warmup iterations constant
    EXPECT_EQ(plan.warmup_iters, Catch::Benchmark::Detail::warmup_iterations);

    // The returned function should be callable and still work
    EXPECT_EQ(counter, 0);
    ASSERT_TRUE(static_cast<bool>(plan.fun));
    plan.fun();
    EXPECT_EQ(counter, 1);
}

// Boundary: warmup >= min_time, so warmup is used for run_for_at_least.
TEST(BenchmarkPrepareTest_912, UsesWarmupWhenWarmupLarger_912) {
    using Clock = Catch::Benchmark::default_clock;

    // Arrange
    MockConfig cfg;

    // env.clock_resolution.mean = 2ms -> min_time = 2ms * 1000 = 2s
    Environment env;
    env.clock_resolution.mean = std::chrono::milliseconds(2);

    // warmup = 3s > min_time(2s)
    EXPECT_CALL(cfg, benchmarkWarmupTime())
        .WillRepeatedly(Return(std::chrono::seconds(3)));
    EXPECT_CALL(cfg, benchmarkSamples())
        .WillRepeatedly(Return(2u));

    // Collaborator returns: iterations=10, elapsed=5s
    g_run_iters = 10;
    g_run_elapsed = std::chrono::seconds(5);

    Benchmark bench{"bm2", [] {}};

    // Act
    ExecutionPlan plan = bench.prepare<Clock>(cfg, env);

    // Assert
    // run_for_at_least should have used warmup (3s)
    ASSERT_TRUE(DurationNear(g_last_requested_duration, std::chrono::seconds(3)));

    // new_iters = ceil( (min_time=2s * 10) / 5s ) = ceil(4) = 4
    EXPECT_EQ(plan.new_iterations, 4);

    // estimated_total = (5s / 10) * 4 * samples(2) = 0.5s * 8 = 4s
    ASSERT_TRUE(DurationNear(plan.estimated_total, std::chrono::seconds(4)));

    // warmup propagated as FDuration(3s)
    ASSERT_TRUE(DurationNear(plan.warmup, FDuration(std::chrono::seconds(3))));

    EXPECT_EQ(plan.warmup_iters, Catch::Benchmark::Detail::warmup_iterations);
}

// Interaction & propagation check: samples scaling and function persistence.
TEST(BenchmarkPrepareTest_912, ScalesBySamplesAndPreservesFunction_912) {
    using Clock = Catch::Benchmark::default_clock;

    MockConfig cfg;
    Environment env;
    // Choose mean so min_time is neat: mean = 500us -> min_time = 500ms
    env.clock_resolution.mean = std::chrono::microseconds(500); // 0.0005s * 1000 = 0.5s

    EXPECT_CALL(cfg, benchmarkWarmupTime())
        .WillRepeatedly(Return(std::chrono::milliseconds(100))); // < min_time -> use min_time
    EXPECT_CALL(cfg, benchmarkSamples())
        .WillRepeatedly(Return(7u)); // verify scaling

    // Collaborator timing
    g_run_iters = 8;
    g_run_elapsed = std::chrono::seconds(2); // 8 iters in 2s -> 0.25s/iter

    int calls = 0;
    Benchmark bench{"bm3", [&] { ++calls; }};

    ExecutionPlan plan = bench.prepare<Clock>(cfg, env);

    // run_for_at_least got min_time (0.5s)
    ASSERT_TRUE(DurationNear(g_last_requested_duration, std::chrono::milliseconds(500)));

    // new_iters = ceil( (0.5s * 8) / 2s ) = ceil(2) = 2
    EXPECT_EQ(plan.new_iterations, 2);

    // estimated_total = (2s / 8) * 2 * samples(7) = 0.25s * 14 = 3.5s
    ASSERT_TRUE(DurationNear(plan.estimated_total, std::chrono::duration<double>(3.5)));

    // Function callable
    EXPECT_EQ(calls, 0);
    plan.fun();
    plan.fun();
    EXPECT_EQ(calls, 2);
}
