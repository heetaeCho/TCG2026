// poppler_text_attributes_new_from_word_test_2477.cc
//
// Unit tests for poppler_text_attributes_new_from_word().
//
// Notes:
// - The function under test is `static` in poppler-page.cc, so in many real codebases
//   you would include the .cc file to access it. For a self-contained unit test that
//   does not depend on Poppler's full build graph, this test provides minimal stubs
//   for the required types and collaborators and compiles the function body exactly
//   as provided in the prompt.
//
// - We treat the implementation as a black box via observable behavior: returned
//   attributes reflect inputs (font name, size, underline, color conversion).
// - We also verify an external interaction: the helper get_font_name_from_word()
//   is invoked with the given index.

#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

// ---- Minimal GLib-ish typedefs used by the snippet ----
using gint = int;
using gdouble = double;
using gboolean = int;
using gchar = char;

// ---- Minimal color struct compatible with fields used by the snippet ----
struct PopplerColor16 {
  int red = 0;
  int green = 0;
  int blue = 0;
};

// ---- Minimal PopplerTextAttributes compatible with fields used by the snippet ----
struct PopplerTextAttributes {
  gchar* font_name = nullptr;
  gdouble font_size = 0.0;
  gboolean is_underlined = 0;
  PopplerColor16 color;
};

static PopplerTextAttributes* poppler_text_attributes_new() {
  // Minimal allocator: zero-init all fields.
  auto* attrs = static_cast<PopplerTextAttributes*>(std::calloc(1, sizeof(PopplerTextAttributes)));
  return attrs;
}

static void poppler_text_attributes_free(PopplerTextAttributes* attrs) {
  if (!attrs) return;
  std::free(attrs->font_name);
  std::free(attrs);
}

// ---- Minimal stub of TextWord with only the needed surface ----
class TextWord {
 public:
  TextWord(std::vector<std::string> font_names,
           double font_size,
           bool underlined,
           double r,
           double g,
           double b)
      : font_names_(std::move(font_names)),
        font_size_(font_size),
        underlined_(underlined),
        r_(r),
        g_(g),
        b_(b) {}

  double getFontSize() const { return font_size_; }
  bool isUnderlined() const { return underlined_; }

  void getColor(double* r, double* g, double* b) const {
    if (r) *r = r_;
    if (g) *g = g_;
    if (b) *b = b_;
  }

  const std::string& fontNameAt(int idx) const {
    static const std::string kEmpty;
    if (idx < 0 || idx >= static_cast<int>(font_names_.size())) return kEmpty;
    return font_names_[idx];
  }

 private:
  std::vector<std::string> font_names_;
  double font_size_;
  bool underlined_;
  double r_;
  double g_;
  double b_;
};

// ---- External collaborator in the snippet: get_font_name_from_word(word, i) ----
// We implement it as a stub and also record calls to verify interaction.
static const TextWord* g_last_fontname_word = nullptr;
static gint g_last_fontname_index = -999;
static int g_fontname_call_count = 0;

static gchar* get_font_name_from_word(const TextWord* word, gint i) {
  g_last_fontname_word = word;
  g_last_fontname_index = i;
  ++g_fontname_call_count;

  // Return a heap-allocated C string as expected by the attributes struct.
  const std::string& s = word ? word->fontNameAt(i) : std::string();
  char* out = static_cast<char*>(std::malloc(s.size() + 1));
  if (!out) return nullptr;
  std::memcpy(out, s.c_str(), s.size() + 1);
  return out;
}

// ---- Function under test (copied verbatim from the prompt) ----
static PopplerTextAttributes* poppler_text_attributes_new_from_word(const TextWord* word, gint i) {
  PopplerTextAttributes* attrs = poppler_text_attributes_new();
  gdouble r, g, b;
  attrs->font_name = get_font_name_from_word(word, i);
  attrs->font_size = word->getFontSize();
  attrs->is_underlined = word->isUnderlined();
  word->getColor(&r, &g, &b);
  attrs->color.red = (int)(r * 65535. + 0.5);
  attrs->color.green = (int)(g * 65535. + 0.5);
  attrs->color.blue = (int)(b * 65535. + 0.5);
  return attrs;
}

// ---- Test fixture ----
class PopplerTextAttributesFromWordTest_2477 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_last_fontname_word = nullptr;
    g_last_fontname_index = -999;
    g_fontname_call_count = 0;
  }
};

// Normal operation: values propagate from TextWord into PopplerTextAttributes.
TEST_F(PopplerTextAttributesFromWordTest_2477, PopulatesFontSizeUnderlineAndFontName_2477) {
  TextWord word(/*font_names=*/{"FontA", "FontB"},
                /*font_size=*/12.25,
                /*underlined=*/true,
                /*r=*/0.1,
                /*g=*/0.2,
                /*b=*/0.3);

  PopplerTextAttributes* attrs = poppler_text_attributes_new_from_word(&word, /*i=*/1);
  ASSERT_NE(attrs, nullptr);

  // Verify external interaction: helper called with the same word pointer and index.
  EXPECT_EQ(g_fontname_call_count, 1);
  EXPECT_EQ(g_last_fontname_word, &word);
  EXPECT_EQ(g_last_fontname_index, 1);

  ASSERT_NE(attrs->font_name, nullptr);
  EXPECT_STREQ(attrs->font_name, "FontB");
  EXPECT_DOUBLE_EQ(attrs->font_size, 12.25);
  EXPECT_TRUE(attrs->is_underlined);

  poppler_text_attributes_free(attrs);
}

