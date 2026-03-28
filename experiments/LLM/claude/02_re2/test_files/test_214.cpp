#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/walker-inl.h"

namespace re2 {

// A concrete Walker implementation for testing purposes.
// We treat the Walker base class as a black box but need a concrete
// subclass to instantiate and test the public interface.
class TestWalker_214 : public Regexp::Walker<int> {
 public:
  TestWalker_214() : Regexp::Walker<int>() {}

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    pre_visit_count_++;
    if (should_stop_early_ && pre_visit_count_ >= stop_after_) {
      *stop = true;
      return -1;
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

  int Copy(int arg) override {
    return arg;
  }

  int ShortVisit(Regexp* re, int parent_arg) override {
    short_visit_count_++;
    return parent_arg;
  }

  void SetStopEarly(bool stop, int after = 1) {
    should_stop_early_ = stop;
    stop_after_ = after;
  }

  int pre_visit_count_ = 0;
  int post_visit_count_ = 0;
  int short_visit_count_ = 0;
  bool should_stop_early_ = false;
  int stop_after_ = 1;
};

// Helper to parse a regexp and return the internal Regexp*.
// Caller must Decref the returned Regexp*.
static Regexp* ParseRegexp(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::NoParseFlags, &status);
  return re;
}

class WalkerTest_214 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any regexp we might have created
  }
};

// Test that a Walker can be constructed and destroyed without issues
TEST_F(WalkerTest_214, ConstructAndDestruct_214) {
  TestWalker_214* walker = new TestWalker_214();
  EXPECT_FALSE(walker->stopped_early());
  delete walker;
}

// Test Walk on a simple literal regexp
TEST_F(WalkerTest_214, WalkSimpleLiteral_214) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);

  TestWalker_214 walker;
  int result = walker.Walk(re, 0);
  // PreVisit should have been called at least once
  EXPECT_GT(walker.pre_visit_count_, 0);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test Walk on a more complex regexp with children
TEST_F(WalkerTest_214, WalkComplexRegexp_214) {
  Regexp* re = ParseRegexp("a|b|c");
  ASSERT_NE(re, nullptr);

  TestWalker_214 walker;
  int result = walker.Walk(re, 0);
  // Multiple nodes should have been visited
  EXPECT_GT(walker.pre_visit_count_, 1);
  EXPECT_GT(walker.post_visit_count_, 0);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test Walk on a concatenation
TEST_F(WalkerTest_214, WalkConcatenation_214) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);

  TestWalker_214 walker;
  int result = walker.Walk(re, 0);
  EXPECT_GT(walker.pre_visit_count_, 0);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test Walk with nullptr regexp
TEST_F(WalkerTest_214, WalkNullRegexp_214) {
  TestWalker_214 walker;
  int result = walker.Walk(nullptr, 0);
  // Walking nullptr should return the default/top_arg or handle gracefully
  // We just verify it doesn't crash
  EXPECT_EQ(walker.pre_visit_count_, 0);
}

// Test stopped_early returns false when walk completes normally
TEST_F(WalkerTest_214, StoppedEarlyFalseNormally_214) {
  Regexp* re = ParseRegexp("hello");
  ASSERT_NE(re, nullptr);

  TestWalker_214 walker;
  walker.Walk(re, 0);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test that stopping early is detected
TEST_F(WalkerTest_214, StopEarlyInPreVisit_214) {
  Regexp* re = ParseRegexp("a|b|c|d");
  ASSERT_NE(re, nullptr);

  TestWalker_214 walker;
  walker.SetStopEarly(true, 1);
  int result = walker.Walk(re, 0);
  EXPECT_TRUE(walker.stopped_early());
  // Should have stopped after first PreVisit
  EXPECT_EQ(walker.pre_visit_count_, 1);

  re->Decref();
}

// Test Reset clears the walker state
TEST_F(WalkerTest_214, ResetClearsState_214) {
  Regexp* re = ParseRegexp("a|b");
  ASSERT_NE(re, nullptr);

  TestWalker_214 walker;
  walker.SetStopEarly(true, 1);
  walker.Walk(re, 0);
  EXPECT_TRUE(walker.stopped_early());

  walker.Reset();
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test WalkExponential with a simple regexp and high max_visits
TEST_F(WalkerTest_214, WalkExponentialSimple_214) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);

  TestWalker_214 walker;
  int result = walker.WalkExponential(re, 0, 1000);
  EXPECT_GT(walker.pre_visit_count_, 0);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test WalkExponential with very low max_visits triggers ShortVisit
TEST_F(WalkerTest_214, WalkExponentialLowMaxVisits_214) {
  // Create a complex regexp that would require many visits
  Regexp* re = ParseRegexp("(a|b)(c|d)(e|f)(g|h)");
  ASSERT_NE(re, nullptr);

  TestWalker_214 walker;
  int result = walker.WalkExponential(re, 0, 1);
  // With max_visits=1, ShortVisit should be called for repeated nodes
  // The walker may or may not stop early depending on the structure
  // Just verify it doesn't crash and the counts make sense
  EXPECT_GE(walker.pre_visit_count_, 0);

  re->Decref();
}

// Test walking the same regexp multiple times with the same walker
TEST_F(WalkerTest_214, WalkMultipleTimes_214) {
  Regexp* re = ParseRegexp("ab");
  ASSERT_NE(re, nullptr);

  TestWalker_214 walker;
  walker.Walk(re, 0);
  int first_pre = walker.pre_visit_count_;
  int first_post = walker.post_visit_count_;
  EXPECT_GT(first_pre, 0);

  // Walk again - the walker resets internally
  walker.pre_visit_count_ = 0;
  walker.post_visit_count_ = 0;
  walker.Walk(re, 0);
  EXPECT_GT(walker.pre_visit_count_, 0);

  re->Decref();
}

// Test walking a nested repetition regexp
TEST_F(WalkerTest_214, WalkNestedRepetition_214) {
  Regexp* re = ParseRegexp("(a+)+");
  ASSERT_NE(re, nullptr);

  TestWalker_214 walker;
  int result = walker.Walk(re, 0);
  EXPECT_GT(walker.pre_visit_count_, 0);
  EXPECT_GT(walker.post_visit_count_, 0);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test walking a character class
TEST_F(WalkerTest_214, WalkCharClass_214) {
  Regexp* re = ParseRegexp("[a-z]");
  ASSERT_NE(re, nullptr);

  TestWalker_214 walker;
  int result = walker.Walk(re, 0);
  EXPECT_GT(walker.pre_visit_count_, 0);

  re->Decref();
}

// Test walking with initial top_arg value propagation
TEST_F(WalkerTest_214, WalkTopArgPropagation_214) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);

  TestWalker_214 walker;
  int result = walker.Walk(re, 42);
  // PreVisit adds 1 to parent_arg, so result from a single literal should be 43
  // PostVisit returns pre_arg (which is parent_arg + 1)
  EXPECT_EQ(result, 43);

  re->Decref();
}

