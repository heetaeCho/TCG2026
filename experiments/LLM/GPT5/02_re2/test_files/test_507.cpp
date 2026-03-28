// File: factor_alternation_round2_test_507.cc

#include <gtest/gtest.h>
#include <vector>
#include <string>

#include "re2/regexp.h"

// Minimal public declarations needed by the tests (no reimplementation of logic).
namespace re2 {

// Forward declaration that matches the production type shape used in parse.cc.
// This is only to make the tests compile/link and to let us inspect observable fields.
struct Splice {
  Regexp* prefix;
  Regexp** sub;
  int nsub;
  Splice(Regexp* p, Regexp** s, int n) : prefix(p), sub(s), nsub(n) {}
};

// Public class & method declarations (implemented in the actual codebase).
class FactorAlternationImpl {
public:
  void Round2(Regexp** sub,
              int nsub,
              Regexp::ParseFlags flags,
              std::vector<Splice>* splices);
};

}  // namespace re2

namespace {

using re2::FactorAlternationImpl;
using re2::Regexp;
using re2::RegexpOp;

// Helper: parse a single branch pattern (e.g., ".x", "^y", "A{3}z").
static Regexp* ParseBranch(const char* pat) {
  return Regexp::Parse(pat, static_cast<Regexp::ParseFlags>(0), /*status=*/nullptr);
}

// Fixture with small helpers.
class FactorAlternationRound2Test_507 : public ::testing::Test {
protected:
  // Run Round2 on a vector of branch regexes, collecting splices.
  void RunRound2(std::vector<Regexp*>& branches, std::vector<re2::Splice>& splices) {
    FactorAlternationImpl impl;
    impl.Round2(branches.data(),
                static_cast<int>(branches.size()),
                static_cast<Regexp::ParseFlags>(0),
                &splices);
  }
};

TEST_F(FactorAlternationRound2Test_507, FactorsAnyCharPrefix_GroupOfThree_507) {
  // Three branches all starting with '.' should be factored.
  std::vector<Regexp*> branches = {
      ParseBranch(".x"),
      ParseBranch(".y"),
      ParseBranch(".z")
  };
  ASSERT_NE(branches[0], nullptr);
  ASSERT_NE(branches[1], nullptr);
  ASSERT_NE(branches[2], nullptr);

  std::vector<re2::Splice> splices;
  RunRound2(branches, splices);

  // One splice over the whole range.
  ASSERT_EQ(splices.size(), 1u);
  EXPECT_EQ(splices[0].nsub, 3);
  EXPECT_EQ(splices[0].sub, branches.data());
  ASSERT_NE(splices[0].prefix, nullptr);
  EXPECT_EQ(splices[0].prefix->op(), kRegexpAnyChar);

  // The leading '.' should be removed from each branch, leaving literals x/y/z.
  for (size_t i = 0; i < branches.size(); ++i) {
    ASSERT_NE(branches[i], nullptr);
    EXPECT_EQ(branches[i]->op(), kRegexpLiteral) << "Index " << i << " not reduced to literal";
  }
}

TEST_F(FactorAlternationRound2Test_507, FactorsBeginLinePrefix_TwoBranches_507) {
  // Two branches both starting with '^' should be factored.
  std::vector<Regexp*> branches = {
      ParseBranch("^a"),
      ParseBranch("^b")
  };
  ASSERT_NE(branches[0], nullptr);
  ASSERT_NE(branches[1], nullptr);

  std::vector<re2::Splice> splices;
  RunRound2(branches, splices);

  ASSERT_EQ(splices.size(), 1u);
  EXPECT_EQ(splices[0].nsub, 2);
  EXPECT_EQ(splices[0].sub, branches.data());
  ASSERT_NE(splices[0].prefix, nullptr);
  EXPECT_EQ(splices[0].prefix->op(), kRegexpBeginLine);

  // After removing '^', suffixes are single literals.
  ASSERT_NE(branches[0], nullptr);
  ASSERT_NE(branches[1], nullptr);
  EXPECT_EQ(branches[0]->op(), kRegexpLiteral);
  EXPECT_EQ(branches[1]->op(), kRegexpLiteral);
}

TEST_F(FactorAlternationRound2Test_507, FactorsFixedRepeatOfLiteral_MinEqMax_507) {
  // Round2 also allows factoring a fixed repeat (min==max) of a simple sub (literal here).
  // Example: "A{3}x" and "A{3}y" share the same leading fixed repeat.
  std::vector<Regexp*> branches = {
      ParseBranch("A{3}x"),
      ParseBranch("A{3}y")
  };
  ASSERT_NE(branches[0], nullptr);
  ASSERT_NE(branches[1], nullptr);

  std::vector<re2::Splice> splices;
  RunRound2(branches, splices);

  ASSERT_EQ(splices.size(), 1u);
  EXPECT_EQ(splices[0].nsub, 2);
  ASSERT_NE(splices[0].prefix, nullptr);
  EXPECT_EQ(splices[0].prefix->op(), kRegexpRepeat);
  // Suffixes should be single literals after removing the repeated prefix.
  EXPECT_EQ(branches[0]->op(), kRegexpLiteral);
  EXPECT_EQ(branches[1]->op(), kRegexpLiteral);
}

TEST_F(FactorAlternationRound2Test_507, DoesNotFactor_PlainLiteralPrefix_507) {
  // Literal-leading branches (e.g., "ax" vs "ay") should NOT be factored by Round2.
  std::vector<Regexp*> branches = {
      ParseBranch("ax"),
      ParseBranch("ay")
  };
  ASSERT_NE(branches[0], nullptr);
  ASSERT_NE(branches[1], nullptr);

  // Capture original string forms to compare post-call (black-box check).
  const std::string before0 = branches[0]->ToString();
  const std::string before1 = branches[1]->ToString();

  std::vector<re2::Splice> splices;
  RunRound2(branches, splices);

  EXPECT_TRUE(splices.empty());
  // Branches remain unchanged.
  EXPECT_EQ(branches[0]->ToString(), before0);
  EXPECT_EQ(branches[1]->ToString(), before1);
}

TEST_F(FactorAlternationRound2Test_507, DoesNotFactor_RepeatWithRange_MinNeMax_507) {
  // Repeat with range (min != max) should NOT be factored.
  std::vector<Regexp*> branches = {
      ParseBranch("A{2,3}x"),
      ParseBranch("A{2,3}y")
  };
  ASSERT_NE(branches[0], nullptr);
  ASSERT_NE(branches[1], nullptr);

  const std::string before0 = branches[0]->ToString();
  const std::string before1 = branches[1]->ToString();

  std::vector<re2::Splice> splices;
  RunRound2(branches, splices);

  EXPECT_TRUE(splices.empty());
  EXPECT_EQ(branches[0]->ToString(), before0);
  EXPECT_EQ(branches[1]->ToString(), before1);
}

TEST_F(FactorAlternationRound2Test_507, MixedRuns_FactorsOnlyContiguousGroup_507) {
  // Only the first two share the allowed leading op ('.').
  // The third starts with a literal (not allowed by Round2), the fourth again with '.' but as a run of size 1.
  std::vector<Regexp*> branches = {
      ParseBranch(".x"),
      ParseBranch(".y"),
      ParseBranch("az"),
      ParseBranch(".w"),
  };
  for (auto* b : branches) ASSERT_NE(b, nullptr);

  const std::string before2 = branches[2]->ToString();
  const std::string before3 = branches[3]->ToString();

  std::vector<re2::Splice> splices;
  RunRound2(branches, splices);

  // Exactly one splice for the first two.
  ASSERT_EQ(splices.size(), 1u);
  EXPECT_EQ(splices[0].nsub, 2);
  EXPECT_EQ(splices[0].sub, branches.data());
  ASSERT_NE(splices[0].prefix, nullptr);
  EXPECT_EQ(splices[0].prefix->op(), kRegexpAnyChar);

  // First two reduced to single literals (x,y).
  EXPECT_EQ(branches[0]->op(), kRegexpLiteral);
  EXPECT_EQ(branches[1]->op(), kRegexpLiteral);

  // Others unchanged.
  EXPECT_EQ(branches[2]->ToString(), before2);
  EXPECT_EQ(branches[3]->ToString(), before3);
}

TEST_F(FactorAlternationRound2Test_507, HandlesEmptyInput_NoCrashes_507) {
  // Boundary: nsub = 0 should yield no splices and no access.
  std::vector<Regexp*> branches;  // empty
  std::vector<re2::Splice> splices;

  // Should not crash; should produce no splices.
  RunRound2(branches, splices);
  EXPECT_TRUE(splices.empty());
}

}  // namespace
