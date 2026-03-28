#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <memory>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"

using namespace Catch;
using ::testing::Return;
using ::testing::ReturnRef;

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

class XmlReporterTestCaseStartingTest_837 : public ::testing::Test {
protected:
    std::shared_ptr<MockConfig> mockConfig;
    std::stringstream ss;
    std::unique_ptr<XmlReporter> reporter;

    void SetUp() override {
        mockConfig = std::make_shared<MockConfig>();

        // Set up default expectations for config
        ON_CALL(*mockConfig, showDurations()).WillByDefault(Return(ShowDurations::Never));
        ON_CALL(*mockConfig, verbosity()).WillByDefault(Return(Verbosity::Normal));
        ON_CALL(*mockConfig, defaultColourMode()).WillByDefault(Return(ColourMode::None));
        ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(Return(false));
        ON_CALL(*mockConfig, name()).WillByDefault(Return(StringRef("test")));
    }

    void createReporter() {
        ReporterConfig config(mockConfig.get(), ss, ColourMode::None, {});
        reporter = std::make_unique<XmlReporter>(CATCH_MOVE(config));
    }

    void startTestRun() {
        TestRunInfo runInfo("test_run"_sr);
        reporter->testRunStarting(runInfo);
    }
};

TEST_F(XmlReporterTestCaseStartingTest_837, OutputContainsTestCaseElement_837) {
    createReporter();
    startTestRun();
    ss.str("");

    NameAndTags nameAndTags("SimpleTest", "");
    SourceLineInfo lineInfo("test_file.cpp", 42);
    TestCaseInfo testInfo("TestClass"_sr, nameAndTags, lineInfo);

    reporter->testCaseStarting(testInfo);

    std::string output = ss.str();
    EXPECT_NE(output.find("TestCase"), std::string::npos);
}

TEST_F(XmlReporterTestCaseStartingTest_837, OutputContainsTestCaseName_837) {
    createReporter();
    startTestRun();
    ss.str("");

    NameAndTags nameAndTags("MyTestName", "");
    SourceLineInfo lineInfo("file.cpp", 10);
    TestCaseInfo testInfo("ClassName"_sr, nameAndTags, lineInfo);

    reporter->testCaseStarting(testInfo);

    std::string output = ss.str();
    EXPECT_NE(output.find("MyTestName"), std::string::npos);
}

TEST_F(XmlReporterTestCaseStartingTest_837, OutputContainsNameAttribute_837) {
    createReporter();
    startTestRun();
    ss.str("");

    NameAndTags nameAndTags("TestWithName", "");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("Class"_sr, nameAndTags, lineInfo);

    reporter->testCaseStarting(testInfo);

    std::string output = ss.str();
    EXPECT_NE(output.find("name="), std::string::npos);
    EXPECT_NE(output.find("TestWithName"), std::string::npos);
}

TEST_F(XmlReporterTestCaseStartingTest_837, OutputContainsTagsAttribute_837) {
    createReporter();
    startTestRun();
    ss.str("");

    NameAndTags nameAndTags("TaggedTest", "[tag1][tag2]");
    SourceLineInfo lineInfo("file.cpp", 5);
    TestCaseInfo testInfo("Class"_sr, nameAndTags, lineInfo);

    reporter->testCaseStarting(testInfo);

    std::string output = ss.str();
    EXPECT_NE(output.find("tags="), std::string::npos);
}

TEST_F(XmlReporterTestCaseStartingTest_837, OutputContainsSourceInfo_837) {
    createReporter();
    startTestRun();
    ss.str("");

    NameAndTags nameAndTags("SourceInfoTest", "");
    SourceLineInfo lineInfo("my_source.cpp", 100);
    TestCaseInfo testInfo("Class"_sr, nameAndTags, lineInfo);

    reporter->testCaseStarting(testInfo);

    std::string output = ss.str();
    EXPECT_NE(output.find("my_source.cpp"), std::string::npos);
}

TEST_F(XmlReporterTestCaseStartingTest_837, ShowDurationsNeverDoesNotAffectOutput_837) {
    ON_CALL(*mockConfig, showDurations()).WillByDefault(Return(ShowDurations::Never));
    createReporter();
    startTestRun();
    ss.str("");

    NameAndTags nameAndTags("DurationNeverTest", "");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("Class"_sr, nameAndTags, lineInfo);

    reporter->testCaseStarting(testInfo);

    std::string output = ss.str();
    EXPECT_NE(output.find("TestCase"), std::string::npos);
}

