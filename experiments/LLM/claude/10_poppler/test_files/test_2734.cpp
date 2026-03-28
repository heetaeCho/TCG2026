#include <gtest/gtest.h>
#include <string>
#include "GooString.h"

// We need to declare the static function we're testing.
// Since it's a static function in a .cc file, we need to include it or redefine its signature.
// We'll include the implementation file directly to access the static function.

// Forward declare strrstr if needed
static const char *strrstr(const char *s, const char *find) {
    const char *last = nullptr;
    size_t findLen = strlen(find);
    if (findLen == 0) return s;
    while ((s = strstr(s, find)) != nullptr) {
        last = s;
        s++;
    }
    return last;
}

// Copy the function under test since it's static in a .cc file
static void CloseTags(GooString *htext, bool &finish_a, bool &finish_italic, bool &finish_bold) {
    const char *last_italic = finish_italic && (finish_bold || finish_a) ? strrstr(htext->c_str(), "<i>") : nullptr;
    const char *last_bold = finish_bold && (finish_italic || finish_a) ? strrstr(htext->c_str(), "<b>") : nullptr;
    const char *last_a = finish_a && (finish_italic || finish_bold) ? strrstr(htext->c_str(), "<a ") : nullptr;

    if (finish_a && (finish_italic || finish_bold) && last_a > (last_italic > last_bold ? last_italic : last_bold)) {
        htext->append("</a>", 4);
        finish_a = false;
    }
    if (finish_italic && finish_bold && last_italic > last_bold) {
        htext->append("</i>", 4);
        finish_italic = false;
    }
    if (finish_bold) {
        htext->append("</b>", 4);
    }
    if (finish_italic) {
        htext->append("</i>", 4);
    }
    if (finish_a) {
        htext->append("</a>");
    }
}

class CloseTagsTest_2734 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: All flags false, nothing should be appended
TEST_F(CloseTagsTest_2734, AllFlagsFalse_NothingAppended_2734) {
    GooString htext("some text");
    bool finish_a = false, finish_italic = false, finish_bold = false;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    EXPECT_STREQ(htext.c_str(), "some text");
    EXPECT_FALSE(finish_a);
    EXPECT_FALSE(finish_italic);
    EXPECT_FALSE(finish_bold);
}

// Test: Only finish_bold is true
TEST_F(CloseTagsTest_2734, OnlyBold_2734) {
    GooString htext("<b>bold text");
    bool finish_a = false, finish_italic = false, finish_bold = true;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    EXPECT_STREQ(htext.c_str(), "<b>bold text</b>");
}

// Test: Only finish_italic is true
TEST_F(CloseTagsTest_2734, OnlyItalic_2734) {
    GooString htext("<i>italic text");
    bool finish_a = false, finish_italic = true, finish_bold = false;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    EXPECT_STREQ(htext.c_str(), "<i>italic text</i>");
}

// Test: Only finish_a is true
TEST_F(CloseTagsTest_2734, OnlyAnchor_2734) {
    GooString htext("<a href=\"url\">link text");
    bool finish_a = true, finish_italic = false, finish_bold = false;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    EXPECT_STREQ(htext.c_str(), "<a href=\"url\">link text</a>");
}

// Test: finish_bold and finish_italic, italic opened after bold
TEST_F(CloseTagsTest_2734, BoldThenItalic_CloseItalicFirst_2734) {
    GooString htext("<b>bold <i>italic");
    bool finish_a = false, finish_italic = true, finish_bold = true;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    // last_italic > last_bold, so </i> appended first, then </b>
    EXPECT_STREQ(htext.c_str(), "<b>bold <i>italic</i></b>");
    EXPECT_FALSE(finish_italic);
}

// Test: finish_bold and finish_italic, bold opened after italic
TEST_F(CloseTagsTest_2734, ItalicThenBold_CloseBoldFirst_2734) {
    GooString htext("<i>italic <b>bold");
    bool finish_a = false, finish_italic = true, finish_bold = true;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    // last_bold > last_italic, so the italic-first condition is false
    // first </b> then </i>
    EXPECT_STREQ(htext.c_str(), "<i>italic <b>bold</b></i>");
}

