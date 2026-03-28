// File: exponential_function_test_369.cpp
//
// Unit tests for ExponentialFunction (Poppler)
// Constraints respected:
// - Treat implementation as black box
// - Only verify observable behavior via public interface
// - No private state access
// - Use mocks only for external collaborators (none needed here)

#include <gtest/gtest.h>

#include <cmath>
#include <memory>
#include <vector>

#include "poppler/Function.h"

// Poppler headers vary a bit by version; these are commonly needed to build Dict/Array/Object.
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/Array.h"

namespace {

constexpr int TEST_ID = 369;

// Helper: add a real number to an Array in a way that matches common Poppler APIs.
static void AddRealToArray(Array* arr, double v) {
  // Many Poppler versions have: arr->add(Object(v)) or arr->add(Object(objReal, v)).
  // Try the most common form first.
#if defined(__clang__) || defined(__GNUC__)
  // Keep it simple; if your Poppler version requires a different Object constructor,
  // adapt these small helpers rather than changing the tests.
#endif
  arr->add(Object(v));
}

static void AddIntToArray(Array* arr, int v) {
  arr->add(Object(v));
}

static std::unique_ptr<Dict> MakeValidExponentialDict_OneOutput() {
  // PDF FunctionType 2 (Exponential interpolation):
  // Required: FunctionType=2, Domain=[xmin xmax], C0, C1, N
  // Optional: Range
  auto dict = std::make_unique<Dict>();

  dict->add("FunctionType", Object(2));

  {
    auto domain = std::make_unique<Array>();
    AddRealToArray(domain.get(), 0.0);
    AddRealToArray(domain.get(), 1.0);
    dict->add("Domain", Object(domain.release()));
  }

  {
    // Single output: C0=[0], C1=[1]
    auto c0 = std::make_unique<Array>();
    AddRealToArray(c0.get(), 0.0);
    dict->add("C0", Object(c0.release()));

    auto c1 = std::make_unique<Array>();
    AddRealToArray(c1.get(), 1.0);
    dict->add("C1", Object(c1.release()));
  }

  dict->add("N", Object(1.0));

  {
    // Optional Range for one output: [0 1]
    auto range = std::make_unique<Array>();
    AddRealToArray(range.get(), 0.0);
    AddRealToArray(range.get(), 1.0);
    dict->add("Range", Object(range.release()));
  }

  return dict;
}

static std::unique_ptr<Dict> MakeValidExponentialDict_TwoOutputs() {
  auto dict = std::make_unique<Dict>();

  dict->add("FunctionType", Object(2));

  {
    auto domain = std::make_unique<Array>();
    AddRealToArray(domain.get(), 0.0);
    AddRealToArray(domain.get(), 1.0);
    dict->add("Domain", Object(domain.release()));
  }

  {
    // Two outputs: C0=[0, 0.5], C1=[1, 1.5]
    auto c0 = std::make_unique<Array>();
    AddRealToArray(c0.get(), 0.0);
    AddRealToArray(c0.get(), 0.5);
    dict->add("C0", Object(c0.release()));

    auto c1 = std::make_unique<Array>();
    AddRealToArray(c1.get(), 1.0);
    AddRealToArray(c1.get(), 1.5);
    dict->add("C1", Object(c1.release()));
  }

  dict->add("N", Object(2.0));

  {
    // Range for two outputs: [0 1 0 2]
    auto range = std::make_unique<Array>();
    AddRealToArray(range.get(), 0.0);
    AddRealToArray(range.get(), 1.0);
    AddRealToArray(range.get(), 0.0);
    AddRealToArray(range.get(), 2.0);
    dict->add("Range", Object(range.release()));
  }

  return dict;
}

static std::unique_ptr<Dict> MakeInvalidExponentialDict_MissingDomain() {
  auto dict = std::make_unique<Dict>();
  dict->add("FunctionType", Object(2));
  // Missing Domain
  auto c0 = std::make_unique<Array>();
  AddRealToArray(c0.get(), 0.0);
  dict->add("C0", Object(c0.release()));

  auto c1 = std::make_unique<Array>();
  AddRealToArray(c1.get(), 1.0);
  dict->add("C1", Object(c1.release()));

  dict->add("N", Object(1.0));
  return dict;
}

static std::unique_ptr<Dict> MakeInvalidExponentialDict_C0C1Mismatch() {
  auto dict = std::make_unique<Dict>();
  dict->add("FunctionType", Object(2));

  auto domain = std::make_unique<Array>();
  AddRealToArray(domain.get(), 0.0);
  AddRealToArray(domain.get(), 1.0);
  dict->add("Domain", Object(domain.release()));

  // C0 has 1 element, C1 has 2 elements (mismatch)
  auto c0 = std::make_unique<Array>();
  AddRealToArray(c0.get(), 0.0);
  dict->add("C0", Object(c0.release()));

  auto c1 = std::make_unique<Array>();
  AddRealToArray(c1.get(), 1.0);
  AddRealToArray(c1.get(), 2.0);
  dict->add("C1", Object(c1.release()));

  dict->add("N", Object(1.0));
  return dict;
}

class ExponentialFunctionTest_369 : public ::testing::Test {
 protected:
  static std::unique_ptr<ExponentialFunction> MakeFuncFromDict(std::unique_ptr<Dict> dict) {
    // ExponentialFunction takes Dict* (ownership not specified by interface snippet).
    // We keep Dict alive for the lifetime of ExponentialFunction in each test by
    // storing it in a unique_ptr member when needed.
    //
    // Here, we pass the raw pointer and transfer the unique_ptr to the caller via
    // a side-channel (returning both) is overkill. Instead, tests that need lifetime
    // control will keep dict_ as a member and construct directly.
    (void)dict;
    return nullptr;
  }
};

}  // namespace

