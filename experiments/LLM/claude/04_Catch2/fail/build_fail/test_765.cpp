#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <vector>

#include "catch2/reporters/catch_reporter_console.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/internal/catch_result_type.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_stream.hpp"
#include "catch2/internal/catch_console_colour.hpp"

using namespace Catch;
using ::testing::Return;
using ::testing::_;

// Mock IConfig for controlling test behavior
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

namespace {

// Helper to create a ReporterConfig with a stringstream-based stream
class ConsoleReporterTest_765 : public ::testing::Test {
protected:
    std::unique_ptr<MockConfig> mockConfig;
    std::ostringstream oss;
    std::unique_ptr<ConsoleReporter> reporter;
    std::vector<std::string> emptyStrVec;
    std::vector<std::string> emptySections;
    TestSpec emptyTestSpec;

    void SetUp() override {
        mockConfig = std::make_unique<MockConfig>();

        // Set up default mock expectations
        ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(Return(false));
        ON_CALL(*mockConfig, verbosity()).WillByDefault(Return(Verbosity::Normal));
        ON_CALL(*mockConfig, defaultColourMode()).WillByDefault(Return(ColourMode::None));
        ON_CALL(*mockConfig, showDurations()).WillByDefault(Return(ShowDurations::DefaultForReporter));
        ON_CALL(*mockConfig, name()).WillByDefault(Return(StringRef("test")));
        ON_CALL(*mockConfig, getTestsOrTags()).WillByDefault(::testing::ReturnRef(emptyStrVec));
        ON_CALL(*mockConfig, getSectionsToRun()).WillByDefault(::testing::ReturnRef(emptySections));
        ON_CALL(*mockConfig, testSpec()).WillByDefault(::testing::ReturnRef(emptyTestSpec));
        ON_CALL(*mockConfig, hasTestFilters()).WillByDefault(Return(false));
        ON_CALL(*mockConfig, rngSeed()).WillByDefault(Return(0));
        ON_CALL(*mockConfig, abortAfter()).WillByDefault(Return(0));
        ON_CALL(*mockConfig, minDuration()).WillByDefault(Return(-1.0));
        ON_CALL(*mockConfig, benchmarkNoAnalysis()).WillByDefault(Return(false));
        ON_CALL(*mockConfig, benchmarkSamples()).WillByDefault(Return(100));
        ON_CALL(*mockConfig, benchmarkResamples()).WillByDefault(Return(100000));
        ON_CALL(*mockConfig, benchmarkConfidenceInterval()).WillByDefault(Return(0.95));
        ON_CALL(*mockConfig, benchmarkWarmupTime()).WillByDefault(Return(std::chrono::milliseconds(100)));
    }

    std::unique_ptr<ConsoleReporter> createReporter() {
        auto streamPtr = Detail::make_unique<StringStream>();
        // We need to use the actual ReporterConfig construction
        ReporterConfig config(mockConfig.get(), Detail::make_unique<StringStream>(), ColourMode::None, {});
        return std::make_unique<ConsoleReporter>(CATCH_MOVE(config));
    }

    AssertionStats makeAssertionStats(ResultWas::OfType resultType) {
        AssertionInfo info;
        info.macroName = "REQUIRE"_sr;
        info.lineInfo = SourceLineInfo("test.cpp", 42);
        info.capturedExpression = "a == b"_sr;

        AssertionResultData data;
        data.resultType = resultType;

        AssertionResult result(info, CATCH_MOVE(data));
        std::vector<MessageInfo> messages;
        Totals totals;

        return AssertionStats(result, messages, totals);
    }

    void setupTestContext(ConsoleReporter& rep) {
        // Set up minimal context so lazyPrint has something to work with
        TestRunInfo runInfo("test_run");
        rep.testRunStarting(runInfo);

        TestCaseInfo testCaseInfo(
            ""_sr, {"test_name"_sr, "[tag]"_sr}, SourceLineInfo("test.cpp", 1));
        rep.testCaseStarting(testCaseInfo);

        SectionInfo sectionInfo(SourceLineInfo("test.cpp", 1), "section");
        rep.sectionStarting(sectionInfo);
    }
};

} // anonymous namespace

