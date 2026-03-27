#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_286 : public ::testing::Test {

protected:

    XMLDocument* doc;

    

    void SetUp() override {

        doc = new XMLDocument(false, Whitespace::COLLAPSE_WHITESPACE);

    }

    

    void TearDown() override {

        delete doc;

    }

};



TEST_F(XMLDocumentTest_286, ErrorIDToName_ValidErrorID_286) {

    EXPECT_STREQ(doc->ErrorIDToName(XML_SUCCESS), "XML_SUCCESS");

}



TEST_F(XMLDocumentTest_286, ErrorIDToName_OutOfBoundsHigh_286) {

    // Assuming XML_ERROR_COUNT is a valid boundary

    EXPECT_DEATH(doc->ErrorIDToName(XML_ERROR_COUNT), "");

}



TEST_F(XMLDocumentTest_286, ErrorIDToName_OutOfBoundsLow_286) {

    EXPECT_DEATH(doc->ErrorIDToName(-1), "");

}
