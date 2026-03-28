// word-text-attributes-equal-test-2502.cc
//
// NOTE:
// - The function under test is `static` in poppler-page.cc, so it is not link-visible.
// - This test file compiles the provided function body (verbatim) together with test doubles
//   that expose only the methods the function calls.
// - Tests treat the function as a black box: they validate only observable return values.

#include <gtest/gtest.h>

namespace {

class FakeTextFontInfo {
public:
  explicit FakeTextFontInfo(bool matches_result = true)
      : matches_result_(matches_result) {}

  bool matches(const FakeTextFontInfo *other) const
  {
    // Observable behavior we control for the comparison.
    // (We do not attempt to model any real Poppler logic.)
    (void)other;
    return matches_result_;
  }

  void set_matches_result(bool v) { matches_result_ = v; }

private:
  bool matches_result_;
};

class TextWord {
public:
  TextWord(FakeTextFontInfo *font_info, double font_size, bool underlined,
           double r, double g, double b)
      : font_info_(font_info),
        font_size_(font_size),
        underlined_(underlined),
        r_(r),
        g_(g),
        b_(b)
  {
  }

  const FakeTextFontInfo *getFontInfo(int /*idx*/) const { return font_info_; }
  double getFontSize() const { return font_size_; }
  bool isUnderlined() const { return underlined_; }

  void getColor(double *r, double *g, double *b) const
  {
    if (r) *r = r_;
    if (g) *g = g_;
    if (b) *b = b_;
  }

  void set_font_size(double v) { font_size_ = v; }
  void set_underlined(bool v) { underlined_ = v; }
  void set_color(double r, double g, double b)
  {
    r_ = r;
    g_ = g;
    b_ = b;
  }

private:
  FakeTextFontInfo *font_info_;
  double font_size_;
  bool underlined_;
  double r_;
  double g_;
  double b_;
};

// Provided implementation (verbatim), compiled into this TU for testing.
static gboolean word_text_attributes_equal(const TextWord *a, gint ai,
                                          const TextWord *b, gint bi)
{
  double ar, ag, ab, br, bg, bb;
  if (!a->getFontInfo(ai)->matches(b->getFontInfo(bi))) {
    return FALSE;
  }
  if (a->getFontSize() != b->getFontSize()) {
    return FALSE;
  }
  if (a->isUnderlined() != b->isUnderlined()) {
    return FALSE;
  }
  a->getColor(&ar, &ag, &ab);
  b->getColor(&br, &bg, &bb);
  return (ar == br && ag == bg && ab == bb);
}

// Minimal typedefs to avoid pulling GLib headers for this isolated unit test.
using gboolean = int;
using gint = int;
constexpr gboolean TRUE = 1;
constexpr gboolean FALSE = 0;

} // namespace

// ----------------------- Tests (TEST_ID: 2502) -----------------------

TEST(WordTextAttributesEqualTest_2502, ReturnsTrueWhenAllAttributesMatch_2502)
{
  FakeTextFontInfo fa(/*matches_result=*/true);
  FakeTextFontInfo fb(/*matches_result=*/true);

  TextWord a(&fa, /*font_size=*/12.0, /*underlined=*/false, 0.1, 0.2, 0.3);
  TextWord b(&fb, /*font_size=*/12.0, /*underlined=*/false, 0.1, 0.2, 0.3);

  EXPECT_EQ(word_text_attributes_equal(&a, 0, &b, 0), TRUE);
}

TEST(WordTextAttributesEqualTest_2502, ReturnsFalseWhenFontInfoDoesNotMatch_2502)
{
  FakeTextFontInfo fa(/*matches_result=*/false); // forces mismatch
  FakeTextFontInfo fb(/*matches_result=*/true);

  TextWord a(&fa, /*font_size=*/12.0, /*underlined=*/false, 0.1, 0.2, 0.3);
  TextWord b(&fb, /*font_size=*/12.0, /*underlined=*/false, 0.1, 0.2, 0.3);

  EXPECT_EQ(word_text_attributes_equal(&a, 0, &b, 0), FALSE);
}

TEST(WordTextAttributesEqualTest_2502, ReturnsFalseWhenFontSizeDiffers_2502)
{
  FakeTextFontInfo fa(/*matches_result=*/true);
  FakeTextFontInfo fb(/*matches_result=*/true);

  TextWord a(&fa, /*font_size=*/12.0, /*underlined=*/false, 0.1, 0.2, 0.3);
  TextWord b(&fb, /*font_size=*/13.0, /*underlined=*/false, 0.1, 0.2, 0.3);

  EXPECT_EQ(word_text_attributes_equal(&a, 0, &b, 0), FALSE);
}

