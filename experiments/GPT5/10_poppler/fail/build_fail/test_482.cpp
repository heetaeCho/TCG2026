// TEST_ID: 482
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "GfxState.h"

namespace {

std::unique_ptr<GfxDeviceNColorSpace> MakeDeviceN(int nComps,
                                                  std::vector<std::string> names = {},
                                                  std::unique_ptr<GfxColorSpace> alt = nullptr,
                                                  std::unique_ptr<Function> func = nullptr,
                                                  std::vector<std::unique_ptr<GfxSeparationColorSpace>> seps = {}) {
  if (names.empty()) {
    names.reserve(static_cast<size_t>(nComps > 0 ? nComps : 0));
    for (int i = 0; i < nComps; ++i) {
      names.emplace_back("C" + std::to_string(i));
    }
  }
  return std::make_unique<GfxDeviceNColorSpace>(nComps, std::move(names), std::move(alt), std::move(func),
                                               std::move(seps));
}

class GfxDeviceNColorSpaceTest_482 : public ::testing::Test {};

} // namespace

TEST_F(GfxDeviceNColorSpaceTest_482, GetNCompsReturnsConstructorValue_482) {
  auto cs = MakeDeviceN(4);
  EXPECT_EQ(cs->getNComps(), 4);
}

TEST_F(GfxDeviceNColorSpaceTest_482, GetNCompsReturnsZeroWhenConstructedWithZero_482) {
  auto cs = MakeDeviceN(0, /*names=*/{}, /*alt=*/nullptr, /*func=*/nullptr, /*seps=*/{});
  EXPECT_EQ(cs->getNComps(), 0);
}

TEST_F(GfxDeviceNColorSpaceTest_482, GetNCompsReturnsLargeValue_482) {
  const int kLarge = 1024;
  auto cs = MakeDeviceN(kLarge);
  EXPECT_EQ(cs->getNComps(), kLarge);
}

TEST_F(GfxDeviceNColorSpaceTest_482, GetNCompsIsPerInstanceNotGlobal_482) {
  auto cs1 = MakeDeviceN(1);
  auto cs2 = MakeDeviceN(6);

  EXPECT_EQ(cs1->getNComps(), 1);
  EXPECT_EQ(cs2->getNComps(), 6);
}