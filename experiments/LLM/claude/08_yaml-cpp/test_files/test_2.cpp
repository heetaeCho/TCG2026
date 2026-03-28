#include <gtest/gtest.h>
#include "yaml-cpp/mark.h"

// Test default constructor creates a Mark with pos=0, line=0, column=0
TEST(MarkTest_2, DefaultConstructor_2) {
    YAML::Mark mark;
    EXPECT_EQ(mark.pos, 0);
    EXPECT_EQ(mark.line, 0);
    EXPECT_EQ(mark.column, 0);
}

// Test null_mark returns a Mark with -1 values
TEST(MarkTest_2, NullMarkReturnsNegativeValues_2) {
    YAML::Mark null_mark = YAML::Mark::null_mark();
    EXPECT_EQ(null_mark.pos, -1);
    EXPECT_EQ(null_mark.line, -1);
    EXPECT_EQ(null_mark.column, -1);
}

// Test that null_mark is_null returns true
TEST(MarkTest_2, NullMarkIsNull_2) {
    YAML::Mark null_mark = YAML::Mark::null_mark();
    EXPECT_TRUE(null_mark.is_null());
}

// Test that default constructed Mark is not null
TEST(MarkTest_2, DefaultConstructedIsNotNull_2) {
    YAML::Mark mark;
    EXPECT_FALSE(mark.is_null());
}

// Test that null_mark is consistent across multiple calls
TEST(MarkTest_2, NullMarkConsistency_2) {
    YAML::Mark null1 = YAML::Mark::null_mark();
    YAML::Mark null2 = YAML::Mark::null_mark();
    EXPECT_EQ(null1.pos, null2.pos);
    EXPECT_EQ(null1.line, null2.line);
    EXPECT_EQ(null1.column, null2.column);
}

// Test that null_mark returns const Mark
TEST(MarkTest_2, NullMarkIsConst_2) {
    const YAML::Mark null_mark = YAML::Mark::null_mark();
    EXPECT_TRUE(null_mark.is_null());
    EXPECT_EQ(null_mark.pos, -1);
    EXPECT_EQ(null_mark.line, -1);
    EXPECT_EQ(null_mark.column, -1);
}

// Test that default Mark members are publicly accessible and modifiable
TEST(MarkTest_2, PublicMembersAccessible_2) {
    YAML::Mark mark;
    mark.pos = 10;
    mark.line = 5;
    mark.column = 3;
    EXPECT_EQ(mark.pos, 10);
    EXPECT_EQ(mark.line, 5);
    EXPECT_EQ(mark.column, 3);
}

// Test that modifying a default mark doesn't affect is_null behavior
TEST(MarkTest_2, ModifiedMarkIsNotNull_2) {
    YAML::Mark mark;
    mark.pos = 42;
    mark.line = 10;
    mark.column = 20;
    EXPECT_FALSE(mark.is_null());
}

// Test copy of null_mark
TEST(MarkTest_2, CopyOfNullMark_2) {
    YAML::Mark null_mark = YAML::Mark::null_mark();
    YAML::Mark copy = null_mark;
    EXPECT_TRUE(copy.is_null());
    EXPECT_EQ(copy.pos, -1);
    EXPECT_EQ(copy.line, -1);
    EXPECT_EQ(copy.column, -1);
}

// Test copy of default mark
TEST(MarkTest_2, CopyOfDefaultMark_2) {
    YAML::Mark mark;
    YAML::Mark copy = mark;
    EXPECT_FALSE(copy.is_null());
    EXPECT_EQ(copy.pos, 0);
    EXPECT_EQ(copy.line, 0);
    EXPECT_EQ(copy.column, 0);
}
