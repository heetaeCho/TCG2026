#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/sparse_array.h"
#include "re2/sparse_set.h"

#include <string>
#include <vector>

namespace re2 {

// Helper to compile a regex pattern into a Prog
static Prog* CompileProg(const std::string& pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

class ProgFlattenTest_412 : public ::testing::Test {
 protected:
  void TearDown() override {
    delete prog_;
    prog_ = nullptr;
  }
  Prog* prog_ = nullptr;
};

// Test that Flatten on a simple pattern completes without error
TEST_F(ProgFlattenTest_412, SimpleLiteralFlatten_412) {
  prog_ = CompileProg("hello");
  ASSERT_NE(prog_, nullptr);
  int orig_start = prog_->start();
  int orig_start_unanchored = prog_->start_unanchored();
  
  prog_->Flatten();
  
  // After flattening, size should be positive
  EXPECT_GT(prog_->size(), 0);
  // list_count should be positive
  EXPECT_GT(prog_->list_count(), 0);
}

// Test that calling Flatten twice is idempotent
TEST_F(ProgFlattenTest_412, FlattenIdempotent_412) {
  prog_ = CompileProg("abc");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  int size_after_first = prog_->size();
  int list_count_first = prog_->list_count();
  int start_first = prog_->start();
  int start_unanchored_first = prog_->start_unanchored();
  
  prog_->Flatten();
  EXPECT_EQ(prog_->size(), size_after_first);
  EXPECT_EQ(prog_->list_count(), list_count_first);
  EXPECT_EQ(prog_->start(), start_first);
  EXPECT_EQ(prog_->start_unanchored(), start_unanchored_first);
}

// Test Flatten with alternation pattern
TEST_F(ProgFlattenTest_412, AlternationFlatten_412) {
  prog_ = CompileProg("a|b|c");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  EXPECT_GT(prog_->size(), 0);
  EXPECT_GT(prog_->list_count(), 0);
}

// Test Flatten with character class pattern
TEST_F(ProgFlattenTest_412, CharClassFlatten_412) {
  prog_ = CompileProg("[a-z]+");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  EXPECT_GT(prog_->size(), 0);
  EXPECT_GT(prog_->list_count(), 0);
}

// Test Flatten with capture groups
TEST_F(ProgFlattenTest_412, CaptureGroupFlatten_412) {
  prog_ = CompileProg("(a)(b)(c)");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  EXPECT_GT(prog_->size(), 0);
  EXPECT_GT(prog_->list_count(), 0);
}

// Test Flatten with complex pattern (repetition)
TEST_F(ProgFlattenTest_412, RepetitionFlatten_412) {
  prog_ = CompileProg("a*b+c?d{2,4}");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  EXPECT_GT(prog_->size(), 0);
  EXPECT_GT(prog_->list_count(), 0);
}

// Test that bit_state_text_max_size is set after Flatten
TEST_F(ProgFlattenTest_412, BitStateTextMaxSizeSet_412) {
  prog_ = CompileProg("test");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  // bit_state_text_max_size should be positive after flattening
  EXPECT_GT(prog_->bit_state_text_max_size(), 0u);
}

// Test Flatten with anchored pattern
TEST_F(ProgFlattenTest_412, AnchoredPatternFlatten_412) {
  prog_ = CompileProg("^hello$");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  EXPECT_GT(prog_->size(), 0);
  EXPECT_GT(prog_->list_count(), 0);
}

// Test that start and start_unanchored are valid after Flatten
TEST_F(ProgFlattenTest_412, StartValuesValidAfterFlatten_412) {
  prog_ = CompileProg("foo.*bar");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  EXPECT_GE(prog_->start(), 0);
  EXPECT_LT(prog_->start(), prog_->size());
  EXPECT_GE(prog_->start_unanchored(), 0);
  EXPECT_LT(prog_->start_unanchored(), prog_->size());
}

// Test Flatten with empty string pattern
TEST_F(ProgFlattenTest_412, EmptyPatternFlatten_412) {
  prog_ = CompileProg("");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  EXPECT_GT(prog_->size(), 0);
}

// Test Flatten with dot-star pattern
TEST_F(ProgFlattenTest_412, DotStarFlatten_412) {
  prog_ = CompileProg(".*");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  EXPECT_GT(prog_->size(), 0);
  EXPECT_GT(prog_->list_count(), 0);
}

// Test that inst_count returns valid values after Flatten
TEST_F(ProgFlattenTest_412, InstCountAfterFlatten_412) {
  prog_ = CompileProg("a(b|c)d");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  int total = 0;
  for (int i = 0; i < kNumInst; i++) {
    int count = prog_->inst_count(static_cast<InstOp>(i));
    EXPECT_GE(count, 0);
    total += count;
  }
  EXPECT_EQ(total, prog_->size());
}

// Test Flatten with a pattern that produces a small program (<=512 instructions)
// to exercise the list_heads_ path
TEST_F(ProgFlattenTest_412, SmallProgramListHeads_412) {
  prog_ = CompileProg("ab");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  EXPECT_LE(prog_->size(), 512);
  // list_heads should be available
  if (prog_->size() <= 512) {
    EXPECT_NE(prog_->list_heads(), nullptr);
  }
}

// Test Flatten preserves the ability to match correctly
TEST_F(ProgFlattenTest_412, FlattenPreservesMatchBehavior_412) {
  // Use RE2 which internally flattens, but we test via the Prog interface
  prog_ = CompileProg("hello");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  // After flattening, a search should still work
  absl::string_view text("say hello world");
  absl::string_view match;
  bool found = prog_->SearchNFA(text, text, Prog::kUnanchored,
                                 Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

// Test Flatten with nested alternation
TEST_F(ProgFlattenTest_412, NestedAlternationFlatten_412) {
  prog_ = CompileProg("(a|b)(c|d)(e|f)");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  EXPECT_GT(prog_->size(), 0);
  EXPECT_GT(prog_->list_count(), 0);
}

// Test Flatten with quantifiers producing larger programs
TEST_F(ProgFlattenTest_412, LargerPatternFlatten_412) {
  prog_ = CompileProg("[a-z]{1,10}[0-9]{1,10}");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  EXPECT_GT(prog_->size(), 0);
  EXPECT_GT(prog_->list_count(), 0);
  EXPECT_GT(prog_->bit_state_text_max_size(), 0u);
}

// Test that Dump works after Flatten (doesn't crash)
TEST_F(ProgFlattenTest_412, DumpAfterFlatten_412) {
  prog_ = CompileProg("a+b*c?");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  std::string dump = prog_->Dump();
  EXPECT_FALSE(dump.empty());
}

// Test Flatten with single character pattern
TEST_F(ProgFlattenTest_412, SingleCharFlatten_412) {
  prog_ = CompileProg("x");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  EXPECT_GT(prog_->size(), 0);
  EXPECT_GE(prog_->start(), 0);
  EXPECT_LT(prog_->start(), prog_->size());
}

// Test that inst() returns valid instructions after Flatten
TEST_F(ProgFlattenTest_412, InstAccessAfterFlatten_412) {
  prog_ = CompileProg("abc");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  for (int i = 0; i < prog_->size(); i++) {
    Prog::Inst* ip = prog_->inst(i);
    ASSERT_NE(ip, nullptr);
    // opcode should be a valid InstOp
    EXPECT_GE(ip->opcode(), 0);
    EXPECT_LT(ip->opcode(), kNumInst);
  }
}

// Test Flatten with word boundary assertion
TEST_F(ProgFlattenTest_412, WordBoundaryFlatten_412) {
  prog_ = CompileProg("\\bword\\b");
  ASSERT_NE(prog_, nullptr);
  
  prog_->Flatten();
  
  EXPECT_GT(prog_->size(), 0);
  EXPECT_GT(prog_->list_count(), 0);
}

}  // namespace re2
