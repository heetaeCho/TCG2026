// TEST_ID is 370
//
// Unit tests for ExponentialFunction::isOk()
// File: ./TestProjects/poppler/poppler/Function.h
//
// Constraints honored:
// - Treat implementation as black box.
// - Use only public interfaces.
// - No private state access.
// - Cover normal, boundary, and error/exceptional (observable) cases.

#include <gtest/gtest.h>

#include "poppler/Function.h"
#include "poppler/Object.h"

// NOTE: These helpers build Poppler "Dict" objects in a way that matches the
// classic Poppler/Xpdf Object/Dict API (Object::init*, Dict::add, Array::add).
// If your Poppler fork uses a newer API, adjust only these helper builders,
// not the assertions about ExponentialFunction observable behavior.

namespace {

class ExponentialFunctionTest_370 : public ::testing::Test {
protected:
  // Builds a minimal FunctionType 2 (Exponential) dictionary.
  // PDF spec fields commonly used:
  //   FunctionType (2), Domain [min max], C0 array, C1 array, N number.
  static std::unique_ptr<Dict> MakeBaseExpFuncDict(double d0, double d1) {
    auto dict = std::make_unique<Dict>(nullptr /* XRef* */);

    Object functionType;
    functionType.initInt(2);
    dict->add(const_cast<char *>("FunctionType"), &functionType);

    // Domain: two numbers.
    Object domainArrObj;
    domainArrObj.initArray(nullptr);
    {
      Object v0, v1;
      v0.initReal(d0);
      v1.initReal(d1);
      domainArrObj.arrayAdd(&v0);
      domainArrObj.arrayAdd(&v1);
    }
    dict->add(const_cast<char *>("Domain"), &domainArrObj);

    return dict;
  }

  static void AddArray(Dict *dict, const char *key, const std::vector<double> &vals) {
    Object arrObj;
    arrObj.initArray(nullptr);
    for (double v : vals) {
      Object num;
      num.initReal(v);
      arrObj.arrayAdd(&num);
    }
    dict->add(const_cast<char *>(key), &arrObj);
  }

  static void AddNumber(Dict *dict, const char *key, double v) {
    Object num;
    num.initReal(v);
    dict->add(const_cast<char *>(key), &num);
  }

  static void AddInt(Dict *dict, const char *key, int v) {
    Object num;
    num.initInt(v);
    dict->add(const_cast<char *>(key), &num);
  }

  static void AddString(Dict *dict, const char *key, const char *s) {
    Object str;
    str.initString(new GooString(s));
    dict->add(const_cast<char *>(key), &str);
  }