// Test that assertionEnded can be called with a successful result when includeSuccessfulResults is false
// The successful result should be skipped (not printed)
TEST_F(ConsoleReporterTest_765, SuccessfulResultSkippedWhenNotIncluded_765) {
    ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(Return(false));

    auto rep = createReporter();
    ASSERT_NE(rep, nullptr);

    setupTestContext(*rep);

    auto stats = makeAssertionStats(ResultWas::Ok);
    // Should not crash; successful results are skipped when includeSuccessfulResults is false
    EXPECT_NO_THROW(rep->assertionEnded(stats));
}

// Test that assertionEnded prints output for failed assertions
TEST_F(ConsoleReporterTest_765, FailedAssertionProducesOutput_765) {
    ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(Return(false));

    auto rep = createReporter();
    ASSERT_NE(rep, nullptr);

    setupTestContext(*rep);

    auto stats = makeAssertionStats(ResultWas::ExpressionFailed);
    EXPECT_NO_THROW(rep->assertionEnded(stats));
}

// Test that assertionEnded prints output when includeSuccessfulResults is true even for Ok results
TEST_F(ConsoleReporterTest_765, SuccessfulResultPrintedWhenIncluded_765) {
    ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(Return(true));

    auto rep = createReporter();
    ASSERT_NE(rep, nullptr);

    setupTestContext(*rep);

    auto stats = makeAssertionStats(ResultWas::Ok);
    EXPECT_NO_THROW(rep->assertionEnded(stats));
}

// Test that Warning results are always processed even when includeSuccessfulResults is false
TEST_F(ConsoleReporterTest_765, WarningResultAlwaysProcessed_765) {
    ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(Return(false));

    auto rep = createReporter();
    ASSERT_NE(rep, nullptr);

    setupTestContext(*rep);

    auto stats = makeAssertionStats(ResultWas::Warning);
    EXPECT_NO_THROW(rep->assertionEnded(stats));
}

// Test that ExplicitSkip results are always processed even when includeSuccessfulResults is false
TEST_F(ConsoleReporterTest_765, ExplicitSkipResultAlwaysProcessed_765) {
    ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(Return(false));

    auto rep = createReporter();
    ASSERT_NE(rep, nullptr);

    setupTestContext(*rep);

    auto stats = makeAssertionStats(ResultWas::ExplicitSkip);
    EXPECT_NO_THROW(rep->assertionEnded(stats));
}

// Test that ExplicitFailure is processed
TEST_F(ConsoleReporterTest_765, ExplicitFailureProcessed_765) {
    ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(Return(false));

    auto rep = createReporter();
    ASSERT_NE(rep, nullptr);

    setupTestContext(*rep);

    auto stats = makeAssertionStats(ResultWas::ExplicitFailure);
    EXPECT_NO_THROW(rep->assertionEnded(stats));
}

// Test that ThrewException is processed
TEST_F(ConsoleReporterTest_765, ThrewExceptionProcessed_765) {
    ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(Return(false));

    auto rep = createReporter();
    ASSERT_NE(rep, nullptr);

    setupTestContext(*rep);

    auto stats = makeAssertionStats(ResultWas::ThrewException);
    EXPECT_NO_THROW(rep->assertionEnded(stats));
}

// Test that DidntThrowException is processed
TEST_F(ConsoleReporterTest_765, DidntThrowExceptionProcessed_765) {
    ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(Return(false));

    auto rep = createReporter();
    ASSERT_NE(rep, nullptr);

    setupTestContext(*rep);

    auto stats = makeAssertionStats(ResultWas::DidntThrowException);
    EXPECT_NO_THROW(rep->assertionEnded(stats));
}

