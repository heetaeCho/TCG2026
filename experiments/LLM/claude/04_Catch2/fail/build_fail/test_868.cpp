#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <memory>

#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_jsonwriter.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_iconfig.hpp"
#include "catch2/catch_session.hpp"

using namespace Catch;

namespace {

// Helper to create a ReporterConfig with a given stream
class JsonReporterTest_868 : public ::testing::Test {
protected:
    std::stringstream m_stream;
    std::unique_ptr<JsonReporter> m_reporter;

    void SetUp() override {
        // We need to create a valid ReporterConfig
        // This typically requires an IConfig and an ostream
    }

    // Helper to create a TestCaseInfo
    static std::unique_ptr<TestCaseInfo> makeTestCaseInfo(
        const std::string& name,
        const std::string& className = "",
        const SourceLineInfo& lineInfo = SourceLineInfo("test_file.cpp", 42)) {
        NameAndTags nameAndTags(name, "");
        return std::make_unique<TestCaseInfo>(
            StringRef(className), nameAndTags, lineInfo);
    }

    // Helper to create a TestCaseInfo with tags
    static std::unique_ptr<TestCaseInfo> makeTestCaseInfoWithTags(
        const std::string& name,
        const std::string& tags,
        const std::string& className = "",
        const SourceLineInfo& lineInfo = SourceLineInfo("test_file.cpp", 42)) {
        NameAndTags nameAndTags(name, tags);
        return std::make_unique<TestCaseInfo>(
            StringRef(className), nameAndTags, lineInfo);
    }

    JsonReporter& createReporter() {
        auto config = Catch::makeTestConfig();
        auto reporterConfig = ReporterConfig(config.get(), m_stream, Catch::ColourMode::None, {});
        m_reporter = std::make_unique<JsonReporter>(std::move(reporterConfig));
        return *m_reporter;
    }
};

} // anonymous namespace

// Test that getDescription returns a non-empty string
TEST_F(JsonReporterTest_868, GetDescription_ReturnsNonEmpty_868) {
    std::string desc = JsonReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test basic test run lifecycle produces valid JSON structure
TEST_F(JsonReporterTest_868, TestRunLifecycle_ProducesJsonOutput_868) {
    auto& reporter = createReporter();

    TestRunInfo runInfo("test_group"_sr);
    reporter.testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("SimpleTest");
    reporter.testCaseStarting(*tcInfo);

    // Create minimal test case stats to end the test case
    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter.testCaseEnded(tcStats);

    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);

    std::string output = m_stream.str();
    EXPECT_FALSE(output.empty());
}

// Test that testCaseStarting writes the test name into output
TEST_F(JsonReporterTest_868, TestCaseStarting_WritesTestName_868) {
    auto& reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("MyUniqueTestName");
    reporter.testCaseStarting(*tcInfo);

    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter.testCaseEnded(tcStats);

    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("MyUniqueTestName"), std::string::npos);
}

// Test that testCaseStarting writes source info
TEST_F(JsonReporterTest_868, TestCaseStarting_WritesSourceInfo_868) {
    auto& reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    SourceLineInfo lineInfo("my_source_file.cpp", 99);
    NameAndTags nameAndTags("TestWithSourceInfo", "");
    auto tcInfo = std::make_unique<TestCaseInfo>(""_sr, nameAndTags, lineInfo);
    reporter.testCaseStarting(*tcInfo);

    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter.testCaseEnded(tcStats);

    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("my_source_file.cpp"), std::string::npos);
}

// Test that testCaseStarting with tags writes them
TEST_F(JsonReporterTest_868, TestCaseStarting_WritesTags_868) {
    auto& reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfoWithTags("TaggedTest", "[tag1][tag2]");
    reporter.testCaseStarting(*tcInfo);

    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter.testCaseEnded(tcStats);

    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("tag1"), std::string::npos);
    EXPECT_NE(output.find("tag2"), std::string::npos);
}

// Test multiple test cases in a single run
TEST_F(JsonReporterTest_868, MultipleTestCases_AllNamesAppear_868) {
    auto& reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto tcInfo1 = makeTestCaseInfo("FirstTest");
    reporter.testCaseStarting(*tcInfo1);
    Totals totals1;
    TestCaseStats tcStats1(*tcInfo1, totals1, "", "", false);
    reporter.testCaseEnded(tcStats1);

    auto tcInfo2 = makeTestCaseInfo("SecondTest");
    reporter.testCaseStarting(*tcInfo2);
    Totals totals2;
    TestCaseStats tcStats2(*tcInfo2, totals2, "", "", false);
    reporter.testCaseEnded(tcStats2);

    TestRunStats runStats(runInfo, totals2, false);
    reporter.testRunEnded(runStats);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("FirstTest"), std::string::npos);
    EXPECT_NE(output.find("SecondTest"), std::string::npos);
}

