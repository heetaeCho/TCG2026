// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_tagvocabulary_operator_eq_1319.cpp
//
// Unit tests for Exiv2::Internal::TagVocabulary::operator==
// Interface under test (black-box): bool operator==(std::string_view key) const;
//
// TEST_ID: 1319

#include <gtest/gtest.h>

#include <string>
#include <string_view>

#include "tags_int.hpp"

namespace {

class TagVocabularyTest_1319 : public ::testing::Test {
 protected:
  Exiv2::Internal::TagVocabulary MakeVoc(std::string_view voc) {
    Exiv2::Internal::TagVocabulary tv;
    tv.voc_ = voc;
    return tv;
  }
};

TEST_F(TagVocabularyTest_1319, ReturnsTrueWhenKeyEndsWithVocabularySuffix_1319) {
  auto tv = MakeVoc("xml");
  EXPECT_TRUE(tv == std::string_view("http://example.com/ns/xml"));
  EXPECT_TRUE(tv == std::string_view("xml"));  // exact match should also end with
}

TEST_F(TagVocabularyTest_1319, ReturnsFalseWhenKeyDoesNotEndWithVocabularySuffix_1319) {
  auto tv = MakeVoc("xml");
  EXPECT_FALSE(tv == std::string_view("http://example.com/ns/xm"));
  EXPECT_FALSE(tv == std::string_view("http://example.com/ns/xml2"));
  EXPECT_FALSE(tv == std::string_view("http://example.com/ns/xmll"));
}

TEST_F(TagVocabularyTest_1319, BoundaryEmptyVocabularyMatchesAnyKey_1319) {
  // Boundary condition: empty suffix should match any string (including empty),
  // because "ends_with" with empty suffix is defined to be true.
  auto tv = MakeVoc(std::string_view{});
  EXPECT_TRUE(tv == std::string_view("anything"));
  EXPECT_TRUE(tv == std::string_view(""));
}

TEST_F(TagVocabularyTest_1319, BoundaryEmptyKeyMatchesOnlyWhenVocabularyEmpty_1319) {
  auto nonEmpty = MakeVoc("x");
  EXPECT_FALSE(nonEmpty == std::string_view(""));

  auto emptyVoc = MakeVoc(std::string_view{});
  EXPECT_TRUE(emptyVoc == std::string_view(""));
}

TEST_F(TagVocabularyTest_1319, BoundaryKeyShorterThanVocabularyReturnsFalse_1319) {
  auto tv = MakeVoc("longsuffix");
  EXPECT_FALSE(tv == std::string_view("short"));
  EXPECT_FALSE(tv == std::string_view("longsuf"));  // still shorter
}

TEST_F(TagVocabularyTest_1319, HandlesEmbeddedNullsInKeyAndVocabulary_1319) {
  // std::string_view can contain '\0' in the middle; ensure comparison uses length-aware semantics.
  const std::string vocStr(std::string("a\0b", 3));
  const std::string keyEndsWith(std::string("xxa\0b", 5));
  const std::string keyNotEndsWith(std::string("xxa\0c", 5));

  auto tv = MakeVoc(std::string_view(vocStr.data(), vocStr.size()));

  EXPECT_TRUE(tv == std::string_view(keyEndsWith.data(), keyEndsWith.size()));
  EXPECT_FALSE(tv == std::string_view(keyNotEndsWith.data(), keyNotEndsWith.size()));
}

TEST_F(TagVocabularyTest_1319, IsCaseSensitive_1319) {
  auto tv = MakeVoc("XML");
  EXPECT_TRUE(tv == std::string_view("prefixXML"));
  EXPECT_FALSE(tv == std::string_view("prefixxml"));
}

}  // namespace