// Boundary: index 0 and multiple calls should not cross-contaminate recorded values.
TEST_F(PopplerTextAttributesFromWordTest_2477, UsesProvidedIndexForFontNameEachCall_2477) {
  TextWord word(/*font_names=*/{"First", "Second", "Third"},
                /*font_size=*/9.0,
                /*underlined=*/false,
                /*r=*/0.0,
                /*g=*/0.0,
                /*b=*/0.0);

  PopplerTextAttributes* a0 = poppler_text_attributes_new_from_word(&word, 0);
  ASSERT_NE(a0, nullptr);
  EXPECT_EQ(g_fontname_call_count, 1);
  EXPECT_EQ(g_last_fontname_index, 0);
  ASSERT_NE(a0->font_name, nullptr);
  EXPECT_STREQ(a0->font_name, "First");

  PopplerTextAttributes* a2 = poppler_text_attributes_new_from_word(&word, 2);
  ASSERT_NE(a2, nullptr);
  EXPECT_EQ(g_fontname_call_count, 2);
  EXPECT_EQ(g_last_fontname_index, 2);
  ASSERT_NE(a2->font_name, nullptr);
  EXPECT_STREQ(a2->font_name, "Third");

  poppler_text_attributes_free(a0);
  poppler_text_attributes_free(a2);
}

// Boundary: color conversion at endpoints 0.0 and 1.0.
TEST_F(PopplerTextAttributesFromWordTest_2477, ConvertsColorEndpointsTo16BitRange_2477) {
  TextWord word(/*font_names=*/{"Any"},
                /*font_size=*/10.0,
                /*underlined=*/false,
                /*r=*/0.0,
                /*g=*/1.0,
                /*b=*/0.0);

  PopplerTextAttributes* attrs = poppler_text_attributes_new_from_word(&word, 0);
  ASSERT_NE(attrs, nullptr);

  EXPECT_EQ(attrs->color.red, 0);
  EXPECT_EQ(attrs->color.green, 65535);
  EXPECT_EQ(attrs->color.blue, 0);

  poppler_text_attributes_free(attrs);
}

// Boundary: rounding behavior around half steps ( +0.5 rounding ).
TEST_F(PopplerTextAttributesFromWordTest_2477, RoundsColorWithPlusHalfRule_2477) {
  // Choose values that produce fractional *65535 results near .5 boundaries.
  // For red: 0.5 -> 32767.5 -> +0.5 => 32768.0 -> int => 32768.
  // For green: 0.0 -> 0.
  // For blue: 1.0 -> 65535.
  TextWord word(/*font_names=*/{"Any"},
                /*font_size=*/10.0,
                /*underlined=*/false,
                /*r=*/0.5,
                /*g=*/0.0,
                /*b=*/1.0);

  PopplerTextAttributes* attrs = poppler_text_attributes_new_from_word(&word, 0);
  ASSERT_NE(attrs, nullptr);

  EXPECT_EQ(attrs->color.red, 32768);
  EXPECT_EQ(attrs->color.green, 0);
  EXPECT_EQ(attrs->color.blue, 65535);

  poppler_text_attributes_free(attrs);
}

// Boundary/error-ish: out-of-range font index should still call helper and return attrs;
// our stub returns empty string for out-of-range index.
TEST_F(PopplerTextAttributesFromWordTest_2477, OutOfRangeFontIndexStillReturnsAttributes_2477) {
  TextWord word(/*font_names=*/{"Only"},
                /*font_size=*/8.0,
                /*underlined=*/true,
                /*r=*/0.25,
                /*g=*/0.5,
                /*b=*/0.75);

  PopplerTextAttributes* attrs = poppler_text_attributes_new_from_word(&word, /*i=*/999);
  ASSERT_NE(attrs, nullptr);

  EXPECT_EQ(g_fontname_call_count, 1);
  EXPECT_EQ(g_last_fontname_word, &word);
  EXPECT_EQ(g_last_fontname_index, 999);

  ASSERT_NE(attrs->font_name, nullptr);
  EXPECT_STREQ(attrs->font_name, "");  // per stub behavior for out-of-range.
  EXPECT_DOUBLE_EQ(attrs->font_size, 8.0);
  EXPECT_TRUE(attrs->is_underlined);

  // Still should convert colors deterministically.
  EXPECT_EQ(attrs->color.red, static_cast<int>(0.25 * 65535. + 0.5));
  EXPECT_EQ(attrs->color.green, static_cast<int>(0.5 * 65535. + 0.5));
  EXPECT_EQ(attrs->color.blue, static_cast<int>(0.75 * 65535. + 0.5));

  poppler_text_attributes_free(attrs);
}