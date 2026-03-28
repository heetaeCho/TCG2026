#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/internal/catch_context.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_config.hpp"

#include <sstream>
#include <memory>

namespace {

// Concrete subclass of StreamingReporterBase for testing purposes
class TestableStreamingReporter : public Catch::StreamingReporterBase {
public:
    using Catch::StreamingReporterBase::StreamingReporterBase;

    // Expose protected members for test verification
    const Catch::TestCaseInfo* getCurrentTestCaseInfo() const {
        return currentTestCaseInfo;
    }

    const Catch::TestRunInfo& getCurrentTestRunInfo() const {
        return currentTestRunInfo;
    }

    const std::vector<Catch::SectionInfo>& getSectionStack() const {
        return m_sectionStack;
    }
};

// Helper to create a ReporterConfig
class StreamingReporterBaseTest_562 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need to set up enough Catch2 infrastructure to create a ReporterConfig
        stream_ = std::make_unique<std::ostringstream>();
    }

    std::unique_ptr<TestableStreamingReporter> createReporter() {
        // Create minimal config for the reporter
        std::vector<const char*> argv = {"test"};
        Catch::ConfigData configData;
        auto config = std::make_shared<Catch::Config>(configData);
        
        auto detail = std::make_unique<Catch::ColourImpl>(Catch::ColourImpl::platformColourInstance(
            Catch::IConfig::empty()
        ));

        Catch::ReporterConfig reporterConfig(
            config,
            *stream_,
            Catch::ColourMode::None,
            {}
        );

        return std::make_unique<TestableStreamingReporter>(CATCH_MOVE(reporterConfig));
    }

    std::unique_ptr<std::ostringstream> stream_;
};

} // anonymous namespace

// Test that currentTestCaseInfo is initially nullptr
TEST_F(StreamingReporterBaseTest_562, InitialCurrentTestCaseInfoIsNull_562) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    EXPECT_EQ(reporter->getCurrentTestCaseInfo(), nullptr);
}

// Test that testCaseStarting sets currentTestCaseInfo
TEST_F(StreamingReporterBaseTest_562, TestCaseStartingSetsCurrentTestCaseInfo_562) {
    auto reporter = createReporter();

    Catch::SourceLineInfo lineInfo("test_file.cpp", 42);
    Catch::NameAndTags nameAndTags("TestName", "[tag1]");
    Catch::TestCaseInfo testInfo("TestClass"_catch_sr, nameAndTags, lineInfo);

    reporter->testCaseStarting(testInfo);

    EXPECT_EQ(reporter->getCurrentTestCaseInfo(), &testInfo);
}

// Test that testCaseStarting updates currentTestCaseInfo when called multiple times
TEST_F(StreamingReporterBaseTest_562, TestCaseStartingUpdatesOnSubsequentCalls_562) {
    auto reporter = createReporter();

    Catch::SourceLineInfo lineInfo1("file1.cpp", 10);
    Catch::NameAndTags nameAndTags1("Test1", "[tag1]");
    Catch::TestCaseInfo testInfo1("Class1"_catch_sr, nameAndTags1, lineInfo1);

    Catch::SourceLineInfo lineInfo2("file2.cpp", 20);
    Catch::NameAndTags nameAndTags2("Test2", "[tag2]");
    Catch::TestCaseInfo testInfo2("Class2"_catch_sr, nameAndTags2, lineInfo2);

    reporter->testCaseStarting(testInfo1);
    EXPECT_EQ(reporter->getCurrentTestCaseInfo(), &testInfo1);

    reporter->testCaseStarting(testInfo2);
    EXPECT_EQ(reporter->getCurrentTestCaseInfo(), &testInfo2);
}

// Test that testRunStarting updates currentTestRunInfo
TEST_F(StreamingReporterBaseTest_562, TestRunStartingSetsTestRunInfo_562) {
    auto reporter = createReporter();

    Catch::TestRunInfo runInfo("my test run"_catch_sr);
    reporter->testRunStarting(runInfo);

    EXPECT_EQ(reporter->getCurrentTestRunInfo().name, "my test run");
}

// Test that sectionStarting pushes onto section stack
TEST_F(StreamingReporterBaseTest_562, SectionStartingPushesToSectionStack_562) {
    auto reporter = createReporter();

    Catch::SourceLineInfo lineInfo("test.cpp", 5);
    Catch::SectionInfo sectionInfo(lineInfo, "Section1");

    reporter->sectionStarting(sectionInfo);

    EXPECT_EQ(reporter->getSectionStack().size(), 1u);
    EXPECT_EQ(reporter->getSectionStack().back().name, "Section1");
}

