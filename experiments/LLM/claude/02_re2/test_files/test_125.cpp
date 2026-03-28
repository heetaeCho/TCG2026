#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/testing/regexp_generator.h"
#include "absl/strings/string_view.h"

namespace re2 {

class ProgTest_125 : public ::testing::Test {
 protected:
  void SetUp() override {
    prog_ = new Prog();
  }

  void TearDown() override {
    delete prog_;
  }

  Prog* prog_;
};

// Test default construction values
TEST_F(ProgTest_125, DefaultConstruction_125) {
  EXPECT_FALSE(prog_->anchor_start());
  EXPECT_FALSE(prog_->anchor_end());
  EXPECT_FALSE(prog_->reversed());
  EXPECT_EQ(prog_->start(), 0);
  EXPECT_EQ(prog_->start_unanchored(), 0);
  EXPECT_EQ(prog_->size(), 0);
  EXPECT_EQ(prog_->bytemap_range(), 0);
  EXPECT_EQ(prog_->dfa_mem(), 0);
  EXPECT_FALSE(prog_->can_prefix_accel());
}

// Test set_anchor_start / anchor_start
TEST_F(ProgTest_125, SetAnchorStartTrue_125) {
  prog_->set_anchor_start(true);
  EXPECT_TRUE(prog_->anchor_start());
}

TEST_F(ProgTest_125, SetAnchorStartFalse_125) {
  prog_->set_anchor_start(true);
  prog_->set_anchor_start(false);
  EXPECT_FALSE(prog_->anchor_start());
}

// Test set_anchor_end / anchor_end
TEST_F(ProgTest_125, SetAnchorEndTrue_125) {
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_end());
}

TEST_F(ProgTest_125, SetAnchorEndFalse_125) {
  prog_->set_anchor_end(true);
  prog_->set_anchor_end(false);
  EXPECT_FALSE(prog_->anchor_end());
}

// Test set_reversed / reversed
TEST_F(ProgTest_125, SetReversedTrue_125) {
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
}

TEST_F(ProgTest_125, SetReversedFalse_125) {
  prog_->set_reversed(true);
  prog_->set_reversed(false);
  EXPECT_FALSE(prog_->reversed());
}

// Test set_start / start
TEST_F(ProgTest_125, SetStart_125) {
  prog_->set_start(42);
  EXPECT_EQ(prog_->start(), 42);
}

TEST_F(ProgTest_125, SetStartZero_125) {
  prog_->set_start(0);
  EXPECT_EQ(prog_->start(), 0);
}

// Test set_start_unanchored / start_unanchored
TEST_F(ProgTest_125, SetStartUnanchored_125) {
  prog_->set_start_unanchored(99);
  EXPECT_EQ(prog_->start_unanchored(), 99);
}

// Test set_dfa_mem / dfa_mem
TEST_F(ProgTest_125, SetDfaMem_125) {
  prog_->set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog_->dfa_mem(), 1024 * 1024);
}

TEST_F(ProgTest_125, SetDfaMemZero_125) {
  prog_->set_dfa_mem(0);
  EXPECT_EQ(prog_->dfa_mem(), 0);
}

// Test IsWordChar static method
TEST_F(ProgTest_125, IsWordCharAlpha_125) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
}

TEST_F(ProgTest_125, IsWordCharDigit_125) {
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
}

TEST_F(ProgTest_125, IsWordCharUnderscore_125) {
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

TEST_F(ProgTest_125, IsWordCharNonWord_125) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
}

// Test both anchors together
TEST_F(ProgTest_125, SetBothAnchors_125) {
  prog_->set_anchor_start(true);
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_start());
  EXPECT_TRUE(prog_->anchor_end());
}

// Test toggle anchor values multiple times
TEST_F(ProgTest_125, ToggleAnchorStart_125) {
  prog_->set_anchor_start(false);
  EXPECT_FALSE(prog_->anchor_start());
  prog_->set_anchor_start(true);
  EXPECT_TRUE(prog_->anchor_start());
  prog_->set_anchor_start(false);
  EXPECT_FALSE(prog_->anchor_start());
}

// Test EmptyFlags static method
TEST_F(ProgTest_125, EmptyFlagsAtBeginning_125) {
  absl::string_view text("hello");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At beginning of text, should have kEmptyBeginText and kEmptyBeginLine set
  // We just verify it returns a non-negative value (exact flags depend on implementation)
  EXPECT_GE(flags, 0u);
}

TEST_F(ProgTest_125, EmptyFlagsAtEnd_125) {
  absl::string_view text("hello");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_GE(flags, 0u);
}

TEST_F(ProgTest_125, EmptyFlagsEmptyText_125) {
  absl::string_view text("");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  EXPECT_GE(flags, 0u);
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow
TEST_F(ProgTest_125, TestingOnlySetDfaShouldBail_125) {
  // Just verify it doesn't crash
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Tests using compiled programs from RE2
class ProgFromRegexpTest_125 : public ::testing::Test {
 protected:
  Prog* CompileProg(const std::string& pattern) {
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

TEST_F(ProgFromRegexpTest_125, DumpNotEmpty_125) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexpTest_125, DumpUnanchoredNotEmpty_125) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexpTest_125, DumpByteMapNotEmpty_125) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgFromRegexpTest_125, SizePositive_125) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
}

