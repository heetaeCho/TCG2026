// TEST_ID: 365
#include <gtest/gtest.h>

#include <cmath>
#include <cstddef>

#if __has_include("poppler/Function.h")
#include "poppler/Function.h"
#elif __has_include("Function.h")
#include "Function.h"
#else
#error "Cannot find poppler Function.h (expected poppler/Function.h or Function.h)"
#endif

namespace {

// Small helper to avoid UB: only call index-based getters on objects that report isOk()==true.
inline bool IsOkSafe(const SampledFunction& f) {
  // isOk() exists per provided interface (Known or Inferred Dependencies).
  return f.isOk();
}

}  // namespace

class SampledFunctionTest_365 : public ::testing::Test {};

TEST_F(SampledFunctionTest_365, NullInputsReportsNotOk_365) {
  // Constructor exists per provided interface: SampledFunction(Object* funcObj, Dict* dict)
  // We treat implementation as a black box; we only verify observable behavior.
  SampledFunction func(nullptr, nullptr);

  // If the implementation chooses to accept nullptrs, this may be true; but most robustly,
  // the constructor should report not OK for invalid inputs. If it *is* OK, subsequent tests
  // will exercise basic getter stability.
  EXPECT_FALSE(func.isOk());
}

TEST_F(SampledFunctionTest_365, GetDecodeMaxCallableWhenOk_365) {
  // Use the same "invalid" construction path; if implementation unexpectedly reports OK,
  // ensure getDecodeMax is callable and returns a finite double for a conservative index.
  SampledFunction func(nullptr, nullptr);

  if (!IsOkSafe(func)) {
    GTEST_SKIP() << "SampledFunction not OK with nullptr inputs; cannot safely call getDecodeMax.";
  }

  double v = 0.0;
  EXPECT_NO_THROW(v = func.getDecodeMax(0));
  EXPECT_TRUE(std::isfinite(v));
}

TEST_F(SampledFunctionTest_365, GetDecodeMaxIsStableAcrossRepeatedCalls_365) {
  SampledFunction func(nullptr, nullptr);

  if (!IsOkSafe(func)) {
    GTEST_SKIP() << "SampledFunction not OK with nullptr inputs; cannot safely call getDecodeMax.";
  }

  double a = 0.0, b = 0.0;
  ASSERT_NO_THROW(a = func.getDecodeMax(0));
  ASSERT_NO_THROW(b = func.getDecodeMax(0));
  EXPECT_DOUBLE_EQ(a, b);
}

TEST_F(SampledFunctionTest_365, CopyPreservesGetDecodeMaxObservableResult_365) {
  SampledFunction func(nullptr, nullptr);

  if (!IsOkSafe(func)) {
    GTEST_SKIP() << "SampledFunction not OK with nullptr inputs; cannot safely compare copy().";
  }

  const double orig = func.getDecodeMax(0);

  // copy() exists per provided interface and returns std::unique_ptr<Function>.
  std::unique_ptr<Function> copiedBase;
  ASSERT_NO_THROW(copiedBase = func.copy());
  ASSERT_NE(copiedBase, nullptr);

  // Verify the returned Function is a SampledFunction and preserves observable behavior.
  auto* copied = dynamic_cast<SampledFunction*>(copiedBase.get());
  ASSERT_NE(copied, nullptr);

  EXPECT_TRUE(copied->isOk());
  EXPECT_DOUBLE_EQ(copied->getDecodeMax(0), orig);
}

TEST_F(SampledFunctionTest_365, CopyDoesNotHaveDifferentResultSetFromOriginal_365) {
  SampledFunction func(nullptr, nullptr);

  if (!IsOkSafe(func)) {
    GTEST_SKIP() << "SampledFunction not OK with nullptr inputs; cannot safely compare result sets.";
  }

  std::unique_ptr<Function> copiedBase = func.copy();
  ASSERT_NE(copiedBase, nullptr);

  // hasDifferentResultSet(const Function*) exists per provided interface.
  EXPECT_FALSE(func.hasDifferentResultSet(copiedBase.get()));
  EXPECT_FALSE(copiedBase->hasDifferentResultSet(&func));
}