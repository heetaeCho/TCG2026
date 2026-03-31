#include <gtest/gtest.h>
#include <cstdint>
#include <vector>
#include <set>

// We need to include the relevant headers from the re2 project
#include "re2/prog.h"

namespace re2 {

// Test fixture for ByteMapBuilder
class ByteMapBuilderTest_409 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a freshly constructed ByteMapBuilder produces a valid bytemap
// with Build() without any Mark/Merge calls.
TEST_F(ByteMapBuilderTest_409, DefaultBuild_409) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  
  // With no marks, all bytes should map to the same value
  // bytemap_range should be at least 1 (one equivalence class)
  EXPECT_GE(bytemap_range, 1);
  
  // All entries should be valid (within [0, bytemap_range))
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test marking a single byte range and building
TEST_F(ByteMapBuilderTest_409, SingleMarkAndBuild_409) {
  ByteMapBuilder builder;
  builder.Mark(0, 0);  // Mark just byte 0
  builder.Merge();
  
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  
  // Byte 0 should be in a different class than byte 1 (likely)
  // At minimum, all values should be valid
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test marking the full range [0, 255]
TEST_F(ByteMapBuilderTest_409, FullRangeMark_409) {
  ByteMapBuilder builder;
  builder.Mark(0, 255);
  builder.Merge();
  
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test marking two disjoint ranges
TEST_F(ByteMapBuilderTest_409, TwoDisjointRanges_409) {
  ByteMapBuilder builder;
  builder.Mark(0, 10);
  builder.Mark(20, 30);
  builder.Merge();
  
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  
  // Bytes within [0,10] should map to the same class
  for (int i = 1; i <= 10; i++) {
    EXPECT_EQ(bytemap[0], bytemap[i]);
  }
  
  // Bytes within [20,30] should map to the same class
  for (int i = 21; i <= 30; i++) {
    EXPECT_EQ(bytemap[20], bytemap[i]);
  }
  
  // All values should be valid
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test marking overlapping ranges
TEST_F(ByteMapBuilderTest_409, OverlappingRanges_409) {
  ByteMapBuilder builder;
  builder.Mark(10, 50);
  builder.Mark(30, 70);
  builder.Merge();
  
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test marking adjacent ranges
TEST_F(ByteMapBuilderTest_409, AdjacentRanges_409) {
  ByteMapBuilder builder;
  builder.Mark(0, 127);
  builder.Mark(128, 255);
  builder.Merge();
  
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test marking a single byte
TEST_F(ByteMapBuilderTest_409, SingleByteMark_409) {
  ByteMapBuilder builder;
  builder.Mark(100, 100);
  builder.Merge();
  
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  
  // bytemap_range should reflect that byte 100 is distinguished
  EXPECT_GE(bytemap_range, 2);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test multiple marks followed by merge
TEST_F(ByteMapBuilderTest_409, MultipleMarksBeforeMerge_409) {
  ByteMapBuilder builder;
  builder.Mark(65, 90);   // uppercase letters
  builder.Mark(97, 122);  // lowercase letters
  builder.Mark(48, 57);   // digits
  builder.Merge();
  
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  
  // All uppercase letters should be in the same class
  for (int i = 66; i <= 90; i++) {
    EXPECT_EQ(bytemap[65], bytemap[i]);
  }
  
  // All lowercase letters should be in the same class
  for (int i = 98; i <= 122; i++) {
    EXPECT_EQ(bytemap[97], bytemap[i]);
  }
  
  // All digits should be in the same class
  for (int i = 49; i <= 57; i++) {
    EXPECT_EQ(bytemap[48], bytemap[i]);
  }
  
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test boundary: Mark(0, 0) - first byte only
TEST_F(ByteMapBuilderTest_409, BoundaryFirstByte_409) {
  ByteMapBuilder builder;
  builder.Mark(0, 0);
  builder.Merge();
  
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 2);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test boundary: Mark(255, 255) - last byte only
TEST_F(ByteMapBuilderTest_409, BoundaryLastByte_409) {
  ByteMapBuilder builder;
  builder.Mark(255, 255);
  builder.Merge();
  
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 2);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test that multiple merge calls work correctly
TEST_F(ByteMapBuilderTest_409, MultipleMergeCalls_409) {
  ByteMapBuilder builder;
  builder.Mark(10, 20);
  builder.Merge();
  builder.Mark(30, 40);
  builder.Merge();
  
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test that bytes outside any marked range are grouped together
TEST_F(ByteMapBuilderTest_409, UnmarkedBytesGrouped_409) {
  ByteMapBuilder builder;
  builder.Mark(5, 5);
  builder.Merge();
  
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  
  // Bytes that are not near any boundary should be in the same class
  // e.g., bytes 6 through 254 should all be in the same class
  for (int i = 7; i <= 254; i++) {
    EXPECT_EQ(bytemap[6], bytemap[i]);
  }
}

// Test many small ranges
TEST_F(ByteMapBuilderTest_409, ManySmallRanges_409) {
  ByteMapBuilder builder;
  for (int i = 0; i < 256; i += 2) {
    builder.Mark(i, i);
  }
  builder.Merge();
  
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test that bytemap_range is bounded by 256
TEST_F(ByteMapBuilderTest_409, BytemapRangeBounded_409) {
  ByteMapBuilder builder;
  // Mark every individual byte as its own range
  for (int i = 0; i < 256; i++) {
    builder.Mark(i, i);
  }
  builder.Merge();
  
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  EXPECT_LE(bytemap_range, 256);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test merge with no marks does not crash
TEST_F(ByteMapBuilderTest_409, MergeWithNoMarks_409) {
  ByteMapBuilder builder;
  builder.Merge();  // Should be safe
  
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
}

// Test that identical ranges marked multiple times don't change the result
TEST_F(ByteMapBuilderTest_409, DuplicateRanges_409) {
  ByteMapBuilder builder1;
  builder1.Mark(10, 50);
  builder1.Merge();
  
  uint8_t bytemap1[256];
  int bytemap_range1 = 0;
  builder1.Build(bytemap1, &bytemap_range1);
  
  ByteMapBuilder builder2;
  builder2.Mark(10, 50);
  builder2.Mark(10, 50);
  builder2.Merge();
  
  uint8_t bytemap2[256];
  int bytemap_range2 = 0;
  builder2.Build(bytemap2, &bytemap_range2);
  
  EXPECT_EQ(bytemap_range1, bytemap_range2);
  for (int i = 0; i < 256; i++) {
    EXPECT_EQ(bytemap1[i], bytemap2[i]);
  }
}

// Test containment: one range contained within another
TEST_F(ByteMapBuilderTest_409, ContainedRanges_409) {
  ByteMapBuilder builder;
  builder.Mark(10, 100);
  builder.Mark(30, 70);
  builder.Merge();
  
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

}  // namespace re2
