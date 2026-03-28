// TEST_ID: 536
// File: test_GfxImageColorMap_useRGBLine_536.cpp

#include <gtest/gtest.h>

#include <memory>
#include <utility>

#include "poppler/GfxState.h"

// A tiny test double that lets us (a) control the return value of
// GfxColorSpace::useGetRGBLine(), and (b) observe how many times it was queried.
class CountingColorSpace : public GfxColorSpace {
public:
  explicit CountingColorSpace(bool use) : use_(use) {}
  ~CountingColorSpace() override = default;

  bool useGetRGBLine() const override
  {
    ++calls_;
    return use_;
  }

  void setUse(bool v) { use_ = v; }
  int calls() const { return calls_; }

private:
  bool use_;
  mutable int calls_ = 0;
};

class GfxImageColorMapTest_536 : public ::testing::Test {
protected:
  static std::unique_ptr<GfxImageColorMap> MakeMap(int bits, bool useGetRGBLine, CountingColorSpace **outCs)
  {
    auto cs = std::make_unique<CountingColorSpace>(useGetRGBLine);
    *outCs = cs.get();

    // decode can be nullptr (constructor takes Object*; behavior should be handled by implementation).
    return std::make_unique<GfxImageColorMap>(bits, /*decode=*/nullptr, std::move(cs));
  }
};

TEST_F(GfxImageColorMapTest_536, UseRGBLineReturnsTrueWhenColorSpaceSupportsRGBLine_536)
{
  CountingColorSpace *cs = nullptr;
  auto map = MakeMap(/*bits=*/8, /*useGetRGBLine=*/true, &cs);
  ASSERT_NE(map, nullptr);
  ASSERT_NE(cs, nullptr);

  EXPECT_TRUE(map->useRGBLine());
  EXPECT_EQ(cs->calls(), 1);
}

TEST_F(GfxImageColorMapTest_536, UseRGBLineReturnsFalseWhenColorSpaceDoesNotSupportRGBLine_536)
{
  CountingColorSpace *cs = nullptr;
  auto map = MakeMap(/*bits=*/8, /*useGetRGBLine=*/false, &cs);
  ASSERT_NE(map, nullptr);
  ASSERT_NE(cs, nullptr);

  EXPECT_FALSE(map->useRGBLine());
  EXPECT_EQ(cs->calls(), 1);
}

TEST_F(GfxImageColorMapTest_536, UseRGBLineIsCallableOnConstAndDelegatesEachTime_536)
{
  CountingColorSpace *cs = nullptr;
  auto map = MakeMap(/*bits=*/8, /*useGetRGBLine=*/true, &cs);
  ASSERT_NE(map, nullptr);
  ASSERT_NE(cs, nullptr);

  const GfxImageColorMap &cmap = *map;
  EXPECT_TRUE(cmap.useRGBLine());
  EXPECT_TRUE(cmap.useRGBLine());
  EXPECT_TRUE(cmap.useRGBLine());

  EXPECT_EQ(cs->calls(), 3);
}

TEST_F(GfxImageColorMapTest_536, UseRGBLineWorksAtBoundaryBitDepths_536)
{
  // Lower-ish boundary
  {
    CountingColorSpace *cs = nullptr;
    auto map = MakeMap(/*bits=*/1, /*useGetRGBLine=*/true, &cs);
    ASSERT_NE(map, nullptr);
    ASSERT_NE(cs, nullptr);

    EXPECT_TRUE(map->useRGBLine());
    EXPECT_EQ(cs->calls(), 1);
  }

  // Upper-ish boundary commonly used for images (e.g., 16bpc)
  {
    CountingColorSpace *cs = nullptr;
    auto map = MakeMap(/*bits=*/16, /*useGetRGBLine=*/false, &cs);
    ASSERT_NE(map, nullptr);
    ASSERT_NE(cs, nullptr);

    EXPECT_FALSE(map->useRGBLine());
    EXPECT_EQ(cs->calls(), 1);
  }
}

TEST_F(GfxImageColorMapTest_536, CopyPreservesObservableUseRGBLineBehavior_536)
{
  CountingColorSpace *cs = nullptr;
  auto map = MakeMap(/*bits=*/8, /*useGetRGBLine=*/true, &cs);
  ASSERT_NE(map, nullptr);
  ASSERT_NE(cs, nullptr);

  // Baseline call on original.
  EXPECT_TRUE(map->useRGBLine());

  // copy() returns a new heap object (per interface); verify it is callable
  // and returns a consistent observable result.
  std::unique_ptr<GfxImageColorMap> copy(map->copy());
  ASSERT_NE(copy, nullptr);

  EXPECT_TRUE(copy->useRGBLine());
  // We do not assert call counts after copy(), since the implementation may
  // or may not share/copy the underlying color space; we only assert the
  // public observable return value is usable and consistent here.
}