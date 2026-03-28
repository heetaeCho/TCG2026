#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_junit.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_istream.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_test_spec.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

#include <sstream>
#include <string>
#include <map>
#include <vector>

using namespace Catch;

namespace {

// A simple IStream wrapper around a stringstream
class StringStream : public Catch::IStream {
public:
    std::ostream& stream() override { return m_ss; }
    std::stringstream m_ss;
};

// Mock IConfig
class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<ReporterSpec> const&, getReporterSpecs, (), (const, override));
    MOCK_METHOD(RawResultsSpec const&, getRawResultsSpec, (), (const, override));
    MOCK_METHOD(unsigned int, rngSeed, (), (const, override));
    MOCK_METHOD(UseColour, useColour, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
};

class JunitReporterTest_1102 : public ::testing::Test {
protected:
    void SetUp() override {
        m_config = new ::testing::NiceMock<MockConfig>();
        
        // Set up default mock behaviors
        static TestSpec emptySpec;
        static std::vector<ReporterSpec> emptyReporterSpecs;
        
        ON_CALL(*m_config, allowThrows()).WillByDefault(::testing::Return(true));
        ON_CALL(*m_config, name()).WillByDefault(::testing::Return(StringRef("")));
        ON_CALL(*m_config, includeSuccessfulResults()).WillByDefault(::testing::Return(false));
        ON_CALL(*m_config, warnAboutMissingAssertions()).WillByDefault(::testing::Return(false));
        ON_CALL(*m_config, warnAboutUnmatchedTestSpecs()).WillByDefault(::testing::Return(false));
        ON_CALL(*m_config, zeroTestsCountAsSuccess()).WillByDefault(::testing::Return(false));
        ON_CALL(*m_config, abortAfter()).WillByDefault(::testing::Return(0));
        ON_CALL(*m_config, showInvisibles()).WillByDefault(::testing::Return(false));
        ON_CALL(*m_config, showDurations()).WillByDefault(::testing::Return(ShowDurations::Never));
        ON_CALL(*m_config, minDuration()).WillByDefault(::testing::Return(-1.0));
        ON_CALL(*m_config, testSpec()).WillByDefault(::testing::ReturnRef(emptySpec));
        ON_CALL(*m_config, hasTestFilters()).WillByDefault(::testing::Return(false));
        ON_CALL(*m_config, getReporterSpecs()).WillByDefault(::testing::ReturnRef(emptyReporterSpecs));
        ON_CALL(*m_config, rngSeed()).WillByDefault(::testing::Return(0));
        ON_CALL(*m_config, shouldDebugBreak()).WillByDefault(::testing::Return(false));
        ON_CALL(*m_config, benchmarkNoAnalysis()).WillByDefault(::testing::Return(false));
        ON_CALL(*m_config, benchmarkSamples()).WillByDefault(::testing::Return(100));
        ON_CALL(*m_config, benchmarkConfidenceInterval()).WillByDefault(::testing::Return(0.95));
        ON_CALL(*m_config, benchmarkResamples()).WillByDefault(::testing::Return(100000));
        ON_CALL(*m_config, benchmarkWarmupTime()).WillByDefault(::testing::Return(std::chrono::milliseconds(100)));
        ON_CALL(*m_config, shardCount()).WillByDefault(::testing::Return(1));
        ON_CALL(*m_config, shardIndex()).WillByDefault(::testing::Return(0));
    }

    void TearDown() override {
        // m_config lifetime managed externally if reporter doesn't own it
    }

    std::unique_ptr<JunitReporter> createReporter() {
        auto stream = Detail::make_unique<StringStream>();
        m_streamPtr = stream.get();
        ReporterConfig config(m_config, Detail::unique_ptr<IStream>(stream.release()), ColourMode::None, {});
        return std::make_unique<JunitReporter>(CATCH_MOVE(config));
    }

    ::testing::NiceMock<MockConfig>* m_config = nullptr;
    StringStream* m_streamPtr = nullptr;
};

// Test that JunitReporter can be constructed
TEST_F(JunitReporterTest_1102, Construction_1102) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
}

// Test that preferences are set correctly: shouldRedirectStdOut = true
TEST_F(JunitReporterTest_1102, PreferencesShouldRedirectStdOut_1102) {
    auto reporter = createReporter();
    auto const& prefs = reporter->getPreferences();
    EXPECT_TRUE(prefs.shouldRedirectStdOut);
}

// Test that preferences are set correctly: shouldReportAllAssertions = false
TEST_F(JunitReporterTest_1102, PreferencesShouldNotReportAllAssertions_1102) {
    auto reporter = createReporter();
    auto const& prefs = reporter->getPreferences();
    EXPECT_FALSE(prefs.shouldReportAllAssertions);
}

