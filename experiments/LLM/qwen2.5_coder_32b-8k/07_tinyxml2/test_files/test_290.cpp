#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <gmock/gmock.h>



using namespace tinyxml2;

using ::testing::HasSubstr;



class XMLPrinterTest : public ::testing::Test {

protected:

    FILE* mockFile = nullptr;

    std::string bufferOutput;

    XMLPrinter printer;



    XMLPrinterTest() : printer(mockFile, false, 0) {}



    virtual void SetUp() {

        // Redirect output to a string stream

        printer._fp = fmemopen(&bufferOutput[0], bufferOutput.capacity(), "w");

    }



    virtual void TearDown() {

        if (printer._fp) {

            fclose(printer._fp);

            printer._fp = nullptr;

        }

    }

};



TEST_F(XMLPrinterTest_290, PrintWritesToBufferWhenNoFile_290) {

    printer.Print("Hello, %s!", "World");

    EXPECT_THAT(bufferOutput, HasSubstr("Hello, World!"));

}



TEST_F(XMLPrinterTest_290, PrintHandlesMultiplePrints_290) {

    printer.Print("First line\n");

    printer.Print("Second line\n");

    EXPECT_EQ(bufferOutput, "First line\nSecond line\n");

}



TEST_F(XMLPrinterTest_290, PrintFormatsIntegersCorrectly_290) {

    printer.Print("Value: %d", 123);

    EXPECT_THAT(bufferOutput, HasSubstr("Value: 123"));

}



TEST_F(XMLPrinterTest_290, PrintFormatsFloatsCorrectly_290) {

    printer.Print("Value: %.2f", 123.456);

    EXPECT_THAT(bufferOutput, HasSubstr("Value: 123.46"));

}



TEST_F(XMLPrinterTest_290, PrintHandlesEmptyString_290) {

    printer.Print("");

    EXPECT_EQ(bufferOutput, "");

}



TEST_F(XMLPrinterTest_290, PrintHandlesLongStrings_290) {

    std::string longString(1024, 'a');

    printer.Print("%s", longString.c_str());

    EXPECT_EQ(bufferOutput, longString);

}
