#include <sstream>
#include <string>
#include <memory>

#include "catch2/reporters/catch_reporter_teamcity.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_test_run_info.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_stream.hpp"
#include "catch2/reporters/catch_reporter_helpers.hpp"

#include <gtest/gtest.h>

namespace {

// Helper to create a ReporterConfig that writes to a given stringstream
class TeamCityReporterTest_782 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need to construct a ReporterConfig. This requires a config and a stream.
        // We'll use Catch2's internal mechanisms to set this up.
    }

    std::string getOutput(const std::string& testName, bool aborting = false) {
        std::stringstream ss;

        // Create minimal argv for config
        const char* argv[] = {"test"};
        Catch::ConfigData configData;
        configData.name = testName;
        auto config = std::make_shared<Catch::Config>(configData);

        auto stream = Catch::Detail::make_unique<Catch::StringStream>();
        auto& streamRef = stream->stream();

        Catch::ReporterConfig reporterConfig(config.get(), CATCH_MOVE(stream), Catch::ColourMode::None, {});
        Catch::TeamCityReporter reporter(CATCH_MOVE(reporterConfig));

        Catch::TestRunInfo runInfo(Catch::StringRef(testName));
        Catch::Totals totals;
        Catch::TestRunStats runStats(runInfo, totals, aborting);

        reporter.testRunEnded(runStats);

        // We need to capture what was written to the stream
        // The stream is internal, so let's use a different approach
        return "";
    }
};

// We need a custom IStream implementation to capture output
class StringOStream : public Catch::IStream {
public:
    std::ostringstream m_oss;
    std::ostream& stream() override { return m_oss; }
    std::string str() const { return m_oss.str(); }
};

class TeamCityReporterFixture_782 : public ::testing::Test {
protected:
    std::shared_ptr<Catch::Config> config_;
    StringOStream* rawStream_ = nullptr;

    std::unique_ptr<Catch::TeamCityReporter> createReporter() {
        Catch::ConfigData configData;
        config_ = std::make_shared<Catch::Config>(configData);

        auto stream = Catch::Detail::make_unique<StringOStream>();
        rawStream_ = stream.get();

        Catch::ReporterConfig reporterConfig(
            config_.get(),
            CATCH_MOVE(stream),
            Catch::ColourMode::None,
            {}
        );
        return std::make_unique<Catch::TeamCityReporter>(CATCH_MOVE(reporterConfig));
    }

    std::string getStreamOutput() const {
        return rawStream_->str();
    }
};

// Test that testRunEnded outputs the expected teamcity format
TEST_F(TeamCityReporterFixture_782, TestRunEnded_OutputsTestSuiteFinished_782) {
    auto reporter = createReporter();

    Catch::TestRunInfo runInfo("MyTestSuite");
    Catch::Totals totals;
    Catch::TestRunStats runStats(runInfo, totals, false);

    reporter->testRunEnded(runStats);

    std::string output = getStreamOutput();
    EXPECT_NE(output.find("##teamcity[testSuiteFinished name='MyTestSuite']"), std::string::npos);
}

// Test that testRunStarting outputs the expected teamcity format
TEST_F(TeamCityReporterFixture_782, TestRunStarting_OutputsTestSuiteStarted_782) {
    auto reporter = createReporter();

    Catch::TestRunInfo runInfo("StartSuite");
    reporter->testRunStarting(runInfo);

    std::string output = getStreamOutput();
    EXPECT_NE(output.find("##teamcity[testSuiteStarted name='StartSuite']"), std::string::npos);
}

// Test with empty name
TEST_F(TeamCityReporterFixture_782, TestRunEnded_EmptyName_782) {
    auto reporter = createReporter();

    Catch::TestRunInfo runInfo("");
    Catch::Totals totals;
    Catch::TestRunStats runStats(runInfo, totals, false);

    reporter->testRunEnded(runStats);

    std::string output = getStreamOutput();
    EXPECT_NE(output.find("##teamcity[testSuiteFinished name='"), std::string::npos);
}

