// File: sampled_function_getsamplesize_test_361.cpp
//
// Unit tests for SampledFunction::getSampleSize(int) based strictly on the
// public interface and observable/compilable contract.
//
// NOTE:
// In the provided interface, SampledFunction has no default constructor and
// requires Poppler-specific collaborators (Object*, Dict*) to create a runtime
// instance. Since those collaborators and their construction APIs are not part
// of the provided interface here, these tests validate the *interface contract*
// (signature/const-correctness/usability) in unevaluated contexts without
// re-implementing or poking private state.

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "Function.h"  // adjust include path as needed in your build

namespace {

class SampledFunctionTest_361 : public ::testing::Test {};

// Normal operation (interface contract): callable and returns int
TEST_F(SampledFunctionTest_361, GetSampleSize_ReturnTypeIsInt_361) {
  using Ret = decltype(std::declval<const SampledFunction&>().getSampleSize(0));
  static_assert(std::is_same_v<Ret, int>,
                "SampledFunction::getSampleSize(int) must return int");
  SUCCEED();
}

// Normal operation (interface contract): callable on const object
TEST_F(SampledFunctionTest_361, GetSampleSize_IsConstCallable_361) {
  // If this compiles, the method is callable on a const SampledFunction.
  (void)std::declval<const SampledFunction&>().getSampleSize(1);
  SUCCEED();
}

// Boundary conditions (interface contract): accepts typical boundary indices as int
TEST_F(SampledFunctionTest_361, GetSampleSize_AcceptsBoundaryIndexValues_361) {
  // We don't assume what indices are valid at runtime; we only verify the API
  // accepts int arguments across boundary-like values at compile time.
  (void)std::declval<const SampledFunction&>().getSampleSize(0);
  (void)std::declval<const SampledFunction&>().getSampleSize(15);
  (void)std::declval<const SampledFunction&>().getSampleSize(31);
  SUCCEED();
}

// Exceptional / error cases (observable via interface): not specified.
// We at least confirm it is not declared to return a status/error object.
TEST_F(SampledFunctionTest_361, GetSampleSize_IsNotBoolOrStatusType_361) {
  using Ret = decltype(std::declval<const SampledFunction&>().getSampleSize(0));
  static_assert(!std::is_same_v<Ret, bool>,
                "getSampleSize should not be a boolean status API");
  SUCCEED();
}

}  // namespace