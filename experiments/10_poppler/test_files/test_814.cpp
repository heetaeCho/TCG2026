#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Annot.h"

#include <gmock/gmock.h>



using namespace testing;



class MockLinkAction : public LinkAction {

public:

    MOCK_METHOD(void, someMethod, (), (const));

};



TEST_F(AnnotLinkTest_814, GetAction_ReturnsNonNullPointer_814) {

    PDFDoc doc(nullptr);

    PDFRectangle rect;

    AnnotLink annotLink(&doc, &rect);



    EXPECT_NE(annotLink.getAction(), nullptr);

}



TEST_F(AnnotLinkTest_814, GetAction_ConsistentReturn_814) {

    PDFDoc doc(nullptr);

    PDFRectangle rect;

    AnnotLink annotLink(&doc, &rect);



    LinkAction* action1 = annotLink.getAction();

    LinkAction* action2 = annotLink.getAction();



    EXPECT_EQ(action1, action2);

}



TEST_F(AnnotLinkTest_814, GetAction_ReturnsSameInstanceAfterDraw_814) {

    PDFDoc doc(nullptr);

    PDFRectangle rect;

    AnnotLink annotLink(&doc, &rect);



    LinkAction* actionBefore = annotLink.getAction();

    Gfx gfx(nullptr, nullptr);

    annotLink.draw(&gfx, false);

    LinkAction* actionAfter = annotLink.getAction();



    EXPECT_EQ(actionBefore, actionAfter);

}



TEST_F(AnnotLinkTest_814, GetAction_ReturnsSameInstanceWithDifferentPrintingFlag_814) {

    PDFDoc doc(nullptr);

    PDFRectangle rect;

    AnnotLink annotLink(&doc, &rect);



    LinkAction* actionNotPrinting = annotLink.getAction();

    Gfx gfx(nullptr, nullptr);

    annotLink.draw(&gfx, false);

    LinkAction* actionPrinting = annotLink.getAction();



    EXPECT_EQ(actionNotPrinting, actionPrinting);

}



TEST_F(AnnotLinkTest_814, GetAction_ReturnsSameInstanceWithDifferentGfx_814) {

    PDFDoc doc(nullptr);

    PDFRectangle rect;

    AnnotLink annotLink(&doc, &rect);



    LinkAction* actionFirstGfx = annotLink.getAction();

    Gfx gfx1(nullptr, nullptr);

    annotLink.draw(&gfx1, false);

    LinkAction* actionSecondGfx = annotLink.getAction();



    EXPECT_EQ(actionFirstGfx, actionSecondGfx);

}
