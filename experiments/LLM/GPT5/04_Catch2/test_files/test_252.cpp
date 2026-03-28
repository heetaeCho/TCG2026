// File: context_get_result_capture_tests_252.cpp
#include <gtest/gtest.h>

// Include the interface under test.
#include "catch2/internal/catch_context.hpp"

// Forward-declare IResultCapture in the same namespace if not already visible
// (only as an incomplete type; we never define or use its internals).
namespace Catch {
    class IResultCapture; // matches pointer type used by Context
}

using Catch::Context;
using Catch::IResultCapture;

namespace {

// Utility: make a distinct, non-null sentinel pointer value for equality checks.
// We never dereference these; we only observe that the same pointer is returned.
template <std::uintptr_t V>
constexpr IResultCapture* PtrSentinel() {
    return reinterpret_cast<IResultCapture*>(V);
}

} // namespace

// -----------------------------------------------------------------------------

TEST(ContextTest_252, ReturnsNullptrByDefault_252) {
    Context ctx;
    // Observable expectation: default result capture pointer is null.
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

TEST(ContextTest_252, SetAndGetNonNull_252) {
    Context ctx;

    // Provide a distinct, non-null sentinel pointer value.
    IResultCapture* p = PtrSentinel<0x1A2B3C4Du>();
    // Public interaction only: set via setter, read via getter.
    ctx.setResultCapture(p);

    EXPECT_EQ(ctx.getResultCapture(), p);
}

TEST(ContextTest_252, SetNullptrThenGet_252) {
    Context ctx;

    // Set to nullptr explicitly and verify getter reflects it.
    ctx.setResultCapture(nullptr);
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

TEST(ContextTest_252, GetterIsConstCorrect_252) {
    Context ctx;

    IResultCapture* p = PtrSentinel<0x0F0E0D0Cu>();
    ctx.setResultCapture(p);

    // Observe through const reference (const-correct interface).
    const Context& cctx = ctx;
    EXPECT_EQ(cctx.getResultCapture(), p);
}

TEST(ContextTest_252, CleanUpResetsResultCaptureIfSupported_252) {
    Context ctx;

    IResultCapture* p = PtrSentinel<0xABCDEF12u>();
    ctx.setResultCapture(p);
    ASSERT_EQ(ctx.getResultCapture(), p); // precondition observed via public API

    // Call the public clean-up function. We only assert its observable effect.
    ctx.cleanUpContext();

    // Expected observable outcome: result capture no longer set.
    // If cleanUpContext resets the pointer, this should be nullptr.
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}
