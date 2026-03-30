// File: parse_do_alternation_test_511.cc

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "re2/regexp.h"
#include "absl/strings/string_view.h"

// We rely strictly on the public interface exposed by parse.cc.
// Including parse.cc ensures the public nested class `Regexp::ParseState`
// and its methods are visible to the test without touching private state.
#include "re2/parse.cc"

using ::testing::UnorderedElementsAre;

namespace re2 {

// Small helpers that only use public APIs of Regexp.
namespace {

void CollectLiterals(Regexp* re, std::vector<int>* out) {
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpLiteral) {
    out->push_back(static_cast<int>(re->rune()));
  }
  // Recurse through any children using only public accessors.
  const int n = re->nsub();
  Regexp** subs = re->sub();
  for (int i = 0; i < n; ++i) {
    CollectLiterals(subs[i], out);
  }
}

bool ContainsOp(Regexp* re, RegexpOp target) {
  if (re->op() == target) return true;
  const int n = re->nsub();
  Regexp** subs = re->sub();
  for (int i = 0; i < n; ++i) {
    if (ContainsOp(subs[i], target)) return true;
  }
  return false;
}

bool HasConcatOfTwoLiterals(Regexp* re, int a, int b) {
  if (re->op() == kRegexpConcat && re->nsub() == 2) {
    Regexp** subs = re->sub();
    if (subs[0]->op() == kRegexpLiteral &&
        subs[1]->op() == kRegexpLiteral &&
        static_cast<int>(subs[0]->rune()) == a &&
        static_cast<int>(subs[1]->rune()) == b) {
      return true;
    }
  }
  const int n = re->nsub();
  Regexp** subs = re->sub();
  for (int i = 0; i < n; ++i) {
    if (HasConcatOfTwoLiterals(subs[i], a, b)) return true;
  }
  return false;
}

}  // namespace

// Fixture for shared aliases/utilities.
class ParseStateDoAlternationTest_511 : public ::testing::Test {
 protected:
  using PS = Regexp::ParseState;
  static Regexp::ParseFlags NoFlags() {
    return static_cast<Regexp::ParseFlags>(0);
  }
};

// Normal operation: a|b
TEST_F(ParseStateDoAlternationTest_511, BuildsAlternationForTwoBranches_511) {
  Regexp::ParseFlags flags = NoFlags();
  PS ps(flags, /*whole_regexp=*/"a|b", /*status=*/nullptr);

  ASSERT_TRUE(ps.PushLiteral('a'));
  ps.DoAlternation();              // acts like seeing '|'
  ASSERT_TRUE(ps.PushLiteral('b'));

  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->op(), kRegexpAlternate);

  std::vector<int> lits;
  CollectLiterals(re, &lits);
  EXPECT_THAT(lits, UnorderedElementsAre('a', 'b'));

  EXPECT_FALSE(ContainsOp(re, kRegexpEmptyMatch));

  re->Decref();
}

// Boundary condition: trailing empty alternative: "a|"
TEST_F(ParseStateDoAlternationTest_511, HandlesTrailingEmptyAlternative_511) {
  Regexp::ParseFlags flags = NoFlags();
  PS ps(flags, /*whole_regexp=*/"a|", /*status=*/nullptr);

  ASSERT_TRUE(ps.PushLiteral('a'));
  ps.DoAlternation();  // no right-hand piece pushed afterwards

  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->op(), kRegexpAlternate);

  // One branch should be the literal 'a', the other an empty match.
  std::vector<int> lits;
  CollectLiterals(re, &lits);
  // Still must contain 'a' somewhere.
  ASSERT_FALSE(lits.empty());
  bool has_a = false;
  for (int v : lits) if (v == 'a') has_a = true;
  EXPECT_TRUE(has_a);
  EXPECT_TRUE(ContainsOp(re, kRegexpEmptyMatch));

  re->Decref();
}

// Normal operation with three branches: a|b|c
TEST_F(ParseStateDoAlternationTest_511, BuildsAlternationForThreeBranches_511) {
  Regexp::ParseFlags flags = NoFlags();
  PS ps(flags, /*whole_regexp=*/"a|b|c", /*status=*/nullptr);

  ASSERT_TRUE(ps.PushLiteral('a'));
  ps.DoAlternation();

  ASSERT_TRUE(ps.PushLiteral('b'));
  ps.DoAlternation();

  ASSERT_TRUE(ps.PushLiteral('c'));

  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->op(), kRegexpAlternate);

  std::vector<int> lits;
  CollectLiterals(re, &lits);
  EXPECT_THAT(lits, UnorderedElementsAre('a', 'b', 'c'));

  re->Decref();
}

// Interaction with concatenation on a branch: "ab|c"
TEST_F(ParseStateDoAlternationTest_511, PreservesConcatenationWithinBranch_511) {
  Regexp::ParseFlags flags = NoFlags();
  PS ps(flags, /*whole_regexp=*/"ab|c", /*status=*/nullptr);

  ASSERT_TRUE(ps.PushLiteral('a'));
  ASSERT_TRUE(ps.PushLiteral('b'));  // left side becomes a concat of 'a' and 'b'
  ps.DoAlternation();
  ASSERT_TRUE(ps.PushLiteral('c'));

  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->op(), kRegexpAlternate);
  EXPECT_TRUE(HasConcatOfTwoLiterals(re, 'a', 'b'));

  // Also ensure 'c' literal is present somewhere in the tree.
  std::vector<int> lits;
  CollectLiterals(re, &lits);
  bool has_c = false;
  for (int v : lits) if (v == 'c') has_c = true;
  EXPECT_TRUE(has_c);

  re->Decref();
}

}  // namespace re2
