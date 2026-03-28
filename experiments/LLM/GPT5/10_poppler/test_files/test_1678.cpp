// MarkedContentOutputDev_test_1678.cpp
#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

#include "MarkedContentOutputDev.h"

// Some Poppler builds require Object for MarkedContentOutputDev ctor.
// Include defensively (if not present in this build, the include may fail,
// but in Poppler it is typically available).
#if __has_include("Object.h")
#include "Object.h"
#endif

namespace {

template <typename T>
std::unique_ptr<T> MakeMarkedContentDevOrSkip() {
  // Prefer default construction if available.
  if constexpr (std::is_default_constructible_v<T>) {
    return std::make_unique<T>();
  }
#if __has_include("Object.h")
  else if constexpr (std::is_constructible_v<T, int, const Object &>) {
    Object obj; // default/empty object; treat as black-box input
    return std::make_unique<T>(0, obj);
  }
#endif
  else {
    return nullptr;
  }
}

} // namespace

TEST(MarkedContentOutputDevTest_1678, NeedNonTextReturnsFalse_1678) {
  auto dev = MakeMarkedContentDevOrSkip<MarkedContentOutputDev>();
  if (!dev) {
    GTEST_SKIP() << "No usable constructor found for MarkedContentOutputDev in this build.";
  }

  EXPECT_FALSE(dev->needNonText());
}

TEST(MarkedContentOutputDevTest_1678, NeedNonTextIsStableAcrossMultipleCalls_1678) {
  auto dev = MakeMarkedContentDevOrSkip<MarkedContentOutputDev>();
  if (!dev) {
    GTEST_SKIP() << "No usable constructor found for MarkedContentOutputDev in this build.";
  }

  EXPECT_FALSE(dev->needNonText());
  EXPECT_FALSE(dev->needNonText());
  EXPECT_FALSE(dev->needNonText());
}

TEST(MarkedContentOutputDevTest_1678, NeedNonTextViaBaseDispatchReturnsFalse_1678) {
  auto dev = MakeMarkedContentDevOrSkip<MarkedContentOutputDev>();
  if (!dev) {
    GTEST_SKIP() << "No usable constructor found for MarkedContentOutputDev in this build.";
  }

  // If MarkedContentOutputDev derives from OutputDev in this build, verify virtual dispatch.
  // (This is a compile-time property; if the base isn't present/visible, skip safely.)
  if constexpr (std::is_base_of_v<OutputDev, MarkedContentOutputDev>) {
    OutputDev *base = dev.get();
    ASSERT_NE(base, nullptr);
    EXPECT_FALSE(base->needNonText());
  } else {
    GTEST_SKIP() << "OutputDev base type not available/visible for MarkedContentOutputDev in this build.";
  }
}