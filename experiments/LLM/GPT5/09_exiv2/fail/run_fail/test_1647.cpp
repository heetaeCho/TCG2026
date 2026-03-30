// =================================================================================================
// Test file: test_tiffcopier_visitmnentry_1647.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace {

using Exiv2::Internal::TiffCopier;
using Exiv2::Internal::TiffMnEntry;

// IfdId is defined in Exiv2; to avoid depending on specific enumerators (which can vary),
// we use integral casts for test inputs (still valid through the public constructor signature).
using Exiv2::IfdId;

static IfdId MakeIfdId(int v) { return static_cast<IfdId>(v); }

class TiffCopierTest_1647 : public ::testing::Test {
 protected:
  // Use nullptr / default-constructed PrimaryGroups to keep the tests focused on the interface
  // of visitMnEntry(), without making assumptions about internal collaboration.
  // NOTE: If the real implementation requires non-null pointers, these tests can be adjusted
  // to use real instances from the codebase; the intent remains purely black-box.
  TiffCopier MakeCopier() {
    return TiffCopier(/*pRoot=*/nullptr,
                      /*root=*/0u,
                      /*pHeader=*/nullptr,
                      /*pPrimaryGroups=*/Exiv2::Internal::PrimaryGroups{});
  }
};

TEST_F(TiffCopierTest_1647, VisitMnEntryAcceptsNonNullPointer_1647) {
  TiffCopier copier = MakeCopier();

  TiffMnEntry entry(/*tag=*/0x1234u, /*group=*/MakeIfdId(0), /*mnGroup=*/MakeIfdId(1));

  // Observable behavior: call is well-formed and should not throw exceptions.
  EXPECT_NO_THROW(copier.visitMnEntry(&entry));
}

TEST_F(TiffCopierTest_1647, VisitMnEntryHandlesBoundaryTagZero_1647) {
  TiffCopier copier = MakeCopier();

  TiffMnEntry entry(/*tag=*/0x0000u, /*group=*/MakeIfdId(0), /*mnGroup=*/MakeIfdId(1));

  EXPECT_NO_THROW(copier.visitMnEntry(&entry));
}

TEST_F(TiffCopierTest_1647, VisitMnEntryHandlesBoundaryTagMax_1647) {
  TiffCopier copier = MakeCopier();

  TiffMnEntry entry(/*tag=*/0xFFFFu, /*group=*/MakeIfdId(0), /*mnGroup=*/MakeIfdId(1));

  EXPECT_NO_THROW(copier.visitMnEntry(&entry));
}

TEST_F(TiffCopierTest_1647, VisitMnEntryIsCallableRepeatedlyOnSameObject_1647) {
  TiffCopier copier = MakeCopier();

  TiffMnEntry entry(/*tag=*/0x00ABu, /*group=*/MakeIfdId(0), /*mnGroup=*/MakeIfdId(1));

  EXPECT_NO_THROW(copier.visitMnEntry(&entry));
  EXPECT_NO_THROW(copier.visitMnEntry(&entry));
}

TEST_F(TiffCopierTest_1647, CopyObjectAndVisitMnEntryAreBothCallable_1647) {
  TiffCopier copier = MakeCopier();

  TiffMnEntry entry(/*tag=*/0x0BEEu, /*group=*/MakeIfdId(2), /*mnGroup=*/MakeIfdId(3));

  // visitMnEntry delegates to copyObject(object). We can't intercept the call (copyObject is not
  // virtual), so the best black-box check we can do here is that both entry points are callable
  // with the same underlying object and neither throws.
  EXPECT_NO_THROW(copier.copyObject(&entry));
  EXPECT_NO_THROW(copier.visitMnEntry(&entry));
}

}  // namespace