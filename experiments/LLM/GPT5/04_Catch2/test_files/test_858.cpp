// File: tests/cumulative_reporter_assertionEnded_858_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Catch2 headers from your codebase
#include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_assertion_result.hpp"

// If your project puts these in different include paths, adjust the includes above.

using ::testing::Test;

namespace {

// -----------------------------
// Test double: expose only what is allowed/needed
// -----------------------------
class TestableCumulativeReporter_858 : public Catch::CumulativeReporterBase {
public:
    using Base = Catch::CumulativeReporterBase;

    // Forward to real ReporterBase config; in your test harness you likely have a ReporterConfig ready.
    // If not, provide a minimal viable ReporterConfig from your codebase.
    explicit TestableCumulativeReporter_858(Catch::ReporterConfig&& cfg)
        : Base(std::move(cfg)) {}

    // Helpers to drive the reporter ONLY through its public interface
    void BeginSection(const Catch::SectionInfo& info) { this->sectionStarting(info); }
    void EndSection(const Catch::SectionStats& stats) { this->sectionEnded(stats); }

    // Expose protected flags for setup (allowed by C++ access rules, does not touch private state)
    void setStoreSuccessful(bool v) { m_shouldStoreSuccesfulAssertions = v; }
    void setStoreFailed(bool v)     { m_shouldStoreFailedAssertions   = v; }
};

// -----------------------------
// Minimal factory helpers
// Fill these using your project’s real constructors/utilities.
// The goal is to create an AssertionStats whose assertionResult.isOk() is true/false.
// -----------------------------

// You likely have concrete types for these in your tree.
// Replace these stubs with real ones as needed.
static Catch::AssertionStats MakeAssertionStatsFromResult(
    const Catch::AssertionResult& ar)
{
    std::vector<Catch::MessageInfo> infos; // usually empty is fine
    Catch::Totals totals{};                // zero-initialized; content unused by the code path under test
    return Catch::AssertionStats(ar, infos, totals);
}

// Provide real implementations for these two helpers in your tree.
// Below is a sketch that assumes you can construct `AssertionResult`
// to represent success/failure without re-implementing internals.
// If your codebase has utilities like `AssertionResultData::makeResult`,
// use those instead.

static Catch::AssertionResult MakePassingAssertionResult() {
    // --- BEGIN: adapt to your constructors ---
    // You need a valid AssertionInfo + AssertionResultData with a "success" ResultWas
    Catch::AssertionInfo info{/*fill with minimal valid fields*/};
    Catch::AssertionResultData data{/*fill to indicate success*/};
    // --- END: adapt to your constructors ---
    return Catch::AssertionResult(info, std::move(data));
}

static Catch::AssertionResult MakeFailingAssertionResult() {
    // --- BEGIN: adapt to your constructors ---
    Catch::AssertionInfo info{/*fill with minimal valid fields*/};
    Catch::AssertionResultData data{/*fill to indicate failure*/};
    // --- END: adapt to your constructors ---
    return Catch::AssertionResult(info, std::move(data));
}

static Catch::AssertionStats MakePassingAssertionStats() {
    return MakeAssertionStatsFromResult(MakePassingAssertionResult());
}

static Catch::AssertionStats MakeFailingAssertionStats() {
    return MakeAssertionStatsFromResult(MakeFailingAssertionResult());
}

// Section scaffolding helpers — only through public API types.
static Catch::SectionInfo DummySectionInfo(const char* name = "S")
{
    // Fill minimally-valid SectionInfo for your tree
    return Catch::SectionInfo{/*name*/name, /*description*/"", /*source*/{}};
}

static Catch::SectionStats DummySectionStats()
{
    // Fill minimally-valid SectionStats for your tree
    return Catch::SectionStats{/*info*/DummySectionInfo(), /*assertions*/{}, /*missingSections*/{}, /*durationInSeconds*/0.0, /*aborting*/false};
}

} // namespace

// ===============================================
// TESTS
// ===============================================

class CumulativeReporterAssertionEnded_858 : public Test {
protected:
    // Provide a real ReporterConfig from your codebase here.
    // If ReporterConfig requires a stream, test name, etc., build it minimally.
    static Catch::ReporterConfig MakeConfig() {
        // --- BEGIN: adapt to your constructors ---
        Catch::ReporterConfig cfg{/* stream */nullptr, /* fullConfig */nullptr};
        // --- END: adapt to your constructors ---
        return cfg;
    }

    TestableCumulativeReporter_858 makeReporter() {
        return TestableCumulativeReporter_858(Catch::ReporterConfig(MakeConfig()));
    }
};

// [TEST_ID: 858]
TEST_F(CumulativeReporterAssertionEnded_858, DiesIfNoSectionStarted_858) {
#ifndef NDEBUG
    // In debug builds, the function asserts that section stack is non-empty.
    auto reporter = makeReporter();
    auto stats = MakePassingAssertionStats();
    EXPECT_DEATH(
        reporter.assertionEnded(stats),
        ".*"); // assertion message pattern; keep generic
#else
    GTEST_SKIP() << "Assertion-based death test skipped in NDEBUG builds.";
#endif
}

// [TEST_ID: 858]
TEST_F(CumulativeReporterAssertionEnded_858, AcceptsPassingAssertionWhenSectionActive_858) {
    auto reporter = makeReporter();

    // Prepare a live section solely via public API
    reporter.BeginSection(DummySectionInfo("sect"));
    // If your flow requires sectionEnded to be called elsewhere, we keep the section open here
    // to satisfy the precondition inside assertionEnded.

    // Enable storing successful assertions (protected flag is accessible in subclass)
    reporter.setStoreSuccessful(true);

    // This must not crash or throw
    EXPECT_NO_THROW({
        reporter.assertionEnded(MakePassingAssertionStats());
    });

    // Close section to keep reporter lifecycle sane for future API calls
    reporter.EndSection(DummySectionStats());
}

// [TEST_ID: 858]
TEST_F(CumulativeReporterAssertionEnded_858, AcceptsFailingAssertionWhenSectionActive_858) {
    auto reporter = makeReporter();

    reporter.BeginSection(DummySectionInfo("sect"));
    reporter.setStoreFailed(true);

    EXPECT_NO_THROW({
        reporter.assertionEnded(MakeFailingAssertionStats());
    });

    reporter.EndSection(DummySectionStats());
}

// [TEST_ID: 858]
TEST_F(CumulativeReporterAssertionEnded_858, RespectsFlags_NoCrashWhenDisabled_858) {
    auto reporter = makeReporter();

    reporter.BeginSection(DummySectionInfo("sect"));

    // Disable both to exercise the short paths where expanded expression should not be stored
    reporter.setStoreSuccessful(false);
    reporter.setStoreFailed(false);

    EXPECT_NO_THROW({
        reporter.assertionEnded(MakePassingAssertionStats());
        reporter.assertionEnded(MakeFailingAssertionStats());
    });

    reporter.EndSection(DummySectionStats());
}

// [TEST_ID: 858]
TEST_F(CumulativeReporterAssertionEnded_858, CanBeCalledMultipleTimesWithinSection_858) {
    auto reporter = makeReporter();

    reporter.BeginSection(DummySectionInfo("sect"));
    reporter.setStoreSuccessful(true);
    reporter.setStoreFailed(true);

    EXPECT_NO_THROW({
        reporter.assertionEnded(MakePassingAssertionStats());
        reporter.assertionEnded(MakeFailingAssertionStats());
        reporter.assertionEnded(MakePassingAssertionStats());
        reporter.assertionEnded(MakeFailingAssertionStats());
    });

    reporter.EndSection(DummySectionStats());
}
