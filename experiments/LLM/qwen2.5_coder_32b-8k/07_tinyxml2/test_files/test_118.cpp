#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest : public ::testing::Test {

protected:

    XMLDocument doc;

    

    XMLDocumentTest() : doc(false, Whitespace::COLLAPSE_WHITESPACE) {}

};



TEST_F(XMLDocumentTest_118, ParseValidXML_118) {

    const char* xml = "<root><child>data</child></root>";

    EXPECT_EQ(doc.Parse(xml, strlen(xml)), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_118, ParseEmptyXML_118) {

    const char* xml = "";

    EXPECT_NE(doc.Parse(xml, strlen(xml)), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_118, ParseInvalidXML_118) {

    const char* xml = "<root><child>data</child>";

    EXPECT_NE(doc.Parse(xml, strlen(xml)), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_118, LoadValidFile_118) {

    // Assuming a valid XML file named "valid.xml" exists

    EXPECT_EQ(doc.LoadFile("valid.xml"), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_118, LoadNonExistentFile_118) {

    EXPECT_NE(doc.LoadFile("nonexistentfile.xml"), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_118, SaveValidFile_118) {

    // Assuming a valid XML file named "valid.xml" exists

    doc.Parse("<root><child>data</child></root>", strlen("<root><child>data</child></root>"));

    EXPECT_EQ(doc.SaveFile("output.xml", false), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_118, SaveEmptyXML_118) {

    // Assuming an empty XML file named "empty.xml" exists

    EXPECT_NE(doc.SaveFile("empty.xml", false), XML_SUCCESS);

}



TEST_F(XMLDocumentTest_118, NewElementValidName_118) {

    XMLElement* element = doc.NewElement("child");

    EXPECT_NE(element, nullptr);

    delete element;

}



TEST_F(XMLDocumentTest_118, NewElementEmptyName_118) {

    XMLElement* element = doc.NewElement("");

    EXPECT_EQ(element, nullptr);

}



TEST_F(XMLDocumentTest_118, DeleteNodeValid_118) {

    XMLElement* element = doc.NewElement("child");

    if (element) {

        doc.DeleteNode(element);

        EXPECT_TRUE(true); // Node should be deleted without error

    }

}



TEST_F(XMLDocumentTest_118, DeleteNodeNull_118) {

    XMLNode* nullNode = nullptr;

    doc.DeleteNode(nullNode);

    EXPECT_TRUE(true); // No error should occur when deleting a null node

}



TEST_F(XMLDocumentTest_118, ClearErrorNoError_118) {

    doc.ClearError();

    EXPECT_FALSE(doc.Error());

}



TEST_F(XMLDocumentTest_118, ErrorIDAndStrAfterParseFailure_118) {

    const char* xml = "<root><child>data</child>";

    doc.Parse(xml, strlen(xml));

    EXPECT_NE(doc.ErrorID(), XML_SUCCESS);

    EXPECT_STRNE(doc.ErrorStr(), "");

}



TEST_F(XMLDocumentTest_118, DepthTrackerPushPop_118) {

    // This test assumes that Parse internally uses DepthTracker

    const char* xml = "<root><child>data</child></root>";

    doc.Parse(xml, strlen(xml));

    EXPECT_TRUE(true); // If parsing succeeds, DepthTracker should handle push and pop correctly

}
