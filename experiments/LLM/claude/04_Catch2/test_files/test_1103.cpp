#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <memory>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_istream.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_test_spec.hpp"
#include "catch2/benchmark/catch_benchmark_stats.hpp"
#include "catch2/catch_tag_alias_autoregistrar.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"

using namespace Catch;

namespace {

// A simple IStream implementation that wraps a stringstream
class StringIStream : public Catch::IStream {
    std::ostringstream m_oss;
public:
    std::ostream& stream() override { return m_oss; }
    std::string str() const { return m_oss.str(); }
};

// A minimal mock config
class MockConfig : public Catch::IConfig {
public:
    bool allowThrows() const override { return true; }
    StringRef name() const override { return "test"_sr; }
    int abortAfter() const override { return -1; }
    bool showInvisibles() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::Never; }
    double minDuration() const override { return -1.0; }
    TestSpec const& testSpec() const override { static TestSpec s; return s; }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override {
        static std::vector<std::string> v;
        return v;
    }
    unsigned int rngSeed() const override { return 0; }
    UseColour colourMode() const override { return UseColour::No; }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> v;
        return v;
    }
    Verbosity verbosity() const override { return Verbosity::Normal; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override {
        return std::chrono::milliseconds(100);
    }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    bool defaultColours() const override { return true; }
};

class XmlReporterTest_1103 : public ::testing::Test {
protected:
    MockConfig config;
    StringIStream* rawStream = nullptr;

    std::unique_ptr<XmlReporter> makeReporter() {
        auto streamPtr = Catch::Detail::make_unique<StringIStream>();
        rawStream = streamPtr.get();
        ReporterConfig reporterConfig(
            &config,
            Catch::Detail::unique_ptr<IStream>(streamPtr.release()),
            ColourMode::None,
            std::map<std::string, std::string>{}
        );
        return std::make_unique<XmlReporter>(CATCH_MOVE(reporterConfig));
    }

    std::string getOutput() const {
        if (rawStream) return rawStream->str();
        return "";
    }
};

} // anonymous namespace

// Test that XmlReporter can be constructed successfully
TEST_F(XmlReporterTest_1103, ConstructionSucceeds_1103) {
    ASSERT_NO_THROW({
        auto reporter = makeReporter();
        ASSERT_NE(reporter, nullptr);
    });
}

// Test that preferences are set correctly after construction
TEST_F(XmlReporterTest_1103, PreferencesSetCorrectly_1103) {
    auto reporter = makeReporter();
    auto prefs = reporter->getPreferences();
    EXPECT_TRUE(prefs.shouldRedirectStdOut);
    EXPECT_TRUE(prefs.shouldReportAllAssertions);
}

// Test getDescription returns a non-empty string
TEST_F(XmlReporterTest_1103, GetDescriptionReturnsNonEmpty_1103) {
    std::string desc = XmlReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test getStylesheetRef returns a string (possibly empty)
TEST_F(XmlReporterTest_1103, GetStylesheetRefReturnsString_1103) {
    auto reporter = makeReporter();
    std::string ref = reporter->getStylesheetRef();
    // The default stylesheet ref may be empty, just verify it doesn't crash
    SUCCEED();
}

// Test testRunStarting produces XML output
TEST_F(XmlReporterTest_1103, TestRunStartingProducesOutput_1103) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("TestRunName"_sr);
    ASSERT_NO_THROW(reporter->testRunStarting(runInfo));
    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
    // Should contain XML-like content
    EXPECT_NE(output.find("<"), std::string::npos);
}

// Test testRunEnded produces XML output
TEST_F(XmlReporterTest_1103, TestRunEndedProducesOutput_1103) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("TestRunName"_sr);
    reporter->testRunStarting(runInfo);

    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    ASSERT_NO_THROW(reporter->testRunEnded(runStats));

    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
}

// Test testCaseStarting does not throw
TEST_F(XmlReporterTest_1103, TestCaseStartingNoThrow_1103) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("TestRun"_sr);
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_sr, {"TestCase"_sr, "[tag]"_sr}, SourceLineInfo("file.cpp", 1)
    );
    ASSERT_NO_THROW(reporter->testCaseStarting(*testCaseInfo));
}

// Test sectionStarting does not throw
TEST_F(XmlReporterTest_1103, SectionStartingNoThrow_1103) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("TestRun"_sr);
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_sr, {"TestCase"_sr, "[tag]"_sr}, SourceLineInfo("file.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "SectionName");
    ASSERT_NO_THROW(reporter->sectionStarting(sectionInfo));
}

