#include <gtest/gtest.h>
#include "re2/regexp.h"

namespace re2 {

TEST(RegexpParseFlagsBitwiseNot_171, NotNoParseFlags_171) {
  // ~0 should give AllParseFlags (all bits set within the mask)
  Regexp::ParseFlags result = ~Regexp::NoParseFlags;
  EXPECT_EQ(result, Regexp::AllParseFlags);
}

TEST(RegexpParseFlagsBitwiseNot_171, NotAllParseFlags_171) {
  // ~AllParseFlags should give NoParseFlags (no bits set)
  Regexp::ParseFlags result = ~Regexp::AllParseFlags;
  EXPECT_EQ(result, Regexp::NoParseFlags);
}

TEST(RegexpParseFlagsBitwiseNot_171, NotFoldCase_171) {
  Regexp::ParseFlags result = ~Regexp::FoldCase;
  // ~1 & 16383 = 16382
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(Regexp::AllParseFlags) & ~static_cast<int>(Regexp::FoldCase));
  // FoldCase bit should not be set
  EXPECT_EQ(static_cast<int>(result) & static_cast<int>(Regexp::FoldCase), 0);
  // All other bits within AllParseFlags should be set
  EXPECT_EQ(static_cast<int>(result) | static_cast<int>(Regexp::FoldCase), static_cast<int>(Regexp::AllParseFlags));
}

TEST(RegexpParseFlagsBitwiseNot_171, NotLiteral_171) {
  Regexp::ParseFlags result = ~Regexp::Literal;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(Regexp::AllParseFlags) & ~static_cast<int>(Regexp::Literal));
}

TEST(RegexpParseFlagsBitwiseNot_171, NotClassNL_171) {
  Regexp::ParseFlags result = ~Regexp::ClassNL;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(Regexp::AllParseFlags) & ~static_cast<int>(Regexp::ClassNL));
}

TEST(RegexpParseFlagsBitwiseNot_171, NotDotNL_171) {
  Regexp::ParseFlags result = ~Regexp::DotNL;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(Regexp::AllParseFlags) & ~static_cast<int>(Regexp::DotNL));
}

TEST(RegexpParseFlagsBitwiseNot_171, NotOneLine_171) {
  Regexp::ParseFlags result = ~Regexp::OneLine;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(Regexp::AllParseFlags) & ~static_cast<int>(Regexp::OneLine));
}

TEST(RegexpParseFlagsBitwiseNot_171, NotLatin1_171) {
  Regexp::ParseFlags result = ~Regexp::Latin1;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(Regexp::AllParseFlags) & ~static_cast<int>(Regexp::Latin1));
}

TEST(RegexpParseFlagsBitwiseNot_171, NotNonGreedy_171) {
  Regexp::ParseFlags result = ~Regexp::NonGreedy;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(Regexp::AllParseFlags) & ~static_cast<int>(Regexp::NonGreedy));
}

TEST(RegexpParseFlagsBitwiseNot_171, NotPerlClasses_171) {
  Regexp::ParseFlags result = ~Regexp::PerlClasses;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(Regexp::AllParseFlags) & ~static_cast<int>(Regexp::PerlClasses));
}

TEST(RegexpParseFlagsBitwiseNot_171, NotPerlB_171) {
  Regexp::ParseFlags result = ~Regexp::PerlB;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(Regexp::AllParseFlags) & ~static_cast<int>(Regexp::PerlB));
}

TEST(RegexpParseFlagsBitwiseNot_171, NotPerlX_171) {
  Regexp::ParseFlags result = ~Regexp::PerlX;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(Regexp::AllParseFlags) & ~static_cast<int>(Regexp::PerlX));
}

TEST(RegexpParseFlagsBitwiseNot_171, NotUnicodeGroups_171) {
  Regexp::ParseFlags result = ~Regexp::UnicodeGroups;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(Regexp::AllParseFlags) & ~static_cast<int>(Regexp::UnicodeGroups));
}

TEST(RegexpParseFlagsBitwiseNot_171, NotNeverNL_171) {
  Regexp::ParseFlags result = ~Regexp::NeverNL;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(Regexp::AllParseFlags) & ~static_cast<int>(Regexp::NeverNL));
}

TEST(RegexpParseFlagsBitwiseNot_171, NotNeverCapture_171) {
  Regexp::ParseFlags result = ~Regexp::NeverCapture;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(Regexp::AllParseFlags) & ~static_cast<int>(Regexp::NeverCapture));
}

TEST(RegexpParseFlagsBitwiseNot_171, NotWasDollar_171) {
  Regexp::ParseFlags result = ~Regexp::WasDollar;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(Regexp::AllParseFlags) & ~static_cast<int>(Regexp::WasDollar));
}

