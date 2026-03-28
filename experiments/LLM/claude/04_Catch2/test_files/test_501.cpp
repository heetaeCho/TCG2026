#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/catch_test_case_info.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Eq;

namespace {

class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

class MockReporter : public IEventListener {
public:
    MockReporter(IConfig const* config) : IEventListener(config) {}

    MOCK_METHOD(void, noMatchingTestCases, (StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef), (override));
    MOCK_METHOD(void, testRunStarting, (TestRunInfo const&), (override));
    MOCK_METHOD(void, testCaseStarting, (TestCaseInfo const&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (TestCaseInfo const&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (SectionInfo const&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (BenchmarkInfo const&), (override));
    MOCK_METHOD(void, benchmarkEnded, (BenchmarkStats<> const&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, assertionStarting, (AssertionInfo const&), (override));
    MOCK_METHOD(void, assertionEnded, (AssertionStats const&), (override));
    MOCK_METHOD(void, sectionEnded, (SectionStats const&), (override));
    MOCK_METHOD(void, testCasePartialEnded, (TestCaseStats const&, uint64_t), (override));
    MOCK_METHOD(void, testCaseEnded, (TestCaseStats const&), (override));
    MOCK_METHOD(void, testRunEnded, (TestRunStats const&), (override));
    MOCK_METHOD(void, skipTest, (TestCaseInfo const&), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
    MOCK_METHOD(void, listReporters, (std::vector<ReporterDescription> const&), (override));
    MOCK_METHOD(void, listListeners, (std::vector<ListenerDescription> const&), (override));
    MOCK_METHOD(void, listTests, (std::vector<TestCaseHandle> const&), (override));
    MOCK_METHOD(void, listTags, (std::vector<TagInfo> const&), (override));
};

class RunContextTest_501 : public ::testing::Test {
protected:
    void SetUp() override {
        mockConfig_ = new MockConfig();
        
        static const std::vector<std::string> emptyVec;
        ON_CALL(*mockConfig_, name()).WillByDefault(::testing::Return(StringRef("test")));
        ON_CALL(*mockConfig_, includeSuccessfulResults()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, warnAboutMissingAssertions()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, abortAfter()).WillByDefault(::testing::Return(0));
        ON_CALL(*mockConfig_, getTestsOrTags()).WillByDefault(::testing::ReturnRef(emptyVec));
        ON_CALL(*mockConfig_, getSectionsToRun()).WillByDefault(::testing::ReturnRef(emptyVec));
        ON_CALL(*mockConfig_, verbosity()).WillByDefault(::testing::Return(Verbosity::Normal));
        ON_CALL(*mockConfig_, benchmarkNoAnalysis()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, benchmarkSamples()).WillByDefault(::testing::Return(100));
        ON_CALL(*mockConfig_, benchmarkConfidenceInterval()).WillByDefault(::testing::Return(0.95));
        ON_CALL(*mockConfig_, benchmarkResamples()).WillByDefault(::testing::Return(100000));
        ON_CALL(*mockConfig_, benchmarkWarmupTime()).WillByDefault(::testing::Return(std::chrono::milliseconds(100)));
        ON_CALL(*mockConfig_, hasTestFilters()).WillByDefault(::testing::Return(false));
        ON_CALL(*mockConfig_, allowThrows()).WillByDefault(::testing::Return(true));
        ON_CALL(*mockConfig_, showDurations()).WillByDefault(::testing::Return(ShowDurations::DefaultForReporter));
        ON_CALL(*mockConfig_, runOrder()).WillByDefault(::testing::Return(TestRunOrder::Declared));
        ON_CALL(*mockConfig_, rngSeed()).WillByDefault(::testing::Return(0));
        ON_CALL(*mockConfig_, defaultColourMode()).WillByDefault(::testing::Return(ColourMode::PlatformDefault));

        mockReporter_ = new MockReporter(mockConfig_);
    }

    void TearDown() override {
        delete mockConfig_;
        // mockReporter_ is owned by RunContext via unique_ptr after construction
    }

    MockConfig* mockConfig_;
    MockReporter* mockReporter_;  // Raw pointer, ownership transferred to RunContext
};

TEST_F(RunContextTest_501, BenchmarkPreparingForwardsNameToReporter_501) {
    // We need to keep a raw pointer before transferring ownership
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(::testing::AnyNumber());
    
    Detail::unique_ptr<IEventListener> reporterOwner(mockReporter_);
    
    EXPECT_CALL(*reporterPtr, benchmarkPreparing(::testing::_)).Times(1);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterOwner));
    context.benchmarkPreparing(StringRef("my_benchmark"));
}

TEST_F(RunContextTest_501, BenchmarkPreparingWithEmptyName_501) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(::testing::AnyNumber());
    
    Detail::unique_ptr<IEventListener> reporterOwner(mockReporter_);
    
    EXPECT_CALL(*reporterPtr, benchmarkPreparing(::testing::_)).Times(1);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterOwner));
    context.benchmarkPreparing(StringRef(""));
}

TEST_F(RunContextTest_501, BenchmarkPreparingCalledMultipleTimes_501) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(::testing::AnyNumber());
    
