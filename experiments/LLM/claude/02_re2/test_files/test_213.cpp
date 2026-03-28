#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/walker-inl.h"
#include "re2/re2.h"

namespace re2 {

// A concrete Walker implementation for testing purposes
class TestIntWalker : public Regexp::Walker<int> {
 public:
  TestIntWalker() : Regexp::Walker<int>() {}
  ~TestIntWalker() override {}

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    return parent_arg + 1;
  }

  int PostVisit(Regexp* re, int parent_arg, int pre_arg,
                int* child_args, int nchild_args) override {
    int sum = pre_arg;
    for (int i = 0; i < nchild_args; i++) {
      sum += child_args[i];
    }
    return sum;
  }

  int ShortVisit(Regexp* re, int parent_arg) override {
    return parent_arg;
  }
};

// A walker that stops early
class StoppingWalker : public Regexp::Walker<int> {
 public:
  StoppingWalker() : Regexp::Walker<int>() {}
  ~StoppingWalker() override {}

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    if (parent_arg > 2) {
      *stop = true;
      return parent_arg;
    }
    return parent_arg + 1;
  }

  int PostVisit(Regexp* re, int parent_arg, int pre_arg,
                int* child_args, int nchild_args) override {
    return pre_arg;
  }

  int ShortVisit(Regexp* re, int parent_arg) override {
    return parent_arg;
  }
};

// A walker that uses Copy
class CopyTestWalker : public Regexp::Walker<int> {
 public:
  CopyTestWalker() : Regexp::Walker<int>() {}
  ~CopyTestWalker() override {}

  int Copy(int arg) override {
    return arg * 2;
  }

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    return parent_arg + 1;
  }

  int PostVisit(Regexp* re, int parent_arg, int pre_arg,
                int* child_args, int nchild_args) override {
    return pre_arg;
  }

  int ShortVisit(Regexp* re, int parent_arg) override {
    return parent_arg;
  }
};

class WalkerTest_213 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(WalkerTest_213, DefaultCopyReturnsArg_213) {
  TestIntWalker walker;
  // Default Copy implementation just returns the argument
  EXPECT_EQ(42, walker.Copy(42));
  EXPECT_EQ(0, walker.Copy(0));
  EXPECT_EQ(-1, walker.Copy(-1));
}

TEST_F(WalkerTest_213, WalkSimpleLiteral_213) {
  TestIntWalker walker;
  // Parse a simple regexp - a single literal character
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  int result = walker.Walk(re, 0);
  // With a single literal, PreVisit gets 0+1=1, PostVisit returns 1
  EXPECT_GE(result, 1);
  
  re->Decref();
}

TEST_F(WalkerTest_213, WalkNullRegexp_213) {
  TestIntWalker walker;
  // Walking a null regexp should return the top_arg
  int result = walker.Walk(nullptr, 42);
  EXPECT_EQ(42, result);
}

TEST_F(WalkerTest_213, StoppedEarlyInitiallyFalse_213) {
  TestIntWalker walker;
  EXPECT_FALSE(walker.stopped_early());
}

TEST_F(WalkerTest_213, WalkConcatenation_213) {
  TestIntWalker walker;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  int result = walker.Walk(re, 0);
  // Should visit all nodes
  EXPECT_GT(result, 0);
  
  re->Decref();
}

TEST_F(WalkerTest_213, WalkAlternation_213) {
  TestIntWalker walker;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  int result = walker.Walk(re, 0);
  EXPECT_GT(result, 0);
  
  re->Decref();
}

TEST_F(WalkerTest_213, WalkExponentialWithLimit_213) {
  TestIntWalker walker;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)d", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  int result = walker.WalkExponential(re, 0, 100);
  EXPECT_GT(result, 0);
  EXPECT_FALSE(walker.stopped_early());
  
  re->Decref();
}

