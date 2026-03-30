// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for: poppler/GfxState.h - GfxDeviceNColorSpace::getMode()
// TEST_ID: 481

#include <gtest/gtest.h>

#include "GfxState.h"

namespace {

static std::unique_ptr<GfxDeviceNColorSpace> makeDeviceNCS_Empty_481()
{
  // Construct with minimal/empty inputs; getMode() must always report csDeviceN.
  std::vector<std::string> names;
  std::unique_ptr<GfxColorSpace> alt;        // nullptr
  std::unique_ptr<Function> func;            // nullptr
  std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS;
  return std::make_unique<GfxDeviceNColorSpace>(0, std::move(names), std::move(alt), std::move(func), std::move(sepsCS));
}

static std::unique_ptr<GfxDeviceNColorSpace> makeDeviceNCS_OneComp_481()
{
  std::vector<std::string> names;
  names.emplace_back("Cyan");

  std::unique_ptr<GfxColorSpace> alt;        // nullptr
  std::unique_ptr<Function> func;            // nullptr
  std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS;

  return std::make_unique<GfxDeviceNColorSpace>(1, std::move(names), std::move(alt), std::move(func), std::move(sepsCS));
}

} // namespace

TEST(GfxDeviceNColorSpaceTest_481, GetMode_ReturnsCsDeviceN_MinimalCtor_481)
{
  auto cs = makeDeviceNCS_Empty_481();
  ASSERT_NE(cs, nullptr);
  EXPECT_EQ(cs->getMode(), csDeviceN);
}

TEST(GfxDeviceNColorSpaceTest_481, GetMode_ReturnsCsDeviceN_WithOneComponent_481)
{
  auto cs = makeDeviceNCS_OneComp_481();
  ASSERT_NE(cs, nullptr);
  EXPECT_EQ(cs->getMode(), csDeviceN);
}

TEST(GfxDeviceNColorSpaceTest_481, GetMode_ThroughBasePointer_ReturnsCsDeviceN_481)
{
  auto derived = makeDeviceNCS_Empty_481();
  ASSERT_NE(derived, nullptr);

  std::unique_ptr<GfxColorSpace> base = std::move(derived);
  ASSERT_NE(base, nullptr);

  EXPECT_EQ(base->getMode(), csDeviceN);
}

TEST(GfxDeviceNColorSpaceTest_481, GetMode_IsConstCallable_481)
{
  const auto cs = makeDeviceNCS_Empty_481();
  ASSERT_NE(cs, nullptr);

  const GfxDeviceNColorSpace &ref = *cs;
  EXPECT_EQ(ref.getMode(), csDeviceN);
}