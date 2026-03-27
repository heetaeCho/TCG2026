// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::Internal::TiffCopier::visitIfdMakernote
// *****************************************************************
//
// File: ./TestProjects/exiv2/src/tiffvisitor_int.cpp
// Class under test: Exiv2::Internal::TiffCopier
//
// Constraints honored:
// - Treat implementation as a black box (no re-implementation of logic).
// - Use only observable behavior via public interfaces.
// - No access to private/internal state.
// - Include normal + boundary/error-ish (null pointers) where observable.
//
// NOTE:
// The provided partial implementation shows visitIfdMakernote calls copyObject(object).
// copyObject is not virtual, so we cannot directly mock/spy on that call.
// These tests therefore focus on observable outcomes and robustness (no crashes / no throws)
// using only public interfaces available in the real Exiv2 codebase.

#include <gtest/gtest.h>

#include <memory>
#include <utility>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

namespace Exiv2::Internal {
namespace {

// A small helper to create an "empty" PrimaryGroups object without knowing its exact shape.
// This relies on PrimaryGroups being default-constructible in the real codebase (it is in Exiv2).
static PrimaryGroups makeEmptyPrimaryGroups() {
  return PrimaryGroups{};
}

class TiffCopierTest_1648 : public ::testing::Test {
 protected:
  // Use conservative, "neutral" values for enums/ids: we do not assume specific enumerators exist.
  static constexpr uint16_t kTag = 0x0001;

  static IfdId asIfdId0() { return static_cast<IfdId>(0); }
};

TEST_F(TiffCopierTest_1648, VisitIfdMakernote_AllowsNullObjectPointer_1648) {
  // Boundary / error-ish: Passing nullptr to the visit function.
  //
  // Observable requirement: should not throw C++ exceptions.
  // (If the underlying code dereferences null, that would be a crash; this test would fail,
  // which is still a valid observable behavior check.)
  TiffCopier copier(/*pRoot=*/nullptr,
                    /*root=*/0u,
                    /*pHeader=*/nullptr,
                    /*pPrimaryGroups=*/makeEmptyPrimaryGroups());

  EXPECT_NO_THROW(copier.visitIfdMakernote(nullptr));
}

TEST_F(TiffCopierTest_1648, VisitIfdMakernote_WithValidObject_DoesNotThrow_1648) {
  // Normal operation: supply a valid TiffIfdMakernote instance.
  //
  // We do NOT assume anything about internal copying semantics beyond the call being valid.
  auto header = std::unique_ptr<MnHeader>{};  // empty/NULL header is permitted as a unique_ptr value
  TiffIfdMakernote mn(kTag, asIfdId0(), asIfdId0(), std::move(header), /*hasNext=*/false);

  TiffCopier copier(/*pRoot=*/nullptr,
                    /*root=*/0u,
                    /*pHeader=*/nullptr,
                    /*pPrimaryGroups=*/makeEmptyPrimaryGroups());

  EXPECT_NO_THROW(copier.visitIfdMakernote(&mn));
}

TEST_F(TiffCopierTest_1648, VisitIfdMakernote_WithRootProvided_RemainsCallable_1648) {
  // Normal operation with a non-null root component pointer.
  //
  // We intentionally avoid asserting specific structural changes to the root because:
  // - copyObject is not observable directly (non-virtual) and the exact copy semantics are not
  //   guaranteed by the provided interface excerpt.
  //
  // However, passing a root is a key usage mode of TiffCopier, so we verify it remains callable.
  TiffDirectory rootDir(kTag, asIfdId0(), /*hasNext=*/false);

  auto header = std::unique_ptr<MnHeader>{};
  TiffIfdMakernote mn(kTag, asIfdId0(), asIfdId0(), std::move(header), /*hasNext=*/false);

  TiffCopier copier(/*pRoot=*/&rootDir,
                    /*root=*/0u,
                    /*pHeader=*/nullptr,
                    /*pPrimaryGroups=*/makeEmptyPrimaryGroups());

  EXPECT_NO_THROW(copier.visitIfdMakernote(&mn));
}

TEST_F(TiffCopierTest_1648, VisitIfdMakernote_CanBeCalledRepeatedly_1648) {
  // Boundary: repeated calls with the same object pointer should remain safe/consistent at the interface level.
  // We do not assume idempotence or structural equality of copies; we only check it remains callable.
  TiffDirectory rootDir(kTag, asIfdId0(), /*hasNext=*/false);

  auto header = std::unique_ptr<MnHeader>{};
  TiffIfdMakernote mn(kTag, asIfdId0(), asIfdId0(), std::move(header), /*hasNext=*/false);

  TiffCopier copier(/*pRoot=*/&rootDir,
                    /*root=*/0u,
                    /*pHeader=*/nullptr,
                    /*pPrimaryGroups=*/makeEmptyPrimaryGroups());

  EXPECT_NO_THROW(copier.visitIfdMakernote(&mn));
  EXPECT_NO_THROW(copier.visitIfdMakernote(&mn));
  EXPECT_NO_THROW(copier.visitIfdMakernote(&mn));
}

}  // namespace
}  // namespace Exiv2::Internal