// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_makernote_int_newpentaxmn2_1524.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <type_traits>
#include <utility>

#include "makernote_int.hpp"  // Exiv2::Internal::newPentaxMn2
#include "types.hpp"          // Exiv2::IfdId (or equivalent in Exiv2)

namespace {

// Detection idiom helpers to only assert properties if the public interface supports them.
template <typename T, typename = void>
struct has_tag_method : std::false_type {};
template <typename T>
struct has_tag_method<T, std::void_t<decltype(std::declval<const T&>().tag())>> : std::true_type {};

template <typename T, typename = void>
struct has_group_method : std::false_type {};
template <typename T>
struct has_group_method<T, std::void_t<decltype(std::declval<const T&>().group())>> : std::true_type {};

template <typename T, typename = void>
struct has_mn_group_method : std::false_type {};
template <typename T>
struct has_mn_group_method<T, std::void_t<decltype(std::declval<const T&>().mnGroup())>> : std::true_type {};

}  // namespace

TEST(PentaxMn2FactoryTest_1524, ReturnsNonNullForTypicalInputs_1524) {
  const uint16_t tag = 0x1234;
  const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(0);
  const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(1);

  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> mn;
  EXPECT_NO_THROW(mn = Exiv2::Internal::newPentaxMn2(tag, group, mnGroup));
  ASSERT_NE(mn, nullptr);

  // Verify observable state only if the interface exposes it.
  if constexpr (has_tag_method<Exiv2::Internal::TiffIfdMakernote>::value) {
    EXPECT_EQ(mn->tag(), tag);
  }
  if constexpr (has_group_method<Exiv2::Internal::TiffIfdMakernote>::value) {
    EXPECT_EQ(mn->group(), group);
  }
  if constexpr (has_mn_group_method<Exiv2::Internal::TiffIfdMakernote>::value) {
    EXPECT_EQ(mn->mnGroup(), mnGroup);
  }
}

TEST(PentaxMn2FactoryTest_1524, AcceptsBoundaryTagZero_1524) {
  const uint16_t tag = 0;
  const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(0);
  const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(0);

  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> mn;
  EXPECT_NO_THROW(mn = Exiv2::Internal::newPentaxMn2(tag, group, mnGroup));
  ASSERT_NE(mn, nullptr);

  if constexpr (has_tag_method<Exiv2::Internal::TiffIfdMakernote>::value) {
    EXPECT_EQ(mn->tag(), tag);
  }
}

TEST(PentaxMn2FactoryTest_1524, AcceptsBoundaryTagMaxUint16_1524) {
  const uint16_t tag = static_cast<uint16_t>(0xFFFFu);
  const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(255);
  const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(256);

  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> mn;
  EXPECT_NO_THROW(mn = Exiv2::Internal::newPentaxMn2(tag, group, mnGroup));
  ASSERT_NE(mn, nullptr);

  if constexpr (has_tag_method<Exiv2::Internal::TiffIfdMakernote>::value) {
    EXPECT_EQ(mn->tag(), tag);
  }
}

TEST(PentaxMn2FactoryTest_1524, ProducesDistinctObjectsOnEachCall_1524) {
  const uint16_t tag = 0x0001;
  const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(7);
  const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(8);

  auto mn1 = Exiv2::Internal::newPentaxMn2(tag, group, mnGroup);
  auto mn2 = Exiv2::Internal::newPentaxMn2(tag, group, mnGroup);

  ASSERT_NE(mn1, nullptr);
  ASSERT_NE(mn2, nullptr);
  EXPECT_NE(mn1.get(), mn2.get());
}

TEST(PentaxMn2FactoryTest_1524, UniquePtrMoveTransfersOwnership_1524) {
  const uint16_t tag = 0x00AA;
  const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(3);
  const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(4);

  auto mn = Exiv2::Internal::newPentaxMn2(tag, group, mnGroup);
  ASSERT_NE(mn, nullptr);

  auto* raw = mn.get();
  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> moved = std::move(mn);

  EXPECT_EQ(mn.get(), nullptr);
  ASSERT_NE(moved, nullptr);
  EXPECT_EQ(moved.get(), raw);

  if constexpr (has_tag_method<Exiv2::Internal::TiffIfdMakernote>::value) {
    EXPECT_EQ(moved->tag(), tag);
  }
}

TEST(PentaxMn2FactoryTest_1524, RepeatedCallsDoNotThrow_1524) {
  // Error/exception behavior is only observable via throws; this test ensures construction is stable.
  const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(0);
  const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(1);

  for (uint16_t tag : {static_cast<uint16_t>(0), static_cast<uint16_t>(1), static_cast<uint16_t>(0x7FFFu),
                       static_cast<uint16_t>(0xFFFFu)}) {
    EXPECT_NO_THROW({
      auto mn = Exiv2::Internal::newPentaxMn2(tag, group, mnGroup);
      ASSERT_NE(mn, nullptr);
    });
  }
}