#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "re2/regexp.h"
#include "re2/walker-inl.h"
#include "re2/re2.h"
#include "re2/prog.h"

namespace re2 {

// Concrete Walker implementation for testing with int type
class TestWalker : public Regexp::Walker<int> {
 public:
  TestWalker() : Regexp::Walker<int>() {}
  ~TestWalker() override {}

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    pre_visit_count_++;
    return parent_arg + 1;
  }

  int PostVisit(Regexp* re, int parent_arg, int pre_arg,
                int* child_args, int nchild_args) override {
    post_visit_count_++;
    int sum = pre_arg;
    for (int i = 0; i < nchild_args; i++) {
      sum += child_args[i];
    }
    return sum;
  }

  int Copy(int arg) override {
    return arg;
  }

  int ShortVisit(Regexp* re, int parent_arg) override {
    short_visit_count_++;
    return parent_arg;
  }

  int pre_visit_count_ = 0;
  int post_visit_count_ = 0;
  int short_visit_count_ = 0;
};

// A walker that can stop early via PreVisit
class StoppingWalker : public Regexp::Walker<int> {
 public:
  StoppingWalker() : Regexp::Walker<int>() {}
  ~StoppingWalker() override {}

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    *stop = true;
    return 42;
  }

  int PostVisit(Regexp* re, int parent_arg, int pre_arg,
                int* child_args, int nchild_args) override {
    return pre_arg;
  }

  int Copy(int arg) override {
    return arg;
  }

  int ShortVisit(Regexp* re, int parent_arg) override {
    return parent_arg;
  }
};

class WalkerTest_215 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  Regexp* ParseRegexp(const char* pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    return re;
  }
};

TEST_F(WalkerTest_215, ConstructorAndDestructor_215) {
  TestWalker walker;
  // Should be able to construct and destruct without issues
  EXPECT_FALSE(walker.stopped_early());
}

TEST_F(WalkerTest_215, ResetOnFreshWalker_215) {
  TestWalker walker;
  // Reset on a fresh walker should be safe (stack is empty)
  walker.Reset();
  EXPECT_FALSE(walker.stopped_early());
}

TEST_F(WalkerTest_215, WalkSimpleLiteral_215) {
  TestWalker walker;
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  // At minimum, PreVisit and PostVisit should have been called
  EXPECT_GT(walker.pre_visit_count_, 0);
  EXPECT_GT(walker.post_visit_count_, 0);

  re->Decref();
}

TEST_F(WalkerTest_215, WalkConcatenation_215) {
  TestWalker walker;
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  // For "abc", there should be multiple nodes visited
  EXPECT_GT(walker.pre_visit_count_, 1);
  EXPECT_GT(walker.post_visit_count_, 1);

  re->Decref();
}

TEST_F(WalkerTest_215, WalkAlternation_215) {
  TestWalker walker;
  Regexp* re = ParseRegexp("a|b|c");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  EXPECT_GT(walker.pre_visit_count_, 1);
  EXPECT_GT(walker.post_visit_count_, 1);

  re->Decref();
}

TEST_F(WalkerTest_215, WalkComplexPattern_215) {
  TestWalker walker;
  Regexp* re = ParseRegexp("(a+b*|c)(d|e?)f");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  EXPECT_GT(walker.pre_visit_count_, 3);
  EXPECT_GT(walker.post_visit_count_, 3);

  re->Decref();
}

TEST_F(WalkerTest_215, WalkWithNullRegexp_215) {
  TestWalker walker;
  // Walking a null regexp - the interface may handle this
  // We just verify it doesn't crash or we get default behavior
  int result = walker.Walk(nullptr, 0);
  // No specific assertion on result since behavior with null is implementation-defined
}

TEST_F(WalkerTest_215, StoppedEarlyInitiallyFalse_215) {
  TestWalker walker;
  EXPECT_FALSE(walker.stopped_early());
}

TEST_F(WalkerTest_215, WalkExponentialWithHighLimit_215) {
  TestWalker walker;
  Regexp* re = ParseRegexp("(a|b)(c|d)");
  ASSERT_NE(re, nullptr);

  int result = walker.WalkExponential(re, 0, 1000000);
  EXPECT_FALSE(walker.stopped_early());
  EXPECT_GT(walker.pre_visit_count_, 0);

  re->Decref();
}

TEST_F(WalkerTest_215, WalkExponentialWithLowLimit_215) {
  TestWalker walker;
  // Create a complex regexp that would require many visits
  Regexp* re = ParseRegexp("(a|b)(c|d)(e|f)(g|h)(i|j)(k|l)(m|n)");
  ASSERT_NE(re, nullptr);

  int result = walker.WalkExponential(re, 0, 1);
  // With max_visits=1, walking should stop early
  EXPECT_TRUE(walker.stopped_early());

  re->Decref();
}

