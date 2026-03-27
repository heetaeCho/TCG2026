// TEST_ID 358
// File: sampledfunction_copy_test.cpp

#include <gtest/gtest.h>

#include "poppler/Function.h"

namespace {

class SampledFunctionTest_358 : public ::testing::Test {
protected:
  // We avoid assuming anything about how SampledFunction parses/validates inputs.
  // The implementation is treated as a black box; we only exercise observable behavior.
  static SampledFunction MakeFuncWithNullInputs()
  {
    // Constructor signature (from provided interface): SampledFunction(Object* funcObj, Dict* dict)
    // Passing nullptrs is a boundary-style construction attempt; tests only rely on whether
    // subsequent public calls behave without crashing and return sensible types/pointers.
    return SampledFunction(nullptr, nullptr);
  }
};

TEST_F(SampledFunctionTest_358, CopyReturnsNonNull_358)
{
  const SampledFunction func = MakeFuncWithNullInputs();

  std::unique_ptr<Function> copied = func.copy();

  ASSERT_NE(copied, nullptr);
}

TEST_F(SampledFunctionTest_358, CopyReturnsSampledFunctionDynamicType_358)
{
  const SampledFunction func = MakeFuncWithNullInputs();

  std::unique_ptr<Function> copied = func.copy();
  ASSERT_NE(copied, nullptr);

  // Verify returned object is actually a SampledFunction instance (observable via RTTI).
  auto *asSampled = dynamic_cast<SampledFunction *>(copied.get());
  EXPECT_NE(asSampled, nullptr);
}

TEST_F(SampledFunctionTest_358, CopyProducesDistinctObjectAddress_358)
{
  const SampledFunction func = MakeFuncWithNullInputs();

  std::unique_ptr<Function> copied = func.copy();
  ASSERT_NE(copied, nullptr);

  // Observable boundary: copy should be a different object instance than the original.
  EXPECT_NE(copied.get(), &func);
}

TEST_F(SampledFunctionTest_358, MultipleCopiesAreNonNullAndDistinct_358)
{
  const SampledFunction func = MakeFuncWithNullInputs();

  std::unique_ptr<Function> copy1 = func.copy();
  std::unique_ptr<Function> copy2 = func.copy();

  ASSERT_NE(copy1, nullptr);
  ASSERT_NE(copy2, nullptr);

  EXPECT_NE(copy1.get(), copy2.get());
  EXPECT_NE(copy1.get(), &func);
  EXPECT_NE(copy2.get(), &func);

  // Both should still be SampledFunction objects.
  EXPECT_NE(dynamic_cast<SampledFunction *>(copy1.get()), nullptr);
  EXPECT_NE(dynamic_cast<SampledFunction *>(copy2.get()), nullptr);
}

TEST_F(SampledFunctionTest_358, CopyIsCallableOnConstReferenceRepeatedly_358)
{
  const SampledFunction func = MakeFuncWithNullInputs();
  const SampledFunction &cref = func;

  // Repeated calls on const object: should consistently return valid unique_ptr objects.
  for (int i = 0; i < 5; ++i) {
    std::unique_ptr<Function> copied = cref.copy();
    ASSERT_NE(copied, nullptr) << "Iteration " << i;
    EXPECT_NE(dynamic_cast<SampledFunction *>(copied.get()), nullptr) << "Iteration " << i;
    EXPECT_NE(copied.get(), &func) << "Iteration " << i;
  }
}

} // namespace