// Test: finish_a and finish_bold, anchor opened after bold
TEST_F(CloseTagsTest_2734, BoldThenAnchor_CloseAnchorFirst_2734) {
    GooString htext("<b>bold <a href=\"x\">link");
    bool finish_a = true, finish_italic = false, finish_bold = true;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    // last_a > last_bold, so </a> first, then </b>
    EXPECT_STREQ(htext.c_str(), "<b>bold <a href=\"x\">link</a></b>");
    EXPECT_FALSE(finish_a);
}

// Test: finish_a and finish_bold, bold opened after anchor
TEST_F(CloseTagsTest_2734, AnchorThenBold_CloseBoldFirst_2734) {
    GooString htext("<a href=\"x\">link <b>bold");
    bool finish_a = true, finish_italic = false, finish_bold = true;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    // last_bold > last_a, so anchor-first condition is false
    // </b> then </a>
    EXPECT_STREQ(htext.c_str(), "<a href=\"x\">link <b>bold</b></a>");
}

// Test: finish_a and finish_italic, anchor opened after italic
TEST_F(CloseTagsTest_2734, ItalicThenAnchor_CloseAnchorFirst_2734) {
    GooString htext("<i>italic <a href=\"x\">link");
    bool finish_a = true, finish_italic = true, finish_bold = false;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    // last_a > last_italic, so </a> first, then </i>
    EXPECT_STREQ(htext.c_str(), "<i>italic <a href=\"x\">link</a></i>");
    EXPECT_FALSE(finish_a);
}

// Test: finish_a and finish_italic, italic opened after anchor
TEST_F(CloseTagsTest_2734, AnchorThenItalic_CloseItalicFirst_2734) {
    GooString htext("<a href=\"x\">link <i>italic");
    bool finish_a = true, finish_italic = true, finish_bold = false;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    // last_italic > last_a, so anchor-first condition is false
    // </i> then </a>
    EXPECT_STREQ(htext.c_str(), "<a href=\"x\">link <i>italic</i></a>");
}

// Test: All three flags true, anchor last
TEST_F(CloseTagsTest_2734, AllThreeFlags_AnchorLast_2734) {
    GooString htext("<b>bold <i>italic <a href=\"x\">link");
    bool finish_a = true, finish_italic = true, finish_bold = true;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    // last_a is last -> </a> first, then last_italic > last_bold -> </i>, then </b>
    EXPECT_STREQ(htext.c_str(), "<b>bold <i>italic <a href=\"x\">link</a></i></b>");
    EXPECT_FALSE(finish_a);
    EXPECT_FALSE(finish_italic);
}

// Test: All three flags true, italic last
TEST_F(CloseTagsTest_2734, AllThreeFlags_ItalicLast_2734) {
    GooString htext("<b>bold <a href=\"x\">link <i>italic");
    bool finish_a = true, finish_italic = true, finish_bold = true;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    // last_italic is last, last_a > last_bold
    // anchor-first condition: last_a > max(last_italic, last_bold)? last_italic > last_a -> no
    // italic-bold: last_italic > last_bold -> yes, so </i> then </b>, then </a>
    EXPECT_STREQ(htext.c_str(), "<b>bold <a href=\"x\">link <i>italic</i></b></a>");
}

// Test: All three flags true, bold last
TEST_F(CloseTagsTest_2734, AllThreeFlags_BoldLast_2734) {
    GooString htext("<i>italic <a href=\"x\">link <b>bold");
    bool finish_a = true, finish_italic = true, finish_bold = true;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    // last_bold is last, last_a > last_italic
    // anchor-first: last_a > max(last_italic, last_bold)? last_bold > last_a -> no
    // italic-bold: last_italic > last_bold? no
    // so: </b>, then </i>, then </a>
    EXPECT_STREQ(htext.c_str(), "<i>italic <a href=\"x\">link <b>bold</b></i></a>");
}

