#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/synchronization/mutex.h"

namespace re2 {

// Test that Regexp objects can be created and reference counted properly
// The ref_mutex and ref_map are internal mechanisms for reference counting

class RegexpRefTest_332 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(RegexpRefTest_332, ParseSimpleRegexp_332) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpRefTest_332, ParseAndIncrefDecref_332) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b*c?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  
  // Incref then Decref should leave object valid for final Decref
  re->Incref();
  re->Decref();
  re->Decref();
}

TEST_F(RegexpRefTest_332, ParseEmptyRegexp_332) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

TEST_F(RegexpRefTest_332, ParseComplexRegexp_332) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)+[c-z]*\\d{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST_F(RegexpRefTest_332, ParseInvalidRegexp_332) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST_F(RegexpRefTest_332, MultipleIncrefDecref_332) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("test", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  // Multiple Incref/Decref cycles
  re->Incref();
  re->Incref();
  re->Decref();
  re->Decref();
  re->Decref();
}

TEST_F(RegexpRefTest_332, MultipleRegexpObjects_332) {
  RegexpStatus status1, status2;
  Regexp* re1 = Regexp::Parse("abc", Regexp::LikePerl, &status1);
  Regexp* re2 = Regexp::Parse("def", Regexp::LikePerl, &status2);
  ASSERT_NE(re1, nullptr);
  ASSERT_NE(re2, nullptr);
  
  re1->Decref();
  re2->Decref();
}

TEST_F(RegexpRefTest_332, ToStringRoundTrip_332) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  
  re->Decref();
}

TEST_F(RegexpRefTest_332, RegexpOp_332) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  // The op should be a valid RegexpOp value
  RegexpOp op = re->op();
  EXPECT_GE(static_cast<int>(op), 0);
  
  re->Decref();
}

}  // namespace re2
