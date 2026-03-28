#include "catch2/internal/catch_context.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// We need to work with the Context class through its public interface.
// Since IConfig and IResultCapture are interfaces, we create mock implementations.

namespace {

class MockConfig : public Catch::IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(Catch::StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutNoTests, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(Catch::TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<Catch::ReporterSpec> const&, getReporterSpecs, (), (const, override));
    MOCK_METHOD(Catch::RngSeed const&, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
};

} // anonymous namespace

class ContextTest_253 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(ContextTest_253, GetConfigReturnsNullByDefault_253) {
    // A default-constructed Context should have m_config == nullptr
    Catch::Context ctx;
    EXPECT_EQ(ctx.getConfig(), nullptr);
}

TEST_F(ContextTest_253, SetConfigAndGetConfig_253) {
    Catch::Context ctx;
    MockConfig mockConfig;
    
    ctx.setConfig(&mockConfig);
    EXPECT_EQ(ctx.getConfig(), &mockConfig);
}

TEST_F(ContextTest_253, SetConfigToNullptr_253) {
    Catch::Context ctx;
    MockConfig mockConfig;
    
    ctx.setConfig(&mockConfig);
    EXPECT_EQ(ctx.getConfig(), &mockConfig);
    
    ctx.setConfig(nullptr);
    EXPECT_EQ(ctx.getConfig(), nullptr);
}

TEST_F(ContextTest_253, SetConfigMultipleTimes_253) {
    Catch::Context ctx;
    MockConfig config1;
    MockConfig config2;
    
    ctx.setConfig(&config1);
    EXPECT_EQ(ctx.getConfig(), &config1);
    
    ctx.setConfig(&config2);
    EXPECT_EQ(ctx.getConfig(), &config2);
}

TEST_F(ContextTest_253, GetResultCaptureReturnsNullByDefault_253) {
    Catch::Context ctx;
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

TEST_F(ContextTest_253, SetAndGetResultCapture_253) {
    // We can't easily mock IResultCapture without knowing all its pure virtuals,
    // but we can test setting to nullptr and checking
    Catch::Context ctx;
    
    ctx.setResultCapture(nullptr);
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

TEST_F(ContextTest_253, GetCurrentMutableContextReturnsSameInstance_253) {
    // getCurrentMutableContext should return a consistent reference
    Catch::Context& ctx1 = Catch::getCurrentMutableContext();
    Catch::Context& ctx2 = Catch::getCurrentMutableContext();
    EXPECT_EQ(&ctx1, &ctx2);
}

TEST_F(ContextTest_253, GetCurrentContextReturnsSameAsGetCurrentMutableContext_253) {
    Catch::Context& mutableCtx = Catch::getCurrentMutableContext();
    const Catch::Context& constCtx = Catch::getCurrentContext();
    EXPECT_EQ(&mutableCtx, &constCtx);
}

TEST_F(ContextTest_253, SetConfigOnGlobalContext_253) {
    MockConfig mockConfig;
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    
    const Catch::IConfig* previousConfig = ctx.getConfig();
    
    ctx.setConfig(&mockConfig);
    EXPECT_EQ(Catch::getCurrentContext().getConfig(), &mockConfig);
    
    // Restore previous state
    ctx.setConfig(previousConfig);
}

TEST_F(ContextTest_253, ConfigPointerIdentity_253) {
    // Verify that getConfig returns the exact same pointer that was set
    Catch::Context ctx;
    MockConfig mockConfig;
    
    ctx.setConfig(&mockConfig);
    const Catch::IConfig* retrieved = ctx.getConfig();
    EXPECT_TRUE(retrieved == &mockConfig);
}

TEST_F(ContextTest_253, IndependentContextInstances_253) {
    // Two separately constructed Context objects should be independent
    Catch::Context ctx1;
    Catch::Context ctx2;
    MockConfig config1;
    
    ctx1.setConfig(&config1);
    EXPECT_EQ(ctx1.getConfig(), &config1);
    EXPECT_EQ(ctx2.getConfig(), nullptr);
}
