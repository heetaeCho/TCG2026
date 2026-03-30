#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <gmock/gmock.h>



using namespace tinyxml2;

using ::testing::_;

using ::testing::Return;



class MockXMLPrinter : public XMLPrinter {

public:

    MOCK_METHOD1(Write, void(const char* data));

    MOCK_METHOD0(Putc, void(char ch));

    MOCK_METHOD1(PrintSpace, void(int depth));



    MockXMLPrinter(FILE * file, bool compact, int depth, EscapeAposCharsInAttributes aposInAttributes)

        : XMLPrinter(file, compact, depth, aposInAttributes) {}

};



TEST_F(MockXMLPrinter_303, CloseElement_NormalOperation_NoCompactMode_303) {

    MockXMLPrinter printer(nullptr, false, 1, EscapeAposCharsInAttributes::no);

    EXPECT_CALL(printer, Write("</root>")).Times(1);

    EXPECT_CALL(printer, Putc('\n')).Times(2);



    printer._stack.Push("root");

    printer.CloseElement(false);

}



TEST_F(MockXMLPrinter_303, CloseElement_NormalOperation_CompactMode_303) {

    MockXMLPrinter printer(nullptr, true, 1, EscapeAposCharsInAttributes::no);

    EXPECT_CALL(printer, Write("</root>")).Times(1);

    EXPECT_CALL(printer, Putc('\n')).Times(0);



    printer._stack.Push("root");

    printer.CloseElement(true);

}



TEST_F(MockXMLPrinter_303, CloseElement_ElementJustOpened_NoCompactMode_303) {

    MockXMLPrinter printer(nullptr, false, 1, EscapeAposCharsInAttributes::no);

    printer._elementJustOpened = true;

    EXPECT_CALL(printer, Write("/>")).Times(1);

    EXPECT_CALL(printer, Putc('\n')).Times(2);



    printer._stack.Push("root");

    printer.CloseElement(false);

}



TEST_F(MockXMLPrinter_303, CloseElement_ElementJustOpened_CompactMode_303) {

    MockXMLPrinter printer(nullptr, true, 1, EscapeAposCharsInAttributes::no);

    printer._elementJustOpened = true;

    EXPECT_CALL(printer, Write("/>")).Times(1);

    EXPECT_CALL(printer, Putc('\n')).Times(0);



    printer._stack.Push("root");

    printer.CloseElement(true);

}



TEST_F(MockXMLPrinter_303, CloseElement_TextDepthSet_NoCompactMode_303) {

    MockXMLPrinter printer(nullptr, false, 1, EscapeAposCharsInAttributes::no);

    printer._textDepth = 0;

    EXPECT_CALL(printer, Write("</root>")).Times(1);

    EXPECT_CALL(printer, Putc('\n')).Times(2);



    printer._stack.Push("root");

    printer.CloseElement(false);

}



TEST_F(MockXMLPrinter_303, CloseElement_TextDepthSet_CompactMode_303) {

    MockXMLPrinter printer(nullptr, true, 1, EscapeAposCharsInAttributes::no);

    printer._textDepth = 0;

    EXPECT_CALL(printer, Write("</root>")).Times(1);

    EXPECT_CALL(printer, Putc('\n')).Times(0);



    printer._stack.Push("root");

    printer.CloseElement(true);

}



TEST_F(MockXMLPrinter_303, CloseElement_DepthZero_NoCompactMode_303) {

    MockXMLPrinter printer(nullptr, false, 1, EscapeAposCharsInAttributes::no);

    EXPECT_CALL(printer, Write("</root>")).Times(1);

    EXPECT_CALL(printer, Putc('\n')).Times(2);



    printer._stack.Push("root");

    printer.CloseElement(false);

}



TEST_F(MockXMLPrinter_303, CloseElement_DepthZero_CompactMode_303) {

    MockXMLPrinter printer(nullptr, true, 1, EscapeAposCharsInAttributes::no);

    EXPECT_CALL(printer, Write("</root>")).Times(1);

    EXPECT_CALL(printer, Putc('\n')).Times(0);



    printer._stack.Push("root");

    printer.CloseElement(true);

}



TEST_F(MockXMLPrinter_303, CloseElement_BoundaryCondition_EmptyStack_NoCompactMode_303) {

    MockXMLPrinter printer(nullptr, false, 1, EscapeAposCharsInAttributes::no);

    EXPECT_CALL(printer, Write("</root>")).Times(0);

    EXPECT_CALL(printer, Putc('\n')).Times(2);



    printer.CloseElement(false); // Stack is empty

}



TEST_F(MockXMLPrinter_303, CloseElement_BoundaryCondition_EmptyStack_CompactMode_303) {

    MockXMLPrinter printer(nullptr, true, 1, EscapeAposCharsInAttributes::no);

    EXPECT_CALL(printer, Write("</root>")).Times(0);

    EXPECT_CALL(printer, Putc('\n')).Times(0);



    printer.CloseElement(true); // Stack is empty

}