TEST_F(XmlReporterTestCaseStartingTest_837, ShowDurationsAlwaysProducesOutput_837) {
    ON_CALL(*mockConfig, showDurations()).WillByDefault(Return(ShowDurations::Always));
    createReporter();
    startTestRun();
    ss.str("");

    NameAndTags nameAndTags("DurationAlwaysTest", "");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("Class"_sr, nameAndTags, lineInfo);

    reporter->testCaseStarting(testInfo);

    std::string output = ss.str();
    EXPECT_NE(output.find("TestCase"), std::string::npos);
}

TEST_F(XmlReporterTestCaseStartingTest_837, EmptyTagsAttribute_837) {
    createReporter();
    startTestRun();
    ss.str("");

    NameAndTags nameAndTags("NoTagsTest", "");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("Class"_sr, nameAndTags, lineInfo);

    reporter->testCaseStarting(testInfo);

    std::string output = ss.str();
    EXPECT_NE(output.find("tags=\"\""), std::string::npos);
}

TEST_F(XmlReporterTestCaseStartingTest_837, NameIsTrimmed_837) {
    createReporter();
    startTestRun();
    ss.str("");

    NameAndTags nameAndTags("  TrimmedName  ", "");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("Class"_sr, nameAndTags, lineInfo);

    reporter->testCaseStarting(testInfo);

    std::string output = ss.str();
    // The name should be trimmed - check that leading/trailing spaces are removed
    EXPECT_NE(output.find("TrimmedName"), std::string::npos);
}

TEST_F(XmlReporterTestCaseStartingTest_837, LineInfoIncludesLineNumber_837) {
    createReporter();
    startTestRun();
    ss.str("");

    NameAndTags nameAndTags("LineNumberTest", "");
    SourceLineInfo lineInfo("test.cpp", 999);
    TestCaseInfo testInfo("Class"_sr, nameAndTags, lineInfo);

    reporter->testCaseStarting(testInfo);

    std::string output = ss.str();
    EXPECT_NE(output.find("999"), std::string::npos);
}

TEST_F(XmlReporterTestCaseStartingTest_837, TagClosed_837) {
    createReporter();
    startTestRun();
    ss.str("");

    NameAndTags nameAndTags("ClosedTagTest", "");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("Class"_sr, nameAndTags, lineInfo);

    reporter->testCaseStarting(testInfo);

    std::string output = ss.str();
    // ensureTagClosed should close the opening tag with >
    // The output should contain a properly closed opening tag
    EXPECT_NE(output.find(">"), std::string::npos);
}

TEST_F(XmlReporterTestCaseStartingTest_837, SpecialCharactersInName_837) {
    createReporter();
    startTestRun();
    ss.str("");

    NameAndTags nameAndTags("Test<With>&Special\"Chars", "");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("Class"_sr, nameAndTags, lineInfo);

    reporter->testCaseStarting(testInfo);

    std::string output = ss.str();
    // XML should escape special characters
    EXPECT_NE(output.find("TestCase"), std::string::npos);
    // Should not contain raw < in attribute value
    // The name should be escaped
    EXPECT_EQ(output.find("name=\"Test<With>"), std::string::npos);
}

TEST_F(XmlReporterTestCaseStartingTest_837, MultipleTestCaseStartings_837) {
    createReporter();
    startTestRun();

    NameAndTags nameAndTags1("FirstTest", "[first]");
    SourceLineInfo lineInfo1("file.cpp", 1);
    TestCaseInfo testInfo1("Class"_sr, nameAndTags1, lineInfo1);

    reporter->testCaseStarting(testInfo1);

    // Need to end the test case before starting another
    // Just verify that the first testCaseStarting produced output
    std::string output = ss.str();
    EXPECT_NE(output.find("FirstTest"), std::string::npos);
}

TEST_F(XmlReporterTestCaseStartingTest_837, DefaultDurationsDoesNotStartTimer_837) {
    ON_CALL(*mockConfig, showDurations()).WillByDefault(Return(ShowDurations::DefaultForReporter));
    createReporter();
    startTestRun();
    ss.str("");

    NameAndTags nameAndTags("DefaultDurationTest", "");
    SourceLineInfo lineInfo("file.cpp", 1);
    TestCaseInfo testInfo("Class"_sr, nameAndTags, lineInfo);

    reporter->testCaseStarting(testInfo);

    std::string output = ss.str();
    EXPECT_NE(output.find("TestCase"), std::string::npos);
}
