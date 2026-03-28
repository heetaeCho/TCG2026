// File: test_tiffcopier_visitbinaryarray_1649.cpp
// TEST_ID: 1649

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"  // Exiv2::Internal::TiffCopier (+ dependencies)

namespace {

// Keep construction centralized so tests stay focused on observable behavior.
class TiffCopierTest_1649 : public ::testing::Test {
 protected:
  using Copier = Exiv2::Internal::TiffCopier;

  static Copier MakeCopierWithNullDeps() {
    // The interface allows passing pointers for collaborators; use nullptr to avoid
    // relying on internal object graphs.
    Exiv2::Internal::TiffComponent* pRoot = nullptr;
    const Exiv2::Internal::TiffHeaderBase* pHeader = nullptr;

    // PrimaryGroups is part of the public constructor signature. We only rely on it
    // being default-constructible and movable (as implied by the ctor).
    Exiv2::Internal::PrimaryGroups primaryGroups{};

    // root_ is a uint32_t; use boundary-ish representative values in tests.
    return Copier(pRoot, /*root*/ 0u, pHeader, std::move(primaryGroups));
  }
};

}  // namespace

TEST_F(TiffCopierTest_1649, ConstructWithNullDependencies_1649) {
  // Normal operation: object construction should be possible with nullptr collaborators.
  EXPECT_NO_THROW({
    auto copier = MakeCopierWithNullDeps();
    (void)copier;
  });
}

TEST_F(TiffCopierTest_1649, VisitBinaryArrayAcceptsNullptr_1649) {
  // Boundary / error case: nullptr input should not throw exceptions.
  // (If the implementation chooses to assert/crash on nullptr, this test will reveal it.)
  auto copier = MakeCopierWithNullDeps();

  Exiv2::Internal::TiffBinaryArray* obj = nullptr;
  EXPECT_NO_THROW({ copier.visitBinaryArray(obj); });
}

TEST_F(TiffCopierTest_1649, VisitBinaryArrayCanBeCalledRepeatedlyWithNullptr_1649) {
  // Boundary: repeated calls should remain safe and not accumulate observable failure.
  auto copier = MakeCopierWithNullDeps();

  Exiv2::Internal::TiffBinaryArray* obj = nullptr;
  EXPECT_NO_THROW({
    copier.visitBinaryArray(obj);
    copier.visitBinaryArray(obj);
    copier.visitBinaryArray(obj);
  });
}