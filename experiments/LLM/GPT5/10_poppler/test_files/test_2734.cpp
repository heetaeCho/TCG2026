// File: CloseTags_test_2734.cc

#include <gtest/gtest.h>

#include "goo/GooString.h"

// CloseTags() is a static function in HtmlOutputDev.cc.
// To test it as a black-box via its public signature, we include the .cc here.
#include "utils/HtmlOutputDev.cc"

namespace {

class CloseTagsTest_2734 : public ::testing::Test {
protected:
  static std::string Str(const GooString &s) {
    // GooString is used with c_str() in production code (CloseTags).
    return std::string(s.c_str());
  }
};

TEST_F(CloseTagsTest_2734, NoFlagsDoesNotAppendAnything_2734) {
  GooString htext("<b>hello</b>");
  bool finish_a = false;
  bool finish_italic = false;
  bool finish_bold = false;

  CloseTags(&htext, finish_a, finish_italic, finish_bold);

  EXPECT_EQ(Str(htext), "<b>hello</b>");
  EXPECT_FALSE(finish_a);
  EXPECT_FALSE(finish_italic);
  EXPECT_FALSE(finish_bold);
}

TEST_F(CloseTagsTest_2734, FinishBoldOnlyAppendsBoldClose_2734) {
  GooString htext("plain");
  bool finish_a = false;
  bool finish_italic = false;
  bool finish_bold = true;

  CloseTags(&htext, finish_a, finish_italic, finish_bold);

  EXPECT_EQ(Str(htext), "plain</b>");
  EXPECT_FALSE(finish_a);
  EXPECT_FALSE(finish_italic);
  EXPECT_TRUE(finish_bold);
}

TEST_F(CloseTagsTest_2734, FinishItalicOnlyAppendsItalicClose_2734) {
  GooString htext("plain");
  bool finish_a = false;
  bool finish_italic = true;
  bool finish_bold = false;

  CloseTags(&htext, finish_a, finish_italic, finish_bold);

  EXPECT_EQ(Str(htext), "plain</i>");
  EXPECT_FALSE(finish_a);
  EXPECT_TRUE(finish_italic);
  EXPECT_FALSE(finish_bold);
}

TEST_F(CloseTagsTest_2734, FinishAnchorOnlyAppendsAnchorClose_2734) {
  GooString htext("plain");
  bool finish_a = true;
  bool finish_italic = false;
  bool finish_bold = false;

  CloseTags(&htext, finish_a, finish_italic, finish_bold);

  EXPECT_EQ(Str(htext), "plain</a>");
  EXPECT_TRUE(finish_a);
  EXPECT_FALSE(finish_italic);
  EXPECT_FALSE(finish_bold);
}

TEST_F(CloseTagsTest_2734, BoldAndItalicWhenItalicOpenedAfterBoldClosesItalicBeforeBold_2734) {
  // Ensure both "<b>" and "<i>" exist and that the last "<i>" appears after the last "<b>".
  GooString htext("<b>bold<i>italic");
  bool finish_a = false;
  bool finish_italic = true;
  bool finish_bold = true;

  CloseTags(&htext, finish_a, finish_italic, finish_bold);

  // Observable behavior: closes italic before bold in this scenario.
  EXPECT_EQ(Str(htext), "<b>bold<i>italic</i></b>");
  // CloseTags may clear finish_italic in this ordering.
  EXPECT_FALSE(finish_italic);
  EXPECT_FALSE(finish_a);
  EXPECT_TRUE(finish_bold);
}

TEST_F(CloseTagsTest_2734, BoldAndItalicWhenBoldOpenedAfterItalicClosesBoldBeforeItalic_2734) {
  // Ensure both "<i>" and "<b>" exist and that the last "<b>" appears after the last "<i>".
  GooString htext("<i>italic<b>bold");
  bool finish_a = false;
  bool finish_italic = true;
  bool finish_bold = true;

  CloseTags(&htext, finish_a, finish_italic, finish_bold);

  // Observable behavior: closes bold before italic in this scenario.
  EXPECT_EQ(Str(htext), "<i>italic<b>bold</b></i>");
  // In this ordering, finish_italic is not cleared by the italic-vs-bold ordering branch.
  EXPECT_TRUE(finish_italic);
  EXPECT_FALSE(finish_a);
  EXPECT_TRUE(finish_bold);
}

TEST_F(CloseTagsTest_2734, AnchorOpenedAfterBoldClosesAnchorFirstAndClearsFinishA_2734) {
  // Ensure both "<b>" and "<a " exist and that the last "<a " appears after the last "<b>".
  GooString htext("<b>bold<a href='x'>link");
  bool finish_a = true;
  bool finish_italic = false;
  bool finish_bold = true;

  CloseTags(&htext, finish_a, finish_italic, finish_bold);

  // Observable behavior: closes </a> before closing </b>.
  EXPECT_EQ(Str(htext), "<b>bold<a href='x'>link</a></b>");
  EXPECT_FALSE(finish_a);       // CloseTags clears finish_a in this scenario.
  EXPECT_FALSE(finish_italic);
  EXPECT_TRUE(finish_bold);
}

TEST_F(CloseTagsTest_2734, AnchorOpenedBeforeBoldClosesBoldThenAnchorAtEnd_2734) {
  // Ensure both "<a " and "<b>" exist and that "<a " appears before "<b>".
  GooString htext("<a href='x'><b>bold");
  bool finish_a = true;
  bool finish_italic = false;
  bool finish_bold = true;

  CloseTags(&htext, finish_a, finish_italic, finish_bold);

  // Observable behavior: closes </b> and then closes </a> at the end.
  EXPECT_EQ(Str(htext), "<a href='x'><b>bold</b></a>");
  EXPECT_TRUE(finish_a);        // Not cleared because the early-close condition should not trigger.
  EXPECT_FALSE(finish_italic);
  EXPECT_TRUE(finish_bold);
}

} // namespace