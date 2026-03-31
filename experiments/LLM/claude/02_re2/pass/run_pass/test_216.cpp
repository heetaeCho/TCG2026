#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/walker-inl.h"

namespace re2 {

// A concrete Walker that counts nodes in a regexp tree.
class CountWalker : public Regexp::Walker<int> {
 public:
  CountWalker() {}
  ~CountWalker() override {}

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
    return 0;
  }

  int Copy(int arg) override {
    return arg;
  }
};

// A walker that accumulates the depth of the tree.
class DepthWalker : public Regexp::Walker<int> {
 public:
  DepthWalker() {}
  ~DepthWalker() override {}

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    return parent_arg + 1;
  }

  int PostVisit(Regexp* re, int parent_arg, int pre_arg,
                int* child_args, int nchild_args) override {
    int max_child = 0;
    for (int i = 0; i < nchild_args; i++) {
      if (child_args[i] > max_child) {
        max_child = child_args[i];
      }
    }
    return max_child > pre_arg ? max_child : pre_arg;
  }

  int ShortVisit(Regexp* re, int parent_arg) override {
    return parent_arg;
  }

  int Copy(int arg) override {
    return arg;
  }
};

// A walker that stops early after seeing the first node.
class EarlyStopWalker : public Regexp::Walker<int> {
 public:
  EarlyStopWalker() {}
  ~EarlyStopWalker() override {}

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

  int Copy(int arg) override {
    return arg;
  }
};

// A walker that returns a string representation (for testing with string type).
class StringWalker : public Regexp::Walker<std::string> {
 public:
  StringWalker() {}
  ~StringWalker() override {}

  std::string PreVisit(Regexp* re, std::string parent_arg, bool* stop) override {
    return "pre";
  }

  std::string PostVisit(Regexp* re, std::string parent_arg, std::string pre_arg,
                        std::string* child_args, int nchild_args) override {
    std::string result = "node(";
    for (int i = 0; i < nchild_args; i++) {
      if (i > 0) result += ",";
      result += child_args[i];
    }
    result += ")";
    return result;
  }

  std::string ShortVisit(Regexp* re, std::string parent_arg) override {
    return "short";
  }

  std::string Copy(std::string arg) override {
    return arg;
  }
};

class WalkerTest_216 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(WalkerTest_216, WalkSimpleLiteral_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkConcatenation_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  // "abc" has at least 3 literal nodes (possibly more with concat)
  EXPECT_GE(count, 3);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkAlternation_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  // At least 3 literals + alternation node(s)
  EXPECT_GE(count, 3);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkNested_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a(b(c)))", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 3);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkDepth_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  DepthWalker walker;
  int depth = walker.Walk(re, 0);
  EXPECT_GE(depth, 1);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkDepthNested_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a(b))", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  DepthWalker walker;
  int depth = walker.Walk(re, 0);
  EXPECT_GE(depth, 2);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkEarlyStop_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  EarlyStopWalker walker;
  int result = walker.Walk(re, 0);
  EXPECT_EQ(result, 42);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkExponentialWithLimit_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c|d|e", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.WalkExponential(re, 0, 2);
  // With very limited visits, stopped_early should be true
  // or it processes normally if within limits
  // Just ensure it doesn't crash and returns a value
  (void)count;
  // Check stopped_early is accessible
  bool stopped = walker.stopped_early();
  (void)stopped;

  re->Decref();
}

TEST_F(WalkerTest_216, WalkExponentialNoLimit_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.WalkExponential(re, 0, 1000000);
  EXPECT_GE(count, 2);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

TEST_F(WalkerTest_216, StoppedEarlyInitiallyFalse_216) {
  CountWalker walker;
  EXPECT_FALSE(walker.stopped_early());
}

TEST_F(WalkerTest_216, WalkRepetition_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkStarQuantifier_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkQuestionQuantifier_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkCharacterClass_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkComplexExpression_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+b*|c?d){2,5}", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 4);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkWithStringType_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  StringWalker walker;
  std::string result = walker.Walk(re, "");
  EXPECT_FALSE(result.empty());

  re->Decref();
}

TEST_F(WalkerTest_216, WalkDotExpression_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkEmptyAlternation_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("|a", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

TEST_F(WalkerTest_216, ResetAndRewalk_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count1 = walker.Walk(re, 0);

  walker.Reset();

  int count2 = walker.Walk(re, 0);
  EXPECT_EQ(count1, count2);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkExponentialStopsEarly_216) {
  RegexpStatus status;
  // Create a regexp with shared subexpressions that exponential walk visits many times
  Regexp* re = Regexp::Parse("a", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.WalkExponential(re, 0, 1);
  // With max_visits=1, it should stop early on larger expressions
  // For a single literal, it might complete
  (void)count;

  re->Decref();
}

TEST_F(WalkerTest_216, WalkMultipleTimesWithSameWalker_216) {
  RegexpStatus status;
  Regexp* re1 = Regexp::Parse("a", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re1 != nullptr);
  Regexp* re2 = Regexp::Parse("ab", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re2 != nullptr);

  CountWalker walker;
  int count1 = walker.Walk(re1, 0);
  int count2 = walker.Walk(re2, 0);

  EXPECT_GE(count1, 1);
  EXPECT_GE(count2, 2);
  EXPECT_GE(count2, count1);

  re1->Decref();
  re2->Decref();
}

TEST_F(WalkerTest_216, WalkCapture_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  // Capture wraps a literal, so at least 2 nodes
  EXPECT_GE(count, 2);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkTopArgPropagated_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  DepthWalker walker;
  int depth_from_zero = walker.Walk(re, 0);
  
  DepthWalker walker2;
  int depth_from_ten = walker2.Walk(re, 10);

  // Starting from 10, depth should be at least 10 more
  EXPECT_GT(depth_from_ten, depth_from_zero);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkBoundedRepeat_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

TEST_F(WalkerTest_216, WalkAnchorExpressions_216) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 3);

  re->Decref();
}

}  // namespace re2
