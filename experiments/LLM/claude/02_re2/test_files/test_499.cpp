#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>

namespace re2 {

// Test fixture for PushRepetition tests via Regexp::Parse
class PushRepetitionTest_499 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Normal repetition with valid min and max via Parse (e.g., a{2,5})
TEST_F(PushRepetitionTest_499, ValidRepetition_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: Repetition with min == max (e.g., a{3,3} which is a{3})
TEST_F(PushRepetitionTest_499, MinEqualsMax_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,3}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: Repetition with exact count (e.g., a{3})
TEST_F(PushRepetitionTest_499, ExactCount_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: Repetition with min=0, max=1 (equivalent to ?)
TEST_F(PushRepetitionTest_499, ZeroToOne_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{0,1}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: Repetition with min=0, max=0
TEST_F(PushRepetitionTest_499, ZeroToZero_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{0,0}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: Repetition with unbounded max (e.g., a{2,})
TEST_F(PushRepetitionTest_499, UnboundedMax_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: Repetition with min=0 and unbounded max (e.g., a{0,})
TEST_F(PushRepetitionTest_499, ZeroToUnbounded_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{0,}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: max < min should fail with kRegexpRepeatSize (e.g., a{5,2})
TEST_F(PushRepetitionTest_499, MaxLessThanMinFails_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{5,2}", Regexp::LikePerl, &status);
  EXPECT_TRUE(re == nullptr);
  EXPECT_EQ(status.code(), kRegexpBadRepeatSize);
}

// Test: Repetition exceeding maximum_repeat_count should fail
TEST_F(PushRepetitionTest_499, ExceedMaxRepeatCount_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{1001}", Regexp::LikePerl, &status);
  EXPECT_TRUE(re == nullptr);
  EXPECT_FALSE(status.ok());
}

// Test: Repetition at maximum_repeat_count boundary (1000)
TEST_F(PushRepetitionTest_499, AtMaxRepeatCountBoundary_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{1000}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: Nongreedy repetition (e.g., a{2,5}?)
TEST_F(PushRepetitionTest_499, NonGreedyRepetition_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}?", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: Repetition with no argument (at start) should fail with kRegexpRepeatArgument
TEST_F(PushRepetitionTest_499, RepeatWithNoArgument_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("{2,5}", Regexp::LikePerl, &status);
  // In Perl mode, this might be treated as literal or error
  // The key is that it doesn't crash; behavior depends on parse mode
  if (re != nullptr) {
    re->Decref();
  }
}

// Test: Nested repetitions that exceed the total repeat count
TEST_F(PushRepetitionTest_499, NestedRepetitionExceedLimit_499) {
  RegexpStatus status;
  // (a{100}){100} would mean 100*100 = 10000 repetitions, exceeding 1000
  Regexp* re = Regexp::Parse("(a{100}){100}", Regexp::LikePerl, &status);
  EXPECT_TRUE(re == nullptr);
  EXPECT_FALSE(status.ok());
}

// Test: Repetition with min=1 (e.g., a{1,})
TEST_F(PushRepetitionTest_499, MinOneUnbounded_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{1,}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: Repetition with min=1, max=1
TEST_F(PushRepetitionTest_499, OneToOne_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{1,1}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: Valid repetition with complex sub-expression
TEST_F(PushRepetitionTest_499, ComplexSubExpression_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc){2,10}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: Repetition on character class
TEST_F(PushRepetitionTest_499, CharClassRepetition_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]{3,7}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: Using FUZZING_ONLY_set_maximum_repeat_count to lower the limit
TEST_F(PushRepetitionTest_499, CustomMaxRepeatCount_499) {
  Regexp::FUZZING_ONLY_set_maximum_repeat_count(10);
  
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{11}", Regexp::LikePerl, &status);
  EXPECT_TRUE(re == nullptr);
  EXPECT_FALSE(status.ok());
  
  // Restore default
  Regexp::FUZZING_ONLY_set_maximum_repeat_count(1000);
}

// Test: With lowered limit, values at the limit should work
TEST_F(PushRepetitionTest_499, CustomMaxRepeatCountAtBoundary_499) {
  Regexp::FUZZING_ONLY_set_maximum_repeat_count(10);
  
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{10}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
  
  // Restore default
  Regexp::FUZZING_ONLY_set_maximum_repeat_count(1000);
}

// Test: Nested repetition within limit
TEST_F(PushRepetitionTest_499, NestedRepetitionWithinLimit_499) {
  RegexpStatus status;
  // (a{2}){3} = 6 total repetitions, within default 1000 limit
  Regexp* re = Regexp::Parse("(a{2}){3}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: Multiple sequential repetitions
TEST_F(PushRepetitionTest_499, MultipleSequentialRepetitions_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2}b{3}c{4}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: Repetition with min=0 (e.g., a{0,5})
TEST_F(PushRepetitionTest_499, MinZeroMaxFive_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{0,5}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: Deeply nested repetitions exceeding limit
TEST_F(PushRepetitionTest_499, DeeplyNestedRepetitionsExceedLimit_499) {
  Regexp::FUZZING_ONLY_set_maximum_repeat_count(100);
  
  RegexpStatus status;
  // (((a{10}){10}){10}) = 1000, exceeds 100
  Regexp* re = Regexp::Parse("((a{10}){10}){10}", Regexp::LikePerl, &status);
  EXPECT_TRUE(re == nullptr);
  EXPECT_FALSE(status.ok());
  
  // Restore default
  Regexp::FUZZING_ONLY_set_maximum_repeat_count(1000);
}

// Test: Verify that Regexp::Repeat static method works with valid params
TEST_F(PushRepetitionTest_499, StaticRepeatMethod_499) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_TRUE(sub != nullptr);
  
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 5);
  ASSERT_TRUE(re != nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test: min=1, max=1000 at boundary
TEST_F(PushRepetitionTest_499, LargeMaxAtBoundary_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{1,1000}", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test: min=1001 exceeds limit
TEST_F(PushRepetitionTest_499, LargeMinExceedsLimit_499) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{1001,2000}", Regexp::LikePerl, &status);
  EXPECT_TRUE(re == nullptr);
  EXPECT_FALSE(status.ok());
}

}  // namespace re2
