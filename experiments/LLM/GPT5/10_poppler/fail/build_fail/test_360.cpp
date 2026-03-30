// TEST_ID: 360
// File: sampled_function_unittest_360.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#if __has_include("poppler/Function.h")
#include "poppler/Function.h"
#else
#include "Function.h"
#endif

// Try to include Object/Dict types if they exist as separate headers in this build.
#if __has_include("poppler/Object.h")
#include "poppler/Object.h"
#elif __has_include("Object.h")
#include "Object.h"
#endif

#if __has_include("poppler/Dict.h")
#include "poppler/Dict.h"
#elif __has_include("Dict.h")
#include "Dict.h"
#endif

namespace {

// NOTE:
// - These tests treat SampledFunction as a black box.
// - They focus on observable behavior and "should not crash" invariants.
// - Where construction details are unknown, tests avoid assuming ok==true/false.

class SampledFunctionTest_360 : public ::testing::Test {
protected:
  static SampledFunction MakeWithNullInputs() {
    // The interface shows: SampledFunction(Object *funcObj, Dict *dict)
    // We intentionally pass nullptrs to exercise boundary/error handling.
    return SampledFunction(/*funcObj=*/nullptr, /*dict=*/nullptr);
  }
};

TEST_F(SampledFunctionTest_360, IsOk_IsDeterministicAcrossCalls_360) {
  auto f = MakeWithNullInputs();

  const bool ok1 = f.isOk();
  const bool ok2 = f.isOk();
  const bool ok3 = f.isOk();

  EXPECT_EQ(ok1, ok2);
  EXPECT_EQ(ok2, ok3);
}

TEST_F(SampledFunctionTest_360, Copy_PreservesIsOkIfCopySucceeds_360) {
  auto f = MakeWithNullInputs();
  const bool origOk = f.isOk();

  std::unique_ptr<Function> c;
  ASSERT_NO_THROW(c = f.copy());

  // copy() is part of the public interface; if it returns a valid object,
  // it should be callable and have a stable isOk().
  if (c) {
    EXPECT_EQ(c->isOk(), origOk);
    EXPECT_EQ(c->isOk(), c->isOk());
  }
}

TEST_F(SampledFunctionTest_360, HasDifferentResultSet_WithSelfIsFalse_360) {
  auto f = MakeWithNullInputs();

  // Boundary / sanity: a function compared with itself should not be "different".
  // This checks an observable invariant without inferring internal logic.
  EXPECT_FALSE(f.hasDifferentResultSet(&f));
}

TEST_F(SampledFunctionTest_360, HasDifferentResultSet_WithCopyIsFalseIfBothOk_360) {
  auto f = MakeWithNullInputs();
  std::unique_ptr<Function> c;
  ASSERT_NO_THROW(c = f.copy());

  if (!c) {
    GTEST_SKIP() << "copy() returned nullptr; skipping comparison test.";
  }

  // Only check when both objects report ok; otherwise behavior may be intentionally undefined.
  if (f.isOk() && c->isOk()) {
    EXPECT_FALSE(f.hasDifferentResultSet(c.get()));
    EXPECT_FALSE(c->hasDifferentResultSet(&f));
  }
}

TEST_F(SampledFunctionTest_360, Getters_AreStableAcrossCalls_360) {
  auto f = MakeWithNullInputs();

  // We do not assume any specific values. We only assert that repeated calls
  // return the same results (stability) for the same object state.
  const int n1 = f.getSampleNumber();
  const int n2 = f.getSampleNumber();
  EXPECT_EQ(n1, n2);

  const double* s1 = f.getSamples();
  const double* s2 = f.getSamples();
  EXPECT_EQ(s1, s2);
}

TEST_F(SampledFunctionTest_360, GetterIndexBoundaries_DoNotCrash_360) {
  auto f = MakeWithNullInputs();

  // Boundary indices around the maximums mentioned in the header excerpt.
  // We do not assert values (black box); we just assert calls are safe.
  EXPECT_NO_THROW((void)f.getSampleSize(0));
  EXPECT_NO_THROW((void)f.getSampleSize(15));
  EXPECT_NO_THROW((void)f.getSampleSize(31));

  EXPECT_NO_THROW((void)f.getEncodeMin(0));
  EXPECT_NO_THROW((void)f.getEncodeMax(0));
  EXPECT_NO_THROW((void)f.getDecodeMin(0));
  EXPECT_NO_THROW((void)f.getDecodeMax(0));
}

TEST_F(SampledFunctionTest_360, Transform_DoesNotCrashOnZeroedBuffers_360) {
  auto f = MakeWithNullInputs();

  // Use conservatively sized buffers. The header excerpt indicates max inputs/outputs up to 32.
  double in[32] = {};
  double out[32] = {};

  // Observable behavior requirement here is simply: callable without crashing.
  EXPECT_NO_THROW(f.transform(in, out));

  // Also sanity: calling again should still be safe/deterministic in terms of not crashing.
  EXPECT_NO_THROW(f.transform(in, out));
}

} // namespace