// TEST_ID: 861

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the real headers from your project.
// If your include paths differ, adjust accordingly.
#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

// If your project uses other headers for ReporterConfig / IConfig / ColourMode, include them here:
// #include "catch2/reporters/catch_reporter_helpers.hpp"
// #include "catch2/internal/catch_config.hpp"
// #include "catch2/internal/catch_stream.hpp"
// etc.

using ::testing::HasSubstr;

namespace {

// --- Minimal helpers for constructing inputs ---
// These types are referenced by TestRunStats. If your project already provides
// them (very likely), rely on the real ones and remove these placeholders.
struct DummyRunInfo : Catch::TestRunInfo {
    // If Catch2 already has a public default-constructible TestRunInfo, prefer that.
    // This is a harmless stand-in if your build needs it.
    using Catch::TestRunInfo::TestRunInfo;
};
struct DummyTotals : Catch::Totals {
    using Catch::Totals::Totals;
};

// A tiny helper that creates a TestRunStats value for our calls.
// Prefer constructing with your project's real TestRunInfo/Totals.
inline Catch::TestRunStats MakeStats(bool aborting = false) {
    DummyRunInfo runInfo{/* name = */ "run" };
    DummyTotals totals{};
    return Catch::TestRunStats(runInfo, totals, aborting);
}

// --- Test double: records calls to the virtual hook ---
class RecordingCumulativeReporter : public Catch::CumulativeReporterBase {
public:
    // Forwarding constructor to base. Adjust construction if your project’s
    // ReporterConfig has a different signature.
    explicit RecordingCumulativeReporter(Catch::ReporterConfig&& cfg)
        : Catch::CumulativeReporterBase(std::move(cfg)) {}

    // Expose a query for the observable interaction: the hook being called.
    int callsToHook() const noexcept { return hookCalls_; }

protected:
    void testRunEndedCumulative() override {
        ++hookCalls_;
    }

private:
    int hookCalls_{0};
};

// Helper to build a ReporterConfig. Adjust this to match your project.
// Many Catch2 setups allow constructing ReporterConfig with (IConfig const&, ColourMode, std::ostream&).
// If your signature differs, update the body accordingly.
static Catch::ReporterConfig MakeReporterConfig(std::ostream& out) {
    // NOTE: If your project requires an actual IConfig instance, provide a lightweight
    // test config (real or stub) the same way you do in your other reporter tests.
    // The following line assumes your environment provides a way to obtain a default config.
    // Replace `Catch::Detail::makeReporterConfigForTesting(out)` with your real constructor.
    //
    // Example patterns you might already use elsewhere:
    //   Catch::ColourMode colour = Catch::ColourMode::None;
    //   auto cfg = Catch::ReporterConfig{*someIConfigPtr, colour, out};
    //
    // For this template code, we simply forward to a plausible constructor.
    // Please adjust to your actual ReporterConfig constructor.
    using Catch::ReporterConfig;
    using Catch::ColourMode;

    // You will likely have an IConfig in your test harness; if not, create or fetch one.
    // Here we assume a trivial way to get it; replace as needed.
    struct TrivialConfig : Catch::IConfig {
        // Implement only what ReporterConfig queries in your environment.
        // If nothing is queried during testRunEnded, this can be very minimal.
        bool allowThrows() const override { return true; }
        std::ostream& stream() const override {
            // Not used here because ReporterConfig takes an explicit stream;
            // provide a safe dummy to satisfy interface if needed.
            return std::cout;
        }
        // Return reasonable defaults for any other pure-virtuals you have.
        // Add overrides here if your build complains.
    } static trivialCfg;

    // If your ReporterConfig ctor takes (IConfig const*, ColourMode, std::ostream&):
    return ReporterConfig(&trivialCfg, ColourMode::None, out);
}

} // namespace

// ---------- Tests ----------

class CumulativeReporterBase_Test_861 : public ::testing::Test {
protected:
    std::ostringstream out_;
};

// Normal operation: single call triggers the virtual hook exactly once.
TEST_F(CumulativeReporterBase_Test_861, CallsVirtualHook_Once_861) {
    auto cfg = MakeReporterConfig(out_);
    RecordingCumulativeReporter reporter(std::move(cfg));

    auto stats = MakeStats(/*aborting*/ false);

    // Action
    reporter.testRunEnded(stats);

    // Observable behavior: the cumulative hook was invoked exactly once.
    EXPECT_EQ(reporter.callsToHook(), 1);
}

// Boundary/error case: calling testRunEnded a second time asserts (death test).
// This checks the observable effect of the internal `assert(!m_testRun)`.
TEST_F(CumulativeReporterBase_Test_861, SecondCallAsserts_861) {
#ifndef NDEBUG
    auto cfg = MakeReporterConfig(out_);
    RecordingCumulativeReporter reporter(std::move(cfg));

    auto stats = MakeStats(/*aborting*/ false);

    reporter.testRunEnded(stats);

    // The second call should fail the assertion. We use a death test to verify.
    // Match the assert message if you want (optional).
    EXPECT_DEATH(
        reporter.testRunEnded(stats),
        HasSubstr("CumulativeReporterBase assumes there can only be one test run")
    );
#else
    GTEST_SKIP() << "Assertion-based death test skipped in NDEBUG builds.";
#endif
}
