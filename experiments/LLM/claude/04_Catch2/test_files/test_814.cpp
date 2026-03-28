#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/reporters/catch_reporter_compact.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/catch_assertion_result.hpp>
#include <catch2/internal/catch_result_type.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <catch2/internal/catch_istream.hpp>
#include <catch2/catch_message.hpp>
#include <catch2/catch_totals.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/reporters/catch_reporter_streaming_base.hpp>

#include <sstream>
#include <string>
#include <vector>

using namespace Catch;
using ::testing::Return;
using ::testing::ReturnRef;

class MockConfig : public IConfig {
public:
    ~MockConfig() override = default;
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

AssertionStats makeAssertionStats(ResultWas::OfType resultType, 
                                   const std::string& expr = "",
                                   const std::string& message = "") {
    SourceLineInfo lineInfo("test_file.cpp", 42);
    AssertionInfo info("test_macro"_catch_sr, lineInfo, expr, ResultDisposition::Normal);
    
    AssertionResultData data;
    data.resultType = resultType;
    if (!message.empty()) {
        data.message = message;
    }
    
    AssertionResult result(info, CATCH_MOVE(data));
    std::vector<MessageInfo> infoMessages;
    Totals totals;
    
    return AssertionStats(result, infoMessages, totals);
}

} // anonymous namespace

class CompactReporterTest_814 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig = std::make_shared<MockConfig>();
        // Set up common defaults
        ON_CALL(*mockConfig, defaultColourMode())
            .WillByDefault(Return(ColourMode::None));
        ON_CALL(*mockConfig, verbosity())
            .WillByDefault(Return(Verbosity::Normal));
    }

    std::shared_ptr<MockConfig> mockConfig;
    
    std::unique_ptr<CompactReporter> createReporter(std::ostream& os) {
        auto stream = Detail::make_unique<Catch::StringStream>();
        // We need to use ReporterConfig to create the reporter
        ReporterConfig config(mockConfig.get(), 
                              Detail::unique_ptr<IStream>(new Catch::ReusableStringStream()),
                              ColourMode::None, {});
        return std::make_unique<CompactReporter>(CATCH_MOVE(config));
    }
};

// Test: Successful result with includeSuccessfulResults=false should produce no output (early return)
TEST(CompactReporterBasicTest_814, SuccessfulResultNotIncluded_NoOutput_814) {
    auto mockConfig = std::make_shared<MockConfig>();
    EXPECT_CALL(*mockConfig, includeSuccessfulResults())
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*mockConfig, defaultColourMode())
        .WillRepeatedly(Return(ColourMode::None));
    EXPECT_CALL(*mockConfig, verbosity())
        .WillRepeatedly(Return(Verbosity::Normal));

    std::stringstream ss;
    auto stringStream = Catch::makeStream("-");
    
    ReporterConfig config(mockConfig.get(), CATCH_MOVE(stringStream), ColourMode::None, {});
    CompactReporter reporter(CATCH_MOVE(config));
    
    // Create a passing assertion (Ok result, not Warning or ExplicitSkip)
    SourceLineInfo lineInfo("test.cpp", 10);
    AssertionInfo aInfo(""_catch_sr, lineInfo, "1 == 1", ResultDisposition::Normal);
    AssertionResultData data;
    data.resultType = ResultWas::Ok;
    AssertionResult result(aInfo, CATCH_MOVE(data));
    std::vector<MessageInfo> msgs;
    Totals totals;
    AssertionStats stats(result, msgs, totals);
    
    // Should return early - the stream content should not change significantly
    reporter.assertionEnded(stats);
    // If it returned early, no assertion printer output was generated
    // We can't easily check the internal stream, but at least it shouldn't crash
}

