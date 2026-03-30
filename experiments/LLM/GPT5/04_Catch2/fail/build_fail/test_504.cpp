// File: run_context_benchmarkFailed_tests_504.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Catch2/src/catch2/internal/catch_run_context.hpp"
#include "Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"
#include "Catch2/src/catch2/internal/catch_stringref.hpp"
#include "Catch2/src/catch2/internal/catch_unique_ptr.hpp"

// If your project exposes IConfig via a different header, include it here.
// The RunContext ctor only needs a config object so it can read name().

using ::testing::_;
using ::testing::Invoke;

namespace Catch {

// ---- Minimal config stub (observable need: name()) ----
// This stays strictly at the interface boundary and does *not*
// attempt to simulate internal config behavior.
class ConfigStub : public IConfig {
public:
    explicit ConfigStub(std::string nm = "run-name") : nm_(std::move(nm)) {}

    // --- IConfig API surface: only what is necessary to link in your setup.
    // If your environment requires more pure-virtual overrides, add trivial
    // implementations here (returning default values). We avoid testing any
    // of these; they are only here so RunContext can be constructed.

    // Name used by RunContext’s constructor
    StringRef name() const override { return nm_; }

    // The rest of IConfig’s API varies by Catch2 version. If your build
    // requires more overrides, add no-op implementations as needed.

private:
    std::string nm_;
};

// ---- Mock reporter: we verify external interaction only ----
class MockEventListener : public IEventListener {
public:
    explicit MockEventListener(IConfig const* cfg) : IEventListener(cfg) {}

    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
};

} // namespace Catch

// ---------- Tests ----------
class RunContextBenchmarkFailedTest_504 : public ::testing::Test {
protected:
    void SetUp() override {
        // Construct a config stub with any name
        config_ = std::make_unique<Catch::ConfigStub>("demo-run-504");
    }

    // Helper to build a RunContext with a mock reporter and return
    // the raw reporter pointer (for EXPECT_CALL) alongside the context.
    struct CtxWithReporter {
        std::unique_ptr<Catch::RunContext> ctx;
        Catch::MockEventListener* reporterRaw; // owned by ctx
    };

    CtxWithReporter makeContext() {
        auto* mock = new Catch::MockEventListener(config_.get());
        Catch::Detail::unique_ptr<Catch::IEventListener> repPtr(mock); // transfers ownership
        CtxWithReporter out;
        out.reporterRaw = mock;
        out.ctx = std::make_unique<Catch::RunContext>(config_.get(), std::move(repPtr));
        return out;
    }

    std::unique_ptr<Catch::ConfigStub> config_;
};

// [Normal] Calls reporter with same error string
TEST_F(RunContextBenchmarkFailedTest_504, CallsReporterWithSameError_504) {
    auto setup = makeContext();

    const char* msg = "benchmark exploded";
    // Verify exact value passed through to the reporter
    EXPECT_CALL(*setup.reporterRaw, benchmarkFailed(_))
        .WillOnce(Invoke([&](Catch::StringRef s) {
            std::string got = static_cast<std::string>(s);
            EXPECT_EQ(got, msg);
        }));

    setup.ctx->benchmarkFailed(Catch::StringRef(msg));
}

// [Boundary] Handles empty error StringRef (still forwards call)
TEST_F(RunContextBenchmarkFailedTest_504, ForwardsEmptyErrorString_504) {
    auto setup = makeContext();

    EXPECT_CALL(*setup.reporterRaw, benchmarkFailed(_))
        .WillOnce(Invoke([&](Catch::StringRef s) {
            EXPECT_TRUE(s.empty());
            EXPECT_EQ(s.size(), 0u);
            EXPECT_EQ(static_cast<std::string>(s), "");
        }));

    // Default-constructed StringRef is empty per interface
    Catch::StringRef empty;
    setup.ctx->benchmarkFailed(empty);
}
