#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/catch_assertion_result.hpp"
#include "catch2/internal/catch_result_type.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::AtLeast;

// Mock IConfig
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

// Mock IEventListener
class MockEventListener : public IEventListener {
public:
    MockEventListener(IConfig const* config) : IEventListener(config) {}

    MOCK_METHOD(void, noMatchingTestCases, (StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef), (override));
    MOCK_METHOD(void, testRunStarting, (const TestRunInfo&), (override));
    MOCK_METHOD(void, testCaseStarting, (const TestCaseInfo&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (const TestCaseInfo&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (const SectionInfo&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo&), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, assertionStarting, (const AssertionInfo&), (override));
    MOCK_METHOD(void, assertionEnded, (const AssertionStats&), (override));
    MOCK_METHOD(void, sectionEnded, (const SectionStats&), (override));
    MOCK_METHOD(void, testCasePartialEnded, (const TestCaseStats&, uint64_t), (override));
    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats&), (override));
    MOCK_METHOD(void, testRunEnded, (const TestRunStats&), (override));
    MOCK_METHOD(void, skipTest, (const TestCaseInfo&), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
    MOCK_METHOD(void, listReporters, (const std::vector<ReporterDescription>&), (override));
    MOCK_METHOD(void, listListeners, (const std::vector<ListenerDescription>&), (override));
    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle>&), (override));
    MOCK_METHOD(void, listTags, (const std::vector<TagInfo>&), (override));

    void setShouldReportAllAssertions(bool val) {
        m_preferences.shouldReportAllAssertions = val;
    }
    void setShouldRedirectStdOut(bool val) {
        m_preferences.shouldRedirectStdOut = val;
    }
};

class MultiReporterTest_800 : public ::testing::Test {
protected:
    MockConfig mockConfig;

    void SetUp() override {
    }

    // Helper to create AssertionStats with a given result type
    AssertionStats makeAssertionStats(ResultWas::OfType resultType) {
        AssertionInfo info;
        info.macroName = "TEST_MACRO"_catch_sr;
        info.lineInfo = SourceLineInfo("file.cpp", 1);
        AssertionResultData data;
        data.resultType = resultType;
        AssertionResult result(info, CATCH_MOVE(data));
        std::vector<MessageInfo> messages;
        Totals totals;
        return AssertionStats(result, messages, totals);
    }
};