// Test assertionStarting does not throw
TEST_F(XmlReporterTest_1103, AssertionStartingNoThrow_1103) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("TestRun"_sr);
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_sr, {"TestCase"_sr, "[tag]"_sr}, SourceLineInfo("file.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    AssertionInfo assertionInfo(
        "test"_sr, SourceLineInfo("file.cpp", 20), ""_sr, ResultDisposition::Normal
    );
    ASSERT_NO_THROW(reporter->assertionStarting(assertionInfo));
}

// Test sectionEnded produces output
TEST_F(XmlReporterTest_1103, SectionEndedProducesOutput_1103) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("TestRun"_sr);
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_sr, {"TestCase"_sr, "[tag]"_sr}, SourceLineInfo("file.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "SectionName");
    reporter->sectionStarting(sectionInfo);

    Counts assertions;
    assertions.passed = 1;
    SectionStats sectionStats(sectionInfo, assertions, 0.5, false);
    ASSERT_NO_THROW(reporter->sectionEnded(sectionStats));
}

// Test testCaseEnded produces output
TEST_F(XmlReporterTest_1103, TestCaseEndedProducesOutput_1103) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("TestRun"_sr);
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_sr, {"TestCase"_sr, "[tag]"_sr}, SourceLineInfo("file.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    Totals totals;
    TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", false);
    ASSERT_NO_THROW(reporter->testCaseEnded(testCaseStats));

    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
}

// Test benchmarkPreparing does not throw
TEST_F(XmlReporterTest_1103, BenchmarkPreparingNoThrow_1103) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("TestRun"_sr);
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_sr, {"TestCase"_sr, "[tag]"_sr}, SourceLineInfo("file.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    ASSERT_NO_THROW(reporter->benchmarkPreparing("BenchmarkName"_sr));
}

// Test benchmarkStarting does not throw
TEST_F(XmlReporterTest_1103, BenchmarkStartingNoThrow_1103) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("TestRun"_sr);
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_sr, {"TestCase"_sr, "[tag]"_sr}, SourceLineInfo("file.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    reporter->benchmarkPreparing("BenchmarkName"_sr);

    BenchmarkInfo benchInfo{"BenchmarkName", 1.0, 100, 1, 1, 1};
    ASSERT_NO_THROW(reporter->benchmarkStarting(benchInfo));
}

// Test benchmarkFailed does not throw
TEST_F(XmlReporterTest_1103, BenchmarkFailedNoThrow_1103) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("TestRun"_sr);
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_sr, {"TestCase"_sr, "[tag]"_sr}, SourceLineInfo("file.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    reporter->benchmarkPreparing("BenchmarkName"_sr);

    ASSERT_NO_THROW(reporter->benchmarkFailed("some error"_sr));
}

// Test full lifecycle: run start -> case start -> section start -> assertion -> section end -> case end -> run end
TEST_F(XmlReporterTest_1103, FullLifecycleProducesValidXml_1103) {
    auto reporter = makeReporter();

    TestRunInfo runInfo("FullLifecycleRun"_sr);
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_sr, {"LifecycleTest"_sr, "[lifecycle]"_sr}, SourceLineInfo("test.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo(SourceLineInfo("test.cpp", 5), "MainSection");
    reporter->sectionStarting(sectionInfo);

    AssertionInfo assertionInfo(
        "x == 1"_sr, SourceLineInfo("test.cpp", 10), ""_sr, ResultDisposition::Normal
    );
    reporter->assertionStarting(assertionInfo);

    // Create a passing assertion result
    AssertionResultData resultData(ResultWas::Ok, LazyExpression(false));
    AssertionResult result(assertionInfo, CATCH_MOVE(resultData));
    std::vector<MessageInfo> messages;
    AssertionStats assertionStats(result, messages, Totals());
    reporter->assertionEnded(assertionStats);

    Counts assertions;
    assertions.passed = 1;
    SectionStats sectionStats(sectionInfo, assertions, 0.1, false);
    reporter->sectionEnded(sectionStats);

    Totals totals;
    totals.assertions.passed = 1;
    TestCaseStats testCaseStats(*testCaseInfo, totals, "", "", false);
    reporter->testCaseEnded(testCaseStats);

    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);

    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
    // Should contain XML declaration or Catch2 XML elements
    EXPECT_NE(output.find("xml"), std::string::npos);
}

