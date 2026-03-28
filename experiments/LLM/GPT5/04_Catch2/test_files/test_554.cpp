// File: assertion_handler_complete_tests_554.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// --- Configure a hook for debug-break detection in tests
// We do this BEFORE including the code under test so the macro is visible here.
// This does not re-implement any internal logic; it merely observes whether the
// external macro hook gets invoked.
static bool g_debugBreakInvoked_554 = false;
#ifndef CATCH_BREAK_INTO_DEBUGGER
#define CATCH_BREAK_INTO_DEBUGGER() do { g_debugBreakInvoked_554 = true; } while(0)
#endif

// Forward declare the exception throw helpers so we can detect which path fired.
// These names are used by Catch2 internally; providing test-visible throw types
// lets us assert precisely which path was taken while keeping the tested logic
// as a black box.
namespace Catch {
    struct TestFailureException_554 : std::exception {
        const char* what() const noexcept override { return "test-failure"; }
    };
    struct TestSkipException_554 : std::exception {
        const char* what() const noexcept override { return "test-skip"; }
    };

    // Provide test versions of the throwing functions that the implementation calls.
    // The production ones throw Catch2-specific exceptions; here we throw distinct
    // types so tests can distinguish them unambiguously.
    inline void throw_test_failure_exception() {
        throw TestFailureException_554{};
    }
    inline void throw_test_skip_exception() {
        throw TestSkipException_554{};
    }
} // namespace Catch

// Now include the Catch2 declarations you use in construction.
// Keep this minimal and from your project’s Catch2 headers.
#include <catch2/internal/catch_source_line_info.hpp>
#include <catch2/internal/catch_stringref.hpp>
#include <catch2/internal/catch_assertion_handler.hpp>

// Finally, include the implementation unit containing complete().
#include <catch2/internal/catch_assertion_handler.cpp>

using namespace Catch;
using ::testing::AnyOf;

// A small helper to create a valid AssertionHandler using the public ctor.
static AssertionHandler makeHandler_554(const char* macroName = "TEST_MACRO",
                                        const char* captured = "expr",
                                        ResultDisposition::Flags disp = ResultDisposition::Normal) {
    SourceLineInfo sli{__FILE__, static_cast<std::size_t>(__LINE__)};
    return AssertionHandler(StringRef(macroName), sli, StringRef(captured), disp);
}

class AssertionHandlerCompleteTest_554 : public ::testing::Test {
protected:
    void SetUp() override {
        g_debugBreakInvoked_554 = false;
    }
};

// 1) Baseline: with no prior failure/skip indications, complete() should not throw
// and should not trigger the debug-break hook.
TEST_F(AssertionHandlerCompleteTest_554, Complete_NoThrowNoSkip_NoBreak_554) {
    auto ah = makeHandler_554();

    // No preconditioning via handle* calls -> normal path.
    EXPECT_NO_THROW(ah.complete());
    EXPECT_FALSE(g_debugBreakInvoked_554);
}

// 2) If a failing condition was reported via public API, complete() should
// propagate it as a failure exception (observable via our test throw type).
TEST_F(AssertionHandlerCompleteTest_554, Complete_WithFailure_ThrowsFailureException_554) {
    auto ah = makeHandler_554();

    // Use a public method that represents a failing outcome.
    // (We are not asserting any internals, just driving the public surface.)
    ah.handleUnexpectedExceptionNotThrown();

    EXPECT_THROW({
        ah.complete();
    }, Catch::TestFailureException_554);
}

// 3) If a skip condition was reported via public API, complete() should
// throw the skip exception (observable via our test throw type).
TEST_F(AssertionHandlerCompleteTest_554, Complete_WithSkip_ThrowsSkipException_554) {
    auto ah = makeHandler_554();

    // Public API signaling the throwing call was intentionally skipped.
    ah.handleThrowingCallSkipped();

    EXPECT_THROW({
        ah.complete();
    }, Catch::TestSkipException_554);
}

// 4) Precedence: if both failure and skip were signaled, the code path in the
// provided snippet checks `shouldThrow` before `shouldSkip`. This means failure
// should win over skip as an observable outcome.
TEST_F(AssertionHandlerCompleteTest_554, Complete_FailureBeatsSkip_Priority_554) {
    auto ah = makeHandler_554();

    // Drive both conditions via public API calls (order here should not matter
    // for our assertion of precedence at completion time).
    ah.handleThrowingCallSkipped();
    ah.handleUnexpectedExceptionNotThrown();

    EXPECT_THROW({
        ah.complete();
    }, Catch::TestFailureException_554);
}

// 5) (Non-invasive) If a failure occurs, we still don’t assert the debug-break
// behavior because it is environment/config dependent. However, we do verify
// that our hook is not spuriously invoked in the normal case (covered in test #1).
// If you wish to positively assert debug-break invocation under your build flags,
// you can enable a configuration that sets shouldDebugBreak via public API before
// calling complete(), then EXPECT_TRUE(g_debugBreakInvoked_554). This stays within
// black-box constraints because it observes only the macro side effect.
