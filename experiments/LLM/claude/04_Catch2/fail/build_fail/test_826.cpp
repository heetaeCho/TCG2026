#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "catch2/reporters/catch_reporter_sonarqube.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_test_run_info.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"

using namespace Catch;

namespace {

// A minimal mock config for testing
class MockConfig : public IConfig {
public:
    bool allowThrows() const override { return true; }
    StringRef name() const override { return "test"_sr; }
    int abortAfter() const override { return -1; }
    bool showInvisibles() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::Never; }
    double minDuration() const override { return -1.0; }
    TestRunOrder runOrder() const override { return TestRunOrder::Declared; }
    uint32_t rngSeed() const override { return 0; }
    unsigned int shardCount() const override { return 1; }
    unsigned int shardIndex() const override { return 0; }
    ColourMode defaultColourMode() const override { return ColourMode::None; }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    std::vector<ReporterSpec> const& getReporterSpecs() const override {
        static std::vector<ReporterSpec> empty;
        return empty;
    }
    std::vector<std::string> const& getTestsOrTags() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    bool hasTestFilters() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    std::string const& getFilename() const override {
        static std::string empty;
        return empty;
    }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override {
        return std::chrono::milliseconds(100);
    }
};

class SonarQubeReporterTest_826 : public ::testing::Test {
protected:
    void SetUp() override {
        m_config = new MockConfig();
    }

    void TearDown() override {
        delete m_config;
    }

    std::unique_ptr<SonarQubeReporter> createReporter(std::ostream& os) {
        auto prefs = ReporterConfig(m_config, os, ColourMode::None, {});
        return std::make_unique<SonarQubeReporter>(std::move(prefs));
    }

    MockConfig* m_config = nullptr;
};

TEST_F(SonarQubeReporterTest_826, TestRunStartingWritesXmlComment_826) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("TestRun"_sr);
    reporter->testRunStarting(runInfo);

    std::string output = oss.str();
    // Should contain an XML comment
    EXPECT_NE(output.find("<!--"), std::string::npos);
    EXPECT_NE(output.find("-->"), std::string::npos);
}

TEST_F(SonarQubeReporterTest_826, TestRunStartingWritesTestExecutionsElement_826) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("TestRun"_sr);
    reporter->testRunStarting(runInfo);

    std::string output = oss.str();
    // Should contain testExecutions element
    EXPECT_NE(output.find("testExecutions"), std::string::npos);
}

TEST_F(SonarQubeReporterTest_826, TestRunStartingWritesVersionAttribute_826) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("TestRun"_sr);
    reporter->testRunStarting(runInfo);

    std::string output = oss.str();
    // Should contain version="1" attribute
    EXPECT_NE(output.find("version"), std::string::npos);
    EXPECT_NE(output.find("1"), std::string::npos);
}

TEST_F(SonarQubeReporterTest_826, TestRunStartingProducesValidXmlStructure_826) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("MyTestSuite"_sr);
    reporter->testRunStarting(runInfo);

    std::string output = oss.str();
    // The XML declaration should appear
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

TEST_F(SonarQubeReporterTest_826, GetDescriptionReturnsNonEmptyString_826) {
    std::string desc = SonarQubeReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(SonarQubeReporterTest_826, TestRunStartingWithEmptyName_826) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo(""_sr);
    reporter->testRunStarting(runInfo);

    std::string output = oss.str();
    // Should still produce valid output with testExecutions
    EXPECT_NE(output.find("testExecutions"), std::string::npos);
}

TEST_F(SonarQubeReporterTest_826, TestRunStartingWithSpecialCharactersInName_826) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("Test<>&\"Run"_sr);
    reporter->testRunStarting(runInfo);

    std::string output = oss.str();
    // Should still contain testExecutions element
    EXPECT_NE(output.find("testExecutions"), std::string::npos);
}

TEST_F(SonarQubeReporterTest_826, TestRunStartingOutputContainsVersionOne_826) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test"_sr);
    reporter->testRunStarting(runInfo);

    std::string output = oss.str();
    // Check version attribute value is 1
    // The attribute should be version="1"
    EXPECT_NE(output.find("version=\"1\""), std::string::npos);
}

TEST_F(SonarQubeReporterTest_826, TestRunStartingCommentBeforeElement_826) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test"_sr);
    reporter->testRunStarting(runInfo);

    std::string output = oss.str();
    // Comment should appear before testExecutions
    auto commentPos = output.find("<!--");
    auto elementPos = output.find("<testExecutions");
    EXPECT_NE(commentPos, std::string::npos);
    EXPECT_NE(elementPos, std::string::npos);
    EXPECT_LT(commentPos, elementPos);
}

TEST_F(SonarQubeReporterTest_826, TestRunStartingCommentContainsMetadata_826) {
    std::ostringstream oss;
    auto reporter = createReporter(oss);

    TestRunInfo runInfo("test"_sr);
    reporter->testRunStarting(runInfo);

    std::string output = oss.str();
    // The comment should contain some metadata (e.g., Catch2 version info)
    auto commentStart = output.find("<!--");
    auto commentEnd = output.find("-->");
    EXPECT_NE(commentStart, std::string::npos);
    EXPECT_NE(commentEnd, std::string::npos);
    // Comment should have some content between the delimiters
    EXPECT_GT(commentEnd, commentStart + 4);
}

} // anonymous namespace
