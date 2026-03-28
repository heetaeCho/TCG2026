// File: test_HorizontalTextLayouter_2791.cc
#include <gtest/gtest.h>

#include <optional>
#include <string>

// Include the implementation file to get the full definition of HorizontalTextLayouter.
// This is necessary because HorizontalTextLayouter is implemented in Annot.cc and may not
// be available via a public header in this test project layout.
#include "poppler/Annot.cc"

#include "goo/GooString.h"
#include "poppler/GfxFont.h"

// A minimal font stub that is sufficient for exercising HorizontalTextLayouter via
// Annot::layoutText without relying on any private/internal state of HorizontalTextLayouter.
// NOTE: This stub is a collaborator; we are not re-implementing HorizontalTextLayouter.
class TestGfxFont_2791 final : public GfxFont
{
public:
  TestGfxFont_2791()
      : GfxFont("FTest", Ref{0, 0}, std::optional<std::string>(std::string("TestFont")),
                static_cast<GfxFontType>(0), Ref{0, 0})
  {
  }

  // Consume exactly one byte per character, and map it to a single Unicode value.
  // Return a deterministic advance (dx=1) so layoutText can compute widths.
  int getNextChar(const char *s, int len, CharCode *code, const Unicode **u, int *uLen,
                  double *dx, double *dy, double *ox, double *oy) override
  {
    if (!s || len <= 0) {
      return 0;
    }

    const unsigned char c = static_cast<unsigned char>(s[0]);

    if (code) {
      *code = static_cast<CharCode>(c);
    }

    static Unicode uni[1];
    uni[0] = static_cast<Unicode>(c);
    if (u) {
      *u = uni;
    }
    if (uLen) {
      *uLen = 1;
    }

    if (dx) {
      *dx = 1.0;
    }
    if (dy) {
      *dy = 0.0;
    }
    if (ox) {
      *ox = 0.0;
    }
    if (oy) {
      *oy = 0.0;
    }

    return 1;
  }
};

class HorizontalTextLayouterTest_2791 : public ::testing::Test
{
protected:
  TestGfxFont_2791 font_;
};

// Normal operation: default-constructed object should be usable.
TEST_F(HorizontalTextLayouterTest_2791, DefaultConstructor_AllowsQueries_2791)
{
  HorizontalTextLayouter layouter;
  // We avoid reading layouter.consumedText here because defaulted ctor may not initialize it.
  EXPECT_DOUBLE_EQ(layouter.totalWidth(), 0.0);
  EXPECT_EQ(layouter.totalCharCount(), 0);
}

// Boundary: empty text.
TEST_F(HorizontalTextLayouterTest_2791, EmptyText_ConsumesNothingAndHasZeroTotals_2791)
{
  GooString text("");
  HorizontalTextLayouter layouter(&text, /*form=*/nullptr, &font_, std::nullopt, /*noReencode=*/true);

  EXPECT_EQ(layouter.consumedText, 0);
  EXPECT_DOUBLE_EQ(layouter.totalWidth(), 0.0);
  EXPECT_EQ(layouter.totalCharCount(), 0);
}

// Normal operation: simple ASCII text with ample width.
TEST_F(HorizontalTextLayouterTest_2791, AsciiText_WithAmpleWidth_ProducesNonNegativeTotals_2791)
{
  GooString text("ABC");
  HorizontalTextLayouter layouter(&text, /*form=*/nullptr, &font_, 1000.0, /*noReencode=*/true);

  // Observable invariants (do not assume exact layout details).
  EXPECT_GE(layouter.consumedText, 0);
  EXPECT_LE(static_cast<size_t>(layouter.consumedText), text.toStr().size());

  EXPECT_GE(layouter.totalWidth(), 0.0);
  EXPECT_GE(layouter.totalCharCount(), 0);

  // For non-empty input, it should typically consume at least one byte and count at least one char.
  // If the underlying implementation chooses otherwise, these can be relaxed, but they reflect
  // expected observable behavior for a layouter.
  EXPECT_GE(layouter.consumedText, 1);
  EXPECT_GE(layouter.totalCharCount(), 1);
}

// Boundary: zero available width should not crash and should keep invariants.
TEST_F(HorizontalTextLayouterTest_2791, ZeroAvailableWidth_DoesNotCrash_2791)
{
  GooString text("ABCDE");
  HorizontalTextLayouter layouter(&text, /*form=*/nullptr, &font_, 0.0, /*noReencode=*/true);

  EXPECT_GE(layouter.consumedText, 0);
  EXPECT_LE(static_cast<size_t>(layouter.consumedText), text.toStr().size());
  EXPECT_GE(layouter.totalWidth(), 0.0);
  EXPECT_GE(layouter.totalCharCount(), 0);
}

// Boundary: Unicode BOM prefix input should not crash and should keep invariants.
TEST_F(HorizontalTextLayouterTest_2791, UnicodeBOMInput_DoesNotCrashAndRespectsBounds_2791)
{
  // UTF-16BE BOM: 0xFE 0xFF, followed by two bytes that could represent 'A' (0x00 0x41).
  std::string s;
  s.push_back(static_cast<char>(0xFE));
  s.push_back(static_cast<char>(0xFF));
  s.push_back(static_cast<char>(0x00));
  s.push_back(static_cast<char>(0x41));
  GooString text(s);

  HorizontalTextLayouter layouter(&text, /*form=*/nullptr, &font_, 1000.0, /*noReencode=*/true);

  EXPECT_GE(layouter.consumedText, 0);
  EXPECT_LE(static_cast<size_t>(layouter.consumedText), text.toStr().size());
  EXPECT_GE(layouter.totalWidth(), 0.0);
  EXPECT_GE(layouter.totalCharCount(), 0);
}

// Error/exceptional (observable): passing noReencode=false should also be constructible.
TEST_F(HorizontalTextLayouterTest_2791, NoReencodeFalse_ConstructsAndIsQueryable_2791)
{
  GooString text("Hello");
  HorizontalTextLayouter layouter(&text, /*form=*/nullptr, &font_, 1000.0, /*noReencode=*/false);

  EXPECT_GE(layouter.consumedText, 0);
  EXPECT_LE(static_cast<size_t>(layouter.consumedText), text.toStr().size());
  EXPECT_GE(layouter.totalWidth(), 0.0);
  EXPECT_GE(layouter.totalCharCount(), 0);
}