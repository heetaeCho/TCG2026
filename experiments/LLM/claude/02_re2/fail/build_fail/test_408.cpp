#include "gtest/gtest.h"
#include "re2/prog.h"
#include <cstdint>
#include <vector>

namespace re2 {

class ByteMapBuilderTest_408 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a freshly constructed ByteMapBuilder can Build without any marks
TEST_F(ByteMapBuilderTest_408, DefaultBuild_408) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  // With no marks, all bytes should map to the same value
  // bytemap_range should be 1 (a single equivalence class)
  EXPECT_EQ(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_EQ(bytemap[i], 0);
  }
}

// Test marking the full range [0, 255] which should be a no-op
TEST_F(ByteMapBuilderTest_408, MarkFullRange_408) {
  ByteMapBuilder builder;
  builder.Mark(0, 255);
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  // Full range mark is a no-op, so same as default
  EXPECT_EQ(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_EQ(bytemap[i], 0);
  }
}

// Test marking a single byte
TEST_F(ByteMapBuilderTest_408, MarkSingleByte_408) {
  ByteMapBuilder builder;
  builder.Mark(65, 65);  // Mark only 'A'
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  // Should create multiple equivalence classes
  EXPECT_GT(bytemap_range, 1);
  // The byte 65 should be in a different class than bytes outside its range
  // Specifically, bytes before 65, byte 65 itself, and bytes after 65 may differ
  // At minimum, byte 65 should map differently from byte 0 or byte 66
  // (unless they happen to merge, but with a single mark they shouldn't)
}

// Test marking a range that splits the byte space
TEST_F(ByteMapBuilderTest_408, MarkSubRange_408) {
  ByteMapBuilder builder;
  builder.Mark(10, 20);
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  EXPECT_GT(bytemap_range, 1);
  // Bytes within [10,20] should have the same mapping
  for (int i = 11; i <= 20; i++) {
    EXPECT_EQ(bytemap[i], bytemap[10]);
  }
}

// Test marking two non-overlapping ranges
TEST_F(ByteMapBuilderTest_408, MarkTwoDisjointRanges_408) {
  ByteMapBuilder builder;
  builder.Mark(10, 20);
  builder.Mark(30, 40);
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  EXPECT_GT(bytemap_range, 1);
  // Bytes within [10,20] should have consistent mapping
  for (int i = 11; i <= 20; i++) {
    EXPECT_EQ(bytemap[i], bytemap[10]);
  }
  // Bytes within [30,40] should have consistent mapping
  for (int i = 31; i <= 40; i++) {
    EXPECT_EQ(bytemap[i], bytemap[30]);
  }
}

// Test marking overlapping ranges
TEST_F(ByteMapBuilderTest_408, MarkOverlappingRanges_408) {
  ByteMapBuilder builder;
  builder.Mark(10, 30);
  builder.Mark(20, 40);
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  EXPECT_GT(bytemap_range, 1);
}

// Test marking at boundary 0
TEST_F(ByteMapBuilderTest_408, MarkLowerBoundary_408) {
  ByteMapBuilder builder;
  builder.Mark(0, 0);
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  EXPECT_GT(bytemap_range, 1);
}

// Test marking at boundary 255
TEST_F(ByteMapBuilderTest_408, MarkUpperBoundary_408) {
  ByteMapBuilder builder;
  builder.Mark(255, 255);
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  EXPECT_GT(bytemap_range, 1);
}

// Test marking range [0, 127] (lower half)
TEST_F(ByteMapBuilderTest_408, MarkLowerHalf_408) {
  ByteMapBuilder builder;
  builder.Mark(0, 127);
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  // Should split into at least 2 classes
  EXPECT_GE(bytemap_range, 2);
  // All bytes in [0,127] should share the same class
  for (int i = 1; i <= 127; i++) {
    EXPECT_EQ(bytemap[i], bytemap[0]);
  }
  // All bytes in [128,255] should share the same class
  for (int i = 129; i <= 255; i++) {
    EXPECT_EQ(bytemap[i], bytemap[128]);
  }
  // The two groups should differ
  EXPECT_NE(bytemap[0], bytemap[128]);
}

// Test Merge followed by Build
TEST_F(ByteMapBuilderTest_408, MergeAndBuild_408) {
  ByteMapBuilder builder;
  builder.Mark(10, 20);
  builder.Merge();
  builder.Mark(30, 40);
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  EXPECT_GT(bytemap_range, 1);
}

// Test multiple Merges
TEST_F(ByteMapBuilderTest_408, MultipleMerges_408) {
  ByteMapBuilder builder;
  builder.Mark(10, 20);
  builder.Merge();
  builder.Mark(15, 25);
  builder.Merge();
  builder.Mark(50, 60);
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  EXPECT_GT(bytemap_range, 1);
}

// Test that bytemap_range is within valid bounds [1, 256]
TEST_F(ByteMapBuilderTest_408, BytemapRangeValid_408) {
  ByteMapBuilder builder;
  // Mark many individual bytes
  for (int i = 0; i < 256; i += 2) {
    builder.Mark(i, i);
  }
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  EXPECT_GE(bytemap_range, 1);
  EXPECT_LE(bytemap_range, 256);
  // Every bytemap entry should be within [0, bytemap_range)
  for (int i = 0; i < 256; i++) {
    EXPECT_GE(bytemap[i], 0);
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test adjacent ranges
TEST_F(ByteMapBuilderTest_408, AdjacentRanges_408) {
  ByteMapBuilder builder;
  builder.Mark(10, 19);
  builder.Mark(20, 29);
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  EXPECT_GT(bytemap_range, 1);
}

// Test marking with Merge creating complex splits
TEST_F(ByteMapBuilderTest_408, ComplexMergeSplits_408) {
  ByteMapBuilder builder;
  builder.Mark(0, 50);
  builder.Merge();
  builder.Mark(25, 75);
  builder.Merge();
  builder.Mark(50, 100);
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  EXPECT_GT(bytemap_range, 1);
  // Validate all entries are in range
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test Merge with no marks is safe
TEST_F(ByteMapBuilderTest_408, MergeWithoutMarks_408) {
  ByteMapBuilder builder;
  builder.Merge();
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  EXPECT_EQ(bytemap_range, 1);
}

// Test marking every single byte individually
TEST_F(ByteMapBuilderTest_408, MarkEveryByte_408) {
  ByteMapBuilder builder;
  for (int i = 0; i < 256; i++) {
    builder.Mark(i, i);
  }
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  // Each byte marked individually could create up to 256 classes
  EXPECT_GE(bytemap_range, 1);
  EXPECT_LE(bytemap_range, 256);
}

// Test that same range marked twice doesn't cause issues
TEST_F(ByteMapBuilderTest_408, DuplicateMarks_408) {
  ByteMapBuilder builder;
  builder.Mark(10, 20);
  builder.Mark(10, 20);
  uint8_t bytemap[256];
  int bytemap_range = 0;
  builder.Build(bytemap, &bytemap_range);
  EXPECT_GT(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

}  // namespace re2
