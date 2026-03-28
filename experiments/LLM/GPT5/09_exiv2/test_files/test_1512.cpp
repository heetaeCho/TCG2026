// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_makernote_int_newOlympusMn2_1512.cpp
//
// Unit tests for:
//   Exiv2::Internal::newOlympusMn2(uint16_t tag, IfdId group, IfdId mnGroup)
//
// Constraints honored:
// - Treat implementation as a black box (no internal-state inspection).
// - Test only observable behavior via public interface.
//
// NOTE:
// This test assumes Exiv2 headers provide:
//   - Exiv2::Internal::newOlympusMn2 declaration (typically via makernote_int.hpp)
//   - Exiv2::Internal::TiffIfdMakernote type
//   - IfdId enum / type
//
// If your build uses different include paths, adjust includes accordingly.

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <type_traits>

#include "makernote_int.hpp"  // Expected to declare Exiv2::Internal::newOlympusMn2
#include "tiffcomposite_int.hpp"  // Expected to declare TiffIfdMakernote (may vary in your tree)

namespace {

using Exiv2::Internal::newOlympusMn2;

// Helper: pick two distinct IfdId values without relying on a particular enumerator name.
// If IfdId is an enum, we can static_cast from integers for test inputs.
template <typename T>
constexpr T as_ifdid(int v) {
  return static_cast<T>(v);
}

class NewOlympusMn2Test_1512 : public ::testing::Test {};

TEST_F(NewOlympusMn2Test_1512, ReturnsNonNullUniquePtr_1512) {
  constexpr uint16_t tag = 0x0001;
  const auto group = as_ifdid<Exiv2::IfdId>(0);
  const auto mnGroup = as_ifdid<Exiv2::IfdId>(1);

  auto mn = newOlympusMn2(tag, group, mnGroup);

  ASSERT_NE(mn, nullptr);
}

TEST_F(NewOlympusMn2Test_1512, ReturnsUniqueOwnershipEachCall_1512) {
  constexpr uint16_t tag = 0x0002;
  const auto group = as_ifdid<Exiv2::IfdId>(0);
  const auto mnGroup = as_ifdid<Exiv2::IfdId>(1);

  auto a = newOlympusMn2(tag, group, mnGroup);
  auto b = newOlympusMn2(tag, group, mnGroup);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  // Observable property: different allocations should yield different addresses.
  EXPECT_NE(a.get(), b.get());
}

TEST_F(NewOlympusMn2Test_1512, AcceptsBoundaryTagValues_1512) {
  const auto group = as_ifdid<Exiv2::IfdId>(0);
  const auto mnGroup = as_ifdid<Exiv2::IfdId>(1);

  auto mnMin = newOlympusMn2(static_cast<uint16_t>(0x0000), group, mnGroup);
  auto mnMax = newOlympusMn2(static_cast<uint16_t>(0xFFFF), group, mnGroup);

  EXPECT_NE(mnMin, nullptr);
  EXPECT_NE(mnMax, nullptr);
}

TEST_F(NewOlympusMn2Test_1512, AcceptsSameGroupAndMnGroup_1512) {
  constexpr uint16_t tag = 0x00AA;
  const auto same = as_ifdid<Exiv2::IfdId>(0);

  auto mn = newOlympusMn2(tag, same, same);

  EXPECT_NE(mn, nullptr);
}

// “Exceptional or error cases (if observable through the interface)”
// Here, the interface returns a std::unique_ptr and (per provided code) uses make_unique.
// Allocation failure would throw std::bad_alloc, but that's not a practical deterministic unit test.
// So we only validate that typical varied inputs do not throw.
TEST_F(NewOlympusMn2Test_1512, DoesNotThrowForTypicalInputs_1512) {
  EXPECT_NO_THROW({
    auto mn = newOlympusMn2(static_cast<uint16_t>(0x1234),
                            as_ifdid<Exiv2::IfdId>(2),
                            as_ifdid<Exiv2::IfdId>(3));
    (void)mn;
  });
}

}  // namespace