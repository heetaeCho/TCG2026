#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest : public ::testing::Test {

protected:

    XMLDocument* doc;



    void SetUp() override {

        doc = new XMLDocument();

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(XMLDocumentTest_285, ClearErrorResetsErrorID_285) {

    // Simulate an error condition

    doc->SetError(XML_ERROR_FILE_NOT_FOUND, 10, "Simulated Error");

    EXPECT_EQ(doc->ErrorID(), XML_ERROR_FILE_NOT_FOUND);



    // Call the method under test

    doc->ClearError();



    // Verify that the error ID is reset to success

    EXPECT_EQ(doc->ErrorID(), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_285, ClearErrorResetsErrorLineNum_285) {

    // Simulate an error condition with a line number

    doc->SetError(XML_ERROR_FILE_NOT_FOUND, 10, "Simulated Error");

    EXPECT_EQ(doc->ErrorLineNum(), 10);



    // Call the method under test

    doc->ClearError();



    // Verify that the error line number is reset to 0

    EXPECT_EQ(doc->ErrorLineNum(), 0);

}



TEST_F(XMLDocumentTest_285, ClearErrorResetsErrorStr_285) {

    // Simulate an error condition with an error string

    doc->SetError(XML_ERROR_FILE_NOT_FOUND, 10, "Simulated Error");

    EXPECT_STREQ(doc->ErrorStr(), "Simulated Error");



    // Call the method under test

    doc->ClearError();



    // Verify that the error string is reset to empty

    EXPECT_TRUE(doc->ErrorStr() == nullptr || *doc->ErrorStr() == '\0');

}
