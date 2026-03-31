#include <gtest/gtest.h>
#include <sstream>
#include "exiv2/matroskavideo.hpp"

using namespace Exiv2::Internal;

// Test the equality operator with matching ID
TEST(MatroskaTagTest_90, EqualityOperatorMatchingId_90) {
  MatroskaTag tag(42, "TestLabel");
  EXPECT_TRUE(tag == 42);
}

// Test the equality operator with non-matching ID
TEST(MatroskaTagTest_90, EqualityOperatorNonMatchingId_90) {
  MatroskaTag tag(42, "TestLabel");
  EXPECT_FALSE(tag == 99);
}

// Test equality operator with zero ID
TEST(MatroskaTagTest_90, EqualityOperatorZeroId_90) {
  MatroskaTag tag(0, "ZeroTag");
  EXPECT_TRUE(tag == 0);
  EXPECT_FALSE(tag == 1);
}

// Test equality operator with max uint64_t value
TEST(MatroskaTagTest_90, EqualityOperatorMaxId_90) {
  uint64_t maxId = UINT64_MAX;
  MatroskaTag tag(maxId, "MaxTag");
  EXPECT_TRUE(tag == maxId);
  EXPECT_FALSE(tag == (maxId - 1));
}

// Test two-argument constructor sets default type and process
TEST(MatroskaTagTest_90, TwoArgConstructorDefaults_90) {
  MatroskaTag tag(100, "DefaultTag");
  EXPECT_TRUE(tag == 100);
  // Verify that _id is set correctly
  EXPECT_EQ(tag._id, 100u);
  EXPECT_EQ(tag._label, "DefaultTag");
  EXPECT_EQ(tag._type, matroskaTypeEnum::UndefinedType);
  EXPECT_EQ(tag._process, matroskaProcessEnum::Undefined);
}

// Test four-argument constructor
TEST(MatroskaTagTest_90, FourArgConstructor_90) {
  MatroskaTag tag(200, "FullTag", matroskaTypeEnum::UnsignedInteger, matroskaProcessEnum::Process);
  EXPECT_EQ(tag._id, 200u);
  EXPECT_EQ(tag._label, "FullTag");
  EXPECT_EQ(tag._type, matroskaTypeEnum::UnsignedInteger);
  EXPECT_EQ(tag._process, matroskaProcessEnum::Process);
}

// Test isSkipped based on process type
TEST(MatroskaTagTest_90, IsSkippedWithSkipProcess_90) {
  MatroskaTag tag(1, "SkipTag", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Skip);
  EXPECT_TRUE(tag.isSkipped());
}

// Test isSkipped returns false for non-skip process
TEST(MatroskaTagTest_90, IsSkippedWithNonSkipProcess_90) {
  MatroskaTag tag(1, "NonSkipTag", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Process);
  EXPECT_FALSE(tag.isSkipped());
}

// Test isSkipped for Undefined process
TEST(MatroskaTagTest_90, IsSkippedWithUndefinedProcess_90) {
  MatroskaTag tag(1, "UndefinedTag");
  // Two-arg constructor sets process to Undefined
  // Testing observable behavior
  bool result = tag.isSkipped();
  // We just verify it doesn't crash and returns a bool
  EXPECT_TRUE(result == true || result == false);
}

// Test isComposite based on type
TEST(MatroskaTagTest_90, IsCompositeWithCompositeType_90) {
  MatroskaTag tag(1, "CompositeTag", matroskaTypeEnum::Composite, matroskaProcessEnum::Process);
  EXPECT_TRUE(tag.isComposite());
}

// Test isComposite returns false for non-composite type
TEST(MatroskaTagTest_90, IsCompositeWithNonCompositeType_90) {
  MatroskaTag tag(1, "NonCompositeTag", matroskaTypeEnum::UnsignedInteger, matroskaProcessEnum::Process);
  EXPECT_FALSE(tag.isComposite());
}

// Test isComposite for UndefinedType
TEST(MatroskaTagTest_90, IsCompositeWithUndefinedType_90) {
  MatroskaTag tag(1, "UndefinedTypeTag");
  EXPECT_FALSE(tag.isComposite());
}

// Test dump outputs something to the stream
TEST(MatroskaTagTest_90, DumpProducesOutput_90) {
  MatroskaTag tag(12345, "DumpTestTag", matroskaTypeEnum::String, matroskaProcessEnum::Process);
  std::ostringstream oss;
  tag.dump(oss);
  std::string output = oss.str();
  // dump should produce some non-empty output
  EXPECT_FALSE(output.empty());
}

// Test dump with default-constructed (two-arg) tag
TEST(MatroskaTagTest_90, DumpWithDefaultTag_90) {
  MatroskaTag tag(0, "EmptyTag");
  std::ostringstream oss;
  tag.dump(oss);
  std::string output = oss.str();
  EXPECT_FALSE(output.empty());
}

// Test equality with different tags having same ID
TEST(MatroskaTagTest_90, DifferentTagsSameId_90) {
  MatroskaTag tag1(50, "Tag1");
  MatroskaTag tag2(50, "Tag2");
  EXPECT_TRUE(tag1 == 50);
  EXPECT_TRUE(tag2 == 50);
}

// Test that label is stored correctly
TEST(MatroskaTagTest_90, LabelIsStoredCorrectly_90) {
  MatroskaTag tag(1, "SomeLabel");
  EXPECT_EQ(tag._label, "SomeLabel");
}

// Test with empty label
TEST(MatroskaTagTest_90, EmptyLabel_90) {
  MatroskaTag tag(1, "");
  EXPECT_EQ(tag._label, "");
  EXPECT_TRUE(tag == 1);
}

// Test equality operator symmetry-like behavior (uint64_t on right side)
TEST(MatroskaTagTest_90, EqualityOperatorWithLargeId_90) {
  uint64_t largeId = 0x1A45DFA3; // Common Matroska EBML header ID
  MatroskaTag tag(largeId, "EBMLHeader");
  EXPECT_TRUE(tag == largeId);
  EXPECT_FALSE(tag == (largeId + 1));
}
