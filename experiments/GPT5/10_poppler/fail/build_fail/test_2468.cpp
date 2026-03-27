// poppler-rectangle-find-get-ignored-hyphen-test.cc
//
// Unit tests for poppler_rectangle_find_get_ignored_hyphen()
// TEST_ID: 2468

#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include "./TestProjects/poppler/glib/poppler-page.h"
}

// Forward declare the function under test (implemented in poppler-page.cc)
extern "C" gboolean poppler_rectangle_find_get_ignored_hyphen(const PopplerRectangle *rectangle);

// Re-declare the extended struct layout used by the implementation (from poppler-private.h).
// This is a dependency type the function explicitly relies on via reinterpret_cast.
struct PopplerRectangleExtended {
  bool match_continued;
  bool ignored_hyphen;
};

class PopplerRectangleFindGetIgnoredHyphenTest_2468 : public ::testing::Test {};

TEST_F(PopplerRectangleFindGetIgnoredHyphenTest_2468, NullRectangleReturnsFalse_2468) {
  // Observable error-case behavior: g_return_val_if_fail(..., false)
  EXPECT_FALSE(poppler_rectangle_find_get_ignored_hyphen(nullptr));
}

TEST_F(PopplerRectangleFindGetIgnoredHyphenTest_2468, ReturnsTrueWhenIgnoredHyphenSet_2468) {
  PopplerRectangleExtended ext{};
  ext.match_continued = false;
  ext.ignored_hyphen = true;

  // Pass the address as PopplerRectangle*, as required by the interface.
  const auto *rect = reinterpret_cast<const PopplerRectangle *>(&ext);

  EXPECT_TRUE(poppler_rectangle_find_get_ignored_hyphen(rect));
}

TEST_F(PopplerRectangleFindGetIgnoredHyphenTest_2468, ReturnsFalseWhenIgnoredHyphenCleared_2468) {
  PopplerRectangleExtended ext{};
  ext.match_continued = true;   // unrelated field; set non-default to ensure no coupling in test inputs
  ext.ignored_hyphen = false;

  const auto *rect = reinterpret_cast<const PopplerRectangle *>(&ext);

  EXPECT_FALSE(poppler_rectangle_find_get_ignored_hyphen(rect));
}

TEST_F(PopplerRectangleFindGetIgnoredHyphenTest_2468, DifferentMatchContinuedValuesDoNotAffectResult_2468) {
  PopplerRectangleExtended ext1{};
  ext1.match_continued = false;
  ext1.ignored_hyphen = true;

  PopplerRectangleExtended ext2{};
  ext2.match_continued = true;
  ext2.ignored_hyphen = true;

  const auto *rect1 = reinterpret_cast<const PopplerRectangle *>(&ext1);
  const auto *rect2 = reinterpret_cast<const PopplerRectangle *>(&ext2);

  // Boundary/robustness: toggling adjacent boolean should not change observed value for ignored_hyphen.
  EXPECT_TRUE(poppler_rectangle_find_get_ignored_hyphen(rect1));
  EXPECT_TRUE(poppler_rectangle_find_get_ignored_hyphen(rect2));
}

TEST_F(PopplerRectangleFindGetIgnoredHyphenTest_2468, WorksWithConstRectanglePointer_2468) {
  const PopplerRectangleExtended ext{true, false};
  const auto *rect = reinterpret_cast<const PopplerRectangle *>(&ext);

  // Boundary: const correctness at the callsite.
  EXPECT_FALSE(poppler_rectangle_find_get_ignored_hyphen(rect));
}