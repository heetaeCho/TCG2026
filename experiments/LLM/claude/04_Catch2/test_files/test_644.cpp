#include <gtest/gtest.h>
#include "catch2/internal/catch_context.hpp"

namespace {

// Test fixture for Context tests
class ContextTest_644 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure we have a clean context for each test
    }

    void TearDown() override {
        // Clean up context after each test
        Catch::cleanUpContext();
    }
};

// Test that getCurrentMutableContext returns a valid reference
TEST_F(ContextTest_644, GetCurrentMutableContextReturnsValidReference_644) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    // Should not crash and should return a valid reference
    // We verify by calling a method on it
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

// Test that getCurrentContext returns a valid const reference
TEST_F(ContextTest_644, GetCurrentContextReturnsValidConstReference_644) {
    const Catch::Context& ctx = Catch::getCurrentContext();
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

// Test that initial config is nullptr
TEST_F(ContextTest_644, InitialConfigIsNull_644) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    EXPECT_EQ(ctx.getConfig(), nullptr);
}

// Test that initial result capture is nullptr
TEST_F(ContextTest_644, InitialResultCaptureIsNull_644) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

// Test that setConfig sets the config pointer correctly
TEST_F(ContextTest_644, SetConfigSetsConfigPointer_644) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    // We need a mock or dummy IConfig. Since we can't easily create one,
    // we use a cast of a non-null address to verify the pointer is stored.
    // This is just to verify the set/get contract.
    Catch::IConfig const* dummyConfig = reinterpret_cast<Catch::IConfig const*>(0x12345678);
    ctx.setConfig(dummyConfig);
    EXPECT_EQ(ctx.getConfig(), dummyConfig);
}

// Test that setResultCapture sets the result capture pointer correctly
TEST_F(ContextTest_644, SetResultCaptureSetsResultCapturePointer_644) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    Catch::IResultCapture* dummyCapture = reinterpret_cast<Catch::IResultCapture*>(0x87654321);
    ctx.setResultCapture(dummyCapture);
    EXPECT_EQ(ctx.getResultCapture(), dummyCapture);
}

// Test that setConfig with nullptr works
TEST_F(ContextTest_644, SetConfigToNullptr_644) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    Catch::IConfig const* dummyConfig = reinterpret_cast<Catch::IConfig const*>(0x12345678);
    ctx.setConfig(dummyConfig);
    EXPECT_EQ(ctx.getConfig(), dummyConfig);
    ctx.setConfig(nullptr);
    EXPECT_EQ(ctx.getConfig(), nullptr);
}

// Test that setResultCapture with nullptr works
TEST_F(ContextTest_644, SetResultCaptureToNullptr_644) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    Catch::IResultCapture* dummyCapture = reinterpret_cast<Catch::IResultCapture*>(0x87654321);
    ctx.setResultCapture(dummyCapture);
    EXPECT_EQ(ctx.getResultCapture(), dummyCapture);
    ctx.setResultCapture(nullptr);
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

// Test that getCurrentMutableContext returns the same context on multiple calls
TEST_F(ContextTest_644, GetCurrentMutableContextReturnsSameInstance_644) {
    Catch::Context& ctx1 = Catch::getCurrentMutableContext();
    Catch::Context& ctx2 = Catch::getCurrentMutableContext();
    EXPECT_EQ(&ctx1, &ctx2);
}

// Test that mutable and const context return the same instance
TEST_F(ContextTest_644, MutableAndConstContextAreSameInstance_644) {
    Catch::Context& mutableCtx = Catch::getCurrentMutableContext();
    const Catch::Context& constCtx = Catch::getCurrentContext();
    EXPECT_EQ(&mutableCtx, &constCtx);
}

// Test that cleanUpContext and re-getting context works
TEST_F(ContextTest_644, CleanUpAndRecreateContext_644) {
    Catch::Context& ctx1 = Catch::getCurrentMutableContext();
    Catch::IConfig const* dummyConfig = reinterpret_cast<Catch::IConfig const*>(0x12345678);
    ctx1.setConfig(dummyConfig);
    EXPECT_EQ(ctx1.getConfig(), dummyConfig);

    Catch::cleanUpContext();

    // After cleanup, getting context should create a new one with defaults
    Catch::Context& ctx2 = Catch::getCurrentMutableContext();
    EXPECT_EQ(ctx2.getConfig(), nullptr);
    EXPECT_EQ(ctx2.getResultCapture(), nullptr);
}

// Test that const getConfig works through const reference
TEST_F(ContextTest_644, ConstContextGetConfig_644) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    Catch::IConfig const* dummyConfig = reinterpret_cast<Catch::IConfig const*>(0xABCDEF00);
    ctx.setConfig(dummyConfig);

    const Catch::Context& constCtx = Catch::getCurrentContext();
    EXPECT_EQ(constCtx.getConfig(), dummyConfig);
}

// Test that const getResultCapture works through const reference
TEST_F(ContextTest_644, ConstContextGetResultCapture_644) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();
    Catch::IResultCapture* dummyCapture = reinterpret_cast<Catch::IResultCapture*>(0xABCDEF00);
    ctx.setResultCapture(dummyCapture);

    const Catch::Context& constCtx = Catch::getCurrentContext();
    EXPECT_EQ(constCtx.getResultCapture(), dummyCapture);
}

// Test overwriting config multiple times
TEST_F(ContextTest_644, OverwriteConfigMultipleTimes_644) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();

    Catch::IConfig const* config1 = reinterpret_cast<Catch::IConfig const*>(0x11111111);
    Catch::IConfig const* config2 = reinterpret_cast<Catch::IConfig const*>(0x22222222);
    Catch::IConfig const* config3 = reinterpret_cast<Catch::IConfig const*>(0x33333333);

    ctx.setConfig(config1);
    EXPECT_EQ(ctx.getConfig(), config1);

    ctx.setConfig(config2);
    EXPECT_EQ(ctx.getConfig(), config2);

    ctx.setConfig(config3);
    EXPECT_EQ(ctx.getConfig(), config3);
}

// Test overwriting result capture multiple times
TEST_F(ContextTest_644, OverwriteResultCaptureMultipleTimes_644) {
    Catch::Context& ctx = Catch::getCurrentMutableContext();

    Catch::IResultCapture* capture1 = reinterpret_cast<Catch::IResultCapture*>(0x11111111);
    Catch::IResultCapture* capture2 = reinterpret_cast<Catch::IResultCapture*>(0x22222222);
    Catch::IResultCapture* capture3 = reinterpret_cast<Catch::IResultCapture*>(0x33333333);

    ctx.setResultCapture(capture1);
    EXPECT_EQ(ctx.getResultCapture(), capture1);

    ctx.setResultCapture(capture2);
    EXPECT_EQ(ctx.getResultCapture(), capture2);

    ctx.setResultCapture(capture3);
    EXPECT_EQ(ctx.getResultCapture(), capture3);
}

} // namespace
