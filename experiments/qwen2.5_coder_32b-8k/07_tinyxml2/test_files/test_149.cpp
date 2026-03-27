#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest_149 : public ::testing::Test {

protected:

    void SetUp() override {

        _file = fopen("test.xml", "w");

        ASSERT_NE(_file, nullptr);

        printer = new XMLPrinter(_file, false, 0, EscapeAposCharsInAttributes::NO_ATTRIBUTE_ESCAPING);

    }



    void TearDown() override {

        delete printer;

        fclose(_file);

        remove("test.xml");

    }



    FILE* _file;

    XMLPrinter* printer;

};



TEST_F(XMLPrinterTest_149, CStrSizeInitiallyZero_149) {

    EXPECT_EQ(printer->CStrSize(), 0U);

}



TEST_F(XMLPrinterTest_149, PushHeaderIncreasesCStrSize_149) {

    printer->PushHeader(false, true);

    EXPECT_GT(printer->CStrSize(), 0U);

}



TEST_F(XMLPrinterTest_149, OpenElementIncreasesCStrSize_149) {

    printer->OpenElement("root", false);

    EXPECT_GT(printer->CStrSize(), 0U);

}



TEST_F(XMLPrinterTest_149, PushAttributeIncreasesCStrSize_149) {

    printer->PushHeader(false, true);

    printer->OpenElement("root", false);

    printer->PushAttribute("name", "value");

    EXPECT_GT(printer->CStrSize(), 0U);

}



TEST_F(XMLPrinterTest_149, PushTextIncreasesCStrSize_149) {

    printer->PushHeader(false, true);

    printer->OpenElement("root", false);

    printer->PushText("Hello, World!");

    EXPECT_GT(printer->CStrSize(), 0U);

}



TEST_F(XMLPrinterTest_149, CloseElementIncreasesCStrSize_149) {

    printer->PushHeader(false, true);

    printer->OpenElement("root", false);

    printer->CloseElement(false);

    EXPECT_GT(printer->CStrSize(), 0U);

}



TEST_F(XMLPrinterTest_149, ClearBufferResetsCStrSize_149) {

    printer->PushHeader(false, true);

    printer->ClearBuffer();

    EXPECT_EQ(printer->CStrSize(), 0U);

}



TEST_F(XMLPrinterTest_149, PushCommentIncreasesCStrSize_149) {

    printer->PushComment("This is a comment");

    EXPECT_GT(printer->CStrSize(), 0U);

}



TEST_F(XMLPrinterTest_149, PushDeclarationIncreasesCStrSize_149) {

    printer->PushDeclaration("version=\"1.0\"");

    EXPECT_GT(printer->CStrSize(), 0U);

}



TEST_F(XMLPrinterTest_149, PushUnknownIncreasesCStrSize_149) {

    printer->PushUnknown("!DOCTYPE");

    EXPECT_GT(printer->CStrSize(), 0U);

}
