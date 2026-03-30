#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest_310 : public ::testing::Test {

protected:

    FILE* dummyFile;

    XMLPrinter printer;



    void SetUp() override {

        dummyFile = fopen("dummy.txt", "w+");

        printer = XMLPrinter(dummyFile, false, 0, EscapeAposCharsInAttributes::eNo);

    }



    void TearDown() override {

        fclose(dummyFile);

        remove("dummy.txt");

    }

};



TEST_F(XMLPrinterTest_310, PushText_BoolTrue_310) {

    printer.PushText(true);

    // Assuming the default behavior is to write "true" as string representation

    EXPECT_EQ(strcmp(printer.CStr(), "true"), 0);

}



TEST_F(XMLPrinterTest_310, PushText_BoolFalse_310) {

    printer.PushText(false);

    // Assuming the default behavior is to write "false" as string representation

    EXPECT_EQ(strcmp(printer.CStr(), "false"), 0);

}



// Test for boundary conditions and exceptional cases are limited here as there are no clear boundaries or exceptions mentioned.

// The function PushText(bool) should ideally handle true/false without any issues, hence additional test cases might not be necessary.



TEST_F(XMLPrinterTest_310, CompactMode_PushText_BoolTrue_310) {

    printer.PushText(true);

    // Assuming in compact mode, the output remains the same

    EXPECT_EQ(strcmp(printer.CStr(), "true"), 0);

}



TEST_F(XMLPrinterTest_310, CompactMode_PushText_BoolFalse_310) {

    printer = XMLPrinter(dummyFile, true, 0, EscapeAposCharsInAttributes::eNo); // Setting compact mode to true

    printer.PushText(false);

    // Assuming in compact mode, the output remains the same

    EXPECT_EQ(strcmp(printer.CStr(), "false"), 0);

}