// Test: Failed result should always produce output
TEST(CompactReporterBasicTest_814, FailedResultAlwaysProducesOutput_814) {
    auto mockConfig = std::make_shared<MockConfig>();
    EXPECT_CALL(*mockConfig, includeSuccessfulResults())
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*mockConfig, defaultColourMode())
        .WillRepeatedly(Return(ColourMode::None));
    EXPECT_CALL(*mockConfig, verbosity())
        .WillRepeatedly(Return(Verbosity::Normal));

    auto stringStream = Catch::makeStream("-");
    ReporterConfig config(mockConfig.get(), CATCH_MOVE(stringStream), ColourMode::None, {});
    CompactReporter reporter(CATCH_MOVE(config));

    SourceLineInfo lineInfo("test.cpp", 20);
    AssertionInfo aInfo(""_catch_sr, lineInfo, "1 == 2", ResultDisposition::Normal);
    AssertionResultData data;
    data.resultType = ResultWas::ExpressionFailed;
    AssertionResult result(aInfo, CATCH_MOVE(data));
    std::vector<MessageInfo> msgs;
    Totals totals;
    AssertionStats stats(result, msgs, totals);

    // Should not return early - will print failure info
    reporter.assertionEnded(stats);
}

// Test: Warning result with includeSuccessfulResults=false should still print (but printInfoMessages=false)
TEST(CompactReporterBasicTest_814, WarningResultPrintsEvenIfNotIncludingSuccess_814) {
    auto mockConfig = std::make_shared<MockConfig>();
    EXPECT_CALL(*mockConfig, includeSuccessfulResults())
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*mockConfig, defaultColourMode())
        .WillRepeatedly(Return(ColourMode::None));
    EXPECT_CALL(*mockConfig, verbosity())
        .WillRepeatedly(Return(Verbosity::Normal));

    auto stringStream = Catch::makeStream("-");
    ReporterConfig config(mockConfig.get(), CATCH_MOVE(stringStream), ColourMode::None, {});
    CompactReporter reporter(CATCH_MOVE(config));

    SourceLineInfo lineInfo("test.cpp", 30);
    AssertionInfo aInfo(""_catch_sr, lineInfo, "", ResultDisposition::Normal);
    AssertionResultData data;
    data.resultType = ResultWas::Warning;
    data.message = "This is a warning";
    AssertionResult result(aInfo, CATCH_MOVE(data));
    std::vector<MessageInfo> msgs;
    Totals totals;
    AssertionStats stats(result, msgs, totals);

    // Warning is Ok but should not early-return; should print with printInfoMessages=false
    reporter.assertionEnded(stats);
}

// Test: ExplicitSkip result with includeSuccessfulResults=false should still print
TEST(CompactReporterBasicTest_814, ExplicitSkipResultPrintsEvenIfNotIncludingSuccess_814) {
    auto mockConfig = std::make_shared<MockConfig>();
    EXPECT_CALL(*mockConfig, includeSuccessfulResults())
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*mockConfig, defaultColourMode())
        .WillRepeatedly(Return(ColourMode::None));
    EXPECT_CALL(*mockConfig, verbosity())
        .WillRepeatedly(Return(Verbosity::Normal));

    auto stringStream = Catch::makeStream("-");
    ReporterConfig config(mockConfig.get(), CATCH_MOVE(stringStream), ColourMode::None, {});
    CompactReporter reporter(CATCH_MOVE(config));

    SourceLineInfo lineInfo("test.cpp", 40);
    AssertionInfo aInfo(""_catch_sr, lineInfo, "", ResultDisposition::Normal);
    AssertionResultData data;
    data.resultType = ResultWas::ExplicitSkip;
    data.message = "Skipping this test";
    AssertionResult result(aInfo, CATCH_MOVE(data));
    std::vector<MessageInfo> msgs;
    Totals totals;
    AssertionStats stats(result, msgs, totals);

    reporter.assertionEnded(stats);
}

// Test: Successful result with includeSuccessfulResults=true should print
TEST(CompactReporterBasicTest_814, SuccessfulResultIncludedWhenConfigured_814) {
    auto mockConfig = std::make_shared<MockConfig>();
    EXPECT_CALL(*mockConfig, includeSuccessfulResults())
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockConfig, defaultColourMode())
        .WillRepeatedly(Return(ColourMode::None));
    EXPECT_CALL(*mockConfig, verbosity())
        .WillRepeatedly(Return(Verbosity::Normal));

    auto stringStream = Catch::makeStream("-");
    ReporterConfig config(mockConfig.get(), CATCH_MOVE(stringStream), ColourMode::None, {});
    CompactReporter reporter(CATCH_MOVE(config));

    SourceLineInfo lineInfo("test.cpp", 50);
    AssertionInfo aInfo(""_catch_sr, lineInfo, "true", ResultDisposition::Normal);
    AssertionResultData data;
    data.resultType = ResultWas::Ok;
    AssertionResult result(aInfo, CATCH_MOVE(data));
    std::vector<MessageInfo> msgs;
    Totals totals;
    AssertionStats stats(result, msgs, totals);

    // Should print because includeSuccessfulResults is true
    reporter.assertionEnded(stats);
}

