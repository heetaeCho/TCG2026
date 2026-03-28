// File: re2_parseflags_or_test.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

using re2::Regexp;

class ParseFlagsOrTest_168 : public ::testing::Test {};

// Ensures the expression type is Regexp::ParseFlags at compile time.
static_assert(std::is_same<
                  decltype(std::declval<Regexp::ParseFlags>() |
                           std::declval<Regexp::ParseFlags>()),
                  Regexp::ParseFlags>::value,
              "operator| must return Regexp::ParseFlags");

TEST_F(ParseFlagsOrTest_168, OrWithZeroReturnsSame_168) {
  const Regexp::ParseFlags zero = static_cast<Regexp::ParseFlags>(0);
  const Regexp::ParseFlags a = static_cast<Regexp::ParseFlags>(1 << 0);

  auto r1 = a | zero;
  auto r2 = zero | a;

  EXPECT_EQ(static_cast<int>(r1), static_cast<int>(a));
  EXPECT_EQ(static_cast<int>(r2), static_cast<int>(a));
}

TEST_F(ParseFlagsOrTest_168, Commutative_168) {
  const Regexp::ParseFlags a = static_cast<Regexp::ParseFlags>(1 << 1);
  const Regexp::ParseFlags b = static_cast<Regexp::ParseFlags>(1 << 3);

  auto ab = a | b;
  auto ba = b | a;

  EXPECT_EQ(static_cast<int>(ab), static_cast<int>(ba));
}

TEST_F(ParseFlagsOrTest_168, Idempotent_168) {
  const Regexp::ParseFlags a = static_cast<Regexp::ParseFlags>(1 << 2);

  auto aa = a | a;

  EXPECT_EQ(static_cast<int>(aa), static_cast<int>(a));
}

TEST_F(ParseFlagsOrTest_168, Associative_168) {
  const Regexp::ParseFlags a = static_cast<Regexp::ParseFlags>(1 << 0);
  const Regexp::ParseFlags b = static_cast<Regexp::ParseFlags>(1 << 5);
  const Regexp::ParseFlags c = static_cast<Regexp::ParseFlags>(1 << 7);

  auto left  = (a | b) | c;
  auto right = a | (b | c);

  EXPECT_EQ(static_cast<int>(left), static_cast<int>(right));
}

TEST_F(ParseFlagsOrTest_168, CombinesDistinctBits_168) {
  const int ai = (1 << 4);
  const int bi = (1 << 6);

  const Regexp::ParseFlags a = static_cast<Regexp::ParseFlags>(ai);
  const Regexp::ParseFlags b = static_cast<Regexp::ParseFlags>(bi);

  auto ab = a | b;

  int combined = ai | bi;
  EXPECT_EQ(static_cast<int>(ab), combined);
  // Both original bits remain set.
  EXPECT_NE(static_cast<int>(ab) & ai, 0);
  EXPECT_NE(static_cast<int>(ab) & bi, 0);
}

TEST_F(ParseFlagsOrTest_168, ReapplyingExistingBitDoesNotChangeResult_168) {
  const int ai = (1 << 8);
  const int bi = (1 << 9);

  const Regexp::ParseFlags a = static_cast<Regexp::ParseFlags>(ai);
  const Regexp::ParseFlags b = static_cast<Regexp::ParseFlags>(bi);

  auto first = a | b;
  auto again = first | a;

  EXPECT_EQ(static_cast<int>(again), static_cast<int>(first));
}

TEST_F(ParseFlagsOrTest_168, ChainsMultipleFlagsSafely_168) {
  // Use several non-overlapping bits, including a large one within 32-bit int range.
  const int a = (1 << 0);
  const int b = (1 << 3);
  const int c = (1 << 10);
  const int d = (1 << 29); // stay clear of sign bit

  const Regexp::ParseFlags fa = static_cast<Regexp::ParseFlags>(a);
  const Regexp::ParseFlags fb = static_cast<Regexp::ParseFlags>(b);
  const Regexp::ParseFlags fc = static_cast<Regexp::ParseFlags>(c);
  const Regexp::ParseFlags fd = static_cast<Regexp::ParseFlags>(d);

  auto all = fa | fb | fc | fd;  // validates chaining of operator|

  EXPECT_EQ(static_cast<int>(all), (a | b | c | d));
}
