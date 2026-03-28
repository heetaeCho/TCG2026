// -*- mode: c++; -*-
// Test file for GfxSeparationColorSpace::isNonMarking
// File: GfxSeparationColorSpace_isNonMarking_477_test.cc

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

#include "poppler/GfxState.h"
#include "poppler/goo/GooString.h"

namespace {

// ---- Detection helpers (C++17) ----
template <typename...>
using void_t = void;

template <typename T, typename = void>
struct has_private_tag : std::false_type {};
template <typename T>
struct has_private_tag<T, void_t<typename T::PrivateTag>> : std::true_type {};

template <typename T, typename = void>
struct private_tag_type {
  // no type
};
template <typename T>
struct private_tag_type<T, void_t<typename T::PrivateTag>> {
  using type = typename T::PrivateTag;
};

template <typename T, typename Tag, typename = void>
struct is_constructible_with_tag : std::false_type {};

template <typename T, typename Tag>
struct is_constructible_with_tag<
    T, Tag,
    void_t<decltype(T(std::declval<std::unique_ptr<GooString> &&>(),
                      std::declval<std::unique_ptr<GfxColorSpace> &&>(),
                      std::declval<std::unique_ptr<Function>>(),
                      std::declval<bool>(),
                      std::declval<unsigned int>(),
                      std::declval<const std::vector<int> &>(),
                      std::declval<Tag>()))>> : std::true_type {};

static std::unique_ptr<GfxColorSpace> MakeAltColorSpace() {
  // Use a common device color space as an "alt" colorspace.
  // (Poppler typically provides these concrete classes in GfxState.h / GfxState.cc)
  return std::make_unique<GfxDeviceRGBColorSpace>();
}

static std::unique_ptr<GfxSeparationColorSpace> MakeSepCS_DefaultCtor() {
  auto name = std::make_unique<GooString>("Spot");
  auto alt = MakeAltColorSpace();
  std::unique_ptr<Function> func; // nullptr is acceptable for many construction paths in Poppler
  return std::make_unique<GfxSeparationColorSpace>(std::move(name), std::move(alt), std::move(func));
}

template <typename Tag>
static std::unique_ptr<GfxSeparationColorSpace> MakeSepCS_WithNonMarking_Tag(bool nonMarking, Tag tag) {
  auto name = std::make_unique<GooString>("Spot");
  auto alt = MakeAltColorSpace();
  std::unique_ptr<Function> func; // nullptr
  const unsigned int overprintMask = 0u;
  const std::vector<int> mapping; // empty mapping is a reasonable boundary input
  return std::make_unique<GfxSeparationColorSpace>(std::move(name), std::move(alt), std::move(func),
                                                   nonMarking, overprintMask, mapping, tag);
}

class GfxSeparationColorSpaceTest_477 : public ::testing::Test {};

} // namespace

// ---------- Tests ----------

TEST_F(GfxSeparationColorSpaceTest_477, IsNonMarking_IsCallableAndStable_477) {
  auto cs = MakeSepCS_DefaultCtor();
  const bool v1 = cs->isNonMarking();
  const bool v2 = cs->isNonMarking();
  EXPECT_EQ(v1, v2);
}

TEST_F(GfxSeparationColorSpaceTest_477, IsNonMarking_CopyPreservesObservedValue_477) {
  auto cs = MakeSepCS_DefaultCtor();

  const bool original = cs->isNonMarking();

  // copy() is part of the public interface; verify observable behavior consistency.
  std::unique_ptr<GfxColorSpace> baseCopy = cs->copy();
  ASSERT_NE(baseCopy, nullptr);

  EXPECT_EQ(baseCopy->isNonMarking(), original);

  // If copyAsOwnType exists and is usable, also validate it preserves the observable value.
  // (This stays within public API and does not inspect internals.)
  auto ownCopy = cs->copyAsOwnType();
  ASSERT_NE(ownCopy, nullptr);
  EXPECT_EQ(ownCopy->isNonMarking(), original);
}

TEST_F(GfxSeparationColorSpaceTest_477, IsNonMarking_ReflectsCtorFlag_WhenAvailable_477) {
  // Some Poppler versions expose a constructor that explicitly sets nonMarking,
  // gated by a PrivateTag. If that constructor (and tag) are not available,
  // we skip rather than guessing internal defaults.
  if constexpr (has_private_tag<GfxSeparationColorSpace>::value) {
    using Tag = typename private_tag_type<GfxSeparationColorSpace>::type;
    constexpr bool canConstruct =
        is_constructible_with_tag<GfxSeparationColorSpace, Tag>::value;

    if constexpr (canConstruct) {
      auto csFalse = MakeSepCS_WithNonMarking_Tag(false, Tag{});
      auto csTrue = MakeSepCS_WithNonMarking_Tag(true, Tag{});

      ASSERT_NE(csFalse, nullptr);
      ASSERT_NE(csTrue, nullptr);

      EXPECT_FALSE(csFalse->isNonMarking());
      EXPECT_TRUE(csTrue->isNonMarking());
    } else {
      GTEST_SKIP() << "GfxSeparationColorSpace constructor with (nonMarking, overprintMask, mapping, PrivateTag) "
                      "not available in this build.";
    }
  } else {
    GTEST_SKIP() << "GfxSeparationColorSpace::PrivateTag not available in this build.";
  }
}

TEST_F(GfxSeparationColorSpaceTest_477, IsNonMarking_Boundary_EmptyMapping_WhenAvailable_477) {
  // Boundary-oriented: empty mapping vector and overprintMask=0 with explicit nonMarking flag,
  // when that constructor exists. We only assert on the public observable isNonMarking().
  if constexpr (has_private_tag<GfxSeparationColorSpace>::value) {
    using Tag = typename private_tag_type<GfxSeparationColorSpace>::type;
    constexpr bool canConstruct =
        is_constructible_with_tag<GfxSeparationColorSpace, Tag>::value;

    if constexpr (canConstruct) {
      auto cs = MakeSepCS_WithNonMarking_Tag(true, Tag{});
      ASSERT_NE(cs, nullptr);
      EXPECT_TRUE(cs->isNonMarking());
    } else {
      GTEST_SKIP() << "Boundary constructor not available in this build.";
    }
  } else {
    GTEST_SKIP() << "PrivateTag not available in this build.";
  }
}