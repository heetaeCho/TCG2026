// TEST_ID: 184
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLNodeValueTest_184 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

} // namespace

TEST_F(XMLNodeValueTest_184, DocumentValueIsNull_184) {
    // Observable behavior from interface: XMLNode::Value() returns nullptr for XMLDocument nodes.
    EXPECT_EQ(nullptr, doc_.Value());
}

TEST_F(XMLNodeValueTest_184, DocumentValueIsNullAfterParse_184) {
    doc_.Parse("<root/>");
    EXPECT_EQ(nullptr, doc_.Value());
}

TEST_F(XMLNodeValueTest_184, ElementValueMatchesName_184) {
    XMLElement* root = doc_.NewElement("root");
    ASSERT_NE(nullptr, root);

    doc_.InsertEndChild(root);

    ASSERT_NE(nullptr, doc_.RootElement());
    EXPECT_STREQ("root", doc_.RootElement()->Value());
}

TEST_F(XMLNodeValueTest_184, ElementValueWorksWhenDetached_184) {
    // Boundary-ish: node not attached to any document tree yet.
    XMLElement* e = doc_.NewElement("x");
    ASSERT_NE(nullptr, e);

    EXPECT_STREQ("x", e->Value());
}

TEST_F(XMLNodeValueTest_184, CommentValueMatchesCommentText_184) {
    XMLComment* c = doc_.NewComment("hello");
    ASSERT_NE(nullptr, c);

    doc_.InsertEndChild(c);

    EXPECT_STREQ("hello", c->Value());
}

TEST_F(XMLNodeValueTest_184, TextValueMatchesTextContent_184) {
    XMLElement* root = doc_.NewElement("root");
    ASSERT_NE(nullptr, root);
    doc_.InsertEndChild(root);

    XMLText* t = doc_.NewText("hi");
    ASSERT_NE(nullptr, t);
    root->InsertEndChild(t);

    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(nullptr, firstChild);

    const XMLText* textNode = firstChild->ToText();
    ASSERT_NE(nullptr, textNode);

    EXPECT_STREQ("hi", textNode->Value());
}

TEST_F(XMLNodeValueTest_184, SetValueUpdatesValueForNonDocumentNode_184) {
    XMLElement* e = doc_.NewElement("a");
    ASSERT_NE(nullptr, e);

    // Observable via interface: Value() reflects changes made via SetValue() (for non-document nodes).
    e->SetValue("b", /*staticMem=*/false);
    EXPECT_STREQ("b", e->Value());
}
