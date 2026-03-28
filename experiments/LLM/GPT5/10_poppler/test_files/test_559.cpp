// TEST_ID: 559
#include <gtest/gtest.h>

#include "poppler/GfxState.h"

#include <memory>

class GfxXYZ2DisplayTransformsTest_559 : public ::testing::Test {
protected:
  // Creates a default/null profile pointer without assuming its concrete type.
  // In Poppler this is typically a smart pointer typedef; default construction should be valid.
  static GfxLCMSProfilePtr MakeNullProfile() { return GfxLCMSProfilePtr(); }
};

TEST_F(GfxXYZ2DisplayTransformsTest_559, ConstructWithNullProfileDoesNotThrow_559)
{
  const auto profile = MakeNullProfile();
  EXPECT_NO_THROW({
    GfxXYZ2DisplayTransforms transforms(profile);
    (void)transforms; // avoid unused warning
  });
}

TEST_F(GfxXYZ2DisplayTransformsTest_559, GetRelColIsCallableOnConstAndStableAcrossCalls_559)
{
  const auto profile = MakeNullProfile();
  ASSERT_NO_THROW({
    const GfxXYZ2DisplayTransforms transforms(profile);

    const std::shared_ptr<GfxColorTransform> p1 = transforms.getRelCol();
    const std::shared_ptr<GfxColorTransform> p2 = transforms.getRelCol();

    // Observable behavior we can rely on without assuming internal logic:
    // repeated calls should return an equivalent shared_ptr (same managed object or both null).
    EXPECT_EQ(p1, p2);

    // Const-call already covered by 'transforms' being const; also ensure pointer is safe to copy.
    const std::shared_ptr<GfxColorTransform> p3 = p1;
    EXPECT_EQ(p1, p3);
  });
}

TEST_F(GfxXYZ2DisplayTransformsTest_559, GetRelColReturnValueCanBeResetIndependently_559)
{
  const auto profile = MakeNullProfile();
  GfxXYZ2DisplayTransforms transforms(profile);

  const std::shared_ptr<GfxColorTransform> p1 = transforms.getRelCol();

  // Resetting our local copy must not affect subsequent calls' returned value.
  // (We do not assume whether the internal pointer is null or non-null.)
  std::shared_ptr<GfxColorTransform> local = p1;
  local.reset();

  const std::shared_ptr<GfxColorTransform> p2 = transforms.getRelCol();
  EXPECT_EQ(p1, p2);
}