// --- Tests ---

TEST_F(ExponentialFunctionTest_369, GetTypeReturnsExponential_369) {
  auto dict = MakeValidExponentialDict_OneOutput();
  ExponentialFunction func(dict.get());

  EXPECT_EQ(func.getType(), Function::Type::Exponential);
}

TEST_F(ExponentialFunctionTest_369, IsOkTrueForWellFormedDict_369) {
  auto dict = MakeValidExponentialDict_OneOutput();
  ExponentialFunction func(dict.get());

  EXPECT_TRUE(func.isOk());
}

TEST_F(ExponentialFunctionTest_369, IsOkFalseWhenMissingDomain_369) {
  auto dict = MakeInvalidExponentialDict_MissingDomain();
  ExponentialFunction func(dict.get());

  EXPECT_FALSE(func.isOk());
}

TEST_F(ExponentialFunctionTest_369, IsOkFalseWhenC0C1SizeMismatch_369) {
  auto dict = MakeInvalidExponentialDict_C0C1Mismatch();
  ExponentialFunction func(dict.get());

  EXPECT_FALSE(func.isOk());
}

TEST_F(ExponentialFunctionTest_369, CopyProducesNonNullFunctionWithSameType_369) {
  auto dict = MakeValidExponentialDict_OneOutput();
  ExponentialFunction func(dict.get());
  ASSERT_TRUE(func.isOk());

  std::unique_ptr<Function> copied = func.copy();
  ASSERT_NE(copied, nullptr);
  EXPECT_EQ(copied->getType(), Function::Type::Exponential);

  // Also verify the copy is a distinct object.
  EXPECT_NE(copied.get(), &func);
}

TEST_F(ExponentialFunctionTest_369, TransformDoesNotCrashForSingleOutput_369) {
  auto dict = MakeValidExponentialDict_OneOutput();
  ExponentialFunction func(dict.get());
  ASSERT_TRUE(func.isOk());

  double in[1] = {0.25};
  double out[1] = {std::nan("")};

  // Observable behavior we can safely assert without inferring math:
  // - call succeeds
  // - output becomes a finite number (typical for well-formed function and finite input)
  func.transform(in, out);

  EXPECT_TRUE(std::isfinite(out[0]));
}

TEST_F(ExponentialFunctionTest_369, TransformHandlesTwoOutputs_369) {
  auto dict = MakeValidExponentialDict_TwoOutputs();
  ExponentialFunction func(dict.get());
  ASSERT_TRUE(func.isOk());

  double in[1] = {0.75};
  double out[2] = {std::nan(""), std::nan("")};

  func.transform(in, out);

  EXPECT_TRUE(std::isfinite(out[0]));
  EXPECT_TRUE(std::isfinite(out[1]));
}

TEST_F(ExponentialFunctionTest_369, TransformBoundaryInputsAtDomainEnds_369) {
  auto dict = MakeValidExponentialDict_OneOutput();
  ExponentialFunction func(dict.get());
  ASSERT_TRUE(func.isOk());

  {
    double in[1] = {0.0};
    double out[1] = {std::nan("")};
    func.transform(in, out);
    EXPECT_TRUE(std::isfinite(out[0]));
  }

  {
    double in[1] = {1.0};
    double out[1] = {std::nan("")};
    func.transform(in, out);
    EXPECT_TRUE(std::isfinite(out[0]));
  }
}

TEST_F(ExponentialFunctionTest_369, GetC0C1PointersAreNonNullWhenOk_369) {
  auto dict = MakeValidExponentialDict_TwoOutputs();
  ExponentialFunction func(dict.get());
  ASSERT_TRUE(func.isOk());

  const double* c0 = func.getC0();
  const double* c1 = func.getC1();

  EXPECT_NE(c0, nullptr);
  EXPECT_NE(c1, nullptr);

  // Boundary/consistency: accessing first couple entries should be safe.
  // We do not assert specific values (black-box), only that they're finite.
  EXPECT_TRUE(std::isfinite(c0[0]));
  EXPECT_TRUE(std::isfinite(c1[0]));
}

TEST_F(ExponentialFunctionTest_369, GetEIsFiniteWhenOk_369) {
  auto dict = MakeValidExponentialDict_OneOutput();
  ExponentialFunction func(dict.get());
  ASSERT_TRUE(func.isOk());

  const double e = func.getE();
  EXPECT_TRUE(std::isfinite(e));
}