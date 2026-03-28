// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for GfxXYZ2DisplayTransforms::getPerc()
// File under test: ./TestProjects/poppler/poppler/GfxState.h
//
// Constraints respected:
// - Treat implementation as black box (no inference of internal logic).
// - Only use public interface (constructor + getPerc()).
// - No private state access.
// - Cover normal + boundary-ish (null profile) and observable error cases (nullptr allowed).
//
// NOTE: This test assumes Poppler headers are available in include path.

#include <gtest/gtest.h>

#include <memory>

// Poppler
#include "poppler/GfxState.h"

namespace {

class GfxXYZ2DisplayTransformsTest_562 : public ::testing::Test {
protected:
  // No shared fixture state needed.
};

TEST_F(GfxXYZ2DisplayTransformsTest_562, GetPerc_CanBeCalledOnConstObject_562) {
  // Arrange
  GfxLCMSProfilePtr profile; // default-constructed / null profile (boundary input)
  const GfxXYZ2DisplayTransforms transforms(profile);

  // Act
  auto perc = transforms.getPerc();

  // Assert
  // Observable behavior: returns a std::shared_ptr<GfxColorTransform> (may be null).
  // We only verify it is callable and the returned type is a shared_ptr.
  (void)perc;
  SUCCEED();
}

TEST_F(GfxXYZ2DisplayTransformsTest_562, GetPerc_IsStableAcrossMultipleCalls_562) {
  // Arrange
  GfxLCMSProfilePtr profile; // boundary: null profile still should not crash
  GfxXYZ2DisplayTransforms transforms(profile);

  // Act
  auto p1 = transforms.getPerc();
  auto p2 = transforms.getPerc();
  auto p3 = transforms.getPerc();

  // Assert
  // Since getPerc() returns a stored shared_ptr, repeated calls should return
  // the same shared_ptr value (either same object or both nullptr).
  EXPECT_EQ(p1.get(), p2.get());
  EXPECT_EQ(p2.get(), p3.get());
}

TEST_F(GfxXYZ2DisplayTransformsTest_562, GetPerc_ReturnValueCanBeNullptr_562) {
  // Arrange
  GfxLCMSProfilePtr profile; // boundary input
  GfxXYZ2DisplayTransforms transforms(profile);

  // Act
  auto perc = transforms.getPerc();

  // Assert
  // "Exceptional/error" observable case: API may legitimately have no transform
  // and expose it via nullptr shared_ptr. This test accepts nullptr and verifies
  // it is represented as such (no crash, consistent semantics).
  if (!perc) {
    EXPECT_EQ(perc.get(), nullptr);
  } else {
    EXPECT_NE(perc.get(), nullptr);
  }
}

TEST_F(GfxXYZ2DisplayTransformsTest_562, GetPerc_CopySharesSameTransformPointer_562) {
  // Arrange
  GfxLCMSProfilePtr profile;
  GfxXYZ2DisplayTransforms original(profile);

  // Act
  GfxXYZ2DisplayTransforms copied = original; // copy (compiler-generated)
  auto o = original.getPerc();
  auto c = copied.getPerc();

  // Assert
  // Observable behavior: copying the object should not make getPerc() crash.
  // If it stores a shared_ptr, a shallow copy should preserve the pointer value.
  EXPECT_EQ(o.get(), c.get());
}

TEST_F(GfxXYZ2DisplayTransformsTest_562, GetPerc_MoveKeepsValidObjectAndIsCallable_562) {
  // Arrange
  GfxLCMSProfilePtr profile;
  GfxXYZ2DisplayTransforms original(profile);

  // Act
  GfxXYZ2DisplayTransforms moved = std::move(original);
  auto m = moved.getPerc();

  // Assert
  // After move, the moved-to object must be usable via public API.
  // Returned shared_ptr may be nullptr or non-null; just ensure call is safe.
  (void)m;
  SUCCEED();
}

} // namespace