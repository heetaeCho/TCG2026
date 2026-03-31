#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/internal/catch_test_spec.hpp"

using namespace Catch;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::_;

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

class XmlReporterSectionEndedTest_840 : public ::testing::Test {
protected:
    std::stringstream ss;
    MockConfig* mockConfig;
    std::vector<std::string> emptyVec;
    TestSpec testSpec;
    std::vector<std::string> sectionsToRun;

    void SetUp() override {
        mockConfig = new MockConfig();
        
        ON_CALL(*mockConfig, allowThrows()).WillByDefault(Return(true));
        ON_CALL(*mockConfig, name()).WillByDefault(Return(StringRef("")));
        ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(Return(false));
        ON_CALL(*mockConfig, shouldDebugBreak()).WillByDefault(Return(false));
        ON_CALL(*mockConfig, warnAboutMissingAssertions()).WillByDefault(Return(false));
        ON_CALL(*mockConfig, warnAboutUnmatchedTestSpecs()).WillByDefault(Return(false));
        ON_CALL(*mockConfig, zeroTestsCountAsSuccess()).WillByDefault(Return(false));
        ON_CALL(*mockConfig, abortAfter()).WillByDefault(Return(0));
        ON_CALL(*mockConfig, showInvisibles()).WillByDefault(Return(false));
        ON_CALL(*mockConfig, showDurations()).WillByDefault(Return(ShowDurations::Never));
        ON_CALL(*mockConfig, minDuration()).WillByDefault(Return(0.0));
        ON_CALL(*mockConfig, testSpec()).WillByDefault(ReturnRef(testSpec));
        ON_CALL(*mockConfig, hasTestFilters()).WillByDefault(Return(false));
        ON_CALL(*mockConfig, getTestsOrTags()).WillByDefault(ReturnRef(emptyVec));
        ON_CALL(*mockConfig, runOrder()).WillByDefault(Return(TestRunOrder::Declared));
        ON_CALL(*mockConfig, rngSeed()).WillByDefault(Return(0));
        ON_CALL(*mockConfig, shardCount()).WillByDefault(Return(1));
        ON_CALL(*mockConfig, shardIndex()).WillByDefault(Return(0));
        ON_CALL(*mockConfig, defaultColourMode()).WillByDefault(Return(ColourMode::None));
        ON_CALL(*mockConfig, getSectionsToRun()).WillByDefault(ReturnRef(sectionsToRun));
        ON_CALL(*mockConfig, verbosity()).WillByDefault(Return(Verbosity::Normal));
        ON_CALL(*mockConfig, skipBenchmarks()).WillByDefault(Return(false));
        ON_CALL(*mockConfig, benchmarkNoAnalysis()).WillByDefault(Return(false));
        ON_CALL(*mockConfig, benchmarkSamples()).WillByDefault(Return(100));
        ON_CALL(*mockConfig, benchmarkConfidenceInterval()).WillByDefault(Return(0.95));
        ON_CALL(*mockConfig, benchmarkResamples()).WillByDefault(Return(100000));
        ON_CALL(*mockConfig, benchmarkWarmupTime()).WillByDefault(Return(std::chrono::milliseconds(100)));
    }

    std::unique_ptr<XmlReporter> createReporter() {
        ReporterConfig config(mockConfig, ss, ColourMode::None, {});
        return std::make_unique<XmlReporter>(CATCH_MOVE(config));
    }

    void startTestRun(XmlReporter& reporter) {
        TestRunInfo runInfo("test_run"_sr);
        reporter.testRunStarting(runInfo);
    }

    void startTestCase(XmlReporter& reporter) {
        auto testCaseInfo = Catch::makeTestCaseInfo(
            "test_class", {"test_name", "[tag]"}, {"file.cpp", 1});
        reporter.testCaseStarting(*testCaseInfo);
    }

    SectionStats makeSectionStats(uint64_t passed, uint64_t failed,
                                   uint64_t failedButOk, uint64_t skipped,
                                   double duration, bool missingAssertions = false) {
        Counts assertions;
        assertions.passed = passed;
        assertions.failed = failed;
        assertions.failedButOk = failedButOk;
        assertions.skipped = skipped;
        SectionInfo sectionInfo("file.cpp", 1, "test_section");
        return SectionStats(CATCH_MOVE(sectionInfo), assertions, duration, missingAssertions);
    }
};

