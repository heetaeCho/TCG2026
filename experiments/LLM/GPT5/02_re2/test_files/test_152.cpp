// File: regexp_parse_flags_test_152.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"

namespace {

using re2::Regexp;

// A tiny helper to ensure we always clean up if a Regexp* was created.
// We only Decref() the pointer we own (returned by factory functions).
struct RePtr {
  Regexp* p = nullptr;
  ~RePtr() { if (p) p->Decref(); }
};

TEST(RegexpParseFlags_152, ReturnsExactFlagsFromNewLiteral_Zero_152) {
  // Arrange: create a Regexp via a public factory that accepts ParseFlags.
  const auto flags0 = static_cast<Regexp::ParseFlags>(0);
  RePtr r;
  r.p = Regexp::NewLiteral('A', flags0);  // Treat implementation as black box.
  ASSERT_NE(nullptr, r.p) << "Factory should return a valid Regexp*";

  // Act / Assert: parse_flags() should expose the flags passed at construction.
  EXPECT_EQ(flags0, r.p->parse_flags());
}

TEST(RegexpParseFlags_152, ReturnsExactFlagsFromNewLiteral_NonZero_152) {
  // Arrange: pick a distinct, non-zero flag bit-pattern without assuming enum values.
  const auto flagsX = static_cast<Regexp::ParseFlags>(0x1234);
  RePtr r;
  r.p = Regexp::NewLiteral('Z', flagsX);
  ASSERT_NE(nullptr, r.p);

  // Act / Assert
  EXPECT_EQ(flagsX, r.p->parse_flags());
}

TEST(RegexpParseFlags_152, DistinguishesDifferentFlagValues_152) {
  // Arrange: build two regexps with different flag values.
  const auto flagsA = static_cast<Regexp::ParseFlags>(0x0001);
  const auto flagsB = static_cast<Regexp::ParseFlags>(0x0002);

  RePtr ra;
  RePtr rb;
  ra.p = Regexp::NewLiteral('a', flagsA);
  rb.p = Regexp::NewLiteral('b', flagsB);
  ASSERT_NE(nullptr, ra.p);
  ASSERT_NE(nullptr, rb.p);

  // Act / Assert: observable outputs differ.
  EXPECT_NE(ra.p->parse_flags(), rb.p->parse_flags());
  EXPECT_EQ(flagsA, ra.p->parse_flags());
  EXPECT_EQ(flagsB, rb.p->parse_flags());
}

TEST(RegexpParseFlags_152, FlagsPropagateThroughPlusFactory_152) {
  // Arrange: create a sub-regexp and wrap it with Plus(…, flags).
  const auto innerFlags = static_cast<Regexp::ParseFlags>(0x0000);
  const auto outerFlags = static_cast<Regexp::ParseFlags>(0x00F0);

  RePtr sub;
  sub.p = Regexp::NewLiteral('X', innerFlags);
  ASSERT_NE(nullptr, sub.p);

  RePtr plus;
  plus.p = Regexp::Plus(sub.p, outerFlags);
  ASSERT_NE(nullptr, plus.p) << "Plus should return a valid Regexp*";

  // Act / Assert: The new node's parse_flags() reflect the flags passed to Plus.
  EXPECT_EQ(outerFlags, plus.p->parse_flags());
  // Sanity: the outer node's flags can differ from the inner node's flags.
  EXPECT_NE(sub.p->parse_flags(), plus.p->parse_flags());
}

}  // namespace
