#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include <chrono>

#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_istream.hpp"
#include "catch2/catch_test_spec.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_message.hpp"
#include "catch2/benchmark/catch_estimate.hpp"
#include "catch2/benchmark/catch_outlier_classification.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/catch_tag_alias_autoregistrar.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"

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

// A simple IStream wrapper around a stringstream
class StringIStream : public Catch::IStream {
public:
    std::ostream& stream() override { return m_ss; }
    std::stringstream m_ss;
};

class JsonReporterTest_1104 : public ::testing::Test {
protected:
    void SetUp() override {
        m_config = new ::testing::NiceMock<MockConfig>();
        m_testSpec = std::make_unique<TestSpec>();
        m_testsOrTags = std::vector<std::string>{};
        m_sectionsToRun = std::vector<std::string>{};

        ON_CALL(*m_config, name()).WillByDefault(Return("test_run"_sr));
        ON_CALL(*m_config, rngSeed()).WillByDefault(Return(12345u));
        ON_CALL(*m_config, testSpec()).WillByDefault(ReturnRef(*m_testSpec));
        ON_CALL(*m_config, hasTestFilters()).WillByDefault(Return(false));
        ON_CALL(*m_config, getTestsOrTags()).WillByDefault(ReturnRef(m_testsOrTags));
        ON_CALL(*m_config, getSectionsToRun()).WillByDefault(ReturnRef(m_sectionsToRun));
        ON_CALL(*m_config, verbosity()).WillByDefault(Return(Verbosity::Normal));
        ON_CALL(*m_config, allowThrows()).WillByDefault(Return(true));
        ON_CALL(*m_config, includeSuccessfulResults()).WillByDefault(Return(false));
        ON_CALL(*m_config, shouldDebugBreak()).WillByDefault(Return(false));
        ON_CALL(*m_config, warnAboutMissingAssertions()).WillByDefault(Return(false));
        ON_CALL(*m_config, warnAboutUnmatchedTestSpecs()).WillByDefault(Return(false));
        ON_CALL(*m_config, abortAfter()).WillByDefault(Return(0));
        ON_CALL(*m_config, showInvisibles()).WillByDefault(Return(false));
        ON_CALL(*m_config, showDurations()).WillByDefault(Return(ShowDurations::DefaultForReporter));
        ON_CALL(*m_config, minDuration()).WillByDefault(Return(-1.0));
        ON_CALL(*m_config, runOrder()).WillByDefault(Return(TestRunOrder::Declared));
        ON_CALL(*m_config, shardCount()).WillByDefault(Return(1u));
        ON_CALL(*m_config, shardIndex()).WillByDefault(Return(0u));
        ON_CALL(*m_config, defaultColourMode()).WillByDefault(Return(ColourMode::None));
        ON_CALL(*m_config, skipBenchmarks()).WillByDefault(Return(false));
        ON_CALL(*m_config, benchmarkNoAnalysis()).WillByDefault(Return(false));
        ON_CALL(*m_config, benchmarkSamples()).WillByDefault(Return(100u));
        ON_CALL(*m_config, benchmarkConfidenceInterval()).WillByDefault(Return(0.95));
        ON_CALL(*m_config, benchmarkResamples()).WillByDefault(Return(100000u));
        ON_CALL(*m_config, benchmarkWarmupTime()).WillByDefault(Return(std::chrono::milliseconds(100)));
        ON_CALL(*m_config, zeroTestsCountAsSuccess()).WillByDefault(Return(false));
    }

    void TearDown() override {
        // Config is owned by the test; reporter only holds a raw pointer
    }

    std::unique_ptr<JsonReporter> createReporter() {
        auto stream = Detail::make_unique<StringIStream>();
        m_streamPtr = stream.get();
        ReporterConfig reporterConfig(
            m_config,
            CATCH_MOVE(stream),
            ColourMode::None,
            std::map<std::string, std::string>{}
        );
        return std::make_unique<JsonReporter>(CATCH_MOVE(reporterConfig));
    }

    std::string getOutput() {
        return m_streamPtr->m_ss.str();
    }

    ::testing::NiceMock<MockConfig>* m_config = nullptr;
    StringIStream* m_streamPtr = nullptr;
    std::unique_ptr<TestSpec> m_testSpec;
    std::vector<std::string> m_testsOrTags;
    std::vector<std::string> m_sectionsToRun;
};

TEST_F(JsonReporterTest_1104, ConstructorWritesVersion_1104) {
    auto reporter = createReporter();
    std::string output = getOutput();
    EXPECT_NE(output.find("\"version\""), std::string::npos);
    EXPECT_NE(output.find("1"), std::string::npos);
}

TEST_F(JsonReporterTest_1104, ConstructorWritesMetadata_1104) {
    auto reporter = createReporter();
    std::string output = getOutput();
    EXPECT_NE(output.find("\"metadata\""), std::string::npos);
}

TEST_F(JsonReporterTest_1104, ConstructorWritesName_1104) {
    ON_CALL(*m_config, name()).WillByDefault(Return("my_test_run"_sr));
    auto reporter = createReporter();
    std::string output = getOutput();
    EXPECT_NE(output.find("\"name\""), std::string::npos);
    EXPECT_NE(output.find("my_test_run"), std::string::npos);
}

