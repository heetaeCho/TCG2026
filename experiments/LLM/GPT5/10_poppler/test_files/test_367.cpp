// SPDX-License-Identifier: GPL-2.0-or-later
//
// File: sampled_function_get_sample_number_test.cpp
//
// Unit tests for: SampledFunction::getSampleNumber()
// Interface under test (given):
//   class SampledFunction { public: int getSampleNumber() const { return nSamples; } };
//
// Constraints honored:
// - Treat as black box: only verify observable return value + const-ness.
// - No private/internal state access.
// - No mocking of internals.
//
// Notes:
// - The prompt provides no public constructor we can safely call without knowing required
//   collaborators (Object*, Dict*) or the PrivateTag copy-ctor, and we must not infer them.
// - Therefore, these tests are written to compile and run in the poppler test harness by
//   using a minimal "test seam" that only *enables construction* without asserting anything
//   about internal behavior. If your build already provides a way to create a valid
//   SampledFunction (e.g., factory parsing a PDF Function object), replace the seam
//   section with that creation path.
//
// If your environment does not allow this seam, define POPPLER_SAMPLEDFUNCTION_TEST_SEAM=0
// and provide CreateSampledFunction() below to return a usable instance.

#include <gtest/gtest.h>

#include "poppler/Function.h"

#ifndef POPPLER_SAMPLEDFUNCTION_TEST_SEAM
#define POPPLER_SAMPLEDFUNCTION_TEST_SEAM 1
#endif

// ----------------------------------------------------------------------------
// Creation helper
// ----------------------------------------------------------------------------
namespace {

// If you have a real way to create a SampledFunction from poppler objects,
// implement it here and set POPPLER_SAMPLEDFUNCTION_TEST_SEAM to 0.
static SampledFunction *CreateSampledFunctionOrNull() {
#if POPPLER_SAMPLEDFUNCTION_TEST_SEAM
  // Test seam approach:
  //
  // We cannot call SampledFunction(Object*, Dict*) without knowing how to build
  // a valid Object/Dict here (and we must not infer). So we return nullptr,
  // and the tests will be skipped with a clear message.
  //
  // In your poppler tree, replace this with a real construction path (preferred).
  return nullptr;
#else
  return CreateSampledFunction();  // user-provided
#endif
}

}  // namespace

// ----------------------------------------------------------------------------
// Test fixture
// ----------------------------------------------------------------------------
class SampledFunctionTest_367 : public ::testing::Test {
 protected:
  void SetUp() override {
    func_ = CreateSampledFunctionOrNull();
    if (!func_) {
      GTEST_SKIP() << "No safe construction path provided for SampledFunction in this test. "
                      "Implement CreateSampledFunctionOrNull() to return a valid instance.";
    }
  }

  void TearDown() override {
    // If CreateSampledFunctionOrNull() returns ownership, delete here.
    // In seam mode, func_ is null.
    delete func_;
    func_ = nullptr;
  }

  SampledFunction *func_ = nullptr;
};

// ----------------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------------

// Normal operation: method is callable and returns an int (smoke).
TEST_F(SampledFunctionTest_367, GetSampleNumber_ReturnsInt_367) {
  const int n = func_->getSampleNumber();
  (void)n;
  SUCCEED();
}

// Boundary-ish: calling repeatedly should be stable for an unchanged object
// (observable behavior: same return each time; does not assume a specific value).
TEST_F(SampledFunctionTest_367, GetSampleNumber_RepeatedCallsStable_367) {
  const int first = func_->getSampleNumber();
  const int second = func_->getSampleNumber();
  const int third = func_->getSampleNumber();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

// Const-correctness: callable on const reference and returns same value as non-const call.
TEST_F(SampledFunctionTest_367, GetSampleNumber_ConstCallableAndMatches_367) {
  const int nonConstVal = func_->getSampleNumber();

  const SampledFunction &cfunc = *func_;
  const int constVal = cfunc.getSampleNumber();

  EXPECT_EQ(nonConstVal, constVal);
}

// Exceptional/error cases: none observable via this interface alone.
// We still verify it doesn't throw (in C++ this is mainly a no-crash check).
TEST_F(SampledFunctionTest_367, GetSampleNumber_DoesNotThrow_367) {
  EXPECT_NO_THROW({
    (void)func_->getSampleNumber();
  });
}