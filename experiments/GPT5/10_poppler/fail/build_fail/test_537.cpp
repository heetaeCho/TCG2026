// TEST_ID: 537
// File: test_gfximagecolormap_usecmykline_537.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "poppler/GfxState.h"

using ::testing::Return;
using ::testing::StrictMock;

// We only mock an external collaborator (GfxColorSpace) that is passed in.
// We do NOT simulate or depend on any internal state of GfxImageColorMap.
class MockGfxColorSpace : public GfxColorSpace {
public:
  MockGfxColorSpace() = default;
  ~MockGfxColorSpace() override = default;

  MOCK_METHOD(bool, useGetCMYKLine, (), (const, override));
};

class GfxImageColorMapTest_537 : public ::testing::Test {
protected:
  static std::unique_ptr<GfxImageColorMap> MakeMapWithColorSpace(
      std::unique_ptr<GfxColorSpace> cs) {
    // Use a common, minimal configuration. We avoid assuming decode contents.
    // Passing nullptr for decode keeps the test focused on delegation behavior.
    return std::make_unique<GfxImageColorMap>(8, /*decode=*/nullptr, std::move(cs));
  }
};

TEST_F(GfxImageColorMapTest_537, UseCMYKLine_DelegatesToColorSpace_WhenTrue_537) {
  auto cs = std::make_unique<StrictMock<MockGfxColorSpace>>();
  auto *csPtr = cs.get();

  auto map = MakeMapWithColorSpace(std::move(cs));
  ASSERT_NE(map, nullptr);

  // Observable behavior: the return value should reflect the delegated call.
  EXPECT_CALL(*csPtr, useGetCMYKLine()).Times(1).WillOnce(Return(true));
  EXPECT_TRUE(map->useCMYKLine());
}

TEST_F(GfxImageColorMapTest_537, UseCMYKLine_DelegatesToColorSpace_WhenFalse_537) {
  auto cs = std::make_unique<StrictMock<MockGfxColorSpace>>();
  auto *csPtr = cs.get();

  auto map = MakeMapWithColorSpace(std::move(cs));
  ASSERT_NE(map, nullptr);

  EXPECT_CALL(*csPtr, useGetCMYKLine()).Times(1).WillOnce(Return(false));
  EXPECT_FALSE(map->useCMYKLine());
}

TEST_F(GfxImageColorMapTest_537, UseCMYKLine_IsConstCallable_AndStable_537) {
  auto cs = std::make_unique<StrictMock<MockGfxColorSpace>>();
  auto *csPtr = cs.get();

  auto map = MakeMapWithColorSpace(std::move(cs));
  ASSERT_NE(map, nullptr);

  const GfxImageColorMap &cmap = *map;

  // Calling multiple times should simply query the collaborator each time.
  EXPECT_CALL(*csPtr, useGetCMYKLine()).Times(2).WillRepeatedly(Return(true));

  EXPECT_TRUE(cmap.useCMYKLine());
  EXPECT_TRUE(cmap.useCMYKLine());
}