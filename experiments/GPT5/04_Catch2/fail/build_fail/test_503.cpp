// File: tests/run_context_benchmarkEnded_503.tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// ---- Minimal, interface-only Catch2 includes (as provided) ----
#include "Catch2/src/catch2/benchmark/detail/catch_benchmark_stats.hpp"
#include "Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"
#include "Catch2/src/catch2/internal/catch_unique_ptr.hpp"
#include "Catch2/src/catch2/internal/catch_run_context.hpp"

using ::testing::StrictMock;
using ::testing::Truly;
using ::testing::_;
using ::testing::Invoke;

namespace Catch {

// Provide a tiny IConfig stub with just what RunContext's constructor needs.
// (Only observable requirement is that name() can be called.)
class StubConfig : public IConfig {
public:
    // Minimal API: Only what's needed by RunContext’s ctor.
    // If your environment has a full IConfig, drop this stub.
    std::string name() const { return "stub-run"; }
};

// Google Mock reporter that lets us assert forwarding behavior.
class MockEventListener : public IEventListener {
public:
    explicit MockEventListener(const IConfig* cfg) : IEventListener(cfg) {}
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>&), (override));

    // Keep the rest as inherited default virtuals; we do not use them here.
};

} // namespace Catch

// ---------- Test fixture ----------
class RunContext_BenchmarkEndedTest_503 : public ::testing::Test {
protected:
    Catch::StubConfig cfg_;
    // We keep a raw pointer to the mock for EXPECT_CALLs,
    // while RunContext owns it via Catch's unique_ptr.
    StrictMock<Catch::MockEventListener>* reporter_raw_ = nullptr;
    Catch::RunContext* ctx_ = nullptr; // will be created in SetUp
    std::unique_ptr<Catch::RunContext> ctx_holder_; // RAII guard in tests that need it

    // Helper to make a Catch::Detail::unique_ptr<IEventListener> from raw
    static Catch::Detail::unique_ptr<Catch::IEventListener>
    makeReporterPtr(StrictMock<Catch::MockEventListener>*& out, const Catch::IConfig* cfg) {
        auto* p = new StrictMock<Catch::MockEventListener>(cfg);
        out = p;
        return Catch::Detail::unique_ptr<Catch::IEventListener>(p);
    }

    void SetUp() override {
        // Construct RunContext with our mock reporter
        auto ptr = makeReporterPtr(reporter_raw_, &cfg_);
        ctx_holder_ = std::unique_ptr<Catch::RunContext>(
            new Catch::RunContext(&cfg_, std::move(ptr))
        );
        ctx_ = ctx_holder_.get();
    }
};

// ---------- Tests ----------

// [Normal] Forwards stats to reporter with the exact same reference.
TEST_F(RunContext_BenchmarkEndedTest_503, ForwardsStatsToReporter_503) {
    Catch::BenchmarkStats<> stats{};

    EXPECT_CALL(*reporter_raw_,
        benchmarkEnded(Truly([&](const Catch::BenchmarkStats<>& s) {
            // Must be the very same object by reference
            return &s == &stats;
        }))
    ).Times(1);

    ctx_->benchmarkEnded(stats);
}

// [Boundary] Accepts default-constructed stats and forwards as-is.
TEST_F(RunContext_BenchmarkEndedTest_503, AcceptsDefaultConstructedStats_503) {
    Catch::BenchmarkStats<> defaultStats{};

    EXPECT_CALL(*reporter_raw_,
        benchmarkEnded(Truly([&](const Catch::BenchmarkStats<>& s) {
            return &s == &defaultStats;
        }))
    ).Times(1);

    ctx_->benchmarkEnded(defaultStats);
}

// [Repeatability] Multiple calls are forwarded 1:1 with the correct reference each time.
TEST_F(RunContext_BenchmarkEndedTest_503, MultipleInvocationsAreForwarded_503) {
    Catch::BenchmarkStats<> a{};
    Catch::BenchmarkStats<> b{};

    {
        ::testing::InSequence seq; // enforce call order a then b

        EXPECT_CALL(*reporter_raw_,
            benchmarkEnded(Truly([&](const Catch::BenchmarkStats<>& s) {
                return &s == &a;
            }))
        ).Times(1);

        EXPECT_CALL(*reporter_raw_,
            benchmarkEnded(Truly([&](const Catch::BenchmarkStats<>& s) {
                return &s == &b;
            }))
        ).Times(1);
    }

    ctx_->benchmarkEnded(a);
    ctx_->benchmarkEnded(b);
}
