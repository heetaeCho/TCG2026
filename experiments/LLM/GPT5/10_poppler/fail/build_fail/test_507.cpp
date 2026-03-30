// TEST_ID: 507
// File: gfxshading_gethasbbox_unittest.cpp

#include <gtest/gtest.h>

#include <climits>
#include <memory>
#include <type_traits>
#include <vector>

#include "poppler/GfxState.h"

namespace {

// Fixture name must include TEST_ID.
class GfxShadingTest_507 : public ::testing::Test {};

TEST_F(GfxShadingTest_507, GetHasBBox_IsConstCallableAndStableAcrossCalls_507) {
  const GfxShading shading(0);

  // Const-callable.
  const bool v1 = shading.getHasBBox();
  const bool v2 = shading.getHasBBox();

  // Observable behavior: repeated calls on the same object should be stable.
  EXPECT_EQ(v1, v2);
}

TEST_F(GfxShadingTest_507, ConstructWithVariousTypeValues_DoesNotCrashAndIsDeterministic_507) {
  const std::vector<int> types = {0, 1, -1, INT_MAX, INT_MIN};

  for (int t : types) {
    SCOPED_TRACE(::testing::Message() << "typeA=" << t);

    GfxShading shading(t);

    const bool first = shading.getHasBBox();
    const bool second = shading.getHasBBox();

    EXPECT_EQ(first, second);
  }
}

TEST_F(GfxShadingTest_507, PointerCopyConstructor_PreservesObservableHasBBoxValue_507) {
  const std::vector<int> types = {0, 1, -1, INT_MAX, INT_MIN};

  for (int t : types) {
    SCOPED_TRACE(::testing::Message() << "typeA=" << t);

    GfxShading original(t);
    GfxShading copied(&original);

    // Without assuming the internal logic, we can still assert that copying from
    // an existing shading yields the same observable result for getHasBBox().
    EXPECT_EQ(copied.getHasBBox(), original.getHasBBox());

    // And that it remains stable across repeated calls.
    EXPECT_EQ(copied.getHasBBox(), copied.getHasBBox());
  }
}

TEST_F(GfxShadingTest_507, CopyAndAssignAreDeleted_507) {
  // Observable at compile time via type traits.
  static_assert(!std::is_copy_constructible_v<GfxShading>,
                "GfxShading must not be copy-constructible");
  static_assert(!std::is_copy_assignable_v<GfxShading>,
                "GfxShading must not be copy-assignable");

  SUCCEED();
}

} // namespace