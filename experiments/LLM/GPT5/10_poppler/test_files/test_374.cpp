// SPDX-License-Identifier: GPL-2.0-or-later
// File: stitching_function_copy_tests.cpp
//
// Unit tests for poppler::StitchingFunction::copy()
// TEST_ID = 374
//
// Notes:
// - Treats implementation as a black box.
// - Focuses only on observable behavior via public interface.
// - Does not access private state or infer internal logic.

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>
#include <utility>

#include "poppler/Function.h"

namespace {

class StitchingFunctionTest_374 : public ::testing::Test {
protected:
  // Best-effort constructor helper:
  // The real constructor takes (Dict*, RefRecursionChecker&). We attempt to
  // construct using a null Dict* (boundary condition) and a default-constructed
  // RefRecursionChecker (if available in this build).
  //
  // If either of these assumptions does not hold in your exact poppler build
  // (e.g., RefRecursionChecker has no default ctor), adjust this helper to use
  // whatever minimal/valid construction utilities exist in your codebase.
  static std::unique_ptr<StitchingFunction> MakeMinimal()
  {
    RefRecursionChecker usedParents;
    return std::make_unique<StitchingFunction>(static_cast<Dict *>(nullptr), usedParents);
  }
};

TEST_F(StitchingFunctionTest_374, CopyReturnTypeIsUniquePtrFunction_374)
{
  // Compile-time verification of the signature's observable contract.
  using Ret = decltype(std::declval<const StitchingFunction &>().copy());
  static_assert(std::is_same_v<Ret, std::unique_ptr<Function>>,
                "StitchingFunction::copy() must return std::unique_ptr<Function>");
  SUCCEED();
}

TEST_F(StitchingFunctionTest_374, CopyReturnsNonNullUniquePtr_374)
{
  const auto original = MakeMinimal();
  ASSERT_NE(original, nullptr);

  std::unique_ptr<Function> cpy;
  ASSERT_NO_THROW(cpy = original->copy());
  EXPECT_NE(cpy, nullptr);
}

TEST_F(StitchingFunctionTest_374, CopyReturnsDistinctObject_374)
{
  const auto original = MakeMinimal();
  ASSERT_NE(original, nullptr);

  auto cpy = original->copy();
  ASSERT_NE(cpy, nullptr);

  // Observable: returned object must not be the same object (distinct address).
  EXPECT_NE(cpy.get(), static_cast<Function *>(original.get()));
}

TEST_F(StitchingFunctionTest_374, CopyPreservesDynamicTypeAsStitchingFunction_374)
{
  const auto original = MakeMinimal();
  ASSERT_NE(original, nullptr);

  auto cpy = original->copy();
  ASSERT_NE(cpy, nullptr);

  // Observable via RTTI: the copy should be a StitchingFunction instance.
  // (If RTTI is disabled in your build, this test can be adjusted/removed.)
  EXPECT_NE(dynamic_cast<StitchingFunction *>(cpy.get()), nullptr);
}

TEST_F(StitchingFunctionTest_374, CopyPreservesReportedTypeEnum_374)
{
  const auto original = MakeMinimal();
  ASSERT_NE(original, nullptr);

  auto cpy = original->copy();
  ASSERT_NE(cpy, nullptr);

  // Observable through public API.
  EXPECT_EQ(cpy->getType(), original->getType());
}

TEST_F(StitchingFunctionTest_374, CopyPreservesIsOkState_374)
{
  const auto original = MakeMinimal();
  ASSERT_NE(original, nullptr);

  auto cpy = original->copy();
  ASSERT_NE(cpy, nullptr);

  // Observable through public API; no inference on what "ok" means.
  EXPECT_EQ(cpy->isOk(), original->isOk());
}

TEST_F(StitchingFunctionTest_374, MultipleCopiesAreIndependentObjects_374)
{
  const auto original = MakeMinimal();
  ASSERT_NE(original, nullptr);

  auto c1 = original->copy();
  auto c2 = original->copy();

  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);

  EXPECT_NE(c1.get(), c2.get());
  EXPECT_NE(c1.get(), static_cast<Function *>(original.get()));
  EXPECT_NE(c2.get(), static_cast<Function *>(original.get()));

  // And they should agree on observable classification.
  EXPECT_EQ(c1->getType(), original->getType());
  EXPECT_EQ(c2->getType(), original->getType());
}

} // namespace