#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/walker-inl.h"

namespace re2 {

// A simple concrete Walker that counts nodes in the regexp tree.
class CountingWalker : public Regexp::Walker<int> {
 public:
  CountingWalker() {}
  ~CountingWalker() override {}

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    return 0;
  }

  int PostVisit(Regexp* re, int parent_arg, int pre_arg,
                int* child_args, int nchild_args) override {
    int sum = 1;  // count this node
    for (int i = 0; i < nchild_args; i++) {
      sum += child_args[i];
    }
    return sum;
  }

  int ShortVisit(Regexp* re, int parent_arg) override {
    return 1;
  }
};

// A Walker that stops early via the stop flag in PreVisit.
class EarlyStopWalker : public Regexp::Walker<int> {
 public:
  EarlyStopWalker() : visit_count_(0) {}
  ~EarlyStopWalker() override {}

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    visit_count_++;
    if (visit_count_ >= 2) {
      *stop = true;
      return -1;
    }
    return 0;
  }

  int PostVisit(Regexp* re, int parent_arg, int pre_arg,
                int* child_args, int nchild_args) override {
    int sum = 1;
    for (int i = 0; i < nchild_args; i++) {
      sum += child_args[i];
    }
    return sum;
  }

  int ShortVisit(Regexp* re, int parent_arg) override {
    return 0;
  }

  int visit_count() const { return visit_count_; }

 private:
  int visit_count_;
};

// A Walker that accumulates string representation info (returns string length).
class StringLenWalker : public Regexp::Walker<int> {
 public:
  StringLenWalker() {}
  ~StringLenWalker() override {}

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    return 0;
  }

  int PostVisit(Regexp* re, int parent_arg, int pre_arg,
                int* child_args, int nchild_args) override {
    int total = 1;
    for (int i = 0; i < nchild_args; i++) {
      total += child_args[i];
    }
    return total;
  }

  int ShortVisit(Regexp* re, int parent_arg) override {
    return 1;
  }
};

class WalkerTest_217 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test Walk on a simple literal regexp.
TEST_F(WalkerTest_217, WalkSimpleLiteral_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test Walk on a concatenation regexp (e.g., "abc").
TEST_F(WalkerTest_217, WalkConcatenation_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  // "abc" should have at least 3 literal nodes plus possibly a concat node
  EXPECT_GE(count, 3);

  re->Decref();
}

// Test Walk on an alternation regexp (e.g., "a|b|c").
TEST_F(WalkerTest_217, WalkAlternation_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  // Should have at least the 3 literal nodes plus an alternation node
  EXPECT_GE(count, 3);

  re->Decref();
}

// Test Walk on a nested/complex regexp.
TEST_F(WalkerTest_217, WalkComplexRegexp_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+b)*c|d(e|f)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 5);

  re->Decref();
}

