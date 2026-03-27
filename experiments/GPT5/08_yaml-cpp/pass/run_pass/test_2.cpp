// mark_test_2.cpp
#include <gtest/gtest.h>

#include <yaml-cpp/mark.h>

namespace {

TEST(MarkTest_2, DefaultConstructorInitializesToZero_2) {
  YAML::Mark m;
  EXPECT_EQ(m.pos, 0);
  EXPECT_EQ(m.line, 0);
  EXPECT_EQ(m.column, 0);

  // Observable behavior through the public interface.
  EXPECT_FALSE(m.is_null());
}

TEST(MarkTest_2, NullMarkHasExpectedSentinelValues_2) {
  const YAML::Mark nm = YAML::Mark::null_mark();
  EXPECT_EQ(nm.pos, -1);
  EXPECT_EQ(nm.line, -1);
  EXPECT_EQ(nm.column, -1);
}

TEST(MarkTest_2, NullMarkReportsIsNull_2) {
  const YAML::Mark nm = YAML::Mark::null_mark();
  EXPECT_TRUE(nm.is_null());
}

TEST(MarkTest_2, NullMarkReturnsIndependentValuesAcrossCalls_2) {
  YAML::Mark a = YAML::Mark::null_mark();
  YAML::Mark b = YAML::Mark::null_mark();

  // Mutate one instance via public fields; should not affect a separately obtained value.
  a.pos = 123;
  a.line = 456;
  a.column = 789;

  EXPECT_EQ(b.pos, -1);
  EXPECT_EQ(b.line, -1);
  EXPECT_EQ(b.column, -1);
  EXPECT_TRUE(b.is_null());
}

TEST(MarkTest_2, DefaultAndNullMarkAreDifferent_2) {
  const YAML::Mark def;
  const YAML::Mark nm = YAML::Mark::null_mark();

  EXPECT_FALSE(def.is_null());
  EXPECT_TRUE(nm.is_null());

  EXPECT_NE(def.pos, nm.pos);
  EXPECT_NE(def.line, nm.line);
  EXPECT_NE(def.column, nm.column);
}

}  // namespace
