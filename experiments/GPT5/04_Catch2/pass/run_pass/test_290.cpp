// File: tests/assertion_result_reconstruct_expression_290_tests.cpp

#include <gtest/gtest.h>
#include <string>

// Headers under test (paths taken from the prompt)
#include "Catch2/src/catch2/catch_assertion_result.hpp"
#include "Catch2/src/catch2/internal/catch_lazy_expr.hpp"

using namespace Catch;

class AssertionResultDataTest_290 : public ::testing::Test {
protected:
    // Helper to construct the SUT while avoiding assumptions about ResultWas::OfType values.
    // We use static_cast to an arbitrary underlying value since the exact enum members are not
    // relevant to reconstructExpression()'s observable behavior per the interface provided.
    static AssertionResultData makeDataWithLazy(const LazyExpression& le) {
        return AssertionResultData(static_cast<ResultWas::OfType>(0), le);
    }
};

// [Behavior] If `reconstructedExpression` is already non-empty, it should be returned as-is,
// without depending on `lazyExpression`.
TEST_F(AssertionResultDataTest_290, ReturnsPrepopulatedExpression_290) {
    auto data = makeDataWithLazy(LazyExpression(false));
    data.reconstructedExpression = "already_built";

    const std::string out = data.reconstructExpression();

    EXPECT_EQ(out, "already_built");
    // Call again to ensure no unintended changes across calls.
    EXPECT_EQ(data.reconstructExpression(), "already_built");
}

// [Behavior] If `reconstructedExpression` is empty and the `LazyExpression` evaluates to false,
// the function should return an empty string (no reconstruction occurs).
TEST_F(AssertionResultDataTest_290, ReturnsEmptyWhenLazyExprEvaluatesFalse_290) {
    auto data = makeDataWithLazy(LazyExpression(false));
    // Ensure precondition: starts empty
    ASSERT_TRUE(data.reconstructedExpression.empty());

    const std::string out = data.reconstructExpression();

    EXPECT_TRUE(out.empty());
    EXPECT_TRUE(data.reconstructedExpression.empty()); // remains unchanged/empty
}

// [Behavior] Idempotency when pre-populated: calling reconstructExpression() multiple times
// should consistently return the same pre-populated text and not mutate it.
TEST_F(AssertionResultDataTest_290, IdempotentWhenPrepopulated_290) {
    auto data = makeDataWithLazy(LazyExpression(false));
    data.reconstructedExpression = "stable_text";

    const std::string first = data.reconstructExpression();
    const std::string second = data.reconstructExpression();

    EXPECT_EQ(first, "stable_text");
    EXPECT_EQ(second, "stable_text");
    EXPECT_EQ(data.reconstructedExpression, "stable_text");
}

// [Behavior] Const-correct usage: The observable return value should be retrievable
// through a const-qualified access path (per the header’s declaration).
TEST_F(AssertionResultDataTest_290, WorksViaConstAccess_290) {
    auto tmp = makeDataWithLazy(LazyExpression(false));
    tmp.reconstructedExpression = "const_access_ok";
    const AssertionResultData& data = tmp;

    const std::string out = data.reconstructExpression();

    EXPECT_EQ(out, "const_access_ok");
}
