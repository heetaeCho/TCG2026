// SPDX-License-Identifier: GPL-2.0-or-later
//
// File: StitchingFunction_getEncode_380_test.cpp
//
// Unit tests for poppler::StitchingFunction::getEncode()
// Constraints respected:
//  - Treat implementation as black box
//  - Only use public/observable behavior (isOk(), getType(), copy(), getEncode(), etc.)
//  - No private state access

#include <gtest/gtest.h>

#include "poppler/Function.h"

// Poppler object model headers are typically needed to build Dict/Array inputs.
// Depending on your poppler tree layout, you may need to adjust include paths.
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/Array.h"
#include "poppler/RefRecursionChecker.h"

namespace {

// Helper: create a simple sampled function (FunctionType 0) dict.
// This is used as a sub-function inside a StitchingFunction (FunctionType 3).
// The goal is only to construct a *parseable* function object; tests do not
// assume any internal behavior beyond public API (isOk(), etc.).
static std::unique_ptr<Dict> MakeMinimalSampledFuncDict()
{
  // Many poppler Dict constructors take an XRef*. Use nullptr for unit tests
  // if your build allows it (common in poppler unit tests). If your poppler
  // requires an XRef, adapt accordingly.
  auto d = std::make_unique<Dict>(nullptr);

  // PDF function basics
  d->add("FunctionType", Object(0));
  {
    auto domain = std::make_unique<Array>(nullptr);
    domain->add(Object(0.0));
    domain->add(Object(1.0));
    d->add("Domain", Object(domain.release()));
  }
  {
    auto range = std::make_unique<Array>(nullptr);
    range->add(Object(0.0));
    range->add(Object(1.0));
    d->add("Range", Object(range.release()));
  }

  // Sampled function required keys (minimal)
  d->add("Size", Object((new Array(nullptr))->add(Object(2)).release()));
  d->add("BitsPerSample", Object(8));
  d->add("Order", Object(1));
  d->add("Encode", Object((new Array(nullptr))->add(Object(0.0)).add(Object(1.0)).release()));
  d->add("Decode", Object((new Array(nullptr))->add(Object(0.0)).add(Object(1.0)).release()));

  // Sample table "DataSource" (stream). In many builds, Function parser can
  // accept a string as a data source too; if yours requires a Stream, adjust.
  // Keep it tiny; exact content is not asserted in these tests.
  d->add("DataSource", Object("00"));

  return d;
}

// Helper: create a valid StitchingFunction (FunctionType 3) dict with N funcs,
// bounds and encode arrays. This is based on the PDF FunctionType 3 structure.
static std::unique_ptr<Dict> MakeStitchingFuncDict(
    int numFuncs,
    const std::vector<double> &boundsVals,
    const std::vector<double> &encodeVals)
{
  auto d = std::make_unique<Dict>(nullptr);
  d->add("FunctionType", Object(3));

  // Domain for 1 input
  {
    auto domain = std::make_unique<Array>(nullptr);
    domain->add(Object(0.0));
    domain->add(Object(1.0));
    d->add("Domain", Object(domain.release()));
  }

  // Range for 1 output (keep simple; some builds may not require Range)
  {
    auto range = std::make_unique<Array>(nullptr);
    range->add(Object(0.0));
    range->add(Object(1.0));
    d->add("Range", Object(range.release()));
  }

  // Functions array
  {
    auto funcsArr = std::make_unique<Array>(nullptr);
    for (int i = 0; i < numFuncs; ++i) {
      auto sub = MakeMinimalSampledFuncDict();
      funcsArr->add(Object(sub.release()));
    }
    d->add("Functions", Object(funcsArr.release()));
  }

  // Bounds array (length = numFuncs - 1)
  {
    auto bounds = std::make_unique<Array>(nullptr);
    for (double v : boundsVals) {
      bounds->add(Object(v));
    }
    d->add("Bounds", Object(bounds.release()));
  }

  // Encode array (length = 2 * numFuncs)
  {
    auto encode = std::make_unique<Array>(nullptr);
    for (double v : encodeVals) {
      encode->add(Object(v));
    }
    d->add("Encode", Object(encode.release()));
  }

  return d;
}

static StitchingFunction *ParseStitchingFunction(Dict *dict)
{
  RefRecursionChecker usedParents; // default-constructed recursion checker
  // StitchingFunction is constructed directly from Dict in poppler
  auto *sf = new StitchingFunction(dict, usedParents);
  return sf;
}

} // namespace

class StitchingFunctionTest_380 : public ::testing::Test {
protected:
  void TearDown() override
  {
    // Nothing: each test owns/free objects explicitly.
  }
};

TEST_F(StitchingFunctionTest_380, GetEncode_NonNullForValidDict_380)
{
  // 2 sub-functions => bounds length 1, encode length 4
  auto dict = MakeStitchingFuncDict(
      /*numFuncs=*/2,
      /*boundsVals=*/{0.5},
      /*encodeVals=*/{0.0, 1.0, 0.0, 1.0});

  std::unique_ptr<StitchingFunction> sf(ParseStitchingFunction(dict.get()));
  ASSERT_NE(sf, nullptr);

  ASSERT_TRUE(sf->isOk()) << "Expected a valid StitchingFunction from a well-formed dict";
  const double *enc = sf->getEncode();
  ASSERT_NE(enc, nullptr) << "getEncode() should return a non-null pointer when function is OK";
}

