// File: ./TestProjects/tinyxml2/test_xmlelement_querystringattribute_88.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementQueryStringAttributeTest_88 : public ::testing::Test {
protected:
    static XMLElement* ParseAndGetRoot(XMLDocument& doc, const char* xml) {
        const XMLError err = doc.Parse(xml);
        EXPECT_EQ(err, XML_SUCCESS) << "XML parse failed; test XML must be valid.";
        XMLElement* root = doc.RootElement();
        EXPECT_NE(root, nullptr) << "RootElement() returned null; test XML must have a root element.";
        return root;
    }
};

TEST_F(XMLElementQueryStringAttributeTest_88, ReturnsSuccessAndOutputsValuePointer_88) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot(doc, "<root a=\"hello\"/>");

    const char* value = nullptr;
    const XMLError err = root->QueryStringAttribute("a", &value);

    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "hello");
}

TEST_F(XMLElementQueryStringAttributeTest_88, ReturnsNoAttributeWhenMissingAndDoesNotModifyOutParam_88) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot(doc, "<root a=\"present\"/>");

    const char* value = "sentinel";
    const XMLError err = root->QueryStringAttribute("missing", &value);

    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
    EXPECT_STREQ(value, "sentinel");  // should remain unchanged if attribute not found
}

TEST_F(XMLElementQueryStringAttributeTest_88, HandlesEmptyAttributeValue_88) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot(doc, "<root empty=\"\"/>");

    const char* value = nullptr;
    const XMLError err = root->QueryStringAttribute("empty", &value);

    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "");
}

TEST_F(XMLElementQueryStringAttributeTest_88, DecodesEntitiesInAttributeValue_88) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot(doc, "<root a=\"x&amp;y\"/>");

    const char* value = nullptr;
    const XMLError err = root->QueryStringAttribute("a", &value);

    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "x&y");
}

TEST_F(XMLElementQueryStringAttributeTest_88, OverwritesOutputPointerOnSuccess_88) {
    XMLDocument doc;
    XMLElement* root = ParseAndGetRoot(doc, "<root a=\"new\"/>");

    const char* value = "old";
    const XMLError err = root->QueryStringAttribute("a", &value);

    EXPECT_EQ(err, XML_SUCCESS);
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value, "new");
}
