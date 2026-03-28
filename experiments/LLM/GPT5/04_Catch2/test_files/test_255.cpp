// tests/context_set_config_tests_255.cpp

#include <gtest/gtest.h>

//
// We only interact with the public interface of Catch::Context.
// To avoid depending on internal details, we forward-declare the
// collaborator types we pass/observe as pointers.
//
namespace Catch {
    class IConfig;         // forward-declared collaborator (pointer-only use)
    class IResultCapture;  // forward-declared collaborator (pointer-only use)

    // Include the header that declares Catch::Context and its public API.
    // If your project layout differs, adjust the include path accordingly.
    #include "catch2/internal/catch_context.hpp"
}

// A simple fixture for clarity; no special setup required.
class ContextSetConfigTest_255 : public ::testing::Test {};

// [Normal operation] Setting a non-null config pointer is observable via getConfig().
TEST_F(ContextSetConfigTest_255, SetNonNullPointer_ReflectsViaGetConfig_255) {
    Catch::Context ctx;

    // Use distinct, non-dereferenced sentinel addresses. We never dereference them;
    // they are used purely to test pointer identity through the public API.
    auto* const p1 = reinterpret_cast<const Catch::IConfig*>(0x1);

    ctx.setConfig(p1);
    EXPECT_EQ(ctx.getConfig(), p1);
}

// [Boundary] Setting nullptr should be observable via getConfig() returning nullptr.
TEST_F(ContextSetConfigTest_255, SetNullPointer_YieldsNullFromGetConfig_255) {
    Catch::Context ctx;

    ctx.setConfig(nullptr);
    EXPECT_EQ(ctx.getConfig(), nullptr);
}

// [Overwrite behavior] Setting a new pointer should overwrite the prior one.
TEST_F(ContextSetConfigTest_255, OverwriteExistingPointer_ReflectsLatestValue_255) {
    Catch::Context ctx;

    auto* const p1 = reinterpret_cast<const Catch::IConfig*>(0x1);
    auto* const p2 = reinterpret_cast<const Catch::IConfig*>(0x2);

    ctx.setConfig(p1);
    EXPECT_EQ(ctx.getConfig(), p1);

    ctx.setConfig(p2);
    EXPECT_EQ(ctx.getConfig(), p2);
}

// [Non-interference] setConfig should not affect unrelated collaborators exposed by the interface.
// We verify getResultCapture() returns the same value before/after setConfig().
TEST_F(ContextSetConfigTest_255, SetConfig_DoesNotChangeResultCapture_255) {
    Catch::Context ctx;

    // Snapshot whatever the current observable result-capture pointer is
    // (likely nullptr in a fresh context, but we only rely on the public API).
    auto* const before = ctx.getResultCapture();

    // Change config and ensure resultCapture is unchanged via public getter.
    auto* const configPtr = reinterpret_cast<const Catch::IConfig*>(0x3);
    ctx.setConfig(configPtr);

    EXPECT_EQ(ctx.getResultCapture(), before);
}
