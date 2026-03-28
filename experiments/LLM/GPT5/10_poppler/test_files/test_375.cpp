// SPDX-License-Identifier: GPL-2.0-or-later
// File: StitchingFunction_gtest_375.cpp
//
// Unit tests for poppler::StitchingFunction (FunctionType 3) public interface.
// Black-box tests: do not rely on private state or internal implementation details.

#include <gtest/gtest.h>

#include <cmath>
#include <memory>
#include <vector>

// Poppler headers (paths may vary depending on your build setup)
#include "poppler/Function.h"
#include "poppler/Object.h"
#include "poppler/Array.h"
#include "poppler/Dict.h"

namespace {

class StitchingFunctionTest_375 : public ::testing::Test {
protected:
  // Helper to build an exponential interpolation function (FunctionType 2)
  // Domain [0 1], C0 [0], C1 [1], N 1, 1 input, 1 output.
  static Object MakeExponentialFunctionType2Obj_375() {
    Dict *d = new Dict(nullptr);

    Object fnType;
    fnType.initInt(2);
    d->add(const_cast<char *>("FunctionType"), fnType);

    // Domain [0 1]
    Array *domain = new Array(nullptr);
    Object v0; v0.initReal(0.0);
    Object v1; v1.initReal(1.0);
    domain->add(v0);
    domain->add(v1);
    Object domainObj;
    domainObj.initArray(domain);
    d->add(const_cast<char *>("Domain"), domainObj);

    // C0 [0]
    Array *c0 = new Array(nullptr);
    Object c0v; c0v.initReal(0.0);
    c0->add(c0v);
    Object c0Obj;
    c0Obj.initArray(c0);
    d->add(const_cast<char *>("C0"), c0Obj);

    // C1 [1]
    Array *c1 = new Array(nullptr);
    Object c1v; c1v.initReal(1.0);
    c1->add(c1v);
    Object c1Obj;
    c1Obj.initArray(c1);
    d->add(const_cast<char *>("C1"), c1Obj);

    // N 1
    Object nObj;
    nObj.initReal(1.0);
    d->add(const_cast<char *>("N"), nObj);

    Object dictObj;
    dictObj.initDict(d);
    return dictObj;
  }

  // Helper to build a stitching function (FunctionType 3) with exactly 1 sub-function.
  // Domain [0 1], Bounds [0 1], Encode [0 1], Functions [ <type2 exponential> ].
  static std::unique_ptr<StitchingFunction> MakeValidStitchingFunction_375() {
    Dict *d = new Dict(nullptr);

    Object fnType;
    fnType.initInt(3);
    d->add(const_cast<char *>("FunctionType"), fnType);

    // Domain [0 1]
    Array *domain = new Array(nullptr);
    Object v0; v0.initReal(0.0);
    Object v1; v1.initReal(1.0);
    domain->add(v0);
    domain->add(v1);
    Object domainObj;
    domainObj.initArray(domain);
    d->add(const_cast<char *>("Domain"), domainObj);

    // Functions [ <type2> ]
    Array *funcs = new Array(nullptr);
    Object type2 = MakeExponentialFunctionType2Obj_375();
    funcs->add(type2);
    Object funcsObj;
    funcsObj.initArray(funcs);
    d->add(const_cast<char *>("Functions"), funcsObj);

    // Bounds [0 1]  (for 1 function: funcs+1 = 2 entries)
    Array *bounds = new Array(nullptr);
    Object b0; b0.initReal(0.0);
    Object b1; b1.initReal(1.0);
    bounds->add(b0);
    bounds->add(b1);
    Object boundsObj;
    boundsObj.initArray(bounds);
    d->add(const_cast<char *>("Bounds"), boundsObj);

    // Encode [0 1]  (for 1 function: 2*funcs = 2 entries)
    Array *encode = new Array(nullptr);
    Object e0; e0.initReal(0.0);
    Object e1; e1.initReal(1.0);
    encode->add(e0);
    encode->add(e1);
    Object encodeObj;
    encodeObj.initArray(encode);
    d->add(const_cast<char *>("Encode"), encodeObj);

    RefRecursionChecker usedParents;
    return std::make_unique<StitchingFunction>(d, usedParents);
  }