// Test listReporters produces output
TEST_F(XmlReporterTest_1103, ListReportersProducesOutput_1103) {
    auto reporter = makeReporter();
    std::vector<ReporterDescription> descriptions;
    descriptions.push_back({"xml", "XML reporter"});
    ASSERT_NO_THROW(reporter->listReporters(descriptions));
    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
}

// Test listReporters with empty list
TEST_F(XmlReporterTest_1103, ListReportersEmptyList_1103) {
    auto reporter = makeReporter();
    std::vector<ReporterDescription> descriptions;
    ASSERT_NO_THROW(reporter->listReporters(descriptions));
}

// Test listTags produces output
TEST_F(XmlReporterTest_1103, ListTagsProducesOutput_1103) {
    auto reporter = makeReporter();
    std::vector<TagInfo> tags;
    ASSERT_NO_THROW(reporter->listTags(tags));
}

// Test listTests produces output
TEST_F(XmlReporterTest_1103, ListTestsProducesOutput_1103) {
    auto reporter = makeReporter();
    std::vector<TestCaseHandle> tests;
    ASSERT_NO_THROW(reporter->listTests(tests));
}

// Test listListeners produces output
TEST_F(XmlReporterTest_1103, ListListenersProducesOutput_1103) {
    auto reporter = makeReporter();
    std::vector<ListenerDescription> descriptions;
    ASSERT_NO_THROW(reporter->listListeners(descriptions));
}

// Test that testRunStarting output contains the run name
TEST_F(XmlReporterTest_1103, TestRunStartingContainsRunName_1103) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("MyUniqueRunName"_sr);
    reporter->testRunStarting(runInfo);
    std::string output = getOutput();
    EXPECT_NE(output.find("MyUniqueRunName"), std::string::npos);
}

// Test that testCaseStarting output contains the test case name
TEST_F(XmlReporterTest_1103, TestCaseStartingContainsName_1103) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("Run"_sr);
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_sr, {"UniqueTestCaseName"_sr, "[tag]"_sr}, SourceLineInfo("file.cpp", 42)
    );
    reporter->testCaseStarting(*testCaseInfo);

    std::string output = getOutput();
    EXPECT_NE(output.find("UniqueTestCaseName"), std::string::npos);
}

// Test multiple sections in sequence
TEST_F(XmlReporterTest_1103, MultipleSectionsInSequence_1103) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("Run"_sr);
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_sr, {"TestCase"_sr, "[tag]"_sr}, SourceLineInfo("file.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    // First section
    SectionInfo section1(SourceLineInfo("file.cpp", 10), "Section1");
    reporter->sectionStarting(section1);
    Counts c1;
    c1.passed = 1;
    SectionStats stats1(section1, c1, 0.1, false);
    reporter->sectionEnded(stats1);

    // Second section
    SectionInfo section2(SourceLineInfo("file.cpp", 20), "Section2");
    reporter->sectionStarting(section2);
    Counts c2;
    c2.passed = 2;
    SectionStats stats2(section2, c2, 0.2, false);
    reporter->sectionEnded(stats2);

    Totals totals;
    TestCaseStats tcStats(*testCaseInfo, totals, "", "", false);
    reporter->testCaseEnded(tcStats);

    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);

    std::string output = getOutput();
    EXPECT_NE(output.find("Section1"), std::string::npos);
    EXPECT_NE(output.find("Section2"), std::string::npos);
}

// Test that a failed assertion produces appropriate output
TEST_F(XmlReporterTest_1103, FailedAssertionProducesOutput_1103) {
    auto reporter = makeReporter();
    TestRunInfo runInfo("Run"_sr);
    reporter->testRunStarting(runInfo);

    auto testCaseInfo = Catch::makeTestCaseInfo(
        ""_sr, {"FailTest"_sr, "[fail]"_sr}, SourceLineInfo("file.cpp", 1)
    );
    reporter->testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 5), "FailSection");
    reporter->sectionStarting(sectionInfo);

    AssertionInfo assertionInfo(
        "x == 2"_sr, SourceLineInfo("file.cpp", 10), ""_sr, ResultDisposition::Normal
    );
    reporter->assertionStarting(assertionInfo);

    AssertionResultData resultData(ResultWas::ExpressionFailed, LazyExpression(false));
    AssertionResult result(assertionInfo, CATCH_MOVE(resultData));
    std::vector<MessageInfo> messages;
    Totals totals;
    totals.assertions.failed = 1;
    AssertionStats assertionStats(result, messages, totals);
    reporter->assertionEnded(assertionStats);

    std::string output = getOutput();
    // Should contain failure-related XML output
    EXPECT_FALSE(output.empty());
}
