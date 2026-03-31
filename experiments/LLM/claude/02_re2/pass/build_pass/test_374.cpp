#include "gtest/gtest.h"
#include "re2/regexp.h"

namespace re2 {

class CharClassBuilderTest_374 : public ::testing::Test {
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
TEST_F(CharClassBuilderTest_374, NewBuilderIsEmpty_374) {
  EXPECT_TRUE(builder_->empty());
  EXPECT_EQ(builder_->size(), 0);
  EXPECT_FALSE(builder_->full());
}

// Test adding a single range and checking containment
TEST_F(CharClassBuilderTest_374, AddRangeAndContains_374) {
  builder_->AddRange('a', 'z');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('m'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_FALSE(builder_->Contains('A'));
  EXPECT_FALSE(builder_->Contains('0'));
}

// Test that builder is not empty after adding a range
TEST_F(CharClassBuilderTest_374, NotEmptyAfterAddRange_374) {
  builder_->AddRange('a', 'z');
  EXPECT_FALSE(builder_->empty());
  EXPECT_GT(builder_->size(), 0);
}

// Test adding multiple ranges
TEST_F(CharClassBuilderTest_374, AddMultipleRanges_374) {
  builder_->AddRange('a', 'z');
  builder_->AddRange('A', 'Z');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('Z'));
  EXPECT_FALSE(builder_->Contains('0'));
}

// Test adding a single character range
TEST_F(CharClassBuilderTest_374, AddSingleCharRange_374) {
  builder_->AddRange('x', 'x');
  EXPECT_TRUE(builder_->Contains('x'));
  EXPECT_FALSE(builder_->Contains('w'));
  EXPECT_FALSE(builder_->Contains('y'));
}

// Test Copy produces an equivalent CharClassBuilder
TEST_F(CharClassBuilderTest_374, CopyProducesEquivalentBuilder_374) {
  builder_->AddRange('a', 'z');
  builder_->AddRange('0', '9');

  CharClassBuilder* copy = builder_->Copy();
  ASSERT_NE(copy, nullptr);

  EXPECT_TRUE(copy->Contains('a'));
  EXPECT_TRUE(copy->Contains('z'));
  EXPECT_TRUE(copy->Contains('5'));
  EXPECT_FALSE(copy->Contains('A'));

  EXPECT_EQ(builder_->size(), copy->size());

  delete copy;
}

// Test that modifying the copy does not affect the original
TEST_F(CharClassBuilderTest_374, CopyIsIndependent_374) {
  builder_->AddRange('a', 'z');

  CharClassBuilder* copy = builder_->Copy();
  copy->AddRange('0', '9');

  EXPECT_FALSE(builder_->Contains('5'));
  EXPECT_TRUE(copy->Contains('5'));

  delete copy;
}

// Test Copy of empty builder
TEST_F(CharClassBuilderTest_374, CopyEmptyBuilder_374) {
  CharClassBuilder* copy = builder_->Copy();
  ASSERT_NE(copy, nullptr);
  EXPECT_TRUE(copy->empty());
  EXPECT_EQ(copy->size(), 0);
  delete copy;
}

// Test Negate
TEST_F(CharClassBuilderTest_374, Negate_374) {
  builder_->AddRange('a', 'z');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_FALSE(builder_->Contains('A'));

  builder_->Negate();
  EXPECT_FALSE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('A'));
}

// Test double Negate returns to original
TEST_F(CharClassBuilderTest_374, DoubleNegate_374) {
  builder_->AddRange('a', 'z');
  builder_->Negate();
  builder_->Negate();
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('z'));
  EXPECT_FALSE(builder_->Contains('A'));
}

// Test RemoveAbove
TEST_F(CharClassBuilderTest_374, RemoveAbove_374) {
  builder_->AddRange(0, 1000);
  EXPECT_TRUE(builder_->Contains(500));
  EXPECT_TRUE(builder_->Contains(1000));

  builder_->RemoveAbove(500);
  EXPECT_TRUE(builder_->Contains(500));
  EXPECT_FALSE(builder_->Contains(501));
  EXPECT_FALSE(builder_->Contains(1000));
}

// Test RemoveAbove with value below all ranges
TEST_F(CharClassBuilderTest_374, RemoveAboveBelowAllRanges_374) {
  builder_->AddRange(100, 200);
  builder_->RemoveAbove(50);
  EXPECT_FALSE(builder_->Contains(100));
  EXPECT_FALSE(builder_->Contains(150));
  EXPECT_TRUE(builder_->empty() || !builder_->Contains(100));
}

// Test AddCharClass merges another builder
TEST_F(CharClassBuilderTest_374, AddCharClass_374) {
  builder_->AddRange('a', 'z');

  CharClassBuilder other;
  other.AddRange('0', '9');

  builder_->AddCharClass(&other);

  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('5'));
}

// Test AddCharClass with empty builder
TEST_F(CharClassBuilderTest_374, AddCharClassEmpty_374) {
  builder_->AddRange('a', 'z');
  int originalSize = builder_->size();

  CharClassBuilder other;
  builder_->AddCharClass(&other);

  EXPECT_EQ(builder_->size(), originalSize);
}

