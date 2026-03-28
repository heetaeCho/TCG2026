#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_context.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

namespace {

// Test fixture for Context tests
class ContextTest_256 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure context exists
    }

    void TearDown() override {
        // Clean up if needed
    }
};

// Test that getCurrentContext returns a valid reference
TEST_F(ContextTest_256, GetCurrentContextReturnsValidReference_256) {
    const Catch::Context& ctx = Catch::getCurrentContext();
    // If we get here without crashing, the context was created successfully
    SUCCEED();
}

// Test that getCurrentContext can be called multiple times and returns consistently
TEST_F(ContextTest_256, GetCurrentContextIsConsistentAcrossMultipleCalls_256) {
    const Catch::Context& ctx1 = Catch::getCurrentContext();
    const Catch::Context& ctx2 = Catch::getCurrentContext();
    // Both calls should return the same context object
    EXPECT_EQ(&ctx1, &ctx2);
}

// Test that getResultCapture returns nullptr by default
TEST_F(ContextTest_256, DefaultResultCaptureIsNull_256) {
    const Catch::Context& ctx = Catch::getCurrentContext();
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

// Test that getConfig returns nullptr by default
TEST_F(ContextTest_256, DefaultConfigIsNull_256) {
    const Catch::Context& ctx = Catch::getCurrentContext();
    EXPECT_EQ(ctx.getConfig(), nullptr);
}

// Test that getCurrentMutableContext returns a mutable reference
TEST_F(ContextTest_256, GetCurrentMutableContextReturnsMutableReference_256) {
    Catch::Context& mutableCtx = Catch::getCurrentMutableContext();
    const Catch::Context& constCtx = Catch::getCurrentContext();
    // Both should refer to the same object
    EXPECT_EQ(&mutableCtx, &constCtx);
}

// Test that setConfig sets the config and getConfig retrieves it
TEST_F(ContextTest_256, SetAndGetConfig_256) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    
    // Save original to restore later
    const Catch::IConfig* originalConfig = ctx.getConfig();
    
    // Use a fake pointer value (we won't dereference it)
    const Catch::IConfig* fakeConfig = reinterpret_cast<const Catch::IConfig*>(0xDEADBEEF);
    ctx.setConfig(fakeConfig);
    
    EXPECT_EQ(ctx.getConfig(), fakeConfig);
    
    // Restore original
    ctx.setConfig(originalConfig);
}

// Test that setResultCapture sets the result capture and getResultCapture retrieves it
TEST_F(ContextTest_256, SetAndGetResultCapture_256) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    
    // Save original to restore later
    Catch::IResultCapture* originalCapture = ctx.getResultCapture();
    
    // Use a fake pointer value (we won't dereference it)
    Catch::IResultCapture* fakeCapture = reinterpret_cast<Catch::IResultCapture*>(0xCAFEBABE);
    ctx.setResultCapture(fakeCapture);
    
    EXPECT_EQ(ctx.getResultCapture(), fakeCapture);
    
    // Restore original
    ctx.setResultCapture(originalCapture);
}

// Test that setConfig with nullptr works
TEST_F(ContextTest_256, SetConfigToNull_256) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    
    const Catch::IConfig* originalConfig = ctx.getConfig();
    
    ctx.setConfig(nullptr);
    EXPECT_EQ(ctx.getConfig(), nullptr);
    
    // Restore original
    ctx.setConfig(originalConfig);
}

// Test that setResultCapture with nullptr works
TEST_F(ContextTest_256, SetResultCaptureToNull_256) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    
    Catch::IResultCapture* originalCapture = ctx.getResultCapture();
    
    ctx.setResultCapture(nullptr);
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
    
    // Restore original
    ctx.setResultCapture(originalCapture);
}

// Test that the const version of getCurrentContext returns the same config as mutable
TEST_F(ContextTest_256, ConstAndMutableContextShareSameConfig_256) {
    Catch::Context& mutableCtx = Catch::getCurrentMutableContext();
    const Catch::Context& constCtx = Catch::getCurrentContext();
    
    const Catch::IConfig* originalConfig = constCtx.getConfig();
    
    const Catch::IConfig* fakeConfig = reinterpret_cast<const Catch::IConfig*>(0x12345678);
    mutableCtx.setConfig(fakeConfig);
    
    EXPECT_EQ(constCtx.getConfig(), fakeConfig);
    
    // Restore
    mutableCtx.setConfig(originalConfig);
}

// Test that the const version of getCurrentContext returns the same result capture as mutable
TEST_F(ContextTest_256, ConstAndMutableContextShareSameResultCapture_256) {
    Catch::Context& mutableCtx = Catch::getCurrentMutableContext();
    const Catch::Context& constCtx = Catch::getCurrentContext();
    
    Catch::IResultCapture* originalCapture = constCtx.getResultCapture();
    
    Catch::IResultCapture* fakeCapture = reinterpret_cast<Catch::IResultCapture*>(0x87654321);
    mutableCtx.setResultCapture(fakeCapture);
    
    EXPECT_EQ(constCtx.getResultCapture(), fakeCapture);
    
    // Restore
    mutableCtx.setResultCapture(originalCapture);
}

// Test cleanUpContext and then re-accessing context
TEST_F(ContextTest_256, CleanUpAndReCreateContext_256) {
    // First ensure context exists
    const Catch::Context& ctx1 = Catch::getCurrentContext();
    (void)ctx1;
    
    // Clean up
    Catch::cleanUpContext();
    
    // After cleanup, getCurrentContext should re-create context
    const Catch::Context& ctx2 = Catch::getCurrentContext();
    
    // New context should have null defaults
    EXPECT_EQ(ctx2.getResultCapture(), nullptr);
    EXPECT_EQ(ctx2.getConfig(), nullptr);
}

// Test that setting values, cleaning up, and re-getting context resets values
TEST_F(ContextTest_256, CleanUpResetsValues_256) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    
    const Catch::IConfig* fakeConfig = reinterpret_cast<const Catch::IConfig*>(0xAAAAAAAA);
    Catch::IResultCapture* fakeCapture = reinterpret_cast<Catch::IResultCapture*>(0xBBBBBBBB);
    
    ctx.setConfig(fakeConfig);
    ctx.setResultCapture(fakeCapture);
    
    EXPECT_EQ(ctx.getConfig(), fakeConfig);
    EXPECT_EQ(ctx.getResultCapture(), fakeCapture);
    
    Catch::cleanUpContext();
    
    // After cleanup, the new context should have null values
    const Catch::Context& newCtx = Catch::getCurrentContext();
    EXPECT_EQ(newCtx.getConfig(), nullptr);
    EXPECT_EQ(newCtx.getResultCapture(), nullptr);
}

} // anonymous namespace
