#include <catch2/reporters/catch_reporter_console.hpp>
#include <catch2/catch_section_info.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/internal/catch_console_colour.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/internal/catch_istream.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/reporters/catch_reporter_helpers.hpp>
#include <catch2/internal/catch_move_and_forward.hpp>

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <memory>

using namespace Catch;

namespace {

// Helper to create a minimal config for testing
class TestConfig : public IConfig {
public:
    bool allowThrows() const override { return true; }
    StringRef name() const override { return "test"_sr; }
    int abortAfter() const override { return -1; }
    bool showInvisibles() const override { return false; }
    ShowDurations showDurations() const override { return ShowDurations::Never; }
    double minDuration() const override { return -1.0; }
    TestRunOrder runOrder() const override { return TestRunOrder::Declared; }
    unsigned int rngSeed() const override { return 0; }
    ColourMode defaultColourMode() const override { return ColourMode::None; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return true; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds(100); }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    std::vector<std::string> const& getTestsOrTags() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    bool hasTestFilters() const override { return false; }
    std::vector<ReporterSpec> const& getReporterSpecs() const override {
        static std::vector<ReporterSpec> empty;
        return empty;
    }
    std::vector<ProcessedReporterSpec> const& getProcessedReporterSpecs() const override {
        static std::vector<ProcessedReporterSpec> empty;
        return empty;
    }
};

class TestConfigWithDuration : public TestConfig {
public:
    ShowDurations showDurations() const override { return ShowDurations::Always; }
    double minDuration() const override { return 0.0; }
};

// A simple stream wrapper for testing
class StringIStream : public IStream {
    std::ostringstream m_oss;
public:
    std::ostream& stream() override { return m_oss; }
    std::string str() const { return m_oss.str(); }
};

} // anonymous namespace

class ConsoleReporterSectionEndedTest_767 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ConsoleReporterSectionEndedTest_767, SectionEndedWithNoMissingAssertions_767) {
    // Test that sectionEnded completes without error when missingAssertions is false
    auto config = std::make_shared<TestConfig>();
    auto streamPtr = Detail::make_unique<StringIStream>();
    auto* rawStream = streamPtr.get();

    ReporterConfig reporterConfig(config.get(), CATCH_MOVE(streamPtr), ColourMode::None, {});
    ConsoleReporter reporter(CATCH_MOVE(reporterConfig));

