#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <gmock/gmock.h>



using namespace tinyxml2;

using ::testing::_;

using ::testing::InSequence;



class MockXMLPrinter : public XMLPrinter {

public:

    MOCK_METHOD(void, Putc, (char ch), (override));

};



TEST_F(MockXMLPrinterTest_304, SealElementIfJustOpened_WhenElementJustOpened_PutcCalledWithGreaterThan_304) {

    MockXMLPrinter printer(nullptr, false, 0, EscapeAposCharsInAttributes::No);

    printer._elementJustOpened = true;



    EXPECT_CALL(printer, Putc('>')).Times(1);



    printer.SealElementIfJustOpened();

}



TEST_F(MockXMLPrinterTest_304, SealElementIfJustOpened_WhenElementNotJustOpened_PutcNotCalled_304) {

    MockXMLPrinter printer(nullptr, false, 0, EscapeAposCharsInAttributes::No);

    printer._elementJustOpened = false;



    EXPECT_CALL(printer, Putc(_)).Times(0);



    printer.SealElementIfJustOpened();

}



TEST_F(MockXMLPrinterTest_304, SealElementIfJustOpened_MultipleCallsWithElementJustOpened_PutcCalledOncePerCall_304) {

    MockXMLPrinter printer(nullptr, false, 0, EscapeAposCharsInAttributes::No);

    printer._elementJustOpened = true;



    InSequence s;

    EXPECT_CALL(printer, Putc('>')).Times(1);

    EXPECT_CALL(printer, Putc('>')).Times(1);



    printer.SealElementIfJustOpened();

    printer.SealElementIfJustOpened();

}



TEST_F(MockXMLPrinterTest_304, SealElementIfJustOpened_MultipleCallsWithElementNotJustOpened_PutcNeverCalled_304) {

    MockXMLPrinter printer(nullptr, false, 0, EscapeAposCharsInAttributes::No);

    printer._elementJustOpened = false;



    EXPECT_CALL(printer, Putc(_)).Times(0);



    printer.SealElementIfJustOpened();

    printer.SealElementIfJustOpened();

}
