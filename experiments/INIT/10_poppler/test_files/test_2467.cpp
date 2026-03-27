// poppler_rectangle_find_get_match_continued_test_2467.cc

#include <gtest/gtest.h>

#include <glib.h>

#include "poppler-page.h"
#include "poppler-private.h"

extern "C" {
gboolean poppler_rectangle_find_get_match_continued(const PopplerRectangle *rectangle);
}

class PopplerRectangleFindGetMatchContinuedTest_2467 : public ::testing::Test {};

// Normal / error case: nullptr should be rejected and return false.
TEST_F(PopplerRectangleFindGetMatchContinuedTest_2467, NullRectangleReturnsFalse_2467) {
  EXPECT_FALSE(poppler_rectangle_find_get_match_continued(nullptr));
}

// Normal operation: returns true when match_continued is true.
TEST_F(PopplerRectangleFindGetMatchContinuedTest_2467, ReturnsTrueWhenMatchContinuedTrue_2467) {
  PopplerRectangleExtended ext{};
  ext.match_continued = true;
  ext.ignored_hyphen = false;

  const auto *rect = reinterpret_cast<const PopplerRectangle *>(&ext);
  EXPECT_TRUE(poppler_rectangle_find_get_match_continued(rect));
}

// Normal operation / boundary: returns false when match_continued is false.
TEST_F(PopplerRectangleFindGetMatchContinuedTest_2467, ReturnsFalseWhenMatchContinuedFalse_2467) {
  PopplerRectangleExtended ext{};
  ext.match_continued = false;
  ext.ignored_hyphen = true; // should not affect result

  const auto *rect = reinterpret_cast<const PopplerRectangle *>(&ext);
  EXPECT_FALSE(poppler_rectangle_find_get_match_continued(rect));
}

// Boundary-ish: calling multiple times should be stable for the same input pointer.
TEST_F(PopplerRectangleFindGetMatchContinuedTest_2467, MultipleCallsAreConsistent_2467) {
  PopplerRectangleExtended ext{};
  ext.match_continued = true;
  ext.ignored_hyphen = true;

  const auto *rect = reinterpret_cast<const PopplerRectangle *>(&ext);

  EXPECT_TRUE(poppler_rectangle_find_get_match_continued(rect));
  EXPECT_TRUE(poppler_rectangle_find_get_match_continued(rect));

  ext.match_continued = false;
  EXPECT_FALSE(poppler_rectangle_find_get_match_continued(rect));
}