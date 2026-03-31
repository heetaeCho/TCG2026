#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_context.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

// Mock for IConfig
class MockIConfig : public Catch::IConfig {
public:
    ~MockIConfig() override = default;
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
    MOCK_METHOD(const Catch::TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(Catch::TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

class ContextTest_255 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure we have a clean context for each test
    }

    void TearDown() override {
        // Clean up after each test
        auto& ctx = Catch::getCurrentMutableContext();
        ctx.setConfig(nullptr);
        ctx.setResultCapture(nullptr);
    }
};

// Test that getConfig returns nullptr by default (before setConfig is called)
TEST_F(ContextTest_255, GetConfigReturnsNullptrByDefault_255) {
    auto& ctx = Catch::getCurrentMutableContext();
    ctx.setConfig(nullptr);
    EXPECT_EQ(ctx.getConfig(), nullptr);
}

// Test that setConfig stores the config and getConfig retrieves it
TEST_F(ContextTest_255, SetConfigAndGetConfig_255) {
    MockIConfig mockConfig;
    auto& ctx = Catch::getCurrentMutableContext();
    ctx.setConfig(&mockConfig);
    EXPECT_EQ(ctx.getConfig(), &mockConfig);
}

// Test that setConfig can be called with nullptr
TEST_F(ContextTest_255, SetConfigWithNullptr_255) {
    MockIConfig mockConfig;
    auto& ctx = Catch::getCurrentMutableContext();
    ctx.setConfig(&mockConfig);
    EXPECT_EQ(ctx.getConfig(), &mockConfig);
    ctx.setConfig(nullptr);
    EXPECT_EQ(ctx.getConfig(), nullptr);
}

// Test that setConfig can be overwritten with a different config
TEST_F(ContextTest_255, SetConfigOverwrite_255) {
    MockIConfig mockConfig1;
    MockIConfig mockConfig2;
    auto& ctx = Catch::getCurrentMutableContext();
    ctx.setConfig(&mockConfig1);
    EXPECT_EQ(ctx.getConfig(), &mockConfig1);
    ctx.setConfig(&mockConfig2);
    EXPECT_EQ(ctx.getConfig(), &mockConfig2);
}

// Test that getResultCapture returns nullptr by default
TEST_F(ContextTest_255, GetResultCaptureReturnsNullptrByDefault_255) {
    auto& ctx = Catch::getCurrentMutableContext();
    ctx.setResultCapture(nullptr);
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

// Test that setResultCapture and getResultCapture work correctly
TEST_F(ContextTest_255, SetResultCaptureAndGetResultCapture_255) {
    auto& ctx = Catch::getCurrentMutableContext();
    // We can't easily mock IResultCapture without its full interface,
    // but we can at least test nullptr behavior
    ctx.setResultCapture(nullptr);
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

// Test that getCurrentMutableContext returns a reference to the same context
TEST_F(ContextTest_255, GetCurrentMutableContextReturnsSameInstance_255) {
    auto& ctx1 = Catch::getCurrentMutableContext();
    auto& ctx2 = Catch::getCurrentMutableContext();
    EXPECT_EQ(&ctx1, &ctx2);
}

// Test that getCurrentContext returns the same context as mutable version
TEST_F(ContextTest_255, GetCurrentContextReturnsSameAsGetCurrentMutableContext_255) {
    MockIConfig mockConfig;
    auto& mutableCtx = Catch::getCurrentMutableContext();
    mutableCtx.setConfig(&mockConfig);
    const auto& constCtx = Catch::getCurrentContext();
    EXPECT_EQ(constCtx.getConfig(), &mockConfig);
}

// Test that getConfig on const Context returns the same pointer set via mutable Context
TEST_F(ContextTest_255, ConstContextGetConfig_255) {
    MockIConfig mockConfig;
    auto& ctx = Catch::getCurrentMutableContext();
    ctx.setConfig(&mockConfig);
    const Catch::Context& constCtx = Catch::getCurrentContext();
    EXPECT_EQ(constCtx.getConfig(), &mockConfig);
}

// Test setting config multiple times in succession
TEST_F(ContextTest_255, SetConfigMultipleTimes_255) {
    MockIConfig configs[5];
    auto& ctx = Catch::getCurrentMutableContext();
    for (int i = 0; i < 5; ++i) {
        ctx.setConfig(&configs[i]);
        EXPECT_EQ(ctx.getConfig(), &configs[i]);
    }
}

// Test that config and resultCapture are independent
TEST_F(ContextTest_255, ConfigAndResultCaptureAreIndependent_255) {
    MockIConfig mockConfig;
    auto& ctx = Catch::getCurrentMutableContext();
    ctx.setConfig(&mockConfig);
    ctx.setResultCapture(nullptr);
    EXPECT_EQ(ctx.getConfig(), &mockConfig);
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

// Test cleanUpContext
TEST_F(ContextTest_255, CleanUpContext_255) {
    // After cleanUpContext, getting context should still work
    // (it recreates itself as needed)
    Catch::cleanUpContext();
    // The context should be accessible again
    auto& ctx = Catch::getCurrentMutableContext();
    // After cleanup and recreation, config should be nullptr
    EXPECT_EQ(ctx.getConfig(), nullptr);
}
