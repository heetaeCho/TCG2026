#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_114 : public ::testing::Test {

protected:

    XMLDocument doc{true, Whitespace::preserve};

};



TEST_F(XMLDocumentTest_114, ConstructorInitializesErrorIDToXML_SUCCESS_114) {

    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_114, LoadFileNonExistentFileSetsErrorID_114) {

    XMLError result = doc.LoadFile("non_existent_file.xml");

    EXPECT_NE(result, XML_SUCCESS);

    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_114, ParseValidXMLDoesNotSetError_114) {

    const char* xml = R"(<root></root>)";

    XMLError result = doc.Parse(xml, strlen(xml));

    EXPECT_EQ(result, XML_SUCCESS);

    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_114, ParseInvalidXMLSetsErrorID_114) {

    const char* xml = R"(<root></roo>)"; // Invalid closing tag

    XMLError result = doc.Parse(xml, strlen(xml));

    EXPECT_NE(result, XML_SUCCESS);

    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_114, NewElementReturnsNonNullPointer_114) {

    XMLElement* elem = doc.NewElement("test");

    EXPECT_NE(elem, nullptr);

}



TEST_F(XMLDocumentTest_114, DeleteNodeDoesNotCrashOnNull_114) {

    doc.DeleteNode(nullptr); // Should not throw or crash

}



TEST_F(XMLDocumentTest_114, ClearResetsErrorID_114) {

    const char* xml = R"(<root></roo>)"; // Invalid closing tag

    doc.Parse(xml, strlen(xml));

    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);

    doc.Clear();

    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_114, RootElementReturnsNullWhenEmpty_114) {

    XMLElement* root = doc.RootElement();

    EXPECT_EQ(root, nullptr);

}
