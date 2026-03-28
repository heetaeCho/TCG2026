// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_makernote_int_tiffmnregistry_test_1430.cpp
#include <gtest/gtest.h>

#include <string_view>

#include "makernote_int.hpp"  // Exiv2::Internal::TiffMnRegistry, IfdId

namespace {

// NOTE: Only tests observable behavior through the public interface.
// We do NOT assume anything about IfdId beyond being comparable/assignable.

class TiffMnRegistryTest_1430 : public ::testing::Test {
 protected:
  Exiv2::Internal::TiffMnRegistry reg_{};

  static Exiv2::IfdId AnyIfdIdValue(int seed) {
    // Avoid inferring IfdId internals; just rely on it being constructible from an int
    // in the Exiv2 codebase (typically an enum). If not constructible, compilation
    // will reveal it and the project should adjust the helper accordingly.
    return static_cast<Exiv2::IfdId>(seed);
  }
};

}  // namespace

TEST_F(TiffMnRegistryTest_1430, EqualsIfdId_ReturnsTrueWhenMnGroupMatches_1430) {
  const Exiv2::IfdId key = TiffMnRegistryTest_1430::AnyIfdIdValue(1);
  reg_.mnGroup_ = key;

  EXPECT_TRUE(reg_ == key);
}

TEST_F(TiffMnRegistryTest_1430, EqualsIfdId_ReturnsFalseWhenMnGroupDiffers_1430) {
  const Exiv2::IfdId set_value = TiffMnRegistryTest_1430::AnyIfdIdValue(1);
  const Exiv2::IfdId other_key = TiffMnRegistryTest_1430::AnyIfdIdValue(2);
  reg_.mnGroup_ = set_value;

  EXPECT_FALSE(reg_ == other_key);
}

TEST_F(TiffMnRegistryTest_1430, EqualsIfdId_IsSymmetricWithTwoRegistriesHavingSameMnGroup_1430) {
  const Exiv2::IfdId key = TiffMnRegistryTest_1430::AnyIfdIdValue(42);

  Exiv2::Internal::TiffMnRegistry a{};
  Exiv2::Internal::TiffMnRegistry b{};
  a.mnGroup_ = key;
  b.mnGroup_ = key;

  EXPECT_TRUE(a == key);
  EXPECT_TRUE(b == key);
}

TEST_F(TiffMnRegistryTest_1430, EqualsIfdId_BoundaryUsesTwoDifferentIfdIdValues_1430) {
  // Boundary-style coverage: exercise two extreme-ish values without assuming semantics.
  const Exiv2::IfdId low = TiffMnRegistryTest_1430::AnyIfdIdValue(0);
  const Exiv2::IfdId high = TiffMnRegistryTest_1430::AnyIfdIdValue(100000);

  reg_.mnGroup_ = low;
  EXPECT_TRUE(reg_ == low);
  EXPECT_FALSE(reg_ == high);

  reg_.mnGroup_ = high;
  EXPECT_TRUE(reg_ == high);
  EXPECT_FALSE(reg_ == low);
}

TEST_F(TiffMnRegistryTest_1430, EqualsIfdId_DoesNotModifyMnGroupObservableByRepeatedQueries_1430) {
  const Exiv2::IfdId key = TiffMnRegistryTest_1430::AnyIfdIdValue(7);
  const Exiv2::IfdId other = TiffMnRegistryTest_1430::AnyIfdIdValue(8);
  reg_.mnGroup_ = key;

  EXPECT_TRUE(reg_ == key);
  EXPECT_FALSE(reg_ == other);
  // Repeat to ensure stable observable behavior.
  EXPECT_TRUE(reg_ == key);
  EXPECT_FALSE(reg_ == other);

  // Still should match original key if operator== is non-mutating (observable via same results).
  EXPECT_TRUE(reg_ == key);
}