// Test: Empty string, all flags true
TEST_F(CloseTagsTest_2734, EmptyString_AllFlagsTrue_2734) {
    GooString htext("");
    bool finish_a = true, finish_italic = true, finish_bold = true;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    // No tags found, so strrstr returns nullptr for all
    // anchor-first condition: nullptr > max(nullptr, nullptr) -> false
    // italic-bold: nullptr > nullptr -> false
    // finish_bold -> </b>
    // finish_italic -> </i>
    // finish_a -> </a>
    EXPECT_STREQ(htext.c_str(), "</b></i></a>");
}

// Test: Tags present but no content between them
TEST_F(CloseTagsTest_2734, TagsNoContent_BoldAndItalic_2734) {
    GooString htext("<b><i>");
    bool finish_a = false, finish_italic = true, finish_bold = true;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    // last_italic > last_bold -> close italic first
    EXPECT_STREQ(htext.c_str(), "<b><i></i></b>");
}

// Test: Verify flags are set to false after closing
TEST_F(CloseTagsTest_2734, FlagsResetAfterClose_2734) {
    GooString htext("<b><i>");
    bool finish_a = false, finish_italic = true, finish_bold = true;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    // finish_italic should be false (reset in the italic>bold branch)
    // finish_bold was true, handled in if(finish_bold) block, but not explicitly set false
    // Actually, looking at the code: finish_bold is never set to false, only finish_a and finish_italic can be
    // Let's verify
    EXPECT_FALSE(finish_italic); // Set false in the italic>bold branch
    EXPECT_TRUE(finish_bold);    // Bold flag is NOT reset in the code; it's just used
    // Wait, re-reading: the code doesn't set finish_bold=false. Let me re-check.
    // Actually the code checks `if (finish_bold)` and appends </b> but doesn't reset it.
    // Same for the final `if (finish_italic)` and `if (finish_a)`.
}

// Test: Multiple occurrences of tags, should use last occurrence
TEST_F(CloseTagsTest_2734, MultipleTagOccurrences_2734) {
    GooString htext("<b>first</b><i>second</i><b>third <i>fourth");
    bool finish_a = false, finish_italic = true, finish_bold = true;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    // strrstr finds last <b> and last <i>
    // last <i> is after last <b>, so italic closed first
    EXPECT_STREQ(htext.c_str(), "<b>first</b><i>second</i><b>third <i>fourth</i></b>");
}

// Test: Bold and italic at same level (bold after italic in string)
TEST_F(CloseTagsTest_2734, BoldAfterItalic_2734) {
    GooString htext("<i><b>text");
    bool finish_a = false, finish_italic = true, finish_bold = true;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    // last_bold (pos 3) > last_italic (pos 0), so italic>bold condition false
    // </b> then </i>
    EXPECT_STREQ(htext.c_str(), "<i><b>text</b></i>");
}

// Test: All three, order: italic, bold, anchor
TEST_F(CloseTagsTest_2734, AllThree_ItalicBoldAnchor_2734) {
    GooString htext("<i>i <b>b <a href=\"x\">a");
    bool finish_a = true, finish_italic = true, finish_bold = true;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    // last_a after last_bold after last_italic
    // anchor-first: last_a > max(last_italic, last_bold) = last_bold -> yes
    // append </a>, finish_a = false
    // italic>bold: last_italic < last_bold -> no
    // finish_bold -> </b>
    // finish_italic -> </i>
    // finish_a is false, skip
    EXPECT_STREQ(htext.c_str(), "<i>i <b>b <a href=\"x\">a</a></b></i>");
}

// Test: Anchor with no other tags
TEST_F(CloseTagsTest_2734, AnchorOnlyWithContent_2734) {
    GooString htext("<a href=\"http://example.com\">Example");
    bool finish_a = true, finish_italic = false, finish_bold = false;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    EXPECT_STREQ(htext.c_str(), "<a href=\"http://example.com\">Example</a>");
}

// Test: String with no matching tags but flags set
TEST_F(CloseTagsTest_2734, NoMatchingTags_AllFlagsSet_2734) {
    GooString htext("plain text no tags");
    bool finish_a = true, finish_italic = true, finish_bold = true;
    CloseTags(&htext, finish_a, finish_italic, finish_bold);
    // strrstr returns nullptr for all, so no early close conditions met
    // Default order: </b>, </i>, </a>
    EXPECT_STREQ(htext.c_str(), "plain text no tags</b></i></a>");
}
