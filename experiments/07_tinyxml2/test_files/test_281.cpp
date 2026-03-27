#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_281 : public ::testing::Test {

protected:

    void SetUp() override {

        doc = new XMLDocument(false, Whitespace::preserve);

    }



    void TearDown() override {

        delete doc;

    }



    XMLDocument* doc;

};



TEST_F(XMLDocumentTest_281, SaveFile_Successful_281) {

    const char* filename = "test.xml";

    XMLError result = doc->SaveFile(filename, true);

    EXPECT_EQ(result, XML_SUCCESS);

}



TEST_F(XMLDocumentTest_281, SaveFile_NullFilename_281) {

    const char* filename = nullptr;

    XMLError result = doc->SaveFile(filename, true);

    EXPECT_EQ(result, XML_ERROR_FILE_COULD_NOT_BE_OPENED);

}



TEST_F(XMLDocumentTest_281, SaveFile_FileNotWritable_281) {

    const char* filename = "/nonexistent_directory/test.xml";

    XMLError result = doc->SaveFile(filename, true);

    EXPECT_EQ(result, XML_ERROR_FILE_COULD_NOT_BE_OPENED);

}