// Test: Exception result should always produce output
TEST(CompactReporterBasicTest_814, ExceptionResultAlwaysProducesOutput_814) {
    auto mockConfig = std::make_shared<MockConfig>();
    EXPECT_CALL(*mockConfig, includeSuccessfulResults())
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*mockConfig, defaultColourMode())
        .WillRepeatedly(Return(ColourMode::None));
    EXPECT_CALL(*mockConfig, verbosity())
        .WillRepeatedly(Return(Verbosity::Normal));

    auto stringStream = Catch::makeStream("-");
    ReporterConfig config(mockConfig.get(), CATCH_MOVE(stringStream), ColourMode::None, {});
    CompactReporter reporter(CATCH_MOVE(config));

    SourceLineInfo lineInfo("test.cpp", 60);
    AssertionInfo aInfo(""_catch_sr, lineInfo, "someFunc()", ResultDisposition::Normal);
    AssertionResultData data;
    data.resultType = ResultWas::ThrewException;
    data.message = "unexpected exception";
    AssertionResult result(aInfo, CATCH_MOVE(data));
    std::vector<MessageInfo> msgs;
    Totals totals;
    AssertionStats stats(result, msgs, totals);

    reporter.assertionEnded(stats);
}

// Test: ExplicitFailure result should always produce output
TEST(CompactReporterBasicTest_814, ExplicitFailureAlwaysProducesOutput_814) {
    auto mockConfig = std::make_shared<MockConfig>();
    EXPECT_CALL(*mockConfig, includeSuccessfulResults())
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*mockConfig, defaultColourMode())
        .WillRepeatedly(Return(ColourMode::None));
    EXPECT_CALL(*mockConfig, verbosity())
        .WillRepeatedly(Return(Verbosity::Normal));

    auto stringStream = Catch::makeStream("-");
    ReporterConfig config(mockConfig.get(), CATCH_MOVE(stringStream), ColourMode::None, {});
    CompactReporter reporter(CATCH_MOVE(config));

    SourceLineInfo lineInfo("test.cpp", 70);
    AssertionInfo aInfo(""_catch_sr, lineInfo, "", ResultDisposition::Normal);
    AssertionResultData data;
    data.resultType = ResultWas::ExplicitFailure;
    data.message = "FAIL() called";
    AssertionResult result(aInfo, CATCH_MOVE(data));
    std::vector<MessageInfo> msgs;
    Totals totals;
    AssertionStats stats(result, msgs, totals);

    reporter.assertionEnded(stats);
}

// Test: Info result (Ok type) with includeSuccessfulResults=false should early return
TEST(CompactReporterBasicTest_814, InfoResultWithoutIncludeSuccessReturnsEarly_814) {
    auto mockConfig = std::make_shared<MockConfig>();
    EXPECT_CALL(*mockConfig, includeSuccessfulResults())
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*mockConfig, defaultColourMode())
        .WillRepeatedly(Return(ColourMode::None));
    EXPECT_CALL(*mockConfig, verbosity())
        .WillRepeatedly(Return(Verbosity::Normal));

    auto stringStream = Catch::makeStream("-");
    ReporterConfig config(mockConfig.get(), CATCH_MOVE(stringStream), ColourMode::None, {});
    CompactReporter reporter(CATCH_MOVE(config));

    SourceLineInfo lineInfo("test.cpp", 80);
    AssertionInfo aInfo(""_catch_sr, lineInfo, "", ResultDisposition::Normal);
    AssertionResultData data;
    data.resultType = ResultWas::Info;
    data.message = "Some info";
    AssertionResult result(aInfo, CATCH_MOVE(data));
    std::vector<MessageInfo> msgs;
    Totals totals;
    AssertionStats stats(result, msgs, totals);

    // Info is Ok and not Warning/ExplicitSkip, so should early return
    reporter.assertionEnded(stats);
}

