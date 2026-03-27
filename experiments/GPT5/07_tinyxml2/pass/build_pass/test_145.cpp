// File: ./TestProjects/tinyxml2/tests/xmlconsthandle_tounknown_test_145.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLConstHandleToUnknownTest_145 : public ::testing::Test {};

TEST_F(XMLConstHandleToUnknownTest_145, ToUnknown_WithNullNode_ReturnsNull_145)
{
    XMLConstHandle h(static_cast<const XMLNode*>(nullptr));
    EXPECT_EQ(nullptr, h.ToUnknown());
}

TEST_F(XMLConstHandleToUnknownTest_145, ToUnknown_OnElementNode_ReturnsNull_145)
{
    XMLDocument doc;
    ASSERT_EQ(XML_SUCCESS, doc.Parse("<root/>"));

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);

    XMLConstHandle h(*root);
    EXPECT_EQ(nullptr, h.ToUnknown());
}

TEST_F(XMLConstHandleToUnknownTest_145, ToUnknown_OnUnknownNode_ReturnsNonNull_145)
{
    XMLDocument doc;
    // In tinyxml2, constructs like <!DOCTYPE ...> are typically parsed as XMLUnknown.
    ASSERT_EQ(XML_SUCCESS, doc.Parse("<!DOCTYPE foo><root/>"));

    const XMLNode* first = doc.FirstChild();
    ASSERT_NE(nullptr, first);

    XMLConstHandle h(*first);
    const XMLUnknown* unk = h.ToUnknown();
    EXPECT_NE(nullptr, unk);

    // Also verify the returned unknown corresponds to the same underlying node.
    EXPECT_EQ(h.ToNode(), unk);
}

TEST_F(XMLConstHandleToUnknownTest_145, ToUnknown_FromFirstChildNavigation_WorksForUnknown_145)
{
    XMLDocument doc;
    ASSERT_EQ(XML_SUCCESS, doc.Parse("<!DOCTYPE foo><root/>"));

    XMLConstHandle docHandle(doc);
    XMLConstHandle firstChildHandle = docHandle.FirstChild();

    // First child should exist and be the unknown node in this document.
    EXPECT_NE(nullptr, firstChildHandle.ToNode());
    EXPECT_NE(nullptr, firstChildHandle.ToUnknown());
}

TEST_F(XMLConstHandleToUnknownTest_145, ToUnknown_CopyConstructor_PreservesBehavior_145)
{
    XMLDocument doc;
    ASSERT_EQ(XML_SUCCESS, doc.Parse("<!DOCTYPE foo><root/>"));

    XMLConstHandle original(*doc.FirstChild());
    XMLConstHandle copy(original);

    EXPECT_EQ(original.ToNode(), copy.ToNode());
    EXPECT_EQ(original.ToUnknown(), copy.ToUnknown());
}

TEST_F(XMLConstHandleToUnknownTest_145, ToUnknown_AssignmentOperator_PreservesBehavior_145)
{
    XMLDocument doc;
    ASSERT_EQ(XML_SUCCESS, doc.Parse("<!DOCTYPE foo><root/>"));

    XMLConstHandle src(*doc.FirstChild());
    XMLConstHandle dst(static_cast<const XMLNode*>(nullptr));

    dst = src;

    EXPECT_EQ(src.ToNode(), dst.ToNode());
    EXPECT_EQ(src.ToUnknown(), dst.ToUnknown());
}

TEST_F(XMLConstHandleToUnknownTest_145, ToUnknown_WhenDocumentHasNoChildren_ReturnsNull_145)
{
    XMLDocument doc; // empty doc: no children
    XMLConstHandle h(doc);

    XMLConstHandle firstChild = h.FirstChild();
    EXPECT_EQ(nullptr, firstChild.ToNode());
    EXPECT_EQ(nullptr, firstChild.ToUnknown());
}