TEST_F(JsonReporterTest_1104, ConstructorWritesRngSeed_1104) {
    ON_CALL(*m_config, rngSeed()).WillByDefault(Return(42u));
    auto reporter = createReporter();
    std::string output = getOutput();
    EXPECT_NE(output.find("\"rng-seed\""), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(JsonReporterTest_1104, ConstructorWritesCatch2Version_1104) {
    auto reporter = createReporter();
    std::string output = getOutput();
    EXPECT_NE(output.find("\"catch2-version\""), std::string::npos);
}

TEST_F(JsonReporterTest_1104, PreferencesShouldRedirectStdOut_1104) {
    auto reporter = createReporter();
    EXPECT_TRUE(reporter->getPreferences().shouldRedirectStdOut);
}

TEST_F(JsonReporterTest_1104, PreferencesShouldReportAllAssertions_1104) {
    auto reporter = createReporter();
    EXPECT_TRUE(reporter->getPreferences().shouldReportAllAssertions);
}

TEST_F(JsonReporterTest_1104, GetDescriptionReturnsNonEmpty_1104) {
    std::string desc = JsonReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

TEST_F(JsonReporterTest_1104, TestRunStartingProducesOutput_1104) {
    auto reporter = createReporter();
    std::string beforeOutput = getOutput();
    TestRunInfo runInfo("test_group"_sr);
    reporter->testRunStarting(runInfo);
    std::string afterOutput = getOutput();
    EXPECT_GT(afterOutput.size(), beforeOutput.size());
}

TEST_F(JsonReporterTest_1104, TestRunStartingWritesTestCasesArray_1104) {
    auto reporter = createReporter();
    TestRunInfo runInfo("test_group"_sr);
    reporter->testRunStarting(runInfo);
    std::string output = getOutput();
    EXPECT_NE(output.find("\"test-cases\""), std::string::npos);
}

TEST_F(JsonReporterTest_1104, FullTestRunLifecycle_1104) {
    auto reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    Totals totals;
    totals.testCases.passed = 1;
    totals.assertions.passed = 5;
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);

    // Destructor should close everything properly
    reporter.reset();

    std::string output = getOutput();
    EXPECT_NE(output.find("\"version\""), std::string::npos);
    EXPECT_NE(output.find("\"test-cases\""), std::string::npos);
}

TEST_F(JsonReporterTest_1104, TestRunEndedWritesTotals_1104) {
    auto reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    Totals totals;
    totals.testCases.passed = 3;
    totals.testCases.failed = 1;
    totals.assertions.passed = 10;
    totals.assertions.failed = 2;
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);

    std::string output = getOutput();
    EXPECT_NE(output.find("\"totals\""), std::string::npos);
}

TEST_F(JsonReporterTest_1104, NoFiltersOmitsFilterField_1104) {
    // testSpec has no filters by default
    auto reporter = createReporter();
    std::string output = getOutput();
    // "filters" should not appear when there are no filters
    EXPECT_EQ(output.find("\"filters\""), std::string::npos);
}

TEST_F(JsonReporterTest_1104, DestructorProducesValidClosingBraces_1104) {
    {
        auto reporter = createReporter();
        // Let it destruct
    }
    std::string output = getOutput();
    // The output should end with a closing brace (possibly with whitespace/newlines)
    auto lastBrace = output.rfind('}');
    EXPECT_NE(lastBrace, std::string::npos);
}

TEST_F(JsonReporterTest_1104, TestCaseStartingProducesOutput_1104) {
    auto reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo(
        ""_sr,
        {"TestCase1"_sr, "[tag1]"_sr},
        {"test_file.cpp", 42}
    );

    reporter->testCaseStarting(*tcInfo);

    std::string output = getOutput();
    EXPECT_NE(output.find("TestCase1"), std::string::npos);
}

TEST_F(JsonReporterTest_1104, SectionStartingProducesOutput_1104) {
    auto reporter = createReporter();

    TestRunInfo runInfo("test_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo(
        ""_sr,
        {"TestCase1"_sr, "[tag1]"_sr},
        {"test_file.cpp", 42}
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);

    SectionInfo sectionInfo({"test_file.cpp", 42}, "Section1"_sr);
    reporter->sectionStarting(sectionInfo);

    std::string output = getOutput();
    EXPECT_NE(output.find("Section1"), std::string::npos);
}

TEST_F(JsonReporterTest_1104, ListReportersProducesOutput_1104) {
    auto reporter = createReporter();
    std::vector<ReporterDescription> descriptions;
    descriptions.push_back({"json", "JSON reporter"});
    
    reporter->listReporters(descriptions);

    std::string output = getOutput();
    EXPECT_NE(output.find("json"), std::string::npos);
}

TEST_F(JsonReporterTest_1104, ListTestsProducesOutput_1104) {
    auto reporter = createReporter();
    std::vector<TestCaseHandle> tests;

    reporter->listTests(tests);

    std::string output = getOutput();
    // Even with empty tests, listing structure should be written
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_1104, ListTagsProducesOutput_1104) {
    auto reporter = createReporter();
    std::vector<TagInfo> tags;

    reporter->listTags(tags);

    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
}

TEST_F(JsonReporterTest_1104, OutputIsJsonLike_1104) {
    auto reporter = createReporter();
    reporter.reset();

    std::string output = getOutput();
    // Should start with opening brace
    auto firstNonSpace = output.find_first_not_of(" \t\n\r");
    ASSERT_NE(firstNonSpace, std::string::npos);
    EXPECT_EQ(output[firstNonSpace], '{');
}

TEST_F(JsonReporterTest_1104, EmptyRunProducesValidOutput_1104) {
    auto reporter = createReporter();

    TestRunInfo runInfo("empty_run"_sr);
    reporter->testRunStarting(runInfo);

    Totals totals;
    TestRunStats runStats(runInfo, totals, false);
    reporter->testRunEnded(runStats);

    reporter.reset();

    std::string output = getOutput();
    EXPECT_NE(output.find("\"version\""), std::string::npos);
    EXPECT_NE(output.find("\"metadata\""), std::string::npos);
}

TEST_F(JsonReporterTest_1104, AbortsWrittenInOutput_1104) {
    auto reporter = createReporter();

    TestRunInfo runInfo("abort_run"_sr);
    reporter->testRunStarting(runInfo);

    Totals totals;
    totals.testCases.failed = 1;
    TestRunStats runStats(runInfo, totals, true);  // aborting = true
    reporter->testRunEnded(runStats);

    std::string output = getOutput();
    EXPECT_NE(output.find("\"totals\""), std::string::npos);
}

TEST_F(JsonReporterTest_1104, MultipleTestCasesInRun_1104) {
    auto reporter = createReporter();

    TestRunInfo runInfo("multi_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo1 = makeTestCaseInfo(
        ""_sr,
        {"TestCase1"_sr, "[tag1]"_sr},
        {"file.cpp", 10}
    );
    auto tcInfo2 = makeTestCaseInfo(
        ""_sr,
        {"TestCase2"_sr, "[tag2]"_sr},
        {"file.cpp", 20}
    );

    // First test case
    reporter->testCaseStarting(*tcInfo1);
    reporter->testCasePartialStarting(*tcInfo1, 0);

    Totals totals1;
    totals1.assertions.passed = 1;
    TestCaseStats tcStats1(*tcInfo1, totals1, "", "", true);
    reporter->testCasePartialEnded(tcStats1, 0);
    reporter->testCaseEnded(tcStats1);

    // Second test case
    reporter->testCaseStarting(*tcInfo2);
    reporter->testCasePartialStarting(*tcInfo2, 0);

    Totals totals2;
    totals2.assertions.passed = 2;
    TestCaseStats tcStats2(*tcInfo2, totals2, "", "", true);
    reporter->testCasePartialEnded(tcStats2, 0);
    reporter->testCaseEnded(tcStats2);

    Totals runTotals;
    runTotals.testCases.passed = 2;
    TestRunStats runStats(runInfo, runTotals, false);
    reporter->testRunEnded(runStats);

    std::string output = getOutput();
    EXPECT_NE(output.find("TestCase1"), std::string::npos);
    EXPECT_NE(output.find("TestCase2"), std::string::npos);
}

TEST_F(JsonReporterTest_1104, BenchmarkPreparingProducesOutput_1104) {
    auto reporter = createReporter();

    TestRunInfo runInfo("bench_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo(
        ""_sr,
        {"BenchTest"_sr, "[bench]"_sr},
        {"bench.cpp", 1}
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);

    SectionInfo sectionInfo({"bench.cpp", 1}, "BenchTest"_sr);
    reporter->sectionStarting(sectionInfo);

    reporter->benchmarkPreparing("my_benchmark"_sr);

    std::string output = getOutput();
    EXPECT_NE(output.find("my_benchmark"), std::string::npos);
}

TEST_F(JsonReporterTest_1104, BenchmarkFailedProducesOutput_1104) {
    auto reporter = createReporter();

    TestRunInfo runInfo("bench_fail_run"_sr);
    reporter->testRunStarting(runInfo);

    auto tcInfo = makeTestCaseInfo(
        ""_sr,
        {"BenchFailTest"_sr, "[bench]"_sr},
        {"bench.cpp", 1}
    );
    reporter->testCaseStarting(*tcInfo);
    reporter->testCasePartialStarting(*tcInfo, 0);

    SectionInfo sectionInfo({"bench.cpp", 1}, "BenchFailTest"_sr);
    reporter->sectionStarting(sectionInfo);

    reporter->benchmarkPreparing("failing_bench"_sr);
    reporter->benchmarkFailed("benchmark error"_sr);

    std::string output = getOutput();
    EXPECT_NE(output.find("benchmark error"), std::string::npos);
}

TEST_F(JsonReporterTest_1104, ListListenersProducesOutput_1104) {
    auto reporter = createReporter();
    std::vector<ListenerDescription> descriptions;

    reporter->listListeners(descriptions);

    std::string output = getOutput();
    EXPECT_FALSE(output.empty());
}