    Detail::unique_ptr<IEventListener> reporterOwner(mockReporter_);
    
    EXPECT_CALL(*reporterPtr, benchmarkPreparing(::testing::_)).Times(3);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterOwner));
    context.benchmarkPreparing(StringRef("bench1"));
    context.benchmarkPreparing(StringRef("bench2"));
    context.benchmarkPreparing(StringRef("bench3"));
}

TEST_F(RunContextTest_501, BenchmarkPreparingWithLongName_501) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(::testing::AnyNumber());
    
    Detail::unique_ptr<IEventListener> reporterOwner(mockReporter_);
    
    std::string longName(1000, 'x');
    
    EXPECT_CALL(*reporterPtr, benchmarkPreparing(::testing::_)).Times(1);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterOwner));
    context.benchmarkPreparing(StringRef(longName));
}

TEST_F(RunContextTest_501, BenchmarkStartingForwardsToReporter_501) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(::testing::AnyNumber());
    
    Detail::unique_ptr<IEventListener> reporterOwner(mockReporter_);
    
    EXPECT_CALL(*reporterPtr, benchmarkStarting(::testing::_)).Times(1);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterOwner));
    BenchmarkInfo info{"benchmark_test", 1.0, 100, 100, 100000, 0.95};
    context.benchmarkStarting(info);
}

TEST_F(RunContextTest_501, BenchmarkFailedForwardsToReporter_501) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(::testing::AnyNumber());
    
    Detail::unique_ptr<IEventListener> reporterOwner(mockReporter_);
    
    EXPECT_CALL(*reporterPtr, benchmarkFailed(::testing::_)).Times(1);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterOwner));
    context.benchmarkFailed(StringRef("some error"));
}

TEST_F(RunContextTest_501, BenchmarkFailedWithEmptyError_501) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(::testing::AnyNumber());
    
    Detail::unique_ptr<IEventListener> reporterOwner(mockReporter_);
    
    EXPECT_CALL(*reporterPtr, benchmarkFailed(::testing::_)).Times(1);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterOwner));
    context.benchmarkFailed(StringRef(""));
}

TEST_F(RunContextTest_501, LastAssertionPassedInitiallyFalse_501) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(::testing::AnyNumber());
    
    Detail::unique_ptr<IEventListener> reporterOwner(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterOwner));
    EXPECT_FALSE(context.lastAssertionPassed());
}

TEST_F(RunContextTest_501, AssertionPassedSetsLastAssertionPassed_501) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(::testing::AnyNumber());
    
    Detail::unique_ptr<IEventListener> reporterOwner(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterOwner));
    context.assertionPassed();
    EXPECT_TRUE(context.lastAssertionPassed());
}

TEST_F(RunContextTest_501, GetCurrentTestNameWhenNoActiveTest_501) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(::testing::AnyNumber());
    
    Detail::unique_ptr<IEventListener> reporterOwner(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterOwner));
    std::string name = context.getCurrentTestName();
    EXPECT_TRUE(name.empty());
}

TEST_F(RunContextTest_501, GetLastResultInitiallyNull_501) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(::testing::AnyNumber());
    
    Detail::unique_ptr<IEventListener> reporterOwner(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterOwner));
    EXPECT_EQ(context.getLastResult(), nullptr);
}

TEST_F(RunContextTest_501, AbortingInitiallyFalse_501) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(::testing::AnyNumber());
    
    Detail::unique_ptr<IEventListener> reporterOwner(mockReporter_);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterOwner));
    EXPECT_FALSE(context.aborting());
}

TEST_F(RunContextTest_501, BenchmarkPreparingWithSpecialCharsInName_501) {
    MockReporter* reporterPtr = mockReporter_;
    
    EXPECT_CALL(*reporterPtr, testRunStarting(_)).Times(::testing::AnyNumber());
    EXPECT_CALL(*reporterPtr, testRunEnded(_)).Times(::testing::AnyNumber());
    
    Detail::unique_ptr<IEventListener> reporterOwner(mockReporter_);
    
    EXPECT_CALL(*reporterPtr, benchmarkPreparing(::testing::_)).Times(1);
    
    RunContext context(mockConfig_, CATCH_MOVE(reporterOwner));
    context.benchmarkPreparing(StringRef("bench!@#$%^&*()"));
}

} // anonymous namespace
