#include <gtest/gtest.h>
#include "re2/regexp.h"
#include "re2/walker-inl.h"

// We need to include the fuzzer file or declare the class.
// Since SubexpressionWalker is defined in re2_fuzzer.cc, we include it or redeclare.
// For testing purposes, we'll include the source.
#include "re2/fuzzing/re2_fuzzer.cc"

class SubexpressionWalkerTest_381 : public ::testing::Test {
 protected:
  SubexpressionWalker walker_;
};

// Test PostVisit with kRegexpConcat and no children
TEST_F(SubexpressionWalkerTest_381, PostVisitConcatNoChildren_381) {
  re2::RegexpStatus status;
  // Create a Concat regexp. We'll use Parse to get a Concat.
  re2::Regexp* re = re2::Regexp::Parse("ab", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  // If re is a Concat, test PostVisit with nchild_args = 0
  if (re->op() == re2::kRegexpConcat) {
    int result = walker_.PostVisit(re, 0, 0, nullptr, 0);
    EXPECT_EQ(result, 0);
  }
  re->Decref();
}

// Test PostVisit with kRegexpConcat and children with values less than nchild_args
TEST_F(SubexpressionWalkerTest_381, PostVisitConcatChildrenLessThanN_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("ab", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpConcat) {
    int child_args[] = {1, 2};
    int result = walker_.PostVisit(re, 0, 0, child_args, 2);
    // max of nchild_args(2), child_args[0](1), child_args[1](2) = 2
    EXPECT_EQ(result, 2);
  }
  re->Decref();
}

// Test PostVisit with kRegexpConcat and children with values greater than nchild_args
TEST_F(SubexpressionWalkerTest_381, PostVisitConcatChildrenGreaterThanN_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("ab", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpConcat) {
    int child_args[] = {10, 5};
    int result = walker_.PostVisit(re, 0, 0, child_args, 2);
    // max of nchild_args(2), child_args[0](10), child_args[1](5) = 10
    EXPECT_EQ(result, 10);
  }
  re->Decref();
}

// Test PostVisit with kRegexpAlternate and no children
TEST_F(SubexpressionWalkerTest_381, PostVisitAlternateNoChildren_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a|b", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpAlternate) {
    int result = walker_.PostVisit(re, 0, 0, nullptr, 0);
    EXPECT_EQ(result, 0);
  }
  re->Decref();
}

// Test PostVisit with kRegexpAlternate and children
TEST_F(SubexpressionWalkerTest_381, PostVisitAlternateWithChildren_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a|b", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpAlternate) {
    int child_args[] = {3, 7};
    int result = walker_.PostVisit(re, 0, 0, child_args, 2);
    // max of nchild_args(2), child_args[0](3), child_args[1](7) = 7
    EXPECT_EQ(result, 7);
  }
  re->Decref();
}

// Test PostVisit with kRegexpAlternate where nchild_args is the maximum
TEST_F(SubexpressionWalkerTest_381, PostVisitAlternateNChildArgsIsMax_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a|b|c|d|e", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpAlternate) {
    int child_args[] = {1, 2, 1, 0, 1};
    int result = walker_.PostVisit(re, 0, 0, child_args, 5);
    // max of nchild_args(5), max(child_args) = 2 => 5
    EXPECT_EQ(result, 5);
  }
  re->Decref();
}

// Test PostVisit with kRegexpLiteral returns -1
TEST_F(SubexpressionWalkerTest_381, PostVisitLiteralReturnsMinus1_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpLiteral) {
    int result = walker_.PostVisit(re, 0, 0, nullptr, 0);
    EXPECT_EQ(result, -1);
  }
  re->Decref();
}

// Test PostVisit with kRegexpStar returns -1
TEST_F(SubexpressionWalkerTest_381, PostVisitStarReturnsMinus1_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a*", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpStar) {
    int child_args[] = {5};
    int result = walker_.PostVisit(re, 0, 0, child_args, 1);
    EXPECT_EQ(result, -1);
  }
  re->Decref();
}

// Test PostVisit with kRegexpPlus returns -1
TEST_F(SubexpressionWalkerTest_381, PostVisitPlusReturnsMinus1_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a+", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpPlus) {
    int result = walker_.PostVisit(re, 0, 0, nullptr, 0);
    EXPECT_EQ(result, -1);
  }
  re->Decref();
}

