#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest : public ::testing::Test {

protected:

    FILE* dummyFile = fopen("dummy.txt", "w+");

    XMLPrinter printer{dummyFile, false, 0, EscapeAposCharsInAttributes::YES};



    ~XMLPrinterTest() {

        fclose(dummyFile);

    }

};



TEST_F(XMLPrinterTest_302, PushAttribute_Double_NormalOperation_302) {

    printer.PushAttribute("test", 123.456);

}



TEST_F(XMLPrinterTest_302, PushAttribute_Double_BoundaryZero_302) {

    printer.PushAttribute("zero", 0.0);

}



TEST_F(XMLPrinterTest_302, PushAttribute_Double_BoundaryLargePositive_302) {

    printer.PushAttribute("large_positive", std::numeric_limits<double>::max());

}



TEST_F(XMLPrinterTest_302, PushAttribute_Double_BoundaryLargeNegative_302) {

    printer.PushAttribute("large_negative", std::numeric_limits<double>::lowest());

}



TEST_F(XMLPrinterTest_302, PushAttribute_Double_SpecialNaN_302) {

    printer.PushAttribute("nan", std::numeric_limits<double>::quiet_NaN());

}



TEST_F(XMLPrinterTest_302, PushAttribute_Double_SpecialInfinity_302) {

    printer.PushAttribute("infinity", std::numeric_limits<double>::infinity());

}