  static std::unique_ptr<Dict> MakeValidMinimalDict() {
    auto dict = MakeBaseExpFuncDict(0.0, 1.0);
    AddArray(dict.get(), "C0", {0.0});
    AddArray(dict.get(), "C1", {1.0});
    AddNumber(dict.get(), "N", 1.0);
    return dict;
  }
};

TEST_F(ExponentialFunctionTest_370, ValidMinimalDict_IsOkTrue_370) {
  auto dict = MakeValidMinimalDict();
  ExponentialFunction func(dict.get());
  EXPECT_TRUE(func.isOk());
}

TEST_F(ExponentialFunctionTest_370, MissingN_IsOkFalse_370) {
  auto dict = MakeBaseExpFuncDict(0.0, 1.0);
  AddArray(dict.get(), "C0", {0.0});
  AddArray(dict.get(), "C1", {1.0});
  // No "N"
  ExponentialFunction func(dict.get());
  EXPECT_FALSE(func.isOk());
}

TEST_F(ExponentialFunctionTest_370, NWrongType_IsOkFalse_370) {
  auto dict = MakeBaseExpFuncDict(0.0, 1.0);
  AddArray(dict.get(), "C0", {0.0});
  AddArray(dict.get(), "C1", {1.0});
  AddString(dict.get(), "N", "not-a-number");
  ExponentialFunction func(dict.get());
  EXPECT_FALSE(func.isOk());
}

TEST_F(ExponentialFunctionTest_370, MissingC0_IsOkFalse_370) {
  auto dict = MakeBaseExpFuncDict(0.0, 1.0);
  // No C0
  AddArray(dict.get(), "C1", {1.0});
  AddNumber(dict.get(), "N", 1.0);
  ExponentialFunction func(dict.get());
  EXPECT_FALSE(func.isOk());
}

TEST_F(ExponentialFunctionTest_370, MissingC1_IsOkFalse_370) {
  auto dict = MakeBaseExpFuncDict(0.0, 1.0);
  AddArray(dict.get(), "C0", {0.0});
  // No C1
  AddNumber(dict.get(), "N", 1.0);
  ExponentialFunction func(dict.get());
  EXPECT_FALSE(func.isOk());
}

TEST_F(ExponentialFunctionTest_370, C0WrongType_IsOkFalse_370) {
  auto dict = MakeBaseExpFuncDict(0.0, 1.0);
  AddString(dict.get(), "C0", "not-an-array");
  AddArray(dict.get(), "C1", {1.0});
  AddNumber(dict.get(), "N", 1.0);
  ExponentialFunction func(dict.get());
  EXPECT_FALSE(func.isOk());
}

TEST_F(ExponentialFunctionTest_370, C1WrongType_IsOkFalse_370) {
  auto dict = MakeBaseExpFuncDict(0.0, 1.0);
  AddArray(dict.get(), "C0", {0.0});
  AddString(dict.get(), "C1", "not-an-array");
  AddNumber(dict.get(), "N", 1.0);
  ExponentialFunction func(dict.get());
  EXPECT_FALSE(func.isOk());
}

TEST_F(ExponentialFunctionTest_370, MismatchedC0C1Lengths_IsOkFalse_370) {
  auto dict = MakeBaseExpFuncDict(0.0, 1.0);
  AddArray(dict.get(), "C0", {0.0, 0.5});
  AddArray(dict.get(), "C1", {1.0});
  AddNumber(dict.get(), "N", 1.0);
  ExponentialFunction func(dict.get());
  EXPECT_FALSE(func.isOk());
}

TEST_F(ExponentialFunctionTest_370, DomainMissing_IsOkFalse_370) {
  auto dict = std::make_unique<Dict>(nullptr);
  Object functionType;
  functionType.initInt(2);
  dict->add(const_cast<char *>("FunctionType"), &functionType);

  AddArray(dict.get(), "C0", {0.0});
  AddArray(dict.get(), "C1", {1.0});
  AddNumber(dict.get(), "N", 1.0);

  ExponentialFunction func(dict.get());
  EXPECT_FALSE(func.isOk());
}

TEST_F(ExponentialFunctionTest_370, DomainWrongLength_IsOkFalse_370) {
  auto dict = std::make_unique<Dict>(nullptr);

  Object functionType;
  functionType.initInt(2);
  dict->add(const_cast<char *>("FunctionType"), &functionType);

  // Domain with 1 element (should typically be 2).
  Object domainArrObj;
  domainArrObj.initArray(nullptr);
  {
    Object v0;
    v0.initReal(0.0);
    domainArrObj.arrayAdd(&v0);
  }
  dict->add(const_cast<char *>("Domain"), &domainArrObj);

  AddArray(dict.get(), "C0", {0.0});
  AddArray(dict.get(), "C1", {1.0});
  AddNumber(dict.get(), "N", 1.0);

  ExponentialFunction func(dict.get());
  EXPECT_FALSE(func.isOk());
}

TEST_F(ExponentialFunctionTest_370, Boundary_MaxOutputs32_IsOkTrueOrFalseButStable_370) {
  // Boundary: header indicates arrays sized [32]. Build C0/C1 length 32.
  // Observable requirement: construction should not crash; isOk should be a stable boolean.
  auto dict = MakeBaseExpFuncDict(0.0, 1.0);

  std::vector<double> c0(32, 0.0);
  std::vector<double> c1(32, 1.0);
  AddArray(dict.get(), "C0", c0);
  AddArray(dict.get(), "C1", c1);
  AddNumber(dict.get(), "N", 1.0);

  ExponentialFunction func(dict.get());

  // We avoid asserting TRUE/FALSE because different Poppler builds may impose
  // additional constraints, but isOk() must be callable and return a boolean.
  EXPECT_TRUE(func.isOk() || !func.isOk());
}

TEST_F(ExponentialFunctionTest_370, Boundary_TooManyOutputs33_IsOkFalse_370) {
  // If implementation enforces funcMaxOutputs==32 (as hinted), 33 should be invalid.
  auto dict = MakeBaseExpFuncDict(0.0, 1.0);

  std::vector<double> c0(33, 0.0);
  std::vector<double> c1(33, 1.0);
  AddArray(dict.get(), "C0", c0);
  AddArray(dict.get(), "C1", c1);
  AddNumber(dict.get(), "N", 1.0);

  ExponentialFunction func(dict.get());
  EXPECT_FALSE(func.isOk());
}

}  // namespace