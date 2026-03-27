// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for StitchingFunction::getFunc(int)
// File under test: poppler/Function.h
//
// TEST_ID: 378
//
// Notes / constraints compliance:
// - Treats StitchingFunction as a black box.
// - Tests only observable behavior through public API (isOk/getNumFuncs/getFunc/getType).
// - Uses death tests only as an observable “error case” when indices are invalid (if supported).

#include <gtest/gtest.h>

#include "poppler/Function.h"

// These headers are commonly needed to build function dictionaries in poppler tests.
// If your build already brings them indirectly, they are still safe.
#include "poppler/Object.h"
#include "poppler/Array.h"
#include "poppler/Dict.h"
#include "poppler/Ref.h"
#include "poppler/RefRecursionChecker.h"

namespace {

static Object makeRealArray(std::initializer_list<double> vals)
{
  Array *arr = new Array();
  for (double v : vals) {
    arr->add(Object(v));
  }
  return Object(arr);
}

static Object makeIntArray(std::initializer_list<int> vals)
{
  Array *arr = new Array();
  for (int v : vals) {
    arr->add(Object(v));
  }
  return Object(arr);
}

// Build a very small Sampled function (FunctionType 0) dict.
// This is “plausible” input for StitchingFunction sub-functions and is intentionally minimal.
static Object makeSampledFunctionDict_1in1out()
{
  Dict *d = new Dict(nullptr);

  // Required / typical keys for a Type 0 (Sampled) function:
  // - FunctionType
  // - Domain
  // - Range
  // - Size
  // - BitsPerSample
  // - Encode
  // - Decode (optional, but often accepted)
  d->add("FunctionType", Object(0));
  d->add("Domain", makeRealArray({0.0, 1.0}));
  d->add("Range", makeRealArray({0.0, 1.0}));

  // 1 input dimension, 1 output.
  d->add("Size", makeIntArray({2}));
  d->add("BitsPerSample", Object(8));

  // Encode has 2 entries per input dimension.
  d->add("Encode", makeRealArray({0.0, 1.0}));

  // Decode has 2 entries per output dimension (optional but benign).
  d->add("Decode", makeRealArray({0.0, 1.0}));

  // Stream data normally required for sampled functions may be present in real PDFs,
  // but poppler’s parser/test harnesses often allow minimal dicts for object creation.
  return Object(d);
}

// Build a Stitching function (FunctionType 3) dict with N sub-functions.
// For 1-input functions: Bounds has (N-1) values, Encode has (2*N) values.
static Object makeStitchingFunctionDict_1in1out_withNFuncs(int nFuncs)
{
  Dict *d = new Dict(nullptr);

  d->add("FunctionType", Object(3));
  d->add("Domain", makeRealArray({0.0, 1.0}));
  d->add("Range", makeRealArray({0.0, 1.0}));

  Array *funcsArr = new Array();
  for (int i = 0; i < nFuncs; ++i) {
    funcsArr->add(makeSampledFunctionDict_1in1out());
  }
  d->add("Functions", Object(funcsArr));

  if (nFuncs > 1) {
    Array *boundsArr = new Array();
    // Monotonic bounds within domain; choose evenly spaced internal points.
    for (int i = 1; i < nFuncs; ++i) {
      boundsArr->add(Object(static_cast<double>(i) / static_cast<double>(nFuncs)));
    }
    d->add("Bounds", Object(boundsArr));
  } else {
    // Some implementations accept empty Bounds for single function;
    // leaving it out is also common. We omit it for nFuncs == 1.
  }

  // Encode: 2 values per function for 1 input dim.
  Array *encodeArr = new Array();
  for (int i = 0; i < nFuncs; ++i) {
    // Map each subdomain to [0,1] for the sub-function.
    encodeArr->add(Object(0.0));
    encodeArr->add(Object(1.0));
  }
  d->add("Encode", Object(encodeArr));

  return Object(d);
}

// Helper: create a StitchingFunction instance from a Dict through the public constructor.
// If construction fails internally, isOk() should be observable.
static std::unique_ptr<StitchingFunction> makeStitchingFromDict(Dict *dict)
{
  RefRecursionChecker checker;
  return std::make_unique<StitchingFunction>(dict, checker);
}

class StitchingFunctionTest_378 : public ::testing::Test {
protected:
  void SetUp() override {}

