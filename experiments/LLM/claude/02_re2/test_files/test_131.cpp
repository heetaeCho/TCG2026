#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/re2.h"

#include <string>
#include <cstring>
#include <memory>

namespace re2 {

// Helper to compile a Prog from a regex pattern
static Prog* CompileRegexp(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

class ProgTest_131 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any progs
  }
};

// Test that a default-constructed Prog has expected initial state
TEST_F(ProgTest_131, DefaultConstructor_131) {
  Prog prog;
  EXPECT_EQ(prog.start(), 0);
  EXPECT_EQ(prog.start_unanchored(), 0);
  EXPECT_EQ(prog.size(), 0);
  EXPECT_FALSE(prog.reversed());
  EXPECT_FALSE(prog.anchor_start());
  EXPECT_FALSE(prog.anchor_end());
  EXPECT_EQ(prog.bytemap_range(), 0);
}

// Test setters and getters for start
TEST_F(ProgTest_131, SetStart_131) {
  Prog prog;
  prog.set_start(5);
  EXPECT_EQ(prog.start(), 5);
}

// Test setters and getters for start_unanchored
TEST_F(ProgTest_131, SetStartUnanchored_131) {
  Prog prog;
  prog.set_start_unanchored(10);
  EXPECT_EQ(prog.start_unanchored(), 10);
}