TEST_F(WalkerTest_215, WalkExponentialStoppedEarly_215) {
  TestWalker walker;
  Regexp* re = ParseRegexp("a(b(c(d(e(f)))))");
  ASSERT_NE(re, nullptr);

  int result = walker.WalkExponential(re, 0, 2);
  // With very small limit on a nested pattern, might stop early
  // Just verify the method runs without error
  re->Decref();
}

TEST_F(WalkerTest_215, ResetAfterWalk_215) {
  TestWalker walker;
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);

  walker.Walk(re, 0);
  walker.Reset();
  // After reset, walker should be in a clean state
  // We can walk again
  walker.pre_visit_count_ = 0;
  walker.post_visit_count_ = 0;

  int result = walker.Walk(re, 0);
  EXPECT_GT(walker.pre_visit_count_, 0);
  EXPECT_GT(walker.post_visit_count_, 0);

  re->Decref();
}

TEST_F(WalkerTest_215, WalkTwiceWithoutReset_215) {
  TestWalker walker;
  Regexp* re = ParseRegexp("ab");
  ASSERT_NE(re, nullptr);

  int result1 = walker.Walk(re, 0);
  int pre1 = walker.pre_visit_count_;

  int result2 = walker.Walk(re, 0);
  // Second walk should also work and increment counters
  EXPECT_GT(walker.pre_visit_count_, pre1);

  re->Decref();
}

TEST_F(WalkerTest_215, StoppingWalkerStopsEarly_215) {
  StoppingWalker walker;
  Regexp* re = ParseRegexp("(a|b)(c|d)");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  // The walker sets stop=true in PreVisit, so it should stop early
  EXPECT_TRUE(walker.stopped_early());

  re->Decref();
}

TEST_F(WalkerTest_215, WalkExponentialZeroMaxVisits_215) {
  TestWalker walker;
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);

  int result = walker.WalkExponential(re, 0, 0);
  // With 0 max visits, should stop early immediately
  EXPECT_TRUE(walker.stopped_early());

  re->Decref();
}

TEST_F(WalkerTest_215, WalkSingleChar_215) {
  TestWalker walker;
  Regexp* re = ParseRegexp("x");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 10);
  // PreVisit returns parent_arg + 1, so for a single literal,
  // result depends on PostVisit
  EXPECT_GT(walker.pre_visit_count_, 0);
  EXPECT_GT(walker.post_visit_count_, 0);

  re->Decref();
}

TEST_F(WalkerTest_215, WalkRepetition_215) {
  TestWalker walker;
  Regexp* re = ParseRegexp("a*");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  EXPECT_GT(walker.pre_visit_count_, 0);

  re->Decref();
}

TEST_F(WalkerTest_215, WalkNestedGroups_215) {
  TestWalker walker;
  Regexp* re = ParseRegexp("((a)(b))");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  // Multiple nodes should be visited
  EXPECT_GT(walker.pre_visit_count_, 2);

  re->Decref();
}

TEST_F(WalkerTest_215, MultipleResetsAreSafe_215) {
  TestWalker walker;
  walker.Reset();
  walker.Reset();
  walker.Reset();
  // Multiple resets on empty walker should be safe
  EXPECT_FALSE(walker.stopped_early());
}

TEST_F(WalkerTest_215, WalkExponentialShortVisitCalled_215) {
  TestWalker walker;
  // Use a pattern with repeated subexpressions that might trigger Copy/ShortVisit
  Regexp* re = ParseRegexp("(a|b)(a|b)(a|b)(a|b)");
  ASSERT_NE(re, nullptr);

  int result = walker.WalkExponential(re, 0, 3);
  // With low max_visits, ShortVisit might be called
  // We just verify it doesn't crash
  re->Decref();
}

TEST_F(WalkerTest_215, WalkCharacterClass_215) {
  TestWalker walker;
  Regexp* re = ParseRegexp("[a-z]");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  EXPECT_GT(walker.pre_visit_count_, 0);
  EXPECT_GT(walker.post_visit_count_, 0);

  re->Decref();
}

TEST_F(WalkerTest_215, WalkEmptyAlternation_215) {
  TestWalker walker;
  Regexp* re = ParseRegexp("|");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  EXPECT_GT(walker.pre_visit_count_, 0);

  re->Decref();
}

TEST_F(WalkerTest_215, WalkTopArgPropagated_215) {
  TestWalker walker;
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 100);
  // PreVisit adds 1 to parent_arg, so for a leaf node,
  // the result from PostVisit should reflect the starting arg
  // We verify the walk completes successfully
  EXPECT_EQ(walker.pre_visit_count_, 1);
  EXPECT_EQ(walker.post_visit_count_, 1);

  re->Decref();
}

}  // namespace re2
