// File: tests/Reporter_Multi_benchmarkEnded_793.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/benchmark/detail/catch_benchmark_stats.hpp"

#include <stdexcept>

using ::testing::_;
using ::testing::Ref;
using ::testing::InSequence;

namespace Catch {

// Minimal mock of IEventListener that exposes only the method we observe here.
class MockListener_793 : public IEventListener {
public:
    // Pass nullptr config — tests never use it; we only observe calls.
    MockListener_793() : IEventListener(nullptr) {}

    MOCK_METHOD(void, benchmarkEnded,
                (BenchmarkStats<> const&),
                (override));
};

} // namespace Catch

// Helper to create a listener/report mock wrapped in the correct pointer type.
static Catch::IEventListenerPtr MakePtr_793(Catch::MockListener_793* p) {
    return Catch::IEventListenerPtr(p); // Catch::Detail::unique_ptr<IEventListener>
}

// -------------------------------------------------------------------------------------------------
// Normal operation: forwards to all added listeners/reporters
// -------------------------------------------------------------------------------------------------
TEST(MultiReporter_BenchmarkEndedTest_793, ForwardsToAllAdded_793) {
    Catch::MultiReporter mr(/*config*/nullptr);

    auto* r1_raw = new Catch::MockListener_793();
    auto* r2_raw = new Catch::MockListener_793();

    // Add as a "reporter" and a "listener" to ensure both kinds are invoked.
    mr.addReporter(MakePtr_793(r1_raw));
    mr.addListener(MakePtr_793(r2_raw));

    Catch::BenchmarkStats<> stats{}; // Only passed by const&, we don't inspect internals.

    EXPECT_CALL(*r1_raw, benchmarkEnded(Ref(stats))).Times(1);
    EXPECT_CALL(*r2_raw, benchmarkEnded(Ref(stats))).Times(1);

    mr.benchmarkEnded(stats);
}

// -------------------------------------------------------------------------------------------------
// Boundary: no listeners/reporters added — should be a no-op (no throw)
// -------------------------------------------------------------------------------------------------
TEST(MultiReporter_BenchmarkEndedTest_793, NoObservers_NoThrow_793) {
    Catch::MultiReporter mr(/*config*/nullptr);
    Catch::BenchmarkStats<> stats{};
    EXPECT_NO_THROW(mr.benchmarkEnded(stats));
}

// -------------------------------------------------------------------------------------------------
// Ordering: calls happen in insertion order across listener/reporters
// -------------------------------------------------------------------------------------------------
TEST(MultiReporter_BenchmarkEndedTest_793, CallsInInsertionOrder_793) {
    Catch::MultiReporter mr(/*config*/nullptr);

    auto* first  = new Catch::MockListener_793();
    auto* second = new Catch::MockListener_793();
    auto* third  = new Catch::MockListener_793();

    // Intentionally mix addListener / addReporter to ensure both contribute to ordering.
    mr.addListener(MakePtr_793(first));   // 1st
    mr.addReporter(MakePtr_793(second));  // 2nd
    mr.addReporter(MakePtr_793(third));   // 3rd

    Catch::BenchmarkStats<> stats{};

    // Verify global order across different mocks.
    InSequence seq;
    EXPECT_CALL(*first,  benchmarkEnded(Ref(stats))).Times(1);
    EXPECT_CALL(*second, benchmarkEnded(Ref(stats))).Times(1);
    EXPECT_CALL(*third,  benchmarkEnded(Ref(stats))).Times(1);

    mr.benchmarkEnded(stats);
}

// -------------------------------------------------------------------------------------------------
// Exceptional case: if a collaborator throws, the exception is observable (propagates)
// (We do not assert anything about subsequent calls; just the observable propagation.)
// -------------------------------------------------------------------------------------------------
TEST(MultiReporter_BenchmarkEndedTest_793, PropagatesExceptionFromChild_793) {
    Catch::MultiReporter mr(/*config*/nullptr);

    auto* throwing = new Catch::MockListener_793();
    mr.addReporter(MakePtr_793(throwing));

    Catch::BenchmarkStats<> stats{};

    EXPECT_CALL(*throwing, benchmarkEnded(_))
        .WillOnce(::testing::Invoke([](auto const&) {
            throw std::runtime_error("boom");
        }));

    EXPECT_THROW(mr.benchmarkEnded(stats), std::runtime_error);
}
