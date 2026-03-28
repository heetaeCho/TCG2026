#include "gtest/gtest.h"
#include "edit_distance.h"
#include "string_piece.h"

// Forward declaration if not in a header
int EditDistance(const StringPiece& s1, const StringPiece& s2,
                bool allow_replacements = true, int max_edit_distance = 0);

// Test identical strings
TEST(EditDistanceTest_165, IdenticalStrings_165) {
  EXPECT_EQ(0, EditDistance("abc", "abc"));
}

// Test both empty strings
TEST(EditDistanceTest_165, BothEmptyStrings_165) {
  EXPECT_EQ(0, EditDistance("", ""));
}

// Test first string empty
TEST(EditDistanceTest_165, FirstStringEmpty_165) {
  EXPECT_EQ(3, EditDistance("", "abc"));
}

// Test second string empty
TEST(EditDistanceTest_165, SecondStringEmpty_165) {
  EXPECT_EQ(3, EditDistance("abc", ""));
}

// Test single character difference (replacement)
TEST(EditDistanceTest_165, SingleReplacementAllowed_165) {
  EXPECT_EQ(1, EditDistance("abc", "adc", true));
}

// Test single insertion
TEST(EditDistanceTest_165, SingleInsertion_165) {
  EXPECT_EQ(1, EditDistance("abc", "abcd", true));
}

// Test single deletion
TEST(EditDistanceTest_165, SingleDeletion_165) {
  EXPECT_EQ(1, EditDistance("abcd", "abc", true));
}

// Test completely different strings
TEST(EditDistanceTest_165, CompletelyDifferentStrings_165) {
  EXPECT_EQ(3, EditDistance("abc", "xyz", true));
}

// Test replacement not allowed - characters differ
TEST(EditDistanceTest_165, ReplacementNotAllowed_165) {
  // Without replacements, changing one char requires delete + insert = 2
  EXPECT_EQ(2, EditDistance("abc", "adc", false));
}

// Test replacement not allowed - identical strings
TEST(EditDistanceTest_165, ReplacementNotAllowedIdentical_165) {
  EXPECT_EQ(0, EditDistance("abc", "abc", false));
}

// Test replacement not allowed - insertion
TEST(EditDistanceTest_165, ReplacementNotAllowedInsertion_165) {
  EXPECT_EQ(1, EditDistance("abc", "abcd", false));
}

// Test max_edit_distance - within limit
TEST(EditDistanceTest_165, MaxEditDistanceWithinLimit_165) {
  EXPECT_EQ(1, EditDistance("abc", "adc", true, 5));
}

// Test max_edit_distance - exceeds limit
TEST(EditDistanceTest_165, MaxEditDistanceExceeded_165) {
  int max_dist = 1;
  int result = EditDistance("abc", "xyz", true, max_dist);
  EXPECT_GT(result, max_dist);
  EXPECT_EQ(max_dist + 1, result);
}

// Test max_edit_distance - exactly at limit
TEST(EditDistanceTest_165, MaxEditDistanceExactlyAtLimit_165) {
  EXPECT_EQ(1, EditDistance("abc", "adc", true, 1));
}

// Test max_edit_distance of 0 means no limit
TEST(EditDistanceTest_165, MaxEditDistanceZeroMeansNoLimit_165) {
  EXPECT_EQ(3, EditDistance("abc", "xyz", true, 0));
}

// Test single character strings - same
TEST(EditDistanceTest_165, SingleCharSame_165) {
  EXPECT_EQ(0, EditDistance("a", "a"));
}

// Test single character strings - different
TEST(EditDistanceTest_165, SingleCharDifferent_165) {
  EXPECT_EQ(1, EditDistance("a", "b", true));
}

// Test single char vs empty
TEST(EditDistanceTest_165, SingleCharVsEmpty_165) {
  EXPECT_EQ(1, EditDistance("a", ""));
  EXPECT_EQ(1, EditDistance("", "a"));
}

// Test longer strings with multiple operations
TEST(EditDistanceTest_165, LongerStringsMultipleOperations_165) {
  EXPECT_EQ(3, EditDistance("kitten", "sitting", true));
}

// Test strings of different lengths
TEST(EditDistanceTest_165, DifferentLengths_165) {
  EXPECT_EQ(2, EditDistance("ab", "abcd", true));
}

// Test replacement not allowed with completely different strings
TEST(EditDistanceTest_165, ReplacementNotAllowedCompletelyDifferent_165) {
  // "ab" -> "cd": need to delete a, delete b, insert c, insert d = 4
  // Or with proper DP: distance should be 4
  int result = EditDistance("ab", "cd", false);
  EXPECT_EQ(4, result);
}

// Test with StringPiece constructed from std::string
TEST(EditDistanceTest_165, StringPieceFromStdString_165) {
  std::string s1 = "hello";
  std::string s2 = "hallo";
  EXPECT_EQ(1, EditDistance(StringPiece(s1), StringPiece(s2), true));
}

// Test with StringPiece with explicit length
TEST(EditDistanceTest_165, StringPieceWithExplicitLength_165) {
  const char* s1 = "hello world";
  const char* s2 = "hello";
  EXPECT_EQ(0, EditDistance(StringPiece(s1, 5), StringPiece(s2, 5)));
}

// Test symmetry of edit distance
TEST(EditDistanceTest_165, Symmetry_165) {
  int d1 = EditDistance("abc", "xyz", true);
  int d2 = EditDistance("xyz", "abc", true);
  EXPECT_EQ(d1, d2);
}

// Test prefix relationship
TEST(EditDistanceTest_165, PrefixRelationship_165) {
  EXPECT_EQ(3, EditDistance("abc", "abcdef", true));
}

// Test suffix relationship
TEST(EditDistanceTest_165, SuffixRelationship_165) {
  EXPECT_EQ(3, EditDistance("def", "abcdef", true));
}

// Test max_edit_distance with early termination
TEST(EditDistanceTest_165, MaxEditDistanceEarlyTermination_165) {
  // Large difference, small max
  int result = EditDistance("abcdefgh", "12345678", true, 2);
  EXPECT_EQ(3, result);  // max_edit_distance + 1
}

// Test transposition-like scenario
TEST(EditDistanceTest_165, TranspositionLike_165) {
  // "ab" -> "ba" with replacements: 2 replacements
  EXPECT_EQ(2, EditDistance("ab", "ba", true));
}

// Test without replacements for transposition
TEST(EditDistanceTest_165, TranspositionWithoutReplacements_165) {
  // "ab" -> "ba" without replacements: delete+insert for each = but DP should give 2 (delete a, insert a at end, or similar)
  int result = EditDistance("ab", "ba", false);
  // Without replacement: need delete+insert operations
  EXPECT_GE(result, 2);
}

// Test repeated characters
TEST(EditDistanceTest_165, RepeatedCharacters_165) {
  EXPECT_EQ(0, EditDistance("aaa", "aaa"));
  EXPECT_EQ(1, EditDistance("aaa", "aaaa"));
  EXPECT_EQ(1, EditDistance("aaa", "aa"));
}
