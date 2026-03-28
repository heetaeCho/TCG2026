#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_279 : public ::testing::Test {

protected:

    XMLDocument* doc;



    void SetUp() override {

        doc = new XMLDocument();

    }



    void TearDown() override {

        delete doc;

    }

};



TEST_F(XMLDocumentTest_279, LoadFile_ValidFilename_ReturnsXML_SUCCESS_279) {

    // Assuming there is a valid test file named "valid.xml"

    XMLError result = doc->LoadFile("valid.xml");

    EXPECT_EQ(result, XML_SUCCESS);

}



TEST_F(XMLDocumentTest_279, LoadFile_NonExistentFile_ReturnsXML_ERROR_FILE_NOT_FOUND_279) {

    // Assuming there is no file named "non_existent_file.xml"

    XMLError result = doc->LoadFile("non_existent_file.xml");

    EXPECT_EQ(result, XML_ERROR_FILE_NOT_FOUND);

}



TEST_F(XMLDocumentTest_279, LoadFile_NullFilename_ReturnsXML_ERROR_FILE_COULD_NOT_BE_OPENED_279) {

    XMLError result = doc->LoadFile(nullptr);

    EXPECT_EQ(result, XML_ERROR_FILE_COULD_NOT_BE_OPENED);

}



TEST_F(XMLDocumentTest_279, LoadFile_EmptyStringFilename_ReturnsXML_ERROR_FILE_NOT_FOUND_279) {

    XMLError result = doc->LoadFile("");

    EXPECT_EQ(result, XML_ERROR_FILE_NOT_FOUND);

}
