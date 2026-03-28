// TEST_ID: 486
// File: gfx_device_n_colorspace_test_486.cpp

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Poppler headers
#include "GfxState.h"
#include "Function.h"

namespace {

class GfxDeviceNColorSpaceTest_486 : public ::testing::Test {};

TEST_F(GfxDeviceNColorSpaceTest_486, GetTintTransformFunc_ReturnsNullWhenFuncNotProvided_486) {
  std::vector<std::string> names;
  names.emplace_back("Cyan");

  std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS; // empty is fine

  GfxDeviceNColorSpace cs(/*nCompsA=*/1,
                          std::move(names),
                          /*alt=*/std::unique_ptr<GfxColorSpace>{},
                          /*func=*/std::unique_ptr<Function>{},
                          std::move(sepsCS));

  EXPECT_EQ(cs.getTintTransformFunc(), nullptr);
}

TEST_F(GfxDeviceNColorSpaceTest_486, GetTintTransformFunc_ReturnsSamePointerAsProvided_486) {
  std::vector<std::string> names;
  names.emplace_back("Cyan");

  std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS; // empty is fine

  auto func = std::make_unique<IdentityFunction>();
  const Function *raw = func.get();

  GfxDeviceNColorSpace cs(/*nCompsA=*/1,
                          std::move(names),
                          /*alt=*/std::unique_ptr<GfxColorSpace>{},
                          /*func=*/std::move(func),
                          std::move(sepsCS));

  EXPECT_EQ(cs.getTintTransformFunc(), raw);
  EXPECT_EQ(cs.getTintTransformFunc(), raw) << "Pointer should be stable across repeated calls";
}

TEST_F(GfxDeviceNColorSpaceTest_486, GetTintTransformFunc_CanBeCalledOnConstObject_486) {
  std::vector<std::string> names;
  names.emplace_back("Cyan");

  std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS; // empty is fine
  auto func = std::make_unique<IdentityFunction>();
  const Function *raw = func.get();

  GfxDeviceNColorSpace cs(/*nCompsA=*/1,
                          std::move(names),
                          /*alt=*/std::unique_ptr<GfxColorSpace>{},
                          /*func=*/std::move(func),
                          std::move(sepsCS));

  const GfxDeviceNColorSpace &ccs = cs;
  EXPECT_EQ(ccs.getTintTransformFunc(), raw);
}

TEST_F(GfxDeviceNColorSpaceTest_486, GetTintTransformFunc_HasExpectedReturnType_486) {
  // Pure interface-level contract check.
  static_assert(std::is_same_v<decltype(std::declval<const GfxDeviceNColorSpace &>().getTintTransformFunc()),
                               const Function *>,
                "getTintTransformFunc() must return const Function*");
}

TEST_F(GfxDeviceNColorSpaceTest_486, GetTintTransformFunc_Boundary_ZeroComponentsAndEmptyNames_486) {
  std::vector<std::string> names; // empty
  std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS; // empty

  GfxDeviceNColorSpace cs(/*nCompsA=*/0,
                          std::move(names),
                          /*alt=*/std::unique_ptr<GfxColorSpace>{},
                          /*func=*/std::unique_ptr<Function>{},
                          std::move(sepsCS));

  // Observable behavior: should simply report no function.
  EXPECT_EQ(cs.getTintTransformFunc(), nullptr);
}

} // namespace