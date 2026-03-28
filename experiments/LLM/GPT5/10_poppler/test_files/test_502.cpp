// TEST_ID: 502
#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxShadingTest_502 : public ::testing::Test {};

TEST_F(GfxShadingTest_502, GetType_IsStableForSameConstructorArg_502) {
  const int typeA = 0;

  GfxShading s1(typeA);
  GfxShading s2(typeA);

  // Black-box observable behavior: same constructor input should yield the same
  // observable type result.
  EXPECT_EQ(s1.getType(), s2.getType());

  // Stability on repeated calls.
  EXPECT_EQ(s1.getType(), s1.getType());
}

TEST_F(GfxShadingTest_502, GetType_PreservesTypeAcrossCopyConstructorFromPointer_502) {
  const int typeA = 1;

  GfxShading original(typeA);
  GfxShading copied(&original);

  // Observable behavior: a copy constructed from an existing shading should
  // expose the same shading type.
  EXPECT_EQ(original.getType(), copied.getType());
}

TEST_F(GfxShadingTest_502, GetType_BoundaryConstructorArgs_DoNotCrash_502) {
  // Boundary / edge inputs: ensure construction + getType is safe and stable.
  const int kCases[] = {
      0,
      1,
      -1,
      std::numeric_limits<int>::min(),
      std::numeric_limits<int>::max(),
  };

  for (int typeA : kCases) {
    GfxShading s(typeA);

    // We don't assume any particular mapping from int -> ShadingType.
    // We only assert the observable property that repeated calls are consistent.
    const auto t1 = s.getType();
    const auto t2 = s.getType();
    EXPECT_EQ(t1, t2);
  }
}

TEST_F(GfxShadingTest_502, GetType_CopyChainPreservesType_502) {
  const int typeA = 2;

  GfxShading s1(typeA);
  GfxShading s2(&s1);
  GfxShading s3(&s2);

  EXPECT_EQ(s1.getType(), s2.getType());
  EXPECT_EQ(s2.getType(), s3.getType());
}

} // namespace