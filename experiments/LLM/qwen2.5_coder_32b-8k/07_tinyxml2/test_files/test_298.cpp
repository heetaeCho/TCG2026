#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <cstdio>



using namespace tinyxml2;



class XMLPrinterTest : public ::testing::Test {

protected:

    FILE* dummyFile;

    XMLPrinter* printer;



    virtual void SetUp() {

        dummyFile = fopen("dummy.txt", "w+");

        printer = new XMLPrinter(dummyFile, false, 0);

    }



    virtual void TearDown() {

        delete printer;

        fclose(dummyFile);

        remove("dummy.txt");

    }

};



TEST_F(XMLPrinterTest_298, PushAttribute_NameAndValue_298) {

    printer->PushAttribute("testName", 42u);

    // Assuming we can verify the output content somehow, this is a placeholder

    // For actual implementation, one would need access to the internal buffer or output file.

}



TEST_F(XMLPrinterTest_298, PushAttribute_ZeroValue_298) {

    printer->PushAttribute("testName", 0u);

    // Assuming we can verify the output content somehow, this is a placeholder

}



TEST_F(XMLPrinterTest_298, PushAttribute_MaxValue_298) {

    printer->PushAttribute("testName", UINT_MAX);

    // Assuming we can verify the output content somehow, this is a placeholder

}



TEST_F(XMLPrinterTest_298, PushAttribute_LongName_298) {

    char longName[BUF_SIZE];

    memset(longName, 'a', BUF_SIZE - 1);

    longName[BUF_SIZE - 1] = '\0';

    printer->PushAttribute(longName, 42u);

    // Assuming we can verify the output content somehow, this is a placeholder

}



TEST_F(XMLPrinterTest_298, PushAttribute_EmptyName_298) {

    printer->PushAttribute("", 42u);

    // Assuming we can verify the output content somehow, this is a placeholder

}
