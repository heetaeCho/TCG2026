#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest : public ::testing::Test {

protected:

    FILE* dummyFile = nullptr;

    XMLPrinter printer;



    XMLPrinterTest() : printer(dummyFile, false, 0, EscapeAposCharsInAttributes::YES) {}



    virtual ~XMLPrinterTest() {}

};



TEST_F(XMLPrinterTest_299, PushAttributeInt64_NormalOperation_299) {

    printer.PushAttribute("test", static_cast<int64_t>(1234567890));

}



TEST_F(XMLPrinterTest_299, PushAttributeInt64_BoundaryConditionMin_299) {

    printer.PushAttribute("test", INT64_MIN);

}



TEST_F(XMLPrinterTest_299, PushAttributeInt64_BoundaryConditionMax_299) {

    printer.PushAttribute("test", INT64_MAX);

}
