#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/sparse_array.h"
#include "re2/sparse_set.h"
#include "absl/strings/string_view.h"
#include <string>
#include <memory>

namespace re2 {

// Helper to compile a Regexp into a Prog for testing purposes
class ProgTest_398 : public ::testing::Test {
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

TEST_F(ProgTest_398, DefaultConstructor_398) {
  Prog prog;
  EXPECT_EQ(prog.start(), 0);
  EXPECT_EQ(prog.start_unanchored(), 0);
  EXPECT_EQ(prog.size(), 0);
  EXPECT_FALSE(prog.reversed());
  EXPECT_FALSE(prog.anchor_start());
  EXPECT_FALSE(prog.anchor_end());
  EXPECT_EQ(prog.bytemap_range(), 0);
  EXPECT_EQ(prog.dfa_mem(), 0);
  EXPECT_FALSE(prog.can_prefix_accel());
}

TEST_F(ProgTest_398, SetStart_398) {
  Prog prog;
  prog.set_start(5);
  EXPECT_EQ(prog.start(), 5);
}

TEST_F(ProgTest_398, SetStartUnanchored_398) {
  Prog prog;
  prog.set_start_unanchored(10);
  EXPECT_EQ(prog.start_unanchored(), 10);
}

TEST_F(ProgTest_398, SetReversed_398) {
  Prog prog;
  EXPECT_FALSE(prog.reversed());
  prog.set_reversed(true);
  EXPECT_TRUE(prog.reversed());
  prog.set_reversed(false);
  EXPECT_FALSE(prog.reversed());
}

TEST_F(ProgTest_398, SetAnchorStart_398) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_start());
  prog.set_anchor_start(true);
  EXPECT_TRUE(prog.anchor_start());
  prog.set_anchor_start(false);
  EXPECT_FALSE(prog.anchor_start());
}

TEST_F(ProgTest_398, SetAnchorEnd_398) {
  Prog prog;
  EXPECT_FALSE(prog.anchor_end());
  prog.set_anchor_end(true);
  EXPECT_TRUE(prog.anchor_end());
  prog.set_anchor_end(false);
  EXPECT_FALSE(prog.anchor_end());
}

TEST_F(ProgTest_398, SetDfaMem_398) {
  Prog prog;
  prog.set_dfa_mem(1024);
  EXPECT_EQ(prog.dfa_mem(), 1024);
}

TEST_F(ProgTest_398, IsWordChar_398) {
  // Letters
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  // Digits
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  // Underscore
  EXPECT_TRUE(Prog::IsWordChar('_'));
  // Non-word characters
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
}

TEST_F(ProgTest_398, EmptyFlagsAtStart_398) {
  std::string text = "hello";
  absl::string_view sv(text);
  uint32_t flags = Prog::EmptyFlags(sv, sv.data());
  // At start of text, kEmptyBeginText and kEmptyBeginLine should be set
  EXPECT_NE(flags & kEmptyBeginText, 0u);
  EXPECT_NE(flags & kEmptyBeginLine, 0u);
}

TEST_F(ProgTest_398, EmptyFlagsAtEnd_398) {
  std::string text = "hello";
  absl::string_view sv(text);
  uint32_t flags = Prog::EmptyFlags(sv, sv.data() + sv.size());
  // At end of text, kEmptyEndText and kEmptyEndLine should be set
  EXPECT_NE(flags & kEmptyEndText, 0u);
  EXPECT_NE(flags & kEmptyEndLine, 0u);
}

TEST_F(ProgTest_398, EmptyFlagsMiddle_398) {
  std::string text = "hello";
  absl::string_view sv(text);
  uint32_t flags = Prog::EmptyFlags(sv, sv.data() + 2);
  // In the middle, neither begin nor end text flags
  EXPECT_EQ(flags & kEmptyBeginText, 0u);
  EXPECT_EQ(flags & kEmptyEndText, 0u);
}

TEST_F(ProgTest_398, EmptyFlagsAtNewline_398) {
  std::string text = "he\nlo";
  absl::string_view sv(text);
  // Position right after the newline
  uint32_t flags = Prog::EmptyFlags(sv, sv.data() + 3);
  EXPECT_NE(flags & kEmptyBeginLine, 0u);
}

