// File: charclassbuilder_empty_166_test.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

namespace {

using re2::CharClassBuilder;

// [166] Basic behavior: default-constructed instance should be empty.
TEST(CharClassBuilderEmptyTest_166, DefaultConstructedIsEmpty_166) {
  CharClassBuilder ccb;
  EXPECT_TRUE(ccb.empty()) << "Default-constructed CharClassBuilder should be empty.";
}

// [166] Idempotence: calling empty() repeatedly should not change the result.
TEST(CharClassBuilderEmptyTest_166, EmptyIsIdempotent_166) {
  CharClassBuilder ccb;
  bool first = ccb.empty();
  bool second = ccb.empty();
  bool third = ccb.empty();
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

}  // namespace
