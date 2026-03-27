// File: tests/StreamingReporterBase_testRunStarting_851.cpp

#include <gtest/gtest.h>
#include <sstream>

#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/internal/catch_test_run_info.hpp"
#include "catch2/catch_tostring.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/reporters/catch_reporter_helpers.hpp" // for ReporterConfig (path may differ)

using namespace Catch;

// ------------------------------
// Test-only derived reporter
// ------------------------------
class TestableStreamingReporter : public StreamingReporterBase {
public:
    // Expose base constructor
    explicit TestableStreamingReporter(ReporterConfig&& cfg)
        : StreamingReporterBase(CATCH_MOVE(cfg)) {}

    // Observable accessors for verification (allowed via protected base members)
    StringRef currentRunName() const { return currentTestRunInfo.name; }

    // No-op overrides: keep the reporter concrete without adding behavior
    void testRunEnded(TestRunStats const&) override {}
    void benchmarkPreparing(StringRef) override {}
    void benchmarkStarting(BenchmarkInfo const&) override {}
    void benchmarkEnded(BenchmarkStats<> const&) override {}
    void benchmarkFailed(StringRef) override {}
    void fatalErrorEncountered(StringRef) override {}
    void noMatchingTestCases(StringRef) override {}
    void reportInvalidTestSpec(StringRef) override {}
    void testCaseStarting(TestCaseInfo const&) override {}
    void testCasePartialStarting(TestCaseInfo const&, uint64_t) override {}
    void sectionStarting(SectionInfo const&) override {}
    void assertionStarting(AssertionInfo const&) override {}
    void assertionEnded(AssertionStats const&) override {}
    void sectionEnded(SectionStats const&) override {}
    void testCasePartialEnded(TestCaseStats const&, uint64_t) override {}
    void testCaseEnded(TestCaseStats const&) override {}
    void skipTest(TestCaseInfo const&) override {}
};

// ------------------------------
// Minimal config helper
// ------------------------------
namespace {
    // A very small IConfig stub sufficient for ReporterConfig construction.
    // If your tree already has a concrete config (e.g., Catch::Config), prefer that.
    class DummyConfig : public IConfig {
    public:
        ~DummyConfig() override = default;

        // Return conservative defaults; reporters usually only read a subset.
        bool allowThrows() const override { return true; }
        std::ostream& stream() const override {
            // Not used by ReporterConfig directly; ReporterConfig holds its own stream.
            static std::ostream* s = &std::cout;
            return *s;
        }
        std::string name() const override { return "dummy-config"; }
        bool includeSuccessfulResults() const override { return true; }
        bool shouldDebugBreak() const override { return false; }
        bool warnAboutMissingAssertions() const override { return false; }
        bool warnAboutNoTests() const override { return false; }
        ShowDurations::OrNot showDurations() const override { return ShowDurations::DefaultForReporter; }
        double minDuration() const override { return -1; }
        TestSpec const& testSpec() const override {
            static TestSpec s;
            return s;
        }
        bool hasTestFilters() const override { return false; }
        bool wantsToRunInLoop() const override { return false; }
        RunTests::InWhatOrder runOrder() const override { return RunTests::InDeclarationOrder; }
        unsigned int rngSeed() const override { return 0; }
        UseColour::YesOrNo useColour() const override { return UseColour::Auto; }
        bool shouldShowHelp() const override { return false; }
        bool alwaysReportUnexpectedExceptions() const override { return false; }
        bool noThrow() const override { return false; }
        std::vector<std::string> getSectionsToRun() const override { return {}; }
        Verbosity verbosity() const override { return Verbosity::Normal; }
        bool benchmarkNoAnalysis() const override { return false; }
        int benchmarkSamples() const override { return 100; }
        double benchmarkConfidenceInterval() const override { return 0.95; }
        unsigned int benchmarkResamples() const override { return 100000; }
        std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{100}; }
        IConfig::ArtifactGenerationMode artifactGenerationMode() const override { return IConfig::ArtifactGenerationMode::None; }
    };

    // Factory for ReporterConfig with an owned stream
    ReporterConfig MakeReporterConfig(std::ostringstream& sink) {
        static DummyConfig cfg; // lifetime for the test duration
        // Note: exact ReporterConfig constructor signature can vary by Catch2 version.
        // Commonly: ReporterConfig(cfg, sink, ColourMode::Auto)
        return ReporterConfig(&cfg, sink, ColourMode::Automatic);
    }
} // namespace

// ------------------------------
// Test fixture
// ------------------------------
class StreamingReporterBase_TestRunStarting_851 : public ::testing::Test {
protected:
    std::ostringstream out;
    std::unique_ptr<TestableStreamingReporter> reporter;

    void SetUp() override {
        reporter = std::make_unique<TestableStreamingReporter>(MakeReporterConfig(out));
    }
};

// ------------------------------
// Tests
// ------------------------------

TEST_F(StreamingReporterBase_TestRunStarting_851, StoresProvidedRunName_Normal_851) {
    // Arrange
    TestRunInfo info{ StringRef{"main-run"} };

    // Act
    reporter->testRunStarting(info);

    // Assert (observable via derived accessor)
    EXPECT_STREQ(reporter->currentRunName().c_str(), std::string("main-run").c_str());
}

TEST_F(StreamingReporterBase_TestRunStarting_851, OverwritesPreviousValue_OnSecondCall_851) {
    // Arrange
    TestRunInfo first{ StringRef{"first"} };
    TestRunInfo second{ StringRef{"second"} };

    // Act
    reporter->testRunStarting(first);
    reporter->testRunStarting(second);

    // Assert
    EXPECT_STREQ(reporter->currentRunName().c_str(), std::string("second").c_str());
}

TEST_F(StreamingReporterBase_TestRunStarting_851, AcceptsEmptyName_Boundary_851) {
    // Arrange
    TestRunInfo empty{ StringRef{""} };

    // Act
    reporter->testRunStarting(empty);

    // Assert
    EXPECT_TRUE(reporter->currentRunName().empty());
    EXPECT_EQ(reporter->currentRunName().size(), 0u);
}

TEST_F(StreamingReporterBase_TestRunStarting_851, SupportsUnicodeName_Boundary_851) {
    // Arrange (Korean + emoji)
    const char* kName = u8"통합테스트🔧";
    TestRunInfo info{ StringRef{kName} };

    // Act
    reporter->testRunStarting(info);

    // Assert
    EXPECT_STREQ(reporter->currentRunName().c_str(), std::string(kName).c_str());
}

TEST_F(StreamingReporterBase_TestRunStarting_851, HandlesVeryLongName_Boundary_851) {
    // Arrange: long but reasonable string (no assumption about internal limits)
    std::string longName(8192, 'A');
    TestRunInfo info{ StringRef{longName} };

    // Act
    reporter->testRunStarting(info);

    // Assert
    EXPECT_EQ(reporter->currentRunName().size(), longName.size());
    // spot-check prefix & suffix via std::string interface
    EXPECT_EQ(std::string(reporter->currentRunName()).substr(0,3), "AAA");
    EXPECT_EQ(std::string(reporter->currentRunName()).back(), 'A');
}
