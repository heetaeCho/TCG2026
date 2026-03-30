#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"

#include <cstdio>



using namespace tinyxml2;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



class MockXMLPrinter : public XMLPrinter {

public:

    MOCK_METHOD(void, Write, (const char* data), (override));

    MOCK_METHOD(void, PrintSpace, (int depth), (override));



    MockXMLPrinter(FILE* file, bool compact, int depth, EscapeAposCharsInAttributes aposInAttributes)

        : XMLPrinter(file, compact, depth, aposInAttributes) {}

};



TEST_F(MockXMLPrinterTest_293, PrintSpace_NormalOperation_293) {

    MockXMLPrinter printer(nullptr, false, 0, EscapeNone);

    EXPECT_CALL(printer, Write(" "));

    printer.PrintSpace(1);

}



TEST_F(MockXMLPrinterTest_293, PrintSpace_BoundaryCondition_ZeroDepth_293) {

    MockXMLPrinter printer(nullptr, false, 0, EscapeNone);

    EXPECT_CALL(printer, Write(_)).Times(0);

    printer.PrintSpace(0);

}



TEST_F(MockXMLPrinterTest_293, PrintSpace_BoundaryCondition_MaxDepth_293) {

    MockXMLPrinter printer(nullptr, false, 0, EscapeNone);

    EXPECT_CALL(printer, Write(" ")).Times(100); // Assuming a reasonable max depth for testing

    printer.PrintSpace(100);

}



TEST_F(MockXMLPrinterTest_293, PrintSpace_ExceptionalCase_NegativeDepth_293) {

    MockXMLPrinter printer(nullptr, false, 0, EscapeNone);

    EXPECT_CALL(printer, Write(_)).Times(0);

    printer.PrintSpace(-5); // Negative depth should not write anything

}



TEST_F(MockXMLPrinterTest_293, PushText_NormalOperation_String_293) {

    MockXMLPrinter printer(nullptr, false, 0, EscapeNone);

    EXPECT_CALL(printer, Write("Hello World"));

    printer.PushText("Hello World", false);

}



TEST_F(MockXMLPrinterTest_293, PushText_BoundaryCondition_EmptyString_293) {

    MockXMLPrinter printer(nullptr, false, 0, EscapeNone);

    EXPECT_CALL(printer, Write(""));

    printer.PushText("", false);

}



TEST_F(MockXMLPrinterTest_293, PushAttribute_NormalOperation_StringValue_293) {

    MockXMLPrinter printer(nullptr, false, 0, EscapeNone);

    EXPECT_CALL(printer, Write("name=\"value\""));

    printer.PushAttribute("name", "value");

}



TEST_F(MockXMLPrinterTest_293, PushAttribute_BoundaryCondition_EmptyNameAndValue_293) {

    MockXMLPrinter printer(nullptr, false, 0, EscapeNone);

    EXPECT_CALL(printer, Write("=\"\""));

    printer.PushAttribute("", "");

}



TEST_F(MockXMLPrinterTest_293, PushAttribute_ExceptionalCase_NullName_293) {

    MockXMLPrinter printer(nullptr, false, 0, EscapeNone);

    EXPECT_CALL(printer, Write(_)).Times(0);

    printer.PushAttribute(nullptr, "value");

}



TEST_F(MockXMLPrinterTest_293, PushAttribute_ExceptionalCase_NullValue_293) {

    MockXMLPrinter printer(nullptr, false, 0, EscapeNone);

    EXPECT_CALL(printer, Write("name=\"\""));

    printer.PushAttribute("name", nullptr);

}
