#include <gtest/gtest.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

// Declaration of the function under test
const char* SpellcheckStringV(const string& text, const vector<const char*>& words);

// Also need EditDistance for understanding, but we only test SpellcheckStringV
int EditDistance(const string& s1, const string& s2, bool allow_replacements, int max_edit_distance);

// Normal operation tests

TEST(SpellcheckStringVTest_143, ExactMatch_143) {
  vector<const char*> words;
  words.push_back("build");
  words.push_back("clean");
  words.push_back("test");
  
  const char* result = SpellcheckStringV("build", words);
  ASSERT_NE(nullptr, result);
  EXPECT_STREQ("build", result);
}

TEST(SpellcheckStringVTest_143, CloseMatch_143) {
  vector<const char*> words;
  words.push_back("build");
  words.push_back("clean");
  words.push_back("test");
  
  // "bild" is close to "build" (one deletion)
  const char* result = SpellcheckStringV("bild", words);
  ASSERT_NE(nullptr, result);
  EXPECT_STREQ("build", result);
}

TEST(SpellcheckStringVTest_143, SingleCharacterReplacement_143) {
  vector<const char*> words;
  words.push_back("build");
  words.push_back("clean");
  words.push_back("test");
  
  // "tost" is close to "test" (one replacement)
  const char* result = SpellcheckStringV("tost", words);
  ASSERT_NE(nullptr, result);
  EXPECT_STREQ("test", result);
}

TEST(SpellcheckStringVTest_143, SingleCharacterInsertion_143) {
  vector<const char*> words;
  words.push_back("build");
  words.push_back("clean");
  words.push_back("test");
  
  // "tesst" is close to "test" (one insertion)
  const char* result = SpellcheckStringV("tesst", words);
  ASSERT_NE(nullptr, result);
  EXPECT_STREQ("test", result);
}

// Boundary condition tests

TEST(SpellcheckStringVTest_143, EmptyWordList_143) {
  vector<const char*> words;
  
  const char* result = SpellcheckStringV("build", words);
  EXPECT_EQ(nullptr, result);
}

TEST(SpellcheckStringVTest_143, NoCloseMatch_143) {
  vector<const char*> words;
  words.push_back("build");
  words.push_back("clean");
  words.push_back("test");
  
  // "xyzzyplugh" is very far from any word
  const char* result = SpellcheckStringV("xyzzyplugh", words);
  EXPECT_EQ(nullptr, result);
}

TEST(SpellcheckStringVTest_143, EmptyInput_143) {
  vector<const char*> words;
  words.push_back("build");
  words.push_back("clean");
  words.push_back("test");
  
  // Empty string should match short words within edit distance 3
  const char* result = SpellcheckStringV("", words);
  // Empty string is distance 4 from "test" (4 chars), distance 5 from "build" and "clean"
  // So no match expected since all words are > 3 characters
  EXPECT_EQ(nullptr, result);
}

TEST(SpellcheckStringVTest_143, EmptyInputWithShortWords_143) {
  vector<const char*> words;
  words.push_back("a");
  words.push_back("ab");
  words.push_back("abc");
  
  // Empty string is distance 1 from "a", distance 2 from "ab", distance 3 from "abc"
  const char* result = SpellcheckStringV("", words);
  ASSERT_NE(nullptr, result);
  EXPECT_STREQ("a", result);
}

TEST(SpellcheckStringVTest_143, SingleWordList_143) {
  vector<const char*> words;
  words.push_back("hello");
  
  const char* result = SpellcheckStringV("helo", words);
  ASSERT_NE(nullptr, result);
  EXPECT_STREQ("hello", result);
}

TEST(SpellcheckStringVTest_143, ExactEditDistanceThree_143) {
  vector<const char*> words;
  words.push_back("abcdef");
  
  // "xyzdef" differs in first 3 chars -> distance 3
  const char* result = SpellcheckStringV("xyzdef", words);
  ASSERT_NE(nullptr, result);
  EXPECT_STREQ("abcdef", result);
}

TEST(SpellcheckStringVTest_143, EditDistanceFour_143) {
  vector<const char*> words;
  words.push_back("abcdef");
  
  // "xyzwef" differs in first 4 chars -> distance 4, beyond threshold
  const char* result = SpellcheckStringV("wxyzef", words);
  // "wxyzef" vs "abcdef" - a->w, b->x, c->y, d->z = 4 replacements
  EXPECT_EQ(nullptr, result);
}

TEST(SpellcheckStringVTest_143, PicksClosestAmongMultiple_143) {
  vector<const char*> words;
  words.push_back("apple");
  words.push_back("apply");
  words.push_back("ample");
  
  // "applo" is distance 1 from "apple" (o->e) and distance 1 from "apply" (o->y)
  // First one found with min distance should be returned (apple comes first)
  const char* result = SpellcheckStringV("applo", words);
  ASSERT_NE(nullptr, result);
  // Both "apple" and "apply" are distance 1, but "apple" comes first
  EXPECT_STREQ("apple", result);
}

TEST(SpellcheckStringVTest_143, PicksFirstOfTiedMatches_143) {
  vector<const char*> words;
  words.push_back("cat");
  words.push_back("bat");
  words.push_back("hat");
  
  // "dat" is distance 1 from all three, should pick "cat" (first)
  const char* result = SpellcheckStringV("dat", words);
  ASSERT_NE(nullptr, result);
  EXPECT_STREQ("cat", result);
}

TEST(SpellcheckStringVTest_143, CloserMatchLaterInList_143) {
  vector<const char*> words;
  words.push_back("xyz");
  words.push_back("build");
  
  // "buld" is closer to "build" than "xyz"
  const char* result = SpellcheckStringV("buld", words);
  ASSERT_NE(nullptr, result);
  EXPECT_STREQ("build", result);
}

TEST(SpellcheckStringVTest_143, CompletelyDifferentText_143) {
  vector<const char*> words;
  words.push_back("abcdefghij");
  words.push_back("klmnopqrst");
  
  const char* result = SpellcheckStringV("zzzzzzzzzz", words);
  EXPECT_EQ(nullptr, result);
}

TEST(SpellcheckStringVTest_143, SingleCharWords_143) {
  vector<const char*> words;
  words.push_back("a");
  words.push_back("b");
  words.push_back("c");
  
  const char* result = SpellcheckStringV("a", words);
  ASSERT_NE(nullptr, result);
  EXPECT_STREQ("a", result);
}

TEST(SpellcheckStringVTest_143, SingleCharInputSingleCharWord_143) {
  vector<const char*> words;
  words.push_back("b");
  
  // "a" vs "b" is distance 1
  const char* result = SpellcheckStringV("a", words);
  ASSERT_NE(nullptr, result);
  EXPECT_STREQ("b", result);
}

TEST(SpellcheckStringVTest_143, ThreeDeletions_143) {
  vector<const char*> words;
  words.push_back("abcdef");
  
  // "abc" is 3 deletions from "abcdef" -> distance 3
  const char* result = SpellcheckStringV("abc", words);
  ASSERT_NE(nullptr, result);
  EXPECT_STREQ("abcdef", result);
}

TEST(SpellcheckStringVTest_143, ThreeInsertions_143) {
  vector<const char*> words;
  words.push_back("abc");
  
  // "abcdef" is 3 insertions from "abc" -> distance 3
  const char* result = SpellcheckStringV("abcdef", words);
  ASSERT_NE(nullptr, result);
  EXPECT_STREQ("abc", result);
}
