#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "re2/walker-inl.h"

namespace re2 {

// A concrete Walker implementation for testing purposes.
// We treat the Walker base class as a black box and only override
// the virtual methods to observe behavior.
class TestWalker : public Regexp::Walker<int> {
 public:
  TestWalker() : pre_visit_count_(0), post_visit_count_(0), short_visit_count_(0), copy_count_(0) {}

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
    copy_count_++;
    return arg;
  }

  int ShortVisit(Regexp* re, int parent_arg) override {
    short_visit_count_++;
    return parent_arg;
  }

  int pre_visit_count() const { return pre_visit_count_; }
  int post_visit_count() const { return post_visit_count_; }
  int short_visit_count() const { return short_visit_count_; }
  int copy_count() const { return copy_count_; }

 private:
  int pre_visit_count_;
  int post_visit_count_;
  int short_visit_count_;
  int copy_count_;
};

// A Walker that stops early during PreVisit
class StoppingWalker : public Regexp::Walker<int> {
 public:
  StoppingWalker() {}

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    *stop = true;
    return parent_arg;
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

class WalkerTest_592 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  Regexp* ParseRegexp(const char* pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    return re;
  }
};

TEST_F(WalkerTest_592, ConstructorInitializesStoppedEarlyToFalse_592) {
  TestWalker walker;
  EXPECT_FALSE(walker.stopped_early());
}

TEST_F(WalkerTest_592, WalkSimpleLiteral_592) {
  TestWalker walker;
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  // PreVisit should be called at least once
  EXPECT_GE(walker.pre_visit_count(), 1);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

TEST_F(WalkerTest_592, WalkNullRegexp_592) {
  TestWalker walker;
  int result = walker.Walk(nullptr, 0);
  // Walking a null regexp should return the default/top arg
  EXPECT_EQ(result, 0);
}

TEST_F(WalkerTest_592, WalkComplexRegexp_592) {
  TestWalker walker;
  Regexp* re = ParseRegexp("a(b|c)d+");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  // Multiple nodes should be visited
  EXPECT_GE(walker.pre_visit_count(), 1);
  EXPECT_GE(walker.post_visit_count(), 1);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

TEST_F(WalkerTest_592, WalkStopsEarly_592) {
  StoppingWalker walker;
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 42);
  EXPECT_TRUE(walker.stopped_early());

  re->Decref();
}

TEST_F(WalkerTest_592, ResetClearsState_592) {
  TestWalker walker;
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);

  walker.Walk(re, 0);
  walker.Reset();
  // After reset, stopped_early should be false
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

TEST_F(WalkerTest_592, ResetAfterStoppedEarly_592) {
  StoppingWalker walker;
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);

  walker.Walk(re, 0);
  EXPECT_TRUE(walker.stopped_early());

  walker.Reset();
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

TEST_F(WalkerTest_592, WalkExponentialNormal_592) {
  TestWalker walker;
  Regexp* re = ParseRegexp("a(b|c)");
  ASSERT_NE(re, nullptr);

  int result = walker.WalkExponential(re, 0, 1000);
  EXPECT_FALSE(walker.stopped_early());
  EXPECT_GE(walker.pre_visit_count(), 1);

  re->Decref();
}

TEST_F(WalkerTest_592, WalkExponentialWithLowMaxVisits_592) {
  TestWalker walker;
  // Create a complex regexp that would require many visits
  Regexp* re = ParseRegexp("(a|b)(c|d)(e|f)(g|h)");
  ASSERT_NE(re, nullptr);

  int result = walker.WalkExponential(re, 0, 1);
  // With very low max_visits, it may stop early and use ShortVisit
  // The exact behavior depends on the implementation, but we can check
  // stopped_early flag or short_visit_count
  // Either it completed or stopped early
  // Just verify it doesn't crash and returns a value

  re->Decref();
}

TEST_F(WalkerTest_592, WalkExponentialNullRegexp_592) {
  TestWalker walker;
  int result = walker.WalkExponential(nullptr, 0, 100);
  EXPECT_EQ(result, 0);
}

TEST_F(WalkerTest_592, WalkMultipleTimes_592) {
  TestWalker walker;
  Regexp* re1 = ParseRegexp("a");
  Regexp* re2 = ParseRegexp("b");
  ASSERT_NE(re1, nullptr);
  ASSERT_NE(re2, nullptr);

  walker.Walk(re1, 0);
  int count_after_first = walker.pre_visit_count();
  EXPECT_GE(count_after_first, 1);

  walker.Walk(re2, 0);
  EXPECT_GT(walker.pre_visit_count(), count_after_first);

  re1->Decref();
  re2->Decref();
}

TEST_F(WalkerTest_592, WalkDeepNestedRegexp_592) {
  TestWalker walker;
  // Create a moderately nested regexp
  Regexp* re = ParseRegexp("((((a))))");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  EXPECT_GE(walker.pre_visit_count(), 1);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

TEST_F(WalkerTest_592, WalkAlternation_592) {
  TestWalker walker;
  Regexp* re = ParseRegexp("a|b|c|d|e");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  // Should visit all alternatives
  EXPECT_GE(walker.pre_visit_count(), 5);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

TEST_F(WalkerTest_592, WalkRepetition_592) {
  TestWalker walker;
  Regexp* re = ParseRegexp("a{2,5}");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  EXPECT_GE(walker.pre_visit_count(), 1);

  re->Decref();
}

TEST_F(WalkerTest_592, WalkCharacterClass_592) {
  TestWalker walker;
  Regexp* re = ParseRegexp("[a-z]");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  EXPECT_GE(walker.pre_visit_count(), 1);

  re->Decref();
}

TEST_F(WalkerTest_592, WalkEmptyRegexp_592) {
  TestWalker walker;
  Regexp* re = ParseRegexp("");
  if (re != nullptr) {
    int result = walker.Walk(re, 0);
    // Just verify it doesn't crash
    re->Decref();
  }
}

TEST_F(WalkerTest_592, WalkWithNonZeroTopArg_592) {
  TestWalker walker;
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 100);
  // The result should reflect that we started with 100
  // PreVisit adds 1 to parent_arg, so we expect at least 101
  EXPECT_GE(result, 101);

  re->Decref();
}

TEST_F(WalkerTest_592, StoppedEarlyInitialState_592) {
  TestWalker walker;
  EXPECT_FALSE(walker.stopped_early());
}

TEST_F(WalkerTest_592, WalkExponentialZeroMaxVisits_592) {
  TestWalker walker;
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);

  // With 0 max visits, should use ShortVisit immediately
  int result = walker.WalkExponential(re, 0, 0);
  // Should stop early since max_visits is 0
  EXPECT_TRUE(walker.stopped_early());

  re->Decref();
}

TEST_F(WalkerTest_592, MultipleResetCalls_592) {
  TestWalker walker;
  walker.Reset();
  walker.Reset();
  EXPECT_FALSE(walker.stopped_early());
}

TEST_F(WalkerTest_592, WalkConcatenation_592) {
  TestWalker walker;
  Regexp* re = ParseRegexp("abcdef");
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  EXPECT_GE(walker.pre_visit_count(), 1);
  EXPECT_GE(walker.post_visit_count(), 1);

  re->Decref();
}

}  // namespace re2
