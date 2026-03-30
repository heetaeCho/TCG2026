#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest : public ::testing::Test {

protected:

    void SetUp() override {

        xmlDocument = new XMLDocument();

        xmlUnknown = new XMLUnknown(xmlDocument);

        printer = new XMLPrinter(stdout, false, 0);

    }



    void TearDown() override {

        delete printer;

        delete xmlUnknown;

        delete xmlDocument;

    }



    XMLDocument* xmlDocument;

    XMLUnknown* xmlUnknown;

    XMLPrinter* printer;

};



TEST_F(XMLPrinterTest_322, VisitWithEmptyValue_322) {

    xmlUnknown->SetValue("", false);

    EXPECT_TRUE(printer->Visit(*xmlUnknown));

}



TEST_F(XMLPrinterTest_322, VisitWithNonEmptyValue_322) {

    const char* value = "Some unknown data";

    xmlUnknown->SetValue(value, false);

    EXPECT_TRUE(printer->Visit(*xmlUnknown));

}



TEST_F(XMLPrinterTest_322, VisitWithNullValue_322) {

    xmlUnknown->SetValue(nullptr, false);

    EXPECT_TRUE(printer->Visit(*xmlUnknown));

}