// Test that output contains test-info key
TEST_F(JsonReporterTest_868, TestCaseStarting_ContainsTestInfoKey_868) {
    auto& reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("InfoKeyTest");
    reporter.testCaseStarting(*tcInfo);

    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter.testCaseEnded(tcStats);

    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("test-info"), std::string::npos);
}

// Test that output contains "name" key within test-info
TEST_F(JsonReporterTest_868, TestCaseStarting_ContainsNameKey_868) {
    auto& reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("NameKeyTest");
    reporter.testCaseStarting(*tcInfo);

    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter.testCaseEnded(tcStats);

    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("\"name\""), std::string::npos);
}

// Test that output contains "runs" array key
TEST_F(JsonReporterTest_868, TestCaseStarting_ContainsRunsKey_868) {
    auto& reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("RunsKeyTest");
    reporter.testCaseStarting(*tcInfo);

    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter.testCaseEnded(tcStats);

    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("runs"), std::string::npos);
}

// Test that output contains "tags" key
TEST_F(JsonReporterTest_868, TestCaseStarting_ContainsTagsKey_868) {
    auto& reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("TagsKeyTest");
    reporter.testCaseStarting(*tcInfo);

    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter.testCaseEnded(tcStats);

    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("tags"), std::string::npos);
}

// Test that output contains "properties" key
TEST_F(JsonReporterTest_868, TestCaseStarting_ContainsPropertiesKey_868) {
    auto& reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("PropertiesKeyTest");
    reporter.testCaseStarting(*tcInfo);

    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter.testCaseEnded(tcStats);

    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("properties"), std::string::npos);
}

// Test empty test case name
TEST_F(JsonReporterTest_868, TestCaseStarting_EmptyName_868) {
    auto& reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    // Empty name should result in a default name being generated
    NameAndTags nameAndTags("", "");
    SourceLineInfo lineInfo("file.cpp", 1);
    auto tcInfo = std::make_unique<TestCaseInfo>(""_sr, nameAndTags, lineInfo);
    reporter.testCaseStarting(*tcInfo);

    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter.testCaseEnded(tcStats);

    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);

    std::string output = m_stream.str();
    // Should still produce valid output with test-info
    EXPECT_NE(output.find("test-info"), std::string::npos);
}

// Test that test-cases array exists in output
TEST_F(JsonReporterTest_868, TestRunProducesTestCasesArray_868) {
    auto& reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("ArrayTest");
    reporter.testCaseStarting(*tcInfo);

    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter.testCaseEnded(tcStats);

    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("test-cases"), std::string::npos);
}

// Test with hidden tag
TEST_F(JsonReporterTest_868, TestCaseStarting_HiddenTag_868) {
    auto& reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfoWithTags("HiddenTest", "[.][hidden]");
    reporter.testCaseStarting(*tcInfo);

    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter.testCaseEnded(tcStats);

    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("HiddenTest"), std::string::npos);
}

// Test section within a test case
TEST_F(JsonReporterTest_868, SectionStartingEnding_868) {
    auto& reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo("SectionTest");
    reporter.testCaseStarting(*tcInfo);

    uint64_t partialIndex = 0;
    reporter.testCasePartialStarting(*tcInfo, partialIndex);

    SectionInfo sectionInfo("file.cpp", 10, "MySection");
    reporter.sectionStarting(sectionInfo);

    Counts counts;
    SectionStats sectionStats(sectionInfo, counts, 0.0, false);
    reporter.sectionEnded(sectionStats);

    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter.testCasePartialEnded(tcStats, partialIndex);
    reporter.testCaseEnded(tcStats);

    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);

    std::string output = m_stream.str();
    EXPECT_FALSE(output.empty());
}

// Test line number appears in output
TEST_F(JsonReporterTest_868, TestCaseStarting_LineNumberInOutput_868) {
    auto& reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    SourceLineInfo lineInfo("unique_file.cpp", 12345);
    NameAndTags nameAndTags("LineNumberTest", "");
    auto tcInfo = std::make_unique<TestCaseInfo>(""_sr, nameAndTags, lineInfo);
    reporter.testCaseStarting(*tcInfo);

    Totals totals;
    TestCaseStats tcStats(*tcInfo, totals, "", "", false);
    reporter.testCaseEnded(tcStats);

    TestRunStats runStats(runInfo, totals, false);
    reporter.testRunEnded(runStats);

    std::string output = m_stream.str();
    EXPECT_NE(output.find("12345"), std::string::npos);
}
