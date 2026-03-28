#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_context.hpp"
#include "catch2/internal/catch_run_context.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

namespace {

// Mock for IResultCapture to use as a collaborator
class MockResultCapture : public Catch::IResultCapture {
public:
    MOCK_METHOD(bool, sectionStarted, (Catch::StringRef, Catch::SourceLineInfo const&, Catch::Counts&), (override));
    MOCK_METHOD(void, sectionEnded, (Catch::SectionEndInfo&&), (override));
    MOCK_METHOD(void, sectionEndedEarly, (Catch::SectionEndInfo&&), (override));
    MOCK_METHOD(auto, acquireGeneratorTracker, (Catch::StringRef, Catch::SourceLineInfo const&), (override));
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

class ContextTest_521 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure context is in a clean state
        auto& ctx = Catch::getCurrentMutableContext();
        ctx.setResultCapture(nullptr);
        ctx.setConfig(nullptr);
    }

    void TearDown() override {
        auto& ctx = Catch::getCurrentMutableContext();
        ctx.setResultCapture(nullptr);
        ctx.setConfig(nullptr);
    }
};

// Test that getResultCapture returns the set result capture
TEST_F(ContextTest_521, GetResultCaptureReturnsSetCapture_521) {
    MockResultCapture mockCapture;
    auto& ctx = Catch::getCurrentMutableContext();
    ctx.setResultCapture(&mockCapture);
    
    Catch::IResultCapture& result = Catch::getResultCapture();
    EXPECT_EQ(&result, &mockCapture);
}

// Test that getResultCapture throws/errors when no capture is set
TEST_F(ContextTest_521, GetResultCaptureThrowsWhenNull_521) {
    auto& ctx = Catch::getCurrentMutableContext();
    ctx.setResultCapture(nullptr);
    
    EXPECT_ANY_THROW(Catch::getResultCapture());
}

// Test Context::getResultCapture returns nullptr by default
TEST_F(ContextTest_521, ContextGetResultCaptureReturnsNullByDefault_521) {
    auto& ctx = Catch::getCurrentMutableContext();
    ctx.setResultCapture(nullptr);
    
    const auto& constCtx = Catch::getCurrentContext();
    EXPECT_EQ(constCtx.getResultCapture(), nullptr);
}

// Test Context::setResultCapture and getResultCapture round-trip
TEST_F(ContextTest_521, ContextSetAndGetResultCapture_521) {
    MockResultCapture mockCapture;
    auto& ctx = Catch::getCurrentMutableContext();
    ctx.setResultCapture(&mockCapture);
    
    const auto& constCtx = Catch::getCurrentContext();
    EXPECT_EQ(constCtx.getResultCapture(), &mockCapture);
}

// Test Context::getConfig returns nullptr by default
TEST_F(ContextTest_521, ContextGetConfigReturnsNullByDefault_521) {
    const auto& ctx = Catch::getCurrentContext();
    EXPECT_EQ(ctx.getConfig(), nullptr);
}

// Test that setResultCapture can be called multiple times
TEST_F(ContextTest_521, SetResultCaptureCanBeCalledMultipleTimes_521) {
    MockResultCapture mockCapture1;
    MockResultCapture mockCapture2;
    
    auto& ctx = Catch::getCurrentMutableContext();
    
    ctx.setResultCapture(&mockCapture1);
    EXPECT_EQ(Catch::getCurrentContext().getResultCapture(), &mockCapture1);
    
    ctx.setResultCapture(&mockCapture2);
    EXPECT_EQ(Catch::getCurrentContext().getResultCapture(), &mockCapture2);
}

// Test that getResultCapture returns reference to correct object after change
TEST_F(ContextTest_521, GetResultCaptureReflectsLatestSet_521) {
    MockResultCapture mockCapture1;
    MockResultCapture mockCapture2;
    
    auto& ctx = Catch::getCurrentMutableContext();
    
    ctx.setResultCapture(&mockCapture1);
    Catch::IResultCapture& result1 = Catch::getResultCapture();
    EXPECT_EQ(&result1, &mockCapture1);
    
    ctx.setResultCapture(&mockCapture2);
    Catch::IResultCapture& result2 = Catch::getResultCapture();
    EXPECT_EQ(&result2, &mockCapture2);
}

// Test that getCurrentContext and getCurrentMutableContext refer to the same context
TEST_F(ContextTest_521, MutableAndConstContextAreSame_521) {
    MockResultCapture mockCapture;
    auto& mutableCtx = Catch::getCurrentMutableContext();
    mutableCtx.setResultCapture(&mockCapture);
    
    const auto& constCtx = Catch::getCurrentContext();
    EXPECT_EQ(constCtx.getResultCapture(), &mockCapture);
}

// Test setting result capture back to nullptr after being set
TEST_F(ContextTest_521, SetResultCaptureBackToNull_521) {
    MockResultCapture mockCapture;
    auto& ctx = Catch::getCurrentMutableContext();
    
    ctx.setResultCapture(&mockCapture);
    EXPECT_NE(Catch::getCurrentContext().getResultCapture(), nullptr);
    
    ctx.setResultCapture(nullptr);
    EXPECT_EQ(Catch::getCurrentContext().getResultCapture(), nullptr);
    
    EXPECT_ANY_THROW(Catch::getResultCapture());
}

} // anonymous namespace
