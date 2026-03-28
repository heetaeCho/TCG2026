#include <sstream>
#include <string>
#include <vector>

#include "catch2/reporters/catch_reporter_junit.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_test_spec.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include "catch2/catch_get_random_seed.hpp"

#include <gtest/gtest.h>

using namespace Catch;

namespace {

// Helper to create a minimal IConfig-like object for ReporterConfig
// We need to create a ReporterConfig to instantiate JunitReporter

class FakeConfig : public IConfig {
public:
    bool allowThrows() const override { return true; }
    StringRef name() const override { return "fake"_catch_sr; }
    int abortAfter() const override { return -1; }
    bool showInvisibles() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::DefaultForReporter; }
    double minDuration() const override { return -1.0; }
    TestSpec const& testSpec() const override { return m_testSpec; }
    bool hasTestFilters() const override { return false; }
    std::vector<ReporterSpec> const& getReporterSpecs() const override { return m_reporterSpecs; }
    std::vector<std::string> const& getSeedReporterSpecs() const override { return m_seedSpecs; }
    unsigned int rngSeed() const override { return 0; }
    UseColour colourMode() const override { return UseColour::Auto; }
    std::vector<std::string> const& getTestsOrTags() const override { return m_testsOrTags; }
    Verbosity verbosity() const override { return Verbosity::Normal; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds(100); }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    ColourMode defaultColourMode() const override { return ColourMode::PlatformDefault; }

private:
    TestSpec m_testSpec;
    std::vector<ReporterSpec> m_reporterSpecs;
    std::vector<std::string> m_seedSpecs;
    std::vector<std::string> m_testsOrTags;
};

} // anonymous namespace

class JunitReporterTest_754 : public ::testing::Test {
protected:
    std::stringstream stream;

    Detail::unique_ptr<JunitReporter> createReporter() {
        auto config = Detail::make_unique<FakeConfig>();
        ReporterConfig reporterConfig(config.get(), stream, ColourMode::None, {});
        return Detail::make_unique<JunitReporter>(CATCH_MOVE(reporterConfig));
    }
};

TEST_F(JunitReporterTest_754, GetDescription_ReturnsNonEmptyString_754) {
    std::string desc = JunitReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(JunitReporterTest_754, GetDescription_ContainsJunit_754) {
    std::string desc = JunitReporter::getDescription();
    // The description should mention JUnit or junit in some form
    bool containsJunit = (desc.find("junit") != std::string::npos) ||
                         (desc.find("JUnit") != std::string::npos) ||
                         (desc.find("Junit") != std::string::npos) ||
                         (desc.find("JUNIT") != std::string::npos) ||
                         (desc.find("XML") != std::string::npos) ||
                         (desc.find("xml") != std::string::npos);
    EXPECT_TRUE(containsJunit);
}

TEST_F(JunitReporterTest_754, Construction_DoesNotThrow_754) {
    EXPECT_NO_THROW({
        auto reporter = createReporter();
    });
}

TEST_F(JunitReporterTest_754, TestRunStarting_ProducesXmlOutput_754) {
    auto reporter = createReporter();

    TestRunInfo runInfo("TestGroup");
    EXPECT_NO_THROW(reporter->testRunStarting(runInfo));
}

TEST_F(JunitReporterTest_754, FullRunLifecycle_ProducesValidXml_754) {
    auto config = Detail::make_unique<FakeConfig>();
    IConfig const* configPtr = config.get();
    ReporterConfig reporterConfig(configPtr, stream, ColourMode::None, {});
    JunitReporter reporter(CATCH_MOVE(reporterConfig));

    // Start test run
    TestRunInfo runInfo("TestSuite");
    reporter.testRunStarting(runInfo);

    // Create a simple test case
    auto fakeTestCaseInfo = Detail::make_unique<TestCaseInfo>(
        "testFunction", NameAndTags{"TestCase1", "[tag1]"}, SourceLineInfo("file.cpp", 42));
    
    reporter.testCaseStarting(*fakeTestCaseInfo);

    // Section starting
    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 42), "TestCase1");
    reporter.sectionStarting(sectionInfo);

    // Create assertion result
    AssertionInfo assertionInfo("expression", SourceLineInfo("file.cpp", 43), "macro", ResultDisposition::Normal);
    AssertionResultData resultData(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(assertionInfo, CATCH_MOVE(resultData));
    
    Counts counts;
    counts.passed = 1;
    AssertionStats assertionStats(result, {}, counts);
    reporter.assertionEnded(assertionStats);

    // Section ended
    SectionStats sectionStats(SectionInfo(SourceLineInfo("file.cpp", 42), "TestCase1"),
                               counts, 0.001, false);
    reporter.sectionEnded(sectionStats);

    // Test case ended
    TestCaseStats testCaseStats(*fakeTestCaseInfo, Totals(), "", "", false);
    reporter.testCaseEnded(testCaseStats);

    // Test run ended
    Totals totals;
    totals.assertions.passed = 1;
    totals.testCases.passed = 1;
    TestRunStats testRunStats(runInfo, totals, false);
    reporter.testRunEnded(testRunStats);

    std::string output = stream.str();
    
    // Should contain XML declaration or JUnit elements
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("testsuites"), std::string::npos);
}

