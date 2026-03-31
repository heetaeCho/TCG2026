#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "util/utf.h"

namespace re2 {

class CharClassBuilderRemoveAboveTest_375 : public ::testing::Test {
 protected:
  void SetUp() override {
    builder_ = new CharClassBuilder();
  }

  void TearDown() override {
    delete builder_;
  }

  CharClassBuilder* builder_;
};

// Test RemoveAbove with Runemax - should be a no-op since r >= Runemax
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveRunemax_375) {
  builder_->AddRange(0, Runemax);
  builder_->RemoveAbove(Runemax);
  // Should still contain Runemax since RemoveAbove returns early for r >= Runemax
  EXPECT_TRUE(builder_->Contains(Runemax));
  EXPECT_TRUE(builder_->Contains(0));
}

// Test RemoveAbove with value larger than Runemax - should be a no-op
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveGreaterThanRunemax_375) {
  builder_->AddRange(0, Runemax);
  builder_->RemoveAbove(Runemax + 1);
  EXPECT_TRUE(builder_->Contains(Runemax));
}

// Test RemoveAbove with 0 - should remove everything above 0
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveZero_375) {
  builder_->AddRange(0, 1000);
  builder_->RemoveAbove(0);
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_FALSE(builder_->Contains(1));
  EXPECT_FALSE(builder_->Contains(1000));
}

// Test RemoveAbove on an empty builder
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveOnEmpty_375) {
  builder_->RemoveAbove(100);
  EXPECT_TRUE(builder_->empty());
}

// Test RemoveAbove removes characters above the threshold
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveBasic_375) {
  builder_->AddRange(0, 500);
  builder_->RemoveAbove(250);
  EXPECT_TRUE(builder_->Contains(250));
  EXPECT_FALSE(builder_->Contains(251));
  EXPECT_FALSE(builder_->Contains(500));
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_TRUE(builder_->Contains(100));
}

// Test RemoveAbove with threshold in lowercase letter range
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveInLowercaseRange_375) {
  builder_->AddRange('a', 'z');
  builder_->RemoveAbove('m');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('m'));
  EXPECT_FALSE(builder_->Contains('n'));
  EXPECT_FALSE(builder_->Contains('z'));
}

// Test RemoveAbove with threshold in uppercase letter range
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveInUppercaseRange_375) {
  builder_->AddRange('A', 'Z');
  builder_->RemoveAbove('M');
  EXPECT_TRUE(builder_->Contains('A'));
  EXPECT_TRUE(builder_->Contains('M'));
  EXPECT_FALSE(builder_->Contains('N'));
  EXPECT_FALSE(builder_->Contains('Z'));
}

// Test RemoveAbove below 'A' clears upper_
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveBelowUppercase_375) {
  builder_->AddRange('A', 'Z');
  builder_->RemoveAbove('@');  // '@' is one below 'A'
  EXPECT_FALSE(builder_->Contains('A'));
  EXPECT_FALSE(builder_->Contains('Z'));
}

// Test RemoveAbove below 'a' clears lower_
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveBelowLowercase_375) {
  builder_->AddRange('a', 'z');
  builder_->RemoveAbove('`');  // '`' is one below 'a'
  EXPECT_FALSE(builder_->Contains('a'));
  EXPECT_FALSE(builder_->Contains('z'));
}

// Test RemoveAbove with multiple disjoint ranges
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveMultipleRanges_375) {
  builder_->AddRange(10, 20);
  builder_->AddRange(30, 40);
  builder_->AddRange(50, 60);
  builder_->RemoveAbove(35);
  EXPECT_TRUE(builder_->Contains(10));
  EXPECT_TRUE(builder_->Contains(20));
  EXPECT_TRUE(builder_->Contains(30));
  EXPECT_TRUE(builder_->Contains(35));
  EXPECT_FALSE(builder_->Contains(36));
  EXPECT_FALSE(builder_->Contains(50));
}

// Test RemoveAbove at exact range boundary (hi of a range)
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveAtRangeBoundary_375) {
  builder_->AddRange(10, 20);
  builder_->AddRange(30, 40);
  builder_->RemoveAbove(20);
  EXPECT_TRUE(builder_->Contains(10));
  EXPECT_TRUE(builder_->Contains(20));
  EXPECT_FALSE(builder_->Contains(21));
  EXPECT_FALSE(builder_->Contains(30));
}

