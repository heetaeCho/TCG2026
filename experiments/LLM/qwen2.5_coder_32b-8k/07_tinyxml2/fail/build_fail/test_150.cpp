#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest_150 : public ::testing::Test {

protected:

    FILE* dummyFile;

    XMLPrinter printer;



    void SetUp() override {

        dummyFile = fopen("/dev/null", "w"); // Redirect to null device for testing

        ASSERT_TRUE(dummyFile != nullptr);

        printer = XMLPrinter(dummyFile, false, 0, EscapeAposCharsInAttributes::YES);

    }



    void TearDown() override {

        fclose(dummyFile);

    }

};



TEST_F(XMLPrinterTest_150, ClearBuffer_ResetsBufferAndFirstElementFlag_150) {

    printer.PushText("Some text");

    EXPECT_FALSE(printer.CStrSize() == 0);



    printer.ClearBuffer();

    EXPECT_EQ(printer.CStrSize(), 0);

}



TEST_F(XMLPrinterTest_150, ClearBuffer_WithResetToFalse_DoesNotResetFirstElementFlag_150) {

    printer.PushText("Some text");

    EXPECT_FALSE(printer.CStrSize() == 0);



    printer.ClearBuffer(false);

    EXPECT_EQ(printer.CStrSize(), 0);

}



TEST_F(XMLPrinterTest_150, ClearBuffer_WithDefaultParameter_ResetsFirstElementFlag_150) {

    printer.PushText("Some text");

    EXPECT_FALSE(printer.CStrSize() == 0);



    printer.ClearBuffer();

    EXPECT_EQ(printer.CStrSize(), 0);

}



TEST_F(XMLPrinterTest_150, PushText_AddsTextToBuffer_150) {

    const char* text = "Sample text";

    printer.PushText(text);

    EXPECT_STREQ(strstr(printer.CStr(), text), text);

}



TEST_F(XMLPrinterTest_150, PushAttribute_StringValue_AddsAttributeToBuffer_150) {

    const char* name = "name";

    const char* value = "value";

    printer.PushAttribute(name, value);



    EXPECT_STREQ(strstr(printer.CStr(), name), name);

    EXPECT_STREQ(strstr(printer.CStr(), value), value);

}



TEST_F(XMLPrinterTest_150, PushAttribute_IntValue_AddsAttributeToBuffer_150) {

    const char* name = "name";

    int value = 42;

    printer.PushAttribute(name, value);



    EXPECT_STREQ(strstr(printer.CStr(), name), name);

    EXPECT_STREQ(strstr(printer.CStr(), std::to_string(value).c_str()), std::to_string(value).c_str());

}



TEST_F(XMLPrinterTest_150, PushComment_AddsCommentToBuffer_150) {

    const char* comment = "This is a comment";

    printer.PushComment(comment);



    EXPECT_STREQ(strstr(printer.CStr(), comment), comment);

}



TEST_F(XMLPrinterTest_150, PushDeclaration_AddsDeclarationToBuffer_150) {

    const char* declaration = "xml version=\"1.0\"";

    printer.PushDeclaration(declaration);



    EXPECT_STREQ(strstr(printer.CStr(), declaration), declaration);

}
