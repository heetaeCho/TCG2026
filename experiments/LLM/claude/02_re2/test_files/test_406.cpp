#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"

namespace re2 {

// Helper to compile a regex pattern into a Prog
static Prog* CompileProg(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

class ProgOptimizeTest_406 : public ::testing::Test {
 protected:
  void TearDown() override {
    for (auto* p : progs_) {
      delete p;
    }
  }

  Prog* MakeProg(const char* pattern) {
    Prog* prog = CompileProg(pattern);
    if (prog) progs_.push_back(prog);
    return prog;
  }

  std::vector<Prog*> progs_;
};

// Test that Optimize can be called on a simple literal pattern without crashing
TEST_F(ProgOptimizeTest_406, SimpleLiteral_406) {
  Prog* prog = MakeProg("hello");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  // After optimization, the program should still be valid
  EXPECT_GE(prog->size(), 1);
}

// Test that Optimize can be called on an alternation pattern
TEST_F(ProgOptimizeTest_406, Alternation_406) {
  Prog* prog = MakeProg("abc|def");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  EXPECT_GE(prog->size(), 1);
}

// Test that Optimize works on a pattern with repetition (which generates Nop instructions)
TEST_F(ProgOptimizeTest_406, Repetition_406) {
  Prog* prog = MakeProg("a*");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  EXPECT_GE(prog->size(), 1);
}

// Test that Optimize works on a pattern with .* which may produce kInstAltMatch
TEST_F(ProgOptimizeTest_406, DotStar_406) {
  Prog* prog = MakeProg(".*abc");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  EXPECT_GE(prog->size(), 1);
}

// Test Optimize on empty pattern
TEST_F(ProgOptimizeTest_406, EmptyPattern_406) {
  Prog* prog = MakeProg("");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  EXPECT_GE(prog->size(), 1);
}

// Test that Optimize preserves matching behavior for a simple pattern
TEST_F(ProgOptimizeTest_406, PreservesMatchSimple_406) {
  RE2 re("hello");
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test that Optimize preserves matching behavior for alternation
TEST_F(ProgOptimizeTest_406, PreservesMatchAlternation_406) {
  RE2 re("abc|def");
  EXPECT_TRUE(RE2::FullMatch("abc", re));
  EXPECT_TRUE(RE2::FullMatch("def", re));
  EXPECT_FALSE(RE2::FullMatch("ghi", re));
}

// Test that Optimize preserves matching behavior for .* prefix (unanchored)
TEST_F(ProgOptimizeTest_406, PreservesMatchDotStar_406) {
  RE2 re(".*xyz");
  EXPECT_TRUE(RE2::FullMatch("xyz", re));
  EXPECT_TRUE(RE2::FullMatch("abcxyz", re));
  EXPECT_FALSE(RE2::FullMatch("abc", re));
}

// Test Optimize on a complex nested alternation/repetition pattern
TEST_F(ProgOptimizeTest_406, ComplexPattern_406) {
  Prog* prog = MakeProg("(a|b)*c(d|e)+f?");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  EXPECT_GE(prog->size(), 1);
}

// Test Optimize on character class patterns
TEST_F(ProgOptimizeTest_406, CharacterClass_406) {
  Prog* prog = MakeProg("[a-zA-Z0-9]+");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  EXPECT_GE(prog->size(), 1);
}

// Test that calling Optimize twice doesn't crash (idempotent)
TEST_F(ProgOptimizeTest_406, DoubleOptimize_406) {
  Prog* prog = MakeProg("a*b+c?");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  prog->Optimize();
  EXPECT_GE(prog->size(), 1);
}

// Test that start instruction is still valid after Optimize
TEST_F(ProgOptimizeTest_406, StartValid_406) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  int start_before = prog->start();
  prog->Optimize();
  int start_after = prog->start();
  // Start should still be a valid instruction index
  EXPECT_GE(start_after, 0);
  EXPECT_LT(start_after, prog->size());
  // Start should remain unchanged (Optimize doesn't change start)
  EXPECT_EQ(start_before, start_after);
}

// Test Optimize with a pattern that has captures (generates capture instructions)
TEST_F(ProgOptimizeTest_406, WithCaptures_406) {
  Prog* prog = MakeProg("(a)(b)(c)");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  EXPECT_GE(prog->size(), 1);
}

// Test Optimize with a pattern containing empty width assertions
TEST_F(ProgOptimizeTest_406, EmptyWidth_406) {
  Prog* prog = MakeProg("^abc$");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  EXPECT_GE(prog->size(), 1);
}

// Test that matching still works correctly after Optimize on a pattern
// that would trigger kInstAltMatch optimization (unanchored match with .*)
TEST_F(ProgOptimizeTest_406, AltMatchOptimization_406) {
  RE2 re("abc");
  // Partial match uses unanchored search which involves .* prefix
  EXPECT_TRUE(RE2::PartialMatch("xxxabcyyy", re));
  EXPECT_FALSE(RE2::PartialMatch("xxxyyy", re));
}

// Test Optimize on a single character pattern
TEST_F(ProgOptimizeTest_406, SingleChar_406) {
  Prog* prog = MakeProg("a");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  EXPECT_GE(prog->size(), 1);
}

// Test Optimize on a dot (any character) pattern
TEST_F(ProgOptimizeTest_406, DotPattern_406) {
  Prog* prog = MakeProg(".");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  EXPECT_GE(prog->size(), 1);
}

// Test that reversed flag is preserved after Optimize
TEST_F(ProgOptimizeTest_406, ReversedPreserved_406) {
  Prog* prog = MakeProg("abc");
  ASSERT_NE(prog, nullptr);
  bool rev_before = prog->reversed();
  prog->Optimize();
  EXPECT_EQ(rev_before, prog->reversed());
}

// Test Optimize with a large alternation
TEST_F(ProgOptimizeTest_406, LargeAlternation_406) {
  Prog* prog = MakeProg("a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  EXPECT_GE(prog->size(), 1);
}

// Test Dump output exists after Optimize (basic sanity)
TEST_F(ProgOptimizeTest_406, DumpAfterOptimize_406) {
  Prog* prog = MakeProg("abc|def");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

}  // namespace re2
