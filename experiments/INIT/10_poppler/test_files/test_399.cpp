// TEST_ID: 399
#include <gtest/gtest.h>

#include <climits>
#include <cstdint>
#include <limits>
#include <type_traits>

#include "GfxState.h"

// Poppler's GfxColorTransform is non-copyable (per header). These compile-time checks
// are purely interface-based and do not depend on implementation details.
static_assert(!std::is_copy_constructible<GfxColorTransform>::value,
              "GfxColorTransform must be non-copy-constructible");
static_assert(!std::is_copy_assignable<GfxColorTransform>::value,
              "GfxColorTransform must be non-copy-assignable");

class GfxColorTransformTest_399 : public ::testing::Test {
protected:
  // Use a clearly non-null, non-dereferenced dummy pointer. Tests below only touch getters.
  static void* DummyTransformPtr() {
    return reinterpret_cast<void*>(static_cast<uintptr_t>(0x1));
  }
};

TEST_F(GfxColorTransformTest_399, GetTransformPixelType_IsStableAcrossCalls_399) {
  const unsigned int transformPixelType = 7u;
  GfxColorTransform t(DummyTransformPtr(), /*cmsIntent=*/0, /*inputPixelType=*/0u, transformPixelType);

  const int first = t.getTransformPixelType();
  const int second = t.getTransformPixelType();
  const int third = t.getTransformPixelType();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(GfxColorTransformTest_399, GetTransformPixelType_ReflectsCtorArgument_ForSmallValues_399) {
  // For values that trivially fit in int, we can check exact equality without relying on
  // any private state (only observable getter output).
  const unsigned int transformPixelType = 42u;
  GfxColorTransform t(DummyTransformPtr(), /*cmsIntent=*/1, /*inputPixelType=*/123u, transformPixelType);

  EXPECT_EQ(t.getTransformPixelType(), static_cast<int>(transformPixelType));
}

TEST_F(GfxColorTransformTest_399, GetTransformPixelType_BoundaryValueZero_399) {
  const unsigned int transformPixelType = 0u;
  GfxColorTransform t(DummyTransformPtr(), /*cmsIntent=*/2, /*inputPixelType=*/0u, transformPixelType);

  EXPECT_EQ(t.getTransformPixelType(), 0);
}

TEST_F(GfxColorTransformTest_399, GetTransformPixelType_BoundaryValueIntMax_399) {
  // Choose a boundary that is representable in both unsigned int and int.
  const unsigned int transformPixelType = static_cast<unsigned int>(INT_MAX);
  GfxColorTransform t(DummyTransformPtr(), /*cmsIntent=*/3, /*inputPixelType=*/0u, transformPixelType);

  EXPECT_EQ(t.getTransformPixelType(), INT_MAX);
}

TEST_F(GfxColorTransformTest_399, GetTransformPixelType_DistinguishesDifferentInstances_399) {
  GfxColorTransform t1(DummyTransformPtr(), /*cmsIntent=*/0, /*inputPixelType=*/0u, /*transformPixelType=*/1u);
  GfxColorTransform t2(DummyTransformPtr(), /*cmsIntent=*/0, /*inputPixelType=*/0u, /*transformPixelType=*/2u);

  EXPECT_NE(t1.getTransformPixelType(), t2.getTransformPixelType());
}

TEST_F(GfxColorTransformTest_399, GetTransformPixelType_UsesProvidedValueEvenWithNullTransformPtr_399) {
  // Error-ish / edge case (observable): constructing with a null transform pointer should still
  // allow reading the pixel type via the public getter (no transform execution required).
  const unsigned int transformPixelType = 9u;
  GfxColorTransform t(/*transformA=*/nullptr, /*cmsIntent=*/0, /*inputPixelType=*/0u, transformPixelType);

  EXPECT_EQ(t.getTransformPixelType(), static_cast<int>(transformPixelType));
}

TEST_F(GfxColorTransformTest_399, GetTransformPixelType_IfGivenUIntMaxMatchesObservedNarrowing_399) {
  // The getter returns int while the stored/ctor type is unsigned int (per header).
  // This test captures the observable behavior for an extreme input without assuming
  // any particular semantic meaning beyond the returned value.
  const unsigned int transformPixelType = std::numeric_limits<unsigned int>::max();
  GfxColorTransform t(DummyTransformPtr(), /*cmsIntent=*/0, /*inputPixelType=*/0u, transformPixelType);

  // Whatever the implementation does, the returned value must be consistent with itself.
  // We also compare to the platform's well-defined cast result to document narrowing.
  const int observed = t.getTransformPixelType();
  const int expected_cast = static_cast<int>(transformPixelType);

  EXPECT_EQ(observed, expected_cast);
  EXPECT_EQ(observed, t.getTransformPixelType());  // stable
}