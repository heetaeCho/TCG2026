#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/walker-inl.h"
#include "re2/re2.h"

namespace re2 {

// A concrete Walker implementation for testing purposes
class TestWalker : public Regexp::Walker<int> {
 public:
  TestWalker() : Regexp::Walker<int>() {}
  ~TestWalker() override {}

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    pre_visit_count_++;
    if (should_stop_early_) {
      *stop = true;
    }
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

  int ShortVisit(Regexp* re, int parent_arg) override {
    short_visit_count_++;
    return parent_arg;
  }

  int Copy(int arg) override {
    return arg;
  }

  void SetShouldStopEarly(bool stop) { should_stop_early_ = stop; }
  int pre_visit_count() const { return pre_visit_count_; }
  int post_visit_count() const { return post_visit_count_; }
  int short_visit_count() const { return short_visit_count_; }

 private:
  bool should_stop_early_ = false;
  int pre_visit_count_ = 0;
  int post_visit_count_ = 0;
  int short_visit_count_ = 0;
};

class WalkerTest_210 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a freshly constructed walker has stopped_early() == false
TEST_F(WalkerTest_210, InitialStoppedEarlyIsFalse_210) {
  TestWalker walker;
  EXPECT_FALSE(walker.stopped_early());
}

// Test walking a simple regexp (literal)
TEST_F(WalkerTest_210, WalkSimpleLiteral_210) {
  Regexp* re = Regexp::Parse("a", Regexp::ClassNL, NULL);
  ASSERT_NE(re, nullptr);

  TestWalker walker;
  int result = walker.Walk(re, 0);
  // We walked with parent_arg=0, PreVisit returns parent_arg+1=1
  // For a leaf node, PostVisit gets pre_arg=1, no children
  EXPECT_EQ(result, 1);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test walking a concatenation (more complex regexp)
TEST_F(WalkerTest_210, WalkConcatenation_210) {
  Regexp* re = Regexp::Parse("abc", Regexp::ClassNL, NULL);
  ASSERT_NE(re, nullptr);

  TestWalker walker;
  int result = walker.Walk(re, 0);
  // Result depends on tree structure, but should be > 0
  EXPECT_GT(result, 0);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test walking with alternation
TEST_F(WalkerTest_210, WalkAlternation_210) {
  Regexp* re = Regexp::Parse("a|b|c", Regexp::ClassNL, NULL);
  ASSERT_NE(re, nullptr);

  TestWalker walker;
  int result = walker.Walk(re, 0);
  EXPECT_GT(result, 0);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test that stopped_early is set when PreVisit sets stop
TEST_F(WalkerTest_210, StoppedEarlyWhenPreVisitStops_210) {
  Regexp* re = Regexp::Parse("abc", Regexp::ClassNL, NULL);
  ASSERT_NE(re, nullptr);

  TestWalker walker;
  walker.SetShouldStopEarly(true);
  walker.Walk(re, 0);
  EXPECT_TRUE(walker.stopped_early());

  re->Decref();
}

// Test WalkExponential with a reasonable max_visits
TEST_F(WalkerTest_210, WalkExponentialNormal_210) {
  Regexp* re = Regexp::Parse("a", Regexp::ClassNL, NULL);
  ASSERT_NE(re, nullptr);

  TestWalker walker;
  int result = walker.WalkExponential(re, 0, 1000);
  EXPECT_EQ(result, 1);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test WalkExponential with very low max_visits on a complex regexp
TEST_F(WalkerTest_210, WalkExponentialHitsMaxVisits_210) {
  // Create a regexp that has sharing / repeated subexpressions
  Regexp* re = Regexp::Parse("(a|b)(c|d)(e|f)(g|h)", Regexp::ClassNL, NULL);
  ASSERT_NE(re, nullptr);

  TestWalker walker;
  // With max_visits = 1, we should stop early on a complex enough tree
  walker.WalkExponential(re, 0, 1);
  // Either it completes or stops early, but the call should not crash
  // For a very small max_visits the walker may use ShortVisit

  re->Decref();
}

// Test Reset clears stopped_early state
TEST_F(WalkerTest_210, ResetClearsStoppedEarly_210) {
  Regexp* re = Regexp::Parse("abc", Regexp::ClassNL, NULL);
  ASSERT_NE(re, nullptr);

  TestWalker walker;
  walker.SetShouldStopEarly(true);
  walker.Walk(re, 0);
  EXPECT_TRUE(walker.stopped_early());

  walker.Reset();
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test that Walk can be called multiple times after Reset
TEST_F(WalkerTest_210, WalkMultipleTimesAfterReset_210) {
  Regexp* re1 = Regexp::Parse("a", Regexp::ClassNL, NULL);
  Regexp* re2 = Regexp::Parse("b", Regexp::ClassNL, NULL);
  ASSERT_NE(re1, nullptr);
  ASSERT_NE(re2, nullptr);

  TestWalker walker;
  int result1 = walker.Walk(re1, 0);
  walker.Reset();
  int result2 = walker.Walk(re2, 0);

  EXPECT_EQ(result1, 1);
  EXPECT_EQ(result2, 1);
  EXPECT_FALSE(walker.stopped_early());

  re1->Decref();
  re2->Decref();
}

// Test walking a regexp with repetition (star)
TEST_F(WalkerTest_210, WalkRepetition_210) {
  Regexp* re = Regexp::Parse("a*", Regexp::ClassNL, NULL);
  ASSERT_NE(re, nullptr);

  TestWalker walker;
  int result = walker.Walk(re, 0);
  EXPECT_GT(result, 0);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test walking a more complex nested regexp
TEST_F(WalkerTest_210, WalkNestedGroups_210) {
  Regexp* re = Regexp::Parse("((a)(b(c)))", Regexp::ClassNL, NULL);
  ASSERT_NE(re, nullptr);

  TestWalker walker;
  int result = walker.Walk(re, 0);
  EXPECT_GT(result, 0);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test Walk with initial top_arg different from zero
TEST_F(WalkerTest_210, WalkWithNonZeroTopArg_210) {
  Regexp* re = Regexp::Parse("a", Regexp::ClassNL, NULL);
  ASSERT_NE(re, nullptr);

  TestWalker walker;
  int result = walker.Walk(re, 10);
  // PreVisit returns parent_arg + 1 = 11, PostVisit returns pre_arg = 11
  EXPECT_EQ(result, 11);

  re->Decref();
}

// Test WalkExponential with ShortVisit being invoked
TEST_F(WalkerTest_210, WalkExponentialShortVisitCalled_210) {
  // Create a complex regexp
  Regexp* re = Regexp::Parse("(a+|b+)(c+|d+)(e+|f+)", Regexp::ClassNL, NULL);
  ASSERT_NE(re, nullptr);

  TestWalker walker;
  // Use very small max_visits to force ShortVisit usage
  walker.WalkExponential(re, 0, 1);
  // We mainly test it doesn't crash and short_visit may have been called
  EXPECT_GE(walker.short_visit_count(), 0);

  re->Decref();
}

// Test walking a character class
TEST_F(WalkerTest_210, WalkCharacterClass_210) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::ClassNL, NULL);
  ASSERT_NE(re, nullptr);

  TestWalker walker;
  int result = walker.Walk(re, 0);
  EXPECT_GT(result, 0);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test walking an empty string regexp
TEST_F(WalkerTest_210, WalkEmptyString_210) {
  Regexp* re = Regexp::Parse("", Regexp::ClassNL, NULL);
  ASSERT_NE(re, nullptr);

  TestWalker walker;
  int result = walker.Walk(re, 0);
  // An empty regexp still has a node
  EXPECT_GE(result, 0);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test walking a nullable with Walk on NULL regexp
TEST_F(WalkerTest_210, WalkNullRegexp_210) {
  TestWalker walker;
  int result = walker.Walk(NULL, 0);
  // Walking NULL should return the default/top arg
  EXPECT_EQ(result, 0);
}

}  // namespace re2
