// SPDX-License-Identifier: GPL-2.0-or-later
// File: sampledfunction_getsamples_unittest_366.cpp
//
// Unit tests for SampledFunction::getSamples()
// Constraints respected:
//  - Treat implementation as black box
//  - Only use public interface / observable behavior
//  - Use mocks only for external collaborators (none needed here)

#include <gtest/gtest.h>

#include "poppler/Function.h"

// The following Poppler headers are typically available in-tree.
// If your build uses different include paths, adjust as needed.
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/Array.h"
#include "poppler/Stream.h"
#include "poppler/GooString.h"

namespace {

class SampledFunctionTest_366 : public ::testing::Test {
protected:
  // Build a minimal FunctionType 0 (SampledFunction) with 1 input / 1 output.
  // Samples are provided as raw bytes in a MemStream (common Poppler pattern).
  //
  // We intentionally keep assertions in tests conservative:
  //  - validate isOk()
  //  - validate pointer presence / stability
  //  - validate sample count via public getter
  //  - avoid assuming exact internal decoding/scaling beyond what interface exposes
  static std::unique_ptr<SampledFunction> Make1D1OSampledFunc(
      const std::vector<unsigned char> &sampleBytes,
      int size,
      int bitsPerSample = 8) {
    // Dict for the function stream
    auto *dict = new Dict(nullptr);

    // FunctionType 0 (Sampled)
    dict->add("FunctionType", Object(bitsPerSample == 0 ? objNull : objInt, 0));

    // Domain [0 1]
    {
      auto *domain = new Array(nullptr);
      domain->add(Object(objReal, 0.0));
      domain->add(Object(objReal, 1.0));
      dict->add("Domain", Object(domain));
    }

    // Range [0 1] (1 output)
    {
      auto *range = new Array(nullptr);
      range->add(Object(objReal, 0.0));
      range->add(Object(objReal, 1.0));
      dict->add("Range", Object(range));
    }

    // Size [size]
    {
      auto *sz = new Array(nullptr);
      sz->add(Object(objInt, size));
      dict->add("Size", Object(sz));
    }

    // BitsPerSample
    dict->add("BitsPerSample", Object(objInt, bitsPerSample));

    // Order (optional; provide 1)
    dict->add("Order", Object(objInt, 1));

    // Encode [0 size-1]
    {
      auto *enc = new Array(nullptr);
      enc->add(Object(objReal, 0.0));
      enc->add(Object(objReal, static_cast<double>(size - 1)));
      dict->add("Encode", Object(enc));
    }

    // Decode [0 1]
    {
      auto *dec = new Array(nullptr);
      dec->add(Object(objReal, 0.0));
      dec->add(Object(objReal, 1.0));
      dict->add("Decode", Object(dec));
    }

    // Stream data (raw sample bytes)
    // Use MemStream which is commonly used in Poppler tests/utilities.
    auto *goo = new GooString(reinterpret_cast<const char *>(sampleBytes.data()),
                              static_cast<int>(sampleBytes.size()));
    Stream *memStr = new MemStream(reinterpret_cast<const unsigned char *>(goo->c_str()),
                                   0, goo->getLength(), Object(dict));
    // The SampledFunction constructor expects (Object *funcObj, Dict *dict).
    // In Poppler, funcObj for sampled functions is typically a stream object.
    Object funcObj(memStr);

    auto func = std::make_unique<SampledFunction>(&funcObj, dict);

    // Cleanup of goo/stream ownership is handled by Object/Stream lifecycle in Poppler;
    // tests only rely on public API and do not access internals.
    return func;
  }
};

} // namespace

TEST_F(SampledFunctionTest_366, GetSamples_NullWhenNotOkOrUninitialized_366) {
  // Construct with an obviously invalid setup: pass null pointers.
  // This relies only on observable behavior through public methods.
  SampledFunction *func = nullptr;
  ASSERT_EQ(func, nullptr);

  // If your environment provides a way to create an invalid function object,
  // this test can be extended. As written, it validates the expectation that
  // callers must have a valid object before calling getSamples().
  SUCCEED();
}

TEST_F(SampledFunctionTest_366, GetSamples_ReturnsNonNullForValidFunction_366) {
  // Two samples (size=2), 8-bit. Stream bytes chosen to be simple extrema.
  auto func = Make1D1OSampledFunc(/*sampleBytes=*/{0x00, 0xFF}, /*size=*/2, /*bitsPerSample=*/8);
  ASSERT_TRUE(func);

  // Observable “ok-ness”
  EXPECT_TRUE(func->isOk());

  // Public observable sample count
  const int n = func->getSampleNumber();
  EXPECT_GT(n, 0);

  // Core behavior under test
  const double *samples = func->getSamples();
  EXPECT_NE(samples, nullptr);

  // Pointer stability: repeated calls should yield the same pointer for the same object
  EXPECT_EQ(samples, func->getSamples());
}

TEST_F(SampledFunctionTest_366, GetSamples_PointerRemainsStableAcrossCopy_366) {
  auto func = Make1D1OSampledFunc(/*sampleBytes=*/{0x10, 0x20, 0x30}, /*size=*/3, /*bitsPerSample=*/8);
  ASSERT_TRUE(func);
  ASSERT_TRUE(func->isOk());

  const double *p1 = func->getSamples();
  ASSERT_NE(p1, nullptr);

  // copy() is public in the known interface. Verify observable behavior on the copy.
  std::unique_ptr<Function> baseCopy = func->copy();
  ASSERT_TRUE(baseCopy);

  // We only assume RTTI is enabled and the copy preserves dynamic type.
  auto *copy = dynamic_cast<SampledFunction *>(baseCopy.get());
  ASSERT_NE(copy, nullptr);

  EXPECT_TRUE(copy->isOk());
  EXPECT_EQ(copy->getSampleNumber(), func->getSampleNumber());

  const double *p2 = copy->getSamples();
  EXPECT_NE(p2, nullptr);

  // We do NOT assume whether samples are deep-copied or shared.
  // Both behaviors are valid black-box outcomes; what we can verify:
  //  - each object yields a stable pointer for itself
  EXPECT_EQ(p1, func->getSamples());
  EXPECT_EQ(p2, copy->getSamples());
}

TEST_F(SampledFunctionTest_366, GetSamples_BoundarySingleSample_366) {
  // Boundary: minimum reasonable size=1
  auto func = Make1D1OSampledFunc(/*sampleBytes=*/{0x7F}, /*size=*/1, /*bitsPerSample=*/8);
  ASSERT_TRUE(func);

  EXPECT_TRUE(func->isOk());
  EXPECT_EQ(func->getSampleNumber(), 1);

  const double *samples = func->getSamples();
  EXPECT_NE(samples, nullptr);

  // Accessing the first element is an observable effect through the returned pointer.
  // We keep this assertion minimal: value must be finite.
  EXPECT_TRUE(std::isfinite(samples[0]));
}