TEST_F(ProgTest_398, EmptyFlagsEmptyString_398) {
  std::string text = "";
  absl::string_view sv(text);
  uint32_t flags = Prog::EmptyFlags(sv, sv.data());
  EXPECT_NE(flags & kEmptyBeginText, 0u);
  EXPECT_NE(flags & kEmptyEndText, 0u);
}

TEST_F(ProgTest_398, CompiledProgDump_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->Dump();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgTest_398, CompiledProgDumpUnanchored_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpUnanchored();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgTest_398, CompiledProgDumpByteMap_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string dump = prog->DumpByteMap();
  EXPECT_FALSE(dump.empty());
}

TEST_F(ProgTest_398, CompiledProgSize_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
}

TEST_F(ProgTest_398, CompiledProgBytemapRange_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->bytemap_range(), 0);
}

TEST_F(ProgTest_398, CompiledProgBytemap_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  const uint8_t* bm = prog->bytemap();
  EXPECT_NE(bm, nullptr);
}

TEST_F(ProgTest_398, SearchNFASimpleMatch_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xabcy");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

TEST_F(ProgTest_398, SearchNFANoMatch_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xyz");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgTest_398, SearchNFAAnchored_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abcdef");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

TEST_F(ProgTest_398, SearchNFAAnchoredNoMatch_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("xabc");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgTest_398, SearchNFAEmptyPattern_398) {
  std::unique_ptr<Prog> prog(CompileRegexp(""));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("hello");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgTest_398, SearchBitStateSimpleMatch_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;
  absl::string_view text("xabcy");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

TEST_F(ProgTest_398, SearchBitStateNoMatch_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  if (!prog->CanBitState()) return;
  absl::string_view text("xyz");
  absl::string_view match;
  bool found = prog->SearchBitState(text, text, Prog::kUnanchored,
                                     Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgTest_398, IsOnePassSimple_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  // Simple literal pattern should be one-pass
  EXPECT_TRUE(prog->IsOnePass());
}

TEST_F(ProgTest_398, SearchOnePassSimple_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  if (!prog->IsOnePass()) return;
  absl::string_view text("abc");
  absl::string_view match;
  bool found = prog->SearchOnePass(text, text, Prog::kAnchored,
                                    Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "abc");
}

TEST_F(ProgTest_398, SearchOnePassNoMatch_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  if (!prog->IsOnePass()) return;
  absl::string_view text("xyz");
  absl::string_view match;
  bool found = prog->SearchOnePass(text, text, Prog::kAnchored,
                                    Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

TEST_F(ProgTest_398, PossibleMatchRange_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  bool ok = prog->PossibleMatchRange(&min_match, &max_match, 10);
  EXPECT_TRUE(ok);
  EXPECT_LE(min_match, "abc");
  EXPECT_GE(max_match, "abc");
}

TEST_F(ProgTest_398, PossibleMatchRangeMaxLen_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("a.*z"));
  ASSERT_NE(prog, nullptr);
  std::string min_match, max_match;
  bool ok = prog->PossibleMatchRange(&min_match, &max_match, 5);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(min_match.empty());
}

TEST_F(ProgTest_398, SearchDFASimpleMatch_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("xabcy");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_TRUE(found);
  }
}

TEST_F(ProgTest_398, SearchDFANoMatch_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  absl::string_view text("xyz");
  absl::string_view match;
  bool failed = false;
  bool found = prog->SearchDFA(text, text, Prog::kUnanchored,
                                Prog::kFirstMatch, &match, &failed, nullptr);
  if (!failed) {
    EXPECT_FALSE(found);
  }
}

TEST_F(ProgTest_398, CanBitState_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  // Small patterns should be able to use bit state
  EXPECT_TRUE(prog->CanBitState());
}

TEST_F(ProgTest_398, Flatten_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("a|b|c"));
  ASSERT_NE(prog, nullptr);
  prog->Flatten();
  // After flatten, the program should still be usable
  EXPECT_GT(prog->size(), 0);
}

TEST_F(ProgTest_398, Optimize_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  prog->Optimize();
  // After optimize, the program should still function
  EXPECT_GT(prog->size(), 0);
}

TEST_F(ProgTest_398, ConfigurePrefixAccelNoPrefixByDefault_398) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

TEST_F(ProgTest_398, ConfigurePrefixAccelShortPrefix_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abcdef.*xyz"));
  ASSERT_NE(prog, nullptr);
  prog->ConfigurePrefixAccel("abcdef", false);
  // After configuring, prefix accel may or may not be available
  // depending on implementation, but shouldn't crash
}

TEST_F(ProgTest_398, ConfigurePrefixAccelEmptyPrefix_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  prog->ConfigurePrefixAccel("", false);
  EXPECT_FALSE(prog->can_prefix_accel());
}

TEST_F(ProgTest_398, PrefixAccelNullWhenNotConfigured_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  if (!prog->can_prefix_accel()) {
    std::string data = "test data";
    const void* result = prog->PrefixAccel(data.data(), data.size());
    EXPECT_EQ(result, nullptr);
  }
}

TEST_F(ProgTest_398, Fanout_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("a|b|c"));
  ASSERT_NE(prog, nullptr);
  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);
  // Fanout should have been populated
}