TEST(WordTextAttributesEqualTest_2502, ReturnsFalseWhenUnderlineFlagDiffers_2502)
{
  FakeTextFontInfo fa(/*matches_result=*/true);
  FakeTextFontInfo fb(/*matches_result=*/true);

  TextWord a(&fa, /*font_size=*/12.0, /*underlined=*/true, 0.1, 0.2, 0.3);
  TextWord b(&fb, /*font_size=*/12.0, /*underlined=*/false, 0.1, 0.2, 0.3);

  EXPECT_EQ(word_text_attributes_equal(&a, 0, &b, 0), FALSE);
}

TEST(WordTextAttributesEqualTest_2502, ReturnsFalseWhenRedComponentDiffers_2502)
{
  FakeTextFontInfo fa(/*matches_result=*/true);
  FakeTextFontInfo fb(/*matches_result=*/true);

  TextWord a(&fa, /*font_size=*/12.0, /*underlined=*/false, 0.11, 0.2, 0.3);
  TextWord b(&fb, /*font_size=*/12.0, /*underlined=*/false, 0.10, 0.2, 0.3);

  EXPECT_EQ(word_text_attributes_equal(&a, 0, &b, 0), FALSE);
}

TEST(WordTextAttributesEqualTest_2502, ReturnsFalseWhenGreenComponentDiffers_2502)
{
  FakeTextFontInfo fa(/*matches_result=*/true);
  FakeTextFontInfo fb(/*matches_result=*/true);

  TextWord a(&fa, /*font_size=*/12.0, /*underlined=*/false, 0.1, 0.21, 0.3);
  TextWord b(&fb, /*font_size=*/12.0, /*underlined=*/false, 0.1, 0.20, 0.3);

  EXPECT_EQ(word_text_attributes_equal(&a, 0, &b, 0), FALSE);
}

TEST(WordTextAttributesEqualTest_2502, ReturnsFalseWhenBlueComponentDiffers_2502)
{
  FakeTextFontInfo fa(/*matches_result=*/true);
  FakeTextFontInfo fb(/*matches_result=*/true);

  TextWord a(&fa, /*font_size=*/12.0, /*underlined=*/false, 0.1, 0.2, 0.31);
  TextWord b(&fb, /*font_size=*/12.0, /*underlined=*/false, 0.1, 0.2, 0.30);

  EXPECT_EQ(word_text_attributes_equal(&a, 0, &b, 0), FALSE);
}

TEST(WordTextAttributesEqualTest_2502, BoundaryValuesExactlyEqualStillReturnTrue_2502)
{
  FakeTextFontInfo fa(/*matches_result=*/true);
  FakeTextFontInfo fb(/*matches_result=*/true);

  // Boundary-style inputs: zeroes and ones.
  TextWord a(&fa, /*font_size=*/0.0, /*underlined=*/false, 0.0, 0.0, 0.0);
  TextWord b(&fb, /*font_size=*/0.0, /*underlined=*/false, 0.0, 0.0, 0.0);
  EXPECT_EQ(word_text_attributes_equal(&a, 0, &b, 0), TRUE);

  a.set_font_size(1.0);
  b.set_font_size(1.0);
  a.set_underlined(true);
  b.set_underlined(true);
  a.set_color(1.0, 1.0, 1.0);
  b.set_color(1.0, 1.0, 1.0);
  EXPECT_EQ(word_text_attributes_equal(&a, 0, &b, 0), TRUE);
}

TEST(WordTextAttributesEqualTest_2502, IndicesAreAcceptedAndDoNotAffectWhenStubsIgnoreIdx_2502)
{
  FakeTextFontInfo fa(/*matches_result=*/true);
  FakeTextFontInfo fb(/*matches_result=*/true);

  TextWord a(&fa, /*font_size=*/10.0, /*underlined=*/false, 0.4, 0.5, 0.6);
  TextWord b(&fb, /*font_size=*/10.0, /*underlined=*/false, 0.4, 0.5, 0.6);

  // Boundary-ish indices (negative / large) as long as the callee tolerates them.
  // In real code, index validity would be governed by TextWord; here we verify
  // the helper itself doesn't do any explicit index checks.
  EXPECT_EQ(word_text_attributes_equal(&a, -1, &b, 9999), TRUE);
}