// TEST_ID: 3
#include <gtest/gtest.h>

#include "yaml-cpp/mark.h"

namespace {

TEST(MarkTest_3, IsNullReturnsTrueWhenAllFieldsAreMinusOne_3) {
  YAML::Mark mark;
  mark.pos = -1;
  mark.line = -1;
  mark.column = -1;

  EXPECT_TRUE(mark.is_null());
}

TEST(MarkTest_3, IsNullReturnsFalseWhenPosIsNotMinusOne_3) {
  YAML::Mark mark;
  mark.pos = 0;
  mark.line = -1;
  mark.column = -1;

  EXPECT_FALSE(mark.is_null());
}

TEST(MarkTest_3, IsNullReturnsFalseWhenLineIsNotMinusOne_3) {
  YAML::Mark mark;
  mark.pos = -1;
  mark.line = 0;
  mark.column = -1;

  EXPECT_FALSE(mark.is_null());
}

TEST(MarkTest_3, IsNullReturnsFalseWhenColumnIsNotMinusOne_3) {
  YAML::Mark mark;
  mark.pos = -1;
  mark.line = -1;
  mark.column = 0;

  EXPECT_FALSE(mark.is_null());
}

TEST(MarkTest_3, IsNullReturnsFalseWhenAllFieldsAreNonMinusOne_3) {
  YAML::Mark mark;
  mark.pos = 1;
  mark.line = 2;
  mark.column = 3;

  EXPECT_FALSE(mark.is_null());
}

TEST(MarkTest_3, IsNullCanBeCalledOnConstObject_3) {
  YAML::Mark mark;
  mark.pos = -1;
  mark.line = -1;
  mark.column = -1;

  const YAML::Mark& const_ref = mark;
  EXPECT_TRUE(const_ref.is_null());
}

TEST(MarkTest_3, DefaultConstructedMarkIsNotNullWhenAnyFieldIsNotMinusOne_3) {
  // This test checks observable behavior only: whatever the default constructor
  // sets, is_null() should reflect whether all fields are -1 or not.
  YAML::Mark mark;

  const bool expected =
      (mark.pos == -1) && (mark.line == -1) && (mark.column == -1);

  EXPECT_EQ(mark.is_null(), expected);
}

}  // namespace
