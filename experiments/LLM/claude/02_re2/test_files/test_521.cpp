#include "gtest/gtest.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"

// Include the necessary structures
#include "re2/unicode_groups.h"

// Since LookupGroup is static in parse.cc, we need to access it.
// We wrap it by including the source in a namespace or re-declaring for test.
// For testing static functions, include the .cc file.
namespace re2_test_521 {
#include "re2/parse.cc"
}

using re2_test_521::re2::LookupGroup;
using re2_test_521::re2::UGroup;
using re2_test_521::re2::URange16;
using re2_test_521::re2::URange32;

class LookupGroupTest_521 : public ::testing::Test {
 protected:
  void SetUp() override {
    groups_[0] = {"Alpha", 1, nullptr, 0, nullptr, 0};
    groups_[1] = {"Beta", 1, nullptr, 0, nullptr, 0};
    groups_[2] = {"Gamma", -1, nullptr, 0, nullptr, 0};
  }

  UGroup groups_[3];
};

TEST_F(LookupGroupTest_521, FindsFirstElement_521) {
  const UGroup* result = LookupGroup("Alpha", groups_, 3);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result->name, "Alpha");
  EXPECT_EQ(result, &groups_[0]);
}

TEST_F(LookupGroupTest_521, FindsMiddleElement_521) {
  const UGroup* result = LookupGroup("Beta", groups_, 3);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result->name, "Beta");
  EXPECT_EQ(result, &groups_[1]);
}

TEST_F(LookupGroupTest_521, FindsLastElement_521) {
  const UGroup* result = LookupGroup("Gamma", groups_, 3);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result->name, "Gamma");
  EXPECT_EQ(result, &groups_[2]);
}

TEST_F(LookupGroupTest_521, ReturnsNullForNonexistentName_521) {
  const UGroup* result = LookupGroup("Delta", groups_, 3);
  EXPECT_EQ(result, nullptr);
}

TEST_F(LookupGroupTest_521, ReturnsNullForEmptyArray_521) {
  const UGroup* result = LookupGroup("Alpha", groups_, 0);
  EXPECT_EQ(result, nullptr);
}

TEST_F(LookupGroupTest_521, ReturnsNullForEmptySearchString_521) {
  const UGroup* result = LookupGroup("", groups_, 3);
  EXPECT_EQ(result, nullptr);
}

TEST_F(LookupGroupTest_521, EmptyNameMatchesEmptyGroupName_521) {
  UGroup empty_group = {"", 1, nullptr, 0, nullptr, 0};
  const UGroup* result = LookupGroup("", &empty_group, 1);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result->name, "");
}

TEST_F(LookupGroupTest_521, CaseSensitiveSearch_521) {
  const UGroup* result = LookupGroup("alpha", groups_, 3);
  EXPECT_EQ(result, nullptr);
}

TEST_F(LookupGroupTest_521, PartialNameDoesNotMatch_521) {
  const UGroup* result = LookupGroup("Alph", groups_, 3);
  EXPECT_EQ(result, nullptr);
}

TEST_F(LookupGroupTest_521, SupersetNameDoesNotMatch_521) {
  const UGroup* result = LookupGroup("Alpha1", groups_, 3);
  EXPECT_EQ(result, nullptr);
}

TEST_F(LookupGroupTest_521, SingleElementArrayFound_521) {
  UGroup single = {"Only", 1, nullptr, 0, nullptr, 0};
  const UGroup* result = LookupGroup("Only", &single, 1);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result->name, "Only");
}

TEST_F(LookupGroupTest_521, SingleElementArrayNotFound_521) {
  UGroup single = {"Only", 1, nullptr, 0, nullptr, 0};
  const UGroup* result = LookupGroup("Other", &single, 1);
  EXPECT_EQ(result, nullptr);
}

TEST_F(LookupGroupTest_521, SearchSubsetOfArray_521) {
  // Only search first 2 elements, so "Gamma" should not be found
  const UGroup* result = LookupGroup("Gamma", groups_, 2);
  EXPECT_EQ(result, nullptr);
}

TEST_F(LookupGroupTest_521, ReturnsFirstMatchWhenDuplicates_521) {
  UGroup dups[3] = {
    {"Dup", 1, nullptr, 0, nullptr, 0},
    {"Dup", 2, nullptr, 0, nullptr, 0},
    {"Other", 1, nullptr, 0, nullptr, 0},
  };
  const UGroup* result = LookupGroup("Dup", dups, 3);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, &dups[0]);
  EXPECT_EQ(result->sign, 1);
}
