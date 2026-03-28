// get_font_name_from_word_test_2476.cc
#include <gtest/gtest.h>

#include <glib.h>

#include <cstddef>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// -----------------------------------------------------------------------------
// Test seam: compile the target static function into this TU and make it visible.
// We also replace the dependent types with lightweight fakes so we can control
// observable behavior strictly via the public interface used by the function.
// -----------------------------------------------------------------------------

class FakeGooString {
public:
  FakeGooString() = default;
  explicit FakeGooString(std::string s) : s_(std::move(s)) {}

  bool empty() const { return s_.empty(); }
  size_t size() const { return s_.size(); }
  char getChar(size_t i) const { return s_.at(i); }
  const char *c_str() const { return s_.c_str(); }

private:
  std::string s_;
};

class FakeTextWord {
public:
  FakeTextWord() = default;

  void SetFontNameForIndex(int idx, const FakeGooString *name) {
    if (idx < 0) {
      return;
    }
    if (static_cast<size_t>(idx) >= font_names_.size()) {
      font_names_.resize(static_cast<size_t>(idx) + 1, nullptr);
    }
    font_names_[static_cast<size_t>(idx)] = name;
  }

  const FakeGooString *getFontName(int idx) const {
    if (idx < 0) {
      return nullptr;
    }
    const size_t uidx = static_cast<size_t>(idx);
    if (uidx >= font_names_.size()) {
      return nullptr;
    }
    return font_names_[uidx];
  }

private:
  std::vector<const FakeGooString *> font_names_;
};

// Replace types used by the implementation with our fakes.
#define TextWord FakeTextWord
#define GooString FakeGooString

// Make the file-scope static function visible in this TU.
#define static

// Include the implementation-under-test.
#include "./TestProjects/poppler/glib/poppler-page.cc"

#undef static
#undef GooString
#undef TextWord

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

class GetFontNameFromWordTest_2476 : public ::testing::Test {
protected:
  static std::string TakeAndFree(gchar *s) {
    if (!s) {
      return std::string();
    }
    std::string out(s);
    g_free(s);
    return out;
  }
};

TEST_F(GetFontNameFromWordTest_2476, NullFontNameReturnsDefault_2476) {
  FakeTextWord word;
  // No font name set => getFontName() returns nullptr.
  gchar *out = get_font_name_from_word(&word, 0);
  EXPECT_NE(out, nullptr);
  EXPECT_EQ(TakeAndFree(out), "Default");
}

TEST_F(GetFontNameFromWordTest_2476, EmptyFontNameReturnsDefault_2476) {
  FakeGooString empty_name("");
  FakeTextWord word;
  word.SetFontNameForIndex(0, &empty_name);

  gchar *out = get_font_name_from_word(&word, 0);
  EXPECT_NE(out, nullptr);
  EXPECT_EQ(TakeAndFree(out), "Default");
}

TEST_F(GetFontNameFromWordTest_2476, NonSubsetNameReturnedAsIs_2476) {
  FakeGooString name("Helvetica");
  FakeTextWord word;
  word.SetFontNameForIndex(0, &name);

  gchar *out = get_font_name_from_word(&word, 0);
  EXPECT_NE(out, nullptr);
  EXPECT_EQ(TakeAndFree(out), "Helvetica");
}

TEST_F(GetFontNameFromWordTest_2476, SubsetPrefixIsStrippedWhenPatternMatches_2476) {
  // Typical subset font name pattern: "ABCDE+FontName"
  FakeGooString name("ABCDE+Helvetica");
  FakeTextWord word;
  word.SetFontNameForIndex(0, &name);

  gchar *out = get_font_name_from_word(&word, 0);
  EXPECT_NE(out, nullptr);
  EXPECT_EQ(TakeAndFree(out), "Helvetica");
}

TEST_F(GetFontNameFromWordTest_2476, AllCapsWithoutPlusNotTreatedAsSubset_2476) {
  FakeGooString name("ABCDE");
  FakeTextWord word;
  word.SetFontNameForIndex(0, &name);

  gchar *out = get_font_name_from_word(&word, 0);
  EXPECT_NE(out, nullptr);
  EXPECT_EQ(TakeAndFree(out), "ABCDE");
}

TEST_F(GetFontNameFromWordTest_2476, PlusAtBeginningNotTreatedAsSubset_2476) {
  FakeGooString name("+Helvetica");
  FakeTextWord word;
  word.SetFontNameForIndex(0, &name);

  gchar *out = get_font_name_from_word(&word, 0);
  EXPECT_NE(out, nullptr);
  EXPECT_EQ(TakeAndFree(out), "+Helvetica");
}

TEST_F(GetFontNameFromWordTest_2476, PlusAtEndAfterAllCapsProducesEmptyString_2476) {
  // "ABC+" matches the subset detection: prefix letters then '+' at position i,
  // and name is advanced by i+1, resulting in empty suffix.
  FakeGooString name("ABC+");
  FakeTextWord word;
  word.SetFontNameForIndex(0, &name);

  gchar *out = get_font_name_from_word(&word, 0);
  EXPECT_NE(out, nullptr);
  EXPECT_EQ(TakeAndFree(out), "");
}

TEST_F(GetFontNameFromWordTest_2476, UsesProvidedWordIndexToSelectFontName_2476) {
  FakeGooString name0("ABCDE+SubsetFont");
  FakeGooString name1("Times-Roman");
  FakeTextWord word;
  word.SetFontNameForIndex(0, &name0);
  word.SetFontNameForIndex(1, &name1);

  gchar *out0 = get_font_name_from_word(&word, 0);
  EXPECT_NE(out0, nullptr);
  EXPECT_EQ(TakeAndFree(out0), "SubsetFont");

  gchar *out1 = get_font_name_from_word(&word, 1);
  EXPECT_NE(out1, nullptr);
  EXPECT_EQ(TakeAndFree(out1), "Times-Roman");
}

TEST_F(GetFontNameFromWordTest_2476, OutOfRangeIndexReturnsDefault_2476) {
  FakeGooString name0("Helvetica");
  FakeTextWord word;
  word.SetFontNameForIndex(0, &name0);

  // Index not set => getFontName() returns nullptr.
  gchar *out = get_font_name_from_word(&word, 123);
  EXPECT_NE(out, nullptr);
  EXPECT_EQ(TakeAndFree(out), "Default");
}

TEST_F(GetFontNameFromWordTest_2476, NegativeIndexReturnsDefault_2476) {
  FakeGooString name0("Helvetica");
  FakeTextWord word;
  word.SetFontNameForIndex(0, &name0);

  gchar *out = get_font_name_from_word(&word, -1);
  EXPECT_NE(out, nullptr);
  EXPECT_EQ(TakeAndFree(out), "Default");
}