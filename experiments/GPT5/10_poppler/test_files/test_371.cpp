// TEST_ID: 371
// Unit tests for ExponentialFunction::getC0()
// File: ExponentialFunction_getC0_test_371.cpp

#include <gtest/gtest.h>

#include "poppler/Function.h"

// The interface snippet provided only exposes:
//   class ExponentialFunction { public: const double *getC0() const { return c0; } };
// and (optionally) indicates constructors depend on Dict / other internals.
// Per constraints, we do NOT attempt to construct ExponentialFunction (constructors require Dict*, etc.)
// and do NOT infer any internal behavior beyond observable interface.
//
// These tests focus on observable behavior of getC0() for a const object reference, using a test-only
// access pattern that does not inspect private state: we can only check pointer properties.

namespace {

class ExponentialFunctionTest_371 : public ::testing::Test {};

}  // namespace

TEST_F(ExponentialFunctionTest_371, GetC0_ReturnsNonNullPointer_371) {
  // Boundary / safety expectation: returning pointer to internal array should not be null
  // for a valid object instance. We cannot construct a real instance here from the public API,
  // so this test is compiled but skipped at runtime unless the embedding test environment
  // provides a valid instance creation helper.
  //
  // If your codebase has a factory/helper that can create a valid ExponentialFunction,
  // replace the GTEST_SKIP() with that construction and run the assertions.

  GTEST_SKIP() << "ExponentialFunction construction requires Dict* / internal setup not provided "
                  "by the prompt. Provide a test helper/factory to instantiate it.";

  // Example (do not enable without real factory):
  // std::unique_ptr<ExponentialFunction> func = MakeExponentialFunctionForTest();
  // ASSERT_NE(func, nullptr);
  // const double* p = func->getC0();
  // EXPECT_NE(p, nullptr);
}

TEST_F(ExponentialFunctionTest_371, GetC0_IsStableAcrossCalls_371) {
  // Normal operation: repeated calls should return the same pointer for the same object.
  GTEST_SKIP() << "Needs a valid ExponentialFunction instance; constructors require Dict*.";

  // Example:
  // auto func = MakeExponentialFunctionForTest();
  // const double* p1 = func->getC0();
  // const double* p2 = func->getC0();
  // EXPECT_EQ(p1, p2);
}

TEST_F(ExponentialFunctionTest_371, GetC0_CanBeCalledOnConstObject_371) {
  // Boundary: method is const; should compile and be callable on const refs.
  // This is primarily a compile-time check; at runtime it needs an instance.
  GTEST_SKIP() << "Needs a valid ExponentialFunction instance; constructors require Dict*.";

  // Example:
  // const ExponentialFunction& cref = *MakeExponentialFunctionForTest();
  // const double* p = cref.getC0();
  // EXPECT_NE(p, nullptr);
}

TEST_F(ExponentialFunctionTest_371, GetC0_PointersDifferBetweenDistinctInstances_371) {
  // Boundary: two different objects should not share the same internal c0 storage.
  // This is an observable property via pointer identity only (no private-state access).
  GTEST_SKIP() << "Needs two valid ExponentialFunction instances; constructors require Dict*.";

  // Example:
  // auto f1 = MakeExponentialFunctionForTest();
  // auto f2 = MakeExponentialFunctionForTest();
  // ASSERT_NE(f1.get(), f2.get());
  // EXPECT_NE(f1->getC0(), f2->getC0());
}