#include "re2/regexp.h"
#include <gtest/gtest.h>

namespace re2 {

class ParseFlagsOperatorTest_168 : public ::testing::Test {
 protected:
};

// Test that OR-ing two distinct flags produces combined value
TEST_F(ParseFlagsOperatorTest_168, OrTwoDistinctFlags_168) {
  Regexp::ParseFlags a = Regexp::FoldCase;
  Regexp::ParseFlags b = Regexp::Literal;
  Regexp::ParseFlags result = a | b;
  EXPECT_EQ(static_cast<int>(result),
            static_cast<int>(a) | static_cast<int>(b));
}

// Test that OR-ing a flag with itself returns the same flag
TEST_F(ParseFlagsOperatorTest_168, OrSameFlag_168) {
  Regexp::ParseFlags a = Regexp::FoldCase;
  Regexp::ParseFlags result = a | a;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(a));
}

// Test OR with zero-equivalent (NoParseFlags)
TEST_F(ParseFlagsOperatorTest_168, OrWithNoParseFlags_168) {
  Regexp::ParseFlags a = Regexp::FoldCase;
  Regexp::ParseFlags zero = static_cast<Regexp::ParseFlags>(0);
  Regexp::ParseFlags result = a | zero;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(a));
}

// Test OR of zero with zero
TEST_F(ParseFlagsOperatorTest_168, OrZeroWithZero_168) {
  Regexp::ParseFlags zero = static_cast<Regexp::ParseFlags>(0);
  Regexp::ParseFlags result = zero | zero;
  EXPECT_EQ(static_cast<int>(result), 0);
}

// Test OR of multiple flags chained
TEST_F(ParseFlagsOperatorTest_168, ChainedOr_168) {
  Regexp::ParseFlags a = Regexp::FoldCase;
  Regexp::ParseFlags b = Regexp::Literal;
  Regexp::ParseFlags c = Regexp::OneLine;
  Regexp::ParseFlags result = a | b | c;
  EXPECT_EQ(static_cast<int>(result),
            static_cast<int>(a) | static_cast<int>(b) | static_cast<int>(c));
}

// Test commutativity: a | b == b | a
TEST_F(ParseFlagsOperatorTest_168, Commutativity_168) {
  Regexp::ParseFlags a = Regexp::FoldCase;
  Regexp::ParseFlags b = Regexp::Literal;
  EXPECT_EQ(static_cast<int>(a | b), static_cast<int>(b | a));
}

// Test associativity: (a | b) | c == a | (b | c)
TEST_F(ParseFlagsOperatorTest_168, Associativity_168) {
  Regexp::ParseFlags a = Regexp::FoldCase;
  Regexp::ParseFlags b = Regexp::Literal;
  Regexp::ParseFlags c = Regexp::OneLine;
  EXPECT_EQ(static_cast<int>((a | b) | c), static_cast<int>(a | (b | c)));
}

// Test with PerlX and other flags
TEST_F(ParseFlagsOperatorTest_168, OrPerlXAndDotNL_168) {
  Regexp::ParseFlags a = Regexp::PerlX;
  Regexp::ParseFlags b = Regexp::DotNL;
  Regexp::ParseFlags result = a | b;
  EXPECT_EQ(static_cast<int>(result),
            static_cast<int>(a) | static_cast<int>(b));
}

// Test that the result type is correct (ParseFlags)
TEST_F(ParseFlagsOperatorTest_168, ResultTypeIsParseFlags_168) {
  Regexp::ParseFlags a = Regexp::FoldCase;
  Regexp::ParseFlags b = Regexp::Literal;
  auto result = a | b;
  static_assert(std::is_same<decltype(result), Regexp::ParseFlags>::value,
                "Result of operator| should be Regexp::ParseFlags");
}

// Test idempotency: a | a | a == a
TEST_F(ParseFlagsOperatorTest_168, Idempotency_168) {
  Regexp::ParseFlags a = Regexp::WasDollar;
  Regexp::ParseFlags result = a | a | a;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(a));
}

// Test combining many flags
TEST_F(ParseFlagsOperatorTest_168, CombineManyFlags_168) {
  Regexp::ParseFlags result = Regexp::FoldCase | Regexp::Literal |
                              Regexp::OneLine | Regexp::DotNL |
                              Regexp::NonGreedy;
  int expected = static_cast<int>(Regexp::FoldCase) |
                 static_cast<int>(Regexp::Literal) |
                 static_cast<int>(Regexp::OneLine) |
                 static_cast<int>(Regexp::DotNL) |
                 static_cast<int>(Regexp::NonGreedy);
  EXPECT_EQ(static_cast<int>(result), expected);
}

}  // namespace re2
