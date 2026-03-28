// File: tests/run_context_benchmarkStarting_502_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/benchmark/detail/catch_benchmark_stats.hpp"

using ::testing::StrictMock;
using ::testing::Truly;

namespace Catch {

// ---- Minimal test doubles ----

// Minimal Config stub: only what's needed by RunContext's ctor (name()).
class DummyConfig_502 : public IConfig {
public:
    // In Catch2, name() is const and returns std::string
    std::string name() const override { return "DummyConfig_502"; }

    // If your IConfig in this environment has more pure virtuals,
    // provide trivial overrides or use your project's existing test stub.
    // The rest of IConfig's virtuals are assumed to have defaults in your tree.
};

// Reporter mock that only observes benchmarkStarting.
// Other IEventListener virtuals keep their default base implementations.
class MockEventListener_502 : public IEventListener {
public:
    MockEventListener_502() : IEventListener(nullptr) {}
    ~MockEventListener_502() override = default;

    MOCK_METHOD(void, benchmarkStarting, (BenchmarkInfo const&), (override));
};

} // namespace Catch

namespace {

class RunContextTest_502 : public ::testing::Test {
protected:
    Catch::DummyConfig_502 cfg_;
};

// Helper to build BenchmarkInfo with explicit fields
static Catch::BenchmarkInfo makeBI(double estimatedDuration,
                                   int iterations,
                                   unsigned int samples,
                                   unsigned int resamples,
                                   double clockResolution,
                                   double clockCost) {
    Catch::BenchmarkInfo bi{};
    bi.estimatedDuration = estimatedDuration;
    bi.iterations        = iterations;
    bi.samples           = samples;
    bi.resamples         = resamples;
    bi.clockResolution   = clockResolution;
    bi.clockCost         = clockCost;
    return bi;
}

// --- Tests ---

TEST_F(RunContextTest_502, ForwardsToReporter_502) {
    using namespace Catch;

    // Arrange
    auto* mock_raw = new StrictMock<MockEventListener_502>();
    IEventListenerPtr reporter(mock_raw); // take ownership
    RunContext ctx(&cfg_, std::move(reporter));

    const BenchmarkInfo expected = makeBI(0.123, 42, 7u, 3u, 1e-6, 2e-6);

    // Expect the reporter to receive the exact values we pass in
    EXPECT_CALL(*mock_raw, benchmarkStarting(Truly([&](const BenchmarkInfo& bi) {
        return bi.estimatedDuration == expected.estimatedDuration &&
               bi.iterations        == expected.iterations &&
               bi.samples           == expected.samples &&
               bi.resamples         == expected.resamples &&
               bi.clockResolution   == expected.clockResolution &&
               bi.clockCost         == expected.clockCost;
    })));

    // Act
    ctx.benchmarkStarting(expected);

    // Assert: handled by the EXPECT_CALL above
}

TEST_F(RunContextTest_502, ForwardsBoundaryValues_ZeroesAndMax_502) {
    using namespace Catch;

    auto* mock_raw = new StrictMock<MockEventListener_502>();
    IEventListenerPtr reporter(mock_raw);
    RunContext ctx(&cfg_, std::move(reporter));

    const BenchmarkInfo boundary = makeBI(
        0.0,                                  // estimatedDuration
        0,                                    // iterations
        std::numeric_limits<unsigned int>::max(), // samples
        0u,                                   // resamples
        0.0,                                  // clockResolution
        std::numeric_limits<double>::max()    // clockCost
    );

    EXPECT_CALL(*mock_raw, benchmarkStarting(Truly([&](const BenchmarkInfo& bi) {
        return bi.estimatedDuration == boundary.estimatedDuration &&
               bi.iterations        == boundary.iterations &&
               bi.samples           == boundary.samples &&
               bi.resamples         == boundary.resamples &&
               bi.clockResolution   == boundary.clockResolution &&
               bi.clockCost         == boundary.clockCost;
    })));

    ctx.benchmarkStarting(boundary);
}

TEST_F(RunContextTest_502, MultipleConsecutiveCalls_AreIndependentlyForwarded_502) {
    using namespace Catch;

    auto* mock_raw = new StrictMock<MockEventListener_502>();
    IEventListenerPtr reporter(mock_raw);
    RunContext ctx(&cfg_, std::move(reporter));

    const BenchmarkInfo first  = makeBI(1.0, 10, 5u, 2u, 1e-6, 1e-6);
    const BenchmarkInfo second = makeBI(2.5, 20, 8u, 4u, 2e-6, 3e-6);

    // Expect both calls with their respective payloads
    EXPECT_CALL(*mock_raw, benchmarkStarting(Truly([&](const BenchmarkInfo& bi) {
        return bi.estimatedDuration == first.estimatedDuration &&
               bi.iterations        == first.iterations &&
               bi.samples           == first.samples &&
               bi.resamples         == first.resamples &&
               bi.clockResolution   == first.clockResolution &&
               bi.clockCost         == first.clockCost;
    })));

    EXPECT_CALL(*mock_raw, benchmarkStarting(Truly([&](const BenchmarkInfo& bi) {
        return bi.estimatedDuration == second.estimatedDuration &&
               bi.iterations        == second.iterations &&
               bi.samples           == second.samples &&
               bi.resamples         == second.resamples &&
               bi.clockResolution   == second.clockResolution &&
               bi.clockCost         == second.clockCost;
    })));

    ctx.benchmarkStarting(first);
    ctx.benchmarkStarting(second);
}

} // namespace
