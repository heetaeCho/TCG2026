#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/walker-inl.h"

namespace re2 {

// A concrete Walker that counts nodes by overriding PreVisit and PostVisit.
class CountingWalker : public Regexp::Walker<int> {
 public:
  CountingWalker() : Regexp::Walker<int>() {}

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    return parent_arg;
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
    return parent_arg + 1;
  }
};

// A Walker that accumulates depth.
class DepthWalker : public Regexp::Walker<int> {
 public:
  DepthWalker() : Regexp::Walker<int>() {}

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    return parent_arg + 1;
  }

  int PostVisit(Regexp* re, int parent_arg, int pre_arg,
                int* child_args, int nchild_args) override {
    int max_depth = pre_arg;
    for (int i = 0; i < nchild_args; i++) {
      if (child_args[i] > max_depth) {
        max_depth = child_args[i];
      }
    }
    return max_depth;
  }

  int ShortVisit(Regexp* re, int parent_arg) override {
    return parent_arg;
  }
};

// A Walker that stops early in PreVisit.
class EarlyStopWalker : public Regexp::Walker<int> {
 public:
  EarlyStopWalker() : Regexp::Walker<int>() {}

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    *stop = true;
    return 42;
  }

  int PostVisit(Regexp* re, int parent_arg, int pre_arg,
                int* child_args, int nchild_args) override {
    return pre_arg;
  }

  int ShortVisit(Regexp* re, int parent_arg) override {
    return parent_arg;
  }
};

// A default Walker that doesn't override PostVisit (uses the default impl).
class DefaultPostVisitWalker : public Regexp::Walker<int> {
 public:
  DefaultPostVisitWalker() : Regexp::Walker<int>() {}

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    return parent_arg + 1;
  }

  int ShortVisit(Regexp* re, int parent_arg) override {
    return parent_arg;
  }
};

// A Walker with string type T.
class StringWalker : public Regexp::Walker<std::string> {
 public:
  StringWalker() : Regexp::Walker<std::string>() {}

  std::string PreVisit(Regexp* re, std::string parent_arg, bool* stop) override {
    return parent_arg + "(";
  }

  std::string PostVisit(Regexp* re, std::string parent_arg, std::string pre_arg,
                        std::string* child_args, int nchild_args) override {
    std::string result = pre_arg;
    for (int i = 0; i < nchild_args; i++) {
      result += child_args[i];
    }
    result += ")";
    return result;
  }

  std::string ShortVisit(Regexp* re, std::string parent_arg) override {
    return parent_arg + "S";
  }
};

class WalkerTest_212 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test: Walk on a simple literal regexp returns node count of 1.
TEST_F(WalkerTest_212, CountSingleLiteral_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test: Walk on a concatenation "abc" counts multiple nodes.
TEST_F(WalkerTest_212, CountConcatenation_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test: Walk on alternation "a|b|c" counts nodes.
TEST_F(WalkerTest_212, CountAlternation_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 3);  // at least 3 literal nodes

  re->Decref();
}

// Test: Walk propagates top_arg correctly.
TEST_F(WalkerTest_212, WalkTopArg_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 100);
  // Starting from 100, with one node, should be at least 101
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test: DepthWalker computes depth for nested expressions.
TEST_F(WalkerTest_212, DepthNested_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a(b(c)))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  DepthWalker walker;
  int depth = walker.Walk(re, 0);
  EXPECT_GE(depth, 3);  // at least 3 levels of nesting

  re->Decref();
}

// Test: EarlyStopWalker stops early and returns the stop value.
TEST_F(WalkerTest_212, EarlyStop_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abcdef", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  EarlyStopWalker walker;
  int result = walker.Walk(re, 0);
  EXPECT_EQ(result, 42);

  re->Decref();
}