TEST_F(XmlReporterSectionEndedTest_840, SectionEndedAtDepthZero_NoOverallResults_840) {
    auto reporter = createReporter();
    startTestRun(*reporter);
    startTestCase(*reporter);

    SectionInfo si("file.cpp", 1, "section1");
    reporter->sectionStarting(si);

    auto stats = makeSectionStats(5, 0, 0, 0, 1.0);
    ss.str("");
    reporter->sectionEnded(stats);

    std::string output = ss.str();
    // At depth 0 after decrement, no OverallResults should be written
    // (m_sectionDepth was 1, decremented to 0, so condition > 0 is false)
    EXPECT_EQ(output.find("OverallResults"), std::string::npos);
}

TEST_F(XmlReporterSectionEndedTest_840, SectionEndedAtDepthGreaterThanZero_WritesOverallResults_840) {
    auto reporter = createReporter();
    startTestRun(*reporter);
    startTestCase(*reporter);

    SectionInfo si1("file.cpp", 1, "outer_section");
    reporter->sectionStarting(si1);
    SectionInfo si2("file.cpp", 2, "inner_section");
    reporter->sectionStarting(si2);

    auto stats = makeSectionStats(10, 2, 1, 0, 2.5);
    ss.str("");
    reporter->sectionEnded(stats);

    std::string output = ss.str();
    EXPECT_NE(output.find("OverallResults"), std::string::npos);
    EXPECT_NE(output.find("successes=\"10\""), std::string::npos);
    EXPECT_NE(output.find("failures=\"2\""), std::string::npos);
    EXPECT_NE(output.find("expectedFailures=\"1\""), std::string::npos);
}

TEST_F(XmlReporterSectionEndedTest_840, SectionEndedWritesSkippedTrue_840) {
    auto reporter = createReporter();
    startTestRun(*reporter);
    startTestCase(*reporter);

    SectionInfo si1("file.cpp", 1, "outer");
    reporter->sectionStarting(si1);
    SectionInfo si2("file.cpp", 2, "inner");
    reporter->sectionStarting(si2);

    auto stats = makeSectionStats(0, 0, 0, 3, 0.0);
    ss.str("");
    reporter->sectionEnded(stats);

    std::string output = ss.str();
    EXPECT_NE(output.find("skipped=\"true\""), std::string::npos);
}

TEST_F(XmlReporterSectionEndedTest_840, SectionEndedWritesSkippedFalse_840) {
    auto reporter = createReporter();
    startTestRun(*reporter);
    startTestCase(*reporter);

    SectionInfo si1("file.cpp", 1, "outer");
    reporter->sectionStarting(si1);
    SectionInfo si2("file.cpp", 2, "inner");
    reporter->sectionStarting(si2);

    auto stats = makeSectionStats(5, 0, 0, 0, 0.0);
    ss.str("");
    reporter->sectionEnded(stats);

    std::string output = ss.str();
    EXPECT_NE(output.find("skipped=\"false\""), std::string::npos);
}

TEST_F(XmlReporterSectionEndedTest_840, SectionEndedShowDurationsAlways_WritesDuration_840) {
    ON_CALL(*mockConfig, showDurations()).WillByDefault(Return(ShowDurations::Always));

    auto reporter = createReporter();
    startTestRun(*reporter);
    startTestCase(*reporter);

    SectionInfo si1("file.cpp", 1, "outer");
    reporter->sectionStarting(si1);
    SectionInfo si2("file.cpp", 2, "inner");
    reporter->sectionStarting(si2);

    auto stats = makeSectionStats(1, 0, 0, 0, 3.14);
    ss.str("");
    reporter->sectionEnded(stats);

    std::string output = ss.str();
    EXPECT_NE(output.find("durationInSeconds"), std::string::npos);
}

TEST_F(XmlReporterSectionEndedTest_840, SectionEndedShowDurationsNever_NoDuration_840) {
    ON_CALL(*mockConfig, showDurations()).WillByDefault(Return(ShowDurations::Never));

    auto reporter = createReporter();
    startTestRun(*reporter);
    startTestCase(*reporter);

    SectionInfo si1("file.cpp", 1, "outer");
    reporter->sectionStarting(si1);
    SectionInfo si2("file.cpp", 2, "inner");
    reporter->sectionStarting(si2);

    auto stats = makeSectionStats(1, 0, 0, 0, 3.14);
    ss.str("");
    reporter->sectionEnded(stats);

    std::string output = ss.str();
    EXPECT_EQ(output.find("durationInSeconds"), std::string::npos);
}

