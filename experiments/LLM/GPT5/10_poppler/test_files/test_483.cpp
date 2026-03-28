// GfxDeviceNColorSpace_isNonMarking_Test_483.cpp
// Unit tests for GfxDeviceNColorSpace::isNonMarking()
// The TEST_ID is 483

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "GfxState.h"

// These tests treat the implementation as a black box and only validate observable behavior
// through the public interface.

namespace {

// Factory that tries to construct GfxDeviceNColorSpace using the ctor that exposes `nonMarkingA`.
// If that ctor (or its PrivateTag) is not available in the current build, returns nullptr and
// the test should GTEST_SKIP().
template <typename T>
std::unique_ptr<GfxDeviceNColorSpace> makeDeviceNWithNonMarkingIfPossible(bool nonMarking) {
  // Common dummy args
  int nCompsA = 0;
  std::vector<std::string> namesA; // empty is fine for this black-box test
  std::unique_ptr<GfxColorSpace> alt; // nullptr
  std::unique_ptr<Function> func;     // nullptr
  std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCSA; // empty
  std::vector<int> mappingA; // empty
  unsigned int overprintMaskA = 0;

  // Prefer the most specific ctor listed in the prompt (with `nonMarkingA` and a tag).
  if constexpr (std::is_class_v<decltype(GfxDeviceNColorSpace::PrivateTag{})> &&
                std::is_constructible_v<GfxDeviceNColorSpace,
                                        int,
                                        const std::vector<std::string>&,
                                        std::unique_ptr<GfxColorSpace>&&,
                                        std::unique_ptr<Function>,
                                        std::vector<std::unique_ptr<GfxSeparationColorSpace>>&&,
                                        const std::vector<int>&,
                                        bool,
                                        unsigned int,
                                        decltype(GfxDeviceNColorSpace::PrivateTag{})>) {
    return std::make_unique<GfxDeviceNColorSpace>(
        nCompsA,
        namesA,
        std::move(alt),
        std::move(func),
        std::move(sepsCSA),
        mappingA,
        nonMarking,
        overprintMaskA,
        GfxDeviceNColorSpace::PrivateTag{});
  } else if constexpr (std::is_class_v<decltype(GfxDeviceNColorSpace::PrivateTag{})> &&
                       std::is_constructible_v<GfxDeviceNColorSpace,
                                               int,
                                               std::vector<std::string>&&,
                                               std::unique_ptr<GfxColorSpace>&&,
                                               std::unique_ptr<Function>,
                                               std::vector<std::unique_ptr<GfxSeparationColorSpace>>&&,
                                               const std::vector<int>&,
                                               bool,
                                               unsigned int,
                                               decltype(GfxDeviceNColorSpace::PrivateTag{})>) {
    // Alternate form: rvalue names, but still with nonMarking and tag.
    return std::make_unique<GfxDeviceNColorSpace>(
        nCompsA,
        std::move(namesA),
        std::move(alt),
        std::move(func),
        std::move(sepsCSA),
        mappingA,
        nonMarking,
        overprintMaskA,
        GfxDeviceNColorSpace::PrivateTag{});
  } else {
    // Cannot reliably build an instance with controllable nonMarking via the exposed interface.
    return nullptr;
  }
}

} // namespace

class GfxDeviceNColorSpaceTest_483 : public ::testing::Test {};

// Normal operation: isNonMarking reflects the constructor-provided setting.
TEST_F(GfxDeviceNColorSpaceTest_483, IsNonMarkingFalseWhenConstructedFalse_483) {
  auto cs = makeDeviceNWithNonMarkingIfPossible<GfxDeviceNColorSpace>(false);
  if (!cs) {
    GTEST_SKIP() << "No accessible GfxDeviceNColorSpace constructor with nonMarkingA in this build.";
  }
  EXPECT_FALSE(cs->isNonMarking());
}

TEST_F(GfxDeviceNColorSpaceTest_483, IsNonMarkingTrueWhenConstructedTrue_483) {
  auto cs = makeDeviceNWithNonMarkingIfPossible<GfxDeviceNColorSpace>(true);
  if (!cs) {
    GTEST_SKIP() << "No accessible GfxDeviceNColorSpace constructor with nonMarkingA in this build.";
  }
  EXPECT_TRUE(cs->isNonMarking());
}

// Boundary-ish: use a minimal/empty configuration (0 components, empty names/mapping/seps).
// Observable behavior remains correct.
TEST_F(GfxDeviceNColorSpaceTest_483, IsNonMarkingWorksWithEmptyInputs_483) {
  auto csFalse = makeDeviceNWithNonMarkingIfPossible<GfxDeviceNColorSpace>(false);
  auto csTrue = makeDeviceNWithNonMarkingIfPossible<GfxDeviceNColorSpace>(true);
  if (!csFalse || !csTrue) {
    GTEST_SKIP() << "No accessible GfxDeviceNColorSpace constructor with nonMarkingA in this build.";
  }
  EXPECT_FALSE(csFalse->isNonMarking());
  EXPECT_TRUE(csTrue->isNonMarking());
}

// Observable interaction: copy() returns a GfxColorSpace; the copied object should preserve
// the observable isNonMarking() behavior.
TEST_F(GfxDeviceNColorSpaceTest_483, CopyPreservesIsNonMarkingFalse_483) {
  auto cs = makeDeviceNWithNonMarkingIfPossible<GfxDeviceNColorSpace>(false);
  if (!cs) {
    GTEST_SKIP() << "No accessible GfxDeviceNColorSpace constructor with nonMarkingA in this build.";
  }

  std::unique_ptr<GfxColorSpace> copied = cs->copy();
  ASSERT_NE(copied, nullptr);

  auto *asDeviceN = dynamic_cast<GfxDeviceNColorSpace *>(copied.get());
  ASSERT_NE(asDeviceN, nullptr) << "copy() did not produce a GfxDeviceNColorSpace instance.";

  EXPECT_FALSE(asDeviceN->isNonMarking());
}

TEST_F(GfxDeviceNColorSpaceTest_483, CopyPreservesIsNonMarkingTrue_483) {
  auto cs = makeDeviceNWithNonMarkingIfPossible<GfxDeviceNColorSpace>(true);
  if (!cs) {
    GTEST_SKIP() << "No accessible GfxDeviceNColorSpace constructor with nonMarkingA in this build.";
  }

  std::unique_ptr<GfxColorSpace> copied = cs->copy();
  ASSERT_NE(copied, nullptr);

  auto *asDeviceN = dynamic_cast<GfxDeviceNColorSpace *>(copied.get());
  ASSERT_NE(asDeviceN, nullptr) << "copy() did not produce a GfxDeviceNColorSpace instance.";

  EXPECT_TRUE(asDeviceN->isNonMarking());
}