#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest : public ::testing::Test {

protected:

    XMLPrinter printer;

    

    XMLPrinterTest() : printer(nullptr, false, 0) {}

};



TEST_F(XMLPrinterTest_148, CStr_ReturnsEmptyStringInitially_148) {

    EXPECT_STREQ(printer.CStr(), "");

}



TEST_F(XMLPrinterTest_148, PushHeader_WritesDeclarationToBuffer_148) {

    printer.PushHeader(false, true);

    EXPECT_STRNE(printer.CStr(), "");

}



TEST_F(XMLPrinterTest_148, OpenElement_AddsElementTagToBuffer_148) {

    printer.OpenElement("test", false);

    EXPECT_STRNE(printer.CStr(), "");

}



TEST_F(XMLPrinterTest_148, PushAttribute_AddsAttributeToCurrentElement_148) {

    printer.OpenElement("test", false);

    printer.PushAttribute("attr", "value");

    EXPECT_STRNE(printer.CStr(), "");

}



TEST_F(XMLPrinterTest_148, CloseElement_ClosesTheLastOpenedElement_148) {

    printer.OpenElement("test", false);

    printer.CloseElement(false);

    EXPECT_STRNE(printer.CStr(), "");

}



TEST_F(XMLPrinterTest_148, PushText_AddsTextToCurrentElement_148) {

    printer.PushText("text");

    EXPECT_STRNE(printer.CStr(), "");

}



TEST_F(XMLPrinterTest_148, PushComment_AddsCommentToBuffer_148) {

    printer.PushComment("comment");

    EXPECT_STRNE(printer.CStr(), "");

}



TEST_F(XMLPrinterTest_148, PushDeclaration_AddsDeclarationToBuffer_148) {

    printer.PushDeclaration("declaration");

    EXPECT_STRNE(printer.CStr(), "");

}



TEST_F(XMLPrinterTest_148, PushUnknown_AddsUnknownElementToBuffer_148) {

    printer.PushUnknown("unknown");

    EXPECT_STRNE(printer.CStr(), "");

}



TEST_F(XMLPrinterTest_148, ClearBuffer_ResetsTheBuffer_148) {

    printer.OpenElement("test", false);

    printer.ClearBuffer();

    EXPECT_STREQ(printer.CStr(), "");

}



TEST_F(XMLPrinterTest_148, CompactMode_ReturnsCorrectCompactMode_148) {

    XMLDocument doc;

    XMLElement element;

    bool compact = printer.CompactMode(element);

    EXPECT_FALSE(compact); // Default is false based on constructor

}
