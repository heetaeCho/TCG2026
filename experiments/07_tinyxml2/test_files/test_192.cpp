#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLNodeTest_192 : public ::testing::Test {

protected:

    void SetUp() override {

        xmlDocument = new XMLDocument();

        xmlNode = new XMLNode(xmlDocument);

    }



    void TearDown() override {

        delete xmlNode;

        delete xmlDocument;

    }



    XMLDocument* xmlDocument;

    XMLNode* xmlNode;

};



TEST_F(XMLNodeTest_192, ParseDeep_ReturnsNullIfErrorSet_192) {

    xmlDocument->SetError(XML_ERROR_PARSING);

    char input[] = "<root></root>";

    StrPair endTag;

    int lineNum = 0;



    char* result = xmlNode->ParseDeep(input, &endTag, &lineNum);



    EXPECT_EQ(result, nullptr);

}



TEST_F(XMLNodeTest_192, ParseDeep_InsertsChildOnSuccessfulParsing_192) {

    char input[] = "<root><child></child></root>";

    StrPair endTag;

    int lineNum = 0;



    xmlNode->ParseDeep(input, &endTag, &lineNum);



    EXPECT_EQ(xmlNode->FirstChild()->Value(), "child");

}



TEST_F(XMLNodeTest_192, ParseDeep_ReturnsNullIfNodeParsingFails_192) {

    char input[] = "<root><child></roo>";

    StrPair endTag;

    int lineNum = 0;



    char* result = xmlNode->ParseDeep(input, &endTag, &lineNum);



    EXPECT_EQ(result, nullptr);

}



TEST_F(XMLNodeTest_192, ParseDeep_SetsErrorOnMismatchedElement_192) {

    char input[] = "<root><child></roo>";

    StrPair endTag;

    int lineNum = 0;



    xmlNode->ParseDeep(input, &endTag, &lineNum);



    EXPECT_EQ(xmlDocument->ErrorID(), XML_ERROR_MISMATCHED_ELEMENT);

}



TEST_F(XMLNodeTest_192, ParseDeep_ReturnsInputPointerOnEmptyEndTagForOpenElement_192) {

    char input[] = "<root><child></child>";

    StrPair endTag;

    int lineNum = 0;



    xmlNode->ParseDeep(input, &endTag, &lineNum);



    EXPECT_EQ(endTag.Empty(), true);

}



TEST_F(XMLNodeTest_192, ParseDeep_TransfersValueToParentEndTagOnClosingElement_192) {

    char input[] = "<root><child></child>";

    StrPair endTag;

    int lineNum = 0;



    xmlNode->ParseDeep(input, &endTag, &lineNum);



    EXPECT_STREQ(endTag.GetStr(), "child");

}



TEST_F(XMLNodeTest_192, ParseDeep_SetsTrackedOnCreatedAndDeletedNode_192) {

    char input[] = "<root><child></child>";

    StrPair endTag;

    int lineNum = 0;



    xmlNode->ParseDeep(input, &endTag, &lineNum);



    EXPECT_TRUE(xmlDocument->_elementPool.Tracked());

}



TEST_F(XMLNodeTest_192, ParseDeep_HandlesDeclarationCorrectly_192) {

    char input[] = "<?xml version=\"1.0\"?><root></root>";

    StrPair endTag;

    int lineNum = 0;



    xmlNode->ParseDeep(input, &endTag, &lineNum);



    EXPECT_EQ(xmlDocument->FirstChild()->ToDeclaration(), nullptr);

}



TEST_F(XMLNodeTest_192, ParseDeep_SetsErrorOnMalformedDeclaration_192) {

    char input[] = "<?xml version=\"1.0\"></root>";

    StrPair endTag;

    int lineNum = 0;



    xmlNode->ParseDeep(input, &endTag, &lineNum);



    EXPECT_EQ(xmlDocument->ErrorID(), XML_ERROR_PARSING_DECLARATION);

}
