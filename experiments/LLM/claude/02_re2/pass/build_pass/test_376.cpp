#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "util/utf.h"

namespace re2 {

class CharClassBuilderTest_376 : public ::testing::Test {
 protected:
  void SetUp() override {
    builder_ = new CharClassBuilder();
  }

  void TearDown() override {
    delete builder_;
  }

  CharClassBuilder* builder_;
};

// Test that a newly constructed CharClassBuilder is empty
TEST_F(CharClassBuilderTest_376, NewBuilderIsEmpty_376) {
  EXPECT_TRUE(builder_->empty());
  EXPECT_FALSE(builder_->full());
  EXPECT_EQ(0, builder_->size());
}

// Test negating an empty set results in a full set (all of [0, Runemax])
TEST_F(CharClassBuilderTest_376, NegateEmptySetBecomesFullRange_376) {
  builder_->Negate();
  EXPECT_TRUE(builder_->full());
  EXPECT_FALSE(builder_->empty());
  // After negation of empty, it should contain everything
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_TRUE(builder_->Contains(Runemax));
  EXPECT_TRUE(builder_->Contains(Runemax / 2));
}

// Test negating a full set results in an empty set
TEST_F(CharClassBuilderTest_376, NegateFullSetBecomesEmpty_376) {
  builder_->AddRange(0, Runemax);
  EXPECT_TRUE(builder_->full());
  builder_->Negate();
  EXPECT_TRUE(builder_->empty());
  EXPECT_EQ(0, builder_->size());
  EXPECT_FALSE(builder_->Contains(0));
  EXPECT_FALSE(builder_->Contains(Runemax));
}

// Test negating a single range
TEST_F(CharClassBuilderTest_376, NegateSingleMiddleRange_376) {
  // Add range [100, 200]
  builder_->AddRange(100, 200);
  EXPECT_TRUE(builder_->Contains(100));
  EXPECT_TRUE(builder_->Contains(150));
  EXPECT_TRUE(builder_->Contains(200));
  EXPECT_FALSE(builder_->Contains(99));
  EXPECT_FALSE(builder_->Contains(201));

  builder_->Negate();

  // After negation, [100, 200] should not be contained
  EXPECT_FALSE(builder_->Contains(100));
  EXPECT_FALSE(builder_->Contains(150));
  EXPECT_FALSE(builder_->Contains(200));
  // But 0-99 and 201-Runemax should be contained
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_TRUE(builder_->Contains(99));
  EXPECT_TRUE(builder_->Contains(201));
  EXPECT_TRUE(builder_->Contains(Runemax));
}

// Test negating a range starting from 0
TEST_F(CharClassBuilderTest_376, NegateRangeStartingFromZero_376) {
  builder_->AddRange(0, 100);
  builder_->Negate();

  EXPECT_FALSE(builder_->Contains(0));
  EXPECT_FALSE(builder_->Contains(50));
  EXPECT_FALSE(builder_->Contains(100));
  EXPECT_TRUE(builder_->Contains(101));
  EXPECT_TRUE(builder_->Contains(Runemax));
}

// Test negating a range ending at Runemax
TEST_F(CharClassBuilderTest_376, NegateRangeEndingAtRunemax_376) {
  builder_->AddRange(500, Runemax);
  builder_->Negate();

  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_TRUE(builder_->Contains(499));
  EXPECT_FALSE(builder_->Contains(500));
  EXPECT_FALSE(builder_->Contains(Runemax));
}

// Test double negation restores original set
TEST_F(CharClassBuilderTest_376, DoubleNegateRestoresOriginal_376) {
  builder_->AddRange(50, 100);
  builder_->AddRange(200, 300);

  // Check initial state
  EXPECT_TRUE(builder_->Contains(50));
  EXPECT_TRUE(builder_->Contains(75));
  EXPECT_TRUE(builder_->Contains(100));
  EXPECT_TRUE(builder_->Contains(250));
  EXPECT_FALSE(builder_->Contains(150));

  builder_->Negate();
  builder_->Negate();

  // Should be back to original
  EXPECT_TRUE(builder_->Contains(50));
  EXPECT_TRUE(builder_->Contains(75));
  EXPECT_TRUE(builder_->Contains(100));
  EXPECT_TRUE(builder_->Contains(250));
  EXPECT_FALSE(builder_->Contains(150));
}

// Test negating multiple disjoint ranges
TEST_F(CharClassBuilderTest_376, NegateMultipleDisjointRanges_376) {
  builder_->AddRange(10, 20);
  builder_->AddRange(30, 40);
  builder_->AddRange(50, 60);

  builder_->Negate();

  // Gaps should now be included
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_TRUE(builder_->Contains(9));
  EXPECT_FALSE(builder_->Contains(10));
  EXPECT_FALSE(builder_->Contains(15));
  EXPECT_FALSE(builder_->Contains(20));
  EXPECT_TRUE(builder_->Contains(21));
  EXPECT_TRUE(builder_->Contains(29));
  EXPECT_FALSE(builder_->Contains(30));
  EXPECT_FALSE(builder_->Contains(35));
  EXPECT_FALSE(builder_->Contains(40));
  EXPECT_TRUE(builder_->Contains(41));
  EXPECT_TRUE(builder_->Contains(49));
  EXPECT_FALSE(builder_->Contains(50));
  EXPECT_FALSE(builder_->Contains(55));
  EXPECT_FALSE(builder_->Contains(60));
  EXPECT_TRUE(builder_->Contains(61));
  EXPECT_TRUE(builder_->Contains(Runemax));
}

// Test AddRange basic functionality
TEST_F(CharClassBuilderTest_376, AddRangeBasic_376) {
  builder_->AddRange(65, 90);  // 'A' to 'Z'
  EXPECT_TRUE(builder_->Contains(65));
  EXPECT_TRUE(builder_->Contains(90));
  EXPECT_FALSE(builder_->Contains(64));
  EXPECT_FALSE(builder_->Contains(91));
  EXPECT_FALSE(builder_->empty());
}

// Test AddRange with single character
TEST_F(CharClassBuilderTest_376, AddRangeSingleChar_376) {
  builder_->AddRange(42, 42);
  EXPECT_TRUE(builder_->Contains(42));
  EXPECT_FALSE(builder_->Contains(41));
  EXPECT_FALSE(builder_->Contains(43));
}

// Test Contains on empty builder
TEST_F(CharClassBuilderTest_376, ContainsOnEmpty_376) {
  EXPECT_FALSE(builder_->Contains(0));
  EXPECT_FALSE(builder_->Contains(100));
  EXPECT_FALSE(builder_->Contains(Runemax));
}

// Test full range
TEST_F(CharClassBuilderTest_376, FullRange_376) {
  builder_->AddRange(0, Runemax);
  EXPECT_TRUE(builder_->full());
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_TRUE(builder_->Contains(Runemax));
  EXPECT_TRUE(builder_->Contains(Runemax / 2));
}

// Test RemoveAbove
TEST_F(CharClassBuilderTest_376, RemoveAbove_376) {
  builder_->AddRange(0, 1000);
  builder_->RemoveAbove(500);
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_TRUE(builder_->Contains(500));
  EXPECT_FALSE(builder_->Contains(501));
  EXPECT_FALSE(builder_->Contains(1000));
}

// Test RemoveAbove on empty builder
TEST_F(CharClassBuilderTest_376, RemoveAboveOnEmpty_376) {
  builder_->RemoveAbove(100);
  EXPECT_TRUE(builder_->empty());
}

// Test Copy
TEST_F(CharClassBuilderTest_376, CopyProducesEquivalentBuilder_376) {
  builder_->AddRange(10, 20);
  builder_->AddRange(30, 40);

  CharClassBuilder* copy = builder_->Copy();
  ASSERT_NE(copy, nullptr);

  EXPECT_TRUE(copy->Contains(10));
  EXPECT_TRUE(copy->Contains(15));
  EXPECT_TRUE(copy->Contains(20));
  EXPECT_TRUE(copy->Contains(30));
  EXPECT_TRUE(copy->Contains(35));
  EXPECT_TRUE(copy->Contains(40));
  EXPECT_FALSE(copy->Contains(25));

  delete copy;
}

// Test AddCharClass
TEST_F(CharClassBuilderTest_376, AddCharClassMerges_376) {
  builder_->AddRange(10, 20);

  CharClassBuilder other;
  other.AddRange(30, 40);

  builder_->AddCharClass(&other);

  EXPECT_TRUE(builder_->Contains(15));
  EXPECT_TRUE(builder_->Contains(35));
  EXPECT_FALSE(builder_->Contains(25));
}

// Test negating a single point range at 0
TEST_F(CharClassBuilderTest_376, NegateSinglePointAtZero_376) {
  builder_->AddRange(0, 0);
  builder_->Negate();
  EXPECT_FALSE(builder_->Contains(0));
  EXPECT_TRUE(builder_->Contains(1));
  EXPECT_TRUE(builder_->Contains(Runemax));
}

// Test negating a single point range at Runemax
TEST_F(CharClassBuilderTest_376, NegateSinglePointAtRunemax_376) {
  builder_->AddRange(Runemax, Runemax);
  builder_->Negate();
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_TRUE(builder_->Contains(Runemax - 1));
  EXPECT_FALSE(builder_->Contains(Runemax));
}

// Test negating range [0, Runemax-1]
TEST_F(CharClassBuilderTest_376, NegateAlmostFullRange_376) {
  builder_->AddRange(0, Runemax - 1);
  builder_->Negate();
  EXPECT_FALSE(builder_->Contains(0));
  EXPECT_FALSE(builder_->Contains(Runemax - 1));
  EXPECT_TRUE(builder_->Contains(Runemax));
}

// Test negating range [1, Runemax]
TEST_F(CharClassBuilderTest_376, NegateAlmostFullRangeExceptZero_376) {
  builder_->AddRange(1, Runemax);
  builder_->Negate();
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_FALSE(builder_->Contains(1));
  EXPECT_FALSE(builder_->Contains(Runemax));
}

// Test overlapping AddRange calls
TEST_F(CharClassBuilderTest_376, OverlappingRanges_376) {
  builder_->AddRange(10, 30);
  builder_->AddRange(20, 40);
  EXPECT_TRUE(builder_->Contains(10));
  EXPECT_TRUE(builder_->Contains(25));
  EXPECT_TRUE(builder_->Contains(40));
  EXPECT_FALSE(builder_->Contains(9));
  EXPECT_FALSE(builder_->Contains(41));
}

// Test negating after overlapping ranges
TEST_F(CharClassBuilderTest_376, NegateOverlappingRanges_376) {
  builder_->AddRange(10, 30);
  builder_->AddRange(20, 40);
  builder_->Negate();
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_TRUE(builder_->Contains(9));
  EXPECT_FALSE(builder_->Contains(10));
  EXPECT_FALSE(builder_->Contains(25));
  EXPECT_FALSE(builder_->Contains(40));
  EXPECT_TRUE(builder_->Contains(41));
  EXPECT_TRUE(builder_->Contains(Runemax));
}

// Test iterator on empty builder
TEST_F(CharClassBuilderTest_376, IteratorOnEmpty_376) {
  EXPECT_EQ(builder_->begin(), builder_->end());
}

// Test size on various configurations
TEST_F(CharClassBuilderTest_376, SizeAfterAddRange_376) {
  EXPECT_EQ(0, builder_->size());
  builder_->AddRange(10, 20);
  EXPECT_GT(builder_->size(), 0);
}

// Test Negate then RemoveAbove interaction
TEST_F(CharClassBuilderTest_376, NegateAndRemoveAbove_376) {
  builder_->AddRange(100, 200);
  builder_->Negate();
  builder_->RemoveAbove(50);

  // After negate: [0,99] and [201, Runemax]
  // After RemoveAbove(50): [0, 50]
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_TRUE(builder_->Contains(50));
  EXPECT_FALSE(builder_->Contains(51));
  EXPECT_FALSE(builder_->Contains(100));
  EXPECT_FALSE(builder_->Contains(Runemax));
}

// Test adjacent ranges
TEST_F(CharClassBuilderTest_376, AdjacentRanges_376) {
  builder_->AddRange(10, 20);
  builder_->AddRange(21, 30);
  EXPECT_TRUE(builder_->Contains(10));
  EXPECT_TRUE(builder_->Contains(20));
  EXPECT_TRUE(builder_->Contains(21));
  EXPECT_TRUE(builder_->Contains(30));
}

// Test negating adjacent ranges
TEST_F(CharClassBuilderTest_376, NegateAdjacentRanges_376) {
  builder_->AddRange(10, 20);
  builder_->AddRange(21, 30);
  builder_->Negate();
  EXPECT_TRUE(builder_->Contains(0));
  EXPECT_TRUE(builder_->Contains(9));
  EXPECT_FALSE(builder_->Contains(10));
  EXPECT_FALSE(builder_->Contains(20));
  EXPECT_FALSE(builder_->Contains(21));
  EXPECT_FALSE(builder_->Contains(30));
  EXPECT_TRUE(builder_->Contains(31));
  EXPECT_TRUE(builder_->Contains(Runemax));
}

}  // namespace re2
