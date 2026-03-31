#include <gtest/gtest.h>
#include "yaml-cpp/mark.h"

// Test default constructor - default Mark should not be null
TEST(MarkTest_3, DefaultConstructorIsNotNull_3) {
    YAML::Mark mark;
    EXPECT_FALSE(mark.is_null());
}

// Test default constructor initializes pos, line, column to 0
TEST(MarkTest_3, DefaultConstructorInitializesToZero_3) {
    YAML::Mark mark;
    EXPECT_EQ(mark.pos, 0);
    EXPECT_EQ(mark.line, 0);
    EXPECT_EQ(mark.column, 0);
}

// Test null_mark returns a null mark
TEST(MarkTest_3, NullMarkIsNull_3) {
    YAML::Mark mark = YAML::Mark::null_mark();
    EXPECT_TRUE(mark.is_null());
}

// Test null_mark has pos == -1
TEST(MarkTest_3, NullMarkPosIsNegativeOne_3) {
    YAML::Mark mark = YAML::Mark::null_mark();
    EXPECT_EQ(mark.pos, -1);
}

// Test null_mark has line == -1
TEST(MarkTest_3, NullMarkLineIsNegativeOne_3) {
    YAML::Mark mark = YAML::Mark::null_mark();
    EXPECT_EQ(mark.line, -1);
}

// Test null_mark has column == -1
TEST(MarkTest_3, NullMarkColumnIsNegativeOne_3) {
    YAML::Mark mark = YAML::Mark::null_mark();
    EXPECT_EQ(mark.column, -1);
}

// Test is_null returns false when only pos is -1 but others are 0
TEST(MarkTest_3, IsNullFalseWhenOnlyPosIsNegativeOne_3) {
    YAML::Mark mark;
    mark.pos = -1;
    mark.line = 0;
    mark.column = 0;
    EXPECT_FALSE(mark.is_null());
}

// Test is_null returns false when only line is -1 but others are 0
TEST(MarkTest_3, IsNullFalseWhenOnlyLineIsNegativeOne_3) {
    YAML::Mark mark;
    mark.pos = 0;
    mark.line = -1;
    mark.column = 0;
    EXPECT_FALSE(mark.is_null());
}

// Test is_null returns false when only column is -1 but others are 0
TEST(MarkTest_3, IsNullFalseWhenOnlyColumnIsNegativeOne_3) {
    YAML::Mark mark;
    mark.pos = 0;
    mark.line = 0;
    mark.column = -1;
    EXPECT_FALSE(mark.is_null());
}

// Test is_null returns false when pos and line are -1 but column is not
TEST(MarkTest_3, IsNullFalseWhenPosAndLineAreNegativeOne_3) {
    YAML::Mark mark;
    mark.pos = -1;
    mark.line = -1;
    mark.column = 0;
    EXPECT_FALSE(mark.is_null());
}

// Test is_null returns false when pos and column are -1 but line is not
TEST(MarkTest_3, IsNullFalseWhenPosAndColumnAreNegativeOne_3) {
    YAML::Mark mark;
    mark.pos = -1;
    mark.line = 0;
    mark.column = -1;
    EXPECT_FALSE(mark.is_null());
}

// Test is_null returns false when line and column are -1 but pos is not
TEST(MarkTest_3, IsNullFalseWhenLineAndColumnAreNegativeOne_3) {
    YAML::Mark mark;
    mark.pos = 0;
    mark.line = -1;
    mark.column = -1;
    EXPECT_FALSE(mark.is_null());
}

// Test is_null returns true only when all three are -1
TEST(MarkTest_3, IsNullTrueWhenAllNegativeOne_3) {
    YAML::Mark mark;
    mark.pos = -1;
    mark.line = -1;
    mark.column = -1;
    EXPECT_TRUE(mark.is_null());
}

// Test that public members are accessible and writable with positive values
TEST(MarkTest_3, PublicMembersAreWritableWithPositiveValues_3) {
    YAML::Mark mark;
    mark.pos = 100;
    mark.line = 10;
    mark.column = 5;
    EXPECT_EQ(mark.pos, 100);
    EXPECT_EQ(mark.line, 10);
    EXPECT_EQ(mark.column, 5);
    EXPECT_FALSE(mark.is_null());
}

// Test with large positive values
TEST(MarkTest_3, LargePositiveValuesNotNull_3) {
    YAML::Mark mark;
    mark.pos = 2147483647;
    mark.line = 2147483647;
    mark.column = 2147483647;
    EXPECT_FALSE(mark.is_null());
}

// Test copy semantics of Mark
TEST(MarkTest_3, CopySemanticsWork_3) {
    YAML::Mark original = YAML::Mark::null_mark();
    YAML::Mark copy = original;
    EXPECT_TRUE(copy.is_null());
    EXPECT_EQ(copy.pos, -1);
    EXPECT_EQ(copy.line, -1);
    EXPECT_EQ(copy.column, -1);
}

// Test copy of default constructed mark
TEST(MarkTest_3, CopyOfDefaultMark_3) {
    YAML::Mark original;
    YAML::Mark copy = original;
    EXPECT_FALSE(copy.is_null());
    EXPECT_EQ(copy.pos, 0);
    EXPECT_EQ(copy.line, 0);
    EXPECT_EQ(copy.column, 0);
}
