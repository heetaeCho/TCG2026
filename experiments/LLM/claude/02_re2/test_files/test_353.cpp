#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

// We need to test NumCapturesWalker through Regexp's public interface
// since NumCapturesWalker is used internally. The observable behavior
// is through Regexp::NumCaptures().

class NumCapturesTest_353 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

TEST_F(NumCapturesTest_353, NoCaptures_353) {
  // A simple pattern with no capture groups
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(NumCapturesTest_353, SingleCapture_353) {
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST_F(NumCapturesTest_353, MultipleCaptures_353) {
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(NumCapturesTest_353, NestedCaptures_353) {
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(NumCapturesTest_353, NonCapturingGroup_353) {
  Regexp* re = Regexp::Parse("(?:abc)", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(NumCapturesTest_353, MixedCapturingAndNonCapturing_353) {
  Regexp* re = Regexp::Parse("(a)(?:b)(c)", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 2);
  re->Decref();
}

TEST_F(NumCapturesTest_353, NamedCapture_353) {
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST_F(NumCapturesTest_353, EmptyPattern_353) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST_F(NumCapturesTest_353, ComplexPattern_353) {
  Regexp* re = Regexp::Parse("(a(b(c)d)e)(f)", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 4);
  re->Decref();
}

TEST_F(NumCapturesTest_353, AlternationWithCaptures_353) {
  Regexp* re = Regexp::Parse("(a)|(b)|(c)", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

TEST_F(NumCapturesTest_353, RepetitionWithCapture_353) {
  Regexp* re = Regexp::Parse("(a)+", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

TEST_F(NumCapturesTest_353, DeeplyNestedCaptures_353) {
  Regexp* re = Regexp::Parse("((((a))))", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 4);
  re->Decref();
}

}  // namespace re2
