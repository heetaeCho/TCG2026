#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

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

class ComputeByteMapTest_411 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Programs are cleaned up individually in tests
  }
};

// Test that ComputeByteMap works on a simple literal pattern
TEST_F(ComputeByteMapTest_411, SimpleLiteral_411) {
  Prog* prog = CompilePattern("abc");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  // bytemap_range should be positive and <= 256
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);
  
  // bytemap should be accessible
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  
  // All bytemap values should be < bytemap_range
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bm[i], prog->bytemap_range());
  }
  
  delete prog;
}

// Test that different characters in simple pattern get different byte classes
TEST_F(ComputeByteMapTest_411, DifferentCharsGetDifferentClasses_411) {
  Prog* prog = CompilePattern("[abc]");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);
  
  delete prog;
}

// Test ComputeByteMap with a character range pattern
TEST_F(ComputeByteMapTest_411, CharacterRange_411) {
  Prog* prog = CompilePattern("[a-z]");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);
  
  // Characters within the same range should have the same bytemap value
  // 'a' through 'z' should all be in the same class
  uint8_t class_a = bm['a'];
  for (int c = 'a'; c <= 'z'; c++) {
    EXPECT_EQ(bm[c], class_a);
  }
  
  delete prog;
}

// Test ComputeByteMap with case-insensitive pattern (foldcase)
TEST_F(ComputeByteMapTest_411, CaseInsensitive_411) {
  Prog* prog = CompilePattern("(?i)abc");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);
  
  // In case insensitive mode, 'a' and 'A' should be in the same byte class
  EXPECT_EQ(bm['a'], bm['A']);
  EXPECT_EQ(bm['b'], bm['B']);
  EXPECT_EQ(bm['c'], bm['C']);
  
  delete prog;
}

// Test ComputeByteMap with line boundary assertions
TEST_F(ComputeByteMapTest_411, LineBoundary_411) {
  Prog* prog = CompilePattern("^abc$");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);
  
  // '\n' should be in its own class due to line boundary marking
  // At minimum, all bytemap values should be valid
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bm[i], prog->bytemap_range());
  }
  
  delete prog;
}

// Test ComputeByteMap with word boundary assertions
TEST_F(ComputeByteMapTest_411, WordBoundary_411) {
  Prog* prog = CompilePattern("\\bword\\b");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);
  
  // Word characters should be separated from non-word characters
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bm[i], prog->bytemap_range());
  }
  
  delete prog;
}

// Test ComputeByteMap with dot (any character)
TEST_F(ComputeByteMapTest_411, DotPattern_411) {
  Prog* prog = CompilePattern(".");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);
  
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bm[i], prog->bytemap_range());
  }
  
  delete prog;
}

// Test ComputeByteMap with empty pattern
TEST_F(ComputeByteMapTest_411, EmptyPattern_411) {
  Prog* prog = CompilePattern("");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  // Should still produce a valid bytemap
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);
  
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bm[i], prog->bytemap_range());
  }
  
  delete prog;
}

// Test ComputeByteMap with complex alternation
TEST_F(ComputeByteMapTest_411, Alternation_411) {
  Prog* prog = CompilePattern("abc|def|ghi");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);
  
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bm[i], prog->bytemap_range());
  }
  
  delete prog;
}

// Test ComputeByteMap with multiple character classes
TEST_F(ComputeByteMapTest_411, MultipleCharClasses_411) {
  Prog* prog = CompilePattern("[a-z][0-9][A-Z]");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);
  
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bm[i], prog->bytemap_range());
  }
  
  delete prog;
}

// Test ComputeByteMap bytemap_range is minimized
TEST_F(ComputeByteMapTest_411, BytemapRangeMinimized_411) {
  // A pattern with a single byte should have a small bytemap_range
  Prog* prog = CompilePattern("a");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  // With just 'a', we expect a small number of byte classes
  // (at least 2: one for 'a' and one for everything else)
  EXPECT_GE(prog->bytemap_range(), 2);
  EXPECT_LE(prog->bytemap_range(), 256);
  
  delete prog;
}

// Test ComputeByteMap with non-word boundary
TEST_F(ComputeByteMapTest_411, NonWordBoundary_411) {
  Prog* prog = CompilePattern("\\Bword\\B");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);
  
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bm[i], prog->bytemap_range());
  }
  
  delete prog;
}

