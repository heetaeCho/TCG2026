#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include <string>

namespace re2 {

class PossibleMatchRangeTest_458 : public ::testing::Test {
 protected:
  // Helper to compile a regex pattern into a Prog
  Prog* CompilePattern(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re == nullptr) return nullptr;
    Prog* prog = re->CompileToProg(0);
    re->Decref();
    return prog;
  }
};

// Test basic PossibleMatchRange with a simple literal pattern
TEST_F(PossibleMatchRangeTest_458, SimpleLiteral_458) {
  Prog* prog = CompilePattern("hello");
  ASSERT_NE(prog, nullptr);
  
  std::string min, max;
  EXPECT_TRUE(prog->PossibleMatchRange(&min, &max, 10));
  EXPECT_FALSE(min.empty());
  EXPECT_FALSE(max.empty());
  EXPECT_LE(min, "hello");
  EXPECT_GE(max, "hello");
  
  delete prog;
}

// Test PossibleMatchRange with a pattern that matches everything
TEST_F(PossibleMatchRangeTest_458, DotStar_458) {
  Prog* prog = CompilePattern(".*");
  ASSERT_NE(prog, nullptr);
  
  std::string min, max;
  EXPECT_TRUE(prog->PossibleMatchRange(&min, &max, 10));
  
  delete prog;
}

// Test PossibleMatchRange with a character class
TEST_F(PossibleMatchRangeTest_458, CharacterClass_458) {
  Prog* prog = CompilePattern("[a-z]+");
  ASSERT_NE(prog, nullptr);
  
  std::string min, max;
  EXPECT_TRUE(prog->PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, max);
  
  delete prog;
}

// Test PossibleMatchRange with maxlen = 0
TEST_F(PossibleMatchRangeTest_458, MaxLenZero_458) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  
  std::string min, max;
  // maxlen=0 should still work (or return false gracefully)
  bool result = prog->PossibleMatchRange(&min, &max, 0);
  // We don't assert on the result, but it should not crash
  (void)result;
  
  delete prog;
}

// Test PossibleMatchRange with maxlen = 1
TEST_F(PossibleMatchRangeTest_458, MaxLenOne_458) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  
  std::string min, max;
  bool result = prog->PossibleMatchRange(&min, &max, 1);
  if (result) {
    EXPECT_LE(min.size(), static_cast<size_t>(1));
    EXPECT_LE(max.size(), static_cast<size_t>(1));
  }
  
  delete prog;
}

// Test PossibleMatchRange with alternation
TEST_F(PossibleMatchRangeTest_458, Alternation_458) {
  Prog* prog = CompilePattern("abc|xyz");
  ASSERT_NE(prog, nullptr);
  
  std::string min, max;
  EXPECT_TRUE(prog->PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, "abc");
  EXPECT_GE(max, "xyz");
  
  delete prog;
}

// Test PossibleMatchRange with a single character pattern
TEST_F(PossibleMatchRangeTest_458, SingleChar_458) {
  Prog* prog = CompilePattern("a");
  ASSERT_NE(prog, nullptr);
  
  std::string min, max;
  EXPECT_TRUE(prog->PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, "a");
  EXPECT_GE(max, "a");
  
  delete prog;
}

// Test PossibleMatchRange with a pattern that has a prefix
TEST_F(PossibleMatchRangeTest_458, CommonPrefix_458) {
  Prog* prog = CompilePattern("prefix(abc|def)");
  ASSERT_NE(prog, nullptr);
  
  std::string min, max;
  EXPECT_TRUE(prog->PossibleMatchRange(&min, &max, 20));
  EXPECT_LE(min, max);
  
  delete prog;
}

// Test PossibleMatchRange with a very large maxlen
TEST_F(PossibleMatchRangeTest_458, LargeMaxLen_458) {
  Prog* prog = CompilePattern("test");
  ASSERT_NE(prog, nullptr);
  
  std::string min, max;
  EXPECT_TRUE(prog->PossibleMatchRange(&min, &max, 1000));
  EXPECT_LE(min, "test");
  EXPECT_GE(max, "test");
  
  delete prog;
}

