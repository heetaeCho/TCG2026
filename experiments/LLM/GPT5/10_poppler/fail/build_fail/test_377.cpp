// TEST_ID is 377
// Unit tests for StitchingFunction::getNumFuncs() (Poppler)
//
// File: ./TestProjects/poppler/poppler/Function_stitching_getnumfuncs_377_test.cc

#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "poppler/Function.h"
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/Array.h"

namespace {

// Helper: build a simple Exponential function dictionary (FunctionType=2)
// Domain: [0 1], C0:[c0], C1:[c1], N:n
static Object MakeExponentialFuncObj(double c0, double c1, double n) {
  auto *dict = new Dict(nullptr);

  // FunctionType = 2
  dict->add("FunctionType", Object(2));

  // Domain = [0 1]
  auto *domain = new Array(nullptr);
  domain->add(Object(0.0));
  domain->add(Object(1.0));
  dict->add("Domain", Object(domain));

  // C0 = [c0]
  auto *c0Arr = new Array(nullptr);
  c0Arr->add(Object(c0));
  dict->add("C0", Object(c0Arr));

  // C1 = [c1]
  auto *c1Arr = new Array(nullptr);
  c1Arr->add(Object(c1));
  dict->add("C1", Object(c1Arr));

  // N = n
  dict->add("N", Object(n));

  return Object(dict);
}

// Helper: build a Stitching function dictionary (FunctionType=3) with k sub-functions.
// Domain: [0 1]
// Bounds: k-1 values (monotonic split points)
// Encode: 2*k values (min/max per sub-function)
static Object MakeStitchingFuncObj(int k) {
  auto *dict = new Dict(nullptr);

  dict->add("FunctionType", Object(3));

  // Domain = [0 1]
  auto *domain = new Array(nullptr);
  domain->add(Object(0.0));
  domain->add(Object(1.0));
  dict->add("Domain", Object(domain));

  // Functions = [ f0 f1 ... ]
  auto *funcs = new Array(nullptr);
  for (int i = 0; i < k; ++i) {
    // Each sub-function is exponential with 1 input/1 output.
    funcs->add(MakeExponentialFuncObj(/*c0=*/0.0, /*c1=*/1.0, /*n=*/1.0));
  }
  dict->add("Functions", Object(funcs));

  // Bounds length = k-1 (split evenly)
  auto *bounds = new Array(nullptr);
  if (k > 1) {
    for (int i = 1; i < k; ++i) {
      bounds->add(Object(static_cast<double>(i) / static_cast<double>(k)));
    }
  }
  dict->add("Bounds", Object(bounds));

  // Encode length = 2*k; use [0 1] for each sub-function
  auto *encode = new Array(nullptr);
  for (int i = 0; i < k; ++i) {
    encode->add(Object(0.0));
    encode->add(Object(1.0));
  }
  dict->add("Encode", Object(encode));

  return Object(dict);
}

static std::unique_ptr<Function> ParseFunction(Object &obj) {
  // Function::parse returns a raw pointer (NULL on failure).
  return std::unique_ptr<Function>(Function::parse(&obj));
}

} // namespace

class StitchingFunctionTest_377 : public ::testing::Test {};

TEST_F(StitchingFunctionTest_377, ParseValidWithOneSubFunction_GetNumFuncsIsOne_377) {
  Object stitchObj = MakeStitchingFuncObj(/*k=*/1);
  auto fn = ParseFunction(stitchObj);

  ASSERT_NE(fn, nullptr);
  EXPECT_TRUE(fn->isOk());
  EXPECT_EQ(fn->getType(), 3);

  auto *stitch = dynamic_cast<StitchingFunction *>(fn.get());
  ASSERT_NE(stitch, nullptr);

  EXPECT_EQ(stitch->getNumFuncs(), 1);
  EXPECT_NE(stitch->getFunc(0), nullptr);
}

TEST_F(StitchingFunctionTest_377, ParseValidWithTwoSubFunctions_GetNumFuncsIsTwo_377) {
  Object stitchObj = MakeStitchingFuncObj(/*k=*/2);
  auto fn = ParseFunction(stitchObj);

  ASSERT_NE(fn, nullptr);
  EXPECT_TRUE(fn->isOk());
  EXPECT_EQ(fn->getType(), 3);

  auto *stitch = dynamic_cast<StitchingFunction *>(fn.get());
  ASSERT_NE(stitch, nullptr);

  EXPECT_EQ(stitch->getNumFuncs(), 2);
  EXPECT_NE(stitch->getFunc(0), nullptr);
  EXPECT_NE(stitch->getFunc(1), nullptr);
}

