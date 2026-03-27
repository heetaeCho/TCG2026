#include <gtest/gtest.h>

#include "./TestProjects/poppler/utils/HtmlOutputDev.cc"

#include "./TestProjects/poppler/goo/GooString.h"



using namespace std;



TEST(CloseTagsTest_2734, NoTagsToClose_2734) {

    GooString htext("Hello World");

    bool finish_a = false;

    bool finish_italic = false;

    bool finish_bold = false;



    CloseTags(&htext, finish_a, finish_italic, finish_bold);



    EXPECT_EQ(htext.toStr(), "Hello World");

}



TEST(CloseTagsTest_2734, CloseBoldTag_2734) {

    GooString htext("<b>Bold Text");

    bool finish_a = false;

    bool finish_italic = false;

    bool finish_bold = true;



    CloseTags(&htext, finish_a, finish_italic, finish_bold);



    EXPECT_EQ(htext.toStr(), "<b>Bold Text</b>");

}



TEST(CloseTagsTest_2734, CloseItalicTag_2734) {

    GooString htext("<i>Italic Text");

    bool finish_a = false;

    bool finish_italic = true;

    bool finish_bold = false;



    CloseTags(&htext, finish_a, finish_italic, finish_bold);



    EXPECT_EQ(htext.toStr(), "<i>Italic Text</i>");

}



TEST(CloseTagsTest_2734, CloseAnchorTag_2734) {

    GooString htext("<a href=\"#\">Link Text");

    bool finish_a = true;

    bool finish_italic = false;

    bool finish_bold = false;



    CloseTags(&htext, finish_a, finish_italic, finish_bold);



    EXPECT_EQ(htext.toStr(), "<a href=\"#\">Link Text</a>");

}



TEST(CloseTagsTest_2734, CloseMultipleTags_2734) {

    GooString htext("<b><i>Bold Italic Text");

    bool finish_a = false;

    bool finish_italic = true;

    bool finish_bold = true;



    CloseTags(&htext, finish_a, finish_italic, finish_bold);



    EXPECT_EQ(htext.toStr(), "<b><i>Bold Italic Text</i></b>");

}



TEST(CloseTagsTest_2734, CloseInOrderAnchorThenBold_2734) {

    GooString htext("<a href=\"#\"><b>Link Bold Text");

    bool finish_a = true;

    bool finish_italic = false;

    bool finish_bold = true;



    CloseTags(&htext, finish_a, finish_italic, finish_bold);



    EXPECT_EQ(htext.toStr(), "<a href=\"#\"><b>Link Bold Text</b></a>");

}



TEST(CloseTagsTest_2734, CloseInOrderBoldThenItalic_2734) {

    GooString htext("<b><i>Bold Italic Text");

    bool finish_a = false;

    bool finish_italic = true;

    bool finish_bold = true;



    CloseTags(&htext, finish_a, finish_italic, finish_bold);



    EXPECT_EQ(htext.toStr(), "<b><i>Bold Italic Text</i></b>");

}



TEST(CloseTagsTest_2734, CloseInOrderBoldThenItalicThenAnchor_2734) {

    GooString htext("<a href=\"#\"><b><i>Link Bold Italic Text");

    bool finish_a = true;

    bool finish_italic = true;

    bool finish_bold = true;



    CloseTags(&htext, finish_a, finish_italic, finish_bold);



    EXPECT_EQ(htext.toStr(), "<a href=\"#\"><b><i>Link Bold Italic Text</i></b></a>");

}



TEST(CloseTagsTest_2734, EmptyString_2734) {

    GooString htext("");

    bool finish_a = false;

    bool finish_italic = false;

    bool finish_bold = false;



    CloseTags(&htext, finish_a, finish_italic, finish_bold);



    EXPECT_EQ(htext.toStr(), "");

}



TEST(CloseTagsTest_2734, MixedTagsWithNoClosingNeeded_2734) {

    GooString htext("<b>Bold Text<i>Italic Text</i></b>");

    bool finish_a = false;

    bool finish_italic = false;

    bool finish_bold = false;



    CloseTags(&htext, finish_a, finish_italic, finish_bold);



    EXPECT_EQ(htext.toStr(), "<b>Bold Text<i>Italic Text</i></b>");

}