// Test: assertionEnded with a failed assertion should notify all reporters
TEST_F(MultiReporterTest_800, AssertionEndedFailedNotifiesAllReporters_800) {
    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillRepeatedly(Return(false));

    MultiReporter multi(&mockConfig);

    auto* listener1 = new MockEventListener(&mockConfig);
    auto* listener2 = new MockEventListener(&mockConfig);
    listener1->setShouldReportAllAssertions(false);
    listener2->setShouldReportAllAssertions(false);

    EXPECT_CALL(*listener1, assertionEnded(_)).Times(1);
    EXPECT_CALL(*listener2, assertionEnded(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(listener1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(listener2));

    auto stats = makeAssertionStats(ResultWas::ExpressionFailed);
    multi.assertionEnded(stats);
}

// Test: assertionEnded with Ok result and includeSuccessfulResults=false, reporter doesn't want all assertions
TEST_F(MultiReporterTest_800, AssertionEndedOkNotReportedWhenNotIncluded_800) {
    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillRepeatedly(Return(false));

    MultiReporter multi(&mockConfig);

    auto* listener1 = new MockEventListener(&mockConfig);
    listener1->setShouldReportAllAssertions(false);

    EXPECT_CALL(*listener1, assertionEnded(_)).Times(0);

    multi.addReporter(Detail::unique_ptr<IEventListener>(listener1));

    auto stats = makeAssertionStats(ResultWas::Ok);
    multi.assertionEnded(stats);
}

// Test: assertionEnded with Ok result and includeSuccessfulResults=true should report
TEST_F(MultiReporterTest_800, AssertionEndedOkReportedWhenIncludeSuccessful_800) {
    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillRepeatedly(Return(true));

    MultiReporter multi(&mockConfig);

    auto* listener1 = new MockEventListener(&mockConfig);
    listener1->setShouldReportAllAssertions(false);

    EXPECT_CALL(*listener1, assertionEnded(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(listener1));

    auto stats = makeAssertionStats(ResultWas::Ok);
    multi.assertionEnded(stats);
}

// Test: assertionEnded with Ok result, includeSuccessfulResults=false, but reporter wants all assertions
TEST_F(MultiReporterTest_800, AssertionEndedOkReportedWhenReporterWantsAll_800) {
    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillRepeatedly(Return(false));

    MultiReporter multi(&mockConfig);

    auto* listener1 = new MockEventListener(&mockConfig);
    listener1->setShouldReportAllAssertions(true);

    EXPECT_CALL(*listener1, assertionEnded(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(listener1));

    auto stats = makeAssertionStats(ResultWas::Ok);
    multi.assertionEnded(stats);
}

// Test: Mixed reporters - one wants all, one doesn't, Ok result, no includeSuccessful
TEST_F(MultiReporterTest_800, AssertionEndedOkMixedReporterPreferences_800) {
    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillRepeatedly(Return(false));

    MultiReporter multi(&mockConfig);

    auto* reporterAll = new MockEventListener(&mockConfig);
    reporterAll->setShouldReportAllAssertions(true);

    auto* reporterDefault = new MockEventListener(&mockConfig);
    reporterDefault->setShouldReportAllAssertions(false);

    EXPECT_CALL(*reporterAll, assertionEnded(_)).Times(1);
    EXPECT_CALL(*reporterDefault, assertionEnded(_)).Times(0);

    multi.addReporter(Detail::unique_ptr<IEventListener>(reporterAll));
    multi.addReporter(Detail::unique_ptr<IEventListener>(reporterDefault));

    auto stats = makeAssertionStats(ResultWas::Ok);
    multi.assertionEnded(stats);
}

// Test: assertionEnded with no reporters added should not crash
TEST_F(MultiReporterTest_800, AssertionEndedNoReportersDoesNotCrash_800) {
    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillRepeatedly(Return(false));

    MultiReporter multi(&mockConfig);

    auto stats = makeAssertionStats(ResultWas::ExpressionFailed);
    EXPECT_NO_THROW(multi.assertionEnded(stats));
}

// Test: assertionEnded with exception result notifies all reporters
TEST_F(MultiReporterTest_800, AssertionEndedExceptionNotifiesAll_800) {
    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillRepeatedly(Return(false));

    MultiReporter multi(&mockConfig);

    auto* listener1 = new MockEventListener(&mockConfig);
    listener1->setShouldReportAllAssertions(false);

    EXPECT_CALL(*listener1, assertionEnded(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(listener1));

    auto stats = makeAssertionStats(ResultWas::ThrewException);
    multi.assertionEnded(stats);
}

// Test: addListener places listener before reporters
TEST_F(MultiReporterTest_800, AddListenerAndReporter_800) {
    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillRepeatedly(Return(false));

    MultiReporter multi(&mockConfig);

    auto* listener = new MockEventListener(&mockConfig);
    listener->setShouldReportAllAssertions(false);

    auto* reporter = new MockEventListener(&mockConfig);
    reporter->setShouldReportAllAssertions(false);

    EXPECT_CALL(*listener, assertionEnded(_)).Times(1);
    EXPECT_CALL(*reporter, assertionEnded(_)).Times(1);

    multi.addListener(Detail::unique_ptr<IEventListener>(listener));
    multi.addReporter(Detail::unique_ptr<IEventListener>(reporter));

    auto stats = makeAssertionStats(ResultWas::ExplicitFailure);
    multi.assertionEnded(stats);
}

// Test: assertionEnded with Warning result (non-Ok) should be reported by default
TEST_F(MultiReporterTest_800, AssertionEndedWarningReportedByDefault_800) {
    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillRepeatedly(Return(false));

    MultiReporter multi(&mockConfig);

    auto* listener1 = new MockEventListener(&mockConfig);
    listener1->setShouldReportAllAssertions(false);

    EXPECT_CALL(*listener1, assertionEnded(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(listener1));

    auto stats = makeAssertionStats(ResultWas::Warning);
    multi.assertionEnded(stats);
}

// Test: assertionEnded with ExplicitSkip result should be reported by default
TEST_F(MultiReporterTest_800, AssertionEndedExplicitSkipReportedByDefault_800) {
    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillRepeatedly(Return(false));

    MultiReporter multi(&mockConfig);

    auto* listener1 = new MockEventListener(&mockConfig);
    listener1->setShouldReportAllAssertions(false);

    EXPECT_CALL(*listener1, assertionEnded(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(listener1));

    auto stats = makeAssertionStats(ResultWas::ExplicitSkip);
    multi.assertionEnded(stats);
}

// Test: Multiple reporters all with shouldReportAllAssertions, Ok result, no includeSuccessful
TEST_F(MultiReporterTest_800, AssertionEndedOkAllReportersWantAll_800) {
    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillRepeatedly(Return(false));

    MultiReporter multi(&mockConfig);

    auto* r1 = new MockEventListener(&mockConfig);
    r1->setShouldReportAllAssertions(true);
    auto* r2 = new MockEventListener(&mockConfig);
    r2->setShouldReportAllAssertions(true);
    auto* r3 = new MockEventListener(&mockConfig);
    r3->setShouldReportAllAssertions(true);

    EXPECT_CALL(*r1, assertionEnded(_)).Times(1);
    EXPECT_CALL(*r2, assertionEnded(_)).Times(1);
    EXPECT_CALL(*r3, assertionEnded(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(r1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(r2));
    multi.addReporter(Detail::unique_ptr<IEventListener>(r3));

    auto stats = makeAssertionStats(ResultWas::Ok);
    multi.assertionEnded(stats);
}

// Test: Both includeSuccessfulResults and shouldReportAllAssertions true, Ok result
TEST_F(MultiReporterTest_800, AssertionEndedOkBothConfigAndPreferenceTrue_800) {
    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillRepeatedly(Return(true));

    MultiReporter multi(&mockConfig);

    auto* r1 = new MockEventListener(&mockConfig);
    r1->setShouldReportAllAssertions(true);

    EXPECT_CALL(*r1, assertionEnded(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(r1));

    auto stats = makeAssertionStats(ResultWas::Ok);
    multi.assertionEnded(stats);
}

// Test: Info result (non-Ok, non-failure) should be reported by default
TEST_F(MultiReporterTest_800, AssertionEndedInfoResultReported_800) {
    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillRepeatedly(Return(false));

    MultiReporter multi(&mockConfig);

    auto* listener1 = new MockEventListener(&mockConfig);
    listener1->setShouldReportAllAssertions(false);

    EXPECT_CALL(*listener1, assertionEnded(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(listener1));

    auto stats = makeAssertionStats(ResultWas::Info);
    multi.assertionEnded(stats);
}

// Test: noMatchingTestCases forwards to all reporters
TEST_F(MultiReporterTest_800, NoMatchingTestCasesForwardsToAll_800) {
    MultiReporter multi(&mockConfig);

    auto* r1 = new MockEventListener(&mockConfig);
    auto* r2 = new MockEventListener(&mockConfig);

    EXPECT_CALL(*r1, noMatchingTestCases(_)).Times(1);
    EXPECT_CALL(*r2, noMatchingTestCases(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(r1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(r2));

    multi.noMatchingTestCases("some_spec"_catch_sr);
}

// Test: fatalErrorEncountered forwards to all reporters
TEST_F(MultiReporterTest_800, FatalErrorEncounteredForwardsToAll_800) {
    MultiReporter multi(&mockConfig);

    auto* r1 = new MockEventListener(&mockConfig);
    auto* r2 = new MockEventListener(&mockConfig);

    EXPECT_CALL(*r1, fatalErrorEncountered(_)).Times(1);
    EXPECT_CALL(*r2, fatalErrorEncountered(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(r1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(r2));

    multi.fatalErrorEncountered("fatal error"_catch_sr);
}

// Test: assertionStarting forwards to all reporters
TEST_F(MultiReporterTest_800, AssertionStartingForwardsToAll_800) {
    MultiReporter multi(&mockConfig);

    auto* r1 = new MockEventListener(&mockConfig);
    auto* r2 = new MockEventListener(&mockConfig);

    EXPECT_CALL(*r1, assertionStarting(_)).Times(1);
    EXPECT_CALL(*r2, assertionStarting(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(r1));
    multi.addReporter(Detail::unique_ptr<IEventListener>(r2));

    AssertionInfo info;
    multi.assertionStarting(info);
}

// Test: FatalErrorCondition result is reported by default (non-Ok)
TEST_F(MultiReporterTest_800, AssertionEndedFatalErrorConditionReported_800) {
    EXPECT_CALL(mockConfig, includeSuccessfulResults()).WillRepeatedly(Return(false));

    MultiReporter multi(&mockConfig);

    auto* listener1 = new MockEventListener(&mockConfig);
    listener1->setShouldReportAllAssertions(false);

    EXPECT_CALL(*listener1, assertionEnded(_)).Times(1);

    multi.addReporter(Detail::unique_ptr<IEventListener>(listener1));

    auto stats = makeAssertionStats(ResultWas::FatalErrorCondition);
    multi.assertionEnded(stats);
}
