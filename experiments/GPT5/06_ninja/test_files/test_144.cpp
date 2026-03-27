// File: ./TestProjects/ninja/src/util_spellcheck_string_test.cc

#include "util.h"

#include <gtest/gtest.h>
#include <vector>

// NOTE:
// These tests treat both SpellcheckString and SpellcheckStringV as black boxes.
// We only verify that the variadic wrapper SpellcheckString forwards its
// arguments correctly to SpellcheckStringV by comparing observable outputs.

// TEST_ID: 144
TEST(SpellcheckStringTest_144, ForwardsNoWords_144) {
  const char* text = "no candidates";

  // Call the variadic wrapper with only the terminating nullptr.
  const char* result = SpellcheckString(text, static_cast<const char*>(nullptr));

  // Expected behavior: equivalent to calling SpellcheckStringV with an empty list.
  std::vector<const char*> words;  // empty
  const char* expected = SpellcheckStringV(text, words);

  EXPECT_STREQ(expected, result);
}

// TEST_ID: 144
TEST(SpellcheckStringTest_144, ForwardsSingleWord_144) {
  const char* text = "single candidate";
  const char* w1 = "candidate";

  const char* result = SpellcheckString(text, w1, static_cast<const char*>(nullptr));

  std::vector<const char*> words;
  words.push_back(w1);
  const char* expected = SpellcheckStringV(text, words);

  EXPECT_STREQ(expected, result);
}

// TEST_ID: 144
TEST(SpellcheckStringTest_144, ForwardsMultipleWordsInOrder_144) {
  const char* text = "multiple candidates";
  const char* w1 = "alpha";
  const char* w2 = "beta";
  const char* w3 = "gamma";

  const char* result =
      SpellcheckString(text, w1, w2, w3, static_cast<const char*>(nullptr));

  std::vector<const char*> words;
  words.push_back(w1);
  words.push_back(w2);
  words.push_back(w3);
  const char* expected = SpellcheckStringV(text, words);

  // If SpellcheckString changes the order or loses elements,
  // the result is likely to differ from SpellcheckStringV with our expected list.
  EXPECT_STREQ(expected, result);
}

// TEST_ID: 144
TEST(SpellcheckStringTest_144, StopsAtNullSentinel_144) {
  const char* text = "sentinel handling";
  const char* w1 = "first";
  const char* w2 = "second";

  // Pass extra arguments after the first nullptr. According to the interface
  // contract, SpellcheckString should only read until the first nullptr.
  const char* result = SpellcheckString(
      text,
      w1,
      static_cast<const char*>(nullptr),
      w2,  // should be ignored by SpellcheckString
      static_cast<const char*>(nullptr));

  // Expected vector contains only the word before the first nullptr.
  std::vector<const char*> words;
  words.push_back(w1);
  const char* expected = SpellcheckStringV(text, words);

  EXPECT_STREQ(expected, result);
}
