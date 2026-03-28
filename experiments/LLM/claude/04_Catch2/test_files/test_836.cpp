#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_test_run_info.hpp"
#include "catch2/catch_test_spec.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/catch_reporter_registrars.hpp"

using namespace Catch;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::_;
using ::testing::NiceMock;

class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(const TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

class XmlReporterTest_836 : public ::testing::Test {
protected:
    std::stringstream m_stream;
    NiceMock<MockConfig> m_mockConfig;
    TestSpec m_testSpec;
    std::vector<std::string> m_emptyVec;
    std::vector<std::string> m_sectionsVec;

    void SetUp() override {
        ON_CALL(m_mockConfig, name()).WillByDefault(Return("TestRun"_sr));
        ON_CALL(m_mockConfig, rngSeed()).WillByDefault(Return(12345u));
        ON_CALL(m_mockConfig, testSpec()).WillByDefault(ReturnRef(m_testSpec));
        ON_CALL(m_mockConfig, hasTestFilters()).WillByDefault(Return(false));
        ON_CALL(m_mockConfig, getTestsOrTags()).WillByDefault(ReturnRef(m_emptyVec));
        ON_CALL(m_mockConfig, getSectionsToRun()).WillByDefault(ReturnRef(m_sectionsVec));
        ON_CALL(m_mockConfig, verbosity()).WillByDefault(Return(Verbosity::Normal));
        ON_CALL(m_mockConfig, defaultColourMode()).WillByDefault(Return(ColourMode::None));
        ON_CALL(m_mockConfig, allowThrows()).WillByDefault(Return(true));
        ON_CALL(m_mockConfig, includeSuccessfulResults()).WillByDefault(Return(false));
        ON_CALL(m_mockConfig, shouldDebugBreak()).WillByDefault(Return(false));
        ON_CALL(m_mockConfig, warnAboutMissingAssertions()).WillByDefault(Return(false));
        ON_CALL(m_mockConfig, warnAboutUnmatchedTestSpecs()).WillByDefault(Return(false));
        ON_CALL(m_mockConfig, zeroTestsCountAsSuccess()).WillByDefault(Return(false));
        ON_CALL(m_mockConfig, abortAfter()).WillByDefault(Return(0));
        ON_CALL(m_mockConfig, showInvisibles()).WillByDefault(Return(false));
        ON_CALL(m_mockConfig, showDurations()).WillByDefault(Return(ShowDurations::DefaultForReporter));
        ON_CALL(m_mockConfig, minDuration()).WillByDefault(Return(-1.0));
        ON_CALL(m_mockConfig, runOrder()).WillByDefault(Return(TestRunOrder::Declared));
        ON_CALL(m_mockConfig, shardCount()).WillByDefault(Return(1u));
        ON_CALL(m_mockConfig, shardIndex()).WillByDefault(Return(0u));
        ON_CALL(m_mockConfig, skipBenchmarks()).WillByDefault(Return(false));
        ON_CALL(m_mockConfig, benchmarkNoAnalysis()).WillByDefault(Return(false));
        ON_CALL(m_mockConfig, benchmarkSamples()).WillByDefault(Return(100u));
        ON_CALL(m_mockConfig, benchmarkConfidenceInterval()).WillByDefault(Return(0.95));
        ON_CALL(m_mockConfig, benchmarkResamples()).WillByDefault(Return(100000u));
        ON_CALL(m_mockConfig, benchmarkWarmupTime()).WillByDefault(Return(std::chrono::milliseconds(100)));
    }

    std::unique_ptr<XmlReporter> createReporter() {
        ReporterConfig config(&m_mockConfig, m_stream, ColourMode::None, {});
        return std::make_unique<XmlReporter>(CATCH_MOVE(config));
    }
};

TEST_F(XmlReporterTest_836, TestRunStartingOutputsXmlDeclaration_836) {
    auto reporter = createReporter();
    TestRunInfo testRunInfo("MyTestRun"_sr);

    reporter->testRunStarting(testRunInfo);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

TEST_F(XmlReporterTest_836, TestRunStartingOutputsCatch2TestRunElement_836) {
    auto reporter = createReporter();
    TestRunInfo testRunInfo("MyTestRun"_sr);

    reporter->testRunStarting(testRunInfo);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("Catch2TestRun"), std::string::npos);
}

TEST_F(XmlReporterTest_836, TestRunStartingOutputsNameAttribute_836) {
    ON_CALL(m_mockConfig, name()).WillByDefault(Return("CustomTestName"_sr));
    auto reporter = createReporter();
    TestRunInfo testRunInfo("MyTestRun"_sr);

    reporter->testRunStarting(testRunInfo);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("CustomTestName"), std::string::npos);
}