// Test that getDescription returns a non-empty string
TEST_F(JunitReporterTest_1102, GetDescriptionReturnsNonEmpty_1102) {
    std::string desc = JunitReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test testRunStarting doesn't crash
TEST_F(JunitReporterTest_1102, TestRunStarting_1102) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    EXPECT_NO_THROW(reporter->testRunStarting(runInfo));
}

// Test testCaseStarting doesn't crash
TEST_F(JunitReporterTest_1102, TestCaseStarting_1102) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto testCaseInfo = Detail::make_unique<TestCaseInfo>(
        ""_catch_sr, SourceLineInfo("file.cpp", 1),
        ""_catch_sr, std::vector<Tag>{});
    
    EXPECT_NO_THROW(reporter->testCaseStarting(*testCaseInfo));
}

// Test full lifecycle: run start -> case start -> case end -> run end
TEST_F(JunitReporterTest_1102, FullLifecycle_1102) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto testCaseInfo = Detail::make_unique<TestCaseInfo>(
        "TestName"_catch_sr, SourceLineInfo("file.cpp", 1),
        "TestName"_catch_sr, std::vector<Tag>{});
    
    reporter->testCaseStarting(*testCaseInfo);
    
    Totals totals;
    TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", true);
    reporter->testCaseEnded(testCaseStats);
    
    Totals runTotals;
    TestRunStats testRunStats(runInfo, runTotals, false);
    reporter->testRunEnded(testRunStats);
    
    // After full lifecycle, check output contains some XML
    std::string output = m_streamPtr->m_ss.str();
    EXPECT_FALSE(output.empty());
}

// Test that output contains XML-like content after run ends
TEST_F(JunitReporterTest_1102, OutputContainsXml_1102) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("my_test_run");
    reporter->testRunStarting(runInfo);
    
    Totals runTotals;
    TestRunStats testRunStats(runInfo, runTotals, false);
    reporter->testRunEnded(testRunStats);
    
    std::string output = m_streamPtr->m_ss.str();
    // JUnit output should contain XML declaration or testsuites element
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

// Test that output contains testsuite element
TEST_F(JunitReporterTest_1102, OutputContainsTestsuite_1102) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("my_test_run");
    reporter->testRunStarting(runInfo);
    
    Totals runTotals;
    TestRunStats testRunStats(runInfo, runTotals, false);
    reporter->testRunEnded(testRunStats);
    
    std::string output = m_streamPtr->m_ss.str();
    EXPECT_NE(output.find("testsuite"), std::string::npos);
}

// Test with a test case that has a section
TEST_F(JunitReporterTest_1102, TestCaseWithSection_1102) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto testCaseInfo = Detail::make_unique<TestCaseInfo>(
        "TestWithSection"_catch_sr, SourceLineInfo("file.cpp", 10),
        "TestWithSection"_catch_sr, std::vector<Tag>{});
    
    reporter->testCaseStarting(*testCaseInfo);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 12), "Section1");
    reporter->sectionStarting(sectionInfo);
    
    Counts assertions;
    assertions.passed = 1;
    SectionStats sectionStats(sectionInfo, assertions, 0.1, false);
    reporter->sectionEnded(sectionStats);
    
    Totals totals;
    totals.assertions.passed = 1;
    TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", true);
    reporter->testCaseEnded(testCaseStats);
    
    Totals runTotals;
    runTotals.assertions.passed = 1;
    TestRunStats testRunStats(runInfo, runTotals, false);
    reporter->testRunEnded(testRunStats);
    
    std::string output = m_streamPtr->m_ss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("testcase"), std::string::npos);
}

// Test that the reporter handles noMatchingTestCases without crashing
TEST_F(JunitReporterTest_1102, NoMatchingTestCases_1102) {
    auto reporter = createReporter();
    EXPECT_NO_THROW(reporter->noMatchingTestCases("some_spec"_catch_sr));
}

// Test that the reporter handles reportInvalidTestSpec without crashing
TEST_F(JunitReporterTest_1102, ReportInvalidTestSpec_1102) {
    auto reporter = createReporter();
    EXPECT_NO_THROW(reporter->reportInvalidTestSpec("bad_spec"_catch_sr));
}

// Test that the reporter handles benchmarkPreparing without crashing
TEST_F(JunitReporterTest_1102, BenchmarkPreparing_1102) {
    auto reporter = createReporter();
    EXPECT_NO_THROW(reporter->benchmarkPreparing("bench"_catch_sr));
}