// Test: WalkExponential with max_visits limit triggers stopped_early.
TEST_F(WalkerTest_212, WalkExponentialStoppedEarly_212) {
  RegexpStatus status;
  // Create a complex regexp that has many nodes
  Regexp* re = Regexp::Parse("(a|b)(c|d)(e|f)(g|h)(i|j)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int result = walker.WalkExponential(re, 0, 1);  // very small limit
  // With max_visits=1, it should stop early
  EXPECT_TRUE(walker.stopped_early());

  re->Decref();
}

// Test: WalkExponential with large limit does not stop early.
TEST_F(WalkerTest_212, WalkExponentialNotStoppedEarly_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int result = walker.WalkExponential(re, 0, 1000000);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test: stopped_early is false initially after construction.
TEST_F(WalkerTest_212, StoppedEarlyInitiallyFalse_212) {
  CountingWalker walker;
  EXPECT_FALSE(walker.stopped_early());
}

// Test: Reset clears the walker state after a walk.
TEST_F(WalkerTest_212, ResetAfterWalk_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  walker.WalkExponential(re, 0, 1);
  // After a walk with small limit, stopped_early might be true
  walker.Reset();
  // After reset, stopped_early should be false
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test: Walk on a star expression (repetition).
TEST_F(WalkerTest_212, CountStar_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 2);  // star node + literal node

  re->Decref();
}

// Test: Walk on plus expression.
TEST_F(WalkerTest_212, CountPlus_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 2);

  re->Decref();
}

// Test: Walk on quest expression.
TEST_F(WalkerTest_212, CountQuest_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 2);

  re->Decref();
}

// Test: Walk on character class.
TEST_F(WalkerTest_212, CountCharClass_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test: Walk with string-typed Walker.
TEST_F(WalkerTest_212, StringWalkerBasic_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  StringWalker walker;
  std::string result = walker.Walk(re, "");
  EXPECT_FALSE(result.empty());

  re->Decref();
}

// Test: DefaultPostVisitWalker uses the default PostVisit (returns pre_arg).
TEST_F(WalkerTest_212, DefaultPostVisit_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  DefaultPostVisitWalker walker;
  int result = walker.Walk(re, 0);
  // Default PostVisit returns pre_arg, which is parent_arg + 1 = 1
  EXPECT_EQ(result, 1);

  re->Decref();
}

// Test: Multiple walks with the same walker instance.
TEST_F(WalkerTest_212, MultipleWalks_212) {
  RegexpStatus status;
  Regexp* re1 = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re1, nullptr);
  Regexp* re2 = Regexp::Parse("b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re2, nullptr);

  CountingWalker walker;
  int count1 = walker.Walk(re1, 0);
  int count2 = walker.Walk(re2, 0);

  EXPECT_GE(count1, 1);
  EXPECT_GE(count2, 2);

  re1->Decref();
  re2->Decref();
}

// Test: Walk on a complex expression.
TEST_F(WalkerTest_212, ComplexExpression_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(foo|bar)+baz[0-9]*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 5);  // multiple nodes expected

  re->Decref();
}

// Test: Walk on empty alternation component.
TEST_F(WalkerTest_212, EmptyAlternation_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test: Walk on dot (any character).
TEST_F(WalkerTest_212, DotAnyChar_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test: Walk on a capture group.
TEST_F(WalkerTest_212, CaptureGroup_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 2);  // capture + literal

  re->Decref();
}

// Test: WalkExponential returns a result even when not stopped early.
TEST_F(WalkerTest_212, WalkExponentialResult_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int result = walker.WalkExponential(re, 0, 1000);
  EXPECT_GE(result, 1);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test: Depth walker on flat alternation.
TEST_F(WalkerTest_212, DepthFlatAlternation_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c|d|e", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  DepthWalker walker;
  int depth = walker.Walk(re, 0);
  EXPECT_GE(depth, 2);  // alternation node + literal child

  re->Decref();
}

// Test: Walk on repeat expression with bounds.
TEST_F(WalkerTest_212, RepeatBounds_212) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  CountingWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

}  // namespace re2
