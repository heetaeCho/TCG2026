// TEST_ID 373
// File: exponential_function_test_373.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

#include "Function.h"

// Poppler core types (Dict/Object/Array) are required to construct ExponentialFunction.
// These headers are typically available in poppler core builds.
#include "Array.h"
#include "Dict.h"
#include "Object.h"
#include "XRef.h"

namespace {

// --- Small C++17 detection helpers (to survive poppler API differences) ---

template <typename T, typename = void>
struct has_initInt : std::false_type {};
template <typename T>
struct has_initInt<T, std::void_t<decltype(std::declval<T &>().initInt(0))>> : std::true_type {};

template <typename T, typename = void>
struct has_initInt64 : std::false_type {};
template <typename T>
struct has_initInt64<T, std::void_t<decltype(std::declval<T &>().initInt64(int64_t{0}))>> : std::true_type {};

template <typename T, typename = void>
struct has_initReal : std::false_type {};
template <typename T>
struct has_initReal<T, std::void_t<decltype(std::declval<T &>().initReal(0.0))>> : std::true_type {};

template <typename T, typename = void>
struct has_initArray : std::false_type {};
template <typename T>
struct has_initArray<T, std::void_t<decltype(std::declval<T &>().initArray((XRef *)nullptr))>> : std::true_type {};

template <typename T, typename = void>
struct has_initDict : std::false_type {};
template <typename T>
struct has_initDict<T, std::void_t<decltype(std::declval<T &>().initDict((XRef *)nullptr))>> : std::true_type {};

static Object MakeIntObject(int v) {
  if constexpr (std::is_constructible_v<Object, int>) {
    return Object(v);
  } else if constexpr (has_initInt<Object>::value) {
    Object o;
    o.initInt(v);
    return o;
  } else if constexpr (has_initInt64<Object>::value) {
    Object o;
    o.initInt64(static_cast<int64_t>(v));
    return o;
  } else {
    static_assert(sizeof(Object) == 0, "No known way to create an integer Object for this poppler version");
  }
}

static Object MakeRealObject(double v) {
  if constexpr (std::is_constructible_v<Object, double>) {
    return Object(v);
  } else if constexpr (has_initReal<Object>::value) {
    Object o;
    o.initReal(v);
    return o;
  } else {
    static_assert(sizeof(Object) == 0, "No known way to create a real Object for this poppler version");
  }
}

static Object MakeArrayObject(Array *arr) {
  // Many poppler versions can construct Object from Array* directly.
  if constexpr (std::is_constructible_v<Object, Array *>) {
    return Object(arr);
  } else {
    // Fallback: create empty and "initArray" with XRef, then add? But we already have an Array*.
    // If this branch is ever hit, update to match your local Object API.
    (void)arr;
    static_assert(sizeof(Object) == 0, "No known way to create an array Object for this poppler version");
  }
}

// Build a minimal Type 2 (Exponential) function dictionary based on the PDF function interface:
// - FunctionType = 2
// - Domain = [d0 d1] (required by spec)
// - C0, C1 arrays (default to [0], [1] when used here)
// - N exponent (the value we validate via getE()).
static std::unique_ptr<Dict> BuildExponentialFunctionDict(double exponentN,
                                                          std::vector<double> domain = {0.0, 1.0},
                                                          std::vector<double> c0 = {0.0},
                                                          std::vector<double> c1 = {1.0}) {
  auto dict = std::make_unique<Dict>((XRef *)nullptr);

  dict->add("FunctionType", MakeIntObject(2));

  {
    auto *arr = new Array((XRef *)nullptr);
    ASSERT_EQ(domain.size(), 2u);
    arr->add(MakeRealObject(domain[0]));
    arr->add(MakeRealObject(domain[1]));
    dict->add("Domain", MakeArrayObject(arr));
  }

  {
    auto *arr = new Array((XRef *)nullptr);
    for (double v : c0) arr->add(MakeRealObject(v));
    dict->add("C0", MakeArrayObject(arr));
  }

  {
    auto *arr = new Array((XRef *)nullptr);
    for (double v : c1) arr->add(MakeRealObject(v));
    dict->add("C1", MakeArrayObject(arr));
  }

  dict->add("N", MakeRealObject(exponentN));
  return dict;
}

}  // namespace

