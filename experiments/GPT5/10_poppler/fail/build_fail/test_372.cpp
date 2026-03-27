// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exponential_function_372.cc
//
// Unit tests for ExponentialFunction::getC1() (and related observable behavior via public API)
//
// Constraints honored:
// - Treat implementation as a black box
// - Use only public interface / observable effects
// - No access to private state

#include <gtest/gtest.h>

#include "poppler/Function.h"

// Poppler helpers (Dict/Object/Array live in Object.h for most Poppler builds)
#include "poppler/Object.h"

namespace {

// Build a minimal Exponential (FunctionType 2) dictionary.
// We keep it small: 1 input, 1 output.
//
// PDF spec basics (observed via public transform()):
// out = C0 + (x^N) * (C1 - C0) for each output component.
static Dict *MakeExponentialDict1Out(double c0, double c1, double n,
                                    double d0 = 0.0, double d1 = 1.0) {
  // Dict(XRef*) is commonly used; nullptr works in many builds for locally-constructed dicts.
  auto *dict = new Dict(nullptr);

  // FunctionType = 2
  {
    Object o;
    o.initInt(2);
    dict->add(const_cast<char *>("FunctionType"), std::move(o));
  }

  // Domain [d0 d1]
  {
    Object domObj;
    domObj.initArray(nullptr);
    Array *dom = domObj.getArray();

    Object a;
    a.initReal(d0);
    dom->add(std::move(a));
    Object b;
    b.initReal(d1);
    dom->add(std::move(b));

    dict->add(const_cast<char *>("Domain"), std::move(domObj));
  }

  // C0 [c0]
  {
    Object c0Obj;
    c0Obj.initArray(nullptr);
    Array *arr = c0Obj.getArray();

    Object v;
    v.initReal(c0);
    arr->add(std::move(v));

    dict->add(const_cast<char *>("C0"), std::move(c0Obj));
  }

  // C1 [c1]
  {
    Object c1Obj;
    c1Obj.initArray(nullptr);
    Array *arr = c1Obj.getArray();

    Object v;
    v.initReal(c1);
    arr->add(std::move(v));

    dict->add(const_cast<char *>("C1"), std::move(c1Obj));
  }

  // N = n
  {
    Object o;
    o.initReal(n);
    dict->add(const_cast<char *>("N"), std::move(o));
  }

  return dict;
}

}  // namespace

class ExponentialFunctionTest_372 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Nothing to do; we delete Dict after constructing ExponentialFunction.
    // ExponentialFunction is responsible for reading needed values during construction.
  }
};

TEST_F(ExponentialFunctionTest_372, GetC1ReturnsNonNullPointerWhenOk_372) {
  std::unique_ptr<Dict> dict(MakeExponentialDict1Out(/*c0=*/0.0, /*c1=*/1.0, /*n=*/1.0));
  ExponentialFunction func(dict.get());

  // Observable: construction success via isOk() (public API)
  ASSERT_TRUE(func.isOk());

  // Primary API under test
  const double *c1 = func.getC1();
  ASSERT_NE(c1, nullptr);

  // For 1-output function, the first element is observable through the accessor.
  EXPECT_DOUBLE_EQ(c1[0], 1.0);
}

TEST_F(ExponentialFunctionTest_372, GetC1IsStableAcrossCalls_372) {
  std::unique_ptr<Dict> dict(MakeExponentialDict1Out(/*c0=*/0.25, /*c1=*/2.5, /*n=*/1.0));
  ExponentialFunction func(dict.get());
  ASSERT_TRUE(func.isOk());

  const double *p1 = func.getC1();
  const double *p2 = func.getC1();

  // Observable behavior of an accessor: repeated calls should be consistent.
  EXPECT_EQ(p1, p2);
  ASSERT_NE(p1, nullptr);
  EXPECT_DOUBLE_EQ(p1[0], 2.5);
}

TEST_F(ExponentialFunctionTest_372, GetC1DistinctFromGetC0Pointer_372) {
  std::unique_ptr<Dict> dict(MakeExponentialDict1Out(/*c0=*/1.0, /*c1=*/3.0, /*n=*/1.0));
  ExponentialFunction func(dict.get());
  ASSERT_TRUE(func.isOk());

  const double *c0 = func.getC0();
  const double *c1 = func.getC1();

  ASSERT_NE(c0, nullptr);
  ASSERT_NE(c1, nullptr);

  // C0 and C1 are exposed as separate coefficient arrays. They should not alias.
  EXPECT_NE(c0, c1);

  EXPECT_DOUBLE_EQ(c0[0], 1.0);
  EXPECT_DOUBLE_EQ(c1[0], 3.0);
}