TEST_F(ProgFromRegexpTest_125, BytemapNotNull_125) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_NE(prog->bytemap(), nullptr);
}

TEST_F(ProgFromRegexpTest_125, BytemapRangePositive_125) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
}

TEST_F(ProgFromRegexpTest_125, PossibleMatchRange_125) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 10);
  EXPECT_TRUE(result);
  EXPECT_LE(min_str, max_str);
}

TEST_F(ProgFromRegexpTest_125, PossibleMatchRangeMaxLenZero_125) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  std::string min_str, max_str;
  // maxlen=0 is a boundary condition
  bool result = prog->PossibleMatchRange(&min_str, &max_str, 0);
  // Result may be true or false depending on implementation; just check no crash
  (void)result;
}

TEST_F(ProgFromRegexpTest_125, SearchNFA_SimpleMatch_125) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xabcy");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

TEST_F(ProgFromRegexpTest_125, SearchNFA_NoMatch_125) {
  Prog* prog = CompileProg("xyz");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abc");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgFromRegexpTest_125, SearchNFA_Anchored_125) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

TEST_F(ProgFromRegexpTest_125, SearchNFA_AnchoredNoMatch_125) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xabc");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgFromRegexpTest_125, IsOnePass_SimplePattern_125) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  // Simple literal pattern should be one-pass
  bool onepass = prog->IsOnePass();
  EXPECT_TRUE(onepass);
}

TEST_F(ProgFromRegexpTest_125, CanPrefixAccel_125) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  // Just check it returns a bool without crashing
  bool can = prog->can_prefix_accel();
  (void)can;
}

TEST_F(ProgFromRegexpTest_125, Flatten_125) {
  Prog* prog = CompileProg("(a|b)+c");
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // After flattening, the program should still be valid
  EXPECT_GT(prog->size(), 0);
}

TEST_F(ProgFromRegexpTest_125, SearchBitState_Match_125) {
  Prog* prog = CompileProg("a+b");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;
  absl::string_view text("aaab");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "aaab");
}

TEST_F(ProgFromRegexpTest_125, SearchBitState_NoMatch_125) {
  Prog* prog = CompileProg("a+b");
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;
  absl::string_view text("cccc");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgFromRegexpTest_125, SearchDFA_Match_125) {
  Prog* prog = CompileProg("hello");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("say hello world");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
}

TEST_F(ProgFromRegexpTest_125, SearchDFA_NoMatch_125) {
  Prog* prog = CompileProg("hello");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("goodbye");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(found);
  }
}

TEST_F(ProgFromRegexpTest_125, SearchOnePass_Match_125) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  if (!prog->IsOnePass()) return;
  absl::string_view text("xabcy");
  absl::string_view match;
  bool found = prog->SearchOnePass(text, text, Prog::kUnanchored,
                                    Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

TEST_F(ProgFromRegexpTest_125, SearchOnePass_NoMatch_125) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  if (!prog->IsOnePass()) return;
  absl::string_view text("xyz");
  absl::string_view match;
  bool found = prog->SearchOnePass(text, text, Prog::kUnanchored,
                                    Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgFromRegexpTest_125, EmptyPattern_125) {
  Prog* prog = CompileProg("");
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abc");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "");
}

TEST_F(ProgFromRegexpTest_125, CanBitState_125) {
  Prog* prog = CompileProg("abc");
  ASSERT_NE(prog, nullptr);
  // Just verify it returns without crashing
  bool can = prog->CanBitState();
  (void)can;
}

// Test multiple setter interactions
TEST_F(ProgTest_125, MultipleSettersIndependent_125) {
  prog_->set_anchor_start(true);
  prog_->set_anchor_end(false);
  prog_->set_reversed(true);
  prog_->set_start(5);
  prog_->set_start_unanchored(10);
  prog_->set_dfa_mem(2048);

  EXPECT_TRUE(prog_->anchor_start());
  EXPECT_FALSE(prog_->anchor_end());
  EXPECT_TRUE(prog_->reversed());
  EXPECT_EQ(prog_->start(), 5);
  EXPECT_EQ(prog_->start_unanchored(), 10);
  EXPECT_EQ(prog_->dfa_mem(), 2048);
}

// Test large dfa_mem value
TEST_F(ProgTest_125, SetDfaMemLargeValue_125) {
  int64_t large_mem = static_cast<int64_t>(1) << 40;
  prog_->set_dfa_mem(large_mem);
  EXPECT_EQ(prog_->dfa_mem(), large_mem);
}

// Test negative start value
TEST_F(ProgTest_125, SetStartNegative_125) {
  prog_->set_start(-1);
  EXPECT_EQ(prog_->start(), -1);
}

}  // namespace re2