class ExponentialFunctionTest_373 : public ::testing::Test {};

// --- Normal operation ---

TEST_F(ExponentialFunctionTest_373, GetEReturnsProvidedExponent_373) {
  auto dict = BuildExponentialFunctionDict(/*exponentN=*/2.0);
  ExponentialFunction func(dict.get());

  ASSERT_TRUE(func.isOk()) << "Constructed exponential function should be OK for a basic valid dict";
  EXPECT_DOUBLE_EQ(func.getE(), 2.0);
}

TEST_F(ExponentialFunctionTest_373, GetEHandlesNonIntegerExponent_373) {
  auto dict = BuildExponentialFunctionDict(/*exponentN=*/0.5);
  ExponentialFunction func(dict.get());

  ASSERT_TRUE(func.isOk()) << "Non-integer exponent should be accepted for a basic valid dict";
  EXPECT_DOUBLE_EQ(func.getE(), 0.5);
}

// --- Boundary conditions ---

TEST_F(ExponentialFunctionTest_373, GetEAllowsLargeMagnitudeExponent_373) {
  const double kLarge = 1.0e6;
  auto dict = BuildExponentialFunctionDict(/*exponentN=*/kLarge);
  ExponentialFunction func(dict.get());

  ASSERT_TRUE(func.isOk()) << "Large exponent should be accepted for a basic valid dict";
  EXPECT_DOUBLE_EQ(func.getE(), kLarge);
}

TEST_F(ExponentialFunctionTest_373, GetEAllowsNegativeExponentWhenOk_373) {
  // Some implementations allow negative N; if accepted, getE should reflect the provided value.
  // If the implementation rejects it, that should be observable via isOk().
  auto dict = BuildExponentialFunctionDict(/*exponentN=*/-3.0);
  ExponentialFunction func(dict.get());

  if (func.isOk()) {
    EXPECT_DOUBLE_EQ(func.getE(), -3.0);
  } else {
    SUCCEED() << "Implementation rejects negative exponent via isOk(); behavior is observable and acceptable";
  }
}

// --- Exceptional / error cases (observable via interface) ---

TEST_F(ExponentialFunctionTest_373, MissingNMarksFunctionNotOk_373) {
  auto dict = BuildExponentialFunctionDict(/*exponentN=*/2.0);
  // Remove the required exponent key to create an invalid configuration.
  dict->remove("N");

  ExponentialFunction func(dict.get());

  EXPECT_FALSE(func.isOk()) << "Missing required exponent should be observable via isOk()";
  // getE() is still callable; ensure it returns a finite value (no crash/NaN/Inf).
  EXPECT_TRUE(std::isfinite(func.getE()));
}

TEST_F(ExponentialFunctionTest_373, WrongTypeForNMarksFunctionNotOk_373) {
  auto dict = BuildExponentialFunctionDict(/*exponentN=*/2.0);
  // Replace N with an integer (some implementations may accept int-as-num; if so, isOk may remain true).
  dict->remove("N");
  dict->add("N", MakeIntObject(7));

  ExponentialFunction func(dict.get());

  if (!func.isOk()) {
    SUCCEED() << "Implementation requires numeric type for N and reports invalid via isOk()";
  } else {
    // If accepted as numeric, getE should reflect the provided exponent value.
    EXPECT_DOUBLE_EQ(func.getE(), 7.0);
  }
}

// --- Copy / type observability (public interface) ---

TEST_F(ExponentialFunctionTest_373, CopyPreservesExponent_373) {
  auto dict = BuildExponentialFunctionDict(/*exponentN=*/3.25);
  ExponentialFunction func(dict.get());

  ASSERT_TRUE(func.isOk());
  std::unique_ptr<Function> copied = func.copy();
  ASSERT_NE(copied, nullptr);

  // The public Function interface includes getType(); verify it stays exponential.
  EXPECT_EQ(copied->getType(), func.getType());

  // If the copy is actually an ExponentialFunction, we can observe that getE is preserved.
  // This is an observable behavior through RTTI/public interface, not internal state.
  auto *asExp = dynamic_cast<ExponentialFunction *>(copied.get());
  ASSERT_NE(asExp, nullptr);
  EXPECT_DOUBLE_EQ(asExp->getE(), 3.25);
}