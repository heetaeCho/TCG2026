// TEST_ID: 192
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tinyxml2.h"

using namespace tinyxml2;

class ParseDeepTest_192 : public ::testing::Test {
protected:
    XMLDocument doc;
};

TEST_F(ParseDeepTest_192, SimpleWellFormedXmlParsesSuccessfully_192) {
    const char* xml = "<root><child/></root>";

    const XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_SUCCESS);

    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");
    EXPECT_EQ(root->ChildElementCount(), 1);
    ASSERT_NE(root->FirstChildElement(), nullptr);
    EXPECT_STREQ(root->FirstChildElement()->Name(), "child");
}

TEST_F(ParseDeepTest_192, MismatchedEndTagSetsMismatchedElementError_192) {
    const char* xml = "<root><a></b></root>";

    const XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_MISMATCHED_ELEMENT);

    // Line number should be a positive, observable value if available.
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

TEST_F(ParseDeepTest_192, OpenElementClosedByDifferentParentSetsMismatchedElementError_192) {
    // <a> is closed by </root> which should be a mismatch.
    const char* xml = "<root><a></root>";

    const XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_MISMATCHED_ELEMENT);
}

TEST_F(ParseDeepTest_192, TopLevelUnexpectedClosingTagReportsAnError_192) {
    const char* xml = "</root>";

    const XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());

    // Depending on how the parser classifies the failure at the document level,
    // it may surface as mismatched element or a parsing error.
    const XMLError id = doc.ErrorID();
    EXPECT_TRUE(id == XML_ERROR_MISMATCHED_ELEMENT ||
                id == XML_ERROR_PARSING ||
                id == XML_ERROR_PARSING_ELEMENT);
}

TEST_F(ParseDeepTest_192, MisplacedXmlDeclarationAfterRootReportsParsingDeclarationError_192) {
    // Declaration after an element is considered not "well located" by the ParseDeep logic.
    const char* xml = "<root></root><?xml version=\"1.0\"?>";

    const XMLError err = doc.Parse(xml, strlen(xml));
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_PARSING_DECLARATION);
    EXPECT_GT(doc.ErrorLineNum(), 0);
}

TEST_F(ParseDeepTest_192, EmptyDocumentIsAnError_192) {
    const char* xml = "";

    const XMLError err = doc.Parse(xml, 0);
    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_EMPTY_DOCUMENT);
}
