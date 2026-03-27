// File: catch_assertion_result_test_293.cpp
#include <gtest/gtest.h>
#include <utility>

#include "catch2/catch_assertion_result.hpp"

using namespace Catch;

// Helper that builds an AssertionResult with a chosen result type,
// without asserting anything about internal behavior.
static AssertionResult MakeResultWithType(ResultWas::OfType type) {
    LazyExpression lazy{};                 // assume default-constructible collaborator
    AssertionResultData data(type, lazy);  // set the observable result type
    AssertionInfo info{};                  // minimal info object
    return AssertionResult(info, std::move(data));
}

// [Normal] getResultType returns the same value that was provided via constructor data.
TEST(AssertionResultTest_293, GetResultType_ReturnsConstructorValue_293) {
    auto expected = static_cast<ResultWas::OfType>(0);  // avoid relying on specific enum labels
    AssertionResult ar = MakeResultWithType(expected);

    EXPECT_EQ(ar.getResultType(), expected);
}

// [Const-correctness] The method can be called on a const object and still returns the same value.
TEST(AssertionResultTest_293, GetResultType_OnConstObject_293) {
    auto expected = static_cast<ResultWas::OfType>(7);
    const AssertionResult ar = MakeResultWithType(expected);

    EXPECT_EQ(ar.getResultType(), expected);
}

// [Distinguish different values / boundary-ish] Different input values round-trip distinctly.
TEST(AssertionResultTest_293, GetResultType_DistinguishesDifferentValues_293) {
    auto typeA = static_cast<ResultWas::OfType>(1);
    auto typeB = static_cast<ResultWas::OfType>(42);

    AssertionResult arA = MakeResultWithType(typeA);
    AssertionResult arB = MakeResultWithType(typeB);

    EXPECT_EQ(arA.getResultType(), typeA);
    EXPECT_EQ(arB.getResultType(), typeB);
    EXPECT_NE(arA.getResultType(), arB.getResultType());
}
