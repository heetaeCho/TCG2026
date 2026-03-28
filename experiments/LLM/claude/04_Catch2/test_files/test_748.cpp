#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <memory>

#include "catch2/catch_totals.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/reporters/catch_reporter_tap.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_istream.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_stream.hpp"
#include "catch2/catch_session.hpp"

namespace {

// Helper to create a stream wrapper that writes to a given ostream
class StringIStream : public Catch::IStream {
    std::ostringstream m_oss;
public:
    std::ostream& stream() override { return m_oss; }
    std::string str() const { return m_oss.str(); }
};

// Helper to build a ReporterConfig with a string stream
struct TestFixture {
    std::shared_ptr<StringIStream> stringStream;
    
    TestFixture() : stringStream(std::make_shared<StringIStream>()) {}
    
    std::string getOutput() const {
        return stringStream->str();
    }
};

Catch::Totals makeTotals(std::uint64_t assertionsPassed, std::uint64_t assertionsFailed,
                          std::uint64_t testCasesPassed, std::uint64_t testCasesFailed) {
    Catch::Totals totals;
    totals.assertions.passed = assertionsPassed;
    totals.assertions.failed = assertionsFailed;
    totals.testCases.passed = testCasesPassed;
    totals.testCases.failed = testCasesFailed;
    return totals;
}

} // anonymous namespace

class TAPReporterTest_748 : public ::testing::Test {
protected:
    std::ostringstream m_oss;
    
    // We'll test the logic by directly examining what testRunEnded writes.
    // Since constructing TAPReporter requires ReporterConfig, we try to do so properly.
};

// Since constructing TAPReporter with all its dependencies is complex,
// let's test through the Catch2 session or build config properly.
// We'll attempt to create the reporter with a minimal config.

TEST(TAPReporterTestRunEnded_748, OutputsCorrectRangeWithAssertions_748) {
    // Create a string stream to capture output
    auto oss = Catch::Detail::make_unique<StringIStream>();
    auto* ossPtr = oss.get();
    
    // We need to construct ReporterConfig - this requires IConfig and stream
    // Using Catch2's own test infrastructure
    Catch::ConfigData cfgData;
    cfgData.name = "test";
    auto config = std::make_shared<Catch::Config>(cfgData);
    
    Catch::ReporterConfig repConfig(config.get(), Catch::Detail::unique_ptr<Catch::IStream>(oss.release()), Catch::ColourMode::None, {});
    
    Catch::TAPReporter reporter(std::move(repConfig));
    
    // Need to call testRunStarting first
    Catch::TestRunInfo runInfo("test_run");
    reporter.testRunStarting(runInfo);
    
    // Create totals with some assertions and test cases
    Catch::Totals totals;
    totals.assertions.passed = 5;
    totals.assertions.failed = 3;
    totals.testCases.passed = 2;
    totals.testCases.failed = 1;
    
    Catch::TestRunStats stats(runInfo, totals, false);
    reporter.testRunEnded(stats);
    
    std::string output = ossPtr->str();
    // Should contain "1..8" (5+3 = 8 total assertions)
    EXPECT_NE(output.find("1..8"), std::string::npos);
    // Should NOT contain skip message since test cases > 0
    EXPECT_EQ(output.find("# Skipped: No tests ran."), std::string::npos);
    // Should end with "\n\n"
    EXPECT_NE(output.find("\n\n"), std::string::npos);
}

TEST(TAPReporterTestRunEnded_748, OutputsSkipMessageWhenNoTestCases_748) {
    auto oss = Catch::Detail::make_unique<StringIStream>();
    auto* ossPtr = oss.get();
    
    Catch::ConfigData cfgData;
    cfgData.name = "test";
    auto config = std::make_shared<Catch::Config>(cfgData);
    
    Catch::ReporterConfig repConfig(config.get(), Catch::Detail::unique_ptr<Catch::IStream>(oss.release()), Catch::ColourMode::None, {});
    
    Catch::TAPReporter reporter(std::move(repConfig));
    
    Catch::TestRunInfo runInfo("test_run");
    reporter.testRunStarting(runInfo);
    
    // Create totals with zero test cases
    Catch::Totals totals;
    totals.assertions.passed = 0;
    totals.assertions.failed = 0;
    totals.testCases.passed = 0;
    totals.testCases.failed = 0;
    
    Catch::TestRunStats stats(runInfo, totals, false);
    reporter.testRunEnded(stats);
    
    std::string output = ossPtr->str();
    // Should contain "1..0"
    EXPECT_NE(output.find("1..0"), std::string::npos);
    // Should contain skip message
    EXPECT_NE(output.find("# Skipped: No tests ran."), std::string::npos);
}