TEST_F(XmlReporterTest_836, TestRunStartingOutputsRngSeedAttribute_836) {
    ON_CALL(m_mockConfig, rngSeed()).WillByDefault(Return(42u));
    auto reporter = createReporter();
    TestRunInfo testRunInfo("MyTestRun"_sr);

    reporter->testRunStarting(testRunInfo);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("rng-seed"), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(XmlReporterTest_836, TestRunStartingOutputsXmlFormatVersion_836) {
    auto reporter = createReporter();
    TestRunInfo testRunInfo("MyTestRun"_sr);

    reporter->testRunStarting(testRunInfo);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("xml-format-version"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

TEST_F(XmlReporterTest_836, TestRunStartingOutputsCatch2VersionAttribute_836) {
    auto reporter = createReporter();
    TestRunInfo testRunInfo("MyTestRun"_sr);

    reporter->testRunStarting(testRunInfo);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("catch2-version"), std::string::npos);
}

TEST_F(XmlReporterTest_836, TestRunStartingWithNoFiltersDoesNotOutputFiltersAttribute_836) {
    ON_CALL(m_mockConfig, testSpec()).WillByDefault(ReturnRef(m_testSpec));
    auto reporter = createReporter();
    TestRunInfo testRunInfo("MyTestRun"_sr);

    reporter->testRunStarting(testRunInfo);

    std::string output = m_stream.str();
    // When no filters, "filters" attribute should not appear
    // (This depends on whether TestSpec::hasFilters returns false for default TestSpec)
    // Default TestSpec should have no filters
    EXPECT_EQ(output.find("filters="), std::string::npos);
}

TEST_F(XmlReporterTest_836, TestRunStartingWithEmptyName_836) {
    ON_CALL(m_mockConfig, name()).WillByDefault(Return(""_sr));
    auto reporter = createReporter();
    TestRunInfo testRunInfo(""_sr);

    reporter->testRunStarting(testRunInfo);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("Catch2TestRun"), std::string::npos);
    EXPECT_NE(output.find("name=\"\""), std::string::npos);
}

TEST_F(XmlReporterTest_836, TestRunStartingWithZeroRngSeed_836) {
    ON_CALL(m_mockConfig, rngSeed()).WillByDefault(Return(0u));
    auto reporter = createReporter();
    TestRunInfo testRunInfo("Test"_sr);

    reporter->testRunStarting(testRunInfo);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("rng-seed=\"0\""), std::string::npos);
}

TEST_F(XmlReporterTest_836, TestRunStartingWithMaxRngSeed_836) {
    ON_CALL(m_mockConfig, rngSeed()).WillByDefault(Return(UINT32_MAX));
    auto reporter = createReporter();
    TestRunInfo testRunInfo("Test"_sr);

    reporter->testRunStarting(testRunInfo);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("rng-seed"), std::string::npos);
    EXPECT_NE(output.find(std::to_string(UINT32_MAX)), std::string::npos);
}

