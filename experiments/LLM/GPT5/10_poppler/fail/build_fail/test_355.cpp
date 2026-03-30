// TEST_ID: 355
// File: IdentityFunction_test_355.cpp

#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <cstddef>
#include <limits>
#include <memory>
#include <type_traits>

#if __has_include("poppler/Function.h")
#include "poppler/Function.h"
#elif __has_include("Function.h")
#include "Function.h"
#else
#error "Cannot find poppler/Function.h (or Function.h). Check include paths."
#endif

namespace {

class IdentityFunctionTest_355 : public ::testing::Test {
protected:
  // Use a deterministic, non-NaN sentinel so untouched output slots can be compared.
  static constexpr double kSentinel = 1234567.89;

  static void FillInput(std::array<double, funcMaxInputs> &in)
  {
    // Mix of typical and boundary-ish values. Avoid NaN comparisons.
    in.fill(0.0);
    in[0] = 0.0;
    if (in.size() > 1) in[1] = 1.0;
    if (in.size() > 2) in[2] = -1.0;
    if (in.size() > 3) in[3] = 42.5;
    if (in.size() > 4) in[4] = -123.25;
    if (in.size() > 5) in[5] = std::numeric_limits<double>::min();   // smallest positive normal
    if (in.size() > 6) in[6] = std::numeric_limits<double>::denorm_min();
    if (in.size() > 7) in[7] = std::numeric_limits<double>::max();
    if (in.size() > 8) in[8] = -std::numeric_limits<double>::max();
  }

  static void FillOutput(std::array<double, funcMaxOutputs> &out)
  {
    out.fill(kSentinel);
  }

  static void ExpectArraysEqual(const std::array<double, funcMaxOutputs> &a,
                                const std::array<double, funcMaxOutputs> &b)
  {
    for (std::size_t i = 0; i < a.size(); ++i) {
      EXPECT_DOUBLE_EQ(a[i], b[i]) << "Mismatch at out[" << i << "]";
    }
  }
};

TEST_F(IdentityFunctionTest_355, CopyReturnsNonNullAndDistinctInstance_355)
{
  IdentityFunction f;
  std::unique_ptr<Function> c = f.copy();

  ASSERT_NE(c, nullptr);
  EXPECT_NE(c.get(), static_cast<Function *>(&f)); // must be a different object
}

TEST_F(IdentityFunctionTest_355, CopyPreservesObservableTraits_TypeAndOk_355)
{
  IdentityFunction f;
  const auto origType = f.getType();
  const bool origOk = f.isOk();

  std::unique_ptr<Function> c = f.copy();
  ASSERT_NE(c, nullptr);

  // Observable public traits should match between original and its copy.
  EXPECT_EQ(c->getType(), origType);
  EXPECT_EQ(c->isOk(), origOk);
}

TEST_F(IdentityFunctionTest_355, CopyHasExpectedDynamicType_355)
{
  IdentityFunction f;
  std::unique_ptr<Function> c = f.copy();
  ASSERT_NE(c, nullptr);

  // We only check RTTI-visible type (no reliance on internals).
  auto *asIdentity = dynamic_cast<IdentityFunction *>(c.get());
  EXPECT_NE(asIdentity, nullptr);
}

TEST_F(IdentityFunctionTest_355, CopyIsBehaviorallyEquivalentForTransform_NormalValues_355)
{
  IdentityFunction f;
  std::unique_ptr<Function> c = f.copy();
  ASSERT_NE(c, nullptr);

  std::array<double, funcMaxInputs> in{};
  FillInput(in);

  std::array<double, funcMaxOutputs> outOrig{};
  std::array<double, funcMaxOutputs> outCopy{};
  FillOutput(outOrig);
  FillOutput(outCopy);

  f.transform(in.data(), outOrig.data());
  c->transform(in.data(), outCopy.data());

  // We don’t assume what “identity” means; we only require the copy behaves
  // the same as the original for the same input.
  ExpectArraysEqual(outOrig, outCopy);
}

TEST_F(IdentityFunctionTest_355, CopyIsBehaviorallyEquivalentForTransform_BoundaryValues_355)
{
  IdentityFunction f;
  std::unique_ptr<Function> c = f.copy();
  ASSERT_NE(c, nullptr);

  std::array<double, funcMaxInputs> in{};
  in.fill(0.0);
  if (in.size() > 0) in[0] = std::numeric_limits<double>::max();
  if (in.size() > 1) in[1] = -std::numeric_limits<double>::max();
  if (in.size() > 2) in[2] = std::numeric_limits<double>::min();
  if (in.size() > 3) in[3] = std::numeric_limits<double>::denorm_min();
  if (in.size() > 4) in[4] = 1e300;
  if (in.size() > 5) in[5] = -1e300;

  std::array<double, funcMaxOutputs> outOrig{};
  std::array<double, funcMaxOutputs> outCopy{};
  FillOutput(outOrig);
  FillOutput(outCopy);

  f.transform(in.data(), outOrig.data());
  c->transform(in.data(), outCopy.data());

  ExpectArraysEqual(outOrig, outCopy);
}

TEST_F(IdentityFunctionTest_355, MultipleCopiesAreIndependentAndEquivalent_355)
{
  IdentityFunction f;

  std::unique_ptr<Function> c1 = f.copy();
  std::unique_ptr<Function> c2 = f.copy();
  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);

  EXPECT_NE(c1.get(), c2.get());
  EXPECT_NE(c1.get(), static_cast<Function *>(&f));
  EXPECT_NE(c2.get(), static_cast<Function *>(&f));

  std::array<double, funcMaxInputs> in{};
  FillInput(in);

  std::array<double, funcMaxOutputs> outF{};
  std::array<double, funcMaxOutputs> out1{};
  std::array<double, funcMaxOutputs> out2{};
  FillOutput(outF);
  FillOutput(out1);
  FillOutput(out2);

  f.transform(in.data(), outF.data());
  c1->transform(in.data(), out1.data());
  c2->transform(in.data(), out2.data());

  ExpectArraysEqual(outF, out1);
  ExpectArraysEqual(outF, out2);
}

} // namespace