// Test that the reporter handles skipTest without crashing
TEST_F(JunitReporterTest_1102, SkipTest_1102) {
    auto reporter = createReporter();
    auto testCaseInfo = Detail::make_unique<TestCaseInfo>(
        "SkippedTest"_catch_sr, SourceLineInfo("file.cpp", 1),
        "SkippedTest"_catch_sr, std::vector<Tag>{});
    EXPECT_NO_THROW(reporter->skipTest(*testCaseInfo));
}

// Test that the reporter handles fatalErrorEncountered without crashing
TEST_F(JunitReporterTest_1102, FatalErrorEncountered_1102) {
    auto reporter = createReporter();
    EXPECT_NO_THROW(reporter->fatalErrorEncountered("fatal error"_catch_sr));
}

// Test with failed assertions
TEST_F(JunitReporterTest_1102, FailedAssertion_1102) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("test_run");
    reporter->testRunStarting(runInfo);
    
    auto testCaseInfo = Detail::make_unique<TestCaseInfo>(
        "FailingTest"_catch_sr, SourceLineInfo("file.cpp", 5),
        "FailingTest"_catch_sr, std::vector<Tag>{});
    
    reporter->testCaseStarting(*testCaseInfo);
    
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 5), "FailingTest");
    reporter->sectionStarting(sectionInfo);
    
    AssertionResultData resultData(ResultWas::ExpressionFailed, LazyExpression(false));
    resultData.message = "test failed";
    AssertionInfo assertionInfo("check", SourceLineInfo("file.cpp", 6), ""_catch_sr, ResultDisposition::Normal);
    AssertionResult result(assertionInfo, CATCH_MOVE(resultData));
    
    Counts assertions;
    assertions.failed = 1;
    AssertionStats assertionStats(result, std::vector<MessageInfo>{}, Totals{});
    reporter->assertionEnded(assertionStats);
    
    SectionStats sectionStats(sectionInfo, assertions, 0.1, false);
    reporter->sectionEnded(sectionStats);
    
    Totals totals;
    totals.assertions.failed = 1;
    TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", false);
    reporter->testCaseEnded(testCaseStats);
    
    Totals runTotals;
    runTotals.assertions.failed = 1;
    TestRunStats testRunStats(runInfo, runTotals, false);
    reporter->testRunEnded(testRunStats);
    
    std::string output = m_streamPtr->m_ss.str();
    EXPECT_FALSE(output.empty());
    // Failed tests should produce failure elements
    EXPECT_NE(output.find("failure"), std::string::npos);
}

// Test with multiple test cases
TEST_F(JunitReporterTest_1102, MultipleTestCases_1102) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("multi_test_run");
    reporter->testRunStarting(runInfo);
    
    for (int i = 0; i < 3; ++i) {
        std::string name = "Test" + std::to_string(i);
        auto testCaseInfo = Detail::make_unique<TestCaseInfo>(
            StringRef(name), SourceLineInfo("file.cpp", i + 1),
            StringRef(name), std::vector<Tag>{});
        
        reporter->testCaseStarting(*testCaseInfo);
        
        Totals totals;
        totals.assertions.passed = 1;
        TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", true);
        reporter->testCaseEnded(testCaseStats);
    }
    
    Totals runTotals;
    runTotals.assertions.passed = 3;
    runTotals.testCases.passed = 3;
    TestRunStats testRunStats(runInfo, runTotals, false);
    reporter->testRunEnded(testRunStats);
    
    std::string output = m_streamPtr->m_ss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("testcase"), std::string::npos);
}

// Test empty test run (no test cases)
TEST_F(JunitReporterTest_1102, EmptyTestRun_1102) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("empty_run");
    reporter->testRunStarting(runInfo);
    
    Totals runTotals;
    TestRunStats testRunStats(runInfo, runTotals, false);
    reporter->testRunEnded(testRunStats);
    
    std::string output = m_streamPtr->m_ss.str();
    EXPECT_FALSE(output.empty());
    // Should still produce valid XML structure
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

// Test that the run name appears in output
TEST_F(JunitReporterTest_1102, RunNameAppearsInOutput_1102) {
    auto reporter = createReporter();
    
    TestRunInfo runInfo("UniqueRunName42");
    reporter->testRunStarting(runInfo);
    
    Totals runTotals;
    TestRunStats testRunStats(runInfo, runTotals, false);
    reporter->testRunEnded(testRunStats);
    
    std::string output = m_streamPtr->m_ss.str();
    EXPECT_NE(output.find("UniqueRunName42"), std::string::npos);
}

} // anonymous namespace
