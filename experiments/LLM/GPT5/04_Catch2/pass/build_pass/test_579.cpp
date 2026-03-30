// File: tests/test_uncaught_exceptions_579.cpp
#include <gtest/gtest.h>
#include <exception>

// Forward declaration based on the provided interface/signature.
namespace Catch {
    bool uncaught_exceptions();
}

#if !defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)
// Helper: observe Catch::uncaught_exceptions() during stack unwinding.
static bool ObserveDuringUnwind_Catch() {
    bool observed = false;
    struct Probe {
        bool& out;
        ~Probe() { out = Catch::uncaught_exceptions(); }
    };

    auto throw_and_unwind = [&]() {
        Probe p{observed};
        throw 42; // force unwinding
    };

    try {
        throw_and_unwind();
    } catch (...) {
        // swallow
    }
    return observed;
}

#if defined(CATCH_CONFIG_CPP17_UNCAUGHT_EXCEPTIONS)
// Helper: capture Catch vs std during unwinding in C++17 mode.
static std::pair<bool, bool> ObserveDuringUnwind_CatchVsStd() {
    std::pair<bool, bool> observed{false, false};
    struct Probe {
        std::pair<bool, bool>& out;
        ~Probe() {
            out.first  = Catch::uncaught_exceptions();
            out.second = std::uncaught_exceptions() > 0;
        }
    };

    auto throw_and_unwind = [&]() {
        Probe p{observed};
        throw 7;
    };

    try {
        throw_and_unwind();
    } catch (...) {
    }
    return observed;
}
#else
// Helper: capture Catch vs std during unwinding in pre-C++17 mode.
static std::pair<bool, bool> ObserveDuringUnwind_CatchVsStd() {
    std::pair<bool, bool> observed{false, false};
    struct Probe {
        std::pair<bool, bool>& out;
        ~Probe() {
            out.first  = Catch::uncaught_exceptions();
            out.second = std::uncaught_exception();
        }
    };

    auto throw_and_unwind = [&]() {
        Probe p{observed};
        throw 7;
    };

    try {
        throw_and_unwind();
    } catch (...) {
    }
    return observed;
}
#endif // CATCH_CONFIG_CPP17_UNCAUGHT_EXCEPTIONS
#endif // !CATCH_CONFIG_DISABLE_EXCEPTIONS

// ----------------------------- Tests -----------------------------

#if defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)

// When exceptions are disabled, the function must always report false.
TEST(UncaughtExceptionsTest_579, AlwaysFalseWhenExceptionsDisabled_579) {
    EXPECT_FALSE(Catch::uncaught_exceptions());
}

#else // exceptions enabled

// Normal operation: outside of any exception, it should be false.
TEST(UncaughtExceptionsTest_579, ReturnsFalseWhenNoExceptionActive_579) {
    EXPECT_FALSE(Catch::uncaught_exceptions());
}

// Observable behavior during unwinding: should be true while an exception is propagating.
TEST(UncaughtExceptionsTest_579, ReturnsTrueDuringExceptionUnwinding_579) {
    EXPECT_TRUE(ObserveDuringUnwind_Catch());
}

// Cross-check vs standard library observable behavior (acts as an oracle).
TEST(UncaughtExceptionsTest_579, MatchesStdUncaughtQueryDuringUnwinding_579) {
    auto [catchVal, stdVal] = ObserveDuringUnwind_CatchVsStd();
    EXPECT_EQ(catchVal, stdVal);
}

#endif // CATCH_CONFIG_DISABLE_EXCEPTIONS