TEST(RegexpParseFlagsBitwiseNot_171, NotLikePerl_171) {
  // LikePerl = 1940 = FoldCase | ClassNL | DotNL | OneLine | PerlClasses | PerlB | PerlX | UnicodeGroups... 
  // Actually LikePerl = 1940 per the definition
  Regexp::ParseFlags result = ~Regexp::LikePerl;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(Regexp::AllParseFlags) & ~static_cast<int>(Regexp::LikePerl));
}

TEST(RegexpParseFlagsBitwiseNot_171, NotMatchNL_171) {
  // MatchNL = 12 = ClassNL | DotNL
  Regexp::ParseFlags result = ~Regexp::MatchNL;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(Regexp::AllParseFlags) & ~static_cast<int>(Regexp::MatchNL));
}

TEST(RegexpParseFlagsBitwiseNot_171, DoubleNegation_171) {
  // ~~x should equal x (within the AllParseFlags mask)
  Regexp::ParseFlags original = Regexp::FoldCase;
  Regexp::ParseFlags result = ~~original;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(original));
}

TEST(RegexpParseFlagsBitwiseNot_171, DoubleNegationLikePerl_171) {
  Regexp::ParseFlags original = Regexp::LikePerl;
  Regexp::ParseFlags result = ~~original;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(original));
}

TEST(RegexpParseFlagsBitwiseNot_171, DoubleNegationAllFlags_171) {
  Regexp::ParseFlags original = Regexp::AllParseFlags;
  Regexp::ParseFlags result = ~~original;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(original));
}

TEST(RegexpParseFlagsBitwiseNot_171, DoubleNegationNoFlags_171) {
  Regexp::ParseFlags original = Regexp::NoParseFlags;
  Regexp::ParseFlags result = ~~original;
  EXPECT_EQ(static_cast<int>(result), static_cast<int>(original));
}

TEST(RegexpParseFlagsBitwiseNot_171, ResultMaskedWithinAllParseFlags_171) {
  // For any single flag, the result should always be within AllParseFlags range
  Regexp::ParseFlags flags[] = {
    Regexp::NoParseFlags, Regexp::FoldCase, Regexp::Literal,
    Regexp::ClassNL, Regexp::DotNL, Regexp::MatchNL,
    Regexp::OneLine, Regexp::Latin1, Regexp::NonGreedy,
    Regexp::PerlClasses, Regexp::PerlB, Regexp::PerlX,
    Regexp::UnicodeGroups, Regexp::NeverNL, Regexp::NeverCapture,
    Regexp::LikePerl, Regexp::WasDollar, Regexp::AllParseFlags
  };
  for (auto f : flags) {
    Regexp::ParseFlags result = ~f;
    int resultInt = static_cast<int>(result);
    // Result should have no bits set outside AllParseFlags
    EXPECT_EQ(resultInt & ~static_cast<int>(Regexp::AllParseFlags), 0)
      << "For flag value " << static_cast<int>(f);
  }
}

TEST(RegexpParseFlagsBitwiseNot_171, CombinedFlags_171) {
  // Test with a combination of flags
  Regexp::ParseFlags combined = static_cast<Regexp::ParseFlags>(
    static_cast<int>(Regexp::FoldCase) | static_cast<int>(Regexp::Literal) | static_cast<int>(Regexp::DotNL));
  Regexp::ParseFlags result = ~combined;
  int expected = ~(static_cast<int>(Regexp::FoldCase) | static_cast<int>(Regexp::Literal) | static_cast<int>(Regexp::DotNL))
                 & static_cast<int>(Regexp::AllParseFlags);
  EXPECT_EQ(static_cast<int>(result), expected);
}

TEST(RegexpParseFlagsBitwiseNot_171, NotResultAndOriginalEqualsZero_171) {
  // For any flag f, (f & ~f) should be 0
  Regexp::ParseFlags f = Regexp::LikePerl;
  Regexp::ParseFlags notf = ~f;
  EXPECT_EQ(static_cast<int>(f) & static_cast<int>(notf), 0);
}

TEST(RegexpParseFlagsBitwiseNot_171, NotResultOrOriginalEqualsAllFlags_171) {
  // For any flag f that is within AllParseFlags, (f | ~f) should be AllParseFlags
  Regexp::ParseFlags f = Regexp::LikePerl;
  Regexp::ParseFlags notf = ~f;
  EXPECT_EQ(static_cast<int>(f) | static_cast<int>(notf), static_cast<int>(Regexp::AllParseFlags));
}

}  // namespace re2
