// File: ./TestProjects/re2/re2/tests/regexp_plus_test_338.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"

namespace {

using re2::Regexp;

// Helper to get a flags value without assuming internal details.
static inline Regexp::ParseFlags F(int v = 0) {
  return static_cast<Regexp::ParseFlags>(v);
}

// Normal operation: Plus builds a regexp node with op()==kRegexpPlus
// and it is a distinct object from the input sub.
TEST(RegexpPlusTest_338, BuildsPlusNodeWithExpectedOp_338) {
  Regexp* sub = Regexp::NewLiteral('a', F());
  ASSERT_NE(sub, nullptr) << "Sub-expression must be constructible via public API";

  // Call the instance method as defined in the provided .cc
  Regexp* maker = Regexp::NewLiteral('b', F());
  ASSERT_NE(maker, nullptr);

  Regexp* plus = maker->Plus(sub, F());
  ASSERT_NE(plus, nullptr) << "Plus should return a valid Regexp*";

  EXPECT_EQ(plus->op(), re2::kRegexpPlus);
  EXPECT_NE(plus, sub) << "Plus should return a different node than the sub";
  EXPECT_NE(plus, maker) << "Plus should not return the 'this' node";
}

// Structure check via public accessors only:
// Plus should have exactly one sub-expression, and that sub should be the one provided.
TEST(RegexpPlusTest_338, HasSingleSubAndKeepsGivenSub_338) {
  Regexp* sub = Regexp::NewLiteral('x', F());
  ASSERT_NE(sub, nullptr);

  // Use a separate object to invoke Plus to avoid any ambiguity about 'this'.
  Regexp* invoker = Regexp::NewLiteral('y', F());
  ASSERT_NE(invoker, nullptr);

  Regexp* plus = invoker->Plus(sub, F());
  ASSERT_NE(plus, nullptr);

  // Validate using only public API
  EXPECT_EQ(plus->op(), re2::kRegexpPlus);
  EXPECT_EQ(plus->nsub(), 1);

  Regexp** subs = plus->sub();
  ASSERT_NE(subs, nullptr);
  EXPECT_EQ(subs[0], sub) << "The sole child reported by sub() should be the input 'sub'";
}

// Flags behavior (observable through the accessor):
// Whatever flags are passed to Plus should be reflected by parse_flags() of the result.
// We don't assume how flags are used internally—only that the accessor reports them.
TEST(RegexpPlusTest_338, ParseFlagsReflectedByResult_338) {
  // Choose a non-zero, arbitrary value to avoid accidentally matching default behavior.
  const int kArbitrary = 0x1234;
  Regexp* sub = Regexp::NewLiteral('z', F(kArbitrary));
  ASSERT_NE(sub, nullptr);

  Regexp* result = sub->Plus(sub, F(kArbitrary));
  ASSERT_NE(result, nullptr);

  EXPECT_EQ(result->parse_flags(), F(kArbitrary))
      << "Result's parse_flags() should reflect the flags passed to Plus";
}

// Sanity with different flags for sub vs. result creation:
// Only check what the API exposes (the result node's own parse_flags()).
TEST(RegexpPlusTest_338, ResultFlagsIndependentFromSubFlags_338) {
  Regexp* sub = Regexp::NewLiteral('q', F(0x1));
  ASSERT_NE(sub, nullptr);

  Regexp* result = sub->Plus(sub, F(0x2));
  ASSERT_NE(result, nullptr);

  EXPECT_EQ(result->parse_flags(), F(0x2))
      << "Result should expose the flags provided to the Plus call";
  EXPECT_EQ(sub->parse_flags(), F(0x1))
      << "Sub should continue to expose its own original flags";
}

}  // namespace
