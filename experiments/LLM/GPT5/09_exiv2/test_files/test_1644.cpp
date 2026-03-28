// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::Internal::TiffCopier (visitImageEntry)
// TEST_ID: 1644
// *****************************************************************

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Exiv2 internals under test
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace {

// Simple fixture (no assumptions about internal state)
class TiffCopierTest_1644 : public ::testing::Test {};

// Helper: compile-time “is invocable” checks without constructing objects.
template <typename Fn, typename... Args>
constexpr bool IsInvocableV = std::is_invocable_v<Fn, Args...>;

}  // namespace

// -----------------------------------------------------------------------------
// Interface / signature tests (purely based on the provided public declarations)
// -----------------------------------------------------------------------------

TEST_F(TiffCopierTest_1644, VisitImageEntryIsInvocableWithPointer_1644) {
  using Exiv2::Internal::TiffCopier;
  using Exiv2::Internal::TiffImageEntry;

  // Verify the member function can be called with (TiffCopier&, TiffImageEntry*)
  static_assert(IsInvocableV<decltype(&TiffCopier::visitImageEntry), TiffCopier*, TiffImageEntry*>,
                "TiffCopier::visitImageEntry should be invocable with (TiffCopier*, TiffImageEntry*).");
  SUCCEED();
}

TEST_F(TiffCopierTest_1644, CopyObjectIsInvocableWithConstTiffComponentPointer_1644) {
  using Exiv2::Internal::TiffCopier;
  using Exiv2::Internal::TiffComponent;

  static_assert(IsInvocableV<decltype(&TiffCopier::copyObject), TiffCopier*, const TiffComponent*>,
                "TiffCopier::copyObject should be invocable with (TiffCopier*, const TiffComponent*).");
  SUCCEED();
}

TEST_F(TiffCopierTest_1644, CopyObjectIsInvocableWithTiffImageEntryPointer_1644) {
  using Exiv2::Internal::TiffCopier;
  using Exiv2::Internal::TiffImageEntry;

  // This validates that TiffImageEntry* is acceptable where const TiffComponent* is expected
  // (i.e., that TiffImageEntry is-a TiffComponent somewhere in the hierarchy).
  static_assert(IsInvocableV<decltype(&TiffCopier::copyObject), TiffCopier*, const TiffImageEntry*>,
                "TiffCopier::copyObject should accept a (const TiffImageEntry*) argument.");
  SUCCEED();
}

// -----------------------------------------------------------------------------
// Runtime “smoke” coverage
// -----------------------------------------------------------------------------
//
// The provided snippet shows visitImageEntry forwards to copyObject(object).
// However, the observable effects of copyObject depend on Exiv2 internal graph
// objects (root/header/primary groups) whose construction details are not
// provided here. To avoid guessing constructors/behavior, we only run a minimal
// smoke test *when* we can safely create the required objects using default
// constructors. Otherwise we skip (rather than inventing invalid objects).
//

TEST_F(TiffCopierTest_1644, VisitImageEntrySmoke_DefaultConstructibleOnly_1644) {
  using Exiv2::Internal::TiffCopier;
  using Exiv2::Internal::TiffComponent;
  using Exiv2::Internal::TiffHeaderBase;
  using Exiv2::Internal::TiffImageEntry;
  using Exiv2::Internal::PrimaryGroups;

  // Only proceed if these are default constructible in the real codebase.
  if constexpr (!std::is_default_constructible_v<PrimaryGroups> ||
                !std::is_default_constructible_v<TiffImageEntry>) {
    GTEST_SKIP() << "Skipping: required Exiv2 internal types are not default-constructible here.";
  } else {
    // We still cannot safely assume TiffCopier can operate with null root/header
    // because copyObject() may dereference them. Only run if TiffCopier itself is
    // default constructible (rare) OR if root/header are default constructible.
    //
    // NOTE: We do NOT infer any constructors; we only use default construction
    // when available.
    if constexpr (!std::is_default_constructible_v<TiffCopier> ||
                  !std::is_default_constructible_v<TiffComponent> ||
                  !std::is_default_constructible_v<TiffHeaderBase>) {
      GTEST_SKIP() << "Skipping: cannot safely construct TiffCopier with valid root/header using only defaults.";
    } else {
      PrimaryGroups groups{};
      TiffComponent root{};
      TiffHeaderBase header{};
      // If TiffCopier has a default ctor, use it; otherwise this branch is excluded above.
      TiffCopier copier{};

      TiffImageEntry imageEntry{};

      // Minimal: ensure the method is callable at runtime without throwing.
      // (We do not assume what it copies; we only verify it can be invoked.)
      EXPECT_NO_THROW(copier.visitImageEntry(&imageEntry));
    }
  }
}