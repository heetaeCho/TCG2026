#include <gtest/gtest.h>
#include <string>
#include <string_view>

// Include the header that defines TagVocabulary
#include "tags_int.hpp"

using namespace Exiv2::Internal;

// Test that a key ending with the vocabulary string matches
TEST(TagVocabularyTest_1319, ExactMatchReturnsTrue_1319) {
    TagVocabulary tv{"photo"};
    EXPECT_TRUE(tv == std::string_view("photo"));
}

// Test that a key ending with the vocabulary string (with prefix) matches
TEST(TagVocabularyTest_1319, KeyEndingWithVocReturnsTrue_1319) {
    TagVocabulary tv{"photo"};
    EXPECT_TRUE(tv == std::string_view("myprefix/photo"));
}

// Test that a key not ending with the vocabulary string does not match
TEST(TagVocabularyTest_1319, KeyNotEndingWithVocReturnsFalse_1319) {
    TagVocabulary tv{"photo"};
    EXPECT_FALSE(tv == std::string_view("photosuffix"));
}

// Test that a completely different key does not match
TEST(TagVocabularyTest_1319, CompletelyDifferentKeyReturnsFalse_1319) {
    TagVocabulary tv{"photo"};
    EXPECT_FALSE(tv == std::string_view("video"));
}

// Test with empty vocabulary string - every string ends with empty string
TEST(TagVocabularyTest_1319, EmptyVocMatchesAnyKey_1319) {
    TagVocabulary tv{""};
    EXPECT_TRUE(tv == std::string_view("anything"));
    EXPECT_TRUE(tv == std::string_view(""));
}

// Test with empty key and non-empty vocabulary
TEST(TagVocabularyTest_1319, EmptyKeyWithNonEmptyVocReturnsFalse_1319) {
    TagVocabulary tv{"photo"};
    EXPECT_FALSE(tv == std::string_view(""));
}

// Test with key shorter than vocabulary
TEST(TagVocabularyTest_1319, KeyShorterThanVocReturnsFalse_1319) {
    TagVocabulary tv{"photograph"};
    EXPECT_FALSE(tv == std::string_view("photo"));
}

// Test with key that contains vocabulary in the middle but not at the end
TEST(TagVocabularyTest_1319, VocInMiddleOfKeyReturnsFalse_1319) {
    TagVocabulary tv{"photo"};
    EXPECT_FALSE(tv == std::string_view("photo/image"));
}

// Test with single character vocabulary
TEST(TagVocabularyTest_1319, SingleCharVocMatchesKeyEndingWithChar_1319) {
    TagVocabulary tv{"x"};
    EXPECT_TRUE(tv == std::string_view("suffix_x"));
    EXPECT_TRUE(tv == std::string_view("x"));
    EXPECT_FALSE(tv == std::string_view("xa"));
}

// Test with key that is a longer suffix match
TEST(TagVocabularyTest_1319, LongKeySuffixMatch_1319) {
    TagVocabulary tv{"Type"};
    EXPECT_TRUE(tv == std::string_view("dc.Type"));
    EXPECT_TRUE(tv == std::string_view("exif.ImageType"));
    EXPECT_FALSE(tv == std::string_view("Typex"));
}

// Test case sensitivity
TEST(TagVocabularyTest_1319, CaseSensitiveComparison_1319) {
    TagVocabulary tv{"Photo"};
    EXPECT_TRUE(tv == std::string_view("myPhoto"));
    EXPECT_FALSE(tv == std::string_view("myphoto"));
    EXPECT_FALSE(tv == std::string_view("myPHOTO"));
}

// Test with special characters in vocabulary
TEST(TagVocabularyTest_1319, SpecialCharactersInVoc_1319) {
    TagVocabulary tv{"/photo"};
    EXPECT_TRUE(tv == std::string_view("prefix/photo"));
    EXPECT_FALSE(tv == std::string_view("prefixphoto"));
}

// Test with spaces in vocabulary
TEST(TagVocabularyTest_1319, SpacesInVoc_1319) {
    TagVocabulary tv{" end"};
    EXPECT_TRUE(tv == std::string_view("the end"));
    EXPECT_FALSE(tv == std::string_view("theend"));
}

// Test both empty key and empty vocabulary
TEST(TagVocabularyTest_1319, BothEmptyReturnsTrue_1319) {
    TagVocabulary tv{""};
    EXPECT_TRUE(tv == std::string_view(""));
}