  std::unique_ptr<StitchingFunction> makeValidWithTwoFuncs()
  {
    Object stitchingObj = makeStitchingFunctionDict_1in1out_withNFuncs(2);
    Dict *d = stitchingObj.getDict();
    return makeStitchingFromDict(d);
  }

  std::unique_ptr<StitchingFunction> makeValidWithOneFunc()
  {
    Object stitchingObj = makeStitchingFunctionDict_1in1out_withNFuncs(1);
    Dict *d = stitchingObj.getDict();
    return makeStitchingFromDict(d);
  }
};

} // namespace

TEST_F(StitchingFunctionTest_378, GetFuncReturnsNonNullForValidIndices_378)
{
  auto f = makeValidWithTwoFuncs();
  ASSERT_TRUE(f);
  ASSERT_TRUE(f->isOk()) << "Expected StitchingFunction to be OK for a plausible minimal dict";
  ASSERT_EQ(f->getType(), Function::Type::stitching);

  const int n = f->getNumFuncs();
  ASSERT_GE(n, 2);

  for (int i = 0; i < n; ++i) {
    const Function *sub = f->getFunc(i);
    EXPECT_NE(sub, nullptr) << "getFunc(" << i << ") should return a valid sub-function pointer";
  }
}

TEST_F(StitchingFunctionTest_378, GetFuncIsStableForSameIndex_378)
{
  auto f = makeValidWithTwoFuncs();
  ASSERT_TRUE(f);
  ASSERT_TRUE(f->isOk());

  const int n = f->getNumFuncs();
  ASSERT_GT(n, 0);

  const Function *p0 = f->getFunc(0);
  const Function *p0_again = f->getFunc(0);

  // Observable behavior: repeated calls should return the same pointer identity for the same index
  // (since API returns a raw pointer to an owned object).
  EXPECT_EQ(p0, p0_again);
}

TEST_F(StitchingFunctionTest_378, GetFuncBoundaryFirstAndLastIndex_378)
{
  auto f = makeValidWithTwoFuncs();
  ASSERT_TRUE(f);
  ASSERT_TRUE(f->isOk());

  const int n = f->getNumFuncs();
  ASSERT_GT(n, 0);

  const Function *first = f->getFunc(0);
  const Function *last = f->getFunc(n - 1);

  EXPECT_NE(first, nullptr);
  EXPECT_NE(last, nullptr);

  // If there is more than one function, the first and last are expected to be different objects.
  if (n > 1) {
    EXPECT_NE(first, last);
  }
}

TEST_F(StitchingFunctionTest_378, GetFuncWorksWithSingleSubFunction_378)
{
  auto f = makeValidWithOneFunc();
  ASSERT_TRUE(f);
  ASSERT_TRUE(f->isOk());

  ASSERT_EQ(f->getNumFuncs(), 1);
  EXPECT_NE(f->getFunc(0), nullptr);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(StitchingFunctionTest_378, GetFuncNegativeIndexDiesOrAborts_378)
{
  auto f = makeValidWithTwoFuncs();
  ASSERT_TRUE(f);
  ASSERT_TRUE(f->isOk());

  // Error case (observable): passing an invalid index may trigger an assertion/abort
  // depending on poppler build flags / STL bounds checks.
  EXPECT_DEATH({ (void)f->getFunc(-1); }, ".*");
}

TEST_F(StitchingFunctionTest_378, GetFuncOutOfRangeIndexDiesOrAborts_378)
{
  auto f = makeValidWithTwoFuncs();
  ASSERT_TRUE(f);
  ASSERT_TRUE(f->isOk());

  const int n = f->getNumFuncs();
  EXPECT_DEATH({ (void)f->getFunc(n); }, ".*");
}
#endif