  // Helper to build an intentionally incomplete stitching function dict to exercise error handling.
  static std::unique_ptr<StitchingFunction> MakeInvalidStitchingFunctionMissingFields_375() {
    Dict *d = new Dict(nullptr);

    Object fnType;
    fnType.initInt(3);
    d->add(const_cast<char *>("FunctionType"), fnType);

    // Provide Domain but omit Functions/Bounds/Encode (common required fields).
    Array *domain = new Array(nullptr);
    Object v0; v0.initReal(0.0);
    Object v1; v1.initReal(1.0);
    domain->add(v0);
    domain->add(v1);
    Object domainObj;
    domainObj.initArray(domain);
    d->add(const_cast<char *>("Domain"), domainObj);

    RefRecursionChecker usedParents;
    return std::make_unique<StitchingFunction>(d, usedParents);
  }

  static bool IsFinite_375(double x) {
    return std::isfinite(x) != 0;
  }
};

TEST_F(StitchingFunctionTest_375, GetTypeReturnsStitching_375) {
  auto func = MakeValidStitchingFunction_375();
  ASSERT_NE(func, nullptr);
  EXPECT_EQ(func->getType(), Function::Type::Stitching);
}

TEST_F(StitchingFunctionTest_375, IsOkTrueForWellFormedDict_375) {
  auto func = MakeValidStitchingFunction_375();
  ASSERT_NE(func, nullptr);
  EXPECT_TRUE(func->isOk());
}

TEST_F(StitchingFunctionTest_375, BasicAccessorsAreNonNullWhenOk_375) {
  auto func = MakeValidStitchingFunction_375();
  ASSERT_NE(func, nullptr);
  ASSERT_TRUE(func->isOk());

  EXPECT_EQ(func->getNumFuncs(), 1);

  const Function *sub0 = func->getFunc(0);
  EXPECT_NE(sub0, nullptr);

  // Out-of-range access should be safely handled (observed via nullptr).
  const Function *sub1 = func->getFunc(1);
  EXPECT_EQ(sub1, nullptr);

  EXPECT_NE(func->getBounds(), nullptr);
  EXPECT_NE(func->getEncode(), nullptr);
  EXPECT_NE(func->getScale(), nullptr);
}

TEST_F(StitchingFunctionTest_375, TransformIsDeterministicForSameInput_375) {
  auto func = MakeValidStitchingFunction_375();
  ASSERT_NE(func, nullptr);
  ASSERT_TRUE(func->isOk());

  double in[1] = {0.25};
  double out1[1] = {0.0};
  double out2[1] = {0.0};

  func->transform(in, out1);
  func->transform(in, out2);

  // Determinism: same input -> same output (black-box expectation for a pure transform).
  EXPECT_DOUBLE_EQ(out1[0], out2[0]);
  EXPECT_TRUE(IsFinite_375(out1[0]));
}

TEST_F(StitchingFunctionTest_375, TransformHandlesDomainEndpoints_375) {
  auto func = MakeValidStitchingFunction_375();
  ASSERT_NE(func, nullptr);
  ASSERT_TRUE(func->isOk());

  {
    double in[1] = {0.0};
    double out[1] = {0.0};
    func->transform(in, out);
    EXPECT_TRUE(IsFinite_375(out[0]));
  }
  {
    double in[1] = {1.0};
    double out[1] = {0.0};
    func->transform(in, out);
    EXPECT_TRUE(IsFinite_375(out[0]));
  }
}

TEST_F(StitchingFunctionTest_375, CopyProducesIndependentObjectWithSameTypeAndBehavior_375) {
  auto func = MakeValidStitchingFunction_375();
  ASSERT_NE(func, nullptr);
  ASSERT_TRUE(func->isOk());

  std::unique_ptr<Function> copied = func->copy();
  ASSERT_NE(copied, nullptr);

  EXPECT_EQ(copied->getType(), Function::Type::Stitching);
  EXPECT_TRUE(copied->isOk());

  // Behavioral check (black-box): same input -> same output between original and copy.
  double in[1] = {0.6};
  double outOrig[1] = {0.0};
  double outCopy[1] = {0.0};

  func->transform(in, outOrig);
  copied->transform(in, outCopy);

  EXPECT_DOUBLE_EQ(outOrig[0], outCopy[0]);
  EXPECT_TRUE(IsFinite_375(outCopy[0]));
}

TEST_F(StitchingFunctionTest_375, InvalidDictResultsInNotOkButTypeStillStitching_375) {
  auto func = MakeInvalidStitchingFunctionMissingFields_375();
  ASSERT_NE(func, nullptr);

  // Even if invalid, the dynamic type is still StitchingFunction.
  EXPECT_EQ(func->getType(), Function::Type::Stitching);

  // Observable error state through public API.
  EXPECT_FALSE(func->isOk());
}

} // namespace