// Test that sectionEnded pops from section stack
TEST_F(StreamingReporterBaseTest_562, SectionEndedPopsFromSectionStack_562) {
    auto reporter = createReporter();

    Catch::SourceLineInfo lineInfo("test.cpp", 5);
    Catch::SectionInfo sectionInfo(lineInfo, "Section1");
    reporter->sectionStarting(sectionInfo);
    EXPECT_EQ(reporter->getSectionStack().size(), 1u);

    Catch::Counts counts;
    Catch::SectionStats sectionStats(CATCH_MOVE(sectionInfo), counts, 0.0, false);
    reporter->sectionEnded(sectionStats);

    EXPECT_EQ(reporter->getSectionStack().size(), 0u);
}

// Test that multiple sections can be nested
TEST_F(StreamingReporterBaseTest_562, MultipleSectionsCanBeNested_562) {
    auto reporter = createReporter();

    Catch::SourceLineInfo lineInfo1("test.cpp", 5);
    Catch::SectionInfo sectionInfo1(lineInfo1, "Outer");
    reporter->sectionStarting(sectionInfo1);

    Catch::SourceLineInfo lineInfo2("test.cpp", 10);
    Catch::SectionInfo sectionInfo2(lineInfo2, "Inner");
    reporter->sectionStarting(sectionInfo2);

    EXPECT_EQ(reporter->getSectionStack().size(), 2u);
    EXPECT_EQ(reporter->getSectionStack()[0].name, "Outer");
    EXPECT_EQ(reporter->getSectionStack()[1].name, "Inner");
}

// Test that testCaseEnded resets currentTestCaseInfo
TEST_F(StreamingReporterBaseTest_562, TestCaseEndedResetsCurrentTestCaseInfo_562) {
    auto reporter = createReporter();

    Catch::SourceLineInfo lineInfo("test_file.cpp", 42);
    Catch::NameAndTags nameAndTags("TestName", "[tag1]");
    Catch::TestCaseInfo testInfo("TestClass"_catch_sr, nameAndTags, lineInfo);

    reporter->testCaseStarting(testInfo);
    EXPECT_EQ(reporter->getCurrentTestCaseInfo(), &testInfo);

    Catch::Counts counts;
    Catch::Totals totals;
    Catch::TestCaseStats testCaseStats(testInfo, totals, "", "", false);
    reporter->testCaseEnded(testCaseStats);

    EXPECT_EQ(reporter->getCurrentTestCaseInfo(), nullptr);
}

// Test that the default test run info has expected initial value
TEST_F(StreamingReporterBaseTest_562, DefaultTestRunInfoHasPlaceholderName_562) {
    auto reporter = createReporter();
    EXPECT_EQ(reporter->getCurrentTestRunInfo().name, "test run has not started yet");
}

// Test that no-op methods don't crash
TEST_F(StreamingReporterBaseTest_562, NoOpMethodsDoNotCrash_562) {
    auto reporter = createReporter();

    EXPECT_NO_THROW(reporter->benchmarkPreparing("bench"_catch_sr));
    
    Catch::BenchmarkInfo benchInfo{"bench_name", 1.0, 100, 10, 0.05, Catch::BenchmarkInfo::Measure::elapsed};
    EXPECT_NO_THROW(reporter->benchmarkStarting(benchInfo));
    
    EXPECT_NO_THROW(reporter->benchmarkFailed("error"_catch_sr));
    EXPECT_NO_THROW(reporter->fatalErrorEncountered("fatal"_catch_sr));
    EXPECT_NO_THROW(reporter->noMatchingTestCases("spec"_catch_sr));
    EXPECT_NO_THROW(reporter->reportInvalidTestSpec("invalid"_catch_sr));
    
    Catch::AssertionInfo assertInfo;
    EXPECT_NO_THROW(reporter->assertionStarting(assertInfo));
}

// Test skipTest doesn't crash
TEST_F(StreamingReporterBaseTest_562, SkipTestDoesNotCrash_562) {
    auto reporter = createReporter();

    Catch::SourceLineInfo lineInfo("test_file.cpp", 42);
    Catch::NameAndTags nameAndTags("SkippedTest", "");
    Catch::TestCaseInfo testInfo("TestClass"_catch_sr, nameAndTags, lineInfo);

    EXPECT_NO_THROW(reporter->skipTest(testInfo));
}