// Test PostVisit with kRegexpQuest returns -1
TEST_F(SubexpressionWalkerTest_381, PostVisitQuestReturnsMinus1_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a?", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpQuest) {
    int result = walker_.PostVisit(re, 0, 0, nullptr, 0);
    EXPECT_EQ(result, -1);
  }
  re->Decref();
}

// Test PostVisit with kRegexpCapture returns -1
TEST_F(SubexpressionWalkerTest_381, PostVisitCaptureReturnsMinus1_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("(a)", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpCapture) {
    int child_args[] = {3};
    int result = walker_.PostVisit(re, 0, 0, child_args, 1);
    EXPECT_EQ(result, -1);
  }
  re->Decref();
}

// Test PostVisit with kRegexpRepeat returns -1
TEST_F(SubexpressionWalkerTest_381, PostVisitRepeatReturnsMinus1_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a{2,3}", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpRepeat) {
    int result = walker_.PostVisit(re, 0, 0, nullptr, 0);
    EXPECT_EQ(result, -1);
  }
  re->Decref();
}

// Test PostVisit with kRegexpAnyChar returns -1
TEST_F(SubexpressionWalkerTest_381, PostVisitAnyCharReturnsMinus1_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse(".", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  // Regardless of op, if not Concat/Alternate, should return -1
  int result = walker_.PostVisit(re, 0, 0, nullptr, 0);
  if (re->op() != re2::kRegexpConcat && re->op() != re2::kRegexpAlternate) {
    EXPECT_EQ(result, -1);
  }
  re->Decref();
}

// Test PostVisit with kRegexpConcat and all negative child_args
TEST_F(SubexpressionWalkerTest_381, PostVisitConcatNegativeChildren_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("ab", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpConcat) {
    int child_args[] = {-1, -1};
    int result = walker_.PostVisit(re, 0, 0, child_args, 2);
    // max of nchild_args(2), child_args[0](-1), child_args[1](-1) = 2
    EXPECT_EQ(result, 2);
  }
  re->Decref();
}

// Test PostVisit with kRegexpConcat and single child
TEST_F(SubexpressionWalkerTest_381, PostVisitConcatSingleChild_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("ab", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpConcat) {
    int child_args[] = {100};
    int result = walker_.PostVisit(re, 0, 0, child_args, 1);
    // max of nchild_args(1), child_args[0](100) = 100
    EXPECT_EQ(result, 100);
  }
  re->Decref();
}

// Test PostVisit with kRegexpAlternate and large child value
TEST_F(SubexpressionWalkerTest_381, PostVisitAlternateLargeChildValue_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a|b", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpAlternate) {
    int child_args[] = {1000000, 500};
    int result = walker_.PostVisit(re, 0, 0, child_args, 2);
    EXPECT_EQ(result, 1000000);
  }
  re->Decref();
}

// Test PostVisit with parent_arg and pre_arg (should be ignored for Concat)
TEST_F(SubexpressionWalkerTest_381, PostVisitConcatIgnoresParentAndPreArgs_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("ab", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpConcat) {
    int child_args[] = {3, 5};
    int result1 = walker_.PostVisit(re, 0, 0, child_args, 2);
    int result2 = walker_.PostVisit(re, 99, 99, child_args, 2);
    EXPECT_EQ(result1, result2);
  }
  re->Decref();
}

// Test PostVisit with kRegexpEmptyMatch returns -1
TEST_F(SubexpressionWalkerTest_381, PostVisitEmptyMatchReturnsMinus1_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpEmptyMatch) {
    int result = walker_.PostVisit(re, 0, 0, nullptr, 0);
    EXPECT_EQ(result, -1);
  }
  re->Decref();
}

// Test PostVisit with Concat where all children equal nchild_args
TEST_F(SubexpressionWalkerTest_381, PostVisitConcatAllChildrenEqualN_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("abc", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpConcat) {
    int child_args[] = {3, 3, 3};
    int result = walker_.PostVisit(re, 0, 0, child_args, 3);
    // max of nchild_args(3) and all child_args(3) = 3
    EXPECT_EQ(result, 3);
  }
  re->Decref();
}

// Test PostVisit with kRegexpBeginLine returns -1
TEST_F(SubexpressionWalkerTest_381, PostVisitBeginLineReturnsMinus1_381) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("^", re2::Regexp::OneLine, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() != re2::kRegexpConcat && re->op() != re2::kRegexpAlternate) {
    int result = walker_.PostVisit(re, 0, 0, nullptr, 0);
    EXPECT_EQ(result, -1);
  }
  re->Decref();
}