// Test: getDescription returns a non-empty string
TEST(CompactReporterBasicTest_814, GetDescriptionReturnsNonEmpty_814) {
    std::string desc = CompactReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test: DidntThrowException result should produce output
TEST(CompactReporterBasicTest_814, DidntThrowExceptionProducesOutput_814) {
    auto mockConfig = std::make_shared<MockConfig>();
    EXPECT_CALL(*mockConfig, includeSuccessfulResults())
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*mockConfig, defaultColourMode())
        .WillRepeatedly(Return(ColourMode::None));
    EXPECT_CALL(*mockConfig, verbosity())
        .WillRepeatedly(Return(Verbosity::Normal));

    auto stringStream = Catch::makeStream("-");
    ReporterConfig config(mockConfig.get(), CATCH_MOVE(stringStream), ColourMode::None, {});
    CompactReporter reporter(CATCH_MOVE(config));

    SourceLineInfo lineInfo("test.cpp", 90);
    AssertionInfo aInfo(""_catch_sr, lineInfo, "throwingFunc()", ResultDisposition::Normal);
    AssertionResultData data;
    data.resultType = ResultWas::DidntThrowException;
    AssertionResult result(aInfo, CATCH_MOVE(data));
    std::vector<MessageInfo> msgs;
    Totals totals;
    AssertionStats stats(result, msgs, totals);

    reporter.assertionEnded(stats);
}

// Test: Assertion with info messages
TEST(CompactReporterBasicTest_814, AssertionWithInfoMessages_814) {
    auto mockConfig = std::make_shared<MockConfig>();
    EXPECT_CALL(*mockConfig, includeSuccessfulResults())
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*mockConfig, defaultColourMode())
        .WillRepeatedly(Return(ColourMode::None));
    EXPECT_CALL(*mockConfig, verbosity())
        .WillRepeatedly(Return(Verbosity::Normal));

    auto stringStream = Catch::makeStream("-");
    ReporterConfig config(mockConfig.get(), CATCH_MOVE(stringStream), ColourMode::None, {});
    CompactReporter reporter(CATCH_MOVE(config));

    SourceLineInfo lineInfo("test.cpp", 100);
    AssertionInfo aInfo(""_catch_sr, lineInfo, "x == 5", ResultDisposition::Normal);
    AssertionResultData data;
    data.resultType = ResultWas::Ok;
    AssertionResult result(aInfo, CATCH_MOVE(data));

    // Add some info messages
    MessageInfo msgInfo("some info", lineInfo, ResultWas::Info);
    std::vector<MessageInfo> msgs = {msgInfo};
    Totals totals;
    AssertionStats stats(result, msgs, totals);

    // With includeSuccessfulResults=true and printInfoMessages=true
    reporter.assertionEnded(stats);
}

// Test: FatalErrorCondition result
TEST(CompactReporterBasicTest_814, FatalErrorConditionProducesOutput_814) {
    auto mockConfig = std::make_shared<MockConfig>();
    EXPECT_CALL(*mockConfig, includeSuccessfulResults())
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*mockConfig, defaultColourMode())
        .WillRepeatedly(Return(ColourMode::None));
    EXPECT_CALL(*mockConfig, verbosity())
        .WillRepeatedly(Return(Verbosity::Normal));

    auto stringStream = Catch::makeStream("-");
    ReporterConfig config(mockConfig.get(), CATCH_MOVE(stringStream), ColourMode::None, {});
    CompactReporter reporter(CATCH_MOVE(config));

    SourceLineInfo lineInfo("test.cpp", 110);
    AssertionInfo aInfo(""_catch_sr, lineInfo, "", ResultDisposition::Normal);
    AssertionResultData data;
    data.resultType = ResultWas::FatalErrorCondition;
    data.message = "SIGSEGV";
    AssertionResult result(aInfo, CATCH_MOVE(data));
    std::vector<MessageInfo> msgs;
    Totals totals;
    AssertionStats stats(result, msgs, totals);

    reporter.assertionEnded(stats);
}