// Test with special characters that need escaping (e.g., single quote, pipe, newline)
TEST_F(TeamCityReporterFixture_782, TestRunEnded_NameWithSingleQuote_782) {
    auto reporter = createReporter();

    Catch::TestRunInfo runInfo("Test's Suite");
    Catch::Totals totals;
    Catch::TestRunStats runStats(runInfo, totals, false);

    reporter->testRunEnded(runStats);

    std::string output = getStreamOutput();
    // TeamCity escaping uses |' for single quotes
    EXPECT_NE(output.find("##teamcity[testSuiteFinished name='"), std::string::npos);
    // The raw quote should be escaped, so literal "Test's" should NOT appear
    EXPECT_EQ(output.find("name='Test's"), std::string::npos);
    // Instead expect escaped version
    EXPECT_NE(output.find("Test|'s Suite"), std::string::npos);
}

// Test with pipe character in name
TEST_F(TeamCityReporterFixture_782, TestRunEnded_NameWithPipe_782) {
    auto reporter = createReporter();

    Catch::TestRunInfo runInfo("Test|Suite");
    Catch::Totals totals;
    Catch::TestRunStats runStats(runInfo, totals, false);

    reporter->testRunEnded(runStats);

    std::string output = getStreamOutput();
    // Pipe should be escaped as ||
    EXPECT_NE(output.find("Test||Suite"), std::string::npos);
}

// Test with newline in name
TEST_F(TeamCityReporterFixture_782, TestRunEnded_NameWithNewline_782) {
    auto reporter = createReporter();

    Catch::TestRunInfo runInfo("Test\nSuite");
    Catch::Totals totals;
    Catch::TestRunStats runStats(runInfo, totals, false);

    reporter->testRunEnded(runStats);

    std::string output = getStreamOutput();
    // Newline should be escaped as |n
    EXPECT_NE(output.find("Test|nSuite"), std::string::npos);
}

// Test with bracket in name
TEST_F(TeamCityReporterFixture_782, TestRunEnded_NameWithBrackets_782) {
    auto reporter = createReporter();

    Catch::TestRunInfo runInfo("Test[Suite]");
    Catch::Totals totals;
    Catch::TestRunStats runStats(runInfo, totals, false);

    reporter->testRunEnded(runStats);

    std::string output = getStreamOutput();
    // Brackets should be escaped as |[ and |]
    EXPECT_NE(output.find("Test|[Suite|]"), std::string::npos);
}

// Test with aborting flag true
TEST_F(TeamCityReporterFixture_782, TestRunEnded_WithAborting_782) {
    auto reporter = createReporter();

    Catch::TestRunInfo runInfo("AbortedSuite");
    Catch::Totals totals;
    Catch::TestRunStats runStats(runInfo, totals, true);

    reporter->testRunEnded(runStats);

    std::string output = getStreamOutput();
    EXPECT_NE(output.find("##teamcity[testSuiteFinished name='AbortedSuite']"), std::string::npos);
}

// Test that testRunStarting followed by testRunEnded produces both messages
TEST_F(TeamCityReporterFixture_782, TestRunStartingAndEnded_ProducesBothMessages_782) {
    auto reporter = createReporter();

    Catch::TestRunInfo runInfo("FullSuite");
    reporter->testRunStarting(runInfo);

    Catch::Totals totals;
    Catch::TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);

    std::string output = getStreamOutput();
    EXPECT_NE(output.find("##teamcity[testSuiteStarted name='FullSuite']"), std::string::npos);
    EXPECT_NE(output.find("##teamcity[testSuiteFinished name='FullSuite']"), std::string::npos);

    // Started should come before Finished
    auto startPos = output.find("testSuiteStarted");
    auto endPos = output.find("testSuiteFinished");
    EXPECT_LT(startPos, endPos);
}

// Test getDescription returns a non-empty string
TEST_F(TeamCityReporterFixture_782, GetDescription_ReturnsNonEmpty_782) {
    std::string desc = Catch::TeamCityReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test with a long name
TEST_F(TeamCityReporterFixture_782, TestRunEnded_LongName_782) {
    auto reporter = createReporter();

    std::string longName(1000, 'A');
    Catch::TestRunInfo runInfo(longName);
    Catch::Totals totals;
    Catch::TestRunStats runStats(runInfo, totals, false);

    reporter->testRunEnded(runStats);

    std::string output = getStreamOutput();
    EXPECT_NE(output.find("##teamcity[testSuiteFinished name='"), std::string::npos);
    EXPECT_NE(output.find(longName), std::string::npos);
}

} // anonymous namespace
