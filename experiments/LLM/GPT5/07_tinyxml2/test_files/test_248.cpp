// File: ./TestProjects/tinyxml2/tinyxml2_querybooltext_test_248.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

class QueryBoolTextTest_248 : public ::testing::Test {
protected:
    static XMLElement* ParseAndGetRoot(XMLDocument& doc, const char* xml) {
        EXPECT_EQ(doc.Parse(xml), XML_SUCCESS);
        XMLElement* root = doc.FirstChildElement();
        EXPECT_NE(root, nullptr);
        return root;
    }
};

TEST_F(QueryBoolTextTest_248, ReturnsSuccessAndParsesTrueFromBoolSetText_248) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);
    doc.InsertEndChild(root);

    root->SetText(true);

    bool value = false;
    const XMLError err = root->QueryBoolText(&value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(QueryBoolTextTest_248, ReturnsSuccessAndParsesFalseFromBoolSetText_248) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);
    doc.InsertEndChild(root);

    root->SetText(false);

    bool value = true;
    const XMLError err = root->QueryBoolText(&value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}

TEST_F(QueryBoolTextTest_248, ReturnsNoTextNodeWhenElementHasNoChildren_248) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);
    doc.InsertEndChild(root);

    bool value = true;  // sentinel
    const XMLError err = root->QueryBoolText(&value);

    EXPECT_EQ(err, XML_NO_TEXT_NODE);
    // Do not assert on "value" mutation here; behavior is not guaranteed by interface.
}

TEST_F(QueryBoolTextTest_248, ReturnsNoTextNodeWhenFirstChildIsNotText_248) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot(doc, "<root><child/></root>");
    ASSERT_NE(root, nullptr);

    bool value = false;
    const XMLError err = root->QueryBoolText(&value);

    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

TEST_F(QueryBoolTextTest_248, ReturnsCanNotConvertTextForNonBooleanString_248) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    ASSERT_NE(root, nullptr);
    doc.InsertEndChild(root);

    root->SetText("not_a_bool");

    bool value = false;
    const XMLError err = root->QueryBoolText(&value);

    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

TEST_F(QueryBoolTextTest_248, ReturnsSuccessForTrueLiteralTextWhenParsedFromXml_248) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot(doc, "<root>true</root>");

    bool value = false;
    const XMLError err = root->QueryBoolText(&value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(value);
}

TEST_F(QueryBoolTextTest_248, ReturnsSuccessForFalseLiteralTextWhenParsedFromXml_248) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot(doc, "<root>false</root>");

    bool value = true;
    const XMLError err = root->QueryBoolText(&value);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(value);
}