// Test RemoveAbove at exact range boundary (lo of a range)
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveAtRangeStart_375) {
  builder_->AddRange(10, 20);
  builder_->AddRange(30, 40);
  builder_->RemoveAbove(30);
  EXPECT_TRUE(builder_->Contains(10));
  EXPECT_TRUE(builder_->Contains(20));
  EXPECT_TRUE(builder_->Contains(30));
  EXPECT_FALSE(builder_->Contains(31));
  EXPECT_FALSE(builder_->Contains(40));
}

// Test RemoveAbove with full range
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveFullRange_375) {
  builder_->AddRange(0, Runemax);
  EXPECT_TRUE(builder_->full());
  builder_->RemoveAbove(127);
  EXPECT_FALSE(builder_->Contains(128));
  EXPECT_TRUE(builder_->Contains(127));
  EXPECT_TRUE(builder_->Contains(0));
}

// Test RemoveAbove between disjoint ranges (in the gap)
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveInGapBetweenRanges_375) {
  builder_->AddRange(10, 20);
  builder_->AddRange(50, 60);
  builder_->RemoveAbove(35);
  EXPECT_TRUE(builder_->Contains(10));
  EXPECT_TRUE(builder_->Contains(20));
  EXPECT_FALSE(builder_->Contains(50));
  EXPECT_FALSE(builder_->Contains(60));
}

// Test RemoveAbove with value below all ranges
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveBelowAllRanges_375) {
  builder_->AddRange(100, 200);
  builder_->RemoveAbove(50);
  EXPECT_FALSE(builder_->Contains(100));
  EXPECT_FALSE(builder_->Contains(200));
  EXPECT_FALSE(builder_->Contains(50));
}

// Test that RemoveAbove preserves characters at exactly r
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAbovePreservesExactValue_375) {
  builder_->AddRange(100, 200);
  builder_->RemoveAbove(150);
  EXPECT_TRUE(builder_->Contains(150));
  EXPECT_TRUE(builder_->Contains(100));
  EXPECT_FALSE(builder_->Contains(151));
}

// Test RemoveAbove called multiple times
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveCalledMultipleTimes_375) {
  builder_->AddRange(0, 1000);
  builder_->RemoveAbove(500);
  EXPECT_TRUE(builder_->Contains(500));
  EXPECT_FALSE(builder_->Contains(501));
  builder_->RemoveAbove(250);
  EXPECT_TRUE(builder_->Contains(250));
  EXPECT_FALSE(builder_->Contains(251));
  EXPECT_FALSE(builder_->Contains(500));
}

// Test RemoveAbove with both upper and lowercase ranges present
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveBothCaseRanges_375) {
  builder_->AddRange('A', 'Z');
  builder_->AddRange('a', 'z');
  builder_->RemoveAbove('m');
  EXPECT_TRUE(builder_->Contains('A'));
  EXPECT_TRUE(builder_->Contains('Z'));
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('m'));
  EXPECT_FALSE(builder_->Contains('n'));
  EXPECT_FALSE(builder_->Contains('z'));
}

// Test RemoveAbove with threshold below 'A' removes both upper and lower
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveBelowAllLetters_375) {
  builder_->AddRange('A', 'Z');
  builder_->AddRange('a', 'z');
  builder_->RemoveAbove(0x30);  // below 'A' (0x41)
  EXPECT_FALSE(builder_->Contains('A'));
  EXPECT_FALSE(builder_->Contains('Z'));
  EXPECT_FALSE(builder_->Contains('a'));
  EXPECT_FALSE(builder_->Contains('z'));
}

// Test RemoveAbove with Unicode range
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveUnicodeRange_375) {
  builder_->AddRange(0x4E00, 0x9FFF);  // CJK Unified Ideographs
  builder_->RemoveAbove(0x5000);
  EXPECT_TRUE(builder_->Contains(0x4E00));
  EXPECT_TRUE(builder_->Contains(0x5000));
  EXPECT_FALSE(builder_->Contains(0x5001));
  EXPECT_FALSE(builder_->Contains(0x9FFF));
}

// Test size changes after RemoveAbove
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAboveAffectsSize_375) {
  builder_->AddRange(0, 99);
  int size_before = builder_->size();
  builder_->RemoveAbove(49);
  int size_after = builder_->size();
  EXPECT_LT(size_after, size_before);
}

}  // namespace re2
