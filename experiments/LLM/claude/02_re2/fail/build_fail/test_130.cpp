#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"
#include <string>
#include <memory>

namespace re2 {

// Helper to compile a Regexp into a Prog for testing
class ProgTest_130 : public ::testing::Test {
 protected:
  Prog* CompileRegexp(const char* pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re == nullptr) return nullptr;
    Prog* prog = re->CompileToProg(0);
    re->Decref();
    return prog;
  }
};

// Test default construction and initial state
TEST_F(ProgTest_130, DefaultConstruction_130) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
  EXPECT_FALSE(prog.anchor_start());
  EXPECT_FALSE(prog.anchor_end());
  EXPECT_FALSE(prog.reversed());
  EXPECT_EQ(prog.start(), 0);
  EXPECT_EQ(prog.start_unanchored(), 0);
  EXPECT_EQ(prog.dfa_mem(), 0);
}

// Test set/get anchor_start
TEST_F(ProgTest_130, SetAnchorStart_130) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_start());
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

// Test set/get anchor_end
TEST_F(ProgTest_130, SetAnchorEnd_130) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_end());
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

// Test set/get reversed
TEST_F(ProgTest_130, SetReversed_130) {
  Prog prog;
  EXPECT_FALSE(prog.reversed());
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

// Test set/get start
TEST_F(ProgTest_130, SetStart_130) {
  Prog prog;
  prog.set_start(5);
  EXPECT_EQ(prog.start(), 5);
  prog.set_start(0);
  EXPECT_EQ(prog.start(), 0);
}

// Test set/get start_unanchored
TEST_F(ProgTest_130, SetStartUnanchored_130) {
  Prog prog;
  prog.set_start_unanchored(10);
  EXPECT_EQ(prog.start_unanchored(), 10);
}

// Test set/get dfa_mem
TEST_F(ProgTest_130, SetDfaMem_130) {
  Prog prog;
  EXPECT_EQ(prog.dfa_mem(), 0);
  prog.set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog.dfa_mem(), 1024 * 1024);
}

// Test can_prefix_accel returns false by default (prefix_size_ == 0)
TEST_F(ProgTest_130, CanPrefixAccelDefaultFalse_130) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test can_prefix_accel after ConfigurePrefixAccel with a non-empty prefix
TEST_F(ProgTest_130, CanPrefixAccelAfterConfigure_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello.*world"));
  ASSERT_NE(prog, nullptr);
  // ConfigurePrefixAccel with a non-empty prefix should enable prefix accel
  prog->ConfigurePrefixAccel("hello", false);
  EXPECT_TRUE(prog->can_prefix_accel());
}

// Test ConfigurePrefixAccel with empty prefix
TEST_F(ProgTest_130, ConfigurePrefixAccelEmpty_130) {
  std::unique_ptr<Prog> prog(CompileRegexp(".*"));
  ASSERT_NE(prog, nullptr);
  prog->ConfigurePrefixAccel("", false);
  EXPECT_FALSE(prog->can_prefix_accel());
}

// Test PrefixAccel returns nullptr when prefix accel is not configured
TEST_F(ProgTest_130, PrefixAccelNullWhenNotConfigured_130) {
  Prog prog;
  const char* data = "hello world";
  const void* result = prog.PrefixAccel(data, strlen(data));
  EXPECT_EQ(result, nullptr);
}

// Test PrefixAccel with configured prefix
TEST_F(ProgTest_130, PrefixAccelFindsPrefix_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello.*"));
  ASSERT_NE(prog, nullptr);
  prog->ConfigurePrefixAccel("hello", false);
  if (prog->can_prefix_accel()) {
    const char* data = "XXXhelloYYY";
    const void* result = prog->PrefixAccel(data, strlen(data));
    // If found, result should point somewhere within the data
    if (result != nullptr) {
      EXPECT_GE(result, static_cast<const void*>(data));
      EXPECT_LE(result, static_cast<const void*>(data + strlen(data)));
    }
  }
}

// Test PrefixAccel with size zero
TEST_F(ProgTest_130, PrefixAccelZeroSize_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  prog->ConfigurePrefixAccel("hello", false);
  const char* data = "hello";
  const void* result = prog->PrefixAccel(data, 0);
  EXPECT_EQ(result, nullptr);
}

// Test IsWordChar for various characters
TEST_F(ProgTest_130, IsWordChar_130) {
  // Alphanumeric and underscore should be word chars
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));
  
  // Non-word chars
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
}

// Test Dump on compiled prog
TEST_F(ProgTest_130, Dump_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("a"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

// Test DumpUnanchored on compiled prog
TEST_F(ProgTest_130, DumpUnanchored_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

// Test DumpByteMap on compiled prog
TEST_F(ProgTest_130, DumpByteMap_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  prog->ComputeByteMap();
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
}

// Test bytemap is non-null on compiled prog
TEST_F(ProgTest_130, ByteMap_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("a"));
  ASSERT_NE(prog, nullptr);
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
}

// Test bytemap_range on compiled prog
TEST_F(ProgTest_130, ByteMapRange_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("a"));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
}

// Test size on compiled prog
TEST_F(ProgTest_130, Size_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
}

// Test EmptyFlags at different positions
TEST_F(ProgTest_130, EmptyFlags_130) {
  absl::string_view text = "hello world";
  
  // At the beginning of text
  uint32_t flags_begin = Prog::EmptyFlags(text, text.data());
  // Should include kEmptyBeginText and kEmptyBeginLine among others
  EXPECT_NE(flags_begin, 0u);
  
  // At the end of text
  uint32_t flags_end = Prog::EmptyFlags(text, text.data() + text.size());
  // Should include kEmptyEndText and kEmptyEndLine among others
  EXPECT_NE(flags_end, 0u);
}

// Test PossibleMatchRange
TEST_F(ProgTest_130, PossibleMatchRange_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_str, max_str);
}

