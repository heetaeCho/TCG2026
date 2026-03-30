// File: re2_fuzzing_only_set_max_global_replace_count_test.cc

#include <gtest/gtest.h>
#include "re2/re2/re2.h"

// The global is part of the provided partial implementation.
// We declare it here to observe the effect of the public API.
namespace re2 {
extern int maximum_global_replace_count;
}

class RE2FuzzMaxReplaceTest_236 : public ::testing::Test {
protected:
  int saved_{-1};

  void SetUp() override { saved_ = re2::maximum_global_replace_count; }
  void TearDown() override { re2::maximum_global_replace_count = saved_; }
};

TEST_F(RE2FuzzMaxReplaceTest_236, DefaultIsMinusOne_236) {
  // From the prompt's "Global Variables" section.
  EXPECT_EQ(re2::maximum_global_replace_count, -1);
}

TEST_F(RE2FuzzMaxReplaceTest_236, SetPositiveValue_236) {
  re2::RE2 re;  // Treating implementation as a black box; using the public class.
  re.FUZZING_ONLY_set_maximum_global_replace_count(5);
  EXPECT_EQ(re2::maximum_global_replace_count, 5);
}

TEST_F(RE2FuzzMaxReplaceTest_236, SetZero_236) {
  re2::RE2 re;
  re.FUZZING_ONLY_set_maximum_global_replace_count(0);
  EXPECT_EQ(re2::maximum_global_replace_count, 0);
}

TEST_F(RE2FuzzMaxReplaceTest_236, SetNegativeValue_236) {
  re2::RE2 re;
  re.FUZZING_ONLY_set_maximum_global_replace_count(-1);
  EXPECT_EQ(re2::maximum_global_replace_count, -1);
}

TEST_F(RE2FuzzMaxReplaceTest_236, MultipleCallsOverride_236) {
  re2::RE2 re;
  re.FUZZING_ONLY_set_maximum_global_replace_count(2);
  EXPECT_EQ(re2::maximum_global_replace_count, 2);

  re.FUZZING_ONLY_set_maximum_global_replace_count(7);
  EXPECT_EQ(re2::maximum_global_replace_count, 7);
}
