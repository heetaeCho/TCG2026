// File: factor_alternation_round3_test_508.cc
#include <gtest/gtest.h>
#include <vector>

// RE2 headers
#include "re2/regexp.h"

// We include the implementation unit to get the Splice type and FactorAlternationImpl API.
// (This is only to access the public interface used by Round3; we do not re-implement logic.)
#include "re2/parse.cc"

using namespace re2;

namespace {

// Small helpers to build inputs via the public API only.
static Regexp* Lit(Rune r, Regexp::ParseFlags f = Regexp::NoParseFlags) {
  return Regexp::NewLiteral(r, f);
}

static Regexp* CC(Rune lo, Rune hi, Regexp::ParseFlags f = Regexp::NoParseFlags) {
  CharClassBuilder b;
  b.AddRangeFlags(lo, hi, f);
  CharClass* cc = b.GetCharClass();
  return Regexp::NewCharClass(cc, f);
}

static Regexp* StarOf(Rune r, Regexp::ParseFlags f = Regexp::NoParseFlags) {
  return Regexp::Star(Regexp::NewLiteral(r, f), f);
}

}  // namespace

// ---------------------- Tests ----------------------

TEST(FactorAlternationRound3Test_508, EmptyInput_NoSplices_508) {
  FactorAlternationImpl impl;
  std::vector<Splice> splices;

  Regexp** sub = nullptr;
  impl.Round3(sub, /*nsub=*/0, Regexp::NoParseFlags, &splices);

  EXPECT_TRUE(splices.empty());
}

TEST(FactorAlternationRound3Test_508, SingleLiteral_NoSplices_508) {
  FactorAlternationImpl impl;
  std::vector<Splice> splices;

  std::vector<Regexp*> subs = { Lit('a') };
  impl.Round3(subs.data(), /*nsub=*/static_cast<int>(subs.size()),
              Regexp::NoParseFlags, &splices);

  EXPECT_TRUE(splices.empty());
}

TEST(FactorAlternationRound3Test_508, TwoLiterals_OneSplice_508) {
  FactorAlternationImpl impl;
  std::vector<Splice> splices;

  std::vector<Regexp*> subs = { Lit('a'), Lit('b') };
  impl.Round3(subs.data(), /*nsub=*/static_cast<int>(subs.size()),
              Regexp::NoParseFlags, &splices);

  ASSERT_EQ(splices.size(), 1u);
}

TEST(FactorAlternationRound3Test_508, TwoCharClasses_OneSplice_508) {
  FactorAlternationImpl impl;
  std::vector<Splice> splices;

  std::vector<Regexp*> subs = { CC('a', 'c'), CC('x', 'z') };
  impl.Round3(subs.data(), /*nsub=*/static_cast<int>(subs.size()),
              Regexp::NoParseFlags, &splices);

  ASSERT_EQ(splices.size(), 1u);
}

TEST(FactorAlternationRound3Test_508, LiteralCharClassLiteral_SingleRun_OneSplice_508) {
  FactorAlternationImpl impl;
  std::vector<Splice> splices;

  std::vector<Regexp*> subs = { Lit('a'), CC('b', 'c'), Lit('D') };
  impl.Round3(subs.data(), /*nsub=*/static_cast<int>(subs.size()),
              Regexp::NoParseFlags, &splices);

  ASSERT_EQ(splices.size(), 1u);
}

TEST(FactorAlternationRound3Test_508, BarrierBetweenTokens_NoSplice_508) {
  FactorAlternationImpl impl;
  std::vector<Splice> splices;

  // The STAR node acts as a non-(literal|charclass) barrier.
  std::vector<Regexp*> subs = { Lit('a'), StarOf('x'), CC('b', 'c') };
  impl.Round3(subs.data(), /*nsub=*/static_cast<int>(subs.size()),
              Regexp::NoParseFlags, &splices);

  // No contiguous run of (literal|charclass) with length >= 2 exists.
  EXPECT_TRUE(splices.empty());
}

TEST(FactorAlternationRound3Test_508, TwoRunsSeparatedByBarrier_TwoSplices_508) {
  FactorAlternationImpl impl;
  std::vector<Splice> splices;

  // [Lit, CC]  STAR  [Lit, CC]  -> should create two splices, one per run.
  std::vector<Regexp*> subs = { Lit('a'), CC('b', 'c'), StarOf('x'), Lit('y'), CC('y', 'z') };
  impl.Round3(subs.data(), /*nsub=*/static_cast<int>(subs.size()),
              Regexp::NoParseFlags, &splices);

  ASSERT_EQ(splices.size(), 2u);
}

TEST(FactorAlternationRound3Test_508, FoldCaseLiterals_Merges_OneSplice_508) {
  FactorAlternationImpl impl;
  std::vector<Splice> splices;

  // Even with FoldCase flags on inputs, Round3 should still detect the run and splice.
  std::vector<Regexp*> subs = { Lit('a', Regexp::FoldCase), Lit('A', Regexp::FoldCase) };
  impl.Round3(subs.data(), /*nsub=*/static_cast<int>(subs.size()),
              Regexp::FoldCase, &splices);

  ASSERT_EQ(splices.size(), 1u);
}