TEST_F(ExponentialFunctionTest_372, TransformUsesC1AtInputOne_372) {
  // If x==1, x^N==1, so output should be C1 (for domain [0,1]).
  std::unique_ptr<Dict> dict(MakeExponentialDict1Out(/*c0=*/-2.0, /*c1=*/5.0, /*n=*/2.0));
  ExponentialFunction func(dict.get());
  ASSERT_TRUE(func.isOk());

  double in[1] = {1.0};
  double out[1] = {0.0};

  func.transform(in, out);

  EXPECT_DOUBLE_EQ(out[0], 5.0);
}

TEST_F(ExponentialFunctionTest_372, TransformUsesC0AtInputZero_372) {
  // If x==0, x^N==0 (for positive N), output should be C0.
  std::unique_ptr<Dict> dict(MakeExponentialDict1Out(/*c0=*/1.5, /*c1=*/9.0, /*n=*/3.0));
  ExponentialFunction func(dict.get());
  ASSERT_TRUE(func.isOk());

  double in[1] = {0.0};
  double out[1] = {123.0};

  func.transform(in, out);

  EXPECT_DOUBLE_EQ(out[0], 1.5);
}

TEST_F(ExponentialFunctionTest_372, TransformLinearCaseMatchesInterpolation_372) {
  // With N=1, output should be linear interpolation: C0 + x*(C1-C0).
  std::unique_ptr<Dict> dict(MakeExponentialDict1Out(/*c0=*/1.0, /*c1=*/2.0, /*n=*/1.0));
  ExponentialFunction func(dict.get());
  ASSERT_TRUE(func.isOk());

  double in[1] = {0.5};
  double out[1] = {0.0};

  func.transform(in, out);

  EXPECT_DOUBLE_EQ(out[0], 1.5);
}

TEST_F(ExponentialFunctionTest_372, BoundaryInputOutsideDomainIsHandled_372) {
  // Observable boundary behavior: transform should handle inputs outside Domain gracefully.
  // Many Poppler builds clamp to domain, but regardless this must not crash and should
  // produce a finite number when isOk() is true.
  std::unique_ptr<Dict> dict(MakeExponentialDict1Out(/*c0=*/0.0, /*c1=*/1.0, /*n=*/1.0,
                                                    /*d0=*/0.0, /*d1=*/1.0));
  ExponentialFunction func(dict.get());
  ASSERT_TRUE(func.isOk());

  double outLow[1] = {0.0};
  double outHigh[1] = {0.0};

  double inLow[1] = {-1.0};
  double inHigh[1] = {2.0};

  func.transform(inLow, outLow);
  func.transform(inHigh, outHigh);

  EXPECT_TRUE(std::isfinite(outLow[0]));
  EXPECT_TRUE(std::isfinite(outHigh[0]));

  // If clamped, these would match C0 and C1 respectively; allow equality if so.
  // We avoid over-asserting implementation specifics beyond "graceful handling".
  EXPECT_GE(outLow[0], -1e308);
  EXPECT_LE(outLow[0], 1e308);
  EXPECT_GE(outHigh[0], -1e308);
  EXPECT_LE(outHigh[0], 1e308);
}

TEST_F(ExponentialFunctionTest_372, InvalidDictMakesIsOkFalseOrSafeToQueryGetC1_372) {
  // Exceptional/error case: missing required keys should lead to non-ok function.
  // We keep assertions conservative and only rely on public isOk() and safe accessor usage.
  auto *dict = new Dict(nullptr);
  std::unique_ptr<Dict> holder(dict);

  // Only set FunctionType=2, omit C0/C1/N/Domain.
  Object ft;
  ft.initInt(2);
  dict->add(const_cast<char *>("FunctionType"), std::move(ft));

  ExponentialFunction func(dict);
  EXPECT_FALSE(func.isOk());

  // Accessors should be safe to call even when not ok (should not crash).
  // We only assert that calling it is allowed and returns either nullptr or a pointer.
  const double *c1 = func.getC1();
  (void)c1;
}