TEST(TAPReporterTestRunEnded_748, OutputsCorrectTotalWithOnlyPassedAssertions_748) {
    auto oss = Catch::Detail::make_unique<StringIStream>();
    auto* ossPtr = oss.get();
    
    Catch::ConfigData cfgData;
    cfgData.name = "test";
    auto config = std::make_shared<Catch::Config>(cfgData);
    
    Catch::ReporterConfig repConfig(config.get(), Catch::Detail::unique_ptr<Catch::IStream>(oss.release()), Catch::ColourMode::None, {});
    
    Catch::TAPReporter reporter(std::move(repConfig));
    
    Catch::TestRunInfo runInfo("test_run");
    reporter.testRunStarting(runInfo);
    
    Catch::Totals totals;
    totals.assertions.passed = 10;
    totals.assertions.failed = 0;
    totals.testCases.passed = 3;
    totals.testCases.failed = 0;
    
    Catch::TestRunStats stats(runInfo, totals, false);
    reporter.testRunEnded(stats);
    
    std::string output = ossPtr->str();
    EXPECT_NE(output.find("1..10"), std::string::npos);
    EXPECT_EQ(output.find("# Skipped: No tests ran."), std::string::npos);
}

TEST(TAPReporterTestRunEnded_748, OutputsCorrectTotalWithOnlyFailedAssertions_748) {
    auto oss = Catch::Detail::make_unique<StringIStream>();
    auto* ossPtr = oss.get();
    
    Catch::ConfigData cfgData;
    cfgData.name = "test";
    auto config = std::make_shared<Catch::Config>(cfgData);
    
    Catch::ReporterConfig repConfig(config.get(), Catch::Detail::unique_ptr<Catch::IStream>(oss.release()), Catch::ColourMode::None, {});
    
    Catch::TAPReporter reporter(std::move(repConfig));
    
    Catch::TestRunInfo runInfo("test_run");
    reporter.testRunStarting(runInfo);
    
    Catch::Totals totals;
    totals.assertions.passed = 0;
    totals.assertions.failed = 7;
    totals.testCases.passed = 0;
    totals.testCases.failed = 2;
    
    Catch::TestRunStats stats(runInfo, totals, false);
    reporter.testRunEnded(stats);
    
    std::string output = ossPtr->str();
    EXPECT_NE(output.find("1..7"), std::string::npos);
    EXPECT_EQ(output.find("# Skipped: No tests ran."), std::string::npos);
}

TEST(TAPReporterTestRunEnded_748, AbortingDoesNotChangeOutput_748) {
    auto oss = Catch::Detail::make_unique<StringIStream>();
    auto* ossPtr = oss.get();
    
    Catch::ConfigData cfgData;
    cfgData.name = "test";
    auto config = std::make_shared<Catch::Config>(cfgData);
    
    Catch::ReporterConfig repConfig(config.get(), Catch::Detail::unique_ptr<Catch::IStream>(oss.release()), Catch::ColourMode::None, {});
    
    Catch::TAPReporter reporter(std::move(repConfig));
    
    Catch::TestRunInfo runInfo("test_run");
    reporter.testRunStarting(runInfo);
    
    Catch::Totals totals;
    totals.assertions.passed = 3;
    totals.assertions.failed = 2;
    totals.testCases.passed = 1;
    totals.testCases.failed = 1;
    
    // aborting = true
    Catch::TestRunStats stats(runInfo, totals, true);
    reporter.testRunEnded(stats);
    
    std::string output = ossPtr->str();
    EXPECT_NE(output.find("1..5"), std::string::npos);
    EXPECT_EQ(output.find("# Skipped: No tests ran."), std::string::npos);
}