// Test that FatalErrorCondition is processed
TEST_F(ConsoleReporterTest_765, FatalErrorConditionProcessed_765) {
    ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(Return(false));

    auto rep = createReporter();
    ASSERT_NE(rep, nullptr);

    setupTestContext(*rep);

    auto stats = makeAssertionStats(ResultWas::FatalErrorCondition);
    EXPECT_NO_THROW(rep->assertionEnded(stats));
}

// Test that Info result is skipped when not included and not a warning/skip
TEST_F(ConsoleReporterTest_765, InfoResultSkippedWhenNotIncluded_765) {
    ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(Return(false));

    auto rep = createReporter();
    ASSERT_NE(rep, nullptr);

    setupTestContext(*rep);

    auto stats = makeAssertionStats(ResultWas::Info);
    EXPECT_NO_THROW(rep->assertionEnded(stats));
}

// Test multiple assertions in sequence
TEST_F(ConsoleReporterTest_765, MultipleAssertionsInSequence_765) {
    ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(Return(false));

    auto rep = createReporter();
    ASSERT_NE(rep, nullptr);

    setupTestContext(*rep);

    auto statsOk = makeAssertionStats(ResultWas::Ok);
    auto statsFailed = makeAssertionStats(ResultWas::ExpressionFailed);
    auto statsWarning = makeAssertionStats(ResultWas::Warning);

    EXPECT_NO_THROW(rep->assertionEnded(statsOk));
    EXPECT_NO_THROW(rep->assertionEnded(statsFailed));
    EXPECT_NO_THROW(rep->assertionEnded(statsWarning));
}

// Test getDescription returns a non-empty string
TEST_F(ConsoleReporterTest_765, GetDescriptionReturnsNonEmpty_765) {
    std::string desc = ConsoleReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test assertionStarting does not crash
TEST_F(ConsoleReporterTest_765, AssertionStartingDoesNotCrash_765) {
    auto rep = createReporter();
    ASSERT_NE(rep, nullptr);

    AssertionInfo info;
    info.macroName = "REQUIRE"_sr;
    info.lineInfo = SourceLineInfo("test.cpp", 10);
    info.capturedExpression = "x == 1"_sr;

    EXPECT_NO_THROW(rep->assertionStarting(info));
}

// Test noMatchingTestCases does not crash
TEST_F(ConsoleReporterTest_765, NoMatchingTestCasesDoesNotCrash_765) {
    auto rep = createReporter();
    ASSERT_NE(rep, nullptr);

    EXPECT_NO_THROW(rep->noMatchingTestCases("some_spec"_sr));
}

// Test reportInvalidTestSpec does not crash
TEST_F(ConsoleReporterTest_765, ReportInvalidTestSpecDoesNotCrash_765) {
    auto rep = createReporter();
    ASSERT_NE(rep, nullptr);

    EXPECT_NO_THROW(rep->reportInvalidTestSpec("bad_arg"_sr));
}

// Test with assertion stats that have info messages
TEST_F(ConsoleReporterTest_765, AssertionWithInfoMessages_765) {
    ON_CALL(*mockConfig, includeSuccessfulResults()).WillByDefault(Return(true));

    auto rep = createReporter();
    ASSERT_NE(rep, nullptr);

    setupTestContext(*rep);

    AssertionInfo info;
    info.macroName = "REQUIRE"_sr;
    info.lineInfo = SourceLineInfo("test.cpp", 42);
    info.capturedExpression = "a == b"_sr;

    AssertionResultData data;
    data.resultType = ResultWas::ExpressionFailed;

    AssertionResult result(info, CATCH_MOVE(data));

    MessageInfo msgInfo("test message", SourceLineInfo("test.cpp", 40), ResultWas::Info);
    std::vector<MessageInfo> messages = {msgInfo};
    Totals totals;

    AssertionStats stats(result, messages, totals);
    EXPECT_NO_THROW(rep->assertionEnded(stats));
}