TEST_F(JunitReporterTest_754, OutputContainsTestsuitesElement_754) {
    auto config = Detail::make_unique<FakeConfig>();
    IConfig const* configPtr = config.get();
    ReporterConfig reporterConfig(configPtr, stream, ColourMode::None, {});
    JunitReporter reporter(CATCH_MOVE(reporterConfig));

    TestRunInfo runInfo("MySuite");
    reporter.testRunStarting(runInfo);

    auto fakeTestCaseInfo = Detail::make_unique<TestCaseInfo>(
        "testFunc", NameAndTags{"SimpleTest", "[unit]"}, SourceLineInfo("test.cpp", 10));

    reporter.testCaseStarting(*fakeTestCaseInfo);

    SectionInfo sectionInfo(SourceLineInfo("test.cpp", 10), "SimpleTest");
    reporter.sectionStarting(sectionInfo);

    Counts counts;
    counts.passed = 1;
    SectionStats sectionStats(SectionInfo(SourceLineInfo("test.cpp", 10), "SimpleTest"),
                               counts, 0.0, false);
    reporter.sectionEnded(sectionStats);

    TestCaseStats testCaseStats(*fakeTestCaseInfo, Totals(), "", "", false);
    reporter.testCaseEnded(testCaseStats);

    Totals totals;
    totals.testCases.passed = 1;
    TestRunStats testRunStats(runInfo, totals, false);
    reporter.testRunEnded(testRunStats);

    std::string output = stream.str();
    EXPECT_NE(output.find("testsuite"), std::string::npos);
}

TEST_F(JunitReporterTest_754, FailedAssertion_ProducesFailureElement_754) {
    auto config = Detail::make_unique<FakeConfig>();
    IConfig const* configPtr = config.get();
    ReporterConfig reporterConfig(configPtr, stream, ColourMode::None, {});
    JunitReporter reporter(CATCH_MOVE(reporterConfig));

    TestRunInfo runInfo("FailingSuite");
    reporter.testRunStarting(runInfo);

    auto fakeTestCaseInfo = Detail::make_unique<TestCaseInfo>(
        "failingFunc", NameAndTags{"FailingTest", "[fail]"}, SourceLineInfo("fail.cpp", 20));

    reporter.testCaseStarting(*fakeTestCaseInfo);

    SectionInfo sectionInfo(SourceLineInfo("fail.cpp", 20), "FailingTest");
    reporter.sectionStarting(sectionInfo);

    // Create a failed assertion
    AssertionInfo assertionInfo("1 == 2", SourceLineInfo("fail.cpp", 21), "REQUIRE", ResultDisposition::Normal);
    AssertionResultData resultData(ResultWas::ExpressionFailed, LazyExpression(false));
    AssertionResult result(assertionInfo, CATCH_MOVE(resultData));

    Counts counts;
    counts.failed = 1;
    AssertionStats assertionStats(result, {}, counts);
    reporter.assertionEnded(assertionStats);

    SectionStats sectionStats(SectionInfo(SourceLineInfo("fail.cpp", 20), "FailingTest"),
                               counts, 0.0, false);
    reporter.sectionEnded(sectionStats);

    Totals totals;
    totals.assertions.failed = 1;
    totals.testCases.failed = 1;
    TestCaseStats testCaseStats(*fakeTestCaseInfo, totals, "", "", false);
    reporter.testCaseEnded(testCaseStats);

    TestRunStats testRunStats(runInfo, totals, false);
    reporter.testRunEnded(testRunStats);

    std::string output = stream.str();
    EXPECT_FALSE(output.empty());
    // Failed assertions should produce failure elements in JUnit XML
    EXPECT_NE(output.find("failure"), std::string::npos);
}

