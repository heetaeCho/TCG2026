// File: ./TestProjects/yaml-cpp/test/null_same_test_588.cpp

#include <gtest/gtest.h>

#include <cstddef>

// Include the implementation directly because the function has internal linkage (`static`)
// and is not link-visible from other translation units.
#include "TestProjects/yaml-cpp/src/null.cpp"

class SameTest_588 : public ::testing::Test {};

TEST_F(SameTest_588, ExactMatchReturnsTrue_588) {
  const char* s = "null";
  EXPECT_TRUE(YAML::same(s, 4u, "null"));
}

TEST_F(SameTest_588, DifferentContentReturnsFalse_588) {
  const char* s = "nulL";
  EXPECT_FALSE(YAML::same(s, 4u, "null"));
}

TEST_F(SameTest_588, SizeTooSmallReturnsFalseEvenIfPrefixMatches_588) {
  const char* s = "null";
  EXPECT_FALSE(YAML::same(s, 3u, "null"));  // "nul" vs "null"
}

TEST_F(SameTest_588, SizeTooLargeReturnsFalseEvenIfPrefixMatches_588) {
  const char* s = "null";
  EXPECT_FALSE(YAML::same(s, 5u, "null"));  // size mismatch
}

TEST_F(SameTest_588, InputWithoutNullTerminatorStillMatchesWhenSizeMatches_588) {
  const char buf[] = {'n', 'u', 'l', 'l'};  // no '\0'
  EXPECT_TRUE(YAML::same(buf, 4u, "null"));
}

TEST_F(SameTest_588, EmbeddedNullDoesNotAffectComparisonBeyondProvidedSize_588) {
  const char buf[] = {'n', 'u', 'l', 'l', '\0', 'x'};
  EXPECT_TRUE(YAML::same(buf, 4u, "null"));   // compares first 4 chars
  EXPECT_FALSE(YAML::same(buf, 5u, "null"));  // size mismatch vs literal length
}

TEST_F(SameTest_588, EmptyLiteralMatchesOnlyWhenSizeIsZero_588) {
  const char* s = "anything";
  EXPECT_TRUE(YAML::same(s, 0u, ""));   // empty literal, size 0
  EXPECT_FALSE(YAML::same(s, 1u, ""));  // size mismatch
}

TEST_F(SameTest_588, CaseSensitivityIsRespected_588) {
  const char* s = "Null";
  EXPECT_FALSE(YAML::same(s, 4u, "null"));
}