TEST_F(WalkerTest_213, WalkExponentialExceedsLimit_213) {
  TestIntWalker walker;
  RegexpStatus status;
  // Create a more complex regexp
  Regexp* re = Regexp::Parse("(a|b)(c|d)(e|f)(g|h)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  // Use a very small limit to trigger stopped_early
  int result = walker.WalkExponential(re, 0, 1);
  // With max_visits=1, it should stop early
  EXPECT_TRUE(walker.stopped_early());
  
  re->Decref();
}

TEST_F(WalkerTest_213, ResetClearsState_213) {
  TestIntWalker walker;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)(c|d)(e|f)(g|h)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  walker.WalkExponential(re, 0, 1);
  EXPECT_TRUE(walker.stopped_early());
  
  walker.Reset();
  // After reset, stopped_early should be false
  EXPECT_FALSE(walker.stopped_early());
  
  re->Decref();
}

TEST_F(WalkerTest_213, WalkRepetition_213) {
  TestIntWalker walker;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  int result = walker.Walk(re, 0);
  EXPECT_GT(result, 0);
  
  re->Decref();
}

TEST_F(WalkerTest_213, WalkNestedGroups_213) {
  TestIntWalker walker;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  int result = walker.Walk(re, 0);
  EXPECT_GT(result, 0);
  
  re->Decref();
}

TEST_F(WalkerTest_213, WalkCharacterClass_213) {
  TestIntWalker walker;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  int result = walker.Walk(re, 0);
  EXPECT_GT(result, 0);
  
  re->Decref();
}

TEST_F(WalkerTest_213, WalkComplexRegexp_213) {
  TestIntWalker walker;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(foo|bar)+baz[0-9]*", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  int result = walker.Walk(re, 0);
  EXPECT_GT(result, 0);
  EXPECT_FALSE(walker.stopped_early());
  
  re->Decref();
}

TEST_F(WalkerTest_213, WalkWithDifferentTopArg_213) {
  TestIntWalker walker;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  int result1 = walker.Walk(re, 0);
  walker.Reset();
  int result2 = walker.Walk(re, 10);
  
  // With parent_arg=10, the result should be larger
  EXPECT_GT(result2, result1);
  
  re->Decref();
}

TEST_F(WalkerTest_213, WalkExponentialHighLimit_213) {
  TestIntWalker walker;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  int result = walker.WalkExponential(re, 0, 1000000);
  EXPECT_GT(result, 0);
  EXPECT_FALSE(walker.stopped_early());
  
  re->Decref();
}

TEST_F(WalkerTest_213, CustomCopyOverride_213) {
  CopyTestWalker walker;
  // Custom Copy doubles the argument
  EXPECT_EQ(84, walker.Copy(42));
  EXPECT_EQ(0, walker.Copy(0));
  EXPECT_EQ(-2, walker.Copy(-1));
}

TEST_F(WalkerTest_213, MultipleWalksWithReset_213) {
  TestIntWalker walker;
  RegexpStatus status;
  Regexp* re1 = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_TRUE(re1 != nullptr);
  Regexp* re2 = Regexp::Parse("b|c", Regexp::LikePerl, &status);
  ASSERT_TRUE(re2 != nullptr);
  
  int result1 = walker.Walk(re1, 0);
  walker.Reset();
  int result2 = walker.Walk(re2, 0);
  
  EXPECT_GT(result1, 0);
  EXPECT_GT(result2, 0);
  
  re1->Decref();
  re2->Decref();
}

TEST_F(WalkerTest_213, WalkDotStar_213) {
  TestIntWalker walker;
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  int result = walker.Walk(re, 0);
  EXPECT_GT(result, 0);
  
  re->Decref();
}

TEST_F(WalkerTest_213, WalkEmptyGroup_213) {
  TestIntWalker walker;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("()", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  int result = walker.Walk(re, 0);
  EXPECT_GE(result, 0);
  
  re->Decref();
}

TEST_F(WalkerTest_213, WalkQuestionMark_213) {
  TestIntWalker walker;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  int result = walker.Walk(re, 0);
  EXPECT_GT(result, 0);
  
  re->Decref();
}

}  // namespace re2
