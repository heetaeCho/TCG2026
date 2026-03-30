// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 398
//
// Unit tests for: GfxColorTransform::getInputPixelType()
// File: ./TestProjects/poppler/poppler/GfxState.h
//
// Constraints respected:
// - Black-box: only observable behavior via public interface.
// - No private-state access.
// - No re-implementation of logic.
//
// Notes:
// - The partial snippet shows an inline getter. We validate that it reflects the
//   constructor-provided value across representative boundary values.
// - Copy/assign are deleted; we avoid those operations.

#include <gtest/gtest.h>

#include <limits>

#include "GfxState.h"

namespace {

class GfxColorTransformTest_398 : public ::testing::Test {};

TEST_F(GfxColorTransformTest_398, GetInputPixelType_ReflectsConstructorValue_398) {
  void* dummyTransform = nullptr;
  const int intent = 0;
  const unsigned int inputPixelType = 123u;
  const unsigned int transformPixelType = 456u;

  GfxColorTransform ct(dummyTransform, intent, inputPixelType, transformPixelType);

  EXPECT_EQ(ct.getInputPixelType(), static_cast<int>(inputPixelType));
}

TEST_F(GfxColorTransformTest_398, GetInputPixelType_Zero_398) {
  void* dummyTransform = nullptr;
  const int intent = 1;
  const unsigned int inputPixelType = 0u;
  const unsigned int transformPixelType = 0u;

  GfxColorTransform ct(dummyTransform, intent, inputPixelType, transformPixelType);

  EXPECT_EQ(ct.getInputPixelType(), 0);
}

TEST_F(GfxColorTransformTest_398, GetInputPixelType_MaxUnsignedCastsToIntConsistently_398) {
  void* dummyTransform = nullptr;
  const int intent = -7;
  const unsigned int inputPixelType = std::numeric_limits<unsigned int>::max();
  const unsigned int transformPixelType = 9u;

  GfxColorTransform ct(dummyTransform, intent, inputPixelType, transformPixelType);

  // The getter returns int, while stored field is unsigned int per dependency snippet.
  // We do not assume any special handling beyond normal C++ conversion rules.
  const int expected = static_cast<int>(inputPixelType);
  EXPECT_EQ(ct.getInputPixelType(), expected);
}

TEST_F(GfxColorTransformTest_398, GetInputPixelType_IntMax_398) {
  void* dummyTransform = nullptr;
  const int intent = 2;
  const unsigned int inputPixelType = static_cast<unsigned int>(std::numeric_limits<int>::max());
  const unsigned int transformPixelType = 77u;

  GfxColorTransform ct(dummyTransform, intent, inputPixelType, transformPixelType);

  EXPECT_EQ(ct.getInputPixelType(), std::numeric_limits<int>::max());
}

TEST_F(GfxColorTransformTest_398, GetInputPixelType_IndependentFromOtherCtorArgs_398) {
  void* t1 = nullptr;
  void* t2 = reinterpret_cast<void*>(static_cast<uintptr_t>(0x1));

  const unsigned int inputPixelType = 42u;

  GfxColorTransform a(t1, /*intent=*/0, inputPixelType, /*transformPixelType=*/0u);
  GfxColorTransform b(t2, /*intent=*/999, inputPixelType, /*transformPixelType=*/999u);

  EXPECT_EQ(a.getInputPixelType(), static_cast<int>(inputPixelType));
  EXPECT_EQ(b.getInputPixelType(), static_cast<int>(inputPixelType));
  EXPECT_EQ(a.getInputPixelType(), b.getInputPixelType());
}

}  // namespace