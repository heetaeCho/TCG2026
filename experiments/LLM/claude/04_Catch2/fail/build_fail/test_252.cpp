#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_context.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

namespace {

// Mock for IResultCapture
class MockResultCapture : public Catch::IResultCapture {
public:
    MOCK_METHOD(bool, sectionStarted, (Catch::StringRef const&, Catch::SourceLineInfo const&, Catch::Counts&), (override));
    MOCK_METHOD(void, sectionEnded, (Catch::SectionEndInfo&&), (override));
    MOCK_METHOD(void, sectionEndedEarly, (Catch::SectionEndInfo&&), (override));
    MOCK_METHOD(auto, acquireGeneratorTracker, (Catch::StringRef, Catch::SourceLineInfo const&) -> Catch::IGeneratorTracker&, (override));
    MOCK_METHOD(void, benchmarkPreparing, (Catch::StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (Catch::BenchmarkInfo const&), (override));
    MOCK_METHOD(void, benchmarkEnded, (Catch::BenchmarkStats<> const&), (override));
    MOCK_METHOD(void, benchmarkFailed, (Catch::StringRef), (override));
    MOCK_METHOD(void, pushScopedMessage, (Catch::MessageInfo const&), (override));
    MOCK_METHOD(void, popScopedMessage, (Catch::MessageInfo const&), (override));
    MOCK_METHOD(void, emplaceUnscopedMessage, (Catch::MessageBuilder&&), (override));
    MOCK_METHOD(void, handleFatalErrorCondition, (Catch::StringRef), (override));
    MOCK_METHOD(void, handleExpr, (Catch::AssertionInfo const&, Catch::ITransientExpression const&, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleMessage, (Catch::AssertionInfo const&, Catch::ResultWas::OfType, Catch::StringRef, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (Catch::AssertionInfo const&, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedInflightException, (Catch::AssertionInfo const&, Catch::StringRef, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleIncomplete, (Catch::AssertionInfo const&, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleNonExpr, (Catch::AssertionInfo const&, Catch::ResultWas::OfType, Catch::AssertionReaction&), (override));
    MOCK_METHOD(bool, lastAssertionPassed, (), (override));
    MOCK_METHOD(void, assertionPassed, (), (override));
    MOCK_METHOD(std::string, getCurrentTestName, (), (const, override));
    MOCK_METHOD(const Catch::AssertionResult*, getLastResult, (), (const, override));
    MOCK_METHOD(void, exceptionEarlyReported, (), (override));
};

// Mock for IConfig
class MockConfig : public Catch::IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(Catch::StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(Catch::TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<Catch::ReporterSpec> const&, getReporterSpecs, (), (const, override));
    MOCK_METHOD(Catch::RngDistribution, benchmarkSamples, (), (const, override));
    MOCK_METHOD(unsigned int, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
};

} // anonymous namespace

class ContextTest_252 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
        Catch::cleanUpContext();
    }
};

TEST_F(ContextTest_252, GetResultCaptureReturnsNullByDefault_252) {
    // A fresh context should have null result capture
    const Catch::Context& ctx = Catch::getCurrentContext();
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

TEST_F(ContextTest_252, GetConfigReturnsNullByDefault_252) {
    // A fresh context should have null config
    const Catch::Context& ctx = Catch::getCurrentContext();
    EXPECT_EQ(ctx.getConfig(), nullptr);
}

TEST_F(ContextTest_252, SetAndGetResultCapture_252) {
    MockResultCapture mockCapture;
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    ctx.setResultCapture(&mockCapture);
    EXPECT_EQ(ctx.getResultCapture(), &mockCapture);
}

TEST_F(ContextTest_252, SetAndGetConfig_252) {
    MockConfig mockConfig;
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    ctx.setConfig(&mockConfig);
    EXPECT_EQ(ctx.getConfig(), &mockConfig);
}

TEST_F(ContextTest_252, SetResultCaptureToNull_252) {
    MockResultCapture mockCapture;
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    ctx.setResultCapture(&mockCapture);
    EXPECT_EQ(ctx.getResultCapture(), &mockCapture);

    ctx.setResultCapture(nullptr);
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

TEST_F(ContextTest_252, SetConfigToNull_252) {
    MockConfig mockConfig;
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    ctx.setConfig(&mockConfig);
    EXPECT_EQ(ctx.getConfig(), &mockConfig);

    ctx.setConfig(nullptr);
    EXPECT_EQ(ctx.getConfig(), nullptr);
}

TEST_F(ContextTest_252, GetCurrentContextAndGetCurrentMutableContextReturnSameObject_252) {
    Catch::Context& mutableCtx = Catch::getCurrentMutableContext();
    const Catch::Context& constCtx = Catch::getCurrentContext();
    EXPECT_EQ(&mutableCtx, &constCtx);
}

TEST_F(ContextTest_252, SetResultCapturePersistsAcrossCalls_252) {
    MockResultCapture mockCapture;
    Catch::getCurrentMutableContext().setResultCapture(&mockCapture);

    // Access via const reference
    const Catch::Context& ctx = Catch::getCurrentContext();
    EXPECT_EQ(ctx.getResultCapture(), &mockCapture);

    // Access via mutable reference again
    Catch::Context& mutableCtx = Catch::getCurrentMutableContext();
    EXPECT_EQ(mutableCtx.getResultCapture(), &mockCapture);
}

TEST_F(ContextTest_252, SetConfigPersistsAcrossCalls_252) {
    MockConfig mockConfig;
    Catch::getCurrentMutableContext().setConfig(&mockConfig);

    const Catch::Context& ctx = Catch::getCurrentContext();
    EXPECT_EQ(ctx.getConfig(), &mockConfig);
}

TEST_F(ContextTest_252, OverwriteResultCapture_252) {
    MockResultCapture mockCapture1;
    MockResultCapture mockCapture2;
    Catch::Context& ctx = Catch::getCurrentMutableContext();

    ctx.setResultCapture(&mockCapture1);
    EXPECT_EQ(ctx.getResultCapture(), &mockCapture1);

    ctx.setResultCapture(&mockCapture2);
    EXPECT_EQ(ctx.getResultCapture(), &mockCapture2);
}

TEST_F(ContextTest_252, OverwriteConfig_252) {
    MockConfig mockConfig1;
    MockConfig mockConfig2;
    Catch::Context& ctx = Catch::getCurrentMutableContext();

    ctx.setConfig(&mockConfig1);
    EXPECT_EQ(ctx.getConfig(), &mockConfig1);

    ctx.setConfig(&mockConfig2);
    EXPECT_EQ(ctx.getConfig(), &mockConfig2);
}

TEST_F(ContextTest_252, SetBothResultCaptureAndConfig_252) {
    MockResultCapture mockCapture;
    MockConfig mockConfig;
    Catch::Context& ctx = Catch::getCurrentMutableContext();

    ctx.setResultCapture(&mockCapture);
    ctx.setConfig(&mockConfig);

    EXPECT_EQ(ctx.getResultCapture(), &mockCapture);
    EXPECT_EQ(ctx.getConfig(), &mockConfig);
}

TEST_F(ContextTest_252, CleanUpContextAndReacquire_252) {
    MockResultCapture mockCapture;
    MockConfig mockConfig;

    {
        Catch::Context& ctx = Catch::getCurrentMutableContext();
        ctx.setResultCapture(&mockCapture);
        ctx.setConfig(&mockConfig);
    }

    Catch::cleanUpContext();

    // After cleanup, getting context again should give a fresh context
    const Catch::Context& ctx = Catch::getCurrentContext();
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
    EXPECT_EQ(ctx.getConfig(), nullptr);
}