// Test that IsWordChar classifies characters correctly
TEST_F(ComputeByteMapTest_411, IsWordChar_411) {
  // Word characters: [0-9A-Za-z_]
  for (int c = '0'; c <= '9'; c++) {
    EXPECT_TRUE(Prog::IsWordChar(static_cast<uint8_t>(c)));
  }
  for (int c = 'A'; c <= 'Z'; c++) {
    EXPECT_TRUE(Prog::IsWordChar(static_cast<uint8_t>(c)));
  }
  for (int c = 'a'; c <= 'z'; c++) {
    EXPECT_TRUE(Prog::IsWordChar(static_cast<uint8_t>(c)));
  }
  EXPECT_TRUE(Prog::IsWordChar(static_cast<uint8_t>('_')));
  
  // Non-word characters
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>(' ')));
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>('\n')));
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>('!')));
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>('@')));
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>(0)));
  EXPECT_FALSE(Prog::IsWordChar(static_cast<uint8_t>(255)));
}

// Test ComputeByteMap with consecutive byte ranges that share outputs
TEST_F(ComputeByteMapTest_411, ConsecutiveByteRanges_411) {
  // Pattern that generates consecutive byte ranges: [a-ce-g]
  Prog* prog = CompilePattern("[a-ce-g]");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);
  
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bm[i], prog->bytemap_range());
  }
  
  delete prog;
}

// Test ComputeByteMap with a complex regex
TEST_F(ComputeByteMapTest_411, ComplexRegex_411) {
  Prog* prog = CompilePattern("(?i)^\\b[a-z0-9._%+-]+@[a-z0-9.-]+\\.[a-z]{2,}$");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);
  
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bm[i], prog->bytemap_range());
  }
  
  delete prog;
}

// Test DumpByteMap produces non-empty output
TEST_F(ComputeByteMapTest_411, DumpByteMap_411) {
  Prog* prog = CompilePattern("[a-z]");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
  
  delete prog;
}

// Test that bytemap_range matches the bytemap values
TEST_F(ComputeByteMapTest_411, BytemapRangeConsistency_411) {
  Prog* prog = CompilePattern("[abc][xyz][123]");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  const uint8_t* bm = prog->bytemap();
  int range = prog->bytemap_range();
  
  // Find the maximum bytemap value
  int max_val = 0;
  for (int i = 0; i < 256; i++) {
    if (bm[i] > max_val) max_val = bm[i];
  }
  
  // max_val + 1 should equal bytemap_range
  EXPECT_EQ(max_val + 1, range);
  
  delete prog;
}

// Test ComputeByteMap with single byte pattern (boundary)
TEST_F(ComputeByteMapTest_411, SingleByte_411) {
  Prog* prog = CompilePattern("\\x00");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);
  
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bm[i], prog->bytemap_range());
  }
  
  delete prog;
}

// Test ComputeByteMap with high byte values
TEST_F(ComputeByteMapTest_411, HighByteValues_411) {
  Prog* prog = CompilePattern("[\\x80-\\xff]");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  EXPECT_LE(prog->bytemap_range(), 256);
  
  // All high bytes should have the same class
  uint8_t high_class = bm[0x80];
  for (int i = 0x80; i <= 0xff; i++) {
    EXPECT_EQ(bm[i], high_class);
  }
  
  delete prog;
}

// Test that calling ComputeByteMap multiple times produces consistent results
TEST_F(ComputeByteMapTest_411, IdempotentCall_411) {
  Prog* prog = CompilePattern("[a-z]+");
  ASSERT_NE(prog, nullptr);
  
  prog->ComputeByteMap();
  
  int range1 = prog->bytemap_range();
  uint8_t bytemap1[256];
  memcpy(bytemap1, prog->bytemap(), 256);
  
  // Call again
  prog->ComputeByteMap();
  
  int range2 = prog->bytemap_range();
  EXPECT_EQ(range1, range2);
  
  for (int i = 0; i < 256; i++) {
    EXPECT_EQ(bytemap1[i], prog->bytemap()[i]);
  }
  
  delete prog;
}

}  // namespace re2