TEST_F(ProgTest_398, SearchNFAWithCaptures_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("(a)(b)(c)"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("abc");
  absl::string_view match[4];
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, match, 4);
  EXPECT_TRUE(found);
  EXPECT_EQ(match[0], "abc");
  EXPECT_EQ(match[1], "a");
  EXPECT_EQ(match[2], "b");
  EXPECT_EQ(match[3], "c");
}

TEST_F(ProgTest_398, SearchNFALongestMatch_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("a+"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("aaa");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kLongestMatch, &match, 1);
  EXPECT_TRUE(found);
  EXPECT_EQ(match, "aaa");
}

TEST_F(ProgTest_398, TestingOnlySetDfaShouldBailWhenSlow_398) {
  // Just verify we can call the testing function without crashing
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

TEST_F(ProgTest_398, CompileSetBasic_398) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = Prog::CompileSet(re, RE2::UNANCHORED, 1 << 20);
  re->Decref();
  if (prog != nullptr) {
    EXPECT_GT(prog->size(), 0);
    delete prog;
  }
}

TEST_F(ProgTest_398, BuildEntireDFA_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("a"));
  ASSERT_NE(prog, nullptr);
  prog->set_dfa_mem(1 << 20);
  int states = prog->BuildEntireDFA(Prog::kFirstMatch, nullptr);
  EXPECT_GT(states, 0);
}

TEST_F(ProgTest_398, EmptyFlagsWordBoundary_398) {
  std::string text = "a b";
  absl::string_view sv(text);
  // Position between 'a' and ' ' (index 1)
  uint32_t flags = Prog::EmptyFlags(sv, sv.data() + 1);
  // After word char 'a', before non-word ' ': should have word boundary
  EXPECT_NE(flags & kEmptyWordBoundary, 0u);
}

TEST_F(ProgTest_398, EmptyFlagsNonWordBoundary_398) {
  std::string text = "ab";
  absl::string_view sv(text);
  // Position between 'a' and 'b' (both word chars)
  uint32_t flags = Prog::EmptyFlags(sv, sv.data() + 1);
  EXPECT_NE(flags & kEmptyNonWordBoundary, 0u);
}

TEST_F(ProgTest_398, InstAccess_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  EXPECT_GT(prog->size(), 0);
  // Should be able to access instructions
  Prog::Inst* inst = prog->inst(0);
  EXPECT_NE(inst, nullptr);
}

TEST_F(ProgTest_398, SearchNFAEmptyText_398) {
  std::unique_ptr<Prog> prog(CompileRegexp(""));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_TRUE(found);
}

TEST_F(ProgTest_398, SearchNFAEmptyTextNonEmptyPattern_398) {
  std::unique_ptr<Prog> prog(CompileRegexp("abc"));
  ASSERT_NE(prog, nullptr);
  absl::string_view text("");
  absl::string_view match;
  bool found = prog->SearchNFA(text, text, Prog::kAnchored,
                                Prog::kFirstMatch, &match, 1);
  EXPECT_FALSE(found);
}

}  // namespace re2