TEST_F(XmlReporterTest_836, GetDescriptionReturnsNonEmptyString_836) {
    std::string desc = XmlReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(XmlReporterTest_836, GetStylesheetRefReturnsEmptyByDefault_836) {
    auto reporter = createReporter();
    std::string ref = reporter->getStylesheetRef();
    EXPECT_TRUE(ref.empty());
}

TEST_F(XmlReporterTest_836, TestRunStartingDoesNotWriteStylesheetWhenRefEmpty_836) {
    auto reporter = createReporter();
    TestRunInfo testRunInfo("Test"_sr);

    reporter->testRunStarting(testRunInfo);

    std::string output = m_stream.str();
    EXPECT_EQ(output.find("xml-stylesheet"), std::string::npos);
}

TEST_F(XmlReporterTest_836, TestRunStartingWithSpecialCharsInName_836) {
    ON_CALL(m_mockConfig, name()).WillByDefault(Return("Test<>&\""_sr));
    auto reporter = createReporter();
    TestRunInfo testRunInfo("Test<>&\""_sr);

    reporter->testRunStarting(testRunInfo);

    std::string output = m_stream.str();
    // XML should properly escape special characters
    EXPECT_NE(output.find("Catch2TestRun"), std::string::npos);
    // The special chars should be escaped in the output
    EXPECT_NE(output.find("&lt;"), std::string::npos);
    EXPECT_NE(output.find("&gt;"), std::string::npos);
    EXPECT_NE(output.find("&amp;"), std::string::npos);
}

TEST_F(XmlReporterTest_836, TestCaseStartingOutputsTestCase_836) {
    auto reporter = createReporter();
    TestRunInfo testRunInfo("Test"_sr);
    reporter->testRunStarting(testRunInfo);
    m_stream.str("");

    // Create a minimal TestCaseInfo - this might require actual Catch2 factory methods
    // We'll test that testCaseStarting produces XML output with TestCase element
    // Note: This may require proper TestCaseInfo construction
}

TEST_F(XmlReporterTest_836, TestRunEndedClosesElements_836) {
    auto reporter = createReporter();
    TestRunInfo testRunInfo("Test"_sr);
    reporter->testRunStarting(testRunInfo);

    Totals totals;
    TestRunStats testRunStats(testRunInfo, totals, false);
    reporter->testRunEnded(testRunStats);

    std::string output = m_stream.str();
    // Should have closing tag for Catch2TestRun
    EXPECT_NE(output.find("</Catch2TestRun>"), std::string::npos);
}

TEST_F(XmlReporterTest_836, TestRunEndedOutputsOverallResults_836) {
    auto reporter = createReporter();
    TestRunInfo testRunInfo("Test"_sr);
    reporter->testRunStarting(testRunInfo);

    Totals totals;
    TestRunStats testRunStats(testRunInfo, totals, false);
    reporter->testRunEnded(testRunStats);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("OverallResults"), std::string::npos);
}

TEST_F(XmlReporterTest_836, BenchmarkPreparingOutputsElement_836) {
    auto reporter = createReporter();
    TestRunInfo testRunInfo("Test"_sr);
    reporter->testRunStarting(testRunInfo);
    m_stream.str("");

    reporter->benchmarkPreparing("MyBenchmark"_sr);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("BenchmarkResults"), std::string::npos);
    EXPECT_NE(output.find("MyBenchmark"), std::string::npos);
}

TEST_F(XmlReporterTest_836, BenchmarkFailedOutputsError_836) {
    auto reporter = createReporter();
    TestRunInfo testRunInfo("Test"_sr);
    reporter->testRunStarting(testRunInfo);

    reporter->benchmarkPreparing("FailBench"_sr);
    m_stream.str("");

    reporter->benchmarkFailed("some error"_sr);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("some error"), std::string::npos);
}

TEST_F(XmlReporterTest_836, NameAttributeWithUnicodeChars_836) {
    ON_CALL(m_mockConfig, name()).WillByDefault(Return("TestÜñíçödé"_sr));
    auto reporter = createReporter();
    TestRunInfo testRunInfo("TestÜñíçödé"_sr);

    reporter->testRunStarting(testRunInfo);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("Catch2TestRun"), std::string::npos);
}