TEST_F(JunitReporterTest_754, EmptyTestRun_ProducesValidOutput_754) {
    auto config = Detail::make_unique<FakeConfig>();
    IConfig const* configPtr = config.get();
    ReporterConfig reporterConfig(configPtr, stream, ColourMode::None, {});
    JunitReporter reporter(CATCH_MOVE(reporterConfig));

    TestRunInfo runInfo("EmptySuite");
    reporter.testRunStarting(runInfo);

    Totals totals;
    TestRunStats testRunStats(runInfo, totals, false);
    reporter.testRunEnded(testRunStats);

    std::string output = stream.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(JunitReporterTest_754, OutputContainsXmlDeclaration_754) {
    auto config = Detail::make_unique<FakeConfig>();
    IConfig const* configPtr = config.get();
    ReporterConfig reporterConfig(configPtr, stream, ColourMode::None, {});
    JunitReporter reporter(CATCH_MOVE(reporterConfig));

    TestRunInfo runInfo("XmlDeclTest");
    reporter.testRunStarting(runInfo);

    Totals totals;
    TestRunStats testRunStats(runInfo, totals, false);
    reporter.testRunEnded(testRunStats);

    std::string output = stream.str();
    // JUnit reporter should produce XML with proper declaration
    EXPECT_NE(output.find("<?xml"), std::string::npos);
}

TEST_F(JunitReporterTest_754, OutputContainsTestSuiteName_754) {
    auto config = Detail::make_unique<FakeConfig>();
    IConfig const* configPtr = config.get();
    ReporterConfig reporterConfig(configPtr, stream, ColourMode::None, {});
    JunitReporter reporter(CATCH_MOVE(reporterConfig));

    TestRunInfo runInfo("MySpecialSuiteName");
    reporter.testRunStarting(runInfo);

    Totals totals;
    TestRunStats testRunStats(runInfo, totals, false);
    reporter.testRunEnded(testRunStats);

    std::string output = stream.str();
    EXPECT_NE(output.find("MySpecialSuiteName"), std::string::npos);
}

TEST_F(JunitReporterTest_754, MultipleTestCases_AllAppearInOutput_754) {
    auto config = Detail::make_unique<FakeConfig>();
    IConfig const* configPtr = config.get();
    ReporterConfig reporterConfig(configPtr, stream, ColourMode::None, {});
    JunitReporter reporter(CATCH_MOVE(reporterConfig));

    TestRunInfo runInfo("MultiTestSuite");
    reporter.testRunStarting(runInfo);

    // First test case
    auto tc1 = Detail::make_unique<TestCaseInfo>(
        "func1", NameAndTags{"FirstTest", "[a]"}, SourceLineInfo("a.cpp", 1));
    reporter.testCaseStarting(*tc1);
    SectionInfo s1(SourceLineInfo("a.cpp", 1), "FirstTest");
    reporter.sectionStarting(s1);
    Counts c1;
    c1.passed = 1;
    reporter.sectionEnded(SectionStats(s1, c1, 0.0, false));
    Totals t1;
    t1.assertions.passed = 1;
    t1.testCases.passed = 1;
    reporter.testCaseEnded(TestCaseStats(*tc1, t1, "", "", false));

    // Second test case
    auto tc2 = Detail::make_unique<TestCaseInfo>(
        "func2", NameAndTags{"SecondTest", "[b]"}, SourceLineInfo("b.cpp", 1));
    reporter.testCaseStarting(*tc2);
    SectionInfo s2(SourceLineInfo("b.cpp", 1), "SecondTest");
    reporter.sectionStarting(s2);
    Counts c2;
    c2.passed = 1;
    reporter.sectionEnded(SectionStats(s2, c2, 0.0, false));
    Totals t2;
    t2.assertions.passed = 2;
    t2.testCases.passed = 2;
    reporter.testCaseEnded(TestCaseStats(*tc2, t2, "", "", false));

    Totals totalTotals;
    totalTotals.assertions.passed = 2;
    totalTotals.testCases.passed = 2;
    TestRunStats testRunStats(runInfo, totalTotals, false);
    reporter.testRunEnded(testRunStats);

    std::string output = stream.str();
    EXPECT_NE(output.find("FirstTest"), std::string::npos);
    EXPECT_NE(output.find("SecondTest"), std::string::npos);
}

TEST_F(JunitReporterTest_754, TestCaseWithStdout_AppearsInOutput_754) {
    auto config = Detail::make_unique<FakeConfig>();
    IConfig const* configPtr = config.get();
    ReporterConfig reporterConfig(configPtr, stream, ColourMode::None, {});
    JunitReporter reporter(CATCH_MOVE(reporterConfig));

    TestRunInfo runInfo("StdoutSuite");
    reporter.testRunStarting(runInfo);

    auto tc = Detail::make_unique<TestCaseInfo>(
        "stdoutFunc", NameAndTags{"StdoutTest", "[out]"}, SourceLineInfo("out.cpp", 1));
    reporter.testCaseStarting(*tc);
    SectionInfo s(SourceLineInfo("out.cpp", 1), "StdoutTest");
    reporter.sectionStarting(s);
    Counts c;
    c.passed = 1;
    reporter.sectionEnded(SectionStats(s, c, 0.0, false));

    Totals t;
    t.assertions.passed = 1;
    t.testCases.passed = 1;
    reporter.testCaseEnded(TestCaseStats(*tc, t, "hello stdout", "", false));

    TestRunStats testRunStats(runInfo, t, false);
    reporter.testRunEnded(testRunStats);

    std::string output = stream.str();
    // stdout content should appear somewhere in the output
    EXPECT_NE(output.find("hello stdout"), std::string::npos);
}

TEST_F(JunitReporterTest_754, TestCaseWithStderr_AppearsInOutput_754) {
    auto config = Detail::make_unique<FakeConfig>();
    IConfig const* configPtr = config.get();
    ReporterConfig reporterConfig(configPtr, stream, ColourMode::None, {});
    JunitReporter reporter(CATCH_MOVE(reporterConfig));

    TestRunInfo runInfo("StderrSuite");
    reporter.testRunStarting(runInfo);

    auto tc = Detail::make_unique<TestCaseInfo>(
        "stderrFunc", NameAndTags{"StderrTest", "[err]"}, SourceLineInfo("err.cpp", 1));
    reporter.testCaseStarting(*tc);
    SectionInfo s(SourceLineInfo("err.cpp", 1), "StderrTest");
    reporter.sectionStarting(s);
    Counts c;
    c.passed = 1;
    reporter.sectionEnded(SectionStats(s, c, 0.0, false));

    Totals t;
    t.assertions.passed = 1;
    t.testCases.passed = 1;
    reporter.testCaseEnded(TestCaseStats(*tc, t, "", "hello stderr", false));

    TestRunStats testRunStats(runInfo, t, false);
    reporter.testRunEnded(testRunStats);

    std::string output = stream.str();
    EXPECT_NE(output.find("hello stderr"), std::string::npos);
}