TEST(TAPReporterTestRunEnded_748, SingleAssertionOutput_748) {
    auto oss = Catch::Detail::make_unique<StringIStream>();
    auto* ossPtr = oss.get();
    
    Catch::ConfigData cfgData;
    cfgData.name = "test";
    auto config = std::make_shared<Catch::Config>(cfgData);
    
    Catch::ReporterConfig repConfig(config.get(), Catch::Detail::unique_ptr<Catch::IStream>(oss.release()), Catch::ColourMode::None, {});
    
    Catch::TAPReporter reporter(std::move(repConfig));
    
    Catch::TestRunInfo runInfo("test_run");
    reporter.testRunStarting(runInfo);
    
    Catch::Totals totals;
    totals.assertions.passed = 1;
    totals.testCases.passed = 1;
    
    Catch::TestRunStats stats(runInfo, totals, false);
    reporter.testRunEnded(stats);
    
    std::string output = ossPtr->str();
    EXPECT_NE(output.find("1..1"), std::string::npos);
    EXPECT_EQ(output.find("# Skipped: No tests ran."), std::string::npos);
}

TEST(TAPReporterTestRunEnded_748, ZeroAssertionsWithTestCasesNoSkipMessage_748) {
    auto oss = Catch::Detail::make_unique<StringIStream>();
    auto* ossPtr = oss.get();
    
    Catch::ConfigData cfgData;
    cfgData.name = "test";
    auto config = std::make_shared<Catch::Config>(cfgData);
    
    Catch::ReporterConfig repConfig(config.get(), Catch::Detail::unique_ptr<Catch::IStream>(oss.release()), Catch::ColourMode::None, {});
    
    Catch::TAPReporter reporter(std::move(repConfig));
    
    Catch::TestRunInfo runInfo("test_run");
    reporter.testRunStarting(runInfo);
    
    // Zero assertions but test cases ran (edge case: test cases with no assertions)
    Catch::Totals totals;
    totals.assertions.passed = 0;
    totals.assertions.failed = 0;
    totals.testCases.passed = 1;
    totals.testCases.failed = 0;
    
    Catch::TestRunStats stats(runInfo, totals, false);
    reporter.testRunEnded(stats);
    
    std::string output = ossPtr->str();
    EXPECT_NE(output.find("1..0"), std::string::npos);
    // testCases.total() == 1, so no skip message
    EXPECT_EQ(output.find("# Skipped: No tests ran."), std::string::npos);
}

TEST(TAPReporterTestRunEnded_748, IncludesSkippedAndFailedButOkInTotal_748) {
    auto oss = Catch::Detail::make_unique<StringIStream>();
    auto* ossPtr = oss.get();
    
    Catch::ConfigData cfgData;
    cfgData.name = "test";
    auto config = std::make_shared<Catch::Config>(cfgData);
    
    Catch::ReporterConfig repConfig(config.get(), Catch::Detail::unique_ptr<Catch::IStream>(oss.release()), Catch::ColourMode::None, {});
    
    Catch::TAPReporter reporter(std::move(repConfig));
    
    Catch::TestRunInfo runInfo("test_run");
    reporter.testRunStarting(runInfo);
    
    Catch::Totals totals;
    totals.assertions.passed = 2;
    totals.assertions.failed = 1;
    totals.assertions.failedButOk = 1;
    totals.assertions.skipped = 1;
    totals.testCases.passed = 1;
    totals.testCases.failed = 1;
    
    Catch::TestRunStats stats(runInfo, totals, false);
    reporter.testRunEnded(stats);
    
    std::string output = ossPtr->str();
    // total = passed + failed + failedButOk + skipped = 2 + 1 + 1 + 1 = 5
    EXPECT_NE(output.find("1..5"), std::string::npos);
    EXPECT_EQ(output.find("# Skipped: No tests ran."), std::string::npos);
}

TEST(TAPReporterTestRunEnded_748, LargeNumberOfAssertions_748) {
    auto oss = Catch::Detail::make_unique<StringIStream>();
    auto* ossPtr = oss.get();
    
    Catch::ConfigData cfgData;
    cfgData.name = "test";
    auto config = std::make_shared<Catch::Config>(cfgData);
    
    Catch::ReporterConfig repConfig(config.get(), Catch::Detail::unique_ptr<Catch::IStream>(oss.release()), Catch::ColourMode::None, {});
    
    Catch::TAPReporter reporter(std::move(repConfig));
    
    Catch::TestRunInfo runInfo("test_run");
    reporter.testRunStarting(runInfo);
    
    Catch::Totals totals;
    totals.assertions.passed = 999999;
    totals.assertions.failed = 1;
    totals.testCases.passed = 100;
    
    Catch::TestRunStats stats(runInfo, totals, false);
    reporter.testRunEnded(stats);
    
    std::string output = ossPtr->str();
    EXPECT_NE(output.find("1..1000000"), std::string::npos);
}
