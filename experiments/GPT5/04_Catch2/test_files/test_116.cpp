// ITransientExpressionTest_116.cpp

#include <gtest/gtest.h>
#include <sstream>
#include "Catch2/src/catch2/internal/catch_decomposer.hpp"

namespace {

// A minimal concrete derived type so we can instantiate the interface safely.
// We do NOT reimplement any behavior under test (getters); the override is only
// to satisfy potential pure-virtual requirements and is not used in assertions.
class TestExpr_116 : public Catch::ITransientExpression {
public:
    TestExpr_116(bool isBinaryExpression, bool result)
        : Catch::ITransientExpression(isBinaryExpression, result) {}

    ~TestExpr_116() override = default;

    void streamReconstructedExpression(std::ostream& os) const override {
        // No-op; tests do not assert on streamed content.
        (void)os;
    }
};

} // namespace

// --- Normal operation: getResult reflects constructor argument (true)
TEST(ITransientExpressionTest_116, GetResult_ReturnsTrueWhenConstructedWithTrue_116) {
    TestExpr_116 expr(/*isBinaryExpression=*/false, /*result=*/true);
    EXPECT_TRUE(expr.getResult());
}

// --- Normal operation: getResult reflects constructor argument (false)
TEST(ITransientExpressionTest_116, GetResult_ReturnsFalseWhenConstructedWithFalse_116) {
    TestExpr_116 expr(/*isBinaryExpression=*/true, /*result=*/false);
    EXPECT_FALSE(expr.getResult());
}

// --- Boundary across both booleans: isBinaryExpression and getResult combinations
TEST(ITransientExpressionTest_116, IsBinaryExpression_True_ResultFalse_116) {
    TestExpr_116 expr(/*isBinaryExpression=*/true, /*result=*/false);
    EXPECT_TRUE(expr.isBinaryExpression());
    EXPECT_FALSE(expr.getResult());
}

TEST(ITransientExpressionTest_116, IsBinaryExpression_False_ResultTrue_116) {
    TestExpr_116 expr(/*isBinaryExpression=*/false, /*result=*/true);
    EXPECT_FALSE(expr.isBinaryExpression());
    EXPECT_TRUE(expr.getResult());
}

// --- Copy construction preserves observable state
TEST(ITransientExpressionTest_116, CopyConstructor_PreservesState_116) {
    TestExpr_116 original(/*isBinaryExpression=*/true, /*result=*/true);
    TestExpr_116 copy = original;

    EXPECT_EQ(copy.isBinaryExpression(), original.isBinaryExpression());
    EXPECT_EQ(copy.getResult(), original.getResult());
}

// --- Copy assignment preserves observable state and overwrites destination
TEST(ITransientExpressionTest_116, CopyAssignment_PreservesAndOverwritesState_116) {
    TestExpr_116 a(/*isBinaryExpression=*/true, /*result=*/false);
    TestExpr_116 b(/*isBinaryExpression=*/false, /*result=*/true);

    b = a;

    EXPECT_EQ(b.isBinaryExpression(), a.isBinaryExpression());
    EXPECT_EQ(b.getResult(), a.getResult());
}

// --- Self-assignment leaves observable state unchanged
TEST(ITransientExpressionTest_116, SelfAssignment_NoChange_116) {
    TestExpr_116 expr(/*isBinaryExpression=*/true, /*result=*/true);

    // NOLINTNEXTLINE(bugprone-use-after-move) — not moving; explicit self-assign
    expr = expr;

    EXPECT_TRUE(expr.isBinaryExpression());
    EXPECT_TRUE(expr.getResult());
}

// --- Calling streamReconstructedExpression should be safe (no exceptions, stream valid)
// Not asserting on content to avoid assuming internal formatting behavior.
TEST(ITransientExpressionTest_116, StreamReconstructedExpression_DoesNotCorruptStream_116) {
    TestExpr_116 expr(/*isBinaryExpression=*/false, /*result=*/false);
    std::ostringstream os;

    // Should not throw and should leave stream in a usable state.
    EXPECT_NO_THROW(expr.streamReconstructedExpression(os));
    EXPECT_FALSE(os.bad());
}
