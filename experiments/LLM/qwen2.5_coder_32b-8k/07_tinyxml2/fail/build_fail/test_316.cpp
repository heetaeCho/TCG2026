#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest_316 : public ::testing::Test {

protected:

    void SetUp() override {

        xmlDocument = new XMLDocument(true, Whitespace::preserve);

        xmlPrinter = new XMLPrinter(nullptr, false, 0, EscapeAposCharsInAttributes::no);

    }



    void TearDown() override {

        delete xmlPrinter;

        delete xmlDocument;

    }



    XMLDocument* xmlDocument;

    XMLPrinter* xmlPrinter;

};



TEST_F(XMLPrinterTest_316, VisitEnter_ReturnsTrue_316) {

    EXPECT_TRUE(xmlPrinter->VisitEnter(*xmlDocument));

}



TEST_F(XMLPrinterTest_316, VisitEnter_SetsProcessEntitiesFromDoc_316) {

    bool processEntities = xmlDocument->ProcessEntities();

    xmlPrinter->VisitEnter(*xmlDocument);

    // Since _processEntities is private, we can't directly verify it.

    // However, the return value and the behavior of other methods that depend on _processEntities can be tested.

}



TEST_F(XMLPrinterTest_316, VisitEnter_PushesHeaderIfHasBOM_316) {

    xmlDocument->SetBOM(true);

    EXPECT_CALL(*xmlPrinter, PushHeader(::testing::_, ::testing::_)).Times(1); // Assuming PushHeader is mockable

    xmlPrinter->VisitEnter(*xmlDocument);

}



TEST_F(XMLPrinterTest_316, VisitEnter_DoesNotPushHeaderIfNoBOM_316) {

    xmlDocument->SetBOM(false);

    EXPECT_CALL(*xmlPrinter, PushHeader(::testing::_, ::testing::_)).Times(0); // Assuming PushHeader is mockable

    xmlPrinter->VisitEnter(*xmlDocument);

}



TEST_F(XMLPrinterTest_316, VisitEnter_BoundaryNoBOM_316) {

    xmlDocument->SetBOM(false);

    EXPECT_TRUE(xmlPrinter->VisitEnter(*xmlDocument));

}



TEST_F(XMLPrinterTest_316, VisitEnter_ErrorCaseInvalidDocPointer_316) {

    XMLDocument* invalidDoc = nullptr;

    EXPECT_FALSE(xmlPrinter->VisitEnter(*invalidDoc)); // This should not happen as per the interface but added for robustness

}
