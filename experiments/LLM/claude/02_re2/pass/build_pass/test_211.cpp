#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/walker-inl.h"

namespace re2 {

// A concrete Walker that counts nodes in the regexp tree.
class CountWalker : public Regexp::Walker<int> {
 public:
  CountWalker() {}
  ~CountWalker() override {}

  int PreVisit(Regexp* re, int parent_arg, bool* stop) override {
    return parent_arg;
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
    return 1;
  }
};

// A walker that stops early on the first node.
class StopEarlyWalker : public Regexp::Walker<int> {
 public:
  StopEarlyWalker() {}
  ~StopEarlyWalker() override {}

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

// A walker that simply returns the parent arg through the tree.
class PassthroughWalker : public Regexp::Walker<int> {
 public:
  PassthroughWalker() {}
  ~PassthroughWalker() override {}

  int PostVisit(Regexp* re, int parent_arg, int pre_arg,
                int* child_args, int nchild_args) override {
    return pre_arg;
  }

  int ShortVisit(Regexp* re, int parent_arg) override {
    return parent_arg;
  }
};

// A walker that accumulates string type.
class StringWalker : public Regexp::Walker<std::string> {
 public:
  StringWalker() {}
  ~StringWalker() override {}

  std::string PreVisit(Regexp* re, std::string parent_arg,
                       bool* stop) override {
    return parent_arg + "pre";
  }

  std::string PostVisit(Regexp* re, std::string parent_arg,
                        std::string pre_arg, std::string* child_args,
                        int nchild_args) override {
    std::string result = pre_arg + "post";
    for (int i = 0; i < nchild_args; i++) {
      result += child_args[i];
    }
    return result;
  }

  std::string ShortVisit(Regexp* re, std::string parent_arg) override {
    return parent_arg + "short";
  }
};

class WalkerTest_211 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test Walk on a simple literal regexp
TEST_F(WalkerTest_211, WalkSimpleLiteral_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test Walk on a concatenation regexp
TEST_F(WalkerTest_211, WalkConcatenation_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test Walk on an alternation regexp
TEST_F(WalkerTest_211, WalkAlternation_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 3);

  re->Decref();
}

// Test Walk on a nested regexp
TEST_F(WalkerTest_211, WalkNestedRegexp_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a(b|c)d)+", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test Walk with NULL regexp
TEST_F(WalkerTest_211, WalkNullRegexp_211) {
  CountWalker walker;
  int count = walker.Walk(nullptr, 0);
  EXPECT_EQ(count, 0);
}

// Test stopped_early is false after a normal walk
TEST_F(WalkerTest_211, StoppedEarlyFalseNormal_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  walker.Walk(re, 0);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test that stopping early sets stopped_early flag
TEST_F(WalkerTest_211, StopEarlyFlag_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  StopEarlyWalker walker;
  int result = walker.Walk(re, 0);
  EXPECT_EQ(result, 42);
  EXPECT_TRUE(walker.stopped_early());

  re->Decref();
}

// Test WalkExponential with high max_visits (no short-circuit)
TEST_F(WalkerTest_211, WalkExponentialNoShortCircuit_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.WalkExponential(re, 0, 1000000);
  EXPECT_GE(count, 1);
  EXPECT_FALSE(walker.stopped_early());

  re->Decref();
}

// Test WalkExponential with low max_visits to trigger short visits
TEST_F(WalkerTest_211, WalkExponentialShortCircuit_211) {
  RegexpStatus status;
  // A complex regexp that would have many nodes
  Regexp* re = Regexp::Parse("(a|b)(c|d)(e|f)(g|h)", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.WalkExponential(re, 0, 1);
  // With max_visits=1, it should stop early
  EXPECT_TRUE(walker.stopped_early());

  re->Decref();
}

// Test default PreVisit returns parent_arg
TEST_F(WalkerTest_211, DefaultPreVisitReturnsParentArg_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  PassthroughWalker walker;
  int result = walker.Walk(re, 99);
  EXPECT_EQ(result, 99);

  re->Decref();
}

// Test Reset allows reusing the walker
TEST_F(WalkerTest_211, ResetAndReuse_211) {
  RegexpStatus status;
  Regexp* re1 = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re1 != nullptr);
  Regexp* re2 = Regexp::Parse("def", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re2 != nullptr);

  CountWalker walker;
  int count1 = walker.Walk(re1, 0);
  walker.Reset();
  int count2 = walker.Walk(re2, 0);

  EXPECT_GE(count1, 1);
  EXPECT_GE(count2, 1);

  re1->Decref();
  re2->Decref();
}

// Test Walk with a complex regexp pattern
TEST_F(WalkerTest_211, WalkComplexPattern_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(foo|bar)+baz[0-9]{2,5}", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 5);  // Should have multiple nodes

  re->Decref();
}

// Test Walk with character class
TEST_F(WalkerTest_211, WalkCharClass_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test Walk with repetition
TEST_F(WalkerTest_211, WalkRepetition_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test walker with string type
TEST_F(WalkerTest_211, WalkWithStringType_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  StringWalker walker;
  std::string result = walker.Walk(re, "");
  EXPECT_FALSE(result.empty());
  // Should contain "pre" from PreVisit and "post" from PostVisit
  EXPECT_NE(result.find("pre"), std::string::npos);
  EXPECT_NE(result.find("post"), std::string::npos);

  re->Decref();
}

// Test Walk on empty string (which should produce an empty match regexp)
TEST_F(WalkerTest_211, WalkEmptyString_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::NoParseFlags, &status);
  // Empty pattern may or may not be valid depending on implementation
  if (re != nullptr) {
    CountWalker walker;
    int count = walker.Walk(re, 0);
    EXPECT_GE(count, 0);
    re->Decref();
  }
}

// Test that WalkExponential with max_visits=0 triggers stopped_early
TEST_F(WalkerTest_211, WalkExponentialMaxVisitsZero_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  walker.WalkExponential(re, 0, 0);
  // With 0 max visits, should stop early on any non-trivial regexp
  EXPECT_TRUE(walker.stopped_early());

  re->Decref();
}

// Test Walk on a deeply nested group
TEST_F(WalkerTest_211, WalkDeeplyNestedGroup_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((((a))))", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;
  int count = walker.Walk(re, 0);
  EXPECT_GE(count, 1);

  re->Decref();
}

// Test Walk with initial arg propagation through concatenation
TEST_F(WalkerTest_211, WalkInitialArgPropagation_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  PassthroughWalker walker;
  int result1 = walker.Walk(re, 100);
  EXPECT_EQ(result1, 100);

  walker.Reset();
  int result2 = walker.Walk(re, 200);
  EXPECT_EQ(result2, 200);

  re->Decref();
}

// Test multiple walks with the same walker after reset
TEST_F(WalkerTest_211, MultipleWalksWithReset_211) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);

  CountWalker walker;

  int count1 = walker.Walk(re, 0);
  walker.Reset();
  int count2 = walker.Walk(re, 0);
  walker.Reset();
  int count3 = walker.Walk(re, 0);

  EXPECT_EQ(count1, count2);
  EXPECT_EQ(count2, count3);

  re->Decref();
}

// Test stopped_early is false initially
TEST_F(WalkerTest_211, StoppedEarlyInitiallyFalse_211) {
  CountWalker walker;
  EXPECT_FALSE(walker.stopped_early());
}

}  // namespace re2
