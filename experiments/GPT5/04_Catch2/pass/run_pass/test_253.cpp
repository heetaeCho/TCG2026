// Context_getConfig_tests_253.cpp
#include <gtest/gtest.h>

// Provide minimal interface stubs so we can create pointers without relying on internals.
// These are only to satisfy the type system; we never depend on their behavior.
namespace Catch {
struct IConfig { virtual ~IConfig() = default; };
struct IResultCapture { virtual ~IResultCapture() = default; };
}  // namespace Catch

// Header under test
#include "catch2/internal/catch_context.hpp"

using Catch::Context;
using Catch::IConfig;

class ContextTest_253 : public ::testing::Test {
protected:
    Context ctx_;  // fresh instance for each test
};

// [Normal] Newly constructed context returns nullptr config
TEST_F(ContextTest_253, DefaultConfigIsNull_253) {
    EXPECT_EQ(ctx_.getConfig(), nullptr);
}

// [Normal] setConfig stores the exact pointer and getConfig returns it
TEST_F(ContextTest_253, SetConfigStoresPointer_253) {
    struct DummyConfig : IConfig {} dummy;
    ctx_.setConfig(&dummy);
    EXPECT_EQ(ctx_.getConfig(), &dummy);
}

// [Boundary] Setting config to nullptr clears any previously set value
TEST_F(ContextTest_253, SetConfigToNullClears_253) {
    struct DummyConfig : IConfig {} dummy;
    ctx_.setConfig(&dummy);
    ASSERT_NE(ctx_.getConfig(), nullptr);  // sanity check

    ctx_.setConfig(nullptr);
    EXPECT_EQ(ctx_.getConfig(), nullptr);
}

// [Isolation] Two Context instances do not affect each other’s stored config
TEST_F(ContextTest_253, MultipleInstancesAreIndependent_253) {
    struct DummyConfigA : IConfig {} a;
    struct DummyConfigB : IConfig {} b;

    Context other;
    ctx_.setConfig(&a);
    other.setConfig(&b);

    EXPECT_EQ(ctx_.getConfig(), &a);
    EXPECT_EQ(other.getConfig(), &b);
}

// [Const-correctness] getConfig can be called on a const Context and returns the same pointer
TEST_F(ContextTest_253, ConstGetterReturnsSamePointer_253) {
    struct DummyConfig : IConfig {} dummy;
    ctx_.setConfig(&dummy);

    const Context& cctx = ctx_;
    EXPECT_EQ(cctx.getConfig(), &dummy);
}
