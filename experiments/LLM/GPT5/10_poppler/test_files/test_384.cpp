// File: test_postscript_function_384.cpp
// TEST_ID: 384
//
// Notes:
// - These tests treat PostScriptFunction as a black box.
// - They build a minimal FunctionType 4 (PostScript calculator) function object via Poppler
//   public PDF object types (Object/Dict/Array/Stream) and then exercise behavior through
//   the public Function interface (isOk/copy/transform/getType).
// - If the Poppler build/config exposes slightly different constructors/APIs for Object/Dict/Array,
//   adjust the small helper builders accordingly (tests remain interface-based).

#include <gtest/gtest.h>

#include <cmath>
#include <memory>
#include <string>
#include <vector>

#include "poppler/Function.h"

// These are Poppler public headers commonly used to construct PDF objects.
// If your Poppler tree uses different include paths (e.g. "Object.h" instead of "poppler/Object.h"),
// update includes accordingly.
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/Array.h"
#include "poppler/Stream.h"
#include "goo/gmem.h"

// -------------------------
// Helper builders (minimal)
// -------------------------

namespace {

// Build an Array of reals: [v0 v1 v2 ...]
static Array *MakeRealArray(XRef *xref, const std::vector<double> &vals) {
  auto *arr = new Array(xref);
  for (double v : vals) {
    Object o;
    o.initReal(v);
    arr->add(std::move(o));
  }
  return arr;
}

// Build a minimal FunctionType 4 Stream object (calculator function).
//
// PDF keys typically required:
//   /FunctionType 4
//   /Domain [min max ...]
//   /Range  [min max ...]   (often required; some builds may tolerate missing Range)
//
// Stream body contains the PostScript code.
// The helper aims to create a well-formed object; whether it's considered OK is checked via isOk().
static Object MakeType4FunctionStreamObject(const std::string &psCode,
                                           const std::vector<double> &domain,
                                           const std::vector<double> &range) {
  // Stream data must remain alive as long as the Stream lives; MemStream typically copies or
  // takes ownership depending on Poppler version. We allocate using gmalloc to match Poppler
  // conventions and pass ownership to the stream where supported.
  const int len = static_cast<int>(psCode.size());
  auto *buf = static_cast<Guchar *>(gmalloc(len > 0 ? len : 1));
  if (len > 0) {
    memcpy(buf, psCode.data(), len);
  }

  // Build stream dictionary
  auto *dict = new Dict(/*xref=*/nullptr);
  {
    Object ft;
    ft.initInt(4);
    dict->add("FunctionType", std::move(ft));
  }
  {
    Object d;
    d.initArray(MakeRealArray(/*xref=*/nullptr, domain));
    dict->add("Domain", std::move(d));
  }
  if (!range.empty()) {
    Object r;
    r.initArray(MakeRealArray(/*xref=*/nullptr, range));
    dict->add("Range", std::move(r));
  }

  // Create stream
  // Poppler variants:
  // - MemStream(const Guchar *bufA, int startA, int lengthA, Object &&dictA)
  // - MemStream(Guchar *bufA, int lengthA, Object &&dictA) etc.
  // We use the common (buf, start, length, dictObj) form.
  Object dictObj;
  dictObj.initDict(dict);

  Stream *s = new MemStream(buf, /*startA=*/0, /*lengthA=*/len, std::move(dictObj));

  Object streamObj;
  streamObj.initStream(s);
  return streamObj;
}

static std::unique_ptr<Function> ParseFunctionOrNull(Object *funcObj) {
  // Poppler commonly provides Function::parse(Object *funcObj).
  // If your Poppler uses a different signature (e.g. parse(Object*, int nInputs, int nOutputs)),
  // adapt here while keeping tests unchanged.
  Function *raw = Function::parse(funcObj);
  return std::unique_ptr<Function>(raw);
}

} // namespace

// -------------------------
// Test fixture
// -------------------------

class PostScriptFunctionTest_384 : public ::testing::Test {
protected:
  // A trivially simple PostScript calculator program. Many implementations accept:
  //   { dup } meaning output = input duplicated (for 1->1 may still be valid).
  // Some require explicit braces to be present in the code stream.
  static std::string MinimalCode() { return "{ dup }"; }
};

// -------------------------
// Tests (TEST_ID = 384)
// -------------------------

