// TEST_ID: 143
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleTest_143 : public ::testing::Test {};

TEST_F(XMLConstHandleTest_143, ToElementWithNullNodeReturnsNullptr_143)
{
    const XMLConstHandle handle(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(handle.ToElement(), nullptr);
}

TEST_F(XMLConstHandleTest_143, ToElementWithElementNodeReturnsSamePointer_143)
{
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root><child/></root>"), XML_SUCCESS);

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLConstHandle handle(*root);
    EXPECT_EQ(handle.ToElement(), root);
}

TEST_F(XMLConstHandleTest_143, ToElementWithTextNodeReturnsNullptr_143)
{
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root>text</root>"), XML_SUCCESS);

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLNode* textNode = root->FirstChild();
    ASSERT_NE(textNode, nullptr);

    const XMLConstHandle handle(*textNode);
    EXPECT_EQ(handle.ToElement(), nullptr);
}

TEST_F(XMLConstHandleTest_143, ToElementWithCommentNodeReturnsNullptr_143)
{
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root><!--comment--></root>"), XML_SUCCESS);

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLNode* commentNode = root->FirstChild();
    ASSERT_NE(commentNode, nullptr);

    const XMLConstHandle handle(*commentNode);
    EXPECT_EQ(handle.ToElement(), nullptr);
}

TEST_F(XMLConstHandleTest_143, ToElementWithDocumentNodeReturnsNullptr_143)
{
    XMLDocument doc;
    ASSERT_EQ(doc.Parse("<root/>"), XML_SUCCESS);

    const XMLConstHandle handle(doc);
    EXPECT_EQ(handle.ToElement(), nullptr);
}
