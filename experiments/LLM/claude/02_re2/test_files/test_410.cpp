#include "gtest/gtest.h"
#include <cstdint>
#include <cstring>

// We need to include the actual header that defines ByteMapBuilder.
// Based on the file structure, ByteMapBuilder is defined in prog.cc/prog.h
#include "re2/prog.h"

namespace re2 {

class ByteMapBuilderTest_410 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a freshly constructed ByteMapBuilder with no marks
// produces a bytemap where all bytes map to the same value (0)
// and bytemap_range is 1.
TEST_F(ByteMapBuilderTest_410, DefaultBuildNoMarks_410) {
  ByteMapBuilder builder;
  builder.Merge();

  uint8_t bytemap[256];
  int bytemap_range = 0;
  memset(bytemap, 0xFF, sizeof(bytemap));

  builder.Build(bytemap, &bytemap_range);

  // With no marks, all bytes should be the same color
  for (int i = 1; i < 256; i++) {
    EXPECT_EQ(bytemap[0], bytemap[i])
        << "bytemap[0]=" << (int)bytemap[0] << " bytemap[" << i << "]=" << (int)bytemap[i];
  }
  // bytemap_range should be 1 (only one color)
  EXPECT_EQ(1, bytemap_range);
}

// Test marking a single byte range and building
TEST_F(ByteMapBuilderTest_410, SingleMarkSingleByte_410) {
  ByteMapBuilder builder;
  builder.Mark(65, 65);  // Mark byte 'A'
  builder.Merge();

  uint8_t bytemap[256];
  int bytemap_range = 0;
  memset(bytemap, 0xFF, sizeof(bytemap));

  builder.Build(bytemap, &bytemap_range);

  // bytemap_range should be > 1 since we split the space
  EXPECT_GT(bytemap_range, 1);

  // Bytes before 65 should have the same color
  for (int i = 0; i < 65; i++) {
    EXPECT_EQ(bytemap[0], bytemap[i]);
  }

  // Byte 65 should potentially be a different color
  // Bytes after 65 (66-255) might be different from byte 65
}

// Test marking a range of bytes
TEST_F(ByteMapBuilderTest_410, MarkRange_410) {
  ByteMapBuilder builder;
  builder.Mark(10, 20);
  builder.Merge();

  uint8_t bytemap[256];
  int bytemap_range = 0;

  builder.Build(bytemap, &bytemap_range);

  // All bytes within the range [10,20] should have the same color
  for (int i = 10; i <= 20; i++) {
    EXPECT_EQ(bytemap[10], bytemap[i])
        << "bytemap[10]=" << (int)bytemap[10] << " bytemap[" << i << "]=" << (int)bytemap[i];
  }

  // Bytes in [0,9] should have the same color
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(bytemap[0], bytemap[i]);
  }

  // Bytes in [21,255] should have the same color
  for (int i = 21; i < 256; i++) {
    EXPECT_EQ(bytemap[21], bytemap[i]);
  }
}

// Test marking the full range [0, 255]
TEST_F(ByteMapBuilderTest_410, MarkFullRange_410) {
  ByteMapBuilder builder;
  builder.Mark(0, 255);
  builder.Merge();

  uint8_t bytemap[256];
  int bytemap_range = 0;

  builder.Build(bytemap, &bytemap_range);

  // All bytes should map to the same value since the entire range is marked
  for (int i = 0; i < 256; i++) {
    EXPECT_EQ(bytemap[0], bytemap[i]);
  }
  EXPECT_EQ(1, bytemap_range);
}

// Test marking multiple non-overlapping ranges
TEST_F(ByteMapBuilderTest_410, MultipleNonOverlappingMarks_410) {
  ByteMapBuilder builder;
  builder.Mark(10, 20);
  builder.Mark(50, 60);
  builder.Merge();

  uint8_t bytemap[256];
  int bytemap_range = 0;

  builder.Build(bytemap, &bytemap_range);

  // Bytes in [10,20] should all be the same
  for (int i = 10; i <= 20; i++) {
    EXPECT_EQ(bytemap[10], bytemap[i]);
  }

  // Bytes in [50,60] should all be the same
  for (int i = 50; i <= 60; i++) {
    EXPECT_EQ(bytemap[50], bytemap[i]);
  }

  // Should have multiple distinct colors
  EXPECT_GT(bytemap_range, 1);
}

// Test marking overlapping ranges
TEST_F(ByteMapBuilderTest_410, OverlappingMarks_410) {
  ByteMapBuilder builder;
  builder.Mark(10, 30);
  builder.Mark(20, 40);
  builder.Merge();

  uint8_t bytemap[256];
  int bytemap_range = 0;

  builder.Build(bytemap, &bytemap_range);

  // The overlap region [20,30] should all have the same color
  for (int i = 20; i <= 30; i++) {
    EXPECT_EQ(bytemap[20], bytemap[i]);
  }

  EXPECT_GT(bytemap_range, 1);
}