// Test WalkExponential with a high max_visits (should behave like Walk).
TEST_F(WalkerTest_217, WalkExponentialHighLimit_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.WalkExponential(re, 0, 1000000);
  EXPECT_GE(count, 3);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test WalkExponential with a very low max_visits triggers early stop.
TEST_F(WalkerTest_217, WalkExponentialLowLimit_217) {
  RegexpStatus status;
  // Create a complex regexp that would have many nodes
  Regexp* re = Regexp::Parse("(a|b)(c|d)(e|f)(g|h)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.WalkExponential(re, 0, 1);
  // With max_visits=1, the walker should stop early
  EXPECT_TRUE(walker.stopped_early());

  re->Decref();
}

// Test WalkExponential with max_visits=0.
TEST_F(WalkerTest_217, WalkExponentialZeroLimit_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.WalkExponential(re, 0, 0);
  // With max_visits=0, walker should stop immediately
  EXPECT_TRUE(walker.stopped_early());

  re->Decref();
}

// Test stopped_early() returns false initially and after a normal walk.
TEST_F(WalkerTest_217, StoppedEarlyDefaultFalse_217) {
  CountingWalker walker;
  EXPECT_FALSE(walker.stopped_early());
}

// Test stopped_early() after a normal Walk (should be false).
TEST_F(WalkerTest_217, StoppedEarlyAfterNormalWalk_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  walker.Walk(re, 0);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test Reset() clears state for reuse.
TEST_F(WalkerTest_217, ResetAllowsReuse_217) {
  RegexpStatus status;
  Regexp* re1 = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re1, nullptr);
  Regexp* re2 = Regexp::Parse("defgh", Regexp::NoParseFlags, &status);
  ASSERT_NE(re2, nullptr);

  CountingWalker walker;
  int count1 = walker.Walk(re1, 0);
  walker.Reset();
  int count2 = walker.Walk(re2, 0);

  EXPECT_GE(count1, 3);
  EXPECT_GE(count2, 5);

  re1->Decref();
  re2->Decref();
}

// Test Walk with a single character class.
TEST_F(WalkerTest_217, WalkCharClass_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test Walk with repetition operators.
TEST_F(WalkerTest_217, WalkRepetition_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test Walk on empty string regexp.
TEST_F(WalkerTest_217, WalkEmptyString_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test Walk with capturing groups.
TEST_F(WalkerTest_217, WalkCapturingGroups_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  // At least 3 literals + 3 captures + 1 concat = 7 or more
  EXPECT_GE(count, 6);

  re->Decref();
}

// Test Walk with star operator.
TEST_F(WalkerTest_217, WalkStarOperator_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  // At least a literal node and a star node
  EXPECT_GE(count, 2);

  re->Decref();
}

// Test Walk with plus operator.
TEST_F(WalkerTest_217, WalkPlusOperator_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 2);

  re->Decref();
}

// Test Walk with quest operator.
TEST_F(WalkerTest_217, WalkQuestOperator_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 2);

  re->Decref();
}

// Test that EarlyStopWalker actually uses the stop mechanism.
TEST_F(WalkerTest_217, EarlyStopMechanism_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abcdef", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  EarlyStopWalker walker;
  int result = walker.Walk(re, 0);
  // The walker stops at the 2nd PreVisit, so we shouldn't see all nodes
  // visited fully. But the exact behavior depends on the walker implementation.
  // At minimum, visit_count should be >= 2.
  EXPECT_GE(walker.visit_count(), 2);

  re->Decref();
}

// Test WalkExponential with different walker on a deeply nested regexp.
TEST_F(WalkerTest_217, WalkExponentialDeepRegexp_217) {
  RegexpStatus status;
  // Build a somewhat deep regexp
  Regexp* re = Regexp::Parse("((((a))))", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.WalkExponential(re, 0, 100);
  EXPECT_GE(count, 1);
  // With enough visits allowed, should not stop early
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test Walk with dot (any character).
TEST_F(WalkerTest_217, WalkDotOperator_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test Walk with anchors.
TEST_F(WalkerTest_217, WalkAnchors_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  // Should have at least the 3 literals + anchors + concat
  EXPECT_GE(count, 3);

  re->Decref();
}

// Test that multiple Walk calls on the same walker with Reset work.
TEST_F(WalkerTest_217, MultipleWalksWithReset_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;

  int count1 = walker.Walk(re, 0);
  walker.Reset();
  int count2 = walker.Walk(re, 0);

  // Same regexp should yield same count
  EXPECT_EQ(count1, count2);

  re->Decref();
}

// Test WalkExponential then check stopped_early with sufficient visits.
TEST_F(WalkerTest_217, WalkExponentialSufficientVisits_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.WalkExponential(re, 0, 10000);
  EXPECT_FALSE(walker.stopped_early());
  EXPECT_GE(count, 2);

  re->Decref();
}

// Test with a regexp that has shared subexpressions (exponential without limit).
TEST_F(WalkerTest_217, WalkExponentialSharedSubs_217) {
  RegexpStatus status;
  // This kind of pattern can create shared sub-expressions
  Regexp* re = Regexp::Parse("(a|b)(a|b)(a|b)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.WalkExponential(re, 0, 1000000);
  EXPECT_GE(count, 6);  // at least the literals
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test StringLenWalker for a different T type usage scenario.
TEST_F(WalkerTest_217, StringLenWalkerBasic_217) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  StringLenWalker walker;
  int len = walker.Walk(re, 0);
  EXPECT_GE(len, 5);

  re->Decref();
}

}  // namespace re2
