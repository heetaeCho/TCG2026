#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest_152 : public ::testing::Test {

protected:

    FILE* file;

    XMLPrinter* printer;



    virtual void SetUp() {

        file = fopen("test_output.xml", "w+");

        ASSERT_NE(file, nullptr);

        printer = new XMLPrinter(file, false, 0, false);

    }



    virtual void TearDown() {

        delete printer;

        fclose(file);

        remove("test_output.xml");

    }

};



TEST_F(XMLPrinterTest_152, WriteString_152) {

    const char* data = "Test String";

    printer->Write(data);

    rewind(file);

    char buffer[100];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);

    EXPECT_EQ(strncmp(buffer, data, strlen(data)), 0);

}



TEST_F(XMLPrinterTest_152, WriteBoundaryCondition_152) {

    const char* emptyString = "";

    printer->Write(emptyString);

    rewind(file);

    char buffer[1];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);

    EXPECT_EQ(bytesRead, 0u);

}



TEST_F(XMLPrinterTest_152, WriteMultipleStrings_152) {

    const char* data1 = "First String";

    const char* data2 = "Second String";

    printer->Write(data1);

    printer->Write(data2);

    rewind(file);

    char buffer[200];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);

    EXPECT_EQ(strncmp(buffer, data1, strlen(data1)), 0);

    EXPECT_EQ(strncmp(buffer + strlen(data1), data2, strlen(data2)), 0);

}



TEST_F(XMLPrinterTest_152, PushHeader_152) {

    printer->PushHeader(true, true);

    rewind(file);

    char buffer[100];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);

    EXPECT_TRUE(bytesRead > 0u); // Check if something is written

}



TEST_F(XMLPrinterTest_152, OpenElement_152) {

    const char* elementName = "TestElement";

    printer->OpenElement(elementName, false);

    rewind(file);

    char buffer[100];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);

    EXPECT_TRUE(bytesRead > 0u); // Check if something is written

}



TEST_F(XMLPrinterTest_152, PushAttribute_String_152) {

    const char* attrName = "attribute";

    const char* attrValue = "value";

    printer->OpenElement("TestElement", false);

    printer->PushAttribute(attrName, attrValue);

    rewind(file);

    char buffer[100];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);

    EXPECT_TRUE(bytesRead > 0u); // Check if something is written

}



TEST_F(XMLPrinterTest_152, PushText_String_152) {

    const char* text = "Sample Text";

    printer->PushText(text, false);

    rewind(file);

    char buffer[100];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);

    EXPECT_TRUE(bytesRead > 0u); // Check if something is written

}



TEST_F(XMLPrinterTest_152, PushComment_152) {

    const char* comment = "This is a comment";

    printer->PushComment(comment);

    rewind(file);

    char buffer[100];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);

    EXPECT_TRUE(bytesRead > 0u); // Check if something is written

}



TEST_F(XMLPrinterTest_152, PushDeclaration_152) {

    const char* declaration = "xml version=\"1.0\"";

    printer->PushDeclaration(declaration);

    rewind(file);

    char buffer[100];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);

    EXPECT_TRUE(bytesRead > 0u); // Check if something is written

}



TEST_F(XMLPrinterTest_152, PushUnknown_152) {

    const char* unknown = "Unknown Node";

    printer->PushUnknown(unknown);

    rewind(file);

    char buffer[100];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);

    EXPECT_TRUE(bytesRead > 0u); // Check if something is written

}



TEST_F(XMLPrinterTest_152, CloseElement_152) {

    printer->OpenElement("TestElement", false);

    printer->CloseElement(false);

    rewind(file);

    char buffer[100];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);

    EXPECT_TRUE(bytesRead > 0u); // Check if something is written

}



TEST_F(XMLPrinterTest_152, ClearBuffer_152) {

    const char* data = "Data before clear";

    printer->Write(data);

    printer->ClearBuffer();

    rewind(file);

    char buffer[100];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);

    EXPECT_EQ(bytesRead, 0u); // Buffer should be empty after clear

}
