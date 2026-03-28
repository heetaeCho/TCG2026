// File: tests/ITransientExpression_test_539.cpp
#include <gtest/gtest.h>
#include <sstream>

// Include the provided interface
#include "catch2/internal/catch_decomposer.hpp"

namespace {

// A minimal derived type that does NOT override streamReconstructedExpression.
// We give it a public destructor so we can create/destroy it normally.
struct DerivedNoOverride : public Catch::ITransientExpression {
  // Forward to the public ctor visible on the interface (per provided header)
  explicit DerivedNoOverride(bool isBinary = false, bool result = false)
      : Catch::ITransientExpression(isBinary, result) {}
  ~DerivedNoOverride() = default;
};

// A derived type that DOES override streamReconstructedExpression
struct DerivedOverride : public Catch::ITransientExpression {
  explicit DerivedOverride(bool isBinary = false, bool result = false)
      : Catch::ITransientExpression(isBinary, result) {}
  ~DerivedOverride() = default;

  void streamReconstructedExpression(std::ostream& os) const override {
    os << "[overridden-expression]";
  }
};

}  // namespace

// Verifies that when a derived class does NOT override the method,
// the base implementation writes the documented fallback message.
TEST(ITransientExpressionTest_539, DefaultMessageWhenNotOverridden_539) {
  DerivedNoOverride expr;
  std::ostringstream oss;

  expr.streamReconstructedExpression(oss);

  EXPECT_EQ(
      oss.str(),
      "Some class derived from ITransientExpression without overriding streamReconstructedExpression");
}

// Verifies that overriding the virtual method changes the observable output.
// This also implicitly checks that dynamic dispatch is used (i.e., method is virtual).
TEST(ITransientExpressionTest_539, DerivedOverrideWritesCustomText_539) {
  DerivedOverride expr;
  std::ostringstream oss;

  expr.streamReconstructedExpression(oss);

  EXPECT_EQ(oss.str(), "[overridden-expression]");
}

// Optional: Call twice to ensure it keeps writing to the provided stream
// (observable effect confined to the std::ostream; no internal assumptions).
TEST(ITransientExpressionTest_539, MultipleCallsAppendToStream_539) {
  DerivedNoOverride expr;
  std::ostringstream oss;

  expr.streamReconstructedExpression(oss);
  oss << "|";
  expr.streamReconstructedExpression(oss);

  const std::string expected =
      "Some class derived from ITransientExpression without overriding streamReconstructedExpression"
      "|"
      "Some class derived from ITransientExpression without overriding streamReconstructedExpression";

  EXPECT_EQ(oss.str(), expected);
}
