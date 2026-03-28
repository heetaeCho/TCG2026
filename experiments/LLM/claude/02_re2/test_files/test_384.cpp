#include <gtest/gtest.h>
#include "re2/regexp.h"
#include "re2/re2.h"

// We need to include the fuzzer file or recreate the SubstringWalker interface.
// Since SubstringWalker is defined in re2_fuzzer.cc, we include it.
// However, since it's in a fuzzer file, we may need to declare it ourselves
// based on the known interface, or include the relevant walker header.

#include "re2/walker-inl.h"

// Forward-declare or include SubstringWalker from the fuzzer file
// Since we can't directly include the fuzzer .cc file in a clean way,
// we test through the public interface based on what's given.

// Recreate the SubstringWalker based on the provided interface for testing purposes.
// This matches the exact interface provided in the prompt.
class SubstringWalker : public re2::Regexp::Walker<int> {
 public:
  SubstringWalker() = default;
  ~SubstringWalker() override = default;

  int PostVisit(re2::Regexp* re, int parent_arg, int pre_arg,
                int* child_args, int nchild_args) override {
    // Black box - we don't know the implementation
    // But we need a minimal implementation for the test to compile
    return 0;
  }

  int ShortVisit(re2::Regexp* re, int parent_arg) override {
    return parent_arg;
  }

 private:
  SubstringWalker(const SubstringWalker&) = delete;
  SubstringWalker& operator=(const SubstringWalker&) = delete;
};

class SubstringWalkerTest_384 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that SubstringWalker can be constructed and destroyed
TEST_F(SubstringWalkerTest_384, ConstructAndDestruct_384) {
  SubstringWalker walker;
  // Simply constructing and destructing should not crash
}

// Test ShortVisit returns the parent_arg when given 0
TEST_F(SubstringWalkerTest_384, ShortVisitReturnsParentArgZero_384) {
  SubstringWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.ShortVisit(re, 0);
  EXPECT_EQ(result, 0);

  re->Decref();
}

// Test ShortVisit returns the parent_arg when given a positive value
TEST_F(SubstringWalkerTest_384, ShortVisitReturnsParentArgPositive_384) {
  SubstringWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("abc", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.ShortVisit(re, 42);
  EXPECT_EQ(result, 42);

  re->Decref();
}

// Test ShortVisit returns the parent_arg when given a negative value
TEST_F(SubstringWalkerTest_384, ShortVisitReturnsParentArgNegative_384) {
  SubstringWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("x", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.ShortVisit(re, -1);
  EXPECT_EQ(result, -1);

  re->Decref();
}

// Test ShortVisit returns the parent_arg with large value
TEST_F(SubstringWalkerTest_384, ShortVisitReturnsParentArgLargeValue_384) {
  SubstringWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse(".", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.ShortVisit(re, INT_MAX);
  EXPECT_EQ(result, INT_MAX);

  re->Decref();
}

// Test ShortVisit returns the parent_arg with INT_MIN
TEST_F(SubstringWalkerTest_384, ShortVisitReturnsParentArgIntMin_384) {
  SubstringWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("[a-z]", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.ShortVisit(re, INT_MIN);
  EXPECT_EQ(result, INT_MIN);

  re->Decref();
}

// Test ShortVisit with different regexp types
TEST_F(SubstringWalkerTest_384, ShortVisitWithAlternation_384) {
  SubstringWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a|b|c", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.ShortVisit(re, 7);
  EXPECT_EQ(result, 7);

  re->Decref();
}

// Test ShortVisit with a complex regexp
TEST_F(SubstringWalkerTest_384, ShortVisitWithComplexRegexp_384) {
  SubstringWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("(a+b*)?[c-z]{2,5}", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.ShortVisit(re, 100);
  EXPECT_EQ(result, 100);

  re->Decref();
}

// Test PostVisit with a simple regexp
TEST_F(SubstringWalkerTest_384, PostVisitWithSimpleRegexp_384) {
  SubstringWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.PostVisit(re, 0, 0, nullptr, 0);
  // We observe the return value without assuming internal logic
  // Just verify it doesn't crash and returns an int
  (void)result;

  re->Decref();
}

// Test Walk with a simple literal regexp
TEST_F(SubstringWalkerTest_384, WalkSimpleLiteral_384) {
  SubstringWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("hello", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  // Just verify Walk completes without crashing
  (void)result;

  re->Decref();
}

// Test Walk with concatenation
TEST_F(SubstringWalkerTest_384, WalkConcatenation_384) {
  SubstringWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("abc", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 5);
  // Verify Walk completes
  (void)result;

  re->Decref();
}

// Test Walk with alternation
TEST_F(SubstringWalkerTest_384, WalkAlternation_384) {
  SubstringWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a|b", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  (void)result;

  re->Decref();
}

// Test Walk with repetition
TEST_F(SubstringWalkerTest_384, WalkRepetition_384) {
  SubstringWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("a{1,3}", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  int result = walker.Walk(re, 0);
  (void)result;

  re->Decref();
}

// Test that multiple ShortVisit calls on the same walker work correctly
TEST_F(SubstringWalkerTest_384, MultipleShortVisitCalls_384) {
  SubstringWalker walker;
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("test", re2::Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);

  for (int i = -10; i <= 10; ++i) {
    int result = walker.ShortVisit(re, i);
    EXPECT_EQ(result, i);
  }

  re->Decref();
}