// Test PossibleMatchRange min <= max invariant
TEST_F(PossibleMatchRangeTest_458, MinLessThanOrEqualMax_458) {
  Prog* prog = CompilePattern("[0-9]+");
  ASSERT_NE(prog, nullptr);
  
  std::string min, max;
  EXPECT_TRUE(prog->PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, max);
  
  delete prog;
}

// Test PossibleMatchRange with anchored pattern
TEST_F(PossibleMatchRangeTest_458, AnchoredPattern_458) {
  Prog* prog = CompilePattern("^abc$");
  ASSERT_NE(prog, nullptr);
  
  std::string min, max;
  bool result = prog->PossibleMatchRange(&min, &max, 10);
  if (result) {
    EXPECT_LE(min, max);
  }
  
  delete prog;
}

// Test PossibleMatchRange with optional pattern
TEST_F(PossibleMatchRangeTest_458, OptionalPattern_458) {
  Prog* prog = CompilePattern("ab?c");
  ASSERT_NE(prog, nullptr);
  
  std::string min, max;
  EXPECT_TRUE(prog->PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, max);
  
  delete prog;
}

// Test PossibleMatchRange with repetition
TEST_F(PossibleMatchRangeTest_458, Repetition_458) {
  Prog* prog = CompilePattern("a{3,5}");
  ASSERT_NE(prog, nullptr);
  
  std::string min, max;
  EXPECT_TRUE(prog->PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, "aaa");
  EXPECT_GE(max, "aaaaa");
  
  delete prog;
}

// Test PossibleMatchRange with empty pattern
TEST_F(PossibleMatchRangeTest_458, EmptyPattern_458) {
  Prog* prog = CompilePattern("");
  ASSERT_NE(prog, nullptr);
  
  std::string min, max;
  bool result = prog->PossibleMatchRange(&min, &max, 10);
  // Empty pattern should either succeed or fail gracefully
  (void)result;
  
  delete prog;
}

// Test via RE2 interface which calls Prog::PossibleMatchRange internally
TEST_F(PossibleMatchRangeTest_458, ViaRE2Interface_458) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  
  std::string min, max;
  EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, "hello");
  EXPECT_GE(max, "hello");
}

// Test via RE2 interface with character class
TEST_F(PossibleMatchRangeTest_458, ViaRE2CharClass_458) {
  RE2 re("[a-f]+");
  ASSERT_TRUE(re.ok());
  
  std::string min, max;
  EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));
  EXPECT_LE(min, max);
}

// Test that the range captures high bytes properly
TEST_F(PossibleMatchRangeTest_458, HighByteRange_458) {
  Prog* prog = CompilePattern("\\xff");
  ASSERT_NE(prog, nullptr);
  
  std::string min, max;
  bool result = prog->PossibleMatchRange(&min, &max, 10);
  if (result) {
    EXPECT_LE(min, max);
  }
  
  delete prog;
}

// Test PossibleMatchRange with a complex pattern
TEST_F(PossibleMatchRangeTest_458, ComplexPattern_458) {
  Prog* prog = CompilePattern("(foo|bar)(baz|qux)[0-9]{2,4}");
  ASSERT_NE(prog, nullptr);
  
  std::string min, max;
  EXPECT_TRUE(prog->PossibleMatchRange(&min, &max, 20));
  EXPECT_LE(min, max);
  
  delete prog;
}

// Test that two calls return consistent results
TEST_F(PossibleMatchRangeTest_458, ConsistentResults_458) {
  Prog* prog = CompilePattern("test[0-9]+");
  ASSERT_NE(prog, nullptr);
  
  std::string min1, max1, min2, max2;
  EXPECT_TRUE(prog->PossibleMatchRange(&min1, &max1, 10));
  EXPECT_TRUE(prog->PossibleMatchRange(&min2, &max2, 10));
  EXPECT_EQ(min1, min2);
  EXPECT_EQ(max1, max2);
  
  delete prog;
}

}  // namespace re2
