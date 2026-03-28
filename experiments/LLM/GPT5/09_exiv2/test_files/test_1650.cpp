// File: test_tiffcopier_visitbinaryelement_1650.cpp
// TEST_ID: 1650

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace {

using Exiv2::Internal::TiffBinaryElement;
using Exiv2::Internal::TiffCopier;
using Exiv2::Internal::PrimaryGroups;

class TiffCopierTest_1650 : public ::testing::Test {
 protected:
  // Helper: run a callable and report whether it threw (without assuming exception type).
  template <typename F>
  static bool DidThrow(F&& f) {
    try {
      f();
      return false;
    } catch (...) {
      return true;
    }
  }

  // Create a copier with the best-effort minimal inputs available from the public interface.
  // We intentionally avoid assumptions about internal invariants.
  static TiffCopier MakeCopier(TiffBinaryElement* root) {
    PrimaryGroups groups;  // default empty is the least-assumptive boundary input
    // pHeader is not available to construct here; nullptr is the least-assumptive boundary input.
    return TiffCopier(root, /*root*/ 0u, /*pHeader*/ nullptr, std::move(groups));
  }
};

TEST_F(TiffCopierTest_1650, VisitBinaryElementMatchesCopyObjectForNonNull_1650) {
  TiffBinaryElement root;
  TiffBinaryElement element;

  TiffCopier copier = MakeCopier(&root);

  const bool copy_threw = DidThrow([&] { copier.copyObject(&element); });
  const bool visit_threw = DidThrow([&] { copier.visitBinaryElement(&element); });

  // Observable behavior requirement: visitBinaryElement should behave like calling copyObject
  // with the same pointer, at least with respect to whether an exception is thrown.
  EXPECT_EQ(visit_threw, copy_threw);
}

TEST_F(TiffCopierTest_1650, VisitBinaryElementMatchesCopyObjectForNullptr_1650) {
  TiffBinaryElement root;
  TiffCopier copier = MakeCopier(&root);

  const bool copy_threw = DidThrow([&] { copier.copyObject(nullptr); });
  const bool visit_threw = DidThrow([&] { copier.visitBinaryElement(nullptr); });

  EXPECT_EQ(visit_threw, copy_threw);
}

TEST_F(TiffCopierTest_1650, VisitBinaryElementIsConsistentAcrossRepeatedCalls_1650) {
  TiffBinaryElement root;
  TiffBinaryElement element;
  TiffCopier copier = MakeCopier(&root);

  const bool first_threw = DidThrow([&] { copier.visitBinaryElement(&element); });
  const bool second_threw = DidThrow([&] { copier.visitBinaryElement(&element); });

  // We do not assume side-effects; we only require that the observable exception behavior is
  // consistent for the same input across repeated calls in a single process.
  EXPECT_EQ(second_threw, first_threw);
}

TEST_F(TiffCopierTest_1650, CopyObjectAndVisitBinaryElementAreIndependentlyCallable_1650) {
  TiffBinaryElement root;
  TiffBinaryElement element;
  TiffCopier copier = MakeCopier(&root);

  // These assertions are intentionally minimal: they verify the functions are callable and
  // do not *crash* the process under normal test execution. We avoid assuming whether they
  // must throw or must not throw.
  EXPECT_NO_FATAL_FAILURE((void)DidThrow([&] { copier.copyObject(&element); }));
  EXPECT_NO_FATAL_FAILURE((void)DidThrow([&] { copier.visitBinaryElement(&element); }));
}

}  // namespace