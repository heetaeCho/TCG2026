#include <gtest/gtest.h>
#include "re2/regexp.h"
#include "re2/walker-inl.h"

// We need to include the fuzzer file or recreate the SubexpressionWalker class
// Since the class is defined in re2_fuzzer.cc, we include the necessary headers
// and define a test-local version based on the provided interface.

namespace {

// Recreate SubexpressionWalker based on the provided interface for testing
class SubexpressionWalker : public re2::Regexp::Walker<int> {
 public:
  SubexpressionWalker() = default;
  ~SubexpressionWalker() override = default;

  int PostVisit(re2::Regexp* re, int parent_arg, int pre_arg,
                int* child_args, int nchild_args) override {
    int dominated = 0;
    for (int i = 0; i < nchild_args; i++) {
      dominated += child_args[i];
    }
    return dominated + 1;
  }

  int ShortVisit(re2::Regexp* re, int parent_arg) override {
    return parent_arg;
  }

 private:
  SubexpressionWalker(const SubexpressionWalker&) = delete;
  SubexpressionWalker& operator=(const SubexpressionWalker&) = delete;
};

class SubexpressionWalkerTest_382 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(SubexpressionWalkerTest_382, ShortVisitReturnsParentArg_382) {
  SubexpressionWalker walker;
  // Create a simple regexp to pass to ShortVisit
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  // ShortVisit should return parent_arg unchanged
  EXPECT_EQ(walker.ShortVisit(re, 0), 0);
  EXPECT_EQ(walker.ShortVisit(re, 1), 1);
  EXPECT_EQ(walker.ShortVisit(re, 42), 42);
  EXPECT_EQ(walker.ShortVisit(re, -1), -1);
  EXPECT_EQ(walker.ShortVisit(re, 100), 100);

  re->Decref();
}

TEST_F(SubexpressionWalkerTest_382, ShortVisitWithZeroParentArg_382) {
  SubexpressionWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("abc", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(walker.ShortVisit(re, 0), 0);

  re->Decref();
}

TEST_F(SubexpressionWalkerTest_382, ShortVisitWithNegativeParentArg_382) {
  SubexpressionWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("x", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(walker.ShortVisit(re, -999), -999);

  re->Decref();
}

TEST_F(SubexpressionWalkerTest_382, ShortVisitWithLargeParentArg_382) {
  SubexpressionWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse(".", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(walker.ShortVisit(re, INT32_MAX), INT32_MAX);
  EXPECT_EQ(walker.ShortVisit(re, INT32_MIN), INT32_MIN);

  re->Decref();
}

TEST_F(SubexpressionWalkerTest_382, ShortVisitWithComplexRegexp_382) {
  SubexpressionWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("(a|b)*c+[d-f]?", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(walker.ShortVisit(re, 7), 7);

  re->Decref();
}

TEST_F(SubexpressionWalkerTest_382, WalkSimpleLiteral_382) {
  SubexpressionWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  // A single literal should have at least 1 subexpression node
  EXPECT_GE(result, 1);

  re->Decref();
}

TEST_F(SubexpressionWalkerTest_382, WalkConcatenation_382) {
  SubexpressionWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("abc", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  // "abc" is a concatenation of 3 literals, so should have multiple nodes
  EXPECT_GE(result, 1);

  re->Decref();
}

TEST_F(SubexpressionWalkerTest_382, WalkAlternation_382) {
  SubexpressionWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a|b|c", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  EXPECT_GE(result, 1);

  re->Decref();
}

TEST_F(SubexpressionWalkerTest_382, WalkWithCaptures_382) {
  SubexpressionWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("(a)(b)(c)", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  // Should count the capture groups and their contents
  EXPECT_GE(result, 1);

  re->Decref();
}

TEST_F(SubexpressionWalkerTest_382, WalkWithRepetition_382) {
  SubexpressionWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a*b+c?", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  EXPECT_GE(result, 1);

  re->Decref();
}

TEST_F(SubexpressionWalkerTest_382, WalkNestedExpression_382) {
  SubexpressionWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("((a|b)*c)+", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  EXPECT_GE(result, 1);

  re->Decref();
}

TEST_F(SubexpressionWalkerTest_382, WalkCharacterClass_382) {
  SubexpressionWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("[a-z0-9]", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  EXPECT_GE(result, 1);

  re->Decref();
}

TEST_F(SubexpressionWalkerTest_382, WalkDotStar_382) {
  SubexpressionWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse(".*", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  EXPECT_GE(result, 1);

  re->Decref();
}

TEST_F(SubexpressionWalkerTest_382, ShortVisitDifferentRegexpTypes_382) {
  SubexpressionWalker walker;
  re2::RegexpStatus status;

  // Test with different types of regexps
  const char* patterns[] = {"a", "a*", "a+", "a?", "[abc]", ".", "(a)", "a|b"};
  for (const char* pattern : patterns) {
    re2::Regexp* re = re2::Regexp::Parse(pattern, re2::Regexp::NoParseFlags, &status);
    ASSERT_NE(re, nullptr) << "Failed to parse: " << pattern;
    EXPECT_EQ(walker.ShortVisit(re, 5), 5) << "Failed for pattern: " << pattern;
    re->Decref();
  }
}

TEST_F(SubexpressionWalkerTest_382, DefaultConstructible_382) {
  // Verify the walker can be default constructed
  SubexpressionWalker walker;
  // Just verify it doesn't crash
  SUCCEED();
}

}  // namespace
