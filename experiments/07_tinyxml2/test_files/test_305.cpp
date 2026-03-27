#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <cstdio>

#include <string>



using namespace tinyxml2;



class XMLPrinterTest_305 : public ::testing::Test {

protected:

    FILE* file;

    XMLPrinter printer;



    void SetUp() override {

        file = fopen("test.xml", "w");

        ASSERT_NE(file, nullptr);

        printer = XMLPrinter(file, false, 0);

    }



    void TearDown() override {

        fclose(file);

        remove("test.xml");

    }

};



TEST_F(XMLPrinterTest_305, PushText_NormalOperation_305) {

    const char* text = "Hello, World!";

    printer.PushText(text, false);



    // Verify the output in the file

    rewind(file);

    char buffer[1024];

    fread(buffer, 1, sizeof(buffer), file);

    EXPECT_STREQ("Hello, World!", buffer);

}



TEST_F(XMLPrinterTest_305, PushText_CData_305) {

    const char* text = "CDATA Text";

    printer.PushText(text, true);



    // Verify the output in the file

    rewind(file);

    char buffer[1024];

    fread(buffer, 1, sizeof(buffer), file);

    EXPECT_STREQ("<![CDATA[CDATA Text]]>", buffer);

}



TEST_F(XMLPrinterTest_305, PushText_BoundaryConditions_305) {

    const char* emptyText = "";

    printer.PushText(emptyText, false);



    // Verify the output in the file

    rewind(file);

    char buffer[1024];

    fread(buffer, 1, sizeof(buffer), file);

    EXPECT_STREQ("", buffer);

}



TEST_F(XMLPrinterTest_305, PushText_ExceptionalCases_305) {

    // Since PushText does not throw exceptions based on the given interface,

    // we test with null pointer which should be handled gracefully.

    const char* nullText = nullptr;

    printer.PushText(nullText, false);



    // Verify the output in the file

    rewind(file);

    char buffer[1024];

    fread(buffer, 1, sizeof(buffer), file);

    EXPECT_STREQ("", buffer); // Assuming null pointer is treated as empty string

}
