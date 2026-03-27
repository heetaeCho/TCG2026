#include <gtest/gtest.h>

#include <tinyxml2.h>



using namespace tinyxml2;



class XMLDocumentTest_113 : public ::testing::Test {

protected:

    void SetUp() override {

        doc = new XMLDocument(false, Whitespace::preserve);

    }



    void TearDown() override {

        delete doc;

    }



    XMLDocument* doc;

};



TEST_F(XMLDocumentTest_113, ConstructorInitializesErrorToSuccess_113) {

    EXPECT_FALSE(doc->Error());

}



TEST_F(XMLDocumentTest_113, LoadNonExistentFileSetsError_113) {

    XMLError result = doc->LoadFile("non_existent_file.xml");

    EXPECT_EQ(result, XML_ERROR_FILE_NOT_FOUND);

    EXPECT_TRUE(doc->Error());

}



TEST_F(XMLDocumentTest_113, ParseInvalidXMLSetsError_113) {

    const char* invalidXML = "<root><child></root>";

    XMLError result = doc->Parse(invalidXML, strlen(invalidXML));

    EXPECT_EQ(result, XML_ERROR_PARSING_ELEMENT);

    EXPECT_TRUE(doc->Error());

}



TEST_F(XMLDocumentTest_113, ParseValidXMLDoesNotSetError_113) {

    const char* validXML = "<root><child></child></root>";

    XMLError result = doc->Parse(validXML, strlen(validXML));

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_FALSE(doc->Error());

}



TEST_F(XMLDocumentTest_113, ClearErrorResetsErrorState_113) {

    const char* invalidXML = "<root><child></root>";

    XMLError result = doc->Parse(invalidXML, strlen(invalidXML));

    EXPECT_TRUE(doc->Error());



    doc->ClearError();

    EXPECT_FALSE(doc->Error());

}



TEST_F(XMLDocumentTest_113, ProcessEntitiesReturnsConstructorValue_113) {

    EXPECT_FALSE(doc->ProcessEntities());

}



TEST_F(XMLDocumentTest_113, WhitespaceModeReturnsConstructorValue_113) {

    EXPECT_EQ(doc->WhitespaceMode(), Whitespace::preserve);

}



TEST_F(XMLDocumentTest_113, RootElementReturnsNullIfNoRoot_113) {

    EXPECT_EQ(doc->RootElement(), nullptr);

}
