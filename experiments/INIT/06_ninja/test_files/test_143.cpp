// util_spellcheckstringv_test.cc

#include "gtest/gtest.h"
#include "util.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class SpellcheckStringVTest_143 : public ::testing::Test {};

// Verifies that when no candidate words are provided, the function returns NULL.
TEST_F(SpellcheckStringVTest_143, ReturnsNullWhenWordsEmpty_143) {
  const string text = "anything";
  vector<const char*> words;  // empty

  const char* result = SpellcheckStringV(text, words);

  EXPECT_EQ(result, nullptr);
}

// Verifies that an exact match in the candidate list is returned.
TEST_F(SpellcheckStringVTest_143, ReturnsExactMatchWhenAvailable_143) {
  const string text = "bar";
  vector<const char*> words;
  words.push_back("foo");
  words.push_back("bar");
  words.push_back("baz");

  const char* result = SpellcheckStringV(text, words);

  ASSERT_NE(result, nullptr);
  EXPECT_STREQ("bar", result);
}

// Verifies that the closest candidate by edit distance is chosen.
TEST_F(SpellcheckStringVTest_143, ChoosesClosestMatchByEditDistance_143) {
  const string text = "hello";
  vector<const char*> words;
  words.push_back("hell");   // edit distance 1 (insertion)
  words.push_back("hello");  // edit distance 0 (exact match)
  words.push_back("help");   // edit distance > 0

  const char* result = SpellcheckStringV(text, words);

  ASSERT_NE(result, nullptr);
  EXPECT_STREQ("hello", result);
}

// Verifies that when multiple candidates have the same minimal edit distance,
// the first such candidate in the list is returned.
TEST_F(SpellcheckStringVTest_143, ReturnsFirstCandidateOnDistanceTie_143) {
  const string text = "bat";
  vector<const char*> words;
  words.push_back("bar");  // distance 1 (r -> t)
  words.push_back("baz");  // distance 1 (z -> t)

  const char* result = SpellcheckStringV(text, words);

  ASSERT_NE(result, nullptr);
  // Expect the first candidate with minimal distance to be chosen.
  EXPECT_EQ(result, words[0]);
  EXPECT_STREQ("bar", result);
}

// Verifies that a candidate at exactly the maximum allowed edit distance
// is still considered a valid suggestion.
TEST_F(SpellcheckStringVTest_143, AcceptsCandidateAtMaxEditDistance_143) {
  // "abc" -> "def": three replacements => edit distance 3 (at the threshold)
  const string text = "abc";
  vector<const char*> words;
  words.push_back("def");

  const char* result = SpellcheckStringV(text, words);

  ASSERT_NE(result, nullptr);
  EXPECT_STREQ("def", result);
}

// Verifies that when all candidates are farther than the maximum allowed
// edit distance, the function returns NULL.
TEST_F(SpellcheckStringVTest_143, ReturnsNullWhenAllCandidatesTooFar_143) {
  const string text = "short";
  vector<const char*> words;
  words.push_back("averyverylongword");
  words.push_back("anotherextremelylongword");

  const char* result = SpellcheckStringV(text, words);

  EXPECT_EQ(result, nullptr);
}
