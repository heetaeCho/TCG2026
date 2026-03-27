// File: assertion_result_isok_tests_292.cpp
#include <gtest/gtest.h>
#include <utility>

// Try to include a modern Catch2 umbrella header first, then fall back.
#if __has_include(<catch2/catch_all.hpp>)
  #include <catch2/catch_all.hpp>
#elif __has_include(<catch2/catch_amalgamated.hpp>)
  #include <catch2/catch_amalgamated.hpp>
#elif __has_include(<catch2/catch.hpp>)
  #include <catch2/catch.hpp>
#else
  // Minimal fallback to the headers shown in the prompt
  #include "catch2/catch_assertion_result.hpp"
  #include "catch2/catch_assertion_info.hpp"
  #include "catch2/catch_result_type.h"
#endif

namespace {

// Helper to build AssertionResult strictly via its public interface.
static Catch::AssertionResult makeResult(Catch::ResultWas::OfType type,
                                         Catch::ResultDisposition::Flags flags) {
    Catch::AssertionInfo info{};
    info.macroName = Catch::StringRef{};
    info.capturedExpression = Catch::StringRef{};
    info.resultDisposition = flags;

    // LazyExpression has a public ctor; value does not matter for isOk().
    Catch::LazyExpression lazy{false};

    Catch::AssertionResultData data(type, lazy);
    return Catch::AssertionResult(info, std::move(data));
}

} // namespace

// --- Normal operation: success types are ok ---
TEST(AssertionResult_IsOk_292, ReturnsTrueForOk_292) {
    auto ar = makeResult(Catch::ResultWas::Ok, Catch::ResultDisposition::Normal);
    EXPECT_TRUE(ar.isOk());
}

// Many success-ish types are considered "ok" by Catch (e.g., Info/Warning).
TEST(AssertionResult_IsOk_292, ReturnsTrueForInfo_292) {
    auto ar = makeResult(Catch::ResultWas::Info, Catch::ResultDisposition::Normal);
    EXPECT_TRUE(ar.isOk());
}

// --- Error case: failure types without suppression are NOT ok ---
TEST(AssertionResult_IsOk_292, ReturnsFalseForExpressionFailedWithoutSuppression_292) {
    auto ar = makeResult(Catch::ResultWas::ExpressionFailed, Catch::ResultDisposition::Normal);
    EXPECT_FALSE(ar.isOk());
}

// --- Boundary around suppression: failure + SuppressFail => ok ---
TEST(AssertionResult_IsOk_292, ReturnsTrueWhenFailureIsSuppressed_292) {
    auto ar = makeResult(Catch::ResultWas::ExpressionFailed, Catch::ResultDisposition::SuppressFail);
    EXPECT_TRUE(ar.isOk());
}