TEST_F(StitchingFunctionTest_380, GetEncode_ReturnsStablePointerAcrossCalls_380)
{
  auto dict = MakeStitchingFuncDict(
      /*numFuncs=*/2,
      /*boundsVals=*/{0.5},
      /*encodeVals=*/{0.0, 1.0, 0.0, 1.0});

  std::unique_ptr<StitchingFunction> sf(ParseStitchingFunction(dict.get()));
  ASSERT_TRUE(sf->isOk());

  const double *p1 = sf->getEncode();
  const double *p2 = sf->getEncode();
  ASSERT_NE(p1, nullptr);
  EXPECT_EQ(p1, p2) << "Repeated getEncode() calls should return the same pointer for the same object";
}

TEST_F(StitchingFunctionTest_380, GetEncode_ReflectsEncodeArrayValues_380)
{
  const std::vector<double> encodeVals = {0.0, 1.0, 2.0, 3.0};
  auto dict = MakeStitchingFuncDict(
      /*numFuncs=*/2,
      /*boundsVals=*/{0.5},
      /*encodeVals=*/encodeVals);

  std::unique_ptr<StitchingFunction> sf(ParseStitchingFunction(dict.get()));
  ASSERT_TRUE(sf->isOk());

  const double *enc = sf->getEncode();
  ASSERT_NE(enc, nullptr);

  // We only assert values we provided via the public input dictionary.
  // This checks observable behavior via getEncode(), without relying on internals.
  EXPECT_DOUBLE_EQ(enc[0], encodeVals[0]);
  EXPECT_DOUBLE_EQ(enc[1], encodeVals[1]);
  EXPECT_DOUBLE_EQ(enc[2], encodeVals[2]);
  EXPECT_DOUBLE_EQ(enc[3], encodeVals[3]);
}

TEST_F(StitchingFunctionTest_380, GetEncode_WorksWithSingleSubFunction_Boundary_380)
{
  // Boundary-ish case: 1 sub-function => bounds length 0, encode length 2
  const std::vector<double> encodeVals = {10.0, 20.0};
  auto dict = MakeStitchingFuncDict(
      /*numFuncs=*/1,
      /*boundsVals=*/{},
      /*encodeVals=*/encodeVals);

  std::unique_ptr<StitchingFunction> sf(ParseStitchingFunction(dict.get()));
  ASSERT_NE(sf, nullptr);

  ASSERT_TRUE(sf->isOk());
  const double *enc = sf->getEncode();
  ASSERT_NE(enc, nullptr);
  EXPECT_DOUBLE_EQ(enc[0], encodeVals[0]);
  EXPECT_DOUBLE_EQ(enc[1], encodeVals[1]);
}

TEST_F(StitchingFunctionTest_380, Copy_PreservesEncodeValues_380)
{
  const std::vector<double> encodeVals = {0.0, 1.0, 5.0, 6.0};
  auto dict = MakeStitchingFuncDict(
      /*numFuncs=*/2,
      /*boundsVals=*/{0.25},
      /*encodeVals=*/encodeVals);

  std::unique_ptr<StitchingFunction> sf(ParseStitchingFunction(dict.get()));
  ASSERT_TRUE(sf->isOk());

  std::unique_ptr<Function> copied = sf->copy();
  ASSERT_NE(copied, nullptr);

  // Ensure we really got a stitching function copy (observable via RTTI).
  auto *sfCopy = dynamic_cast<StitchingFunction *>(copied.get());
  ASSERT_NE(sfCopy, nullptr);

  ASSERT_TRUE(sfCopy->isOk());
  const double *enc = sfCopy->getEncode();
  ASSERT_NE(enc, nullptr);

  EXPECT_DOUBLE_EQ(enc[0], encodeVals[0]);
  EXPECT_DOUBLE_EQ(enc[1], encodeVals[1]);
  EXPECT_DOUBLE_EQ(enc[2], encodeVals[2]);
  EXPECT_DOUBLE_EQ(enc[3], encodeVals[3]);
}

TEST_F(StitchingFunctionTest_380, MissingEncode_IsErrorOrProducesNullEncode_380)
{
  // Construct a StitchingFunction dict but omit /Encode.
  auto d = std::make_unique<Dict>(nullptr);
  d->add("FunctionType", Object(3));
  {
    auto domain = std::make_unique<Array>(nullptr);
    domain->add(Object(0.0));
    domain->add(Object(1.0));
    d->add("Domain", Object(domain.release()));
  }
  {
    auto funcsArr = std::make_unique<Array>(nullptr);
    funcsArr->add(Object(MakeMinimalSampledFuncDict().release()));
    funcsArr->add(Object(MakeMinimalSampledFuncDict().release()));
    d->add("Functions", Object(funcsArr.release()));
  }
  {
    auto bounds = std::make_unique<Array>(nullptr);
    bounds->add(Object(0.5));
    d->add("Bounds", Object(bounds.release()));
  }

  std::unique_ptr<StitchingFunction> sf(ParseStitchingFunction(d.get()));
  ASSERT_NE(sf, nullptr);

  // We only assert what is observable and robust:
  // - Either the function is not OK (common), OR it is OK but encode is null.
  // We do NOT dereference encode in this error-path test.
  if (sf->isOk()) {
    EXPECT_EQ(sf->getEncode(), nullptr) << "If function reports OK, getEncode() should still be safe";
  } else {
    // On error, getEncode() should not crash; it may be null.
    (void)sf->getEncode();
    SUCCEED();
  }
}