// Test setters and getters for reversed
TEST_F(ProgTest_131, SetReversed_131) {
  Prog prog;
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test setters and getters for anchor_start
TEST_F(ProgTest_131, SetAnchorStart_131) {
  Prog prog;
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test setters and getters for anchor_end
TEST_F(ProgTest_131, SetAnchorEnd_131) {
  Prog prog;
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test setters and getters for dfa_mem
TEST_F(ProgTest_131, SetDfaMem_131) {
  Prog prog;
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog.dfa_mem(), 1024 * 1024);
}

// Test default can_prefix_accel is false
TEST_F(ProgTest_131, DefaultCanPrefixAccel_131) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test ConfigurePrefixAccel with a single-char prefix (no foldcase)
TEST_F(ProgTest_131, ConfigurePrefixAccelSingleChar_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("a", false);
  EXPECT_TRUE(prog.can_prefix_accel());
}

// Test ConfigurePrefixAccel with a multi-char prefix (no foldcase)
TEST_F(ProgTest_131, ConfigurePrefixAccelMultiChar_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("abc", false);
  EXPECT_TRUE(prog.can_prefix_accel());
}

// Test ConfigurePrefixAccel with foldcase
TEST_F(ProgTest_131, ConfigurePrefixAccelFoldcase_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("abc", true);
  EXPECT_TRUE(prog.can_prefix_accel());
}

// Test PrefixAccel with single char prefix finds the character
TEST_F(ProgTest_131, PrefixAccelSingleCharFound_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("x", false);
  ASSERT_TRUE(prog.can_prefix_accel());

  const char data[] = "hello x world";
  const void* result = prog.PrefixAccel(data, strlen(data));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(static_cast<const char*>(result), &data[6]);
}

// Test PrefixAccel with single char prefix not found
TEST_F(ProgTest_131, PrefixAccelSingleCharNotFound_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("z", false);
  ASSERT_TRUE(prog.can_prefix_accel());

  const char data[] = "hello world";
  const void* result = prog.PrefixAccel(data, strlen(data));
  EXPECT_EQ(result, nullptr);
}

// Test PrefixAccel with single char at beginning
TEST_F(ProgTest_131, PrefixAccelSingleCharAtBeginning_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("h", false);
  ASSERT_TRUE(prog.can_prefix_accel());

  const char data[] = "hello";
  const void* result = prog.PrefixAccel(data, strlen(data));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(static_cast<const char*>(result), &data[0]);
}

// Test PrefixAccel with single char at end
TEST_F(ProgTest_131, PrefixAccelSingleCharAtEnd_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("o", false);
  ASSERT_TRUE(prog.can_prefix_accel());

  const char data[] = "hello";
  const void* result = prog.PrefixAccel(data, strlen(data));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(static_cast<const char*>(result), &data[4]);
}

// Test PrefixAccel with empty data
TEST_F(ProgTest_131, PrefixAccelEmptyData_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("a", false);
  ASSERT_TRUE(prog.can_prefix_accel());

  const char data[] = "";
  const void* result = prog.PrefixAccel(data, 0);
  EXPECT_EQ(result, nullptr);
}

// Test PrefixAccel with multi-char prefix (FrontAndBack path)
TEST_F(ProgTest_131, PrefixAccelMultiCharFound_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("he", false);
  ASSERT_TRUE(prog.can_prefix_accel());

  const char data[] = "say hello there";
  const void* result = prog.PrefixAccel(data, strlen(data));
  // Should find "he" somewhere in the data
  ASSERT_NE(result, nullptr);
  // The result should point to a position within data
  EXPECT_GE(static_cast<const char*>(result), data);
  EXPECT_LT(static_cast<const char*>(result), data + strlen(data));
}

// Test PrefixAccel with multi-char prefix not found
TEST_F(ProgTest_131, PrefixAccelMultiCharNotFound_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("xyz", false);
  ASSERT_TRUE(prog.can_prefix_accel());

  const char data[] = "hello world";
  const void* result = prog.PrefixAccel(data, strlen(data));
  EXPECT_EQ(result, nullptr);
}

// Test PrefixAccel with foldcase prefix (ShiftDFA path)
TEST_F(ProgTest_131, PrefixAccelFoldcaseFound_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("hello", true);
  ASSERT_TRUE(prog.can_prefix_accel());

  const char data[] = "say HELLO there";
  const void* result = prog.PrefixAccel(data, strlen(data));
  // With foldcase, HELLO should match hello
  ASSERT_NE(result, nullptr);
  EXPECT_GE(static_cast<const char*>(result), data);
  EXPECT_LT(static_cast<const char*>(result), data + strlen(data));
}

// Test PrefixAccel with foldcase prefix not found
TEST_F(ProgTest_131, PrefixAccelFoldcaseNotFound_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("xyz", true);
  ASSERT_TRUE(prog.can_prefix_accel());

  const char data[] = "hello world";
  const void* result = prog.PrefixAccel(data, strlen(data));
  EXPECT_EQ(result, nullptr);
}

// Test PrefixAccel with size of 1
TEST_F(ProgTest_131, PrefixAccelSizeOne_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("a", false);
  ASSERT_TRUE(prog.can_prefix_accel());

  const char data[] = "a";
  const void* result = prog.PrefixAccel(data, 1);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(static_cast<const char*>(result), data);
}

// Test PrefixAccel single char not matching in single-byte data
TEST_F(ProgTest_131, PrefixAccelSingleCharSizeOneNotFound_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("b", false);
  ASSERT_TRUE(prog.can_prefix_accel());

  const char data[] = "a";
  const void* result = prog.PrefixAccel(data, 1);
  EXPECT_EQ(result, nullptr);
}

// Test IsWordChar
TEST_F(ProgTest_131, IsWordCharAlpha_131) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

TEST_F(ProgTest_131, IsWordCharNonWord_131) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('!'));
}

// Test EmptyFlags at various positions
TEST_F(ProgTest_131, EmptyFlagsBeginning_131) {
  absl::string_view text = "hello";
  uint32_t flags = Prog::EmptyFlags(text, text.data());
  // At the beginning of text, should have kEmptyBeginText and kEmptyBeginLine
  // We just check it returns something (implementation details are opaque)
  // but we know it should be non-zero for beginning of text.
  EXPECT_NE(flags, 0u);
}

TEST_F(ProgTest_131, EmptyFlagsEnd_131) {
  absl::string_view text = "hello";
  uint32_t flags = Prog::EmptyFlags(text, text.data() + text.size());
  // At the end of text, should have kEmptyEndText and kEmptyEndLine
  EXPECT_NE(flags, 0u);
}

TEST_F(ProgTest_131, EmptyFlagsMiddle_131) {
  absl::string_view text = "hello";
  uint32_t flags = Prog::EmptyFlags(text, text.data() + 2);
  // In the middle, might have word boundary flags etc.
  // Just ensure it doesn't crash.
  (void)flags;
}

