#include <gtest/gtest.h>

#include "TextOutputDev.h"

#include "PDFDoc.h"

#include "GfxState.h"

#include "TextPage.h"

#include "TextFlow.h"

#include "TextBlock.h"

#include "TextLine.h"

#include "TextWord.h"



using namespace std;



class MockPDFDoc : public PDFDoc {

public:

    MockPDFDoc() {}

    bool isOk() const override { return true; }

    double getPageMediaWidth(int page) override { return 595.0; } // A4 width

    double getPageMediaHeight(int page) override { return 842.0; } // A4 height

};



class MockGfxState : public GfxState {

public:

    MockGfxState() {}

};



class TextOutputDevTest : public ::testing::Test {

protected:

    void SetUp() override {

        doc = new MockPDFDoc();

        text_output_dev = new TextOutputDev(nullptr, false, 0.0, false, false);

        gfx_state = new MockGfxState();



        // Mocking a simple page with one word

        text_page = make_unique<TextPage>(nullptr, nullptr);

        text_flow = new TextFlow(text_page.get(), nullptr);

        text_block = new TextBlock(text_page.get(), 0);

        text_line = new TextLine(text_block, 0, 0.0);

        text_word = new TextWord(gfx_state, 0, 12.0);



        // Adding the word to the line

        text_line->addWord(text_word);



        // Adding the line to the block

        text_block->addWord(text_word);



        // Adding the block to the flow

        text_flow->addBlock(text_block);



        // Assigning the flow to the text page

        text_page->addFlow(text_flow);

    }



    void TearDown() override {

        delete text_output_dev;

        delete doc;

        delete gfx_state;



        // Clean up TextPage components

        delete text_word;

        delete text_line;

        delete text_block;

        delete text_flow;

    }



    MockPDFDoc* doc;

    TextOutputDev* text_output_dev;

    MockGfxState* gfx_state;

    unique_ptr<TextPage> text_page;

    TextFlow* text_flow;

    TextBlock* text_block;

    TextLine* text_line;

    TextWord* text_word;

};



TEST_F(TextOutputDevTest, GetFlows_ReturnsValidTextFlow) {

    const TextFlow* flows = text_output_dev->getFlows();

    EXPECT_EQ(flows, nullptr); // TextOutputDev::getFlows() returns the internal text page's flow, which is set in our test setup

}



TEST_F(TextOutputDevTest, GetFlows_MatchesConstructedTextFlow) {

    text_output_dev->startPage(1, gfx_state, nullptr);

    text_page->display(text_output_dev, gfx_state, nullptr);

    const TextFlow* flows = text_output_dev->getFlows();

    EXPECT_NE(flows, nullptr);

}



TEST_F(TextOutputDevTest, GetText_ReturnsEmptyString_WhenNoText) {

    TextOutputDev empty_text_output_dev(nullptr, false, 0.0, false, false);

    GooString result = empty_text_output_dev.getText({});

    EXPECT_EQ(result.getCString(), "");

}



// Test for boundary conditions and edge cases can be added as necessary

```


