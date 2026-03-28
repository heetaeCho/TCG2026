#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_context.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"

// Mock for IResultCapture
class MockResultCapture : public Catch::IResultCapture {
public:
    ~MockResultCapture() override = default;

    MOCK_METHOD(void, notifyAssertionStarted, (const Catch::AssertionInfo&), (override));
    MOCK_METHOD(bool, sectionStarted, (Catch::StringRef, const Catch::SourceLineInfo&, Catch::Counts&), (override));
    MOCK_METHOD(void, sectionEnded, (Catch::SectionEndInfo&&), (override));
    MOCK_METHOD(void, sectionEndedEarly, (Catch::SectionEndInfo&&), (override));
    MOCK_METHOD(Catch::IGeneratorTracker*, acquireGeneratorTracker, (Catch::StringRef, const Catch::SourceLineInfo&), (override));
    MOCK_METHOD(Catch::IGeneratorTracker*, createGeneratorTracker, (Catch::StringRef, Catch::SourceLineInfo, Catch::Generators::GeneratorBasePtr&&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (Catch::StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (const Catch::BenchmarkInfo&), (override));
    MOCK_METHOD(void, benchmarkEnded, (const Catch::BenchmarkStats<>&), (override));
    MOCK_METHOD(void, benchmarkFailed, (Catch::StringRef), (override));
    MOCK_METHOD(void, pushScopedMessage, (const Catch::MessageInfo&), (override));
    MOCK_METHOD(void, popScopedMessage, (const Catch::MessageInfo&), (override));
    MOCK_METHOD(void, emplaceUnscopedMessage, (Catch::MessageBuilder&&), (override));
    MOCK_METHOD(void, handleFatalErrorCondition, (Catch::StringRef), (override));
    MOCK_METHOD(void, handleExpr, (const Catch::AssertionInfo&, const Catch::ITransientExpression&, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleMessage, (const Catch::AssertionInfo&, Catch::ResultWas::OfType, std::string&&, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (const Catch::AssertionInfo&, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedInflightException, (const Catch::AssertionInfo&, std::string&&, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleIncomplete, (const Catch::AssertionInfo&), (override));
    MOCK_METHOD(void, handleNonExpr, (const Catch::AssertionInfo&, Catch::ResultWas::OfType, Catch::AssertionReaction&), (override));
    MOCK_METHOD(bool, lastAssertionPassed, (), (override));
    MOCK_METHOD(void, assertionPassed, (), (override));
    MOCK_METHOD(const std::string, getCurrentTestName, (), (const, override));
    MOCK_METHOD(const Catch::AssertionResult*, getLastResult, (), (const, override));
    MOCK_METHOD(void, exceptionEarlyReported, (), (override));
};

// Mock for IConfig
class MockConfig : public Catch::IConfig {
public:
    ~MockConfig() override = default;
    // IConfig has various pure virtual methods; we provide minimal mocks
    // The exact methods depend on the Catch2 version, but we need at least a compilable mock
};

class ContextTest_254 : public ::testing::Test {
protected:
    void SetUp() override {
        // Clean up and get a fresh mutable context
    }

    void TearDown() override {
        // Reset the context state to avoid leaking between tests
        Catch::getCurrentMutableContext().setResultCapture(nullptr);
        Catch::getCurrentMutableContext().setConfig(nullptr);
    }
};

// Test that setResultCapture stores the pointer and getResultCapture retrieves it
TEST_F(ContextTest_254, SetAndGetResultCapture_254) {
    MockResultCapture mockCapture;
    Catch::Context& ctx = Catch::getCurrentMutableContext();

    ctx.setResultCapture(&mockCapture);

    EXPECT_EQ(ctx.getResultCapture(), &mockCapture);
}

// Test that getResultCapture returns nullptr by default (or after setting to nullptr)
TEST_F(ContextTest_254, GetResultCaptureDefaultIsNull_254) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    ctx.setResultCapture(nullptr);

    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

// Test that setConfig stores the pointer and getConfig retrieves it
TEST_F(ContextTest_254, SetAndGetConfig_254) {
    MockConfig mockConfig;
    Catch::Context& ctx = Catch::getCurrentMutableContext();

    ctx.setConfig(&mockConfig);

    EXPECT_EQ(ctx.getConfig(), &mockConfig);
}

// Test that getConfig returns nullptr by default (or after setting to nullptr)
TEST_F(ContextTest_254, GetConfigDefaultIsNull_254) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    ctx.setConfig(nullptr);

    EXPECT_EQ(ctx.getConfig(), nullptr);
}

// Test that setting result capture to nullptr after having a valid pointer works
TEST_F(ContextTest_254, SetResultCaptureToNullAfterValid_254) {
    MockResultCapture mockCapture;
    Catch::Context& ctx = Catch::getCurrentMutableContext();

    ctx.setResultCapture(&mockCapture);
    EXPECT_EQ(ctx.getResultCapture(), &mockCapture);

    ctx.setResultCapture(nullptr);
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

// Test that setting config to nullptr after having a valid pointer works
TEST_F(ContextTest_254, SetConfigToNullAfterValid_254) {
    MockConfig mockConfig;
    Catch::Context& ctx = Catch::getCurrentMutableContext();

    ctx.setConfig(&mockConfig);
    EXPECT_EQ(ctx.getConfig(), &mockConfig);

    ctx.setConfig(nullptr);
    EXPECT_EQ(ctx.getConfig(), nullptr);
}

// Test that replacing the result capture pointer works correctly
TEST_F(ContextTest_254, ReplaceResultCapture_254) {
    MockResultCapture mockCapture1;
    MockResultCapture mockCapture2;
    Catch::Context& ctx = Catch::getCurrentMutableContext();

    ctx.setResultCapture(&mockCapture1);
    EXPECT_EQ(ctx.getResultCapture(), &mockCapture1);

    ctx.setResultCapture(&mockCapture2);
    EXPECT_EQ(ctx.getResultCapture(), &mockCapture2);
}

// Test that replacing the config pointer works correctly
TEST_F(ContextTest_254, ReplaceConfig_254) {
    MockConfig mockConfig1;
    MockConfig mockConfig2;
    Catch::Context& ctx = Catch::getCurrentMutableContext();

    ctx.setConfig(&mockConfig1);
    EXPECT_EQ(ctx.getConfig(), &mockConfig1);

    ctx.setConfig(&mockConfig2);
    EXPECT_EQ(ctx.getConfig(), &mockConfig2);
}

// Test that getCurrentMutableContext returns the same reference each time
TEST_F(ContextTest_254, GetCurrentMutableContextReturnsSameInstance_254) {
    Catch::Context& ctx1 = Catch::getCurrentMutableContext();
    Catch::Context& ctx2 = Catch::getCurrentMutableContext();

    EXPECT_EQ(&ctx1, &ctx2);
}

// Test that getCurrentContext returns const reference and reflects setResultCapture
TEST_F(ContextTest_254, GetCurrentContextReflectsSetResultCapture_254) {
    MockResultCapture mockCapture;
    Catch::Context& mutableCtx = Catch::getCurrentMutableContext();
    mutableCtx.setResultCapture(&mockCapture);

    const Catch::Context& constCtx = Catch::getCurrentContext();
    EXPECT_EQ(constCtx.getResultCapture(), &mockCapture);
}

// Test that getCurrentContext returns const reference and reflects setConfig
TEST_F(ContextTest_254, GetCurrentContextReflectsSetConfig_254) {
    MockConfig mockConfig;
    Catch::Context& mutableCtx = Catch::getCurrentMutableContext();
    mutableCtx.setConfig(&mockConfig);

    const Catch::Context& constCtx = Catch::getCurrentContext();
    EXPECT_EQ(constCtx.getConfig(), &mockConfig);
}

// Test setting both result capture and config independently
TEST_F(ContextTest_254, SetBothResultCaptureAndConfig_254) {
    MockResultCapture mockCapture;
    MockConfig mockConfig;
    Catch::Context& ctx = Catch::getCurrentMutableContext();

    ctx.setResultCapture(&mockCapture);
    ctx.setConfig(&mockConfig);

    EXPECT_EQ(ctx.getResultCapture(), &mockCapture);
    EXPECT_EQ(ctx.getConfig(), &mockConfig);
}

// Test that setting result capture doesn't affect config
TEST_F(ContextTest_254, SetResultCaptureDoesNotAffectConfig_254) {
    MockResultCapture mockCapture;
    MockConfig mockConfig;
    Catch::Context& ctx = Catch::getCurrentMutableContext();

    ctx.setConfig(&mockConfig);
    ctx.setResultCapture(&mockCapture);

    EXPECT_EQ(ctx.getConfig(), &mockConfig);
}

// Test that setting config doesn't affect result capture
TEST_F(ContextTest_254, SetConfigDoesNotAffectResultCapture_254) {
    MockResultCapture mockCapture;
    MockConfig mockConfig;
    Catch::Context& ctx = Catch::getCurrentMutableContext();

    ctx.setResultCapture(&mockCapture);
    ctx.setConfig(&mockConfig);

    EXPECT_EQ(ctx.getResultCapture(), &mockCapture);
}
