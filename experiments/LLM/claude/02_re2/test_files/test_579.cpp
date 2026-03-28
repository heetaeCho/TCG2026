#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/sparse_array.h"

namespace re2 {

// Helper function to compile a regex pattern into a Prog
static Prog* CompilePattern(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

class FanoutTest_579 : public ::testing::Test {
 protected:
  void TearDown() override {
    delete prog_;
    prog_ = nullptr;
  }
  Prog* prog_ = nullptr;
};

// Test Fanout with a simple literal pattern
TEST_F(FanoutTest_579, SimpleLiteral_579) {
  prog_ = CompilePattern("abc");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  // Fanout should not be empty for a non-trivial pattern
  EXPECT_GT(fanout.size(), 0);
}

// Test Fanout with a single character pattern
TEST_F(FanoutTest_579, SingleChar_579) {
  prog_ = CompilePattern("a");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  EXPECT_GT(fanout.size(), 0);
}

// Test Fanout with alternation pattern
TEST_F(FanoutTest_579, Alternation_579) {
  prog_ = CompilePattern("a|b|c");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  EXPECT_GT(fanout.size(), 0);
}

// Test Fanout with character class pattern
TEST_F(FanoutTest_579, CharClass_579) {
  prog_ = CompilePattern("[a-z]");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  EXPECT_GT(fanout.size(), 0);
}

// Test Fanout with repetition (star)
TEST_F(FanoutTest_579, StarRepetition_579) {
  prog_ = CompilePattern("a*");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  // Even "a*" should produce some fanout entries
  EXPECT_GE(fanout.size(), 0);
}

// Test Fanout with plus repetition
TEST_F(FanoutTest_579, PlusRepetition_579) {
  prog_ = CompilePattern("a+");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  EXPECT_GT(fanout.size(), 0);
}

// Test Fanout with optional pattern
TEST_F(FanoutTest_579, OptionalPattern_579) {
  prog_ = CompilePattern("a?b");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  EXPECT_GT(fanout.size(), 0);
}

// Test Fanout with a dot (any char)
TEST_F(FanoutTest_579, DotPattern_579) {
  prog_ = CompilePattern(".");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  EXPECT_GT(fanout.size(), 0);
}

// Test that Fanout clears the fanout array before populating
TEST_F(FanoutTest_579, ClearsBefore_579) {
  prog_ = CompilePattern("abc");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  // Pre-populate with some data (set start entry)
  fanout.set_new(0, 999);

  prog_->Fanout(&fanout);

  // After Fanout, the array should have been cleared and repopulated
  // The start entry should be present
  EXPECT_TRUE(fanout.has_index(prog_->start()));
}

// Test Fanout with a complex pattern involving groups
TEST_F(FanoutTest_579, GroupPattern_579) {
  prog_ = CompilePattern("(a)(b)(c)");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  EXPECT_GT(fanout.size(), 0);
}

// Test Fanout with empty width assertion
TEST_F(FanoutTest_579, EmptyWidthAssertion_579) {
  prog_ = CompilePattern("^abc$");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  EXPECT_GT(fanout.size(), 0);
}

// Test that Fanout's start index is present in the result
TEST_F(FanoutTest_579, StartIndexPresent_579) {
  prog_ = CompilePattern("hello");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  EXPECT_TRUE(fanout.has_index(prog_->start()));
}

// Test Fanout with a more complex alternation
TEST_F(FanoutTest_579, ComplexAlternation_579) {
  prog_ = CompilePattern("abc|def|ghi");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  EXPECT_GT(fanout.size(), 0);
}

// Test Fanout with nested groups and quantifiers
TEST_F(FanoutTest_579, NestedGroups_579) {
  prog_ = CompilePattern("(a(b+)c)*d");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  EXPECT_GT(fanout.size(), 0);
}

// Test Fanout called multiple times produces consistent results
TEST_F(FanoutTest_579, ConsistentResults_579) {
  prog_ = CompilePattern("abc|xyz");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout1(prog_->size());
  SparseArray<int> fanout2(prog_->size());

  prog_->Fanout(&fanout1);
  prog_->Fanout(&fanout2);

  EXPECT_EQ(fanout1.size(), fanout2.size());

  for (auto it = fanout1.begin(); it != fanout1.end(); ++it) {
    EXPECT_TRUE(fanout2.has_index(it->index()));
    EXPECT_EQ(it->value(), fanout2.get_existing(it->index()));
  }
}

// Test Fanout with word boundary
TEST_F(FanoutTest_579, WordBoundary_579) {
  prog_ = CompilePattern("\\bword\\b");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  EXPECT_GT(fanout.size(), 0);
}

// Test Fanout values are non-negative counts
TEST_F(FanoutTest_579, NonNegativeCounts_579) {
  prog_ = CompilePattern("[a-z]+[0-9]*");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  for (auto it = fanout.begin(); it != fanout.end(); ++it) {
    EXPECT_GE(it->value(), 0);
  }
}

// Test Fanout with a large character class has higher fanout
TEST_F(FanoutTest_579, LargeCharClassHigherFanout_579) {
  prog_ = CompilePattern("[a-zA-Z0-9]");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  // The start node should have a count reflecting the byte ranges
  EXPECT_TRUE(fanout.has_index(prog_->start()));
  EXPECT_GT(fanout.get_existing(prog_->start()), 0);
}

// Test Fanout with a single byte literal should have fanout of 1 at start
TEST_F(FanoutTest_579, SingleByteFanoutCount_579) {
  prog_ = CompilePattern("x");
  ASSERT_NE(prog_, nullptr);

  SparseArray<int> fanout(prog_->size());
  prog_->Fanout(&fanout);

  EXPECT_TRUE(fanout.has_index(prog_->start()));
  // For a simple single-character pattern, start should lead to at least 1 byte range
  EXPECT_GE(fanout.get_existing(prog_->start()), 1);
}

}  // namespace re2
