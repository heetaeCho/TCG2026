#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <cstdio>



using namespace tinyxml2;



class XMLPrinterTest : public ::testing::Test {

protected:

    virtual void SetUp() {

        _file = fopen("test_output.xml", "w");

        printer = new XMLPrinter(_file, false, 0, EscapeAposCharsInAttributes(false));

    }



    virtual void TearDown() {

        delete printer;

        fclose(_file);

        remove("test_output.xml");

    }



    FILE* _file;

    XMLPrinter* printer;

};



TEST_F(XMLPrinterTest_297, PushAttribute_NameAndIntValue_297) {

    printer->PushAttribute("intAttr", 42);

}



TEST_F(XMLPrinterTest_297, PushAttribute_BoundaryCondition_Zero_297) {

    printer->PushAttribute("zeroAttr", 0);

}



TEST_F(XMLPrinterTest_297, PushAttribute_BoundaryCondition_NegativeValue_297) {

    printer->PushAttribute("negativeAttr", -42);

}



TEST_F(XMLPrinterTest_297, PushAttribute_LargePositiveValue_297) {

    printer->PushAttribute("largePosAttr", 1234567890);

}
