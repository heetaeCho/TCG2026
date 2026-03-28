// File: regexp_literalstring_test_347.cc

#include "re2/regexp.h"
#include "gtest/gtest.h"

using re2::Regexp;
using re2::kRegexpEmptyMatch;
using re2::kRegexpLiteral;
using re2::kRegexpLiteralString;

namespace {

// RAII helper to avoid leaks via Regexp's reference counting API.
struct ReDeleter {
  void operator()(Regexp* r) const {
    if (r) r->Decref();
  }
};
using RePtr = std::unique_ptr<Regexp, ReDeleter>;

}  // namespace

// Normal & boundary: nrunes == 0 → EmptyMatch
TEST(RegexpLiteralStringTest_347, NrunesZero_ReturnsEmptyMatch_347) {
  // Passing nullptr is fine when nrunes == 0: shouldn't be dereferenced.
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(0);
  RePtr re(Regexp::LiteralString(/*runes=*/nullptr, /*nrunes=*/0, flags));

  ASSERT_NE(re.get(), nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  EXPECT_EQ(re->parse_flags(), flags);
}

// Boundary: nrunes < 0 → EmptyMatch
TEST(RegexpLiteralStringTest_347, NrunesNegative_ReturnsEmptyMatch_347) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(0);
  // Any non-null pointer should be ignored when nrunes <= 0
  Rune dummy = 123;
  RePtr re(Regexp::LiteralString(&dummy, -5, flags));

  ASSERT_NE(re.get(), nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  EXPECT_EQ(re->parse_flags(), flags);
}

// Normal: single rune → Literal with the same rune value
TEST(RegexpLiteralStringTest_347, SingleRune_ReturnsLiteralWithSameRune_347) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(0);
  // Use a non-ASCII code point to ensure Unicode is handled opaquely.
  const Rune r = 0x1F600;  // 😀
  RePtr re(Regexp::LiteralString(const_cast<Rune*>(&r), 1, flags));

  ASSERT_NE(re.get(), nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->parse_flags(), flags);
  EXPECT_EQ(re->rune(), r);
}

// Normal: multiple runes → LiteralString with the same runes in order
TEST(RegexpLiteralStringTest_347, MultipleRunes_ReturnsLiteralStringWithAllRunes_347) {
  // Use a mix of ASCII, BMP, and non-BMP runes.
  Rune input[] = { static_cast<Rune>('a'), 0x03A9 /*Ω*/, 0x1F600 /*😀*/ };
  const int n = static_cast<int>(sizeof(input) / sizeof(input[0]));
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(0);
  RePtr re(Regexp::LiteralString(input, n, flags));

  ASSERT_NE(re.get(), nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->parse_flags(), flags);

  // Validate nrunes() and exact rune sequence via the public accessors.
  ASSERT_EQ(re->nrunes(), n);
  const Rune* out = re->runes();
  ASSERT_NE(out, nullptr);
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(out[i], input[i]) << "Rune mismatch at index " << i;
  }
}

// Flags propagation sanity check with a non-zero flag value
TEST(RegexpLiteralStringTest_347, FlagsArePropagated_ForSingleAndMulti_347) {
  // Use a generic non-zero bit pattern without assuming specific flag meanings.
  Regexp::ParseFlags flags_nonzero = static_cast<Regexp::ParseFlags>(1);

  // Single-rune case
  Rune one = 'Z';
  RePtr re_one(Regexp::LiteralString(&one, 1, flags_nonzero));
  ASSERT_NE(re_one.get(), nullptr);
  EXPECT_EQ(re_one->op(), kRegexpLiteral);
  EXPECT_EQ(re_one->parse_flags(), flags_nonzero);

  // Multi-rune case
  Rune many[] = { 'x', 'y' };
  RePtr re_many(Regexp::LiteralString(many, 2, flags_nonzero));
  ASSERT_NE(re_many.get(), nullptr);
  EXPECT_EQ(re_many->op(), kRegexpLiteralString);
  EXPECT_EQ(re_many->parse_flags(), flags_nonzero);
  ASSERT_EQ(re_many->nrunes(), 2);
  const Rune* out = re_many->runes();
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out[0], many[0]);
  EXPECT_EQ(out[1], many[1]);
}