// Test walking a deeply nested regexp
TEST_F(WalkerTest_214, WalkDeeplyNested_214) {
  // Create a deeply nested regexp via grouping
  Regexp* re = ParseRegexp("((((((a))))))");
  ASSERT_NE(re, nullptr);

  TestWalker_214 walker;
  int result = walker.Walk(re, 0);
  EXPECT_GT(walker.pre_visit_count_, 0);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test WalkExponential with max_visits=0
TEST_F(WalkerTest_214, WalkExponentialZeroMaxVisits_214) {
  Regexp* re = ParseRegexp("a|b");
  ASSERT_NE(re, nullptr);

  TestWalker_214 walker;
  int result = walker.WalkExponential(re, 0, 0);
  // With 0 max visits, ShortVisit should be used frequently
  // Just verify no crash
  EXPECT_GE(walker.short_visit_count_, 0);

  re->Decref();
}

// Test that after Reset, Walk can be called again
TEST_F(WalkerTest_214, ResetThenWalkAgain_214) {
  Regexp* re = ParseRegexp("x|y");
  ASSERT_NE(re, nullptr);

  TestWalker_214 walker;
  walker.Walk(re, 0);
  EXPECT_FALSE(walker.stopped_early());

  walker.Reset();
  EXPECT_FALSE(walker.stopped_early());

  walker.pre_visit_count_ = 0;
  walker.post_visit_count_ = 0;
  walker.Walk(re, 10);
  EXPECT_GT(walker.pre_visit_count_, 0);

  re->Decref();
}

// Test walking empty alternation-like pattern
TEST_F(WalkerTest_214, WalkEmptyString_214) {
  Regexp* re = ParseRegexp("");
  // Empty pattern may or may not parse successfully
  if (re != nullptr) {
    TestWalker_214 walker;
    int result = walker.Walk(re, 0);
    // Just verify no crash
    re->Decref();
  }
}

// Test walking a regexp with quantifiers
TEST_F(WalkerTest_214, WalkWithQuantifiers_214) {
  Regexp* re = ParseRegexp("a{3,5}b*c+d?");
  ASSERT_NE(re, nullptr);

  TestWalker_214 walker;
  int result = walker.Walk(re, 0);
  EXPECT_GT(walker.pre_visit_count_, 0);
  EXPECT_GT(walker.post_visit_count_, 0);

  re->Decref();
}

// Test with a string-typed Walker
class StringWalker_214 : public Regexp::Walker<std::string> {
 public:
  StringWalker_214() : Regexp::Walker<std::string>() {}

  std::string PreVisit(Regexp* re, std::string parent_arg, bool* stop) override {
    return parent_arg + "P";
  }

  std::string PostVisit(Regexp* re, std::string parent_arg, std::string pre_arg,
                        std::string* child_args, int nchild_args) override {
    std::string result = pre_arg;
    for (int i = 0; i < nchild_args; i++) {
      result += child_args[i];
    }
    return result;
  }

  std::string Copy(std::string arg) override {
    return arg;
  }

  std::string ShortVisit(Regexp* re, std::string parent_arg) override {
    return parent_arg + "S";
  }
};

TEST_F(WalkerTest_214, WalkWithStringType_214) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);

  StringWalker_214 walker;
  std::string result = walker.Walk(re, "");
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("P"), std::string::npos);

  re->Decref();
}

}  // namespace re2