// Test Dump on a compiled program
TEST_F(ProgTest_131, DumpCompiledProg_131) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

// Test DumpUnanchored on a compiled program
TEST_F(ProgTest_131, DumpUnanchoredCompiledProg_131) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

// Test DumpByteMap on a compiled program
TEST_F(ProgTest_131, DumpByteMapCompiledProg_131) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
}

// Test compilation produces non-null prog
TEST_F(ProgTest_131, CompileBasicRegexp_131) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
}

// Test bytemap on a compiled program
TEST_F(ProgTest_131, ByteMapCompiledProg_131) {
  std::unique_ptr<Prog> prog(CompileRegexp("[a-z]+"));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
}

// Test PossibleMatchRange
TEST_F(ProgTest_131, PossibleMatchRange_131) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool ok = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(ok);
  EXPECT_LE(min_str, max_str);
}

// Test PossibleMatchRange with maxlen of 0
TEST_F(ProgTest_131, PossibleMatchRangeMaxlenZero_131) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  // maxlen 0 is a boundary case
  bool ok = prog->PossibleMatchRange(&min_str, &max_str, 0);
  // Result may vary; just ensure no crash
  (void)ok;
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_131, TestingOnlySetDfaShouldBail_131) {
  // Just ensure the static function can be called without crashing
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test ConfigurePrefixAccel with empty prefix
TEST_F(ProgTest_131, ConfigurePrefixAccelEmptyPrefix_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("", false);
  // An empty prefix should not enable prefix accel
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test PrefixAccel multi-char with data shorter than prefix
TEST_F(ProgTest_131, PrefixAccelMultiCharDataShorterThanPrefix_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("hello", false);
  ASSERT_TRUE(prog.can_prefix_accel());

  const char data[] = "hel";
  const void* result = prog.PrefixAccel(data, strlen(data));
  EXPECT_EQ(result, nullptr);
}

// Test PrefixAccel multi-char exact match
TEST_F(ProgTest_131, PrefixAccelMultiCharExactMatch_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("hello", false);
  ASSERT_TRUE(prog.can_prefix_accel());

  const char data[] = "hello";
  const void* result = prog.PrefixAccel(data, strlen(data));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(static_cast<const char*>(result), data);
}

// Test via RE2 that prefix acceleration works end-to-end
TEST_F(ProgTest_131, RE2PrefixAccelEndToEnd_131) {
  RE2 re("hello world");
  EXPECT_TRUE(RE2::PartialMatch("say hello world now", re));
  EXPECT_FALSE(RE2::PartialMatch("say goodbye now", re));
}

// Test that CanBitState returns meaningful value for compiled prog
TEST_F(ProgTest_131, CanBitState_131) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  // Just test it doesn't crash; the return depends on prog size
  bool can = prog->CanBitState();
  (void)can;
}

// Test multi-char prefix with repeated characters
TEST_F(ProgTest_131, PrefixAccelRepeatedChars_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("aaa", false);
  ASSERT_TRUE(prog.can_prefix_accel());

  const char data[] = "bbaaa";
  const void* result = prog.PrefixAccel(data, strlen(data));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(static_cast<const char*>(result), &data[2]);
}

// Test PrefixAccel with null bytes in data
TEST_F(ProgTest_131, PrefixAccelWithNullBytes_131) {
  Prog prog;
  prog.ConfigurePrefixAccel("ab", false);
  ASSERT_TRUE(prog.can_prefix_accel());

  const char data[] = "x\0ab";
  const void* result = prog.PrefixAccel(data, 4);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(static_cast<const char*>(result), &data[2]);
}

// Test single char prefix searching for null byte
TEST_F(ProgTest_131, PrefixAccelSearchForNullByte_131) {
  Prog prog;
  std::string prefix(1, '\0');
  prog.ConfigurePrefixAccel(prefix, false);
  ASSERT_TRUE(prog.can_prefix_accel());

  const char data[] = "abc\0def";
  const void* result = prog.PrefixAccel(data, 7);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(static_cast<const char*>(result), &data[3]);
}

}  // namespace re2
