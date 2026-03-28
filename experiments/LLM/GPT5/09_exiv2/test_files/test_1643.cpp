// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::Internal::TiffCopier::visitDataEntry
// -----------------------------------------------------------------
// File: ./TestProjects/exiv2/src/tiffvisitor_int.cpp
//
// Constraints honored:
// - Treat implementation as black box
// - Test only observable behavior via public interface
// - No access to private/internal state
// - No re-implementation/inference of internal logic
// *****************************************************************

#include <gtest/gtest.h>

#include <type_traits>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace {

using Exiv2::Internal::PrimaryGroups;
using Exiv2::Internal::TiffCopier;
using Exiv2::Internal::TiffDataEntry;
using Exiv2::Internal::TiffHeaderBase;
using Exiv2::Internal::TiffComponent;

class TiffCopierTest_1643 : public ::testing::Test {
 protected:
  static PrimaryGroups MakeEmptyPrimaryGroups() {
    // PrimaryGroups is an Exiv2-internal type; default construction should yield "empty".
    return PrimaryGroups{};
  }
};

TEST_F(TiffCopierTest_1643, CanConstructWithNullDependencies_1643) {
  // Construction is part of the public interface; this verifies basic usability with
  // minimal (null/empty) dependencies.
  PrimaryGroups groups = MakeEmptyPrimaryGroups();
  EXPECT_NO_THROW({
    TiffCopier copier(/*pRoot=*/static_cast<TiffComponent*>(nullptr),
                      /*root=*/0u,
                      /*pHeader=*/static_cast<const TiffHeaderBase*>(nullptr),
                      /*pPrimaryGroups=*/std::move(groups));
    (void)copier;
  });
}

TEST_F(TiffCopierTest_1643, VisitDataEntryAcceptsPointerWhenDefaultConstructible_1643) {
  // We avoid guessing constructors: if TiffDataEntry isn't default-constructible in this build,
  // we cannot create an instance here without inferring required invariants.
  if (!std::is_default_constructible_v<TiffDataEntry>) {
    GTEST_SKIP() << "TiffDataEntry is not default-constructible in this build; "
                    "test avoids inferring constructor requirements.";
  }

  PrimaryGroups groups = MakeEmptyPrimaryGroups();
  TiffCopier copier(/*pRoot=*/static_cast<TiffComponent*>(nullptr),
                    /*root=*/0u,
                    /*pHeader=*/static_cast<const TiffHeaderBase*>(nullptr),
                    /*pPrimaryGroups=*/std::move(groups));

  TiffDataEntry entry{};
  // Observable behavior available to the test: the call should be well-formed and not throw.
  EXPECT_NO_THROW(copier.visitDataEntry(&entry));
}

TEST_F(TiffCopierTest_1643, VisitDataEntryIsCallableRepeatedly_1643) {
  if (!std::is_default_constructible_v<TiffDataEntry>) {
    GTEST_SKIP() << "TiffDataEntry is not default-constructible in this build; "
                    "test avoids inferring constructor requirements.";
  }

  PrimaryGroups groups = MakeEmptyPrimaryGroups();
  TiffCopier copier(/*pRoot=*/static_cast<TiffComponent*>(nullptr),
                    /*root=*/0u,
                    /*pHeader=*/static_cast<const TiffHeaderBase*>(nullptr),
                    /*pPrimaryGroups=*/std::move(groups));

  TiffDataEntry entry{};

  // Boundary-ish behavior: multiple invocations should remain safe/consistent from the
  // public API perspective (no throw).
  EXPECT_NO_THROW(copier.visitDataEntry(&entry));
  EXPECT_NO_THROW(copier.visitDataEntry(&entry));
  EXPECT_NO_THROW(copier.visitDataEntry(&entry));
}

}  // namespace