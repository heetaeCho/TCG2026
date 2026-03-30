// File: regexp_star_test_339.cc
#include "re2/regexp.h"
#include "gtest/gtest.h"

using namespace re2;

class RegexpStarTest_339 : public ::testing::Test {};

// [Normal] Star wraps a valid sub-expression and produces a node whose op() is kRegexpStar.
TEST(RegexpStarTest_339, ReturnsStarOpForValidSub_339) {
  Regexp* sub = Regexp::NewLiteral('x', /*flags=*/0);
  ASSERT_NE(sub, nullptr) << "NewLiteral should return a valid Regexp for a simple rune.";

  Regexp* star = Regexp::Star(sub, /*flags=*/0);
  ASSERT_NE(star, nullptr) << "Star should return a valid Regexp when given a valid sub-expression.";

  EXPECT_EQ(star->op(), kRegexpStar);
}

// [Flags propagation] Star should reflect the provided parse flags in the resulting node's observable flags.
TEST(RegexpStarTest_339, PropagatesFlags_339) {
  const int flags = 1;  // Use a non-zero integral value; ParseFlags is integral/enum-convertible.
  Regexp* sub = Regexp::NewLiteral('a', /*flags=*/0);
  ASSERT_NE(sub, nullptr);

  Regexp* star = Regexp::Star(sub, /*flags=*/flags);
  ASSERT_NE(star, nullptr);

  EXPECT_EQ(star->op(), kRegexpStar);
  EXPECT_EQ(star->parse_flags(), flags);
}

// [Compositional behavior] Even when applied to a composite input, the top-level op() remains kRegexpStar.
TEST(RegexpStarTest_339, TopLevelOpRemainsStarOnNestedInput_339) {
  Regexp* inner = Regexp::NewLiteral('b', /*flags=*/0);
  ASSERT_NE(inner, nullptr);

  Regexp* inner_star = Regexp::Star(inner, /*flags=*/0);
  ASSERT_NE(inner_star, nullptr);

  Regexp* outer_star = Regexp::Star(inner_star, /*flags=*/0);
  ASSERT_NE(outer_star, nullptr);

  EXPECT_EQ(outer_star->op(), kRegexpStar);
}

// [Boundary] Null sub-expression is handled in a defined, observable way (either nullptr or a star node).
// We assert the function returns either nullptr or a valid Regexp with kRegexpStar op without crashing.
TEST(RegexpStarTest_339, HandlesNullSubGracefully_339) {
  Regexp* star = Regexp::Star(/*sub=*/nullptr, /*flags=*/0);

  // The observable contract we can safely assert without relying on internals:
  // - If star is nullptr, the function declined to create a node.
  // - If star is non-null, it must represent a star operation.
  if (star == nullptr) {
    SUCCEED() << "Star(nullptr, ...) returned nullptr (graceful no-op).";
  } else {
    EXPECT_EQ(star->op(), kRegexpStar);
  }
}
