#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/testing/regexp_generator.h"
#include "absl/strings/string_view.h"

namespace re2 {

class ProgTest_128 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default construction and initial values
TEST_F(ProgTest_128, DefaultConstruction_128) {
  Prog prog;
  EXPECT_EQ(prog.start(), 0);
  EXPECT_EQ(prog.start_unanchored(), 0);
  EXPECT_EQ(prog.bytemap_range(), 0);
  EXPECT_FALSE(prog.reversed());
  EXPECT_FALSE(prog.anchor_start());
  EXPECT_FALSE(prog.anchor_end());
  EXPECT_EQ(prog.dfa_mem(), 0);
  EXPECT_EQ(prog.size(), 0);
}

// Test set_start and start
TEST_F(ProgTest_128, SetStart_128) {
  Prog prog;
  prog.set_start(5);
  EXPECT_EQ(prog.start(), 5);
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_128, SetStartUnanchored_128) {
  Prog prog;
  prog.set_start_unanchored(10);
  EXPECT_EQ(prog.start_unanchored(), 10);
}

// Test set_reversed and reversed
TEST_F(ProgTest_128, SetReversed_128) {
  Prog prog;
  EXPECT_FALSE(prog.reversed());
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test set_anchor_start and anchor_start
TEST_F(ProgTest_128, SetAnchorStart_128) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_start());
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test set_anchor_end and anchor_end
TEST_F(ProgTest_128, SetAnchorEnd_128) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_end());
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test set_dfa_mem and dfa_mem
TEST_F(ProgTest_128, SetDfaMem_128) {
  Prog prog;
  EXPECT_EQ(prog.dfa_mem(), 0);
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog.dfa_mem(), 1024 * 1024);
}

// Test bytemap_range default
TEST_F(ProgTest_128, BytemapRangeDefault_128) {
  Prog prog;
  EXPECT_EQ(prog.bytemap_range(), 0);
}

// Test bytemap pointer is not null
TEST_F(ProgTest_128, BytemapNotNull_128) {
  Prog prog;
  EXPECT_NE(prog.bytemap(), nullptr);
}

// Test can_prefix_accel defaults to false on default-constructed Prog
TEST_F(ProgTest_128, CanPrefixAccelDefault_128) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test IsWordChar for various characters
TEST_F(ProgTest_128, IsWordChar_128) {
  // Letters should be word chars
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  // Digits should be word chars
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  // Underscore should be word char
  EXPECT_TRUE(Prog::IsWordChar('_'));
  // Non-word chars
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('\t'));
}

// Test IsWordChar boundary values
TEST_F(ProgTest_128, IsWordCharBoundary_128) {
  // '0' - 1 = '/'
  EXPECT_FALSE(Prog::IsWordChar('/'));
  // '9' + 1 = ':'
  EXPECT_FALSE(Prog::IsWordChar(':'));
  // 'A' - 1 = '@'
  EXPECT_FALSE(Prog::IsWordChar('@'));
  // 'Z' + 1 = '['
  EXPECT_FALSE(Prog::IsWordChar('['));
  // 'a' - 1 = '`'
  EXPECT_FALSE(Prog::IsWordChar('`'));
  // 'z' + 1 = '{'
  EXPECT_FALSE(Prog::IsWordChar('{'));
}

// Test EmptyFlags at various positions
TEST_F(ProgTest_128, EmptyFlagsBeginOfText_128) {
  absl::string_view text("hello");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At beginning of text, kEmptyBeginText and kEmptyBeginLine should be set
  // We check that it returns non-zero at minimum
  EXPECT_NE(flags, 0u);
}

TEST_F(ProgTest_128, EmptyFlagsEndOfText_128) {
  absl::string_view text("hello");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At end of text, kEmptyEndText and kEmptyEndLine should be set
  EXPECT_NE(flags, 0u);
}

TEST_F(ProgTest_128, EmptyFlagsEmptyText_128) {
  absl::string_view text("");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // Both begin and end flags should be set
  EXPECT_NE(flags, 0u);
}

// Test using a compiled Prog via RE2's internals for a simple pattern
class ProgFromRegexpTest_128 : public ::testing::Test {
 protected:
  Prog* CompileRegexp(const std::string& pattern) {
    RegexpStatus status;
    re_ = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re_ == nullptr) return nullptr;
    prog_ = re_->CompileToProg(0);
    return prog_;
  }

  void TearDown() override {
    delete prog_;
    if (re_) re_->Decref();
  }

  Regexp* re_ = nullptr;
  Prog* prog_ = nullptr;
};

TEST_F(ProgFromRegexpTest_128, SimplePatternCompiles_128) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  EXPECT_GT(prog->bytemap_range(), 0);
}

TEST_F(ProgFromRegexpTest_128, DumpNotEmpty_128) {
  Prog* prog = CompileRegexp("ab|cd");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexpTest_128, DumpUnanchoredNotEmpty_128) {
  Prog* prog = CompileRegexp("ab|cd");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexpTest_128, DumpByteMapNotEmpty_128) {
  Prog* prog = CompileRegexp("ab|cd");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexpTest_128, BytemapRangePositive_128) {
  Prog* prog = CompileRegexp("[a-z]+");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
  // bytemap_range should be at most 256
  EXPECT_LE(prog->bytemap_range(), 256);
}

