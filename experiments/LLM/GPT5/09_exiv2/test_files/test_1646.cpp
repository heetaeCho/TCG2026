// =================================================================================================
// TEST_ID: 1646
// File: test_tiffcopier_visitSubIfd_1646.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace {

// A small fixture that constructs TiffCopier with the least-assumptive arguments.
// These tests are intentionally black-box: they only verify that the public interface
// can be invoked safely for typical/boundary inputs (no reliance on private state).
class TiffCopierTest_1646 : public ::testing::Test {
protected:
  void SetUp() override {
    // We do not assume ownership requirements or non-null constraints unless observable.
    // If production code requires non-null collaborators, these tests may need to be
    // adapted to construct real instances from the codebase.
    copier_ = std::make_unique<Exiv2::Internal::TiffCopier>(
        /*pRoot=*/nullptr,
        /*root=*/0u,
        /*pHeader=*/nullptr,
        /*pPrimaryGroups=*/Exiv2::Internal::PrimaryGroups{});
  }

  std::unique_ptr<Exiv2::Internal::TiffCopier> copier_;
};

}  // namespace

TEST_F(TiffCopierTest_1646, VisitSubIfdAcceptsNullptrBoundary_1646) {
  // Boundary/error-like input: nullptr.
  // Observable requirement: the call should be well-formed and not throw C++ exceptions.
  ASSERT_NE(copier_, nullptr);
  EXPECT_NO_THROW(copier_->visitSubIfd(nullptr));
}

TEST_F(TiffCopierTest_1646, VisitSubIfdWithDefaultLikeValuesDoesNotThrow_1646) {
  // Normal operation: visiting a concrete TiffSubIfd instance.
  ASSERT_NE(copier_, nullptr);

  const auto group = static_cast<Exiv2::Internal::IfdId>(0);
  const auto newGroup = static_cast<Exiv2::Internal::IfdId>(0);

  Exiv2::Internal::TiffSubIfd subIfd(/*tag=*/0u, group, newGroup);
  EXPECT_NO_THROW(copier_->visitSubIfd(&subIfd));
}

TEST_F(TiffCopierTest_1646, VisitSubIfdWithMaxTagBoundaryDoesNotThrow_1646) {
  // Boundary condition: maximum uint16_t tag.
  ASSERT_NE(copier_, nullptr);

  const auto group = static_cast<Exiv2::Internal::IfdId>(1);
  const auto newGroup = static_cast<Exiv2::Internal::IfdId>(2);

  Exiv2::Internal::TiffSubIfd subIfd(/*tag=*/0xFFFFu, group, newGroup);
  EXPECT_NO_THROW(copier_->visitSubIfd(&subIfd));
}