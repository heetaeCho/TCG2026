#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest_317 : public ::testing::Test {

protected:

    FILE* dummyFile;

    XMLDocument doc;

    XMLElement element;

    XMLAttribute attribute;



    void SetUp() override {

        // Open a dummy file for the XMLPrinter

        dummyFile = fopen("dummy.txt", "w");

        ASSERT_NE(dummyFile, nullptr);



        // Initialize XML elements and attributes

        element.SetName("testElement");

        attribute.SetName("testAttribute");

        attribute.SetValue("testValue");

    }



    void TearDown() override {

        // Close the dummy file

        fclose(dummyFile);

    }

};



TEST_F(XMLPrinterTest_317, VisitEnter_ValidElementAndAttribute_ReturnsTrue_317) {

    XMLPrinter printer(dummyFile, false, 0, EscapeAposCharsInAttributes::YES);

    bool result = printer.VisitEnter(element, &attribute);

    EXPECT_TRUE(result);

}



TEST_F(XMLPrinterTest_317, VisitEnter_ValidElementNoAttribute_ReturnsTrue_317) {

    XMLPrinter printer(dummyFile, false, 0, EscapeAposCharsInAttributes::YES);

    bool result = printer.VisitEnter(element, nullptr);

    EXPECT_TRUE(result);

}



TEST_F(XMLPrinterTest_317, VisitEnter_CompactMode_ReturnsTrue_317) {

    XMLPrinter printer(dummyFile, true, 0, EscapeAposCharsInAttributes::YES);

    bool result = printer.VisitEnter(element, &attribute);

    EXPECT_TRUE(result);

}



TEST_F(XMLPrinterTest_317, VisitEnter_ParentElement_CompactMode_ReturnsTrue_317) {

    XMLElement parentElement(&doc);

    parentElement.SetName("parentElement");

    element.SetParent(&parentElement);



    XMLPrinter printer(dummyFile, false, 0, EscapeAposCharsInAttributes::YES);

    bool result = printer.VisitEnter(element, &attribute);

    EXPECT_TRUE(result);

}



TEST_F(XMLPrinterTest_317, VisitEnter_ParentElement_DefaultCompactMode_ReturnsTrue_317) {

    XMLElement parentElement(&doc);

    parentElement.SetName("parentElement");

    element.SetParent(&parentElement);



    XMLPrinter printer(dummyFile, false, 0, EscapeAposCharsInAttributes::YES);

    bool result = printer.VisitEnter(element, &attribute);

    EXPECT_TRUE(result);

}



TEST_F(XMLPrinterTest_317, VisitEnter_NullElement_ReturnsTrue_317) {

    XMLPrinter printer(dummyFile, false, 0, EscapeAposCharsInAttributes::YES);

    bool result = printer.VisitEnter(*static_cast<XMLElement*>(nullptr), &attribute);

    EXPECT_TRUE(result); // Assuming the implementation handles null gracefully

}