TEST_F(StitchingFunctionTest_377, ParseValidWithManySubFunctions_GetNumFuncsMatchesCount_377) {
  constexpr int kCount = 5;
  Object stitchObj = MakeStitchingFuncObj(/*k=*/kCount);
  auto fn = ParseFunction(stitchObj);

  ASSERT_NE(fn, nullptr);
  EXPECT_TRUE(fn->isOk());
  EXPECT_EQ(fn->getType(), 3);

  auto *stitch = dynamic_cast<StitchingFunction *>(fn.get());
  ASSERT_NE(stitch, nullptr);

  EXPECT_EQ(stitch->getNumFuncs(), kCount);
  for (int i = 0; i < kCount; ++i) {
    EXPECT_NE(stitch->getFunc(i), nullptr);
  }
}

TEST_F(StitchingFunctionTest_377, ParseInvalidMissingFunctions_ReportsNotOkOrNull_377) {
  auto *dict = new Dict(nullptr);
  dict->add("FunctionType", Object(3));

  // Domain present but Functions missing.
  auto *domain = new Array(nullptr);
  domain->add(Object(0.0));
  domain->add(Object(1.0));
  dict->add("Domain", Object(domain));

  // Bounds and Encode present to avoid failing for those first in some implementations.
  auto *bounds = new Array(nullptr);
  bounds->add(Object(0.5));
  dict->add("Bounds", Object(bounds));

  auto *encode = new Array(nullptr);
  encode->add(Object(0.0));
  encode->add(Object(1.0));
  encode->add(Object(0.0));
  encode->add(Object(1.0));
  dict->add("Encode", Object(encode));

  Object stitchObj(dict);
  auto fn = ParseFunction(stitchObj);

  // Observable error handling: either parse fails (nullptr) or function exists but is not OK.
  if (!fn) {
    SUCCEED();
    return;
  }
  EXPECT_FALSE(fn->isOk());
}

TEST_F(StitchingFunctionTest_377, ParseInvalidEncodeLength_ReportsNotOkOrNull_377) {
  auto *dict = new Dict(nullptr);
  dict->add("FunctionType", Object(3));

  // Domain
  auto *domain = new Array(nullptr);
  domain->add(Object(0.0));
  domain->add(Object(1.0));
  dict->add("Domain", Object(domain));

  // Functions = 2
  auto *funcs = new Array(nullptr);
  funcs->add(MakeExponentialFuncObj(0.0, 1.0, 1.0));
  funcs->add(MakeExponentialFuncObj(0.0, 1.0, 1.0));
  dict->add("Functions", Object(funcs));

  // Bounds = [0.5]
  auto *bounds = new Array(nullptr);
  bounds->add(Object(0.5));
  dict->add("Bounds", Object(bounds));

  // Encode SHOULD be 4 numbers for 2 funcs, but we intentionally give 2.
  auto *encode = new Array(nullptr);
  encode->add(Object(0.0));
  encode->add(Object(1.0));
  dict->add("Encode", Object(encode));

  Object stitchObj(dict);
  auto fn = ParseFunction(stitchObj);

  if (!fn) {
    SUCCEED();
    return;
  }
  EXPECT_FALSE(fn->isOk());
}

TEST_F(StitchingFunctionTest_377, CopyPreservesGetNumFuncs_377) {
  Object stitchObj = MakeStitchingFuncObj(/*k=*/3);
  auto fn = ParseFunction(stitchObj);

  ASSERT_NE(fn, nullptr);
  ASSERT_TRUE(fn->isOk());
  ASSERT_EQ(fn->getType(), 3);

  auto *stitch = dynamic_cast<StitchingFunction *>(fn.get());
  ASSERT_NE(stitch, nullptr);

  const int originalCount = stitch->getNumFuncs();

  std::unique_ptr<Function> copied(fn->copy());
  ASSERT_NE(copied, nullptr);
  EXPECT_TRUE(copied->isOk());
  EXPECT_EQ(copied->getType(), 3);

  auto *stitchCopy = dynamic_cast<StitchingFunction *>(copied.get());
  ASSERT_NE(stitchCopy, nullptr);
  EXPECT_EQ(stitchCopy->getNumFuncs(), originalCount);
}

TEST_F(StitchingFunctionTest_377, BoundaryZeroSubFunctions_ReportsNotOkOrNull_377) {
  // Construct with k=0: Functions empty, Bounds empty, Encode empty.
  // Some implementations may reject this; we accept either nullptr or !isOk().
  auto *dict = new Dict(nullptr);
  dict->add("FunctionType", Object(3));

  auto *domain = new Array(nullptr);
  domain->add(Object(0.0));
  domain->add(Object(1.0));
  dict->add("Domain", Object(domain));

  dict->add("Functions", Object(new Array(nullptr)));
  dict->add("Bounds", Object(new Array(nullptr)));
  dict->add("Encode", Object(new Array(nullptr)));

  Object stitchObj(dict);
  auto fn = ParseFunction(stitchObj);

  if (!fn) {
    SUCCEED();
    return;
  }
  EXPECT_FALSE(fn->isOk());
}