// Test iterator begin and end
TEST_F(CharClassBuilderTest_374, IteratorBeginEndEmpty_374) {
  EXPECT_EQ(builder_->begin(), builder_->end());
}

// Test iterator with ranges
TEST_F(CharClassBuilderTest_374, IteratorWithRanges_374) {
  builder_->AddRange('a', 'z');
  EXPECT_NE(builder_->begin(), builder_->end());

  int count = 0;
  for (auto it = builder_->begin(); it != builder_->end(); ++it) {
    count++;
  }
  EXPECT_GT(count, 0);
}

// Test Contains on empty builder returns false
TEST_F(CharClassBuilderTest_374, ContainsOnEmpty_374) {
  EXPECT_FALSE(builder_->Contains('a'));
  EXPECT_FALSE(builder_->Contains(0));
}

// Test overlapping ranges
TEST_F(CharClassBuilderTest_374, OverlappingRanges_374) {
  builder_->AddRange('a', 'm');
  builder_->AddRange('j', 'z');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('j'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test adjacent ranges
TEST_F(CharClassBuilderTest_374, AdjacentRanges_374) {
  builder_->AddRange('a', 'm');
  builder_->AddRange('n', 'z');
  EXPECT_TRUE(builder_->Contains('a'));
  EXPECT_TRUE(builder_->Contains('m'));
  EXPECT_TRUE(builder_->Contains('n'));
  EXPECT_TRUE(builder_->Contains('z'));
}

// Test FoldsASCII with no ASCII letters
TEST_F(CharClassBuilderTest_374, FoldsASCIINoLetters_374) {
  builder_->AddRange('0', '9');
  // FoldsASCII checks whether the class folds ASCII - without both cases, likely false
  // We just verify it doesn't crash and returns a bool
  bool result = builder_->FoldsASCII();
  (void)result;  // We can't predict exact value without knowing implementation
}

// Test FoldsASCII with both cases
TEST_F(CharClassBuilderTest_374, FoldsASCIIWithBothCases_374) {
  builder_->AddRange('a', 'z');
  builder_->AddRange('A', 'Z');
  bool result = builder_->FoldsASCII();
  EXPECT_TRUE(result);
}

// Test Negate of empty builder creates full builder
TEST_F(CharClassBuilderTest_374, NegateEmpty_374) {
  EXPECT_TRUE(builder_->empty());
  builder_->Negate();
  EXPECT_TRUE(builder_->full());
}

// Test full after negating empty
TEST_F(CharClassBuilderTest_374, FullAfterNegateEmpty_374) {
  builder_->Negate();
  EXPECT_TRUE(builder_->full());
  EXPECT_FALSE(builder_->empty());
}

// Test GetCharClass returns non-null
TEST_F(CharClassBuilderTest_374, GetCharClassNonNull_374) {
  builder_->AddRange('a', 'z');
  CharClass* cc = builder_->GetCharClass();
  EXPECT_NE(cc, nullptr);
  cc->Delete();
}

// Test GetCharClass on empty builder
TEST_F(CharClassBuilderTest_374, GetCharClassEmpty_374) {
  CharClass* cc = builder_->GetCharClass();
  EXPECT_NE(cc, nullptr);
  cc->Delete();
}

// Test adding range where lo > hi (boundary)
TEST_F(CharClassBuilderTest_374, AddRangeLoGreaterThanHi_374) {
  bool result = builder_->AddRange('z', 'a');
  // When lo > hi, the range should be empty or ignored
  EXPECT_FALSE(builder_->Contains('a'));
  EXPECT_FALSE(builder_->Contains('m'));
  EXPECT_FALSE(builder_->Contains('z'));
}

// Test RemoveAbove on empty builder
TEST_F(CharClassBuilderTest_374, RemoveAboveOnEmpty_374) {
  builder_->RemoveAbove(100);
  EXPECT_TRUE(builder_->empty());
}

// Test Copy preserves containment after multiple operations
TEST_F(CharClassBuilderTest_374, CopyAfterMultipleOperations_374) {
  builder_->AddRange('a', 'z');
  builder_->AddRange('0', '9');
  builder_->RemoveAbove('m');

  CharClassBuilder* copy = builder_->Copy();
  ASSERT_NE(copy, nullptr);

  EXPECT_TRUE(copy->Contains('a'));
  EXPECT_TRUE(copy->Contains('m'));
  EXPECT_EQ(builder_->Contains('n'), copy->Contains('n'));
  EXPECT_EQ(builder_->Contains('9'), copy->Contains('9'));

  delete copy;
}

// Test AddRange returns bool
TEST_F(CharClassBuilderTest_374, AddRangeReturnValue_374) {
  bool first = builder_->AddRange('a', 'z');
  // First add of a range should typically return true (new runes added)
  EXPECT_TRUE(first);

  // Adding the same range again might return false (no new runes)
  bool second = builder_->AddRange('a', 'z');
  EXPECT_FALSE(second);
}

}  // namespace re2
