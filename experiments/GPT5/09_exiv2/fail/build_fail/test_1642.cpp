// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 1642
//
// Unit tests for Exiv2::Internal::TiffCopier::visitEntry
// File under test: ./TestProjects/exiv2/src/tiffvisitor_int.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace {

using Exiv2::Internal::PrimaryGroups;
using Exiv2::Internal::TiffCopier;
using Exiv2::Internal::TiffEntry;

class TiffCopierTest_1642 : public ::testing::Test {
 protected:
  static PrimaryGroups MakePrimaryGroups() {
    // PrimaryGroups is expected to be a standard container / value type.
    // If it is not default-constructible in some configurations, we skip tests
    // that require it (see usage sites).
    if constexpr (std::is_default_constructible_v<PrimaryGroups>) {
      return PrimaryGroups{};
    } else {
      // This return is never instantiated when not default-constructible.
      return PrimaryGroups{};
    }
  }

  static bool CanMakePrimaryGroups() {
    return std::is_default_constructible_v<PrimaryGroups>;
  }
};

TEST_F(TiffCopierTest_1642, ConstructWithNullPointers_1642) {
  if (!CanMakePrimaryGroups()) {
    GTEST_SKIP() << "PrimaryGroups is not default-constructible in this build.";
  }

  // Construction should be possible with nullptr collaborators if the interface
  // allows it. This test validates that the constructor is callable and does not
  // throw exceptions.
  EXPECT_NO_THROW({
    TiffCopier copier(/*pRoot=*/nullptr, /*root=*/0u, /*pHeader=*/nullptr,
                      MakePrimaryGroups());
    (void)copier;
  });
}

TEST_F(TiffCopierTest_1642, VisitEntryAcceptsNullptr_1642) {
  if (!CanMakePrimaryGroups()) {
    GTEST_SKIP() << "PrimaryGroups is not default-constructible in this build.";
  }

  TiffCopier copier(/*pRoot=*/nullptr, /*root=*/0u, /*pHeader=*/nullptr,
                    MakePrimaryGroups());

  // Boundary / error-case: nullptr input.
  // Observable requirement: should not throw exceptions (and should not crash).
  EXPECT_NO_THROW({
    copier.visitEntry(nullptr);
  });
}

TEST_F(TiffCopierTest_1642, VisitEntryWithDefaultConstructibleEntryDoesNotThrow_1642) {
  if (!CanMakePrimaryGroups()) {
    GTEST_SKIP() << "PrimaryGroups is not default-constructible in this build.";
  }

  if constexpr (!std::is_default_constructible_v<TiffEntry>) {
    GTEST_SKIP() << "TiffEntry is not default-constructible in this build.";
  } else {
    TiffCopier copier(/*pRoot=*/nullptr, /*root=*/0u, /*pHeader=*/nullptr,
                      MakePrimaryGroups());
    TiffEntry entry{};

    // Normal operation: visiting a real object pointer should be safe.
    EXPECT_NO_THROW({
      copier.visitEntry(&entry);
    });
  }
}

TEST_F(TiffCopierTest_1642, VisitEntryMultipleCallsAreSafe_1642) {
  if (!CanMakePrimaryGroups()) {
    GTEST_SKIP() << "PrimaryGroups is not default-constructible in this build.";
  }

  TiffCopier copier(/*pRoot=*/nullptr, /*root=*/0u, /*pHeader=*/nullptr,
                    MakePrimaryGroups());

  // Boundary: repeated calls should remain safe and not throw.
  EXPECT_NO_THROW({
    copier.visitEntry(nullptr);
    copier.visitEntry(nullptr);
    copier.visitEntry(nullptr);
  });
}

}  // namespace