// Test PossibleMatchRange with maxlen = 0
TEST_F(ProgTest_130, PossibleMatchRangeZeroMaxlen_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 0);
  // With maxlen 0, behavior should still be well-defined
  // (may return true or false depending on implementation)
  (void)result;
}

// Test Flatten does not crash
TEST_F(ProgTest_130, Flatten_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("(a|b)*c"));
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // After flattening, the program should still be usable
  EXPECT_GT(prog->size(), 0);
}

// Test Optimize does not crash
TEST_F(ProgTest_130, Optimize_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("a+b+c"));
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  EXPECT_GT(prog->size(), 0);
}

// Test IsOnePass
TEST_F(ProgTest_130, IsOnePass_130) {
  // Simple pattern that should be one-pass
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  // Just verify it doesn't crash; result depends on pattern
  bool onepass = prog->IsOnePass();
  (void)onepass;
}

// Test CanBitState
TEST_F(ProgTest_130, CanBitState_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  // Just verify it returns a value without crashing
  bool can = prog->CanBitState();
  (void)can;
}

// Test SearchNFA basic match
TEST_F(ProgTest_130, SearchNFA_BasicMatch_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("say hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

// Test SearchNFA no match
TEST_F(ProgTest_130, SearchNFA_NoMatch_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("xyz"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test SearchNFA anchored
TEST_F(ProgTest_130, SearchNFA_Anchored_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "hello");
}

// Test SearchNFA anchored no match
TEST_F(ProgTest_130, SearchNFA_AnchoredNoMatch_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("world"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("hello world");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

// Test SearchDFA basic match
TEST_F(ProgTest_130, SearchDFA_BasicMatch_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("say hello world");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
}

// Test SearchDFA no match
TEST_F(ProgTest_130, SearchDFA_NoMatch_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("xyz"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("hello world");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(found);
  }
}

// Test SearchBitState basic match
TEST_F(ProgTest_130, SearchBitState_BasicMatch_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("hello"));
  ASSERT_NE(prog, nullptr);
  if (prog->CanBitState()) {
    absl::string_view text("say hello world");
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "hello");
  }
}

// Test SearchBitState no match
TEST_F(ProgTest_130, SearchBitState_NoMatch_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("xyz"));
  ASSERT_NE(prog, nullptr);
  if (prog->CanBitState()) {
    absl::string_view text("hello world");
    absl::string_view match;
    bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                       Prog::kFirstMatch, &match, 1);
    EXPECT_FALSE(found);
  }
}

// Test empty text search
TEST_F(ProgTest_130, SearchNFA_EmptyText_130) {
  std::unique_ptr<Prog> prog(CompileRegexp(""));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

// Test SearchOnePass for a one-pass pattern
TEST_F(ProgTest_130, SearchOnePass_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("^abc$"));
  ASSERT_NE(prog, nullptr);
  if (prog->IsOnePass()) {
    absl::string_view text("abc");
    absl::string_view match;
    bool found = prog->SearchOnePass(text, text, Prog::kAnchored,
                                      Prog::kFirstMatch, &match, 1);
    EXPECT_TRUE(found);
    EXPECT_EQ(match, "abc");
  }
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_130, TestingOnlySetDfaShouldBailWhenSlow_130) {
  // Just test it doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test CompileSet
TEST_F(ProgTest_130, CompileSet_130) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::unique_ptr<Prog> prog(Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20));
  re->Decref();
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
}

// Test BuildEntireDFA
TEST_F(ProgTest_130, BuildEntireDFA_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("[ab]"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  int states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(states, 0);
}

// Test ConfigurePrefixAccel with foldcase
TEST_F(ProgTest_130, ConfigurePrefixAccelFoldcase_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("(?i)hello"));
  ASSERT_NE(prog, nullptr);
  prog->ConfigurePrefixAccel("hello", true);
  // May or may not enable prefix accel depending on implementation
  // Just verify it doesn't crash
}

// Test PrefixAccel when prefix is present in data
TEST_F(ProgTest_130, PrefixAccelPresent_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  prog->ConfigurePrefixAccel("abc", false);
  if (prog->can_prefix_accel()) {
    const char* data = "xxxabcyyy";
    const void* result = prog->PrefixAccel(data, strlen(data));
    if (result != nullptr) {
      // Result should point to or before 'a' in "abc"
      EXPECT_GE(result, static_cast<const void*>(data));
      EXPECT_LE(result, static_cast<const void*>(data + strlen(data)));
    }
  }
}

// Test PrefixAccel when prefix is not present
TEST_F(ProgTest_130, PrefixAccelNotPresent_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  prog->ConfigurePrefixAccel("abc", false);
  if (prog->can_prefix_accel()) {
    const char* data = "xxxdefyyy";
    const void* result = prog->PrefixAccel(data, strlen(data));
    // When not found, result should be nullptr or point past data
    // (implementation-dependent, but shouldn't crash)
    (void)result;
  }
}

// Test inst_count
TEST_F(ProgTest_130, InstCount_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  // Inst types are 0-7 based on the inst_count_ array size
  int total = 0;
  for (int i = 0; i < 8; i++) {
    int count = prog->inst_count(static_cast<Prog::InstOp>(i));
    EXPECT_GE(count, 0);
    total += count;
  }
  // Total inst count should match size or close to it
  EXPECT_GT(total, 0);
}

// Test bit_state_text_max_size
TEST_F(ProgTest_130, BitStateTextMaxSize_130) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  size_t max_size = prog->bit_state_text_max_size();
  // Should be a non-negative value
  EXPECT_GE(max_size, 0u);
}

}  // namespace re2
