#include "gtest/gtest.h"
#include "re2/compile.cc"

namespace re2 {

TEST(IsNoMatchTest_291, ReturnsTrueWhenBeginIsZero_291) {
  Frag frag;
  frag.begin = 0;
  frag.end = kNullPatchList;
  frag.nullable = false;
  EXPECT_TRUE(IsNoMatch(frag));
}

TEST(IsNoMatchTest_291, ReturnsFalseWhenBeginIsNonZero_291) {
  Frag frag;
  frag.begin = 1;
  frag.end = kNullPatchList;
  frag.nullable = false;
  EXPECT_FALSE(IsNoMatch(frag));
}

TEST(IsNoMatchTest_291, ReturnsFalseWhenBeginIsLargeValue_291) {
  Frag frag;
  frag.begin = 0xFFFFFFFF;
  frag.end = kNullPatchList;
  frag.nullable = false;
  EXPECT_FALSE(IsNoMatch(frag));
}

TEST(IsNoMatchTest_291, ReturnsTrueRegardlessOfNullableTrue_291) {
  Frag frag;
  frag.begin = 0;
  frag.end = kNullPatchList;
  frag.nullable = true;
  EXPECT_TRUE(IsNoMatch(frag));
}

TEST(IsNoMatchTest_291, ReturnsFalseWhenBeginIsOne_291) {
  Frag frag;
  frag.begin = 1;
  frag.end = kNullPatchList;
  frag.nullable = true;
  EXPECT_FALSE(IsNoMatch(frag));
}

TEST(IsNoMatchTest_291, DefaultConstructedFragIsNoMatch_291) {
  Frag frag;
  EXPECT_TRUE(IsNoMatch(frag));
}

TEST(IsNoMatchTest_291, ReturnsFalseWhenBeginIsMaxUint32MinusOne_291) {
  Frag frag;
  frag.begin = 0xFFFFFFFE;
  frag.end = kNullPatchList;
  frag.nullable = false;
  EXPECT_FALSE(IsNoMatch(frag));
}

TEST(IsNoMatchTest_291, ReturnsFalseWhenBeginIsSmallNonZero_291) {
  Frag frag;
  frag.begin = 42;
  frag.end = kNullPatchList;
  frag.nullable = false;
  EXPECT_FALSE(IsNoMatch(frag));
}

}  // namespace re2
