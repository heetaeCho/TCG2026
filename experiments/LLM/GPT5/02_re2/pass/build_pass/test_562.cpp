// File: prefilter_debugstring_test_562.cc

#include <gtest/gtest.h>
#include <vector>
#include <string>

// Assuming the headers below are available in your include path as given:
#include "re2/prefilter.h"

using re2::Prefilter;

class PrefilterDebugStringTest_562 : public ::testing::Test {
protected:
  // Helper to build an AND node with provided children (raw pointers as per API).
  static Prefilter* MakeAnd(const std::vector<Prefilter*>& children) {
    auto* node = new Prefilter(Prefilter::AND);
    auto* subs = new std::vector<Prefilter*>(children);
    node->set_subs(subs);
    return node;
  }

  // Helper to build an OR node with provided children (raw pointers as per API).
  static Prefilter* MakeOr(const std::vector<Prefilter*>& children) {
    auto* node = new Prefilter(Prefilter::OR);
    auto* subs = new std::vector<Prefilter*>(children);
    node->set_subs(subs);
    return node;
  }
};

// ALL → empty string.
TEST_F(PrefilterDebugStringTest_562, AllReturnsEmptyString_562) {
  Prefilter all(Prefilter::ALL);
  EXPECT_EQ(all.DebugString(), "");
}

// NONE → "*no-matches*".
TEST_F(PrefilterDebugStringTest_562, NoneReturnsNoMatchesLiteral_562) {
  Prefilter none(Prefilter::NONE);
  EXPECT_EQ(none.DebugString(), "*no-matches*");
}

// AND formatting: children joined by a single space; "<nil>" for nullptr;
// empty child string contributes an empty segment (so adjacent spaces can appear).
TEST_F(PrefilterDebugStringTest_562, AndJoinsChildrenWithSpacesAndNilForNull_562) {
  auto* n0 = new Prefilter(Prefilter::NONE);  // DebugString() = "*no-matches*"
  auto* a0 = new Prefilter(Prefilter::ALL);   // DebugString() = "" (empty)
  Prefilter* nil = nullptr;                   // DebugString() → "<nil>" in parent

  std::unique_ptr<Prefilter> and_node(MakeAnd({n0, a0, nil}));

  // Expected:
  // i=0: "*no-matches*"
  // i=1: " " + ""            → adds a trailing space
  // i=2: " " + "<nil>"       → results in double-space before "<nil>"
  EXPECT_EQ(and_node->DebugString(), "*no-matches*  <nil>");
}

// OR formatting: children joined by '|' and wrapped in parentheses;
// "<nil>" for nullptr; empty child produces an empty field between pipes.
TEST_F(PrefilterDebugStringTest_562, OrPipesChildrenAndShowsNilForNull_562) {
  auto* n0 = new Prefilter(Prefilter::NONE);  // "*no-matches*"
  auto* a0 = new Prefilter(Prefilter::ALL);   // ""
  Prefilter* nil = nullptr;                   // "<nil>"

  std::unique_ptr<Prefilter> or_node(MakeOr({n0, a0, nil}));

  // Expected: "(*no-matches*||<nil>)" (empty child between the two pipes)
  EXPECT_EQ(or_node->DebugString(), "(*no-matches*||<nil>)");
}

// AND with empty subs: loop runs zero times; result remains "".
TEST_F(PrefilterDebugStringTest_562, AndWithEmptySubsReturnsEmpty_562) {
  auto* empty_and = new Prefilter(Prefilter::AND);
  empty_and->set_subs(new std::vector<Prefilter*>{});
  std::unique_ptr<Prefilter> guard(empty_and);

  EXPECT_EQ(empty_and->DebugString(), "");
}

// OR with empty subs: starts with "(" and ends with ")" with nothing inside.
TEST_F(PrefilterDebugStringTest_562, OrWithEmptySubsRendersEmptyParens_562) {
  auto* empty_or = new Prefilter(Prefilter::OR);
  empty_or->set_subs(new std::vector<Prefilter*>{});
  std::unique_ptr<Prefilter> guard(empty_or);

  EXPECT_EQ(empty_or->DebugString(), "()");
}

// Nested structures: ensure recursion uses child DebugString() verbatim.
TEST_F(PrefilterDebugStringTest_562, NestedOrOfAndKeepsChildFormatting_562) {
  // Inner AND: [NONE, ALL] → "*no-matches* " (note trailing space from empty ALL)
  auto* inner_and = PrefilterDebugStringTest_562::MakeAnd({
      new Prefilter(Prefilter::NONE),
      new Prefilter(Prefilter::ALL),
  });

  // OR: [inner_and, nullptr] → "(*no-matches* |<nil>)"
  // Explanation:
  //   inner_and DebugString() ends with a space; OR then adds '|' after that.
  auto* outer_or = PrefilterDebugStringTest_562::MakeOr({
      inner_and,
      nullptr
  });
  std::unique_ptr<Prefilter> guard(outer_or);

  EXPECT_EQ(outer_or->DebugString(), "(*no-matches* |<nil>)");
}

// (Optional/edge) Invalid op: DebugString() logs DFATAL but returns "op<value>".
// This can abort in some builds; keep it disabled to avoid flakiness.
// Enable locally if your environment treats DFATAL as non-fatal.
TEST_F(PrefilterDebugStringTest_562, DISABLED_UnknownOpReturnsTaggedString_562) {
  Prefilter invalid(static_cast<Prefilter::Op>(999));
  EXPECT_EQ(invalid.DebugString(), "op999");
}
