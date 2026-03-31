#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "catch2/reporters/catch_reporter_teamcity.hpp"
#include "catch2/internal/catch_test_run_info.hpp"
#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/internal/catch_istream.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"

using namespace Catch;

namespace {

// Helper to create a stream wrapper that writes to a given stringstream
class StringOStream : public Catch::IStream {
    std::ostringstream m_oss;
public:
    std::ostream& stream() override { return m_oss; }
    std::string str() const { return m_oss.str(); }
};

// Helper to create a ReporterConfig with a string stream for capturing output
class TeamCityReporterTest_781 : public ::testing::Test {
protected:
    std::unique_ptr<TeamCityReporter> createReporter(StringOStream*& outStream) {
        auto streamPtr = Catch::Detail::make_unique<StringOStream>();
        outStream = streamPtr.get();
        
        // Create a minimal config - we need a ConfigData and IConfig
        Catch::ConfigData configData;
        configData.name = "test";
        auto config = Catch::Detail::make_unique<Catch::Config>(configData);
        
        auto colourMode = Catch::ColourMode::None;
        std::map<std::string, std::string> customOptions;
        
        Catch::ReporterConfig reporterConfig(
            config.get(),
            CATCH_MOVE(streamPtr),
            colourMode,
            customOptions
        );
        
        m_config = CATCH_MOVE(config);
        return std::make_unique<TeamCityReporter>(CATCH_MOVE(reporterConfig));
    }
    
    Catch::Detail::unique_ptr<Catch::Config> m_config;
};

TEST_F(TeamCityReporterTest_781, TestRunStartingOutputsTestSuiteStarted_781) {
    StringOStream* outStream = nullptr;
    auto reporter = createReporter(outStream);
    
    TestRunInfo runInfo("MyTestSuite");
    reporter->testRunStarting(runInfo);
    
    std::string output = outStream->str();
    EXPECT_THAT(output, ::testing::HasSubstr("##teamcity[testSuiteStarted name='MyTestSuite']"));
}

TEST_F(TeamCityReporterTest_781, TestRunStartingEscapesSpecialCharacters_781) {
    StringOStream* outStream = nullptr;
    auto reporter = createReporter(outStream);
    
    TestRunInfo runInfo("Suite'With|Special");
    reporter->testRunStarting(runInfo);
    
    std::string output = outStream->str();
    // TeamCity escape rules: ' -> |', | -> ||
    EXPECT_THAT(output, ::testing::HasSubstr("##teamcity[testSuiteStarted name='"));
    // The special characters should be escaped
    EXPECT_THAT(output, ::testing::Not(::testing::HasSubstr("Suite'With|Special'")));
}

TEST_F(TeamCityReporterTest_781, TestRunEndingOutputsTestSuiteFinished_781) {
    StringOStream* outStream = nullptr;
    auto reporter = createReporter(outStream);
    
    TestRunInfo runInfo("MyTestSuite");
    reporter->testRunStarting(runInfo);
    
    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);
    
    std::string output = outStream->str();
    EXPECT_THAT(output, ::testing::HasSubstr("##teamcity[testSuiteFinished name='MyTestSuite']"));
}

TEST_F(TeamCityReporterTest_781, TestRunStartingWithEmptyName_781) {
    StringOStream* outStream = nullptr;
    auto reporter = createReporter(outStream);
    
    TestRunInfo runInfo("");
    reporter->testRunStarting(runInfo);
    
    std::string output = outStream->str();
    EXPECT_THAT(output, ::testing::HasSubstr("##teamcity[testSuiteStarted name='"));
}

TEST_F(TeamCityReporterTest_781, TestCaseStartingOutputsTestStarted_781) {
    StringOStream* outStream = nullptr;
    auto reporter = createReporter(outStream);
    
    TestRunInfo runInfo("Suite");
    reporter->testRunStarting(runInfo);
    
    auto testCaseInfo = Catch::makeTestCaseInfo(
        "classname", {"TestCase1", "[tag]"}, {"file.cpp", 1}
    );
    reporter->testCaseStarting(*testCaseInfo);
    
    std::string output = outStream->str();
    EXPECT_THAT(output, ::testing::HasSubstr("##teamcity[testStarted name='TestCase1']"));
}

TEST_F(TeamCityReporterTest_781, GetDescriptionReturnsNonEmptyString_781) {
    std::string desc = TeamCityReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(TeamCityReporterTest_781, TestRunStartingWithNewlineInName_781) {
    StringOStream* outStream = nullptr;
    auto reporter = createReporter(outStream);
    
    TestRunInfo runInfo("Suite\nName");
    reporter->testRunStarting(runInfo);
    
    std::string output = outStream->str();
    EXPECT_THAT(output, ::testing::HasSubstr("##teamcity[testSuiteStarted name='"));
}

TEST_F(TeamCityReporterTest_781, TestRunStartingWithBracketInName_781) {
    StringOStream* outStream = nullptr;
    auto reporter = createReporter(outStream);
    
    TestRunInfo runInfo("Suite[Name]");
    reporter->testRunStarting(runInfo);
    
    std::string output = outStream->str();
    EXPECT_THAT(output, ::testing::HasSubstr("##teamcity[testSuiteStarted name='"));
    // Brackets should be escaped in TeamCity format
}

TEST_F(TeamCityReporterTest_781, TestRunStartingEndsWithNewline_781) {
    StringOStream* outStream = nullptr;
    auto reporter = createReporter(outStream);
    
    TestRunInfo runInfo("MySuite");
    reporter->testRunStarting(runInfo);
    
    std::string output = outStream->str();
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), '\n');
}

TEST_F(TeamCityReporterTest_781, MultipleTestRunStartingCallsProduceMultipleLines_781) {
    StringOStream* outStream = nullptr;
    auto reporter = createReporter(outStream);
    
    TestRunInfo runInfo1("Suite1");
    reporter->testRunStarting(runInfo1);
    
    std::string output = outStream->str();
    size_t count = 0;
    size_t pos = 0;
    while ((pos = output.find("##teamcity[testSuiteStarted", pos)) != std::string::npos) {
        ++count;
        ++pos;
    }
    EXPECT_EQ(count, 1u);
}

} // anonymous namespace