    // Set up minimal state: need testRunStarting and testCaseStarting
    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto testCaseInfo = makeTestCaseInfo("", {"test_case", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter.testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "test_section");
    reporter.sectionStarting(sectionInfo);

    Counts assertions;
    assertions.passed = 1;
    SectionStats sectionStats(
        SectionInfo(SourceLineInfo("file.cpp", 10), "test_section"),
        assertions,
        0.0,
        false  // missingAssertions = false
    );

    EXPECT_NO_THROW(reporter.sectionEnded(sectionStats));

    std::string output = rawStream->str();
    // Should NOT contain "No assertions" message
    EXPECT_EQ(output.find("No assertions"), std::string::npos);
}

TEST_F(ConsoleReporterSectionEndedTest_767, SectionEndedWithMissingAssertionsInTestCase_767) {
    // Test that sectionEnded prints "No assertions in test case" when section stack has 1 entry
    auto config = std::make_shared<TestConfig>();
    auto streamPtr = Detail::make_unique<StringIStream>();
    auto* rawStream = streamPtr.get();

    ReporterConfig reporterConfig(config.get(), CATCH_MOVE(streamPtr), ColourMode::None, {});
    ConsoleReporter reporter(CATCH_MOVE(reporterConfig));

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto testCaseInfo = makeTestCaseInfo("", {"test_case", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter.testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "my_section");
    reporter.sectionStarting(sectionInfo);

    Counts assertions;
    SectionStats sectionStats(
        SectionInfo(SourceLineInfo("file.cpp", 10), "my_section"),
        assertions,
        0.0,
        true  // missingAssertions = true
    );

    reporter.sectionEnded(sectionStats);

    std::string output = rawStream->str();
    // With only one section in stack, should say "No assertions in test case"
    EXPECT_NE(output.find("No assertions in test case"), std::string::npos);
    EXPECT_NE(output.find("my_section"), std::string::npos);
}

TEST_F(ConsoleReporterSectionEndedTest_767, SectionEndedWithMissingAssertionsInNestedSection_767) {
    // Test that sectionEnded prints "No assertions in section" when section stack has > 1 entry
    auto config = std::make_shared<TestConfig>();
    auto streamPtr = Detail::make_unique<StringIStream>();
    auto* rawStream = streamPtr.get();

    ReporterConfig reporterConfig(config.get(), CATCH_MOVE(streamPtr), ColourMode::None, {});
    ConsoleReporter reporter(CATCH_MOVE(reporterConfig));

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto testCaseInfo = makeTestCaseInfo("", {"test_case", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter.testCaseStarting(*testCaseInfo);

    // Push two sections onto the stack
    SectionInfo outerSection(SourceLineInfo("file.cpp", 10), "outer_section");
    reporter.sectionStarting(outerSection);

    SectionInfo innerSection(SourceLineInfo("file.cpp", 20), "inner_section");
    reporter.sectionStarting(innerSection);

    Counts assertions;
    SectionStats sectionStats(
        SectionInfo(SourceLineInfo("file.cpp", 20), "inner_section"),
        assertions,
        0.0,
        true  // missingAssertions = true
    );

    reporter.sectionEnded(sectionStats);

    std::string output = rawStream->str();
    // With nested sections, should say "No assertions in section"
    EXPECT_NE(output.find("No assertions in section"), std::string::npos);
    EXPECT_NE(output.find("inner_section"), std::string::npos);
}

TEST_F(ConsoleReporterSectionEndedTest_767, SectionEndedWithDurationShown_767) {
    // Test that duration is printed when config says to show durations
    auto config = std::make_shared<TestConfigWithDuration>();
    auto streamPtr = Detail::make_unique<StringIStream>();
    auto* rawStream = streamPtr.get();

    ReporterConfig reporterConfig(config.get(), CATCH_MOVE(streamPtr), ColourMode::None, {});
    ConsoleReporter reporter(CATCH_MOVE(reporterConfig));

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto testCaseInfo = makeTestCaseInfo("", {"test_case", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter.testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "timed_section");
    reporter.sectionStarting(sectionInfo);

    Counts assertions;
    assertions.passed = 1;
    SectionStats sectionStats(
        SectionInfo(SourceLineInfo("file.cpp", 10), "timed_section"),
        assertions,
        1.5,  // 1.5 seconds duration
        false
    );

    reporter.sectionEnded(sectionStats);

    std::string output = rawStream->str();
    // Should contain the section name with duration info
    EXPECT_NE(output.find("timed_section"), std::string::npos);
    EXPECT_NE(output.find("s:"), std::string::npos);
}

TEST_F(ConsoleReporterSectionEndedTest_767, SectionEndedWithZeroDurationHidden_767) {
    // Test that zero duration is not printed when config says Never show durations
    auto config = std::make_shared<TestConfig>(); // ShowDurations::Never
    auto streamPtr = Detail::make_unique<StringIStream>();
    auto* rawStream = streamPtr.get();

    ReporterConfig reporterConfig(config.get(), CATCH_MOVE(streamPtr), ColourMode::None, {});
    ConsoleReporter reporter(CATCH_MOVE(reporterConfig));

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto testCaseInfo = makeTestCaseInfo("", {"test_case", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter.testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "quick_section");
    reporter.sectionStarting(sectionInfo);

    Counts assertions;
    assertions.passed = 1;
    SectionStats sectionStats(
        SectionInfo(SourceLineInfo("file.cpp", 10), "quick_section"),
        assertions,
        0.0,
        false
    );

    reporter.sectionEnded(sectionStats);

    std::string output = rawStream->str();
    // Duration should NOT be shown since ShowDurations is Never
    EXPECT_EQ(output.find("s: quick_section"), std::string::npos);
}

TEST_F(ConsoleReporterSectionEndedTest_767, SectionEndedPopsFromSectionStack_767) {
    // Test that after sectionEnded, the section stack is properly managed
    // (verified indirectly by being able to start/end another section)
    auto config = std::make_shared<TestConfig>();
    auto streamPtr = Detail::make_unique<StringIStream>();

    ReporterConfig reporterConfig(config.get(), CATCH_MOVE(streamPtr), ColourMode::None, {});
    ConsoleReporter reporter(CATCH_MOVE(reporterConfig));

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto testCaseInfo = makeTestCaseInfo("", {"test_case", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter.testCaseStarting(*testCaseInfo);

    // First section
    SectionInfo sectionInfo1(SourceLineInfo("file.cpp", 10), "section1");
    reporter.sectionStarting(sectionInfo1);

    Counts assertions;
    assertions.passed = 1;
    SectionStats sectionStats1(
        SectionInfo(SourceLineInfo("file.cpp", 10), "section1"),
        assertions,
        0.0,
        false
    );
    EXPECT_NO_THROW(reporter.sectionEnded(sectionStats1));

    // Second section (should work if stack was properly popped)
    SectionInfo sectionInfo2(SourceLineInfo("file.cpp", 20), "section2");
    EXPECT_NO_THROW(reporter.sectionStarting(sectionInfo2));

    SectionStats sectionStats2(
        SectionInfo(SourceLineInfo("file.cpp", 20), "section2"),
        assertions,
        0.0,
        false
    );
    EXPECT_NO_THROW(reporter.sectionEnded(sectionStats2));
}

TEST_F(ConsoleReporterSectionEndedTest_767, SectionEndedWithEmptySectionName_767) {
    // Test behavior with an empty section name
    auto config = std::make_shared<TestConfig>();
    auto streamPtr = Detail::make_unique<StringIStream>();
    auto* rawStream = streamPtr.get();

    ReporterConfig reporterConfig(config.get(), CATCH_MOVE(streamPtr), ColourMode::None, {});
    ConsoleReporter reporter(CATCH_MOVE(reporterConfig));

    TestRunInfo runInfo("test_run"_sr);
    reporter.testRunStarting(runInfo);

    auto testCaseInfo = makeTestCaseInfo("", {"test_case", "[tag]"}, SourceLineInfo("file.cpp", 1));
    reporter.testCaseStarting(*testCaseInfo);

    SectionInfo sectionInfo(SourceLineInfo("file.cpp", 10), "");
    reporter.sectionStarting(sectionInfo);

    Counts assertions;
    SectionStats sectionStats(
        SectionInfo(SourceLineInfo("file.cpp", 10), ""),
        assertions,
        0.0,
        true  // missingAssertions
    );

    EXPECT_NO_THROW(reporter.sectionEnded(sectionStats));

    std::string output = rawStream->str();
    // Should still print the missing assertions message with empty name
    EXPECT_NE(output.find("No assertions in test case"), std::string::npos);
}

TEST_F(ConsoleReporterSectionEndedTest_767, GetDescription_767) {
    // Test that getDescription returns a non-empty string
    std::string desc = ConsoleReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}
