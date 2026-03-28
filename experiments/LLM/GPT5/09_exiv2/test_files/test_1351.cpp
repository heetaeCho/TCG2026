// SPDX-License-Identifier: MIT
// File: test_http_stringToDict_1351.cpp

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

#include <string>

// Include the implementation unit to access the file-local (static) function.
// This keeps the test black-box at the interface level (input/output), while
// still allowing us to call the internal helper under test.
#include "http.cpp"

namespace {

using Exiv2::Dictionary;

static bool DictContainsKey(const Dictionary& d, const std::string& key) {
  return d.find(key) != d.end();
}

static std::string DictValueOrEmpty(const Dictionary& d, const std::string& key) {
  const auto it = d.find(key);
  return (it == d.end()) ? std::string{} : it->second;
}

}  // namespace

TEST(StringToDictTest_1351, SingleToken_NoComma_1351) {
  const Dictionary d = stringToDict("alpha");

  EXPECT_EQ(d.size(), 1u);
  EXPECT_TRUE(DictContainsKey(d, "alpha"));
  EXPECT_EQ(DictValueOrEmpty(d, "alpha"), "alpha");
}

TEST(StringToDictTest_1351, MultipleTokens_CommaSeparated_1351) {
  const Dictionary d = stringToDict("a,b,c");

  EXPECT_EQ(d.size(), 3u);
  EXPECT_TRUE(DictContainsKey(d, "a"));
  EXPECT_TRUE(DictContainsKey(d, "b"));
  EXPECT_TRUE(DictContainsKey(d, "c"));
  EXPECT_EQ(DictValueOrEmpty(d, "a"), "a");
  EXPECT_EQ(DictValueOrEmpty(d, "b"), "b");
  EXPECT_EQ(DictValueOrEmpty(d, "c"), "c");
}

TEST(StringToDictTest_1351, SpacesAreIgnoredEverywhere_1351) {
  const Dictionary d = stringToDict("  a , b  ,c d  ,  e");

  // Tokens are produced with spaces removed.
  EXPECT_EQ(d.size(), 4u);
  EXPECT_TRUE(DictContainsKey(d, "a"));
  EXPECT_TRUE(DictContainsKey(d, "b"));
  EXPECT_TRUE(DictContainsKey(d, "cd"));
  EXPECT_TRUE(DictContainsKey(d, "e"));
  EXPECT_EQ(DictValueOrEmpty(d, "cd"), "cd");
}

TEST(StringToDictTest_1351, EmptyString_ProducesSingleEmptyToken_1351) {
  const Dictionary d = stringToDict("");

  EXPECT_EQ(d.size(), 1u);
  EXPECT_TRUE(DictContainsKey(d, ""));
  EXPECT_EQ(DictValueOrEmpty(d, ""), "");
}

TEST(StringToDictTest_1351, SpacesOnly_ProducesSingleEmptyToken_1351) {
  const Dictionary d = stringToDict("     ");

  EXPECT_EQ(d.size(), 1u);
  EXPECT_TRUE(DictContainsKey(d, ""));
  EXPECT_EQ(DictValueOrEmpty(d, ""), "");
}

TEST(StringToDictTest_1351, LeadingComma_ProducesEmptyTokenEntry_1351) {
  const Dictionary d = stringToDict(",a");

  EXPECT_EQ(d.size(), 2u);
  EXPECT_TRUE(DictContainsKey(d, ""));
  EXPECT_TRUE(DictContainsKey(d, "a"));
  EXPECT_EQ(DictValueOrEmpty(d, ""), "");
  EXPECT_EQ(DictValueOrEmpty(d, "a"), "a");
}

TEST(StringToDictTest_1351, TrailingComma_ProducesEmptyTokenEntry_1351) {
  const Dictionary d = stringToDict("a,b,");

  EXPECT_EQ(d.size(), 3u);
  EXPECT_TRUE(DictContainsKey(d, "a"));
  EXPECT_TRUE(DictContainsKey(d, "b"));
  EXPECT_TRUE(DictContainsKey(d, ""));
}

TEST(StringToDictTest_1351, ConsecutiveCommas_ProduceEmptyTokenEntry_1351) {
  const Dictionary d = stringToDict("a,,b");

  EXPECT_EQ(d.size(), 3u);
  EXPECT_TRUE(DictContainsKey(d, "a"));
  EXPECT_TRUE(DictContainsKey(d, ""));
  EXPECT_TRUE(DictContainsKey(d, "b"));
}

TEST(StringToDictTest_1351, DuplicateTokens_CollapseToSingleDictionaryKey_1351) {
  const Dictionary d = stringToDict("dup,dup");

  // Dictionary keys are unique; duplicates should not increase size.
  EXPECT_EQ(d.size(), 1u);
  EXPECT_TRUE(DictContainsKey(d, "dup"));
  EXPECT_EQ(DictValueOrEmpty(d, "dup"), "dup");
}

TEST(StringToDictTest_1351, TokenWithOnlySpacesBetweenCommas_BecomesEmptyKey_1351) {
  const Dictionary d = stringToDict("a,   ,b");

  EXPECT_EQ(d.size(), 3u);
  EXPECT_TRUE(DictContainsKey(d, "a"));
  EXPECT_TRUE(DictContainsKey(d, ""));
  EXPECT_TRUE(DictContainsKey(d, "b"));
}