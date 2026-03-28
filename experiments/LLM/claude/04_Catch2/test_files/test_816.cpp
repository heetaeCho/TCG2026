#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "catch2/reporters/catch_reporter_compact.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/internal/catch_config_wchar.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_stream.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_istream.hpp"
#include "catch2/catch_session.hpp"

namespace {

// Helper to create a ReporterConfig with a string stream for capturing output
class CompactReporterTest_816 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need to set up a minimal Catch2 config and reporter config
        // This may require using Catch2's internal infrastructure
    }

    std::unique_ptr<Catch::CompactReporter> makeReporter(std::ostream& os) {
        // Create a config for the reporter
        // We need to construct a ReporterConfig that wraps our stream
        auto cfg = Catch::ConfigData{};
        cfg.showDurations = Catch::ShowDurations::Never;
        auto config = Catch::makeShared<Catch::Config>(cfg);

        auto streamWrapper = Catch::Detail::make_unique<Catch::ReporterStreamBuf>(os.rdbuf());
        // Need to create a proper ReporterConfig
        // This is tricky since ReporterConfig takes ownership of an IStream
        return nullptr; // placeholder
    }
};

} // anonymous namespace

// Since constructing CompactReporter requires complex Catch2 internal setup,
// we use Catch2's own infrastructure to create one properly.

class CompactReporterFixture_816 : public ::testing::Test {
protected:
    std::stringstream m_ss;
    std::unique_ptr<Catch::CompactReporter> m_reporter;

    void SetUp() override {
        auto cfg = Catch::ConfigData{};
        auto config = Catch::makeShared<Catch::Config>(cfg);

        // Create an IStream wrapping our stringstream
        auto stream = Catch::Detail::make_unique<Catch::StringStream>();
        
        Catch::ReporterConfig reporterConfig(
            config.get(),
            Catch::Detail::make_unique<Catch::StringStream>(),
            Catch::ColourMode::None,
            std::map<std::string, std::string>{}
        );

        m_reporter = Catch::Detail::make_unique<Catch::CompactReporter>(
            std::move(reporterConfig)
        );
    }
};

// Test getDescription returns a non-empty string
TEST(CompactReporterStatic_816, GetDescription_816) {
    std::string desc = Catch::CompactReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test that getDescription returns a meaningful description
TEST(CompactReporterStatic_816, GetDescriptionContent_816) {
    std::string desc = Catch::CompactReporter::getDescription();
    // The description should contain some text about the reporter
    EXPECT_GT(desc.size(), 0u);
}

// Test testRunEnded with all tests passing
TEST_F(CompactReporterFixture_816, TestRunEndedAllPassed_816) {
    if (!m_reporter) GTEST_SKIP() << "Reporter could not be constructed";

    Catch::TestRunInfo runInfo("test_run"_catch_sr);
    m_reporter->testRunStarting(runInfo);

    Catch::Totals totals;
    totals.assertions.passed = 10;
    totals.assertions.failed = 0;
    totals.testCases.passed = 5;
    totals.testCases.failed = 0;

    Catch::TestRunStats stats(runInfo, totals, false);
    EXPECT_NO_THROW(m_reporter->testRunEnded(stats));
}

// Test testRunEnded with some failures
TEST_F(CompactReporterFixture_816, TestRunEndedWithFailures_816) {
    if (!m_reporter) GTEST_SKIP() << "Reporter could not be constructed";

    Catch::TestRunInfo runInfo("test_run"_catch_sr);
    m_reporter->testRunStarting(runInfo);

    Catch::Totals totals;
    totals.assertions.passed = 8;
    totals.assertions.failed = 2;
    totals.testCases.passed = 3;
    totals.testCases.failed = 2;

    Catch::TestRunStats stats(runInfo, totals, false);
    EXPECT_NO_THROW(m_reporter->testRunEnded(stats));
}

// Test testRunEnded with zero totals
TEST_F(CompactReporterFixture_816, TestRunEndedZeroTotals_816) {
    if (!m_reporter) GTEST_SKIP() << "Reporter could not be constructed";

    Catch::TestRunInfo runInfo("empty_run"_catch_sr);
    m_reporter->testRunStarting(runInfo);

    Catch::Totals totals;
    Catch::TestRunStats stats(runInfo, totals, false);
    EXPECT_NO_THROW(m_reporter->testRunEnded(stats));
}

// Test testRunEnded with aborting flag
TEST_F(CompactReporterFixture_816, TestRunEndedAborting_816) {
    if (!m_reporter) GTEST_SKIP() << "Reporter could not be constructed";

    Catch::TestRunInfo runInfo("aborted_run"_catch_sr);
    m_reporter->testRunStarting(runInfo);

    Catch::Totals totals;
    totals.assertions.failed = 1;
    totals.testCases.failed = 1;

    Catch::TestRunStats stats(runInfo, totals, true);
    EXPECT_NO_THROW(m_reporter->testRunEnded(stats));
}

// Test testRunStarting
TEST_F(CompactReporterFixture_816, TestRunStarting_816) {
    if (!m_reporter) GTEST_SKIP() << "Reporter could not be constructed";

    Catch::TestRunInfo runInfo("my_test_run"_catch_sr);
    EXPECT_NO_THROW(m_reporter->testRunStarting(runInfo));
}

// Test noMatchingTestCases
TEST_F(CompactReporterFixture_816, NoMatchingTestCases_816) {
    if (!m_reporter) GTEST_SKIP() << "Reporter could not be constructed";

    EXPECT_NO_THROW(m_reporter->noMatchingTestCases("nonexistent_spec"_catch_sr));
}

// Test that testRunEnded can be called after testRunStarting (normal flow)
TEST_F(CompactReporterFixture_816, NormalTestRunFlow_816) {
    if (!m_reporter) GTEST_SKIP() << "Reporter could not be constructed";

    Catch::TestRunInfo runInfo("normal_flow"_catch_sr);
    m_reporter->testRunStarting(runInfo);

    Catch::Totals totals;
    totals.assertions.passed = 100;
    totals.testCases.passed = 50;

    Catch::TestRunStats stats(runInfo, totals, false);
    EXPECT_NO_THROW(m_reporter->testRunEnded(stats));
}

// Test with large numbers
TEST_F(CompactReporterFixture_816, TestRunEndedLargeTotals_816) {
    if (!m_reporter) GTEST_SKIP() << "Reporter could not be constructed";

    Catch::TestRunInfo runInfo("large_run"_catch_sr);
    m_reporter->testRunStarting(runInfo);

    Catch::Totals totals;
    totals.assertions.passed = 999999;
    totals.assertions.failed = 1;
    totals.testCases.passed = 99999;
    totals.testCases.failed = 1;

    Catch::TestRunStats stats(runInfo, totals, false);
    EXPECT_NO_THROW(m_reporter->testRunEnded(stats));
}
