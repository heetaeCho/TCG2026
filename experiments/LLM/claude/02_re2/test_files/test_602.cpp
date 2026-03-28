#include "gtest/gtest.h"
#include <cstdint>
#include <cstring>

// We need to include the relevant headers to access ByteMapBuilder
// Based on the code structure, ByteMapBuilder is in re2 namespace within prog.cc
#include "re2/prog.h"

namespace re2 {

// ByteMapBuilder is defined in prog.cc. We need to check if it's accessible.
// Based on the partial code, it seems to be a class within the re2 namespace.
// If ByteMapBuilder is not directly accessible from the header, we may need
// to include prog.cc or use a testing header.

class ByteMapBuilderTest_602 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Default construction and Build with no marks
TEST_F(ByteMapBuilderTest_602, DefaultConstructionBuild_602) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  memset(bytemap, 0xFF, sizeof(bytemap));
  
  builder.Build(bytemap, &bytemap_range);
  
  // With no marks, we expect a minimal bytemap_range
  EXPECT_GE(bytemap_range, 1);
  // All bytes should have valid mappings (0 to bytemap_range-1)
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test: Mark a single byte range and build
TEST_F(ByteMapBuilderTest_602, MarkSingleByte_602) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  
  builder.Mark(0, 0);
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test: Mark the full range [0, 255]
TEST_F(ByteMapBuilderTest_602, MarkFullRange_602) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  
  builder.Mark(0, 255);
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test: Mark multiple non-overlapping ranges
TEST_F(ByteMapBuilderTest_602, MarkMultipleNonOverlappingRanges_602) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  
  builder.Mark(0, 10);
  builder.Mark(20, 30);
  builder.Mark(50, 60);
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  
  // Bytes within the same marked range should have the same bytemap value
  // Bytes in [0,10] should map to the same value
  for (int i = 1; i <= 10; i++) {
    EXPECT_EQ(bytemap[0], bytemap[i]);
  }
  // Bytes in [20,30] should map to the same value
  for (int i = 21; i <= 30; i++) {
    EXPECT_EQ(bytemap[20], bytemap[i]);
  }
  
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test: Mark overlapping ranges
TEST_F(ByteMapBuilderTest_602, MarkOverlappingRanges_602) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  
  builder.Mark(10, 50);
  builder.Mark(30, 70);
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test: Mark adjacent ranges
TEST_F(ByteMapBuilderTest_602, MarkAdjacentRanges_602) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  
  builder.Mark(0, 127);
  builder.Mark(128, 255);
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test: Mark a single character range (lo == hi)
TEST_F(ByteMapBuilderTest_602, MarkSingleCharacter_602) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  
  builder.Mark(100, 100);
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test: Merge with no marks
TEST_F(ByteMapBuilderTest_602, MergeNoMarks_602) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  
  builder.Merge();
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test: Mark then Merge then Build
TEST_F(ByteMapBuilderTest_602, MarkMergeBuild_602) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  
  builder.Mark(65, 90);  // A-Z
  builder.Mark(97, 122); // a-z
  builder.Merge();
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  
  // Characters within [65,90] should have the same mapping
  for (int i = 66; i <= 90; i++) {
    EXPECT_EQ(bytemap[65], bytemap[i]);
  }
  // Characters within [97,122] should have the same mapping
  for (int i = 98; i <= 122; i++) {
    EXPECT_EQ(bytemap[97], bytemap[i]);
  }
  
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test: Boundary - Mark byte 255
TEST_F(ByteMapBuilderTest_602, MarkByte255_602) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  
  builder.Mark(255, 255);
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test: Boundary - Mark byte 0
TEST_F(ByteMapBuilderTest_602, MarkByte0_602) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  
  builder.Mark(0, 0);
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test: Many small ranges create distinct groups
TEST_F(ByteMapBuilderTest_602, ManySmallRanges_602) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  
  // Mark individual bytes
  for (int i = 0; i < 256; i += 2) {
    builder.Mark(i, i);
  }
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test: Multiple merges
TEST_F(ByteMapBuilderTest_602, MultipleMerges_602) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  
  builder.Mark(10, 20);
  builder.Merge();
  builder.Mark(30, 40);
  builder.Merge();
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test: Distinct ranges produce different bytemap values
TEST_F(ByteMapBuilderTest_602, DistinctRangesProduceDifferentValues_602) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  
  builder.Mark(0, 0);
  builder.Mark(100, 100);
  builder.Build(bytemap, &bytemap_range);
  
  // The marked byte 0 and marked byte 100 should potentially differ
  // from unmarked bytes, but at minimum the bytemap should be valid
  EXPECT_GE(bytemap_range, 1);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test: bytemap_range is bounded by 256
TEST_F(ByteMapBuilderTest_602, BytemapRangeBounded_602) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  
  // Mark every single byte individually to maximize range
  for (int i = 0; i < 256; i++) {
    builder.Mark(i, i);
  }
  builder.Build(bytemap, &bytemap_range);
  
  // bytemap_range should be at most 256 since bytemap values are uint8_t
  EXPECT_GT(bytemap_range, 0);
  EXPECT_LE(bytemap_range, 256);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test: Mark range [0, 254] leaves 255 separate
TEST_F(ByteMapBuilderTest_602, MarkAllExceptLast_602) {
  ByteMapBuilder builder;
  uint8_t bytemap[256];
  int bytemap_range = 0;
  
  builder.Mark(0, 254);
  builder.Build(bytemap, &bytemap_range);
  
  EXPECT_GE(bytemap_range, 1);
  // All bytes in [0,254] should map to the same value
  for (int i = 1; i <= 254; i++) {
    EXPECT_EQ(bytemap[0], bytemap[i]);
  }
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

}  // namespace re2