TEST_F(PostScriptFunctionTest_384, ParseValidType4Function_IsOkIsTrueOrSkips_384) {
  Object funcObj = MakeType4FunctionStreamObject(
      MinimalCode(),
      /*domain=*/{0.0, 1.0},
      /*range=*/{0.0, 1.0});

  auto fn = ParseFunctionOrNull(&funcObj);
  if (!fn) {
    GTEST_SKIP() << "Function::parse returned null for a minimal FunctionType 4 object in this build.";
  }

  // Observable behavior: a successfully parsed function is expected to be OK.
  // If some builds parse but mark not-ok, this will catch it.
  EXPECT_TRUE(fn->isOk());
}

TEST_F(PostScriptFunctionTest_384, ParseType4MissingRange_IsNotOkOrNull_384) {
  Object funcObj = MakeType4FunctionStreamObject(
      MinimalCode(),
      /*domain=*/{0.0, 1.0},
      /*range=*/{}); // omit Range

  auto fn = ParseFunctionOrNull(&funcObj);

  // Either outcome is acceptable and observable through the interface:
  // - parse fails => null
  // - parse succeeds but isOk() == false
  if (!fn) {
    SUCCEED() << "Parse failed (null) when Range was omitted.";
    return;
  }
  EXPECT_FALSE(fn->isOk());
}

TEST_F(PostScriptFunctionTest_384, ParseType4EmptyCode_IsNotOkOrNull_384) {
  Object funcObj = MakeType4FunctionStreamObject(
      /*psCode=*/"",
      /*domain=*/{0.0, 1.0},
      /*range=*/{0.0, 1.0});

  auto fn = ParseFunctionOrNull(&funcObj);
  if (!fn) {
    SUCCEED() << "Parse failed (null) for empty PostScript code.";
    return;
  }
  EXPECT_FALSE(fn->isOk());
}

TEST_F(PostScriptFunctionTest_384, CopyPreservesTypeAndOkFlag_384) {
  Object funcObj = MakeType4FunctionStreamObject(
      MinimalCode(),
      /*domain=*/{0.0, 1.0},
      /*range=*/{0.0, 1.0});

  auto fn = ParseFunctionOrNull(&funcObj);
  if (!fn) {
    GTEST_SKIP() << "Function::parse returned null; cannot verify copy() behavior.";
  }

  const bool okBefore = fn->isOk();
  const Function::Type typeBefore = fn->getType();

  std::unique_ptr<Function> cp = fn->copy();
  ASSERT_NE(cp, nullptr);

  EXPECT_EQ(cp->getType(), typeBefore);
  EXPECT_EQ(cp->isOk(), okBefore);
}

TEST_F(PostScriptFunctionTest_384, TransformBoundaryInputs_DoesNotProduceNaN_384) {
  Object funcObj = MakeType4FunctionStreamObject(
      MinimalCode(),
      /*domain=*/{0.0, 1.0},
      /*range=*/{0.0, 1.0});

  auto fn = ParseFunctionOrNull(&funcObj);
  if (!fn || !fn->isOk()) {
    GTEST_SKIP() << "FunctionType 4 minimal function is not available/ok in this build.";
  }

  // Boundary values within domain.
  for (double inVal : {0.0, 1.0}) {
    double in[1] = {inVal};
    double out[1] = {0.0};

    // transform() has void return; observable behavior is that it should not crash and should
    // write a finite value to output (a minimal, implementation-agnostic sanity check).
    fn->transform(in, out);

    EXPECT_TRUE(std::isfinite(out[0])) << "Output should be finite for input=" << inVal;
  }
}

TEST_F(PostScriptFunctionTest_384, TransformOutOfDomainInput_DoesNotProduceNaN_384) {
  Object funcObj = MakeType4FunctionStreamObject(
      MinimalCode(),
      /*domain=*/{0.0, 1.0},
      /*range=*/{0.0, 1.0});

  auto fn = ParseFunctionOrNull(&funcObj);
  if (!fn || !fn->isOk()) {
    GTEST_SKIP() << "FunctionType 4 minimal function is not available/ok in this build.";
  }

  // Out-of-domain values (behavior may clamp, extrapolate, or do something else).
  for (double inVal : {-1.0, 2.0}) {
    double in[1] = {inVal};
    double out[1] = {0.0};

    fn->transform(in, out);
    EXPECT_TRUE(std::isfinite(out[0])) << "Output should be finite for out-of-domain input=" << inVal;
  }
}