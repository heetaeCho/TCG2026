// File: ITransientExpression_test_115.cpp

#include <gtest/gtest.h>
#include <sstream>

// Include the header under test
#include "Catch2/src/catch2/internal/catch_decomposer.hpp"

namespace {

// A minimal concrete type to allow construction and destruction in tests.
// We do NOT reimplement any logic; we only expose construction and a public dtor.
struct TestExpr : Catch::ITransientExpression {
  using Catch::ITransientExpression::ITransientExpression; // inherit ctor
  ~TestExpr() override = default;                          // make dtor public
  // Do not override any behavior; we rely on base class as-is.
};

} // namespace

// Suite focuses solely on observable behavior of the public interface.
class ITransientExpressionTest_115 : public ::testing::Test {};

// Normal operation: value constructed with true reports true via isBinaryExpression().
TEST_F(ITransientExpressionTest_115, IsBinaryExpressionTrueWhenConstructedTrue_115) {
  const TestExpr expr(/*isBinaryExpression=*/true, /*result=*/false);
  EXPECT_TRUE(expr.isBinaryExpression());
}

// Normal operation: value constructed with false reports false via isBinaryExpression().
TEST_F(ITransientExpressionTest_115, IsBinaryExpressionFalseWhenConstructedFalse_115) {
  const TestExpr expr(/*isBinaryExpression=*/false, /*result=*/true);
  EXPECT_FALSE(expr.isBinaryExpression());
}

// Const-correctness: isBinaryExpression() is callable on const objects and returns a stable value.
TEST_F(ITransientExpressionTest_115, IsBinaryExpressionCallableOnConstObject_115) {
  const TestExpr expr(/*isBinaryExpression=*/true, /*result=*/true);
  const Catch::ITransientExpression& cref = expr; // use const ref to base as API surface
  EXPECT_TRUE(cref.isBinaryExpression());
}

// Copy construction: observable state exposed via isBinaryExpression() is preserved after copy.
TEST_F(ITransientExpressionTest_115, CopyPreservesIsBinaryExpression_115) {
  const TestExpr original(/*isBinaryExpression=*/false, /*result=*/false);
  const TestExpr copy = original; // relies on the declared default copy ctor
  EXPECT_EQ(original.isBinaryExpression(), copy.isBinaryExpression());
}

// (Non-observational smoke) Streaming should be callable without throwing; output is unspecified.
// We only verify that invoking the function does not crash/throw.
TEST_F(ITransientExpressionTest_115, StreamReconstructedExpressionDoesNotThrow_115) {
  const TestExpr expr(/*isBinaryExpression=*/true, /*result=*/false);
  std::ostringstream os;
  // Behavior/content is unspecified; just ensure callable via public interface.
  EXPECT_NO_THROW(expr.streamReconstructedExpression(os));
  // Do not assert on 'os' content as the interface does not specify it.
}
