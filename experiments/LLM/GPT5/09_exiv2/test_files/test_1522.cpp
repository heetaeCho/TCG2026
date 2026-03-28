// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_makernote_int_new_panasonic_mn2_1522.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <type_traits>
#include <utility>

// The factory under test is implemented in:
//   ./TestProjects/exiv2/src/makernote_int.cpp
// and is expected to be declared from an internal header.
#include "makernote_int.hpp"

namespace {

// ---- Detection helpers (compile-time) ----
template <typename T, typename = void>
struct has_tag_method : std::false_type {};
template <typename T>
struct has_tag_method<T, std::void_t<decltype(std::declval<const T&>().tag())>> : std::true_type {};

template <typename T, typename = void>
struct has_group_method : std::false_type {};
template <typename T>
struct has_group_method<T, std::void_t<decltype(std::declval<const T&>().group())>> : std::true_type {};

template <typename T, typename = void>
struct has_mnGroup_method : std::false_type {};
template <typename T>
struct has_mnGroup_method<T, std::void_t<decltype(std::declval<const T&>().mnGroup())>> : std::true_type {};

template <typename T>
constexpr bool has_tag_method_v = has_tag_method<T>::value;
template <typename T>
constexpr bool has_group_method_v = has_group_method<T>::value;
template <typename T>
constexpr bool has_mnGroup_method_v = has_mnGroup_method<T>::value;

}  // namespace

namespace Exiv2::Internal {

class PanasonicMn2FactoryTest_1522 : public ::testing::Test {};

TEST_F(PanasonicMn2FactoryTest_1522, ReturnsNonNullUniquePtrForTypicalInputs_1522) {
  const uint16_t tag = 0x1234;
  const IfdId group = static_cast<IfdId>(1);
  const IfdId mnGroup = static_cast<IfdId>(2);

  auto mn = newPanasonicMn2(tag, group, mnGroup);
  ASSERT_NE(mn, nullptr);
}

TEST_F(PanasonicMn2FactoryTest_1522, ReturnedObjectReflectsConstructorInputsWhenObservable_1522) {
  const uint16_t tag = 0x00AB;
  const IfdId group = static_cast<IfdId>(3);
  const IfdId mnGroup = static_cast<IfdId>(4);

  auto mn = newPanasonicMn2(tag, group, mnGroup);
  ASSERT_NE(mn, nullptr);

  // Only assert properties if the interface exposes them.
  using ObjT = std::remove_reference_t<decltype(*mn)>;

  if constexpr (has_tag_method_v<ObjT>) {
    EXPECT_EQ(mn->tag(), tag);
  } else {
    SUCCEED() << "TiffIfdMakernote::tag() not available in this build; skipping tag check.";
  }

  if constexpr (has_group_method_v<ObjT>) {
    EXPECT_EQ(mn->group(), group);
  } else {
    SUCCEED() << "TiffIfdMakernote::group() not available in this build; skipping group check.";
  }

  if constexpr (has_mnGroup_method_v<ObjT>) {
    EXPECT_EQ(mn->mnGroup(), mnGroup);
  } else {
    SUCCEED() << "TiffIfdMakernote::mnGroup() not available in this build; skipping mnGroup check.";
  }
}

TEST_F(PanasonicMn2FactoryTest_1522, BoundaryTagValuesDoNotCrashAndReturnNonNull_1522) {
  const IfdId group = static_cast<IfdId>(0);
  const IfdId mnGroup = static_cast<IfdId>(0);

  auto mn_min = newPanasonicMn2(static_cast<uint16_t>(0), group, mnGroup);
  ASSERT_NE(mn_min, nullptr);

  auto mn_max = newPanasonicMn2(static_cast<uint16_t>(0xFFFF), group, mnGroup);
  ASSERT_NE(mn_max, nullptr);

  // If observable, verify tag boundaries are preserved.
  using ObjT = std::remove_reference_t<decltype(*mn_min)>;
  if constexpr (has_tag_method_v<ObjT>) {
    EXPECT_EQ(mn_min->tag(), static_cast<uint16_t>(0));
    EXPECT_EQ(mn_max->tag(), static_cast<uint16_t>(0xFFFF));
  }
}

TEST_F(PanasonicMn2FactoryTest_1522, MultipleCallsProduceDistinctInstances_1522) {
  const uint16_t tag = 0x4242;
  const IfdId group = static_cast<IfdId>(5);
  const IfdId mnGroup = static_cast<IfdId>(6);

  auto a = newPanasonicMn2(tag, group, mnGroup);
  auto b = newPanasonicMn2(tag, group, mnGroup);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  EXPECT_NE(a.get(), b.get());
}

TEST_F(PanasonicMn2FactoryTest_1522, DifferentInputsYieldObjectsWithDifferentObservableFields_1522) {
  const IfdId group1 = static_cast<IfdId>(7);
  const IfdId group2 = static_cast<IfdId>(8);

  auto mn1 = newPanasonicMn2(static_cast<uint16_t>(0x0101), group1, static_cast<IfdId>(9));
  auto mn2 = newPanasonicMn2(static_cast<uint16_t>(0x0202), group2, static_cast<IfdId>(10));

  ASSERT_NE(mn1, nullptr);
  ASSERT_NE(mn2, nullptr);

  using ObjT = std::remove_reference_t<decltype(*mn1)>;

  // Only compare if the corresponding accessors exist.
  if constexpr (has_tag_method_v<ObjT>) {
    EXPECT_NE(mn1->tag(), mn2->tag());
  } else {
    SUCCEED() << "TiffIfdMakernote::tag() not available; skipping tag inequality check.";
  }

  if constexpr (has_group_method_v<ObjT>) {
    EXPECT_NE(mn1->group(), mn2->group());
  } else {
    SUCCEED() << "TiffIfdMakernote::group() not available; skipping group inequality check.";
  }

  if constexpr (has_mnGroup_method_v<ObjT>) {
    EXPECT_NE(mn1->mnGroup(), mn2->mnGroup());
  } else {
    SUCCEED() << "TiffIfdMakernote::mnGroup() not available; skipping mnGroup inequality check.";
  }
}

}  // namespace Exiv2::Internal