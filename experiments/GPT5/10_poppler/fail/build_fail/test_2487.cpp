// File: poppler-image-mapping-copy-test-2487.cc
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include "./TestProjects/poppler/glib/poppler-page.h"

// Function under test (implemented in poppler-page.cc)
PopplerImageMapping *poppler_image_mapping_copy(PopplerImageMapping *mapping);
}

namespace {

class PopplerImageMappingCopyTest_2487 : public ::testing::Test {
protected:
  static PopplerImageMapping *NewMapping(int image_id) {
    PopplerImageMapping *m = g_slice_new(PopplerImageMapping);
    m->image_id = image_id;
    return m;
  }

  static void FreeMapping(PopplerImageMapping *m) {
    if (m)
      g_slice_free(PopplerImageMapping, m);
  }
};

TEST_F(PopplerImageMappingCopyTest_2487, CopyReturnsDistinctObjectWithSameFields_2487) {
  PopplerImageMapping *orig = NewMapping(123);
  ASSERT_NE(orig, nullptr);

  PopplerImageMapping *copy = poppler_image_mapping_copy(orig);
  ASSERT_NE(copy, nullptr);

  // Observable behavior: copy should be a different allocation with the same public field values.
  EXPECT_NE(copy, orig);
  EXPECT_EQ(copy->image_id, orig->image_id);

  FreeMapping(copy);
  FreeMapping(orig);
}

TEST_F(PopplerImageMappingCopyTest_2487, CopyPreservesNegativeImageId_2487) {
  PopplerImageMapping *orig = NewMapping(-1);
  ASSERT_NE(orig, nullptr);

  PopplerImageMapping *copy = poppler_image_mapping_copy(orig);
  ASSERT_NE(copy, nullptr);

  EXPECT_NE(copy, orig);
  EXPECT_EQ(copy->image_id, -1);

  FreeMapping(copy);
  FreeMapping(orig);
}

TEST_F(PopplerImageMappingCopyTest_2487, CopyHandlesIntMinAndMax_2487) {
  {
    PopplerImageMapping *orig = NewMapping(G_MININT);
    ASSERT_NE(orig, nullptr);

    PopplerImageMapping *copy = poppler_image_mapping_copy(orig);
    ASSERT_NE(copy, nullptr);

    EXPECT_NE(copy, orig);
    EXPECT_EQ(copy->image_id, G_MININT);

    FreeMapping(copy);
    FreeMapping(orig);
  }

  {
    PopplerImageMapping *orig = NewMapping(G_MAXINT);
    ASSERT_NE(orig, nullptr);

    PopplerImageMapping *copy = poppler_image_mapping_copy(orig);
    ASSERT_NE(copy, nullptr);

    EXPECT_NE(copy, orig);
    EXPECT_EQ(copy->image_id, G_MAXINT);

    FreeMapping(copy);
    FreeMapping(orig);
  }
}

TEST_F(PopplerImageMappingCopyTest_2487, CopyIsIndependentFromOriginalAfterMutation_2487) {
  PopplerImageMapping *orig = NewMapping(7);
  ASSERT_NE(orig, nullptr);

  PopplerImageMapping *copy = poppler_image_mapping_copy(orig);
  ASSERT_NE(copy, nullptr);
  ASSERT_NE(copy, orig);
  ASSERT_EQ(copy->image_id, 7);

  // Mutate original after copying; the copy should retain its original value.
  orig->image_id = 999;
  EXPECT_EQ(orig->image_id, 999);
  EXPECT_EQ(copy->image_id, 7);

  FreeMapping(copy);
  FreeMapping(orig);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerImageMappingCopyTest_2487, CopyWithNullptrDiesOrAborts_2487) {
  // Error case (observable): passing nullptr may crash/abort depending on GLib build/settings.
  // We treat the implementation as a black box and only assert that it does not "silently succeed".
  ASSERT_DEATH(
      {
        PopplerImageMapping *out = poppler_image_mapping_copy(nullptr);
        // Prevent unused warning if it somehow returns.
        (void)out;
      },
      ".*");
}
#endif

} // namespace