TEST_F(XmlReporterSectionEndedTest_840, SectionEndedShowDurationsDefault_NoDuration_840) {
    ON_CALL(*mockConfig, showDurations()).WillByDefault(Return(ShowDurations::DefaultForReporter));

    auto reporter = createReporter();
    startTestRun(*reporter);
    startTestCase(*reporter);

    SectionInfo si1("file.cpp", 1, "outer");
    reporter->sectionStarting(si1);
    SectionInfo si2("file.cpp", 2, "inner");
    reporter->sectionStarting(si2);

    auto stats = makeSectionStats(1, 0, 0, 0, 5.0);
    ss.str("");
    reporter->sectionEnded(stats);

    std::string output = ss.str();
    EXPECT_EQ(output.find("durationInSeconds"), std::string::npos);
}

TEST_F(XmlReporterSectionEndedTest_840, SectionEndedZeroCounts_840) {
    auto reporter = createReporter();
    startTestRun(*reporter);
    startTestCase(*reporter);

    SectionInfo si1("file.cpp", 1, "outer");
    reporter->sectionStarting(si1);
    SectionInfo si2("file.cpp", 2, "inner");
    reporter->sectionStarting(si2);

    auto stats = makeSectionStats(0, 0, 0, 0, 0.0);
    ss.str("");
    reporter->sectionEnded(stats);

    std::string output = ss.str();
    EXPECT_NE(output.find("successes=\"0\""), std::string::npos);
    EXPECT_NE(output.find("failures=\"0\""), std::string::npos);
    EXPECT_NE(output.find("expectedFailures=\"0\""), std::string::npos);
    EXPECT_NE(output.find("skipped=\"false\""), std::string::npos);
}

TEST_F(XmlReporterSectionEndedTest_840, SectionEndedTripleNested_WritesOverallResultsForInnerTwo_840) {
    auto reporter = createReporter();
    startTestRun(*reporter);
    startTestCase(*reporter);

    SectionInfo si1("file.cpp", 1, "level1");
    reporter->sectionStarting(si1);
    SectionInfo si2("file.cpp", 2, "level2");
    reporter->sectionStarting(si2);
    SectionInfo si3("file.cpp", 3, "level3");
    reporter->sectionStarting(si3);

    // End level3 - depth was 3, becomes 2, > 0 so writes OverallResults
    auto stats3 = makeSectionStats(1, 0, 0, 0, 0.1);
    ss.str("");
    reporter->sectionEnded(stats3);
    std::string output3 = ss.str();
    EXPECT_NE(output3.find("OverallResults"), std::string::npos);

    // End level2 - depth was 2, becomes 1, > 0 so writes OverallResults
    auto stats2 = makeSectionStats(2, 1, 0, 0, 0.2);
    ss.str("");
    reporter->sectionEnded(stats2);
    std::string output2 = ss.str();
    EXPECT_NE(output2.find("OverallResults"), std::string::npos);

    // End level1 - depth was 1, becomes 0, no OverallResults
    auto stats1 = makeSectionStats(3, 1, 0, 0, 0.3);
    ss.str("");
    reporter->sectionEnded(stats1);
    std::string output1 = ss.str();
    EXPECT_EQ(output1.find("OverallResults"), std::string::npos);
}

TEST_F(XmlReporterSectionEndedTest_840, SectionEndedLargeCounts_840) {
    auto reporter = createReporter();
    startTestRun(*reporter);
    startTestCase(*reporter);

    SectionInfo si1("file.cpp", 1, "outer");
    reporter->sectionStarting(si1);
    SectionInfo si2("file.cpp", 2, "inner");
    reporter->sectionStarting(si2);

    auto stats = makeSectionStats(999999, 888888, 777777, 1, 99999.99);
    ss.str("");
    reporter->sectionEnded(stats);

    std::string output = ss.str();
    EXPECT_NE(output.find("successes=\"999999\""), std::string::npos);
    EXPECT_NE(output.find("failures=\"888888\""), std::string::npos);
    EXPECT_NE(output.find("expectedFailures=\"777777\""), std::string::npos);
    EXPECT_NE(output.find("skipped=\"true\""), std::string::npos);
}

TEST_F(XmlReporterSectionEndedTest_840, GetDescription_840) {
    std::string desc = XmlReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}
