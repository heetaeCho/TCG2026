// GfxIndexedColorSpace_useGetRGBLine_466_test.cc
// File: ./TestProjects/poppler/poppler/GfxState.h

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

// Try to construct GfxIndexedColorSpace using whatever constructor is available in the
// real codebase, without assuming internal behavior.
template <typename... Args>
constexpr bool IsConstructibleV = std::is_constructible<GfxIndexedColorSpace, Args...>::value;

static GfxIndexedColorSpace MakeIndexedCS(int indexHigh)
{
  // Prefer ctor taking std::unique_ptr<GfxColorSpace>&&, if available.
  if constexpr (IsConstructibleV<std::unique_ptr<GfxColorSpace>&&, int>) {
    std::unique_ptr<GfxColorSpace> nullBase;
    return GfxIndexedColorSpace(std::move(nullBase), indexHigh);
  }
  // Some variants use raw pointers.
  else if constexpr (IsConstructibleV<GfxColorSpace*, int>) {
    return GfxIndexedColorSpace(static_cast<GfxColorSpace*>(nullptr), indexHigh);
  }
  // Some generated headers may expose an integral ctor (as hinted by the prompt).
  else if constexpr (IsConstructibleV<int&&, int>) {
    int baseA = 0;
    return GfxIndexedColorSpace(std::move(baseA), indexHigh);
  } else if constexpr (IsConstructibleV<int, int>) {
    return GfxIndexedColorSpace(0, indexHigh);
  } else {
    // If none of the above are available, this test cannot portably construct the type.
    // Fail at compile-time with a clear message.
    static_assert(IsConstructibleV<std::unique_ptr<GfxColorSpace>&&, int> ||
                      IsConstructibleV<GfxColorSpace*, int> || IsConstructibleV<int&&, int> ||
                      IsConstructibleV<int, int>,
                  "No known GfxIndexedColorSpace constructor is available for this test.");
    // Unreachable, but required to satisfy all control paths.
    return *static_cast<GfxIndexedColorSpace*>(nullptr);
  }
}

class GfxIndexedColorSpaceTest_466 : public ::testing::Test {};

} // namespace

TEST_F(GfxIndexedColorSpaceTest_466, UseGetRGBLineReturnsTrue_DefaultishIndexHigh_466)
{
  const auto cs = MakeIndexedCS(/*indexHigh=*/0);
  EXPECT_TRUE(cs.useGetRGBLine());
}

TEST_F(GfxIndexedColorSpaceTest_466, UseGetRGBLineReturnsTrue_TypicalMaxIndexHigh_466)
{
  const auto cs = MakeIndexedCS(/*indexHigh=*/255);
  EXPECT_TRUE(cs.useGetRGBLine());
}

TEST_F(GfxIndexedColorSpaceTest_466, UseGetRGBLineCallableOnConstReference_466)
{
  const auto cs = MakeIndexedCS(/*indexHigh=*/1);
  const GfxIndexedColorSpace &ref = cs;
  EXPECT_TRUE(ref.useGetRGBLine());
}

TEST_F(GfxIndexedColorSpaceTest_466, UseGetRGBLineReturnsTrue_ForNegativeIndexHighIfConstructible_466)
{
  // Boundary-ish case: only run if the chosen ctor path accepts negative values at runtime.
  // (Construction itself is handled by MakeIndexedCS; if it throws/aborts in a particular
  // build, that would be a behavior change outside this test's assumptions.)
  const auto cs = MakeIndexedCS(/*indexHigh=*/-1);
  EXPECT_TRUE(cs.useGetRGBLine());
}

TEST_F(GfxIndexedColorSpaceTest_466, UseGetRGBLineVirtualDispatchThroughBaseIfApplicable_466)
{
  // Only meaningful if GfxIndexedColorSpace is actually derived from GfxColorSpace in this build.
  if constexpr (std::is_base_of<GfxColorSpace, GfxIndexedColorSpace>::value) {
    auto cs = MakeIndexedCS(/*indexHigh=*/10);
    const GfxColorSpace *basePtr = &cs;
    EXPECT_TRUE(basePtr->useGetRGBLine());
  } else {
    GTEST_SKIP() << "GfxIndexedColorSpace is not a GfxColorSpace in this build.";
  }
}