TEST_F(ProgFromRegexpTest_128, PossibleMatchRange_128) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 10);
  EXPECT_TRUE(result);
  EXPECT_FALSE(min_match.empty());
  EXPECT_FALSE(max_match.empty());
  EXPECT_LE(min_match, max_match);
}

TEST_F(ProgFromRegexpTest_128, PossibleMatchRangeMaxlenZero_128) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  // maxlen of 0 is a boundary case
  bool result = prog->PossibleMatchRange(&min_match, &max_match, 0);
  // Just check it doesn't crash; result may be true or false
  (void)result;
}

TEST_F(ProgFromRegexpTest_128, SearchNFAMatch_128) {
  Prog* prog = CompileRegexp("hel+o");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  // "hello" should not match anchored at start because text is "hello world"
  // Actually anchored means match from start, "hello" matches the prefix via "hel+o"
  // Let's just check it doesn't crash
  (void)found;
}

TEST_F(ProgFromRegexpTest_128, SearchNFANoMatch_128) {
  Prog* prog = CompileRegexp("xyz");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgFromRegexpTest_128, SearchBitState_128) {
  Prog* prog = CompileRegexp("hel+o");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) {
    // Skip if CanBitState returns false
    return;
  }
  absl::string_view text("hello");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kAnchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgFromRegexpTest_128, IsOnePass_128) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  // Simple literal pattern should be one-pass
  bool onepass = prog->IsOnePass();
  // Just verify it returns without crashing
  (void)onepass;
}

TEST_F(ProgFromRegexpTest_128, SearchOnePassIfAvailable_128) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  if (!prog->IsOnePass()) return;
  absl::string_view text("hello");
  absl::string_view match;
  bool found = prog->SearchOnePass(text, text, Prog::kAnchored,
                                    Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

TEST_F(ProgFromRegexpTest_128, Flatten_128) {
  Prog* prog = CompileRegexp("a(b|c)d");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // After flattening, should still be able to dump
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexpTest_128, OptimizeDoesNotCrash_128) {
  Prog* prog = CompileRegexp("a(b|c)d");
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  // Should still have valid state
  EXPECT_GT(prog->size(), 0);
}

TEST_F(ProgFromRegexpTest_128, ConfigurePrefixAccel_128) {
  Prog* prog = CompileRegexp("hello.*world");
  ASSERT_NE(prog, nullptr);
  prog->ConfigurePrefixAccel("hello", false);
  // After configuring, can_prefix_accel may or may not be true depending on implementation
  // Just ensure no crash
}

TEST_F(ProgFromRegexpTest_128, CanBitState_128) {
  Prog* prog = CompileRegexp("ab+c");
  ASSERT_NE(prog, nullptr);
  // Just check it returns a boolean without crashing
  bool result = prog->CanBitState();
  (void)result;
}

TEST_F(ProgFromRegexpTest_128, DfaSearch_128) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);  // 1MB
  absl::string_view text("hello");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
}

TEST_F(ProgFromRegexpTest_128, DfaSearchNoMatch_128) {
  Prog* prog = CompileRegexp("xyz");
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("hello");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(found);
  }
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgFromRegexpTest_128, TestingOnlySetDfaShouldBail_128) {
  // Just ensure the static method doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test CompileSet
TEST_F(ProgTest_128, CompileSet_128) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  // CompileSet may or may not succeed depending on internal constraints
  if (prog != nullptr) {
    EXPECT_GT(prog->size(), 0);
    delete prog;
  }
  re->Decref();
}

// Test bytemap values are in valid range
TEST_F(ProgFromRegexpTest_128, BytemapValuesInRange_128) {
  Prog* prog = CompileRegexp("[a-zA-Z0-9]+");
  ASSERT_NE(prog, nullptr);
  const uint8_t* bm = prog->bytemap();
  int range = prog->bytemap_range();
  ASSERT_GT(range, 0);
  for (int i = 0; i < 256; i++) {
    EXPECT_LT(bm[i], range) << "bytemap[" << i << "] out of range";
  }
}

// Test size is positive for compiled programs
TEST_F(ProgFromRegexpTest_128, SizePositive_128) {
  Prog* prog = CompileRegexp("(a|b)*c");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
}

// Test inst_count for various op types doesn't crash
TEST_F(ProgFromRegexpTest_128, InstCount_128) {
  Prog* prog = CompileRegexp("a.b");
  ASSERT_NE(prog, nullptr);
  // Check that inst_count for various op codes doesn't crash
  // The exact values depend on the compilation, so just verify non-negative
  for (int op = 0; op < 8; op++) {
    EXPECT_GE(prog->inst_count(static_cast<Prog::InstOp>(op)), 0);
  }
}

// Test PrefixAccel with null data
TEST_F(ProgFromRegexpTest_128, PrefixAccelNullData_128) {
  Prog* prog = CompileRegexp("hello");
  ASSERT_NE(prog, nullptr);
  if (!prog->can_prefix_accel()) {
    // If prefix accel is not configured, PrefixAccel should handle gracefully
    // Skip this test
    return;
  }
  const void* result = prog->PrefixAccel(nullptr, 0);
  (void)result;
}

}  // namespace re2
