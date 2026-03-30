// File: edit_distance_test_165.cc

#include "edit_distance.h"
#include "string_piece.h"

#include "gtest/gtest.h"

// We treat EditDistance as a black box and only test via its public interface.

/**
 * TEST_ID: 165
 * Basic sanity: identical strings should have distance 0
 * when replacements are allowed.
 */
TEST(EditDistanceTest_165, IdenticalStringsAllowReplacements_165) {
  StringPiece s1("ninja");
  StringPiece s2("ninja");

  int result = EditDistance(s1, s2, /*allow_replacements=*/true,
                            /*max_edit_distance=*/0);

  EXPECT_EQ(0, result);
}

/**
 * TEST_ID: 165
 * Identical strings should also have distance 0
 * when replacements are not allowed.
 */
TEST(EditDistanceTest_165, IdenticalStringsDisallowReplacements_165) {
  StringPiece s1("ninja");
  StringPiece s2("ninja");

  int result = EditDistance(s1, s2, /*allow_replacements=*/false,
                            /*max_edit_distance=*/0);

  EXPECT_EQ(0, result);
}

/**
 * TEST_ID: 165
 * Distance between an empty string and a non-empty string
 * should be the length of the non-empty one (insertions/deletions).
 */
TEST(EditDistanceTest_165, OneEmptyString_165) {
  StringPiece empty("");
  StringPiece s("abc");

  int result_allow = EditDistance(empty, s, /*allow_replacements=*/true,
                                  /*max_edit_distance=*/0);
  int result_disallow = EditDistance(empty, s, /*allow_replacements=*/false,
                                     /*max_edit_distance=*/0);

  EXPECT_EQ(3, result_allow);
  EXPECT_EQ(3, result_disallow);
}

/**
 * TEST_ID: 165
 * Single differing character:
 *  - With replacements allowed: distance should be 1.
 *  - Without replacements: needs delete+insert => distance > 1 (we know it's 2).
 */
TEST(EditDistanceTest_165, SingleReplacementEffectOfAllowReplacements_165) {
  StringPiece s1("cat");
  StringPiece s2("cut");

  int with_replacements =
      EditDistance(s1, s2, /*allow_replacements=*/true,
                   /*max_edit_distance=*/0);
  int without_replacements =
      EditDistance(s1, s2, /*allow_replacements=*/false,
                   /*max_edit_distance=*/0);

  EXPECT_EQ(1, with_replacements);
  EXPECT_EQ(2, without_replacements);
}

/**
 * TEST_ID: 165
 * Pure insertion/deletion: "cat" -> "cats" should have distance 1.
 */
TEST(EditDistanceTest_165, SingleInsertionOrDeletion_165) {
  StringPiece s1("cat");
  StringPiece s2("cats");

  int result_allow = EditDistance(s1, s2, /*allow_replacements=*/true,
                                  /*max_edit_distance=*/0);
  int result_disallow = EditDistance(s1, s2, /*allow_replacements=*/false,
                                     /*max_edit_distance=*/0);

  EXPECT_EQ(1, result_allow);
  EXPECT_EQ(1, result_disallow);
}

/**
 * TEST_ID: 165
 * max_edit_distance == 0 is treated as "no limit":
 * the function should return the actual edit distance even if it's > 0.
 */
TEST(EditDistanceTest_165, MaxEditDistanceZeroBehavesAsNoLimit_165) {
  StringPiece s1("a");
  StringPiece s2("b");

  int result_allow = EditDistance(s1, s2, /*allow_replacements=*/true,
                                  /*max_edit_distance=*/0);
  int result_disallow = EditDistance(s1, s2, /*allow_replacements=*/false,
                                     /*max_edit_distance=*/0);

  // Known small-case distances.
  EXPECT_EQ(1, result_allow);
  EXPECT_EQ(2, result_disallow);
}

/**
 * TEST_ID: 165
 * When the true edit distance is greater than max_edit_distance,
 * the function returns max_edit_distance + 1.
 */
TEST(EditDistanceTest_165, MaxEditDistanceExceededReturnsMaxPlusOne_165) {
  StringPiece s1("aaaaa");
  StringPiece s2("bbbbb");

  // With replacements, each char differs => distance is 5.
  int max_edit_distance = 2;

  int result = EditDistance(s1, s2, /*allow_replacements=*/true,
                            max_edit_distance);

  EXPECT_EQ(max_edit_distance + 1, result);
}

/**
 * TEST_ID: 165
 * When the true edit distance is less than or equal to max_edit_distance,
 * the function returns the actual distance.
 */
TEST(EditDistanceTest_165, MaxEditDistanceNotExceededReturnsActual_165) {
  StringPiece s1("aaaaa");
  StringPiece s2("bbbbb");

  // True distance is 5 (all chars replaced).
  int max_edit_distance_equal = 5;
  int max_edit_distance_greater = 10;

  int result_equal = EditDistance(s1, s2, /*allow_replacements=*/true,
                                  max_edit_distance_equal);
  int result_greater = EditDistance(s1, s2, /*allow_replacements=*/true,
                                    max_edit_distance_greater);

  EXPECT_EQ(5, result_equal);
  EXPECT_EQ(5, result_greater);
}