// Test marking adjacent ranges
TEST_F(ByteMapBuilderTest_410, AdjacentMarks_410) {
  ByteMapBuilder builder;
  builder.Mark(10, 20);
  builder.Mark(21, 30);
  builder.Merge();

  uint8_t bytemap[256];
  int bytemap_range = 0;

  builder.Build(bytemap, &bytemap_range);

  // Bytes 10-20 should be same color
  for (int i = 10; i <= 20; i++) {
    EXPECT_EQ(bytemap[10], bytemap[i]);
  }

  // Bytes 21-30 should be same color
  for (int i = 21; i <= 30; i++) {
    EXPECT_EQ(bytemap[21], bytemap[i]);
  }
}

// Test marking a single byte at boundary 0
TEST_F(ByteMapBuilderTest_410, MarkByte0_410) {
  ByteMapBuilder builder;
  builder.Mark(0, 0);
  builder.Merge();

  uint8_t bytemap[256];
  int bytemap_range = 0;

  builder.Build(bytemap, &bytemap_range);

  // Bytes [1, 255] should all be the same color
  for (int i = 1; i < 256; i++) {
    EXPECT_EQ(bytemap[1], bytemap[i]);
  }

  EXPECT_GT(bytemap_range, 0);
}

// Test marking a single byte at boundary 255
TEST_F(ByteMapBuilderTest_410, MarkByte255_410) {
  ByteMapBuilder builder;
  builder.Mark(255, 255);
  builder.Merge();

  uint8_t bytemap[256];
  int bytemap_range = 0;

  builder.Build(bytemap, &bytemap_range);

  // Bytes [0, 254] should all be the same color
  for (int i = 0; i < 255; i++) {
    EXPECT_EQ(bytemap[0], bytemap[i]);
  }

  EXPECT_GT(bytemap_range, 0);
}

// Test that bytemap values are within valid range
TEST_F(ByteMapBuilderTest_410, BytemapValuesInRange_410) {
  ByteMapBuilder builder;
  builder.Mark(0, 50);
  builder.Mark(100, 150);
  builder.Mark(200, 255);
  builder.Merge();

  uint8_t bytemap[256];
  int bytemap_range = 0;

  builder.Build(bytemap, &bytemap_range);

  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range)
        << "bytemap[" << i << "]=" << (int)bytemap[i]
        << " >= bytemap_range=" << bytemap_range;
  }
}

// Test many individual marks creating many equivalence classes
TEST_F(ByteMapBuilderTest_410, ManyIndividualMarks_410) {
  ByteMapBuilder builder;
  // Mark every other byte
  for (int i = 0; i < 256; i += 2) {
    builder.Mark(i, i);
  }
  builder.Merge();

  uint8_t bytemap[256];
  int bytemap_range = 0;

  builder.Build(bytemap, &bytemap_range);

  // All values should be within range
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test marking all individual bytes separately
TEST_F(ByteMapBuilderTest_410, MarkAllBytesIndividually_410) {
  ByteMapBuilder builder;
  for (int i = 0; i < 256; i++) {
    builder.Mark(i, i);
  }
  builder.Merge();

  uint8_t bytemap[256];
  int bytemap_range = 0;

  builder.Build(bytemap, &bytemap_range);

  // Each byte should have its own color, so bytemap_range should be 256
  // or each bytemap[i] should be unique
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

// Test that bytemap_range is reasonable after multiple merges of same range
TEST_F(ByteMapBuilderTest_410, DuplicateMarks_410) {
  ByteMapBuilder builder;
  builder.Mark(10, 20);
  builder.Mark(10, 20);  // duplicate
  builder.Merge();

  uint8_t bytemap[256];
  int bytemap_range = 0;

  builder.Build(bytemap, &bytemap_range);

  // Should behave same as single mark
  for (int i = 10; i <= 20; i++) {
    EXPECT_EQ(bytemap[10], bytemap[i]);
  }

  EXPECT_GT(bytemap_range, 0);
}

// Test with a typical character class like [a-z]
TEST_F(ByteMapBuilderTest_410, TypicalCharClassLowercase_410) {
  ByteMapBuilder builder;
  builder.Mark('a', 'z');
  builder.Merge();

  uint8_t bytemap[256];
  int bytemap_range = 0;

  builder.Build(bytemap, &bytemap_range);

  // All lowercase letters should have the same color
  for (int i = 'a'; i <= 'z'; i++) {
    EXPECT_EQ(bytemap['a'], bytemap[i]);
  }

  // bytemap_range should reflect the number of distinct regions
  EXPECT_GT(bytemap_range, 1);
}

// Test with multiple character classes simulating a regex like [a-zA-Z0-9]
TEST_F(ByteMapBuilderTest_410, MultipleCharClasses_410) {
  ByteMapBuilder builder;
  builder.Mark('a', 'z');
  builder.Mark('A', 'Z');
  builder.Mark('0', '9');
  builder.Merge();

  uint8_t bytemap[256];
  int bytemap_range = 0;

  builder.Build(bytemap, &bytemap_range);

  // Each class should be internally consistent
  for (int i = 'a'; i <= 'z'; i++) {
    EXPECT_EQ(bytemap['a'], bytemap[i]);
  }
  for (int i = 'A'; i <= 'Z'; i++) {
    EXPECT_EQ(bytemap['A'], bytemap[i]);
  }
  for (int i = '0'; i <= '9'; i++) {
    EXPECT_EQ(bytemap['0'], bytemap[i]);
  }

  // All values should be in range
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bytemap[i], bytemap_range);
  }
}

}  // namespace re2
