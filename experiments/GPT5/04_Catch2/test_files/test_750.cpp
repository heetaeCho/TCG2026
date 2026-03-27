// File: tests/junit_reporter_testRunStarting_750.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>

// Catch2 reporter + deps (interfaces only)
#include <catch2/reporters/catch_reporter_junit.hpp>
#include <catch2/reporters/catch_reporter_helpers.hpp>
#include <catch2/internal/catch_test_run_info.hpp>

using ::testing::HasSubstr;

namespace {

class JunitReporterTest_750 : public ::testing::Test {
protected:
    std::ostringstream out;

    // Helper to construct a reporter with our output stream.
    // This stays strictly at interface level (ReporterConfig).
    Catch::JunitReporter makeReporter() {
        // Construct a minimal ReporterConfig that directs output to `out`.
        // We do not rely on any internal state of the reporter.
        Catch::ReporterPreferences prefs;
        // Keep defaults; we only care that output goes to our stream.
        Catch::ReporterConfig cfg{ prefs, nullptr, out };
        return Catch::JunitReporter( std::move(cfg) );
    }
};

} // namespace

// Normal operation: calling testRunStarting writes the opening testsuites element
TEST_F(JunitReporterTest_750, WritesTestsuitesStartElement_750) {
    auto reporter = makeReporter();

    // Name is not used directly by the tested function for output shape,
    // but we provide a realistic non-empty run name.
    Catch::TestRunInfo runInfo{ "sample-run" };

    // Exercise
    ASSERT_NO_THROW(reporter.testRunStarting(runInfo));

    // Verify observable effect via the configured stream:
    // We do not assert exact formatting; we only check that the
    // "testsuites" element was begun in some form.
    const std::string xml = out.str();
    EXPECT_FALSE(xml.empty());
    EXPECT_THAT(xml, HasSubstr("testsuites"));
}

// Boundary case: empty run name should not throw and should still begin testsuites
TEST_F(JunitReporterTest_750, AcceptsEmptyRunName_750) {
    auto reporter = makeReporter();
    Catch::TestRunInfo runInfo{ "" };

    EXPECT_NO_THROW(reporter.testRunStarting(runInfo));

    const std::string xml = out.str();
    EXPECT_FALSE(xml.empty());
    EXPECT_THAT(xml, HasSubstr("testsuites"));
}

// Idempotency-ish / repeated call behavior (observable):
// Calling testRunStarting twice should not throw; output should be appended (stream grows)
// We DO NOT check internal state or XML correctness beyond "testsuites" presence.
TEST_F(JunitReporterTest_750, MultipleCallsAppendOutputWithoutThrowing_750) {
    auto reporter = makeReporter();
    Catch::TestRunInfo runInfo{ "run" };

    ASSERT_NO_THROW(reporter.testRunStarting(runInfo));
    const auto firstSize = out.str().size();

    // Call again; while this might not be typical usage, it’s an interface-level
    // boundary check that must not crash/throw. We only observe stream growth.
    EXPECT_NO_THROW(reporter.testRunStarting(runInfo));
    const auto secondSize = out.str().size();

    EXPECT_GT(secondSize, firstSize);
    EXPECT_THAT(out.str(), HasSubstr("testsuites"));
}
